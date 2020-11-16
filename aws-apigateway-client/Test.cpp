// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#include<iostream>
#include <aws/core/Aws.h>
#include <aws/core/http/HttpTypes.h>
#include <aws/core/http/HttpClientFactory.h>
#include <aws/core/client/ClientConfiguration.h>
#include <aws/core/http/HttpClient.h>
#include <aws/core/http/HttpResponse.h>
#include <aws/core/http/URI.h>
#include <aws/core/Region.h>
#include <aws/core/auth/AWSAuthSigner.h>
#include <aws/core/auth/AWSAuthSignerProvider.h>
#include <aws/core/utils/memory/stl/AWSStringStream.h>
#include <aws/core/auth/AWSCredentials.h>
#include <aws/core/auth/AWSCredentialsProvider.h>
#include <aws/core/auth/AWSCredentialsProviderChain.h>
#include <aws/sts/model/AssumeRoleRequest.h>
#include <aws/sts/STSClient.h>
#include <GenericApiGatewayClient.h>

using namespace std;
using namespace Aws::Http;
using namespace AwsApiGatewayClientLib::Model;
using namespace AwsApiGatewayClientLib;

int main() {
    Aws::SDKOptions options;
    Aws::InitAPI(options);
    // Fill following values to test
    const char * accessKey = "";
    const char * secretKey = "";
    string apiKey = "";
    const char * roleName = "";
    string apiGatewayBaseEndpoint = "";
    string apiGatewayApiName = "";
    string input = "";

    Aws::Client::ClientConfiguration clientConfiguration = Aws::Client::ClientConfiguration();
    clientConfiguration.scheme = Aws::Http::Scheme::HTTPS;
    clientConfiguration.region = Aws::Region::US_EAST_1;

    // Create STS client to assume role first through the user
    // If the role is not required directly user credentials to create AwsCredentials
    auto stsClientInvokeCredentials = Aws::MakeShared<Aws::Auth::SimpleAWSCredentialsProvider>("api-gateway-client", accessKey, secretKey);
    auto stsClient = Aws::MakeShared<Aws::STS::STSClient>("api-gateway-client", stsClientInvokeCredentials -> GetAWSCredentials(), clientConfiguration);
    auto assumeRoleRequest = Aws::STS::Model::AssumeRoleRequest();
    assumeRoleRequest.SetRoleArn(roleName);
    assumeRoleRequest.SetRoleSessionName("Code-Session"); 
    assumeRoleRequest.SetDurationSeconds(3600);
    auto assumeRoleResult = stsClient -> AssumeRole(assumeRoleRequest).GetResult();

    // Now make request to API gateway    
    auto credentialsProvider = Aws::MakeShared<Aws::Auth::SimpleAWSCredentialsProvider>("api-gateway-client", assumeRoleResult.GetCredentials().GetAccessKeyId(), assumeRoleResult.GetCredentials().GetSecretAccessKey(), assumeRoleResult.GetCredentials().GetSessionToken());
    std::shared_ptr<Aws::StringStream> inputString = Aws::MakeShared<Aws::StringStream>("");
    *inputString << input;
    map<string, string> headerMap;
    headerMap["Content-Type"] = "application/json";
    std::shared_ptr<GenericApiGatewayClient> genericApiGatewayClient = Aws::MakeShared<GenericApiGatewayClient>("api-gateway-client", credentialsProvider, clientConfiguration, apiGatewayBaseEndpoint);
    GenericApiGatewayRequest request = GenericApiGatewayRequest(apiKey, inputString, headerMap, apiGatewayApiName);
    
    auto response = genericApiGatewayClient -> call(request);

    if (response.GetResponseCode() == Aws::Http::HttpResponseCode::OK) {
      cout << "API gateway call succeeded!!\n";
      cout << response.GetOutputStream().rdbuf();
    }
    else {
        cout << "API gateway call failed!!\n";
    }
    Aws::ShutdownAPI(options);
}
