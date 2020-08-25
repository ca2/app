#pragma once


namespace ftp
{


   class CLASS_DECL_CORE file :
      virtual public itransfer_notification
   {
   public:

      file_pointer          m_file;
      string                     m_strFileName;

      //enum TOriginEnum { orBegin = SEEK_SET, orEnd = SEEK_END, orCurrent = SEEK_CUR };

      file();
      virtual ~file();

      bool Open( const string& strFileName, UINT uiMode);

      bool close();

      bool Seek(long lOffset, ::file::e_seek enOrigin);

      long Tell();

      memsize write(const void* pBuffer, memsize itemSize, memsize itemCount);

      memsize Read(void* pBuffer, memsize itemSize, memsize itemCount);

      virtual string GetLocalStreamName() const override;

      virtual UINT GetLocalStreamSize() const override;

      virtual void SetLocalStreamOffset(DWORD dwOffsetFromBeginOfStream) override;

      virtual void OnBytesReceived(const memory & vBuffer, long lReceivedBytes) override;

      virtual void OnPreBytesSend(byte* pszBuffer, memsize bufferSize, memsize& bytesToSend) override;

   };

} // namespace ftp

