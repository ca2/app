#include "framework.h"

#include <X11/Xatom.h>


//extern cairo_surface_t *  g_cairosurface;
//extern cairo_t *  g_cairo;


oswindow_data::oswindow_data()
{

   m_plongmap              = memory_new int_to_int;

   m_htask               = nullptr;

   m_window                = None;

   m_puserinteraction                   = nullptr;

   m_bMessageOnlyWindow    = false;

   m_bDestroying           = false;

   m_osdisplay             = nullptr;

   zero(m_visual);

}

oswindow_data::~oswindow_data()
{

   delete m_plongmap;

}



#define CA2_X11_WINDOW_LONG "ca2_ccwarehouse_fontopu_window_long"
#define CA2_X11_WINDOW_LONG_STYLE "ca2_ccwarehouse_fontopu_window_long_style"
#define CA2_X11_WINDOW_LONG_STYLE_EX "ca2_ccwarehouse_fontopu_window_long_style_ex"

oswindow_dataptra * oswindow_data::s_pdataptra = memory_new oswindow_dataptra;
::pointer< ::mutex > oswindow_data::s_pmutex = memory_new ::pointer < ::mutex >(nullptr);


i32 oswindow_find_message_only_window(::user::interaction_impl * pinteraction)
{

   if(pinteraction == nullptr)
      return -1;

   single_lock slOsWindow(oswindow_data::s_pmutex, true);

   for(i32 i = 0; i < ::oswindow_data::s_pdataptra->get_count(); i++)
   {
      if(::oswindow_data::s_pdataptra->element_at(i)->m_bMessageOnlyWindow
            && ::oswindow_data::s_pdataptra->element_at(i)->m_puserinteraction == pinteraction)
      {
         return i;
      }
   }

   return -1;

}

i32 oswindow_find(Display * pdisplay, Window window)
{

   single_lock slOsWindow(::oswindow_data::s_pmutex, true);

   for(i32 i = 0; i < ::oswindow_data::s_pdataptra->get_count(); i++)
   {
      if(!::oswindow_data::s_pdataptra->element_at(i)->m_bMessageOnlyWindow
            &&  ::oswindow_data::s_pdataptra->element_at(i)->m_osdisplay->display() == pdisplay
            &&  ::oswindow_data::s_pdataptra->element_at(i)->m_window == window)
      {
         return i;
      }
   }

   return -1;

}

i32 oswindow_find(Window window)
{

   single_lock slOsWindow(::oswindow_data::s_pmutex, true);

   for(i32 i = 0; i < ::oswindow_data::s_pdataptra->get_count(); i++)
   {
      if(!::oswindow_data::s_pdataptra->element_at(i)->m_bMessageOnlyWindow
            &&  ::oswindow_data::s_pdataptra->element_at(i)->m_window == window)
      {
         return i;
      }
   }

   return -1;

}

oswindow_data * oswindow_get_message_only_window(::user::interaction_impl * pinteraction)
{

   if(pinteraction == nullptr)
      return nullptr;

   single_lock slOsWindow(::oswindow_data::s_pmutex, true);

   auto pFind = oswindow_find_message_only_window(pinteraction);

   if(::is_set(pFind))
      return ::oswindow_data::s_pdataptra->element_at(iFind);

   ::oswindow_data * pdata = memory_new oswindow_data;

   pdata->m_bMessageOnlyWindow          = true;
   pdata->m_window                      = None;
   pdata->m_puserinteraction                         = pinteraction;
   pdata->m_osdisplay                   = nullptr;

   ::oswindow_data::s_pdataptra->add(pdata);

   return pdata;

}


