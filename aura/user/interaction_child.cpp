#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "aura/user/_user.h"
#endif
#include "apex/platform/app_core.h"


void __reposition_window(SIZEPARENTPARAMS * pLayout, ::user::interaction * pinteraction, const ::rect & rect);


namespace user
{


   interaction_child::interaction_child()
   {

      m_pinteractionchild = this;
      m_bCreate = false;
      m_puiOwner = nullptr;

   }


   //interaction_child::interaction_child(::layered * pobjectContext) :
   //   ::object(pobject)
   //{

   //   m_bCreate = false;
   //   m_puiOwner = nullptr;

   //}


   ::user::interaction_child * interaction_child::get_user_interaction_child()
   {

      return this;

   }


   interaction_child::~interaction_child()
   {

   }


   bool interaction_child::create_window_ex(::user::interaction * pinteraction, __pointer(::user::create_struct) pcreatestruct, ::user::primitive * puiParent, id id)
   {

      if (_is_window())
      {

         INFO("-------------------------------------------------------------------");
         INFO("");
         INFO("");
         INFO("interaction_child::create_window_ex (DestroyWindow)");
         INFO("");
         INFO("");

         DestroyWindow();

      }

      try
      {

         m_bCreate = true;

         m_puserinteraction = pinteraction;

         //__refer(m_pthreadUserImpl,  m_puserinteraction->m_pthreadUserInteraction  OBJ_REF_DBG_COMMA_THIS_FUNCTION_LINE);

         m_puserinteraction->m_pimpl = this;

         m_puserinteraction->m_pimpl2.release();

         m_puserinteraction->m_id = id;

         if (!m_puserinteraction->pre_create_window(pcreatestruct))
         {
            INFO("-------------------------------------------------------------------");
            INFO("");
            INFO("");
            INFO("interaction_child::create_window_ex (2)");
            INFO("");
            INFO("");

            return false;

         }

         m_puserinteraction->on_set_parent(puiParent);

         install_message_routing(m_puserinteraction);

         if (m_puserinteraction->m_ewindowflag & e_window_flag_load_window_rect_on_impl)
         {

            INFO("-------------------------------------------------------------------");
            INFO("");
            INFO("");
            INFO("interaction_child::create_window_ex (rect)");
            INFO("");
            INFO("");

            m_puserinteraction->WindowDataLoadWindowRect();

         }

         m_puserinteraction->m_ewindowflag |= e_window_flag_is_window;

         m_puserinteraction->set_window_long_ptr(GWL_STYLE, pcreatestruct->m_createstruct.style);

         auto rectChild = pcreatestruct->get_rect();

         if (rectChild.is_set())
         {

            INFO("-------------------------------------------------------------------");
            INFO("");
            INFO("");
            INFO("interaction_child::create_window_ex (rectChild %d, %d, (%d, %d))", rectChild.origin().x, rectChild.origin().y, rectChild.width(), rectChild.height());
            INFO("");
            INFO("");

            m_puserinteraction->layout().sketch() = rectChild;

         }

         string strType = m_puserinteraction->type_name();

         if(m_puserinteraction->is_host_top_level())
         {

            INFO("host_top_level");

         }
         else
         {

            if (pcreatestruct->m_createstruct.style & WS_VISIBLE)
            {

               INFO("-------------------------------------------------------------------");
               INFO("");
               INFO("");
               INFO("interaction_child::create_window_ex VISIBLE");
               INFO("");
               INFO("");

               m_puserinteraction->display();

            }
            else
            {

               INFO("-------------------------------------------------------------------");
               INFO("");
               INFO("");
               INFO("interaction_child::create_window_ex NOT VISIBLE");
               INFO("");
               INFO("");

               m_puserinteraction->hide();

            }

         }

         m_puserinteraction->send_message(e_message_create, 0, (lparam)(LPARAM)& pcreatestruct->m_createstruct);

      }
      catch (...)
      {

         m_puserinteraction->m_ewindowflag -= e_window_flag_is_window;

         m_bCreate = false;

         return false;

      }

      m_puserinteraction->m_ewindowflag |= e_window_flag_window_created;

      return true;

   }


