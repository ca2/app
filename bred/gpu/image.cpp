#include "platform.h"
#include "bitmap.h"
#include "image.h"
#include "context.h"
#include "context_lock.h"
#include "layer.h"
#include "renderer.h"
#include "texture.h"
#include "texture_site.h"
#include "acme/platform/application.h"
#include "apex/gpu/approach.h"
#include "aura/graphics/draw2d/draw2d.h"
#include "aura/user/user/interaction.h"
#include "bred/gpu/device.h"
#include "bred/gpu/graphics.h"


CLASS_DECL_ACME::string _001_image32_diagnostics(const ::i32_size &size, const image32_t *pimage32, int iScan);

namespace
{


   ::std::atomic<::u64> s_uMapTransitionSequence{0};


   ::i64 steady_nanoseconds()
   {

      return ::std::chrono::duration_cast<::std::chrono::nanoseconds>(
         ::std::chrono::steady_clock::now().time_since_epoch()).count();

   }


} // namespace


namespace gpu
{


   image::image()
   {

   }


   image::~image()
   {

      destroy();

   }


   //::draw2d::graphics_pointer image::owned_graphics() const
   //{

   //   unmap();

   //   return _get_graphics();

   //}


   //void image::create_gpu_texture()
   //{

   //   auto pacmewindowingwindow = m_pacmeuserinteractionMain->m_pacmewindowingwindow;

   //   auto pgpudevice = m_papplication->get_gpu_approach()->get_gpu_device(pacmewindowingwindow);

   //   _synchronous_lock synchronouslock(pgpudevice->synchronization());

   //   auto pgpucontextlease = pgpudevice->acquire_gpu_context(::gpu::e_output_none, m_size);

   //   auto mapImage = pixmap::map();

   //   ((image *)this)->initialize_gpu_image(pgpucontextlease, m_size, mapImage);

   //   //if (!m_pimage32Raw)
   //   //{

   //   //   return;

   //   //}

   //   //auto pgputexture = m_pgputexture;

   //   //if (!pgputexture)
   //   //{

   //   //   throw ::exception(error_wrong_state);
   //   //}

   //   //auto pgpucontext = pgputexture->context();

   //   //if (!pgpucontext)
   //   //{

   //   //   throw ::exception(error_wrong_state);
   //   //}

   //   //pgpucontext->send(
   //   //   [this, pgputexture, pgpucontext]()
   //   //   {
   //   //      auto bPerformanceDiagnostics =
   //   //         m_papplication &&
   //   //         m_papplication->m_gpu.m_bPerformanceDiagnostics.load(::std::memory_order_relaxed);

   //   //      if (bPerformanceDiagnostics)
   //   //      {

   //   //         auto uPerformanceDiagnosticsGeneration =
   //   //            m_papplication->m_gpu.m_uPerformanceDiagnosticsGeneration.load(::std::memory_order_relaxed);

   //   //         if (uPerformanceDiagnosticsGeneration !=
   //   //               m_uPerformanceDiagnosticsGenerationLast.load(::std::memory_order_relaxed))
   //   //         {

   //   //            reset_performance_diagnostics();
   //   //         }
   //   //      }

   //   //      auto timeStart = ::std::chrono::steady_clock::time_point{};

   //   //      if (bPerformanceDiagnostics)
   //   //      {

   //   //         timeStart = ::std::chrono::steady_clock::now();
   //   //      }


   //   //      ::gpu::context_lock contextlock(pgpucontext);

   //   //      pgputexture->write_pixels(m_size, m_pimage32Raw, m_iScan);

   //   //      auto uMicroseconds = (::u64)0;

   //   //      if (bPerformanceDiagnostics)
   //   //      {

   //   //         uMicroseconds = (::u64)::std::chrono::duration_cast<::std::chrono::microseconds>(
   //   //                              ::std::chrono::steady_clock::now() - timeStart)
   //   //                              .count();
   //   //      }

