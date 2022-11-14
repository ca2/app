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

      string str;

      ::filemanager::tab_impact * ptabimpact = get_typed_parent < ::filemanager::tab_impact >();
      if (ptabimpact != nullptr)
      {
         get_window_text(str);
         ptabimpact->set_title_by_id(m_atomTab, str);
      }

   }



} // namespace filemanager




