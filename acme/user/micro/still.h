// Created by camilo on 2022-02-06 08:55 <3ThomasBorregaardSorensen!! (Thomas likes number 5 <3)
#pragma once


#include "acme/user/micro/elemental.h"


namespace micro
{


   class device;
   class icon;

   class still :
      virtual public ::micro::elemental
   {
   public:


      bool        m_bHyperlink;
      ::pointer < ::nano::graphics::icon > m_picon;

      virtual ~still();


      void on_draw(::nano::graphics::device * pnanodevice) override;
      void on_char(int iChar) override;

      virtual void set_icon(::nano::graphics::icon * picon);

      void fore_on_mouse_move(::user::mouse * pmouse) override;

      bool is_keyboard_focusable() override;


      void resize_to_fit() override;


   };


} // namespace micro



