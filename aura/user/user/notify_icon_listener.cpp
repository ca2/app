#include "framework.h"

#include "notify_icon_listener.h"


namespace user
{


   notify_icon_listener::notify_icon_listener()
   {

   }


   notify_icon_listener::~notify_icon_listener()
   {

   }


   //void notify_icon_listener::OnNotifyIconMessage(unsigned int uNotifyIcon, unsigned int message)
   //{

   //   switch(message)
   //   {
   //   case ::user::e_message_right_button_down:

   //      OnNotifyIconContextMenu(uNotifyIcon);

   //      break;

   //   case ::user::e_message_left_button_double_click:

   //      OnNotifyIconLButtonDblClk(uNotifyIcon);

   //      break;

   //   case ::user::e_message_left_button_down:

   //      OnNotifyIconLButtonDown(uNotifyIcon);

   //      break;

   //   }

   //}


   //void notify_icon_listener::OnNotifyIconContextMenu(unsigned int uNotifyIcon)
   //{

   //   __UNREFERENCED_PARAMETER(uNotifyIcon);

   //}


   //void notify_icon_listener::OnNotifyIconLButtonDblClk(unsigned int uNotifyIcon)
   //{

   //   __UNREFERENCED_PARAMETER(uNotifyIcon);

   //}


   //void notify_icon_listener::OnNotifyIconLButtonDown(unsigned int uNotifyIcon)
   //{

   //   __UNREFERENCED_PARAMETER(uNotifyIcon);

   //}


   //int notify_icon_listener::_get_notification_area_action_count()
   //{

   //   return (int) m_notifyiconitema.get_count();

   //}


   //const_char_pointer notify_icon_listener::_get_notification_area_action_name(int iItem)
   //{

   //   if (iItem < 0 || iItem >= m_notifyiconitema.get_count())
   //   {

   //      return nullptr;

   //   }

   //   auto & pitem = m_notifyiconitema[iItem];

   //   return pitem->m_strName.c_str();

   //}


   //const_char_pointer notify_icon_listener::_get_notification_area_action_id(int iItem)
   //{

   //   if (iItem < 0 || iItem >= m_notifyiconitema.get_count())
   //   {

   //      return nullptr;

   //   }

   //   auto & pitem = m_notifyiconitema[iItem];

   //   return pitem->m_strId.c_str();

   //}


   //const_char_pointer notify_icon_listener::_get_notification_area_action_label(int iItem)
   //{

   //   if (iItem < 0 || iItem >= m_notifyiconitema.get_count())
   //   {

   //      return nullptr;

   //   }

   //   auto & pitem = m_notifyiconitema[iItem];

   //   return pitem->m_strLabel.c_str();

   //}


   //const_char_pointer notify_icon_listener::_get_notification_area_action_accelerator(int iItem)
   //{

   //   if (iItem < 0 || iItem >= m_notifyiconitema.get_count())
   //   {

   //      return nullptr;

   //   }

   //   auto & pitem = m_notifyiconitema[iItem];

   //   return pitem->m_strAccelerator.c_str();

   //}


   //const_char_pointer notify_icon_listener::_get_notification_area_action_description(int iItem)
   //{

   //   if (iItem < 0 || iItem >= m_notifyiconitema.get_count())
   //   {

   //      return nullptr;

   //   }

   //   auto & pitem = m_notifyiconitema[iItem];

   //   return pitem->m_strDescription.c_str();

   //}


   ::application_menu * notify_icon_listener::menu()
   {

      ødefer_construct_new(m_papplicationmenu);

      return m_papplicationmenu;

   }


   bool notify_icon_listener::handle_command(const ::atom &atom, ::user::activation_token * puseractivationtoken)
   {

      return false;

   }


   //notify_icon_listener::item::item()
   //{

   //}

   //notify_icon_listener::item::item(const ::scoped_string & scopedstrName, const ::scoped_string & scopedstrId, const ::scoped_string & scopedstrLabel, const ::scoped_string & scopedstrAccelerator, const ::scoped_string & scopedstrDescription)
   //{

   //   m_strName = strName.if_empty(m_strId);

   //   m_strId = strId.if_empty(m_strName);

   //   m_strLabel = strLabel.if_empty(m_strId);

   //   m_strAccelerator = strAccelerator.if_empty(m_strId);

   //   m_strDescription = strDescription.if_empty(m_strName);

   //}


   //notify_icon_listener::item:: ~item()
   //{

   //}


   //bool notify_icon_listener::notify_icon_insert_item(bool bStockItem, ::collection::index & iIndex, const ::scoped_string & scopedstrName, const ::scoped_string & scopedstrId, const ::scoped_string & scopedstrLabel, const ::scoped_string & scopedstrAccelerator, const ::scoped_string & scopedstrDescription)
   //{

   //   if (iIndex < 0 || iIndex > m_notifyiconitema.get_count())
   //   {

   //      return false;

   //   }


   //   for(auto & pitem : m_notifyiconitema)
   //   {

   //      if(pitem->m_strId == "separator")
   //      {


   //      }
   //      else if(pitem->m_strId == strId)
   //      {

   //         // Don't add item with duplicated atom
   //         return false;

   //      }

   //   }

   //   if(strId == "separator")
   //   {

   //      if(iIndex > 0)
   //      {

   //         if(m_notifyiconitema[iIndex - 1]->m_strId == "separator")
   //         {

   //            // Don't add consecutive <separator>

   //            return false;

   //         }

   //      }

   //      if(iIndex < m_notifyiconitema.get_upper_bound())
   //      {

   //         if(m_notifyiconitema[iIndex]->m_strId == "separator")
   //         {

   //            // Don't add consecutive <separator>

   //            return false;

   //         }

   //      }


   //   }

   //   auto pitem = øallocate item(strName, strId, strLabel, strAccelerator, strDescription);

   //   pitem->m_bStockItem = bStockItem;

   //   m_notifyiconitema.insert_at(iIndex, pitem);

   //   iIndex++;

   //   return true;

   //}


} // namespace user



