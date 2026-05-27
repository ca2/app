// Created by camilo on 2022-01-21 16:52 <3ThomasBorregaardSorensen
#pragma once


#include "child.h"

namespace nano
{

   namespace user
   {
   

class button :
   virtual public ::micro::child
{
public:


   enum_dialog_result      m_edialogresult1 = e_dialog_result_cancel;
   ::i8                    m_chLetter = '\0';


   void on_draw(::nano::graphics::context * pnanodevice) override;
   void on_char(::i32 iChar) override;


   bool is_focusable() override;


};





   } // namespace user


} // namespace nano



