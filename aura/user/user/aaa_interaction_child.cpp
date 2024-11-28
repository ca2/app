#include "framework.h"
#include "interaction_child.h"
#include "interaction.h"
#include "acme/constant/message.h"
#include "aura/graphics/draw2d/graphics.h"
#include "aura/message/user.h"
#include "aura/windowing/windowing.h"


namespace user
{


   interaction_child::interaction_child()
   {

      m_pinteractionchild = this;
      m_bCreate = false;
      m_puserprimitiveOwner = nullptr;

   }


   //interaction_child::interaction_child(::particle * pparticle) :
   //   ::object(pparticle)
   //{

   //   m_bCreate = false;
   //   m_puserprimitiveOwner = nullptr;

   //}


   ::user::interaction_child * interaction_child::get_user_interaction_child()
   {

      return this;

   }


   interaction_child::~interaction_child()
   {

   }


   void interaction_child::create_child(::user::interaction * pinteraction, ::user::interaction_base * pprimitiveParent)
   {

      if (_is_window())
      {

         information() << "-------------------------------------------------------------------";
         information() << "";
         information() << "";
         information() << "interaction_child::create_window_ex (DestroyWindow)";
         information() << "";
         information() << "";

         start_destroying_window();

      }

      //try
      //{

         m_bCreate = true;

         m_puserinteraction = pinteraction;

         if (::is_null(system()))
         {

            initialize(pprimitiveParent);

         }

         //__refer(m_pthreadUserImpl,  m_puserinteraction->m_pthreadUserInteraction  REFERENCING_DEBUGGING_COMMA_THIS_FUNCTION_FILE_LINE);

         m_puserinteraction->m_pprimitiveimpl = this;

         m_puserinteraction->m_pinteractionimpl.release();

         //m_puserinteraction->m_atom = atom;

         //if (!m_puserinteraction->pre_create_window(pusersystem))
         //{
         //   information() << "-------------------------------------------------------------------";
         //   information() << "";
         //   information() << "";
         //   information() << "interaction_child::create_window_ex (2)";
         //   information() << "";
         //   information() << "";

         //   return false;

         //}

         m_puserinteraction->on_set_parent(pprimitiveParent);

         m_puserinteraction->on_after_set_parent();

         if(m_puserinteraction->m_puserinteractionOwner)
         {

            m_puserinteraction->on_set_owner(m_puserinteraction->m_puserinteractionOwner);

            ::user::interaction_base * puiRet = set_owner(m_puserinteraction->m_puserinteractionOwner);

            if (m_puserinteraction->m_ewindowflag & e_window_flag_satellite_window)
            {

               m_puserinteraction->m_pthreadUserInteraction = m_puserinteraction->m_puserinteractionOwner->m_pthreadUserInteraction;

            }

         }

         install_message_routing(m_puserinteraction);

         if (m_puserinteraction->m_ewindowflag & e_window_flag_load_window_rect_on_impl
             && (!m_puserinteraction->is_top_level()
                 || !m_puserinteraction->windowing()->is_sandboxed()))
         {

            information() << "-------------------------------------------------------------------";
            information() << "";
            information() << "";
            information() << "interaction_child::create_window_ex (rectangle)";
            information() << "";
            information() << "";

            m_puserinteraction->WindowDataLoadWindowRectangle();

         }
         else
         {
            
            m_puserinteraction->display(m_puserinteraction->const_layout().sketch().m_edisplay);
            
         }
            
            

         m_puserinteraction->m_ewindowflag |= e_window_flag_is_window;

         //m_puserinteraction->set_window_long_ptr(GWL_STYLE, pusersystem->m_createstruct.style);
         //m_puserinteraction->set_window_long_ptr(GWL_STYLE, m_puserinteraction-());

         //auto rectangleChild = pusersystem->get_rect();

         //if (rectangleChild.is_set())
         //{

         //   information() << "-------------------------------------------------------------------";
         //   information() << "";
         //   information() << "";
         //   informationf("interaction_child::create_window_ex (rectangleChild %d, %d, (%d, %d))", rectangleChild.origin().x(), rectangleChild.origin().y(), rectangleChild.width(), rectangleChild.height());
         //   information() << "";
         //   information() << "";

         //   m_puserinteraction->layout().sketch() = rectangleChild;

         //}

         string strType = ::type(m_puserinteraction).name();

         if(m_puserinteraction->is_top_level())
         {

            information() << "top_level";

         }
         else
         {

            //if (pusersystem->m_createstruct.style & WS_VISIBLE)
            //{

            //   information() << "-------------------------------------------------------------------";
            //   information() << "";
            //   information() << "";
            //   information() << "interaction_child::create_window_ex VISIBLE";
            //   information() << "";
            //   information() << "";

            //   m_puserinteraction->display();

            //}
            //else
            //{

            //   information() << "-------------------------------------------------------------------";
            //   information() << "";
            //   information() << "";
            //   information() << "interaction_child::create_window_ex NOT VISIBLE";
            //   information() << "";
            //   information() << "";

            //   m_puserinteraction->hide();

            //}

         }

         //m_puserinteraction->send_message(e_message_create, 0, (lparam)(lparam)& pusersystem->m_createstruct);
         if (!(m_puserinteraction->m_ewindowflag & ::e_window_flag_window_created))
         {
//            auto pmessage = __create_new <::message::create>();
//            pmessage->m_atom = e_message_create;
//            m_puserinteraction->send_message(pmessage);

//            m_puserinteraction->send_create_message();
            
            m_puserinteraction->send_message(e_message_create);
            
         }

         if (m_puserinteraction->m_procedureOnAfterCreate)
         {

            m_puserinteraction->m_procedureOnAfterCreate();

         }

      //}
      //catch (...)
      //{

      //   m_puserinteraction->m_ewindowflag -= e_window_flag_is_window;

      //   m_bCreate = false;

      //   return false;

      //}

      m_puserinteraction->m_ewindowflag |= e_window_flag_window_created;

      m_bUserImplCreated = true;

      m_puserinteraction->set_flag(e_flag_task_started);

      //return true;

   }

//
//   //bool interaction_child::create_interaction(::user::interaction * pinteraction, const ::string & pszClassName, const ::string & pszWindowName, unsigned int uStyle, const ::int_rectangle & rectangle, ::user::interaction_base * puiParent, atom atom, ::request * prequest)
//   bool interaction_child::create_child(::user::interaction * pinteraction, ::user::interaction_base * pprimitiveParent)
//   {
//
//      auto pusersystem = __allocate ::user::system();
//
//      ::int_rectangle rectangle;
//
//      rectangle.set(pinteraction->screen_rect());
//
//      pusersystem->set_rect(&rectangle);
//
//      unsigned int nExStyle = 0;
//
//      unsigned int nStyle = 0;
//
//      __synthesizes_creates_styles(pinteraction, nExStyle, nStyle);
//
//      pusersystem->m_createstruct.dwExStyle = nExStyle;
//      
//      pusersystem->m_createstruct.style = nStyle;
//
////#ifdef WINDOWS
////
////      wstring wstrClassName(pszClassName);
////
////      pusersystem->m_createstruct.lpszClass = wstrClassName;
////
////      wstring wstrWindowName(pszWindowName);
////
////      pusersystem->m_createstruct.lpszName = wstrWindowName;
////
////#ifndef UNIVERSAL_WINDOWS
////      pusersystem->m_createstruct.hInstance = psystem->m_hinstance;
////#endif
////
////#else
////
////      pusersystem->m_createstruct.lpszClass = pszClassName;
////      pusersystem->m_createstruct.lpszName = pszWindowName;
////
////#endif
//
//      pusersystem->m_createstruct.hwndParent = pparent->get_handle();
//      pusersystem->m_createstruct.hMenu = nullptr;
//      //pusersystem->m_pcreate = pcreate;
//
//      //return create_window_ex(pinteraction, pusersystem, puiParent, atom);
//      return _create_interaction(pinteraction, pparent);
//
//   }


