#pragma once


class FileException;
struct FileStatus;


//void CLASS_DECL_CORE vfxGetRoot(const unichar* pszPath, string& wstrRoot);
//
//void CLASS_DECL_CORE vfxGetRoot(wstring& wstrRoot, const wstring& wstrPath);


/////////////////////////////////////////////////////////////////////////////
// File - raw unbuffered disk file I/O

#define INVALID_FILE -1

namespace android
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

      enum
      {

         hFileNull = -1

      };

      enum BufferCommand
      {

         bufferRead,
         bufferWrite,
         bufferCommit,
         bufferCheck

      };

      ::file::path   m_strFileName;
      i32        m_iFile;


      file();
      virtual ~file();


//      // void assert_ok() const override;
//      void dump(dump_context & dumpcontext) const override;


      virtual filesize get_position() const override;


      virtual bool get_status(::file::file_status & rStatus) const override;
      //virtual string GetFileName() const;
      //virtual string GetFileTitle() const;
      virtual ::file::path get_file_path() const override;
      virtual void set_file_path(const ::file::path & path) override;

      virtual ::extended::status open(const ::file::path & lpszFileName, const ::file::e_open & eopen) override;

      //virtual bool PASCAL GetStatus(const ::string & lpszFileName, ::file::file_status& rStatus);

      //u64 ReadHuge(void * lpBuffer, u64 dwCount);
      //void WriteHuge(const void * lpBuffer, u64 dwCount);

      //virtual file_pointer Duplicate() const;

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

      virtual bool is_opened() const override;

      //virtual u64 GetBufferPtr(::u32 nCommand, u64 nCount = 0, void ** ppBufStart = nullptr, void ** ppBufMax = nullptr);


   };


   //namespace file_exception
   //{


   //   void PASCAL OsErrorToException(::i32 lOsError);
   //   void PASCAL ErrnoToException(i32 nErrno);
   //   void PASCAL ThrowOsError(::particle * pparticle, ::i32 lOsError, const ::string & lpszFileName = nullptr);
   //   void PASCAL ThrowErrno(::particle * pparticle, i32 nErrno, const ::string & lpszFileName = nullptr);


   //}  // namespace file_exception


} // namepsace android




bool CLASS_DECL_CORE windows_full_path(wstring & wstrFullPath, const wstring & wstrPath);



