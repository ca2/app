//
// Created by camilo on 2022-01-21 14:57 <3ThomasBorregaardSørensen
// Generalized by camilo on 31/01/2022 14:28 <3ThomasBorregaardSørensen!!
//
#pragma once


class nano_message_box :
   virtual public nano_window
{
public:


   string                              m_strMessage;
   string                              m_strTitle;

   string                              m_strLabelDetails;


   __pointer(nano_still)               m_pstillDetails;


   nano_message_box();
   ~nano_message_box() override;

   virtual void calculate_size();

   virtual void display_synchronously(const ::string & strMessage, const ::string & strTitle, const ::e_message_box & emessagebox, const ::string & strDetails = nullptr);

   void on_draw(nano_device * pnanodevice) override;

   void on_click(const ::atom & atom) override;

   void on_right_click(const ::atom & atom) override;

   void defer_create_details_still();

   void on_create() override;

};
