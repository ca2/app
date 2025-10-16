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

      bool m_bSrgb = false;

      int                                 m_iAtlasX;
      int                                 m_iAtlasY;
      int                                 m_iAtlasCurrentRowHeight;
      enum_type                           m_etype;
      bool                                m_bWithDepth;
      bool                                m_bClearColor;
      ::color::color                      m_colorClear;
      bool                                m_bRenderTarget;
      ::pointer < ::gpu::renderer >       m_pgpurenderer;
      int                                 m_iLayerCount;
      ::collection::index                 m_iIndex;
      //::pointer < ::gpu::render_target >  m_pgpurendertarget;
      ::int_rectangle                     m_rectangleTarget;
      int                                 m_mipsLevel;
      ::int_size                          m_sizeMip;
      bool                                m_bTransferDst;
      bool                                m_bTransferSrc;
      bool                                m_bCpuRead;
      ::pointer < texture >               m_ptextureDepth;

      ::string                            m_strTextureType;
      //::string                            m_strUniform;

      ::file::path                        m_path;

      texture();
      ~texture() override;


      virtual ::int_size size();
      virtual int width();
      virtual int height();


      void defer_throw_if_cube_map_images_are_not_ok(const ::pointer_array < ::image::image >& imagea);
      
      virtual void initialize_hdr_texture_on_memory(::gpu::renderer *prenderer, const ::block & block);
      virtual void initialize_image_texture(::gpu::renderer* pgpurenderer, const ::int_rectangle& rectangleTarget, bool bWithDepth, const ::pointer_array < ::image::image >& imagea = {}, enum_type etype = e_type_image);
      virtual void initialize_depth_texture(::gpu::renderer* pgpurenderer, const ::int_rectangle& rectangleTarget);

      virtual void initialize_image_texture(::gpu::renderer* pgpurenderer, const ::file::path & path, bool bIsSrgb);
      virtual void initialize_image_texture(::gpu::renderer* pgpurenderer, const ::pointer_array < ::image::image >& imagea, enum_type etype = e_type_image);

      virtual ::pointer < ::gpu::pixmap > create_gpu_pixmap(const ::int_size & size);

      virtual void merge_layers(::pointer_array < ::gpu::layer >* playera);
      virtual void blend(::gpu::layer * player);
      virtual void blend(::gpu::texture * ptexture);

      virtual void create_render_target();

      virtual void create_depth_resources();

      virtual void bind_render_target();

      virtual texture* get_depth_texture();

      virtual ::string texture_type();
      virtual void set_pixels(const ::int_rectangle& rectangle, const void* data);

      virtual bool is_in_shader_sampling_state();

   };


} // namespace gpu



