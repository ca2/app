//
//  menu_shared.cpp
//  aura
//
//  Created by Camilo Sasuke Tsumanuma on 10/08/20.
//
#include "framework.h"
#include "menu_shared.h"


void free_c_string_array(char * const * ppszList, int iCount);
char * const * alloc_c_string_array(const string_array & stra);

 menu_shared::menu_shared()
{
   m_ppszParent = nullptr;
   m_ppszMenu = nullptr;
   m_ppszId = nullptr;
   m_ositema = nullptr;
   m_statusa = nullptr;
   m_iCount = 0;
}
 menu_shared::~menu_shared()
{
   free_c_string_array(m_ppszParent, m_iCount);
   free_c_string_array(m_ppszMenu, m_iCount);
   free_c_string_array(m_ppszId, m_iCount);
   delete []m_ositema;
   delete []m_statusa;

}


__pointer(menu_shared) create_menu_shared(const string_array & straParent, const string_array & straMenu, const string_array & straId)
{
   
   int iCount = (int) straParent.get_count();
   
   if(iCount <= 0
      || iCount != straMenu.get_size()
      || iCount != straId.get_size())
   {
      
      return nullptr;
      
   }
   
   __pointer(menu_shared) pmenushared = __new(menu_shared);
   
   pmenushared->m_iCount = iCount;
   pmenushared->m_ppszParent = alloc_c_string_array(straParent);
   pmenushared->m_ppszMenu = alloc_c_string_array(straMenu);
   pmenushared->m_ppszId = alloc_c_string_array(straId);
   pmenushared->m_ositema = new void *[iCount];
   pmenushared->m_statusa = new int[iCount];
   
   memset(pmenushared->m_ositema, 0, sizeof(void *) * iCount);
   memset(pmenushared->m_statusa, 0, sizeof(menu_shared::enum_status) * iCount);
   
   return pmenushared;
   
}


void * menu_shared::find_item(const char * pszParent, const char * pszId)
{

   for(int i = 0; i < m_iCount; i++)
   {

      if(!strcmp(pszParent, m_ppszParent[i]))
      {
         
         if(!strcmp(pszId, m_ppszId[i]))
         {
            
            return m_ositema[i];
            
         }
         
      }

   }
   
   return nullptr;

}


void menu_shared::on_idle_update()
{
   
   
   for(int i = 0; i < m_iCount; i++)
   {
      
      void * pitem = m_ositema[i];

      if(pitem)
      {
         
         bool bCheck = m_statusa[i] & status_checked;
         bool bSetCheck = m_statusa[i] & status_set_checked;
         
         if(is_different(bCheck, bSetCheck))
         {
            
            if(bCheck)
            {
               
               m_statusa[i] |= status_set_checked;
               
            }
            else
            {
             
               m_statusa[i] &= ~status_set_checked;
               
            }

            os_menu_item_check(pitem, bCheck);
            
         }

         bool bDisabled = m_statusa[i] & status_disabled;
         bool bSetDisabled = m_statusa[i] & status_set_disabled;
         
         if(is_different(bCheck, bSetDisabled))
         {
            
            if(bDisabled)
            {
               
               m_statusa[i] |= status_set_disabled;
               
            }
            else
            {
             
               m_statusa[i] &= ~status_set_disabled;
               
            }

            os_menu_item_enable(pitem, !bDisabled);
            
         }

         
      }

   }

}




class menu_shared_command :
   public ::user::command        // class private to this file !
{
public: // re-implementations only
   
   int * m_pestatus;

   menu_shared_command(int * pestatus):
   m_pestatus(pestatus)
   {
   }
   virtual void Enable(bool bOn = TRUE, const ::action_context & context = ::source_system)
   {
         if(bOn)
         {
            
            *m_pestatus &= ~menu_shared::status_disabled;
            
         }
         else
         {
            
            *m_pestatus |= menu_shared::status_disabled;
         
         }
      
   }
   //   virtual void _001SetCheck(bool bCheck, const ::action_context & context = ::source_system);   // 0, 1 or 2 (indeterminate)
   virtual void _001SetCheck(enum_check echeck, const ::action_context & context = ::source_system)   // 0, 1 or 2 (indeterminate)
   {
      
      if(echeck == check_checked)
      {
         
         *m_pestatus |= menu_shared::status_checked;

      }
      else
      {
         
         *m_pestatus &= ~menu_shared::status_checked;
      
      }
   }
//   virtual void SetRadio(bool bOn = TRUE, const ::action_context & context = ::source_system);
   //virtual void SetText(const char * pszText, const ::action_context & context = ::source_system);

};




void menu_shared_idle(::user::frame * pframe)
{
   
   menu_shared * pmenushared = pframe->m_pmenushared;
   
   if(::is_null(pmenushared))
   {
      
      return;
      
   }
   
   for(int i = 0; i < pmenushared->m_iCount; i++)
   {
      
      void * pitem = pmenushared->m_ositema[i];

      if(pitem)
      {
         
         ::message::id id(pmenushared->m_ppszId[i],::message::type_command_probe);
         
         menu_shared_command command(&pmenushared->m_statusa[i]);
         
         command.m_id = id;

         pframe->on_command_probe(&command);

      }

   }
   
   pmenushared->on_idle_update();

}
