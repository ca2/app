#include "framework.h"
#include "apex/platform/app_core.h"
#include "_user.h"
//#include <gdk/gdk.h>


extern ::app_core * g_pappcore;

Display * x11_get_display();

mutex * x11_mutex();

#define CA2_X11_WINDOW_LONG "ca2_ccwarehouse_window_long"
#define CA2_X11_WINDOW_LONG_STYLE "ca2_ccwarehouse_window_long_style"
#define CA2_X11_WINDOW_LONG_STYLE_EX "ca2_ccwarehouse_window_long_style_ex"


void windowing_output_debug_string(const char * pszDebugString);


osdisplay_dataptra * osdisplay_data::s_pdataptra = nullptr;
::mutex * osdisplay_data::s_pmutex = nullptr;

osdisplay_data * g_posdisplaydataMain = nullptr;

void defer_init_ui();

osdisplay_data * x11_main_display()
{

   return g_posdisplaydataMain;

}

osdisplay_data::osdisplay_data()
{

   m_pcsOsDisplayData      = new critical_section();
   m_pdisplay              = nullptr;
   m_atomLongType          = None;
   m_atomLongStyle         = None;
   m_atomNetWmState        = None;
   m_atomLongStyleEx       = 0;
   m_countReference        = 1;
//   m_pmutexInput           = new ::mutex();

}


osdisplay_data::~ osdisplay_data()
{

//   ::acme::del(m_pmutexInput);

   ::acme::del(m_pcsOsDisplayData);

}


i32 osdisplay_find(Display * pdisplay)
{

   single_lock slOsWindow(::osdisplay_data::s_pmutex, true);

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

   if(pdisplay == nullptr)
   {

      return nullptr;

   }

   single_lock slOsWindow(::osdisplay_data::s_pmutex, true);

   iptr iFind = osdisplay_find(pdisplay);

   if(iFind >= 0)
   {

      return osdisplay_data::s_pdataptra->element_at(iFind);

   }

   osdisplay_data * pdisplaydata     = new osdisplay_data;

   pdisplaydata->m_pdisplay          = pdisplay;
   pdisplaydata->m_atomLongType      = XInternAtom(pdisplay, CA2_X11_WINDOW_LONG, False);
   pdisplaydata->m_atomLongStyle     = XInternAtom(pdisplay, CA2_X11_WINDOW_LONG_STYLE, False);
   pdisplaydata->m_atomLongStyleEx   = XInternAtom(pdisplay, CA2_X11_WINDOW_LONG_STYLE_EX, False);

   ::osdisplay_data::s_pdataptra->add(pdisplaydata);

   if(!::g_pappcore->m_bGtkApp)
   {

      if(!g_posdisplaydataMain)
      {

         g_posdisplaydataMain = pdisplaydata;

         //defer_init_ui();

      }

   }

   return pdisplaydata;

}



bool osdisplay_remove(Display * pdisplay)
{

   single_lock slOsWindow(::osdisplay_data::s_pmutex, true);

   iptr iFind = osdisplay_find(pdisplay);

   if(iFind < 0)
      return false;

   osdisplay_data * pdata = ::osdisplay_data::s_pdataptra->element_at(iFind);

   XCloseDisplay(pdata->m_pdisplay);

   ::osdisplay_data::s_pdataptra->remove_at(iFind);

   return true;

}


Atom osdisplay_data::get_window_long_atom(i32 nIndex)
{

   if(::is_null(this))
      return 0;

   switch(nIndex)
   {
   case GWL_STYLE:

      return m_atomLongStyle;

   case GWL_EXSTYLE:

      return m_atomLongStyleEx;

   default:
   {

      string strProperty;

      strProperty = CA2_X11_WINDOW_LONG + ansi_string_from_i64(nIndex);

      return XInternAtom(m_pdisplay, strProperty, False);

   }
   }

}


Atom osdisplay_data::intern_atom(const char * pszAtomName, bool bCreate)
{

   if(m_pdisplay == nullptr)
   {

      return 0;

   }

   auto atom = XInternAtom(m_pdisplay, pszAtomName, bCreate ? True : False);

   if(atom == None)
   {

      windowing_output_debug_string("ERROR: cannot find atom for " + string(pszAtomName) + "\n");

      return None;

   }

   return atom;

}


Atom osdisplay_data::intern_atom(e_net_wm_state estate, bool bCreate)
{

   if(estate < net_wm_state_above || estate >= net_wm_state_count)
   {

      return None;

   }

   if(m_atomaNetWmState[estate] == None)
   {

      m_atomaNetWmState[estate] = intern_atom(net_wm_state_text(estate), bCreate);

   }

   return m_atomaNetWmState[estate];

}


Atom osdisplay_data::net_wm_state_atom(bool bCreate)
{

   if(m_atomNetWmState == None)
   {

      m_atomNetWmState = intern_atom("_NET_WM_STATE", bCreate);

   }

   return m_atomNetWmState;

}


Window osdisplay_data::default_root_window()
{

   if(m_pdisplay == nullptr)
   {

      return None;

   }

   return DefaultRootWindow(m_pdisplay);

}




void enum_display_monitors(::aura::session * psession)
{

   auto pnode = Node;

   pnode->enum_display_monitors(psession);

}
