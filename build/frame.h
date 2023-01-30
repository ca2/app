#pragma once


#include "base/user/simple/frame_window.h"


namespace app_build
{


   class CLASS_DECL_APP_BUILD frame :
      virtual public simple_frame_window
   {
   public:


      frame();
      virtual ~frame();


//      // void assert_ok() const override;
//      // void dump(dump_context & dumpcontext) const override;


      virtual void on_layout(::draw2d::graphics_pointer& pgraphics) override;


   };


} // namespace app_build



