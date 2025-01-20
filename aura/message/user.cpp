#include "framework.h"
#include "user.h"
#include "acme/constant/user_key.h"
#include "acme/exception/interface_only.h"
#include "acme/include/_c_swap.h"
#include "aura/windowing/windowing.h"
#include "aura/windowing/window.h"
#include "aura/user/user/system.h"
#include "aura/user/user/user.h"
#include "aura/user/user/interaction.h"
//#include "aura/user/user/interaction_impl.h"
#include "aura/platform/session.h"


#if defined(LINUX)
// Ubuntu apt-get install libx11-dev
//!!!#include <X11/Xlib.h>
//!!!#include <X11/Xutil.h>

#endif




//
//struct myfx_CTLCOLOR
//{
//
//   ::oswindow     m_oswindow;
//   hdc            m_hdc;
//   unsigned int          m_nCtlType;
//
//
//};


namespace message
{



   //base::base(::particle * pparticle) :
   //   ::message::message(psignal)
   //{

   //   m_lresult = 0;
   //   m_bDestroyed = false;
   //   m_puserinteraction = nullptr;
   //   m_plresult = &m_lresult;
   //   m_bDoSystemDefault = true;

   //}


   //void create::set(oswindow oswindow, ::windowing::window * pwindow, const ::atom & atom, wparam wparam, ::lparam lparam)
   //{

   //   ::user::message::set(oswindow, pwindow, atom, wparam, lparam);

   //   //m_pusersystem = __user_interaction(pwindow)->payload("user_create").cast < ::user::system >();

   //   //CREATESTRUCT * pusersystem = (CREATESTRUCT *)lparam.m_lparam;

   //   //if (pusersystem)
   //   //{

   //   //   m_pusersystem = (::user::system *)pusersystem->CREATE_STRUCT_P_CREATE_PARAMS;

   //   //}

   //}


   create::create() 
   { 
   
   }

   void create::failed(const ::string & strErrorMessage)
   {

      m_lresult = -1;

      error() <<strErrorMessage;

   }


//   ::user::system * create::get_user_system()
//   {
//
//      return m_pusersystem;
//
//   }
//
//
//   ::request * create::get_request()
//   {
//
//      auto pusersystem = get_user_system();
//
//      if (::is_null(pusersystem))
//      {
//
//         return nullptr;
//
//      }
//
//      auto prequest = pusersystem->m_prequest;
//
//      if (::is_null(prequest))
//      {
//
//         return nullptr;
//
//      }
//
//      return prequest;
//
//   }


   //::user::system * create::get_user_create()
   //{

   //   auto pcreate = get_create();

   //   if (::is_null(pcreate))
   //   {

   //      return nullptr;

   //   }

   //   auto pusersystem = __user_system(pcreate->m_pusersystem);

   //   if (!pusersystem)
   //   {

   //      return nullptr;

   //   }

   //   return pusersystem;

   //}


//   ::particle * create::get_impact_data()
//   {
//
//      auto pusersystem = get_user_system();
//
//      if (!pusersystem)
//      {
//
//         return nullptr;
//
//      }
//
//      return pusersystem->m_pimpactdata;
//
//   }


   activate::activate()
   {

   }


   //void activate::set(oswindow oswindow, ::windowing::window * pwindow, const ::atom & atom, wparam wparam, ::lparam lparam)
   //{

   //   ::user::message::set(oswindow, pwindow, atom, wparam, lparam);

   //   m_eactivate = (enum_activate)(first_unsigned_short(wparam));

   //   if(lparam == 0)
   //   {

   //      m_pWndOther = nullptr;

   //   }
   //   else
   //   {

   //      auto paurasession = m_papplication->m_psession;

   //      auto puser = paurasession->m_puser;

   //      auto pwindowing = system()->windowing();

   //      m_pWndOther = __interaction(pwindowing->window(lparam.raw_cast < ::oswindow >()));

   //   }

   //   m_bMinimized = second_unsigned_short(wparam) != false;

   //}


   erase_bkgnd::erase_bkgnd()
   {

   }


   void erase_bkgnd::set_result(bool bResult)
   {

      m_lresult = bResult;

   }


   key::key()
   {

      m_union.m_pkey = this;
      m_ekey = ::user::e_key_none;
      m_nScanCode = 0;
      m_nChar = 0;
      m_nRepCnt = 0;
      m_iCode = 0;
      m_bExt = false;
      m_nFlags = 0;
#if REFERENCING_DEBUGGING
      m_bIncludeCallStackTrace = true;
#endif

   }

   
   key::~key()
   {

   }


   //void key::set(oswindow oswindow, ::windowing::window * pwindow, const ::atom & atom, wparam wparam, ::lparam lparam)
   //{

   //   ::user::message::set(oswindow, pwindow, atom, wparam, lparam);

   //   m_nChar = static_cast<unsigned int>(wparam);

   //   m_nRepCnt = first_unsigned_short(lparam);

   //   m_nFlags = second_unsigned_short(lparam);
   //   
   //   m_iVirtualKey = (int)wparam;

