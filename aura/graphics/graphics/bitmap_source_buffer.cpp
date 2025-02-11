#include "framework.h"
#include "bitmap_source_buffer.h"
#include "acme/parallelization/mutex.h"
#include "acme/parallelization/single_lock.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/platform/node.h"
#include "acme/filesystem/filesystem/directory_context.h"
#include "apex/platform/context.h"
#include "aura/graphics/image/image.h"
#include "aura/user/user/interaction.h"
#include "aura/windowing/window.h"
#include "aura/windowing/windowing.h"


namespace graphics
{


   bitmap_source_buffer::bitmap_source_buffer()
   {


   }


   bitmap_source_buffer::~bitmap_source_buffer()
   {

      clear_bitmap_source();

   }


   void bitmap_source_buffer::initialize_graphics_graphics(::windowing::window* pwindow)
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
         
         __øconstruct(m_pmemorymap);

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


   void bitmap_source_buffer::set_bitmap_source(const ::string &strBitmapSource)
   {

      if (m_strBitmapSource == strBitmapSource)
      {

         return;

      }

      clear_bitmap_source();

      m_strBitmapSource = strBitmapSource;

      char szName[] = "Local\\bitmap-source:%s";

      string strMutexName;

      strMutexName.formatf(szName, strBitmapSource.c_str());

      m_pmutexBitmapSource = node()->create_local_named_mutex(this, false, strMutexName, nullptr);

      synchronous_lock synchronouslock(m_pmutexBitmapSource);

      ::file::path pathFolder;

      pathFolder = directory()->config();

      ::file::path path;

      path = pathFolder / "bitmap-source" / strBitmapSource;

      //auto estatus = 
      
      __øconstruct(m_pmemorymap);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //estatus = 
      
      m_pmemorymap->open_path(path, false, true, true, 128_MiB);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //return ::success;

   }


   void bitmap_source_buffer::clear_bitmap_source()
   {

      m_strBitmapSource.empty();

      if (m_pmemorymap)
      {

         synchronous_lock synchronouslock(m_pmutexBitmapSource);

         auto estatus = m_pmemorymap.release();

      }

      m_pmutexBitmapSource.release();
      
      //return ::success;

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

         long long * p = (long long *)pdata;

         int iScan = (int)(ppixmap->width() * sizeof(::color32_t));

         *p++ = ppixmap->width();
         *p++ = ppixmap->height();
         *p++ = iScan;

         //::copy_image32((::color32_t*)p, ppixmap->size(), iScan, ppixmap);

         memory_copy(p, ppixmap->m_pimage32Raw, ppixmap->height() * iScan);

      }
      catch (...)
      {

      }

      return true;

   }


   bool bitmap_source_buffer::buffer_lock_round_swap_key_buffers()
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

         if (!ipc_copy(get_screen_item()->m_pimage2))
         {

            return false;

         }

      }

      return true;

   }


} // namespace graphics



