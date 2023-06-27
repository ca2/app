#include "framework.h"
//#include "apex/os/android/windowing.h"
#include "apex/platform/app_core.h"


void defer_term_ui()
{



}


//::user::interaction * get_system_window_interaction(::os_system_window * psystemwindow)
//{
//
//   if (psystemwindow == nullptr)
//   {
//
//      return nullptr;
//
//   }
//
//   return psystemwindow->m_puserinteraction;
//
//}


CLASS_DECL_APEX i32 oswindow_find_message_only_window(::user::interaction_impl * puibaseMessageWindow);
//CLASS_DECL_APEX i32 oswindow_find(Display * pdisplay,Window window);
//CLASS_DECL_APEX i32 oswindow_find(Window window);
CLASS_DECL_APEX oswindow_data * oswindow_get_message_only_window(::user::interaction_impl * puibaseMessageWindow);
//CLASS_DECL_APEX oswindow_data * oswindow_get(Display * pdisplay,Window window,Visual * pvisual = nullptr,int iDepth = -1,int iScreen = -1,Colormap colormap = None);
//CLASS_DECL_APEX oswindow_data * oswindow_get(Window window);
//CLASS_DECL_APEX oswindow oswindow_defer_get(Window w);
//CLASS_DECL_APEX bool oswindow_erase(Display * pdisplay,Window window);
CLASS_DECL_APEX bool oswindow_erase_message_only_window(::user::interaction_impl * puibaseMessageOnlyWindow);


namespace user
{


   class primitive;
   class interaction;


} // namespace user



oswindow_data::oswindow_data()
{

   m_pmq = nullptr;

   m_htask = (htask_t) nullptr;

   m_pimpl = nullptr;

   m_bMessageOnlyWindow = false;

   m_bDestroying = false;

}


oswindow_data::~oswindow_data()
{

}



#define CA2_X11_WINDOW_LONG "ca2_ccwarehouse_fontopu_window_long"
#define CA2_X11_WINDOW_LONG_STYLE "ca2_ccwarehouse_fontopu_window_long_style"
#define CA2_X11_WINDOW_LONG_STYLE_EX "ca2_ccwarehouse_fontopu_window_long_style_ex"

//oswindow_dataptra * oswindow_data::s_pdataptra = memory_new oswindow_dataptra;
//::pointer< ::mutex > oswindow_data::s_pmutex = memory_new ::pointer < ::mutex >;


i32 oswindow_find_message_only_window(::user::interaction_impl * pimpl)
{

   if (pimpl == nullptr)
   {

      return -1;

   }

   synchronous_lock slOsWindow(oswindow_data::s_pmutex);

   for (i32 i = 0; i < ::oswindow_data::s_pdataptra->get_count(); i++)
   {

      if (::oswindow_data::s_pdataptra->element_at(i)->m_bMessageOnlyWindow
            && ::oswindow_data::s_pdataptra->element_at(i)->m_pimpl == pimpl)
      {

         return i;

      }

   }

   return -1;

}



i32 oswindow_find(::user::interaction_impl * pimpl)
{

   synchronous_lock slOsWindow(::oswindow_data::s_pmutex);

   for (i32 i = 0; i < ::oswindow_data::s_pdataptra->get_count(); i++)
   {
      if (!::oswindow_data::s_pdataptra->element_at(i)->m_bMessageOnlyWindow
            &&  ::oswindow_data::s_pdataptra->element_at(i)->m_pimpl == pimpl)
      {
         return i;
      }
   }

   return -1;

}

oswindow_data * oswindow_get_message_only_window(::user::interaction_impl * pimpl)
{

   if (pimpl == nullptr)
      return nullptr;

   synchronous_lock slOsWindow(::oswindow_data::s_pmutex);

   auto pFind = oswindow_find_message_only_window(pimpl);

   if (::is_set(pFind))
   {

      return ::oswindow_data::s_pdataptra->element_at(iFind);

   }

   ::oswindow_data * pdata = memory_new oswindow_data;

   pdata->m_bMessageOnlyWindow = true;

   pdata->m_pimpl = pimpl;

   ::oswindow_data::s_pdataptra->add(pdata);

   return pdata;

}