oswindow_data * oswindow_get(Display * pdisplay, Window window, Visual * pvisual)
{

   single_lock slOsWindow(::oswindow_data::s_pmutex, true);

   auto pFind = oswindow_find(pdisplay, window);

   if(::is_set(pFind))
      return ::oswindow_data::s_pdataptra->element_at(iFind);

   ::oswindow_data * pdata = memory_new ::oswindow_data;

   pdata->m_bMessageOnlyWindow      = false;
   pdata->m_osdisplay               = osdisplay_get(pdisplay);
   pdata->m_window                  = window;
   ::memory_copy(&pdata->m_visual, pvisual, sizeof(Visual));

   ::oswindow_data::s_pdataptra->add(pdata);

   return pdata;

}

oswindow_data * oswindow_get(Window window)
{

   single_lock slOsWindow(::oswindow_data::s_pmutex, true);

   auto pFind = oswindow_find(window);

   if(::is_null(pFind))
      return nullptr;

   return ::oswindow_data::s_pdataptra->element_at(iFind);

}

/*
oswindow::oswindow()
{

   m_pdata = nullptr;

}

oswindow::oswindow(::user::interaction * pinteraction)
{

   single_lock slOsWindow(s_pmutex, true);

   m_pdata = get_message_only_window(pinteraction);



}

oswindow::oswindow(Display * pdisplay, Window window, Visual * pvisual)
{

   single_lock slOsWindow(s_pmutex, true);

   m_pdata = get(pdisplay, window);

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


oswindow oswindow_defer_get(Window window)
{

   return oswindow_get(window);

}



bool oswindow_erase(Display * pdisplay, Window window)
{

   single_lock slOsWindow(::oswindow_data::s_pmutex, true);

   auto pFind = oswindow_find(pdisplay, window);

   if(::is_null(pFind))
      return false;

   ::oswindow_data::s_pdataptra->erase_at(iFind);

   return true;

}


bool oswindow_erase_message_only_window(::user::interaction_impl * puibaseMessageOnlyWindow)
{

   single_lock slOsWindow(::oswindow_data::s_pmutex, true);

   auto pFind = oswindow_find_message_only_window(puibaseMessageOnlyWindow);

   if(::is_null(pFind))
      return false;

   ::oswindow_data::s_pdataptra->erase_at(iFind);

   return true;

}


i32 oswindow_data::store_name(const ::string & psz)
{

   single_lock synchronouslock(&user_synchronization(), true);

   single_lock slOsWindow(s_pmutex, true);

   xdisplay d(display());

   return XStoreName(display(), window(), psz);

}


i32 oswindow_data::select_input(i32 iInput)
{


   single_lock synchronouslock(&user_synchronization(), true);

   single_lock slOsWindow(s_pmutex, true);

   xdisplay d(display());

   return XSelectInput(display(), window(), iInput);

}


i32 oswindow_data::select_all_input()
{

   xdisplay d(display());

   return select_input(ExposureMask | ButtonPressMask);

}


i32 oswindow_data::map_window()
{


   single_lock synchronouslock(&user_synchronization(), true);

   single_lock slOsWindow(s_pmutex, true);

   xdisplay d(display());

   return XMapWindow(display(), window());

}


void oswindow_data::post_nc_destroy()
{

   single_lock slOsWindow(s_pmutex, true);

   oswindow_erase(display(), window());

}


void oswindow_data::set_user_interaction(::user::interaction * pinteraction)
{

   single_lock slOsWindow(s_pmutex, true);

   if(this == nullptr)
      throw ::exception(::exception("error, m_pdata cannot be nullptr to ::oswindow::set_user_interaction"));

   m_puserinteraction = pinteraction;

   m_htask = pinteraction->m_pthread->get_os_handle();

}


::user::interaction * oswindow_data::get_user_interaction_base()
{

   single_lock slOsWindow(s_pmutex, true);

   if(this == nullptr)
      return nullptr;

   return m_puserinteraction;

}

::user::interaction * oswindow_data::get_user_interaction_base() const
{

   if(this == nullptr)
      return nullptr;

   return m_puserinteraction;

}

::user::interaction * oswindow_data::get_user_interaction()
{

   single_lock slOsWindow(s_pmutex, true);

   if(this == nullptr)
      return nullptr;

   if(m_puserinteraction == nullptr)
      return nullptr;

   return m_puserinteraction->m_puserinteraction;

}

::user::interaction * oswindow_data::get_user_interaction() const
{

   single_lock slOsWindow(s_pmutex, true);

   if(this == nullptr)
      return nullptr;

   if(m_puserinteraction == nullptr)
      return nullptr;

   return m_puserinteraction->m_puserinteraction;

}


bool oswindow_data::is_child(::oswindow oswindow)
{

   single_lock synchronouslock(&user_synchronization(), true);

   single_lock slOsWindow(s_pmutex, true);

   oswindow = oswindow->get_parent();

   while(!oswindow->is_null())
   {
      if(oswindow == this)
         return true;
   }

   return false;

}

oswindow oswindow_data::get_parent()
{

   single_lock synchronouslock(&user_synchronization(), true);

   single_lock slOsWindow(s_pmutex, true);

   if(this == nullptr)
      return nullptr;

   return nullptr;

   Window root = 0;
   Window parent = 0;
   Window * pchildren = nullptr;
   u32 ncount = 0;

   XQueryTree(display(), window(), &root, &parent, &pchildren, &ncount);

   if(pchildren != nullptr)
      XFree(pchildren);

   return oswindow_get(display(), parent);

}

oswindow oswindow_data::set_parent(oswindow oswindow)
{

   single_lock synchronouslock(&user_synchronization(), true);

   single_lock slOsWindow(s_pmutex, true);

   if(this == nullptr)
      return nullptr;

   xdisplay d(display());

   ::oswindow oswindowOldParent = get_parent();

   XReparentWindow(display(), window(), oswindow->window(), 0, 0);

   return oswindowOldParent;

}

bool oswindow_data::show_window(i32 nCmdShow)
{

   single_lock synchronouslock(&user_synchronization(), true);

   single_lock slOsWindow(s_pmutex, true);

   xdisplay d(display());

   if(!show_window_is_visible(nCmdShow))
   {

      XUnmapWindow(display(), window());

   }
   else
   {

      XMapWindow(display(), window());

   }

   return true;

}



::i32 oswindow_data::get_window_long(i32 nIndex)
{

   return m_plongmap->operator[](nIndex);

   /*   Atom type = 0;
      i32 format = 0;
      unsigned long itemcount = 0;
      unsigned long remaining = 0;
      ::i32 * pl = nullptr;
      ::i32 l;

      if(XGetWindowProperty(display(), window(), m_pdata->m_osdisplay.get_window_long_atom(nIndex), 0, 1, False, m_pdata->m_osdisplay.atom_long_type(), &type, &format, &itemcount, &remaining, (unsigned char **) &pl) == Success)
      {

         if(pl != nullptr)
         {

            l = *pl;

            XFree(pl);

         }
         else
         {

            l = 0;

         }

      }
      else
      {

         l = 0;

      }


      return l;*/

}


