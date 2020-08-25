#include "framework.h"
#include "aura/platform/app_core.h"
#include "aura/message.h"
#include "aura/const/timer.h"
#include "aura/const/id.h"




#define TEST_PRINT_BUFFER

#ifdef WINDOWS_DESKTOP
#include "aura/os/windows/windowing.h"
#define MESSAGE_WINDOW_PARENT HWND_MESSAGE
#include "aura/node/windows/system_interaction_impl.h"

#elif defined(_UWP)
//#define MESSAGE_WINDOW_PARENT HWND_MESSAGE
#include "aura/os/uwp/_uwp.h"

#endif // _UWP

#define new AURA_NEW

namespace user
{


#ifdef _UWP


   Agile<Windows::UI::Core::CoreWindow>(*interaction::s_get_os_window)(interaction * pinteraction) = &interaction::get_os_window_default;


#endif


   interaction::interaction()
   {

      user_interaction_common_construct();

   }


   void interaction::user_interaction_common_construct()
   {

      reset_window_state();

      m_bFocus = false;
      
      m_bParentScroll = true;

      m_bUserInteractionSetFinish = false;

      m_tickMouseMoveIgnore = 20_ms;

      m_bOverdraw = false;

      m_pframe = nullptr;

      m_bTrackMouseLeave = false;

      m_bSimpleUIDefaultMouseHandling = false;

      m_iIndex = -1;

      m_ewindowflag |= window_flag_enable;

      m_iMouseMoveSkipCount = 0;

      int iMouseMoveTriggerDistance = 10;

      m_iMouseMoveSkipSquareDistance = iMouseMoveTriggerDistance * iMouseMoveTriggerDistance;

      m_tickMouseMovePeriod = 5;

      m_bOffScreenRender = false;

      m_uiUserInteractionFlags = 0;

      m_eupdown = ::user::interaction::updown_normal_frame;

      m_playout = NULL;

      m_bWfiUpDownTarget = false;

      m_puiThis = this;

      //m_econtroltype = control_type_none;

      m_iItemHeight = -1;
      m_flagNonClient.add(non_client_background);
      m_flagNonClient.add(non_client_focus_rect);

      m_bMouseHover = false;

      m_bRedraw = false;

      m_bRedrawOnVisible = false;

      m_bUpdateVisual = false;

      m_bNeedLayout = false;

      m_bLockWindowUpdate = false;

      m_bRedrawing = false;
      m_bWorkspaceFullScreen = false;
      m_bHideOnTransparentFrame = false;
      m_puiThis = this;

      m_bCursorInside = false;
      m_puiOwner = nullptr;
      m_ecursor = cursor_default;
      m_bModal = false;
      m_bRectOk = false;
      m_bLayoutEnable = true;
      m_bMessageWindow = false;

      m_bVoidPaint = false;
      m_bBackgroundBypass = false;
      m_bSaveWindowRect = false;
      m_bEnableSaveWindowRect2 = false;


      m_bLockWindowUpdate = false;


      m_bDefaultWalkPreTranslateParentTree = false;

      m_bMoveWindow = false;

      m_bSizeMove = false;

      m_pointScroll.x = 0;
      m_pointScroll.y = 0;
      m_palphasource = nullptr;

      m_pform = nullptr;
      //m_pformParent = nullptr;


      // Control Member Variables BEGIN
      m_puiLabel = nullptr;
      m_pdrawcontext = nullptr;
      m_pdescriptor = nullptr;
      m_bControlExCommandEnabled = true;
      m_pform = nullptr;
      m_bDefaultWalkPreTranslateParentTree = true;
      m_bIdBound = false;
      // Control Member Variables END


   }


   interaction::~interaction()
   {

      //TRACE("::user::interaction::~interaction interaction=0x%016x %s", this, typeid(*this).name());

   }


   //bool interaction::get_element_rect(RECT* prect, e_element eelement)
   //{

   //   return false;

   //}


   e_element interaction::get_default_element() const
   {

      return element_none;

   }


   ::draw2d::font_pointer interaction::get_font(style * pstyle, e_element eelement, estate estate) const
   {

      if (pstyle)
      {

         if (pstyle->m_pfont)
         {

            return pstyle->m_pfont;

         }

      }

      return nullptr;

   }


   e_translucency interaction::get_translucency(style * pstyle) const
   {

      if (pstyle)
      {

         return pstyle->m_etranslucency;

      }

      return translucency_undefined;

   }


   int interaction::get_int(style* pstyle, enum_int eint, int iDefault) const
   {

      return iDefault;

   }


   double interaction::get_double(style* pstyle, enum_double edouble, double dDefault) const
   {

      return dDefault;

   }


   ::rect interaction::get_border(style * pstyle, e_element eelement, estate estate) const
   {

      return ::rect();

   }


   ::rect interaction::get_padding(style * pstyle, e_element eelement, estate estate) const
   {

      return ::rect();

   }


   ::rect interaction::get_margin(style * pstyle, e_element eelement, estate estate) const
   {

      return ::rect();

   }


   ::color interaction::get_color(style * pstyle, e_element eelement, estate estate) const
   {

      if (pstyle)
      {

         switch (eelement)
         {
         case element_background:
            if (pstyle->m_colorBackground.is_set())
            {

               return pstyle->m_colorBackground;

            }
            break;
         case element_text:
            if (pstyle->m_colorText.is_set())
            {

               return pstyle->m_colorText;

            }
            break;
         default:
            break;
         }

      }

      if (::is_set(pstyle))
      {

         return pstyle->get_color(this, eelement, estate);

      }

      return Session.get_color(eelement, estate);

   }





   eflag interaction::get_draw_flags(style * pstyle) const
   {

      return flag_none;
   
   }





   style* interaction::_get_style() const
   {
      
      auto pframe = GetTopLevelFrame();
      
      if(pframe)
      {
         
         return pframe->m_puserstyle;
         
      }

      return Session.user()->m_pstyle;

   }


   //style * interaction::get_style(::user::draw_context* pgraphics) const
   //{

   //   if (::is_set(pgraphics))
   //   {

   //      if (::is_set(pgraphics->m_pdrawcontext))
   //      {

   //         return pgraphics->m_pdrawcontext->m_puserstyle;

   //      }

   //   }

   //   return Application.get_style();

   //}


   void interaction::on_tsf_activate(bool bActivate)
   {

      m_pimpl2->on_tsf_activate(bActivate);

   }

   ///// if you (developer) don't know how to create a control,
   ///// you should be able (control developer pay attention now),
   ///// to build a default control with a default constructed
   ///// ::user::control_descriptor.
   //bool interaction::create_control(class control_descriptor * pdescriptor)
   //{

   //   m_pdescriptor = pdescriptor;

   //   if (!create_window(pdescriptor->m_puserinteractionParent, pdescriptor->m_id))
   //   {

   //      m_pdescriptor.release();

   //      return false;

   //   }

   //   //m_pdescriptor->m_pusercontrol = this;

   //   return true;

   //}


   string interaction::default_id_prefix() const
   {

      return string(typeid(*this).name()) + "_";

   }


   bool interaction::child_set_unique_id(::user::interaction * pinteraction)
   {

      if (pinteraction->m_id.has_char())
      {

         return true;

      }

      string strDefaultIdPrefix;

      string strCandidateId;

      bool bDuplicate = true;

      for (index iIdSuffix = 1; iIdSuffix <= 1000; iIdSuffix++)
      {

         strCandidateId.Format("%s_%d", strDefaultIdPrefix.c_str(), iIdSuffix);

         bDuplicate = false;

         for (auto & pinteraction : m_uiptraChild.ptra())
         {

            if (pinteraction->m_id == strCandidateId)
            {

               bDuplicate = true;

               break;

            }

         }

         if (!bDuplicate)
         {

            break;

         }

      }

      if (bDuplicate)
      {

         return false;

      }

      pinteraction->m_id = strCandidateId;

      return true;


   }


   /// arguments : control_descriptor
   bool interaction::add_control(arguments arguments)
   {

      arguments.insert_at(0, this);

      auto pdescriptor = __new(control_descriptor(arguments));

      //if (::is_null(pdescriptor->m_puserinteractionParent))
      //{

      //   pdescriptor->m_puserinteractionParent = this;

      //}

      __pointer(interaction) pinteraction = pdescriptor->alloc();

      if (!pinteraction)
      {

         dev_log("type " + pdescriptor->m_type.m_strName + " is not allocatable ::user::interaction");

         return false;

      }

      //auto pdescriptor = __new(control_descriptor());


      //pdescriptor->m_id = id;

      //pdescriptor->m_type = type;

      //pdescriptor->m_playout = playout;

      if (!pinteraction->create_control(pdescriptor))
      {

         return false;

      }

      if (::is_set(pdescriptor->m_playout))
      {

         pdescriptor->m_playout->on_add_layout(pinteraction);

      }

      return true;

   }


   interaction *    interaction::get_tooltip()
   {

      return m_ptooltip;

   }


   void interaction::set_reposition(bool bSetThis)
   {

      sync_lock sl(mutex_children());

      _set_reposition(bSetThis);

   }


   void interaction::_set_reposition(bool bSetThis)
   {

      if (bSetThis)
      {

         m_bReposition = true;

      }

      for (auto & pinteraction : m_uiptraChild.ptra())
      {

         pinteraction->ui_state().m_point = pinteraction->process_state().m_point;

         pinteraction->ui_state().m_pointScreen = pinteraction->ui_state().m_point;

         _001ClientToScreen(pinteraction->ui_state().m_pointScreen);

         pinteraction->process_state().m_pointScreen = pinteraction->ui_state().m_pointScreen;

         pinteraction->request_state().m_pointScreen = pinteraction->ui_state().m_pointScreen;

         pinteraction->window_state3().m_pointScreen = pinteraction->ui_state().m_pointScreen;

         pinteraction->set_reposition();

      }

   }


   void interaction::set_need_layout(bool bAscendants)
   {

      m_bNeedLayout = true;

      //if (bAscendants &&
      //      m_pdescriptor.is_set()
      //      && ::is_set(m_pdescriptor->m_puserinteractionParent))
      //{

      //   m_pdescriptor->m_puserinteractionParent->set_need_layout(true);

      //}

   }


   void interaction::set_need_redraw(bool bAscendants)
   {

      auto * pinteraction = get_wnd();

      if(::is_null(pinteraction))
      {

         pinteraction = this;

      }

      pinteraction->m_bRedraw = true;

      auto edisplayRequest = pinteraction->display_request();

      auto edisplayState = pinteraction->display_state();

      if (pinteraction->m_pimpl.is_set() &&
         (
            is_this_screen_visible() || edisplayState != edisplayRequest
         ))
      {

         pinteraction->m_pimpl->set_need_redraw();

      }

   }


   void interaction::set_need_load_form_data()
   {

      m_bNeedLoadFormData = true;

      post_message(message_need_load_form_data);

   }


   void interaction::set_need_save_form_data()
   {

      m_bNeedSaveFormData = true;

      post_message(message_need_save_form_data);

   }



   bool interaction::window_move(i32 x, i32 y)
   {

      if(!m_pimpl)
      {

         return ::user::layout::window_move(x, y);

      }

      if(!m_pimpl->window_move(x, y))
      {

         return false;

      }

      return true;

   }


   void interaction::post_redraw(bool bAscendants)
   {

      if (m_bLockWindowUpdate)
      {

         return;

      }

      auto* pinteraction = get_wnd();

      if (::is_null(pinteraction))
      {

         pinteraction = this;

      }

      auto edisplayRequest = pinteraction->display_request();

      auto edisplayState = pinteraction->display_state();

      if (pinteraction->m_pimpl.is_set() &&
         (is_this_screen_visible() || edisplayState != edisplayRequest
           || pinteraction == get_user_interaction_host()))
      {

         pinteraction->m_pimpl->post_redraw();

      }

   }


   ::user::interaction * interaction::GetTopWindow() const
   {

      if (m_pimpl != nullptr)
      {

         return m_pimpl->GetTopWindow();

      }

      __pointer(interaction) pinteraction = get_wnd();

      if (!pinteraction)
      {

         return nullptr;

      }

      return pinteraction->GetTopWindow();

   }


   ::user::interaction * interaction::get_form()
   {

      return m_pform;

   }


   void interaction::set_place_child_title(const char* pszTitle)
   {

      value("place_child_title") = pszTitle;

      //__pointer(::user::place_holder) pholder = GetParent();

      //if (pholder)
      //{

      //   auto pparent = pholder->GetParent();

      //   if (pparent)
      //   {

      //      auto pupdate = new_update();

      //      pupdate->m_id = id_place_child_title_change;

      //      pupdate->m_puserinteraction = pholder;

      //      pparent->call_update(pupdate);

      //   }

      //}

   }


   ::user::interaction * interaction::get_parent_form()
   {

      auto pform = get_form();

      if (::is_null(pform))
      {

         return nullptr;

      }

      auto pformParent = pform->get_form();

      if (::is_null(pformParent))
      {

         return pform;

      }

      return pformParent;

   }



   //::form_property_set * interaction::get_form_property_set()
   //{

   //   if (m_pformParent == nullptr)
   //   {

   //      return get_form();

   //   }

   //   return m_pformParent;

   //}


   ::user::interaction * interaction::get_bind_ui()
   {

      if (::is_null(get_context_session()))
      {

         return nullptr;

      }

      if (m_idView.is_null())
      {

         return nullptr;

      }

      return get_context_session()->get_bound_ui(m_idView);

   }


   string interaction::get_display_tag()
   {

      return "";

   }


   interaction * interaction::get_parent() const
   {

      return GetParent();

   }


   bool interaction::is_host_top_level() const
   {

      if (!::is_set(get_context_session()))
      {

         return false;

      }

      if (::is_null(get_context_session()->m_puiHost))
      {

         return false;

      }

      if (m_pdescriptor->m_puserinteractionParent != get_context_session()->m_puiHost)
      {

         return false;

      }

      return true;

   }


   interaction * interaction::GetParent() const
   {

      if (!m_pdescriptor)
      {

         return nullptr;

      }

      if (::is_set(get_context_session()))
      {

         if (m_pdescriptor->m_puserinteractionParent == get_context_session()->m_puiHost)
         {

            return nullptr;

         }

      }

      return m_pdescriptor->m_puserinteractionParent;

   }


   oswindow interaction::GetParentHandle() const
   {

      interaction * puiParent = GetParent();

      if (puiParent == nullptr)
         return nullptr;

      return puiParent->get_safe_handle();

   }


   //__pointer(place_holder) interaction::place_hold(::user::interaction * pinteraction)
   //{

   //   UNREFERENCED_PARAMETER(pinteraction);

   //   return nullptr;

   //}


   bool interaction::on_before_set_parent(::user::interaction * puiParent)
   {

      return true;

   }


   ::user::interaction * interaction::SetParent(::user::interaction * puiParent)
   {

      if (puiParent == nullptr && GetParent() == nullptr)
      {

         return nullptr;

      }

      if (puiParent != nullptr && (puiParent == this || puiParent == GetParent() || is_descendant(puiParent)))
      {

         return GetParent();

      }

      if (!on_before_set_parent(puiParent))
      {

         return GetParent();

      }

      if (m_pthreadUserInteraction.is_set() && ::is_set(m_pthreadUserInteraction->m_puiptraThread))
      {

         m_pthreadUserInteraction->m_puiptraThread->remove(this);

      }

      __release(m_pthreadUserInteraction);

      auto pimplOld = m_pimpl;

      __pointer(interaction) pparentOld = GetParent();

      if (puiParent == nullptr)
      {

         auto pimplNew = __create < ::user::interaction_impl >();

         auto strName = get_window_text();

         const char * pszClassName = nullptr;

         m_bEnableSaveWindowRect2 = true;

         on_set_parent(nullptr);

         if (m_ewindowflag & window_flag_load_window_rect_on_impl)
         {

            WindowDataLoadWindowRect();

         }

         auto rectRequest = window_request_rect();

//#ifdef WINDOWS_DESKTOP
//
//         wstring wstrClassName(pszClassName);
//
//         wstring wstrName(strName);
//
//         ::user::create_struct createstruct(get_window_long(GWL_EXSTYLE),wstrClassName, wstrName, get_window_long(GWL_STYLE), rectRequest);
//
//#else
//
         ::user::create_struct createstruct(get_window_long(GWL_EXSTYLE), pszClassName, strName, get_window_long(GWL_STYLE), rectRequest);

//#endif

         createstruct.style &= ~WS_CHILD;

         createstruct.add_visible(is_visible(display_request()));

         if (pimplOld.is_set())
         {

            pimplOld->destroy_impl_only();

         }

         if (!pimplNew->create_window_ex(this, createstruct, nullptr, GetDlgCtrlId()))
         {

            __throw(::exception::exception("could not impl interaction"));

         }
         else
         {

            on_after_set_parent();

         }

      }
      else // puiParent != nullptr
      {

         auto pimplNew = __create_new < ::user::interaction_child > ();

         pimplNew->m_puserinteraction = this;

         //Session.remove_frame(this); // no more a top level frame if it were one
         Application.remove_frame(this); // no more a top level frame if it were one

         m_pimpl = pimplNew;

         string strName;

         i32 iStyle = get_window_long(GWL_STYLE);

         iStyle |= WS_CHILD;

         if (is_visible(display_request()))
         {

            iStyle |= WS_VISIBLE;

         }

         ::rect rectWindow;

         puiParent->get_child_rect(rectWindow);

         if (pimplOld.is_set())
         {

            pimplOld->destroy_impl_only();

         }

         if (!pimplNew->create_window(this, nullptr, strName, iStyle, rectWindow, puiParent, GetDlgCtrlId()))
         {

            __throw(::exception::exception("could not impl interaction"));

         }

      }

      return pparentOld;

   }


   void interaction::install_message_routing(::channel * pchannel)
   {

      IGUI_MSG_LINK(WM_CREATE, pchannel, this, &interaction::_001OnCreate);
      IGUI_MSG_LINK(WM_DESTROY, pchannel, this, &interaction::_001OnDestroy);
      IGUI_MSG_LINK(message_text_composition, pchannel, this, &interaction::_001OnTextComposition);

      primitive::install_message_routing(pchannel);

      if (m_bMessageWindow)
      {

         //IGUI_MSG_LINK(WM_DESTROY              , pchannel, this, &interaction::_001OnDestroyMessageWindow);

      }
      else
      {

         IGUI_MSG_LINK(WM_CLOSE, pchannel, this, &interaction::_001OnClose);
         IGUI_MSG_LINK(WM_SIZE, pchannel, this, &interaction::_001OnSize);
         IGUI_MSG_LINK(WM_MOVE, pchannel, this, &interaction::_001OnMove);
         IGUI_MSG_LINK(WM_NCCALCSIZE, pchannel, this, &interaction::_001OnNcCalcSize);
         IGUI_MSG_LINK(WM_SHOWWINDOW, pchannel, this, &interaction::_001OnShowWindow);
         IGUI_MSG_LINK(WM_KILLFOCUS, pchannel, this, &interaction::_001OnKillFocus);
         IGUI_MSG_LINK(WM_SETFOCUS, pchannel, this, &interaction::_001OnSetFocus);
         IGUI_MSG_LINK(WM_DISPLAYCHANGE, pchannel, this, &interaction::_001OnDisplayChange);
         IGUI_MSG_LINK(WM_LBUTTONDOWN, pchannel, this, &interaction::_001OnLButtonDown);
         IGUI_MSG_LINK(WM_KEYDOWN, pchannel, this, &::user::interaction::_001OnKeyDown);
         IGUI_MSG_LINK(WM_ENABLE, pchannel, this, &::user::interaction::_001OnEnable);

      }
      


      IGUI_MSG_LINK(WM_COMMAND, pchannel, this, &interaction::_001OnCommand);
      IGUI_MSG_LINK(message_simple_command, pchannel, this, &interaction::_001OnSimpleCommand);



      //      ::user::impact::install_message_routing(pchannel);
      //::user::box::install_message_routing(pchannel);

      //IGUI_MSG_LINK(WM_CREATE, pchannel, this, &::user::interaction::_001OnCreate);
      //      IGUI_MSG_LINK(WM_MOUSEMOVE, pchannel, this, &::user::interaction::_001OnMouseMove);
      //
      //#ifdef WINDOWS
      //
      //      IGUI_MSG_LINK(WM_MOUSELEAVE, pchannel, this, &::user::interaction::_001OnMouseLeave);
      //
      //#else
      //
      //      //::exception::throw_not_implemented();
      //
      //#endif
      //
      //IGUI_MSG_LINK(WM_KEYDOWN, pchannel, this, &::user::interaction::_001OnKeyDown);
      //IGUI_MSG_LINK(WM_ENABLE, pchannel, this, &::user::interaction::_001OnEnable);
//      IGUI_MSG_LINK(WM_SETFOCUS, pchannel, this, &::user::interaction::_001OnSetFocus);
  //    IGUI_MSG_LINK(WM_KILLFOCUS, pchannel, this, &::user::interaction::_001OnKillFocus);


   }


   void interaction::_001OnNcCalcSize(::message::message * pmessage)
   {

      pmessage->m_bRet = true; // avoid any Microsoft-Window-concept-of-non-client-area

   }

   void interaction::set_finish()
   {

      if(m_bUserInteractionSetFinish)
      {

         return;

      }

      m_bUserInteractionSetFinish = true;

      if (GetParent() == nullptr)
      {

         display(::display_none);

         set_need_redraw();

         post_redraw();

         post_pred([this]() { on_set_finish(); });

      }

   }


   void interaction::on_set_finish()
   {

      sync_lock sl(mutex());

      m_threada.remove_all();

      if (m_pcompositea)
      {

         for (auto& pcomposite : *m_pcompositea)
         {

            if (pcomposite)
            {

               auto pthread = dynamic_cast < ::thread * > (pcomposite);

               if (pthread)
               {

                  m_threada.add(pthread);

               }

            }

         }

      }

      if(m_threada.is_empty())
      {

         sl.unlock();

         DestroyWindow();

         return;

      }

      string strWaiting;

      for (auto& pthread : m_threada)
      {

         try
         {

            strWaiting += pthread->type_name();

            strWaiting += "\r\n";

            pthread->add(procedure(DESTROY_PROCEDURE, [this, pthread]()
            {

               m_threada.remove(pthread);

               if (m_threada.is_empty())
               {

                  DestroyWindow();

               }

            }));

         }
         catch (...)
         {

         }

      }

      for (auto& pthread : m_threada)
      {

         try
         {

            pthread->set_finish();

         }
         catch (...)
         {

         }

      }

      if (strWaiting.has_char())
      {

         TRACE("The thread %s is waiting for the following threads to finish:\r\n%s", type_name(), strWaiting.c_str());

      }

      //::output_debug_string("set_finish DestroyWindow\n");

      //::output_debug_string("set_finish DestroyWindow\n");

   }


   void interaction::_001OnDestroy(::message::message * pmessage)
   {

      try
      {

         if (m_pimpl)
         {

            m_pimpl->m_bDestroying = true;

         }

      }
      catch (...)
      {

      }

      string strType;

      strType = type_name();

      if (strType.contains("main_frame"))
      {

         output_debug_string("main_frame _001OnDestroy");

      }

      UNREFERENCED_PARAMETER(pmessage);

      user_interaction_on_destroy();

      _OnDestroy();

      pmessage->previous();



   }




   void interaction::user_interaction_on_hide()
   {


      m_pimpl->user_interaction_on_hide();
      ::user::interaction * pinteraction = get_wnd();

      if(::is_set(pinteraction) && pinteraction != this && pinteraction->get_focus_primitive()== this)
      {

         pinteraction->set_focus_primitive(nullptr);

      }

      clear_prodevian();

      try
      {

         if (!m_pimpl->m_bDestroying)
         {

            for (index i = 0; i < m_uiptraChild.get_size(); i++)
            {

               try
               {

                  if (m_uiptraChild[i].is_set())
                  {

                     m_uiptraChild[i]->send_message(WM_SHOWWINDOW, 0, 1);

                  }

               }
               catch (...)
               {

               }

            }

         }

      }
      catch (...)
      {

      }

      try
      {

         for (index i = 0; i < m_uiptraOwned.get_size(); i++)
         {

            try
            {

               if (::is_set(m_uiptraOwned[i]))
               {

                  m_uiptraOwned[i]->display(display_none);

               }

            }
            catch (...)
            {

            }

         }

      }
      catch (...)
      {

      }


      try
      {

         if (get_context_application() != nullptr && get_context_application()->get_context_session() != nullptr)
         {

            ::user::interaction * puiCapture = Session.GetCapture();

            if (puiCapture != nullptr && puiCapture == this)
            {

               ReleaseCapture();

            }

         }

      }
      catch (...)
      {

      }

      try
      {

         if (mouse_hover_remove(this))
         {

            call_message_handler(WM_MOUSELEAVE);

         }

      }
      catch (...)
      {

      }

      try
      {

         auto pinteraction = get_wnd();

         if (::is_null(pinteraction) || get_wnd()->m_pimpl->m_bDestroying)
         {

            INFO("destroying os window");

         }
         else
         {

            post_pred([this]()
               {

                  if (get_context_application() != nullptr && get_context_application()->get_context_session() != nullptr && has_focus())
                  {

                     if (GetParent() == nullptr || !is_window_visible())
                     {

                        get_context_application()->get_context_session()->set_keyboard_focus(nullptr);

                     }
                     else
                     {

                        keyboard_set_focus_next();

                     }

                  }

               });

         }

      }
      catch (...)
      {

      }

#ifndef WINDOWS_DESKTOP

      if (get_context_application() != nullptr && get_context_system() != nullptr && System.get_active_ui() == this)
      {

         ::set_active_window(nullptr);

      }

#endif

      try
      {

         if (::is_set(get_context_application()))
         {

            get_context_application()->m_puiActive = nullptr;

         }

      }
      catch (...)
      {

      }

      ::user::interaction * puiParent = GetParent();

      if (puiParent != nullptr)
      {

         try
         {

            puiParent->on_hide_child(this);

         }
         catch (...)
         {

         }

      }

      if (get_context_session())
      {

         {

            sync_lock sl(Session.mutex());

            try
            {

               if (Session.m_puiLastUserInputPopup == this)
               {

                  Session.m_puiLastUserInputPopup = nullptr;

               }

            }
            catch (...)
            {

            }

         }

      }

   }


   void interaction::_001GetSel(strsize& iBeg, strsize& iEnd) const
   {


   }


   void interaction::_001GetXScrollInfo(scroll_info & info)
   {

      ::size sizeTotal = get_total_size();
      auto sizePage = get_page_size();
      auto pointOffset = get_viewport_offset();

      info.nMin = 0;
      info.nMax = sizeTotal.cx;
      info.nPage = sizePage.cx;
      info.nPos = pointOffset.x;
      info.nTrackPos = pointOffset.x;
   }

   void interaction::_001GetYScrollInfo(scroll_info & info)
   {
      auto sizeTotal = get_total_size();
      auto sizePage = get_page_size();
      auto pointOffset = get_viewport_offset();

      info.nMin = 0;
      info.nMax = sizeTotal.cy;
      info.nPage = sizePage.cy;
      info.nPos = pointOffset.y;
      info.nTrackPos = pointOffset.y;
   }


   void interaction::layout_scroll_bar()
   {

   }


   void interaction::on_remove_child(::user::interaction * pinteraction)
   {

   }


   void interaction::on_remove_place_holder_child(::user::interaction * pinteraction)
   {

   }


   void interaction::on_hide_child(::user::interaction * pinteraction)
   {

   }


   void interaction::on_hide_place_holder_child(::user::interaction * pinteraction)
   {

   }


   void interaction::user_interaction_on_destroy()
   {

      user_interaction_on_hide();

      {

         auto pimpl = m_pimpl;

         if(pimpl)
         {

            auto ptimerarray = pimpl->m_ptimerarray;

            if(ptimerarray)
            {

               ptimerarray->delete_all_timers();

            }

         }

      }

      auto pwnd = get_wnd();

#ifdef WINDOWS_DESKTOP

      if (pwnd == this)
      {

         ::KillTimer(get_handle(), timer_transparent_mouse_event);

      }

#endif

      if (pwnd == this)
      {

         prodevian_stop();

      }

      if(::is_set(pwnd) && pwnd != this)
      {

         auto pimpl = pwnd->m_pimpl2;

         if(pimpl)
         {

            sync_lock sl(pimpl->mutex());

            pimpl->m_guieptraMouseHover.remove(this);

         }

      }

      {

         sync_lock sl(mutex());

         ::thread* pthread = ::get_thread();

         if (pthread != nullptr)
         {

            if (pthread->get_active_ui() == this)
            {

               pthread->set_active_ui(nullptr);

            }

         }

      }

      ::user::interaction * puiParent = m_pdescriptor->m_puserinteractionParent;

      if (puiParent != nullptr)
      {

         try
         {

            single_lock sl(puiParent->mutex(), true);

            if (puiParent->m_bUserPrimitiveOk)
            {

               puiParent->on_remove_child(this);

               puiParent->m_uiptraChild.remove(this);

            }
            else
            {

               TRACE("Parent being destroyed");

            }

         }
         catch (...)
         {

         }

         m_pdescriptor->m_puserinteractionParent = nullptr;

      }

      if (!is_message_only_window())
      {

         if (get_context_application() != nullptr)
         {

            try
            {

               Application.remove_frame(this); // guess this may be a frame, it doesn't hurt to remove if this is not there

            }
            catch (...)
            {

            }

            if (get_context_application()->get_context_session() != nullptr)
            {

               try
               {

                  Application.remove_frame(this); // guess this may be a frame, it doesn't hurt to remove if this is not there

               }
               catch (...)
               {

               }

            }

            //if (get_context_application()->get_context_system() != nullptr)
            //{

            //   try
            //   {

            //      System.remove_frame(this); // guess this may be a frame, it doesn't hurt to remove if this is not there

            //   }
            //   catch (...)
            //   {

            //   }

            //}

         }

      }

      //if (get_context_application())
      //{

      //   if (Application.m_puiMain1 == this)
      //   {

      //      Application.m_puiMain1 = nullptr;

      //   }

      //}

      m_bUserPrimitiveOk = false;

      //if (m_pmenuitemThis.is_set() && m_pmenuitemThis->m_puserinteraction == this)
      //{

      //   m_pmenuitemThis->m_puserinteraction.release();

      //}

      //m_pmenuitemThis.release();

      m_ewindowflag -= window_flag_is_window;

      if (m_pthreadUserInteraction != nullptr
            && m_pthreadUserInteraction->m_puiptraThread != nullptr)
      {

         m_pthreadUserInteraction->m_puiptraThread->remove(this);

      }

      single_lock slDraw(get_wnd() == nullptr || get_wnd()->m_pimpl.is_null()
                         || get_wnd()->m_pimpl.cast < ::user::interaction_impl >() == nullptr ? nullptr : get_wnd()->m_pimpl.cast < ::user::interaction_impl >()->draw_mutex(), true);

      try
      {

         if (m_pimpl != nullptr)
         {

            m_pimpl->m_ptimerarray.release();

         }

      }
      catch (...)
      {

      }

      try
      {

         set_display_state(display_none);

         set_display_request(display_none);

      }
      catch (...)
      {

      }



      interaction_pointer_array uiptra;

      {

         sync_lock sl(mutex_children());

         m_uiptraChild.slice(uiptra);

      }

      for (i32 i = 0; i < uiptra.get_count(); i++)
      {

         auto pinteraction = uiptra[i];

         try
         {

            pinteraction->set_finish();

         }
         catch (...)
         {

         }

      }



      //children_post_quit_and_wait(one_minute());

      //release_parents();

   }


