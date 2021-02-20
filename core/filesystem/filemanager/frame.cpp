#include "framework.h"
#include "core/filesystem/filemanager/_filemanager.h"


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

//#ifdef WINDOWS_DESKTOP
//      MESSAGE_LINK(WM_SETTEXT, pchannel, this, &frame::_001OnSetText);
//#endif

      MESSAGE_LINK(e_message_create, pchannel, this, &frame::_001OnCreate);

   }


   void  frame::_001OnSetText(::message::message * pmessage)
   {
      //   __pointer(::user::message) pusermessage(pmessage);

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