oswindow_data * oswindow_get(::user::interaction_impl * pimpl)
{

   synchronous_lock slOsWindow(::oswindow_data::s_pmutex);

   auto pFind = oswindow_find(pimpl);

   if (::is_set(pFind))
      return ::oswindow_data::s_pdataptra->element_at(iFind);

   ::oswindow_data * pdata = memory_new ::oswindow_data;

   pdata->m_bMessageOnlyWindow = false;
   pdata->m_pimpl = pimpl;

   ::oswindow_data::s_pdataptra->add(pdata);

   return pdata;

}



/*
oswindow::oswindow()
{

m_pdata = nullptr;

}

oswindow::oswindow(::user::interaction * pinteraction)
{

synchronous_lock slOsWindow(s_pmutex);

m_pdata = get_message_only_window(pinteraction);



}

oswindow::oswindow(Display * pdisplay, Window interaction_impl, Visual * pvisual)
{

synchronous_lock slOsWindow(s_pmutex);

m_pdata = get(pdisplay, interaction_impl);

if(pvisual != nullptr)
{

m_pdata->m_pvisual = pvisual;

}


}

oswindow::oswindow(const oswindow & oswindow)
{

m_pdata = oswindow.m_pdata;

}

oswindow::oswindow(const void * p)
{

m_pdata = (data *) p;

}

oswindow::oswindow(const LPARAM & lparam)
{

m_pdata = (data *) lparam;

}

oswindow::oswindow(const WPARAM & wparam)
{

m_pdata = (data *) wparam;

}






oswindow & oswindow::operator = (const oswindow & oswindow)
{

m_pdata = oswindow.m_pdata;

return *this;

}



*/


oswindow oswindow_defer_get(::user::interaction_impl * pimpl)
{

   return pimpl->m_oswindow;

}



//int_bool oswindow_erase(::user::interaction * pinteraction)
//{
//
//   synchronous_lock slOsWindow(::oswindow_data::s_pmutex);
//
//   auto pFind = oswindow_find(pinteraction);
//
//   if(::is_null(pFind))
//      return false;
//
//   ::oswindow_data::s_pdataptra->erase_at(iFind);
//
//   return true;
//
//}


bool oswindow_erase_message_only_window(::user::interaction_impl * pinteraction)
{

   synchronous_lock slOsWindow(::oswindow_data::s_pmutex);

   auto pFind = oswindow_find_message_only_window(pinteraction);

   if (::is_null(pFind))
      return false;

   ::oswindow_data::s_pdataptra->erase_at(iFind);

   return true;

}


i32 oswindow_data::store_name(const ::scoped_string & scopedstr)
{

   synchronous_lock synchronouslock(m_pimpl == nullptr || m_pimpl->m_puserinteraction ? nullptr : m_pimpl->m_puserinteraction->synchronization());

   synchronous_lock slOsWindow(s_pmutex);

   /*

   xdisplay d(display());

   return XStoreName(display(), interaction_impl(), psz);

   */

   return 0;

}


i32 oswindow_data::select_input(i32 iInput)
{

   synchronous_lock synchronouslock(m_pimpl == nullptr || m_pimpl->m_puserinteraction ? nullptr : m_pimpl->m_puserinteraction->synchronization());

   synchronous_lock slOsWindow(s_pmutex);

   /*

   xdisplay d(display());

   return XSelectInput(display(), interaction_impl(), iInput);

   */

   return 0;

}


i32 oswindow_data::select_all_input()
{

   /*

   xdisplay d(display());

   return select_input(ExposureMask | ButtonPressMask);

   */

   return 0;

}


