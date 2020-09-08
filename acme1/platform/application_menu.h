//
//  ace_application_menu.hpp
//  acme
//
//  Created by Camilo Sasuke Tsumanuma on 13/11/18.
//
#pragma once


namespace acme
{

   class CLASS_DECL_ACME  application_menu_item
   {
   public:
      
      string m_strName;
      string m_strId;
      
      application_menu_item();
      application_menu_item(string strName, string strId);
      
   };


   class CLASS_DECL_ACME application_menu :
   public array < application_menu_item >
   {
   public:
      
      void add_item(index iIndex, string strName, string strId);
      
   };


} // namespace acme




