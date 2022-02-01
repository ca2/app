// Created by camilo on 2021-01-21 16:52 <3ThomasBorregaardSørensen
#pragma once


#include "nano_child.h"


class nano_device;


class nano_button :
   virtual public nano_child
{
public:


   enum_dialog_result      m_edialogresult;


   void on_draw(nano_device * pnanodevice) override;
   void on_char(int iChar) override;


};