   //bool interaction_child::create_interaction(::user::interaction * pinteraction, ::user::interaction_base * pparent)
   //{

   //   return _create_interaction(pinteraction, pparent);
   //   /*return create_interaction(pinteraction, nullptr, nullptr, WS_CHILD | WS_VISIBLE, rectangle, puiParent, atom, nullptr);*/

   //}


   void interaction_child::VirtualOnSize()
   {

   }


   void interaction_child::install_message_routing(::channel * pchannel)
   {

      last_install_message_routing(pchannel);

      MESSAGE_LINK(e_message_destroy, pchannel, this, &interaction_child::on_message_destroy);

      MESSAGE_LINK(e_message_show_window, pchannel, this, &interaction_child::on_message_show_window);

      m_puserinteraction->install_message_routing(pchannel);

      prio_install_message_routing(pchannel);

   }


   void interaction_child::on_message_show_window(::message::message * pmessage)
   {

      ::pointer<::message::show_window>pshowwindow(pmessage);

   }


   void interaction_child::_002InstallMessageHandling(::channel * pchannel)
   {
      __UNREFERENCED_PARAMETER(pchannel);
   }


   void interaction_child::__synthesizes_creates_styles(::user::interaction * pinteraction, unsigned int & nExStyle, unsigned int & nStyle)
   {

   }


   //void interaction_child::CalcWindowRect(::int_rectangle * pClientRect, unsigned int nAdjustType)

   //{
   //   __UNREFERENCED_PARAMETER(pClientRect);

