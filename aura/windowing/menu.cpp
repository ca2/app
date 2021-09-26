//
//  menu.cpp
//  aura
//
//  Created by Camilo Sasuke Tsumanuma on 10/08/20.
//
#include "framework.h"
#include "aura/user/_menu.h"


namespace windowing
{


   //void free_c_string_array(char * const * ppszList, int iCount);
   //char * const * alloc_c_string_array(const string_array & stra);

   menu::menu()
   {

   }


   menu::~menu()
   {

      //free_c_string_array(m_ppszParent, m_iCount);
      //free_c_string_array(m_ppszMenu, m_iCount);
      //free_c_string_array(m_ppszId, m_iCount);

      //delete[]m_ositema;
      //delete[]m_statusa;

   }


   __pointer(menu) create_menu_shared(::object * pobject, const string_array & straParent, const string_array & straMenu, const string_array & straId)
   {

      int iCount = (int)straParent.get_count();

      if (iCount <= 0
         || iCount != straMenu.get_size()
         || iCount != straId.get_size())
      {

         return nullptr;

      }

      auto pmenu = pobject->__create < menu >();

      for (int i = 0; i < straParent.get_count(); i++)
      {

         auto pitem = pobject->__create < menu_item >();

         pitem->m_strParent = straParent[i];
         pitem->m_strMenu = straMenu[i];
         pitem->m_id = straId[i];

         pmenu->m_itema.add(pitem);

      }

      //pmenushared->m_iCount = iCount;
      //pmenushared->m_ppszParent = alloc_c_string_array(straParent);
      //pmenushared->m_ppszMenu = alloc_c_string_array(straMenu);
      //pmenushared->m_ppszId = alloc_c_string_array(straId);
      //pmenushared->m_ositema = new void * [iCount];
      //pmenushared->m_statusa = new int[iCount];

      //memset(pmenushared->m_ositema, 0, sizeof(void *) * iCount);
      //memset(pmenushared->m_statusa, 0, sizeof(menu::enum_status) * iCount);

      return pmenu;

   }


   menu_item * menu::find_item(const ::string & pszParent, const ::string & pszId)
   {

      for (int i = 0; i < m_itema.get_count(); i++)
      {

         auto pitem = m_itema[i];

         if (!strcmp(pszParent, pitem->m_strParent))
         {

            if (!strcmp(pszId, pitem->m_id.to_string()))
            {

               return pitem;

            }

         }

      }

      return nullptr;

   }


   void menu::on_idle_update()
   {

      for (int i = 0; i < m_itema.get_count(); i++)
      {

         auto pitem = m_itema[i];

         if (pitem)
         {

            bool bCheck = pitem->is_checked();

            bool bSetCheck = pitem->should_set_checked();

            if (is_different(bCheck, bSetCheck))
            {

               if (bCheck)
               {

                  pitem->add_status(e_status_set_checked);

               }
               else
               {

                  pitem->erase_status(e_status_set_checked);

               }

               //os_menu_item_check(pitem, bCheck);

            }

            bool bDisabled = pitem->is_disabled();

            bool bSetDisabled = pitem->should_set_disabled();

            if (is_different(bCheck, bSetDisabled))
            {

               if (bDisabled)
               {

                  pitem->add_status(e_status_set_disabled);

               }
               else
               {

                  pitem->erase_status(e_status_set_disabled);

               }

               //os_menu_item_enable(pitem, !bDisabled);

            }

         }

      }

   }


   void menu::on_idle(::channel * pchannel)
{
//      void menu_shared_idle(::user::frame * pframe)
//      {
//
//         auto pmenushared = pframe->m_pmenushared;
//
//         if(::is_null(pmenushared))
//         {
//
//            return;
//
//         }

         for(int i = 0; i < m_itema.get_count(); i++)
         {

            auto pitem = m_itema[i];

            if(pitem)
            {

               ::id id(::id::e_type_command_probe, pitem->m_id);

               menu_command command(pitem);

               command.m_id = id;

               pchannel->on_command_probe(&command);

            }

         }

         on_idle_update();

      }

   //}

} // namespace windowing



