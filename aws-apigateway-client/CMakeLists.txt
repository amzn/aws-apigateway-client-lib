
set(API_GATEWAY_CLIENT_LIB_INCLUDES
    "${CMAKE_CURRENT_SOURCE_DIR}/include/"
  )
set(CMAKE_CXX_STANDARD 11)
add_library(aws-apigateway-client-support-lib "${CMAKE_SOURCE_DIR}/aws-apigateway-client/include/model/GenericApiGatewayRequest.h" "${CMAKE_SOURCE_DIR}/aws-apigateway-client/source/model/GenericApiGatewayRequest.cpp" "${CMAKE_SOURCE_DIR}/aws-apigateway-client/include/model/GenericApiGatewayResponse.h" "${CMAKE_SOURCE_DIR}/aws-apigateway-client/source/model/GenericApiGatewayResponse.cpp" "${CMAKE_SOURCE_DIR}/aws-apigateway-client/include/GenericApiGatewayClient.h" "${CMAKE_SOURCE_DIR}/aws-apigateway-client/source/GenericApiGatewayClient.cpp")


include_directories("${CMAKE_SOURCE_DIR}/build/aws-sdk/ext/AwsSdk/include" ${API_GATEWAY_CLIENT_LIB_INCLUDES})
target_link_libraries(aws-apigateway-client-support-lib PUBLIC ${CMAKE_SOURCE_DIR}/build/aws-sdk/ext/AwsSdk/lib/libaws-cpp-sdk-core.dylib ${CMAKE_SOURCE_DIR}/build/aws-sdk/ext/AwsSdk/lib/libaws-cpp-sdk-sts.dylib)
