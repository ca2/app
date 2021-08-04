//
//  menu_shared.hpp
//  aura
//
//  Created by Camilo Sasuke Tsumanuma on 10/08/20.
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
   
   char * const * m_ppszParent;
   char * const * m_ppszMenu;
   char * const * m_ppszId;
   void ** m_ositema;
   int * m_statusa;
   int m_iCount;
  
   menu_shared();
   virtual ~menu_shared();
   
   
   void * find_item(const ::string & pszParent, const ::string & pszId);
   
   void on_idle_update();
   
};


void os_menu_item_enable(void * pitem, bool bEnable);
void os_menu_item_check(void * pitem, bool bCheck);



