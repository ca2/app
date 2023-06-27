#include "framework.h"
#include "user.h"
#include "acme/exception/interface_only.h"
#include "acme/include/_c_swap.h"
#include "aura/windowing/windowing.h"
#include "aura/windowing/window.h"
#include "aura/user/user/system.h"
#include "aura/user/user/user.h"
#include "aura/user/user/interaction.h"
#include "aura/user/user/interaction_impl.h"
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
//   ::u32          m_nCtlType;
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


   ::user::system * create::get_user_system()
   {

      return m_pusersystem;

   }


   ::request * create::get_request()
   {

      auto pusersystem = get_user_system();

      if (::is_null(pusersystem))
      {

         return nullptr;

      }

      auto prequest = pusersystem->m_prequest;

      if (::is_null(prequest))
      {

         return nullptr;

      }

      return prequest;

   }


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


   ::particle * create::get_impact_data()
   {

      auto pusersystem = get_user_system();

      if (!pusersystem)
      {

         return nullptr;

      }

      return pusersystem->m_pimpactdata;

   }


   activate::activate()
   {

   }


   //void activate::set(oswindow oswindow, ::windowing::window * pwindow, const ::atom & atom, wparam wparam, ::lparam lparam)
   //{

   //   ::user::message::set(oswindow, pwindow, atom, wparam, lparam);

   //   m_eactivate = (enum_activate)(first_u16(wparam));

   //   if(lparam == 0)
   //   {

   //      m_pWndOther = nullptr;

   //   }
   //   else
   //   {

   //      auto paurasession = m_pcontext->m_pacmesession->m_paurasession;

   //      auto puser = paurasession->m_puser;

   //      auto pwindowing = puser->m_pwindowing;

   //      m_pWndOther = __interaction(pwindowing->window(lparam.raw_cast < ::oswindow >()));

   //   }

   //   m_bMinimized = second_u16(wparam) != false;

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

   }

   
   key::~key()
   {

   }


   //void key::set(oswindow oswindow, ::windowing::window * pwindow, const ::atom & atom, wparam wparam, ::lparam lparam)
   //{

   //   ::user::message::set(oswindow, pwindow, atom, wparam, lparam);

   //   m_nChar = static_cast<::u32>(wparam);

   //   m_nRepCnt = first_u16(lparam);

   //   m_nFlags = second_u16(lparam);
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

   //   m_point = ::point_i32(lparam);

   //}


   //void size::set(oswindow oswindow, ::windowing::window * pwindow, const ::atom & atom, wparam wparam, ::lparam lparam)
   //{

   //   ::user::message::set(oswindow, pwindow, atom, wparam, lparam);

   //   m_nType     = static_cast < ::u32 > (wparam);

   //   m_size      = ::size_i32(x_i16(lparam), y_i16(lparam));

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

//#if defined(LINUX) || defined(FREEBSD)
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

      try
      {

         auto pwindow = window();

         if (pwindow)
         {

            auto puserinteractionimpl = pwindow->m_puserinteractionimpl;

            if (puserinteractionimpl)
            {

               auto puserinteraction = puserinteractionimpl->m_puserinteraction;

               if (puserinteraction)
               {

                  auto pwindow = puserinteraction->window();

                  if (pwindow)
                  {

                     if (m_pcursor)
                     {

                        pwindow->set_mouse_cursor(m_pcursor);

                     }

                  }

               }

            }

         }

      }
      catch(...)
      {

      }

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

   //   if((m_nFlags & 0x80000000) == (0x80000000))
   //   {

   //      information("(m_nFlags & 0x80000000) == (0x80000000)");

   //   }

   //   m_point    = ::point_i32(lparam);


   //}


   //void mouse_wheel::set(oswindow oswindow, ::windowing::window * pwindow, const ::atom & atom, wparam wparam, ::lparam lparam)
   //{

   //   ::user::message::set(oswindow, pwindow, atom, wparam, lparam);

   //   m_nFlags    = wparam;

   //   m_point        = ::point_i32(lparam);

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


   ::u32 mouse_activate::GetHitTest()
   {

      return lower_u16(m_lparam);

   }


   ::u32 mouse_activate::get_message()
   {

      return upper_u16(m_lparam);

   }

   
   context_menu::context_menu()
   {

      m_union.m_pcontextmenu = this;

   }


   point_i32 context_menu::GetPoint()
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

      //            pwindow->set_mouse_cursor(m_pcursor);

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

   }


   scroll:: ~scroll()
   {

   }


   //void scroll::set(oswindow oswindow, ::windowing::window * pwindow, const ::atom & atom, wparam wparam, ::lparam lparam)
   //{

   //   ::pointer<::user::primitive>pprimitive(lparam);

   //   m_pscrollbar = pprimitive;

   //   ::user::message::set(oswindow, pwindow, atom, wparam, lparam);

   //   m_ecommand = (enum_scroll_command) (i16)first_u16(wparam);

   //   m_nPos = (i16)second_u16(wparam);

   //}


   //void show_window::set(oswindow oswindow, ::windowing::window * pwindow, const ::atom & atom, wparam wparam, ::lparam lparam)
   //{

   //   ::user::message::set(oswindow, pwindow, atom, wparam, lparam);

   //   m_bShow = wparam != false;

   //   m_nStatus = static_cast<::u32>(lparam);

   //}


   //void kill_keyboard_focus::set(oswindow oswindow, ::windowing::window * pwindow, const ::atom & atom, wparam wparam, ::lparam lparam)
   //{

   //   ::user::message::set(oswindow, pwindow, atom, wparam, lparam);

   //   m_oswindowNew = (::oswindow) wparam.m_number;

   //}


   //void nc_hit_test::set(oswindow oswindow, ::windowing::window * pwindow, const ::atom & atom, wparam wparam, ::lparam lparam)
   //{

   //   ::user::message::set(oswindow, pwindow, atom, wparam, lparam);

   //   m_point.x() = x_i16(m_lparam);
   //   
   //   m_point.y() = y_i16(m_lparam);

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


   ::u32 mouse_wheel::GetFlags()
   {

      return lower_u16(m_wparam);

   }


//   i16 mouse_wheel::GetDelta()
//   {
//
//      return second_i16(m_wparam);
//
//   }


   point_i32 mouse_wheel::GetPoint()
   {

      return point_i32(i32_x(m_lparam), i32_y(m_lparam));

   }


   i32 notify::get_ctrl_id()
   {

      return (i32)m_wparam;

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

   //   ::pointer < ::particle > pparticle(lparam);

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



