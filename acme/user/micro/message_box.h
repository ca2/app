//
// Created by camilo on 2022-01-21 14:57 <3ThomasBorregaardSorensen
// Generalized by camilo on 31/01/2022 14:28 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "acme/user/user/message_box.h"
#include "acme/user/micro/dialog.h"


namespace micro
{


      class icon;


      class message_box :
         virtual public ::micro::dialog,
         virtual public ::acme::user::message_box
      {
      public:


         string                                    m_strLabelDetails;
         ::pointer<::micro::still>                 m_pstillDetails;
         //::pointer<::micro::still>               m_pstillIcon;
         ::pointer<::nano::graphics::icon>         m_picon;
         //::pointer < ::message_box >               m_pmessagebox;


         message_box();
         ~message_box() override;


         void create_window() override;

         void destroy() override;

         //virtual void set(::message_box * pmessagebox);

         void on_realize(::message_box * pmessagebox) override;

         //virtual void create_message_box(conversation * pconversation);
         void add_button(const ::scoped_string & scopedstrText, enum_dialog_result edialogresult, char chLetter) override;
         
         ::string get_title() override;


         //::e_message_box get_conversation_flags() override;
         virtual void set_icon(::nano::graphics::icon * picon);

         virtual void calculate_size();

         void set_dialog_result(const ::payload & payloadResult);

         ::payload get_dialog_result() override;


         //void initialize_conversation(const ::string & strMessage, const ::string & strTitle, const ::e_message_box & emessagebox, const ::string & strDetails = nullptr, ::nano::graphics::icon * picon = nullptr) override;

         // void initialize_message_box(const ::string & strMessage, const ::string & strTitle, const ::e_message_box & emessagebox, const ::string & strDetails) override;

         //void do_message_box(const ::string& strMessage, const ::string& strTitle, const ::e_message_box & emessagebox, const ::string & strDetails) override;

         void on_draw(::nano::graphics::device * pnanodevice) override;

         void on_click(const ::payload & payload, ::user::mouse * pmouse) override;

         void on_right_click(const ::payload & payload, ::user::mouse * pmouse) override;

         void defer_create_details_still();

         void on_before_create_window(::acme::windowing::window * pacmewindowingwindow) override;

         void on_create_window() override;

         bool is_popup_window() const override;

      };


} // namespace micro



