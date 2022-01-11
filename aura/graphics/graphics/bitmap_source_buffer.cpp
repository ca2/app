#include "framework.h"
#include "aura/user/_user.h"
#include "_.h"
#include "_graphics.h"



namespace graphics
{


   bitmap_source_buffer::bitmap_source_buffer()
   {


   }


   bitmap_source_buffer::~bitmap_source_buffer()
   {

      clear_bitmap_source();

   }


   void bitmap_source_buffer::initialize_graphics_graphics(::user::interaction_impl* pimpl)
   {

      auto estatus = graphics::initialize_graphics_graphics(pimpl);

      if (!estatus)
      {

         return estatus;

      }

      if (pimpl->m_strBitmapSource.has_char())
      {


         estatus = __construct(m_pmemorymap);

         if (!estatus)
         {

            ::output_debug_string("no memory map for the graphics buffer");
            //return estatus;

            estatus = ::success;

         }

         estatus = set_bitmap_source(pimpl->m_strBitmapSource);

         if (!estatus)
         {

            return estatus;

         }

      }

      return estatus;

   }


   void bitmap_source_buffer::set_bitmap_source(const ::string &strBitmapSource)
   {

      if (m_strBitmapSource == strBitmapSource)
      {

         return true;

      }

      clear_bitmap_source();

      m_strBitmapSource = strBitmapSource;

      char szName[] = "Local\\bitmap-source:%s";

      string strMutexName;

      strMutexName.format(szName, strBitmapSource.c_str());

      m_pmutexBitmapSource = __new(::mutex(this, false, strMutexName));

      synchronous_lock synchronouslock(m_pmutexBitmapSource);

      ::file::path pathFolder;

      pathFolder = m_pcontext->m_papexcontext->dir().config();

      ::file::path path;

      path = pathFolder / "bitmap-source" / strBitmapSource;

      auto estatus = __construct(m_pmemorymap);

      if (!estatus)
      {

         return estatus;

      }

      estatus = m_pmemorymap->open_path(path, false, true, true, 128_mb);

      if (!estatus)
      {

         return estatus;

      }

      return ::success;

   }


   void bitmap_source_buffer::clear_bitmap_source()
   {

      m_strBitmapSource.Empty();

      if (m_pmemorymap)
      {

         synchronous_lock synchronouslock(m_pmutexBitmapSource);

         auto estatus = m_pmemorymap.release();

      }

      m_pmutexBitmapSource.release();
      
      return ::success;

   }

   string bitmap_source_buffer::get_bitmap_source() const
   {

      if (!is_ipc_copy_enabled())
      {

         return "";

      }

      return m_strBitmapSource;

   }


   bool bitmap_source_buffer::ipc_copy(const pixmap * ppixmap)
   {

      if (!is_ipc_copy_enabled())
      {

         return false;

      }

      void * pdata = m_pmemorymap->get_data();

      if (pdata == nullptr)
      {

         return false;

      }

      synchronous_lock synchronouslock(m_pmutexBitmapSource);

      try
      {

         i64 * p = (i64 *)pdata;

         int iScan = (int)(ppixmap->width() * sizeof(::color32_t));

         *p++ = ppixmap->width();
         *p++ = ppixmap->height();
         *p++ = iScan;

         //::copy_colorref((::color32_t*)p, ppixmap->size(), iScan, ppixmap);

         memcpy(p, ppixmap->m_pcolorrefRaw, ppixmap->height() * iScan);

      }
      catch (...)
      {

      }

      return true;

   }


   bool bitmap_source_buffer::buffer_lock_round_swap_key_buffers()
   {

      if (!m_pimpl)
      {

         return false;

      }

      if (!m_pimpl->m_puserinteraction)
      {

         return false;

      }

      if (is_ipc_copy_enabled())
      {

         if (!ipc_copy(get_screen_image()))
         {

            return false;

         }

      }

      return true;

   }


} // namespace graphics



