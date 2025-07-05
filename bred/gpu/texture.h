// Created by camilo on 2025-06-12 21:04 <3ThomasBorregaardSørensen!!
#pragma once


namespace gpu
{


   class CLASS_DECL_BRED texture :
      virtual public ::particle 
   {
   public:

      
      enum enum_type
      {

         e_type_none,
         e_type_image = 1,
         e_type_depth = 2,
         e_type_depth_stencil = 3,

      };


      enum_type                           m_etype;
      bool                                m_bWithDepth;
      bool                                m_bClearColor;
      ::color::color                      m_colorClear;
      bool                                m_bRenderTarget;
      ::pointer < ::gpu::renderer >       m_pgpurenderer;
      ::int_rectangle                     m_rectangleTarget;
      bool                                m_bTransferDst;
      bool                                m_bCpuRead;


      texture();
      ~texture() override;


      virtual ::int_size size();

      
      virtual void initialize_image_texture(::gpu::renderer* pgpurenderer, const ::int_rectangle& rectangleTarget, bool bWithDepth);
      virtual void initialize_depth_texture(::gpu::renderer* pgpurenderer, const ::int_rectangle& rectangleTarget);


      virtual void merge_layers(::pointer_array < ::gpu::layer >* playera);
      virtual void blend(::gpu::layer * player);
      virtual void blend(::gpu::texture * ptexture);

      virtual void create_render_target();

      virtual void create_depth_resources();

      virtual void bind_render_target();


   };


} // namespace gpu



