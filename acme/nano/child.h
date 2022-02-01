// Created by camilo on 2021-01-21 05:10 PM <3ThomasBorregaardSørensen
#pragma once


class nano_window;


class nano_child :
   virtual public ::object
{
public:


   string                  m_strText;
   ::id                    m_id;
   rectangle_i32           m_rectangle;
   nano_window *           m_pwindow;


   virtual void on_draw(nano_device * pnanodevice) = 0;
   virtual void on_char(int iChar) = 0;
   virtual void set_focus();


};



