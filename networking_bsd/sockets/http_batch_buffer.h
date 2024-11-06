#pragma once


namespace networking_bsd
{


   class CLASS_DECL_NETWORKING_BSD http_batch_buffer :
      virtual public ::file::file
   {
   public:

      
      unsigned int                 m_nOpenFlags;
      string               m_strPath;


      http_batch_buffer();


      //virtual ::extended::status open(const ::file::path & path, unsigned int nOpenFlags);

      virtual void open(const ::file::path & path, unsigned int nOpenFlags);

      virtual void close();
      virtual void flush();

      virtual void get_file_data() = 0;
      virtual void set_file_data() = 0;


   };

} // namespace networking_bsd




