#pragma once


/////////////////////////////////////////////////////////////////////////////
// STDIO file implementation


namespace linux
{


   class stdio_file :
      virtual public ::linux::file,
      virtual public ::file::text_file
   {
   public:


      FILE* m_pStream;    // stdio FILE
      // m_hFile from aura class is _fileno(m_pStream)



      stdio_file();
      virtual ~stdio_file();

      virtual void write_string(const char * psz) override;

      virtual char * read_string(char * psz, ::u32 nMax);

      virtual bool read_string(string & rString) override;


      void dump(dump_context & dumpcontext) const override;
      virtual filesize get_position() const override;
      virtual ::status::result open(const ::file::path & pszFileName, const cflag < ::file::e_open > & eopen) override;

      virtual memsize read(void * pdata, memsize nCount) override;

      virtual void write(const void * pdata, memsize nCount) override;

      virtual filesize seek(filesize lOff, ::file::e_seek nFrom) override;
      virtual void Abort() override;
      virtual void Flush() override;
      virtual void close() override;
      virtual filesize get_length() const;

      // Unsupported APIs
      virtual __pointer(::file::file) Duplicate() const;
      virtual void LockRange(filesize dwPos, filesize dwCount) override;
      virtual void UnlockRange(filesize dwPos, filesize dwCount) override;


   };



} // namespace linux


