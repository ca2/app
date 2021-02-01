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
   m_plongptrmap = new iptr_to_iptr();
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

   ::user::interaction * pinteraction = m_pimpl->m_puserinteraction->get_parent();

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

   ::user::primitive * pprimitive;

   if (oswindow == nullptr || oswindow->m_pimpl == nullptr || oswindow->m_pimpl->m_puserinteraction == nullptr)
   {

      pprimitive = m_pimpl->m_puserinteraction->set_parent(nullptr);

   }
   else
   {

      pprimitive = m_pimpl->m_puserinteraction->set_parent(oswindow->m_pimpl->m_puserinteraction);

   }

   return __user_interaction(pprimitive)->get_safe_handle();

}


bool oswindow_data::show_window(int nCmdShow)
{

   if (m_pimpl == nullptr || m_pimpl->m_puserinteraction == nullptr)
   {

      return false;

   }

   enum_activation eactivation = e_activation_default;

   auto edisplay = windows_show_window_to_edisplay(nCmdShow, eactivation);

   return m_pimpl->m_puserinteraction->display(edisplay, eactivation);

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


bool oswindow_data::_001ClientToScreen(POINT_I32 * lppoint)
{
   if (m_pimpl == nullptr || m_pimpl->m_puserinteraction == nullptr)
   {

      return false;

   }

   m_pimpl->m_puserinteraction->_001ClientToScreen(lppoint);
   return true;
}

bool oswindow_data::_001ScreenToClient(POINT_I32 * lppoint)
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
//   //SendMessage(__oswindow, e_message_set_focus, WPARAM, (LPARAM) (void *) oswindowOldFocus)
//   //SendMessage(oswindowOldFocus, e_message_kill_focus, WPARAM, (LPARAM) (void *) __oswindow)
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
   //SendMessage(__oswindow, e_message_set_focus, WPARAM, (LPARAM) (void *) oswindowOldFocus)
   //SendMessage(oswindowOldFocus, e_message_kill_focus, WPARAM, (LPARAM) (void *) __oswindow)

   return oswindowOldCapture;

}


int_bool release_capture()
{

   ::oswindow oswindowOldCapture = g_oswindowCapture;

   g_oswindowCapture = nullptr;

   // todo
   //SendMessage(__oswindow, e_message_set_focus, WPARAM, (LPARAM) (void *) oswindowOldFocus)
   //SendMessage(oswindowOldFocus, e_message_kill_focus, WPARAM, (LPARAM) (void *) __oswindow)

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
   //SendMessage(__oswindow, e_message_set_focus, WPARAM, (LPARAM) (void *) oswindowOldFocus)
   //SendMessage(oswindowOldFocus, e_message_kill_focus, WPARAM, (LPARAM) (void *) __oswindow)

   return oswindowOldActive;

}





int_bool is_window(oswindow oswindow)
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
//CLASS_DECL_AURA::user::interaction_impl * oswindow_interaction_impl(oswindow oswindow)
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


int_bool point_is_window_origin(POINT_I32 ptHitTest, oswindow oswindowExclude, int iMargin)
{

   return abs(ptHitTest.x) < iMargin && abs(ptHitTest.y) < iMargin;

}


int_bool os_init_windowing()
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


::i64 oswindow_id(struct oswindow_data * pdata)
{

   return (::i64)pdata;

}

oswindow g_oswindowFocus = nullptr;


CLASS_DECL_AURA oswindow get_focus()
{

   return g_oswindowFocus;

}


CLASS_DECL_AURA oswindow set_focus(oswindow oswindow)
{

   ::oswindow oswindowPrevious = g_oswindowFocus;

   if (oswindowPrevious != oswindow)
   {

      if (oswindowPrevious)
      {

         if(oswindowPrevious->m_pimpl->m_puserinteraction->m_bFocus)
         {

            oswindowPrevious->m_pimpl->m_puserinteraction->send_message(e_message_kill_focus);

         }

      }

      g_oswindowFocus = oswindow;

      if (oswindow)
      {

         if (!oswindow->m_pimpl->m_puserinteraction->m_bFocus)
         {

            oswindow->m_pimpl->m_puserinteraction->send_message(e_message_set_focus);

         }

      }

   }

   return oswindowPrevious;

}


CLASS_DECL_AURA oswindow get_window(oswindow oswindow, int iWindow)
{

   if (iWindow == GW_OWNER)
   {

      ::user::interaction * pinteraction = System.ui_from_handle(oswindow);

      if (pinteraction == nullptr || pinteraction->m_puiOwner)
      {

         return nullptr;

      }

      return pinteraction->m_puiOwner->get_safe_handle();

   }

   return nullptr;

}





CLASS_DECL_AURA int_bool show_window(oswindow oswindow, const ::e_display & edisplay, const ::e_activation & eactivation)
{

   UNREFERENCED_PARAMETER(oswindow);
   UNREFERENCED_PARAMETER(edisplay);
   UNREFERENCED_PARAMETER(eactivation);

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



int_bool WINAPI SetWindowPos(oswindow pdata, oswindow pdataAfter, int x, int y, int cx, int cy, ::u32 uFlags)
{

   pdata->m_pimpl->m_puserinteraction->order(pdata);

   pdata->m_pimpl->m_puserinteraction->set_dim(x, y, cx, cy);

   pdata->m_pimpl->m_puserinteraction->set_need_layout();

   pdata->m_pimpl->m_puserinteraction->set_need_redraw();

   pdata->m_pimpl->m_puserinteraction->post_redraw();

   return TRUE;

}


void defer_term_ui()
{

}


//int g_iMouse = -1;
//
//
//int g_iMouseX = 0;
//int g_iMouseY = 0;
//
//
//CLASS_DECL_AURA int_bool GetCursorPos(POINT_I32 * lppoint)
//{
//
//   lppoint->x = g_iMouseX;
//
//   lppoint->y = g_iMouseY;
//
//   if (g_iMouse < 0)
//      return FALSE;
//
//   Windows::ApplicationModel::Core::CoreApplication::MainView->CoreWindow->Dispatcher->RunAsync(::Windows::UI::Core::CoreDispatcherPriority::Normal,
//      ref new Windows::UI::Core::DispatchedHandler([]()
//         {
//
//            Windows::Foundation::Collections::IVectorView < Windows::Devices::Input::PointerDevice^ >^ deva = ::Windows::Devices::Input::PointerDevice::GetPointerDevices();
//
//            for (unsigned int u = 0; u < deva->Size; u++)
//            {
//
//               Windows::Devices::Input::PointerDevice^ dev = deva->GetAt(u);
//
//               if (dev->PointerDeviceType == ::Windows::Devices::Input::PointerDeviceType::Mouse)
//               {
//
//                  Windows::UI::Input::PointerPoint^ pointerPoint = ::Windows::UI::Input::PointerPoint::GetCurrentPoint(g_iMouse);
//
//                  g_iMouseX = (::i32)pointerPoint->RawPosition.X;
//
//                  g_iMouseY = (::i32)pointerPoint->RawPosition.Y;
//
//               }
//
//            }
//
//         }));
//
//   return TRUE;
//
//}



iptr get_window_long_ptr(oswindow_data* oswindow, int iIndex)
{

   return oswindow->get_window_long_ptr(iIndex);

}


iptr set_window_long_ptr(oswindow_data* oswindow, int iIndex, iptr i)
{

   return oswindow->set_window_long_ptr(iIndex, i);

}



