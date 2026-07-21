#pragma once


#include "aura/graphics/image/image.h"


#include <atomic>
#include <chrono>


namespace gpu
{


   class context;
   class texture;


   class CLASS_DECL_BRED image :
      virtual public ::image::image
   {
   public:


      ::pointer < ::gpu::texture > m_pgputexture;
      mutable ::std::atomic_bool m_bPerformanceDiagnosticsEnabledLast{false};
      mutable ::std::atomic<::u64> m_uPerformanceDiagnosticsGenerationLast{0};
      mutable ::std::atomic<::u64> m_uPerformanceMapGeneration{0};
      mutable ::std::atomic<::u64> m_uPerformanceDetailTransitions{0};
      mutable ::std::atomic<::u64> m_uPerformanceMapTransitions{0};
      mutable ::std::atomic<::u64> m_uPerformanceUnmapTransitions{0};
      mutable ::std::atomic<::u64> m_uPerformanceBytesRead{0};
      mutable ::std::atomic<::u64> m_uPerformanceBytesWritten{0};
      mutable ::std::atomic<::u64> m_uPerformanceReadMicroseconds{0};
      mutable ::std::atomic<::u64> m_uPerformanceWriteMicroseconds{0};
      mutable ::std::atomic<::i64> m_iPerformanceNextReportNanoseconds{0};


      image();
      ~image() override;


      ::draw2d::graphics * get_graphics() const override;

      virtual ::gpu::texture * gpu_texture() const;
      virtual void initialize_gpu_image(
         ::gpu::context * pgpucontext,
         const ::i32_size & size);

      void destroy() override;

      void map(bool bApplyAlphaTransform = true) const override;
      void unmap() const override;

      virtual ::gpu::texture *get_gpu_texture();

      void on_load_image(const image32_t *pimage32, const ::i32_size &size, int iScan) override;

      void reset_performance_diagnostics() const;
      void record_performance_map_transition(::u64 uMicroseconds) const;
      void record_performance_unmap_transition(::u64 uMicroseconds) const;
      void report_performance_diagnostics_if_due() const;


   };


} // namespace gpu
