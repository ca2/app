// Created by camilo on 2025-06-12 21:04 <3ThomasBorregaardSørensen!!
#pragma once


namespace gpu
{


   class CLASS_DECL_BRED texture :
      virtual public ::particle 
   {
   public:


      bool                                m_bClearColor;            
      ::color::color                      m_colorClear;
      bool                                m_bRenderTarget;
      bool                                m_bDepthStencil;
      ::pointer < ::gpu::renderer >       m_pgpurenderer;
      ::int_rectangle                     m_rectangleTarget;
      bool                                m_bTransferDst;
      bool                                m_bCpuRead;


      texture();
      ~texture() override;


      virtual ::int_size size();

      
      virtual void initialize_gpu_texture(::gpu::renderer * pgpurenderer, const ::int_rectangle & rectangleTarget);

      virtual void merge_layers(::pointer_array < ::gpu::layer >* playera);
      virtual void blend(::gpu::layer * player);
      virtual void blend(::gpu::texture * ptexture);

   };


} // namespace gpu



