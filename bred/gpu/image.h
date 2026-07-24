#pragma once


#include "aura/graphics/image/image.h"


#include <atomic>
#include <chrono>


namespace gpu
{


   class context;
   class texture;
   struct texture_data;


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


      //::draw2d::graphics_pointer owned_graphics() const override;

      virtual ::gpu::texture * gpu_texture() const;
      virtual void create_gpu_texture();
      virtual void initialize_gpu_image(
         ::gpu::context * pgpucontext,
         const ::i32_size & size,
         const ::gpu::texture_data & texturedata);

      void destroy() override;

      virtual ::gpu::texture *get_gpu_texture();

      void on_load_image(const image32_t *pimage32, const ::i32_size &size, int iScan) override;

      void reset_performance_diagnostics() const;
      void record_performance_map_transition(::u64 uMicroseconds) const;
      void record_performance_unmap_transition(::u64 uMicroseconds) const;
      void report_performance_diagnostics_if_due() const;


   protected:

      void _map(bool bApplyAlphaTransform = true) override;
      void _unmap(bool bDoUnmap = false) override;


   };


} // namespace gpu
