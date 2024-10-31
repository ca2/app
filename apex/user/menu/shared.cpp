//
//  menu_shared.cpp
//  aura
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 10/08/20.
//
/// Refactoring (from application_menu and menu_shared) by
/// camilo on 2023-10-26 00:21 <3ThomasBorregaardSorensen
#include "framework.h"
//#include "shared.h"
//#include "acme/platform/system.h"
//#include "aura/platform/session.h"
//#include "aura/user/user/user.h"
//#include "aura/windowing/windowing.h"
//
//
//void free_c_string_array(char * const * ppszList, int iCount);
//char * const * alloc_c_string_array(const string_array & stra);
//
//
//menu_shared::menu_shared()
//{
//   
//   m_ppszParent = nullptr;
//   m_ppszMenu = nullptr;
//   m_ppszId = nullptr;
//   m_ositema = nullptr;
//   m_statusa = nullptr;
//   m_iCount = 0;
//   
//}
//
//
//menu_shared::~menu_shared()
//{
//   
//   free_c_string_array(m_ppszParent, m_iCount);
//   free_c_string_array(m_ppszMenu, m_iCount);
//   free_c_string_array(m_ppszId, m_iCount);
//   delete []m_ositema;
//   delete []m_statusa;
//
//}
//
//
//::pointer<menu_shared>create_menu_shared(::particle * pparticle, const string_array & straParent, const string_array & straMenu, const string_array & straId)
//{
//
//   int iCount = (int) straParent.get_count();
//
//   auto pmenushared = pparticle->__create_new < menu_shared >();
//
//   pmenushared->m_iCount = iCount;
//   pmenushared->m_ppszParent = alloc_c_string_array(straParent);
//   pmenushared->m_ppszMenu = alloc_c_string_array(straMenu);
//   pmenushared->m_ppszId = alloc_c_string_array(straId);
//   pmenushared->m_ositema = ___new void *[iCount];
//   pmenushared->m_statusa = ___new int[iCount];
//
//   memory_set(pmenushared->m_ositema, 0, sizeof(void *) * iCount);
//   memory_set(pmenushared->m_statusa, 0, sizeof(menu_shared::enum_status) * iCount);
//
//   return pmenushared;
//
//}
//
//
//void * menu_shared::find_item(const ::scoped_string & scopedstrParent, const ::scoped_string & scopedstrId)
//{
//
//   for(int i = 0; i < m_iCount; i++)
//   {
//
//      if(!ansi_cmp(scopedstrParent, m_ppszParent[i]))
//      {
//
//         if(!ansi_cmp(scopedstrId, m_ppszId[i]))
//         {
//
//            return m_ositema[i];
//
//         }
//
//      }
//
//   }
//
//   return nullptr;
//
//}
//
//
//void menu_shared::on_idle_update()
//{
//
//   auto psession = session();
//   
//   auto puser = user();
//   
//   auto pwindowing = system()->windowing();
//   
//   for(int i = 0; i < m_iCount; i++)
//   {
//
//      void * pitem = m_ositema[i];
//
//      if(pitem)
//      {
//
//         bool bCheck = m_statusa[i] & status_checked;
//         bool bSetCheck = m_statusa[i] & status_set_checked;
//
//         if(is_different(bCheck, bSetCheck))
//         {
//
//            if(bCheck)
//            {
//
//               m_statusa[i] |= status_set_checked;
//
//            }
//            else
//            {
//
//               m_statusa[i] &= ~status_set_checked;
//
//            }
//            
//            pwindowing->os_menu_item_check(pitem, bCheck);
//
//            //os_menu_item_check(pitem, bCheck);
//
//         }
//
//         bool bDisabled = m_statusa[i] & status_disabled;
//         bool bSetDisabled = m_statusa[i] & status_set_disabled;
//
//         if(is_different(bCheck, bSetDisabled))
//         {
//
//            if(bDisabled)
//            {
//
//               m_statusa[i] |= status_set_disabled;
//
//            }
//            else
//            {
//
//               m_statusa[i] &= ~status_set_disabled;
//
//            }
//            
//            pwindowing->os_menu_item_enable(pitem, !bDisabled);
//
//            //os_menu_item_enable(pitem, !bDisabled);
//
//         }
//
//      }
//
//   }
//
//}
//
//
//void menu_shared_increment_reference_count(menu_shared * pmenushared)
//{
//   
//   pmenushared->increment_reference_count();
//   
//}
//
//
//void menu_shared_release(menu_shared * pmenushared)
//{
//   
//   ::release(pmenushared);
//   
//}
//
//
//::string menu_shared::application_name()
//{
//   
//   return application()->get_application_name();
//   
//}
//
//
//
//
