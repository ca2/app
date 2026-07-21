#include "framework.h"
#include "image.h"
#include "context.h"
#include "context_lock.h"
#include "renderer.h"
#include "texture.h"
#include "apex/gpu/approach.h"
#include "bred/gpu/device.h"
#include "acme/platform/application.h"


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


   ::draw2d::graphics * image::get_graphics() const
   {

      unmap();

      return _get_graphics();

   }


   ::gpu::texture * image::gpu_texture() const
   {

      return m_pgputexture;

   }


   void image::initialize_gpu_image(
      ::gpu::context * pgpucontext,
      const ::i32_size & size)
   {

      if (has_active_destination_graphics_lease())
      {

         throw ::exception(
            error_wrong_state,
            "cannot create or resize a GPU image with active destination graphics");

      }

      if (!pgpucontext || size.is_empty())
      {

         throw ::exception(error_bad_argument);

      }

      ::gpu::context_lock contextlock(pgpucontext);

      auto pgpurenderer = pgpucontext->get_gpu_renderer();
      auto pgputexture = pgpurenderer->create_image_texture(size, false);

      if (!pgputexture)
      {

         throw ::exception(error_failed, "Failed to create GPU image texture.");

      }

      m_pgputexture = pgputexture;
      m_size = size;
      m_sizeRaw = size;
      m_point.clear();
      m_iScan = 0;
      m_pimage32 = nullptr;
      m_pimage32Raw = nullptr;
      set_ok_flag();

   }


   void image::destroy()
   {

      ::image::image::destroy();
      m_pgputexture.release();

   }


   void image::map(bool) const
   {

      if (has_active_destination_graphics_lease())
      {

         throw ::exception(
            error_wrong_state,
            "cannot map a GPU image with active destination graphics");

      }

      if (m_bMapped)
      {

         return;

      }

      auto pgputexture = m_pgputexture;

      if (!pgputexture || m_sizeRaw.is_empty())
      {

         throw ::exception(error_wrong_state);

      }

      auto pgpucontext = pgputexture->context();

      if (!pgpucontext)
      {

         throw ::exception(error_wrong_state);

      }

      auto pthis = const_cast < image * >(this);

      pgpucontext->send(
         [pthis, pgputexture, pgpucontext]()
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

            pthis->pixmap_t::create(
               pthis->m_memoryPixmap,
               pthis->m_sizeRaw,
               pthis->m_sizeRaw.cx * (int)sizeof(::image32_t));

            auto timeStart = ::std::chrono::steady_clock::time_point{};

            if (bPerformanceDiagnostics)
            {

               timeStart = ::std::chrono::steady_clock::now();

            }

            pgputexture->read_pixels(pthis);

            auto uMicroseconds = (::u64)0;

            if (bPerformanceDiagnostics)
            {

               uMicroseconds = (::u64)::std::chrono::duration_cast<
                  ::std::chrono::microseconds>(
                     ::std::chrono::steady_clock::now() - timeStart).count();

            }

            pthis->pixmap_t::map(pthis->rectangle());
            pthis->m_bMapped = true;

            if (bPerformanceDiagnostics)
            {

               pthis->record_performance_map_transition(uMicroseconds);

            }

         });

   }


   ::gpu::texture * image::get_gpu_texture()
   {

      if (!m_pgputexture)
      {

         auto pgpucontextMain = m_papplication->get_gpu_approach()->get_gpu_device(m_papplication->m_pacmeuserinteractionMain->m_pacmewindowingwindow)
                                   ->main_context();

         initialize_gpu_image(pgpucontextMain, m_size);

      }

      return m_pgputexture;
   }


   void image::unmap() const
   {

      if (!m_bMapped)
      {

         return;

      }

      auto pgputexture = m_pgputexture;

      if (!pgputexture)
      {

         throw ::exception(error_wrong_state);

      }

      auto pgpucontext = pgputexture->context();

      if (!pgpucontext)
      {

         throw ::exception(error_wrong_state);

      }

      auto pthis = const_cast < image * >(this);

      pgpucontext->send(
         [pthis, pgputexture]()
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

            auto timeStart = ::std::chrono::steady_clock::time_point{};

            if (bPerformanceDiagnostics)
            {

               timeStart = ::std::chrono::steady_clock::now();

            }

            pgputexture->write_pixels(pthis);

            auto uMicroseconds = (::u64)0;

            if (bPerformanceDiagnostics)
            {

               uMicroseconds = (::u64)::std::chrono::duration_cast<
                  ::std::chrono::microseconds>(
                     ::std::chrono::steady_clock::now() - timeStart).count();

            }

            pgputexture->defer_fence();
            pthis->pixmap::unmap();
            pthis->m_bMapped = false;

            if (bPerformanceDiagnostics)
            {

               pthis->record_performance_unmap_transition(uMicroseconds);

            }

         });

   }


   void image::on_load_image(const image32_t * pimage32, const ::i32_size & size, int iScan)
   {

      if (m_bMapped)
      {

         if (size == this->size())
         {

            copy(size, pimage32, iScan);

         }
         else
         {

            unmap();

         }

      }

      if (m_pgputexture)
      {

         if (m_pgputexture->size() != size)
         {

            auto pgpucontextWork =
               m_papplication->get_gpu_approach()
                  ->get_gpu_device(m_papplication->m_pacmeuserinteractionMain->m_pacmewindowingwindow)
                  ->work_context();

            initialize_gpu_image(pgpucontextWork, size);

         }

               auto pgputexture = m_pgputexture;

         if (!pgputexture)
         {

            throw ::exception(error_wrong_state);
         }

         auto pgpucontext = pgputexture->context();

         if (!pgpucontext)
         {

            throw ::exception(error_wrong_state);
         }

         auto pthis = const_cast<image *>(this);

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

               pgputexture->write_pixels(size, pimage32, iScan);

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
      else if (!m_bMapped)
      {

         pixmap_t::initialize_pixmap(size, nullptr, iScan);

         pixmap::map();
         
         pixmap_t::copy(size, pimage32, iScan);

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

         information() << "[gpu.performance.image_mapping] transition=map"
            << " sequence=" << uSequence
            << " generation=" << uGeneration
            << " image=" << (const void *)this
            << " texture=" << (const void *)m_pgputexture.m_p
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

         information() << "[gpu.performance.image_mapping] transition=unmap"
            << " sequence=" << uSequence
            << " generation=" << m_uPerformanceMapGeneration.load(
               ::std::memory_order_relaxed)
            << " image=" << (const void *)this
            << " texture=" << (const void *)m_pgputexture.m_p
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