   //   //      pgputexture->defer_fence();
   //   //      // pthis->pixmap::unmap();
   //   //      // pthis->m_bMapped = false;

   //   //      if (bPerformanceDiagnostics)
   //   //      {

   //   //         record_performance_unmap_transition(uMicroseconds);
   //   //      }
   //   //   });

   //}


   ::gpu::texture * image::gpu_texture() const
   {

      ::cast<::gpu::bitmap> pgpubitmap = m_pdraw2dbitmap;

      if (!pgpubitmap)
      {

         return nullptr;

      }

      ::cast < ::gpu::graphics > pgpugraphics = m_pgraphicsOwned;

      if(pgpugraphics && pgpugraphics->m_pgpucontextOwned)
      {

         return pgpubitmap->gpu_texture(pgpugraphics->m_pgpucontextOwned);

      }

      return pgpubitmap->gpu_texture(nullptr);

   }



   void image::update_as_backed_by_gpu_texture(const ::i32_size & size, ::gpu::texture * pgputexture, ::draw2d::graphics * pdraw2dgraphics)
   {

      auto ptexture = pgputexture;

      ::cast < ::gpu::bitmap > pdraw2dbitmap = m_pdraw2dbitmap;

      if (!pdraw2dbitmap)
      {

         defer_constructø(m_pdraw2dbitmap);

         pdraw2dbitmap = m_pdraw2dbitmap;

      }

      if (pdraw2dbitmap->m_pgputexture != ptexture)
      {

         m_size = ptexture->m_textureattributes.m_size;

         m_sizeRaw = ptexture->m_textureattributes.m_sizeRaw;

         pdraw2dbitmap->update_bitmap_as_backed_by_gpu_texture(ptexture, pdraw2dgraphics);

      }

   }


   void image::update_as_render_target(const ::i32_size & sizeRaw, ::user::interaction * puserinteraction, ::draw2d::graphics * pdraw2dgraphics, ::enum_flag eflagCreate, ::i32 iGoodStride, bool bPreserve, bool bTopDraw2d)
   {

      if (!puserinteraction)
      {

         throw ::exception(error_null_pointer, "user::interaction is null");

      }

      m_pacmeuserinteractionAffinity = puserinteraction;

      // if (m_pgputexture && m_pgraphics && m_pgputexture->size() == size)

      destroy();

      if (sizeRaw.is_empty())
      {

         return;

      }

      create_as_descriptor(sizeRaw, eflagCreate, iGoodStride);

      auto pdraw2dbitmap = createø<::draw2d::bitmap>();

      ::cast<::gpu::bitmap> pgpubitmap = pdraw2dbitmap;

      //auto pacmewindowingwindow = m_pacmeuserinteractionMain->m_pacmewindowingwindow;

      //auto pgpudevice = m_papplication->get_gpu_approach()->get_gpu_device(pacmewindowingwindow);

      //_synchronous_lock synchronouslock(pgpudevice->synchronization());

      //auto pixmap = this->pixmap::map();

      auto pacmewindowingwindow = m_pacmeuserinteractionAffinity->m_pacmewindowingwindow;

      auto pgpudevice = m_papplication->get_gpu_approach()->get_gpu_device(pacmewindowingwindow);

      _synchronous_lock synchronouslock(pgpudevice->synchronization());

      if (!bTopDraw2d)
      {

         auto pgpucontextlease = pgpudevice->acquire_gpu_context(
            bTopDraw2d ? ::gpu::e_output_draw2d_bitmap : ::gpu::e_output_none, {25, 25}, pdraw2dgraphics);

         pgpucontextlease->m_pacmeuserinteractionAffinity = m_pacmeuserinteractionAffinity;

         //::pixmap_t pixmap;

         //pixmap.m_pimage32Raw = (::image32_t *)pimage32;

         //pixmap.m_pimage32 = (::image32_t *)pimage32;

         //pixmap.m_size = size;

         //pixmap.m_sizeRaw = size;

         //pixmap.m_iScan = iScan;

         //pgpubitmap->initialize_gpu_bitmap(pgpucontextlease, sizeRaw, pixmap);

         pgpubitmap->initialize_gpu_bitmap(pgpucontextlease, sizeRaw, {});

         m_pdraw2dbitmap = pgpubitmap;

      }

      //auto pdraw2dgraphics = system()->draw2d()->allocate_graphics(m_pacmeuserinteractionAffinity);

      //if (bTopDraw2d)
      //{

      //   pdraw2dgraphics->create_for_window_draw2d(puserinteraction, sizeRaw);

      //}
      //else
      //{

      //   pdraw2dgraphics->create_for_image(this);

      //}


      //m_pgraphicsOwned = pdraw2dgraphics;

      //pdraw2dgraphics->m_pimage = this;

      //auto pgpucontext = pgpudevice->acquire_gpu_context(::gpu::e_output_none, size);

      //::gpu::context_lock contextlock(pgpucontext);

      //pixmap_t pixmap;

      //pixmap.initialize_pixmap(size, (::image32_t*) pimage32, iScan);

      //pgputexture->initialize_gpu_pimage(pgpucontext, size, pixmap);

      m_eflagElement = eflagCreate;

      m_estatus = ::success;

      set_ok_flag();

      //      m_pgputexture->write_pixels(size, pimage32, iScan);

   }


