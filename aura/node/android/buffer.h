#pragma once


namespace android
{


   class CLASS_DECL_AURA buffer :
      virtual public ::graphics::double_buffer
   {
   public:


      buffer();
      virtual ~buffer();


      virtual bool update_buffer(const ::size_i32 & size, int iStride = -1) override;
      virtual void destroy_buffer() override;

      virtual bool update_window(::image * pimage) override;

      //virtual ::draw2d::graphics * on_begin_draw();

   };


} // namespace android



