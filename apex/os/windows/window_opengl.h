#pragma once


namespace opengl
{


   class CLASS_DECL_APEX buffer :
      virtual public graphics::buffer
   {


      buffer(::object * pobject);
      virtual ~buffer();


      virtual void initialize(::user::interaction_impl * pimpl) override;



      virtual bool create_buffer(const ::size & size, int iStride = -1);
      virtual void destroy_buffer();


      virtual ::draw2d::graphics * on_begin_draw(sync ** ppsync) override;


      virtual bool update_window() override;




   };


} // namespace opengl


