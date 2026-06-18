#include "framework.h"
#include "main_frame.h"


namespace coding
{


   main_frame::main_frame()
   {

      m_bDefaultNotifyIcon2 = true;

   }


   main_frame::~main_frame()
   {

   }


   ::pointer < ::experience::frame > main_frame::frame_experience()
   {

      auto pframe = ::simple_frame_window::frame_experience(nullptr, "008", "LightBlue");
      
      return pframe;

   }


//   bool main_frame::has_pending_graphical_update()
//   {
//
//      return ::simple_main_frame::has_pending_graphical_update();
//
//   }


} // namespace integration_integration