i32 oswindow_data::map_window()
{

   /*

   synchronous_lock synchronouslock(m_puserinteraction == nullptr ? nullptr : m_puserinteraction->mutex());

   synchronous_lock slOsWindow(s_pmutex);

   xdisplay d(display());

   return XMapWindow(display(), interaction_impl());

   */

   return 0;

}


void oswindow_data::post_nc_destroy()
{

   synchronous_lock slOsWindow(s_pmutex);

   oswindow_erase(this);

}


void oswindow_data::set_impl(::user::interaction_impl * pimpl)
{

   synchronous_lock slOsWindow(s_pmutex);

   if (::is_null(this))
   {

      throw ::exception(::exception("error, m_pdata cannot be nullptr to ::oswindow::set_user_interaction"));

   }

   m_pimpl = pimpl;

   m_htask = m_pimpl->m_puserinteraction->get_app()->get_os_handle();

}


::user::interaction_impl * oswindow_data::get_impl()
{

   single_lock slOsWindow(s_pmutex, true);

   if (::is_null(this))
   {

      return nullptr;

   }

   return m_pimpl;

}


::user::interaction_impl * oswindow_data::get_impl() const
{

   single_lock slOsWindow(s_pmutex, true);

   if (::is_null(this))
   {

      return nullptr;

   }

   return m_pimpl;

}


::user::interaction * oswindow_data::get_user_interaction()
{

   ::user::interaction_impl * pimpl = get_impl();

   try
   {

      return pimpl->m_puserinteraction;

   }
   catch (...)
   {

   }

   return nullptr;

}


::user::interaction * oswindow_data::get_user_interaction() const
{

   ::user::interaction_impl * pimpl = get_impl();

   try
   {

      return pimpl->m_puserinteraction;

   }
   catch (...)
   {

   }

   return nullptr;

}



bool oswindow_data::is_child(::oswindow oswindow)
{

   synchronous_lock synchronouslock(m_pimpl == nullptr || m_pimpl->m_puserinteraction ? nullptr : m_pimpl->m_puserinteraction->synchronization());

   synchronous_lock slOsWindow(s_pmutex);

   oswindow = oswindow->get_parent();

   while (!oswindow->is_null())
   {
      if (oswindow == this)
         return true;
   }

   return false;

}


oswindow oswindow_data::get_parent()
{

   return nullptr;

}


oswindow oswindow_data::set_parent(oswindow oswindow)
{

   return nullptr;

}


bool oswindow_data::show_window(::e_display edisplay)
{

   synchronous_lock synchronouslock(m_pimpl == nullptr || m_pimpl->m_puserinteraction ? nullptr : m_pimpl->m_puserinteraction->synchronization());

   synchronous_lock slOsWindow(s_pmutex);

   if(is_visible(edisplay))
   {

      m_pimpl->m_puserinteraction->ModifyStyle(0, WS_VISIBLE);

   }
   else
   {

      m_pimpl->m_puserinteraction->ModifyStyle(WS_VISIBLE, 0);

   }

   return false;

}


LONG_PTR oswindow_data::get_window_long_ptr(i32 nIndex)
{

   return m_pimpl->get_window_long_ptr(nIndex);

}


LONG_PTR oswindow_data::set_window_long_ptr(i32 nIndex, LONG_PTR l)
{

   return m_pimpl->set_window_long_ptr(nIndex, l);

}


bool oswindow_data::client_to_screen(POINT32 * pp)
{

   return true;

}


bool oswindow_data::screen_to_client(POINT32 * pp)
{

   return true;

}


long oswindow_data::get_state()
{

   return -1;

}


bool oswindow_data::is_iconic()
{

   return m_bIconic;
}