   //   __UNREFERENCED_PARAMETER(nAdjustType);
   //   //unsigned int dwExStyle = GetExStyle();
   //   //if (nAdjustType == 0)
   //   //   dwExStyle &= ~WS_EX_CLIENTEDGE;
   //   //::AdjustWindowRectEx(pClientRect, GetStyle(), false, dwExStyle);

   //}





   //bool interaction_child::has_keyboard_focus() const
   //{

   //   if (::is_set(pinteraction) || pinteraction != m_puserinteraction)
   //   {

   //      m_puserinteraction->set_

   //   }

   //   if (::is_null(pinteraction) || pinteraction == m_puserinteraction)
   //   {

   //      m_bFocus = true;

   //      return true;


   //   }
   //   
   //   if (pinteraction == m_puserinteraction)
   //   {


   //   }


   //   return p
   //   if (m_puserinteraction->keyboard_focus_is_focusable())
   //   {

   //      m_puserinteraction->set_keyboard_focus();

   //   }

   //   return true;

   //}


   //bool interaction_child::has_keyboard_focus()
   //{

   //   return ::user::primitive_impl::has_keyboard_focus();

   //}


   //bool interaction_child::is_active()
   //{

   //   return false;

   //}


   //unsigned int interaction_child::GetStyle() const
   //{

   //   return ::user::primitive_impl::GetStyle();

   //}


   //unsigned int interaction_child::GetExStyle() const
   //{

   //   return ::user::primitive_impl::GetExStyle();

   //}


   //lresult interaction_child::default_window_procedure()
   //{

   //   return 0;

   //}


   void interaction_child::start_destroying_window()
   {

      if (!m_bCreate)
      {

         return;

      }

      //bool bOk = 
      
      ::user::primitive_impl::start_destroying_window();

      //return bOk;

   }


   void interaction_child::destroy_window()
   {

      auto puserinteraction = m_puserinteraction;

      try
      {

         puserinteraction->send_message(e_message_destroy);

      }
      catch (...)
      {


      }

      try
      {

         puserinteraction->send_message(e_message_non_client_destroy);

      }
      catch (...)
      {


      }

   }


   void interaction_child::message_handler(::message::message * pmessage)
   {

      ::message::key* pkey = nullptr;

      bool bKeyMessage = false;

      if (!m_puserinteraction)
      {

         return;

      }

      if (m_puserinteraction->pre_message_handler(pkey, bKeyMessage, pmessage))
      {

         return;

      }

      if (bKeyMessage)
      {

         //::pointer<::user::interaction>puiFocus;

         //puiFocus = m_puserinteractionFocus1;

         /////auto pkey = pmessage->m_pkey;

         //if (message == e_message_key_down)
         //{

         //   informationf("\n Key Down Event ");

         //}

         //if (puiFocus)
         //{

         //   puiFocus->route_message(pmessage);

         //}
         //else
         //{

         m_puserinteraction->route_message(pmessage);

         //         }

         if (pmessage->m_bRet)
         {

            return;

         }

         //m_wparam-

         //m_lparam = pmessage->m_lparam;

         //pmessage->set_lresult(::default_window_procedure(message, pmessage->m_wparam, pmessage->m_lparam));

         //return;

      }


      auto message = pmessage->m_atom.m_emessage;

      //if (m_puserinteraction != nullptr)
      //{

      //   //m_puserinteraction->GuieProc(pmessage);

      //   //if (pmessage->m_bRet)
      //   //{

      //   //   return;

      //   //}

      //}

      //if (message == e_message_event)
      //{

      //   ::user::control_event * phappening = pmessage->m_lparam.cast < ::user::control_event >();

      //   m_puserinteraction->handle(ptopic, pcontext);

      //   return;

      //}

      if (::is_set(m_puserinteraction))
      {

         m_puserinteraction->route_message(pmessage);

      }
      else
      {

         route_message(pmessage);

      }

   }


   //iptr interaction_child::get_window_long_ptr(int nIndex) const
   //{

   //   return m_longptr[nIndex];

   //}


   //void interaction_child::set_window_long_ptr(int nIndex, iptr lValue)
   //{

   //   auto & l = m_longptr[nIndex];

   //   auto lOld = l;

   //   l = lValue;

   //   return lOld;