   void interaction::_001OnSize(::message::message * pmessage)
   {

      SCAST_PTR(::message::size, psize, pmessage);

      pmessage->previous();

      if (psize->m_nType == SIZE_MINIMIZED)
      {

         TRACE("::user::interaction::_001OnSize SIZE_MINIMIZED - ignoring event");

      }
      else if (m_pimpl->m_bIgnoreSizeEvent)
      {

         TRACE("::user::interaction::_001OnSize instructed to m_bIgnoreSizeEvent");

      }
      
      if(this == Session.m_puiHost)
      {
         
         for (auto& puserinteraction : m_uiptraChild)
         {

            puserinteraction->post_message(WM_DISPLAYCHANGE);

         }

      }

   }


   bool interaction::is_frame_window()
   {

      return false;

   }


//void interaction::translate()
//{

//   m_pimpl->on_reposition();

//   single_lock sl(mutex(), true);

//   on_reposition();

//}


//void interaction::do_show_flags()
//{

//   m_pimpl->on_show_window();

//   single_lock sl(mutex(), true);

//   on_show_window();

//}




   void interaction::show_window()
   {

      _do_show_window();

   }


   void interaction::_001OnMove(::message::message * pmessage)
   {

      pmessage->previous();

   }


   bool interaction::set_icon(::draw2d::icon * picon, bool bSmall)
   {

      if(::is_null(m_pimpl))
      {

         return false;

      }

      if(!m_pimpl->set_icon(picon, bSmall))
      {

         return false;

      }

      return true;

   }


   void interaction::set_viewport_org(::draw2d::graphics_pointer & pgraphics)
   {

      if (m_pimpl == nullptr)
         return;

      m_pimpl->set_viewport_org(pgraphics);

      //auto point = get_viewport_offset();
      
     // pgraphics->OffsetViewportOrg(point.x, point.y);

   }


   ::point interaction::get_parent_accumulated_scroll() const
   {
      
      ::point pointScroll;
      
      auto pChild = this;
   
      while(::is_set(pChild) && ::is_set(pChild->GetParent()))
      {
         
         if(pChild->m_bParentScroll)
         {
         
            pointScroll += pChild->GetParent()->m_pointScroll;
            
         }
         
         pChild = pChild->GetParent();
         
      }
      
      return pointScroll;
         
   }


   void interaction::_001OnClip(::draw2d::graphics_pointer & pgraphics)
   {

      try
      {

         ::rect rectClip;

         ::aura::draw_context * pdrawcontext = pgraphics->::aura::simple_chain < ::aura::draw_context >::get_last();

         ::rect rectClient;

         bool bFirst = true;

         string strType = type_name();

         if(strType.contains_ci("control_box"))
         {

            output_debug_string("control box on clip");

         }

         if (pdrawcontext != nullptr)
         {

            rectClient = pdrawcontext->m_rectWindow;

            _001ScreenToClient(rectClient);

            rectClient.bottom++;
            rectClient.right++;

            rectClip = rectClient;

            bFirst = false;

         }

         ::user::interaction * pinteraction = this;

         ::rect rectFocus;

         ::rect rectIntersect;

         index i = 0;
         
         while (pinteraction != nullptr)
         {

            pinteraction->get_client_rect(rectFocus);

            pinteraction->_001ClientToScreen(rectFocus);

            _001ScreenToClient(rectFocus);
            
            if (i == 0)
            {

               rectIntersect = rectFocus;

            }
            else
            {

               rectIntersect.intersect(rectFocus);

            }

            i++;

            pinteraction = pinteraction->GetParent();

         }
         
         ::rect rectClipbox;
         
         pgraphics->GetClipBox(rectClipbox);
         
         pgraphics->IntersectClipRect(rectIntersect);

      }
      catch (...)
      {

         __throw(::exception::exception("no more a window"));

      }

   }


   void interaction::_001DrawThis(::draw2d::graphics_pointer & pgraphics)
   {

      ::draw2d::savedc k(pgraphics);

      pgraphics->m_puserinteraction = this;

      if (pgraphics == nullptr)
      {

         __throw(invalid_argument_exception());

      }

      try
      {

         pgraphics->m_dFontFactor = 1.0;

         {

            sync_lock sl(mutex());

            {

#ifdef __DEBUG

               auto tickStart = tick::now();

#endif //__DEBUG

               _001OnNcDraw(pgraphics);


#ifdef __DEBUG

               auto tickEnd = tick::now();

               tick tickElapsed = tickEnd - tickStart;

               if (tickElapsed > 100)
               {

                  output_debug_string("\ndrawing took " + __str(tickElapsed.m_i) + "!!");
                  output_debug_string("\ndrawing took more than 100ms to complete!!");
                  output_debug_string("\n");

                  // let's trye to see what happened?
                  //_001OnNcDraw(pgraphics);


               }

#endif //__DEBUG

            }



         }

         //if(false)
//         {
//
//            _001OnClip(pgraphics);
//
//         }

         //throw 0;



         {

#ifdef __DEBUG

            auto tickStart = tick::now();

#endif //__DEBUG

            try
            {

               _001CallOnDraw(pgraphics);

            }
            catch (...)
            {

            }
//
//            if (!pointScroll.is_null())
//            {
//
//               pgraphics->OffsetViewportOrg(pointScroll.x, pointScroll.y);
//
//            }

#ifdef __DEBUG

            auto tickElapsed = tickStart.elapsed();

            if (tickElapsed > 50)
            {

               auto type = ::str::demangle(this->type_name());

               if (type.contains("font_list"))
               {

                  output_debug_string(type + "\n");

               }

               CINFO(prodevian)(type + " drawing took more than 50ms to complete ("+ __str(tickElapsed) +")!!\n");

               // let's trye to see what happened?
               //_001CallOnDraw(pgraphics);



            }

#endif //__DEBUG

         }



      }
      catch (...)
      {

         TRACE("Exception: interaction::_001DrawThis %s", typeid(*this).name());

      }

      if (m_pdescriptor->m_puserinteractionParent != nullptr)
      {

         {

#ifdef __DEBUG

            auto tickStart = tick::now();

#endif //__DEBUG

            on_after_graphical_update();


#ifdef __DEBUG

            auto tickEnd = tick::now();

            tick tickElapsed = tickEnd - tickStart;

            if (tickElapsed > 100)
            {

               CINFO(prodevian)("\ndrawing took " + __str(tickElapsed.m_i) + "!!");
               CINFO(prodevian)("\ndrawing took more than 100ms more than 50ms to complete!!");

               // let's trye to see what happened?
               //on_after_graphical_update();


            }

#endif //__DEBUG

         }

      }

   }


   void interaction::_001CallOnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      point pointScroll = m_pointScroll;

      if (!pointScroll.is_null())
      {

         pgraphics->OffsetViewportOrg(-pointScroll.x, -pointScroll.y);

      }

      //on_viewport_offset(pgraphics);

#ifdef __DEBUG

      auto tickStartWithLock = tick::now();

#endif

      sync_lock sl(mutex());

      {

         {

#ifdef __DEBUG

            auto tickStart = tick::now();

#endif //__DEBUG
            
            _001OnClip(pgraphics);

            get_client_rect(pgraphics->m_rectDraw);

            _001OnDraw(pgraphics);

#ifdef __DEBUG

            m_itemHover.set_drawn();

            m_itemCurrent.set_drawn();

            auto tickEnd = tick::now();

            tick tickElapsed = tickEnd - tickStart;

            if (tickElapsed > 100)
            {

               output_debug_string("\ndrawing at " + string(type_name()) + "!!");
               output_debug_string("\ndrawing took " + __str(tickElapsed.m_i) + "!!");
               output_debug_string("\ndrawing took more more than 100ms more than 50ms to complete!!");
               output_debug_string("\n");

               // let's trye to see what happened?
               //_001OnDraw(pgraphics);

            }

#endif //__DEBUG

         }

      }

#ifdef __DEBUG

      auto tickEndWithLock = tick::now();

      tick tickElapsedWithLock = tickEndWithLock - tickStartWithLock;

      if (tickElapsedWithLock > 3)
      {

		  string strType = type_name();

//         output_debug_string("\n" + strType + "drawing took " + __str(tickElapsedWithLock.m_i) + "!!");
  //       output_debug_string("\ndrawing took more than 3ms to complete!!");
    //     output_debug_string("\n");

      }

#endif //__DEBUG
      
      pgraphics->OffsetViewportOrg(pointScroll.x, pointScroll.y);

   }


   void interaction::_008CallOnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      ::draw2d::savedc k(pgraphics);

      try
      {

         set_viewport_org(pgraphics);

         sync_lock sl(mutex());

         _008OnDraw(pgraphics);

      }
      catch (...)
      {

      }

   }


   void interaction::on_viewport_offset(::draw2d::graphics_pointer & pgraphics)
   {
      
      ::point pointOffset;
      
      if (m_pdescriptor->m_puserinteractionParent != nullptr)
      {

         pointOffset = ui_state().m_point;

      }

      auto pointViewportOffset = get_viewport_offset();
      
      auto offset = pointOffset - pointViewportOffset;

      pgraphics->OffsetViewportOrg((::i32) offset.cx, (::i32) offset.cy);

   }


   sync* interaction::mutex_draw()
   {

      auto puserinteraction = get_wnd();

      if (::is_null(puserinteraction))
      {

         return nullptr;

      }

      auto pimpl = puserinteraction->m_pimpl;

      if (::is_null(pimpl))
      {

         return nullptr;

      }

      auto pinteractionimpl = pimpl->m_pinteractionimpl;

      if (::is_null(pinteractionimpl))
      {

         return nullptr;

      }

      auto pgraphics = pinteractionimpl->m_pgraphics;

      if (::is_null(pgraphics))
      {

         return nullptr;

      }

      return pgraphics->mutex();

   }


   //bool interaction::AddControlBar(::user::control_bar* pcontrolbar)
   //{

   //   return false;

   //}
   //
   //
   //bool interaction::RemoveControlBar(::user::control_bar* pcontrolbar)
   //{

   //   return false;

   //}


   void interaction::_001DrawChildren(::draw2d::graphics_pointer & pgraphics)
   {

      
      point pointScroll = m_pointScroll;
      
      bool bParentScroll = false;

      try {

      //::draw2d::savedc k(pgraphics);

      //on_viewport_offset(pgraphics);
      //// while drawing layout can occur and change z-order.
      //// keep this past z-order
      //interaction_pointer_array uia;

      //{

      //   sync_lock sl(mutex_children());

      //   uia = m_uiptraChild;

      //}

      for (auto & pinteraction : m_uiptraChild)
      {

         try
         {

            if(!pinteraction)
            {

               continue;

            }

            //::draw2d::savedc keep(pgraphics);

            if (::is_set(pinteraction) && !pinteraction->is_custom_draw())
            {
               
               if(!pointScroll.is_null())
               {
               
                  if(!bParentScroll && pinteraction->m_bParentScroll)
                  {
                     
                     pgraphics->OffsetViewportOrg(-pointScroll.x, -pointScroll.y);
                     
                     bParentScroll = true;

                  }
                  else if(bParentScroll && !pinteraction->m_bParentScroll)
                  {
                     
                     pgraphics->OffsetViewportOrg(pointScroll.x, pointScroll.y);
                     
                     bParentScroll = false;

                  }
                     
               }

               pinteraction->_000CallOnDraw1(pgraphics);

               //{

               //   //tick t1 = tick::now();

               //   pinteraction->_000OnDraw(pgraphics);

               //   ///tick d1 = t1.elapsed();

               //   //if(d1.m_i > 50)
               //   //{

               //   //   string strType = ::str::demangle(pinteraction->type_name());

               //   //   if(strType.contains("hellomultiverse") && strType.contains("frame"))
               //   //   {

               //   //      output_debug_string(".");

               //   //   }

               //   //   CINFO(prodevian)("(more than 50ms) "+strType+"::_000OnDraw took " + __str(d1.m_i) + "millis.\n");

               //   //   //pinteraction->_000OnDraw(pgraphics);

               //   //}

               //}


            }

         }
         catch (...)
         {

            TRACE("\n\nException thrown while drawing user::interaction\n\n");

         }

      }
         
      }
      catch(...)
      {
         
         
      }
      
      //pgraphics->OffsetViewportOrg(pointScroll.x, pointScroll.y);

      if (bParentScroll && !pointScroll.is_null())
      {

         pgraphics->OffsetViewportOrg(pointScroll.x, pointScroll.y);

      }

   }


   void interaction::_001PrintBuffer(::draw2d::graphics_pointer & pgraphics)
   {

      windowing_output_debug_string("\n_001UpdateBuffer : before graphics lock");

      windowing_output_debug_string("\n_001UpdateBuffer : after graphics lock");

      windowing_output_debug_string("\n_001UpdateBuffer : after check1");

      ::draw2d::savedc savedc(pgraphics);

      windowing_output_debug_string("\n_001UpdateBuffer : after savedc");

      windowing_output_debug_string("\n_001UpdateBuffer : after check2");

      ::rect rectWindow;

      get_window_rect(rectWindow);

      ::rect rect(rectWindow);

      rect.offset(-rect.top_left());

   #ifdef _UWP

      pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

   #else

      pgraphics->set_alpha_mode(::draw2d::alpha_mode_set);

   #endif

      windowing_output_debug_string("\n_001UpdateBuffer : after set alphamode");

      if (pgraphics->m_pimageimplDraw2dGraphics->is_ok())
      {

         if (m_pimpl->is_composite())
         {

            pgraphics->m_pimageimplDraw2dGraphics->fill(0);

         }
         else
         {

            pgraphics->m_pimageimplDraw2dGraphics->fill(255, 192, 192, 192);

         }

      }
      else
      {

         if (m_pimpl->is_composite())
         {

            pgraphics->fill_rect(rect, ARGB(0, 0, 0, 0));

         }
         else
         {

            if (::user::is_app_dark_mode())
            {

               pgraphics->fill_rect(rect, ARGB(255, 25, 25, 25));

            }
            else
            {

               pgraphics->fill_rect(rect, ARGB(255, 255, 255, 255));

            }

         }

      }

      windowing_output_debug_string("\n_001UpdateBuffer : before Print");

      try
      {

         _001Print(pgraphics);

      }
      catch (...)
      {


      }

   #ifdef REDRAW_HINTING

      {

         auto rectClient = m_puserinteraction->get_client_rect();

         ::rect rectHint(rectClient);

         pgraphics->SelectClipRgn(nullptr);

         pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

         pgraphics->fill_rect(rectHint, ARGB(128, __random(128, 255), __random(128, 255), __random(128, 255)));

      }

   #endif
//      pgraphics->fill_solid_rect_dim(10, 50, 200, 200, ARGB(128, __random(128, 255), __random(128, 255), __random(128, 255)));


      windowing_output_debug_string("\n_001UpdateBuffer : after Print");

   #if HARD_DEBUG

      ::draw2d::graphics_pointer g(e_create);

      g->debug();

      m_size.cx = 0;

      m_size.cy = 0;

   #endif

   }

   void interaction::_001Print(::draw2d::graphics_pointer & pgraphics)
   {

      windowing_output_debug_string("\n_001Print A");

      {

         ::draw2d::savedc k(pgraphics);

         try
         {

            _000CallOnDraw1(pgraphics);

         }
         catch (...)
         {

         }

      }

      windowing_output_debug_string("\n_001Print B");

      if (!is_null_ref(Session) && Session.m_bDrawCursor)
      {

         {

            ::draw2d::savedc k(pgraphics);

            try
            {

               ::point pointCursor;

               Session.get_cursor_pos(pointCursor);

               _001ScreenToClient(pointCursor);

               ::draw2d::cursor * pcursor = Session.get_cursor();

               if (pcursor != nullptr && pgraphics != nullptr)
               {

                  pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

                  pcursor->to(pgraphics, pointCursor);

               }

            }
            catch (...)
            {

            }

         }

      }

   }


   string interaction::calc_window_class()
   {

#ifdef WINDOWS_DESKTOP

      return "windows_interaction_impl";

      //u32 uStyle = get_window_default_style();

      //string strIcon = get_window_icon_matter();

      //if (strIcon.has_char())
      //{

      //   return windows_calc_icon_window_class(this, uStyle, strIcon);

      //}
      //else
      //{

      //   return windows_get_user_interaction_window_class(this);

      //}

#else

      return "";

#endif

   }


   bool interaction::_000OnBeforeDraw(::draw2d::graphics_pointer & pgraphics)
   {

      //if (GetParent() != nullptr || Session.m_puiHost.is_set())
      //{

      //   bool bUpdateBuffer = false;

      //   bool bUpdateWindow = false;

      //   prodevian_update_visual(bUpdateBuffer, bUpdateWindow);

      //}

      //if (!is_this_visible() || m_bLockWindowUpdate)
      //{

      //   return false;

      //}

      return true;

   }


   void interaction::_000CallOnDraw1(::draw2d::graphics_pointer & pgraphics)
   {

      if (!(m_ewindowflag & window_flag_window_created))
      {

         set_need_redraw();

         post_redraw();

         return;

      }

      bool bUpdateBuffer = false;

      bool bUpdateWindow = false;

      string strType(type_c_str());

      if (strType.contains_ci("albertopibiri_keyboard") && strType.contains_ci("main_frame"))
      {

         output_debug_string("albertopibiri_keyboard::main_frame");

      }
      else if (strType.contains_ci("plain_edit"))
      {

         output_debug_string("plain_edit");

      }

      prodevian_update_visual(bUpdateBuffer, bUpdateWindow);

      if (!is_this_visible() || m_bLockWindowUpdate)
      {

         return;

      }

      ::point pointOffset;
      
      if (m_pdescriptor->m_puserinteractionParent != nullptr)
      {

         pointOffset = ui_state().m_point;

      }

      if (!pointOffset.is_null())
      {

         pgraphics->OffsetViewportOrg(pointOffset.x, pointOffset.y);

      }

      try
      {

         _000OnDraw1(pgraphics);

      }
      catch (...)
      {

      }

      if (!pointOffset.is_null())
      {

         pgraphics->OffsetViewportOrg(-pointOffset.x, -pointOffset.y);

      }
      


   }


   void interaction::_000OnDraw1(::draw2d::graphics_pointer & pgraphics)
   {

      try
      {

         //string strType = type_name();

         //if (strType == "type_messing_viewport_offset_question")
         //{

         //   if (!is_custom_draw() && pgraphics->m_pnext == nullptr)
         //   {

         //      set_viewport_org(pgraphics);

         //   }

         //}
         ////         ::point pointParentOffset = get_parent_viewport_offset();
         ////
         ////         pgraphics->OffsetViewportOrg(-pointParentOffset.x, -pointParentOffset.y);

         try
         {

            _001DrawThis(pgraphics);

         }
         catch (...)
         {

            TRACE("Exception: interaction::_000OnDraw _001DrawThis %s", typeid(*this).name());

         }

      }
      catch (...)
      {

      }

      try
      {

         if (m_uiptraChild.has_elements())
         {

            try
            {

               _001DrawChildren(pgraphics);

            }
            catch (...)
            {

               TRACE("Exception: interaction::_000OnDraw _001DrawChildren %s", typeid(*this).name());

            }

         }

      }
      catch (...)
      {

      }

      try
      {

         if (m_bOverdraw)
         {

            {

               tick t1 = tick::now();

               _008CallOnDraw(pgraphics);

               tick d1 = t1.elapsed();

               if (d1.m_i > 50)
               {

                  string strType = type_name();

                  CINFO(prodevian)("(more than 50ms) " + strType + "::_008CallOnDraw took " + __str(d1.m_i) + "millis.\n");

               }

            }

         }
         
      }
      catch(...)
      {
         
         
      }

   }


   //void interaction::_001OnNcDraw(::draw2d::graphics_pointer & pgraphics)
   //{

   //   if (m_flagNonClient.has(non_client_background))
   //   {

   //      draw_control_background(pgraphics);

   //   }

   //}


   //void interaction::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   //{


   //}

   void interaction::_008OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

   }


   void interaction::draw_control_background(::draw2d::graphics_pointer & pgraphics)
   {

      ::aura::draw_context * pdrawcontext = pgraphics->::aura::simple_chain < ::aura::draw_context >::get_last();

      ::rect rectClient;

      if (pdrawcontext != nullptr)
      {

         rectClient = pdrawcontext->m_rectClient;

      }
      else
      {

         get_client_rect(rectClient);

      }

      auto pstyle = get_style(pgraphics);

      if (get_draw_flags(pstyle) & e_flag_background_bypass)
      {

      }
      else if (get_translucency(pstyle) >= translucency_total)
      {

      }
      else if (get_translucency(pstyle) >= translucency_present)
      {

         pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

         auto colorBackground = get_color(pstyle, element_background);

         //if (colorref_get_r_value(crBackground) != 255)
         //{

         //   output_debug_string("no full red");

         //}

         if (colorBackground.is_set())
         {

            pgraphics->fill_rect(rectClient, colorBackground);

         }

      }
      else
      {

         pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

         auto colorBackground = get_color(pstyle, element_background);

         //if (colorref_get_r_value(crBackground) != 255)
         //{

         //   output_debug_string("no full red");

         //}

         pgraphics->fill_rect(rectClient, colorBackground);

      }

   }


   bool interaction::is_custom_draw()
   {

      return false;

   }




   bool interaction::add_prodevian(::context_object * pobject)
   {

      if (get_wnd() == nullptr)
      {

         return false;

      }

      return get_wnd()->m_pimpl->add_prodevian(pobject);

   }


   bool interaction::remove_prodevian(::context_object * pobject)
   {

      if (get_wnd() == nullptr)
      {

         return false;

      }

      return get_wnd()->m_pimpl->remove_prodevian(pobject);

   }


   void interaction::default_message_handler(::message::message * pmessage)
   {

      if (!m_pimpl)
      {

         return;

      }

      m_pimpl->default_message_handler(pmessage);

   }


   void interaction::_001OnTextComposition(::message::message * pmessage)
   {

      string strText;

      bool bOk = false;

      try
      {

         string * pstringText = (string *) (iptr) (LPARAM) pmessage->m_lparam.m_lparam;

         if(pstringText)
         {

            strText = *pstringText;

            ::aura::del(pstringText);

            bOk = true;

         }

      }
      catch(...)
      {

      }

      if(bOk)
      {

         auto pprimitive = Session.get_keyboard_focus();

         if(pprimitive)
         {

            pprimitive->on_text_composition(strText);

         }
         else
         {

            on_text_composition(strText);

         }

      }

   }


   void interaction::_001OnDisplayChange(::message::message* pmessage)
   {

      _001InitialFramePosition();

   }


   void interaction::on_create_user_interaction()
   {


   }


   ::user::item* interaction::get_user_item(const ::user::item& item)
   {

      for (auto& pitem : m_itema)
      {

         if (*pitem == item)
         {

            return pitem;

         }

      }

      return nullptr;

   }


   LRESULT interaction::_OnCreate(VOID)
   {

      return 0;

   }


   LRESULT interaction::_OnDestroy(VOID)
   {

      return 0;

   }


   LRESULT interaction::_OnSetFocus(VOID)
   {

      return 0;

   }


   LRESULT interaction::_OnKillFocus(VOID)
   {

      return 0;

   }

   void interaction::_001OnCreate(::message::message * pmessage)
   {

      UNREFERENCED_PARAMETER(pmessage);

      on_create_user_interaction();

      run_property("on_create");

      runall(CREATE_PROCEDURE);

      runall(CREATE_PROCEDURE);

      sync_style();

      m_bUserPrimitiveOk = true;

      m_ewindowflag |= window_flag_is_window;


      ::user::control_event ev;

      ev.m_puie = this;

      ev.m_eevent = ::user::event_create;

      on_control_event(&ev);


//      if (get_context_application() == nullptr)
//      {

//         __throw(::exception::exception("get_context_application() cannot be null"));

//      }

      {

         //get_context_application()->add(this);
         if ((GetParent() == nullptr || GetParent() == Session.m_puiHost)
            && !is_message_only_window()
            && Session.m_puiHost != this)
         {

            sync_lock sl(mutex());

            //if (get_context_application()->get_context_system() != nullptr)
            //{

            //   System.add_frame(this);

            //}

            //if (get_context_application()->get_context_session() != nullptr)
            //{

            //   Session.add_frame(this);

            //}

            if (get_context_application() != nullptr)
            {

               Application.add_frame(this);




            }

         }

      }

      defer_create_mutex();

      try
      {
         if ((GetParent() != nullptr && GetParent() != Session.m_puiHost)
               && !is_message_only_window()
               && Session.m_puiHost != this
            )
         {

            //__pointer(place_holder) pholder = GetParent();

            //if (pholder.is_set())
            //{

            //   // A Copy Paste error (the commented out code below)?
            //   //single_lock sl(puiParent->mutex(),TRUE);
            //   //single_lock sl2(mutex(),TRUE);

            //   if (!pholder->is_place_holding(this))
            //   {

            //      pholder->place_hold(this);

            //   }

            //}

         }

      }
      catch (...)
      {

      }

      send_message(message_change_experience);

      _OnCreate();

   }


   void interaction::_000OnDrag(::message::drag_and_drop * pdrag)
   {

#ifdef WINDOWS

      if (pdrag->m_id != MESSAGE_OLE_DRAGLEAVE)
      {

         try
         {

            if (!is_window_visible())
            {

               return;

            }

            if (!_001IsPointInside(point(pdrag->point.x, pdrag->point.y)))
            {

               return;

            }

         }
         catch (...)
         {
            return;
         }

      }

      // these try catchs are needed for multi threading : multi threaded windows: the hell
      // Now I understand why Microsoft (TM) Windows (R) windows are single threaded.

      __pointer(::user::interaction) pinteraction = top_child();

      //      i32 iSize;

      try
      {

         while (pinteraction != nullptr)
         {

            try
            {

               if (pinteraction->is_window_visible() && (pdrag->m_id == MESSAGE_OLE_DRAGLEAVE || pinteraction->_001IsPointInside(point(pdrag->point.x, pdrag->point.y))))
               {

                  try
                  {

                     pinteraction->_000OnDrag(pdrag);

                     if (pdrag->m_bRet)
                     {

                        return;

                     }

                  }
                  catch (...)
                  {

                  }

               }

               pinteraction = pinteraction->under_sibling();

            }
            catch (...)
            {

            }

         }

      }
      catch (...)
      {

      }

      try
      {

         if (m_pimpl == nullptr)
         {

            return;

         }

         route_message(pdrag);

         if (pdrag->m_bRet)
         {

            return;

         }

      }
      catch (...)
      {

      }

#endif

   }

   double interaction::get_rotate()
   {

      return 0.0;

   }


   void interaction::_000OnMouseLeave(::message::message* pmessage)
   {

      m_pimpl->_000OnMouseLeave(pmessage);

   }


   void interaction::_000OnMouse(::message::mouse * pmouse)
   {

      // must lock ::user::mutex_children() at top stack chain
      // and only at top stack chain.

      bool bThisCapture = false;

      try
      {

         if (!is_window_visible())
         {

            return;

         }

         bThisCapture = Session.m_puiCapture == this;

         if (!bThisCapture && !is_descendant(Session.m_puiCapture) && !_001IsPointInside(pmouse->m_point))
         {

            return;

         }

      }
      catch (...)
      {

         return;

      }

      if (bThisCapture)
      {

         _000OnThisMouse(pmouse);

         if (pmouse->m_bRet)
         {

            return;

         }

         _000OnChildrenMouse(pmouse);

      }
      else
      {

         _000OnChildrenMouse(pmouse);

         if (pmouse->m_bRet)
         {

            return;

         }

         _000OnThisMouse(pmouse);

      }

   }


   void interaction::_000OnThisMouse(::message::mouse * pmouse)
   {

      try
      {

         if (m_pimpl == nullptr)
         {

            return;

         }

         route_message(pmouse);

         if (pmouse->m_lresult != 0)
         {

            return;

         }

      }
      catch (...)
      {

      }

   }


   void interaction::_000OnChildrenMouse(::message::mouse * pmouse)
   {

      // must lock ::user::mutex_children() at top stack chain
      // and only at top stack chain.

      // these try catchs are needed for multi threading : multi threaded windows: the hell
      // Now I understand why many OSes windows are single threaded.
      __pointer(::user::interaction) pinteraction;

      try
      {
         while (m_uiptraChild.rget_child(pinteraction))
         {
            try
            {
               if (!pinteraction)
               {
                  continue;
               }
               if (pinteraction->is_window_visible() && pinteraction->_001IsPointInside(pmouse->m_point))
               {
                  try
                  {
                     pinteraction->_000OnMouse(pmouse);
                     if (pmouse->m_bRet)
                        return;
                  }
                  catch (...)
                  {
                  }
               }
            }
            catch (...)
            {
            }
         }
      }
      catch (...)
      {
      }

   }


   void interaction::_000OnKey(::message::key * pkey)
   {

      if (!(pkey->m_uiMessageFlags & 1)) // message already pre translated
      {

         pre_translate_message(pkey);

         if(pkey->m_bRet)
         {

            return;

         }

         pkey->m_uiMessageFlags |= 1;

      }

      ::point pointCursor;

      Session.get_cursor_pos(&pointCursor);

      if (!pkey->m_bRet)
      {

         // these try catchs are needed for multi threading : multi threaded windows: the hell
         // Now I understand why Microsoft (TM) Windows (R) windows are single threaded.

         ::user::interaction * pinteraction = top_child();

         //         i32 iSize;

         try
         {

            while (pinteraction != nullptr)
            {

               try
               {

                  if (pinteraction->is_window_visible())
                  {

                     try
                     {

                        pinteraction->_000OnKey(pkey);

                        if (pkey->m_bRet)
                        {

                           return;

                        }

                     }
                     catch (...)
                     {

                     }

                  }

                  pinteraction = pinteraction->under_sibling();

               }
               catch (...)
               {

               }

            }

         }
         catch (...)
         {

         }

         //try
         //{

         //   m_pimpl->route_message(pkey);

         //   if (pkey->get_lresult() != 0)
         //   {

         //      return;

         //   }

         //}
         //catch (...)
         //{

         //}

      }

   }


   ::user::interaction * interaction::_001FromPoint(::point point, bool bTestedIfParentVisible)
   {

      if (bTestedIfParentVisible)
      {

         if (!is_this_visible() || !_001IsPointInside(point)) // inline version - do not need pointer to the function
         {

            return nullptr;

         }

      }
      else
      {

         if (!is_window_visible() || !_001IsPointInside(point)) // inline version - do not need pointer to the function
         {

            return nullptr;

         }

      }

      __pointer(interaction) pinteraction = top_child();

      while (pinteraction != nullptr)
      {

         __pointer(interaction) puie = pinteraction->_001FromPoint(point, true);

         if (puie != nullptr)
         {

            return puie;

         }

         pinteraction = pinteraction->under_sibling();

      }

      return this;

   }


   bool interaction::_001IsPointInside(::point point)
   {

      if (m_pimpl.is_null())
      {

         return false;

      }

      if (!is_window_screen_visible())
      {

         return false;

      }

      ::rect rectWindow;
      
      get_window_rect(rectWindow);

      return rectWindow.contains(point);

   }


   void interaction::_001OnKeyDown(::message::message * pmessage)
   {
      //if(Session.get_keyboard_focus() != this
      //   && Session.get_keyboard_focus() != nullptr)
      //{
      // Session.get_keyboard_focus()->keyboard_focus_OnKeyDown(pmessage);
      //}
   }

   void interaction::_001OnKeyUp(::message::message * pmessage)
   {
      //if(Session.get_keyboard_focus() != this
      ///&& Session.get_keyboard_focus() != nullptr)
      //{
      // Session.get_keyboard_focus()->keyboard_focus_OnKeyUp(pmessage);
      //}
   }

   void interaction::_001OnChar(::message::message * pmessage)
   {
      //if(Session.get_keyboard_focus() != this
      // && Session.get_keyboard_focus() != nullptr)
      //{
      // Session.get_keyboard_focus()->keyboard_focus_OnChar(pmessage);
      //}
   }


   void interaction::_001OnTimer(::timer * ptimer)
   {

   }


   bool interaction::on_timer(::timer * ptimer)
   {

      _001OnTimer(ptimer);

      return true;

   }


   ::user::interaction * interaction::get_child_by_name(const char * lpszName, i32 iLevel)
   {
      __pointer(interaction) pinteraction = top_child();
      while (pinteraction != nullptr)
      {
         if (pinteraction->m_strName == lpszName)
         {
            return pinteraction;
         }
         pinteraction = pinteraction->under_sibling();
      }
      __pointer(interaction) pchild;
      if (iLevel > 0 || iLevel == -1)
      {
         if (iLevel > 0)
         {
            iLevel--;
         }
         __pointer(interaction) pinteraction = top_child();
         while (pinteraction != nullptr)
         {
            pchild = pinteraction->get_child_by_name(lpszName, iLevel);
            if (pchild != nullptr)
               return pchild;
            pinteraction = pinteraction->under_sibling();
         }
      }
      return nullptr;
   }


   ::user::interaction * interaction::get_child_by_id(id id, i32 iLevel)
   {

      sync_lock sl(::user::mutex_children());

      for (index i = m_uiptraChild.get_upper_bound(); i >= 0; i--)
      {

         ::user::interaction * pinteraction = m_uiptraChild[i];

         if (pinteraction->GetDlgCtrlId() == id)
         {

            return pinteraction;

         }

      }

      if (iLevel == 0)
      {

         return nullptr;

      }
      else if(iLevel > 0)
      {

         iLevel--;

      }

      for (index i = m_uiptraChild.get_upper_bound(); i >= 0; i--)
      {

         ::user::interaction * pinteraction = m_uiptraChild[i];

         ::user::interaction * puiChild = pinteraction->get_child_by_id(id, iLevel);

         if (::is_set(puiChild))
         {

            return puiChild;

         }

      }

      return nullptr;

   }



   void interaction::_002OnLButtonDown(::message::message * pmessage)
   {
      UNREFERENCED_PARAMETER(pmessage);
   }

   void interaction::_002OnLButtonUp(::message::message * pmessage)
   {
      UNREFERENCED_PARAMETER(pmessage);
   }

   void interaction::_002OnMouseMove(::message::message * pmessage)
   {
      UNREFERENCED_PARAMETER(pmessage);
   }

   void interaction::_002OnMouseEnter(::message::message * pmessage)
   {
      UNREFERENCED_PARAMETER(pmessage);
   }

   void interaction::_002OnMouseLeave(::message::message * pmessage)
   {

      UNREFERENCED_PARAMETER(pmessage);

   }


   void interaction::_002OnKeyDown(::message::message * pmessage)
   {

      UNREFERENCED_PARAMETER(pmessage);

   }


   void interaction::_002OnKeyUp(::message::message * pmessage)
   {

      UNREFERENCED_PARAMETER(pmessage);

   }


   void interaction::_002OnTimer(::message::message * pmessage)
   {

      UNREFERENCED_PARAMETER(pmessage);

   }


   LRESULT interaction::send(::message::base * pbase)
   {

      message_handler(pbase);

      return pbase->m_lresult;

   }


   bool interaction::post(::message::base * pbase)
   {

      if(pbase->m_id == WM_KEYDOWN)
      {

         output_debug_string("::user::interaction::post WM_KEYDOWN");

      }

      return post_message(message_post_user, 1, pbase);

   }


   LRESULT interaction::send_message(UINT uiMessage, WPARAM wparam, lparam lparam)
   {

      if (m_pimpl == nullptr)
      {

         return 0;

      }

      return m_pimpl->send_message(uiMessage, wparam, lparam);

   }


   LRESULT interaction::message_call(UINT uiMessage, WPARAM wparam, lparam lparam)
   {

      if (m_pimpl == nullptr)
      {

         return 0;

      }

      return m_pimpl->message_call(uiMessage, wparam, lparam);

   }


   LRESULT interaction::message_call(::message::base * pbase)
   {

      if (m_pimpl == nullptr)
      {

         return 0;

      }

      return m_pimpl->message_call(pbase);

   }


