#pragma once


namespace opengl
{


   class CLASS_DECL_AURA buffer :
      virtual public graphics::buffer
   {


      buffer(::layered * pobjectContext);
      virtual ~buffer();


      virtual void initialize(::user::interaction_impl * pimpl) override;



      virtual bool update_buffer(const ::size_i32 & size, int iStride = -1) override;
      virtual void destroy_buffer() override;


      virtual ::draw2d::graphics * on_begin_draw(synchronization_object ** ppsync) override;


      virtual bool update_window() override;




   };


} // namespace opengl


