// Merging micro::dialog::add_button and micro::message_box::add_button implementation by
//    camilo on 2024-10-09 09:11 <3ThomasBorregaardSorensen!!
// 
// From aura/user/user/message_box.cpp by
//    camilo on 2024-10-09 08:57 <3ThomasBorregaardSorensen!!
//
// aura/user/user/message_box.cpp
// Created by camilo on 29/01/2021.  02:05 BRT <3ThomasBS_!!
//
#include "framework.h"
#include "message_box.h"


namespace acme
{


   namespace user
   {


      void message_box::on_realize(::message_box * pmessagebox)
      {

         auto emessageboxType = pmessagebox->m_emessagebox & ::user::e_message_box_type_mask;

         switch (emessageboxType)
         {
         case ::user::e_message_box_ok_cancel:
            add_button("OK", e_dialog_result_ok, 'o');
            add_button("Cancel", e_dialog_result_cancel, 'c');
            break;
         case ::user::e_message_box_abort_retry_ignore:
            add_button("Abort", e_dialog_result_abort, 'a');
            add_button("Retry", e_dialog_result_retry, 'r');
            add_button("Ignore", e_dialog_result_ignore, 'i');
            break;
         case ::user::e_message_box_yes_no_cancel:
            add_button("Yes", e_dialog_result_yes, 'y');
            add_button("No", e_dialog_result_no, 'n');
            add_button("Cancel", e_dialog_result_cancel, 'c');
            break;
         case ::user::e_message_box_yes_no:
            add_button("Yes", e_dialog_result_yes, 'y');
            add_button("No", e_dialog_result_no, 'n');
            break;
         case ::user::e_message_box_retry_cancel:
            add_button("Retry", e_dialog_result_retry, 'r');
            add_button("Cancel", e_dialog_result_cancel, 'c');
            break;
         case ::user::e_message_box_cancel_try_continue:
            add_button("Cancel", e_dialog_result_cancel, 'c');
            add_button("Try", e_dialog_result_retry, 't');
            add_button("Continue", e_dialog_result_continue, 'e');
            break;
         default:
            add_button("OK", e_dialog_result_ok, 'o');
            break;
         }

         //return nullptr;

      }


      void message_box::set_dialog_result(const ::payload & payloadResult)
      {


      }


   } // namespace user


} // namespace acme



