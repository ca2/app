#pragma once


namespace opengl
{


   class CLASS_DECL_AURA buffer :
      virtual public graphics::buffer
   {


      ::graphics::buffer();
      virtual ~buffer();


      virtual ::e_status initialize_graphics_graphics(::user::interaction_impl * pimpl) override;

      virtual bool update_buffer(const ::size & size, int iStride = -1) override;
      virtual void destroy_buffer() override;


      virtual sync * get_draw_lock() override;
      virtual ::draw2d::graphics * on_begin_draw() override;


      virtual bool update_window() override;




   };


} // namespace opengl