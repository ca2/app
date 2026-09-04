// Created by camilo on 2026-07-27 14:21 <3ThomasBorregaardSørensen!! Mummi!! Bilbo!!
#include "platform.h"
#include "bitmap.h"
#include "image.h"
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


   void bitmap::create_bitmap(::draw2d::graphics * pdraw2dgraphics, const ::i32_size & size, ::pixmap * ppixmap)
   {

      ::draw2d::bitmap::create_bitmap(pdraw2dgraphics, size, ppixmap);
      //::pixmap_t pixmap{};

      //int iScan = size.cx * 4;

      //if (ppixmap && ppixmap->m_iScan > iScan)
      //{

      //   iScan = ppixmap->m_iScan;
      //}

      //pixmap.initialize_pixmap(size, (::image32_t *)ppixmap->m_memoryPixmap.data_if_at_least(size.cy * iScan), iScan);

      //_create_gpu_bitmap(size, pdraw2dgraphics, &pixmap);

   }


   //::gpu::texture *bitmap::gpu_texture() const
   //{

   //   //if (!m_pgputexture)
   //   //{

   //   //   ((bitmap *)this)->create_gpu_texture();

   //   //}

   //   //return m_pgputexture;

   //   return ::gpu::bitmap::gpu_texture();

   //}


   void bitmap::preserve_image(const ::i32_size & size, ::image::image * pimage)
   {

      if (!pimage || size.is_empty())
      {

         throw ::exception(error_bad_argument);

      }

      if (pimage->m_pdraw2dbitmap != this)
      {

         throw ::exception(
            error_bad_argument,
            "The image is not backed by this OpenGL bitmap");

      }

      if (pimage->has_active_destination_graphics_lease()
         || pimage->m_pimagepixmaplease
         || (pimage->m_ppixmapOwned
            && pimage->m_ppixmapOwned->m_interlockedcountMap > 0))
      {

         throw ::exception(
            error_wrong_state,
            "Cannot preserve an image while it is mapped or has active destination graphics");

      }

      auto sizeRawOld = pimage->raw_size();
      auto sizeRawRequired = pimage->m_point + size;
      auto sizeRawNew = sizeRawOld.maximum(sizeRawRequired);

      if (sizeRawNew == sizeRawOld)
      {

         pimage->m_size = size;
         return;

      }

      auto pgputextureOld = ::as_pointer(gpu_texture(nullptr));

      if (!pgputextureOld)
      {

         throw ::exception(
            error_wrong_state,
            "OpenGL bitmap has no texture to preserve");

      }

      auto pgpudevice = pgputextureOld->m_pgpucontext->m_pgpudevice;

      auto pgpucontextlease = pgpudevice->acquire_gpu_context(
         ::gpu::e_output_none,
         {256, 256},
         pimage->m_pgraphicsOwned);

      if (!pgpucontextlease)
      {

         throw ::exception(
            error_wrong_state,
            "Could not acquire an OpenGL context to preserve the bitmap");

      }

      ::gpu::texture_data texturedata(pgputextureOld);

      initialize_gpu_bitmap(pgpucontextlease, sizeRawNew, texturedata);

      m_size = sizeRawNew;
      m_iStride = sizeRawNew.cx * (::i32)sizeof(::image32_t);

      pimage->m_size = size;
      pimage->m_sizeRaw = sizeRawNew;
      pimage->m_iScan = maximum(pimage->m_iScan, m_iStride);

      // The resized GPU texture is now authoritative. Keeping the former CPU
      // storage would expose its old dimensions and stale pixels on the next map.
      pimage->m_ppixmapOwned.release();
      //m_memOut.set_size(0);
      //m_memIn.set_size(0);
      pimage->m_bGraphicsWasAcquiredAfterLastMap = true;
      pimage->m_bWasMappedAfterLastGraphicsAcquisition = false;


   }


   void bitmap::write_pixels(
      const ::i32_size & size,
      const ::i32_point & point,
      const ::image32_t * pimage32,
      ::i32 iScan,
      bool bTopDown)
   {

      if (!m_pgputexture
         || !pimage32
         || size.is_empty()
         || iScan < size.cx * (::i32) sizeof(::image32_t))
      {

         throw ::exception(error_bad_argument);

      }

      ::pixmap_t pixmap;

      pixmap.m_size = size;
      pixmap.m_sizeRaw = size;
      pixmap.m_iScan = iScan;
      pixmap.m_pimage32 = (::image32_t *) pimage32;
      pixmap.m_pimage32Raw = (::image32_t *) pimage32;
      pixmap.m_bTopLeft = bTopDown;

      m_pgputexture->write_pixels(false, &pixmap, point);

   }

   
   void bitmap::update_bitmap_as_backed_by_gpu_texture(::gpu::texture * pgputexture, ::draw2d::graphics * pdraw2graphics)
   {

      m_pgputexture = pgputexture;

      ///::cast < ::gpu::graphics > pdraw2dgraphics = pdraw2dgraphics;

   }


   void bitmap::_create_gpu_bitmap(const ::i32_size & size, ::draw2d::graphics * pdraw2dgraphics, pixmap_t * ppixmap)
   {

      m_size = size;

      auto pacmeuserinteractionMain = m_papplication->main_acme_user_interaction();

      auto pacmewindowingwindow = pacmeuserinteractionMain->m_pacmewindowingwindow;

      auto pgpudevice = m_papplication->get_gpu_approach()->get_gpu_device(pacmewindowingwindow);

      _synchronous_lock synchronouslock(pgpudevice->synchronization());

      auto pgpucontextlease = pgpudevice->acquire_gpu_context(::gpu::e_output_none, m_size, pdraw2dgraphics);

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

      auto pgputexture = createø< texture>();

      ::gpu::texture_attributes textureattributes(size);

      textureattributes.m_sizeRaw = size;

      ::gpu::texture_flags textureflags;

      textureflags.m_bWithDepth = false;
      textureflags.m_bRenderTarget = true;
      textureflags.m_bShaderResource = true;
      textureflags.m_bTransferTarget = true;
      textureflags.m_bTransferSource = true;

      pgputexture->create_texture(pgpucontext, textureattributes, textureflags, texturedata);

      pgpucontext->on_create_texture(pgputexture);

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


   ::gpu::texture * bitmap::gpu_texture(::gpu::context * pgpucontext)
   {

      if (!m_pgputexture)
      {

         //auto pgpucontextMain = m_papplication->get_gpu_approach()
         //                          ->get_gpu_device(m_pacmeuserinteractionMain->m_pacmewindowingwindow)
         //                          ->main_context();

         auto pacmeuserinteractionMain = m_papplication->main_acme_user_interaction();

         auto pacmewindowingwindow = pacmeuserinteractionMain->m_pacmewindowingwindow;

         //auto pgpudevice = m_papplication->get_gpu_approach()->get_gpu_device(pacmewindowingwindow);

         //_synchronous_lock synchronouslock(pgpudevice->synchronization());

         //auto pgpucontextlease = pgpudevice->acquire_gpu_context(::gpu::e_output_none, m_size, nullptr);

         auto pixmap = get_pixmap();

         if (pixmap.is_ok())
         {

            initialize_gpu_bitmap(pgpucontext, m_size, { pixmap });

         }
         else
         {

            initialize_gpu_bitmap(pgpucontext, m_size, {});

         }

      }

      return m_pgputexture;

   }


   pixmap_t bitmap::get_pixmap()
   {

      return ::draw2d::bitmap::get_pixmap();

   }


} // namespace gpu



