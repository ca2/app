#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "base/user/user/_user.h"
#endif


namespace user
{


   notify_icon_listener::notify_icon_listener()
   {

   }


   notify_icon_listener::~notify_icon_listener()
   {

   }


   void notify_icon_listener::OnNotifyIconMessage(UINT uiNotifyIcon, UINT message)
   {

      switch(message)
      {
      case WM_RBUTTONDOWN:

         OnNotifyIconContextMenu(uiNotifyIcon);

         break;

      case WM_LBUTTONDBLCLK:

         OnNotifyIconLButtonDblClk(uiNotifyIcon);

         break;

      case WM_LBUTTONDOWN:

         OnNotifyIconLButtonDown(uiNotifyIcon);

         break;

      }

   }


   void notify_icon_listener::OnNotifyIconContextMenu(UINT uiNotifyIcon)
   {

      UNREFERENCED_PARAMETER(uiNotifyIcon);

   }


   void notify_icon_listener::OnNotifyIconLButtonDblClk(UINT uiNotifyIcon)
   {

      UNREFERENCED_PARAMETER(uiNotifyIcon);

   }


   void notify_icon_listener::OnNotifyIconLButtonDown(UINT uiNotifyIcon)
   {

      UNREFERENCED_PARAMETER(uiNotifyIcon);

   }


   int notify_icon_listener::_get_notification_area_action_count()
   {

      return (int) m_notifyiconitema.get_count();

   }


   const char * notify_icon_listener::_get_notification_area_action_name(int iItem)
   {

      if (iItem < 0 || iItem >= m_notifyiconitema.get_count())
      {

         return nullptr;

      }

      auto & pitem = m_notifyiconitema[iItem];

      return pitem->m_strName.c_str();

   }


   const char * notify_icon_listener::_get_notification_area_action_id(int iItem)
   {

      if (iItem < 0 || iItem >= m_notifyiconitema.get_count())
      {

         return nullptr;

      }

      auto & pitem = m_notifyiconitema[iItem];

      return pitem->m_strId.c_str();

   }


   const char * notify_icon_listener::_get_notification_area_action_label(int iItem)
   {

      if (iItem < 0 || iItem >= m_notifyiconitema.get_count())
      {

         return nullptr;

      }

      auto & pitem = m_notifyiconitema[iItem];

      return pitem->m_strLabel.c_str();

   }


   const char * notify_icon_listener::_get_notification_area_action_accelerator(int iItem)
   {

      if (iItem < 0 || iItem >= m_notifyiconitema.get_count())
      {

         return nullptr;

      }

      auto & pitem = m_notifyiconitema[iItem];

      return pitem->m_strAccelerator.c_str();

   }


   const char * notify_icon_listener::_get_notification_area_action_description(int iItem)
   {

      if (iItem < 0 || iItem >= m_notifyiconitema.get_count())
      {

         return nullptr;

      }

      auto & pitem = m_notifyiconitema[iItem];

      return pitem->m_strDescription.c_str();

   }


   void notify_icon_listener::call_notification_area_action(const char * pszId)
   {

   }

   notify_icon_listener::item::item()
   {

   }

   notify_icon_listener::item::item(string strName, string strId, string strLabel, string strAccelerator, string strDescription)
   {

      m_strName = strName.if_empty(m_strId);

      m_strId = strId.if_empty(m_strName);

      m_strLabel = strLabel.if_empty(m_strId);

      m_strAccelerator = strAccelerator.if_empty(m_strId);

      m_strDescription = strDescription.if_empty(m_strName);

   }


   notify_icon_listener::item:: ~item()
   {

   }


   bool notify_icon_listener::notify_icon_insert_item(index & iIndex, string strName, string strId, string strLabel, string strAccelerator, string strDescription)
   {

      if (iIndex < 0 || iIndex > m_notifyiconitema.get_count())
      {

         return false;

      }


      for(auto & pitem : m_notifyiconitema)
      {

         if(pitem->m_strId == "separator")
         {


         }
         else if(pitem->m_strId == strId)
         {

            // Don't add item with duplicated id
            return false;

         }

      }

      if(strId == "separator")
      {

         if(iIndex > 0)
         {

            if(m_notifyiconitema[iIndex - 1]->m_strId == "separator")
            {

               // Don't add consecutive <separator>

               return false;

            }

         }

         if(iIndex < m_notifyiconitema.get_upper_bound())
         {

            if(m_notifyiconitema[iIndex + 1]->m_strId == "separator")
            {

               // Don't add consecutive <separator>

               return false;

            }

         }


      }

      auto pitem = __new(item(strName, strId, strLabel, strAccelerator, strDescription));

      m_notifyiconitema.insert_at(iIndex, pitem);

      iIndex++;

      return true;

   }


} // namespace user



