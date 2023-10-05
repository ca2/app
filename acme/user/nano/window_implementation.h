//
// Created by camilo on 31/01/2022 23:04 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "window_interface.h"


class CLASS_DECL_ACME nano_window_implementation :
   virtual public nano_window_interface
{
public:


   ::pointer < ::nano_window >         m_pinterface;


   nano_window_implementation();
   ~nano_window_implementation() override;


   virtual ::nano::display * get_display();


   void draw(nano_device * pnanodevice) override;


   bool get_dark_mode() override;
   bool is_active() override;

   virtual void nano_window_on_create();

   virtual void on_create();


   ::point_i32 try_absolute_mouse_position(const ::point_i32 & point) override;


   void handle(::topic * ptopic, ::context * pcontext) override;


   virtual ::size_i32 get_main_screen_size();

   
   virtual ::payload do_synchronously(const class time & timeWait = ::time::infinity()) override;
   virtual void do_asynchronously() override;
   

};



