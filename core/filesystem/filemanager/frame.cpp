#include "framework.h"
#include "frame.h"
#include "tab_impact.h"
#include "acme/constant/message.h"


namespace filemanager
{


   frame::frame()
   {



   }


   frame::~frame()
   {

   }


   void  frame::on_message_create(::message::message * pmessage)
   {

      pmessage->previous();

   }


   void frame::on_create_bars()
   {

      return simple_frame_window::on_create_bars();

   }


   void frame::install_message_routing(::channel * pchannel)
   {

      simple_frame_window::install_message_routing(pchannel);

//#ifdef WINDOWS_DESKTOP
//      MESSAGE_LINK(WM_SETTEXT, pchannel, this, &frame::_001OnSetText);
//#endif

      MESSAGE_LINK(MESSAGE_CREATE, pchannel, this, &frame::on_message_create);

   }


   void  frame::_001OnSetText(::message::message * pmessage)
   {
      //   ::pointer<::user::message>pusermessage(pmessage);

      pmessage->previous();

      ::filemanager::tab_impact * ptabimpact = get_typed_parent < ::filemanager::tab_impact >();
      
      if (ptabimpact != nullptr)
      {
         
         auto strWindowText = get_window_text();

         ptabimpact->set_title_by_id(m_atomTab, strWindowText);

      }

   }


   ::pointer < ::experience::frame > frame::frame_experience()
   {

      auto pframe = ::simple_frame_window::frame_experience(nullptr, "022", "LightBlue");

      //on_select_user_style();

//      create_point_font(::user::font_list_item, "Arial", 14.0, e_font_weight_bold);
//
//      create_double(::user::double_width_rate, 1.2);
//
//      create_double(::user::double_list_item_height_rate, 2.0);

      //set_need_layout();

      return pframe;

   }



} // namespace filemanager




