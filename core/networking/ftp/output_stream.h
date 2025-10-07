#pragma once


#include "transfer_notification.h"


namespace ftp
{


   class CLASS_DECL_CORE output_stream :
      virtual public itransfer_notification
   {
   public:


      class implementation;


      ::pointer<implementation>     m_pimpl;


      output_stream(const ::scoped_string & scopedstrEolCharacterSequence, const ::scoped_string & scopedstrStreamName);
      virtual ~output_stream();

      void SetBuffer(const ::scoped_string & scopedstrBuffer);
      const string& GetBuffer();
      void SetStartPosition();
      bool GetNextLine(string& strLine);

      virtual string GetLocalStreamName() const override;
      virtual unsigned int GetLocalStreamSize() const override;
      virtual void SetLocalStreamOffset(unsigned int dwOffsetFromBeginOfStream) override;
      virtual void OnBytesReceived(const memory& vBuffer, long lReceivedBytes) override;
      virtual void OnPreBytesSend(unsigned char* pszBuffer, memsize bufferSize, memsize& bytesToSend) override;
   };



   class CLASS_DECL_CORE output_stream::implementation:
      virtual public ::object
   {
   public:


      const string mc_strEolCharacterSequence;
      string      m_vBuffer;
      character_count     m_iCurrentPos;
      string      m_strStreamName;


      implementation(const ::scoped_string & scopedstrEolCharacterSequence, const ::scoped_string & scopedstrStreamName);

      virtual bool GetNextLine(string& strLine);
      virtual void OnPreBytesSend(unsigned char * pszBuffer, memsize bufferSize, memsize& bytesToSend);


   private:

      implementation& operator=(const implementation&); // no implementation for assignment operator

   };


} // namespace ftp