   void image::create_gpu_texture_image(::gpu::texture * pgputexture, ::gpu::graphics * pgpugraphics)
   {



   }


   //void image::initialize_gpu_image(
   //   ::gpu::context * pgpucontext,
   //   const ::i32_size & size,
   //   const ::gpu::texture_data & texturedata)
   //{

   //   if (has_active_destination_graphics_lease())
   //   {

   //      throw ::exception(
   //         error_wrong_state,
   //         "cannot create or resize a GPU image with active destination graphics");

   //   }

   //   if (!pgpucontext || size.is_empty())
   //   {

   //      throw ::exception(error_bad_argument);

   //   }

   //   ::gpu::context_lock contextlock(pgpucontext);

   //   auto pgpurenderer = pgpucontext->get_gpu_renderer();
   //   auto pgputexture = pgpurenderer->create_image_texture(size, false, texturedata);

   //   if (!pgputexture)
   //   {

   //      throw ::exception(error_failed, "Failed to create GPU image texture.");

   //   }

   //   //auto pixmap = texturedata.raw_scoped_pixmap();

   //   m_pgputexture = pgputexture;
   //   m_size = size;
   //   m_sizeRaw = size;
   //   m_point.clear();

   //   //if (texturedata.is)
   //   //m_iScan = pixmap.m_iScan;
   //   //m_pimage32 = pixmap.m_pimage32;
   //   //m_pimage32Raw = pixmap.m_pimage32Raw;
   //   set_ok_flag();

   //}


   void image::destroy()
   {

      ::image::image::destroy();

   }


   ::gpu::texture * image::get_gpu_texture_as_target(::gpu::context * pgpucontext)
   {

      if (m_pdraw2dbitmap.is_null())
      {

         m_pdraw2dbitmap = get_bitmap_as_target();

         if (!m_pdraw2dbitmap)
         {

            return nullptr;

         }

      }

      ::cast<::gpu::bitmap> pgpubitmap = m_pdraw2dbitmap;

      if (pgpubitmap.is_null())
      {

         return nullptr;

      }

      ::cast < ::gpu::graphics > pgpugraphics = m_pgraphicsOwned;

      if (pgpugraphics && pgpugraphics->m_pgpucontextOwned)
      {

         return pgpubitmap->gpu_texture(pgpugraphics->m_pgpucontextOwned);

      }

      return pgpubitmap->gpu_texture(pgpucontext);

   }