   //   m_nScanCode = ((lparam >> 16) & 0xff);

   //   m_bExt = (lparam & (1 << 24)) != 0;

   //}


   nc_activate::nc_activate()
   {

   }


   //void nc_activate::set(oswindow oswindow, ::windowing::window * pwindow, const ::atom & atom, wparam wparam, ::lparam lparam)
   //{

   //   ::user::message::set(oswindow, pwindow, atom, wparam, lparam);

   //   m_bActive = wparam != false;

   //}


   //void reposition::set(oswindow oswindow, ::windowing::window * pwindow, const ::atom & atom, wparam wparam, ::lparam lparam)
   //{

   //   ::user::message::set(oswindow, pwindow, atom, wparam, lparam);

   //   m_point = ::int_point(lparam);

   //}


   //void size::set(oswindow oswindow, ::windowing::window * pwindow, const ::atom & atom, wparam wparam, ::lparam lparam)
   //{

   //   ::user::message::set(oswindow, pwindow, atom, wparam, lparam);

   //   m_nType     = static_cast < unsigned int > (wparam);

   //   m_size      = ::int_size(x_short(lparam), y_short(lparam));

   //}


   mouse_base & mouse_base::operator = (const mouse_base & mousebase)
   {

      ::user::message::operator = (mousebase);

      ::user::mouse::operator = (mousebase);

      return *this;

   }


   mouse::mouse()
   {

      //m_ecursor = e_cursor_unmodified;

      //m_pcursor = nullptr;
      
      m_union.m_pmouse = this;

//#if defined(LINUX) || defined(FREEBSD) || defined(OPENBSD)
//
//      m_bTranslated = true;  // in root coordinates
//
//      //#elif defined(WINDOWS_DESKTOP)
//      //
//      //      m_bTranslated = true; // not in root coordinates
//      //
//      //      ::client_to_screen(m_oswindow, &m_point);
//
//#else
//
//      m_bTranslated = false; // not in root coordinates
//
//#endif
   }


   mouse::~mouse()
   {

      // try
      // {
      //
      //    //information() << "mouse::~mouse this (X) : " << (::iptr) (::user::message *)this;
      //    //information() << "mouse::~mouse pwnd (X) : " << (::iptr) m_pwindow.m_p;
      //
      //    auto pwindow = window();
      //
      //    if (::is_set(pwindow))
      //    {
      //
      //       //information() << "::message::mouse::~mouse pwindow is_set";
      //
      //       pwindow->on_destruct_mouse_message(this);
      //
      //    }
      //    else
      //    {
      //
      //       //information() << "::message::mouse::~mouse pwindow !is_set";
      //
      //    }
      //
      // }
      // catch(...)
      // {
      //
      // }

   }


   mouse & mouse::operator = (const mouse & mouse)
   {

      mouse_base::operator=(mouse);

      return *this;


   }


   //void mouse::set(oswindow oswindow, ::windowing::window * pwindow, const ::atom & atom, wparam wparam, ::lparam lparam)
   //{

   //   ::user::message::set(oswindow, pwindow, atom, wparam, lparam);

   //   m_nFlags   = wparam;

   //   if((m_nFlags & I32_MINIMUM) == (I32_MINIMUM))
   //   {

   //      informationf("(m_nFlags & I32_MINIMUM) == (I32_MINIMUM)");

   //   }

   //   m_point    = ::int_point(lparam);


   //}


   //void mouse_wheel::set(oswindow oswindow, ::windowing::window * pwindow, const ::atom & atom, wparam wparam, ::lparam lparam)
   //{

   //   ::user::message::set(oswindow, pwindow, atom, wparam, lparam);

   //   m_nFlags    = wparam;

   //   m_point        = ::int_point(lparam);

   //}


   //void set_cursor::set(oswindow oswindow, ::windowing::window* pwindow, const ::atom& atom, wparam wparam, ::lparam lparam)
   //{

   //   ::user::message::set(oswindow, pwindow, atom, wparam, lparam);

   //}


   mouse_activate::mouse_activate()
   {


   }


   ::user::interaction * mouse_activate::get_desktop_window()
   {

      throw ::interface_only();

      //      return interaction_impl::from_handle_dup(reinterpret_cast<oswindow>(m_wparam));

      return nullptr;

   }


   unsigned int mouse_activate::GetHitTest()
   {

      return lower_unsigned_short(m_lparam);

   }


   unsigned int mouse_activate::get_message()
   {

      return upper_unsigned_short(m_lparam);

   }

   
   context_menu::context_menu()
   {

      m_union.m_pcontextmenu = this;

   }


   int_point context_menu::GetPoint()
   {

      return m_pointMessage;

   }


   set_cursor::set_cursor()
   {


   }


   set_cursor::~set_cursor()
   {

      //try
      //{

      //   auto puserinteraction = userinteraction();

      //   if (puserinteraction)
      //   {

      //      auto pwindow = puserinteraction->get_window();

      //      if (pwindow)
      //      {

      //         if (m_pcursor)
      //         {

      //            pwindow->aaa_set_mouse_cursor(m_pcursor);

      //         }

      //      }

      //   }

      //}
      //catch (...)
      //{

      //}

   }


