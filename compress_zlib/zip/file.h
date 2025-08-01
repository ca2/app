#pragma once


namespace zip
{


   class CLASS_DECL_ACME file :
      virtual public ::matter
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


      void write_to_file(file_pointer  pfile, const ::wide_character * pcsz);


      //bool unzip_open(const_char_pointer  pcwsz);

      bool unzip_open(file_pointer pfile, int iBufferLevel = 2);

      bool zip_open(const_char_pointer  pcwsz);

      bool zip_open(file_pointer pfile);


   };


} // namespace zip




void *         c_zip_file_open_file_func        (void * opaque, const_char_pointer  filename, int mode);
uptr       c_zip_file_read_file_func        (void * opaque, void * stream, void * buf, uptr size);
uptr       c_zip_file_write_file_func       (void * opaque, void * stream, const void * buf, uptr size);
long           c_zip_file_tell_file_func        (void * opaque, void * stream);
long           c_zip_file_seek_file_func        (void * opaque, void * stream, uptr offset, int origin);
int        c_zip_file_close_file_func       (void * opaque, void * stream);
int        c_zip_file_testerror_file_func   (void * opaque, void * stream);





