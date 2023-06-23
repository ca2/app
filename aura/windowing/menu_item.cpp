//
//  menu_shared.hpp
//  aura
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 2021-02-08 20:44 <3TBS_!! Thomas Borregaard Soerensen
//
#include "framework.h"
////#include "aura/user/menu/_component.h"
#include "menu_item.h"


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



