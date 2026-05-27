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
      //bool m_bBorder = true;
      

      virtual ~still();


      void on_draw(::nano::graphics::context * pnanodevice) override;
      void on_char(::i32 iChar) override;

      virtual void set_icon(::nano::graphics::icon * picon);

      //void fore_on_mouse_move(::user::mouse * pmouse) override;
      void on_mouse_enter() override;
      void on_mouse_leave() override;

      bool is_keyboard_focusable() override;


      void resize_to_fit() override;


   };


} // namespace micro



