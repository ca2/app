#pragma once


/////////////////////////////////////////////////////////////////////////////
// STDIO file implementation


namespace android
{


   class CLASS_DECL_APEX stdio_file :
      virtual public ::android::file,
      virtual public ::file::text_file
   {
   public:


      FILE* m_pStream;    // stdio FILE
      // m_hFile from apex class is _fileno(m_pStream)



      stdio_file();
      virtual ~stdio_file();

      virtual void write_string(const char * lpsz);
      virtual char * read_string(char * lpsz, UINT nMax);
      virtual bool read_string(string & rString);


      void dump(dump_context & dumpcontext) const;
      virtual filesize get_position() const;
      virtual ::status::result open(const ::file::path & lpszFileName, UINT nOpenFlags);
      virtual memsize read(void * lpBuf, memsize nCount);
      virtual void write(const void * lpBuf, memsize nCount);
      virtual filesize seek(filesize lOff, ::file::e_seek nFrom);
      virtual void Abort();
      virtual void Flush();
      virtual void close();
      virtual filesize get_length() const;

      // Unsupported APIs
      virtual file_pointer Duplicate() const;
      virtual void LockRange(filesize dwPos, filesize dwCount);
      virtual void UnlockRange(filesize dwPos, filesize dwCount);


   };



} // namespace android


