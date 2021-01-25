#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "aura/user/_user.h"
#endif


#if defined(LINUX)
// Ubuntu apt-get install libx11-dev
#include <X11/Xlib.h>
#include <X11/Xutil.h>

#endif

#undef new

struct myfx_CTLCOLOR
{
   ::oswindow oswindow;
   HDC hDC;
   ::u32 nCtlType;
};


namespace message
{


   void create::set(oswindow oswindow, ::layered * playeredUserPrimitive, const ::id & id, WPARAM wparam, ::lparam lparam)
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


   void activate::set(oswindow oswindow, ::layered * playeredUserPrimitive,const ::id & id,WPARAM wparam,::lparam lparam)
   {

      base::set(oswindow, playeredUserPrimitive, id, wparam, lparam);

      m_eactivate = (enum_activate)(LOWORD(wparam));

      if(lparam == 0)
      {

         m_pWndOther = nullptr;

      }
      else
      {

         m_pWndOther = System.ui_from_handle(lparam.cast < void >());

      }

      m_bMinimized = HIWORD(wparam) != FALSE;

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

      m_ekey = ::user::key_none;
      m_nScanCode = 0;
      m_nChar = 0;
      m_nRepCnt = 0;
      m_iCode = 0;
      m_bExt = false;
      m_nFlags = 0;

   }


#ifdef WINDOWS_DESKTOP


   // https://stackoverflow.com/questions/15966642/how-do-you-tell-lshift-apart-from-rshift-in-wm-keydown-events

   WPARAM MapLeftRightKeys(WPARAM vk, LPARAM lParam)
   {
      WPARAM new_vk = vk;
      ::u32 scancode = (lParam & 0x00ff0000) >> 16;
      int extended = (lParam & 0x01000000) != 0;
      switch (vk)
      {
      case VK_SHIFT:
         new_vk = MapVirtualKey(scancode, MAPVK_VSC_TO_VK_EX);
         break;
      case VK_CONTROL:
         new_vk = extended ? VK_RCONTROL : VK_LCONTROL;
         break;
      case VK_MENU:
         new_vk = extended ? VK_RMENU : VK_LMENU;
         break;
      default:
         // not a key we map from matter to left/right specialized
         //  just return it.
         new_vk = vk;
         break;
      }
      return new_vk;
   }


#endif


   void key::set(oswindow oswindow, ::layered * playeredUserPrimitive,const ::id & id,WPARAM wparam,::lparam lparam)
   {

      base::set(oswindow, playeredUserPrimitive, id,wparam,lparam);

      m_nChar = static_cast<::u32>(wparam);

      m_nRepCnt = LOWORD(lparam);

      m_nFlags = HIWORD(lparam);

      m_nScanCode = ((lparam >> 16) & 0xff);

      m_bExt = (lparam & (1 << 24)) != 0;

#ifdef WINDOWS_DESKTOP

      m_iVirtualKey = (int) MapLeftRightKeys(wparam, lparam);

#else

      m_iVirtualKey = -1;

#endif

      auto psession = Session;

      psession->translate_os_key_message(this);

   }


   nc_activate::nc_activate()
   {

   }


   void nc_activate::set(oswindow oswindow, ::layered * playeredUserPrimitive,const ::id & id,WPARAM wparam,::lparam lparam)
   {

      base::set(oswindow, playeredUserPrimitive, id,wparam,lparam);

      m_bActive = wparam != FALSE;

   }


   void move::set(oswindow oswindow, ::layered * playeredUserPrimitive, const ::id & id, WPARAM wparam, ::lparam lparam)
   {

      base::set(oswindow, playeredUserPrimitive, id, wparam, lparam);

      m_point = __point(lparam);

   }


   void size::set(oswindow oswindow, ::layered * playeredUserPrimitive,const ::id & id,WPARAM wparam,::lparam lparam)
   {

      base::set(oswindow, playeredUserPrimitive, id,wparam,lparam);

      m_nType     = static_cast < ::u32 > (wparam);

      m_size      = ::size(LOWORD(lparam),HIWORD(lparam));

   }


