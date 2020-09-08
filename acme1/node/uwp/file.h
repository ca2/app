#pragma once





class FileException;
struct FileStatus;

void CLASS_DECL_ACME vfxGetRoot(const unichar * lpszPath, string& wstrRoot);
void CLASS_DECL_ACME vfxGetRoot(wstring & wstrRoot, const wstring & wstrPath);

#define HFILE_NULL INVALID_HANDLE_VALUE

namespace uwp
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


      bool              m_bCloseOnDelete;
      HANDLE            m_hFile;


      file();
      virtual ~file();


      virtual void assert_valid() const override;
      virtual void dump(dump_context& dumpcontext) const override;


      operator HANDLE() const;

      virtual filesize get_position() const override;
      virtual bool get_status(::file::file_status & rStatus) const override;
      //virtual string GetFileName() const override;
      //virtual string GetFileTitle() const override;
      virtual ::file::path get_file_path() const override;
      virtual void set_file_path(const ::file::path & path) override;

      virtual ::status::result open(const ::file::path & lpszFileName, const ::efileopen & efileopen) override;

      //virtual bool GetStatus(const ::file::path & lpszFileName,::file::file_status& rStatus);

      u64 ReadHuge(void * lpBuffer, u64 dwCount);
      void WriteHuge(const void * lpBuffer, u64 dwCount);

      //virtual __pointer(::file::file) Duplicate() const;

      virtual filesize seek(filesize lOff, ::file::e_seek nFrom) override;
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
      //virtual u64 GetBufferPtr(UINT nCommand, u64 nCount = 0,
      //                              void ** ppBufStart = nullptr, void ** ppBufMax = nullptr);

   };

   //namespace WinFileException
   //{

   //   ::estatus OsErrorToException(LONG lOsError);
   //   ::estatus ErrnoToException(int nErrno);
   //   void ThrowOsError(::generic * pobject, LONG lOsError, const char * lpszFileName = nullptr);
   //   void ThrowErrno(::generic * pobject, int nErrno, const char * lpszFileName = nullptr);

   //}



} // namespace uwp