::i32 oswindow_data::set_window_long(i32 nIndex, ::i32 l)
{

   ::i32 lOld = m_plongmap->operator[](nIndex);

   m_plongmap->operator[](nIndex) = l;
   /*   ::i32 lOld = get_window_long(nIndex);

      XChangeProperty(display(), window(), m_osdisplay.get_window_long_atom(nIndex), m_osdisplay.atom_long_type(), 32, PropModeReplace, (unsigned char *) &l, 1);*/

   return lOld;

}


bool oswindow_data::client_to_screen(POINT_I32 * pp)
{

   return true;

}


bool oswindow_data::screen_to_client(POINT_I32 * pp)
{

   return true;

}

Atom get_window_long_atom(i32 nIndex);




long oswindow_data::get_state()
{


   single_lock synchronouslock(&user_synchronization(), true);

   xdisplay d(display());

   static const long WM_STATE_ELEMENTS = 2L;

   unsigned long nitems = 0;
   unsigned long leftover = 0;
   Atom xa_WM_STATE = 0;
   Atom actual_type = 0;
   i32 actual_format = 0;
   i32 status = 0;
   unsigned char* p = nullptr;

   xa_WM_STATE = XInternAtom(display(), "WM_STATE", false);

   status = XGetWindowProperty(display(), window(), xa_WM_STATE, 0L, WM_STATE_ELEMENTS, False, xa_WM_STATE, &actual_type, &actual_format, &nitems, &leftover, &p);


   if(status == 0)
   {
      long lStatus = -1;
      if(p!= nullptr)
         lStatus = (long)*p;
      XFree(p);
      return lStatus;
   }

   return -1;

}




