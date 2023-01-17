#include "framework.h"
#include "main_frame.h"
#include "acme/constant/message.h"


namespace app_integration
{


   main_frame::main_frame()
   {

      //m_ewindowflag += window_flag_miniaturizable;

      //m_bDefaultCreateToolbar = false;

      window_enable_full_screen();

   }


   main_frame::~main_frame()
   {

   }


//   void main_frame::assert_ok() const
//   {
//
//      simple_frame_window::assert_ok();
//
//   }
//
//
//   void main_frame::dump(dump_context & dumpcontext) const
//   {
//
//      simple_frame_window::dump(dumpcontext);
//
//   }


   ::experience::frame * main_frame::frame_experience()
   {

      auto pframe = ::simple_main_frame::frame_experience(nullptr, "013", "LightBlue");

      return pframe;

   }


   bool main_frame::has_pending_graphical_update()
   {

      return ::simple_frame_window::has_pending_graphical_update();

   }


   //bool main_frame::get_translucency(::user::enum_translucency & etranslucency, ::enum_element eelement, ::user::style_context * pcontext)
   //{

   //   if (m_bExplicitTranslucency)
   //   {

   //      etranslucency = m_etranslucency;

   //      return true;

   //   }

   //   //if (userstyle() != NULL)
   //   //{

   //   //   if (m_puserstyle->_001GetMainFrameTranslucency(etranslucency))
   //   //      return true;

   //   //}
   //   //etranslucency = ::user::e_translucency_present;

   //   ////      etranslucency = ::user::e_translucency_none;

   //   //return true;

   //   return ::user::style::get_translucency(etranslucency, eelement, pcontext);

   //}


   void main_frame::install_message_routing(::channel * pchannel)
   {

      simple_frame_window::install_message_routing(pchannel);

      MESSAGE_LINK(MESSAGE_CREATE, pchannel, this, &simple_main_frame::on_message_create);

   }


   void main_frame::on_message_create(::message::message * pmessage)
   {

      set_bitmap_source("Integration!!");

   }


} // namespace simple_drawing







