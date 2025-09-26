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
#include "acme/constant/id.h"


//namespace apex
//{
//

application_menu::application_menu()
   {
      
   }
   

application_menu::application_menu(const ::scoped_string & scopedstrName, popup_flag_t) :
      m_strName(scopedstrName),
      m_bPopup(true)
   {
      
      
   }

   
application_menu::application_menu(bool bStockItem, const ::scoped_string & scopedstrName, const ::atom & atom, const ::scoped_string & scopedstrAccelerator, const ::scoped_string & scopedstrDescription) :
   m_bStockItem(bStockItem),
   m_strName(scopedstrName),
   id()(atom),
   m_strAccelerator(scopedstrAccelerator),
   m_strDescription(scopedstrDescription)
   {
      
   }
   
   
//   void application_menu::add_item(::collection::index iIndex, const ::scoped_string & scopedstrName, const ::atom & atom, const ::scoped_string & scopedstrMacosAccelerator, const ::scoped_string & scopedstrDescription)
//   {
//      
//      this->set_at_grow(iIndex, application_menu_item(strName, strId, strMacosAccelerator, strDescription));
//      
//   }

//   

application_menu * application_menu::popup_at(::collection::index & iIndex, const ::scoped_string & scopedstrName)
{

   auto ppopup = 
      __initialize(øallocate ::application_menu(scopedstrName, popup_flag_t{}));

   this->insert_at(iIndex++, ppopup);

   information() << "application_menu::popup_at : " << ppopup->m_strName;

   return ppopup;

}


application_menu * application_menu::popup(const ::scoped_string & scopedstrName)
{

   auto iIndex = this->predicate_find_first([&scopedstrName](auto pmenu)
      {

         return pmenu->is_popup() && pmenu->m_strName == scopedstrName;

         });

   if (iIndex >= 0)
   {

      return element_at(iIndex);

   }
      
   iIndex = this->count();

   information() << "application_menu::popup : " << scopedstrName;

   auto ppopup = popup_at(iIndex, scopedstrName);

   return ppopup;

}


application_menu * application_menu::_item_at(::collection::index & i, bool bStockItem, const ::scoped_string & scopedstrName, const ::atom & atom, const ::scoped_string & scopedstrAccelerator, const ::scoped_string & scopedstrDescription)
{

   auto papplicationmenuItem =
      __initialize(øallocate ::application_menu(bStockItem, scopedstrName, atom, scopedstrAccelerator, scopedstrDescription));

   this->insert_at(i++, papplicationmenuItem);

   return papplicationmenuItem;

}


application_menu * application_menu::_item(bool bStockItem, const ::scoped_string & scopedstrName, const ::atom & atom, const ::scoped_string & scopedstrAccelerator, const ::scoped_string & scopedstrDescription)
{

   auto iIndex = this->count();

   auto pitem = _item_at(iIndex, bStockItem, scopedstrName, atom, scopedstrAccelerator, scopedstrDescription);
      //__initialize(øallocate ::application_menu(bStockItem, strName, strId, strMacosAccelerator, strDescription));

   return pitem;

   //this->insert_at(i, papplicationmenuItem);

   //return pitem;

}


application_menu * application_menu::item_at(::collection::index & iIndex, const ::scoped_string & scopedstrName, const ::atom & atom, const ::scoped_string & scopedstrAccelerator, const ::scoped_string & scopedstrDescription)
{

   auto pitem = _item_at(iIndex, false, scopedstrName, atom, scopedstrAccelerator, scopedstrDescription);

   return pitem;

}


application_menu * application_menu::stock_item_at(::collection::index & iIndex, const ::scoped_string & scopedstrName, const ::atom & atom, const ::scoped_string & scopedstrAccelerator, const ::scoped_string & scopedstrDescription)
{

   auto pitem = _item_at(iIndex, true, scopedstrName, atom, scopedstrAccelerator, scopedstrDescription);

   return pitem;

}


application_menu * application_menu::item(const ::scoped_string & scopedstrName, const ::atom & atom, const ::scoped_string & scopedstrAccelerator, const ::scoped_string & scopedstrDescription)
{

   auto iIndex = this->predicate_find_first([&atom](auto pmenu)
      {

         return !pmenu->is_popup() && pmenu->id() == atom;

         });
   
   if (iIndex >= 0)
   {

      auto pitem = element_at(iIndex);
      
      pitem->m_strName = scopedstrName;
      pitem->m_strAccelerator = scopedstrAccelerator;
      pitem->m_strDescription = scopedstrDescription;
      
      return pitem;

   }
   else
   {
      
      iIndex = this->count();
      
      auto pitem = item_at(iIndex, scopedstrName, atom, scopedstrAccelerator, scopedstrDescription);
      
      return pitem;
      
   }

}


application_menu * application_menu::stock_item(const ::scoped_string & scopedstrName, const ::atom & atom, const ::scoped_string & scopedstrAccelerator, const ::scoped_string & scopedstrDescription)
{

   auto iIndex = this->count();

   auto pitem = stock_item_at(iIndex, scopedstrName, atom, scopedstrAccelerator, scopedstrDescription);

   return pitem;

}


application_menu * application_menu::separator_at(::collection::index & i)
{

   auto pseparator = item_at(i, {}, id_separator);

   return pseparator;

}


application_menu * application_menu::separator()
{

   auto iIndex = this->count();

   auto pseparator = separator_at(iIndex);

   return pseparator;

}

   ::collection::index application_menu::find_child_with_name(const char * pszName) const
   {
      
      return predicate_find_first([pszName](auto & pitem)
                                  {
         
         return pitem->m_strName == pszName;
         
      });
      
   }


   //string simple_frame_window::notification_area_get_xml_menu()
//{
//
//   auto pxmldocument = øcreate_new < ::xml::document >();
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

   void application_menu::destroy()
   {

      for (auto & pmenu : *this)
      {

         try
         {

            pmenu->destroy();

         }
         catch (...)
         {

         }


      }

      ::pointer_array < application_menu >::clear();

      ::pointer_array < application_menu >::destroy();

   }
//} // namespace apex
//
//
//
