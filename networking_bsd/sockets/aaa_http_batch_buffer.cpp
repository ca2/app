#include "framework.h" 



namespace networking_bsd
{


   http_batch_buffer::http_batch_buffer()
   {

      m_nOpenFlags = 0;

   }


   void http_batch_buffer::open(const scoped_string & strFileName, ::u32 nOpenFlags)
   {

      m_strPath = pszFileName;


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


} // namespace networking_bsd


