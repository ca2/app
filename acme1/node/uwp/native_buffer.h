#pragma once


namespace uwp
{

   /////////////////////////////////////////////////////////////////////////////
   // native_buffer - raw unbuffered disk native_buffer I/O

   class CLASS_DECL_ACME native_buffer:
      virtual public ::file::file
   {
   public:


      enum Attribute
      {
         normal =    0x00,
         readOnly =  0x01,
         hidden =    0x02,
         system =    0x04,
         volume =    0x08,
         directory = 0x10,
         archive =   0x20
      };

      enum { hnative_bufferNull = -1 };

      bool                                m_bCloseOnDelete;
      ::file::path                        m_strFileName;
      StorageFile ^                       m_file;
      StorageFolder ^                     m_folder;
      Streams::IRandomAccessStream ^      m_stream;
      efileopen                           m_efileopen;


      native_buffer();
      native_buffer(StorageFile ^ file);
      virtual ~native_buffer();

      virtual void assert_valid() const override;
      virtual void dump(dump_context & dumpcontext) const override;

      operator StorageFile ^ () const;

      virtual filesize get_position() const override;
      virtual bool get_status(::file::file_status & rStatus) const override;
      //virtual string GetFileName() const;
      //virtual string GetFileTitle() const;
      virtual ::file::path get_file_path() const override;
      virtual void set_file_path(const ::file::path & pathNewName) override;

      virtual ::status::result open(::Windows::Storage::StorageFolder ^ folder, const ::file::path & lpszfileName, const ::efileopen& efileopen);
      virtual ::status::result open(const ::file::path & lpszfileName, const :: efileopen & efileopen) override;

      //virtual bool GetStatus(const ::file::path & lpszfileName,::file::file_status& rStatus);

      ///u64 ReadHuge(void * lpBuffer,u64 dwCount);
      //void WriteHuge(const void * lpBuffer,u64 dwCount);

      //virtual __pointer(::file::file) Duplicate() const;

      virtual filesize seek(filesize lOff,::file::e_seek nFrom) override;
      virtual void set_size(filesize dwNewLen) override;
      virtual filesize get_size() const override;

      virtual memsize read(void * lpBuf,memsize nCount) override;
      virtual void write(const void * lpBuf,memsize nCount) override;

      virtual void lock(filesize dwPos,filesize dwCount) override;
      virtual void unlock(filesize dwPos,filesize dwCount) override;

      //virtual void Abort();
      virtual void flush() override;
      virtual void close() override;

      virtual bool is_opened() const override;
      //enum BufferCommand { bufferRead,bufferWrite,bufferCommit,bufferCheck };
      //virtual u64 GetBufferPtr(UINT nCommand,u64 nCount = 0,
      //                              void ** ppBufStart = nullptr,void ** ppBufMax = nullptr);

   };


} // namespace uwp




