#include "framework.h"
#include "_linux.h"
#include "_user.h"
////#include "third/sn/sn.h"
#include "acme/parallelization/message_queue.h"


extern SnLauncheeContext* g_psncontext;
mutex * user_mutex();

#undef ALOG_CONTEXT
#define ALOG_CONTEXT ::trace_object(::trace_category_windowing)


#ifdef XDISPLAY_LOCK_LOG

extern bool b_prevent_xdisplay_lock_log;

#endif


void windowing_output_debug_string(const char * pszDebugString);
void wm_state_clear_raw(oswindow w, bool bSet);
void wm_state_below_raw(oswindow w, bool bSet);
void wm_state_above_raw(oswindow w, bool bSet);
void wm_toolwindow(oswindow w, bool bSet);
void wm_iconify_window(oswindow w);
void x11_post_message(MESSAGE & msg);

const char * g_pszaNetWmState[]=
{
   "_NET_WM_STATE_ABOVE",
   "_NET_WM_STATE_BELOW",
   "_NET_WM_STATE_HIDDEN",
   "_NET_WM_STATE_MAXIMIZED_HORZ",
   "_NET_WM_STATE_MAXIMIZED_VERT",
   "_NET_WM_STATE_FULLSCREEN",
   "_NET_WM_STATE_SKIP_TASKBAR",
   NULL
};


e_net_wm_state net_wm_state(const char * pszText)
{

   if(::is_null(pszText))
   {

      return net_wm_state_count;

   }

   auto ppsz = g_pszaNetWmState;

   int i = 0;

   while(ppsz[i] != NULL)
   {

      if(!ansi_compare_ci(pszText, ppsz[i]))
      {

         break;

      }

      i++;

   }

   return (e_net_wm_state) i;

}


const char * net_wm_state_text(e_net_wm_state estate)
{

   if(estate < net_wm_state_above || estate >= net_wm_state_count)
   {

      return "";

   }

   return g_pszaNetWmState[estate];

}


Display * x11_get_display();


oswindow_data::oswindow_data()
{

   m_iXic = 0;

   m_xic = nullptr;

   for(auto & i : m_iaNetWmState)
   {

      i = -1;

   }

   m_hcursorLast           = 0;

   m_htask               = 0;

   m_window                = None;

   m_pimpl                 = nullptr;

   m_bMessageOnlyWindow    = false;

   m_osdisplay             = nullptr;

   __zero(m_visual);

   m_iDepth                = -1;

   m_iScreen               = -1;

   m_colormap              = None;

   m_iXic                  = 0;

}


oswindow_data::~oswindow_data()
{

}


void oswindow_data::set_wm_class(const char * psz)
{

   m_strWMClass = psz;

   xdisplay d(display());

   XClassHint classHint;

   classHint.res_name = m_strWMClass;

   classHint.res_class = m_strWMClass;

   XSetClassHint(display(), window(), &classHint);

}


i32 oswindow_data::map_window()
{

   int i = 0;

   {

      windowing_output_debug_string("\noswindow_data::map_window");

      xdisplay d(display());

      i = XMapWindow(display(), window());

   }

#ifndef RASPBIAN

   if(g_psncontext != nullptr)
   {

      sn_launchee_context_complete(g_psncontext);

      g_psncontext = nullptr;

   }

#endif // RASPBIAN

   windowing_output_debug_string("\noswindow_data::map_window END");

   return i;

}



i32 oswindow_data::unmap_window(bool bWithdraw)
{

   windowing_output_debug_string("\noswindow_data::unmap_window");

   xdisplay d(display());

   int i;

   if(bWithdraw)
   {

      i = XWithdrawWindow(display(), window(), m_iScreen);

   }
   else
   {

      i = XUnmapWindow(display(), window());

   }

   windowing_output_debug_string("\noswindow_data::unmap_window END");

   return i;

}


oswindow_dataptra * oswindow_data::s_pdataptra = nullptr;


::mutex * oswindow_data::s_pmutex = nullptr;


