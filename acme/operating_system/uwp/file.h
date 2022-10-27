#pragma once





class FileException;
struct FileStatus;

void CLASS_DECL_ACME vfxGetRoot(const unichar * lpszPath, string& wstrRoot);
void CLASS_DECL_ACME vfxGetRoot(wstring & wstrRoot, const wstring & wstrPath);




namespace universal_windows
{

   /////////////////////////////////////////////////////////////////////////////
   // File - raw unbuffered disk file I/O

   class CLASS_DECL_ACME file :
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


      bool                 m_bCloseOnDelete;
      hfile                m_hfile;


      file();
      virtual ~file();


      void assert_ok() const override;
      virtual void dump(dump_context& dumpcontext) const override;


      operator HANDLE() const;

      virtual filesize get_position() const override;
      virtual bool get_status(::file::file_status & rStatus) const override;
      //virtual string GetFileName() const override;
      //virtual string GetFileTitle() const override;
      virtual ::file::path get_file_path() const override;
      virtual void set_file_path(const ::file::path & path) override;

      virtual ::extended::status open(const ::file::path & lpszFileName, const ::file::e_open & eopen) override;

      //virtual bool GetStatus(const ::file::path & lpszFileName,::file::file_status& rStatus);

      u64 ReadHuge(void * lpBuffer, u64 dwCount);
      void WriteHuge(const void * lpBuffer, u64 dwCount);

      //virtual ::pointer<::file::file>Duplicate() const;

      virtual filesize seek(filesize lOff, ::enum_seek eseek) override;
      virtual void set_size(filesize dwNewLen) override;
      virtual filesize get_size() const override;

      virtual memsize read(void * lpBuf, memsize nCount) override;
      virtual void write(const void * lpBuf, memsize nCount) override;

      virtual void lock(filesize dwPos, filesize dwCount) override;
      virtual void unlock(filesize dwPos, filesize dwCount) override;

      //virtual void Abort();
      virtual void flush() override;
      virtual void close() override;

      virtual bool is_opened()const  override;
      //enum BufferCommand { bufferRead, bufferWrite, bufferCommit, bufferCheck };
      //virtual u64 GetBufferPtr(::u32 nCommand, u64 nCount = 0,
      //                              void ** ppBufStart = nullptr, void ** ppBufMax = nullptr);

   };

   //namespace WinFileException
   //{

   //   void OsErrorToException(::i32 lOsError);
   //   void ErrnoToException(int nErrno);
   //   void ThrowOsError(::particle * pparticle, ::i32 lOsError, const char * lpszFileName = nullptr);
   //   void ThrowErrno(::particle * pparticle, int nErrno, const char * lpszFileName = nullptr);

   //}



} // namespace universal_windows
