//
//  apex_application_menu.hpp
//  apex
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 13/11/18.
//
/// Refactoring (from application_menu and menu_shared) by
/// camilo on 2023-10-26 00:22 <3ThomasBorregaardSorensen
/// Back to application_menu, totally classical like a good
/// orange jam and Thommy!! on 2023-10-29 21:19 <ThomasBorregaardSorensen!!
#pragma once


struct popup_flag_t{};

//#include "acme/constant/id.h"

#include "acme/user/menu/menu.h"


class CLASS_DECL_ACME application_menu :
   virtual public ::menu::menu,
   virtual public ::pointer_array < application_menu >
{
public:
   

   enum enum_status
   {
      e_status_none = 0,
      e_status_checked = 1<<0,
      e_status_disabled = 1<<1,
      e_status_set_checked = 1<<8,
      e_status_set_disabled = 1<<9,
   };
   
   
   ::collection::index m_iCurrentLayoutItemIndex = 0;
   bool        m_bPopup = false;
   string      m_strName;
   ::atom      m_atomMenu;
   string      m_strLabel;
   string      m_strAccelerator;
   string      m_strDescription;
   bool        m_bStockItem = false;
   
   application_menu();
   application_menu(const ::scoped_string & scopedstrName, popup_flag_t);
   application_menu(
      bool bStockItem,
      const ::scoped_string & scopedstrName,
      const ::atom & atom = {},
      const ::scoped_string & scopedstrAccelerator = {},
      const ::scoped_string & scopedstrDescription = {});


   virtual application_menu * insert_popup(const ::scoped_string & scopedstrName);
   virtual application_menu * defer_add_popup(const ::scoped_string & scopedstrName);
   virtual application_menu * _set_item_at_and_go_next(::collection::index & iIndex, bool bStockItem, const ::scoped_string & scopedstrName, const ::atom & atom = {}, const ::scoped_string & scopedstrMacosAccelerator = {}, const ::scoped_string & scopedstrDescription = {});
   virtual application_menu * add_item(bool bStockItem, const ::scoped_string & scopedstrName, const ::atom & atom = {}, const ::scoped_string & scopedstrMacosAccelerator = {}, const ::scoped_string & scopedstrDescription = {});
   virtual application_menu * insert_item(const ::scoped_string & scopedstrName, const ::atom & atom = {}, const ::scoped_string & scopedstrMacosAccelerator = {}, const ::scoped_string & scopedstrDescription = {});
   virtual application_menu * insert_stock_item(const ::scoped_string & scopedstrName, const ::atom & atom = {}, const ::scoped_string & scopedstrMacosAccelerator = {}, const ::scoped_string & scopedstrDescription = {});
   virtual application_menu * defer_add_item(const ::scoped_string & scopedstrName, const ::atom & atom = {}, const ::scoped_string & scopedstrMacosAccelerator = {}, const ::scoped_string & scopedstrDescription = {});
   virtual application_menu * add_stock_item(const ::scoped_string & scopedstrName, const ::atom & atom = {}, const ::scoped_string & scopedstrMacosAccelerator = {}, const ::scoped_string & scopedstrDescription = {});
   virtual application_menu * insert_separator();
   virtual application_menu * add_separator();

   
   ::collection::index find_child_with_name(const_char_pointer pszName) const;
   
   virtual bool is_popup() const;

   virtual bool is_separator() const;

   void destroy() override;

};


