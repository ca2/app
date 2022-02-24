//
// Created by camilo on 2022-02-16 22:38 <3ThomasBorregaardSørensen!!
//
#pragma once


class popup_button :
   virtual public nano_window
{
public:



   popup_button();
   ~popup_button() override;



   void calculate_size();


   virtual void display_synchronously(const ::string & strText);



   void on_click(const ::atom & atom) override;

   void on_draw(nano_device * pnanodevice);



};
