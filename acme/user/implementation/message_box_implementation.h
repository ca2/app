//
//  conversation_message.hpp
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 01/Oct/22. 00:59
//  Copyright (c) 2022 Camilo Sasuke Thomas Borregaard Soerensen. All rights reserved.
//
#pragma once


#include "acme/user/interface/message_box.h"
#include "acme/user/implementation/dialog_implementation.h"


namespace user_interface
{


// namespace user
// {
//
//class message_box;
//
//
//enum enum_dialog
//{
//   
//   e_dialog_none,
//   e_dialog_message_box,
//   
//   
//};
//
//
//class dialog;
//
//
//class CLASS_DECL_ACME dialog :
//virtual public ::acme::user::interaction
//{
//public:
//   
//   enum_dialog                                        m_edialog;
//   ::string                                           m_strTitle;
//   ::payload                                          m_payloadResult;
//   ::function<void(dialog *)>                         m_functionOnTimeOut;
//   ::function<void(const ::payload &)>                m_functionOnDialogResult2;
//   class ::time                                       m_timeShowStart;
//   class ::time                                       m_timeTimeout;
//   class ::time                                       m_timeCancelledTimeout;
//   
//   dialog();
//   ~dialog() override;
//   
//   
//   virtual ::string dialog_title() const;
//   
//   
//   virtual void display_dialog();
//   //virtual void display_dialog(::dialog * pdialog);
//   //virtual void display_dialog_and_wait_dialog_response(::dialog * pdialog);
//   //virtual void display_dialog(::dialog * pdialog);
//   virtual void display_dialog_and_wait_dialog_response();
//   
//   
//   virtual void set_dialog_result(const ::payload & payloadResult);
//   
//   
//   virtual void on_dialog_result(const ::payload & payloadResult);
//   
//   
//   //virtual message_box * get_message_box_payload();
//   
//   virtual class ::time dialog_time_remaining_from_timeout() const;
//   virtual class ::time dialog_timeout() const;
//   virtual ::string dialog_details() const;
//   virtual ::string_array_base dialog_details_icon_urls() const;
//   
//   //   ::string dialog_title() const override;
//   //
//   ////   using dialog::display_dialog;
//   //   void display_dialog() override;
//   //   void on_dialog_result(const ::payload & payloadResult) override;
//   //
//   //
//   //   class ::time dialog_time_remaining_from_timeout() const override;
//   //   class ::time dialog_timeout() const override;
//   
//};


//
//class CLASS_DECL_ACME dialog_payload :
//   virtual public dialog
//{
//public:
//
//
//
//
//   dialog_payload();
//   ~dialog_payload() override;
//
//
//
//
//};
//

//class CLASS_DECL_ACME dialog_reifier :
//   virtual public ::dialog
//{
//public:
//
//
//   ::pointer < ::dialog > m_pdialog;
//
//   dialog_reifier();
//   ~dialog_reifier() override;
//
//
//   ::string dialog_title() const override;
//
//
//   void display_dialog() override;
//   //void display_dialog(::dialog * pdialog) override;
//
//
//   void set_dialog_result(const ::payload & payloadResult) override;
//
//
//   class ::time dialog_time_remaining_from_timeout() const override;
//   class ::time dialog_timeout() const override;
//
//
//   message_box_payload * get_message_box_payload() override;
//
//
//
//};
//

class CLASS_DECL_ACME message_box_implementation :
//virtual public ::realizable < message_box >,
   virtual public ::user_interface::dialog_implementation,
virtual public ::user_interface::message_box
{
public:




   bool                                               m_bDetails = false;
   string                                             m_strMessage;
   string                                             m_strTitle;
   ::user::e_message_box                              m_emessagebox;
   string                                             m_strDetails;
   ::string                                           m_strDetailsTitle;
   ::string_array                                     m_straDetailsIconUrl;
   ::pointer < ::nano::graphics::icon >               m_picon2;
   ::string_array                                     m_straIconUrl;
   ::pointer < ::user::activation_token >             m_puseractivationtoken;
   ::function<void(::user_interface::message_box *)>  m_functionOnMessageBoxResult;
   ::pointer<::nano::graphics::icon>                  m_picon;




   
   //message_box_payload(const ::scoped_string & scopedstrMessage, const ::scoped_string & scopedstrTitle = {}, const ::user::e_message_box & emessagebox = {}, const ::scoped_string & scopedstrDetails = nullptr, ::nano::graphics::icon * picon = nullptr);
   //message_box(const ::scoped_string &scopedstrMessage, const ::scoped_string &scopedstrTitle = {},
     //          const ::user::e_message_box &emessagebox = {}, const ::scoped_string &scopedstrDetails = nullptr,
       //        const ::string_array_base &straIconUrl = {});
   //message_box(const ::exception & exception, const ::scoped_string & strMoreDetails);
   //message_box(const ::exception &exception, const ::scoped_string &strMessage,
     //          const ::scoped_string &scopedstrTitle, const ::user::e_message_box &emessagebox = {},
       //        const ::scoped_string &scopedstrDetails = nullptr, const ::string_array_base &straIconUrl = {});
   message_box_implementation();
   ~message_box_implementation() override;




   virtual void initialize_message_box(const ::scoped_string &scopedstrMessage, const ::scoped_string &scopedstrTitle = {},
            const ::user::e_message_box &emessagebox = {}, const ::scoped_string &scopedstrDetails = nullptr,
            const ::string_array_base &straIconUrl = {});
   virtual void initialize_message_box(const ::exception & exception, const ::scoped_string & strMoreDetails);
   virtual void initialize_message_box(const ::exception &exception, const ::scoped_string &strMessage,
               const ::scoped_string &scopedstrTitle, const ::user::e_message_box &emessagebox = {},
               const ::scoped_string &scopedstrDetails = nullptr, const ::string_array_base &straIconUrl = {});



   ::function < void (::user_interface::message_box *) > & message_box_response_callback() override;

   //virtual void _001InitializeMessageBox();

   void set_user_activation_token(user::activation_token *puseractivationtoken) override;

   ::i32_rectangle initial_frame_rectangle() override;

   ::string get_message() const override;
   ::string get_title() const override;

   ::string dialog_details_title() const override;

   ::user::e_message_box get_emessagebox() const override;

   virtual void _001InitializeMessageBox();
   ///void _on_draw(::nano::graphics::context * pgraphicscontext) override;
//void set_dialog_response(const ::payload &payloadResult) override;
   //void on_di
   //
   //#ifdef _DEBUG
   //   ::i64 increment_reference_count() override;
   //   ::i64 decrement_reference_count() override;
   //#endif
   
   //virtual ::string get_conversation_message();
   //virtual ::string get_conversation_title();
   //virtual ::user::e_message_box get_conversation_flags();
   //virtual ::string get_conversation_details();
   //virtual ::payload get_conversation_result();
   
   //message_box_payload *get_message_box_payload() override;
   
   ::payload get_dialog_response() override;
   


   void on_timed_out() override;
   
   ::string dialog_details() const override;
   
   ::string_array_base dialog_details_icon_urls() const override;

   ::string_array_base & dialog_details_icon_urls() override;


   void set_dialog_details_title(const ::scoped_string & scopedstrTitle) override;
   virtual void add_button(const ::scoped_string & scopedstrTitle, enum_dialog_result edialogresult, ::i8 chLetter);
   
//   void display_dialog() override;
   //virtual void async();
   //virtual void sync();
   
   //::payload do_synchronously(const class time & timeWait) override;
   //void do_asynchronously() override;
   
   /// shows the message box
   /// override in the topper implementation to display the message box (run the message box)
   void run() override;
   //void complete_aggregation(sequence * psequence) override;
   //
   
   void on_dialog_response(const ::payload &payloadResult) override;
   
};



//} // namespace user

} // namespace user_interface
