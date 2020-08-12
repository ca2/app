//
//  macos_window.cpp
//  base
//
//  Created by Camilo Sasuke Tsumanuma on 2013-09-17.
//
//

#include "framework.h"
#include "ios_window_impl.h"


oswindow_dataptra * g_poswindowdataptra = nullptr;


int oswindow_find(nswindow window)
{

   for(int i = 0; i < g_poswindowdataptra->get_count(); i++)
   {
      if(g_poswindowdataptra->element_at(i)->m_nswindow == window)
      {
         return i;
      }
   }

   return -1;

}

oswindow_data * oswindow_get(nswindow window)
{

   iptr iFind = oswindow_find(window);

   if(iFind >= 0)
      return g_poswindowdataptra->element_at(iFind);

   ::oswindow_data * pdata = new ::oswindow_data;

   pdata->m_nswindow    = window;

   g_poswindowdataptra->add(pdata);

   return pdata;

}


oswindow_data::oswindow_data()
{

   m_nswindow  = nullptr;
   m_puserinteraction       = nullptr;
   m_plongmap  = new int_to_int;

}


oswindow_data::oswindow_data(nswindow window)
{

   m_nswindow  = window;
   m_puserinteraction       = nullptr;
   m_plongmap  = new int_to_int;

}


oswindow_data::oswindow_data(const oswindow_data & oswindow)
{

   m_nswindow  = oswindow.m_nswindow;
   m_puserinteraction       = oswindow.m_puserinteraction;
   m_plongmap  = oswindow.m_plongmap;

}


oswindow_data::~oswindow_data()
{

   delete m_plongmap;

}


oswindow_data & oswindow_data::operator = (const oswindow_data & oswindow)
{

   if(&oswindow != this)
   {

      m_nswindow  = oswindow.m_nswindow;
      m_puserinteraction       = oswindow.m_puserinteraction;
      m_plongmap  = oswindow.m_plongmap;

   }

   return *this;

}


bool oswindow_remove(nswindow window)
{

   iptr iFind = oswindow_find(window);

   if(iFind < 0)
      return false;

   g_poswindowdataptra->remove_at(iFind);

   return true;

}


void oswindow_data::set_user_interaction(::user::interaction * pinteraction)
{

   if(this == nullptr)
      __throw(::exception::exception("error, m_pdata cannot be nullptr to ::oswindow::set_user_interaction"));

   m_puserinteraction = pinteraction;

}


::user::interaction * oswindow_data::get_user_interaction_base()
{

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

   if(this == nullptr)
      return nullptr;

   if(m_puserinteraction == nullptr)
      return nullptr;

   return m_puserinteraction;

}

::user::interaction * oswindow_data::get_user_interaction() const
{

   if(this == nullptr)
      return nullptr;

   if(m_puserinteraction == nullptr)
      return nullptr;

   return m_puserinteraction;

}


oswindow oswindow_data::get_parent()
{

   if(this == nullptr)
      return nullptr;

   return m_puserinteraction->get_parent_handle();

}


oswindow oswindow_data::set_parent(oswindow oswindow)
{

   if(this == nullptr)
      return nullptr;

   ::oswindow oswindowOldParent = get_parent();

   if(oswindow == nullptr
      || oswindow->m_puserinteraction == nullptr)
   {

      m_puserinteraction->set_parent_base(nullptr);

   }
   else
   {

      m_puserinteraction->set_parent_base(oswindow->m_puserinteraction);

   }

   return oswindowOldParent;

}


i32 oswindow_data::get_window_long(i32 iIndex)
{

   if(this == nullptr)
      return 0;

   if(m_plongmap == nullptr)
      return 0;

   return m_plongmap->operator[](iIndex);

}


i32 oswindow_data::set_window_long(i32 iIndex, i32 iNewLong)
{

   if(this == nullptr)
      return 0;

   if(m_plongmap == nullptr)
      return 0;

   i32 iLong = m_plongmap->operator[](iIndex);

   m_plongmap->operator[](iIndex) = iNewLong;

   return iLong;

}


static oswindow g_oswindowCapture;


oswindow GetCapture()
{
   return g_oswindowCapture;
}

oswindow SetCapture(oswindow window)
{

   oswindow windowOld(g_oswindowCapture);

   if(window->window() == nullptr)
      return nullptr;

   g_oswindowCapture = window;

   /*   if(XGrabPointer(window.display(), window.window(), False, ButtonPressMask | ButtonReleaseMask | PointerMotionMask, GrabModeAsync, GrabModeAsync, None, None, 8CurrentTime) == GrabSuccess)
    {

    g_oswindowCapture = window;

    return windowOld;

    }*/

   return windowOld;

}


WINBOOL ReleaseCapture()
{

   //ifGetCapture().display() == nullptr)
   // return FALSE;

   //  WINBOOL bRet = XUngrabPointer(GetCapture().display(), CurrentTime) != FALSE;

   WINBOOL bRet = TRUE;

   if(bRet)
      g_oswindowCapture = nullptr;

   return bRet;

}


oswindow GetFocus();


oswindow SetFocus(oswindow window)
{

   if(!IsWindow(window))
      return nullptr;

   oswindow windowOld = ::GetFocus();

   return windowOld;

}

oswindow GetFocus()
{

   //isplay * pdisplay = XOpenDisplay(nullptr);

   //   Window window = None;

   //   int revert_to = 0;

   //bool bOk = XGetInputFocus(pdisplay, &window, &revert_to) != 0;

   //XCloseDisplay(pdisplay);

   //   if(!bOk)
   //    return nullptr;

   // if(window == None || window == PointerRoot)
   //  return nullptr;

   //return oswindow::defer_get(window);
   return nullptr;

}




static oswindow g_oswindowActive = nullptr;


oswindow GetActiveWindow()
{
   return g_oswindowActive;
}

oswindow SetActiveWindow(oswindow window)
{

   oswindow windowOld(g_oswindowActive);

   if(window->window() == nullptr)
      return nullptr;

   g_oswindowActive = window;

   return windowOld;

}