   scroll::scroll()
   {
      
      m_dPosition = DOUBLE_MOST_NEGATIVE;

   }


   scroll:: ~scroll()
   {

   }


   //void scroll::set(oswindow oswindow, ::windowing::window * pwindow, const ::atom & atom, wparam wparam, ::lparam lparam)
   //{

   //   ::pointer<::user::interaction_base>pprimitive(lparam);

   //   m_pscrollbar = pprimitive;

   //   ::user::message::set(oswindow, pwindow, atom, wparam, lparam);

   //   m_ecommand = (enum_scroll_command) (short)first_unsigned_short(wparam);

   //   m_nPos = (short)second_unsigned_short(wparam);

   //}


   //void show_window::set(oswindow oswindow, ::windowing::window * pwindow, const ::atom & atom, wparam wparam, ::lparam lparam)
   //{

   //   ::user::message::set(oswindow, pwindow, atom, wparam, lparam);

   //   m_bShow = wparam != false;

   //   m_nStatus = static_cast<unsigned int>(lparam);

   //}


   //void kill_keyboard_focus::set(oswindow oswindow, ::windowing::window * pwindow, const ::atom & atom, wparam wparam, ::lparam lparam)
   //{

   //   ::user::message::set(oswindow, pwindow, atom, wparam, lparam);

   //   m_oswindowNew = (::oswindow) wparam.m_number;

   //}


   //void nc_hit_test::set(oswindow oswindow, ::windowing::window * pwindow, const ::atom & atom, wparam wparam, ::lparam lparam)
   //{

   //   ::user::message::set(oswindow, pwindow, atom, wparam, lparam);

   //   m_point.x() = x_short(m_lparam);
   //   
   //   m_point.y() = y_short(m_lparam);

   //}


   //void set_keyboard_focus::set(oswindow oswindow, ::windowing::window * pwindow, const ::atom & atom, wparam wparam, ::lparam lparam)
   //{

   //   ::user::message::set(oswindow, pwindow, atom, wparam, lparam);

   //   //m_puserinteraction = psystem->ui_from_handle(reinterpret_cast<oswindow>(wparam));

   //   //m_puserinteraction = nullptr;

   //}


#ifdef WINDOWS_DESKTOP


   //void window_pos::set(oswindow oswindow, ::windowing::window * pwindow, const ::atom & atom, wparam wparam, ::lparam lparam)
   //{

   //   ::user::message::set(oswindow, pwindow, atom, wparam, lparam);

   //   m_pWINDOWPOS = reinterpret_cast<void*>(lparam.m_lparam);

   //}


   //void nc_calc_size::set(oswindow oswindow, ::windowing::window * pwindow, const ::atom & atom, wparam wparam, ::lparam lparam)
   //{

   //   ::user::message::set(oswindow, pwindow, atom, wparam, lparam);

   //   m_pNCCALCSIZE_PARAMS = reinterpret_cast<void*>(lparam.m_lparam);

   //}


   bool nc_calc_size::GetCalcValidRects()
   {

      return m_wparam != false;

   }


#endif


   bool enable::get_enable()
   {

      return m_wparam != 0;

   }


   mouse_wheel::mouse_wheel() 
   {
   
      //m_bTranslated = true;
   
   }


   unsigned int mouse_wheel::GetFlags()
   {

      return lower_unsigned_short(m_wparam);

   }


//   short mouse_wheel::GetDelta()
//   {
//
//      return second_short(m_wparam);
//
//   }


   int_point mouse_wheel::GetPoint()
   {

      return int_point(lparam_int_x(m_lparam), lparam_int_y(m_lparam));

   }


   int notify::get_ctrl_id()
   {

      return (int)m_wparam;

   }


   particle::particle()
   {

      m_union.m_pparticle = this;

   }


   particle::~particle()
   {


   }


   //void particle::set(oswindow oswindow, ::windowing::window * pwindow, const ::atom & atom, wparam wparam, ::lparam lparam)
   //{

   //   ::user::message::set(oswindow, pwindow, atom, wparam, lparam);

   //   ::particle_pointer pparticle(lparam);

   //   m_pparticle = pparticle;

   //   m_lparam = 0;

   //}

   drag_and_drop::drag_and_drop(oswindow oswindow, ::windowing::window * pwindow, const ::atom & atom)
   {

      m_lresult = 0;

      m_oswindow = oswindow;
      
      m_pwindow = pwindow;
      
      m_atom = atom;

   }



} // namespace message


#define ROUND(x,y) (((x)+(y-1))&~(y-1))
#define ROUND4(x) ROUND(x, 4)

#define IMPLEMENT_SIGNAL_OBJECT_FIXED_ALLOC(class_name) IMPLEMENT_FIXED_ALLOC(class_name, ROUND4(sizeof(class_name) * 32))



