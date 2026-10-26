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
#include "acme/filesystem/filesystem/file_context.h"
#include "acme/filesystem/filesystem/listing.h"
#include "acme/filesystem/file/file.h"
#include <chrono>


namespace graphics
{

   bitmap_source_interest::~bitmap_source_interest()
   {
      release_interest();
   }

   void bitmap_source_interest::acquire(const ::scoped_string & scopedstrProducerAppId,
      const ::scoped_string & scopedstrBitmapSourceName,
      const ::scoped_string & scopedstrConsumerAppId)
   {
      string strProducerAppId(scopedstrProducerAppId);
      string strBitmapSourceName(scopedstrBitmapSourceName);
      string strConsumerAppId(scopedstrConsumerAppId);
      if (strProducerAppId.is_empty() || strProducerAppId.begins("/") || strProducerAppId.contains("..")
         || strProducerAppId.contains("\\") || strProducerAppId.contains(":")
         || strBitmapSourceName.is_empty() || strBitmapSourceName.contains("..")
         || strBitmapSourceName.contains("/") || strBitmapSourceName.contains("\\")
         || strConsumerAppId.is_empty() || strConsumerAppId.begins("/") || strConsumerAppId.contains("..")
         || strConsumerAppId.contains("\\") || strConsumerAppId.contains(":"))
      {
         throw ::exception(error_bad_argument);
      }
      release_interest();
      auto pathFolder = directory_system()->roaming() / strProducerAppId
         / "bitmap-source" / strBitmapSourceName;
      directory()->create(pathFolder);
      auto pathLease = pathFolder / (strConsumerAppId + ".lock");
//<<<<<<< HEAD
      directory()->create(pathLease.folder());
//=======
//>>>>>>> origin/main
      auto pfile = file()->get_file(pathLease,
         ::file::e_open_read_write | ::file::e_open_create | ::file::e_open_no_truncate
         | ::file::e_open_share_deny_none | ::file::e_open_no_inherit
         | ::file::e_open_no_share_violation_wait);
#if defined(WINDOWS)
      // Lock beyond the declaration contents so readers can inspect metadata.
      pfile->lock(0x7ffffffe, 1);
#endif
      m_pfileLease = pfile;
   }

   void bitmap_source_interest::release_interest()
   {
      // Closing the handle also releases the lock, including after a crash.
      m_pfileLease.release();
   }

   void bitmap_source_interest::destroy()
   {
      release_interest();
      object::destroy();
   }

   void bitmap_source_buffer_graphics::destroy()
   {
      stop_interest_monitor();
      graphics::destroy();
   }

   bool bitmap_source_buffer_graphics::has_bitmap_source_interest()
   {
#if defined(WINDOWS)
      ::file::listing_base listing;
      auto pathInterestFolder = directory_system()->roaming() / m_strAppId
         / "bitmap-source" / m_strBitmapSource;
      listing.set_file_listing(pathInterestFolder);
      listing.m_bRecursive = true;
      directory()->enumerate(listing);
      for (auto & path : listing)
      {
         auto strName = path.name();
         if (!strName.case_insensitive_ends(".lock"))
            continue;
         ::file_pointer pfile;
         try
         {
            pfile = file()->get_file(path, ::file::e_open_read_write
               | ::file::e_open_share_deny_none | ::file::e_open_no_inherit
               | ::file::e_open_no_share_violation_wait | ::file::e_open_no_callstack);
         }
         catch (...)
         {
            continue; // An open failure is not evidence of an active lease.
         }
         try
         {
            // Probe the consumer's byte-range lock without modifying or
            // removing its declaration. Only a lock conflict signals interest.
            pfile->lock(0x7ffffffe, 1);
         }
         catch (const ::exception & exception)
         {
            if (exception.m_estatus == error_file_lock_violation)
               return true;
            continue;
         }
         pfile->unlock(0x7ffffffe, 1);
      }
      return false;
#else
      // The POSIX file adapter currently has no lock implementation.
      // Preserve publishing there until a real lease implementation is available.
      return true;
#endif
   }

   void bitmap_source_buffer_graphics::start_interest_monitor()
   {
#if defined(WINDOWS)
      directory()->create(directory_system()->roaming() / m_strAppId
         / "bitmap-source" / m_strBitmapSource);
      m_bStopBitmapSourceInterest = false;
      m_threadBitmapSourceInterest = std::thread([this]()
      {
         std::unique_lock<std::mutex> lock(m_mutexBitmapSourceInterest);
         while (!m_bStopBitmapSourceInterest)
         {
            lock.unlock();
            bool bInterested = false;
            try { bInterested = has_bitmap_source_interest(); }
            catch (...) { }
            m_bBitmapSourceInterested.store(bInterested);
            lock.lock();
            m_conditionBitmapSourceInterest.wait_for(lock, std::chrono::milliseconds(500),
               [this]() { return m_bStopBitmapSourceInterest; });
         }
      });
#else
      m_bBitmapSourceInterested.store(true);
#endif
   }

