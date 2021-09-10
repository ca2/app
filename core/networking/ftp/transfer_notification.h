#pragma once


namespace ftp
{


   class CLASS_DECL_CORE itransfer_notification :
      virtual public iinterface
   {
   public:
      virtual ~itransfer_notification() {}
      virtual string GetLocalStreamName() const = 0;
      virtual ::u32 GetLocalStreamSize() const = 0;
      virtual void SetLocalStreamOffset(::u32 dwOffsetFromBeginOfStream) = 0;
      virtual void OnBytesReceived(const memory& /*vBuffer*/, long /*lReceivedBytes*/) {}
      virtual void OnPreBytesSend(byte* /*pszBuffer*/, memsize /*bufferSize*/, memsize& /*bytesToSend*/) {}
   };


} // namespace ftp





