#pragma once


#include "berg/user/simple/main_frame.h"


namespace coding
{


   class CLASS_DECL_CODING main_frame :
      virtual public ::simple_main_frame
   {
   public:


      main_frame();
      ~main_frame() override;


      ::pointer < ::experience::frame > frame_experience() override;

      //bool has_pending_graphical_update() override;


   };


} // namespace coding