i32 oswindow_find_message_only_window(::user::interaction_impl * pimpl)
{

   if(pimpl == nullptr)
      return -1;

   single_lock slOsWindow(oswindow_data::s_pmutex, true);

   for(i32 i = 0; i < ::oswindow_data::s_pdataptra->get_count(); i++)
   {

      if(::oswindow_data::s_pdataptra->element_at(i)->m_bMessageOnlyWindow
            && ::oswindow_data::s_pdataptra->element_at(i)->m_pimpl == pimpl)
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
   {

      return nullptr;

   }

   single_lock slOsWindow(::oswindow_data::s_pmutex, true);

   iptr iFind = oswindow_find_message_only_window(pinteraction);

   if(iFind >= 0)
   {

      return ::oswindow_data::s_pdataptra->element_at(iFind);

   }

   ::oswindow_data * pdata = new oswindow_data;

   pdata->m_bMessageOnlyWindow      = true;
   pdata->m_window                  = None;
   pdata->m_pimpl                   = pinteraction;
   pdata->m_osdisplay               = nullptr;
   pdata->m_parent                  = 0;
   pdata->m_pmq                     = pinteraction->m_puserinteraction->m_pthreadUserInteraction->get_message_queue();

   ::oswindow_data::s_pdataptra->add(pdata);

   return pdata;

}


oswindow_data * oswindow_defer_get(Display * pdisplay, Window window)
{

   single_lock slOsWindow(::oswindow_data::s_pmutex, true);

   iptr iFind = oswindow_find(pdisplay, window);

   if(iFind < 0)
   {

      return nullptr;

   }

   return ::oswindow_data::s_pdataptra->element_at(iFind);

}


oswindow_data * oswindow_get(Display * pdisplay, Window window, Visual * pvisual, int iDepth, int iScreen, Colormap colormap)
{

   single_lock slOsWindow(::oswindow_data::s_pmutex, true);

   iptr iFind = oswindow_find(pdisplay, window);

   if(iFind >= 0)
   {

      return ::oswindow_data::s_pdataptra->element_at(iFind);

   }

   ::oswindow_data * pdata = new ::oswindow_data;

   pdata->m_bMessageOnlyWindow      = false;
   pdata->m_osdisplay               = osdisplay_get(pdisplay);
   pdata->m_window                  = window;

   if(pvisual != nullptr)
   {

      pdata->m_visual               = *pvisual;

   }

   pdata->m_iDepth                  = iDepth;
   pdata->m_iScreen                 = iScreen;
   pdata->m_colormap                = colormap;
   pdata->m_parent                  = 0;

   ::oswindow_data::s_pdataptra->add(pdata);

   return pdata;

}


//void x11_on_start_session()
//{

//   Display * dpy = x11_get_display();
//
//   g_oswindowDesktop = oswindow_get(dpy, DefaultRootWindow(dpy));
//
//   g_oswindowDesktop->m_pimpl = nullptr;
//
//   XSelectInput(g_oswindowDesktop->display(), g_oswindowDesktop->window(), StructureNotifyMask);
//
//}


oswindow_data * oswindow_get(Window window)
{

   single_lock slOsWindow(::oswindow_data::s_pmutex, true);

   iptr iFind = oswindow_find(window);

   if(iFind < 0)
   {

      return nullptr;

   }

   return ::oswindow_data::s_pdataptra->element_at(iFind);

}


// void oswindow_set_active_window(oswindow oswindow)
// {

//    single_lock slOsWindow(::oswindow_data::s_pmutex, true);

//    for(auto & point : *::oswindow_data::s_pdataptra)
//    {

//       if(::is_set(point->m_pimpl) && ::is_set(point->m_pimpl->m_puserinteraction))
//       {

//          if(point == oswindow)
//          {

//             point->m_pimpl->m_puserinteraction->m_ewindowflag |= ::window_flag_active;

//          }
//          else
//          {

//             point->m_pimpl->m_puserinteraction->m_ewindowflag -= window_flag_active;

//          }

//       }

//    }

// }


bool oswindow_data::bamf_set_icon(::application * papplication)
{

   ::linux::desktop_file file;

   file.bamf_set_icon(this, papplication);

   return true;

}


int oswindow_data::x_change_property(Atom property, Atom type, int format, int mode, const unsigned char * data, int nelements)
{

   return XChangeProperty(display(), window(), property, type, format, mode, data, nelements);

}


Atom oswindow_data::intern_atom(const char * pszAtomName, bool bCreate)
{

   return m_osdisplay->intern_atom(pszAtomName, bCreate);

}


Atom oswindow_data::intern_atom(e_net_wm_state estate, bool bCreate)
{

   return m_osdisplay->intern_atom(estate, bCreate);

}


bool oswindow_data::set_icon(::image * pimage)
{

   // http://stackoverflow.com/questions/10699927/xlib-argb-window-icon
   // http://stackoverflow.com/users/432509/ideasman42

#if 0

   unsigned int buffer[] =
   {
      16, 16,
      4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 338034905, 3657433343, 0, 184483840, 234881279, 3053453567, 3221225727, 1879048447, 0, 0, 0, 0, 0, 0, 0, 1224737023, 3305111807, 3875537151,0, 0, 2063597823, 1291845887, 0, 67109119, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 50266112, 3422552319, 0, 0, 3070230783, 2063597823, 2986344703, 771752191, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3422552319, 0, 0, 3372220671, 1509949695, 704643327, 3355443455, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 0, 3422552319, 0, 134152192, 3187671295, 251658495, 0, 3439329535, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3422552319, 0, 0, 2332033279, 1342177535, 167772415, 3338666239, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 0, 3422552319, 0, 0, 436207871, 3322085628, 3456106751, 1375731967, 4278255360, 4026597120, 3758161664, 3489726208, 3204513536, 2952855296, 2684419840, 2399207168, 2130771712, 1845559040, 1593900800, 1308688128, 1040252672, 755040000, 486604544, 234946304, 4278255360, 4043374336, 3774938880, 3506503424, 3221290752, 2952855296, 2667642624, 2399207168, 2130771712, 1862336256, 1627453957, 1359017481, 1073805064, 788591627, 503379721, 218169088, 4278255360, 4043374336, 3758161664, 3506503424, 3221290752, 2952855296, 2684419840, 2415984384, 2130771712, 1862336256, 1577123584, 1308688128, 1040252672, 755040000, 486604544, 218169088, 4278190335, 4026532095, 3758096639, 3489661183, 3221225727, 2952790271, 2667577599, 2415919359, 2130706687, 1862271231, 1593835775, 1325400319, 1056964863, 771752191, 520093951, 234881279, 4278190335, 4026532095, 3758096639, 3489661183, 3221225727, 2952790271, 2667577599, 2415919359, 2130706687, 1862271231, 1593835775, 1325400319, 1056964863, 771752191, 503316735, 234881279, 4278190335, 4026532095, 3758096639, 3489661183, 3221225727, 2952790271, 2684354815, 2399142143, 2130706687, 1862271231, 1593835775, 1325400319, 1040187647, 771752191, 520093951, 234881279, 4294901760, 4043243520, 3774808064, 3506372608, 3221159936, 2952724480, 2684289024, 2399076352, 2147418112, 1862205440, 1593769984, 1308557312, 1040121856, 771686400, 503250944, 234815488, 4294901760, 4060020736, 3758030848, 3506372608, 3221159936, 2952724480, 2684289024, 2415853568, 2130640896, 1862205440, 1593769984, 1308557312, 1040121856, 771686400, 503250944, 234815488, 4294901760, 4043243520, 3774808064, 3489595392, 3237937152, 2952724480, 2684289024, 2415853568, 2147418112, 1862205440, 1593769984, 1325334528, 1056899072, 788463616, 503250944, 234815488,
      32, 32,
      4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 0, 0, 0, 0, 0, 0, 0, 0, 0, 268369920, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 1509949695, 3120562431, 4009754879, 4194304255, 3690987775, 2130706687, 83886335, 0, 50331903, 1694499071, 3170894079, 3992977663, 4211081471, 3657433343, 1879048447, 16777471, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3087007999, 2281701631, 1191182591, 1040187647, 2030043391, 4127195391, 2566914303, 0, 16777471, 3254780159, 2181038335, 1191182591, 973078783, 2030043391,4177527039, 2130706687, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 0, 0, 0, 0, 0, 2214592767, 4093640959, 0, 0, 0, 0, 0, 0, 0, 2298478847, 3909091583, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2214592767, 3607101695, 0, 0, 0, 0, 0, 0, 0, 1946157311, 4093640959, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 0, 0, 536871167, 1191182591, 2281701631,3019899135, 637534463, 0, 0, 0, 100597760, 251592704, 33488896, 0, 3321889023, 2919235839, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2550137087, 4278190335, 4278190335, 3405775103, 570425599, 0, 0, 0, 0, 0, 0, 2046820607, 4043309311, 620757247, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 33488896, 0, 0, 218104063, 1291845887, 3841982719, 3388997887, 0, 0, 0, 0, 0, 1996488959, 4093640959, 1073742079, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1761607935, 4278190335, 150995199, 0, 0, 67109119, 2550137087, 3909091583, 889192703, 0, 0, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 0, 0, 0, 0, 0, 2181038335, 3925868799, 0, 0, 218104063, 3070230783, 3623878911, 570425599, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 805306623, 3288334591, 1795162367, 1040187647, 1023410431, 2231369983, 4211081471, 1694499071, 0, 369099007, 3456106751, 3825205503, 1174405375, 872415487, 872415487, 872415487, 872415487, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4293984270, 2046951677, 3422552319, 4110418175, 4177527039, 3405775103, 1409286399, 0, 0, 1409286399, 4278190335, 4278190335, 4278190335, 4278190335, 4278190335, 4278190335, 4278190335, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760,4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4278255360, 4144037632, 4009819904, 3875602176, 3741384448, 3607166720, 3472948992, 3338731264, 3204513536, 3053518592, 2936078080, 2801860352, 2650865408, 2516647680, 2382429952, 2264989440, 2113994496, 1996553984, 1862336256, 1728118528, 1577123584, 1459683072, 1325465344, 1191247616, 1040252672, 922812160, 771817216, 637599488, 503381760, 385941248, 234946304, 100728576, 4278255360, 4144037632, 4009819904, 3875602176, 3724607232, 3607166720, 3472948992, 3338731264, 3204513536, 3070295808, 2936078080, 2801860352, 2667642624, 2516647680, 2399207168, 2264989440, 2130771712, 1996553984, 1845559040, 1728118528, 1593900800, 1459683072, 1308688128, 1191247616, 1057029888, 922812160, 788594432, 637599488, 503381760, 369164032, 234946304, 117505792, 4278255360, 4144037632, 4009819904, 3875602176, 3741384448, 3607166720, 3472948992, 3338731264, 3204513536, 3053518592, 2919300864, 2801860352, 2650865408, 2533424896, 2399207168, 2264989440, 2113994496, 1996553984, 1862336256, 1728118528,1593900800, 1459683072, 1325465344, 1191247616, 1040252672, 906034944, 771817216, 654376704, 503381760, 369164032, 234946304, 117505792, 4278255360, 4144037632, 4009819904, 3858824960, 3741384448, 3607166720, 3472948992, 3338731264, 3204513536, 3070295808, 2936078080, 2801860352, 2667642624, 2533424896, 2382429952, 2264989440, 2130771712, 1979776768, 1862336256, 1728118528, 1577123584, 1442905856, 1325465344, 1191247616, 1040252672, 922812160, 771817216, 637599488, 503381760, 369164032, 234946304, 100728576, 4278255360, 4144037632, 4009819904, 3875602176, 3741384448, 3607166720, 3472948992, 3338731264, 3204513536, 3070295808, 2919300864, 2801860352, 2667642624, 2533424896, 2399207168, 2264989440, 2113994496, 1996553984, 1862336256, 1728118528, 1593900800, 1442905856, 1342241795, 1174470400, 1057029888, 906034944, 788594432, 654376704, 503381760, 385941248, 251723520, 100728576, 4278190335, 4160749823, 4026532095, 3892314367, 3741319423, 3623878911, 3472883967, 3338666239, 3221225727, 3070230783, 2952790271, 2818572543, 2667577599, 2533359871, 2399142143, 2264924415, 2147483903, 1996488959, 1862271231, 1728053503, 1593835775, 1459618047, 1325400319, 1191182591, 1056964863, 922747135, 788529407, 654311679, 520093951,385876223, 251658495, 117440767, 4278190335, 4160749823, 4026532095, 3892314367, 3741319423, 3623878911, 3489661183, 3355443455, 3221225727, 3087007999, 2936013055, 2801795327, 2667577599, 2533359871, 2399142143, 2281701631, 2130706687, 1996488959, 1862271231, 1728053503, 1593835775,1459618047, 1325400319, 1191182591, 1056964863, 922747135, 788529407, 654311679, 520093951, 385876223, 234881279, 100663551, 4278190335, 4160749823, 4026532095, 3892314367, 3758096639, 3623878911, 3489661183, 3355443455, 3221225727, 3087007999, 2936013055, 2801795327, 2667577599, 2550137087, 2415919359, 2264924415, 2130706687, 1996488959, 1862271231, 1728053503, 1593835775, 1459618047, 1325400319, 1191182591, 1056964863, 922747135, 788529407, 654311679, 503316735, 369099007, 251658495, 100663551, 4278190335, 4160749823, 4026532095, 3892314367, 3758096639, 3623878911, 3489661183, 3355443455, 3204448511, 3087007999, 2936013055, 2818572543, 2667577599, 2533359871, 2399142143, 2264924415, 2130706687, 1996488959, 1879048447, 1728053503, 1593835775, 1459618047, 1325400319, 1191182591, 1056964863, 922747135, 788529407, 654311679, 520093951, 385876223, 251658495, 117440767, 4278190335, 4160749823, 4026532095, 3892314367, 3758096639, 3623878911, 3489661183, 3355443455, 3221225727, 3087007999, 2952790271, 2818572543, 2667577599, 2533359871, 2399142143, 2264924415, 2147483903, 2013266175, 1862271231, 1744830719, 1610612991, 1476395263, 1342177535, 1191182591, 1056964863, 922747135, 788529407, 654311679, 520093951, 385876223, 251658495, 100663551, 4294901760, 4160684032, 4026466304, 3909025792, 3774808064, 3623813120, 3489595392, 3355377664, 3237937152, 3103719424, 2952724480, 2818506752, 2684289024, 2550071296, 2415853568, 2281635840, 2147418112, 2013200384, 1878982656, 1744764928, 1593769984, 1476329472,1325334528, 1207894016, 1056899072, 939458560, 788463616, 654245888, 520028160, 385810432, 251592704, 117374976, 4294901760, 4177461248, 4043243520, 3909025792, 3774808064, 3640590336, 3506372608, 3355377664, 3221159936, 3086942208, 2952724480, 2818506752, 2701066240, 2550071296, 2415853568, 2281635840, 2147418112, 2013200384, 1878982656, 1727987712, 1610547200, 1476329472, 1325334528, 1191116800, 1073676288, 922681344, 788463616, 654245888, 520028160, 385810432, 251592704, 100597760, 4294901760, 4177461248, 4043243520, 3909025792, 3774808064, 3640590336, 3489595392, 3372154880, 3237937152, 3103719424, 2952724480, 2818506752, 2700935170, 2550071296, 2415853568, 2281635840, 2147418112, 2013200384, 1878982656, 1744764928, 1610547200, 1459552256, 1342111744, 1191116800, 1056899072, 922681344, 788463616, 671023104, 520028160, 385810432, 251592704, 100597760, 4294901760, 4177461248, 4043243520, 3909025792, 3774808064, 3640590336, 3489595392, 3372154880, 3237937152, 3086942208, 2969501696, 2818506752, 2684289024, 2550071296, 2432630784, 2281635840, 2147418112, 2013200384, 1862205440, 1744764928, 1610547200, 1476329472, 1342111744, 1191116800, 1056899072, 922681344, 788463616, 654245888, 520028160, 385810432, 251592704, 117374976, 4294901760, 4177461248, 4043243520, 3909025792, 3774808064, 3623813120, 3506372608, 3372154880, 3237937152, 3103719424, 2952724480, 2835283968, 2684289024, 2550071296, 2432630784, 2281635840, 2147418112, 2046492676, 1862205440, 1744764928, 1610547200, 1476329472, 1342111744,1207894016, 1056899072, 939458560, 788463616, 654245888, 536281096, 385810432, 251592704, 134152192,
   };

   xdisplay d(display());

   int iScreen = DefaultScreen(d);

   Atom net_wm_icon = d.intern_atom("_NET_WM_ICON", False);

   Atom cardinal = d.intern_atom("CARDINAL", False);

   int length = 2 + 16 * 16 + 2 + 32 * 32;

   int status = XChangeProperty(d, w->window(), net_wm_icon, cardinal, 32, PropModeReplace, (const unsigned char*) buffer, length);

   if(status != 0)
   {

      return false;

   }

#elif 1

   auto d1 = __create_image({32, 32});

   if(!::is_ok(d1))
   {

      return false;

   }

   d1->g()->set_interpolation_mode(e_interpolation_mode_high_quality_bicubic);

   d1->g()->StretchBlt(d1->rectangle(), pimage->g(), pimage->rectangle());

   memory m(m_pimpl->m_puserinteraction->get_application());

   int length = 2 + d1->area();

   m.set_size(length * 4);

   unsigned int * pcr = (unsigned int *) m.get_data();

   pcr[0] = d1->width();

   pcr[1] = d1->height();

   int c = d1->area();

   for(int i = 0; i < c; i++)
   {

      pcr[i+2] = d1->colorref()[i];

   }

   windowing_output_debug_string("\noswindow_data::set_icon");

   xdisplay d(display());

   Atom net_wm_icon = intern_atom("_NET_WM_ICON", False);

   Atom cardinal = intern_atom("CARDINAL", False);

   int status = x_change_property(net_wm_icon, cardinal, 32, PropModeReplace, (const unsigned char*) pcr, length);

   if(status == BadAlloc)
   {


   }
   else if(status != 0)
   {

      return false;

   }

   windowing_output_debug_string("\noswindow_data::set_icon END");

   fflush(stdout);

#else

   image d1(w->m_pimpl->m_puserinteraction->create_new, this);

   if(!d1->create(24, 24))
   {

      return false;

   }

   d1->get_graphics()->set_interpolation_mode(e_interpolation_mode_high_quality_bicubic);

   d1->get_graphics()->StretchBlt(0, 0, d1.width(), d1.height(), point->get_graphics(), 0, 0, point.width(), point.height());

   image d2(w->m_pimpl->m_puserinteraction->create_new, this);

   if(!d2->create(54, 54))
   {

      return false;

   }

   d2->get_graphics()->set_interpolation_mode(e_interpolation_mode_high_quality_bicubic);

   d2->get_graphics()->StretchBlt(0, 0, d2.width(), d2.height(), point->get_graphics(), 0, 0, point.width(), point.height());

   memory m(w->m_pimpl->m_puserinteraction->get_application());

   int length = 2 + d1->area() + 2 + d2->area();

   m.set_size(length * 4);

   unsigned int * pcr = (unsigned int *) m.get_data();

   pcr[0] = d1.width();

   pcr[1] = d1.height();

   int c = d1->area();

   for(int i = 0; i < c; i++)
   {

      pcr[i+2] = d1->m_pcolorref[i];

   }

   memsize o;

   o = 2 + d1->area();

   pcr[o] = d2.width();

   pcr[o+1] = d2.height();

   c = d2->area();

   for(int i = 0; i < c; i++)
   {

      pcr[i+o+2] = d2->m_pcolorref[i];

   }

   Display *display = w->display();

   Atom net_wm_icon = XInternAtom(display, "_NET_WM_ICON", False);

   Atom cardinal = XInternAtom(display, "CARDINAL", False);

   int status = XChangeProperty(display, w->window(), net_wm_icon, cardinal, 32, PropModeReplace, (const unsigned char*) pcr, length);

   if(status != 0)
   {

      //m_psystem->m_pacmefile->put_contents("/home/camilo/window.txt", __str((int)w->window()));
      return false;

   }
#endif
   return true;

}


i32 oswindow_data::store_name(const char * psz)
{

   windowing_output_debug_string("\noswindow_data::store_name");

   xdisplay d(display());

   int i = XStoreName(display(), window(), psz);

   windowing_output_debug_string("\noswindow_data::store_name END");

   return i;

}


i32 oswindow_data::select_input(i32 iInput)
{

   windowing_output_debug_string("\noswindow_data::select_input");

   xdisplay d(display());

   int i = XSelectInput(display(), window(), iInput);

   windowing_output_debug_string("\noswindow_data::select_input END");

   return i;

}


i32 oswindow_data::select_all_input()
{

   windowing_output_debug_string("\noswindow_data::select_all_input");

   xdisplay d(display());

   int i = select_input(ExposureMask | ButtonPressMask);

   windowing_output_debug_string("\noswindow_data::select_all_input");

   return i;

}


void oswindow_data::post_nc_destroy()
{

   if(!::is_null(this))
   {

      oswindow_erase(display(), window());

   }

}


void oswindow_data::set_user_interaction(::user::interaction_impl * pimpl)
{

   single_lock slOsWindow(s_pmutex, true);

   if(::is_null(this))
   {

      __throw(::exception::exception("error, m_pdata cannot be nullptr to ::oswindow::set_user_interaction"));

   }

   m_pimpl = pimpl;

   m_htask = pimpl->get_application()->get_os_handle();

   m_pmq = pimpl->m_puserinteraction->m_pthreadUserInteraction->get_message_queue();

   oswindow_assign(this, pimpl);

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


Window oswindow_data::get_parent_handle()
{

   single_lock slOsWindow(s_pmutex, true);

   if(::is_null(this))
      return 0;

   return m_parent;

}


oswindow oswindow_data::get_parent()
{

   if(::is_null(this))
   {

      return nullptr;

   }

   return nullptr;

}


oswindow oswindow_data::set_parent(oswindow oswindow)
{

   if(::is_null(this))
   {

      return nullptr;

   }

   xdisplay d(display());

   ::oswindow oswindowOldParent = get_parent();

   XReparentWindow(display(), window(), oswindow->window(), 0, 0);

   return oswindowOldParent;

}


/// Post an event from the client to the X server
void oswindow_data::send_client_event(Atom atom, unsigned int numArgs, ...)
{

   XEvent xevent;

   unsigned int i;

   va_list argp;

   va_start(argp, numArgs);

   __zero(xevent);

   xevent.xclient.type = ClientMessage;
   xevent.xclient.serial = 0;
   xevent.xclient.send_event = False;
   xevent.xclient.display = display();
   xevent.xclient.window = window();
   xevent.xclient.message_type = atom;
   xevent.xclient.format = 32;

   for (i = 0; i < numArgs; i++)
   {

      xevent.xclient.data.l[i] = va_arg(argp, int);

   }

   XSendEvent(display(), RootWindow(display(), m_iScreen), False, SubstructureRedirectMask | SubstructureNotifyMask, &xevent);

   va_end(argp);

}


bool oswindow_data::show_window(int iShow)
{

   windowing_output_debug_string("\n::oswindow_data::show_window 1");

   xdisplay d(display());

   if(d.is_null())
   {

      windowing_output_debug_string("\n::oswindow_data::show_window 1.1");

      fflush(stdout);

      return false;

   }

   XWindowAttributes attr;

   if(!XGetWindowAttributes(d, m_window, &attr))
   {

      windowing_output_debug_string("\n::oswindow_data::show_window 1.2");

      return false;

   }

   if(iShow <= SW_HIDE)
   {

      if(attr.map_state != IsUnmapped)
      {

         XWithdrawWindow(d, m_window, m_iScreen);

      }

   }
   else if(iShow == SW_MAXIMIZE)
   {

      if(attr.map_state == IsUnmapped)
      {

         XMapWindow(d, m_window);

      }

      mapped_net_state_raw(true, d, m_window, m_iScreen,
                           intern_atom(net_wm_state_maximized_horz, false),
                           intern_atom(net_wm_state_maximized_vert, false));

   }
   else if(iShow == SW_MINIMIZE || iShow == SW_SHOWMINNOACTIVE)
   {

      wm_iconify_window(this);

   }
   else
   {

      if(attr.map_state == IsUnmapped)
      {

         XMapWindow(d, m_window);

      }

   }

   windowing_output_debug_string("\n::oswindow_data::show_window 2");

   return true;

}


void oswindow_data::full_screen(const ::rectangle & rectangle)
{

   ::rectangle rBest;

   int iMonitor = best_xinerama_monitor(m_pimpl->m_puserinteraction, rectangle, rBest);

   windowing_output_debug_string("\n::oswindow_data::full_screen 1");

   xdisplay d(display());

   if(d.is_null())
   {

      windowing_output_debug_string("\n::oswindow_data::full_screen 1.1");

      return;

   }

   XWindowAttributes attr;

   if(!XGetWindowAttributes(display(), window(), &attr))
   {

      windowing_output_debug_string("\n::oswindow_data::full_screen 1.2");

      fflush(stdout);

      return;

   }

   ::rectangle rWindow;

   rWindow.left      = attr.x;
   rWindow.top       = attr.y;
   rWindow.right     = attr.x    + attr.width;
   rWindow.bottom    = attr.y    + attr.height;

   if(rBest != rWindow)
   {

      m_pimpl->m_puserinteraction->place(rBest);

      XMoveResizeWindow(d, m_window, rBest.left, rBest.top, rBest.width(), rBest.height());

   }

   if(attr.map_state == IsViewable)
   {

      mapped_net_state_raw(true, d, window(), m_iScreen, intern_atom(net_wm_state_fullscreen, false), 0);

   }
   else
   {

      unmapped_net_state_raw(d, window(), intern_atom(net_wm_state_fullscreen, false), 0);

      XMapWindow(display(), window());

   }

   windowing_output_debug_string("\n::oswindow_data::full_screen 2");

   ::fflush(stdout);

}


void oswindow_data::exit_iconify()
{

   xdisplay d(display());

   if(d.is_null())
   {

      windowing_output_debug_string("\n::oswindow_data::exit_iconify 1.1");

      return;

   }

   XWindowAttributes attr;

   if(!XGetWindowAttributes(display(), window(), &attr))
   {

      windowing_output_debug_string("\n::oswindow_data::exit_full_screen 1.2");

      fflush(stdout);

      return;

   }

   if(attr.map_state == IsViewable)
   {

      mapped_net_state_raw(false, d, window(), m_iScreen, intern_atom(net_wm_state_hidden, false), 0);

   }

}

void oswindow_data::exit_full_screen()
{

   xdisplay d(display());

   if(d.is_null())
   {

      windowing_output_debug_string("\n::oswindow_data::exit_full_screen 1.1");

      return;

   }

   XWindowAttributes attr;

   if(!XGetWindowAttributes(display(), window(), &attr))
   {

      windowing_output_debug_string("\n::oswindow_data::exit_full_screen 1.2");

      fflush(stdout);

      return;

   }

   if(attr.map_state == IsViewable)
   {

      mapped_net_state_raw(false, d, window(), m_iScreen, intern_atom("_NET_WM_STATE_FULLSCREEN", false), 0);

   }

}


void oswindow_data::exit_zoomed()
{

   synchronous_lock synchronouslock(x11_mutex());

   xdisplay d(display());

   if(d.is_null())
   {

      windowing_output_debug_string("\n::oswindow_data::exit_zoomed 1.1");

      return;

   }

   XWindowAttributes attr;

   if(!XGetWindowAttributes(display(), window(), &attr))
   {

      windowing_output_debug_string("\n::oswindow_data::exit_zoomed 1.2");

      fflush(stdout);

      return;

   }

   if(attr.map_state == IsViewable)
   {

      mapped_net_state_raw(false, d, window(), m_iScreen,
                     intern_atom("_NET_WM_STATE_MAXIMIZED_HORZ", false),
                     intern_atom("_NET_WM_STATE_MAXIMIZED_VERT", false));

   }

}


LONG_PTR oswindow_data::get_window_long_ptr(i32 nIndex)
{

   return m_pimpl->m_longptr.operator[](nIndex);

}


LONG_PTR oswindow_data::set_window_long_ptr(i32 nIndex, LONG_PTR l)
{

   LONG_PTR lOld = m_pimpl->m_longptr[nIndex];

   if(nIndex == GWL_EXSTYLE)
   {

      if(is_different((l & WS_EX_TOOLWINDOW), (m_pimpl->m_longptr[nIndex] & WS_EX_TOOLWINDOW)))
      {

         wm_toolwindow(this, (l & WS_EX_TOOLWINDOW) != 0);

      }

   }

   m_pimpl->m_longptr[nIndex] = l;

   return lOld;

}


bool oswindow_data::client_to_screen(POINT32 * ppoint)
{

   return true;

}


bool oswindow_data::screen_to_client(POINT32 * ppoint)
{

   return true;

}



long oswindow_data::get_state()
{

   windowing_output_debug_string("\n::oswindow_data::get_state 1");

   xdisplay d(display());

   static const long WM_STATE_ELEMENTS = 2L;

   unsigned long nitems = 0;

   unsigned long leftover = 0;

   Atom atomWmState = 0;

   Atom actual_type = 0;

   i32 actual_format = 0;

   i32 status = 0;

   unsigned char* point = nullptr;

   if(d.m_pdata->m_atomWmState == None)
   {

      d.m_pdata->m_atomWmState = d.intern_atom("WM_STATE", false);

   }

   atomWmState = d.m_pdata->m_atomWmState;

   status = XGetWindowProperty(d, m_window, atomWmState, 0L, WM_STATE_ELEMENTS, False, AnyPropertyType, &actual_type, &actual_format, &nitems, &leftover, &point);

   if(status == 0)
   {

      long lStatus = -1;

      if(point!= nullptr)
      {

         lStatus = (long)*point;

      }

      XFree(point);

      windowing_output_debug_string("\n::oswindow_data::get_state 1.1");

      return lStatus;

   }

   windowing_output_debug_string("\n::oswindow_data::get_state 2");

   return -1;

}


bool oswindow_data::is_iconic()
{

#ifdef XDISPLAY_LOCK_LOG

   b_prevent_xdisplay_lock_log = true;

#endif

   bool b = get_state() == IconicState;

#ifdef XDISPLAY_LOCK_LOG

   b_prevent_xdisplay_lock_log = false;

#endif

   return b;

}


bool oswindow_data::is_window_visible()
{

   windowing_output_debug_string("\n::oswindow_data::is_window_visible 1");

   xdisplay d(display());

   if(d.is_null())
   {

      windowing_output_debug_string("\n::oswindow_data::is_window_visible 1.1");

      return false;

   }

   XWindowAttributes attr;

   if(!XGetWindowAttributes(display(), window(), &attr))
   {

      windowing_output_debug_string("\n::oswindow_data::is_window_visible 1.2");

      return false;

   }

   windowing_output_debug_string("\n::oswindow_data::is_window_visible 2");

   return attr.map_state == IsViewable;

}


bool oswindow_data::is_destroying()
{

   if(::is_null(this))
   {

      return true;

   }

   if(m_pimpl == nullptr)
   {

      return true;

   }

   if(!m_pimpl->m_puserinteraction->m_bUserPrimitiveOk)
   {

      return true;

   }

   return false;

}

#undef SET_WINDOW_POS_LOG

bool oswindow_data::set_window_position(class ::zorder zorder, i32 x, i32 y, i32 cx, i32 cy, ::u32 nFlags)
{

   bool bOk = false;

   x11_sync([&]()
   {

      bOk = _set_window_pos(zorder, x, y, cx, cy, nFlags);

   });

   return bOk;

}


bool oswindow_data::_set_window_pos(class ::zorder zorder, i32 x, i32 y, i32 cx, i32 cy, ::u32 nFlags)
{

   synchronous_lock synchronouslock(x11_mutex());

   windowing_output_debug_string("\n::oswindow_data::set_window_position 1");

   auto pdisplay = display();

   xdisplay d(pdisplay);

   XWindowAttributes attrs = {};

   Window w = window();

   if(!XGetWindowAttributes(pdisplay, w, &attrs))
   {

      windowing_output_debug_string("\n::oswindow_data::set_window_position 1.1 xgetwindowattr failed");

      return false;

   }

   if(nFlags & SWP_SHOWWINDOW)
   {

      if(attrs.map_state == IsUnmapped)
      {

         windowing_output_debug_string("\n::oswindow_data::set_window_position Mapping Window 1.2");

         XMapWindow(display(), window());

      }

      if(!XGetWindowAttributes(display(), window(), &attrs))
      {

         windowing_output_debug_string("\n::oswindow_data::set_window_position 1.3 xgetwindowattr failed");

         return false;

      }

   }

   bool bMove = !(nFlags & SWP_NOMOVE);

   bool bSize = !(nFlags & SWP_NOSIZE);

   if(bMove)
   {

      if(bSize)
      {

         windowing_output_debug_string("\n::oswindow_data::set_window_position Move Resize Window 1.4");

         #ifdef SET_WINDOW_POS_LOG

         INFO("XMoveResizeWindow (%d, %d) - (%d, %d)", x, y, cx, cy);

         #endif

         if(cx <= 0 || cy <= 0)
         {

            cx = 1;

            cy = 1;

            #ifdef SET_WINDOW_POS_LOG

            INFO("Changing parameters... (%d, %d) - (%d, %d)", x, y, cx, cy);

            #endif

         }

         XMoveResizeWindow(display(), window(), x, y, cx, cy);

      }
      else
      {

         windowing_output_debug_string("\n::oswindow_data::set_window_position Move Window 1.4.1");

         XMoveWindow(display(), window(), x, y);

      }

   }
   else if(bSize)
   {

      windowing_output_debug_string("\n::oswindow_data::set_window_position Resize Window 1.4.2");

      XResizeWindow(display(), window(), cx, cy);

   }

//   if(bMove || bSize)
//   {
//
//      if(attrs.override_redirect)
//      {
//
//         if(!(m_pimpl->m_puserinteraction->m_ewindowflag & e_window_flag_arbitrary_positioning))
//         {
//
//            XSetWindowAttributes set;
//
//            set.override_redirect = False;
//
//            if(!XChangeWindowAttributes(display(), window(), CWOverrideRedirect, &set))
//            {
//
//               INFO("linux::interaction_impl::_native_create_window_ex failed to clear override_redirect");
//
//            }
//
//         }
//
//      }
//
//   }


   if(nFlags & SWP_HIDEWINDOW)
   {

      if(attrs.map_state == IsViewable)
      {

         windowing_output_debug_string("\n::oswindow_data::set_window_position Withdraw Window 1.4.3");

         XWithdrawWindow(display(), window(), m_iScreen);

      }

   }

   if(!XGetWindowAttributes(display(), window(), &attrs))
   {

      windowing_output_debug_string("\n::oswindow_data::set_window_position xgetwndattr 1.4.4");

      return false;

   }

   if(attrs.map_state == IsViewable || (nFlags & SWP_SHOWWINDOW))
   {

      if(!(nFlags & SWP_NOZORDER))
      {

         if(zorder.m_ezorder == e_zorder_top_most)
         {

            if(m_iaNetWmState[net_wm_state_above] != 1)
            {

               wm_state_above_raw(this, true);

            }

            XRaiseWindow(display(), window());

         }
         else if(zorder.m_ezorder == e_zorder_top)
         {

            if(m_iaNetWmState[net_wm_state_above] != 0
             || m_iaNetWmState[net_wm_state_below] != 0
             || m_iaNetWmState[net_wm_state_hidden] != 0
             || m_iaNetWmState[net_wm_state_maximized_horz] != 0
             || m_iaNetWmState[net_wm_state_maximized_vert] != 0
             || m_iaNetWmState[net_wm_state_fullscreen] != 0)
            {

               wm_state_clear_raw(this, false);

            }

            XRaiseWindow(display(), window());

         }
         else if(zorder.m_ezorder == e_zorder_bottom)
         {

            if(m_iaNetWmState[net_wm_state_below] != 1)
            {

               wm_state_below_raw(this, true);

            }

            XLowerWindow(display(), window());

         }

      }

      m_pimpl->m_puserinteraction->ModifyStyle(0, WS_VISIBLE, 0);

   }
   else
   {

      m_pimpl->m_puserinteraction->ModifyStyle(WS_VISIBLE, 0, 0);

   }

   //m_pimpl->on_change_visibility();

   windowing_output_debug_string("\n::oswindow_data::set_window_position 2");

   return 1;

}





int_bool show_window(oswindow oswindow, int iShow)
{

   x11_sync([oswindow, iShow]()
   {

      return oswindow->show_window(iShow);

   });

   return true;

}





