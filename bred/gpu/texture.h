// Created by camilo on 2025-06-12 21:04 <3ThomasBorregaardSørensen!!
#pragma once


#include "bred/gpu/context_object.h"
#include "bred/gpu/texture_attributes.h"
#include "bred/gpu/texture_flags.h"
#include "bred/gpu/texture_data.h"


struct pixmap_t;
class pixmap;


namespace gpu
{


   class CLASS_DECL_BRED texture :
      virtual public ::gpu::context_object
   {
   public:


      ::collection::index                 m_iTextureSerial;
      ::string                            m_strTextureName;
      texture_attributes                  m_textureattributes;
      texture_flags                       m_textureflags;
      enum_texture_state                  m_etexturestate;
      ::i32                                 m_iAtlasX;
      ::i32                                 m_iAtlasY;
      ::i32                                 m_iAtlasCurrentRowHeight;
      bool                                m_bClearColor;
      ::color::color                      m_colorClear;
      //::pointer < ::gpu::renderer >       m_pgpurenderer;
      ::collection::index                 m_iIndex;
      ::i32                                 m_iCurrentMip;
      ::i32                                 m_iCurrentLayer;
      bool m_bHdr = false;

      //::pointer < ::gpu::render_target >  m_pgpurendertarget;
      ::i32_size m_sizeMip{-1, -1};
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
      ::pointer<::gpu::binding_slot_set> m_pbindingslotsetSingular;

      texture();
      ~texture() override;


      virtual void _create_texture(const texture_data & texturedata = {});
      virtual void _set_data(const texture_data &texturedata = {});

      virtual ::i32_rectangle rectangle() const;
      virtual ::i32_size size() const;
      virtual ::i32 width() const;
      virtual ::i32 height() const;

      virtual ::i32 mip_count() const;
      virtual ::i32 maximum_mip_count() const;
      virtual ::i32 mip_width_for_mip(::i32 baseWidth, ::i32 iMip) const;
      virtual ::i32 mip_height_for_mip(::i32 baseHeight, ::i32 iMip) const;
      virtual ::i32 mip_width() const;
      virtual ::i32 mip_height() const;
///      virtual ::i32 render_target_view_index(::i32 iFace, ::i32 iMip) const;
//      virtual ::i32 current_render_target_view_index() const;


      virtual ::i32 layer_count() const;


      virtual void set_state(::gpu::command_buffer *pgpucommandbuffer, ::gpu::enum_texture_state etexturestate);

      virtual void from_external_state(::gpu::enum_texture_state etexturestate,
                                       ::gpu::enum_texture_state etexturestateNow);
      virtual void to_external_state(::gpu::command_buffer *pgpucommandbuffer);


      void defer_throw_if_cube_map_pixmaps_are_not_ok(const ::pointer_array < ::pixmap >& pixmapa);
      
      virtual void initialize_hdr_texture_on_memory(::gpu::context *pcontext, const ::block & block);
      virtual void initialize_with_image_data(
         ::gpu::context *pgpucontext, 
         const ::i32_rectangle &rectangleTarget,
         ::i32 numChannels,
         bool bSrgb,
         const void * pdata,
         enum_texture etexture = e_texture_image);
      virtual void initialize_texture(::gpu::context* pgpucontext,
         const texture_attributes & textureattributes,
         const texture_flags & textureflags = {},
         const texture_data & texturedata = {});
//      virtual void initialize_mipmap_cubemap_texture(::gpu::context *pgpucontext, const ::i32_rectangle& rectangleTarget, ::i32 iMipCount = -1, bool bRenderTarget = true, bool bShaderResourceView = true);
      virtual void initialize_depth_texture(::gpu::context* pgpucontext, const ::i32_rectangle& rectangleTarget);

      virtual void initialize_texture_from_file_path(::gpu::context* pgpucontext, const ::file::path & path, bool bIsSrgb);
      virtual void initialize_texture_from_pixmap(::gpu::context* pgpucontext, const ::pointer_array < ::pixmap > & pixmapa, enum_texture etexture = e_texture_image);

      virtual ::pointer < ::gpu::pixmap > create_gpu_pixmap(const ::i32_size & size);

      //virtual void merge_layers(::pointer_array < ::gpu::layer >* playera);
      //virtual void blend(::gpu::layer * player);
      //virtual void blend(::gpu::texture * ptexture);

      virtual void create_render_target();

      virtual void create_shader_resource_view();

      virtual void create_depth_resources();

      virtual void bind_render_target();

      virtual texture* get_depth_texture();

      virtual ::string texture_type();
      virtual void set_pixels(const ::i32_rectangle& rectangle, const void* data);
      virtual void read_pixels(::pixmap * ppixmap);
      virtual void write_pixels(const ::pixmap * ppixmap);
      virtual void write_pixels(const ::i32_size & size, const ::image32_t * pimage32, ::i32 iScan);

      virtual bool is_in_shader_sampling_state();

      //virtual void set_cube_face(::i32 iFace, ::gpu::shader *pgpushader);

      virtual void generate_mipmap(::gpu::command_buffer * pgpucommandbuffer);

      virtual void set_current_mip(::i32 level);

      virtual ::i32 mip_width();

      virtual ::i32 mip_height();

      virtual void set_current_layer(::i32 iLayer);


      //virtual void defer_fence();


            ::gpu::binding_slot_set *binding_slot_set(::gpu::command_buffer *pgpucommandbuffer,
                                                ::gpu::binding_set *pbindingset);


      virtual void defer_fence();
      virtual void wait_fence();


   };


} // namespace gpu



