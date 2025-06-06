// Created by camilo on 2021-01-21 14:57 <3ThomasBorregaardSorensen
// Help from http://www.winprog.org/tutorial/simple_window.html
// implementing windows::message_box 2023-12-19 04:55 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "acme/operating_system/message_box.h"
#include "acme/_operating_system.h"


CLASS_DECL_ACME int message_box_to_windows_message_box_type(enum_message_box emessagebox)
{

   auto emessageboxType = (enum_message_box)(emessagebox & e_message_box_type_mask);

   switch (emessageboxType)
   {
   case e_message_box_ok:
      return MB_OK;
   case e_message_box_ok_cancel:
      return MB_OKCANCEL;
   case e_message_box_abort_retry_ignore:
      return MB_ABORTRETRYIGNORE;
   case e_message_box_yes_no_cancel:
      return MB_YESNOCANCEL;
   case e_message_box_yes_no:
      return MB_YESNO;
   case e_message_box_retry_cancel:
      return MB_RETRYCANCEL;
   case e_message_box_cancel_try_continue:
      return MB_CANCELTRYCONTINUE;
   default:
      return 0;
   }

}


CLASS_DECL_ACME int message_box_to_windows_message_box_icon(enum_message_box emessagebox)
{

   auto emessageboxIcon = (enum_message_box)(emessagebox & e_message_box_icon_mask);

   switch (emessageboxIcon)
   {
   case e_message_box_icon_error:
      return MB_ICONERROR;
   case e_message_box_icon_exclamation:
      return MB_ICONEXCLAMATION;
   case e_message_box_icon_question:
      return MB_ICONQUESTION;
   case e_message_box_icon_asterisk:
      return MB_ICONASTERISK;
   default:
      return 0;
   }

}


CLASS_DECL_ACME int message_box_to_windows_message_box_default_button(enum_message_box emessagebox)
{

   auto emessageboxDefaultButton = (enum_message_box)(emessagebox & e_message_box_default_button_mask);

   switch (emessageboxDefaultButton)
   {
   case e_message_box_default_button_1:
      return MB_DEFBUTTON1;
   case e_message_box_default_button_2:
      return MB_DEFBUTTON1;
   case e_message_box_default_button_3:
      return MB_DEFBUTTON3;
   case e_message_box_default_button_4:
      return MB_DEFBUTTON4;
   default:
      return 0;
   }

}



//
//namespace windows
//{
//
//
//   class message_box:
//   public ::operating_system::message_box
//   {
//   public:
//
//      //::atom do_modal(const ::scoped_string & scopedstrMessage,
//      //                               const ::scoped_string & scopedstrTitle, const ::e_message_box & emessagebox,
//      //                               const ::scoped_string & scopedstrDetails) override
//      ::enum_dialog_result m_edialogresult;
//      void run() override
//      {
//         auto iType = message_box_to_windows_message_box(m_emessagebox);
//         ::wstring wstrMessage(m_strMessage);
//         ::wstring wstrTitle(m_strTitle);
//
//         auto iRet = ::MessageBoxW(nullptr, wstrMessage, wstrTitle, iType);
//
//         m_edialogresult = windows_message_box_result_to_dialog_result(iRet);
//
//
//      }
//
//
//      void complete_step(sequencer & sequencer) override
//      {
//
//         sequencer.add_result(m_edialogresult);
//
//      }
//
//   };
//
//
//} // namespace windows

//
//void windows_message_box_factory(::factory::factory * pfactory)
//{
//
//   pfactory->add_factory_item<::windows::message_box, ::operating_system::message_box >();
//
//}
//





CLASS_DECL_ACME int message_box_to_windows_message_box(enum_message_box emessagebox)
{

   int iMessageBox = 0;

   iMessageBox |= message_box_to_windows_message_box_type(emessagebox);

   iMessageBox |= message_box_to_windows_message_box_icon(emessagebox);

   iMessageBox |= message_box_to_windows_message_box_default_button(emessagebox);

   return iMessageBox;

}


CLASS_DECL_ACME enum_dialog_result windows_message_box_result_to_dialog_result(int iResult)
{

   switch (iResult)
   {
   case IDOK:
      return e_dialog_result_ok;
   case IDCANCEL:
      return e_dialog_result_cancel;
   case IDABORT:
      return e_dialog_result_abort;
   case IDRETRY:
      return e_dialog_result_retry;
   case IDIGNORE:
      return e_dialog_result_ignore;
   case IDYES:
      return e_dialog_result_yes;
   case IDNO:
      return e_dialog_result_no;
   case IDCLOSE:
      return e_dialog_result_close;
   case IDHELP:
      return e_dialog_result_help;
   case IDTRYAGAIN:
      return e_dialog_result_retry;
   case IDCONTINUE:
      return e_dialog_result_continue;
   case IDTIMEOUT:
      return e_dialog_result_timeout;
   default:
      return e_dialog_result_none;
   }

}
