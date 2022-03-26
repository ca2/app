#pragma once


class FileException;
struct FileStatus;


void CLASS_DECL_CORE vfxGetRoot(const widechar * pszPath, string& wstrRoot);

void CLASS_DECL_CORE vfxGetRoot(wstring & wstrRoot, const wstring & wstrPath);


/////////////////////////////////////////////////////////////////////////////
// File - raw unbuffered disk file I/O

#define INVALID_FILE -1

namespace linux
{


   class CLASS_DECL_CORE file :
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
      //file(::object * pobject);
      //file(::object * pobject, int hFile);
      //file(::object * pobject, const ::file::path & pszFileName, const cflag < ::file::e_open > & eflag);

      virtual ~file();


      void assert_ok() const override;
      void dump(dump_context & dumpcontext) const override;

      virtual filesize get_position() const override;


      bool GetStatus(::file::file_status & rStatus) const;
      virtual string GetFileName() const;
      virtual string GetFileTitle() const;
      virtual string GetFilePath() const;
      virtual void SetFilePath(const ::string & pszNewName);


      virtual ::extended::status open(const ::file::path & pszFileName, const cflag < ::file::e_open > & eflag) override;


      //virtual bool PASCAL GetStatus(const ::string & pszFileName, ::file::file_status& rStatus);


      u64 ReadHuge(void * pBuffer, u64 dwCount);

      void WriteHuge(const void * pBuffer, u64 dwCount);


//      virtual __pointer(::file::file) Duplicate() const;

      virtual filesize seek(filesize lOff, ::enum_seek eseek) override;
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
//      void os_error_to_exception(::i32 lOsError);
////      void PASCAL ErrnoToException(i32 nErrno);
//      void throw_os_error(::i32 lOsError, const ::string & pszFileName = nullptr);

//      //void PASCAL ThrowErrno(__pointer(::aura::application) papp, i32 nErrno, const ::string & pszFileName = nullptr);

//
//
//   }  // namespace file_exception


} // namepsace linux




bool CLASS_DECL_CORE windows_full_path(wstring & wstrFullPath, const wstring & wstrPath);



