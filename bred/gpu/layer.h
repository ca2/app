// Created by camilo on 2025-06-12 20:58 <3ThomasBorregaardSørensen!!
#pragma once
#include "acme/parallelization/manual_reset_happening.h"


namespace gpu
{


   class CLASS_DECL_BRED layer :
      virtual public ::particle
   {
   public:

      ::i32 m_iFrameIndex = -1;
      ::i32 m_iLayerIndex = -1;
      bool m_bFirstLayer;
      bool m_bClosingLayer;
      ::pointer < ::gpu::renderer >        m_pgpurenderer;
      bool m_bRenderTargetFramebufferInitialized;
      //::pointer < renderer >        m_pgpurendererTarget;
      //::i32_rectangle m_rectangleTarget;
      ::pointer_array <::gpu::texture >    m_texturea;
      ::pointer_array <::gpu::texture >    m_textureaSource;
      //::pointer < ::gpu::frame > m_pgpulayer;
      ::pointer < ::gpu::fence > m_pgpufence;
      ::pointer < ::gpu::semaphore > m_pgpusemaphoreSignal;
      //::comptr < ID3D12Resource > m_presource;
      ///bool m_bFinished;
      ::pointer < ::manual_reset_happening > m_pmanualresethappeningFinished;

      ::pointer_array<command_buffer>	 m_commandbufferaLayer;
      ::pointer<::gpu::command_buffer> m_pcommandbufferScoped;
      class ::time m_timeStart;
      class ::time m_timeEnd;
      class ::time m_timeDuration;


      layer();
      ~layer() override;


      virtual ::manual_reset_happening * finished_manual_reset_happening();

      
      virtual ::gpu::command_buffer* getCurrentCommandBuffer4();


      virtual void initialize_gpu_layer(::gpu::renderer * pgpurenderer, ::i32 iFrameIndex, ::i32 iLayerIndex);


      virtual void create_command_buffers();

      //virtual void set_target_texture(texture* ptextureTarget);

      virtual void layer_start();
      virtual void layer_end();
      virtual void layer_on_after_submit();


      ::pointer < ::gpu::texture > & texture();
      ::pointer < ::gpu::texture > & source_texture();
      ::gpu::renderer * renderer();


   };
   

   CLASS_DECL_BRED void set_current_layer(::gpu::layer *pgpulayer);
   CLASS_DECL_BRED ::gpu::layer *current_layer();


} // namespace gpu



