#pragma once


class FileException;
struct FileStatus;


void CLASS_DECL_ACME vfxGetRoot(const widechar * pszPath, string& wstrRoot);

void CLASS_DECL_ACME vfxGetRoot(wstring & wstrRoot, const wstring & wstrPath);


/////////////////////////////////////////////////////////////////////////////
// File - raw unbuffered disk file I/O

#define INVALID_FILE -1

namespace linux
{


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

      enum BufferCommand
      {

         bufferRead,
         bufferWrite,
         bufferCommit,
         bufferCheck

      };

      int                  m_iFile;


      file();
      //file(::matter * pobject);
      //file(::matter * pobject, int hFile);
      //file(::matter * pobject, const ::file::path & pszFileName, const cflag < ::file::e_open > & eflag);

      virtual ~file();


      virtual void assert_valid() const override;
      virtual void dump(dump_context & dumpcontext) const override;

      virtual filesize get_position() const override;


      bool GetStatus(::file::file_status & rStatus) const;
      virtual string GetFileName() const;
      virtual string GetFileTitle() const;
      virtual string GetFilePath() const;
      virtual void SetFilePath(const char * pszNewName);


      virtual ::status::result open(const ::file::path & pszFileName, const ::file::e_open & eopen) override;


      //virtual bool PASCAL GetStatus(const char * pszFileName, ::file::file_status& rStatus);


      u64 ReadHuge(void * pBuffer, u64 dwCount);

      void WriteHuge(const void * pBuffer, u64 dwCount);


//      virtual __pointer(::file::file) Duplicate() const;

      virtual filesize seek(filesize lOff, ::file::e_seek nFrom) override;
      virtual void set_size(filesize dwNewLen) override;
      virtual filesize get_size() const override;

      virtual memsize read(void * pdata, memsize nCount) override;

      virtual void write(const void * pdata, memsize nCount) override;


      virtual void LockRange(filesize dwPos, filesize dwCount);
      virtual void UnlockRange(filesize dwPos, filesize dwCount);

      virtual void Abort();
      virtual void Flush();
      virtual void close() override;

      virtual bool IsOpened();

      virtual u64 GetBufferPtr(::u32 nCommand, u64 nCount = 0, void ** ppBufStart = nullptr, void ** ppBufMax = nullptr);


   };


//   namespace file_exception
//   {
//
//
//      ::e_status os_error_to_exception(::i32 lOsError);
////      ::e_status PASCAL ErrnoToException(i32 nErrno);
//      void throw_os_error(::i32 lOsError, const char * pszFileName = nullptr);

//      //void PASCAL ThrowErrno(__pointer(::acme::application) papp, i32 nErrno, const char * pszFileName = nullptr);

//
//
//   }  // namespace file_exception


} // namepsace linux




bool CLASS_DECL_ACME vfxFullPath(wstring & wstrFullPath, const wstring & wstrPath);



