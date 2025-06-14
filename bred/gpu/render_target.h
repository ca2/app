// Created by camilo on 2025-06-12 12:32 <3ThomasBorregaardSørensen!!
#pragma once


namespace gpu
{


   class CLASS_DECL_BRED render_target :
      virtual public ::particle
   {
   public:


      static constexpr int MAX_FRAMES_IN_FLIGHT = 2;

      bool m_bDepthStencil = false;

      ::pointer_array < texture >            m_texturea;


      ::int_size m_size;


      ::pointer < renderer >  m_pgpurenderer;

      ::pointer<render_target> m_prendertargetviewOld;


      
      render_target();
      ~render_target() override;


      virtual void initialize_render_target(::gpu::renderer* prenderer, const ::int_size& size, ::pointer <::gpu::render_target>previous);


      virtual void init();

      //virtual int get_image_index() const;
      size_t imageCount() { return m_texturea.size(); }
      uint32_t width() { return m_size.cx(); }
      uint32_t height() { return m_size.cy(); }


      virtual texture * current_texture();


      virtual void on_before_begin_draw_frame(::draw2d_gpu::graphics* pgraphics);
      virtual void on_after_end_draw_frame(::draw2d_gpu::graphics* pgraphics);


   };


} // namespace gpu