#ifdef LINUX


   LRESULT interaction::send_x11_event(void * pevent)
   {

      if (m_pimpl == nullptr)
      {

         return false;

      }
      else
      {

         return m_pimpl->send_x11_event(pevent);

      }

   }


#endif


   bool interaction::enable_window(bool bEnable)
   {

      if (m_pimpl == nullptr)
      {

         return false;

      }

      return m_pimpl->enable_window(bEnable);

   }


   void interaction::SetWindowDisplayChanged()
   {

      if (m_pimpl.is_null())
      {

         return;

      }

      m_pimpl->SetWindowDisplayChanged();

   }


   bool interaction::is_this_enabled() const
   {

      if (m_pimpl == nullptr)
      {

         return false;

      }

      return m_pimpl->is_this_enabled();

   }


   void interaction::send_message_to_descendants(UINT message, WPARAM wparam, lparam lparam, bool bDeep, bool bOnlyPerm)

   {

      if (m_pimpl == nullptr)
      {

         return;

      }

      sync_lock sl(::user::mutex_children());

      auto uiptraChild = m_uiptraChild;

      sl.unlock();

      for (auto & pinteraction : uiptraChild.ptra())
      {

         try
         {

            pinteraction->send_message(message, wparam, lparam);


         }
         catch (...)
         {

         }

      }

      if (!bDeep)
      {

         return;

      }

      for (auto & pinteraction : uiptraChild.ptra())
      {

         try
         {

            pinteraction->send_message_to_descendants(message, wparam, lparam, true, bOnlyPerm);


         }
         catch (...)
         {

         }

      }

   }


   void interaction::route_message_to_descendants(::message::message * pmessage)
   {

      if (m_pimpl == nullptr)
      {

         return;

      }

      interaction_pointer_array uiptraChild;

      {

         sync_lock sl(mutex());

         uiptraChild = m_uiptraChild;

      }

      for (auto & puiChild : uiptraChild.ptra())
      {

         try
         {

            puiChild->route_message_to_descendants(pmessage);

         }
         catch (...)
         {

         }

      }

   }


   //void interaction::pre_translate_message(::message::message * pmessage)
   //{

   //   UNREFERENCED_PARAMETER(pmessage);

   //   //SCAST_PTR(::message::base, pbase, pmessage);

   //   //if(pbase->m_id == WM_KEYDOWN)
   //   //{

   //   //   SCAST_PTR(::message::key,pkey,pmessage);

   //   //   if(pkey->m_ekey == ::user::key_tab)
   //   //   {

   //   //      ::user::control_event ev;

   //   //      ev.m_puie         = this;

   //   //      ev.m_eevent       = ::user::event_tab_key;

   //   //      ev.m_context        = ::source_user;

   //   //      if(!on_control_event(&ev))
   //   //      {

   //   //         __pointer(::user::interaction) pinteraction = Session.get_keyboard_focus();

   //   //         pinteraction =  pinteraction->is_set() ? pinteraction->keyboard_get_next_focusable() : keyboard_get_next_focusable();

   //   //         if(pinteraction != nullptr)
   //   //         {

   //   //            if (!pinteraction->does_consume_key(::user::key_tab))
   //   //            {

   //   //               pinteraction->keyboard_set_focus();

   //   //               pkey->m_bRet = true;

   //   //            }

   //   //         }

   //   //      }

   //   //   }

   //   //}


   //}


   oswindow interaction::get_handle() const
   {

#if defined(_UWP)

      __pointer(::user::interaction) pwnd;

      try
      {

         pwnd = get_wnd();

         if (!pwnd)
         {

            return nullptr;

         }

         if (!pwnd->m_pimpl)
         {

            return nullptr;

         }

         return oswindow_get(pwnd->m_pimpl->m_pinteractionimpl);

      }
      catch (...)
      {

      }

      return nullptr;

#else

      ::user::interaction * pinteraction;

      ::user::interaction_impl * pwnd;

      try
      {

         pinteraction = get_wnd();

         if (pinteraction == nullptr)
            return nullptr;

         if (pinteraction->m_pimpl == nullptr)
            return nullptr;

         pwnd = pinteraction->m_pimpl->get_user_interaction_impl();

         if (pwnd == nullptr)
            return nullptr;

         return pwnd->get_handle();

      }
      catch (...)
      {

      }

      return nullptr;

#endif


   }



   bool interaction::subclass_window(oswindow posdata)
   {

      sync_lock sl(mutex());

      if (is_window())
      {

         DestroyWindow();

      }

      remove_all_routes();

      __pointer(primitive_impl) pimplOld = m_pimpl;

      auto pimplNew = __create < interaction_impl >();

      pimplNew->m_puserinteraction = this;

      if (!pimplNew->subclass_window(posdata))
      {

         pimplNew.release();

      }

      if (pimplNew != nullptr)
      {

         if (pimplOld != nullptr)
         {

            pimplOld->m_puserinteraction = nullptr;

            pimplOld->remove_all_routes();

            auto pwindowOld = pimplOld;

            if (pwindowOld != nullptr)
            {

               pwindowOld->install_message_routing(this);

            }

            pimplOld.release();

         }

         m_pimpl = pimplNew;

         return true;

      }
      else
      {

         return false;

      }

   }

   oswindow interaction::unsubclass_window()
   {

      auto pwindow = m_pimpl;

      if (pwindow != nullptr)
      {

         return pwindow->unsubclass_window();
      }

      return nullptr;

   }


   //bool interaction::create_native_window(::user::native_window_initialize* pinitialize)
   //{

   //   // UWP Removed
   //   throw "trying to remove this create native window, it does anything or do less?";

   //   if (is_window())
   //   {

   //      DestroyWindow();

   //   }

   //   if (m_pdescriptor.is_null())
   //   {

   //      m_pdescriptor.create(this);

   //   }

   //   m_pimpl = __create < interaction_impl >();

   //   m_pimpl->m_puserinteraction = this;

   //   if (!m_pimpl->create_native_window(pinitialize))
   //   {

   //      m_pimpl.release();

   //      return false;

   //   }

   //   return true;

   //}


   bool interaction::create_window(::user::interaction * puiParent, const ::id & id)
   {

      if (m_pdescriptor.is_null())
      {

         m_pdescriptor.create(this);

      }

      if (!create_window(
            nullptr,
            nullptr,
            WS_VISIBLE | WS_CHILD,
            puiParent,
            id))
      {

         TRACE("Failed to create control");

         return false;

      }

      return true;

   }


   bool interaction::create_window(const char * pszClassName, const char * pszWindowName, u32 uStyle, ::user::interaction * puiParent, const ::id & id, ::create * pcreate)
   {

      if (is_window())
      {

         DestroyWindow();

      }

      if (m_pdescriptor.is_null())
      {

         m_pdescriptor.create(this);

      }

      __refer(m_pthreadUserInteraction, ::get_thread());

      if (m_pthreadUserInteraction)
      {

         m_pthreadUserInteraction->uiptra().add(this);

      }

      try
      {

         m_id = id;

         m_bUserPrimitiveOk = true;

         //remove_all_routes();

         __pointer(primitive_impl) pimplNew;

         auto rect(request_state().rect());

         //if (rect.area() <= 0)
         //{

         //   if (puiParent != nullptr && dynamic_cast <::user::place_holder *> (puiParent) != nullptr)
         //   {

         //      puiParent->get_client_rect(rect);

         //   }

         //}

         if (puiParent == nullptr && Session.m_puiHost.is_set() && Session.m_puiHost != this)
         {

            puiParent = Session.m_puiHost;

         }

         if (puiParent == nullptr || puiParent->get_safe_handle() == (oswindow)MESSAGE_WINDOW_PARENT)
         {

            pimplNew = __create < interaction_impl > ();

//#ifdef WINDOWS_DESKTOP
//
//            wstring wstrClassName(pszClassName);
//
//            wstring wstrWindowName(pszWindowName);
//
//            ::user::create_struct createstruct(0, wstrClassName, wstrWindowName, uStyle, rect, pcreate);
//
//#else

            ::user::create_struct createstruct(0, pszClassName, pszWindowName, uStyle, rect, pcreate);

//#endif

            createstruct.hwndParent = ::is_set(puiParent) ? puiParent->get_safe_handle() : nullptr;

            if (!pimplNew->create_window_ex(this, createstruct, puiParent, m_id))
            {

               m_pimpl.release();

               pimplNew.release();

            }

         }
         else
         {

            pimplNew = __create_new < ::user::interaction_child >();

            m_pdescriptor.create(this);

            if (!pimplNew->create_window(this, pszClassName, pszWindowName, uStyle, rect, puiParent, id, pcreate))

            {

               pimplNew.release();

               m_bUserPrimitiveOk = false;

               if (m_pthreadUserInteraction.is_set()
                     && ::is_set(m_pthreadUserInteraction->m_puiptraThread))
               {

                  m_pthreadUserInteraction->m_puiptraThread->remove(this);

               }

               __release(m_pthreadUserInteraction);

               return false;

            }

         }

      }
      catch (...)
      {

         m_bUserPrimitiveOk = false;

         if (m_pthreadUserInteraction.is_set()
               && ::is_set(m_pthreadUserInteraction->m_puiptraThread))
         {

            m_pthreadUserInteraction->m_puiptraThread->remove(this);

         }

         __release(m_pthreadUserInteraction);

         return false;

      }

      return true;

   }


   bool interaction::create_window_ex(::user::create_struct & createstruct, ::user::interaction * puiParent, const ::id & id)
   {

      createstruct.hMenu = nullptr;

      if(puiParent != nullptr)
      {

         createstruct.hwndParent = puiParent->get_safe_handle();

      }

#ifdef WINDOWS_DESKTOP

      createstruct.hInstance = System.m_hinstance;

#endif

      /// moving to implementation
      // (either interaction_child::create_window
      //    or interaction_impl::create_window)
      if (is_window())
      {

         DestroyWindow();

      }

      try
      {

         m_bUserPrimitiveOk = true;

         //remove_all_routes();

         //::thread * pthread = ::get_thread();

         //if(pthread != nullptr)
         //{

         //   m_threadptra.add(pthread);

         //}

         if (puiParent == nullptr && this != Session.m_puiHost && Session.m_puiHost.is_set())
         {

            puiParent = Session.m_puiHost;

         }

         if ((WS_CHILD & createstruct.style) == 0 && (!puiParent || puiParent != Session.m_puiHost))
         {

            m_pimpl = __create < interaction_impl > ();

            //uStyle &= ~WS_CHILD;

            if (m_pdescriptor.is_null())
            {

               m_pdescriptor.create(this);

            }

            if (!m_pimpl->create_window_ex(this, createstruct, puiParent, id))
            {

               m_bUserPrimitiveOk = false;

               m_pimpl.release();

               if (m_pthreadUserInteraction.is_set()
                     && ::is_set(m_pthreadUserInteraction->m_puiptraThread))
               {

                  m_pthreadUserInteraction->m_puiptraThread->remove(this);

               }

               __release(m_pthreadUserInteraction);

               return false;

            }

            return true;

         }
         else
         {

            if (puiParent == nullptr && this != Session.m_puiHost && Session.m_puiHost.is_set())
            {

               puiParent = Session.m_puiHost;

            }

            ::rect rect;

            createstruct.get_rect(rect);

            ::rect rectFrame(0, 0, 0, 0);

            if (IsRectEmpty(&rect))
            {

               if (rectFrame.is_null() && ::is_set(puiParent) && puiParent->is_place_holder())
               {

                  puiParent->get_client_rect(rectFrame);

               }

            }
            else
            {

               rectFrame = rect;

            }

            //sync_lock sl(puiParent == nullptr ? nullptr : puiParent->mutex());

            m_pimpl = __create_new < ::user::interaction_child > ();

            m_pimpl->m_puserinteraction = this;

            m_pdescriptor.create(this);

            if (!m_pimpl->create_window_ex(this, createstruct, puiParent, id))
            {

               m_bUserPrimitiveOk = false;

               m_pimpl.release();

               if (m_pthreadUserInteraction.is_set()
                     && ::is_set(m_pthreadUserInteraction->m_puiptraThread))
               {

                  m_pthreadUserInteraction->m_puiptraThread->remove(this);

               }

               __release(m_pthreadUserInteraction);

               return false;

            }

         }

      }
      catch (...)
      {

         m_bUserPrimitiveOk = false;

         if (m_pthreadUserInteraction.is_set()
               && ::is_set(m_pthreadUserInteraction->m_puiptraThread))
         {

            m_pthreadUserInteraction->m_puiptraThread->remove(this);

         }

         __release(m_pthreadUserInteraction);

         return false;

      }

      return true;

   }


   bool interaction::_is_window() const
   {

      if (is_null(this))
      {

         return false;

      }

      if (m_pimpl.is_null())
      {

         return false;

      }

      if (GetParent() != nullptr)
      {

         if (!GetParent()->is_window())
         {

            return false;

         }

      }

      return is_window();

   }


   LONG interaction::get_window_long(i32 nIndex) const
   {

      if (m_pimpl == nullptr)
      {

         return 0;

      }

      return m_pimpl->get_window_long(nIndex);

   }


   LONG interaction::set_window_long(i32 nIndex, LONG lValue)
   {

      if (m_pimpl == nullptr)
      {

         return 0;

      }

      return m_pimpl->set_window_long(nIndex, lValue);

   }
