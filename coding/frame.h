#pragma once


#include "berg/user/simple/frame_window.h"


namespace coding
{


   class CLASS_DECL_CODING frame :
      virtual public simple_frame_window
   {
   public:


      frame();
      ~frame() override;


      virtual void on_layout(::draw2d::graphics_pointer& pgraphics) override;


   };


} // namespace coding