bool oswindow_data::is_window_visible()
{

   synchronous_lock synchronouslock(m_pimpl == nullptr || m_pimpl->m_puserinteraction ? nullptr : m_pimpl->m_puserinteraction->synchronization());

   if (m_pimpl == nullptr)
   {

      return false;

   }

   return get_window_long_ptr(GWL_STYLE) & WS_VISIBLE;

}






/* Copyright (c) 2012 the authors listed at the following URL, and/or
the authors of referenced articles or incorporated external code:
http://en.literateprograms.org/Hello_World_(C,_Cairo)?action=history&offset=20070528220552

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, topic to
the following conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

Retrieved from: http://en.literateprograms.org/Hello_World_(C,_Cairo)?oldid=10388
*/


void message_box_paint(::draw2d::graphics_pointer & pgraphics, string_array & stra, bool_array  & baTab, int_array  & ya, SIZE32 * psize)
{

   pgraphics->fill_solid_rect_dim(0, 0, psize->cx(), psize->cy(), rgb(84, 90, 80));

   draw2d::brush_pointer pen(e_create_new);

   ppen->create_solid(0);

   for (index i = 0; i < stra.get_count(); i++)
   {
      pgraphics->text_out(10.0 + 50.0 + (baTab[i] ? 25.0 : 0), 10.0 + 50.0 + ya[i], stra[i]);
   }



}



static oswindow g_oswindowCapture;
static oswindow g_oswindowFocus;
static oswindow g_oswindowActive;


oswindow get_capture()
{

   return g_oswindowCapture;

}

oswindow set_capture(oswindow oswindow)
{

   ::oswindow oswindowCapturePrevious = g_oswindowCapture;

   g_oswindowCapture = oswindow;

   return oswindowCapturePrevious;

}


int_bool release_capture()
{

   g_oswindowCapture = nullptr;

   return true;

}


oswindow set_focus(oswindow oswindow)
{

   ::oswindow oswindowFocusPrevious = g_oswindowFocus;

   g_oswindowFocus = oswindow;

   return g_oswindowFocus;

}


oswindow get_focus()
{

   return g_oswindowFocus;

}


int_bool client_rectangle(oswindow_data * pdata, RECT32 * prect)
{

   pdata->m_pimpl->m_puserinteraction->client_rectangle(prect);

   //prect->right -= prect->left;
   //prect->bottom -= prect->top;
   //prect->left = 0;
   //prect->top = 0;

   return true;

}


int_bool window_rectangle(oswindow_data * pdata, RECT32 * prect)
{

   pdata->m_pimpl->m_puserinteraction->window_rectangle(prect);

   return true;

}


int_bool show_window(oswindow_data * pdata, int nCmdShow)
{

   return pdata->show_window(nCmdShow);

}


int_bool SetWindowPos(oswindow_data * pdata, oswindow_data * pdataAfter, int x, int y, int cx, int cy, unsigned int uFlags)
{

   return pdata->m_pimpl->m_puserinteraction->set_window_position((iptr)pdataAfter, x, y, cx, cy, uFlags);

}


//oswindow_data * get_parent(oswindow_data * pdata)
//{
//
//   if (pdata == nullptr)
//      return nullptr;
//
//   if (!IsWindow(pdata))
//      return nullptr;
//
//   return pdata->get_parent();
//
//
//}
//
int_bool IsAscendant(oswindow_data * pdata, oswindow_data * pdataAscendant)
{

   if (pdata == nullptr)
      return false;

   oswindow_data * pdataParent = pdata->get_parent();

   if (pdataAscendant == nullptr)
   {
      if (pdataParent == nullptr)
         return true;
      else
         return false;
   }

   while (pdataParent != nullptr)
   {

      if (pdataParent == pdataAscendant)
         return true;

      pdataParent = pdataParent->get_parent();
   }

   return false;

}


//oswindow g_oswindowActive = nullptr;


oswindow get_active_window()
{

   return g_oswindowActive;

}


oswindow set_active_window(oswindow oswindow)
{

   ::oswindow oswindowPrevious = g_oswindowActive;

   g_oswindowActive = oswindow;

   return g_oswindowActive;

}