::object * interaction::parent_property_set_holder() const
{

   ::object * pobject = GetParent();

   if(::is_set(pobject))
   {

      return pobject;

   }

   pobject = GetOwner();

   if(::is_set(pobject))
   {

      return pobject;

   }

   return ::user::primitive::parent_property_set_holder();

}

   LONG_PTR interaction::get_window_long_ptr(i32 nIndex) const
   {

      if (m_pimpl == nullptr)
      {

         return 0;

      }

      return m_pimpl->get_window_long_ptr(nIndex);

   }


   LONG_PTR interaction::set_window_long_ptr(i32 nIndex, LONG_PTR lValue)
   {

      if (m_pimpl == nullptr)
      {

         return 0;

      }

      return m_pimpl->set_window_long_ptr(nIndex, lValue);

   }


   bool interaction::RedrawWindow(const ::rect& rectUpdate, ::draw2d::region* prgnUpdate, UINT flags)
   {

      if (m_pimpl == nullptr)
      {

         return false;

      }

      return m_pimpl->RedrawWindow(rectUpdate, prgnUpdate, flags);

   }


   ::user::interaction * interaction::ChildWindowFromPoint(const ::point & point)
   {

      if (m_pimpl == nullptr)
      {

         return nullptr;

      }

      return m_pimpl->ChildWindowFromPoint(point);

   }


   ::user::interaction * interaction::ChildWindowFromPoint(const ::point & point, UINT nFlags)
   {

      if (m_pimpl == nullptr)
      {

         return nullptr;

      }

      return m_pimpl->ChildWindowFromPoint(point, nFlags);

   }


   ::user::interaction * interaction::get_next_window(UINT nFlag)
   {

      if (m_pimpl == nullptr)
      {

         return nullptr;

      }

      return m_pimpl->get_next_window(nFlag);

   }


   ::user::interaction * interaction::get_next(bool bIgnoreChildren, i32 * piLevel)
   {

      if (!bIgnoreChildren)
      {

         if (m_uiptraChild.has_elements())
         {

            if (piLevel != nullptr)
            {

               (*piLevel)++;

            }

            return m_uiptraChild[0];

         }

      }

      if (GetParent() == nullptr)
      {

         // todo, reached desktop or similar very top system interaction_impl
         return nullptr;

      }

      sync_lock slParent(GetParent()->mutex());

      sync_lock sl(mutex());

      index iFind = GetParent()->m_uiptraChild.find_first(this);

      if (iFind < 0)
      {

         __throw(::exception::exception("not expected situation"));

      }

      if (iFind < GetParent()->m_uiptraChild.get_upper_bound())
      {

         return GetParent()->m_uiptraChild[iFind + 1];

      }

      if (GetParent()->GetParent() == nullptr)
      {

         // todo, reached desktop or similar very top system interaction_impl
         return nullptr;

      }

      if (piLevel != nullptr)
      {

         (*piLevel)--;

      }

      return GetParent()->GetParent()->get_next(true, piLevel);

   }


   bool interaction::is_message_only_window() const
   {

      return m_bMessageWindow;

   }


   ::user::interaction * interaction::GetTopWindow()
   {

      if (m_pimpl == nullptr)
      {

         return nullptr;

      }

      return m_pimpl->GetTopWindow();

   }


   ::user::interaction * interaction::get_wnd(UINT nCmd) const
   {

      if (m_pimpl == nullptr)
      {

         return nullptr;

      }

      return m_pimpl->get_wnd(nCmd);

   }


   ::user::interaction * interaction::GetActiveWindow()
   {

      if (m_pimpl == nullptr)
      {

         return nullptr;

      }

      return m_pimpl->GetActiveWindow();

   }


   bool interaction::SetFocus()
   {

      if (m_pimpl == nullptr)
      {

         return false;

      }

      return m_pimpl->SetFocus();

   }


   ::user::interaction * interaction::GetFocus()
   {

      if (m_pimpl == nullptr)
      {

         return nullptr;

      }

      return m_pimpl->GetFocus();

   }


   ::user::interaction * interaction::SetActiveWindow()
   {

      if (m_pimpl == nullptr)
      {

         return nullptr;

      }

      return m_pimpl->SetActiveWindow();

   }


   bool interaction::SetForegroundWindow()
   {

      if (m_pimpl == nullptr)
      {

         return false;

      }

      return m_pimpl->SetForegroundWindow();

   }


   ::user::interaction * interaction::GetLastActivePopup()
   {

      if (m_pimpl == nullptr)
      {

         return nullptr;

      }

      return m_pimpl->GetLastActivePopup();

   }


   bool interaction::is_text_composition_active()
   {

      auto pimpl = m_pimpl;

      if (::is_null(pimpl))
      {

         return false;

      }

      return pimpl->is_text_composition_active();

   }


   //::form_property_set * interaction::get_form_property_set()
   //{

   //   if (m_pformpropertyset)
   //   {

   //      return m_pformpropertyset;

   //   }

   //   return ::user::primitive::get_form_property_set();

   //}


   int interaction::on_text_composition_message(int iMessage)
   {

      return -1;

   }



   void interaction::insert_text(string str, bool bForceNewStep)
   {

      auto strText = get_window_text();

      strsize iBeg = strText.get_length();

      strsize iEnd = strText.get_length();

      _001GetSel(iBeg, iEnd);

      strText.translate_index(iBeg);

      strText.translate_index(iEnd);

      strText.replace(iBeg, iEnd, strText);

   }


   void interaction::set_window_text(const char * pszString)
   {

      m_strWindowText = pszString;

      if (m_pimpl != nullptr)
      {

         m_pimpl->set_window_text(pszString);

      }

   }


   strsize interaction::get_window_text(char * pszStringBuf, strsize nMaxCount)
   {

      strsize n = MIN(nMaxCount, m_strWindowText.get_length());

      ansi_count_copy(pszStringBuf, m_strWindowText, n);

      return n;

   }


   string interaction::get_window_text()
   {

      string str;

      get_window_text(str);

      return str;

   }


   void interaction::get_window_text(string & rectString)
   {

      sync_lock sl(mutex());

      rectString = m_strWindowText;

   }


   strsize interaction::get_window_text_length()
   {

      sync_lock sl(mutex());

      if (m_pimpl == nullptr)
      {

         return 0;

      }

      return m_pimpl->get_window_text_length();

   }


   ::user::interaction * interaction::GetParentTopLevel() const
   {

      __pointer(::user::interaction) puiParent = GetParent();

      __pointer(::user::interaction) puiParentTopLevel;

      if (puiParent.is_null())
      {

         return nullptr;

      }

      do
      {

         puiParentTopLevel = puiParent;

         puiParent = puiParent->GetParent();

      }
      while (puiParent.is_set());

      return puiParentTopLevel;

   }


   ::user::interaction * interaction::EnsureParentTopLevel()
   {

      __pointer(interaction) pwindow = GetParentTopLevel();

      ENSURE_VALID(pwindow);

      return pwindow;

   }


   ::user::interaction * interaction::GetTopLevel() const
   {

      ::user::interaction * puiParent = (::user::interaction *) this;

      ::user::interaction * puiTopLevelParent;

      if (puiParent == nullptr)
      {

         return nullptr;

      }

      do
      {

         puiTopLevelParent = puiParent;

         puiParent = puiParent->GetParent();

      }
      while (puiParent != nullptr);

      return puiTopLevelParent;

   }


   ::user::interaction * interaction::EnsureTopLevel()
   {

      __pointer(interaction) pwindow = GetTopLevel();

      ENSURE_VALID(pwindow);

      return pwindow;

   }


   ::user::frame * interaction::GetFrame() const
   {

      ::user::interaction * pinteraction = (::user::interaction *) this;

      if (pinteraction == nullptr)
      {

         return nullptr;

      }

      ::user::frame * pframeParent;

      do
      {

         pframeParent = pinteraction->m_pframe;

         if (pframeParent != nullptr)
         {

            return pframeParent;

         }

         pinteraction = pinteraction->get_parent();

      }
      while (pinteraction != nullptr);

      return nullptr;

   }


   ::user::frame * interaction::GetParentFrame() const
   {

      ::user::interaction * pinteraction = get_parent();

      if (pinteraction == nullptr)
      {

         return nullptr;

      }

      return pinteraction->GetFrame();

   }


   ::user::frame * interaction::GetTopLevelFrame() const
   {

      __pointer(::user::frame) pframe = GetFrame();

      if (pframe.is_null())
      {

         return nullptr;

      }

      __pointer(::user::frame) pframeTopLevel;

      do
      {

         pframeTopLevel = pframe;

         pframe = pframe->GetParentFrame();

      }
      while (pframe.is_set());

      return pframeTopLevel;

   }


   ::user::frame * interaction::GetParentTopLevelFrame() const
   {

      __pointer(::user::frame) pframe = GetParentFrame();

      if (pframe.is_null())
      {

         return nullptr;

      }

      return pframe->GetTopLevelFrame();

   }


   ::user::frame * interaction::EnsureParentFrame()
   {

      ::user::frame * pFrameWnd = GetParentFrame();

      ENSURE_VALID(pFrameWnd);

      return pFrameWnd;

   }


   //LRESULT interaction::default_window_procedure()
   //{

   //   if (m_pimpl == nullptr)
   //   {

   //      return 0;

   //   }

   //   return m_pimpl->default_window_procedure();

   //}


   u32 interaction::GetStyle() const
   {

      if (m_pimpl == nullptr)
      {

         return 0;

      }

      return m_pimpl->GetStyle();

   }


   u32 interaction::GetExStyle() const
   {

      if (m_pimpl == nullptr)
      {

         return 0;

      }

      return m_pimpl->GetExStyle();

   }


   bool interaction::ModifyStyle(u32 dwRemove, u32 dwAdd, UINT nFlags)
   {

      if (m_pimpl == nullptr)
      {

         return false;

      }

      return m_pimpl->ModifyStyle(dwRemove, dwAdd, nFlags);

   }


   bool interaction::ModifyStyleEx(u32 dwRemove, u32 dwAdd, UINT nFlags)
   {

      if (m_pimpl == nullptr)
      {

         return false;

      }


      return m_pimpl->ModifyStyleEx(dwRemove, dwAdd, nFlags);

   }


   bool interaction::DestroyWindow()
   {

      string strType;

      strType = type_name();

      if (strType.contains("main_frame"))
      {

         output_debug_string("main_frame DestroyWindow\n");

      }

      if (!m_bUserPrimitiveOk && !(m_ewindowflag & window_flag_is_window))
      {

         return true;

      }

      m_bUserPrimitiveOk = false;

      m_ewindowflag -= window_flag_is_window;

      if (m_pimpl == nullptr)
      {

         return false;

      }

      return m_pimpl->DestroyWindow();

   }


   void interaction::destroy_window()
   {

      if (m_pimpl.is_set())
      {

         m_pimpl->destroy_window();

      }

   }


   void interaction::finalize()
   {

      ::user::primitive::finalize();

      if (m_pimpl.is_set())
      {

         m_pimpl->finalize();

      }

   }


   void interaction::PostNcDestroy()
   {

      {

         sync_lock sl(mutex());

         try
         {

            remove_all_routes();

         }
         catch (...)
         {

         }

      }

      string strType;

      strType = type_name();

      if (strType.contains("main_frame"))
      {

         output_debug_string("main_frame PostNcDestroy");

      }

      ::user::primitive::PostNcDestroy();

      m_pimpl.release();

      m_pimpl2.release();

   }


   void interaction::CalcWindowRect(RECT * prect, UINT nAdjustType)
   {

      if (m_pimpl == nullptr)
      {

         return;

      }

      return m_pimpl->CalcWindowRect(prect, nAdjustType);

   }


   void interaction::RepositionBars(UINT nIDFirst, UINT nIDLast, ::id idLeftOver, UINT nFlag, RECT * prectParam, const ::rect & rectClient, bool bStretch)
   {

      if (m_pimpl == nullptr)
      {

         return;

      }

      return m_pimpl->RepositionBars(nIDFirst, nIDLast, idLeftOver, nFlag, prectParam, rectClient, bStretch);

   }


   ::user::interaction * interaction::SetOwner(::user::interaction * pinteraction)
   {

      if (m_pimpl == nullptr)
      {

         return nullptr;

      }

      if (m_puiOwner != nullptr)
      {

         try
         {

            m_puiOwner->m_uiptraOwned.remove(this);

         }
         catch (...)
         {

         }

      }

      m_puiOwner = pinteraction;

      pinteraction->m_uiptraOwned.add(this);

      ::user::interaction * puiRet = m_pimpl->SetOwner(pinteraction);

      return puiRet;

   }


   ::user::interaction * interaction::GetOwner() const
   {

      if (m_puiOwner != nullptr)
      {

         return m_puiOwner;

      }

      if (m_pimpl == nullptr)
      {

         return nullptr;

      }

      return m_pimpl->GetOwner();

   }


   ::user::frame * interaction::GetOwnerFrame() const
   {

      ::user::interaction * pinteraction = GetOwner();

      if (pinteraction == nullptr)
      {

         return nullptr;

      }

      ::user::frame * pframe = dynamic_cast < ::user::frame * > (pinteraction);

      while (pinteraction != nullptr)
      {

         if (pframe != nullptr)
         {

            return pframe;

         }

         pframe = pinteraction->GetParentFrame();

         if (pframe != nullptr)
         {

            return pframe;

         }

         pinteraction = pinteraction->GetOwner();

         if (pinteraction == nullptr)
         {

            break;

         }

         pframe = dynamic_cast < ::user::frame * > (pinteraction);

      }

      return nullptr;

   }


   ::user::interaction * interaction::GetParentOwner() const
   {

      __pointer(::user::interaction) puiParent = GetParent();

      if (puiParent.is_null())
      {

         return nullptr;

      }

      return puiParent->GetOwner();

   }


   ::user::interaction * interaction::GetParentOrOwner() const
   {

      __pointer(::user::interaction) puiParent = GetParent();

      if (puiParent.is_set())
      {

         return puiParent;

      }

      return GetOwner();

   }


   ::user::interaction * interaction::GetTopLevelOwner() const
   {

      __pointer(::user::interaction) puiOwner = GetOwner();

      __pointer(::user::interaction) puiTopLevelOwner;

      if (puiOwner.is_null())
      {

         return nullptr;

      }

      do
      {

         puiTopLevelOwner = puiOwner;

         puiOwner = puiOwner->GetParent();

      }
      while (puiOwner.is_set());

      return puiTopLevelOwner;

   }


   void interaction::viewport_client_to_screen(POINT * ppt)
   {

      m_pimpl->viewport_client_to_screen(ppt);

   }


   bool interaction::window_is_notify_icon_enabled()
   {

      return false;

   }


   void interaction::viewport_screen_to_client(POINT * ppt)
   {

      if (m_pimpl.is_null())
      {

         return;

      }

      m_pimpl->viewport_screen_to_client(ppt);

   }


   void interaction::viewport_client_to_screen(RECT * prect)
   {

      viewport_client_to_screen((POINT *)&prect->left);

      viewport_client_to_screen((POINT *)&prect->right);

   }


   void interaction::viewport_screen_to_client(RECT * prect)
   {

      viewport_screen_to_client((POINT *)&prect->left);

      viewport_screen_to_client((POINT *)&prect->right);

   }


   //bool interaction::window_is_zoomed()
   //{

   //   if (m_pimpl == nullptr)
   //   {

   //      return false;

   //   }

   //   return m_pimpl->window_is_zoomed();

   //}


   //bool interaction::window_is_full_screen()
   //{

   //   if (m_pimpl.is_null())
   //   {

   //      return false;

   //   }

   //   return m_pimpl->window_is_full_screen();

   //}


   //bool interaction::window_is_iconic()
   //{

   //   if (m_pimpl == nullptr)
   //   {

   //      return false;

   //   }

   //   return m_pimpl->window_is_iconic();

   //}


   void interaction::_001OnAfterAppearance()
   {


   }

   bool interaction::should_save_window_rect()
   {

      return false;

   }


   bool interaction::WindowDataSaveWindowRect()
   {

      return false;

   }


   bool interaction::WindowDataLoadWindowRect(bool bForceRestore, bool bInitialFramePosition)
   {

      return false;

   }


   void interaction::on_defer_display()
   {

   }


   bool interaction::defer_display()
   {

      if (string(type_name()).contains_ci("page_home"))
      {

         INFO("page_home");

      }

      auto edisplayState = ui_state().m_edisplay3;

      auto edisplay = display_request();

      auto eactivation = request_state().m_eactivation;

      bool bDisplay = edisplayState != display_request()
         || eactivation & activation_under_mouse_cursor
         || eactivation & activation_display_change;

      if (bDisplay)
      {

         prodevian_display();

      }

      return bDisplay;

   }


   bool interaction::prodevian_display()
   {
      
      string strType = type_name();

      if (strType.contains_ci("page_home"))
      {

         INFO("page_home");

      }

      auto edisplay = display_request();

      if (edisplay == ::display_full_screen)
      {

         if (GetParent() != nullptr)
         {

            WARN("full screen child window?");

            set_display_request(display_normal);

         }
         else
         {

            prodevian_prepare_window_full_screen(window_request_rect());

         }

      }
      else if (edisplay == ::display_iconic)
      {

         if (GetParent() != nullptr)
         {

            WARN("iconify child window?");

            set_display_request(display_normal);

         }
         else
         {

            prodevian_prepare_window_minimize(request_state().m_eactivation);

         }

      }
      else if (edisplay == ::display_zoomed)
      {

         if (GetParent() != nullptr)
         {

            WARN("zooming child window?");

            set_display_request(display_normal);

         }
         else
         {

            prodevian_prepare_window_maximize();

         }

      }
      else if (edisplay == ::display_restore
         || edisplay == ::display_compact
         || edisplay == ::display_broad)
      {

         if (GetParent() != nullptr)
         {

            WARN("restoring child window?");

            set_display_request(display_normal);

         }
         else
         {

            prodevian_prepare_window_restore(edisplay);

         }

      }
      else if (edisplay == ::display_up)
      {

         prodevian_prepare_up();

      }
      else if (edisplay == ::display_down)
      {

         prodevian_prepare_down();

      }
      else if (::is_docking_appearance(edisplay))
      {

         if (GetParent() != nullptr)
         {

            WARN("snapping child window?");

            set_display_request(display_normal);

         }
         else
         {

            prodevian_prepare_window_dock(edisplay);

         }

      }
      else if (is_screen_visible(edisplay))
      {

         if (GetParent() != nullptr)
         {

            INFO("showing child window");

         }
         else
         {

            INFO("simply showing top level window");

         }

         //display();

      }
      else
      {

         if (string(type_name()).contains_ci("page_home"))
         {

            INFO("page_home");

         }

         if (GetParent() != nullptr)
         {

            INFO("hiding child window");

            ui_state().m_edisplay3 = display_none;

         }
         else
         {

            INFO("hiding top level window");

         }



         //hide();

      }

      return true;

   }


   bool interaction::prodevian_appearance()
   {

      ui_state().m_eappearance = process_state().m_eappearance;

      return true;

   }


   CLASS_DECL_AURA bool zorder_sync_request(::user::interaction_pointer_array & uiptra)
   {

      int iZOrder = 0;

      bool bSetRequest = false;

      for (auto & pinteraction : uiptra.ptra())
      {

         pinteraction->request_state().m_zorder.m_iZOrder = iZOrder;
         pinteraction->process_state().m_zorder.m_iZOrder = iZOrder;
         pinteraction->ui_state().m_zorder.m_iZOrder = iZOrder;
         pinteraction->window_state3().m_zorder.m_iZOrder = iZOrder;

         pinteraction->ui_state().m_zorder.clear_request();

         auto ezorder = pinteraction->ui_state().m_zorder.m_ezorder;

         pinteraction->request_state().m_zorder.m_ezorder = ezorder;
         pinteraction->process_state().m_zorder.m_ezorder = ezorder;
         pinteraction->ui_state().m_zorder.m_ezorder = ezorder;
         pinteraction->window_state3().m_zorder.m_ezorder = ezorder;

         iZOrder += 10;

      }

      return bSetRequest;

   }


   CLASS_DECL_AURA void zorder_sort(::user::interaction_pointer_array & uiptra)
   {

      auto predZ = [](auto & pui1, auto & pui2)
      {

         return pui1->ui_state().m_zorder < pui2->ui_state().m_zorder;

      };

      uiptra.pred_sort(predZ);

   }


   bool interaction::prodevian_zorder()
   {

      ui_state().m_zorder = process_state().m_zorder;

      if (GetParent() != NULL)
      {

         string strType = type_name();

         auto & uiptra = GetParent()->m_uiptraChild;

         //zorder_pre_order(uiptra);

         zorder_sort(uiptra);

         zorder_sync_request(uiptra);

      }

      return true;

   }

#undef EXTRA_PRODEVIAN_REPOSITION_LOG

   bool interaction::prodevian_reposition()
   {

      if (!m_bUserPrimitiveOk)
      {

         return false;

      }

      #ifdef EXTRA_PRODEVIAN_REPOSITION_LOG

      if(type_name().contains_ci("control_box"))
      {

         output_debug_string("control_box prodevian_reposition");

      }

      #endif
      
      ::point point = process_state().m_point;

      ui_state().m_point = point;

      ui_state().m_pointScreen = ui_state().m_point;

      if (GetParent() != NULL)
      {

         GetParent()->_001ClientToScreen(ui_state().m_pointScreen);

         process_state().m_pointScreen = ui_state().m_pointScreen;

         request_state().m_pointScreen = ui_state().m_pointScreen;

         window_state3().m_pointScreen = ui_state().m_pointScreen;

      }

      if(string(type_name()).contains_ci("tap"))
      {

         INFO("tap prodevian_reposition (%d, %d)", ui_state().m_pointScreen.x, ui_state().m_pointScreen.y);

      }

      on_reposition();

      set_reposition(false);

      return true;

   }


   bool interaction::prodevian_layout()
   {

      sync_lock sl(mutex());

      if (m_pimpl->m_puserinteraction == nullptr)
      {

         return false;

      }

      ui_state().m_size = process_state().m_size;

      auto pgraphics = ::draw2d::create_memory_graphics();

      m_pimpl->on_layout(pgraphics);

      on_layout(pgraphics);

      if (::is_set(m_playout))
      {

         if (m_playout->m_bFillParent)
         {

            ::rect rectClient;

            get_client_rect(rectClient);

            m_playout->place(rectClient);

         }

         m_playout->on_layout(pgraphics);

      }

      m_bNeedLayout = false;

      return true;

   }


   bool interaction::CheckAutoCenter()
   {

      if (m_pimpl == nullptr)
      {

         return true;

      }

      return m_pimpl->CheckAutoCenter();

   }


   void interaction::CenterWindow(::user::interaction * pAlternateOwner)
   {

      if (m_pimpl == nullptr)
      {

         return;

      }

      m_pimpl->CenterWindow(pAlternateOwner);

   }


   //void interaction::default_window_procedure(::message::message * pmessage)
   //{

   //   if (m_pimpl == nullptr)
   //   {

   //      return;

   //   }

   //   return m_pimpl->default_window_procedure(pmessage);

   //}


   void interaction::pre_translate_message(::message::message * pmessage)
   {

      if (pmessage->m_uiMessageFlags & 1)
      {

         // message already pre translated
         return;

      }

      if (::is_set(get_context_session()))
      {

         auto puiSession = Session.get_session_window();

         if (puiSession == nullptr || puiSession != this)
         {

            if (!(pmessage->m_uiMessageFlags & 2)) // message already pre translated
            {

               Session.pre_translate_message(pmessage);

               if (pmessage->m_bRet)
               {

                  return;

               }

            }

         }

      }

      pmessage->m_uiMessageFlags |= 1;

   }


   void interaction::message_handler(::message::base * pbase)
   {

      string strType;

      strType = type_name();

      if (strType.contains_ci("combo_list"))
      {

         ::output_debug_string("combo_list");

      }

//      pre_translate_message(pbase);

//      if (pbase->m_bRet)
//      {

//         return;

//      }

      if (m_pimpl == nullptr)
      {

         return;

      }

      primitive_impl * pimpl = m_pimpl;

      bool bDestroying = pimpl->m_bDestroying;

      pimpl->message_handler(pbase);

      if (!bDestroying && m_ewindowflag & window_flag_window_created)
      {

         if (m_bRedraw || m_bReposition)
         {

            bool bUpdateBuffer = m_bRedraw;

            m_bRedraw = false;

            prodevian_redraw(bUpdateBuffer);

         }

      }

   }


   LRESULT interaction::message_handler(LPMESSAGE pmessage)
   {

      return send_message(pmessage->message, pmessage->wParam, pmessage->lParam);

   }


#ifdef WINDOWS_DESKTOP

   bool interaction::GetWindowPlacement(WINDOWPLACEMENT* pwndpl)
   {

      if (m_pimpl == nullptr)
      {

         return false;

      }

      return m_pimpl->GetWindowPlacement(pwndpl);

   }


   bool interaction::SetWindowPlacement(const WINDOWPLACEMENT* pwndpl)
   {

      if (m_pimpl == nullptr)
      {

         return false;

      }

      return m_pimpl->SetWindowPlacement(pwndpl);

   }


#endif


   bool interaction::pre_create_window(::user::create_struct& createstruct)
   {

      return true;

   }


   bool interaction::IsTopParentActive()
   {

      if (m_pimpl == nullptr)
      {

         return false;

      }

      return m_pimpl->IsTopParentActive();

   }


   void interaction::ActivateTopParent()
   {

      if (m_pimpl == nullptr)
      {

         return;

      }

      m_pimpl->ActivateTopParent();

   }


   void interaction::update_dialog_controls(channel * pTarget)
   {

      if (m_pimpl.is_null())
      {

         return;

      }

      m_pimpl->update_dialog_controls(pTarget);

   }


   void interaction::UpdateWindow()
   {

      if (m_pimpl == nullptr)
      {

         return;

      }

      m_pimpl->UpdateWindow();

   }


   void interaction::register_drop_target()
   {

      if (m_pimpl == nullptr)
      {

         return;

      }

      m_pimpl->register_drop_target();

   }


   void interaction::SetRedraw(bool bRedraw)
   {

      if (m_pimpl == nullptr)
      {

         return;

      }

      m_pimpl->SetRedraw(bRedraw);

   }


   bool interaction::GetUpdateRect(RECT * prect, bool bErase)
   {

      if (m_pimpl == nullptr)
      {

         return false;

      }

      return m_pimpl->GetUpdateRect(prect, bErase);

   }


   i32 interaction::GetUpdateRgn(::draw2d::region* pRgn, bool bErase)
   {

      if (m_pimpl == nullptr)
      {

         return 0;

      }

      return m_pimpl->GetUpdateRgn(pRgn, bErase);

   }


   void interaction::Invalidate(bool bErase)
   {

      if (m_pimpl == nullptr)
      {

         return;

      }

      m_pimpl->Invalidate(bErase);

   }


   void interaction::InvalidateRect(const ::rect & rect, bool bErase)
   {

      if (m_pimpl == nullptr)
      {

         return;

      }

      m_pimpl->InvalidateRect(rect, bErase);

   }


   void interaction::InvalidateRgn(::draw2d::region* pRgn, bool bErase)
   {

      if (m_pimpl == nullptr)
      {

         return;

      }

      m_pimpl->InvalidateRgn(pRgn, bErase);

   }


   void interaction::ValidateRect(const ::rect & rect)
   {

      if (m_pimpl == nullptr)
      {

         return;

      }

      m_pimpl->ValidateRect(rect);

   }


   void interaction::ValidateRgn(::draw2d::region* pRgn)
   {

      if (m_pimpl == nullptr)
      {

         return;

      }

      m_pimpl->ValidateRgn(pRgn);

   }


   void interaction::on_start_layout_experience(e_layout_experience elayoutexperience)
   {

      m_elayoutexperience = elayoutexperience;

      if(m_pimpl.is_null())
      {

         return;

      }

      m_pimpl->on_start_layout_experience(elayoutexperience);

   }


   void interaction::on_end_layout_experience(e_layout_experience elayoutexperience)
   {

      ASSERT(m_elayoutexperience == elayoutexperience);

      m_elayoutexperience = layout_experience_none;

      if(m_pimpl.is_null())
      {

         return;

      }

      m_pimpl->on_end_layout_experience(elayoutexperience);

   }


   void interaction::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

      layout_tooltip();

      on_change_view_size();

      m_pathFocusRect1.release();
      m_pathFocusRect2.release();
      m_pathFocusRect3.release();
      m_pathFocusRect4.release();

      {

         auto pitem = get_user_item(::user::element_close_button);

         if (pitem)
         {

            if (pitem->m_rect.is_null())
            {

               get_client_rect(pitem->m_rect);

               pitem->m_rect.left = pitem->m_rect.right - 32;

               pitem->m_rect.bottom = pitem->m_rect.top + 32;

            }

         }

      }

      {

         auto pitem = get_user_item(::user::element_close_icon);

         if (pitem)
         {

            if (pitem->m_rect.is_null())
            {

               get_client_rect(pitem->m_rect);

               pitem->m_rect.left = pitem->m_rect.right - 48;

               pitem->m_rect.bottom = pitem->m_rect.top + 48;

            }

         }

      }

   }


   void interaction::on_visual_applied()
   {

      clear_visual_changed();

      if (!m_pimpl2)
      {

         return;

      }

      m_pimpl2->on_visual_applied();

      auto edisplay = display_state();

      get_window_rect(m_windowrect.m_rectWindow);

      if (is_docking_appearance(edisplay))
      {

         m_windowrect.m_rectSnapped = m_windowrect.m_rectWindow;

      }
      else if (is_equivalent(edisplay, display_normal))
      {

         calculate_broad_and_compact_restore();

         if (m_windowrect.m_rectWindow.size() != m_sizeRestoreBroad
            && m_windowrect.m_rectWindow.size() != m_sizeRestoreCompact)
         {

            if (m_windowrect.m_rectWindow.size() != m_windowrect.m_rectRestored.size())
            {

               m_windowrect.m_rectRestored = m_windowrect.m_rectWindow;

            }
            else if (m_windowrect.m_rectWindow != m_windowrect.m_rectRestored)
            {

               m_windowrect.m_rectRestored = m_windowrect.m_rectWindow;

            }

         }
         else
         {

            if (m_windowrect.m_rectRestored.is_empty()
               || m_windowrect.m_rectRestored.size() == m_sizeRestoreCompact
               || m_windowrect.m_rectRestored.size() == m_sizeRestoreBroad)
            {

               m_windowrect.m_rectRestored = m_windowrect.m_rectWindow;

            }

         }

      }

   }


   void interaction::on_reposition()
   {

      layout_tooltip();

   }


   void interaction::on_show_window()
   {

      layout_tooltip();

//      user_interaction_update_visibility_cache(_is_window_visible());

   }


   bool interaction::is_this_visible()
   {

      if (!m_pimpl)
      {

         return false;

      }

      return m_pimpl->is_this_visible();

   }


   void interaction::_on_show_window()
   {

      if (is_auto_prodevian_on_show())
      {

         if (is_this_visible())
         {

            set_prodevian();

         }
         else
         {

            clear_prodevian();

         }

      }

      if (is_window_screen_visible())
      {

         if (GetParent() == nullptr)
         {

            check_transparent_mouse_events();

         }

      }
      else
      {

         user_interaction_on_hide();

      }

      if (GetParent() != nullptr || is_host_top_level())
      {

         _do_show_window();

      }

   }


   void interaction::_do_show_window()
   {

      ::e_display edisplayProcess = m_stateProcess2.m_edisplay3;

      ::e_display edisplayWindow = m_stateWindow3.m_edisplay3;

      if(is_equivalent(edisplayProcess, display_normal))
      {

         edisplayProcess = display_normal;

      }

      if(is_equivalent(edisplayWindow, display_normal))
      {

         edisplayWindow = display_normal;

      }

      ::e_display edisplayProcessForOsShowWindow = edisplayProcess;

      ::e_display edisplayWindowForOsShowWindow = edisplayWindow;

      if(::is_docking_appearance(edisplayProcessForOsShowWindow))
      {

         edisplayProcessForOsShowWindow = display_normal;

      }

      if(::is_docking_appearance(edisplayWindowForOsShowWindow))
      {

         edisplayWindowForOsShowWindow = display_normal;

      }

#ifdef WINDOWS_DESKTOP
      if (((GetExStyle() & WS_EX_LAYERED) &&
         (::is_different(::is_screen_visible(edisplayProcessForOsShowWindow),
            ::is_screen_visible(edisplayWindowForOsShowWindow))))
         || (!(GetExStyle() & WS_EX_LAYERED) &&
         (edisplayProcessForOsShowWindow != edisplayWindowForOsShowWindow)))
#else
      if(edisplayProcessForOsShowWindow != edisplayWindowForOsShowWindow)
#endif
      {

         if (m_pimpl.is_set())
         {

            m_pimpl->_do_show_window();

         }

      }

      if(edisplayProcess == display_iconic)
      {

#ifdef WINDOWS_DESKTOP

         if (GetExStyle() & WS_EX_LAYERED)
         {

            window_state3().m_edisplay3 = edisplayProcess;

         }

#endif

         output_debug_string("blocking setting window state to iconic (1)");

      }
      else
      {

         window_state3().m_edisplay3 = edisplayProcess;

      }

      m_windowrect.m_edisplay = edisplayProcess;

   }


   void interaction::defer_save_window_placement()
   {


   }


   void interaction::ShowOwnedPopups(bool bShow)
   {
      if (m_pimpl == nullptr)
         return;
      else
         m_pimpl->ShowOwnedPopups(bShow);
   }

   void * interaction::get_os_data() const
   {

      return get_handle();

   }

   bool interaction::attach(oswindow oswindow_New)
   {
      if (m_pimpl == nullptr)
         return FALSE;
      else
         return m_pimpl->attach(oswindow_New);
   }

   oswindow interaction::detach()
   {
      if (m_pimpl == nullptr)
         return nullptr;
      else
         return m_pimpl->detach();
   }

   void interaction::pre_subclass_window()
   {
      if (m_pimpl == nullptr)
         return;
      else
         m_pimpl->pre_subclass_window();
   }


   void interaction::_001Emphasize(int cx, int cy)
   {

      ::rect rectMainMonitor;

      System.get_main_monitor(rectMainMonitor);

      int x = (rectMainMonitor.width() - cx) / 2;

      int y = (rectMainMonitor.height() - cy) / 3;

      order(zorder_top);

      set_dim(x, y, cx, cy);

      display(display_normal);

   }


   id interaction::run_modal_loop(::user::interaction * pinteraction, u32 dwFlags)
   {

      return pinteraction->_001RunModalLoop(dwFlags);

   }


   id interaction::RunModalLoop(u32 dwFlags)
   {

      set_need_redraw();

      post_redraw();

      return _001RunModalLoop(dwFlags);

   }


   id interaction::_001RunModalLoop(u32 dwFlags)
   {

      ASSERT(!m_bModal);

      if(m_bModal)
      {

         return ::id();

      }

      __keep(m_bModal);

      __keep_current_thread(m_pthreadModal);

      while(true)
      {

         if (!ContinueModal())
         {

            break;

         }


         if(::is_null(get_thread()))
         {

            break;

         }

         if(!::get_thread()->pump_message())
         {

            break;

         }

      }

      //System.post_to_all_threads(WM_KICKIDLE, 0, 0);

      return m_idModalResult;

   }


   bool interaction::ContinueModal()
   {

      bool bRun = ::thread_get_run();

      return m_bModal && bRun;

   }


   void interaction::EndModalLoop(id idResult)
   {

      TRACE("EndModalLoop");

      ASSERT(is_window());

      // this result will be returned from interaction_impl::RunModalLoop
      m_idModalResult = idResult;

      // make sure a message goes through to exit the modal loop
      m_bModal = false;

      receive(DIALOG_RESULT_CALLBACK, idResult);

      post_message(WM_CLOSE);

      if(::is_set(m_pthreadModal))
      {

         m_pthreadModal->kick_thread();

      }

      if(get_wnd() != nullptr && get_wnd()->m_pthreadUserInteraction.is_set())
      {

         get_wnd()->m_pthreadUserInteraction->kick_thread();

      }

   }


   void interaction::route_control_event(control_event * pevent)
   {

      on_control_event(pevent);

      if (pevent->m_bRet)
      {

         return;

      }

      on_notify_control_event(pevent);

      if (pevent->m_bRet)
      {

         return;

      }

   }


   void interaction::on_notify_control_event(control_event* pevent)
   {

      auto pusercallback = get_user_callback();

      if (pusercallback)
      {

         pusercallback->on_control_event(pevent);

         if (pevent->m_bRet)
         {

            return;

         }

      }

      auto pinteractionBind = get_bind_ui();

      if (pinteractionBind && pinteractionBind != pusercallback)
      {

         pinteractionBind->on_control_event(pevent);

         if (pevent->m_bRet)
         {

            return;

         }

      }

      auto puiParent = GetParent();

      if (puiParent && puiParent != pinteractionBind && puiParent != pusercallback)
      {

         puiParent->route_control_event(pevent);

         return;

      }

      auto puiOwner = GetOwner();

      if (puiOwner && puiOwner !=puiParent && puiOwner != pinteractionBind && puiOwner != pusercallback)
      {

         puiOwner->route_control_event(pevent);

         return;

      }

      auto papp = get_context_application();

      if (papp && papp != pusercallback)
      {

         papp->route_control_event(pevent);

         return;

      }


   }


   void interaction::on_control_event(control_event* pevent)
   {

   }



   bool interaction::post_message(UINT uiMessage, WPARAM wparam, lparam lparam)

   {

      if (m_pimpl.is_null())
      {

         return false;

      }

      if(uiMessage == WM_KEYDOWN)
      {

         output_debug_string("::user::interaction::post_message WM_KEYDOWN");

      }

      if(uiMessage == message_redraw)
      {

         //output_debug_string("message_redraw\n");

      }

      return m_pimpl->post_message(uiMessage, wparam, lparam);


   }


   bool interaction::post_object(UINT uiMessage, WPARAM wparam, lparam lparam)
   {

      bool bIsWindow = m_pimpl.is_set() && is_window();

      if (uiMessage == WM_QUIT || !bIsWindow)
      {

         {

            // discards object
            __pointer(::object) spo(lparam);


         }

         if (!bIsWindow)
         {

            return false;

         }

         return m_pimpl->post_message(uiMessage);

      }

      return m_pimpl->post_message(uiMessage, wparam, lparam);


   }


   bool interaction::call_and_set_timer(uptr nIDEvent, ::duration durationElapse, PFN_TIMER pfnTimer)
   {

      ::timer timer(nullptr, nIDEvent);

      _001OnTimer(&timer);

      return SetTimer(nIDEvent, (UINT) durationElapse.get_total_milliseconds(), pfnTimer);

   }


   bool interaction::set_timer(uptr nIDEvent, ::duration durationElapse, PFN_TIMER pfnTimer)
   {

      return SetTimer(nIDEvent, (UINT) durationElapse.get_total_milliseconds(), pfnTimer);

   }


