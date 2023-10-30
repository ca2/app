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


//namespace user
//{


   class CLASS_DECL_APEX application_menu :
      public ::pointer_array < application_menu >
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
      string      m_strId;
      string      m_strLabel;
      string      m_strAccelerator;
      string      m_strDescription;
      bool        m_bStockItem = false;
      
      application_menu();
      application_menu(string strName, popup_flag_t);
      application_menu(bool bStockItem, string strName, string strId="", string strMacosAccelerator="", string strDescription="");


      virtual application_menu * popup_at(::index & iIndex, string strName);
      virtual application_menu * popup(string strName);
      virtual application_menu * _item_at(::index & iIndex, bool bStockItem, string strName, string strId = "", string strMacosAccelerator = "", string strDescription = "");
      virtual application_menu * _item(bool bStockItem, string strName, string strId = "", string strMacosAccelerator = "", string strDescription = "");
      virtual application_menu * item_at(::index & iIndex, string strName, string strId = "", string strMacosAccelerator = "", string strDescription = "");
      virtual application_menu * stock_item_at(::index & iIndex, string strName, string strId = "", string strMacosAccelerator = "", string strDescription = "");
      virtual application_menu * item(string strName, string strId = "", string strMacosAccelerator = "", string strDescription = "");
      virtual application_menu * stock_item(string strName, string strId = "", string strMacosAccelerator = "", string strDescription = "");
      virtual application_menu * separator_at(::index & iIndex);
      virtual application_menu * separator();

      
      ::index find_child_with_name(const char * pszName) const;
      
      bool is_popup() const
      {
         
         return this->has_elements() || m_bPopup;
         
      }
      
      bool is_separator() const
      {

         return this->m_strId == "separator";

      }

   };


//   class CLASS_DECL_APEX application_menu :
//      public array < application_menu_item >
//   {
//   public:
//      
//
//      void add_item(index iIndex, string strName, string strId, string strMacosAccelerator, string strDescription);
//
//      
//   };

//
//} // namespace user