   ::gpu::texture * image::get_gpu_texture_as_source(::gpu::context * pgpucontext)
   {

      if (m_pdraw2dbitmap.is_null())
      {

         m_pdraw2dbitmap = get_bitmap_as_source();

         if (!m_pdraw2dbitmap)
         {

            return nullptr;

         }

      }

      ::cast<::gpu::bitmap> pgpubitmap = m_pdraw2dbitmap;

      if (pgpubitmap.is_null())
      {

         return nullptr;

      }

      ::cast < ::gpu::graphics > pgpugraphics = m_pgraphicsOwned;

      if (pgpugraphics && pgpugraphics->m_pgpucontextOwned)
      {

         return pgpubitmap->gpu_texture(pgpugraphics->m_pgpucontextOwned);

      }

      return pgpubitmap->gpu_texture(pgpucontext);

   }


   ::image_pixmap_lease image::_map(::image::enum_map emap, const ::i32_rectangle & rectangle)
   {

      _tidy_map(rectangle);

      // if (has_active_destination_graphics_lease())
      // {
      //
      //    throw ::exception(
      //       error_wrong_state,
      //       "cannot map a GPU image with active destination graphics");
      //
      // }
      //
      // if (m_bMapped)
      // {
      //
      //    return {};
      //
      // }

      auto pthis = this;

      auto size = this->m_size;

      auto sizeRaw = this->m_sizeRaw;

      defer_construct_newø(m_ppixmapOwned);

      pthis->m_ppixmapOwned->m_size = size;

      pthis->m_ppixmapOwned->m_sizeRaw = sizeRaw;

      auto iScanAreaInBytes = pthis->scan_area_in_bytes();

      pthis->m_ppixmapOwned->m_iScan = pthis->m_iScan;

      auto iScanWidth = pthis->m_iScan / 4;

      int iHeightThis = pthis->m_sizeRaw.height();

      pthis->m_ppixmapOwned->m_memoryPixmap.set_size(iHeightThis * pthis->m_ppixmapOwned->m_iScan);

      pthis->m_ppixmapOwned->m_pimage32Raw = (::image32_t *)pthis->m_ppixmapOwned->m_memoryPixmap.data();

      pthis->m_ppixmapOwned->m_pimage32 = pthis->m_ppixmapOwned->m_pimage32Raw;

      if (emap == ::image::e_map_load)
      {

         ::gpu::texture * pgputexture = nullptr;

         ::cast < ::gpu::bitmap > pdraw2dbitmap = m_pdraw2dbitmap;

         if (pdraw2dbitmap)
         {

            pgputexture = pdraw2dbitmap->m_pgputexture;

         }

         if (!pgputexture)
         {

            if (m_size.is_empty() && m_sizeRaw.is_empty())
            {

               throw ::exception(error_wrong_state);

            }

            auto ppixmap = ::transfer(::image::image::_map(emap, rectangle));

            return ::transfer(ppixmap);

         }

         auto pgpucontextlease = pgputexture->acquire_context(m_pgraphicsOwned);

         if (!pgpucontextlease)
         {

            throw ::exception(error_wrong_state);

         }

         auto pthis = const_cast <image *>(this);

         auto pgpucontext = ::as_pointer(pgpucontextlease.m_p);

         auto pgpudevice = pgpucontext->m_pgpudevice;

         auto pgpuqueueGraphics = pgpudevice->graphics_queue();

         //pgpucontext->send(
            //[pthis, pgputexture, pgpucontext, rectangle]()
         {

            auto bPerformanceDiagnostics = pthis->m_papplication
               && pthis->m_papplication->m_gpu.m_bPerformanceDiagnostics.load(
                  ::std::memory_order_relaxed);

            if (bPerformanceDiagnostics)
            {

               auto uPerformanceDiagnosticsGeneration =
                  pthis->m_papplication->m_gpu.m_uPerformanceDiagnosticsGeneration.load(
                     ::std::memory_order_relaxed);

               if (uPerformanceDiagnosticsGeneration !=
                  pthis->m_uPerformanceDiagnosticsGenerationLast.load(
                     ::std::memory_order_relaxed))
               {

                  pthis->reset_performance_diagnostics();

               }

            }

            pgputexture->wait_fence();

            ::gpu::context_lock contextlock(pgpucontext);

            //pthis->pixmap_t::create(
            //   pthis->m_memoryPixmap,
            //   pthis->m_sizeRaw,
            //   pthis->m_sizeRaw.cx * (int)sizeof(::image32_t));

            auto timeStart = ::std::chrono::steady_clock::time_point{};

            if (bPerformanceDiagnostics)
            {

               timeStart = ::std::chrono::steady_clock::now();

            }

            if (emap == ::image::e_map_load)
            {

               //auto pgpucommandbuffer = ::gpu::current_layer()->getCurrentCommandBuffer4();

               auto pgpucommandbuffer = pgpucontext->beginSingleTimeCommands(pgpuqueueGraphics);

               auto ptexturesite = ::gpu::current_layer()->texture(false);

               pgputexture->read_pixels(pgpucommandbuffer, pthis->m_ppixmapOwned, ptexturesite->m_pointOutput);

               pgpucommandbuffer.commit();

               auto uMicroseconds = (::u64)0;

               if (bPerformanceDiagnostics)
               {

                  uMicroseconds = (::u64)::std::chrono::duration_cast<
                     ::std::chrono::microseconds>(
                        ::std::chrono::steady_clock::now() - timeStart).count();

               }

               // if (rectangle.is_empty())
               // {
               //
               //    pthis->m_ppixmapOwned->pixmap_map(pthis->rectangle());
               //
               // }
               // else
               // {
               //
               //    pthis->m_ppixmapOwned->pixmap_map(rectangle);
               //
               // }
               //
               //pthis->m_bMapped = true;

               if (bPerformanceDiagnostics)
               {

                  pthis->record_performance_map_transition(uMicroseconds);

               }

            }


         }
         //);

      }

      return {this, m_ppixmapOwned };

   }


