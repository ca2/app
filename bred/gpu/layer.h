// Created by camilo on 2025-06-12 20:58 <3ThomasBorregaardSørensen!!
#pragma once
#include "acme/parallelization/manual_reset_happening.h"
#include <mutex>


namespace gpu
{


   class CLASS_DECL_BRED layer :
      virtual public ::particle
   {
   public:


      enum_gpu_layer_state m_egpulayerstate = e_gpu_layer_state_initial;
      enum_start_layer m_estartlayer = e_start_layer_none;
      ::i32 m_iGpuLayerFrameIndex = -1;
      //::i32 m_iFrameIndexReady = -1;
      ::i32 m_iGpuLayerIndex = -1;
      bool m_bFirstLayer;
      bool m_bClosingLayer;
      bool m_bIncludeInFrameComposition = true;
      bool m_bExternalRendering = false;
      ::pointer < ::gpu::renderer >        m_pgpurenderer;
      bool m_bRenderTargetFramebufferInitialized;
      //::pointer < renderer >        m_pgpurendererTarget;
      //::i32_rectangle m_rectangleTarget;
      ::pointer_array <::gpu::texture_site >    m_texturesitea;
      //::pointer_array <::gpu::texture_site >    m_texturesiteaSource;
      //::pointer < ::gpu::texture >         m_ptextureDrawing;
      //::pointer < ::gpu::texture >         m_ptextureReady;
      std::mutex                           m_mutexTextureSnapshot;
      //::pointer < ::gpu::frame > m_pgpulayer;
      ::pointer < ::gpu::fence > m_pgpufence;
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


      virtual void initialize_layer_state();

      virtual void start_layer_render();

      virtual void end_layer_render();



      virtual ::manual_reset_happening * finished_manual_reset_happening();

      
      virtual ::gpu::command_buffer* getCurrentCommandBuffer4();


      virtual void initialize_gpu_layer(::gpu::renderer * pgpurenderer, ::i32 iFrameIndex, ::i32 iLayerIndex);


      virtual void create_command_buffers();

      //virtual void set_target_texture(texture* ptextureTarget);

      virtual void layer_start();
      virtual void layer_end();
      virtual void layer_on_after_submit();


      ::pointer < ::gpu::texture_site > & texture(bool bRenderTarget);

      //::pointer < ::gpu::texture_site > & target_texture(bool bRenderTarget);
      //::pointer < ::gpu::texture > composition_texture();
      //::pointer < ::gpu::texture_site > & source_texture();
      ::gpu::renderer * renderer();


   };
   

   CLASS_DECL_BRED void set_current_layer(::gpu::layer *pgpulayer);
   CLASS_DECL_BRED ::gpu::layer *current_layer();


} // namespace gpu



