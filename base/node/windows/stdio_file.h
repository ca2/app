#pragma once


#define iFileNull ((int)-1)

namespace windows
{


   class stdio_file :
      virtual public ::file::text_file
   {
   public:


      FILE *            m_pStream;     // stdio FILE
      int               m_iFile;       // _fileno(m_pStream)



      stdio_file();
      virtual ~stdio_file();

      
      void dump(dump_context & dumpcontext) const;


      virtual void write_string(const char * psz);

      virtual char * read_string(char * psz, UINT nMax);

      virtual bool read_string(string & rString);



      virtual filesize get_position() const;
      virtual ::status::result open(const ::file::path & pszFileName, const efileopen & eopen) override;

      virtual memsize read(void * pdata, memsize nCount);

      virtual void write(const void * pdata, memsize nCount);

      virtual filesize seek(filesize lOff, ::file::e_seek nFrom);
      virtual void Abort();
      virtual void Flush();
      virtual void close();
      virtual filesize get_length() const;

      // Unsupported APIs
      virtual file_pointer  Duplicate() const;
      virtual void LockRange(filesize dwPos, filesize dwCount);
      virtual void UnlockRange(filesize dwPos, filesize dwCount);


   };



} // namespace windows



