include(FindGit)
find_package(Git)

if (NOT Git_FOUND)
	message(FATAL_ERROR "Git not found!")
endif ()

include (ExternalProject)

set (EP_AWSSDK "AwsSdk")

ExternalProject_Add(${EP_AWSSDK}
	PREFIX ${EP_AWSSDK}
	GIT_REPOSITORY https://github.com/aws/aws-sdk-cpp.git
	GIT_TAG 44f616a5c87cf26a6dee30583c9c1ba176206619
	GIT_SHALLOW    ON
	BUILD_ALWAYS   OFF
	UPDATE_COMMAND ""
	INSTALL_DIR    ${CMAKE_CURRENT_BINARY_DIR}/ext/${EP_AWSSDK}
	CMAKE_CACHE_ARGS
		-DBUILD_SHARED_LIBS:BOOL=ON
		-DENABLE_STATIC_RUNTIME:BOOL=OFF
		-DBUILD_EXAMPLES:BOOL=ON
		-DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR>
)

include_directories(${CMAKE_CURRENT_BINARY_DIR}/ext/${EP_AWSSDK})
