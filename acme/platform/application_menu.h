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

#include "acme/constant/id.h"

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


   virtual application_menu * popup_at(::collection::index & iIndex, const ::scoped_string & scopedstrName);
   virtual application_menu * popup(const ::scoped_string & scopedstrName);
   virtual application_menu * _item_at(::collection::index & iIndex, bool bStockItem, const ::scoped_string & scopedstrName, const ::atom & atom = {}, const ::scoped_string & scopedstrMacosAccelerator = {}, const ::scoped_string & scopedstrDescription = {});
   virtual application_menu * _item(bool bStockItem, const ::scoped_string & scopedstrName, const ::atom & atom = {}, const ::scoped_string & scopedstrMacosAccelerator = {}, const ::scoped_string & scopedstrDescription = {});
   virtual application_menu * item_at(::collection::index & iIndex, const ::scoped_string & scopedstrName, const ::atom & atom = {}, const ::scoped_string & scopedstrMacosAccelerator = {}, const ::scoped_string & scopedstrDescription = {});
   virtual application_menu * stock_item_at(::collection::index & iIndex, const ::scoped_string & scopedstrName, const ::atom & atom = {}, const ::scoped_string & scopedstrMacosAccelerator = {}, const ::scoped_string & scopedstrDescription = {});
   virtual application_menu * item(const ::scoped_string & scopedstrName, const ::atom & atom = {}, const ::scoped_string & scopedstrMacosAccelerator = {}, const ::scoped_string & scopedstrDescription = {});
   virtual application_menu * stock_item(const ::scoped_string & scopedstrName, const ::atom & atom = {}, const ::scoped_string & scopedstrMacosAccelerator = {}, const ::scoped_string & scopedstrDescription = {});
   virtual application_menu * separator_at(::collection::index & iIndex);
   virtual application_menu * separator();

   
   ::collection::index find_child_with_name(const_char_pointer pszName) const;
   
   bool is_popup() const
   {
      
      return this->has_elements() || m_bPopup;
      
   }
   
   bool is_separator() const
   {

      return this->m_atomMenu == id_separator;

   }

   void destroy() override;

};