   //}


//   bool interaction_child::is_this_visible(enum_layout elayout)
//   {
//
//      if (!m_puserinteraction)
//      {
//
//         return false;
//
//      }
//
//      if (!(m_puserinteraction->m_ewindowflag & e_window_flag_is_window))
//      {
//
//         return false;
//
//      }
//
//      //if (!(GetStyle() & WS_VISIBLE))
//      //{
//
//      //   return false;
//
//      //}
//
//      if (!m_puserinteraction->const_layout().state(elayout).is_visible())
//      {
//
//         return false;
//
//      }
//
//      return true;
//
//   }


//   bool interaction_child::is_there_graphics_output_interest() const
//   {
//
//      return true;
//
//   }


//   void interaction_child::_window_show_change_visibility_unlocked(::e_display edisplay, ::e_activation eactivation)
//   {
//
//      try
//      {
//
//         if (::is_visible(edisplay))
//         {
//
//            //ModifyStyle(0, WS_VISIBLE);
//
//            m_puserinteraction->send_message(e_message_show_window, 1);
//
//         }
//         else
//         {
//
//            ///ModifyStyle(WS_VISIBLE, 0);
//
//            m_puserinteraction->send_message(e_message_show_window, 0);
//
//         }
//
//      }
//      catch (...)
//      {
//
//      }
//
//      m_puserinteraction->layout().m_statea[e_layout_window].m_edisplay = edisplay;
//
//   }


   bool interaction_child::_is_window()
   {

      //if (!m_bUserElementOk)
      //{

      //   return false;

      //}

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


   void interaction_child::on_message_destroy(::message::message * pmessage)
   {

      m_bCreate = false;

      pmessage->previous();

//      __release(m_pthreadUserImpl REFERENCING_DEBUGGING_COMMA_THIS);


   }


   void interaction_child::send_message_to_descendants(const ::atom & atom, wparam wParam, lparam lParam, bool bDeep, bool bOnlyPerm)
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

            pinteraction->send_message(atom, wParam, lParam);

         }
         catch (...)
         {

         }

         if (bDeep)
         {

            try
            {

               pinteraction->send_message_to_descendants(atom, wParam, lParam, bDeep, bOnlyPerm);

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


   //void interaction_child::_000CallOnDraw(::draw2d::graphics_pointer & pgraphics)
   //{

   //   ::user::primitive_impl::_000CallOnDraw(pgraphics);

   //}


   void interaction_child::set_origin(::draw2d::graphics_pointer & pgraphics)
   {

      try
      {

         if (!m_puserinteraction)
         {

            return;

         }

         ::int_rectangle rectangleWindow;

         m_puserinteraction->window_rectangle(rectangleWindow, ::user::e_layout_design);

         auto puserinteraction = get_wnd();

         if (::is_set(puserinteraction))
         {

            puserinteraction->viewport_screen_to_client(rectangleWindow);

            pgraphics->set_origin(rectangleWindow.top_left());

         }

      }
      catch (...)
      {

      }

   }


   void interaction_child::RedrawWindow(const ::int_rectangle & rectangleUpdate, ::draw2d::region * prgnUpdate, unsigned int flags)
   {

      ::user::interaction * pinteraction = get_wnd();

      if (pinteraction == nullptr)
      {

         return;

      }

      pinteraction->RedrawWindow(rectangleUpdate, prgnUpdate, flags);

      //return true;

   }


   void interaction_child::rects_from_system()
   {

   }


   ::user::interaction_base * interaction_child::set_owner(::user::interaction_base * pinteraction)
   {

      m_puserprimitiveOwner = pinteraction;

      return m_puserprimitiveOwner->user_interaction_base();

   }


   ::user::interaction * interaction_child::get_owner()
   {

      if (m_puserprimitiveOwner != nullptr)
      {

         return m_puserprimitiveOwner->user_interaction();

      }

      return get_parent();

   }


   bool interaction_child::keyboard_focus_OnKillFocus(oswindow oswindowNew)
   {

      ::user::interaction * pinteraction = get_wnd();

      if (pinteraction != nullptr)
      {

         informationf("::user::interaction_child::keyboard_focus_OnKillFocus() (1) \n");

         return pinteraction->keyboard_focus_OnChildKillFocus();

      }

      return true;

   }


//   void interaction_child::_window_request_presentation_locked()
//   {
//
//      _window_request_presentation_unlocked();
//
//   }


//   void interaction_child::_window_request_presentation_unlocked()
//   {
//
//      if (!m_puserinteraction)
//      {
//
//         return;
//
//      }
//
//      if (m_puserinteraction->const_layout().window().visual() == m_puserinteraction->const_layout().sketch().visual())
//      {
//
//         return;
//
//      }
//
//      auto& edisplayOld = m_puserinteraction->const_layout().window().m_edisplay;
//
//      bool bWasVisible = m_puserinteraction->const_layout().window().is_visible();
//
//      auto& edisplayNew = m_puserinteraction->const_layout().sketch().m_edisplay;
//
//      bool bNewVisible = m_puserinteraction->const_layout().sketch().is_visible();
//
//      bool bChangeVisibility = is_different(bWasVisible, bNewVisible);
//
//      if (bChangeVisibility)
//      {
//
//         m_puserinteraction->_on_show_window();
//
//      }
//
//      //return true;
//
//   }


} // namespace user



