// Created by camilo on 2025-06-12 12:32 <3ThomasBorregaardSørensen!!
#pragma once


namespace gpu
{


   class CLASS_DECL_BRED render_target :
      virtual public ::particle
   {
   public:


      bool                                         m_bAdvancedPipelineSynchronization = false;

      //::collection::index                          m_iCurrentFrame2 = -1;
      //::collection::index                          m_iFrameSerial2 = -1;


      bool                                         m_bRenderTargetInit;
      bool                                         m_bBackBuffer;

      bool                                         m_bWithDepth;

      ::pointer < ::pointer_array < texture > >    m_ptexturea;
      ::pointer < ::pointer_array < texture > >    m_ptextureaDepth;


      ::int_size m_size;


      ::pointer < renderer >  m_pgpurenderer;

      ::pointer<render_target> m_prendertargetOld;

      ::pointer < frame > m_pgpuframe;

      
      render_target();
      ~render_target() override;


      virtual ::pointer_array < ::gpu::texture > *texturea();
      virtual ::pointer_array < ::gpu::texture >* depth_texturea();

      virtual void initialize_render_target(::gpu::renderer* prenderer, const ::int_size& size, ::pointer <::gpu::render_target>previous);

      virtual void restart_frame_counter();


      virtual bool is_starting_frame()const;


      //virtual void on_new_frame();

      virtual void init();

      virtual void on_init();

      virtual void on_resize(const ::int_size & size);

      virtual void create_images();

      virtual void on_create_render_target_texture(::gpu::texture* pgputexture);


      virtual int get_frame_index();
      virtual int get_frame_count();

      //virtual int get_image_index() const;
      virtual int imageCount();
      virtual int width();
      virtual int height();


      virtual texture* current_texture(::gpu::frame* pgpuframe);
      virtual texture* current_depth_texture(::gpu::frame* pgpuframe);


      virtual void on_before_begin_draw_frame(::gpu::graphics* pgraphics);
      virtual void on_after_end_draw_frame(::gpu::graphics* pgraphics);


//      virtual void on_end_render(::gpu::frame* pgpuframe);


   };


} // namespace gpu



