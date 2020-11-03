#include "framework.h" 
#if !BROAD_PRECOMPILED_HEADER
#include "core/user/simple_ui/_simple_ui.h"
#endif


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

      MESSAGE_LINK(WM_KEYDOWN, pchannel, this, &edit_box::_001OnKeyDown);
      MESSAGE_LINK(WM_KEYUP, pchannel, this, &edit_box::_001OnKeyDown);
      MESSAGE_LINK(e_message_lbutton_down, pchannel, this, &edit_box::_001OnLButtonDown);
      MESSAGE_LINK(e_message_lbutton_up, pchannel, this, &edit_box::_001OnLButtonUp);

   }


   void edit_box::_001OnLButtonDown(::message::message * pmessage)
   {

      UNREFERENCED_PARAMETER(pmessage);

//      SCAST_PTR(::message::mouse, pmouse, pmessage);

      //    keyboard_set_focus();

//      pmouse->m_bRet = true;
      //pmessage->previous();
      //pmessage->m_bRet = true;
   }


   void edit_box::_001OnLButtonUp(::message::message * pmessage)
   {

      UNREFERENCED_PARAMETER(pmessage);
      //pmessage->previous();

//      SCAST_PTR(::message::mouse, pmouse, pmessage);

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


   void edit_box::_001OnKeyDown(::message::message * pmessage)
   {
      //pmessage->previous();
      //pmessage->m_bRet = true;
      return;


   }


} // namespace simple_ui
