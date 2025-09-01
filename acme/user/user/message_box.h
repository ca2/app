// Merging micro::dialog::add_button by
//    camilo on 2024-10-09 09:11 <3ThomasBorregaardSorensen!!
// 
// From aura/user/user/messagebox.h by
//    camilo on 2024-10-09 08:55 <3ThomasBorregaardSorensen!!
//
// aura/user/user/message_box.h
// Created by camilo on 29/01/2021.  02:05 BRT <3ThomasBS_!!
//
#pragma once


namespace acme
{


   namespace user
   {


      class CLASS_DECL_ACME message_box :
         virtual public ::reified < ::message_box >
      {
      public:


         // ::pointer < ::

         //virtual ::pointer < ::subparticle > show(::user::interaction * puserinteraction, const ::scoped_string & scopedstrMessage, const ::scoped_string & scopedstrTitle, const ::user::e_message_box & emessagebox);
         void on_realize(::message_box * pmessagebox) override;


         virtual void add_button(const ::scoped_string & scopedstrText, enum_dialog_result edialogresult, char chLetter) = 0;

         
         virtual void set_dialog_result(const ::payload & payloadResult);

            
      };


   } // namespace user


}// namespace acme


