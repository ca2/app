#pragma once


#include "acme/filesystem/file/file.h"


namespace sockets
{


   class CLASS_DECL_APEX http_batch_buffer :
      virtual public ::file::file
   {
   public:

      
      //::file::e_open       m_eopen;
      //string               m_strPath;


      http_batch_buffer();


      //virtual ::extended::status open(const ::file::path & path, ::u32 nOpenFlags);

      
      void open(const ::file::path& path, ::file::e_open eopen, ::pointer < ::file::exception >* pfileexception = nullptr) override;


      void close() override;
      void flush() override;

      virtual void get_file_data() = 0;
      virtual void set_file_data() = 0;


   };

} // namespace sockets




