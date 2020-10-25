#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "base/user/user/_user.h"
#endif


//#include "control_ddx_dbflags.h"

//
//namespace user
//{
//
//
//   control::control()
//   {
//
//      m_puiLabel = nullptr;
//      m_pdrawcontext = nullptr;
//      m_pdescriptor = nullptr;
//      m_bControlExCommandEnabled = true;
//      m_pform = nullptr;
//      m_bDefaultWalkPreTranslateParentTree = true;
//      m_bIdBound = false;
//
//   }
//
//
//   control::~control()
//   {
//
//   }
//
//
//   void control::install_message_routing(::channel* pchannel)
//   {
//
//      //      ::user::impact::install_message_routing(pchannel);
//      ::user::box::install_message_routing(pchannel);
//
//      MESSAGE_LINK(e_message_create, pchannel, this, &::user::interaction::_001OnCreate);
//      //      MESSAGE_LINK(e_message_mouse_move, pchannel, this, &::user::interaction::_001OnMouseMove);
//      //
//      //#ifdef WINDOWS
//      //
//      //      MESSAGE_LINK(WM_MOUSELEAVE, pchannel, this, &::user::interaction::_001OnMouseLeave);
//      //
//      //#else
//      //
//      //      //::exception::throw_not_implemented();
//      //
//      //#endif
//      //
//      MESSAGE_LINK(WM_KEYDOWN, pchannel, this, &::user::interaction::_001OnKeyDown);
//
//      MESSAGE_LINK(WM_ENABLE, pchannel, this, &::user::interaction::_001OnEnable);
//      MESSAGE_LINK(e_message_set_focus, pchannel, this, &::user::interaction::_001OnSetFocus);
//      MESSAGE_LINK(e_message_kill_focus, pchannel, this, &::user::interaction::_001OnKillFocus);
//
//
//
//
//   }
//
//
//   void control::_001OnCreate(::message::message* pmessage)
//   {
//
//      SCAST_PTR(::message::create, pcreate, pmessage);
//
//      pcreate->previous();
//
//      ::user::control_event ev;
//
//      ev.m_puie = this;
//
//      ev.m_eevent = ::user::event_create;
//
//      on_control_event(&ev);
//
//   }
//
//
//   //bool control::has_action_hover()
//   //{
//
//   //   return m_eelementHover;
//
//   //}
//
//
//   void control::_003OnCustomDraw(::draw2d::graphics_pointer& pgraphics, ::aura::draw_context* pdrawcontext)
//   {
//
//      pgraphics->chain(pdrawcontext);
//
//      _000OnDraw(pgraphics);
//
//      pgraphics->unchain(pdrawcontext);
//
//   }
//
//
//   bool control::_003IsCustomMessage()
//   {
//
//      return m_bCustomWindowProc;
//
//   }
//
//
//   void control::_003CallCustomDraw(::draw2d::graphics_pointer& pgraphics, ::aura::draw_context* pdrawcontext)
//   {
//
//      _003OnCustomDraw(pgraphics, pdrawcontext);
//
//   }
//
//
//   bool control::_003CallCustomWindowProc(__pointer(::user::interaction) pwnd, const ::id & id, WPARAM wparam, LPARAM lparam, LRESULT& lresult)
//
//   {
//
//      m_pwndCustomWindowProc = pwnd;
//
//      __keep(m_bCustomWindowProc);
//
//      ::message::base base(pwnd, message, wparam, lparam);
//
//      _003CustomWindowProc(&base);
//
//      return base.m_bRet;
//
//   }
//
//
//   void control::_003CustomWindowProc(::message::message* pmessage)
//   {
//
//      UNREFERENCED_PARAMETER(pmessage);
//
//   }
//
//
//   bool control::operator == (const class control_descriptor& control_descriptor) const
//   {
//
//      return *m_pdescriptor == control_descriptor;
//
//   }
//
//
//   bool control::operator == (const class control& control) const
//   {
//
//      return operator == (*control.m_pdescriptor);
//
//   }
//
//
//
//   index control::GetEditItem()
//   {
//
//      return m_iEditItem;
//
//   }
//
//
//   index control::GetEditSubItem()
//   {
//
//      return (::index) control_descriptor().m_iSubItem;
//
//   }
//
//
//   void control::SetEditItem(index iItem)
//   {
//
//      m_iEditItem = iItem;
//
//   }
//
//
//   void control::SetEditSubItem(index iSubItem)
//   {
//
//      descriptor().m_iSubItem = iSubItem;
//
//   }
//
//
//   bool control::get_data(__pointer(::user::interaction)pwnd, var& var)
//   {
//
//      string str;
//
//      if (control_descriptor().get_control_type() == control_type_edit)
//      {
//
//         __pointer(::user::text) pedit = pwnd.m_p;
//
//         if (pedit == nullptr)
//            return false;
//
//         pedit->_001GetText(str);
//
//      }
//      else
//      {
//
//         __pointer(::user::text) ptext = this;
//
//         if (!ptext)
//         {
//
//            return false;
//
//         }
//
//         ptext->_001GetText(str);
//
//      }
//
//      switch (control_descriptor().get_data_type())
//      {
//      case control_data_type_string:
//      {
//         var = str;
//      }
//      return true;
//      case control_data_type_natural:
//      {
//         var = atoi(str);
//         return true;
//      }
//      break;
//      default:
//         return false;
//      }
//
//   }
//
//
//
//   bool control::Validate(string& strParam)
//   {
//
//      switch (control_descriptor().get_data_type())
//      {
//      case control_data_type_string:
//         return true;
//      case control_data_type_natural:
//      {
//         string str = strParam;
//         str.trim_left();
//         str.trim_right();
//         for (i32 i = 0; i < str.get_length(); i++)
//         {
//            if (str[i] >= L'0'
//               && str[i] <= L'9')
//            {
//            }
//            else
//            {
//               return false;
//            }
//
//         }
//         return true;
//      }
//      break;
//      default:
//         return true;
//      }
//   }
//
//
//
//   bool control::_001IsPointInside(::point point)
//   {
//
//      return ::user::interaction::_001IsPointInside(point);
//
//   }
//
//
//
//
//   bool control::has_function(e_control_function econtrolfunction) const
//   {
//
//      if (m_pdescriptor.is_null())
//      {
//
//         return false;
//
//      }
//
//      return m_pdescriptor->has_function(econtrolfunction);
//
//   }
//
//
//   e_control_type control::get_control_type() const
//   {
//
//      if (m_pdescriptor.is_null())
//      {
//
//         return control_type_none;
//
//      }
//
//      return m_pdescriptor->get_control_type();
//
//   }
//
//
//   bool control::create_control(class control_descriptor* pdescriptor)
//   {
//
//      m_pdescriptor = pdescriptor;
//
//      try
//      {
//
//         if (!create_window(pdescriptor->m_puserinteractionParent, pdescriptor->m_id))
//         {
//
//            m_pdescriptor.release();
//
//            return false;
//
//         }
//
//      }
//      catch (...)
//      {
//
//         m_pdescriptor.release();
//
//         return false;
//
//      }
//
//      m_pdescriptor->m_pinteraction = this;
//
//      m_pdescriptor->m_bCreated = true;
//
//      m_pdescriptor->m_controlmap[m_pdescriptor->m_iItem] = this;
//
//      return true;
//
//   }
//
//
//   estate control::get_state() const
//   {
//   if (m_pdrawcontext != nullptr)
//   {
//
//      estate estate = e_state_none;
//
//      if (!is_window_enabled())
//      {
//
//         estate |= e_state_disabled;
//
//      }
//
//      if (Session.get_focus_ui() == this)
//      {
//
//         estate |= e_state_focused;
//
//      }
//
//
//      if (m_pdrawcontext->is_control_hover())
//      {
//
//         estate |= e_state_hover;
//
//      }
//
//      if (m_pdrawcontext->is_control_selected())
//      {
//
//         estate |= e_state_selected;
//
//
//      }
//
//      return estate;
//
//   }
//
//   return ::user::interaction::get_state();
//
//}
//
//
//
//
//
//
//   //bool control::get_window_rect(RECT * prect)
//
//   //{
//
//   //   if (m_pdrawcontext != nullptr)
//   //   {
//
//   //      *prect = m_pdrawcontext->m_rectWindow;
//
//
//   //      return true;
//
//   //   }
//
//   //   return ::user::box::get_window_rect(prect);
//
//
//   //}
//
//
//
//   //bool control::get_client_rect(RECT * prect)
//
//   //{
//
//   //   if (m_pdrawcontext != nullptr)
//   //   {
//
//   //      *prect = m_pdrawcontext->m_rectClient;
//
//
//   //      ::offset_rect(prect, -m_pdrawcontext->m_rectClient.top_left());
//
//
//   //      return true;
//
//   //   }
//
//
//   //   return ::user::box::get_client_rect(prect);
//
//
//   //}
//
//
//
//
//
//   bool control::IsControlCommandEnabled()
//   {
//      return m_bControlExCommandEnabled;
//   }
//
//
//   void control::EnableControlCommand(bool bEnable)
//   {
//
//      m_bControlExCommandEnabled = bEnable;
//
//      set_need_redraw();
//
//   }
//
//
//   void control::_001OnSetFocus(::message::message * pmessage)
//   {
//
//      //if (!::user::box::keyboard_focus_OnSetFocus())
//      //{
//
//      //   return false;
//
//      //}
//
//      ::user::control_event ev;
//
//      ev.m_puie = this;
//
//      ev.m_eevent = ::user::event_set_focus;
//
//      on_control_event(&ev);
//
//      pmessage->m_bRet =  ev.m_bRet;
//
//   }
//
//
//   void control::_001OnKillFocus(::message::message * pmessage)
//   {
//
//      SCAST_PTR(::message::kill_focus, pkillfocus, pmessage);
//
//      ::user::control_event ev;
//
//      ev.m_puie = this;
//
//      ev.m_id = m_id;
//
//      ev.m_eevent = ::user::event_kill_focus;
//
//      on_control_event(&ev);
//
//      pkillfocus->m_bRet = ev.m_bRet;
//
//   }
//
//
//   void control_cmd_ui::enable(bool bOn)
//   {
//
//      m_bEnableChanged = TRUE;
//
//      __pointer(::user::interaction) pwnd = m_puiOther;
//
//      ASSERT(pwnd != nullptr);
//
//      ASSERT_KINDOF(::user::interaction, pwnd);
//
//      __pointer(::user::interaction) pinteraction = pwnd->get_child_by_id(m_idControl);
//
//      __pointer(control) pcontrolex = (pinteraction.m_p);
//
//      if (pcontrolex != nullptr)
//      {
//
//         if (bOn)
//         {
//
//            if (pwnd->is_window_enabled() && !pcontrolex->IsControlCommandEnabled())
//            {
//
//               pcontrolex->EnableControlCommand(true);
//
//            }
//
//         }
//         else
//         {
//
//            if (pcontrolex->IsControlCommandEnabled())
//            {
//
//               pcontrolex->EnableControlCommand(false);
//
//            }
//
//         }
//
//      }
//      else
//      {
//
//         if (pinteraction != nullptr)
//         {
//
//            if (bOn)
//            {
//
//               if (!pinteraction->is_window_enabled())
//               {
//
//                  pinteraction->enable_window();
//
//               }
//
//            }
//            else
//            {
//
//               if (pinteraction->is_window_enabled())
//               {
//
//                  pinteraction->enable_window(FALSE);
//
//               }
//
//            }
//
//         }
//
//      }
//
//   }
//
//
//   void control_cmd_ui::SetCheck(i32 nCheck)
//   {
//      ASSERT(nCheck >= 0 && nCheck <= 2); // 0=>off, 1=>on, 2=>indeterminate
//      /*__pointer(::user::interaction) pwnd = (__pointer(::user::interaction))m_pOther;
//      ASSERT(pToolBar != nullptr);
//      ASSERT_KINDOF(simple_toolbar, pToolBar);
//      ASSERT(m_nIndex < m_nIndexMax);
//
//      UINT nNewStyle = pToolBar->GetButtonStyle(m_nIndex) &
//                  ~(TBBS_CHECKED | TBBS_INDETERMINATE);
//      if (nCheck == 1)
//          nNewStyle |= TBBS_CHECKED;
//      else if (nCheck == 2)
//          nNewStyle |= TBBS_INDETERMINATE;
//      ASSERT(!(nNewStyle & TBBS_SEPARATOR));
//      pToolBar->SetButtonStyle(m_nIndex, nNewStyle | TBBS_CHECKBOX);*/
//   }
//
//   void control_cmd_ui::SetText(const char *)
//   {
//      // ignore it
//   }
//
//
//   id control_cmd_ui::GetControlCommand(id id)
//   {
//      ::id idCommand;
//      if (m_mapControlCommand.lookup(id, idCommand))
//      {
//         return id;
//      }
//      return id;
//   }
//
//
////   LRESULT control_view_impl::BaseControlExOnIdleUpdateCmdUI(WPARAM wParam, LPARAM)
////   {
////      __pointer(::user::interaction) pview = get_window();
////
////      // handle delay hide/show
////      bool bVis = (pview->GetStyle() & WS_VISIBLE) != 0;
////
////      // the style must be visible
////      if (bVis)
////      {
////         __pointer(::user::frame_window) pTarget = pview->GetOwner();
////         if (pTarget == nullptr)
////            pTarget = pview->GetParentFrame();
////         if (pTarget != nullptr)
////            BaseControlExOnUpdateCmdUI(pTarget, wParam != FALSE);
////      }
////
////      return 0L;
////
////   }
////
////
////   void control_view_impl::BaseControlExOnUpdateCmdUI(__pointer(::user::frame_window) pTarget, bool bDisableIfNoHndler)
////   {
////
////      __pointer(::user::interaction) pview = get_window();
////
////      ::user::command & state = m_commandui;
////
////      state.m_puiOther = pview;
////
////      __pointer(::user::interaction) pwndIterator = pview->GetTopWindow();
////
////      __pointer(::user::interaction) pwnd;
////
////      __pointer(control) pcontrolex;
////
////      for (; pwndIterator != nullptr; pwndIterator = pwndIterator->get_next_window())
////      {
////
////         pwnd = pwndIterator->GetTopLevel();
////
////         pcontrolex = nullptr;
////
////         if (pwnd != nullptr)
////         {
////            //#ifdef WINDOWS_DESKTOP
////            //            pwnd->send_message(control::g_uiMessage, control::MessageParamGetBaseControlExPtr, (LPARAM) &pcontrolex);
////            //#else
////            __throw(todo(pwnd->get_context_application()));
////            //#endif
////         }
////         if (pcontrolex != nullptr)
////         {
////
////            id idControl = pwnd->GetDlgCtrlId();
////
////            // xxx         state.m_nIndex = uiID;
////            state.m_iCount = -1;
////            state.m_id = m_commandui.GetControlCommand(idControl);
////            state.m_bContinueRouting = FALSE;
////
////            // ignore separators
////            if ((pwnd->GetStyle() & WS_VISIBLE))
////            {
////               // allow reflections
////               if (pview->on_command_probe(&state))
////               {
////                  continue;
////               }
////
////               // allow the toolbar itself to have update handlers
////               if (pview->on_command_probe(&state))
////                  //               {
////                    //                state.DoUpdate(pTarget, bDisableIfNoHndler);
////                  continue;
////               //           }
////
////                          // allow the owner to process the update
////               state.DoUpdate(pTarget, bDisableIfNoHndler);
////            }
////         }
////      }
////
////      // update the dialog controls added to the toolbar
////  //  UpdateDialogControls(pTarget, bDisableIfNoHndler);
////   }
////
////
////   __pointer(::user::interaction) control_view_impl::get_window()
////   {
////      return  (this);
////   }
////
////
////   bool control_view_impl::BaseControlExOnCommand(WPARAM wParam, LPARAM lParam)
////   {
////
////      UNREFERENCED_PARAMETER(lParam);
////
////      if (get_window() != nullptr)
////      {
////
////#ifdef WINDOWS
////
////         const ::id & id = ((wParam >> 16) & 0xffff);
////
////
////         if (emessage == BN_CLICKED)
////         {
////            //xxx id idCommand = m_commandui.GetControlCommand(wParam & 0xffff);
////            //::user::command command(idCommand);
////            //xxx get_window()->GetParentFrame()->_001SendCommand(&command);
////         }
////
////#endif
////
////      }
////
////      return FALSE;
////
////   }
//
//
//
//   //void control::BaseControlExOnMouseMove(UINT nFlags, const ::point & point)
//   //{
//   //   UNREFERENCED_PARAMETER(nFlags);
//   //   UNREFERENCED_PARAMETER(point);
//   //   __pointer(::user::interaction) pwnd = ControlExGetWnd();
//
//   //   ::point pointCursor;
//   //   Session.get_cursor_pos(&pointCursor);
//
//   //   e_element eelement;
//
//   //   index iHover = hit_test(pointCursor, eelement);
//
//   //   if (iHover != -1)
//   //   {
//
//   //      if (m_iHover != iHover || Session.GetCapture() != pwnd)
//   //      {
//
//   //         m_iHover = iHover;
//
//   //         pwnd->SetCapture();
//
//   //         pwnd->set_need_redraw();
//
//   //      }
//
//   //   }
//   //   else
//   //   {
//
//   //      if (m_iHover != -1)
//   //      {
//
//   //         m_iHover = -1;
//
//   //         Session.ReleaseCapture();
//
//   //         pwnd->set_need_redraw();
//
//   //      }
//
//   //   }
//
//   //}
//
//
//   //void control::_001OnMouseMove(::message::message * pmessage)
//   //{
//   //
//   //   if (is_window_enabled())
//   //   {
//
//   //      SCAST_PTR(::message::mouse, pmouse, pmessage);
//
//   //      auto point = screen_to_client(pmouse->m_point);
//
//   //      ::user::e_element eelementHover = hit_test(pmouse);
//
//   //      if (m_eelementHover != eelementHover)
//   //      {
//
//   //         m_eelementHover = eelementHover;
//
//   //         if (m_eelementHover)
//   //         {
//
//   //            track_mouse_leave();
//
//   //         }
//
//   //         set_need_redraw();
//
//   //      }
//
//   //   }
//
//   //}
//
//
//   //void control::_001OnMouseLeave(::message::message * pmessage)
//   //{
//
//   //   if (m_eelementHover)
//   //   {
//
//   //      m_eelementHover = element_none;
//
//   //      set_need_redraw();
//
//   //   }
//
//   //   ::user::control_event ev;
//
//   //   ev.m_id = m_id;
//
//   //   ev.m_puie = this;
//
//   //   ev.m_eevent = event_mouse_leave;
//
//   //   ev.m_pmessage = pmessage;
//
//   //   on_control_event(&ev);
//
//   //}
//
//
//   //void control::on_hit_test(::user::item & item)
//   //{
//
//   //   auto rectClient = get_client_rect();
//
//   //   if (!rectClient.contains(point))
//   //   {
//
//   //      return element_none;
//
//   //   }
//
//   //   return element_client;
//
//   //}
//
//
//   control_cmd_ui::control_cmd_ui()
//   {
//
//   }
//
//
//   //::user::form * control::get_form()
//   //{
//
//   //   return m_pform;
//
//   //}
//
//
//   void control::route_control_event(::user::control_event* pevent)
//   {
//
//      ::user::box::route_control_event(pevent);
//
//   }
//
//
//   void control::on_notify_control_event(control_event* pevent)
//   {
//
//      ::user::box::on_notify_control_event(pevent);
//
//   }
//
//
//   void control::on_control_event(::user::control_event * pevent)
//   {
//
//      ::user::box::on_control_event(pevent);
//
//   }
//
//
//   void control::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
//   {
//
//      ::user::box::_001OnDraw(pgraphics);
//   }
//
//
//   void control::route_command_message(::user::command * pcommand)
//   {
//
//      ::user::box::route_command_message(pcommand);
//
//      if (pcommand->m_bRet)
//      {
//
//         return;
//
//      }
//
//      __pointer(::user::interaction) puiParent = get_parent();
//
//      while (puiParent.is_set() && puiParent->is_place_holder())
//      {
//
//         puiParent = puiParent->get_parent();
//
//      }
//
//      if (puiParent != nullptr)
//      {
//
//         puiParent->route_command_message(pcommand);
//
//      }
//
//
//   }
//
//
//   void control::_001OnKeyDown(::message::message * pmessage)
//   {
//
//      UNREFERENCED_PARAMETER(pmessage);
//      //      SCAST_PTR(::message::key,pkey,pmessage);
//
//
//   }
//
//
//   void control::_001OnEnable(::message::message * pmessage)
//   {
//
//      SCAST_PTR(::message::enable, penable, pmessage);
//
//      if (m_puiLabel != nullptr)
//      {
//
//         m_puiLabel->enable_window(penable->get_enable());
//
//      }
//
//   }
//
//
//   bool control::get_element_rect(RECT * prect, e_element eelement)
//
//   {
//
//      if (eelement == element_drop_down)
//      {
//
//         ::rect rectClient;
//
//         ((control *)this)->get_client_rect(rectClient);
//
//         //i32 iMargin = rectClient.height() / 8;
//         i32 iMargin = 0;
//
//         ::rect rectDropDown;
//
//         rectDropDown = rectClient;
//
//         i32 iW = rectClient.height() * 5 / 8;
//
//         rectDropDown.right -= iMargin;
//         rectDropDown.bottom -= iMargin;
//         rectDropDown.top += iMargin;
//         rectDropDown.left = rectDropDown.right - iW;
//
//         *prect = rectDropDown;
//
//
//         return true;
//
//      }
//      else if (eelement == element_combo_edit)
//      {
//
//         ::rect rectClient;
//
//         get_client_rect(rectClient);
//
//         ::rect rectDropDown;
//
//         get_element_rect(rectDropDown, element_drop_down);
//
//         ::rect rectEdit = rectClient;
//
//         rectEdit.right = rectDropDown.left;
//
//         //::rect rectPadding = _001GetRect(::user::rect_edit_padding);
//
//         //rectEdit.deflate(rectPadding);
//
//         *prect = rectEdit;
//
//
//         return true;
//
//      }
//
//      return false;
//
//   }
//
//
//   void control::get_simple_drop_down_open_arrow_polygon(point_array & pointa)
//   {
//
//      ::rect rectDropDown;
//
//      get_element_rect(rectDropDown, element_drop_down);
//
//      i32 cx = rectDropDown.width() / 3;
//
//      i32 cy = cx * 2 / 3;
//
//      ::point pointCenter = rectDropDown.center();
//
//      pointa.add(pointCenter.x - cx / 2, pointCenter.y - cy / 2);
//
//      pointa.add(pointCenter.x + cx / 2, pointCenter.y - cy / 2);
//
//      pointa.add(pointCenter.x, pointCenter.y + cy / 2);
//
//   }
//
//
//
//} // namespace base
//


