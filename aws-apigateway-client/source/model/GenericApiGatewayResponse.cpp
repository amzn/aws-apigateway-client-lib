#include <model/GenericApiGatewayResponse.h>

namespace AwsApiGatewayClientLib
{
namespace Model 
{
    GenericApiGatewayResponse::GenericApiGatewayResponse(shared_ptr<HttpResponse> httpResponse)
    {
        this -> httpResponse = httpResponse;
    }

    HttpResponseCode GenericApiGatewayResponse::GetResponseCode() {
        return httpResponse -> GetResponseCode();
    }

    const IOStream& GenericApiGatewayResponse::GetOutputStream() {
        return httpResponse -> GetResponseBody();
    }
}

}