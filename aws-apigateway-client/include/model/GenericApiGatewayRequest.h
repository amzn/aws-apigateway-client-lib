// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#include <aws/core/utils/memory/stl/AWSStreamFwd.h>
#include <map>

using namespace std;
using namespace Aws;

namespace AwsApiGatewayClientLib
{
namespace Model 
{
    /**
     * Model class that encapsulates all the parameters required to make a generic AWS ApiGateway call.
     */
    class GenericApiGatewayRequest 
    {
    public:
        GenericApiGatewayRequest(string apiKey, shared_ptr<IOStream> inputStream, map<string, string> headers, string resourcePath);
        
        /**
         * Method to provide api key for this request.
         */
        string GetApiKey();
        /**
         * Method to provide input as stream for this request .
         */
        shared_ptr<IOStream> GetInputStream();
        /**
         * Method to provide headers that needs to be set in the request.
         */
        map<string, string> GetHeaders();
        /**
         * Method to provide the resource path that needs to be appened to a root path.
         */
        string GetResourcePath();
    private:
        /**
         * API Key to be used in the request
         */
        string apiKey;

        /**
         * Pointer to input stream that can be used to invoke the request.
         */
        shared_ptr<IOStream> inputStream;

        /**
         * Map containing header value pairs that needs to be set during request.
         */
        map<string, string> headers;

        /**
         * API end point path, that specifies the specific API that needs to be called.
         */
        string resourcePath;
    };
}
}
