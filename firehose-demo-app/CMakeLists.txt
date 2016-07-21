cmake_minimum_required(VERSION 2.6)
project(aws-cpp-sdk-firehose-app)

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
  "${AWS_NATIVE_SDK_ROOT}/aws-cpp-sdk-firehose/include/"
  "${AWS_NATIVE_SDK_ROOT}/aws-cpp-sdk-cognito-identity/include/"
  "${AWS_NATIVE_SDK_ROOT}/aws-cpp-sdk-access-management/include/"  
  "${AWS_NATIVE_SDK_ROOT}/aws-cpp-sdk-iam/include/"
  "${AWS_NATIVE_SDK_ROOT}/testing-resources/include/"
  "*.h"
)

include_directories(${INCLUDE_DIRECTORIES})


SET( FIREHOSE_SOURCES
  firehoseApplication.cpp
  firehoseTests.cpp
)


add_executable(firehose-application ${FIREHOSE_SOURCES})


target_link_libraries(firehose-application
  aws-cpp-sdk-core  
	aws-cpp-sdk-firehose aws-cpp-sdk-access-management aws-cpp-sdk-iam aws-cpp-sdk-cognito-identity 
)

#testing-resources
#copyDlls(firehose-application aws-cpp-sdk-core aws-cpp-sdk-firehose aws-cpp-sdk-access-management aws-cpp-sdk-iam aws-cpp-sdk-cognito-identity)