   //
   // bool image::_on_unmap(bool bDoUnmap)
   // {
   //
   //    if (m_interlockedcountMap <= 0)
   //    {
   //
   //       throw ::exception(error_wrong_state);
   //
   //    }
   //
   //    m_interlockedcountMap--;
   //
   //    if (m_interlockedcountMap > 0)
   //    {
   //
   //       return false;
   //
   //    }
   //
   //    if ((!m_bMapped || !m_pimage32Raw) && bDoUnmap)
   //    {
   //
   //       throw ::exception(error_wrong_state);
   //    }
   //
   //    return true;
   //
   // }


   void image::_unmap(::image_pixmap_lease * pimagepixmaplease)
   {

      ::image::image::_unmap(pimagepixmaplease);
      //_tidy_unmap(pimagepixmaplease);
      // if (!_on_unmap(bDoUnmap))
      // {
      //
      //    return;
      //
      // }

      if (m_pdraw2dbitmap)
      {

         ::cast <::gpu::graphics> pgpugraphics = m_pgraphicsOwned;

         ::pointer < ::gpu::context > pgpucontext;

         if (pgpugraphics && pgpugraphics->m_pgpucontextOwned)
         {

            pgpucontext = pgpugraphics->m_pgpucontextOwned;

         }

         auto pgputexture = get_gpu_texture_as_target(pgpucontext);

         if (!pgputexture)
         {

            //throw ::exception(error_wrong_state);
            return;

         }

         auto pgpucontextlease = pgputexture->acquire_context(m_pgraphicsOwned);

         if (!pgpucontextlease)
         {

            throw ::exception(error_wrong_state);

         }

         auto pthis = const_cast <image *>(this);

         pgpucontext = ::as_pointer(pgpucontextlease.m_p);

         //pgpucontext->send(
           // [pthis, pgputexture, pgpucontext]()
         {

            ::gpu::context_lock contextlock(pgpucontext);

            auto bPerformanceDiagnostics = pthis->m_papplication
               && pthis->m_papplication->m_gpu.m_bPerformanceDiagnostics.load(
                  ::std::memory_order_relaxed);

            if (bPerformanceDiagnostics)
            {

               auto uPerformanceDiagnosticsGeneration =
                  pthis->m_papplication->m_gpu.m_uPerformanceDiagnosticsGeneration.load(
                     ::std::memory_order_relaxed);

               if (uPerformanceDiagnosticsGeneration !=
                  pthis->m_uPerformanceDiagnosticsGenerationLast.load(
                     ::std::memory_order_relaxed))
               {

                  pthis->reset_performance_diagnostics();

               }

            }

            auto timeStart = ::std::chrono::steady_clock::time_point{};

            if (bPerformanceDiagnostics)
            {

               timeStart = ::std::chrono::steady_clock::now();

            }

            pgputexture->write_pixels(true, pthis->m_ppixmapOwned, {});

            auto uMicroseconds = (::u64)0;

            if (bPerformanceDiagnostics)
            {

               uMicroseconds = (::u64)::std::chrono::duration_cast<
                  ::std::chrono::microseconds>(
                     ::std::chrono::steady_clock::now() - timeStart).count();

            }

            pgputexture->defer_fence();
            //pthis->m_ppixmapOwned->pixmap_unmap();
            //pthis->m_bMapped = false;

            if (bPerformanceDiagnostics)
            {

               pthis->record_performance_unmap_transition(uMicroseconds);

            }

         }
            //);

      }

   }


