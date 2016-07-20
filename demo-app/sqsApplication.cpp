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


//TBD; TODO; are all these includes required.

#include <aws/core/client/ClientConfiguration.h>
#include <aws/core/client/CoreErrors.h>
#include <aws/core/auth/AWSCredentialsProviderChain.h>
#include <aws/core/utils/json/JsonSerializer.h>
#include <aws/core/utils/xml/XmlSerializer.h>

#include <aws/sqs/model/CreateQueueRequest.h>
#include <aws/sqs/model/ListQueuesRequest.h>
#include <aws/sqs/model/DeleteQueueRequest.h>
#include <aws/sqs/model/SendMessageRequest.h>
#include <aws/sqs/model/ReceiveMessageRequest.h>
#include <aws/sqs/model/DeleteMessageRequest.h>
#include <aws/sqs/model/GetQueueAttributesRequest.h>
#include <aws/sqs/model/SetQueueAttributesRequest.h>
#include <aws/sqs/model/AddPermissionRequest.h>
#include <aws/sqs/model/RemovePermissionRequest.h>
#include <aws/sqs/model/ListDeadLetterSourceQueuesRequest.h>
#include <aws/core/utils/Outcome.h>
#include <aws/sqs/model/ChangeMessageVisibilityBatchRequestEntry.h>
#include <aws/sqs/model/ChangeMessageVisibilityBatchRequest.h>
#include <aws/sqs/model/SendMessageBatchRequestEntry.h>
#include <aws/sqs/model/SendMessageBatchRequest.h>
#include <aws/access-management/AccessManagementClient.h>
#include <aws/iam/IAMClient.h>
#include <aws/cognito-identity/CognitoIdentityClient.h>
#include <aws/core/utils/memory/stl/AWSStringStream.h>

#include "sqsApplication.h"


//#define DEBUG_INFO 

using namespace std;
using namespace Aws::Http;
using namespace Aws;
using namespace Aws::Auth;
using namespace Aws::Client;
using namespace Aws::SQS;
using namespace Aws::SQS::Model;
using namespace Aws::Utils::Json;

static const int DATA_SIZE = (1024 * 100); //~200 KB 

//Constructor
sqsApplication::sqsApplication(Aws::String queueName) :
  m_queuename(queueName),
  m_queueUrl("")
{
  init();
}

//destructor
sqsApplication::~sqsApplication()
{

}

void sqsApplication::initQueue()
{
#ifdef DEBUG_INFO
  cout << "Starting Queue" << endl;
#endif
  CreateQueueRequest request;
  request.SetQueueName(m_queuename);

  bool shouldContinue = true;
  while (shouldContinue)
  {
    CreateQueueOutcome outcome = sqsClient->CreateQueue(request);
    if (outcome.IsSuccess())
    {
#ifdef DEBUG_INFO
        cout << "Success, QUEUE-URL: " << outcome.GetResult().GetQueueUrl() << endl;
#endif
        m_queueUrl = outcome.GetResult().GetQueueUrl() ;
    }
    if (outcome.GetError().GetErrorType() != SQSErrors::QUEUE_DELETED_RECENTLY)
    {
      break;
    }
    this_thread::sleep_for(chrono::seconds(1));
  }
}


