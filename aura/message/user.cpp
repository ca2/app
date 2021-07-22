#include "framework.h"
#include "aura/user/_user.h"


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



   //base::base(::object * pobject) :
   //   ::message::message(psignal)
   //{

   //   m_lresult = 0;
   //   m_bDestroyed = false;
   //   m_puserinteraction = nullptr;
   //   m_plresult = &m_lresult;
   //   m_bDoSystemDefault = true;

   //}









   void create::set(oswindow oswindow, ::windowing::window * pwindow, const ::id & id, wparam wparam, ::lparam lparam)
   {

      ::user::message::set(oswindow, pwindow, id, wparam, lparam);

      //m_pusersystem = __user_interaction(pwindow)->payload("user_create").cast < ::user::system >();

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

      auto psystem = get_system()->m_paurasystem;

      psystem->log().print(pcszErrorMessage);

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


   void activate::set(oswindow oswindow, ::windowing::window * pwindow, const ::id & id, wparam wparam, ::lparam lparam)
   {

      ::user::message::set(oswindow, pwindow, id, wparam, lparam);

      m_eactivate = (enum_activate)(LOWORD(wparam));

      if(lparam == 0)
      {

         m_pWndOther = nullptr;

      }
      else
      {

         auto psession = get_session();

         auto paurasession = psession->m_paurasession;

         auto puser = paurasession->m_puser;

         auto pwindowing = puser->m_pwindowing;

         m_pWndOther = __interaction(pwindowing->window(lparam.raw_cast < ::oswindow >()));

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

      m_pkey = this;

      m_ekey = ::user::e_key_none;
      m_nScanCode = 0;
      m_nChar = 0;
      m_nRepCnt = 0;
      m_iCode = 0;
      m_bExt = false;
      m_nFlags = 0;

   }


   void key::set(oswindow oswindow, ::windowing::window * pwindow, const ::id & id, wparam wparam, ::lparam lparam)
   {

      ::user::message::set(oswindow, pwindow, id, wparam, lparam);

      m_nChar = static_cast<::u32>(wparam);

      m_nRepCnt = LOWORD(lparam);

      m_nFlags = HIWORD(lparam);

      m_nScanCode = ((lparam >> 16) & 0xff);

      m_bExt = (lparam & (1 << 24)) != 0;

   }


   nc_activate::nc_activate()
   {

   }


   void nc_activate::set(oswindow oswindow, ::windowing::window * pwindow, const ::id & id, wparam wparam, ::lparam lparam)
   {

      ::user::message::set(oswindow, pwindow, id, wparam, lparam);

      m_bActive = wparam != false;

   }


   void move::set(oswindow oswindow, ::windowing::window * pwindow, const ::id & id, wparam wparam, ::lparam lparam)
   {

      ::user::message::set(oswindow, pwindow, id, wparam, lparam);

      m_point = __point(lparam);

   }


   void size::set(oswindow oswindow, ::windowing::window * pwindow, const ::id & id, wparam wparam, ::lparam lparam)
   {

      ::user::message::set(oswindow, pwindow, id, wparam, lparam);

      m_nType     = static_cast < ::u32 > (wparam);

      m_size      = ::size_i32(LOWORD(lparam),HIWORD(lparam));

   }


   mouse::mouse()
   {

      //m_ecursor = e_cursor_unmodified;

      //m_pcursor = nullptr;

      m_pmouse = this;

      m_bTranslated = false;

   }


   mouse::~mouse()
   {

      try
      {

         auto puserinteraction = userinteraction();

         if(puserinteraction)
         {

            auto pwindow = puserinteraction->get_window();

            if (pwindow)
            {

               if (m_pcursor)
               {

                  pwindow->set_mouse_cursor(m_pcursor);

               }

            }

         }

      }
      catch(...)
      {

      }

   }


   void mouse::set(oswindow oswindow, ::windowing::window * pwindow, const ::id & id, wparam wparam, ::lparam lparam)
   {

      ::user::message::set(oswindow, pwindow, id, wparam, lparam);

      m_nFlags   = wparam;

      m_point    = __point(lparam);

#ifdef LINUX

      m_bTranslated = true;  // in root coordinates

//#elif defined(WINDOWS_DESKTOP)
//
//      m_bTranslated = true; // not in root coordinates
//
//      ::client_to_screen(m_oswindow, &m_point);

#else

      m_bTranslated = false; // not in root coordinates

#endif

   }


   void mouse_wheel::set(oswindow oswindow, ::windowing::window * pwindow, const ::id & id, wparam wparam, ::lparam lparam)
   {

      ::user::message::set(oswindow, pwindow, id, wparam, lparam);

      m_nFlags    = wparam;

      m_point        = __point(lparam);

      m_bTranslated = true;

   }


   void set_cursor::set(oswindow oswindow, ::windowing::window* pwindow, const ::id& id, wparam wparam, ::lparam lparam)
   {

      ::user::message::set(oswindow, pwindow, id, wparam, lparam);

   }


   mouse_activate::mouse_activate()
   {


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

   
   context_menu::context_menu()
   {

   }


   point_i32 context_menu::GetPoint()
   {

      return __point(m_lparam);

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


   void scroll::set(oswindow oswindow, ::windowing::window * pwindow, const ::id & id, wparam wparam, ::lparam lparam)
   {

      ::user::message::set(oswindow, pwindow, id, wparam, lparam);

      m_ecommand = (enum_scroll_command) (i16)LOWORD(wparam);

      m_nPos = (i16)HIWORD(wparam);

      m_pscrollbar = lparam.cast < ::user::primitive > ();

   }


   void show_window::set(oswindow oswindow, ::windowing::window * pwindow, const ::id & id, wparam wparam, ::lparam lparam)
   {

      ::user::message::set(oswindow, pwindow, id, wparam, lparam);

      m_bShow = wparam != false;

      m_nStatus = static_cast<::u32>(lparam);

   }


   void kill_keyboard_focus::set(oswindow oswindow, ::windowing::window * pwindow, const ::id & id, wparam wparam, ::lparam lparam)
   {

      ::user::message::set(oswindow, pwindow, id, wparam, lparam);

      m_oswindowNew = (::oswindow) wparam.m_number;

   }


   void nc_hit_test::set(oswindow oswindow, ::windowing::window * pwindow, const ::id & id, wparam wparam, ::lparam lparam)
   {

      ::user::message::set(oswindow, pwindow, id, wparam, lparam);

      m_point.x = GET_X_LPARAM(m_lparam);
      
      m_point.y = GET_Y_LPARAM(m_lparam);

   }


   void set_keyboard_focus::set(oswindow oswindow, ::windowing::window * pwindow, const ::id & id, wparam wparam, ::lparam lparam)
   {

      ::user::message::set(oswindow, pwindow, id, wparam, lparam);

      //m_puserinteraction = psystem->ui_from_handle(reinterpret_cast<oswindow>(wparam));

      //m_puserinteraction = nullptr;

   }


#ifdef WINDOWS_DESKTOP

   void window_pos::set(oswindow oswindow, ::windowing::window * pwindow, const ::id & id, wparam wparam, ::lparam lparam)
   {

      ::user::message::set(oswindow, pwindow, id, wparam, lparam);

      m_pWINDOWPOS = reinterpret_cast<void*>(lparam.m_lparam);

   }


   void nc_calc_size::set(oswindow oswindow, ::windowing::window * pwindow, const ::id & id, wparam wparam, ::lparam lparam)
   {

      ::user::message::set(oswindow, pwindow, id, wparam, lparam);

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



   i32 notify::get_ctrl_id()
   {

      return (i32)m_wparam;

   }


   object::object()
   {


   }


   object::~object()
   {


   }


   void object::set(oswindow oswindow, ::windowing::window * pwindow, const ::id & id, wparam wparam, ::lparam lparam)
   {

      ::user::message::set(oswindow, pwindow, id, wparam, lparam);

      __pointer(::matter) pmatter(lparam);

      m_pmatter = pmatter;

   }


//   text::text()
//   {
//      
//   }


} // namespace message









#define ROUND(x,y) (((x)+(y-1))&~(y-1))
#define ROUND4(x) ROUND(x, 4)

#define IMPLEMENT_SIGNAL_OBJECT_FIXED_ALLOC(class_name) IMPLEMENT_FIXED_ALLOC(class_name, ROUND4(sizeof(class_name) * 32))