   void image::on_load_image(const image32_t * pimage32, const ::i32_size & size, int iScan)
   {

      auto pgputexture = gpu_texture();

      if (pgputexture)
      {

         if (pgputexture->size() != size)
         {

            auto pgpucontextlease = pgputexture->acquire_context(m_pgraphicsOwned);

            ::cast<::gpu::bitmap> pgpubitmap = get_bitmap_as_source();

            construct_newø(m_ppixmapOwned);

            m_ppixmapOwned->create_as_descriptor(size);

            m_ppixmapOwned->m_memoryPixmap.set_size(iScan * size.height());

            m_ppixmapOwned->copy(size, pimage32, iScan);

            pgpubitmap->initialize_gpu_bitmap(pgpucontextlease, size, *m_ppixmapOwned);

            return;

         }

         if (!pgputexture)
         {

            throw ::exception(error_wrong_state);

         }

         auto pgpucontextlease = pgputexture->acquire_context(m_pgraphicsOwned);

         if (!pgpucontextlease)
         {

            throw ::exception(error_wrong_state);

         }

         auto pthis = const_cast<image *>(this);

         auto pgpucontext = ::as_pointer(pgpucontextlease.m_p);

         pgpucontext->send(
            [pthis, pgputexture, pimage32, size, iScan, pgpucontext]()
            {

               auto bPerformanceDiagnostics =
                  pthis->m_papplication &&
                  pthis->m_papplication->m_gpu.m_bPerformanceDiagnostics.load(::std::memory_order_relaxed);

               if (bPerformanceDiagnostics)
               {

                  auto uPerformanceDiagnosticsGeneration =
                     pthis->m_papplication->m_gpu.m_uPerformanceDiagnosticsGeneration.load(::std::memory_order_relaxed);

                  if (uPerformanceDiagnosticsGeneration !=
                      pthis->m_uPerformanceDiagnosticsGenerationLast.load(::std::memory_order_relaxed))
                  {

                     pthis->reset_performance_diagnostics();

                  }

               }

               auto timeStart = ::std::chrono::steady_clock::time_point{};

               if (bPerformanceDiagnostics)
               {

                  timeStart = ::std::chrono::steady_clock::now();

               }

               ::gpu::context_lock contextlock(pgpucontext);

               pgputexture->write_pixels(true, size, pimage32, iScan);

               auto uMicroseconds = (::u64)0;

               if (bPerformanceDiagnostics)
               {

                  uMicroseconds = (::u64)::std::chrono::duration_cast<::std::chrono::microseconds>(
                                     ::std::chrono::steady_clock::now() - timeStart)
                                     .count();
               }

               pgputexture->defer_fence();
               // pthis->pixmap::unmap();
               // pthis->m_bMapped = false;

               if (bPerformanceDiagnostics)
               {

                  pthis->record_performance_unmap_transition(uMicroseconds);

               }

            });

      }
      else
      {

         create_as_descriptor(size, e_flag_success, iScan);

         auto ppixmapThis = this->map();

         ppixmapThis->copy(size, pimage32, iScan);

         //m_sizeRaw = size;
         //
         //m_size = size;
         //
         //m_iScan = size.cx * 4;

         //int iScanArea = scan_area_in_bytes();

         //m_memoryPixmap.set_size(iScanArea);

         //m_pimage32Raw = (::image32_t *)m_memoryPixmap.data();

         //m_pimage32Raw->copy(size, m_iScan, pimage32, iScan);

         //::string str = _001_image32_diagnostics(size, m_pimage32Raw, m_iScan);

         //::information("pixmap::on_load_image {}", str);

         //m_pimage32 = m_pimage32Raw;

         //m_bMapped = true;

      }

      m_estatus = success;

      set_ok_flag();

   }


