#pragma once

#include <aws/firehose/FirehoseClient.h>
#include <aws/core/client/ClientConfiguration.h>
#include <aws/core/utils/memory/stl/AWSStringStream.h>

class firehoseApp
{
  private:
    Aws::Client::ClientConfiguration m_config;
    Aws::Firehose::FirehoseClient *m_firehoseClient;
    Aws::String m_streamName;

  private: //functions
    bool init();
  public:
    firehoseApp(Aws::String name);
    ~firehoseApp();
    
    bool initQueue();
    
    bool sendMessage(const Aws::StringStream& data, int repetitions = 0);
    /*
    bool receiveMessage(Aws::String &handle);
    void deleteMessage(Aws::String handle);
    * */
};
