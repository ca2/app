#include "framework.h" 
#include "http_batch_buffer.h"


namespace sockets
{


   http_batch_buffer::http_batch_buffer()
   {

      //m_ = 0;

   }


   void http_batch_buffer::open(const ::file::path& path, ::file::e_open eopen, ::pointer < ::file::exception >* pfileexception)
   {

      m_path = path;

      m_eopen = eopen;

      if(m_eopen & ::file::e_open_read)
      {

         get_file_data();

      }

      //return ::success;

   }


   void http_batch_buffer::close()
   {

      if(m_eopen & ::file::e_open_write)
      {

         set_file_data();

      }

   }


   void http_batch_buffer::flush()
   {
      
      if(m_eopen & ::file::e_open_write)
      {

         set_file_data();

      }

   }


} // namespace sockets


