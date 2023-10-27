//
//  apex_application_menu.cpp
//  apex
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 13/11/18.
//
/// Refactoring (from application_menu and menu_shared) by
/// camilo on 2023-10-26 00:21 <3ThomasBorregaardSorensen

#include "framework.h"
#include "menu.h"



namespace apex
{


   menu::menu()
   {
      
   }
   

   menu::menu(string strName, popup_flag_t) :
      m_strName(strName),
      m_bPopup(true)
   {
      
      
   }

   
   menu::menu(string strName, string strId, string strMacosAccelerator, string strDescription) :
   m_strName(strName),
   m_strId(strId),
m_strMacosAccelerator(strMacosAccelerator),
m_strDescription(strDescription)
   {
      
   }
   
   
//   void application_menu::add_item(index iIndex, string strName, string strId, string strMacosAccelerator, string strDescription)
//   {
//      
//      this->set_at_grow(iIndex, application_menu_item(strName, strId, strMacosAccelerator, strDescription));
//      
//   }

//   


   ::index menu::find_child_with_name(const char * pszName) const
   {
      
      return predicate_find_first([pszName](auto & pitem)
                                  {
         
         return pitem->m_strName == pszName;
         
      });
      
   }


} // namespace apex
//
//
//
