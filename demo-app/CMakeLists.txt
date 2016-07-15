cmake_minimum_required(VERSION 2.6)
project(aws-cpp-sdk-sqs-demo-app)

IF (NOT CMAKE_BUILD_TYPE)

  SET(CMAKE_BUILD_TYPE "Debug")
ELSE()

  SET(CMAKE_BUILD_TYPE "Release")

ENDIF (NOT CMAKE_BUILD_TYPE)

OPTION(BUILD_SHARED_LIBS "Use shared libraries" OFF)

#no optimalisation for eclipse debugging
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O0 -g")


set(INCLUDE_DIRECTORIES
  "${AWS_NATIVE_SDK_ROOT}/aws-cpp-sdk-core/include/"
  "${AWS_NATIVE_SDK_ROOT}/aws-cpp-sdk-sqs/include/"
  "${AWS_NATIVE_SDK_ROOT}/aws-cpp-sdk-cognito-identity/include/"
  "${AWS_NATIVE_SDK_ROOT}/aws-cpp-sdk-access-management/include/"  
  "${AWS_NATIVE_SDK_ROOT}/aws-cpp-sdk-iam/include/"
  "${AWS_NATIVE_SDK_ROOT}/testing-resources/include/"
  "*.h"
)

include_directories(${INCLUDE_DIRECTORIES})


SET( TEST_SOURCES
  sqsApplication.cpp
  RunTests.cpp
)

SET( READ_TEST_SOURCES
  sqsApplication.cpp
  RunListener.cpp
)

add_executable(sqs-writer-application ${TEST_SOURCES})

add_executable(read-application ${READ_TEST_SOURCES})

target_link_libraries(sqs-writer-application
  aws-cpp-sdk-core  
	aws-cpp-sdk-sqs aws-cpp-sdk-access-management aws-cpp-sdk-iam aws-cpp-sdk-cognito-identity 
)

target_link_libraries(read-application
  aws-cpp-sdk-core  
	aws-cpp-sdk-sqs aws-cpp-sdk-access-management aws-cpp-sdk-iam aws-cpp-sdk-cognito-identity 
)
#testing-resources
#copyDlls(runSqsIntegrationTests aws-cpp-sdk-core aws-cpp-sdk-sqs aws-cpp-sdk-access-management aws-cpp-sdk-iam aws-cpp-sdk-cognito-identity)
