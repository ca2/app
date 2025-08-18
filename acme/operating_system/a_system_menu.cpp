//
// Created by camilo on 9/18/24.
//
#include "framework.h"
#include "a_system_menu.h"


namespace operating_system
{


   a_system_menu_item::a_system_menu_item()
   {


   }


   a_system_menu_item::a_system_menu_item(const ::scoped_string & scopedstrName, const ::scoped_string & scopedstrAtom) :
      m_strName(scopedstrName),
      m_strAtom(scopedstrAtom)
   {

   }


   a_system_menu_item::~a_system_menu_item()
   {


   }


//   void a_system_menu_item::set_p(const ::scoped_string & scopedstrKey, void * p)
//   {
//
//      m_map[scopedstrKey]=p;
//
//   }
//
//
//   void * a_system_menu_item::get_p(const ::scoped_string & scopedstrKey)
//   {
//
//      return m_map[scopedstrKey];
//
//   }



   a_system_menu::a_system_menu()
   {

   }


   a_system_menu::~a_system_menu()
   {


   }


   void a_system_menu::add_item(const ::scoped_string & scopedstrName, const ::scoped_string & scopedstrAtom)
   {

      ::pointer_array < a_system_menu_item >::add_item(øallocate a_system_menu_item(scopedstrName, scopedstrAtom));

   }


   void a_system_menu::add_separator()
   {

      add_item("", "(separator)");

   }


} // operating_system