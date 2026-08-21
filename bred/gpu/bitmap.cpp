// Created by camilo on 2026-07-27 14:21 <3ThomasBorregaardSørensen!! Mummi!! Bilbo!!
#include "platform.h"
#include "bitmap.h"
#include "acme/graphics/image/pixmap_t.h"
#include "apex/gpu/approach.h"
#include "bred/gpu/context_lock.h"
#include "bred/gpu/device.h"
#include "bred/gpu/renderer.h"
#include "bred/gpu/texture.h"


namespace gpu
{


   bitmap::bitmap() 
   {
   

   }


   bitmap::~bitmap() 
   {


   }


   void bitmap::destroy()
   {

      ::draw2d::bitmap::destroy();
      m_pgputexture.release();

   }


   void bitmap::create_bitmap(::draw2d::graphics *pgraphics, const ::i32_size &size, ::pixmap * ppixmap)
   {

      ::pixmap_t pixmap{};

      int iScan = size.cx * 4;

      if (ppixmap && ppixmap->m_iScan > iScan)
      {

         iScan = ppixmap->m_iScan;
      }

      pixmap.initialize_pixmap(size, (::image32_t *)ppixmap->m_memoryPixmap.data_if_at_least(size.cy * iScan), iScan);

      _create_gpu_bitmap(size, &pixmap);

   }

   
   ::gpu::texture *bitmap::gpu_texture() const
   {

      //if (!m_pgputexture)
      //{

      //   ((bitmap *)this)->create_gpu_texture();

      //}

      return m_pgputexture;

   }


   void bitmap::_create_gpu_bitmap(const ::i32_size & size, pixmap_t * ppixmap)
   {

      m_size = size;

      auto pacmeuserinteractionMain = m_papplication->main_acme_user_interaction();

      auto pacmewindowingwindow = pacmeuserinteractionMain->m_pacmewindowingwindow;

      auto pgpudevice = m_papplication->get_gpu_approach()->get_gpu_device(pacmewindowingwindow);

      _synchronous_lock synchronouslock(pgpudevice->synchronization());

      auto pgpucontextlease = pgpudevice->acquire_gpu_context(::gpu::e_output_none, m_size);

      if (::is_set(ppixmap))
      {

         initialize_gpu_bitmap(pgpucontextlease, m_size, *ppixmap);

      }
      else
      {

         initialize_gpu_bitmap(pgpucontextlease, m_size, {});

      }


      // if (!m_pimage32Raw)
      //{

      //   return;

      //}

      // auto pgputexture = m_pgputexture;

      // if (!pgputexture)
      //{

      //   throw ::exception(error_wrong_state);
      //}

      // auto pgpucontext = pgputexture->context();

      // if (!pgpucontext)
      //{

      //   throw ::exception(error_wrong_state);
      //}

      // pgpucontext->send(
      //    [this, pgputexture, pgpucontext]()
      //    {
      //       auto bPerformanceDiagnostics =
      //          m_papplication &&
      //          m_papplication->m_gpu.m_bPerformanceDiagnostics.load(::std::memory_order_relaxed);

      //      if (bPerformanceDiagnostics)
      //      {

      //         auto uPerformanceDiagnosticsGeneration =
      //            m_papplication->m_gpu.m_uPerformanceDiagnosticsGeneration.load(::std::memory_order_relaxed);

      //         if (uPerformanceDiagnosticsGeneration !=
      //               m_uPerformanceDiagnosticsGenerationLast.load(::std::memory_order_relaxed))
      //         {

      //            reset_performance_diagnostics();
      //         }
      //      }

      //      auto timeStart = ::std::chrono::steady_clock::time_point{};

      //      if (bPerformanceDiagnostics)
      //      {

      //         timeStart = ::std::chrono::steady_clock::now();
      //      }


      //      ::gpu::context_lock contextlock(pgpucontext);

      //      pgputexture->write_pixels(m_size, m_pimage32Raw, m_iScan);

      //      auto uMicroseconds = (::u64)0;

      //      if (bPerformanceDiagnostics)
      //      {

      //         uMicroseconds = (::u64)::std::chrono::duration_cast<::std::chrono::microseconds>(
      //                              ::std::chrono::steady_clock::now() - timeStart)
      //                              .count();
      //      }

      //      pgputexture->defer_fence();
      //      // pthis->pixmap::unmap();
      //      // pthis->m_bMapped = false;

      //      if (bPerformanceDiagnostics)
      //      {

      //         record_performance_unmap_transition(uMicroseconds);
      //      }
      //   });
   }


   void bitmap::initialize_gpu_bitmap(::gpu::context *pgpucontext, const ::i32_size &size,
                                    const ::gpu::texture_data &texturedata)
   {

      //if (has_active_destination_graphics_lease())
      //{

      //   throw ::exception(error_wrong_state, "cannot create or resize a GPU image with active destination graphics");
      //}

      if (!pgpucontext || size.is_empty())
      {

         throw ::exception(error_bad_argument);

      }

      ::gpu::context_lock contextlock(pgpucontext);

      auto pgpurenderer = pgpucontext->get_gpu_renderer();

      auto pgputexture = pgpurenderer->create_image_texture(size, false, texturedata);

      if (!pgputexture)
      {

         throw ::exception(error_failed, "Failed to create GPU image texture.");
      }

      // auto pixmap = texturedata.raw_scoped_pixmap();

      m_pgputexture = pgputexture;
      m_size = size;
      //m_sizeRaw = size;
      //m_point.clear();

      // if (texturedata.is)
      // m_iScan = pixmap.m_iScan;
      // m_pimage32 = pixmap.m_pimage32;
      // m_pimage32Raw = pixmap.m_pimage32Raw;
      set_ok_flag();

   }


   ::gpu::texture * bitmap::get_gpu_texture()
   {

      if (!m_pgputexture)
      {

         //auto pgpucontextMain = m_papplication->get_gpu_approach()
         //                          ->get_gpu_device(m_pacmeuserinteractionMain->m_pacmewindowingwindow)
         //                          ->main_context();

         auto pacmeuserinteractionMain = m_papplication->main_acme_user_interaction();

         auto pacmewindowingwindow = pacmeuserinteractionMain->m_pacmewindowingwindow;

         auto pgpudevice = m_papplication->get_gpu_approach()->get_gpu_device(pacmewindowingwindow);

         _synchronous_lock synchronouslock(pgpudevice->synchronization());

         auto pgpucontextlease = pgpudevice->acquire_gpu_context(::gpu::e_output_none, m_size);

         initialize_gpu_bitmap(pgpucontextlease, m_size, {});

      }

      return m_pgputexture;

   }



} // namespace gpu



