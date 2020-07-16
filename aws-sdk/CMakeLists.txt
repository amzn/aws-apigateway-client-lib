cmake_minimum_required(VERSION 3.2)

project(aws-sdk)

include(${CMAKE_ROOT}/Modules/ExternalProject.cmake)

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

include(AwsSdk)

