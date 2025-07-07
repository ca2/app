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
      ::pointer < renderer >        m_pgpurenderer;
      //::pointer < renderer >        m_pgpurendererTarget;
      //::int_rectangle m_rectangleTarget;
      ::pointer_array <texture >    m_texturea;
      ::pointer_array <texture >    m_textureaSource;
      ::pointer < ::gpu::frame > m_pgpuframe;
      //::comptr < ID3D12Resource > m_presource;

      ::pointer < command_buffer >  m_pcommandbufferLayer;

      layer();
      ~layer() override;


      virtual void initialize_gpu_layer(renderer * pgpurenderer, int iFrameIndex, int iLayerIndex);


      //virtual void set_target_texture(texture* ptextureTarget);

      virtual void layer_start();
      virtual void layer_end();


      ::pointer < class texture > & texture();
      ::pointer < class texture > & source_texture();
      renderer * renderer();


   };
   

} // namespace gpu



