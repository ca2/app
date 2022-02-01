//
// Created by camilo on 31/01/2022 14:28 <3ThomasBorregaardSørensen!!
//
#pragma once


// Created by camilo on 2021-01-21 14:57 <3ThomasBorregaardSørensen
#include "framework.h"
#include "acme/operating_system.h"
#include "nano_window.h"


class nano_message_box :
   virtual public nano_window
{
public:


   string            m_strMessage;
   string            m_strTitle;


   nano_message_box();
   ~nano_message_box();

   virtual void display_synchronously(const ::string & strMessage, const ::string & strTitle, const ::e_message_box & emessagebox);
   //__pointer(::sequence < ::conversation >) display(const ::string & strMessage, const ::string & strTitle, const ::e_message_box & emessagebox);

   void on_draw(nano_device * pnanodevice) override;

   //void draw_buttons(HDC hdc);

   //void delete_drawing_objects();
   //bool get_dark_mode();

   //void create_drawing_objects();
   //void update_drawing_objects();
   //enum_dialog_result hit_test(int x, int y);
   //void on_mouse_down(int x, int y);
   //void on_mouse_up(int x, int y);
   //enum_dialog_result get_result();

   //static LRESULT CALLBACK s_window_procedure(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);

   //LRESULT window_procedure(UINT message, WPARAM wparam, LPARAM lparam);

   void on_click(const ::id & id) override;

   void add_button(const char * pszText, enum_dialog_result edialogresult);


};