   bool interaction_child::create_window(::user::interaction * pinteraction, const char * pszClassName, const char * pszWindowName, u32 uStyle, const ::rect & rect, ::user::primitive * puiParent, id id, ::create * pcreate)
   {

      auto pcreatestruct = __new(::user::create_struct);

      pcreatestruct->set_rect(&rect);

      pcreatestruct->m_createstruct.dwExStyle = 0;
      pcreatestruct->m_createstruct.style = uStyle;

#ifdef WINDOWS

      wstring wstrClassName(pszClassName);
      pcreatestruct->m_createstruct.lpszClass = wstrClassName;
      wstring wstrWindowName(pszWindowName);
      pcreatestruct->m_createstruct.lpszName = wstrWindowName;
#ifndef _UWP
      pcreatestruct->m_createstruct.hInstance = System.m_hinstance;
#endif

#else

      pcreatestruct->m_createstruct.lpszClass = pszClassName;
      pcreatestruct->m_createstruct.lpszName = pszWindowName;

#endif

      pcreatestruct->m_createstruct.hwndParent = puiParent->get_handle();
      pcreatestruct->m_createstruct.hMenu = nullptr;
      pcreatestruct->m_pcreate = pcreate;

      return create_window_ex(pinteraction, pcreatestruct, puiParent, id);

   }


   bool interaction_child::create_window(::user::interaction * pinteraction, const ::rect & rect, ::user::primitive * puiParent, id id)
   {

      return create_window(pinteraction, nullptr, nullptr, WS_CHILD | WS_VISIBLE, rect, puiParent, id, nullptr);

   }


   void interaction_child::VirtualOnSize()
   {

   }


   void interaction_child::install_message_routing(::channel * pchannel)
   {

      last_install_message_routing(pchannel);

      MESSAGE_LINK(e_message_destroy, pchannel, this, &interaction_child::_001OnDestroy);

      MESSAGE_LINK(e_message_show_window, pchannel, this, &interaction_child::_001OnShowWindow);

      m_puserinteraction->install_message_routing(pchannel);

      prio_install_message_routing(pchannel);

   }


   void interaction_child::_001OnShowWindow(::message::message * pmessage)
   {

      SCAST_PTR(::message::show_window, pshowwindow, pmessage);

   }


   void interaction_child::_002InstallMessageHandling(::channel * pchannel)
   {
      UNREFERENCED_PARAMETER(pchannel);
   }



   void interaction_child::CalcWindowRect(RECT32 * pClientRect, ::u32 nAdjustType)

   {
      UNREFERENCED_PARAMETER(pClientRect);

      UNREFERENCED_PARAMETER(nAdjustType);
      //u32 dwExStyle = GetExStyle();
      //if (nAdjustType == 0)
      //   dwExStyle &= ~WS_EX_CLIENTEDGE;
      //::AdjustWindowRectEx(pClientRect, GetStyle(), FALSE, dwExStyle);

   }





   bool interaction_child::SetFocus()
   {

      if (m_puserinteraction->keyboard_focus_is_focusable())
      {

         m_puserinteraction->set_keyboard_focus();

      }

      return true;

   }


   bool interaction_child::has_focus()
   {

      return ::user::primitive_impl::has_focus();

   }


   bool interaction_child::is_active()
   {

      return false;

   }


   u32 interaction_child::GetStyle() const
   {

      return ::user::primitive_impl::GetStyle();

   }


   u32 interaction_child::GetExStyle() const
   {

      return ::user::primitive_impl::GetExStyle();

   }


   //LRESULT interaction_child::default_window_procedure()
   //{

   //   return 0;

   //}


   bool interaction_child::DestroyWindow()
   {

      if (!m_bCreate)
      {

         return false;

      }

      bool bOk = ::user::primitive_impl::DestroyWindow();

      return bOk;

   }


   void interaction_child::message_handler(::message::base * pbase)
   {

      ::u32 message;

      message = pbase->m_id.umessage();

      if (m_puserinteraction != nullptr)
      {

         m_puserinteraction->GuieProc(pbase);

         if (pbase->m_bRet)
         {

            return;

         }

      }

      if (message == e_message_event)
      {

         ::user::control_event * pevent = pbase->m_lparam.cast < ::user::control_event >();

         m_puserinteraction->on_control_event(pevent);

         return;

      }

      if (::is_set(m_puserinteraction))
      {

         m_puserinteraction->route_message(pbase);

      }
      else
      {

         route_message(pbase);

      }

   }


   iptr interaction_child::get_window_long_ptr(i32 nIndex) const
   {

      return m_longptr[nIndex];

   }


   iptr interaction_child::set_window_long_ptr(i32 nIndex, iptr lValue)
   {

      auto & l = m_longptr[nIndex];

      auto lOld = l;

      l = lValue;

      return lOld;

   }


