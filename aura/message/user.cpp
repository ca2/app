#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "aura/user/_user.h"
#endif


#if defined(LINUX)
// Ubuntu apt-get install libx11-dev
//!!!#include <X11/Xlib.h>
//!!!#include <X11/Xutil.h>

#endif


#undef new


struct myfx_CTLCOLOR
{
   
   ::oswindow     m_oswindow;
   hdc            m_hdc;
   ::u32          m_nCtlType;


};


namespace message
{


   void create::set(oswindow oswindow, ::layered * playeredUserPrimitive, const ::id & id, wparam wparam, ::lparam lparam)
   {

      base::set(oswindow, playeredUserPrimitive, id,wparam,lparam);

      //m_pusersystem = __user_interaction(playeredUserPrimitive)->payload("user_create").cast < ::user::system >();

      //CREATESTRUCT * pusersystem = (CREATESTRUCT *)lparam.m_lparam;

      //if (pusersystem)
      //{

      //   m_pusersystem = (::user::system *)pusersystem->CREATE_STRUCT_P_CREATE_PARAMS;

      //}

   }


   void create::failed(const char * pcszErrorMessage)
   {

      error(pcszErrorMessage);

   }


   void create::error(const char * pcszErrorMessage)
   {

      m_lresult = -1;

      ///::aura::application * papp = ::get_context_system();

      TRACE("%s", pcszErrorMessage);

#ifdef __DEBUG

      System.log().print(pcszErrorMessage);

#endif //__DEBUG

   }


   ::user::system * create::get_user_create()
   {

      return m_pusersystem;

   }


