#pragma once


#include "interface.h"


namespace ftp
{


   class CLASS_DECL_CORE itransfer_notification :
      virtual public iinterface
   {
   public:
      virtual ~itransfer_notification() {}
      virtual string GetLocalStreamName() const = 0;
      virtual unsigned int GetLocalStreamSize() const = 0;
      virtual void SetLocalStreamOffset(unsigned int dwOffsetFromBeginOfStream) = 0;
      virtual void OnBytesReceived(const memory& /*vBuffer*/, long /*lReceivedBytes*/) {}
      virtual void OnPreBytesSend(unsigned char* /*pszBuffer*/, memsize /*bufferSize*/, memsize& /*bytesToSend*/) {}
   };


} // namespace ftp





