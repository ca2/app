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
         e_type_cube_map = 4,

      };


      enum_type                           m_etype;
      bool                                m_bWithDepth;
      bool                                m_bClearColor;
      ::color::color                      m_colorClear;
      bool                                m_bRenderTarget;
      ::pointer < ::gpu::renderer >       m_pgpurenderer;
      //::pointer < ::gpu::render_target >  m_pgpurendertarget;
      ::int_rectangle                     m_rectangleTarget;
      bool                                m_bTransferDst;
      bool                                m_bTransferSrc;
      bool                                m_bCpuRead;
      ::pointer < texture >               m_ptextureDepth;

      ::string                            m_strTextureType;
      ::string                            m_strUniform;

      ::file::path                        m_path;

      texture();
      ~texture() override;


      virtual ::int_size size();
      virtual int width();
      virtual int height();

      
      virtual void initialize_image_texture(::gpu::renderer* pgpurenderer, const ::int_rectangle& rectangleTarget, bool bWithDepth, ::pixmap * ppixmap = nullptr, enum_type etype = e_type_image);
      virtual void initialize_depth_texture(::gpu::renderer* pgpurenderer, const ::int_rectangle& rectangleTarget);

      virtual void initialize_image_texture(::gpu::renderer* pgpurenderer, const ::file::path & path);
      virtual void initialize_image_texture(::gpu::renderer* pgpurenderer, ::image::image * pimage, enum_type etype = e_type_image);


      virtual void merge_layers(::pointer_array < ::gpu::layer >* playera);
      virtual void blend(::gpu::layer * player);
      virtual void blend(::gpu::texture * ptexture);

      virtual void create_render_target();

      virtual void create_depth_resources();

      virtual void bind_render_target();

      virtual texture* get_depth_texture();

      virtual ::string texture_type();


   };


} // namespace gpu



