//
//  menu_shared.hpp
//  aura
//
//  Created by Camilo Sasuke Tsumanuma on 10/08/20.
//
#pragma once


class CLASS_DECL_APEX menu_shared :
   virtual public ::matter
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
   

   char * const *       m_ppszParent;
   char * const *       m_ppszMenu;
   char * const *       m_ppszId;
   void **              m_ositema;
   int  *               m_statusa;
   int                  m_iCount;
  

   menu_shared();
   virtual ~menu_shared();
   
   
   void * find_item(const char * pszParent, const char * pszId);
   
   void on_idle_update();
   

};




