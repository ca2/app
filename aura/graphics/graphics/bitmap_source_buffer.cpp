#include "framework.h"
#include "aura/user/_user.h"
#include "bitmap_source_buffer.h"


namespace graphics
{


   bitmap_source_buffer::bitmap_source_buffer()
   {


   }


   bitmap_source_buffer::~bitmap_source_buffer()
   {


   }

   ::e_status bitmap_source_buffer::initialize_graphics_graphics(::user::interaction_impl* pimpl)
   {

      auto estatus = graphics::initialize_graphics_graphics(pimpl);

      if (!estatus)
      {

         return estatus;

      }

      if (m_strBitmapSource.is_empty())
      {

         m_strBitmapSource = pimpl->payload("bitmap-source");

      }

      return estatus;

   }

   void bitmap_source_buffer::defer_initialize_bitmap_source_buffer()
   {

      if (m_pwindow == nullptr || m_pimpl->m_puserinteraction->payload("bitmap-source").is_empty())
      {

         return;

      }

      if (m_memorymap.is_mapped())
      {

         return;

      }

      m_strBitmapSource = m_pimpl->m_puserinteraction->payload("bitmap-source");

      char szName[] = "Local\\bitmap-source-%s";

      string strPath;

      strPath.Format(szName, m_strBitmapSource.c_str());

      m_memorymap.open(strPath, false, true, true, 8192 * 4096 * 4);

   }


   bool bitmap_source_buffer::ipc_copy(const pixmap * ppixmap)
   {

      if (!m_memorymap.is_mapped())
      {

         return false;

      }

      void * pdata = m_memorymap.get_data();

      if (pdata == nullptr)
      {

         return false;

      }

      sync_lock sl(m_memorymap.mutex());

      try
      {

         i64 * p = (i64 *)pdata;

         int iScan = (int)(ppixmap->width() * sizeof(color32_t));

         *p++ = ppixmap->width();
         *p++ = ppixmap->height();
         *p++ = iScan;

         ::copy_colorref((color32_t *)p, ppixmap->size(), iScan, ppixmap);

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

      if (m_pimpl->m_puserinteraction->payload("bitmap-source").has_char())
      {

         if (!ipc_copy(get_screen_image()))
         {

            return false;

         }

      }

      return true;

   }


} // namespace graphics



