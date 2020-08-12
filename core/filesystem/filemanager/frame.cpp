#include "framework.h"



namespace filemanager
{


   frame::frame()
   {



   }


   frame::~frame()
   {

   }


   void  frame::_001OnCreate(::message::message * pmessage)
   {

      pmessage->previous();

   }


   bool  frame::on_create_bars()
   {

      return simple_frame_window::on_create_bars();

   }


   void  frame::install_message_routing(::channel * pchannel)
   {

      simple_frame_window::install_message_routing(pchannel);

      IGUI_MSG_LINK(WM_SETTEXT, pchannel, this, &frame::_001OnSetText);

      IGUI_MSG_LINK(WM_CREATE, pchannel, this, &frame::_001OnCreate);

   }


   void  frame::_001OnSetText(::message::message * pmessage)
   {
      //   SCAST_PTR(::message::base, pbase, pmessage);

      pmessage->previous();

      string str;

      ::filemanager::tab_view * ptabview = GetTypedParent < ::filemanager::tab_view >();
      if (ptabview != nullptr)
      {
         get_window_text(str);
         ptabview->SetTitleById(m_idTab, str);
      }

   }



} // namespace filemanager




