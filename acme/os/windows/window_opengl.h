#pragma once


namespace opengl
{


   class CLASS_DECL_ACME buffer :
      virtual public graphics::buffer
   {


      buffer(::generic * pobject);
      virtual ~buffer();


      virtual void initialize(::user::interaction_impl * pimpl) override;



      virtual bool update_buffer(const ::size & size, int iStride = -1) override;
      virtual void destroy_buffer() override;


      virtual ::draw2d::graphics * on_begin_draw(sync ** ppsync) override;


      virtual bool update_window() override;




   };


} // namespace opengl


