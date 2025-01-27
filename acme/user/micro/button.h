// Created by camilo on 2022-01-21 16:52 <3ThomasBorregaardSorensen
#pragma once


#include "acme/user/micro/elemental.h"


namespace micro
{


   class button :
      virtual public ::micro::elemental
   {
   public:


      enum_dialog_result      m_edialogresult1 = e_dialog_result_cancel;
      char                    m_chLetter = '\0';


      button();
      ~button() override;


      void on_draw(::nano::graphics::device * pnanodevice) override;
      void on_char(int iChar) override;


      bool is_keyboard_focusable() override;


   };





} // namespace micro



