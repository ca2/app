//
//  apex_application_menu.hpp
//  apex
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 13/11/18.
//
/// Refactoring (from application_menu and menu_shared) by
/// camilo on 2023-10-26 00:22 <3ThomasBorregaardSorensen
#pragma once


namespace apex
{


   class CLASS_DECL_APEX menu :
      public ::pointer_array < menu >
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
      
      
      string m_strName;
      string m_strId;
      string m_strMacosAccelerator;
      string m_strDescription;
      
      menu();
      menu(string strName, string strId="", string strMacosAccelerator="", string strDescription="");

      
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
} // namespace apex




