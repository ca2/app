// Created by camilo on 2025-06-12 12:32 <3ThomasBorregaardSørensen!!
#pragma once


#include "bred/gpu/texture_attributes.h"
#include "bred/gpu/texture_flags.h"


namespace gpu
{


   class CLASS_DECL_BRED render_target :
      virtual public ::particle
   {
   public:


      ::collection::index m_iGpuRenderTarget = -1;

      bool                                         m_bAdvancedPipelineSynchronization = false;

      //::collection::index                          m_iCurrentFrame2 = -1;
      //::collection::index                          m_iFrameSerial2 = -1;


      bool                                         m_bRenderTargetInit;
      bool                                         m_bBackBuffer;

      bool                                         m_bWithDepth;

      ::pointer < ::pointer_array < ::gpu::texture > >    m_ptexturea;
      ::pointer < ::pointer_array < ::gpu::texture > >    m_ptextureaDepth;


      ::i32_size m_size;


      ::pointer < renderer >  m_pgpurenderer;

      ::pointer<render_target> m_prendertargetOld;

      //::pointer < frame > m_pgpulayer;
      ::pointer<layer> m_pgpulayer;

      
      render_target();
      ~render_target() override;



      virtual void on_new_frame();


      virtual ::pointer_array < ::gpu::texture > *texturea2();
      virtual ::pointer_array < ::gpu::texture >* depth_texturea2();
      virtual ::gpu::texture *texture(::collection::index i);
      virtual ::gpu::texture *depth_texture(::collection::index i);

      virtual void initialize_render_target(::gpu::renderer* prenderer, const ::i32_size& size, ::pointer <::gpu::render_target>previous);

      virtual void restart_frame_counter();


      virtual bool is_starting_frame()const;


      //virtual void on_new_frame();

      virtual void init();

      virtual void on_init();

      virtual void on_resize(const ::i32_size & size);

      //virtual void create_images();

      virtual void on_create_render_target_texture(::gpu::texture_attributes & textureattributes, ::gpu::texture_flags & textureflags);


      virtual ::i32 get_frame_index();
      virtual ::i32 get_frame_count();

      //virtual ::i32 get_image_index() const;
      virtual ::i32 imageCount();
      virtual ::i32 width();
      virtual ::i32 height();


      virtual void initialize_render_target_image(::gpu::texture *pgputexture);


      //virtual ::gpu::texture* current_texture(::gpu::layer* pgpulayer);
      //virtual ::gpu::texture *current_depth_texture(::gpu::layer * pgpulayer);
      virtual ::gpu::texture* current_texture(::gpu::layer* pgpulayer);
      virtual ::gpu::texture *current_depth_texture(::gpu::layer *pgpulayer);


      virtual void on_before_begin_draw_frame(::gpu::graphics* pgraphics);
      virtual void on_after_end_draw_frame(::gpu::graphics* pgraphics);


//      virtual void on_end_render(::gpu::layer* pgpulayer);


   };


} // namespace gpu



