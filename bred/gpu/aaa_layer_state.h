// Created by camilo on 2025-06-20 18:43 <3ThomasBorregaardSørensen!!
#pragma once


namespace gpu
{


   class CLASS_DECL_BRED layer_state :
      virtual public ::particle
   {
   public:


      //;
      //;
      enum_gpu_layer_state          m_egpulayerstate = e_gpu_layer_state_initial;
      //     enum_render_mode m_emode = e_render_mode_multiple_frame_states;


      layer_state();
      ~layer_state() override;


      virtual void initialize_layer_state();

      virtual void start_layer_render();

      virtual void end_layer_render();

      //virtual void set_no_frame();

      //virtual void set_single_frame();

      //virtual void restart_frame_counter();

      //   ;
      //virtual void on_happening(enum_happening ehappening);


      //virtual void init();

      //virtual void on_init();


      //virtual void createImages();


      //virtual ::i32 get_frame_index();
      //virtual ::i32 get_frame_count();

      //virtual void on_new_frame();



      //virtual void endFrame();



      //virtual texture* current_texture();


      //virtual void on_before_begin_draw_frame(::gpu::graphics* pgraphics);
      //virtual void on_after_end_draw_frame(::gpu::graphics* pgraphics);


      //      virtual void on_end_render(::gpu::layer* pgpulayer);


   };


} // namespace gpu



