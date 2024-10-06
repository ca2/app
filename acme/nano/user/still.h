// Created by camilo on 2022-02-06 08:55 <3ThomasBorregaardSorensen!! (Thomas likes number 5 <3)
#pragma once


#include "interaction.h"

namespace nano 
{


   namespace user 
   {


      class device;
      class icon;

      class still :
         virtual public ::nano::user::elemental
      {
      public:


         bool        m_bHyperlink;
         ::pointer < ::nano::graphics::icon > m_picon;

         virtual ~still();


         void on_draw(::nano::graphics::device * pnanodevice) override;
         void on_char(int iChar) override;

         virtual void set_icon(::nano::graphics::icon * picon);

         void on_mouse_move(::user::mouse * pmouse) override;

         bool is_focusable() override;


         void resize_to_fit() override;


      };



   } // namespace user


} // namespace nano



