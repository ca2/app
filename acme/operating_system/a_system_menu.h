//
// Created by camilo on 2024-09-18 05:07 <3ThomasBorregaardSorensen!!
//
#pragma once


namespace operating_system
{

   class a_system_menu;


   class CLASS_DECL_ACME a_system_menu_item :
      virtual public ::particle
   {
   public:


      ::string    m_strName;
      ::string    m_strAtom;
      union {
         void * m_pWindowingImplWindow;
      };
      union {
         void * m_pWidgetImpl;
      };


      a_system_menu_item();
      a_system_menu_item(const ::scoped_string & scopedstrName, const ::scoped_string & scopedstrAtom);
      ~a_system_menu_item() override;


   };


   class CLASS_DECL_ACME a_system_menu :
      virtual public ::pointer_array < a_system_menu_item >
   {
   public:

      a_system_menu();
      ~a_system_menu() override;
      void add_item(const ::scoped_string & scopedstrName, const ::scoped_string & scopedstrAtom);
      void add_separator();

   };


} // operating_system


