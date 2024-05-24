// Created by camilo on 2022-02-06 08:55 <3ThomasBorregaardSorensen!! (Thomas likes number 5 <3)
#pragma once


#include "child.h"

namespace nano{namespace user{
class device;


class still :
   virtual public ::nano::user::child
{
public:


   bool        m_bHyperlink;


   virtual ~still();


   void on_draw(::nano::user::device * pnanodevice) override;
   void on_char(int iChar) override;


   void on_mouse_move(::user::mouse * pmouse) override;

   bool is_focusable() const override;


   //virtual void resize_to_fit();


};



   } // namespace user


} // namespace nano



