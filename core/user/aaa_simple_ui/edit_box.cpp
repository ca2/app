#include "framework.h" 
#include "core/user/simple_ui/_simple_ui.h"

namespace simple_ui
{


   edit_box::edit_box()
   {

      m_iPos = 0;

   }


   edit_box::~edit_box()
   {

   }


   void edit_box::install_message_routing(::channel * pchannel)
   {

      ::user::plain_edit::install_message_routing(pchannel);

      MESSAGE_LINK(e_message_key_down, pchannel, this, &edit_box::on_message_key_down);
      MESSAGE_LINK(e_message_key_up, pchannel, this, &edit_box::on_message_key_down);
      MESSAGE_LINK(e_message_left_button_down, pchannel, this, &edit_box::on_message_left_button_down);
      MESSAGE_LINK(e_message_left_button_up, pchannel, this, &edit_box::on_message_left_button_up);

   }


   void edit_box::on_message_left_button_down(::message::message * pmessage)
   {

      UNREFERENCED_PARAMETER(pmessage);

//      auto pmouse = pmessage->m_pmouse;

      //    keyboard_set_focus();

//      pmouse->m_bRet = true;
      //pmessage->previous();
      //pmessage->m_bRet = true;
   }


   void edit_box::on_message_left_button_up(::message::message * pmessage)
   {

      UNREFERENCED_PARAMETER(pmessage);
      //pmessage->previous();

//      auto pmouse = pmessage->m_pmouse;

      //pmessage->m_bRet = true;

   }



   bool edit_box::keyboard_focus_is_focusable()
   {

      return true;

   }


   /*

   CLASS_DECL_CORE char ansi_upper(i32 ch)
   {

   if(ch >= 'a' && ch <= 'z')
   {
   ch = ch - 'a' + 'A';
   }

   return ch;

   }


   CLASS_DECL_CORE char * ansi_upper(char * pchParam)
   {
   char * pch = pchParam;
   while(*pch == '\0')
   {
   *pch = ansi_upper(*pch);
   pch++;
   }
   return pchParam;
   }


   */


   void edit_box::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {


      ::user::plain_edit::_001OnDraw(pgraphics);


   }


   void edit_box::on_message_key_down(::message::message * pmessage)
   {
      //pmessage->previous();
      //pmessage->m_bRet = true;
      return;


   }


} // namespace simple_ui