bool oswindow_data::is_iconic()
{

   return get_state() == IconicState;

}

bool oswindow_data::is_window_visible()
{

   single_lock synchronouslock(&user_synchronization(), true);
   xdisplay d(display());

   if(d.m_pdisplay == nullptr)
      return false;

   XWindowAttributes attr;
   if(!XGetWindowAttributes(display(), window(), &attr))
      return false;
   return attr.map_state == IsViewable;

}






/* Copyright (c) 2012 the authors listed at the following URL, and/or
the authors of referenced articles or incorporated external code:
http://en.literateprograms.org/Hello_World_(C,_Cairo)?action=history&offset=20070528220552

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to uxse, cxopy, mxodify, mxerge, pxublish,
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


#include <cairo/cairo.h>
#include <cairo/cairo-xlib.h>
#include <X11/Xlib.h>


#define SIZEX 100
#define SIZEY  50


void message_box_paint(::draw2d::graphics_pointer & pgraphics, string_array & stra, bool_array  & baTab, int_array  & ya,SIZE_I32 * psize)
{

   pgraphics->FillSolidRect(0, 0, psizecx, psize->cy, rgb(84, 90, 80));

   draw2d::brush_pointer pen(pgraphics->create_new, this);

   ppen->create_solid(0);

   for(index i = 0; i < stra.get_count(); i++)
   {
      pgraphics->text_out(10.0 + 50.0 + (baTab[i] ? 25.0 : 0), 10.0 + 50.0 + ya[i], stra[i]);
   }



}



class xlib_message_box :
   virtual public ::os::simple_ui
{
public:


   pointer_array < ::simple_ui::label > m_labela;

   ::rectangle_i32 m_rectangleDesktop;

   xlib_message_box(::pointer<base_application>papp) : ::object(pparticle), ::os::simple_ui(pparticle), ::user::interaction(pparticle)
   {
   }


   void draw_this(::draw2d::graphics *  pgraphics)
   {
      ::rectangle_i32 rectangle;

      client_rectangle(rectangle);

      pgraphics->FillSolidRect(rectangle, argb(255, 240, 240, 240));
   }

   using ::os::simple_ui::show_window;
   i32 show_window(const ::string & lpText, const ::string & lpCaption)
   {

      ::window_rectangle(::get_desktop_window(), &m_rectangleDesktop);


      ::rectangle_i32 rectangle(100, 100, 200, 200);

      if(!create_window(rectangle))
         return 0;


      draw2d::graphics_pointer g(e_create);

      g->CreateCompatibleDC(nullptr);

      auto pfont = __create < ::write_text::font > ();

      pfont->create_point_font(pnode->font_name(e_font_sans), 12.0);

      g->selectFont(font);

      string_array stra;

      stra.add_tokens(lpText, "\n");

      bool_array baTab;

      int_array ya;

      size_i32 sz;

      sz.cx = 0;
      sz.cy = 0;

      for(index i = 0; i < stra.get_count(); i++)
      {

         string str = stra[i];

         bool bTab = ansi_begins(str, "\t");

         str.trim();

         bool bEmpty = str.is_empty();

         if(bEmpty)
            str = "L";

         SIZE_I32 sizeItem = g->get_text_extent(str);

         int x = bTab ? 25 : 0;

         if(sizeItem.cx + x > sz.cx)
         {

            sz.cx = sizeItem.cx + x;

         }

         baTab.add(bTab);

         ya.add( sz.cy);

         sz.cy += sizeItem.cy;

         if(bEmpty)
         {
            stra[i] = "";
         }
         else
         {
            stra[i] = str;
         }

      }

      for(index i = 0; i < stra.get_count(); i++)
      {

         m_labela.add(__new(::simple_ui::label(this)));

         ::simple_ui::label & label = *m_labela.last_element();

         label.set_parent(this);

         label.m_strText = stra[i];

         label.m_bVisible = true;

         label.m_rectangle.left = 10;
         label.m_rectangle.top = 10 + (sz.cy / stra.get_count()) * i;
         label.m_rectangle.right = label.m_rectangle.left+sz.cx - 20;
         label.m_rectangle.bottom = label.m_rectangle.top+ (sz.cy / stra.get_count());

      }

      sz.cx += 20;
      sz.cy += 20;

      rectangle.left = m_rectangleDesktop.left + ((m_rectangleDesktop.width() - sz.cx) / 2);
      rectangle.top = m_rectangleDesktop.top + ((m_rectangleDesktop.height() - sz.cy) / 4);
      rectangle.right = rectangle.left + sz.cx;
      rectangle.bottom = rectangle.top + sz.cy;


      if(!prepare_window(rectangle))
         return 0;



      set_window_position(m_window, nullptr, rectangle.left, rectangle.top, rectangle.width(), rectangle.height(), SWP_SHOWWINDOW);

      run_loop();

      return 0;

   }

};

i32 message_box_show_xlib(base_application * papp, const ::string & lpText, const ::string & lpCaption)
{

   xlib_message_box box(pparticle);

   return box.show_window(lpText, lpCaption);


}



i32 WINAPI MessageBoxA_x11(oswindow hWnd, const ::string & lpText, const ::string & lpCaption, ::u32 uType)
{

   base_application * papp = nullptr;

   if(hWnd == nullptr || hWnd->get_user_interaction() == nullptr || hWnd->get_user_interaction()->get_app() == nullptr)
   {

      papp = get_app();

   }
   else
   {

      papp = hWnd->get_user_interaction()->get_app();

   }

   return message_box_show_xlib(get_app(), lpText, lpCaption);

}





__attribute__((constructor))
static void initialize_x11_message_box()
{

   g_messageboxa = &::MessageBoxA_x11;

}



i32 WINAPI MessageBoxA(oswindow hWnd, const ::string & lpText, const ::string & lpCaption, ::u32 uType)
{

   message_box_show_xlib(get_app(), lpText, lpCaption);

   return 0;

}


static oswindow g_oswindowCapture;


oswindow GetCapture()
{
   return g_oswindowCapture;
}

oswindow SetCapture(oswindow window)
{

   single_lock synchronouslock(&user_synchronization(), true);

   oswindow windowOld(g_oswindowCapture);

   if(window->display() == nullptr)
      return nullptr;

   if(window->window() == None)
      return nullptr;

   xdisplay d(window->display());

   if(XGrabPointer(window->display(), window->window(), False, ButtonPressMask | ButtonReleaseMask | PointerMotionMask, GrabModeAsync, GrabModeAsync, None, None, CurrentTime) == GrabSuccess)
   {

      g_oswindowCapture = window;

      return windowOld;

   }

   return nullptr;

}


int_bool ReleaseCapture()
{

   single_lock synchronouslock(&user_synchronization(), true);

   xdisplay d(g_oswindowCapture->display());


   int_bool bRet = XUngrabPointer(g_oswindowCapture->display(), CurrentTime) != false;

   if(bRet)
      g_oswindowCapture = nullptr;

   return bRet;

}


oswindow SetFocus(oswindow window)
{

   single_lock synchronouslock(&user_synchronization(), true);

   xdisplay display(window->display());

   if(!IsWindow(window))
      return nullptr;

   oswindow windowOld = ::GetFocus();

   if(!XSetInputFocus(window->display(), window->window(), RevertToNone, CurrentTime))
      return nullptr;

   return windowOld;

}

oswindow GetFocus()
{

   single_lock synchronouslock(&user_synchronization(), true);

   xdisplay pdisplay;

   pdisplay.open(nullptr);

   if(pdisplay == nullptr)
      return nullptr;

   Window window = None;

   int revert_to = 0;

   bool bOk = XGetInputFocus(pdisplay, &window, &revert_to) != 0;

   pdisplay.close();

   if(!bOk)
      return nullptr;

   if(window == None || window == PointerRoot)
      return nullptr;

   return oswindow_defer_get(window);

}


oswindow GetActiveWindow()
{

   return GetFocus();

}


oswindow SetActiveWindow(oswindow window)
{

   return SetFocus(window);

}


oswindow GetWindow(oswindow windowParam, int iParentHood)
{

   single_lock synchronouslock(&user_synchronization(), true);




   oswindow window = windowParam;

   if(window == nullptr)
      return nullptr;

   xdisplay d(window->display());

   if(iParentHood == GW_HWNDFIRST
         || iParentHood == GW_HWNDLAST
         || iParentHood == GW_HWNDNEXT
         || iParentHood == GW_HWNDPREV)
   {

      window = ::get_parent(window);

      if(window == nullptr)
         return nullptr;

   }


   Window root = 0;
   Window parent = 0;
   Window * pchildren = nullptr;
   u32 ncount = 0;

   XQueryTree(window->display(), window->window(), &root, &parent, &pchildren, &ncount);

   switch(iParentHood)
   {
   case GW_CHILD:
   case GW_HWNDFIRST:
   {

      if(pchildren == nullptr)
         return nullptr;

      window = ::oswindow_get(window->display(), pchildren[0]);

   }
   break;
   case GW_HWNDLAST:
   {

      if(pchildren == nullptr)
         return nullptr;

      window = ::oswindow_get(window->display(), pchildren[ncount - 1]);

   }
   break;
   case GW_HWNDNEXT:
   case GW_HWNDPREV:
   {

      if(pchildren == nullptr) // ????
         return nullptr;

      int iFound = -1;

      for(int i = 0; i < ncount; i++)
      {
         if(pchildren[i] == windowParam->window())
         {
            iFound = i;
            break;
         }
      }

      if(iFound < 0)
         return nullptr;

      if(iParentHood == GW_HWNDNEXT)
      {

         if(iFound + 1 >= ncount)
            return nullptr;

         window = ::oswindow_get(window->display(), pchildren[iFound - 1]);

      }
      else
      {

         if(iFound - 1 < 0)
            return nullptr;

         window = ::oswindow_get(window->display(), pchildren[iFound - 1]);

      }

   }

   }


   if(pchildren != nullptr)
      XFree(pchildren);


   return window;

}



int_bool DestroyWindow(oswindow window)
{

   single_lock synchronouslock(&user_synchronization(), true);

   if(!IsWindow(window))
      return false;

   Display * pdisplay = window->display();

   Window win = window->window();

   xdisplay d(pdisplay);


   oswindow_data * pdata = (oswindow_data *) (void *) window;

   pdata->m_bDestroying = true;

   bool bIs = IsWindow(window);

   XDestroyWindow(pdisplay, win);

   return true;

}


bool oswindow_data::is_destroying()
{

   if(this == nullptr)
      return true;

   if(m_bDestroying)
      return true;

   return false;

}


int IsWindow(oswindow oswindow)
{
   return oswindow->get_user_interaction() != nullptr && !oswindow->is_destroying();
}


oswindow g_oswindowDesktop;


bool c_xstart()
{

   Display * dpy = XOpenDisplay(nullptr);

   g_oswindowDesktop = oswindow_get(dpy, DefaultRootWindow(dpy));

   XSelectInput(g_oswindowDesktop->display(), g_oswindowDesktop->window(), StructureNotifyMask);

   return true;

}



oswindow get_desktop_window()
{

   return g_oswindowDesktop;
}
