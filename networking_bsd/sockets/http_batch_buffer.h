#pragma once


namespace networking_bsd
{


   class CLASS_DECL_NETWORKING_BSD http_batch_buffer :
      virtual public ::file::file
   {
   public:

      
      ::u32                 m_nOpenFlags;
      string               m_strPath;


      http_batch_buffer();


      //virtual ::extended::status open(const char * pszFileName, ::u32 nOpenFlags);

      virtual void open(const char* pszFileName, ::u32 nOpenFlags);

      virtual void close();
      virtual void flush();

      virtual void get_file_data() = 0;
      virtual void set_file_data() = 0;


   };

} // namespace networking_bsd




