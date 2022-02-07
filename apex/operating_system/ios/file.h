#pragma once


class FileException;
struct FileStatus;

void CLASS_DECL_APEX vfxGetRoot(const unichar * lpszPath, string& wstrRoot);

namespace ios
{

   /////////////////////////////////////////////////////////////////////////////
   // File - raw unbuffered disk file I/O

   class CLASS_DECL_APEX file :
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

      zip::util *    m_pziputil;
      string         m_strFileName;
      wstring        m_wstrFileName;
      i32            m_iFile;


      file();
      virtual ~file();


      void assert_ok() const override;
      void dump(dump_context & dumpcontext) const override;

      //virtual bool has_write_mode() override;

      virtual filesize get_position() const override;
      virtual bool get_status(::file::file_status & status) const override;
      virtual ::file::path get_file_path() const override;
      virtual void set_file_path(const ::file::path & path) override;

      virtual ::extended::status open(const ::file::path & path, const ::file::e_open & eopen) override;

      virtual filesize seek(filesize uiCount, ::enum_seek eseek) override;
      virtual void set_size(filesize uiCount) override;
      virtual filesize get_size() const override;

      virtual memsize read(void * pbuffer, memsize uiCount) override;
      virtual void write(const void * pbuffer, memsize uiCount) override;

      virtual void lock(filesize pos, filesize uiCount) override;
      virtual void unlock(filesize pos, filesize uiCount) override;

      virtual void flush() override;
      virtual void close() override;

      virtual bool is_opened() const override;


   };


//   namespace file_exception
//   {
//
//
//      void os_error_to_exception(::i32 lOsError);
//      void err_no_to_exception(i32 nErrno);
//      void throw_os_error(::object * pobject, ::i32 lOsError, const char * lpszFileName = nullptr);
//      void throw_err_no(::object * pobject, i32 nErrno, const char * lpszFileName = nullptr);
//
//
//   }  // namespace file_exception
//
//
} // namespace ios