   bool interaction_child::is_this_visible(enum_layout elayout)
   {

      if (!m_puserinteraction)
      {

         return false;

      }

      if (!(m_puserinteraction->m_ewindowflag & e_window_flag_is_window))
      {

         return false;

      }

      //if (!(GetStyle() & WS_VISIBLE))
      //{

      //   return false;

      //}

      if (!m_puserinteraction->layout().state(elayout).is_visible())
      {

         return false;

      }

      return true;

   }


   void interaction_child::window_show_change_visibility(::e_display edisplay, ::e_activation eactivation)
   {

      try
      {

         if (::is_visible(edisplay))
         {

            ModifyStyle(0, WS_VISIBLE);

            m_puserinteraction->send_message(e_message_show_window, 1);

         }
         else
         {

            ModifyStyle(WS_VISIBLE, 0);

            m_puserinteraction->send_message(e_message_show_window, 0);

         }

      }
      catch (...)
      {

      }

   }


   bool interaction_child::_is_window() const
   {

      if (!m_bUserPrimitiveOk)
      {

         return false;

      }

      if (!m_bCreate)
      {

         return false;

      }

      if (m_puserinteraction == nullptr)
      {

         return false;

      }

      return true;

   }


   void interaction_child::_001OnDestroy(::message::message * pmessage)
   {

      m_bCreate = false;

      pmessage->previous();

//      __release(m_pthreadUserImpl OBJ_REF_DBG_COMMA_THIS);


   }


   void interaction_child::send_message_to_descendants(const ::id & id, WPARAM wParam, lparam lParam, bool bDeep, bool bOnlyPerm)
   {

      if (m_puserinteraction == nullptr)
      {

         return;

      }

      ::user::interaction * pinteraction = m_puserinteraction->top_child();

      while (pinteraction != nullptr)
      {

         try
         {

            pinteraction->send_message(id, wParam, lParam);

         }
         catch (...)
         {

         }

         if (bDeep)
         {

            try
            {

               pinteraction->send_message_to_descendants(id, wParam, lParam, bDeep, bOnlyPerm);

            }
            catch (...)
            {

            }

         }

         try
         {

            pinteraction = under_sibling(pinteraction);

         }
         catch (...)
         {

            break;

         }

      }

   }


   void interaction_child::set_viewport_org(::draw2d::graphics_pointer & pgraphics)
   {

      try
      {

         if (!m_puserinteraction)
         {

            return;

         }

         ::rect rectWindow;

         m_puserinteraction->get_window_rect(rectWindow, ::user::e_layout_design);

         auto pwnd = get_wnd();

         if (::is_set(pwnd))
         {

            pwnd->viewport_screen_to_client(rectWindow);

            pgraphics->SetViewportOrg(rectWindow.top_left());

         }

      }
      catch (...)
      {

      }

   }


   bool interaction_child::RedrawWindow(const ::rect & rectUpdate, ::draw2d::region * prgnUpdate, ::u32 flags)
   {

      ::user::interaction * pinteraction = get_wnd();

      if (pinteraction == nullptr)
      {

         return false;

      }

      pinteraction->RedrawWindow(rectUpdate, prgnUpdate, flags);

      return true;

   }


   void interaction_child::rects_from_system()
   {

   }


   ::user::interaction * interaction_child::SetOwner(::user::primitive * pinteraction)
   {

      m_puiOwner = pinteraction;

      return m_puiOwner->m_puiThis;

   }


   ::user::interaction * interaction_child::GetOwner() const
   {

      if (m_puiOwner != nullptr)
      {

         return m_puiOwner->m_puiThis;

      }

      return GetParent();

   }


   bool interaction_child::keyboard_focus_OnKillFocus(oswindow oswindowNew)
   {

      ::user::interaction * pinteraction = get_wnd();

      if (pinteraction != nullptr)
      {

         output_debug_string("::user::interaction_child::keyboard_focus_OnKillFocus() (1) \n");

         return pinteraction->keyboard_focus_OnChildKillFocus();

      }

      return true;

   }


   bool interaction_child::start_window_visual()
   {

      if (!m_puserinteraction)
      {

         return false;

      }

      if (m_puserinteraction->layout().window().visual() == m_puserinteraction->layout().sketch().visual())
      {

         return true;

      }

      bool bWasVisible = m_puserinteraction->layout().window().is_visible();

      bool bNewVisible = m_puserinteraction->layout().sketch().is_visible();

      bool bChangeVisibility = is_different(bWasVisible, bNewVisible);

      if (bChangeVisibility)
      {

         m_puserinteraction->_on_show_window();

      }

      return true;

   }


} // namespace user