oswindow get_window(oswindow windowParam, int iParentHood)
{

   synchronous_lock synchronouslock(windowParam == nullptr ? nullptr : (windowParam->m_pimpl == nullptr || windowParam->m_pimpl->m_puserinteraction == nullptr ? nullptr : windowParam->m_pimpl->m_puserinteraction->synchronization()));

   oswindow interaction_impl = windowParam;

   if (interaction_impl == nullptr)
   {

      return nullptr;

   }

   return nullptr;

}



int_bool destroy_window(oswindow w)
{

   synchronous_lock synchronouslock(w == nullptr || w->m_pimpl == nullptr || w->m_pimpl->m_puserinteraction == nullptr ? nullptr : w->m_pimpl->m_puserinteraction->synchronization());

   if (!is_window(w))
   {

      return false;

   }

   return false;

}


bool oswindow_data::is_destroying()
{

   if (::is_null(this))
      return true;

   if (m_bDestroying)
      return true;

   return false;

}


//bool IsWindow(oswindow oswindow)
//{
//
//   return oswindow->get_user_interaction() != nullptr && !oswindow->is_destroying();
//
//}


oswindow g_oswindowDesktop;


bool c_xstart()
{

   /*
   Display * dpy = XOpenDisplay(nullptr);

   g_oswindowDesktop = oswindow_get(dpy, DefaultRootWindow(dpy));

   XSelectInput(g_oswindowDesktop->display(), g_oswindowDesktop->interaction_impl(), StructureNotifyMask);


   return true;

   */


   return false;

}



oswindow get_desktop_window()
{

   return g_oswindowDesktop;
}


POINT32 g_pointCursor;


int_bool SetCursorPos(POINT32 * lppt)
{
   g_pointCursor = *lppt;
   return true;
}


int_bool GetCursorPos(POINT32 * lppt)
{
   *lppt = g_pointCursor;
   return true;
}







//bool IsWindow(oswindow oswindow)
//{
//   return (oswindow->get_user_interaction() == nullptr && oswindow->display() != nullptr && oswindow->window() != None)
//      || (oswindow->get_user_interaction() != nullptr && !oswindow->is_destroying());
//}





//i32 IsWindowVisible(oswindow window)
//{
//
//   if (!IsWindow(window))
//      return false;
//
//   return window->is_window_visible();
//
//}
//


//::i32 GetWindowLongA(oswindow window, int nIndex)
//{
//
//   if (!IsWindow(window))
//      return false;
//
//   return (::i32) window->get_window_long_ptr(nIndex);
//
//}
//
//
//::i32 SetWindowLongA(oswindow window, int nIndex, ::i32 lValue)
//{
//
//   if (!IsWindow(window))
//      return false;
//
//   return (::i32) window->set_window_long_ptr(nIndex, lValue);
//
//}

//
//oswindow SetParent(oswindow window, oswindow windowNewParent)
//{
//
//   if (!IsWindow(window) || !(windowNewParent == nullptr || ::IsWindow(windowNewParent)))
//      return nullptr;
//
//   return window->SetParent(windowNewParent);
//
//}



//i32 IsIconic(oswindow window)
//{
//
//   if (!IsWindow(window))
//      return false;
//
//   return window->is_iconic();
//
//}


::user::interaction_impl * window_from_handle(oswindow oswindow)
{

   if (oswindow == nullptr)
      return nullptr;

   return oswindow->m_pimpl;

}



//bool IsChild(oswindow windowParent, oswindow oswindowCandidateChildOrDescendant)
//{
//
//   if (!IsWindow(windowParent) || !IsWindow(oswindowCandidateChildOrDescendant))
//      return false;
//
//
//   return windowParent->is_child(oswindowCandidateChildOrDescendant);
//
//
//}

