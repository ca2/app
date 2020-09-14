#include "framework.h"
#include "_uwp.h"
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

   if (this == nullptr)
      return nullptr;

   return m_pimpl;

}


index oswindow_find(::user::interaction_impl * pimpl)
{

   for (int i = 0; i < g_oswindow_dataptra()->get_count(); i++)
   {

      if (g_oswindow_dataptra()->element_at(i)->m_pimpl == pimpl)
      {

         return i;

      }

   }

   return -1;

}


oswindow_data::oswindow_data(::user::interaction_impl * pimpl)
{
   m_plongptrmap = new int_ptr_to_int_ptr();
   m_pimpl = pimpl;

}

oswindow_data::~oswindow_data()
{

   ::acme::del(m_plongptrmap);

}

bool oswindow_data::is_child(::oswindow oswindow)
{

   if (oswindow == nullptr || oswindow->m_pimpl == nullptr || oswindow->m_pimpl->m_puserinteraction == nullptr)
   {

      return false;

   }

   if (m_pimpl == nullptr || m_pimpl->m_puserinteraction == nullptr)
   {

      return false;

   }

   return m_pimpl->m_puserinteraction->is_child(oswindow->m_pimpl->m_puserinteraction);

}


::oswindow oswindow_data::get_parent()
{

   if (m_pimpl == nullptr || m_pimpl->m_puserinteraction == nullptr)
   {

      return nullptr;

   }

   ::user::interaction * pinteraction = m_pimpl->m_puserinteraction->GetParent();

   if (pinteraction == nullptr)
   {

      return nullptr;

   }

   return pinteraction->get_safe_handle();

}


::oswindow oswindow_data::set_parent(::oswindow oswindow)
{

   if (m_pimpl == nullptr || m_pimpl->m_puserinteraction == nullptr)
   {

      return nullptr;

   }

   ::user::interaction * pinteraction;

   if (oswindow == nullptr || oswindow->m_pimpl == nullptr || oswindow->m_pimpl->m_puserinteraction == nullptr)
   {

      pinteraction = m_pimpl->m_puserinteraction->SetParent(nullptr);

   }
   else
   {

      pinteraction = m_pimpl->m_puserinteraction->SetParent(oswindow->m_pimpl->m_puserinteraction);

   }

   return pinteraction->get_safe_handle();

}


bool oswindow_data::show_window(int nCmdShow)
{

   if (m_pimpl == nullptr || m_pimpl->m_puserinteraction == nullptr)
   {

      return false;

   }

   return m_pimpl->m_puserinteraction->display(nCmdShow);

}


LONG_PTR oswindow_data::get_window_long_ptr(int nIndex)
{

   if (m_pimpl == nullptr || m_pimpl->m_puserinteraction == nullptr)
   {

      return 0;

   }

   return m_pimpl->m_puserinteraction->get_window_long_ptr(nIndex);

}


LONG_PTR oswindow_data::set_window_long_ptr(int nIndex, LONG_PTR l)
{
   if (m_pimpl == nullptr || m_pimpl->m_puserinteraction == nullptr)
   {

      return 0;

   }
   return m_pimpl->m_puserinteraction->set_window_long_ptr(nIndex, l);
}


bool oswindow_data::_001ClientToScreen(LPPOINT lppoint)
{
   if (m_pimpl == nullptr || m_pimpl->m_puserinteraction == nullptr)
   {

      return false;

   }

   m_pimpl->m_puserinteraction->_001ClientToScreen(lppoint);
   return true;
}

bool oswindow_data::_001ScreenToClient(LPPOINT lppoint)
{
   if (m_pimpl == nullptr || m_pimpl->m_puserinteraction == nullptr)
   {

      return false;

   }

   m_pimpl->m_puserinteraction->_001ScreenToClient(lppoint);
   return true;
}

bool oswindow_data::is_iconic()
{
   if (m_pimpl == nullptr || m_pimpl->m_puserinteraction == nullptr)
   {

      return false;

   }

   return m_pimpl->m_puserinteraction->layout().is_iconic();
}

bool  oswindow_data::is_window_visible()
{
   if (m_pimpl == nullptr || m_pimpl->m_puserinteraction == nullptr)
   {

      return false;

   }

   return m_pimpl->m_puserinteraction->is_window_visible();
}

