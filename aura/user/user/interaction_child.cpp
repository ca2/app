#include "framework.h"
#include "aura/platform/app_core.h"


void __reposition_window(SIZEPARENTPARAMS * pLayout, ::user::interaction * pinteraction, const ::rect & rect);


namespace user
{


   interaction_child::interaction_child()
   {

      m_pinteractionchild = this;
      m_bCreate = false;
      m_puiOwner = nullptr;

   }


   //interaction_child::interaction_child(::object * pobject) :
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


   bool interaction_child::create_window_ex(::user::interaction * pinteraction, ::user::create_struct & createstruct, ::user::interaction * puiParent, id id)
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

         if (m_puserinteraction->m_pthreadUserInteraction.is_set()
            && ::is_set(m_puserinteraction->m_pthreadUserInteraction->m_puiptraThread))
         {

            m_puserinteraction->m_pthreadUserInteraction->m_puiptraThread->remove(m_puserinteraction);

         }

         //m_pthreadUserInteraction.release();

         m_puserinteraction->m_pthreadUserInteraction = puiParent->m_pthreadUserInteraction;

         m_pthreadUserImpl = m_puserinteraction->m_pthreadUserInteraction;

         m_puserinteraction->m_pimpl = this;

         m_puserinteraction->m_pimpl2.release();

         m_puserinteraction->m_id = id;

         if (!m_puserinteraction->pre_create_window(createstruct))
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

         if (m_puserinteraction->m_ewindowflag & window_flag_load_window_rect_on_impl)
         {


            INFO("-------------------------------------------------------------------");
            INFO("");
            INFO("");
            INFO("interaction_child::create_window_ex (rect)");
            INFO("");
            INFO("");
            m_puserinteraction->WindowDataLoadWindowRect();

         }

         m_puserinteraction->m_ewindowflag |= window_flag_is_window;

         m_puserinteraction->set_window_long_ptr(GWL_STYLE, createstruct.style);

         auto rectChild = createstruct.get_rect();

         if (rectChild.is_set())
         {
            INFO("-------------------------------------------------------------------");
            INFO("");
            INFO("");
            INFO("interaction_child::create_window_ex (rectChild %d, %d, (%d, %d))", rectChild.origin().x, rectChild.origin().y, rectChild.width(), rectChild.height());
            INFO("");
            INFO("");
            m_puserinteraction->place(rectChild);

         }

         string strType = m_puserinteraction->type_name();
         
         if(m_puserinteraction->is_host_top_level())
         {
            
         INFO("host_top_level");

         }
         else
         {


         if (createstruct.style & WS_VISIBLE)
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

         m_puserinteraction->send_message(WM_CREATE, 0, (lparam)(LPARAM)& createstruct);

      }
      catch (...)
      {

         m_puserinteraction->m_ewindowflag -= window_flag_is_window;

         m_bCreate = false;

         return false;

      }

      m_puserinteraction->m_ewindowflag |= window_flag_window_created;

      return true;

   }


   bool interaction_child::create_window(::user::interaction * pinteraction, const char * pszClassName, const char * pszWindowName, u32 uStyle, const ::rect & rect, ::user::interaction * puiParent, id id, ::create * pcreate)
   {

      ::user::create_struct createstruct;

      createstruct.set_rect(&rect);

      createstruct.dwExStyle = 0;
      createstruct.style = uStyle;

#ifdef WINDOWS

      wstring wstrClassName(pszClassName);
      createstruct.lpszClass = wstrClassName;
      wstring wstrWindowName(pszWindowName);
      createstruct.lpszName = wstrWindowName;
#ifndef _UWP
      createstruct.hInstance = System.m_hinstance;
#endif

#else

      createstruct.lpszClass = pszClassName;
      createstruct.lpszName = pszWindowName;

#endif

      createstruct.hwndParent = puiParent->get_handle();
      createstruct.hMenu = nullptr;
#ifdef _UWP
      createstruct.pCreateParams = (LPVOID)pcreate;
#else
      createstruct.lpCreateParams = (LPVOID)pcreate;
#endif

      return create_window_ex(pinteraction, createstruct, puiParent, id);

   }


   bool interaction_child::create_window(::user::interaction * pinteraction, const ::rect & rect, ::user::interaction * puiParent, id id)
   {

      return create_window(pinteraction, nullptr, nullptr, WS_CHILD | WS_VISIBLE, rect, puiParent, id, nullptr);

   }


   void interaction_child::VirtualOnSize()
   {

   }


   void interaction_child::install_message_routing(::channel * pchannel)
   {

      last_install_message_routing(pchannel);

      IGUI_MSG_LINK(WM_DESTROY, pchannel, this, &interaction_child::_001OnDestroy);

      IGUI_MSG_LINK(WM_SHOWWINDOW, pchannel, this, &interaction_child::_001OnShowWindow);

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



   void interaction_child::CalcWindowRect(RECT * pClientRect, UINT nAdjustType)

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

         m_puserinteraction->keyboard_set_focus();

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

      UINT uiMessage;

      uiMessage = (UINT)(pbase->m_id.i64());

      if (m_puserinteraction != nullptr)
      {

         m_puserinteraction->GuieProc(pbase);

         if (pbase->m_bRet)
         {

            return;

         }

      }

      if (uiMessage == EVENT_MESSAGE)
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


   bool interaction_child::is_this_visible()
   {

      if (!m_puserinteraction)
      {

         return false;

      }

      if (!(m_puserinteraction->m_ewindowflag & window_flag_is_window))
      {

         return false;

      }

      //if (!(GetStyle() & WS_VISIBLE))
      //{

      //   return false;

      //}

      if (!::is_visible(m_puserinteraction->window_display()))
      {

         return false;

      }

      return true;

   }


   void interaction_child::_do_show_window()
   {

      try
      {

         //if (is_different(GetStyle() & WS_VISIBLE, is_visible(m_puserinteraction->display_state())))
         {

            if (is_visible(m_puserinteraction->display_state()))
            {

               ModifyStyle(0, WS_VISIBLE);

               m_puserinteraction->send_message(WM_SHOWWINDOW, 1);

            }
            else
            {

               ModifyStyle(WS_VISIBLE, 0);

               m_puserinteraction->send_message(WM_SHOWWINDOW, 0);

            }

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



   }


   void interaction_child::send_message_to_descendants(UINT message, WPARAM wParam, lparam lParam, bool bDeep, bool bOnlyPerm)
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

            pinteraction->send_message(message, wParam, lParam);

         }
         catch (...)
         {

         }

         if (bDeep)
         {

            try
            {

               pinteraction->send_message_to_descendants(message, wParam, lParam, bDeep, bOnlyPerm);

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
         
         m_puserinteraction->get_window_rect(rectWindow);

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


   bool interaction_child::RedrawWindow(const ::rect & rectUpdate, ::draw2d::region * prgnUpdate, UINT flags)
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


   ::user::interaction * interaction_child::SetOwner(::user::interaction * pinteraction)
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

      if (m_puserinteraction->window_state3() == m_puserinteraction->process_state())
      {

         return true;

      }

      bool bWasVisible = is_visible(m_puserinteraction->window_state3().m_edisplay3);

      bool bNewVisible = is_visible(m_puserinteraction->process_state().m_edisplay3);

      bool bChangeVisibility = is_different(bWasVisible, bNewVisible);

      if (bChangeVisibility)
      {

         m_puserinteraction->_on_show_window();

      }

      return true;

   }


} // namespace user



