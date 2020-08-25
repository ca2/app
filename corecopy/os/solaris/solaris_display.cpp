#include "framework.h"



#define CA2_X11_WINDOW_LONG "ca2_ccwarehouse_window_long"
#define CA2_X11_WINDOW_LONG_STYLE "ca2_ccwarehouse_window_long_style"
#define CA2_X11_WINDOW_LONG_STYLE_EX "ca2_ccwarehouse_window_long_style_ex"

osdisplay_dataptra * osdisplay_data::s_pdataptra = new osdisplay_dataptra;
::mutex * osdisplay_data::s_pmutex = new ::mutex(nullptr);

osdisplay_data::osdisplay_data()
{

   m_pdisplay           = nullptr;
   m_atomLongType       = None;
   m_atomLongStyle      = None;
   m_atomLongStyleEx    = nullptr;

}




i32 osdisplay_find(Display * pdisplay)
{

   single_lock sl(user_mutex(), true);

   for(i32 i = 0; i < osdisplay_data::s_pdataptra->get_count(); i++)
   {
      if(osdisplay_data::s_pdataptra->element_at(i)->m_pdisplay == pdisplay)
      {
         return i;
      }
   }

   return -1;

}

osdisplay_data * osdisplay_get(Display * pdisplay)
{

   mutex_lock sl(user_mutex(), true);

   iptr iFind = osdisplay_find(pdisplay);

   if(iFind >= 0)
      return osdisplay_data::s_pdataptra->element_at(iFind);

   osdisplay_data * pdata     = new osdisplay_data;

   pdata->m_pdisplay          = pdisplay;
   pdata->m_atomLongType      = XInternAtom(pdisplay, CA2_X11_WINDOW_LONG, False);
   pdata->m_atomLongStyle     = XInternAtom(pdisplay, CA2_X11_WINDOW_LONG_STYLE, False);
   pdata->m_atomLongStyleEx   = XInternAtom(pdisplay, CA2_X11_WINDOW_LONG_STYLE_EX, False);

   ::osdisplay_data::s_pdataptra->add(pdata);

   return pdata;

}



bool osdisplay_remove(Display * pdisplay)
{

   mutex_lock sl(user_mutex(), true);

   iptr iFind = osdisplay_find(pdisplay);

   if(iFind < 0)
      return false;

   ::osdisplay_data::s_pdataptra->remove_at(iFind);

   return true;

}

Atom osdisplay_data::get_window_long_atom(i32 nIndex)
{

   if(this == nullptr)
      return 0;

   switch(nIndex)
   {
   case GWL_STYLE:

      return m_atomLongStyle;

   case GWL_EXSTYLE:

      return m_atomLongStyleEx;

   default:
   {

      vsstring strProperty;

      strProperty = CA2_X11_WINDOW_LONG + ansi_string_from_i64(nIndex);

      return XInternAtom(m_pdisplay, strProperty, False);

   }
   }

}


xdisplay::xdisplay()
{
   m_pdisplay    = nullptr;
   m_bOwn        = false;
   m_bLocked     = false;
}

xdisplay::xdisplay(Display * pdisplay, bool bInitialLock)
{
   m_pdisplay    = pdisplay;
   m_bOwn        = false;
   m_bLocked     = false;
   if(bInitialLock)
      lock();
}

bool xdisplay::open(char * display_name, bool bInitialLock)
{
   unlock();
   close();
   m_pdisplay      = XOpenDisplay(display_name);
   if(m_pdisplay == nullptr)
      return false;
   m_bOwn          = true;
   if(bInitialLock)
      lock();
   return true;
}

bool xdisplay::close()
{

   if(!m_bOwn || m_pdisplay == nullptr)
      return false;

   XCloseDisplay(m_pdisplay);
   m_pdisplay = nullptr;
   m_bOwn = false;
   return true;

}

xdisplay::~ xdisplay()
{
   unlock();


   close();

}


void xdisplay::lock()
{
   if(m_pdisplay == nullptr || m_bLocked)
      return;
   m_bLocked = true;
   XLockDisplay(m_pdisplay);

}

void xdisplay::unlock()
{

   if(m_pdisplay == nullptr || !m_bLocked)
      return;
   XUnlockDisplay(m_pdisplay);
   m_bLocked = false;
}




Window xdisplay::default_root_window()
{
   if(m_pdisplay == nullptr)
      return None;
   return DefaultRootWindow(m_pdisplay);
}

int xdisplay::default_screen()
{
   if(m_pdisplay == nullptr)
      return None;
   return DefaultScreen(m_pdisplay);
}
