#include "framework.h"
#include "_user.h"


xdisplay::xdisplay()
{

   m_pdata           = nullptr;

   m_bOwn            = false;

   m_bLocked         = false;

}


xdisplay::xdisplay(Display * pdisplay, bool bInitialLock)
{

   m_pdata        = osdisplay_get(pdisplay);

   m_bOwn         = false;

   m_bLocked      = false;

   if(bInitialLock)
   {

      lock();

   }

}


xdisplay::~ xdisplay()
{

   unlock();

   close();

}


bool xdisplay::open(char * display_name, bool bInitialLock)
{

   unlock();

   close();

   Display * pdisplay = x11_get_display();

   if(pdisplay == nullptr)
   {

      return false;

   }

   m_pdata = osdisplay_get(pdisplay);

   if(m_pdata == nullptr)
   {

      return false;

   }

   m_pdata->increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_P_NOTE(nullptr, "xdisplay::open"));

   m_bOwn = true;

   if(bInitialLock)
   {

      lock();

   }

   return true;

}


bool xdisplay::close()
{

   if(!m_bOwn || m_pdata == nullptr || m_pdata->m_pdisplay == nullptr)
   {

      return false;

   }

   if(m_bLocked)
   {

      unlock();

   }

   m_pdata->release();

   m_pdata = nullptr;

   m_bOwn = false;

   return true;

}


//#define PREVENT_XDISPLAY_LOCK_LOG 1


void xdisplay::lock()
{

   if(m_pdata == nullptr || m_bLocked)
   {

      return;

   }

#ifdef XDISPLAY_LOCK_LOG

   if(!b_prevent_xdisplay_lock_log)
   {

      windowing_output_debug_string("\nxdisplay::lock x1");

   }

#endif

   m_pdata->m_pcsOsDisplayData->lock();

#ifdef XDISPLAY_LOCK_LOG

   if(!b_prevent_xdisplay_lock_log)
   {

      windowing_output_debug_string("\nxdisplay::lock x2");

   }

#endif

   m_bLocked = true;

   XLockDisplay(m_pdata->m_pdisplay);

#ifdef XDISPLAY_LOCK_LOG

   if(!b_prevent_xdisplay_lock_log)
   {

      windowing_output_debug_string("\nxdisplay::lock x3");

   }

#endif

}


void xdisplay::unlock()
{

   if(m_pdata == nullptr || !m_bLocked)
   {

      return;

   }

#ifdef XDISPLAY_LOCK_LOG

   if(!b_prevent_xdisplay_lock_log)
   {

      windowing_output_debug_string("\nxdisplay::unlock");

   }

#endif

   m_pdata->m_pcsOsDisplayData->unlock();

   XUnlockDisplay(m_pdata->m_pdisplay);

   m_bLocked = false;

}


Window xdisplay::default_root_window()
{

   if(m_pdata == nullptr)
   {

      return None;

   }

   return m_pdata->default_root_window();

}


int xdisplay::default_screen()
{

   if(m_pdata == nullptr)
   {

      return None;

   }

   return DefaultScreen(m_pdata->m_pdisplay);

}


Atom xdisplay::intern_atom(const ::string & pszAtomName, bool bCreate)
{

   if(m_pdata == nullptr)
   {

      return 0;

   }

   return m_pdata->intern_atom(pszAtomName, bCreate);

}

