# Minimum version of CMake required to build this project
cmake_minimum_required(VERSION 3.2)

# Use shared libraries, which is the default for the AWS C++ SDK build.
option(BUILD_SHARED_LIBS "Build shared libraries" ON)
message("Hello world ")
# build the sdk targets
project(aws-apigateway-client-lib)
file(GLOB AWS_API_GATEWAY_CLIENT_LIB_HEADERS
     "${CMAKE_SOURCE_DIR}/aws-apigateway-client/include/model/*.h"
     "${CMAKE_SOURCE_DIR}/aws-apigateway-client/include/*.h"
 )
file(GLOB AWS_API_GATEWAY_CLIENT_LIB_SOURCE
     "${CMAKE_SOURCE_DIR}/aws-apigateway-client/source/model/*.cpp"
     "${CMAKE_SOURCE_DIR}/aws-apigateway-client/source/*.cpp"
 )

file(GLOB AWS_API_GATEWAY_CLIENT_LIB_SRC
     "${AWS_API_GATEWAY_CLIENT_LIB_SOURCE}"
     "${AWS_API_GATEWAY_CLIENT_LIB_HEADERS}" 
)
# project directories
set(APIGATEWAY_CLIENT_DIR aws-apigateway-client)

set(SOURCE_FILES
    ${AWS_API_GATEWAY_CLIENT_LIB_SRC})

add_subdirectory(aws-sdk)
add_subdirectory(aws-apigateway-client)

add_executable(
  aws-apigateway-client-lib
  ${AWS_API_GATEWAY_CLIENT_LIB_SRC}
  ${APIGATEWAY_CLIENT_DIR}/Test.cpp
)

target_compile_features(aws-apigateway-client-lib PUBLIC cxx_std_11)

target_link_libraries(aws-apigateway-client-lib PUBLIC ${CMAKE_SOURCE_DIR}/build/aws-sdk/ext/AwsSdk/lib/libaws-cpp-sdk-core.dylib ${CMAKE_SOURCE_DIR}/build/aws-sdk/ext/AwsSdk/lib/libaws-cpp-sdk-sts.dylib aws-apigateway-client-support-lib)
target_include_directories(aws-apigateway-client-lib PUBLIC "${CMAKE_SOURCE_DIR}/build/aws-sdk/ext/AwsSdk/include" "${CMAKE_SOURCE_DIR}/aws-apigateway-client/include")


