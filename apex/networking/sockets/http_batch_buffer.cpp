#include "framework.h" 
#include "apex/networking/sockets/_sockets.h"


namespace sockets
{


   http_batch_buffer::http_batch_buffer()
   {

      m_nOpenFlags = 0;

   }


   ::extended::status http_batch_buffer::open(const char * pszFileName, ::u32 nOpenFlags)
   {

      m_strPath = pszFileName;


      m_nOpenFlags = nOpenFlags;

      if(m_nOpenFlags & ::file::e_open_read)
      {

         get_file_data();

      }

      return ::success;

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


