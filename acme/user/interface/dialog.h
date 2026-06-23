//
//  conversation_message.hpp
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 01/Oct/22. 00:59
//  Copyright (c) 2022 Camilo Sasuke Thomas Borregaard Soerensen. All rights reserved.
//
#pragma once

//
//::particle_pointer particle::realize(::particle * pparticleReificator)
//{
//
//   return pparticleReificator->realize_particle(this);
//
//}
//
//
//// this is reificator/director
//::particle_pointer particle::realize_particle(::particle * pparticleToRealize)
//{
//
//
//}
//
//
////#include "acme/user/user/conversation.h"


#include "acme/prototype/prototype/realizable.h"
#include "acme/handler/sequenceable.h"
#include "acme/user/user/element.h"
//#include "acme/user/user/interaction.h"

namespace user_interface
{

//namespace user
//{

class message_box;


enum enum_dialog
{
   
   e_dialog_none,
   e_dialog_message_box,
   e_dialog_message_box_details,
   
};


class CLASS_DECL_ACME dialog :
virtual public ::user::element
{
public:

   //class CLASS_DECL_ACME data :
   //    virtual public ::particle {
   // public:
   //
   //    enum_dialog                                        m_edialog;
   //    ::string                                           m_strTitle;
   //    ::payload                                          m_payloadResult;
   //    ::function<void(dialog *)>                         m_functionOnTimeOut;
   //    ::function<void(const ::payload &)>                m_functionOnDialogResult2;
   //    class ::time                                       m_timeShowStart;
   //    class ::time                                       m_timeTimeout;
   //    class ::time                                       m_timeCancelledTimeout;
   //    ::pointer < ::manual_reset_happening >             m_pmanualresethappeningDialogResponse;
   //
   // };


   ::pointer < ::user_interface::dialog > m_pdialog;

   
   dialog();
   ~dialog() override;

virtual ::i32_rectangle initial_frame_rectangle();

   virtual void on_initialize_dialog();

   virtual void set_dialog_type(enum_dialog edialog);

   virtual ::string dialog_title() const;
   

   virtual ::function<void(const ::payload &)> & dialog_response_callback();

   //virtual void display_dialog();
   //virtual void display_dialog(::dialog * pdialog);
   //virtual void display_dialog_and_wait_dialog_response(::dialog * pdialog);
   //virtual void display_dialog(::dialog * pdialog);
   virtual bool is_waiting_for_dialog_response();

   virtual void wait_dialog_response(const class ::time & timeTimeout = ::time::infinity());
   
   
   virtual void set_dialog_response(const ::payload & payloadResult);

   virtual ::payload get_dialog_response();
   
   virtual void on_dialog_response(const ::payload & payloadResult);

   virtual void on_dialog_finished();

   void display(::e_display edisplay = e_display_default, const ::user::activation & useractivation = {}) override;
   //virtual message_box * get_message_box_payload();
   
   virtual class ::time dialog_time_remaining_from_timeout() const;
   virtual class ::time dialog_timeout() const;
   virtual ::string dialog_details() const;
   virtual ::string_array_base dialog_details_icon_urls() const;
   virtual ::string_array_base & dialog_details_icon_urls();

   //   ::string dialog_title() const override;
   //
   ////   using dialog::display_dialog;
   //   void display_dialog() override;
   //   void on_dialog_result(const ::payload & payloadResult) override;
   //
   //
   //   class ::time dialog_time_remaining_from_timeout() const override;
   //   class ::time dialog_timeout() const override;
   
};


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
//class CLASS_DECL_ACME message_box :
////virtual public ::realizable < message_box >
//virtual public ::dialog
//{
//public:
//   
//   
//   bool                                               m_bDetails = false;
//   string                                             m_strMessage;
//   string                                             m_strTitle;
//   ::user::e_message_box                              m_emessagebox;
//   string                                             m_strDetails;
//   ::string                                           m_strDetailsTitle;
//   ::string_array                                     m_straDetailsIconUrl;
//   ::pointer < ::nano::graphics::icon >               m_picon2;
//   ::string_array                                     m_straIconUrl;
//   ::pointer < ::user::activation_token >             m_puseractivationtoken;
//   ::function<void(::message_box *)>                  m_functionOnMessageBoxResult;
//   
//   
//   //message_box_payload(const ::scoped_string & scopedstrMessage, const ::scoped_string & scopedstrTitle = {}, const ::user::e_message_box & emessagebox = {}, const ::scoped_string & scopedstrDetails = nullptr, ::nano::graphics::icon * picon = nullptr);
//   message_box(const ::scoped_string &scopedstrMessage, const ::scoped_string &scopedstrTitle = {},
//               const ::user::e_message_box &emessagebox = {}, const ::scoped_string &scopedstrDetails = nullptr,
//               const ::string_array_base &straIconUrl = {});
//   message_box(const ::exception & exception, const ::scoped_string & strMoreDetails);
//   message_box(const ::exception &exception, const ::scoped_string &strMessage,
//               const ::scoped_string &scopedstrTitle, const ::user::e_message_box &emessagebox = {},
//               const ::scoped_string &scopedstrDetails = nullptr, const ::string_array_base &straIconUrl = {});
//   ~message_box() override;
//   //
//   //#ifdef _DEBUG
//   //   ::i64 increment_reference_count() override;
//   //   ::i64 decrement_reference_count() override;
//   //#endif
//   
//   //virtual ::string get_conversation_message();
//   //virtual ::string get_conversation_title();
//   //virtual ::user::e_message_box get_conversation_flags();
//   //virtual ::string get_conversation_details();
//   //virtual ::payload get_conversation_result();
//   
//   //message_box_payload *get_message_box_payload() override;
//   
//   ::payload get_result_payload() override;
//   
//   
//   void on_timed_out() override;
//   
//   ::string dialog_details() const override;
//   
//   ::string_array_base dialog_details_icon_urls() const override;
//   
//   void display_dialog() override;
//   //virtual void async();
//   //virtual void sync();
//   
//   //::payload do_synchronously(const class time & timeWait) override;
//   //void do_asynchronously() override;
//   
//   /// shows the message box
//   /// override in the topper implementation to display the message box (run the message box)
//   void run() override;
//   //void complete_aggregation(sequence * psequence) override;
//   //
//   
//   void on_dialog_result(const ::payload &payloadResult) override;
//   
//};
//


//} // namespace user


} // namespace user_interface