// timer Functions
   bool interaction::SetTimer(uptr nIDEvent, UINT nElapse, PFN_TIMER pfnTimer)
   {

      if (m_pimpl == nullptr)
         return false;

      return m_pimpl->SetTimer(nIDEvent, nElapse, pfnTimer);

   }


   bool interaction::KillTimer(uptr nIDEvent)
   {

      if (m_pimpl == nullptr)
         return false;

      return m_pimpl->KillTimer(nIDEvent);

   }


   bool interaction::has_focus()
   {

      if(m_pimpl.is_null())
      {

         return false;

      }

      return m_pimpl->has_focus();

   }


   bool interaction::is_active()
   {

      if(m_pimpl.is_null())
      {

         return false;

      }

      return m_pimpl->is_active();

   }


   bool interaction::SetCapture(::user::interaction * pinteraction)
   {

      if (m_pimpl == nullptr)
      {

         return false;

      }

      if (pinteraction == nullptr)
      {

         pinteraction = this;

      }

      return m_pimpl->SetCapture(pinteraction);

   }


   ::user::interaction * interaction::GetCapture()
   {

      if (m_pimpl != nullptr)
      {

         return m_pimpl->GetCapture();

      }

      ::user::interaction * pwnd = get_wnd();

      if (pwnd != nullptr)
      {

         return pwnd->GetCapture();

      }

      return nullptr;

   }


   bool interaction::ReleaseCapture()
   {

      if (m_pimpl == nullptr)
      {

         return false;

      }

      return m_pimpl->ReleaseCapture();

   }


   void interaction::track_mouse_leave()
   {

      track_mouse_hover();

   }


   void interaction::track_mouse_hover()
   {

      if (m_bTrackMouseLeave)
      {

         return;

      }

      ::user::interaction * pinteraction = GetTopLevel();

      if (pinteraction == nullptr)
      {

         return;

      }

      if (pinteraction->get_wnd() == nullptr)
      {

         return;

      }

      pinteraction->get_wnd()->mouse_hover_add(this);

      m_bTrackMouseLeave = true;

   }


   void interaction::defer_restore(const ::rect & rectRequest)
   {

      ::rect rectWkspace;

      index iBestWkspace = Session.get_best_monitor(rectWkspace, rectRequest);

      bool bWindowCrossesWkspaceBoundaries = !rectWkspace.contains(rectRequest);

      bool bWindowLargerThanBroadRestore = rectRequest.width() > m_sizeRestoreBroad.cx
      || rectRequest.height() > m_sizeRestoreBroad.cy;

      if (bWindowCrossesWkspaceBoundaries || bWindowLargerThanBroadRestore)
      {

         prodevian_prepare_window_restore(display_restore);

      }
      else
      {

         //place(rect_dim(10, 10, 800, 300));

         ::rect rectPlace(rectRequest);

         if (rectPlace.size().any_lt(get_window_minimum_size()))
         {

            rectPlace = get_window_minimum_size();

         }

         place(rectPlace);

         display(display_normal);

      }

   }


   static i64 g_i_prodevian_update_visual = 0;


   void interaction::prodevian_update_visual(bool & bUpdateBuffer, bool & bUpdateWindow)
   {

      bUpdateBuffer = false;

      bUpdateWindow = false;

      if (!m_bRequestReady && !m_bReposition && !m_bNeedLayout)
      {

         return;

      }
      
      string strType = type_name();

      if (strType.contains("albertopibiri_keyboard") && strType.contains("main_frame"))
      {

         output_debug_string("albertopibiri_keyboard::main_frame");

      }

      __keep(m_bUpdatingVisual);

      m_bRequestReady = false;

      bool bDisplay = defer_display();

      if (!is_equivalent(request_state().m_edisplay3, process_state().m_edisplay3))
      {

         m_tickLastDisplayChange.Now();

      }

      set_process_state(request_state());

      request_state().m_eactivation = activation_none;

      set_display_state(process_state().m_edisplay3);

      bool bAppearance = ui_state().m_eappearance != process_state().m_eappearance;

      bool bZorder = process_state().m_zorder.is_change_request();
      
      ::point pointUi = ui_state().m_point;
      
      ::point pointProcess = process_state().m_point;

      bool bPosition = pointUi != pointProcess || m_bReposition;

      m_bReposition = false;
      
      ::size sizeProcess = process_state().m_size;
      
      ::size sizeUi = ui_state().m_size;

      bool bLayout = sizeUi != sizeProcess || m_bNeedLayout;

      if (bDisplay || bAppearance)
      {

         // bPosition and bLayout wouldn't set this flag,
         // as it can trigger too many calls to save_window_rect.
         // moving and sizing changes are handled at
         // on_end_layout_experience

         if (m_ewindowflag & window_flag_loading_window_rect)
         {

            INFO("window visual changed: not setting pending save rect cause loading window rect");

         }
         else
         {

            m_ewindowflag |= window_flag_pending_save_window_rect;

         }

      }

      m_bUpdateVisual |= bDisplay || bZorder || bLayout;

      bUpdateBuffer = bLayout;

      bUpdateWindow = bDisplay || bZorder || bPosition;

      bool bDeferDisplay =
         m_bUpdateVisual
         || bPosition
         || !is_equivalent(window_state3().m_edisplay3, process_state().m_edisplay3);

      if(bDeferDisplay)
      {

         on_defer_display();

      }

      if (m_bUpdateVisual)
      {

         if (bAppearance)
         {

            prodevian_appearance();

         }

         if (bZorder)
         {

            prodevian_zorder();

         }

         if (bLayout)
         {

            prodevian_layout();

         }

         if (bDisplay)
         {

            //output_debug_string(::str::from(++g_i_prodevian_update_visual) + "updvis dpy change\n");

         }

      }

      if (bDeferDisplay || bPosition)
      {

         if (!(m_ewindowflag & window_flag_embedded_prodevian))
         {

            if (!(m_ewindowflag & window_flag_postpone_visual_update))
            {

               if (m_pimpl)
               {

                  m_pimpl->start_window_visual();

               }

            }

         }

      }

      if (bPosition)
      {

         prodevian_reposition();

      }

      if (bDisplay)
      {

         _001OnAfterAppearance();

      }

      if (!::is_screen_visible(process_display()))
      {

         if (m_ewindowflag & window_flag_on_show_window_visible
            || m_ewindowflag & window_flag_on_show_window_screen_visible)
         {

            m_ewindowflag -= window_flag_on_show_window_visible;

            m_ewindowflag -= window_flag_on_show_window_screen_visible;

            _on_show_window();

         }

      }
      else if(GetParent() != nullptr)
      {

         m_ewindowflag += window_flag_on_show_window_visible;

         m_ewindowflag += window_flag_on_show_window_screen_visible;

         _on_show_window();

      }

      if (m_bUpdateVisual || m_bReposition)
      {

         if(!(m_ewindowflag & window_flag_postpone_visual_update))
         {

            if (m_ewindowflag & window_flag_embedded_prodevian)
            {

               if(GetParent() == nullptr || GetParent() == Session.m_puiHost)
               {

                  if (m_pimpl2)
                  {

                     m_pimpl2->window_thread_apply_visual();

                  }

               }
               else
               {

                  if (m_pimpl)
                  {

                     m_pimpl->start_window_visual();

                  }

               }

            }

            ui_state().m_eactivation = activation_none;

         }

      }

   }


   void interaction::_001UpdateWindow()
   {

      if (m_bLockWindowUpdate)
      {

         return;

      }

      if (m_pimpl == nullptr)
      {

         return;

      }

      m_pimpl->_001UpdateWindow();

      on_after_graphical_update();

   }


   void interaction::window_apply_visual(const struct window_state & windowstate)
   {

      m_pimpl->window_apply_visual(windowstate);

   }


   void interaction::GuieProc(::message::message * pmessage)
   {

      UNREFERENCED_PARAMETER(pmessage);

   }


   void interaction::_001DeferPaintLayeredWindowBackground(::draw2d::graphics_pointer & pgraphics)
   {

      if (m_pimpl != nullptr)
      {

         //         m_pimpl->_001DeferPaintLayeredWindowBackground(pgraphics);

      }

   }


   void interaction::_001OnDeferPaintLayeredWindowBackground(::draw2d::graphics_pointer & pgraphics)
   {

      _001DeferPaintLayeredWindowBackground(pgraphics);

   }







   void interaction::OnLinkClick(const char * psz, const char * pszTarget)
   {

      Context.hyperlink().open_link(psz, "", pszTarget);

   }


   bool interaction::on_set_parent(::user::interaction * puiParent)
   {

      if (m_pdescriptor->m_puserinteractionParent == puiParent)
      {


         INFO("-------------------------------------------------------------------");
         INFO("");
         INFO("");
         INFO("interaction::on_set_parent (xxxx1)");
         INFO("");
         INFO("");
         return false;

      }

      if (::is_set(puiParent) && puiParent->is_descendant_of(this, true))
      {
         INFO("-------------------------------------------------------------------");
         INFO("");
         INFO("");
         INFO("interaction::on_set_parent (xxxx2)");
         INFO("");
         INFO("");

         return false;

      }

      __pointer(::user::interaction) puiThis = this;

      try
      {

         if (m_pdescriptor->m_puserinteractionParent != nullptr
               && m_pdescriptor->m_puserinteractionParent != puiParent)
         {

            INFO("-------------------------------------------------------------------");
            INFO("");
            INFO("");
            INFO("interaction::on_set_parent (remove)");
            INFO("");
            INFO("");


            single_lock sl(m_pdescriptor->m_puserinteractionParent->mutex(), TRUE);

            single_lock sl2(mutex(), TRUE);

            m_pdescriptor->m_puserinteractionParent->m_uiptraChild.remove(this);

         }

      }
      catch (...)
      {
      }

      m_pdescriptor->m_puserinteractionParent = puiParent;

      try
      {

         if (puiParent != nullptr)
         {

            INFO("-------------------------------------------------------------------");
            INFO("");
            INFO("");
            INFO("interaction::on_set_parent (3)");
            INFO("");
            INFO("");

            if (m_pthreadUserInteraction.is_set() && ::is_set(m_pthreadUserInteraction->m_puiptraThread))
            {

               m_pthreadUserInteraction->m_puiptraThread->remove(this);

            }

            __release(m_pthreadUserInteraction);

//#ifdef _UWP
//
//            __refer(m_pthreadUserInteraction, Session.m_puihost->m_pthreadUserInteraction);
//
//#else

            __refer(m_pthreadUserInteraction, puiParent->get_wnd()->m_pthreadUserInteraction);

//#endif

            puiParent->m_uiptraChild.add_unique(this);

         }

      }
      catch (...)
      {
         INFO("-------------------------------------------------------------------");
         INFO("");
         INFO("");
         INFO("interaction::on_set_parent (xxxxxx3)");
         INFO("");
         INFO("");

      }


      return true;

   }


   void interaction::on_after_set_parent()
   {


   }


   bool interaction::create_message_queue(const char * lpszName)
   {

      if (is_window())
      {

         DestroyWindow();

      }

      try
      {

         m_bUserPrimitiveOk = true;

         m_pimpl = __create < interaction_impl > ();

         if (m_pimpl == nullptr)
         {

            m_bUserPrimitiveOk = false;

            return false;

         }

         m_bMessageWindow = true;

         m_pimpl->m_puserinteraction = this;

         m_pdescriptor.create(this);
         //::thread * pthread = ::get_thread();

         //if(pthread != nullptr)
         //{

         //   m_threadptra.add(pthread);

         //}

         //if(m_threadptra.get_count() <= 0)
         //{

         //   m_threadptra.add(get_object());

         //}

         if (!m_pimpl->create_message_queue(this, lpszName))
         {

            //m_threadptra.remove_all();

            m_bUserPrimitiveOk = false;

            m_pimpl.release();

            return false;

         }

      }
      catch (...)
      {

         m_bUserPrimitiveOk = false;

         return false;

      }

      return true;

   }



   void interaction::walk_pre_translate_tree(::message::message * pmessage, ::user::interaction * puiStop)
   {

      if (puiStop == this)
      {

         return;

      }

      try
      {

         pre_translate_message(pmessage);

      }
      catch (...)
      {

      }

      if (!m_bDefaultWalkPreTranslateParentTree)
         return;

      if (pmessage->m_bRet)
         return;

      ::user::interaction * puiParent = GetParent();

      if (puiParent != nullptr)
         return;

      if (puiParent == puiStop)
         return;

      try
      {

         puiParent->pre_translate_message(pmessage);

      }
      catch (...)
      {

      }



   }


   bool interaction::contains_user_interaction(::user::interaction * pinteraction, bool bRecursive) const
   {

      if (this == pinteraction)
      {

         return true;

      }

      if (m_uiptraChild.contains(pinteraction))
      {

         return true;

      }

      if (!bRecursive)
      {

         return false;

      }

      for (auto & puiChild : m_uiptraChild.ptra())
      {

         if (puiChild->contains_user_interaction(pinteraction))
         {

            return true;

         }

      }

      return false;

   }


   void interaction::on_select()
   {

   }


   bool interaction::is_place_holder()
   {

      return false;

   }


   e_cursor interaction::get_cursor()
   {

      return m_ecursor;

   }


   bool interaction::set_cursor(e_cursor ecursor)
   {

      m_ecursor = ecursor;

      if (get_context_session())
      {

         Session.set_cursor(this, m_ecursor);

      }

      return true;

   }


   void interaction::_001OnMouseEnter(::message::message * pmessage)
   {

      pmessage->m_bRet = false;

   }


   bool interaction::can_merge(::user::interaction * pinteraction)
   {

      UNREFERENCED_PARAMETER(pinteraction);

      return false;

   }


   bool interaction::merge(::user::interaction * pinteraction)
   {

      UNREFERENCED_PARAMETER(pinteraction);

      return false;

   }


   ::user::primitive * interaction::first_child_user_primitive()
   {

      return first_child();

   }


   ::user::primitive * interaction::top_user_primitive()
   {

      return primitive::top_user_primitive();

   }


   ::user::primitive * interaction::under_user_primitive()
   {

      return under_sibling();

   }


   ::user::primitive * interaction::above_user_primitive()
   {

      return above_sibling();

   }


   ::user::primitive * interaction::next_user_primitive()
   {

      return next_sibling();

   }


   ::user::primitive * interaction::previous_user_primitive()
   {

      return previous_sibling();

   }



   ::user::interaction * interaction::first_child()
   {

      try
      {
         if (m_uiptraChild.get_count() <= 0)
            return nullptr;
         else
            return m_uiptraChild.first_pointer();

      }
      catch (...)
      {
      }
      return nullptr;
   }

   ::user::interaction * interaction::last_child()
   {
      try
      {
         if (m_uiptraChild.get_count() <= 0)
            return nullptr;
         else
            return m_uiptraChild.last_pointer();
      }
      catch (...)
      {
      }
      return nullptr;
   }



   ::user::interaction * interaction::first_sibling()
   {
      try
      {

         if (GetParent() == nullptr)
            return nullptr;

         return GetParent()->first_child();

      }
      catch (...)
      {
      }
      return nullptr;

   }


   ::user::interaction * interaction::next_sibling()
   {
      try
      {

         ::user::interaction * pinteraction = nullptr;
         try
         {
            pinteraction = GetParent();
         }
         catch (...)
         {
            return nullptr;
         }
         if (pinteraction == nullptr)
            return nullptr;
         index i = pinteraction->m_uiptraChild.find_first(this);
         if (i < 0)
            return nullptr;
         i++;
         if (i >= pinteraction->m_uiptraChild.get_count())
            return nullptr;
         else
            return pinteraction->m_uiptraChild[i];

      }
      catch (...)
      {
      }
      return nullptr;


   }

   ::user::interaction * interaction::next_sibling(::user::interaction * pinteraction)
   {
      sync_lock sl(mutex());
      try
      {

         index i = m_uiptraChild.find_first(pinteraction);
         if (i < 0)
            return nullptr;
         i++;
restart:
         if (i >= m_uiptraChild.get_count())
            return nullptr;
         else
         {
            try
            {
               return m_uiptraChild[i];
            }
            catch (...)
            {
               goto restart;
            }
         }
      }
      catch (...)
      {

      }

      return nullptr;

   }

   ::user::interaction * interaction::previous_sibling()
   {

      try
      {

         ::user::interaction * pinteraction = nullptr;
         try
         {
            pinteraction = GetParent();
         }
         catch (...)
         {
            return nullptr;
         }
         if (pinteraction == nullptr)
            return nullptr;
         index i = pinteraction->m_uiptraChild.find_first(this);
         if (i < 0)
            return nullptr;
         i--;
         if (i < 0)
            return nullptr;
         else
            return pinteraction->m_uiptraChild[i];

      }
      catch (...)
      {

      }

      return nullptr;

   }

   ::user::interaction * interaction::last_sibling()
   {

      try
      {

         if (GetParent() == nullptr)
            return nullptr;

         return GetParent()->last_child();

      }
      catch (...)
      {

      }

      return nullptr;


   }


   void interaction::mouse_hover_add(::user::interaction * pinterface)
   {

      if (m_pimpl == nullptr)
         return;

     m_pimpl->mouse_hover_add(pinterface);

   }


   bool interaction::mouse_hover_remove(::user::interaction * pinterface)
   {

      if (m_pimpl == nullptr)
      {

         return false;

      }

      return m_pimpl->mouse_hover_remove(pinterface);

   }


   i32 interaction::get_wheel_scroll_delta()
   {

      return 0;

   }


   ::user::interaction * interaction::previous_sibling(::user::interaction * pinteraction)
   {
      single_lock sl(mutex(), TRUE);
      index i = m_uiptraChild.find_first(pinteraction);
      if (i < 0)
         return nullptr;
restart:
      i--;
      if (i < 0)
         return nullptr;
      else
      {
         try
         {
            return m_uiptraChild[i];
         }
         catch (...)
         {
            goto restart;
         }
      }
   }


   void interaction::get_child_rect(RECT* prect)
   {

      get_client_rect(prect);

   }


   bool interaction::on_keyboard_focus(::user::primitive * pfocus)
   {

      if (m_pimpl == nullptr)
         return true;


      return m_pimpl->on_keyboard_focus(pfocus);

   }


   bool interaction::keyboard_focus_OnKillFocus(oswindow oswindowNew)
   {

      send_message(WM_KILLFOCUS, (WPARAM) oswindowNew);

      if (m_pimpl == nullptr)
      {

         return true;

      }

      return m_pimpl->keyboard_focus_OnKillFocus(oswindowNew);

   }


   bool interaction::keyboard_focus_OnChildKillFocus()
   {

      if (m_pimpl == nullptr)
         return true;


      return m_pimpl->keyboard_focus_OnChildKillFocus();

   }


   ::user::interaction * interaction::get_os_focus_uie()
   {

      return nullptr;

   }


   bool interaction::is_ascendant(const primitive * puiIsAscendant) const
   {

      return m_pimpl->is_ascendant(puiIsAscendant);

   }


   bool interaction::is_parent(const primitive * puiIsParent) const
   {

      return m_pimpl->is_parent(puiIsParent);

   }


   bool interaction::is_child(const primitive * puiIsChild) const
   {

      return m_pimpl->is_child(puiIsChild);

   }


   bool interaction::is_descendant(const primitive * puiIsDescendant) const
   {

      return m_pimpl->is_descendant(puiIsDescendant);

   }


   ::user::interaction * interaction::get_wnd() const
   {

      if(m_pdescriptor.is_null())
      {

         return nullptr;

      }

      if (m_pdescriptor->m_puserinteractionParent == nullptr)
      {

         return (::user::interaction*) this;

      }
          
      if(get_context_session() != nullptr
          && m_pdescriptor->m_puserinteractionParent == get_context_session()->m_puiHost)
      {

         return (::user::interaction *) this;

      }

      return m_pdescriptor->m_puserinteractionParent->get_wnd();

   }


// returns -1 if not descendant
   i32 interaction::get_descendant_level(::user::interaction * pinteraction)
   {
      i32 iLevel = 0;
      while (pinteraction != nullptr)
      {
         if (pinteraction == this)
            return iLevel;
         pinteraction = pinteraction->GetParent();
         iLevel++;
      }

      return -1;

   }


   bool interaction::is_descendant(::user::interaction * pinteraction, bool bIncludeSelf)
   {
      if (bIncludeSelf)
      {
         return get_descendant_level(pinteraction) >= 0;
      }
      else
      {
         return get_descendant_level(pinteraction) > 0;
      }
   }

   ::user::interaction * interaction::get_focusable_descendant(::user::interaction * pinteraction)
   {
      i32 iLevel = 0;
      if (pinteraction == nullptr)
      {
         pinteraction = this;
      }
      else if (pinteraction != this)
      {
         iLevel = get_descendant_level(pinteraction);
         if (iLevel < 0)
         {
            return nullptr;
         }
      }

      __pointer(::user::interaction) puiFocusable;

      i32 iPreviousLevel = iLevel;

      while (true)
      {
         iPreviousLevel = iLevel;
         pinteraction = pinteraction->get_next(false, &iLevel);
         if (iLevel == 0)
            break;
         if (iLevel <= iPreviousLevel && puiFocusable != nullptr)
            break;
         if (pinteraction == nullptr)
            break;
         if (pinteraction->keyboard_focus_is_focusable())
            puiFocusable = pinteraction;

      }
      return puiFocusable;
   }


   void interaction::_001OnTriggerMouseInside()
   {

      if (m_pimpl != nullptr)
      {

         m_pimpl->_001OnTriggerMouseInside();

      }

   }


   bool interaction::update_data(bool bSaveAndValidate)
   {

      return true;

   }


   void interaction::_001OnClose(::message::message * pmessage)
   {

      pmessage->m_bRet = true;

      for (auto& pitem : m_itema)
      {

         if (pitem->m_eelement == ::user::element_close_button
            || pitem->m_eelement == ::user::element_close_icon)
         {

            if (pitem->m_eevent == ::user::event_close_app)
            {

               Application.close(::aura::end_app);

            }

         }

      }

      display(display_none);

      DestroyWindow();

   }


   string interaction::get_window_default_matter()
   {

      return "";

   }


   string interaction::get_window_icon_matter()
   {

      return get_window_default_matter();

   }

   u32 interaction::get_window_default_style()
   {
      return 0;
   }

   ::user::interaction::e_type interaction::get_window_type()
   {
      return type_window;
   }


//bool interaction::post_simple_command(e_simple_command ecommand,lparam lparam)

//{

//   post_message(message_simple_command,(WPARAM)ecommand,lparam);


//   return true;

