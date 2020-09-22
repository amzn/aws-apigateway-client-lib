# AWS API Gateway client library for C++
AWS API Gateway client library provides a modern C++ (version C++ 11 or later) interface to call API Gateway using minimumal attributes like api key, AWS credentials and input. It provides a GenericApiGatewayClient class that abstracts request signing and http request calls to complete API Gateway client. 

## Features
* AWS SigV4 signing using IAM auth credentials.
* API keys and customer headers
* Compatibility with existing client configuration supported by AWS
* Supports loosely-typed API calls to api gateway in absence of an official AWS API Gateway SDK.

# Getting Started

## From source:
```
# git clone first and then execute following commands
mkdir build/
cd build
cmake ..
make

# To test
./aws-apigateway-client-lib
```
## Sample Usage:

Sample usage can be found here [link to file once the git project is uploaded].
