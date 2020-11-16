// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#include <GenericApiGatewayClient.h>
#include <aws/core/http/HttpResponse.h>
#include <aws/core/http/URI.h>
#include <aws/core/http/HttpTypes.h>
#include <aws/core/http/HttpClientFactory.h>

using namespace std;
using namespace Aws;
using namespace Aws::Client;
using namespace Aws::Utils::Stream;

namespace AwsApiGatewayClientLib
{
    static const string AWS_API_GATEWAY_OPERATION = "execute-api";
    static const string CONTENT_TYPE_HEADER_KEY = "Content-Type";
    static const string AWS_API_GATEWAY_API_KEY_HEADER = "x-api-key";

    GenericApiGatewayClient::GenericApiGatewayClient(shared_ptr<AWSCredentialsProvider> awsCredentialsProvider, ClientConfiguration clientConfiguration, string endpoint)
    {
        this -> authV4Signer = MakeShared<AWSAuthV4Signer>("", awsCredentialsProvider, AWS_API_GATEWAY_OPERATION.c_str(), clientConfiguration.region);
        this -> httpClient = CreateHttpClient(clientConfiguration);
        this -> endpoint = endpoint;
    }

    GenericApiGatewayResponse GenericApiGatewayClient::call(GenericApiGatewayRequest request)
    {   
        string fullyQualifiedEndpoint = GetFullyQualifiedEndpoint(endpoint, request.GetResourcePath());
        shared_ptr<HttpRequest> httpRequest(CreateHttpRequest(String(fullyQualifiedEndpoint.c_str(), fullyQualifiedEndpoint.size()),
                                             HttpMethod::HTTP_POST, // i.e. HttpMethod::HTTP_POST
                                             DefaultResponseStreamFactoryMethod));
        // set input body
        httpRequest -> AddContentBody(request.GetInputStream());
        // set headers
        map<string, string> headers = request.GetHeaders();
        for( auto it = headers.begin(); it != headers.end(); ++it )
        {
            string headerKey = it -> first;
            string headerValue = it -> second;
            if (headerKey == CONTENT_TYPE_HEADER_KEY) {
                httpRequest -> SetContentType(String(headerValue.c_str(), headerValue.size()));
            } else {
                httpRequest -> SetHeaderValue(String(headerKey.c_str(), headerKey.size()), String(headerValue.c_str(), headerValue.size()));
            }
        }
        // set api key
        httpRequest -> SetHeaderValue(String(AWS_API_GATEWAY_API_KEY_HEADER.c_str(), AWS_API_GATEWAY_API_KEY_HEADER.size()), String(request.GetApiKey().c_str(), request.GetApiKey().size()));
        // sign request
        authV4Signer -> SignRequest(*httpRequest);
        // call and adapt
        return GenericApiGatewayResponse(httpClient -> MakeRequest(httpRequest));
    }

    string GenericApiGatewayClient::GetFullyQualifiedEndpoint(string endpoint, string resourcePath)
    {
        return endpoint + resourcePath;
    }
}
