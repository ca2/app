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


class message_box_payload;


enum enum_dialog
{

   e_dialog_none,
   e_dialog_message_box,


};


class dialog;


class CLASS_DECL_ACME dialog :
   virtual public ::particle
{
public:


   dialog();
   ~dialog() override;


   virtual ::string dialog_title() const;


   virtual void display_dialog();
   virtual void display(::dialog * pdialog);


   virtual void set_dialog_result(const ::payload & payloadResult);


   virtual void on_dialog_result(const ::payload & payloadResult);


   virtual message_box_payload * get_message_box_payload();

   virtual class ::time dialog_time_remaining_from_timeout() const;
   virtual class ::time dialog_timeout() const;
   virtual ::string dialog_details() const;


};



class CLASS_DECL_ACME dialog_payload :
   virtual public dialog
{
public:


   enum_dialog                                        m_edialog;
   ::string                                           m_strTitle;
   ::payload                                          m_payloadResult;
   ::function<void(dialog *)>                         m_functionOnTimeOut;
   ::function<void(const ::payload &)>                m_functionOnDialogResult;
   class ::time                                       m_timeShowStart;
   class ::time                                       m_timeTimeout;
   class ::time                                       m_timeCancelledTimeout;


   dialog_payload();
   ~dialog_payload() override;


   ::string dialog_title() const override;


   void display(::dialog * pdialog) override;
   void on_dialog_result(const ::payload & payloadResult) override;


   class ::time dialog_time_remaining_from_timeout() const override;
   class ::time dialog_timeout() const override;


};


class CLASS_DECL_ACME dialog_reifier :
   virtual public ::dialog
{
public:


   ::pointer < ::dialog > m_pdialog;

   dialog_reifier();
   ~dialog_reifier() override;


   ::string dialog_title() const override;


   void display_dialog() override;
   void display(::dialog * pdialog) override;


   void set_dialog_result(const ::payload & payloadResult) override;


   class ::time dialog_time_remaining_from_timeout() const override;
   class ::time dialog_timeout() const override;


   message_box_payload * get_message_box_payload() override;



};


class CLASS_DECL_ACME message_box_payload :
   //virtual public ::realizable < message_box >
   virtual public ::dialog_payload
{
public:
   
   
   bool                                               m_bDetails = false;
   string                                             m_strMessage;
   string                                             m_strTitle;
   ::user::e_message_box                              m_emessagebox;
   string                                             m_strDetails;
   ::pointer < ::nano::graphics::icon >               m_picon;
   ::pointer < ::user::activation_token >             m_puseractivationtoken;


   message_box_payload(const ::scoped_string & scopedstrMessage, const ::scoped_string & scopedstrTitle = {}, const ::user::e_message_box & emessagebox = {}, const ::scoped_string & scopedstrDetails = nullptr, ::nano::graphics::icon * picon = nullptr);
   message_box_payload(const ::exception & exception, const ::scoped_string & strMoreDetails);
   message_box_payload(const ::exception & exception, const ::scoped_string & strMessage, const ::scoped_string & scopedstrTitle, const ::user::e_message_box & emessagebox = {}, const ::scoped_string & scopedstrDetails = nullptr, ::nano::graphics::icon * picon = nullptr);
   ~message_box_payload() override;
//
//#ifdef _DEBUG
//   long long increment_reference_count() override;
//   long long decrement_reference_count() override;
//#endif
   
   //virtual ::string get_conversation_message();
   //virtual ::string get_conversation_title();
   //virtual ::user::e_message_box get_conversation_flags();
   //virtual ::string get_conversation_details();
   //virtual ::payload get_conversation_result();
   
   message_box_payload *get_message_box_payload() override;
   
   ::payload get_result_payload() override;

   
   void on_timed_out() override;

   ::string dialog_details() const override;

   //virtual void async();
   //virtual void sync();

   //::payload do_synchronously(const class time & timeWait) override;
   //void do_asynchronously() override;

   /// shows the message box
   /// override in the topper implementation to display the message box (run the message box)
   //void run() override;
   //void complete_aggregation(sequence * psequence) override;   
};



