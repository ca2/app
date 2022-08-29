#pragma once


#include "transfer_notification.h"


namespace ftp
{


   class CLASS_DECL_CORE output_stream :
      virtual public itransfer_notification
   {
   public:


      class implementation;


      __pointer(implementation)      m_pimpl;


      output_stream(const string& strEolCharacterSequence, const string& strStreamName);
      virtual ~output_stream();

      void SetBuffer(const string& strBuffer);
      const string& GetBuffer();
      void SetStartPosition();
      bool GetNextLine(string& strLine);

      virtual string GetLocalStreamName() const override;
      virtual ::u32 GetLocalStreamSize() const override;
      virtual void SetLocalStreamOffset(::u32 dwOffsetFromBeginOfStream) override;
      virtual void OnBytesReceived(const memory& vBuffer, long lReceivedBytes) override;
      virtual void OnPreBytesSend(byte* pszBuffer, memsize bufferSize, memsize& bytesToSend) override;
   };



   class CLASS_DECL_CORE output_stream::implementation:
      virtual public ::object
   {
   public:


      const string mc_strEolCharacterSequence;
      string      m_vBuffer;
      strsize     m_iCurrentPos;
      string      m_strStreamName;


      implementation(const string& strEolCharacterSequence, const string& strStreamName);

      virtual bool GetNextLine(string& strLine);
      virtual void OnPreBytesSend(u8 * pszBuffer, memsize bufferSize, memsize& bytesToSend);


   private:

      implementation& operator=(const implementation&); // no implementation for assignment operator

   };


} // namespace ftp