void on_post_nc_destroy(oswindow window)
{

   window->post_nc_destroy();

}


bool is_message_only_window(oswindow window)
{

   return window->m_bMessageOnlyWindow;

}


int translate_android_key_message(::message::key * pkey, int keyCode, int iUni);




void android_mouse(unsigned int message, float x, float y)
{

   if (::apexacmesystem() == nullptr)
      return;

   if (::apexacmesystem()->get_session() == nullptr)
      return;

   if (::apexacmesystem()->get_session()->m_puserinteractionHost == nullptr)
      return;

   MESSAGE msg;

   msg.hwnd = ::apexacmesystem()->get_session()->m_puserinteractionHost->get_handle();

   msg.message = message;

   msg.wParam = 0;

   msg.lParam = MAKELPARAM((long)x, (long)y);

   msg.pt.x() = (long)x;

   msg.pt.y() = (long)y;

   //::apexacmesystem()->get_session()->m_puserinteractionHost->message_handler(&msg);
   ::apexacmesystem()->get_session()->m_puserinteractionHost->post_message(msg.message, msg.wParam, msg.lParam);

}


// 
// void android_l_button_down(float x, float y)
// {

//    android_mouse(e_message_left_button_down, x, y);

// }





// 
// void android_mouse_move(float x, float y)
// {

//    android_mouse(e_message_mouse_move, x, y);

// }





// 
// void android_l_button_up(float x, float y)
// {

//    android_mouse(e_message_left_button_up, x, y);

// }

void _android_key(unsigned int message, int keyCode, int iUni);



void android_key(unsigned int message, int keyCode, int iUni)
{

   //::fork(::apexacmesystem(), [=]()
   //{

      _android_key(message, keyCode, iUni);

   //});

}

void _android_key(unsigned int message, int keyCode, int iUni)
{

   if (::apexacmesystem() == nullptr)
      return;

   if (::apexacmesystem()->get_session() == nullptr)
      return;

   if (::apexacmesystem()->get_session()->m_puserinteractionHost == nullptr)
      return;

   ::pointer<::message::key>pkey = __new(::message::key());

   pkey->m_atom = message;

   if (!translate_android_key_message(pkey, keyCode, iUni))
   {

      return;

   }

   //::apexacmesystem()->get_session()->m_puserinteractionHost->message_handler(pkey);
   ::apexacmesystem()->get_session()->m_puserinteractionHost->post(pkey);

}


void _android_size(float xDummy, float yDummy, float cx, float cy)
{

   UNREFERENCED_PARAMETER(xDummy);

   UNREFERENCED_PARAMETER(yDummy);

   if (::apexacmesystem() == nullptr)
      return;

   if (::apexacmesystem()->get_session() == nullptr)
      return;

   if (::apexacmesystem()->get_session()->m_puserinteractionHost == nullptr)
      return;

   ::apexacmesystem()->get_session()->m_puserinteractionHost->set_window_position(e_zorder_top, 0, 0, cx, cy, SWP_SHOWWINDOW);


}


// 
// void android_key_down(int keyCode, int iUni)
// {

//    information("here???555");

//    android_key(e_message_key_down, keyCode, iUni);

// }

int g_iAndroidSampleRate = -2;

int g_iAndroidBufferSize = -2;


void android_audio_parameters(int iSampleRate, int iBufferSize)
{

   information("here???555.1");

   g_iAndroidSampleRate = iSampleRate;

   g_iAndroidBufferSize = iBufferSize;

}

// aPokemon : oh_Isee_a_pattern_and_I_am_clown_describing_exactly_pay_attention_exactly_as_inphysical_mirror_that_is_surely_a_perfect_human_mirror_than_another_person

void _android_size(float xScreen, float yScreen, float aPok, float yBitmap);



