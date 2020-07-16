#include <model/GenericApiGatewayRequest.h>
#include <model/GenericApiGatewayResponse.h>
#include <aws/core/client/ClientConfiguration.h>
#include <aws/core/auth/AWSAuthSigner.h>
#include <aws/core/auth/AWSCredentialsProvider.h>
#include <aws/core/http/HttpTypes.h>
#include <aws/core/http/HttpClient.h>

using namespace std;
using namespace Aws;
using namespace Aws::Auth;
using namespace Aws::Client;
using namespace AwsApiGatewayClientLib::Model;

namespace AwsApiGatewayClientLib
{
    /**
     * Generic api gateway client class to be used for making api gateway class.
     */
    class GenericApiGatewayClient
    {
    public:
        GenericApiGatewayClient(shared_ptr<AWSCredentialsProvider> awsCredentialsProvider, ClientConfiguration clientConfiguration, string endpoint);
        /**
         * Method to make a call to api gateway using parameter provided in GenericApiGatewayRequest.
         */
        GenericApiGatewayResponse call(GenericApiGatewayRequest request);
    private:
        /**
         * Auth signer for api gateway request.
         */
        shared_ptr<AWSAuthV4Signer> authV4Signer;
        /**
         * Http client to make api gateway rest call.
         */
        shared_ptr<HttpClient> httpClient;
        /**
         * Base endpoint to be used for making request to api gateway endpoint.
         */
        string endpoint;
        /**
         * Method to provide fully qualified endpoint for making api gateway call. Takes endpoint and resource path as 
         * input and merges them to return exact api gateway endpoint.
         */
        string GetFullyQualifiedEndpoint(string endpoint, string resourcePath);
    };
}