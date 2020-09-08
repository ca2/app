#pragma once


namespace zip
{


   class CLASS_DECL_APEX file :
      virtual public ::object
   {
   public:


      file_pointer            m_pfile;
      file_pointer            m_pbuffile1;
      file_pointer            m_pbuffile2;
      void *                  m_pfUnzip;
      void *                  m_pfZip;
      bool                    m_bOwnFile;
      void *                  m_pvoidFileFuncDef;


      file();
      virtual ~file();


      void write_to_file(file_pointer  pfile, const widechar * pcsz);


      bool unzip_open(const char * pcwsz);

      bool unzip_open(file_pointer pfile, int iBufferLevel = 2);

      bool zip_open(const char * pcwsz);

      bool zip_open(file_pointer pfile);


   };


} // namespace zip




void *         c_zip_file_open_file_func        (void * opaque, const char* filename, i32 mode);
uptr       c_zip_file_read_file_func        (void * opaque, void * stream, void * buf, uptr size);
uptr       c_zip_file_write_file_func       (void * opaque, void * stream, const void * buf, uptr size);
long           c_zip_file_tell_file_func        (void * opaque, void * stream);
long           c_zip_file_seek_file_func        (void * opaque, void * stream, uptr offset, i32 origin);
i32        c_zip_file_close_file_func       (void * opaque, void * stream);
i32        c_zip_file_testerror_file_func   (void * opaque, void * stream);





