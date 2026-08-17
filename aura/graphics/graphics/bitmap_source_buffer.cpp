#include "platform.h"
#include "buffer_item.h"
#include "bitmap_source_buffer.h"
#include "acme/parallelization/mutex.h"
#include "acme/parallelization/single_lock.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/platform/node.h"
#include "acme/filesystem/filesystem/directory_context.h"
#include "acme/filesystem/filesystem/directory_system.h"
#include "apex/platform/context.h"
#include "aura/graphics/image/image.h"
#include "aura/user/user/interaction.h"
#include "aura/windowing/window.h"
#include "aura/windowing/window_buffer.h"
#include "aura/windowing/windowing.h"


namespace graphics
{


   bitmap_source_buffer_graphics::bitmap_source_buffer_graphics()
   {


   }


   bitmap_source_buffer_graphics::~bitmap_source_buffer_graphics()
   {

      clear_bitmap_source();

   }


   void bitmap_source_buffer_graphics::initialize_graphics_graphics(::windowing::window* pwindow)
   {

      //auto estatus =
      
      graphics::initialize_graphics_graphics(pwindow);

      /*if (!estatus)
      {

         return estatus;

      }*/

      if (pwindow->m_strBitmapSource.has_character())
      {


         //estatus =
         
         constructø(m_pmemorymap);

         //if (!estatus)
         //{

         //   informationf("no memory map for the graphics buffer");
         //   //return estatus;

         //   estatus = ::success;

         //}

         //estatus = 
         
         set_bitmap_source(pwindow->m_strBitmapSource);

         //if (!estatus)
         //{

         //   return estatus;

         //}

      }



      //return estatus;

   }


   void bitmap_source_buffer_graphics::set_bitmap_source(const ::scoped_string & scopedstrBitmapSource, bool bCreate)
   {

      if (m_strBitmapSource == scopedstrBitmapSource)
      {

         return;

      }

      clear_bitmap_source();

      m_strBitmapSource = scopedstrBitmapSource;

      ::i8 szName[] = "Local\\bitmap-source:%s";

      string strMutexName;

      strMutexName.formatf(szName, scopedstrBitmapSource.as_string().c_str());

      if (bCreate)
      {

         m_pmutexBitmapSource = node()->create_local_named_mutex(this, false, strMutexName, nullptr);

      }
      else
      {

         m_pmutexBitmapSource = node()->open_local_named_mutex(this, strMutexName);

      }

      synchronous_lock synchronouslock(m_pmutexBitmapSource, DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      ::file::path pathFolder;

      pathFolder = directory_system()->roaming();

      ::file::path path;

      path = pathFolder / "bitmap-source" / scopedstrBitmapSource;

      //auto estatus = 
      
      constructø(m_pmemorymap);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //estatus = 

      if (bCreate)
      {

         m_pmemorymap->open_path(path, false, true, true, 128_MiB);
      }

      else
      {

         m_pmemorymap->open_path(path, false, true, false, 128_MiB);

      }

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //return ::success;

   }


   void bitmap_source_buffer_graphics::clear_bitmap_source()
   {

      m_strBitmapSource.empty();

      if (m_pmemorymap)
      {

         synchronous_lock synchronouslock(m_pmutexBitmapSource, DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

         auto estatus = m_pmemorymap.release();

      }

      m_pmutexBitmapSource.release();
      
      //return ::success;

   }


   string bitmap_source_buffer_graphics::get_bitmap_source() const
   {

      if (!is_ipc_copy_enabled())
      {

         return "";

      }

      return m_strBitmapSource;

   }


   bool bitmap_source_buffer_graphics::ipc_copy(const pixmap * ppixmap)
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

      synchronous_lock synchronouslock(m_pmutexBitmapSource, DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      try
      {

         ::i64 * p = (::i64 *)pdata;

         ::i32 iScan = (::i32)(ppixmap->m_iScan);

         *p++ = m_pwindow->m_pointWindow.x;
         *p++ = m_pwindow->m_pointWindow.y;
         *p++ = m_pwindow->m_sizeWindow.cx;
         *p++ = m_pwindow->m_sizeWindow.cy;
         *p++ = ppixmap->m_sizeRaw.cx;
         *p++ = ppixmap->m_sizeRaw.cy;
         *p++ = iScan;

         //::copy_image32((::color32_t*)p, ppixmap->size(), iScan, ppixmap);

         memory_copy(p, ppixmap->m_pimage32Raw, ppixmap->m_sizeRaw.cy * iScan);

      }
      catch (...)
      {

      }

      return true;

   }


   bool bitmap_source_buffer_graphics::buffer_lock_round_swap_key_buffers()
   {

      if (!m_pwindow)
      {

         return false;

      }

      if (!m_pwindow->user_interaction())
      {

         return false;

      }

      if (is_ipc_copy_enabled())
      {

         if (m_pwindowbuffer)
         {

            if (m_pwindowbuffer->m_ppixmapWindowBuffer)
            {

               if (m_pwindowbuffer->m_ppixmapWindowBuffer->m_pimage32Raw)
               {

                  if (ipc_copy(m_pwindowbuffer->m_ppixmapWindowBuffer))
                  {

                     return true;

                  }

               }

            }

         }

         auto ppixmapImageBufferItem = get_screen_item()->m_pimageBufferItem->map();

         if (!ipc_copy(ppixmapImageBufferItem))
         {

            return false;

         }

      }

      return true;

   }


} // namespace graphics