//}

   void interaction::_001OnCommand(::message::message * pmessage)
   {

      SCAST_PTR(::message::base, pbase, pmessage);

      LRESULT lresult = 0;

      pbase->m_bRet = OnCommand(pbase);

      pbase->m_lresult = lresult;

   }


   void interaction::_001OnSimpleCommand(::message::message * pmessage)
   {

      SCAST_MSG(simple_command);

      on_simple_command(psimple_command);

   }


   void interaction::_001OnNeedLoadFormData(::message::message * pmessage)
   {

      m_bNeedLoadFormData = false;

      update_data(false);

      set_need_redraw();

      post_redraw();

   }


   void interaction::_001OnNeedSaveFormData(::message::message * pmessage)
   {

      m_bNeedSaveFormData = false;

      update_data(true);

   }


   bool interaction::OnCommand(::message::base * pbase)
   {

      if (m_pimpl != nullptr)
         return m_pimpl->OnCommand(pbase);

      return false;

   }


   bool interaction::OnNotify(::message::base * pbase)
   {

      if (m_pimpl != nullptr)
         return m_pimpl->OnNotify(pbase);

      return false;

   }


   bool interaction::OnChildNotify(::message::base * pbase)
   {

      if (m_pimpl != nullptr)
         return m_pimpl->OnChildNotify(pbase);

      return false;

   }


   void interaction::on_simple_command(::message::simple_command * psimplecommand)
   {

      switch (psimplecommand->m_esimplecommand)
      {
      case simple_command_layout:
      {

         set_need_layout();

         psimplecommand->m_bRet = true;

      }
      case simple_command_check_transparent_mouse_events:
      {

      #ifdef WINDOWS_DESKTOP

         ::user::interaction* puiTop = get_wnd();

         if (puiTop != this)
         {

            ASSERT(FALSE);

            return;

         }

         __pointer(::user::interaction_impl) pimpl = m_pimpl;

         bool bStart = pimpl->m_bTransparentMouseEvents
               && puiTop->is_this_visible()
               || (puiTop->GetExStyle() & WS_EX_LAYERED
                  && puiTop->window_is_full_screen());

         if (bStart && is_layout_experience_active())
         {

            bStart = false;

         }

         if (bStart)
         {

            value("transparent_mouse_event_thread") = fork([this]()
               {

                  auto pthread = ::get_thread();
                  ::point pointCursor;

                  auto pimpl = m_pimpl.cast < interaction_impl>();

                  oswindow oswindow = get_safe_handle();

            while (pthread->thread_get_run())
            {

         ::GetCursorPos(pointCursor);

         if (pimpl->m_pointCursor == pointCursor)
         {
            Sleep(30);
            continue;

         }

         pimpl->m_pointCursor = pointCursor;

         LPARAM lparam;

         ::ScreenToClient(oswindow, pointCursor);
         RECT rectClient;
         ::GetClientRect(oswindow, &rectClient);

         if (!PtInRect(&rectClient, pointCursor))
         {
            Sleep(100);
            continue;

         }
         lparam = MAKELPARAM(pointCursor.x, pointCursor.y);
         output_debug_string("transparent_mouse_event:x="+__str(pointCursor.x) +",y="+__str(pointCursor.y)+"\n");
         pimpl->call_message_handler(WM_MOUSEMOVE, 0, lparam);

               }
         }
         );
            //::SetTimer(get_handle(), timer_transparent_mouse_event, 5, NULL);

            //SetTimer(timer_transparent_mouse_event, 100);

         }
         else
         {

            auto& pthread = value("transparent_mouse_event_thread").cast<::thread>();

            if (pthread)
            {

               pthread->post_quit();

               value("transparent_mouse_event_thread").unset();

            }

            //::KillTimer(get_handle(), timer_transparent_mouse_event);

            //KillTimer(timer_transparent_mouse_event);

         }

         #endif

      }
      break;
         //case simple_command_defer_start_prodevian:
         //{

         //   m_pimpl->_defer_start_prodevian();


         //}
      break;
      default:

         break;

      }

      if (psimplecommand->m_bRet)
      {

         return;

      }

      ::user::primitive::on_simple_command(psimplecommand);

   }


   void interaction::on_command(::user::command * pcommand)
   {

      ::user::primitive::on_command(pcommand);

   }


   bool interaction::is_selected(::data::item * pitem)
   {

      UNREFERENCED_PARAMETER(pitem);

      return false;

   }


   bool interaction::has_command_handler(::user::command * pcommand)
   {

      if (channel::has_command_handler(pcommand))
      {

         return true;

      }

      return false;

   }


   //bool interaction::track_popup_menu(::user::menu_item * pitem, i32 iFlags)
   //{

   //   ::point point;

   //   Session.get_cursor_pos(point);

   //   return track_popup_menu(pitem, iFlags, point);

   //}


   //__pointer(::user::menu) interaction::track_popup_xml_menu_text(string strXml, i32 iFlags)
   //{

   //   auto point = Session.get_cursor_pos();

   //   return track_popup_xml_menu_text(strXml, iFlags, point);

   //}


   //__pointer(::user::menu) interaction::track_popup_xml_matter_menu(const char * pszMatter, i32 iFlags)
   //{

   //   auto point = Session.get_cursor_pos();

   //   return track_popup_xml_matter_menu(pszMatter, iFlags, point);

   //}



   //bool interaction::track_popup_menu(::user::menu_item * pitem, i32 iFlags, ::message::message * pmessage)
   //{

   //   SCAST_PTR(::message::mouse, pmouse, pmessage);

   //   ::point point = pmouse->m_point;

   //   _001ScreenToClient(point);

   //   return track_popup_menu(pitem, iFlags, point);

   //}


   //__pointer(::user::menu) interaction::track_popup_xml_menu_text(string strXml, i32 iFlags, ::message::message * pmessage)
   //{

   //   SCAST_PTR(::message::mouse, pmouse, pmessage);

   //   auto point = pmouse->m_point;

   //   _001ScreenToClient(point);

   //   return track_popup_xml_menu_text(strXml, iFlags, point);


   //}


   //__pointer(::user::menu) interaction::track_popup_xml_matter_menu(const char * pszMatter, i32 iFlags, ::message::message * pmessage)
   //{

   //   SCAST_PTR(::message::mouse, pmouse, pmessage);

   //   ::point point = pmouse->m_point;

   //   return track_popup_xml_matter_menu(pszMatter, iFlags, point);

   //}


   //bool interaction::track_popup_menu(::user::menu_item * pitem, i32 iFlags, const ::point & point)
   //{

   //   __pointer(::user::menu) pmenu = __create <  ::user::menu  > ();

   //   pmenu->m_pmenuitemThis = pitem;

   //   if (!pmenu->track_popup_menu(this, this))
   //   {

   //      pmenu.release();

   //      return false;

   //   }

   //   return true;

   //}


   //__pointer(::user::menu) interaction::track_popup_xml_menu(const var & varXml, i32 iFlags, const ::point & point, const ::size & sizeMinimum)
   //{

   //   __pointer(::user::menu) pmenu = __create <  ::user::menu  > ();

   //   pmenu->m_sizeMinimum = sizeMinimum;

   //   if (!pmenu->load_xml_menu(varXml))
   //   {

   //      pmenu.release();

   //      return pmenu;

   //   }

   //   pmenu->hints(iFlags, point);

   //   if (!pmenu->track_popup_menu(this, this))
   //   {

   //      pmenu.release();

   //      return pmenu;

   //   }

   //   return pmenu;

   //}


   //__pointer(::user::menu) interaction::track_popup_xml_matter_menu(const char * pszMatter, i32 iFlags, const ::point & pointParam)
   //{

   //   string strMatterSource(pszMatter);

   //   ::point point(pointParam);

   //   fork([=]()
   //   {

   //      __pointer(::user::menu) pmenu = alloc <  ::user::menu  >();

   //      string strMatter(strMatterSource);

   //      if (!strMatter.begins_ci("matter://"))
   //      {

   //         strMatter = "matter://" + strMatter;

   //      }

   //      if (!pmenu->load_xml_menu_file(strMatter))
   //      {

   //         pmenu.release();

   //         return false;

   //      }

   //      pmenu->hints(iFlags, point);

   //      if (!pmenu->track_popup_menu(this))
   //      {

   //         pmenu.release();

   //         return false;

   //      }

   //      return true;

   //   });

   //   return true;

   //}


   //__pointer(::user::menu) interaction::track_popup_xml_menu_file(var varXmlFile, i32 iFlags, const ::point & point, const ::size & sizeMinimum)
   //{

   //   string strXml = Context.file().as_string(varXmlFile);

   //   return track_popup_xml_menu_text(strXml, iFlags, point, sizeMinimum)

   //   //__pointer(::user::menu) pmenu = alloc <  ::user::menu  > ();

   //   //pmenu->m_sizeMinimum = sizeMinimum;

   //   //if (!pmenu->load_xml_menu_file(varXmlFile))
   //   //{

   //   //   pmenu.release();

   //   //   return pmenu;

   //   //}

   //   //pmenu->hints(iFlags, point);

   //   //if (!pmenu->track_popup_menu(this))
   //   //{

   //   //   pmenu.release();

   //   //   return pmenu;

   //   //}

   //   //return pmenu;

   //}


   void interaction::_001OnExitIconic()
   {

      if(m_pimpl.is_null())
      {

         return;

      }

      m_pimpl->_001OnExitIconic();

   }


   void interaction::_001OnExitFullScreen()
   {

      if(m_pimpl.is_null())
      {

         return;

      }

      m_pimpl->_001OnExitFullScreen();

   }


   //void interaction::defer_exit_iconify()
   //{

   //   if(get_display() == display_iconic)
   //   {

   //      exit_iconify();

   //   }

   //}


   //void interaction::defer_exit_full_screen()
   //{

   //   if(get_display() == display_full_screen)
   //   {

   //      exit_full_screen();

   //   }

   //}


   bool interaction::_001OnBeforeAppearance()
   {

      return true;

   }


   bool interaction::_001OnExitAppearance()
   {

      if (display_request() != display_none
         && display_request() != display_current)
      {

         if (display_request() != display_iconic && display_state() == display_iconic)
         {

            _001OnExitIconic();

         }

         if (display_request() != display_full_screen && display_state() == display_full_screen)
         {

            _001OnExitFullScreen();

         }

      }

      return true;

   }


   void interaction::show_keyboard(bool bShow)
   {

      if (m_pimpl == nullptr)
      {

         return;

      }

      m_pimpl->show_keyboard(bShow);

   }



   void interaction::keep_alive(::object * pliveobject)
   {

      get_context_application()->keep_alive();

      if (::get_thread() != nullptr)
      {

         ::get_thread()->keep_alive();

      }

      if (pliveobject != nullptr)
      {

         pliveobject->keep_alive();

      }

   }


   ::user::interaction * interaction::best_top_level_parent(RECT * prect)
   {

      __pointer(::user::interaction) pinteraction = GetTopLevel();

      if (!pinteraction || pinteraction == this)
      {

         best_monitor(prect);

      }
      else
      {

         pinteraction->get_window_rect(prect);

      }

      return pinteraction;

   }


   void interaction::get_window_rect(RECT* prect) const
   {
      
      ::user::layout::get_window_rect(prect);
      
      ::point pointParentOffset = get_parent_viewport_offset();
      
      ::offset(prect, -pointParentOffset.x, -pointParentOffset.y);
      
   }


   void interaction::prodevian_prepare_window_minimize(::eactivation eactivation)
   {

      auto rectRequest = window_request_rect();

      good_iconify(nullptr, rectRequest, true, eactivation, request_state().m_zorder);

   }


   void interaction::prodevian_prepare_window_maximize()
   {

      ::rect rectRequest = window_request_rect();

      best_wkspace(nullptr, rectRequest, true, request_state().m_eactivation, request_state().m_zorder);

   }


   void interaction::prodevian_prepare_window_full_screen(const ::rect & rectHint)
   {

      ::rect rectRequest;

      if (!rectHint.is_empty())
      {

         rectRequest = rectHint;

      }
      else
      {

         rectRequest = window_request_rect();

      }

      best_monitor(nullptr, rectRequest, true, request_state().m_eactivation, request_state().m_zorder);

   }


   void interaction::prodevian_prepare_window_restore(edisplay edisplay)
   {

      auto rectRequest = window_request_rect();

      good_restore(nullptr, rectRequest, true, request_state().m_eactivation, request_state().m_zorder, edisplay);

   }


   void interaction::prodevian_prepare_window_dock(edisplay edisplay)
   {

      ASSERT(is_docking_appearance(edisplay));

      if (is_docking_appearance(edisplay))
      {

         auto rectRequest = window_request_rect();

         make_zoneing(nullptr, rectRequest, true, &edisplay, request_state().m_eactivation, request_state().m_zorder);

      }

   }


   index interaction::best_monitor(RECT * prect, const ::rect & rect, bool bSet, ::eactivation eactivation, ::zorder zorderParam)
   {

      ::rect rectSample;

      if (eactivation & activation_under_mouse_cursor || rect.is_null())
      {

         ::point pointCursor = Session.get_cursor_pos();

         rectSample.set(pointCursor - ::size(5, 5), ::size(10, 10));

      }
      else if (rect.is_set())
      {

         rectSample = rect;

      }
      else
      {

         get_window_rect(rectSample);

      }

      ::rect rectNew;

      index iMatchingMonitor = -1;

      if (GetParent() != nullptr)
      {

         GetParent()->get_client_rect(rectNew);

         iMatchingMonitor = 0;

      }
      else
      {

         if (m_bWorkspaceFullScreen)
         {

            iMatchingMonitor = get_best_wkspace(&rectNew, rectSample);

         }
         else
         {

            iMatchingMonitor = Session.get_best_monitor(rectNew, rectSample);

         }

      }

      if (bSet && rectNew.is_set() && iMatchingMonitor >= 0)
      {

         INFO("interaction::bestmonitor (%d, %d, %d, %d) activation %d", rectNew.left, rectNew.top, rectNew.right, rectNew.bottom, (i32) eactivation);

         order(zorderParam);

         place(rectNew);

         display(display_full_screen, eactivation);

      }

      if (prect != nullptr)
      {

         *prect = rectNew;

      }

      return iMatchingMonitor;

   }


   index interaction::best_wkspace(RECT * prect, const ::rect & rect, bool bSet, ::eactivation eactivation, ::zorder zorderParam)
   {

      ::rect rectWindow;

      if (!::IsRectEmpty(&rect))
      {

         rectWindow = rect;

      }
      else
      {

         get_window_rect(rectWindow);

      }

      ::rect rectNew;

      index iMatchingMonitor = Session.get_best_monitor(rectNew, rectWindow, eactivation);

      ::rect rectWkspace;

      Session.get_wkspace_rect(iMatchingMonitor, rectWkspace);

      if (bSet && (!::IsRectEmpty(&rect) || iMatchingMonitor >= 0))
      {
         
#if !MOBILE_PLATFORM

         if (iMatchingMonitor >= 0 && rectNew.bottom > 0)
         {

            if (rectWkspace.bottom > rectNew.bottom - 2)
            {

               rectWkspace.bottom = rectNew.bottom - 2;

            }

         }
         
#endif

         order(zorderParam);

         place(rectWkspace);

         display(display_zoomed, eactivation | activation_display_change);

      }

      if (prect != nullptr)
      {

         *prect = rectWkspace;


      }

      return iMatchingMonitor;

   }


   index interaction::get_zoneing(::rect * prect, const ::rect & rectParam, edisplay edisplay)
   {

      if (!is_docking_appearance(edisplay))
      {

         return -1;

      }

      ::rect rectWkspace;

      index iWkspace = get_best_wkspace(&rectWkspace, rectParam);

      if (iWkspace < 0 || rectWkspace.is_empty())
      {

         return -1;

      }

      if (rectParam)
      {

         *prect = rectParam;

      }
      else
      {

         auto point = rectWkspace.center();

         ::top_left(prect) = point;

         ::bottom_right(prect) = point;

      }

      auto sizeMinimum = get_window_minimum_size();

      if (edisplay & ::display_top)
      {

         prect->move_top_to(rectWkspace.top);

         if(::height(prect) < sizeMinimum.cy)
         {

            prect->bottom = prect->top + sizeMinimum.cy;

         }

      }

      if (edisplay & ::display_bottom)
      {

         prect->move_bottom_to(rectWkspace.bottom);

         if(::height(prect) < sizeMinimum.cy)
         {

            prect->top = prect->bottom - sizeMinimum.cy;

         }

      }

      if (edisplay & ::display_left)
      {

         prect->move_left_to(rectWkspace.left);

         if(::width(prect) < sizeMinimum.cx)
         {

            prect->right = prect->left + sizeMinimum.cx;

         }

      }

      if (edisplay & ::display_right)
      {

         prect->move_right_to(rectWkspace.right);

         if(::width(prect) < sizeMinimum.cx)
         {

            prect->left = prect->right + sizeMinimum.cx;

         }

      }

      return iWkspace;

   }


   edisplay interaction::initial_restore_display()
   {

      return display_restore;

   }


   index interaction::calculate_broad_and_compact_restore(RECT* prectWkspace, SIZE * psizeMin, const ::rect& rectHint)
   {

      ::rect rectRestore(rectHint);

      if (rectRestore.is_null())
      {

         rectRestore = window_request_rect();

      }

      ::rect rectWkspace;

      index iMatchingWkspace = Session.get_best_wkspace(&rectWkspace, rectRestore);

      if (iMatchingWkspace >= 0)
      {

         ::size sizeMin;

         if (::is_set(psizeMin) && !is_empty(psizeMin))
         {

            sizeMin = *psizeMin;

         }
         else
         {

            sizeMin = get_window_minimum_size();

         }

         m_sizeRestoreBroad = sizeMin.max(rectWkspace.size() * 4 / 5);

         m_sizeRestoreCompact = sizeMin.max(rectWkspace.size() * 2 / 5);

         if (::is_set(prectWkspace))
         {

            *prectWkspace = rectWkspace;

         }

         if (::is_set(psizeMin))
         {

            *psizeMin = sizeMin;

         }

      }

      return iMatchingWkspace;

   }


   void interaction::reset_window_state()
   {

      m_statePrevious2.reset();
      m_stateRequest2.reset();
      m_stateProcess2.reset();
      m_state2.reset();
      m_stateWindow3.reset();
      m_windowrect.reset();
      m_windowrectStore.reset();

   }


   index interaction::make_zoneing(RECT * prect, const ::rect & rect, bool bSet, edisplay * pedisplay, ::eactivation eactivation, ::zorder zorderParam)
   {

      if (pedisplay == nullptr || !is_docking_appearance(*pedisplay))
      {

         return best_zoneing(prect, rect, bSet, pedisplay, eactivation, zorderParam);


      }

      ::rect rectWindow;

      if (IsRectEmpty(&rect))
      {

         get_window_rect(rectWindow);

      }
      else
      {

         rectWindow = rect;

      }

      ::rect rectNew;

      index iMatchingMonitor = get_zoneing(&rectNew, rectWindow, *pedisplay);

      if (bSet && !::IsRectEmpty(&rectNew) && iMatchingMonitor >= 0)
      {

         sync_lock slUserMutex(mutex());

         order(zorderParam);

         place(rectNew);

         display(*pedisplay, eactivation);

      }

      if (prect != nullptr)
      {

         *prect = rectNew;

      }

      return iMatchingMonitor;

   }


   index interaction::get_best_zoneing(edisplay & edisplay, ::rect * prect, const ::rect & rectRequest, bool bPreserveSize)
   {

      edisplay = display_state();

      if (rectRequest.is_empty())
      {

         return Session._get_best_zoneing(&edisplay, prect, ui_state().rect(), bPreserveSize);

      }
      else
      {

         return Session._get_best_zoneing(&edisplay, prect, rectRequest, bPreserveSize);

      }

   }


   index interaction::get_best_wkspace(::rect * prect, const ::rect& rect, ::eactivation eactivation)
   {

      return Session.get_best_wkspace(prect, rect, eactivation);

   }


   index interaction::best_zoneing(RECT * prect, const ::rect & rect, bool bSet, edisplay * pedisplay, ::eactivation eactivation, ::zorder zorderParam)
   {

      edisplay edisplay;

      if (pedisplay == nullptr)
      {

         pedisplay = &edisplay;

      }

      *pedisplay = display_state();

      ::rect rectNew;

      index iMatchingMonitor;

      if (rect.is_set())
      {

         iMatchingMonitor = Session._get_best_zoneing(pedisplay, &rectNew, rect);

      }
      else
      {

         iMatchingMonitor = get_best_zoneing(*pedisplay, &rectNew);

      }

      if (bSet && (!::IsRectEmpty(&rect) || iMatchingMonitor >= 0))
      {

         sync_lock slUserMutex(mutex());

         order(zorderParam);

         place(rectNew);

         display(*pedisplay, eactivation);

      }

      if (prect != nullptr)

      {

         *prect = rectNew;


      }

      return iMatchingMonitor;

   }


   index interaction::good_restore(RECT * prect, const ::rect & rect, bool bSet, ::eactivation eactivation, ::zorder zorderParam, edisplay edisplay)
   {

      ::rect rectWindow;

      if (!::IsRectEmpty(&rect))
      {

         rectWindow = rect;

      }
      else
      {

         get_window_rect(rectWindow);

      }

      ::rect rectNew;

      index iMatchingMonitor = Session.get_window_restore_2(rectNew, rectWindow, this, edisplay);

      if (bSet)
      {

         if (rectNew.is_set() && iMatchingMonitor >= 0)
         {

            order(zorderParam);

            place(rectNew);

            display(display_normal, eactivation);

            SetWindowDisplayChanged();

         }
         else
         {

            order(zorderParam);

            place(rectWindow);

            display(display_normal, eactivation);

            SetWindowDisplayChanged();

         }

      }

      if (prect != nullptr)
      {

         *prect = rectNew;

      }

      return iMatchingMonitor;

   }


   index interaction::good_iconify(RECT * prect, const ::rect & rect, bool bSet, ::eactivation eactivation, ::zorder zorderParam)
   {

      ::rect rectWindow;

      if (!::IsRectEmpty(&rect))
      {

         rectWindow = rect;

      }
      else
      {

         get_window_rect(rectWindow);

      }

      ::rect rectNew;

      index iMatchingMonitor = Session.get_good_iconify(&rectNew, rectWindow);

      if (bSet && (!::IsRectEmpty(&rectNew) || iMatchingMonitor >= 0))
      {

         sync_lock slUserMutex(mutex());

         display(display_iconic, eactivation);

      }

      if (prect != nullptr)
      {

         *prect = rectNew;

      }

      return iMatchingMonitor;

   }


   index interaction::good_move(RECT * prect, const ::rect & rect, ::eactivation eactivation, ::zorder zorderParam)
   {

      ::rect rectWindow;

      if (!::IsRectEmpty(&rect))
      {

         rectWindow = rect;

      }
      else
      {

         get_window_rect(rectWindow);

      }

      ::rect rectNew;

      index iMatchingMonitor = Session.get_good_move(rectNew, rectWindow, this);

      if (!::IsRectEmpty(&rectNew) || iMatchingMonitor >= 0)
      {

         order(zorderParam);

         place(rectNew);

         display(display_normal, eactivation);

      }

      if (prect != nullptr)
      {

         *prect = rectNew;

      }

      return iMatchingMonitor;

   }


   id interaction::GetDlgCtrlId() const
   {

      return m_id;

   }


   id interaction::SetDlgCtrlId(id id)
   {

      m_id = id;

      return m_id;

   }


   //void interaction::_001OnBaseWndGetProperty(::message::message * pmessage)
   //{
   //
   //   SCAST_PTR(::message::base, pbase, pmessage);

   //   pbase->m_lresult = _001BaseWndGetProperty((EProperty)pbase->m_wparam.m_number, pbase->m_lparam);

   //}


   //LRESULT interaction::_001BaseWndGetProperty(EProperty eprop, LPARAM lparam)

   //{
   //   switch (eprop)
   //   {
   //   case PropertyBaseWndInterface:
   //   case PropertyDrawBaseWndInterface:
   //   {
   //      const primitive ** ppinterface = (const primitive **)lparam;

   //      *ppinterface = this;
   //   }
   //   return 1;
   //   default:
   //      break;
   //   }
   //   return 0;
   //}



   bool interaction::get_rect_normal(RECT * prect)

   {

      return m_pimpl->get_rect_normal(prect);


   }


   scroll_bar* interaction::get_horizontal_scroll_bar()
   {

      return nullptr;

   }


   scroll_bar* interaction::get_vertical_scroll_bar()
   {

      return nullptr;

   }


   scroll_data* interaction::get_horizontal_scroll_data()
   {

      return nullptr;

   }


   scroll_data* interaction::get_vertical_scroll_data()
   {

      return nullptr;

   }


   void interaction::offset_viewport_offset(int x, int y)
   {

      auto pointOffset = get_viewport_offset();

      set_viewport_offset(pointOffset.x + x, pointOffset.y + y);

   }


   void interaction::offset_viewport_offset_x(int x)
   {

      offset_viewport_offset(x, 0);

   }


   void interaction::offset_viewport_offset_y(int y)
   {

      offset_viewport_offset(0, y);

   }


   void interaction::set_viewport_offset(int x, int y)
   {

      ::point pointOffset(x, y);

      if (pointOffset == m_pointScroll)
      {

         return;

      }

      if(!validate_viewport_offset(pointOffset))
      {

         return;

      }

      m_pointScroll = pointOffset;

      on_change_viewport_offset();

   }


   bool interaction::validate_viewport_offset(point & point)
   {

      if (point == m_pointScroll)
      {

         return false;

      }

      return true;

   }


   void interaction::set_viewport_offset_x(int x)
   {

      set_viewport_offset(x, (::i32) get_viewport_offset().y);

   }


   void interaction::set_viewport_offset_y(int y)
   {

      set_viewport_offset((::i32) get_viewport_offset().x, y);

   }


   void interaction::on_change_viewport_offset()
   {

      set_need_redraw();

   }


   point interaction::get_viewport_offset()
   {
      
      ::point point = m_pointScroll;
      
      return point;

   }


   sized interaction::get_total_size()
   {

      ::rect rectClient;

      get_client_rect(rectClient);

      return rectClient.size();

   }

   ::estatus interaction::set_total_size(const ::sized& size)
   {

      return ::error_interface_only;

   }


   ::estatus interaction::set_page_size(const ::sized& size)
   {

      return ::error_interface_only;

   }


   void interaction::on_change_view_size()
   {

   }


   sized interaction::get_page_size()
   {

      ::rect rectClient;

      get_client_rect(rectClient);

      return rectClient.size();

   }


   point interaction::get_ascendant_viewport_offset() const
   {

      __pointer(::user::interaction) puser = GetParent();

      point point;

      while (puser.is_set())
      {

         point += puser->get_viewport_offset();

         puser = puser->GetParent();

      }

      return point;

   }


   void interaction::get_margin_rect(RECT * prectMargin)

   {

      prectMargin->left = 0;

      prectMargin->top = 0;

      prectMargin->right = 0;

      prectMargin->bottom = 0;


   }

   int interaction::get_final_x_scroll_bar_width()
   {

      return 0;

   }

   int interaction::get_final_y_scroll_bar_width()
   {

      return 0;

   }


   bool interaction::is_system_message_window()
   {

      return false;

   }


   point interaction::get_parent_viewport_offset() const
   {

      ::user::interaction * puser = GetParent();

      if (puser == nullptr)
      {

         return ::point();

      }
      
      ::point pointParentAccumulated;
      
      if(puser != NULL)
      {
         
         pointParentAccumulated = puser->get_viewport_offset();
         
         pointParentAccumulated += puser->get_parent_viewport_offset();
         
      }
      
      return pointParentAccumulated;

   }


//   bool interaction::set(::draw2d::graphics_pointer & pgraphics, e_font efont)
//   {
//
//      return ::user::style::set(pgraphics, efont, this);
//
//   }


//::user::style * interaction::parent_userstyle()
//{

//   ::user::interaction * puiParent = GetParent();

//   if (puiParent == nullptr)
//      return nullptr;

//   return puiParent->userstyle();

//}

   void interaction::_001OnShowWindow(::message::message * pmessage)
   {

      SCAST_PTR(::message::show_window, pshowwindow, pmessage);
//SW_OTHERUNZOOM
//4
//The window is being uncovered because a maximize window was restored or minimized.
//SW_OTHERZOOM
//2
//The window is being covered by another window that has been maximized.
//SW_PARENTCLOSING
//1
//The window's owner window is being minimized.
//SW_PARENTOPENING
//3
//The window's owner window is being restored.

      //sync_lock sl(mutex_children());

      //if(m_uiptraChild.has_element())
      //{

      //   auto uiptra = m_uiptraChild;

      //   if(pshowwindow->m_bShow)
      //   {

      //      for(auto & pui : uiptra)
      //      {

      //         try
      //         {

      //            if (pui && pui->is_this_visible())
      //            {

      //               pui->send_message(WM_SHOWWINDOW, 1, SW_PARENTOPENING);

      //            }

      //         }
      //         catch (...)
      //         {

      //         }

      //      }

      //   }
      //   else
      //   {

      //      for (index i = 0; i < uiptra.get_size(); i++)
      //      {

      //         try
      //         {

      //            if (uiptra[i].is_set() && uiptra[i]->is_this_visible())
      //            {

      //               uiptra[i]->send_message(WM_SHOWWINDOW, 0, SW_PARENTCLOSING);

      //            }

      //         }
      //         catch (...)
      //         {

      //         }

      //      }

      //   }

      //}

   }


   void interaction::_001OnKillFocus(::message::message* pmessage)
   {

      SCAST_PTR(::message::kill_focus, pkillfocus, pmessage);

      _OnKillFocus();

      ::user::control_event ev;

      ev.m_puie = this;

      ev.m_id = m_id;

      ev.m_eevent = ::user::event_kill_focus;

      on_control_event(&ev);

      pkillfocus->m_bRet = ev.m_bRet;

   }

      
   void interaction::_001OnSetFocus(::message::message * pmessage)
   {

      SCAST_PTR(::message::set_focus, psetfocus, pmessage);

      on_reset_focus_start_tick();

      // get_keyboard_focus will return the control with focus

      if (Session.m_puiHost == this)
      {

         return;

      }

      // return true to set focus to this control
      Application.keyboard_focus_OnSetFocus(this);

      _OnSetFocus();

      ::user::control_event ev;

      ev.m_puie = this;

      ev.m_eevent = ::user::event_set_focus;

      on_control_event(&ev);

      pmessage->m_bRet = ev.m_bRet;

   }


   ::graphics::graphics * interaction::get_window_graphics()
   {

      if (m_pimpl == nullptr)
         return ::user::primitive::get_window_graphics();

      return m_pimpl->get_window_graphics();

   }


   bool interaction::is_composite()
   {

      if (m_pimpl == nullptr)
         return true; // optimistic response, assume always true alpha blendable

      return m_pimpl->is_composite();

   }

   size interaction::get_window_minimum_size()
   {

      return nullptr;

   }

// up down target

//UpDownTarget::UpDownTarget()
//{
//   m_eupdowntargettype = type_normal_frame;
//}

   void interaction::UpDownTargetAttach(::user::interaction * pupdown)
   {

      //bool bAttached = false;

      //pupdown->m_eupdown = updown_down;

      //try
      //{

      //   if (OnUpDownTargetAttach(pupdown))
      //   {

      //      bAttached = true;

      //   }

      //}
      //catch (...)
      //{

      //}

      //if (!bAttached)
      //{

      //   pupdown->m_eupdown = updown_none;

      //}

   }


   void interaction::UpDownTargetDetach(::user::interaction * pupdown)
   {

      //bool bDetached = false;

      //pupdown->m_eupdown = updown_up;

      //try
      //{

      //   if (OnUpDownTargetDetach(pupdown))
      //   {

      //      bDetached = true;

      //   }

      //}
      //catch (...)
      //{

      //}

      //if (!bDetached)
      //{

      //   pupdown->m_eupdown = updown_none;

      //}

   }


   bool interaction::OnUpDownTargetAttach(::user::interaction * pupdown)
   {

      return false;

   }


   bool interaction::OnUpDownTargetDetach(::user::interaction * pupdown)
   {

      return false;

   }




   void interaction::keyboard_focus_OnKeyDown(::message::message * pmessage)
   {

      SCAST_PTR(::message::key, pkey, pmessage);

      if (pkey->m_ekey == ::user::key_tab)
      {

         control_event ev;

         ev.m_puie = dynamic_cast <::user::interaction *> (this);
         ev.m_eevent = ::user::event_tab_key;
         ev.m_actioncontext = ::source_user;

         route_control_event(&ev);

      }

   }



   bool interaction::get_child(__pointer(::user::interaction) & pinteraction)
   {

      sync_lock sl(mutex());

      return m_uiptraChild.get_child(pinteraction);

   }

   bool interaction::rget_child(__pointer(::user::interaction) & pinteraction)
   {

      sync_lock sl(mutex());

      return m_uiptraChild.rget_child(pinteraction);

   }


   ::user::primitive * interaction::get_focus_primitive()
   {

      if (m_pimpl == nullptr)
      {

         return nullptr;

      }

      return m_pimpl->get_focus_primitive();

   }


   bool interaction::set_focus_primitive(::user::primitive * pprimitive)
   {

      if (m_pimpl == nullptr)
      {

         return false;

      }

      return m_pimpl->set_focus_primitive(pprimitive);

   }


   bool interaction::is_ascendant_of(::user::interaction * puiDescendantCandidate, bool bIncludeSelf)
   {

      if (puiDescendantCandidate == nullptr)
      {

         return false;

      }

      return puiDescendantCandidate->is_descendant_of(this, bIncludeSelf);

   }


   bool interaction::is_descendant_of(::user::interaction * puiAscendantCandidate, bool bIncludeSelf)
   {

      ::user::interaction * pinteraction = bIncludeSelf ? this : GetParent();

      while (pinteraction != nullptr)
      {

         if (pinteraction == puiAscendantCandidate)
         {

            return true;

         }

         pinteraction = pinteraction->GetParent();

      }

      return false;

   }


   bool interaction::is_ascendant_or_owner_of(::user::interaction * puiDescendantCandidate, bool bIncludeSelf)
   {

      if (puiDescendantCandidate == nullptr)
      {

         return false;

      }

      return puiDescendantCandidate->is_descendant_of_or_owned_by(this, bIncludeSelf);

   }


   bool interaction::is_descendant_of_or_owned_by(::user::interaction * puiAscendantCandidate, bool bIncludeSelf)
   {

      ::user::interaction * pinteraction = bIncludeSelf ? this : GetParentOrOwner();

      while (pinteraction != nullptr)
      {

         if (pinteraction == puiAscendantCandidate)
            return true;

         pinteraction = pinteraction->GetParentOrOwner();

      }

      return false;

   }


   bool interaction::kick_queue()
   {

      post_message(::message_null);

      return true;

   }


   bool interaction::is_left_button_pressed() const
   {

      return get_context_application()->get_context_session()->m_puiLastLButtonDown == this;

   }


   void interaction::set_current_item(const ::user::item & item, const ::action_context & context)
   {

      m_itemCurrent = item;

   }


   item interaction::current_item()
   {

      return m_itemCurrent;

   }


   item interaction::hover_item()
   {

      return m_itemHover;

   }


   bool interaction::show_tooltip(const string & str, bool bError)
   {

//
//
//      if (m_ptooltip.is_null())
//      {
//
//         m_ptooltip = __new(tooltip(get_context_object()));
//
////#ifdef WINDOWS_DESKTOP
////
////         ::user::create_struct createstruct(WS_EX_LAYERED | WS_EX_TOOLWINDOW, nullptr, L"tooltip", 0, nullptr);
////
////#else
//
//         ::user::create_struct createstruct(WS_EX_LAYERED | WS_EX_TOOLWINDOW, nullptr, "tooltip", 0, nullptr);
//
////#endif
//
//         m_ptooltip->create_window_ex(createstruct);
//
//      }
//
//      get_tooltip()->m_str = str;
//
//      get_tooltip()->m_bError = bError;
//
//      get_tooltip()->CalcSize();
//
//      if (!layout_tooltip(true))
//      {
//
//         return false;
//
//      }

      return true;

   }

   void interaction::ExitHelpMode()
   {

   }


   void interaction::on_control_event(::message::base * pbase)
   {

      auto pevent = pbase->m_lparam.cast < ::user::control_event >();

      on_control_event(pevent);

   }


   bool interaction::layout_tooltip(bool bForceShow)
   {

      if (m_ptooltip.is_null())
      {

         return true;

      }

      if (m_ptooltip->is_window_visible() && !get_wnd()->is_active())
      {

         hide_tooltip();

         return false;

      }

      if (!bForceShow && !m_ptooltip->is_window_visible())
      {

         return true;

      }

      //::size sizeTooltip = get_tooltip()->m_size;

      //::rect rectThisWindow;

      //get_window_rect(rectThisWindow);

      //::rect rectWindow;

      //::rect rectMonitor;

      //Session.get_best_monitor(rectMonitor, rectThisWindow);

      //rectWindow = rectThisWindow;

      //rectWindow.SetBottomRightSize(sizeTooltip);

      //rectWindow.offset(0, -sizeTooltip.cy);

      //if (rectWindow.top < rectMonitor.top)
      //{

      //   rectWindow.move_top_to(rectThisWindow.bottom);

      //}

      //if (rectWindow.right > rectMonitor.right)
      //{

      //   rectWindow.move_left_to(rectMonitor.right - sizeTooltip.cx - rectThisWindow.height());

      //}

      //m_ptooltip->order(zorder_top_most);
      //m_ptooltip->place(rectWindow);
      //m_ptooltip->display(display_normal, activation_no_activate);
      ////m_ptooltip->show(show_no_activate);
      ////SWP_FRAMECHANGED | SWP_SHOWWINDOW | SWP_NOACTIVATE);

      return true;

   }


   bool interaction::hide_tooltip()
   {

      if (m_ptooltip.is_null())
      {

         return true;

      }

      m_ptooltip->display(display_none);

      return true;

   }


   bool interaction::frame_is_transparent()
   {

      return false;

   }


   double interaction::get_alpha()
   {

      if (m_palphasource == nullptr)
      {

         return 1.0;

      }
      else
      {

         return m_palphasource->get_alpha(this);

      }

   }


   bool interaction::has_pending_graphical_update()
   {

      if (has_prodevian())
      {

         return true;

      }

#ifdef APPLE_IOS

      {

         sync_lock sl(mutex());

         for (index i = 0; i < m_uiptraChild.get_size(); i++)
         {

            ::user::interaction * pinteraction = m_uiptraChild[i];

            if(pinteraction)
            {
            sl.unlock();


            if (pinteraction->has_pending_graphical_update())
            {

               return true;

            }

            sl.lock();

               }


         }

      }

#endif

      if(is_window_visible())
      {

         if (m_bRedrawOnVisible)
         {

            return true;

         }

      }

      if (m_pimpl->has_pending_graphical_update())
      {

         return true;

      }

      return false;

   }


   bool interaction::enable_transparent_mouse_events(bool bEnable)
   {

#ifdef WINDOWS

      ::user::interaction * puiTop = get_wnd();

      if (puiTop == nullptr)
      {

         return false;

      }

      sync_lock sl(puiTop->mutex());

      __pointer(::user::interaction_impl) pimpl = puiTop->m_pimpl;

      if (pimpl.is_null())
      {

         return false;

      }

      if (is_different(pimpl->m_bTransparentMouseEvents, bEnable))
      {

         pimpl->m_bTransparentMouseEvents = bEnable;

         check_transparent_mouse_events();

      }

#endif

      return true;

   }


   void interaction::check_transparent_mouse_events()
   {

#ifdef WINDOWS_DESKTOP

      auto pwnd = get_wnd();

      if (::is_null(pwnd))
      {

         return;

      }

      if (!pwnd->is_composite())
      {

         enable_transparent_mouse_events(false);

         return;

      }

      pwnd->post_message(message_simple_command, simple_command_check_transparent_mouse_events);

#endif

   }


   void interaction::redraw_add(::context_object * p)
   {

      get_wnd()->m_pimpl->redraw_add(p);

   }


   void interaction::redraw_remove(::context_object * p)
   {

      get_wnd()->m_pimpl->redraw_remove(p);

   }


   bool interaction::has_redraw()
   {

      return get_wnd()->m_pimpl->has_redraw();

   }


   void interaction::defer_notify_mouse_move(bool & bPointInside, point & pointLast)
   {

      if (Session.get_capture() != nullptr)
      {

         return;

      }

      ::point pointCurrent;

      Session.get_cursor_pos(pointCurrent);

      if (pointCurrent != pointLast)
      {

         pointLast = pointCurrent;

         bPointInside = _001IsPointInside(pointCurrent);

         if (bPointInside || m_bMouseHover)
         {

            auto pinteraction = get_wnd();

            //bool bMoving = pinteraction->window_is_moving();

            //bool bSizing = pinteraction->window_is_sizing();

            //bool bDocking = pinteraction->window_is_docking();

            //bool bVoidSending = bMoving || bSizing || bDocking;;

            //if (bVoidSending)
            //{

            //   output_debug_string("void sending :: defer_notify_mouse_move");

            //}
            //else
            {


               //#if !defined(LINUX)
               //
               //            get_wnd()->_001ScreenToClient(pointCurrent);
               //
               //#endif

               if (bPointInside)
               {

                  m_bMouseHover = true;

                  auto pmouse = __new(message::mouse);

                  pmouse->m_eflagMessage += ::message::flag_synthesized;

                  pmouse->m_id = WM_MOUSEMOVE;
                  pmouse->m_puserinteraction = pinteraction;
                  pmouse->m_point = pointCurrent;
                  pmouse->m_bTranslated = true;

                  pinteraction->message_handler(pmouse);

               }
               else
               {

                  m_bMouseHover = false;

                  get_impl()->mouse_hover_remove(this);

                  send_message(WM_MOUSELEAVE);

                  set_need_redraw();

               }

            }

         }

      }

   }


   void interaction::destruct()
   {

      // If this is a "top level" or "operating system" window,
      // the operating system may keep context_object to this object,
      // preventing it from being fully released.
      // If the window DestroyWindow member is called in interaction::~interaction destructor,
      // derived classes from interaction::~interaction may have deleted object resources
      // that could be used to correctly destroy window, as DestroyWindow generally require
      // that the object be a full valid object before being disposed.

      DestroyWindow();

      ::user::primitive::destruct();

   }


   void interaction::defer_notify_mouse_move()
   {

      if (get_wnd() == nullptr)
      {

         return;

      }

      if (Session.get_capture() != nullptr)
      {

         return;

      }

      ::point pointCurrent;

      Session.get_cursor_pos(pointCurrent);

#if !defined(LINUX)

      get_wnd()->_001ScreenToClient(pointCurrent);

#endif

      get_wnd()->send_message(WM_MOUSEMOVE, 0, pointCurrent);

   }


   double alpha_source::get_alpha(::user::interaction * puiTarget)
   {

      return 1.0;

   }


   void alpha_source::on_alpha_target_initial_frame_position()
   {


   }


   void interaction::on_after_graphical_update()
   {

      ::user::primitive::on_after_graphical_update();

      if(m_pimpl.is_set())
      {

         m_pimpl->on_after_graphical_update();

      }

   }


   void interaction::_001OnDeiconify(edisplay edisplay)
   {

      display(display_normal);

   }


   bool interaction::on_click(const ::user::item & item)
   {

      if (item == ::user::element_close_button
         || item == ::user::element_close_icon)
      {

         post_message(WM_CLOSE);

         return true;

      }

      return false;

   }


   bool interaction::on_right_click(const ::user::item & item)
   {

      return false;

   }


   ::sized interaction::get_size()
   {

      ::rect rectWindow;

      get_window_rect(rectWindow);

      return rectWindow.size();

   }


   ::sized interaction::get_client_size()
   {

      ::rect rectClient;

      get_client_rect(rectClient);

      return rectClient.size();

   }


   int interaction::width()
   {

      ::rect rectWindow;

      get_window_rect(rectWindow);

      return rectWindow.width();

   }


   int interaction::height()
   {

      ::rect rectWindow;

      get_window_rect(rectWindow);

      return rectWindow.height();

   }


   int interaction::client_width()
   {

      ::rect rectClient;

      get_client_rect(rectClient);

      return rectClient.width();

   }


   int interaction::client_height()
   {

      ::rect rectClient;

      get_client_rect(rectClient);

      return rectClient.height();

   }


   void interaction::resize_to_fit(::draw2d::graphics_pointer& pgraphics)
   {

      // this default implementation doesn't need to be called by derived
      // classes and it has the side effect of warning at debug output log
      // the default resize_to_fit implementation is being called.

      ::output_debug_string("default resize_to_fit doesn't do anything\n");


   }


   void interaction::wait_redraw()
   {

      while (has_pending_redraw_flags())
      {

         do_events();

         Sleep(5);

      }


   }


   bool interaction::has_pending_redraw_flags()
   {

      if (m_pimpl == nullptr)
      {

         return false;

      }

      return m_pimpl->has_pending_redraw_flags();

   }



   void interaction::set_stock_icon(e_stock_icon eicon)
   {

      __throw(interface_only_exception());

   }


   e_stock_icon interaction::get_stock_icon()
   {

      return stock_icon_none;

   }


   void interaction::set_bitmap_source(string strBitmapSource)
   {

      value("bitmap-source") = strBitmapSource;

   }

   void interaction::clear_bitmap_source()
   {

      value("bitmap-source").unset();

   }


   //::user::item interaction::hit_test(::message::mouse* pmouse->
   //{

   //   auto point = pmouse->m_point;

   //   screen_to_client(point);

   //   point += m_ptScroll;


   //}

   //::user::item interaction::on_hit_test(const ::point& point)
   //{

   //   auto rect = this->rect(::user::element_client);

   //   if (!rect.contains(point))
   //   {

   //      return ::user::element_none;

   //   }

   //   return ::user::element_client;

   //}


   bool interaction::scroll_bar_get_client_rect(RECT * prect)
   {

      get_client_rect(prect);

      prect->right += get_final_y_scroll_bar_width();

      prect->bottom += get_final_x_scroll_bar_width();

      return true;

   }


   void interaction::on_calc_size(calc_size * psize)
   {

      ::rect rectWindow;

      get_window_rect(rectWindow);

      psize->m_size = rectWindow.size();

   }


   //e_control_type interaction::get_control_type() const
   //{

   //   return m_pdescriptor->get_control_type();

   //}


   void interaction::show_software_keyboard(bool bShow, string str, strsize iBeg, strsize iEnd)
   {

      if (get_wnd() == this)
      {

         if (m_pimpl.is_null())
         {

            return;

         }

         m_pimpl->show_software_keyboard(bShow, str, iBeg, iEnd);

      }
      else
      {

         get_wnd()->show_software_keyboard(bShow, str, iBeg, iEnd);

      }

   }


   void interaction::post_task(::generic_object * pobjectTask)
   {

      if (::is_set(m_pthreadUserInteraction))
      {

         m_pthreadUserInteraction->post_task(pobjectTask);

      }

   }


