//
//  menu_shared.hpp
//  aura
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 10/08/20.
//
#pragma once

class menu_shared :
   virtual public matter
{
public:
   
   enum enum_status
   {
      status_none = 0,
      status_checked = 1<<0,
      status_disabled = 1<<1,
      status_set_checked = 1<<8,
      status_set_disabled = 1<<9,
   };
   
   char_pointer const * m_ppszParent;
   char_pointer const * m_ppszMenu;
   char_pointer const * m_ppszId;
   void ** m_ositema;
   ::i32 * m_statusa;
   ::i32 m_iCount;
  
   menu_shared();
   virtual ~menu_shared();
   
   
   void * find_item(const ::scoped_string & scopedstrParent, const ::scoped_string & scopedstrId);
   
   void on_idle_update();
   
};


void os_menu_item_enable(void * pitem, bool bEnable);
void os_menu_item_check(void * pitem, bool bCheck);



