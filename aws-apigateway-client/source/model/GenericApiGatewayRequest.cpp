#include <model/GenericApiGatewayRequest.h>

namespace AwsApiGatewayClientLib
{
namespace Model 
{
    GenericApiGatewayRequest::GenericApiGatewayRequest(string apiKey, shared_ptr<IOStream> inputStream, map<string, string> headers, string resourcePath)
    {
        this -> apiKey = apiKey;
        this -> headers = headers;
        this -> inputStream = inputStream;
        this -> resourcePath = resourcePath;
        this -> inputStream = inputStream;
    }

    string GenericApiGatewayRequest::GetApiKey()
    {
        return apiKey;
    }

    shared_ptr<IOStream> GenericApiGatewayRequest::GetInputStream()
    {
        return inputStream;
    }

    map<string, string> GenericApiGatewayRequest::GetHeaders()
    {
        return headers;
    }

    string GenericApiGatewayRequest::GetResourcePath()
    {
        return resourcePath;
    }
}

}