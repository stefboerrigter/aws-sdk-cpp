#pragma once

#include <aws/firehose/FirehoseClient.h>

class firehoseApp
{
  private:
    //Aws::String m_accountId;
    //std::shared_ptr<Aws::Firehose::FirehoseClient> m_firehoseClient;
    Aws::Firehose::FirehoseClient *m_firehoseClient;
    Aws::String m_streamName;
    //Aws::String m_queueUrl;
    bool m_initialized;
    Aws::StringStream m_buffer;

  private: //functions
    bool init();
  public:
    firehoseApp(Aws::String name);
    ~firehoseApp();
    
    /*void initQueue();*/
    void sendMessage(int amount);
    /*
    bool receiveMessage(Aws::String &handle);
    void deleteMessage(Aws::String handle);
    * */
};
