//
//  menu_shared.hpp
//  aura
//
//  Created by Camilo Sasuke Tsumanuma on 2021-02-08 20:44 <3TBS_!! Thomas Borregaard Sørensen
//
#include "framework.h"
//#include "aura/user/_menu.h"


namespace windowing
{


   menu_item::menu_item()
   {

   }

   menu_item::~menu_item()
   {

   }

   void menu_item::add_status(enum_status estatus)
   {

      m_estatus += estatus;

   }


   void menu_item::erase_status(enum_status estatus)
   {

      m_estatus -= estatus;

   }

} // namespace windowing



