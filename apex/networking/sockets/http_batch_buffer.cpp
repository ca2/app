#include "framework.h" 
#include "http_batch_buffer.h"


namespace sockets
{


   http_batch_buffer::http_batch_buffer()
   {

      m_nOpenFlags = 0;

   }


   void http_batch_buffer::open(const ::file::path & path, ::u32 nOpenFlags)
   {

      m_strPath = path;

      m_nOpenFlags = nOpenFlags;

      if(m_nOpenFlags & ::file::e_open_read)
      {

         get_file_data();

      }

      //return ::success;

   }


   void http_batch_buffer::close()
   {
      if(m_nOpenFlags & ::file::e_open_write)
      {
         set_file_data();
      }
   }

   void http_batch_buffer::flush()
   {
      if(m_nOpenFlags & ::file::e_open_write)
      {
         set_file_data();
      }
   }


} // namespace sockets


