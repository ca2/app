//
// Created by camilo on 2023-12-19 04:57 <3ThomasBorregaardSorensen!!
// From https://github.com/ca2/motif_labs
//
#pragma once


#include "acme/operating_system/message_box.h"
//
//
//namespace macos
//{
//
//   class message_box :
//      virtual public ::operating_system::message_box
//   {
//   public:
//      
//      //::atom do_modal(const ::scoped_string & scopedstrMessage, const ::scoped_string & scopedstrTitle, const ::user::e_message_box & emessagebox, const ::scoped_string & scopedstrDetails = {}) override;
//      
//      ::payload do_synchronously(const class time & timeWait) override;
//
//      
//   };
//
//} // macos
//


::enum_dialog_result ns_message_box(const_char_pointer title, const_char_pointer message, ::user::enum_message_box emessagebox);



