//
//  aura_application_menu.cpp
//  aura
//
//  Created by Camilo Sasuke Tsumanuma on 13/11/18.
//

#include "framework.h"


namespace axis
{
   
   
   application_menu_item::application_menu_item()
   {
      
   }
   
   
   application_menu_item::application_menu_item(string strName, string strId) :
   m_strName(strName),
   m_strId(strId)
   {
      
   }
   
   
   void application_menu::add_item(index iIndex, string strName, string strId)
   {
      
      this->set_at_grow(iIndex, application_menu_item(strName, strId));
      
   }

   
} // namespace axis



