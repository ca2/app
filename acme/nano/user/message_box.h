//
// Created by camilo on 2022-01-21 14:57 <3ThomasBorregaardSorensen
// Generalized by camilo on 31/01/2022 14:28 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "window.h"


namespace nano
{

namespace user
{

class message_box :
   virtual public ::nano::user::window
{
public:


   string                              m_strLabelDetails;
   ::pointer<::nano::user::still>               m_pstillDetails;


   message_box();
   ~message_box() override;



   //::e_message_box get_conversation_flags() override;


   virtual void calculate_size();


   void initialize_conversation(const ::string & strMessage, const ::string & strTitle, const ::e_message_box & emessagebox, const ::string & strDetails = nullptr) override;

   // void initialize_message_box(const ::string & strMessage, const ::string & strTitle, const ::e_message_box & emessagebox, const ::string & strDetails) override;

   //void do_message_box(const ::string& strMessage, const ::string& strTitle, const ::e_message_box & emessagebox, const ::string & strDetails) override;

   void on_draw(::nano::user::device * pnanodevice) override;

   void on_click(const ::payload & payload, ::user::mouse * pmouse) override;

   void on_right_click(const ::payload& payload, ::user::mouse * pmouse) override;

   void defer_create_details_still();

   void on_create() override;
   
   bool is_popup_window() const override;

};



   } // namespace user


} // namespace nano