#ifdef WINDOWS


   strsize interaction::_009GetWindowText(wchar_t * pwsz, int n)
   {

      wstring wstr(m_strWindowText);

      n = (int) MIN(wstr.get_length() + 1, n);

      wcsncpy(pwsz, wstr.c_str(), n);

      pwsz[n - 1] = '\0';

      return n - 1;

   }


   strsize interaction::_009GetWindowTextLength()
   {
      wstring wstr(m_strWindowText);

      return wstr.get_length();

   }


#else


   strsize interaction::_009GetWindowText(char * psz, int n)
   {

      strncpy(psz, m_strWindowText.c_str(), n);

      psz[n-1] = '\0';

      return n - 1;

   }


   strsize interaction::_009GetWindowTextLength()
   {

      return m_strWindowText.get_length();

   }


#endif


   void interaction::send_task(::generic_object * pobjectTask, ::duration durationTimeout)
   {

      ::thread * pthread = get_wnd() == nullptr ? (::thread *) nullptr : get_wnd()->m_pthreadUserInteraction;

      ::thread * pthreadCurrent = ::get_thread();

      if (pthread == nullptr || pthread == pthreadCurrent)
      {

         ::__call(pobjectTask);

      }
      else
      {

         pthread->send_task(pobjectTask, durationTimeout);

      }

   }


   CLASS_DECL_AURA ::mutex *  mutex_children()
   {

      return &::get_context_system()->m_mutexUserChildren;

   }


//void interaction::get_layout_rect(RECT * prect)

//{

//   get_window_rect(prect);


//}


   /*void interaction::set_placement(const ::rect & rect)

   {

      ::rect rectFinal(rect);


      rectFinal.deflate(m_rectPadding);

      SetPlacement(rectFinal);

   }*/


   void interaction::prodevian_redraw(bool bUpdateBuffer)
   {

      string strType = type_name();

      if (strType.contains_ci("combo_list"))
      {

         output_debug_string("prodevian_redraw combo_list");

      }

      if (m_pimpl.is_null())
      {

         return;

      }

      m_pimpl->prodevian_redraw(bUpdateBuffer);

   }



   void interaction::prodevian_stop()
   {

      m_pimpl->prodevian_stop();

   }

   byte brate(double dRate, double dMin, double dMax)
   {

      return (byte)(dRate * (dMax - dMin) + dMin);

   }


   //interaction::interaction() :
   //   ::object(get_object()),
   //   ::user::interaction(get_object())

   //{

   //   m_iIndex = -1;
   //   //m_eelementHover = ::user::element_none;

   //}


   //interaction::~interaction()
   //{
   //}


   //void interaction::install_message_routing(::channel* pchannel)
   //{

   //   ::user::interaction::install_message_routing(pchannel);

   //   IGUI_MSG_LINK(WM_SHOWWINDOW, pchannel, this, &::user::interaction::_001OnShowWindow);

   //}


   void interaction::install_simple_ui_default_mouse_handling(::channel* pchannel)
   {

      m_bSimpleUIDefaultMouseHandling = true;

      IGUI_MSG_LINK(WM_LBUTTONDOWN, pchannel, this, &interaction::_001OnLButtonDown);
      IGUI_MSG_LINK(WM_LBUTTONUP, pchannel, this, &interaction::_001OnLButtonUp);
      IGUI_MSG_LINK(WM_MBUTTONDOWN, pchannel, this, &interaction::_001OnMButtonDown);
      IGUI_MSG_LINK(WM_MBUTTONUP, pchannel, this, &interaction::_001OnMButtonUp);
      IGUI_MSG_LINK(WM_MOUSEMOVE, pchannel, this, &interaction::_001OnMouseMove);
      IGUI_MSG_LINK(WM_MOUSELEAVE, pchannel, this, &interaction::_001OnMouseLeave);

   }

   void interaction::install_update_data_message_routing(::channel * pchannel)
   {

      IGUI_MSG_LINK(::message_need_load_form_data, pchannel, this, &interaction::_001OnNeedLoadFormData);
      IGUI_MSG_LINK(::message_need_save_form_data, pchannel, this, &interaction::_001OnNeedSaveFormData);

   }



   bool interaction::simple_on_control_event(::message::message* pmessage, ::user::e_event eevent)
   {

      SCAST_PTR(::message::base, pbase, pmessage);

      if (eevent == event_mouse_leave)
      {

         __pointer(interaction) pinteraction = top_child();

         while (pinteraction != nullptr)
         {

            if (pinteraction->m_bCursorInside)
            {

               pinteraction->m_bCursorInside = false;

               pinteraction->message_handler(pbase);

            }

            pinteraction = pinteraction->under_sibling();

         }

      }

      ::user::control_event ev;

      ev.m_puie = this;

      ev.m_id = m_id;

      ev.m_eevent = eevent;

      ev.m_pmessage = pmessage;

      route_control_event(&ev);

      if (::is_set(pmessage))
      {

         pmessage->m_bRet = ev.m_bRet;

         if (pmessage->m_bRet)
         {

            if (pbase != nullptr)
            {

               pbase->m_lresult = 1;

            }

         }

      }

      return ev.m_bRet;

   }


   void interaction::_001OnLButtonDown(::message::message* pmessage)
   {

      SCAST_PTR(::message::mouse, pmouse, pmessage);

      if (!is_window_enabled())
      {

         return;

      }

      try
      {

         if (keyboard_focus_is_focusable())
         {

            Session.set_keyboard_focus(this);

         }
         else
         {
            
            Session.clear_focus();
          
         }

      }
      catch (...)
      {

      }

      if (m_bSimpleUIDefaultMouseHandling)
      {

         hit_test(m_itemLButtonDown, pmouse);

         if (m_itemLButtonDown)
         {

            Session.m_puiLastLButtonDown = this;

            pmouse->m_bRet = true;

         }
         else
         {

            if (pmessage->previous())
            {

               return;

            }

            Session.m_puiLastLButtonDown = this;

            simple_on_control_event(pmessage, ::user::event_button_down);

         }

      }

   }


   void interaction::_001OnLButtonUp(::message::message* pmessage)
   {

      SCAST_PTR(::message::mouse, pmouse, pmessage);

      if (!is_window_enabled())
      {

         return;

      }

      if (m_bSimpleUIDefaultMouseHandling)
      {

         auto item = hit_test(pmouse);

         bool bSameUserInteractionAsMouseDown = Session.m_puiLastLButtonDown == this;

         int iSizeOfItem = sizeof(ITEM);

         bool bSameItemAsMouseDown = m_itemLButtonDown == item;

         TRACE("interaction::_001OnLButtonUp item=%d, SameIntAsMsDwn=%d, SameItemAsMsDwn=%d", (int) item.m_iItem, (int) bSameUserInteractionAsMouseDown, (int) bSameItemAsMouseDown);

         if (m_itemLButtonDown && bSameUserInteractionAsMouseDown && bSameItemAsMouseDown)
         {

            Session.m_puiLastLButtonDown = nullptr;

            pmessage->m_bRet = on_click(item);

            TRACE("interaction::_001OnLButtonUp on_click_ret=%d", (int) pmessage->m_bRet);

            if (pmessage->m_bRet)
            {

               pmouse->m_lresult = 1;

            }
            else
            {

               ::user::control_event ev;

               ev.m_puie = this;

               ev.m_id = m_id;

               ev.m_eevent = ::user::event_button_clicked;

               ev.m_pmessage = pmouse;

               ev.m_item = item;

               ev.m_actioncontext.add(::source_user);

               route_control_event(&ev);

               TRACE("interaction::_001OnLButtonUp route_btn_clked=%d", (int) ev.m_bRet);

               pmessage->m_bRet = ev.m_bRet;

               if (!pmessage->m_bRet)
               {

                  ::user::command command;

                  command.m_id = m_id;

                  command.m_puiOther = this;

                  route_command_message(&command);

                  TRACE("interaction::_001OnLButtonUp route_cmd_msg=%d", (int) command.m_bRet);

                  pmessage->m_bRet = command.m_bRet;

               }

               if (pmessage->m_bRet)
               {

                  pmouse->m_lresult = 1;

               }

            }

         }
         else
         {

            if (pmessage->previous())
            {

               return;

            }

            Session.m_puiLastLButtonDown = nullptr;

            simple_on_control_event(pmessage, ::user::event_button_down);

         }

      }

   }


   void interaction::_001OnMButtonDown(::message::message* pmessage)
   {

      SCAST_PTR(::message::mouse, pmouse, pmessage);

      pmessage->previous();

      if (m_bSimpleUIDefaultMouseHandling)
      {

         auto item = hit_test(pmouse);

         if (item)
         {

            simple_on_control_event(pmessage, ::user::event_m_button_down);

         }

      }

   }


   void interaction::_001OnMButtonUp(::message::message* pmessage)
   {

      SCAST_PTR(::message::mouse, pmouse, pmessage);

      pmessage->previous();

      if (m_bSimpleUIDefaultMouseHandling)
      {

         auto item = hit_test(pmouse);

         if (item)
         {

            simple_on_control_event(pmessage, ::user::event_m_button_up);

         }

      }

   }


   void interaction::_001OnMouseMove(::message::message* pmessage)
   {

      SCAST_PTR(::message::mouse, pmouse, pmessage);

      if (!is_window_enabled())
      {

         return;

      }

      sync_lock sl(mutex());

      pmouse->m_ecursor = get_cursor();

      if (m_bSimpleUIDefaultMouseHandling)
      {

         update_hover(pmouse);

      }

   }


   void interaction::update_hover(::message::mouse* pmouse, bool bAvoidRedraw)
   {

      sync_lock sl(mutex());

      point pointCursor;

      if (::is_set(pmouse))
      {

         pointCursor = pmouse->m_point;

      }
      else
      {

         pointCursor = Session.get_cursor_pos();

      }

      auto itemHitTest = hit_test(pointCursor);

      bool bAnyHoverChange = false;

      if (itemHitTest != m_itemHover)
      {

         m_itemHover = itemHitTest;

         bAnyHoverChange = true;

      }

      if (::is_set(pmouse))
      {

         if (itemHitTest != m_itemHoverMouse)
         {

            auto itemOldMouseHover = m_itemHoverMouse;

            m_itemHoverMouse = itemHitTest;

            bAnyHoverChange = true;

            if (m_itemHoverMouse && !itemOldMouseHover)
            {

               track_mouse_hover();

               simple_on_control_event(pmouse, event_mouse_enter);

            }
            else if (!m_itemHoverMouse && itemOldMouseHover)
            {

               simple_on_control_event(pmouse, event_mouse_leave);

            }

            pmouse->m_bRet = true;

         }

      }

      if(bAnyHoverChange || !m_itemHover.is_drawn())
      {

         if (!bAvoidRedraw)
         {

            set_need_redraw();

            post_redraw();

         }

      }

   }


   void interaction::_001OnMouseLeave(::message::message * pmessage)
   {

      SCAST_PTR(::message::base, pbase, pmessage);

      sync_lock sl(mutex());

      auto itemOldHover = m_itemHover;

      m_itemHover = ::user::element_none;

      m_bTrackMouseLeave = false;

      if (itemOldHover)
      {

         set_need_redraw();

         simple_on_control_event(pmessage, event_mouse_leave);

      }

   }


   void interaction::hit_test(::user::item & item, const ::point & point)
   {

      item.m_pointScreen = point;

      item.m_pointClient = screen_to_client(item.m_pointScreen);

      item.m_pointHitTest = item.m_pointClient + m_pointScroll;

      on_hit_test(item);

   }


   void interaction::on_hit_test(::user::item & item)
   {

      sync_lock sl(mutex());

      for (auto & pitem : m_itema)
      {

         if (pitem->m_ppath)
         {

            //if (!item.m_pgraphics)
            //{

            //   item.m_pgraphics = create_memory_graphics();

            //}

            if (pitem->m_ppath->contains(item.m_pgraphics, item.m_pointHitTest))
            {

               ((ITEM &)item) = ((ITEM &)*pitem);

               return;

            }

         }
         else if (get_rect(*pitem))
         {

            if (pitem->m_rect.contains(item.m_pointHitTest))
            {

               ((ITEM&)item) = ((ITEM&)*pitem);

               return;

            }

         }

      }

      auto rect = this->rect(::user::element_client);

      if (!rect.contains(item.m_pointHitTest))
      {

         item = element_none;

      }
      else
      {

         item = element_client;

      }

   }


   bool interaction::get_rect(::user::item& item)
   {

      auto pitem = get_user_item(item);

      if (pitem)
      {

         item.m_rect = pitem->m_rect;

         return true;

      }
     
      if (!item)
      {

         return false;

      }

      get_client_rect(item.m_rect);

      return true;

   }


   bool interaction::on_action(const char* pszId)
   {

      auto pinteractionParent = GetParent();

      if (::is_set(pinteractionParent))
      {

         if (pinteractionParent->on_action(pszId))
         {

            return true;

         }

      }

      return false;

   }



   bool interaction::keyboard_focus_is_focusable()
   {

      return false;

   }


   //   ::user::style * interaction::get_user_style()
   //   {
   //
   //      if (pstyle != nullptr)
   //         return pstyle;
   //
   //      if (GetTypedParent < ::user::interaction >() == nullptr)
   //         return nullptr;
   //
   //      return GetTypedParent < ::user::interaction >()->get_style();
   //
   //   }


   void interaction::simple_ui_draw_back_01_old(::rect rect, ::draw2d::graphics_pointer & pgraphics)
   {

      pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

      COLORREF crOut;

      COLORREF crIn;

      /*   if (eschema == ::hotplugin::plugin::schema_darker)
         {

         crOut = ARGB(0, 90, 90, 80);

         crIn = ARGB(133, 90, 90, 80);

         }
         else*/
      {

         crOut = ARGB(0, 255, 255, 233);

         crIn = ARGB(133, 255, 255, 233);

      }

      i32 iBorderH = MIN(rect.height() / 2, 49);

      ::draw2d::brush_pointer br(e_create);

      br->CreateLinearGradientBrush(rect.top_left(), point(rect.left, rect.top + iBorderH), crOut, crIn);

      pgraphics->fill_rect(::rect(rect.left, rect.top, (i32)rect.width(), iBorderH), br);

      br->create_solid(crIn);

      pgraphics->fill_rect(::rect(rect.left, rect.top + iBorderH, (i32)rect.width(), (i32)rect.height() - (iBorderH * 2)), br);

      br->CreateLinearGradientBrush(point(rect.left, rect.bottom - iBorderH), rect.bottom_left(), crIn, crOut);

      pgraphics->fill_rect(::rect(rect.left, rect.bottom - iBorderH, (i32)rect.width(), iBorderH), br);

   }


   void interaction::simple_ui_draw_back_01_new(::rect rect, ::draw2d::graphics_pointer & pgraphics)
   {

      /*simple_solid_brush br(g, ARGB(255, 255, 255, 255));

      simple_pen pen;

      pen.create_solid(ARGB(255, 0, 0, 0));

      pgraphics->select(br);

      pgraphics->select(pen);

      m_rect.deflate(0, 0, 1, 1);

      pgraphics->rectangle(m_rect);*/

      //pgraphics->set_alpha_mode(::draw2d::alpha_mode_set);

      //pgraphics->fill_rect(rect,ARGB(0,0,0,0));

   }


   void interaction::_001OnNcDraw(::draw2d::graphics_pointer & pgraphics)
   {

      if (m_flagNonClient.has(non_client_background))
      {

         draw_control_background(pgraphics);

      }

      if (m_flagNonClient.has(non_client_focus_rect) && keyboard_focus_is_focusable())
      {

         simple_ui_draw_focus_rect(pgraphics);

      }

   }


   void interaction::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      //::user::interaction::_001OnDraw(pgraphics);
      if (m_itema.has_element())
      {

         _001DrawItems(pgraphics);

      }

   }


   __pointer(::user::item) interaction::add_user_item(const ::user::item & item)
   {

      __pointer(::user::item) pitem = __new(::user::item(item));

      m_itema.add(pitem);

      return pitem;

   }

   void interaction::_001DrawItems(::draw2d::graphics_pointer& pgraphics)
   {

      for (auto& pitem : m_itema)
      {

         _001DrawItem(pgraphics, pitem);

      }

   }


   void interaction::_001DrawItem(::draw2d::graphics_pointer& pgraphics, ::user::item * pitem)
   {

      if (::is_null(pitem))
      {

         return;

      }

      if (pitem->m_eelement == ::user::element_close_button)
      {

         pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

         ::draw2d::pen_pointer ppen(e_create);

         ::draw2d::brush_pointer pbrush(e_create);

         auto pstyle = get_style(pgraphics);

         ::rectd rectd(pitem->m_rect);

         auto color = get_color(pstyle, ::user::element_background);

         ppen->create_solid(rectd.minimum_dimension() / 10.0, color);

         pbrush->create_solid(color);

         pgraphics->set(pbrush);

         if (m_itemHover == ::user::element_close_button)
         {

            color.m_iA = 180;

         }
         else
         {

            color.m_iA = 127;

         }

         pgraphics->set_smooth_mode(::draw2d::smooth_mode_none);

         pgraphics->fill_rect(rectd, color);

         if (color.get_hls().m_dL <= 0.5)
         {

            // If color is dark (dark mode?)
            // blend lighter pixel at top-right edge
            // so that the button looks more sharply square-edged

            auto colorLighter = color;

            colorLighter.hls_rate(0.0, 0.312569, 0.0);

            colorLighter.m_iA = 127;

            pgraphics->blend_pixel(pitem->m_rect.top_right() - ::size(1, 0), colorLighter);

         }

         rectd.deflate(rectd.minimum_dimension() / 5.0);

         pgraphics->set(ppen);

         pgraphics->set_smooth_mode(::draw2d::smooth_mode_high);

         pgraphics->draw_stock_icon(rectd, stock_icon_close);

      }
      else if (pitem->m_eelement == ::user::element_close_icon)
      {

         pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

         ::draw2d::brush_pointer pbrush(e_create);

         auto pstyle = get_style(pgraphics);

         if (!pitem->m_ppath)
         {

            ::rectd rect(pitem->m_rect);

            double dMinimumDimension = rect.minimum_dimension();

            double dDeflate = dMinimumDimension / 3.0;

            double w = rect.width();

            double h = rect.height();

            rect.deflate(0, dDeflate);

            double w2 = rect.width();

            double h2 = rect.height();

            pitem->m_ppath.create();

            pitem->m_ppath->add_rect(rect, 45_degrees);

            pitem->m_ppath->add_rect(rect, -45_degrees);

         }

         auto color = get_color(pstyle, ::user::element_background);

         if (m_itemHover == ::user::element_close_icon)
         {

            color.m_iA = 180;

         }
         else
         {

            color.m_iA = 127;

         }

         pbrush->create_solid(color);

         pgraphics->set(pbrush);

         pgraphics->fill_path(pitem->m_ppath);

      }

   }


   bool interaction::has_text_input()
   {

      return false;

   }


   //COLORREF interaction::get_action_hover_border_color()
   //{

   //   return _001GetColor(::user::color_action_hover_border_color);

   //}


   void interaction::edit_on_set_focus(::user::interaction* pinteraction)
   {

      if (::is_null(m_pimpl))
      {

         return;

      }

      m_pimpl->edit_on_set_focus(pinteraction);

   }


   void interaction::edit_on_kill_focus(::user::interaction* pinteraction)
   {

      if (::is_null(m_pimpl))
      {

         return;

      }

      m_pimpl->edit_on_kill_focus(pinteraction);

   }


   void interaction::simple_ui_draw_focus_rect(::draw2d::graphics_pointer & pgraphics)
   {

      auto pstyle = get_style(pgraphics);

      pstyle->simple_ui_draw_focus_rect(this, pgraphics);

   }


   void interaction::simple_ui_draw_frame_window_rect(::draw2d::graphics_pointer & pgraphics)
   {

      ::rect rectClient;

      get_client_rect(rectClient);

      rectClient.deflate(0, 0, 1, 1);

      ::draw2d::brush_pointer b(e_create);

      b->create_solid(ARGB(255, 255, 255, 255));

      pgraphics->set(b);

      ::draw2d::pen_pointer point(e_create);

      point->create_solid(1.0, ARGB(255, 0, 0, 0));

      pgraphics->set(point);

      pgraphics->rectangle(rectClient);

   }


   void interaction::simple_ui_draw_fuzzy_color_spread(::draw2d::graphics_pointer & pgraphics)
   {
      /*
      ::rect rectWindow;

      get_window_rect(rectWindow);

      int i = 0;
      int j = 0;
      int iCount = rectWindow.width();
      int jCount = rectWindow.height();

      BYTE * point = (BYTE *)m_pimage->get_data();

      for (i = 0; i < iCount; i++)
      {
      for (j = 0; j < jCount; j++)
      {
      double dPhase = fmod((((double) ::get_tick() * 360 * 0.5984 / 1000.0) + (i * 360.0 / (double)iCount) + (j * 360.0 / (double)jCount) + ((double)(sin(((double) ::get_tick() * 3.1415 * 2.0  *0.0484 / 1000.0) + i * 3.1415 * 2.0 * 2.0 / (double)(iCount)) * sin(((double) ::get_tick() * 3.1415 * 2.0  * 0.0484 / 1000.0) + j * 3.1415 * 2.0 * 2.0 / (double)(jCount)) * 360))), 360.0);
      i32 iR;
      i32 iG;
      i32 iB;
      double dRate = fmod(dPhase, 60.0) / 60.0;
      i32 iColor = (i32)(dRate * 155.0);
      if (dPhase < 60)
      {
      // purple to blue
      iR = 255 - iColor;
      iG = 100;
      iB = 255;
      }
      else if (dPhase < (120))
      {
      // blue to cyan
      iR = 100;
      iG = 100 + iColor;
      iB = 255;
      }
      else if (dPhase < (180))
      {
      // cyan to green
      iR = 100;
      iG = 255;
      iB = 255 - iColor;
      }
      else if (dPhase < (240))
      {
      // green to yellow
      iR = 100 + iColor;
      iG = 255;
      iB = 100;
      }
      else if (dPhase < (300))
      {
      // yellow to red
      iR = 255;
      iG = 255 - iColor;
      iB = 100;
      }
      else
      {
      // red to purple
      iR = 255;
      iG = 100;
      iB = 100 + iColor;
      }

      point[0] = iR;
      point[1] = iG;
      point[2] = iB;
      point[3] = 84;
      point += 4;

      }
      }
      */


   }


   void interaction::simple_ui_draw_dark_glass(::draw2d::graphics_pointer & pgraphics)
   {

      ::rect rectWindow;

      get_client_rect(rectWindow);

      pgraphics->fill_rect(rectWindow, ARGB(90, 127, 127, 127));

   }



   void interaction::simple_ui_draw_pestana(::draw2d::graphics_pointer & pgraphics)
   {

      ::rect rectWindow;

      get_client_rect(rectWindow);

      pgraphics->set_alpha_mode(draw2d::alpha_mode_blend);

      int iCount = rectWindow.height();
      ::draw2d::pen_pointer point(e_create);
      for (int i = 0; i < iCount; i += 2)
      {
         double dRate = (double)i / (double)iCount;
         dRate = 1.0 - dRate;
         byte a1 = brate(1.0 - dRate, 23, 90);
         byte r1 = brate(dRate, 23, 127);
         byte g1 = brate(dRate, 23, 127);
         byte b1 = brate(dRate, 23, 127);
         point->create_solid(1.0, ARGB(a1, r1, g1, b1));
         pgraphics->set(point);
         pgraphics->draw_line(rectWindow.left, i, rectWindow.right, i);

      }


   }



   void interaction::simple_ui_draw_auth_box(::draw2d::graphics_pointer & pgraphics)
   {

      ::rect rect;

      get_client_rect(rect);

      pgraphics->set_alpha_mode(draw2d::alpha_mode_blend);

      // front
      point pa[4];
      //  0       1
      //
      //
      //  3       2

      // back
      point pb[4];


      // guards
      point pc[4];


      pa[0].x = rect.left;
      pa[0].y = rect.top;
      pa[1].x = rect.right - rect.width() / 10;
      pa[1].y = rect.top + rect.height() / 10;
      pa[2].x = rect.right - rect.width() / 8;
      pa[2].y = rect.bottom - rect.height() / 10;
      pa[3].x = rect.left;
      pa[3].y = rect.bottom;


      pb[0].x = rect.left + rect.width() / 6;
      pb[0].y = rect.top + rect.height() / 6;
      pb[1].x = rect.right - rect.width() / 6;
      pb[1].y = rect.top + rect.height() / 6;
      pb[2].x = rect.right - rect.width() / 5;
      pb[2].y = rect.bottom - rect.height() / 4;
      pb[3].x = rect.left + rect.width() / 5;
      pb[3].y = rect.bottom - rect.height() / 4;

      {

         ::draw2d::brush_pointer b(e_create);

         b->create_solid(ARGB(192, 220, 220, 220));

         pgraphics->set(b);

         pgraphics->fill_polygon(pb, 4);

         ::draw2d::pen_pointer point(e_create);

         point->create_solid(1.0, ARGB(192, 192, 192, 192));

         pgraphics->set(point);

         pgraphics->draw_polygon(pb, 4);


      }













      // top
      ::memcpy_dup(pc, pa, sizeof(pb));
      pc[2].x = pb[1].x;
      pc[2].y = pb[1].y;
      pc[3].x = pb[0].x;
      pc[3].y = pb[0].y;

      {

         ::draw2d::brush_pointer b(e_create);

         b->create_solid(ARGB(180, 210, 210, 210));

         pgraphics->set(b);

         pgraphics->fill_polygon(pc, 4);

         ::draw2d::pen_pointer point(e_create);

         point->create_solid(1.0, ARGB(180, 180, 177, 177));

         pgraphics->set(point);

         pgraphics->draw_polygon(pc, 4);


      }
      // left
      ::memcpy_dup(pc, pa, sizeof(pb));
      pc[1].x = pb[0].x;
      pc[1].y = pb[0].y;
      pc[2].x = pb[3].x;
      pc[2].y = pb[3].y;
      {

         ::draw2d::brush_pointer b(e_create);

         b->create_solid(ARGB(123, 120, 120, 123));

         pgraphics->set(b);

         pgraphics->fill_polygon(pc, 4);

         ::draw2d::pen_pointer point(e_create);

         point->create_solid(1.0, ARGB(123, 90, 90, 90));

         pgraphics->set(point);

         pgraphics->draw_polygon(pc, 4);


      }
      // bottom
      ::memcpy_dup(pc, pa, sizeof(pb));
      pc[0].x = pb[3].x;
      pc[0].y = pb[3].y;
      pc[1].x = pb[2].x;
      pc[1].y = pb[2].y;
      {

         ::draw2d::brush_pointer b(e_create);

         b->create_solid(ARGB(149, 192, 192, 192));

         pgraphics->set(b);

         pgraphics->fill_polygon(pc, 4);

         ::draw2d::pen_pointer point(e_create);

         point->create_solid(1.0, ARGB(149, 176, 176, 176));

         pgraphics->set(point);

         pgraphics->draw_polygon(pc, 4);


      }
      // right
      ::memcpy_dup(pc, pa, sizeof(pb));
      pc[0].x = pb[1].x;
      pc[0].y = pb[1].y;
      pc[3].x = pb[2].x;
      pc[3].y = pb[2].y;
      {

         ::draw2d::brush_pointer b(e_create);

         b->create_solid(ARGB(90, 150, 149, 149));

         pgraphics->set(b);

         pgraphics->fill_polygon(pc, 4);

         ::draw2d::pen_pointer point(e_create);

         point->create_solid(1.0, ARGB(90, 120, 120, 123));

         pgraphics->set(point);

         pgraphics->draw_polygon(pc, 4);


      }





      {

         ::draw2d::pen_pointer point(e_create);

         point->create_solid(1.0, ARGB(190, 90, 90, 90));

         pgraphics->set(point);

         pgraphics->draw_polygon(pa, 4);

      }


   }


   //void interaction::on_hit_test(::user::item & item)
   //{

   //   auto rectClient = get_client_rect();

   //   if (!rectClient.contains(point))
   //   {

   //      return ::user::element_none;

   //   }

   //   return ::user::element_client;

   //}


   void interaction::get_text_composition_area(::rect & rect)
   {


   }


   void interaction::edit_on_text(string str)
   {

      _001SetText(str, source_user);

   }


   void interaction::edit_on_sel(strsize iBeg, strsize iEnd)
   {

      _001SetSel(iBeg, iEnd);

   }


   void interaction::on_text_composition(string str)
   {


   }


   void interaction::on_text_composition_done()
   {


   }


   bool interaction::edit_undo()
   {

      return false;

   }


   void interaction::update(::update * pupdate)
   {

      if (pupdate->m_id == REDRAW_ID || pupdate->m_id == m_id)
      {

         set_need_redraw();

         post_redraw();

      }

   }


   bool interaction::setWMClass(const char * psz)
   {

      if(!m_pimpl)
      {

         return false;

      }

      return m_pimpl->setWMClass(psz);

   }


   double interaction::_001GetTopLeftWeightedOccludedOpaqueRate()
   {

      if (!m_pimpl)
      {

         return ::user::primitive::_001GetTopLeftWeightedOccludedOpaqueRate();

      }

      return m_pimpl->_001GetTopLeftWeightedOccludedOpaqueRate();

   }


   bool interaction::_001InitialFramePosition()
   {

      ::rect rectWindow;

      if (!_001InitialFramePosition(rectWindow, { 0.05, 0.05, 0.4, 0.4 }))
      {

         return false;

      }

      display(display_normal);

      place(rectWindow);

      set_need_layout();

      set_need_redraw();

      post_redraw();

      return true;

   }


   bool interaction::_001InitialFramePosition(LPRECT lprect, const rectd & rectOptionalRateOrSize)
   {

      ::rectd rectRate(rectOptionalRateOrSize);

      ::rect rectMainMonitor;

      System.get_main_monitor(rectMainMonitor);

      ::rect rectWindow;

#if MOBILE_PLATFORM

      // rectOptionalRateOrSize is disregarded on mobile platform

      rectWindow = rectMainMonitor;

#else

      if(rectRate.is_empty())
      {

         rectRate.set_dim(100, 100, 800, 400);

      }
      else if(abs(rectRate.left) < 10.0
      && abs(rectRate.right) < 10.0
      && abs(rectRate.bottom) < 10.0
      && abs(rectRate.top) < 10.0)
      {

         rectRate *= rectd(rectMainMonitor.width(), rectMainMonitor.height(), rectMainMonitor.width(), rectMainMonitor.height());

      }

      __copy(rectWindow, rectRate);

      rectWindow += rectMainMonitor.top_left();

#endif

      *lprect = rectWindow;

      return true;

   }


   void interaction::on_finalize()
   {

      DestroyWindow();

   }


