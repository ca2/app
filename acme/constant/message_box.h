//
// Created by camilo on 2022-10-23 14:17 <3ThomasBorregaardSorensen!!
//
#pragma once


enum enum_message_box
{


   e_message_box_ok                    = 0x00000000L,
   e_message_box_ok_cancel             = 0x00000001L,
   e_message_box_abort_retry_ignore    = 0x00000002L,
   e_message_box_yes_no_cancel         = 0x00000003L,
   e_message_box_yes_no                = 0x00000004L,
   e_message_box_retry_cancel          = 0x00000005L,
   e_message_box_cancel_try_continue   = 0x00000006L,
   e_message_box_icon_error            = 0x00000010L,
   e_message_box_icon_exclamation      = 0x00000030L,
   e_message_box_icon_question         = 0x00000020L,
   e_message_box_icon_asterisk         = 0x00000040L,
   e_message_box_default_button_1      = 0x00000000L,
   e_message_box_default_button_2      = 0x00000100L,
   e_message_box_default_button_3      = 0x00000200L,
   e_message_box_default_button_4      = 0x00000300L,
   e_message_box_button_mask           = 0x00000300L,


   e_message_box_icon_hand             = e_message_box_icon_error,
   e_message_box_icon_warning          = e_message_box_icon_exclamation,
   e_message_box_icon_information      = e_message_box_icon_asterisk,
   e_message_box_icon_stop             = e_message_box_icon_asterisk,


   e_message_box_system_modal          = 0x00001000L,


   e_message_box_type_mask             = 0x0000000FL,
   e_message_box_icon_mask             = 0x000000F0L,
   e_message_box_default_button_mask   = 0x00000F00L,
   e_message_box_mode_mask             = 0x00003000L,
   e_message_box_miscellaneous_mask    = 0x0000C000L,


};


DECLARE_ENUMERATION(e_message_box, enum_message_box);



