#pragma once


#include "base/user/simple/main_frame.h"


namespace app_build
{


   class CLASS_DECL_APP_BUILD main_frame :
      virtual public ::simple_main_frame
   {
   public:


      main_frame();
      virtual ~main_frame();


//      // void assert_ok() const override;
//      // void dump(dump_context & dumpcontext) const override;


      ::experience::frame * frame_experience() override;

      bool has_pending_graphical_update() override;


   };


} // namespace app_build



