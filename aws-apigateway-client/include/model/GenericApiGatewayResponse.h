#include <aws/core/http/HttpResponse.h>

using namespace std;
using namespace Aws;
using namespace Aws::Http;

namespace AwsApiGatewayClientLib
{
namespace Model 
{
    /**
     * Model class that encapsulates all the parameters required to make a generic AWS ApiGateway call.
     */
    class GenericApiGatewayResponse 
    {
    public:
        GenericApiGatewayResponse(shared_ptr<HttpResponse> httpResponse);
        
        /**
         * Method to provide response code for the http response.
         */
        HttpResponseCode GetResponseCode();
        /**
         * Method to provide output as stream for http response.
         */
        const IOStream& GetOutputStream();
    private:
        /**
         * Http response received after making api gateway call.
         */
        shared_ptr<HttpResponse> httpResponse;
    };
}
}