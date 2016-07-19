#pragma once

#include <aws/sqs/SQSClient.h>

class sqsApplication
{
  private:
    Aws::String m_accountId;
    std::shared_ptr<Aws::SQS::SQSClient> sqsClient;
    Aws::String m_queuename;
    Aws::String m_queueUrl;

  private: //functions
    void init();
  public:
    sqsApplication();
    ~sqsApplication();
    
    void initQueue();
    void sendMessage(int amount);
    bool receiveMessage(Aws::String &handle);
    void deleteMessage(Aws::String handle);
};
