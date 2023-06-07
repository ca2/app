#include "framework.h"
#include "main_frame.h"


namespace app_build
{


   main_frame::main_frame()
   {

      m_bToolbar = false;

      window_enable_full_screen();

      m_etranslucencyFrame = ::user::e_translucency_present;

   }


   main_frame::~main_frame()
   {

   }


   //void main_frame::assert_ok() const
   //{

   //   simple_frame_window::assert_ok();

   //}


   //void main_frame::dump(dump_context & dumpcontext) const
   //{

   //   simple_frame_window::dump(dumpcontext);

   //}


   ::experience::frame * main_frame::frame_experience()
   {

      auto pframe = ::simple_frame_window::frame_experience(nullptr, "013", "LightBlue");
      
      //auto pframe = ::simple_main_frame::frame_experience(nullptr, "013", "BlackPiano");

      return pframe;

   }


   bool main_frame::has_pending_graphical_update()
   {

      return is_window_visible();

   }





} // namespace app_build