   void bitmap_source_buffer_graphics::stop_interest_monitor()
   {
      {
         std::lock_guard<std::mutex> lock(m_mutexBitmapSourceInterest);
         m_bStopBitmapSourceInterest = true;
      }
      m_conditionBitmapSourceInterest.notify_all();
      if (m_threadBitmapSourceInterest.joinable())
         m_threadBitmapSourceInterest.join();
      m_bBitmapSourceInterested.store(false);
   }


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
         
         if (pwindow->m_strBitmapSourceAppId.has_character())
         {
            set_bitmap_source(pwindow->m_strBitmapSourceAppId,
               pwindow->m_strBitmapSource, pwindow->m_bBitmapSourceCreate);
         }
         else
         {
            set_bitmap_source(pwindow->m_strBitmapSource);
         }

         //if (!estatus)
         //{

         //   return estatus;

         //}

      }



      //return estatus;

   }


   void bitmap_source_buffer_graphics::set_bitmap_source(const ::scoped_string & scopedstrBitmapSource, bool bCreate)
   {
      string strAppId;
      if (application())
         strAppId = application()->m_strAppId;
      set_bitmap_source(strAppId, scopedstrBitmapSource, bCreate);
   }


   void bitmap_source_buffer_graphics::set_bitmap_source(
      const ::scoped_string & scopedstrAppId,
      const ::scoped_string & scopedstrBitmapSource,
      bool bCreate)
   {

      string strAppId(scopedstrAppId);
      string strBitmapSource(scopedstrBitmapSource);
      if (strAppId.is_empty() || strAppId.begins("/") || strAppId.contains("..")
         || strAppId.contains("\\") || strAppId.contains(":")
         || strBitmapSource.is_empty() || strBitmapSource.contains("..")
         || strBitmapSource.contains("/") || strBitmapSource.contains("\\"))
      {
         throw ::exception(error_bad_argument);
      }

      if (m_strAppId == strAppId && m_strBitmapSource == strBitmapSource)
      {

         return;

      }

      clear_bitmap_source();

      m_strAppId = strAppId;
      m_strBitmapSource = strBitmapSource;

      if (!bCreate)
      {

         construct_newø(m_pbitmapsourceinterest);
         string strConsumerAppId;
         if (application())
            strConsumerAppId = application()->m_strAppId;
         m_pbitmapsourceinterest->acquire(
            m_strAppId, m_strBitmapSource, strConsumerAppId);

      }

      ::i8 szName[] = "Local\\bitmap-source:%s:%s";

      string strMutexName;

      strMutexName.formatf(szName, m_strAppId.c_str(), scopedstrBitmapSource.as_string().c_str());

      if (bCreate)
      {

         m_pmutexBitmapSource = node()->create_local_named_mutex(this, false, strMutexName, nullptr);

      }
      else
      {

         m_pmutexBitmapSource = node()->open_local_named_mutex(this, strMutexName);
         if (!m_pmutexBitmapSource)
         {
            // The consumer can start before the producer creates its mutex.
            // Create the same named mutex so either process can initialize first.
            m_pmutexBitmapSource = node()->create_local_named_mutex(
               this, false, strMutexName, nullptr);
         }

      }

      if (!m_pmutexBitmapSource)
      {
         throw ::exception(error_wrong_state, "Could not open or create bitmap source mutex");
      }

      synchronous_lock synchronouslock(m_pmutexBitmapSource, DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      ::file::path pathFolder;

      pathFolder = directory_system()->roaming();

      ::file::path path;

      path = pathFolder / m_strAppId / "bitmap-source" / scopedstrBitmapSource / "buffer.bin";
      directory()->create(path.folder());

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
         start_interest_monitor();
      }

      else
      {

         m_pmemorymap->open_path(path, false, true, false, 128_MiB);
         m_bBitmapSourceInterested.store(true);

      }

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //return ::success;

   }


   void bitmap_source_buffer_graphics::clear_bitmap_source()
   {

      stop_interest_monitor();

      m_strBitmapSource.empty();
      m_strAppId.empty();

      if (m_pmemorymap)
      {

         synchronous_lock synchronouslock(m_pmutexBitmapSource, DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

         auto estatus = m_pmemorymap.release();

      }

      m_pbitmapsourceinterest.release();

      m_pmutexBitmapSource.release();
      
      //return ::success;

   }


   string bitmap_source_buffer_graphics::get_bitmap_source() const
   {

      if (!m_pmemorymap || !m_pmemorymap->is_mapped())
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

         auto sizeBitmap = ppixmap->raw_size();

         auto iScan = ppixmap->m_iScan;

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
               sizeBitmap, iScan, ppixmap->m_pimage32Raw, ppixmap->m_iScan);

         }
         else
         {

            pimage32Target->y_swap_copy(
               sizeBitmap, iScan, ppixmap->m_pimage32Raw, ppixmap->m_iScan);

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

         //auto ppixmapImageBufferItem = get_screen_item()->m_pimageBufferItem->map();

         //if (!ipc_copy(ppixmapImageBufferItem))
         //{

         //   return false;

         //}

      }

      return true;

   }


} // namespace graphics