void sqsApplication::sendMessage(int amount)
{
    // current date/time based on current system
    SendMessageRequest sendMessageRequest;
    MessageAttributeValue stringAttributeValue;
    MessageAttributeValue binaryAttributeValue;

    stringAttributeValue.SetStringValue("TestString");
    stringAttributeValue.SetDataType("String");
    sendMessageRequest.AddMessageAttributes("TestStringAttribute", stringAttributeValue);
    
    Aws::Utils::ByteBuffer byteBuffer(DATA_SIZE);
        
    unsigned i = 0;
    
    for(i; i < DATA_SIZE; ++i)
    {
        byteBuffer[i] = (unsigned char)i;
    }
    
#ifdef DEBUG_INFO
    cout << " Sending Test Messages " << amount << endl;
#endif

    binaryAttributeValue.SetBinaryValue(byteBuffer);
    binaryAttributeValue.SetDataType("Binary");
    sendMessageRequest.AddMessageAttributes("TestBinaryAttribute", binaryAttributeValue);

    sendMessageRequest.SetQueueUrl(m_queueUrl);
    
    for(int i = 0; i < amount; i++)
    {
      time_t now = time(0);
      Aws::String date = "TestMessageBody ";
      date = date + ctime(&now);
#ifdef DEBUG_INFO
      cout << date << endl;
#endif
      sendMessageRequest.SetMessageBody(date);
    
      SendMessageOutcome sendMessageOutcome = sqsClient->SendMessage(sendMessageRequest);
      
      if(!sendMessageOutcome.IsSuccess())
      {
        cout << "Message outcome is not Successfull" << endl;
        return;
      }
    }
};

bool sqsApplication::receiveMessage(Aws::String &handle)
{
    ReceiveMessageRequest receiveMessageRequest;
    receiveMessageRequest.SetMaxNumberOfMessages(1);
    receiveMessageRequest.SetQueueUrl(m_queueUrl);
    receiveMessageRequest.AddMessageAttributeNames("All");

    ReceiveMessageOutcome receiveMessageOutcome = sqsClient->ReceiveMessage(receiveMessageRequest);
    if(!(receiveMessageOutcome.IsSuccess()))
    {
      cout << "FAILED to Receive message" << endl;
      return false;
    }
    ReceiveMessageResult receiveMessageResult = receiveMessageOutcome.GetResult();
    
    if(receiveMessageResult.GetMessages().size() != 1)
    {
       //cout << "Received size is not 1; " << receiveMessageResult.GetMessages().size() << endl;
       return false;
    }
    
    cout << "Received MSG,  (Body: " << receiveMessageResult.GetMessages()[0].GetBody() << ")." << endl;

    //set handle to parameter, to return it.
    handle = receiveMessageResult.GetMessages()[0].GetReceiptHandle();
    return true;
    
}

void sqsApplication::deleteMessage(Aws::String receiptHandle)
{
    DeleteMessageRequest deleteMessageRequest;
    deleteMessageRequest.SetQueueUrl(m_queueUrl);
    deleteMessageRequest.SetReceiptHandle(receiptHandle);

    DeleteMessageOutcome deleteMessageOutcome = sqsClient->DeleteMessage(deleteMessageRequest);
    if(!deleteMessageOutcome.IsSuccess())
    {
      cout << "Message Deletion did not succeed" << endl;
    }else{ 
#ifdef DEBUG_INFO
      cout << "Message Deletion succeeded" << endl; 
#endif
    }
#ifdef DEBUG_INFO
    cout << "Deleting QUEUE Request" << endl;
#endif
    DeleteQueueRequest deleteQueueRequest;
    deleteQueueRequest.WithQueueUrl(m_queueUrl);

    DeleteQueueOutcome deleteQueueOutcome = sqsClient->DeleteQueue(deleteQueueRequest);
}

//private
void sqsApplication::init()
{
  ClientConfiguration config;
  config.scheme = Scheme::HTTPS;
  config.region = Region::EU_CENTRAL_1;
  
  sqsClient = Aws::MakeShared<SQSClient>("QueueOperationTest", Aws::MakeShared<DefaultAWSCredentialsProviderChain>("QueueOperationTest"), config);
        
  auto cognitoClient = Aws::MakeShared<Aws::CognitoIdentity::CognitoIdentityClient>("QueueOperationTest", config);

  auto iamClient = Aws::MakeShared<Aws::IAM::IAMClient>("QueueOperationTest", config);
  Aws::AccessManagement::AccessManagementClient accessManagementClient(iamClient, cognitoClient);
  m_accountId = accessManagementClient.GetAccountId();
}
