// Created by camilo on 2025-06-20 18:43 <3ThomasBorregaardSørensen!!
#pragma once


namespace gpu
{


   class CLASS_DECL_BRED render_state :
      virtual public ::particle
   {
   public:


      enum_state                    m_estate = e_state_initial;
      enum_render_mode              m_emode = e_render_mode_multiple_frame_states;


      render_state();
      ~render_state() override;


      //virtual void set_no_frame();

      //virtual void set_single_frame();

      //virtual void restart_frame_counter();

      virtual void on_happening(enum_happening ehappening);


      //virtual void init();

      //virtual void on_init();


      //virtual void createImages();


      //virtual int get_frame_index();
      //virtual int get_frame_count();

      //virtual void on_new_frame();



      //virtual void endFrame();



      //virtual texture* current_texture();


      //virtual void on_before_begin_draw_frame(::draw2d_gpu::graphics* pgraphics);
      //virtual void on_after_end_draw_frame(::draw2d_gpu::graphics* pgraphics);


      //      virtual void on_end_render(::gpu::frame* pgpuframe);


   };


} // namespace gpu



