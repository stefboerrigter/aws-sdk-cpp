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
//Listener
//#include <aws/external/gtest.h>
#include <aws/core/Aws.h>
#include "sqsApplication.h"

#include <unistd.h>

int main(int argc, char** argv)
{
    Aws::SDKOptions options;
    Aws::String handle;
    options.loggingOptions.logLevel = Aws::Utils::Logging::LogLevel::Trace;
    Aws::InitAPI(options);
       
    sqsApplication app;
    app.initQueue();

    while(true)
    {
      if(app.receiveMessage(handle))
      {
        app.deleteMessage(handle);
      }else{
        usleep(1000);//sleep for a little while
      }
    }
    
    Aws::ShutdownAPI(options);
    return 0;
}



