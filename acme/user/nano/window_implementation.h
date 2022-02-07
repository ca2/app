//
// Created by camilo on 31/01/2022 23:04 <3ThomasBorregaardSørensen!!
//
#pragma once


class CLASS_DECL_ACME nano_window_implementation :
   virtual public nano_window_interface
{
public:


   __pointer(nano_window)        m_pinterface;


   nano_window_implementation();
   ~nano_window_implementation() override;


   void draw(nano_device * pnanodevice) override;

   bool get_dark_mode() override;
   bool is_active() override;

   virtual void on_create();


};



