// Created by camilo on 2022-01-21 16:52 <3ThomasBorregaardSorensen
#pragma once


#include "child.h"


class nano_device;


class nano_button :
   virtual public nano_child
{
public:


   enum_dialog_result      m_edialogresult1 = e_dialog_result_cancel;
   char                    m_chLetter = '\0';


   void on_draw(nano_device * pnanodevice) override;
   void on_char(int iChar) override;


   bool is_focusable() const override;


};



