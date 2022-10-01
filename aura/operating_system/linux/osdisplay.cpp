#include "framework.h"
#include "apex/platform/app_core.h"
#include "_user.h"
//#include <gdk/gdk.h>

//
////Display * x11_get_display();
//
//::mutex * user_mutex();
//
//#define CA2_X11_WINDOW_LONG "ca2_ccwarehouse_window_long"
//#define CA2_X11_WINDOW_LONG_STYLE "ca2_ccwarehouse_window_long_style"
//#define CA2_X11_WINDOW_LONG_STYLE_EX "ca2_ccwarehouse_window_long_style_ex"
//
//
//void windowing_output_debug_string(const ::string & pszDebugString);
//
//namespace windowing
//{
//
//   display_map * g_pdisplaymap = nullptr;
//
//   display * g_pdisplay = nullptr;
//
//   display_map * get_display_map()
//   {
//
//      return g_pdisplaymap;
//
//   }
//
//
//   display * get_display()
//   {
//
//      return g_pdisplay;
//
//   }
//
//   //osdisplay_dataptra * display::s_pdataptra = nullptr;
//   //::mutex * display::s_pmutex = nullptr;
//
//   //display * g_posdisplaydataMain = nullptr;
//
//   void defer_init_ui();
//
//
//
//   display::display()
//   {
//
//      //m_pcsOsDisplayData      = memory_new critical_section();
//      //m_pdisplay              = nullptr;
//      //m_atomLongType          = None;
//      //m_atomLongStyle         = None;
//      //m_atomNetWmState        = None;
//      //m_atomLongStyleEx       = 0;
//      //m_countReference        = 1;
//   //   m_pmutexInput           = memory_new ::mutex();
//
//   }
//
//
//   display::~ display()
//   {
//
//   //   ::acme::del(m_pmutexInput);
//
//      //::acme::del(m_pcsOsDisplayData);
//
//   }
//
//
//   display * find_display(iptr i)
//   {
//
//      synchronous_lock synchronouslock(get_display_map_mutex());
//
//      return m_pdisplaymap[i];
//
//   }
//
//
//
//   display * osdisplay_get(Display * pdisplay)
//   {
//
//      if(pdisplay == nullptr)
//      {
//
//         return nullptr;
//
//      }
//
//      single_lock slOsWindow(::display::s_pmutex, true);
//
//      iptr iFind = osdisplay_find(pdisplay);
//
//      if(iFind >= 0)
//      {
//
//         return display::s_pdataptra->element_at(iFind);
//
//      }
//
//      display * pdisplaydata     = memory_new display;
//
//      pdisplaydata->m_pdisplay          = pdisplay;
//      pdisplaydata->m_atomLongType      = XInternAtom(pdisplay, CA2_X11_WINDOW_LONG, False);
//      pdisplaydata->m_atomLongStyle     = XInternAtom(pdisplay, CA2_X11_WINDOW_LONG_STYLE, False);
//      pdisplaydata->m_atomLongStyleEx   = XInternAtom(pdisplay, CA2_X11_WINDOW_LONG_STYLE_EX, False);
//
//      ::display::s_pdataptra->add(pdisplaydata);
//
//      if(!::g_p//appcore->m_bGtkApp)
//      {
//
//         if(!g_posdisplaydataMain)
//         {
//
//            g_posdisplaydataMain = pdisplaydata;
//
//            //defer_init_ui();
//
//         }
//
//      }
//
//      return pdisplaydata;
//
//   }
//
//
//
//   bool osdisplay_erase(Display * pdisplay)
//   {
//
//      single_lock slOsWindow(::display::s_pmutex, true);
//
//      iptr iFind = osdisplay_find(pdisplay);
//
//      if(iFind < 0)
//         return false;
//
//      display * pdata = ::display::s_pdataptra->element_at(iFind);
//
//      XCloseDisplay(pdata->m_pdisplay);
//
//      ::display::s_pdataptra->erase_at(iFind);
//
//      return true;
//
//   }
//
//
//   Atom display::get_window_long_atom(i32 nIndex)
//   {
//
//      if(::is_null(this))
//         return 0;
//
//      switch(nIndex)
//      {
//      case GWL_STYLE:
//
//         return m_atomLongStyle;
//
//      case GWL_EXSTYLE:
//
//         return m_atomLongStyleEx;
//
//      default:
//      {
//
//         string strProperty;
//
//         strProperty = CA2_X11_WINDOW_LONG + ansi_string_from_i64(nIndex);
//
//         return XInternAtom(m_pdisplay, strProperty, False);
//
//      }
//      }
//
//   }
//
//
//   Atom display::intern_atom(const ::string & pszAtomName, bool bCreate)
//   {
//
//      if(m_pdisplay == nullptr)
//      {
//
//         return 0;
//
//      }
//
//      auto atom = XInternAtom(m_pdisplay, pszAtomName, bCreate ? True : False);
//
//      if(atom == None)
//      {
//
//         windowing_output_debug_string("ERROR: cannot find atom for " + string(pszAtomName) + "\n");
//
//         return None;
//
//      }
//
//      return atom;
//
//   }
//
//
//   Atom display::intern_atom(e_net_wm_state estate, bool bCreate)
//   {
//
//      if(estate < net_wm_state_above || estate >= net_wm_state_count)
//      {
//
//         return None;
//
//      }
//
//      if(m_atomaNetWmState[estate] == None)
//      {
//
//         m_atomaNetWmState[estate] = intern_atom(net_wm_state_text(estate), bCreate);
//
//      }
//
//      return m_atomaNetWmState[estate];
//
//   }
//
//
//   Atom display::net_wm_state_atom(bool bCreate)
//   {
//
//      if(m_atomNetWmState == None)
//      {
//
//         m_atomNetWmState = intern_atom("_NET_WM_STATE", bCreate);
//
//      }
//
//      return m_atomNetWmState;
//
//   }
//
//
//   Window display::default_root_window()
//   {
//
//      if(m_pdisplay == nullptr)
//      {
//
//         return None;
//
//      }
//
//      return DefaultRootWindow(m_pdisplay);
//
//   }
//
//
//
//
//   void enum_display_monitors(::aura::session * psession)
//   {
//
//      auto pnode = Node;
//
//      if(pnode)
//      {
//
//         pnode->enum_display_monitors(psession);
//
//      }
//
//   }
//
//
//
//} // namespace windowing
//
//

