//
// Created by camilo on 2022-10-23 14:17 <3ThomasBorregaardSorensen!!
//
#pragma once


enum enum_message_box
{


   ::user::e_message_box_ok                    = 0x00000000L,
   ::user::e_message_box_ok_cancel             = 0x00000001L,
   ::user::e_message_box_abort_retry_ignore    = 0x00000002L,
   ::user::e_message_box_yes_no_cancel         = 0x00000003L,
   ::user::e_message_box_yes_no                = 0x00000004L,
   ::user::e_message_box_retry_cancel          = 0x00000005L,
   ::user::e_message_box_cancel_try_continue   = 0x00000006L,
   ::user::e_message_box_icon_error            = 0x00000010L,
   ::user::e_message_box_icon_exclamation      = 0x00000030L,
   ::user::e_message_box_icon_question         = 0x00000020L,
   ::user::e_message_box_icon_asterisk         = 0x00000040L,
   ::user::e_message_box_default_button_1      = 0x00000000L,
   ::user::e_message_box_default_button_2      = 0x00000100L,
   ::user::e_message_box_default_button_3      = 0x00000200L,
   ::user::e_message_box_default_button_4      = 0x00000300L,
   ::user::e_message_box_button_mask           = 0x00000300L,


   ::user::e_message_box_icon_hand             = ::user::e_message_box_icon_error,
   ::user::e_message_box_icon_warning          = ::user::e_message_box_icon_exclamation,
   ::user::e_message_box_icon_information      = ::user::e_message_box_icon_asterisk,
   ::user::e_message_box_icon_stop             = ::user::e_message_box_icon_asterisk,


   ::user::e_message_box_system_modal          = 0x00001000L,


   ::user::e_message_box_type_mask             = 0x0000000FL,
   ::user::e_message_box_icon_mask             = 0x000000F0L,
   ::user::e_message_box_default_button_mask   = 0x00000F00L,
   ::user::e_message_box_mode_mask             = 0x00003000L,
   ::user::e_message_box_miscellaneous_mask    = 0x0000C000L,


};




