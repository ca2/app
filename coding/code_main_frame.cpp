#include "framework.h"
#include "code_main_frame.h"


namespace coding
{


   main_frame::main_frame()
   {


   }


   main_frame::~main_frame()
   {

   }


   ::pointer < ::experience::frame > main_frame::frame_experience()
   {

      auto pframe = ::simple_main_frame::frame_experience(nullptr, "022", "LightBlue");

      return pframe;

   }


} // namespace coding



