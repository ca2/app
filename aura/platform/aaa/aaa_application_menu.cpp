//
//  aura_application_menu.cpp
//  aura
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 13/11/18.
//

#include "framework.h"


namespace aura
{
   
   
   application_menu_item::application_menu_item()
   {
      
   }
   
   
   application_menu_item::application_menu_item(string strName, string strId) :
   m_strName(strName),
   m_strId(strId)
   {
      
   }
   
   
   void application_menu::add_item(::collection::index iIndex, string strName, string strId)
   {
      
      this->set_at_grow(iIndex, application_menu_item(strName, strId));
      
   }

   
} // namespace aura



