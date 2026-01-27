// Created by camilo on 2025-06-12 20:58 <3ThomasBorregaardSørensen!!
#pragma once


namespace gpu
{


   class CLASS_DECL_BRED layer :
      virtual public ::particle
   {
   public:

      int m_iFrameIndex = -1;
      int m_iLayerIndex = -1;
      ::pointer < ::gpu::renderer >        m_pgpurenderer;
      bool m_bRenderTargetFramebufferInitialized;
      //::pointer < renderer >        m_pgpurendererTarget;
      //::int_rectangle m_rectangleTarget;
      ::pointer_array <::gpu::texture >    m_texturea;
      ::pointer_array <::gpu::texture >    m_textureaSource;
      ::pointer < ::gpu::frame > m_pgpuframe;
      ::pointer < ::gpu::fence > m_pgpufence;
      //::comptr < ID3D12Resource > m_presource;
      bool m_bFinished;

      ::pointer_array<command_buffer>	 m_commandbufferaLayer;


      layer();
      ~layer() override;

      
      virtual ::gpu::command_buffer* getCurrentCommandBuffer4();


      virtual void initialize_gpu_layer(::gpu::renderer * pgpurenderer, int iFrameIndex, int iLayerIndex);


      virtual void create_command_buffers();

      //virtual void set_target_texture(texture* ptextureTarget);

      virtual void layer_start();
      virtual void layer_end();


      ::pointer < ::gpu::texture > & texture();
      ::pointer < ::gpu::texture > & source_texture();
      ::gpu::renderer * renderer();


   };
   

} // namespace gpu