   void image::reset_performance_diagnostics() const
   {

      auto bEnabled = m_papplication
         && m_papplication->m_gpu.m_bPerformanceDiagnostics.load(
            ::std::memory_order_relaxed);
      auto iIntervalMilliseconds = m_papplication
         ? m_papplication->m_gpu.m_iPerformanceDiagnosticsIntervalMilliseconds.load(
            ::std::memory_order_relaxed)
         : 1'000;

      iIntervalMilliseconds = maximum(
         100,
         minimum(60'000, iIntervalMilliseconds));

      m_uPerformanceDetailTransitions.store(0, ::std::memory_order_relaxed);
      m_uPerformanceMapTransitions.store(0, ::std::memory_order_relaxed);
      m_uPerformanceUnmapTransitions.store(0, ::std::memory_order_relaxed);
      m_uPerformanceBytesRead.store(0, ::std::memory_order_relaxed);
      m_uPerformanceBytesWritten.store(0, ::std::memory_order_relaxed);
      m_uPerformanceReadMicroseconds.store(0, ::std::memory_order_relaxed);
      m_uPerformanceWriteMicroseconds.store(0, ::std::memory_order_relaxed);
      m_iPerformanceNextReportNanoseconds.store(
         steady_nanoseconds() + (::i64)iIntervalMilliseconds * 1'000'000,
         ::std::memory_order_relaxed);
      m_bPerformanceDiagnosticsEnabledLast.store(
         bEnabled,
         ::std::memory_order_relaxed);
      m_uPerformanceDiagnosticsGenerationLast.store(
         m_papplication
            ? m_papplication->m_gpu.m_uPerformanceDiagnosticsGeneration.load(
               ::std::memory_order_relaxed)
            : 0,
         ::std::memory_order_relaxed);

   }


   void image::record_performance_map_transition(::u64 uMicroseconds) const
   {

      auto uGeneration = m_uPerformanceMapGeneration.fetch_add(
         1,
         ::std::memory_order_relaxed) + 1;

      auto uBytes = (::u64)m_sizeRaw.area() * sizeof(::image32_t);

      m_uPerformanceMapTransitions.fetch_add(1, ::std::memory_order_relaxed);

      m_uPerformanceBytesRead.fetch_add(uBytes, ::std::memory_order_relaxed);

      m_uPerformanceReadMicroseconds.fetch_add(
         uMicroseconds,
         ::std::memory_order_relaxed);

      auto uDetail = m_uPerformanceDetailTransitions.fetch_add(
         1,
         ::std::memory_order_relaxed);

      if (uDetail < 64)
      {

         auto uSequence = s_uMapTransitionSequence.fetch_add(
            1,
            ::std::memory_order_relaxed) + 1;

         auto pgputexture = gpu_texture();

         information() << "[gpu.performance.image_mapping] transition=map"
            << " sequence=" << uSequence
            << " generation=" << uGeneration
            << " image=" << (const void *)this
            << " texture=" << (const void *)pgputexture
            << " size=" << m_sizeRaw
            << " task=" << ::current_task_name();

      }

      report_performance_diagnostics_if_due();

   }


   void image::record_performance_unmap_transition(::u64 uMicroseconds) const
   {

      auto uBytes = (::u64)m_sizeRaw.area() * sizeof(::image32_t);

      m_uPerformanceUnmapTransitions.fetch_add(1, ::std::memory_order_relaxed);

      m_uPerformanceBytesWritten.fetch_add(uBytes, ::std::memory_order_relaxed);

      m_uPerformanceWriteMicroseconds.fetch_add(
         uMicroseconds,
         ::std::memory_order_relaxed);

      auto uDetail = m_uPerformanceDetailTransitions.fetch_add(
         1,
         ::std::memory_order_relaxed);

      if (uDetail < 64)
      {

         auto uSequence = s_uMapTransitionSequence.fetch_add(
            1,
            ::std::memory_order_relaxed) + 1;

         auto pgputexture = gpu_texture();

         information() << "[gpu.performance.image_mapping] transition=unmap"
            << " sequence=" << uSequence
            << " generation=" << m_uPerformanceMapGeneration.load(
               ::std::memory_order_relaxed)
            << " image=" << (const void *)this
            << " texture=" << (const void *) pgputexture
            << " size=" << m_sizeRaw
            << " task=" << ::current_task_name();

      }

      report_performance_diagnostics_if_due();

   }


   void image::report_performance_diagnostics_if_due() const
   {

      if (!m_papplication
         || !m_papplication->m_gpu.m_bPerformanceDiagnostics.load(
            ::std::memory_order_relaxed))
      {

         return;

      }

      auto iNowNanoseconds = steady_nanoseconds();
      auto iDeadlineNanoseconds = m_iPerformanceNextReportNanoseconds.load(
         ::std::memory_order_relaxed);

      if (iNowNanoseconds < iDeadlineNanoseconds)
      {

         return;

      }

      auto iIntervalMilliseconds = maximum(
         100,
         minimum(
            60'000,
            m_papplication->m_gpu.m_iPerformanceDiagnosticsIntervalMilliseconds.load(
               ::std::memory_order_relaxed)));
      auto iNextNanoseconds = iNowNanoseconds
         + (::i64)iIntervalMilliseconds * 1'000'000;

      if (!m_iPerformanceNextReportNanoseconds.compare_exchange_strong(
         iDeadlineNanoseconds,
         iNextNanoseconds,
         ::std::memory_order_relaxed))
      {

         return;

      }

      auto uMaps = m_uPerformanceMapTransitions.exchange(
         0,
         ::std::memory_order_relaxed);
      auto uUnmaps = m_uPerformanceUnmapTransitions.exchange(
         0,
         ::std::memory_order_relaxed);
      auto uBytesRead = m_uPerformanceBytesRead.exchange(
         0,
         ::std::memory_order_relaxed);
      auto uBytesWritten = m_uPerformanceBytesWritten.exchange(
         0,
         ::std::memory_order_relaxed);
      auto uReadMicroseconds = m_uPerformanceReadMicroseconds.exchange(
         0,
         ::std::memory_order_relaxed);
      auto uWriteMicroseconds = m_uPerformanceWriteMicroseconds.exchange(
         0,
         ::std::memory_order_relaxed);

      information() << "[gpu.performance.image_mapping] maps=" << uMaps
         << " unmaps=" << uUnmaps
         << " bytes_read=" << uBytesRead
         << " bytes_written=" << uBytesWritten
         << " read_us=" << uReadMicroseconds
         << " write_us=" << uWriteMicroseconds;

   }


} // namespace gpu
