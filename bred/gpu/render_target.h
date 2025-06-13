// Created by camilo on 2025-06-12 12:32 <3ThomasBorregaardSørensen!!
#pragma once


namespace gpu
{


   class CLASS_DECL_BRED render_target :
      virtual public ::particle
   {
   public:

      
      render_target();
      ~render_target() override;


      virtual void init();


      virtual texture * current_texture();


      virtual void on_before_begin_draw_frame(::draw2d_gpu::graphics* pgraphics);
      virtual void on_after_end_draw_frame(::draw2d_gpu::graphics* pgraphics);


   };


} // namespace gpu



