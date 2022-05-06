#pragma once


#include "aura/graphics/graphics/_graphics.h"


namespace android
{


   class CLASS_DECL_AURA buffer :
      virtual public ::graphics::double_buffer
   {
   public:


      buffer();
      ~buffer() override;


      bool update_buffer(const ::size_i32 & size, int iStride = -1) override;
      void destroy_buffer() override;

      bool update_screen(::image * pimage) override;

      //virtual ::draw2d::graphics * on_begin_draw();

   };


} // namespace android



