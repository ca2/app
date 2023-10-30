//
//  apex_application_menu.cpp
//  apex
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 13/11/18.
//
/// Refactoring (from application_menu and menu_shared) by
/// camilo on 2023-10-26 00:21 <3ThomasBorregaardSorensen

#include "framework.h"
#include "application_menu.h"



//namespace apex
//{
//

application_menu::application_menu()
   {
      
   }
   

application_menu::application_menu(string strName, popup_flag_t) :
      m_strName(strName),
      m_bPopup(true)
   {
      
      
   }

   
application_menu::application_menu(bool bStockItem, string strName, string strId, string strAccelerator, string strDescription) :
   m_bStockItem(bStockItem),
   m_strName(strName),
   m_strId(strId),
   m_strAccelerator(strAccelerator),
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

application_menu * application_menu::popup_at(::index & iIndex, string strName)
{

   auto ppopup = 
      __initialize(__new(::application_menu(strName, popup_flag_t{})));

   this->insert_at(iIndex++, ppopup);

   return ppopup;

}


application_menu * application_menu::popup(string strName)
{

   auto iIndex = this->predicate_find_first([&strName](auto pmenu)
      {

         return pmenu->is_popup() && pmenu->m_strName == strName;

         });

   if (iIndex >= 0)
   {

      return element_at(iIndex);

   }
      
   iIndex = this->count();

   auto ppopup = popup_at(iIndex, strName);

   return ppopup;

}


application_menu * application_menu::_item_at(::index & i, bool bStockItem, string strName, string strId, string strMacosAccelerator, string strDescription)
{

   auto papplicationmenuItem =
      __initialize(__new(::application_menu(bStockItem, strName, strId, strMacosAccelerator, strDescription)));

   this->insert_at(i++, papplicationmenuItem);

   return papplicationmenuItem;

}


application_menu * application_menu::_item(bool bStockItem, string strName, string strId, string strAccelerator, string strDescription)
{

   auto iIndex = this->count();

   auto pitem = _item_at(iIndex, bStockItem, strName, strId, strAccelerator, strDescription);
      //__initialize(__new(::application_menu(bStockItem, strName, strId, strMacosAccelerator, strDescription)));

   return pitem;

   //this->insert_at(i, papplicationmenuItem);

   return pitem;

}


application_menu * application_menu::item_at(::index & iIndex, string strName, string strId, string strAccelerator, string strDescription)
{

   auto pitem = _item_at(iIndex, false, strName, strId, strAccelerator, strDescription);

   return pitem;

}


application_menu * application_menu::stock_item_at(::index & iIndex, string strName, string strId, string strAccelerator, string strDescription)
{

   auto pitem = _item_at(iIndex, true, strName, strId, strAccelerator, strDescription);

   return pitem;

}


application_menu * application_menu::item(string strName, string strId, string strAccelerator, string strDescription)
{

   auto iIndex = this->count();

   auto pitem = item_at(iIndex, strName, strId, strAccelerator, strDescription);

   return pitem;

}


application_menu * application_menu::stock_item(string strName, string strId, string strAccelerator, string strDescription)
{

   auto iIndex = this->count();

   auto pitem = stock_item_at(iIndex, strName, strId, strAccelerator, strDescription);

   return pitem;

}


application_menu * application_menu::separator_at(::index & i)
{

   auto pseparator = item_at(i, "", "separator");

   return pseparator;

}


application_menu * application_menu::separator()
{

   auto iIndex = this->count();

   auto pseparator = separator_at(iIndex);

   return pseparator;

}

   ::index application_menu::find_child_with_name(const char * pszName) const
   {
      
      return predicate_find_first([pszName](auto & pitem)
                                  {
         
         return pitem->m_strName == pszName;
         
      });
      
   }


   //string simple_frame_window::notification_area_get_xml_menu()
//{
//
//   auto pxmldocument = __create_new < ::xml::document >();
//
//   pxmldocument->create_root("menu");
//
//   for (auto & pitem : m_pnotifyicon->m_notifyiconitema)
//   {
//
//      if (pitem->m_strId == "separator")
//      {
//
//         pxmldocument->root()->add_child("separator");
//
//      }
//      else
//      {
//
//         pxmldocument->root()->add_child("item", { "id", pitem->m_strId }, pitem->m_strName);
//
//      }
//
//   }
//
//   return pxmldocument->get_xml();
//
//}


//} // namespace apex
//
//
//
