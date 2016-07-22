/*
 * Copyright 2010-2015 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 * 
 * Licensed under the Apache License, Version 2.0 (the "License").
 * You may not use this file except in compliance with the License.
 * A copy of the License is located at
 * 
 *  http://aws.amazon.com/apache2.0
 * 
 * or in the "license" file accompanying this file. This file is distributed
 * on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
 * express or implied. See the License for the specific language governing
 * permissions and limitations under the License.
 */


//TBD; TODO; are all these includes required.?

#include <aws/core/client/ClientConfiguration.h>
#include <aws/core/client/CoreErrors.h>
#include <aws/core/auth/AWSCredentialsProviderChain.h>
#include <aws/core/utils/json/JsonSerializer.h>
#include <aws/core/utils/xml/XmlSerializer.h>

#include <aws/core/utils/Outcome.h>
#include <aws/access-management/AccessManagementClient.h>
#include <aws/iam/IAMClient.h>
#include <aws/cognito-identity/CognitoIdentityClient.h>
#include <aws/core/utils/memory/stl/AWSStringStream.h>

//Verified includes:
#include <aws/firehose/model/CreateDeliveryStreamRequest.h>
#include <aws/firehose/model/S3DestinationConfiguration.h>

#include <aws/firehose/model/PutRecordRequest.h>


#include "firehoseApplication.h"
#include <fstream>


#define DEBUG_INFO 

using namespace std;
using namespace Aws::Http;
using namespace Aws;
using namespace Aws::Auth;
using namespace Aws::Client;
using namespace Aws::Client;
using namespace Aws::Firehose;
using namespace Aws::Firehose::Model;
using namespace Aws::Utils::Json;

static const int DATA_SIZE = (1024 * 200); //~200 KB 

//Constructor
firehoseApp::firehoseApp(Aws::String streamName) :
  m_firehoseClient(nullptr),
  m_streamName(streamName),
  m_initialized(false)
{
  if(init())
  {
    m_initialized = true;
  }
  std::ifstream fc("demofile.txt", std::ios_base::in | std::ios_base::binary);
  m_buffer << fc.rdbuf();
#ifdef DEBUG_INFO
  cout << "Reading File Done" << endl;
#endif
}

//destructor
firehoseApp::~firehoseApp()
{

}

void firehoseApp::sendMessage(int amount)
{
  if(!m_initialized){ 
    return;
  }
  
  PutRecordRequest request;
  request.SetDeliveryStreamName(m_streamName);
  Record record;
#ifdef DEBUG_INFO  
  cout << "Buff Size to transfer: [" << m_buffer.str().length() << "]" << endl;
#endif
  Aws::Utils::ByteBuffer buff((unsigned char*)m_buffer.str().c_str(), m_buffer.str().length());
  
  {
    record.SetData(buff);
  }
  request.SetRecord(record);//putRecordList);
  for(int i = 0; i < amount; i++)
  {
    Model::PutRecordOutcome outcome = m_firehoseClient->PutRecord(request);
    if(!outcome.IsSuccess())
    {
      cout << "Error sending message " << i + 1 << "." << endl;
      i = amount;
    }
  }
}

//private
bool firehoseApp::init()
{
  ClientConfiguration config;
  config.scheme = Scheme::HTTPS;
  //config.region = Region::EU_WEST_1;
  config.region = Region::US_EAST_1;
  
  m_firehoseClient = new FirehoseClient(config);
  //m_firehoseClient = Aws::MakeShared<FirehoseClient>("QueueOperationTest", Aws::MakeShared<DefaultAWSCredentialsProviderChain>("QueueOperationTest"), config);
  
  auto cognitoClient = Aws::MakeShared<Aws::CognitoIdentity::CognitoIdentityClient>("QueueOperationTest", config);

  auto iamClient = Aws::MakeShared<Aws::IAM::IAMClient>("QueueOperationTest", config);
  Aws::AccessManagement::AccessManagementClient accessManagementClient(iamClient, cognitoClient);
  
  Aws::String m_accountId = accessManagementClient.GetAccountId();
  
  Aws::String user;
  Aws::IAM::Model::User data;
  
  accessManagementClient.GetUser(user, data);
#ifdef DEBUG_INFO 
  cout << "Account ID : " << m_accountId << user <<endl;
#endif
  
  CreateDeliveryStreamRequest request;
  request.SetDeliveryStreamName(m_streamName);
  
  S3DestinationConfiguration s3Config;

  //TBD; role is fixed now... 
  Aws::String roleARN = "arn:aws:iam::" + m_accountId + ":role/firehose_delivery_role";
  
  s3Config.SetRoleARN(roleARN);
  s3Config.SetBucketARN("arn:aws:s3:::testbucketstef");
  s3Config.SetPrefix("stef_");
  s3Config.SetBufferingHints(BufferingHints());
  s3Config.SetCompressionFormat(CompressionFormat::UNCOMPRESSED);
  s3Config.SetEncryptionConfiguration(EncryptionConfiguration());
  request.SetS3DestinationConfiguration(s3Config);
  
  CreateDeliveryStreamOutcome outcome = m_firehoseClient->CreateDeliveryStream(request);
  if (outcome.IsSuccess())
  {
    cout << "Succesfull created new deliverystream [" << m_streamName << "]" << endl ;
    return true;
  }else if (outcome.GetError().GetErrorType() == FirehoseErrors::RESOURCE_IN_USE){
#ifdef DEBUG_INFO
    cout << "Resource in use, stream [" << m_streamName << "] exists already"<< endl;
#endif
    return true;
  }else if (outcome.GetError().GetErrorType() == FirehoseErrors::LIMIT_EXCEEDED){
    cout << "Limit Exceeded "<< endl;
  }else if (outcome.GetError().GetErrorType() == FirehoseErrors::UNKNOWN){
    cout << "Unknown error "<< endl;
  }else if (outcome.GetError().GetErrorType() == FirehoseErrors::ACCESS_DENIED){
    cout << "Access Denied "<< endl;
  }else{
    cout << "Other error.... "<< endl;
  }
  return false;
}
