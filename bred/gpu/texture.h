// Created by camilo on 2025-06-12 21:04 <3ThomasBorregaardSørensen!!
#pragma once


#include "bred/gpu/texture_attributes.h"
#include "bred/gpu/texture_flags.h"
#include "bred/gpu/texture_data.h"


namespace gpu
{


   class CLASS_DECL_BRED texture :
      virtual public ::particle 
   {
   public:



      texture_attributes                  m_textureattributes;
      texture_flags                       m_textureflags;
      enum_texture_state                  m_etexturestate;
      int                                 m_iAtlasX;
      int                                 m_iAtlasY;
      int                                 m_iAtlasCurrentRowHeight;
      bool                                m_bClearColor;
      ::color::color                      m_colorClear;
      ::pointer < ::gpu::renderer >       m_pgpurenderer;
      ::collection::index                 m_iIndex;
      int                                 m_iCurrentMip;
      int                                 m_iCurrentFace;
      bool m_bHdr = false;

      //::pointer < ::gpu::render_target >  m_pgpurendertarget;
      ::int_size                          m_sizeMip;
      //bool                                m_bTransferDst;
      //bool                                m_bTransferSrc;
      //bool                                m_bCpuRead;
      ::pointer < texture >               m_ptextureDepth;
      //bool                                m_bShaderResourceView;
      ::string                            m_strTextureType;
      //::string                            m_strUniform;
      //bool m_bRedGreen;
      //bool m_bFloat;
      ::file::path                        m_path;

      texture();
      ~texture() override;


      virtual void _create_texture(const texture_data & texturedata = {});
      virtual void _set_data(const texture_data &texturedata = {});

      virtual ::int_rectangle rectangle() const;
      virtual ::int_size size() const;
      virtual int width() const;
      virtual int height() const;

      virtual int mip_count() const;
      virtual int max_mip_count() const;
      virtual int mip_width_for_mip(int baseWidth, int iMip) const;
      virtual int mip_height_for_mip(int baseHeight, int iMip) const;
      virtual int mip_width() const;
      virtual int mip_height() const;
      virtual int render_target_view_index(int iFace, int iMip) const;
      virtual int current_render_target_view_index() const;


      virtual int layer_count() const;


      virtual void set_state(::gpu::command_buffer *pgpucommandbuffer, ::gpu::enum_texture_state etexturestate);



      void defer_throw_if_cube_map_images_are_not_ok(const ::pointer_array < ::image::image >& imagea);
      
      virtual void initialize_hdr_texture_on_memory(::gpu::renderer *prenderer, const ::block & block);
      virtual void initialize_with_image_data(
         ::gpu::renderer *pgpurenderer, 
         const ::int_rectangle &rectangleTarget,
         int numChannels,
         bool bSrgb,
         const void * pdata,
         enum_texture etexture = e_texture_image);
      virtual void initialize_texture(::gpu::renderer* pgpurenderer,
         const texture_attributes & textureattributes,
         const texture_flags & textureflags = {},
         const texture_data & texturedata = {});
      virtual void initialize_mipmap_cubemap_texture(::gpu::renderer *pgpurenderer, const ::int_rectangle& rectangleTarget, int iMipCount = -1, bool bRenderTarget = true, bool bShaderResourceView = true);
      virtual void initialize_depth_texture(::gpu::renderer* pgpurenderer, const ::int_rectangle& rectangleTarget);

      virtual void initialize_texture_from_file_path(::gpu::renderer* pgpurenderer, const ::file::path & path, bool bIsSrgb);
      virtual void initialize_texture_from_image(::gpu::renderer* pgpurenderer, const ::pointer_array < ::image::image > & imagea, enum_texture etexture = e_texture_image);

      virtual ::pointer < ::gpu::pixmap > create_gpu_pixmap(const ::int_size & size);

      //virtual void merge_layers(::pointer_array < ::gpu::layer >* playera);
      //virtual void blend(::gpu::layer * player);
      //virtual void blend(::gpu::texture * ptexture);

      virtual void create_render_target();

      virtual void create_shader_resource_view();

      virtual void create_depth_resources();

      virtual void bind_render_target();

      virtual texture* get_depth_texture();

      virtual ::string texture_type();
      virtual void set_pixels(const ::int_rectangle& rectangle, const void* data);

      virtual bool is_in_shader_sampling_state();

      //virtual void set_cube_face(int iFace, ::gpu::shader *pgpushader);

      virtual void generate_mipmap();

               /**
       * Set the mip level to render with.
       * @param mipLevel
       */
      virtual void set_current_mip(int level);


      /**
       * Get the current width based on the mip level.
       * @return
       */
      virtual int mip_width();


      /**
       * Get the current height based on the mip level.
       * @return
       */
      virtual int mip_height();


      /**
       * Set which cube face texture to render to.
       * @param index
       */
      virtual void set_cube_face(int iFace, ::gpu::shader * pgpushader);




   };


} // namespace gpu



