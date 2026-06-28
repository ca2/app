//
// Created by camilo on 2022-01-21 14:57 <3ThomasBorregaardSorensen
// Generalized by camilo on 31/01/2022 14:28 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "acme/user/interface/message_box.h"
#include "acme/user/micro/dialog.h"
#include "acme/user/user/message_box_reifier.h"
#include "user/implementation/message_box_implementation.h"


namespace micro
{


      class icon;


      class message_box :
         virtual public ::micro::dialog,
         virtual public ::user_interface::message_box_implementation
      {
      public:


         string                                    m_strLabelDetails;
         ::pointer<::micro::still>                 m_pstillDetails;
         ::pointer<::micro::still>                 m_pstillTimeout;
         //::pointer<::micro::still>               m_pstillIcon;
         ::pointer<::nano::graphics::icon>         m_picon;
         //::pointer < ::message_box_payload >               m_pmessagebox;
         ::manual_reset_happening                  m_manualresethappeningDialogResult;



         // class CLASS_DECL_ACME data :
         //    virtual public ::acme::user::dialog::data {
         // public:
         // };


         message_box();
         ~message_box() override;


         void create_window() override;

         void destroy() override;


         ::i32_rectangle initial_frame_rectangle() override;
         //void on_sequence() override;
         //virtual void set(::message_box_payload * pmessageboxpayload);

         //using ::acme::user::interaction::display;
         void display(::e_display edisplay = e_display_default, const ::user::activation & useractivation = {}) override;


         ///void display_dialog_and_wait_dialog_response() override;


         void on_context_menu(::user::mouse * pmouse) override;

         //virtual void create_message_box(conversation * pconversation);
         void add_button(const ::scoped_string & scopedstrText, enum_dialog_result edialogresult, ::i8 chLetter) override;

         //::string get_title() override;
         void on_initialize_dialog() override;


         void on_elemental_layout() override;

         //::user::e_message_box get_conversation_flags() override;
         virtual void set_icon(::nano::graphics::icon * picon);

         virtual void calculate_size();

         void set_dialog_response(const ::payload & payloadResult) override;

         ::payload get_dialog_response() override;

         void on_dialog_response(const ::payload & payloadResult) override;

         //void operator()(::timer * ptimer) override;

         void operator()(::timer * ptimer) override;

         //void initialize_conversation(const ::scoped_string & scopedstrMessage, const ::scoped_string & scopedstrTitle, const ::user::e_message_box & emessagebox, const ::scoped_string & scopedstrDetails = nullptr, ::nano::graphics::icon * picon = nullptr) override;

         // void initialize_message_box(const ::scoped_string & scopedstrMessage, const ::scoped_string & scopedstrTitle, const ::user::e_message_box & emessagebox, const ::scoped_string & scopedstrDetails) override;

         //void do_message_box(const ::scoped_string & scopedstrMessage, const ::scoped_string & scopedstrTitle, const ::user::e_message_box & emessagebox, const ::scoped_string & scopedstrDetails) override;

         void _on_draw(::nano::graphics::context * pnanodevice) override;

         void on_draw(::nano::graphics::context * pnanodevice) override;

         void on_click(const ::payload & payload, ::user::mouse * pmouse) override;

         void on_right_click(const ::payload & payload, ::user::mouse * pmouse) override;

         void defer_create_details_still();

         void on_before_create_window(::acme::windowing::window * pacmewindowingwindow) override;

         //void on_create_window() override;

         bool is_popup_window() const override;


         void run() override;

      };


} // namespace micro



