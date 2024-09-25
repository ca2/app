// Created by camilo on 2022-02-06 08:55 <3ThomasBorregaardSorensen!! (Thomas likes number 5 <3)
#pragma once


#include "child.h"

namespace nano{namespace user{
class device;
class icon;

class still :
   virtual public ::nano::user::child
{
public:


   bool        m_bHyperlink;
::pointer < ::nano::user::icon > m_picon;

   virtual ~still();


   void on_draw(::nano::user::device * pnanodevice) override;
   void on_char(int iChar) override;

   virtual void set_icon(::nano::user::icon * picon);

   void on_mouse_move(::user::mouse * pmouse) override;

   bool is_focusable() const override;


   void resize_to_fit() override;


};



   } // namespace user


} // namespace nano



