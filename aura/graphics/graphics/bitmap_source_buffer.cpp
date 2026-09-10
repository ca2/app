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
#include "aura/windowing/display.h"
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

         auto sizeBitmap = ppixmap->size();

         auto iScan = sizeBitmap.cx * (::i32)sizeof(::image32_t);

         ::memsize sRequired = (::memsize)sizeof(bitmap_source_buffer_header)
            + (::memsize)iScan * (::memsize)sizeBitmap.cy;

         auto sMemoryMap = (::memsize)m_pmemorymap->m_size;

         if (sizeBitmap.is_empty()
            || !ppixmap->data()
            || ppixmap->m_iScan < sizeBitmap.cx * (::i32)sizeof(::image32_t)
            || sRequired > sMemoryMap)
         {

            return false;

         }

         ::i32_rectangle rectangleMainMonitor;

         auto pdisplay = system()->windowing()->display();

         pdisplay->get_main_monitor(rectangleMainMonitor);

         if (rectangleMainMonitor.is_empty())
         {

            auto sizeMainMonitor = pdisplay->get_main_monitor_size();

            rectangleMainMonitor = {
               0, 0, sizeMainMonitor.cx, sizeMainMonitor.cy};

         }

         auto pheader = (::graphics::bitmap_source_buffer_header *)pdata;

         pheader->m_iMagic = BITMAP_SOURCE_BUFFER_MAGIC;
         pheader->m_iVersion = BITMAP_SOURCE_BUFFER_VERSION;
         pheader->m_xWindow = m_pwindow->m_pointWindow.x;
         pheader->m_yWindow = m_pwindow->m_pointWindow.y;
         pheader->m_cxWindow = m_pwindow->m_sizeWindow.cx;
         pheader->m_cyWindow = m_pwindow->m_sizeWindow.cy;
         pheader->m_xMonitor = rectangleMainMonitor.left;
         pheader->m_yMonitor = rectangleMainMonitor.top;
         pheader->m_cxMonitor = rectangleMainMonitor.width();
         pheader->m_cyMonitor = rectangleMainMonitor.height();
         pheader->m_cxBitmap = sizeBitmap.cx;
         pheader->m_cyBitmap = sizeBitmap.cy;
         pheader->m_iScan = iScan;
         pheader->m_bTopLeft = true;

         auto pimage32Target = (::image32_t *)(pheader + 1);

         if (ppixmap->m_bTopLeft)
         {

            pimage32Target->copy(
               sizeBitmap, iScan, ppixmap->data(), ppixmap->m_iScan);

         }
         else
         {

            pimage32Target->y_swap_copy(
               sizeBitmap, iScan, ppixmap->data(), ppixmap->m_iScan);

         }

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



