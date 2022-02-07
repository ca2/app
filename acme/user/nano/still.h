// Created by camilo on 2022-02-06 08:55 <3ThomasBorregaardSørensen!! (Thomas likes number 5 <3)
#pragma once


class nano_device;


class nano_still :
   virtual public nano_child
{
public:


   bool        m_bHyperlink;


   void on_draw(nano_device * pnanodevice) override;
   void on_char(int iChar) override;


   virtual void on_mouse_move(int x, int y);

   bool is_focusable() const override;


   virtual void resize_to_fit();


};