oswindow oswindow_get(::user::interaction_impl * pimpl)
{

   iptr iFind = oswindow_find(pimpl);

   if (iFind >= 0)
      return g_oswindow_dataptra()->element_at(iFind);

   oswindow pdata = new oswindow_data;

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



Agile < Windows::UI::Core::CoreWindow > oswindow_core_window(oswindow window)
{

   return window->m_pimpl->m_puserinteraction->get_os_window();

}


//static oswindow g_oswindowFocus;
//
//
//oswindow WINAPI WinGetFocus()
//{
//
//   return g_oswindowFocus;
//
//}
//
//oswindow WINAPI WinSetFocus(oswindow __oswindow)
//{
//
//   ::oswindow oswindowOldFocus = g_oswindowFocus;
//
//   g_oswindowFocus = __oswindow;
//
//   // todo
//   //SendMessage(__oswindow, WM_SETFOCUS, WPARAM, (LPARAM) (void *) oswindowOldFocus)
//   //SendMessage(oswindowOldFocus, WM_KILLFOCUS, WPARAM, (LPARAM) (void *) __oswindow)
//
//   return oswindowOldFocus;
//
//}



static oswindow g_oswindowCapture;


oswindow get_capture()
{

   return g_oswindowCapture;

}

oswindow set_capture(oswindow __oswindow)
{

   ::oswindow oswindowOldCapture = g_oswindowCapture;

   g_oswindowCapture = __oswindow;

   // todo
   //SendMessage(__oswindow, WM_SETFOCUS, WPARAM, (LPARAM) (void *) oswindowOldFocus)
   //SendMessage(oswindowOldFocus, WM_KILLFOCUS, WPARAM, (LPARAM) (void *) __oswindow)

   return oswindowOldCapture;

}


WINBOOL release_capture()
{

   ::oswindow oswindowOldCapture = g_oswindowCapture;

   g_oswindowCapture = nullptr;

   // todo
   //SendMessage(__oswindow, WM_SETFOCUS, WPARAM, (LPARAM) (void *) oswindowOldFocus)
   //SendMessage(oswindowOldFocus, WM_KILLFOCUS, WPARAM, (LPARAM) (void *) __oswindow)

   return true;

}


static oswindow g_oswindowActive;


oswindow get_active_window()
{

   return g_oswindowActive;

}

oswindow  set_active_window(oswindow __oswindow)
{

   ::oswindow oswindowOldActive = g_oswindowActive;

   g_oswindowActive = __oswindow;

   // todo
   //SendMessage(__oswindow, WM_SETFOCUS, WPARAM, (LPARAM) (void *) oswindowOldFocus)
   //SendMessage(oswindowOldFocus, WM_KILLFOCUS, WPARAM, (LPARAM) (void *) __oswindow)

   return oswindowOldActive;

}





WINBOOL is_window(oswindow oswindow)
{

   if (((void *)oswindow) == nullptr)
      return FALSE;

   return TRUE;

}

int destroy_window(oswindow oswindow)
{

   return TRUE;

}


//
//CLASS_DECL_CORE::user::interaction_impl * oswindow_interaction_impl(oswindow oswindow)
//{
//
//   if(oswindow == nullptr)
//   {
//
//      return nullptr;
//
//   }
//
//   return oswindow->m_pimpl;
//
//}


int_bool point_is_window_origin(POINT ptHitTest, oswindow oswindowExclude, int iMargin)
{

   return abs(ptHitTest.x) < iMargin && abs(ptHitTest.y) < iMargin;

}


WINBOOL os_init_windowing()
{

   return true;

}


void os_term_windowing()
{


}

//
//
//
//os_system_window::os_system_window()
//{
//
//   //      m_bWindowSizeChange = false;
//
//}

//
//::user::interaction * get_system_window_interaction(::os_system_window * pwindow)
//{
//
//   if (pwindow == nullptr)
//   {
//
//      return nullptr;
//
//   }
//
//   try
//   {
//
//      return pwindow->m_puserinteraction;
//
//   }
//   catch (...)
//   {
//
//   }
//
//   return nullptr;
//
//}
//


__int64 oswindow_id(struct oswindow_data * pdata)
{

   return (__int64)pdata;

}

oswindow g_oswindowFocus = nullptr;


CLASS_DECL_CORE oswindow get_focus()
{

   return g_oswindowFocus;

}


CLASS_DECL_CORE oswindow set_focus(oswindow oswindow)
{

   ::oswindow oswindowPrevious = g_oswindowFocus;

   if (oswindowPrevious != oswindow)
   {

      if (oswindowPrevious)
      {

         if(oswindowPrevious->m_pimpl->m_puserinteraction->m_bFocus)
         {

            oswindowPrevious->m_pimpl->m_puserinteraction->send_message(WM_KILLFOCUS);

         }

      }

      g_oswindowFocus = oswindow;

      if (oswindow)
      {

         if (!oswindow->m_pimpl->m_puserinteraction->m_bFocus)
         {

            oswindow->m_pimpl->m_puserinteraction->send_message(WM_SETFOCUS);

         }

      }

   }

   return oswindowPrevious;

}


CLASS_DECL_CORE oswindow get_window(oswindow oswindow, int iWindow)
{

   if (iWindow == GW_OWNER)
   {

      ::user::interaction * pinteraction = Sys(::get_context_system()).ui_from_handle(oswindow);

      if (pinteraction == nullptr || pinteraction->m_puiOwner)
      {

         return nullptr;

      }

      return pinteraction->m_puiOwner->get_safe_handle();

   }

   return nullptr;

}





CLASS_DECL_CORE WINBOOL show_window(oswindow oswindow, int iShowCmd)
{

   UNREFERENCED_PARAMETER(oswindow);
   UNREFERENCED_PARAMETER( iShowCmd);

   return TRUE;

}


// void update_session_cursor(class user::interaction_impl * puiimpl)
// {

//    __pointer(::uwp::interaction_impl) pimpl = puiimpl;

//    if (pimpl.is_set())
//    {

//       return;

//    }

//    Sess(puiimpl->get_context_application()).get_cursor_pos(puiimpl->m_pointCursor);

// }


HCURSOR CreateAlphaCursor(::image * pimage, int xHotSpot, int yHotSpot)
{

   return nullptr;

}


int_bool is_window_occluded(oswindow oswindow)
{

   return false;

}



WINBOOL WINAPI SetWindowPos(oswindow pdata, oswindow pdataAfter, int x, int y, int cx, int cy, UINT uiFlags)
{

   return pdata->m_pimpl->m_puserinteraction->set_window_pos((iptr)pdataAfter, x, y, cx, cy, uiFlags);

}


void defer_term_ui()
{

}