   mouse::mouse()
   {

      m_ecursor = cursor_unmodified;

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

                  psession->set_cursor(dynamic_cast <::user::interaction *> (userinteraction()), m_pcursor);

               }
               else if (m_ecursor != cursor_unmodified && papplication->get_context_session() != nullptr)
               {

                  auto psession = Sess(userinteraction()->get_context_session());

                  psession->set_cursor(dynamic_cast <::user::interaction *> (userinteraction()), m_ecursor);

               }

            }

         }

      }
      catch(...)
      {

      }

   }


   void mouse::set(oswindow oswindow, ::layered * playeredUserPrimitive,const ::id & id,WPARAM wparam,::lparam lparam)
   {

      base::set(oswindow, playeredUserPrimitive, id,wparam,lparam);

      m_nFlags   = wparam;

      m_point    = __point(lparam);

#ifdef LINUX

      m_bTranslated = true;  // in root coordinates

#elif defined(WINDOWS_DESKTOP)

      m_bTranslated = true; // not in root coordinates

      ::ClientToScreen(m_oswindow, &m_point);

#else

      m_bTranslated = false; // not in root coordinates

#endif

   }


   void mouse_wheel::set(oswindow oswindow, ::layered * playeredUserPrimitive,const ::id & id,WPARAM wparam,::lparam lparam)
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


   point context_menu::GetPoint()
   {

      return __point(m_lparam);

   }


   void scroll::set(oswindow oswindow, ::layered * playeredUserPrimitive,const ::id & id,WPARAM wparam,::lparam lparam)
   {

      base::set(oswindow, playeredUserPrimitive, id,wparam,lparam);

      m_nSBCode = (i16)LOWORD(wparam);

      m_nPos = (i16)HIWORD(wparam);

      m_pScrollBar = lparam.cast < ::user::primitive > ();

   }


   void show_window::set(oswindow oswindow, ::layered * playeredUserPrimitive,const ::id & id,WPARAM wparam,::lparam lparam)
   {

      base::set(oswindow, playeredUserPrimitive, id,wparam,lparam);

      m_bShow = wparam != FALSE;

      m_nStatus = static_cast<::u32>(lparam);

   }


   void kill_focus::set(oswindow oswindow, ::layered * playeredUserPrimitive, const ::id & id, WPARAM wparam, ::lparam lparam)
   {

      base::set(oswindow, playeredUserPrimitive, id, wparam, lparam);

      m_oswindowNew = (::oswindow) wparam;

   }


   void set_focus::set(oswindow oswindow, ::layered * playeredUserPrimitive,const ::id & id,WPARAM wparam,::lparam lparam)
   {

      base::set(oswindow, playeredUserPrimitive, id,wparam,lparam);

      //m_puserinteraction = System.ui_from_handle(reinterpret_cast<oswindow>(wparam));

      //m_puserinteraction = nullptr;

   }


#ifdef WINDOWS_DESKTOP

   void window_pos::set(oswindow oswindow, ::layered * playeredUserPrimitive,const ::id & id,WPARAM wparam,::lparam lparam)
   {

      base::set(oswindow, playeredUserPrimitive, id,wparam,lparam);

      m_pwindowpos = reinterpret_cast<WINDOWPOS*>(lparam.m_lparam);

   }


   void nc_calc_size::set(oswindow oswindow, ::layered * playeredUserPrimitive,const ::id & id,WPARAM wparam,::lparam lparam)
   {

      base::set(oswindow, playeredUserPrimitive, id,wparam,lparam);

      m_pparams = reinterpret_cast<NCCALCSIZE_PARAMS*>(lparam.m_lparam);

   }


   bool nc_calc_size::GetCalcValidRects()
   {

      return m_wparam != FALSE;

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

   point mouse_wheel::GetPoint()
   {
      return point(GET_X_LPARAM(m_lparam),GET_Y_LPARAM(m_lparam));
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

   LPNMHDR notify::get_lpnmhdr()
   {

      return (LPNMHDR)m_lparam.m_lparam;

   }

#endif

   i32 notify::get_ctrl_id()
   {

      return (i32)m_wparam;

   }


} // namespace message







