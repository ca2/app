// Created by camilo on 2022-01-21 05:10 PM <3ThomasBorregaardSørensen
#pragma once


class nano_window;


class nano_child :
   virtual public ::object
{
public:


   string                  m_strText;
   ::atom                  m_atom;
   rectangle_i32           m_rectangle;
   nano_window *           m_pwindow;


   virtual void on_draw(nano_device * pnanodevice) = 0;
   virtual void on_char(int iChar) = 0;
   virtual void set_focus();
   virtual bool is_focusable() const;
   virtual void on_mouse_move(int x, int y);
   virtual void set_capture();
   virtual bool has_capture() const;
   virtual void release_capture();


};




