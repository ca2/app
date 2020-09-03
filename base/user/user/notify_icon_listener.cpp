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


   bool notify_icon_listener::_get_notification_area_action_info(char ** ppszName, char ** ppszId, char ** ppszLabel, char ** ppszAccelerator, char ** ppszDescription, int iItem)
   {

      if (iItem < 0 || iItem >= m_notifyiconitema.get_count())
      {

         return false;

      }

      auto & item = m_notifyiconitema[iItem];

      *ppszName = strdup(item->m_strName);
      *ppszId = strdup(item->m_strId);
      *ppszLabel = strdup(item->m_strLabel);
      *ppszAccelerator = strdup(item->m_strAccelerator);
      *ppszDescription = strdup(item->m_strDescription);

      return true;

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


   bool notify_icon_listener::notify_icon_insert_item(index iIndex, string strName, string strId, string strLabel, string strAccelerator, string strDescription)
   {

      if (iIndex < 0 || iIndex > m_notifyiconitema.get_count())
      {

         return false;

      }

      auto pitem = __new(item(strName, strId, strLabel, strAccelerator, strDescription));

      m_notifyiconitema.insert_at(iIndex, pitem);

      return true;

   }


} // namespace user



