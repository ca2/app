#include "framework.h"


namespace app_core_build
{


   main_frame::main_frame()
   {

      m_bDefaultCreateToolbar = false;

      window_enable_full_screen();

      m_etranslucencyFrame = ::user::e_translucency_present;

   }


   main_frame::~main_frame()
   {

   }


   void main_frame::assert_valid() const
   {

      simple_frame_window::assert_valid();

   }


   void main_frame::dump(dump_context & dumpcontext) const
   {

      simple_frame_window::dump(dumpcontext);

   }


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





} // namespace app_core_build