// please refer to object::set_finish verses/documentation
// ::user::interaction implements custom/dedicated set_finish protocol/feature/function
// this is why default set_finish isn't/(and shouldn't be) called here 
// (like is done for a regular object instance of *object* class)
// (look at ::object::delete_this implementation to confirm/study the default set_finish call)
   void interaction::delete_this()
   {

      context_object::delete_this();

   }




   // updown
   bool interaction::wfi_is_up()
   {

      return m_eupdown == updown_up;

   }


   bool interaction::wfi_is_down()
   {

      return m_eupdown == updown_down;

   }


   bool interaction::wfi_is_up_down()
   {

      return m_ewindowflag & window_flag_updown;

   }
   // updown end


   //interaction::control()
   //{

      //m_puiLabel = nullptr;
      //m_pdrawcontext = nullptr;
      //m_pdescriptor = nullptr;
      //m_bControlExCommandEnabled = true;
      //m_pform = nullptr;
      //m_bDefaultWalkPreTranslateParentTree = true;
      //m_bIdBound = false;

   //}


   //interaction::~control()
   //{

   //}


   //void interaction::install_message_routing(::channel* pchannel)
   //{

   //   //      ::user::impact::install_message_routing(pchannel);
   //   ::user::box::install_message_routing(pchannel);

   //   IGUI_MSG_LINK(WM_CREATE, pchannel, this, &::user::interaction::_001OnCreate);
   //   //      IGUI_MSG_LINK(WM_MOUSEMOVE, pchannel, this, &::user::interaction::_001OnMouseMove);
   //   //
   //   //#ifdef WINDOWS
   //   //
   //   //      IGUI_MSG_LINK(WM_MOUSELEAVE, pchannel, this, &::user::interaction::_001OnMouseLeave);
   //   //
   //   //#else
   //   //
   //   //      //::exception::throw_not_implemented();
   //   //
   //   //#endif
   //   //
   //   IGUI_MSG_LINK(WM_KEYDOWN, pchannel, this, &::user::interaction::_001OnKeyDown);

   //   IGUI_MSG_LINK(WM_ENABLE, pchannel, this, &::user::interaction::_001OnEnable);
   //   IGUI_MSG_LINK(WM_SETFOCUS, pchannel, this, &::user::interaction::_001OnSetFocus);
   //   IGUI_MSG_LINK(WM_KILLFOCUS, pchannel, this, &::user::interaction::_001OnKillFocus);




   //}


   //void interaction::_001OnCreate(::message::message* pmessage)
   //{

   //   SCAST_PTR(::message::create, pcreate, pmessage);

   //   pcreate->previous();

   //   ::user::control_event ev;

   //   ev.m_puie = this;

   //   ev.m_eevent = ::user::event_create;

   //   on_control_event(&ev);

   //}


   //bool interaction::has_action_hover()
   //{

   //   return m_eelementHover;

   //}


   void interaction::_003OnCustomDraw(::draw2d::graphics_pointer& pgraphics, ::aura::draw_context* pdrawcontext)
   {

      pgraphics->chain(pdrawcontext);

      _000OnDraw1(pgraphics);

      pgraphics->unchain(pdrawcontext);

   }


   bool interaction::_003IsCustomMessage()
   {

      return m_bCustomWindowProc;

   }


   void interaction::_003CallCustomDraw(::draw2d::graphics_pointer& pgraphics, ::aura::draw_context* pdrawcontext)
   {

      _003OnCustomDraw(pgraphics, pdrawcontext);

   }


   bool interaction::_003CallCustomWindowProc(__pointer(::user::interaction) pwnd, UINT message, WPARAM wparam, LPARAM lparam, LRESULT& lresult)

   {

      m_pwndCustomWindowProc = pwnd;

      __keep(m_bCustomWindowProc);

      ::message::base base(pwnd, message, wparam, lparam);

      _003CustomWindowProc(&base);

      return base.m_bRet;

   }


   void interaction::_003CustomWindowProc(::message::message* pmessage)
   {

      UNREFERENCED_PARAMETER(pmessage);

   }


   //bool interaction::operator == (const class control_descriptor& control_descriptor) const
   //{

   //   return *m_pdescriptor == control_descriptor;

   //}


   //bool interaction::operator == (const class control& control) const
   //{

   //   return operator == (*control.m_pdescriptor);

   //}



   index interaction::GetEditItem()
   {

      return m_iEditItem;

   }


   index interaction::GetEditSubItem()
   {

      return (::index) control_descriptor().m_iSubItem;

   }


   void interaction::SetEditItem(index iItem)
   {

      m_iEditItem = iItem;

   }


   void interaction::SetEditSubItem(index iSubItem)
   {

      descriptor().m_iSubItem = iSubItem;

   }


   bool interaction::get_data(__pointer(::user::interaction)pwnd, var& var)
   {

      string str;

      if (control_descriptor().get_control_type() == control_type_edit)
      {

         __pointer(::user::text) pedit = pwnd.m_p;

         if (pedit == nullptr)
            return false;

         pedit->_001GetText(str);

      }
      else
      {

         __pointer(::user::text) ptext = this;

         if (!ptext)
         {

            return false;

         }

         ptext->_001GetText(str);

      }

      switch (control_descriptor().get_data_type())
      {
      case control_data_type_string:
      {
         var = str;
      }
      return true;
      case control_data_type_natural:
      {
         var = atoi(str);
         return true;
      }
      break;
      default:
         return false;
      }

   }



   bool interaction::Validate(string& strParam)
   {

      switch (control_descriptor().get_data_type())
      {
      case control_data_type_string:
         return true;
      case control_data_type_natural:
      {
         string str = strParam;
         str.trim_left();
         str.trim_right();
         for (i32 i = 0; i < str.get_length(); i++)
         {
            if (str[i] >= L'0'
               && str[i] <= L'9')
            {
            }
            else
            {
               return false;
            }

         }
         return true;
      }
      break;
      default:
         return true;
      }
   }



   //bool interaction::_001IsPointInside(::point point)
   //{

   //   return ::user::interaction::_001IsPointInside(point);

   //}




   bool interaction::has_function(e_control_function econtrolfunction) const
   {

      if (m_pdescriptor.is_null())
      {

         return false;

      }

      return m_pdescriptor->has_function(econtrolfunction);

   }


   e_control_type interaction::get_control_type() const
   {

      if (m_pdescriptor.is_null())
      {

         return control_type_none;

      }

      return m_pdescriptor->get_control_type();

   }


   bool interaction::create_control(class control_descriptor* pdescriptor)
   {

      m_pdescriptor = pdescriptor;

      try
      {

         if (!create_window(pdescriptor->m_puserinteractionParent, pdescriptor->m_id))
         {

            m_pdescriptor.release();

            return false;

         }

      }
      catch (...)
      {

         m_pdescriptor.release();

         return false;

      }

      m_pdescriptor->m_pinteraction = this;

      m_pdescriptor->m_bCreated = true;

      m_pdescriptor->m_controlmap[m_pdescriptor->m_iItem] = this;

      return true;

   }


   estate interaction::get_state() const
   {
      if (m_pdrawcontext != nullptr)
      {

         estate estate = e_state_none;

         if (!is_window_enabled())
         {

            estate |= e_state_disabled;

         }

         if (Session.get_focus_ui() == this)
         {

            estate |= e_state_focused;

         }


         if (m_pdrawcontext->is_control_hover())
         {

            estate |= e_state_hover;

         }

         if (m_pdrawcontext->is_control_selected())
         {

            estate |= e_state_selected;


         }

         return estate;

      }
      else
      {

         estate estate = ::user::e_state_none;

         if (!is_window_enabled())
         {

            estate |= e_state_disabled;

         }

         if (m_itemHover)
         {

            estate |= e_state_hover;

         }

         if (Session.get_focus_ui() == this)
         {

            estate |= e_state_focused;

         }

         return estate;

      }

      return ::user::interaction::get_state();

   }






   //bool interaction::get_window_rect(RECT * prect)

   //{

   //   if (m_pdrawcontext != nullptr)
   //   {

   //      *prect = m_pdrawcontext->m_rectWindow;


   //      return true;

   //   }

   //   return ::user::box::get_window_rect(prect);


   //}



   //bool interaction::get_client_rect(RECT * prect)

   //{

   //   if (m_pdrawcontext != nullptr)
   //   {

   //      *prect = m_pdrawcontext->m_rectClient;


   //      ::offset_rect(prect, -m_pdrawcontext->m_rectClient.top_left());


   //      return true;

   //   }


   //   return ::user::box::get_client_rect(prect);


   //}





   bool interaction::IsControlCommandEnabled()
   {
      return m_bControlExCommandEnabled;
   }


   void interaction::EnableControlCommand(bool bEnable)
   {

      m_bControlExCommandEnabled = bEnable;

      set_need_redraw();

   }


   //void interaction::_001OnSetFocus(::message::message* pmessage)
   //{

   //   //if (!::user::box::keyboard_focus_OnSetFocus())
   //   //{

   //   //   return false;

   //   //}

   //   ::user::control_event ev;

   //   ev.m_puie = this;

   //   ev.m_eevent = ::user::event_set_focus;

   //   on_control_event(&ev);

   //   pmessage->m_bRet = ev.m_bRet;

   //}


   //void interaction::_001OnKillFocus(::message::message* pmessage)
   //{

   //   SCAST_PTR(::message::kill_focus, pkillfocus, pmessage);

   //   ::user::control_event ev;

   //   ev.m_puie = this;

   //   ev.m_id = m_id;

   //   ev.m_eevent = ::user::event_kill_focus;

   //   on_control_event(&ev);

   //   pkillfocus->m_bRet = ev.m_bRet;

   //}


   void control_cmd_ui::Enable(bool bOn)
   {

      m_bEnableChanged = TRUE;

      __pointer(::user::interaction) pwnd = m_puiOther;

      ASSERT(pwnd != nullptr);

      ASSERT_KINDOF(::user::interaction, pwnd);

      __pointer(::user::interaction) pinteraction = pwnd->get_child_by_id(m_idControl);

      //__pointer(control) pcontrolex = (pinteraction.m_p);

      if (pinteraction)
      {

         if (bOn)
         {

            if (pwnd->is_window_enabled() && !pinteraction->IsControlCommandEnabled())
            {

               pinteraction->EnableControlCommand(true);

            }

         }
         else
         {

            if (pinteraction->IsControlCommandEnabled())
            {

               pinteraction->EnableControlCommand(false);

            }

         }

      }
      else
      {

         if (pinteraction != nullptr)
         {

            if (bOn)
            {

               if (!pinteraction->is_window_enabled())
               {

                  pinteraction->enable_window();

               }

            }
            else
            {

               if (pinteraction->is_window_enabled())
               {

                  pinteraction->enable_window(FALSE);

               }

            }

         }

      }

   }


   void control_cmd_ui::SetCheck(i32 nCheck)
   {
      ASSERT(nCheck >= 0 && nCheck <= 2); // 0=>off, 1=>on, 2=>indeterminate
      /*__pointer(::user::interaction) pwnd = (__pointer(::user::interaction))m_pOther;
      ASSERT(pToolBar != nullptr);
      ASSERT_KINDOF(simple_toolbar, pToolBar);
      ASSERT(m_nIndex < m_nIndexMax);

      UINT nNewStyle = pToolBar->GetButtonStyle(m_nIndex) &
                  ~(TBBS_CHECKED | TBBS_INDETERMINATE);
      if (nCheck == 1)
          nNewStyle |= TBBS_CHECKED;
      else if (nCheck == 2)
          nNewStyle |= TBBS_INDETERMINATE;
      ASSERT(!(nNewStyle & TBBS_SEPARATOR));
      pToolBar->SetButtonStyle(m_nIndex, nNewStyle | TBBS_CHECKBOX);*/
   }

   void control_cmd_ui::SetText(const char*)
   {
      // ignore it
   }


   id control_cmd_ui::GetControlCommand(id id)
   {
      ::id idCommand;
      if (m_mapControlCommand.lookup(id, idCommand))
      {
         return id;
      }
      return id;
   }


   //   LRESULT control_view_impl::BaseControlExOnIdleUpdateCmdUI(WPARAM wParam, LPARAM)
   //   {
   //      __pointer(::user::interaction) pview = get_window();
   //
   //      // handle delay hide/show
   //      bool bVis = (pview->GetStyle() & WS_VISIBLE) != 0;
   //
   //      // the style must be visible
   //      if (bVis)
   //      {
   //         __pointer(::user::frame_window) pTarget = pview->GetOwner();
   //         if (pTarget == nullptr)
   //            pTarget = pview->GetParentFrame();
   //         if (pTarget != nullptr)
   //            BaseControlExOnUpdateCmdUI(pTarget, wParam != FALSE);
   //      }
   //
   //      return 0L;
   //
   //   }
   //
   //
   //   void control_view_impl::BaseControlExOnUpdateCmdUI(__pointer(::user::frame_window) pTarget, bool bDisableIfNoHndler)
   //   {
   //
   //      __pointer(::user::interaction) pview = get_window();
   //
   //      ::user::command & state = m_commandui;
   //
   //      state.m_puiOther = pview;
   //
   //      __pointer(::user::interaction) pwndIterator = pview->GetTopWindow();
   //
   //      __pointer(::user::interaction) pwnd;
   //
   //      __pointer(control) pcontrolex;
   //
   //      for (; pwndIterator != nullptr; pwndIterator = pwndIterator->get_next_window())
   //      {
   //
   //         pwnd = pwndIterator->GetTopLevel();
   //
   //         pcontrolex = nullptr;
   //
   //         if (pwnd != nullptr)
   //         {
   //            //#ifdef WINDOWS_DESKTOP
   //            //            pwnd->send_message(interaction::g_uiMessage, interaction::MessageParamGetBaseControlExPtr, (LPARAM) &pcontrolex);
   //            //#else
   //            __throw(todo(pwnd->get_context_application()));
   //            //#endif
   //         }
   //         if (pcontrolex != nullptr)
   //         {
   //
   //            id idControl = pwnd->GetDlgCtrlId();
   //
   //            // xxx         state.m_nIndex = uiID;
   //            state.m_iCount = -1;
   //            state.m_id = m_commandui.GetControlCommand(idControl);
   //            state.m_bContinueRouting = FALSE;
   //
   //            // ignore separators
   //            if ((pwnd->GetStyle() & WS_VISIBLE))
   //            {
   //               // allow reflections
   //               if (pview->on_command_probe(&state))
   //               {
   //                  continue;
   //               }
   //
   //               // allow the toolbar itself to have update handlers
   //               if (pview->on_command_probe(&state))
   //                  //               {
   //                    //                state.DoUpdate(pTarget, bDisableIfNoHndler);
   //                  continue;
   //               //           }
   //
   //                          // allow the owner to process the update
   //               state.DoUpdate(pTarget, bDisableIfNoHndler);
   //            }
   //         }
   //      }
   //
   //      // update the dialog controls added to the toolbar
   //  //  UpdateDialogControls(pTarget, bDisableIfNoHndler);
   //   }
   //
   //
   //   __pointer(::user::interaction) control_view_impl::get_window()
   //   {
   //      return  (this);
   //   }
   //
   //
   //   bool control_view_impl::BaseControlExOnCommand(WPARAM wParam, LPARAM lParam)
   //   {
   //
   //      UNREFERENCED_PARAMETER(lParam);
   //
   //      if (get_window() != nullptr)
   //      {
   //
   //#ifdef WINDOWS
   //
   //         UINT uiMessage = ((wParam >> 16) & 0xffff);
   //
   //
   //         if (uiMessage == BN_CLICKED)
   //         {
   //            //xxx id idCommand = m_commandui.GetControlCommand(wParam & 0xffff);
   //            //::user::command command(idCommand);
   //            //xxx get_window()->GetParentFrame()->_001SendCommand(&command);
   //         }
   //
   //#endif
   //
   //      }
   //
   //      return FALSE;
   //
   //   }



      //void interaction::BaseControlExOnMouseMove(UINT nFlags, const ::point & point)
      //{
      //   UNREFERENCED_PARAMETER(nFlags);
      //   UNREFERENCED_PARAMETER(point);
      //   __pointer(::user::interaction) pwnd = ControlExGetWnd();

      //   ::point pointCursor;
      //   Session.get_cursor_pos(&pointCursor);

      //   e_element eelement;

      //   index iHover = hit_test(pointCursor, eelement);

      //   if (iHover != -1)
      //   {

      //      if (m_iHover != iHover || Session.GetCapture() != pwnd)
      //      {

      //         m_iHover = iHover;

      //         pwnd->SetCapture();

      //         pwnd->set_need_redraw();

      //      }

      //   }
      //   else
      //   {

      //      if (m_iHover != -1)
      //      {

      //         m_iHover = -1;

      //         Session.ReleaseCapture();

      //         pwnd->set_need_redraw();

      //      }

      //   }

      //}


      //void interaction::_001OnMouseMove(::message::message * pmessage)
      //{
      //
      //   if (is_window_enabled())
      //   {

      //      SCAST_PTR(::message::mouse, pmouse, pmessage);

      //      auto point = screen_to_client(pmouse->m_point);

      //      ::user::e_element eelementHover = hit_test(pmouse);

      //      if (m_eelementHover != eelementHover)
      //      {

      //         m_eelementHover = eelementHover;

      //         if (m_eelementHover)
      //         {

      //            track_mouse_leave();

      //         }

      //         set_need_redraw();

      //      }

      //   }

      //}


      //void interaction::_001OnMouseLeave(::message::message * pmessage)
      //{

      //   if (m_eelementHover)
      //   {

      //      m_eelementHover = element_none;

      //      set_need_redraw();

      //   }

      //   ::user::control_event ev;

      //   ev.m_id = m_id;

      //   ev.m_puie = this;

      //   ev.m_eevent = event_mouse_leave;

      //   ev.m_pmessage = pmessage;

      //   on_control_event(&ev);

      //}


      //void interaction::on_hit_test(::user::item & item)
      //{

      //   auto rectClient = get_client_rect();

      //   if (!rectClient.contains(point))
      //   {

      //      return element_none;

      //   }

      //   return element_client;

      //}


   control_cmd_ui::control_cmd_ui()
   {

   }


   //::user::form * interaction::get_form()
   //{

   //   return m_pform;

   //}


   //void interaction::route_control_event(::user::control_event* pevent)
   //{

   //   ::user::box::route_control_event(pevent);

   //}


   //void interaction::on_notify_control_event(control_event* pevent)
   //{

   //   ::user::box::on_notify_control_event(pevent);

   //}


   //void interaction::on_control_event(::user::control_event* pevent)
   //{

   //   ::user::box::on_control_event(pevent);

   //}


   //void interaction::_001OnDraw(::draw2d::graphics_pointer& pgraphics)
   //{

   //   ::user::box::_001OnDraw(pgraphics);
   //}


   void interaction::route_command_message(::user::command* pcommand)
   {

      ::user::layout::route_command_message(pcommand);

////      on_comman
//      ////::user::box::route_command_message(pcommand);
//
//      ////if (pcommand->m_bRet)
//      ////{
//
//      ////   return;
//
//      ////}

      __pointer(::user::interaction) puiParent = get_parent();

      while (puiParent.is_set() && puiParent->is_place_holder())
      {

         puiParent = puiParent->get_parent();

      }

      if (puiParent && puiParent->is_frame_window())
      {

         puiParent->route_command_message(pcommand);

      }


   }


   //void interaction::_001OnKeyDown(::message::message* pmessage)
   //{

   //   UNREFERENCED_PARAMETER(pmessage);
   //   //      SCAST_PTR(::message::key,pkey,pmessage);


   //}


   void interaction::_001OnEnable(::message::message* pmessage)
   {

      SCAST_PTR(::message::enable, penable, pmessage);

      if (m_puiLabel != nullptr)
      {

         m_puiLabel->enable_window(penable->get_enable());

      }

   }


   bool interaction::get_element_rect(RECT* prect, e_element eelement)
   {

      if (eelement == element_drop_down)
      {

         ::rect rectClient;

         get_client_rect(rectClient);

         //i32 iMargin = rectClient.height() / 8;
         i32 iMargin = 0;

         ::rect rectDropDown;

         rectDropDown = rectClient;

         i32 iW = rectClient.height() * 5 / 8;

         rectDropDown.right -= iMargin;
         rectDropDown.bottom -= iMargin;
         rectDropDown.top += iMargin;
         rectDropDown.left = rectDropDown.right - iW;

         *prect = rectDropDown;


         return true;

      }
      else if (eelement == element_combo_edit)
      {

         ::rect rectClient;

         get_client_rect(rectClient);

         ::rect rectDropDown;

         get_element_rect(rectDropDown, element_drop_down);

         ::rect rectEdit = rectClient;

         rectEdit.right = rectDropDown.left;

         //::rect rectPadding = _001GetRect(::user::rect_edit_padding);

         //rectEdit.deflate(rectPadding);

         *prect = rectEdit;


         return true;

      }

      return false;

   }


   void interaction::get_simple_drop_down_open_arrow_polygon(point_array& pointa)
   {

      ::rect rectDropDown;

      get_element_rect(rectDropDown, element_drop_down);

      i32 cx = rectDropDown.width() / 3;

      i32 cy = cx * 2 / 3;

      ::point pointCenter = rectDropDown.center();

      pointa.add(pointCenter.x - cx / 2, pointCenter.y - cy / 2);

      pointa.add(pointCenter.x + cx / 2, pointCenter.y - cy / 2);

      pointa.add(pointCenter.x, pointCenter.y + cy / 2);

   }



} // namespace user


//CLASS_DECL_AURA void g_track_popup_lyricview(::user::interaction * pinteraction, ::message::mouse * pmouse)
//{
//
//   //auto point = pmouse->m_point;
//
//   //pinteraction->_001ScreenToClient(point);
//
//   //pinteraction->track_popup_xml_menu("matter://popup_lyricview.xml", 0, point);
//
//}





prodevian::~prodevian()
{

   m_pinteraction->remove_prodevian(this);

}
