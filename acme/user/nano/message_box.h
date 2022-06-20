//
// Created by camilo on 2022-01-21 14:57 <3ThomasBorregaardSørensen
// Generalized by camilo on 31/01/2022 14:28 <3ThomasBorregaardSørensen!!
//
#pragma once


class nano_message_box :
   virtual public nano_window
{
public:


   e_message_box                          m_emessagebox;
   string                              m_strLabelDetails;
   __pointer(nano_still)               m_pstillDetails;


   nano_message_box();
   ~nano_message_box() override;



   ::e_message_box get_message_box_flags() override;


   virtual void calculate_size();

   virtual void display(const ::string & strMessage, const ::string & strTitle, const ::e_message_box & emessagebox, const ::string & strDetails = nullptr);

   void do_message_box(const ::string& strMessage, const ::string& strTitle, const ::e_message_box & emessagebox, const ::string & strDetails) override;

   void on_draw(nano_device * pnanodevice) override;

   void on_click(const ::atom & atom, ::user::mouse * pmouse) override;

   void on_right_click(const ::atom & atom, ::user::mouse * pmouse) override;

   void defer_create_details_still();

   void on_create() override;
   
   bool is_popup_window() const override;

};