void android_on_size(float xScreen, float yScreen, float pikachu, float yBitmap)
{

   information("android_on_size\n");

   if (::apexacmesystem() == nullptr)
   {

      return;

   }

   //::fork(::apexacmesystem(), [=]()
   //{

   ::apexacmesystem()->get_session()->m_puserinteractionHost->post_predicate([=]()
      {

         _android_size(xScreen, yScreen, pikachu, yBitmap);

      });

   //});

}


// 
// void android_key_up(int keyCode, int iUni)
// {
//    information("here???444");

//    android_key(e_message_key_up, keyCode, iUni);

// }




int translate_android_key_message(::message::key * pkey, int keyCode, int iUni)
{

   information("here???333");

   if (0x80000000 & iUni)
   {

      return 0;

   }
   bool bOk = true;
   switch (keyCode)
   {
   case 62:
      pkey->m_ekey = ::user::e_key_space;
      break;
   case 67:
      pkey->m_ekey = ::user::e_key_back;
      break;
   case 112:
      pkey->m_ekey = ::user::e_key_delete;
      break;
   case 59:
      pkey->m_ekey = ::user::e_key_left_shift;
      break;
   case 60:
      pkey->m_ekey = ::user::e_key_right_shift;
      break;
   case 66:
      pkey->m_ekey = ::user::e_key_return;
      break;
   default:
      bOk = false;
   }

   //if (keyCode >= 29 && keyCode <= 54)
   if(!bOk)
   {

      //pkey->m_ekey = (::user::enum_key) ((int) ::user::e_key_a + keyCode - 29);
      pkey->m_ekey = ::user::e_key_refer_to_text_member;

      ::wd32_character u32sz[2];
      u32sz[0] = iUni;
      u32sz[1] = 0;

      pkey->m_strText = wd32_to_ansi_str(u32sz);

   }
   //else if (keyCode >= 7 && keyCode <= 16)
   //{

   //   pkey->m_ekey = (::user::enum_key) ((int) ::user::e_key_0 + keyCode - 7);

   //   pkey->m_ekey = ::user::e_key_refer_to_text_member;

   //   pkey->m_strText = string((unichar)iUni);

   //}
   //else
   //{

   //}

   return 1;

}

void _android_on_text(string str);


void android_on_text(enum_os_text etext, const wchar_t * pwch, size_t len)
{

   information("here???222");

   string strText(pwch, len);

   //::apexacmesystem()->fork([=]()
   //{

   ::apexacmesystem()->get_session()->m_puserinteractionHost->post_predicate([=]()
      {

         ::apexacmesystem()->on_os_text(etext, strText);

      });

   //});

}


namespace apex
{

   void system::on_os_text(e_os_text etext, string strText)
   {

      if (get_session() == nullptr || ::is_null(get_session()->m_puserinteractionHost))
         return;

      ::pointer<::message::key>pkey = __new(::message::key());

      pkey->m_atom = e_message_key_down;

      pkey->m_ekey = ::user::e_key_refer_to_text_member;

      pkey->m_strText = strText;

      if (pkey->m_strText == "\n" || pkey->m_strText == "\r\n" || pkey->m_strText == "\r")
      {

         pkey->m_strText.empty();

         pkey->m_ekey = ::user::e_key_return;

         //psession->get_user_interaction_host()->message_handler(pkey);

      }
      else
      {

         //psession->get_user_interaction_host()->message_handler(pkey);

      }

      ::apexacmesystem()->get_session()->m_puserinteractionHost->post(pkey);


   }


} // namespace base


CLASS_DECL_APEX void defer_dock_application(int_bool bDock)
{

   UNREFERENCED_PARAMETER(bDock);


}


CLASS_DECL_APEX ::user::interaction_impl * oswindow_get(oswindow oswindow)
{

   if (oswindow == nullptr)
   {

      return nullptr;

   }

   return oswindow->m_pimpl;

}

::pointer< ::mutex > oswindow_data::s_pmutex = nullptr;

oswindow_dataptra * oswindow_data::s_pdataptra = nullptr;