   ::create * create::get_create()
   {

      auto pusersystem = get_user_create();

      if (::is_null(pusersystem))
      {

         return nullptr;

      }

      auto pcreate = pusersystem->m_pcreate;

      if (::is_null(pusersystem))
      {

         return nullptr;

      }

      return pcreate;

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


   ::matter * create::get_impact_data()
   {

      auto pusersystem = get_user_create();

      if (!pusersystem)
      {

         return nullptr;

      }

      return pusersystem->m_pimpactdata;

   }


   activate::activate()
   {

   }


   void activate::set(oswindow oswindow, ::layered * playeredUserPrimitive,const ::id & id,wparam wparam,::lparam lparam)
   {

      base::set(oswindow, playeredUserPrimitive, id, wparam, lparam);

      m_eactivate = (enum_activate)(LOWORD(wparam));

      if(lparam == 0)
      {

         m_pWndOther = nullptr;

      }
      else
      {

         auto psession = Session;

         auto puser = psession->m_puser;

         auto pwindowing = puser->m_pwindowing;

         m_pWndOther = __interaction(pwindowing->window(lparam.cast < oswindow_t >()));

      }

      m_bMinimized = HIWORD(wparam) != false;

   }


   erase_bkgnd::erase_bkgnd()
   {

   }


   void erase_bkgnd::set_result(bool bResult)
   {

      m_lresult = bResult;

   }


   key::key()
   {

      m_ekey = ::user::e_key_none;
      m_nScanCode = 0;
      m_nChar = 0;
      m_nRepCnt = 0;
      m_iCode = 0;
      m_bExt = false;
      m_nFlags = 0;

   }


   void key::set(oswindow oswindow, ::layered * playeredUserPrimitive,const ::id & id,wparam wparam,::lparam lparam)
   {

      base::set(oswindow, playeredUserPrimitive, id,wparam,lparam);

      m_nChar = static_cast<::u32>(wparam);

      m_nRepCnt = LOWORD(lparam);

      m_nFlags = HIWORD(lparam);

      m_nScanCode = ((lparam >> 16) & 0xff);

      m_bExt = (lparam & (1 << 24)) != 0;

   }


   nc_activate::nc_activate()
   {

   }


   void nc_activate::set(oswindow oswindow, ::layered * playeredUserPrimitive,const ::id & id,wparam wparam,::lparam lparam)
   {

      base::set(oswindow, playeredUserPrimitive, id,wparam,lparam);

      m_bActive = wparam != false;

   }


   void move::set(oswindow oswindow, ::layered * playeredUserPrimitive, const ::id & id, wparam wparam, ::lparam lparam)
   {

      base::set(oswindow, playeredUserPrimitive, id, wparam, lparam);

      m_point = __point(lparam);

   }


   void size::set(oswindow oswindow, ::layered * playeredUserPrimitive,const ::id & id,wparam wparam,::lparam lparam)
   {

      base::set(oswindow, playeredUserPrimitive, id,wparam,lparam);

      m_nType     = static_cast < ::u32 > (wparam);

      m_size      = ::size_i32(LOWORD(lparam),HIWORD(lparam));

   }


   mouse::mouse()
   {

      m_ecursor = e_cursor_unmodified;

      m_pcursor = nullptr;

      m_bTranslated = false;

   }


   mouse::~mouse()
   {

      try
      {

         if(userinteraction())
         {

            auto papplication = userinteraction()->get_context_application();

            if (papplication)
            {

               if (m_pcursor != nullptr && papplication->get_context_session() != nullptr)
               {

                  auto psession = Sess(userinteraction()->get_context_session());

                  auto puserinteraction = dynamic_cast <::user::interaction *> (userinteraction());

                  puserinteraction->set_cursor(m_pcursor->get_cursor());

               }
               else if (m_ecursor != e_cursor_unmodified && papplication->get_context_session() != nullptr)
               {

                  auto psession = Sess(userinteraction()->get_context_session());

                  auto puserinteraction = dynamic_cast <::user::interaction *> (userinteraction());

                  puserinteraction->set_cursor(m_ecursor);

               }

            }

         }

      }
      catch(...)
      {

      }

   }


   void mouse::set(oswindow oswindow, ::layered * playeredUserPrimitive,const ::id & id,wparam wparam,::lparam lparam)
   {

      base::set(oswindow, playeredUserPrimitive, id,wparam,lparam);

      m_nFlags   = wparam;

      m_point    = __point(lparam);

#ifdef LINUX

      m_bTranslated = true;  // in root coordinates

//#elif defined(WINDOWS_DESKTOP)
//
//      m_bTranslated = true; // not in root coordinates
//
//      ::ClientToScreen(m_oswindow, &m_point);

#else

      m_bTranslated = false; // not in root coordinates

#endif

   }


   void mouse_wheel::set(oswindow oswindow, ::layered * playeredUserPrimitive,const ::id & id,wparam wparam,::lparam lparam)
   {

      base::set(oswindow, playeredUserPrimitive, id,wparam,lparam);

      m_nFlags    = wparam;

      m_point        = __point(lparam);

      m_bTranslated = true;

   }


   ::user::interaction * mouse_activate::get_desktop_window()
   {

      ::exception::throw_not_implemented();

      //      return interaction_impl::from_handle_dup(reinterpret_cast<oswindow>(m_wparam));

      return nullptr;

   }


   ::u32 mouse_activate::GetHitTest()
   {

      return LOWORD(m_lparam);

   }


   ::u32 mouse_activate::get_message()
   {

      return HIWORD(m_lparam);

   }


   point_i32 context_menu::GetPoint()
   {

      return __point(m_lparam);

   }


   void scroll::set(oswindow oswindow, ::layered * playeredUserPrimitive,const ::id & id,wparam wparam,::lparam lparam)
   {

      base::set(oswindow, playeredUserPrimitive, id,wparam,lparam);

      m_nSBCode = (i16)LOWORD(wparam);

      m_nPos = (i16)HIWORD(wparam);

      m_pScrollBar = lparam.cast < ::user::primitive > ();

   }


   void show_window::set(oswindow oswindow, ::layered * playeredUserPrimitive,const ::id & id,wparam wparam,::lparam lparam)
   {

      base::set(oswindow, playeredUserPrimitive, id,wparam,lparam);

      m_bShow = wparam != false;

      m_nStatus = static_cast<::u32>(lparam);

   }


   void kill_focus::set(oswindow oswindow, ::layered * playeredUserPrimitive, const ::id & id, wparam wparam, ::lparam lparam)
   {

      base::set(oswindow, playeredUserPrimitive, id, wparam, lparam);

      m_oswindowNew = (::oswindow) wparam.m_number;

   }


   void set_focus::set(oswindow oswindow, ::layered * playeredUserPrimitive,const ::id & id,wparam wparam,::lparam lparam)
   {

      base::set(oswindow, playeredUserPrimitive, id,wparam,lparam);

      //m_puserinteraction = System.ui_from_handle(reinterpret_cast<oswindow>(wparam));

      //m_puserinteraction = nullptr;

   }


#ifdef WINDOWS_DESKTOP

   void window_pos::set(oswindow oswindow, ::layered * playeredUserPrimitive,const ::id & id,wparam wparam,::lparam lparam)
   {

      base::set(oswindow, playeredUserPrimitive, id,wparam,lparam);

      m_pWINDOWPOS = reinterpret_cast<void*>(lparam.m_lparam);

   }


   void nc_calc_size::set(oswindow oswindow, ::layered * playeredUserPrimitive,const ::id & id,wparam wparam,::lparam lparam)
   {

      base::set(oswindow, playeredUserPrimitive, id,wparam,lparam);

      m_pNCCALCSIZE_PARAMS = reinterpret_cast<void*>(lparam.m_lparam);

   }


   bool nc_calc_size::GetCalcValidRects()
   {

      return m_wparam != false;

   }


#endif


   bool enable::get_enable()
   {

      return m_wparam != 0;

   }


   ::u32 mouse_wheel::GetFlags()
   {
      return LOWORD(m_wparam);
   }

   i16 mouse_wheel::GetDelta()
   {
      return (i16)HIWORD(m_wparam);
   }

   point_i32 mouse_wheel::GetPoint()
   {
      return point_i32(GET_X_LPARAM(m_lparam),GET_Y_LPARAM(m_lparam));
   }

   ::u32 command::GetNotifyCode()
   {
      return HIWORD(m_wparam);
   }

   ::u32 command::GetId()
   {
      return LOWORD(m_wparam);
   }

#ifdef WINDOWS

   oswindow command::get_oswindow()
   {
      return (oswindow)m_lparam.m_lparam;
   }

#endif

#ifdef WINDOWS_DESKTOP

   //LPNMHDR notify::get_lpnmhdr()
   //{

   //   return (LPNMHDR)m_lparam.m_lparam;

   //}

#endif

   i32 notify::get_ctrl_id()
   {

      return (i32)m_wparam;

   }


} // namespace message







