#include "framework.h"
//#include "metrowin_window_impl.h"
//#include "base/user/user.h"




namespace user
{

   class interaction_impl;

} // namespace user


class oswindow_dataptra :
   public comparable_raw_array < oswindow_data * >
{
public:


};

oswindow_dataptra * g_oswindow_dataptra()
{
   static oswindow_dataptra * s_pdataptra = new oswindow_dataptra;

   return s_pdataptra;
}


::user::interaction_impl * oswindow_data::window()
{

   if(this == NULL)
      return NULL;

   return m_pimpl;

}


index oswindow_find(::user::interaction_impl * pimpl)
{

   for(int i = 0; i < g_oswindow_dataptra()->get_count(); i++)
   {

      if(g_oswindow_dataptra()->element_at(i)->m_pimpl == pimpl)
      {

         return i;

      }

   }

   return -1;

}


oswindow oswindow_get(::user::interaction_impl * pimpl)
{

   iptr iFind = oswindow_find(pimpl);

   if(iFind >= 0)
      return g_oswindow_dataptra()->element_at(iFind);

   oswindow pdata  = new oswindow_data;

   pdata->m_pimpl = pimpl;

   g_oswindow_dataptra()->add(pdata);

   return pdata;

}




//int_bool oswindow_remove(::user::interaction_impl * pinteraction)
//{
//
//   iptr iFind = oswindow_find(pinteraction);
//
//   if(iFind < 0)
//      return false;
//
//   g_oswindow_dataptra()->remove_at(iFind);
//
//   return true;
//
//}



Agile < Windows::UI::Core::CoreWindow > get_os_window(oswindow window)
{

   return window->m_pimpl->m_puserinteraction->get_os_window();

}


static oswindow g_oswindowFocus;


oswindow WINAPI WinGetFocus()
{

   return g_oswindowFocus;

}

oswindow WINAPI WinSetFocus(oswindow __oswindow)
{

   ::oswindow oswindowOldFocus = g_oswindowFocus;

   g_oswindowFocus = __oswindow;

   // todo
   //SendMessage(__oswindow, WM_SETFOCUS, WPARAM, (LPARAM) (void *) oswindowOldFocus)
   //SendMessage(oswindowOldFocus, WM_KILLFOCUS, WPARAM, (LPARAM) (void *) __oswindow)

   return oswindowOldFocus;

}



static oswindow g_oswindowCapture;


oswindow WINAPI get_capture()
{

   return g_oswindowCapture;

}

oswindow WINAPI set_capture(oswindow __oswindow)
{

   ::oswindow oswindowOldCapture = g_oswindowCapture;

   g_oswindowCapture = __oswindow;

   // todo
   //SendMessage(__oswindow, WM_SETFOCUS, WPARAM, (LPARAM) (void *) oswindowOldFocus)
   //SendMessage(oswindowOldFocus, WM_KILLFOCUS, WPARAM, (LPARAM) (void *) __oswindow)

   return oswindowOldCapture;

}


oswindow WINAPI WinReleaseCapture()
{

   ::oswindow oswindowOldCapture = g_oswindowCapture;

   g_oswindowCapture = NULL;

   // todo
   //SendMessage(__oswindow, WM_SETFOCUS, WPARAM, (LPARAM) (void *) oswindowOldFocus)
   //SendMessage(oswindowOldFocus, WM_KILLFOCUS, WPARAM, (LPARAM) (void *) __oswindow)

   return oswindowOldCapture;

}


static oswindow g_oswindowActive;


oswindow WINAPI WinGetActiveWindow()
{

   return g_oswindowActive;

}

oswindow WINAPI WinSetActiveWindow(oswindow __oswindow)
{

   ::oswindow oswindowOldActive = g_oswindowActive;

   g_oswindowActive = __oswindow;

   // todo
   //SendMessage(__oswindow, WM_SETFOCUS, WPARAM, (LPARAM) (void *) oswindowOldFocus)
   //SendMessage(oswindowOldFocus, WM_KILLFOCUS, WPARAM, (LPARAM) (void *) __oswindow)

   return oswindowOldActive;

}



oswindow_data * WINAPI GetParent(oswindow_data * pdata)
{

   if(pdata == NULL)
      return NULL;

   if(!::WinIsWindow(pdata))
      return NULL;

   return (oswindow_data *) pdata->m_pimpl->m_puserinteraction->GetParent()->get_os_data();


}



WINBOOL WinIsWindow(oswindow oswindow)
{

   if(((void *)oswindow) == NULL)
      return FALSE;

   return TRUE;

}

int DestroyWindow(oswindow oswindow)
{

   return TRUE;

}



CLASS_DECL_BASE ::user::interaction * oswindow_interaction(oswindow oswindow)
{

   if (is_ptr_null(oswindow, sizeof(*oswindow)))
   {

      return NULL;

   }

   if (is_ptr_null(oswindow->m_pimpl, sizeof(*oswindow->m_pimpl)))
   {

      return NULL;

   }

   return oswindow->m_pimpl->m_puserinteraction;

}