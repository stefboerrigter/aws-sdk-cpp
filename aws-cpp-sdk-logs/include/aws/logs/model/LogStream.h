/*
* Copyright 2010-2016 Amazon.com, Inc. or its affiliates. All Rights Reserved.
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
#pragma once
#include <aws/logs/CloudWatchLogs_EXPORTS.h>
#include <aws/core/utils/memory/stl/AWSString.h>

namespace Aws
{
namespace Utils
{
namespace Json
{
  class JsonValue;
} // namespace Json
} // namespace Utils
namespace CloudWatchLogs
{
namespace Model
{

  /**
   * <p>A log stream is sequence of log events from a single emitter of logs.</p>
   */
  class AWS_CLOUDWATCHLOGS_API LogStream
  {
  public:
    LogStream();
    LogStream(const Aws::Utils::Json::JsonValue& jsonValue);
    LogStream& operator=(const Aws::Utils::Json::JsonValue& jsonValue);
    Aws::Utils::Json::JsonValue Jsonize() const;

    
    inline const Aws::String& GetLogStreamName() const{ return m_logStreamName; }

    
    inline void SetLogStreamName(const Aws::String& value) { m_logStreamNameHasBeenSet = true; m_logStreamName = value; }

    
    inline void SetLogStreamName(Aws::String&& value) { m_logStreamNameHasBeenSet = true; m_logStreamName = value; }

    
    inline void SetLogStreamName(const char* value) { m_logStreamNameHasBeenSet = true; m_logStreamName.assign(value); }

    
    inline LogStream& WithLogStreamName(const Aws::String& value) { SetLogStreamName(value); return *this;}

    
    inline LogStream& WithLogStreamName(Aws::String&& value) { SetLogStreamName(value); return *this;}

    
    inline LogStream& WithLogStreamName(const char* value) { SetLogStreamName(value); return *this;}

    
    inline long long GetCreationTime() const{ return m_creationTime; }

    
    inline void SetCreationTime(long long value) { m_creationTimeHasBeenSet = true; m_creationTime = value; }

    
    inline LogStream& WithCreationTime(long long value) { SetCreationTime(value); return *this;}

    
    inline long long GetFirstEventTimestamp() const{ return m_firstEventTimestamp; }

    
    inline void SetFirstEventTimestamp(long long value) { m_firstEventTimestampHasBeenSet = true; m_firstEventTimestamp = value; }

    
    inline LogStream& WithFirstEventTimestamp(long long value) { SetFirstEventTimestamp(value); return *this;}

    
    inline long long GetLastEventTimestamp() const{ return m_lastEventTimestamp; }

    
    inline void SetLastEventTimestamp(long long value) { m_lastEventTimestampHasBeenSet = true; m_lastEventTimestamp = value; }

    
    inline LogStream& WithLastEventTimestamp(long long value) { SetLastEventTimestamp(value); return *this;}

    
    inline long long GetLastIngestionTime() const{ return m_lastIngestionTime; }

    
    inline void SetLastIngestionTime(long long value) { m_lastIngestionTimeHasBeenSet = true; m_lastIngestionTime = value; }

    
    inline LogStream& WithLastIngestionTime(long long value) { SetLastIngestionTime(value); return *this;}

    
    inline const Aws::String& GetUploadSequenceToken() const{ return m_uploadSequenceToken; }

    
    inline void SetUploadSequenceToken(const Aws::String& value) { m_uploadSequenceTokenHasBeenSet = true; m_uploadSequenceToken = value; }

    
    inline void SetUploadSequenceToken(Aws::String&& value) { m_uploadSequenceTokenHasBeenSet = true; m_uploadSequenceToken = value; }

    
    inline void SetUploadSequenceToken(const char* value) { m_uploadSequenceTokenHasBeenSet = true; m_uploadSequenceToken.assign(value); }

    
    inline LogStream& WithUploadSequenceToken(const Aws::String& value) { SetUploadSequenceToken(value); return *this;}

    
    inline LogStream& WithUploadSequenceToken(Aws::String&& value) { SetUploadSequenceToken(value); return *this;}

    
    inline LogStream& WithUploadSequenceToken(const char* value) { SetUploadSequenceToken(value); return *this;}

    
    inline const Aws::String& GetArn() const{ return m_arn; }

    
    inline void SetArn(const Aws::String& value) { m_arnHasBeenSet = true; m_arn = value; }

    
    inline void SetArn(Aws::String&& value) { m_arnHasBeenSet = true; m_arn = value; }

    
    inline void SetArn(const char* value) { m_arnHasBeenSet = true; m_arn.assign(value); }

    
    inline LogStream& WithArn(const Aws::String& value) { SetArn(value); return *this;}

    
    inline LogStream& WithArn(Aws::String&& value) { SetArn(value); return *this;}

    
    inline LogStream& WithArn(const char* value) { SetArn(value); return *this;}

    
    inline long long GetStoredBytes() const{ return m_storedBytes; }

    
    inline void SetStoredBytes(long long value) { m_storedBytesHasBeenSet = true; m_storedBytes = value; }

    
    inline LogStream& WithStoredBytes(long long value) { SetStoredBytes(value); return *this;}

  private:
    Aws::String m_logStreamName;
    bool m_logStreamNameHasBeenSet;
    long long m_creationTime;
    bool m_creationTimeHasBeenSet;
    long long m_firstEventTimestamp;
    bool m_firstEventTimestampHasBeenSet;
    long long m_lastEventTimestamp;
    bool m_lastEventTimestampHasBeenSet;
    long long m_lastIngestionTime;
    bool m_lastIngestionTimeHasBeenSet;
    Aws::String m_uploadSequenceToken;
    bool m_uploadSequenceTokenHasBeenSet;
    Aws::String m_arn;
    bool m_arnHasBeenSet;
    long long m_storedBytes;
    bool m_storedBytesHasBeenSet;
  };

} // namespace Model
} // namespace CloudWatchLogs
} // namespace Aws