int_bool os_init_windowing()
{

   //set_TranslateMessage(&axis_TranslateMessage);

   //set_DispatchMessage(&axis_DispatchMessage);

   oswindow_data::s_pdataptra = memory_new oswindow_dataptra;

   oswindow_data::s_pmutex = memory_new ::pointer < ::mutex >;

   return true;

}


void os_term_windowing()
{

   ::acme::del(oswindow_data::s_pmutex);

   ::acme::del(oswindow_data::s_pdataptra);

}


int_bool is_window(oswindow oswindow)
{

   if (::oswindow_data::s_pdataptra->find_first(oswindow) < 0)
   {

      return false;

   }

   return true;

}


i64 oswindow_id(oswindow w)
{

   return (i64)(w);

}


CLASS_DECL_APEX void message_box_synchronous(oswindow oswindow, const char * pText, const char * lpCaption, const ::e_message_box & emessagebox, ::callback callback)
{

   while (::apexacmesystem()->oslocal().m_iMessageBoxResult > 0)
   {

      if (!task_sleep(100_ms))
      {

         return -1;

      }

   }

   int iButton = 0;

   switch(emessagebox & 7)
   {
   case e_message_box_ok:
      iButton = 1;
      break;
   case MB_OKCANCEL:
      iButton = 1 | 2;
      break;
   case MB_ABORTRETRYIGNORE:
      iButton = 2 | 4 | 8;
      break;
   case MB_YESNOCANCEL:
      iButton = 2 | 4 | 8;
      break;
   case MB_YESNO:
      iButton = 4 | 8;
      break;
   case MB_RETRYCANCEL:
      iButton = 2 | 4;
      break;
   case MB_CANCELTRYCONTINUE:
      iButton = 1 | 2 | 4;
      break;

   }

   string strOpenUrl;

   if (::is_set(pText))
   {

      ::apexacmesystem()->oslocal().m_strMessageBox = ansi_dup(pText);

   }

   if (::is_set(lpCaption))
   {

      ::apexacmesystem()->oslocal().m_strMessageBoxCaption = ansi_dup(lpCaption);

   }

   ::apexacmesystem()->oslocal().m_iMessageBoxButton = iButton;

   while (::apexacmesystem()->oslocal().m_iMessageBoxResult <= 0)
   {

      if (!task_sleep(100_ms))
      {

         return -1;

      }

   }

   int iResult = ::apexacmesystem()->oslocal().m_iMessageBoxResult;

   ::apexacmesystem()->oslocal().m_iMessageBoxResult = 0;

   if (iResult == 1)
   {

      return e_dialog_result_ok;

   }
   else if (iResult == 2)
   {

      return e_dialog_result_cancel;

   }
   else if (iResult == 4)
   {

      return e_dialog_result_yes;

   }
   else if (iResult == 8)
   {

      return e_dialog_result_no;

   }

   return e_dialog_result_ok;

}


int_bool point_is_window_origin(POINT32 ptHitTest, oswindow oswindowExclude, int iMargin)
{

   return abs(ptHitTest.x()) < iMargin && abs(ptHitTest.y()) < iMargin;

}


int_bool is_window_occluded(oswindow oswindow)
{

   return false;

}


double _001GetWindowTopLeftWeightedOccludedOpaqueRate(oswindow oswindow)
{

   return 0.0;

}






int get_main_screen_rectangle(::rectangle_i32 * lprect)
{

   *lprect = ::apexacmesystem()->get_session()->m_puserinteractionHost->m_pimpl->cast < ::user::interaction_impl >()->m_rectangleWindowScreen;

   return true;

}






int SetMainScreenRect(LPCRECT32 lpcrect)
{

   ::apexacmesystem()->get_session()->m_puserinteractionHost->m_pimpl->cast < ::user::interaction_impl >()->m_rectangleWindowScreen = *lpcrect;

   return true;

}





