#pragma once


namespace sockets
{


   class CLASS_DECL_AURA http_batch_buffer :
      virtual public ::file::file
   {
   public:

      
      UINT                 m_nOpenFlags;
      string               m_strPath;


      http_batch_buffer();


      virtual ::status::result open(const char * pszFileName, UINT nOpenFlags);

      virtual void close();
      virtual void flush();

      virtual void get_file_data() = 0;
      virtual void set_file_data() = 0;


   };

} // namespace sockets




