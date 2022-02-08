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
   string                              m_strDetails;
   string                              m_strTitle;


   __pointer_array(nano_button)        m_buttona;
   __pointer(nano_still)               m_pstillDetails;


   nano_message_box();
   ~nano_message_box() override;

   virtual void calculate_size();

   virtual void display_synchronously(const ::string & strMessage, const ::string & strTitle, const ::e_message_box & emessagebox, const ::string & strDetails = nullptr);

   void on_draw(nano_device * pnanodevice) override;

   void on_click(const ::atom & atom) override;

   void add_button(const char * pszText, enum_dialog_result edialogresult);

   void on_create() override;

};
