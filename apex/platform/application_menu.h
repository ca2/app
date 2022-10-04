//
//  apex_application_menu.hpp
//  apex
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 13/11/18.
//
#pragma once


//namespace apex
//{


   class CLASS_DECL_APEX  application_menu_item
   {
   public:
      
      string m_strName;
      string m_strId;
      
      application_menu_item();
      application_menu_item(string strName, string strId);
      
   };


   class CLASS_DECL_APEX application_menu :
   public array < application_menu_item >
   {
   public:
      
      void add_item(index iIndex, string strName, string strId);
      
   };

//
//} // namespace apex




