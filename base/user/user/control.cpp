#include "framework.h"
#include "base/user/user/_user.h"


//#include "e_control_ddx_dbflags.h"

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
//      MESSAGE_LINK(e_message_create, pchannel, this, &::user::interaction::on_message_create);
//      //      MESSAGE_LINK(e_message_mouse_move, pchannel, this, &::user::interaction::on_message_mouse_move);
//      //
//      //#ifdef WINDOWS
//      //
//      //      MESSAGE_LINK(e_message_mouse_leave, pchannel, this, &::user::interaction::on_message_mouse_leave);
//      //
//      //#else
//      //
//      //      //throw interface_only_exception();
//      //
//      //#endif
//      //
//      MESSAGE_LINK(e_message_key_down, pchannel, this, &::user::interaction::on_message_key_down);
//
//      MESSAGE_LINK(e_message_enable, pchannel, this, &::user::interaction::_001OnEnable);
//      MESSAGE_LINK(e_message_set_focus, pchannel, this, &::user::interaction::_001OnSetFocus);
//      MESSAGE_LINK(e_message_kill_focus, pchannel, this, &::user::interaction::_001OnKillFocus);
//
//
//
//
//   }
//
//
//   void control::on_message_create(::message::message* pmessage)
//   {
//
//      __pointer(::message::create) pcreate(pmessage);
//
//      pcreate->previous();
//
//      ::subject subject;
//
//      subject.m_puserinteraction = this;
//
//      subject.m_id = ::e_subject_create;
//
//      route(&subject);
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
//   bool control::_003CallCustomWindowProc(__pointer(::user::interaction) puserinteraction, const ::id & id, wparam wparam, lparam lparam, LRESULT& lresult)
//
//   {
//
//      m_puserinteractionCustomWindowProc = puserinteraction;
//
//      __keep(m_bCustomWindowProc);
//
//      ::user::message base(puserinteraction, message, wparam, lparam);
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
//      __UNREFERENCED_PARAMETER(pmessage);
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
//   bool control::get_data(__pointer(::user::interaction)puserinteraction, ::payload& payload)
//   {
//
//      string str;
//
//      if (control_descriptor().get_control_type() == e_control_type_edit)
//      {
//
//         __pointer(::user::text) pedit = puserinteraction.m_p;
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
//      case e_control_data_type_string:
//      {
//         payload = str;
//      }
//      return true;
//      case e_control_data_type_natural:
//      {
//         payload = atoi(str);
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
//      case e_control_data_type_string:
//         return true;
//      case e_control_data_type_natural:
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
//   bool control::_001IsPointInside(::point_i32 point)
//   {
//
//      return ::user::interaction::_001IsPointInside(point);
//
//   }
//
//
//
//
//   bool control::has_function(enum_control_function econtrolfunction) const
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
//   enum_control_type control::get_control_type() const
//   {
//
//      if (m_pdescriptor.is_null())
//      {
//
//         return e_control_type_none;
//
//      }
//
//      return m_pdescriptor->get_control_type();
//
//   }
//
//
//   bool control::create_interaction(::user::interaction * pinteractionParent, const ::id & id)
//   {
//
//      m_pdescriptor = pdescriptor;
//
//      try
//      {
//
//         if (!create_interaction(pdescriptor->m_puserinteractionParent, pdescriptor->m_id))
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
//      if (psession->get_focus_ui() == this)
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
//   //bool control::get_window_rect(RECTANGLE_I32 * prectangle)
//
//   //{
//
//   //   if (m_pdrawcontext != nullptr)
//   //   {
//
//   //      *prectangle = m_pdrawcontext->m_rectangleWindow;
//
//
//   //      return true;
//
//   //   }
//
//   //   return ::user::box::get_window_rect(prectangle);
//
//
//   //}
//
//
//
//   //bool control::get_client_rect(RECTANGLE_I32 * prectangle)
//
//   //{
//
//   //   if (m_pdrawcontext != nullptr)
//   //   {
//
//   //      *prectangle = m_pdrawcontext->m_rectangleClient;
//
//
//   //      ::offset_rect(prectangle, -m_pdrawcontext->m_rectangleClient.top_left());
//
//
//   //      return true;
//
//   //   }
//
//
//   //   return ::user::box::get_client_rect(prectangle);
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
//      ::subject subject;
//
//      subject.m_puserinteraction = this;
//
//      subject.m_id = ::e_subject_set_focus;
//
//      route(&subject);
//
//      pmessage->m_bRet =  subject.m_bRet;
//
//   }
//
//
//   void control::_001OnKillFocus(::message::message * pmessage)
//   {
//
//      __pointer(::message::kill_focus) pkillfocus(pmessage);
//
//      ::subject subject;
//
//      subject.m_puserinteraction = this;
//
//      //subject.m_id = m_id;
//
//      subject.m_id = ::e_subject_kill_focus;
//
//      route(&subject);
//
//      pkillfocus->m_bRet = subject.m_bRet;
//
//   }
//
//
//   void control_cmd_ui::enable(bool bOn)
//   {
//
//      m_bEnableChanged = true;
//
//      __pointer(::user::interaction) puserinteraction = m_puiOther;
//
//      ASSERT(puserinteraction != nullptr);
//
//      ASSERT_KINDOF(::user::interaction, puserinteraction);
//
//      __pointer(::user::interaction) pinteraction = puserinteraction->get_child_by_id(m_idControl);
//
//      __pointer(control) pcontrolex = (pinteraction.m_p);
//
//      if (pcontrolex != nullptr)
//      {
//
//         if (bOn)
//         {
//
//            if (puserinteraction->is_window_enabled() && !pcontrolex->IsControlCommandEnabled())
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
//                  pinteraction->enable_window(false);
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
//      /*__pointer(::user::interaction) puserinteraction = (__pointer(::user::interaction))m_pOther;
//      ASSERT(pToolBar != nullptr);
//      ASSERT_KINDOF(simple_toolbar, pToolBar);
//      ASSERT(m_nIndex < m_nIndexMax);
//
//      ::u32 nNewStyle = pToolBar->GetButtonStyle(m_nIndex) &
//                  ~(TBBS_CHECKED | TBBS_INDETERMINATE);
//      if (nCheck == 1)
//          nNewStyle |= TBBS_CHECKED;
//      else if (nCheck == 2)
//          nNewStyle |= TBBS_INDETERMINATE;
//      ASSERT(!(nNewStyle & e_toolbar_item_style_separator));
//      pToolBar->SetButtonStyle(m_nIndex, nNewStyle | TBBS_CHECKBOX);*/
//   }
//
//   void control_cmd_ui::SetText(const ::string &)
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
////         __pointer(::user::frame_window) pTarget = pview->get_owner();
////         if (pTarget == nullptr)
////            pTarget = pview->get_parent_frame();
////         if (pTarget != nullptr)
////            BaseControlExOnUpdateCmdUI(pTarget, wParam != false);
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
////      ::message::command & state = m_commandui;
////
////      state.m_puiOther = pview;
////
////      __pointer(::user::interaction) puserinteractionIterator = pview->GetTopWindow();
////
////      __pointer(::user::interaction) puserinteraction;
////
////      __pointer(control) pcontrolex;
////
////      for (; puserinteractionIterator != nullptr; puserinteractionIterator = puserinteractionIterator->get_next_window())
////      {
////
////         puserinteraction = puserinteractionIterator->get_top_level();
////
////         pcontrolex = nullptr;
////
////         if (puserinteraction != nullptr)
////         {
////            //#ifdef WINDOWS_DESKTOP
////            //            puserinteraction->send_message(control::g_uiMessage, control::MessageParamGetBaseControlExPtr, (LPARAM) &pcontrolex);
////            //#else
////            __throw(todo(puserinteraction->get_application()));
////            //#endif
////         }
////         if (pcontrolex != nullptr)
////         {
////
////            id idControl = puserinteraction->GetDlgCtrlId();
////
////            // xxx         state.m_nIndex = uId;
////            state.m_iCount = -1;
////            state.m_id = m_commandui.GetControlCommand(idControl);
////            state.m_bContinueRouting = false;
////
////            // ignore separators
////            if ((puserinteraction->GetStyle() & WS_VISIBLE))
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
////      __UNREFERENCED_PARAMETER(lParam);
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
////            //::message::command command(idCommand);
////            //xxx get_window()->get_parent_frame()->_001SendCommand(&command);
////         }
////
////#endif
////
////      }
////
////      return false;
////
////   }
//
//
//
//   //void control::BaseControlExOnMouseMove(::u32 nFlags, const ::point_i32 & point)
//   //{
//   //   __UNREFERENCED_PARAMETER(nFlags);
//   //   __UNREFERENCED_PARAMETER(point);
//   //   __pointer(::user::interaction) puserinteraction = ControlExGetWnd();
//
//   //   ::point_i32 pointCursor;
//   //   psession->get_cursor_position(&pointCursor);
//
//   //   enum_element eelement;
//
//   //   index iHover = hit_test(pointCursor, eelement);
//
//   //   if (iHover != -1)
//   //   {
//
//   //      if (m_iHover != iHover || psession->GetCapture() != puserinteraction)
//   //      {
//
//   //         m_iHover = iHover;
//
//   //         puserinteraction->SetCapture();
//
//   //         puserinteraction->set_need_redraw();
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
//auto psession = get_session();
//
//auto puser = psession->user();
//
//auto pwindowing = puser->windowing();
//
//pwindowing->release_capture();
//
//   //         puserinteraction->set_need_redraw();
//
//   //      }
//
//   //   }
//
//   //}
//
//
//   //void control::on_message_mouse_move(::message::message * pmessage)
//   //{
//   //
//   //   if (is_window_enabled())
//   //   {
//
//   //      auto pmouse = pmessage->m_pmouse;
//
//   //      auto point = screen_to_client(pmouse->m_point);
//
//   //      ::enum_element eelementHover = hit_test(pmouse);
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
//   //void control::on_message_mouse_leave(::message::message * pmessage)
//   //{
//
//   //   if (m_eelementHover)
//   //   {
//
//   //      m_eelementHover = e_element_none;
//
//   //      set_need_redraw();
//
//   //   }
//
//   //   ::subject subject;
//
//   //   //subject.m_id = m_id;
//
//   //   subject.m_puserinteraction = this;
//
//   //   subject.m_id = e_event_mouse_leave;
//
//   //   subject.m_pmessage = pmessage;
//
//   //   route(&subject);
//
//   //}
//
//
//   //void control::on_hit_test(::item & item)
//   //{
//
//   //   auto rectangleClient = get_client_rect();
//
//   //   if (!rectangleClient.contains(point))
//   //   {
//
//   //      return e_element_none;
//
//   //   }
//
//   //   return e_element_client;
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
//   void control::route(::subject * psubject, ::context * pcontext)
//   {
//
//      ::user::box::route_handling(pevent);
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
//   void control::handle(::subject * psubject, ::context * pcontext)
//   {
//
//      ::user::box::handle(psubject, pcontext);
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
//   void control::route_command(::message::command * pcommand, bool bRouteToKeyDescendant)
//   {
//
//      ::user::box::route_command(pcommand);
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
//         puiParent->route_command(pcommand);
//
//      }
//
//
//   }
//
//
//   void control::on_message_key_down(::message::message * pmessage)
//   {
//
//      __UNREFERENCED_PARAMETER(pmessage);
//      //      auto pkey = pmessage->m_pkey;
//
//
//   }
//
//
//   void control::_001OnEnable(::message::message * pmessage)
//   {
//
//      __pointer(::message::enable) penable(pmessage);
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
//   bool control::get_element_rect(RECTANGLE_I32 * prectangle, enum_element eelement)
//
//   {
//
//      if (eelement == e_element_drop_down)
//      {
//
//         ::rectangle_i32 rectangleClient;
//
//         ((control *)this)->get_client_rect(rectangleClient);
//
//         //i32 iMargin = rectangleClient.height() / 8;
//         i32 iMargin = 0;
//
//         ::rectangle_i32 rectangleDropDown;
//
//         rectangleDropDown = rectangleClient;
//
//         i32 iW = rectangleClient.height() * 5 / 8;
//
//         rectangleDropDown.right -= iMargin;
//         rectangleDropDown.bottom -= iMargin;
//         rectangleDropDown.top += iMargin;
//         rectangleDropDown.left = rectangleDropDown.right - iW;
//
//         *prectangle = rectangleDropDown;
//
//
//         return true;
//
//      }
//      else if (eelement == e_element_combo_edit)
//      {
//
//         ::rectangle_i32 rectangleClient;
//
//         get_client_rect(rectangleClient);
//
//         ::rectangle_i32 rectangleDropDown;
//
//         get_element_rect(rectangleDropDown, e_element_drop_down);
//
//         ::rectangle_i32 rectangleEdit = rectangleClient;
//
//         rectangleEdit.right = rectangleDropDown.left;
//
//         //::rectangle_i32 rectanglePadding = _001GetRect(::user::rect_edit_padding);
//
//         //rectangleEdit.deflate(rectanglePadding);
//
//         *prectangle = rectangleEdit;
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
//   void control::get_simple_drop_down_open_arrow_polygon(point_f64_array & pointa)
//   {
//
//      ::rectangle_i32 rectangleDropDown;
//
//      get_element_rect(rectangleDropDown, e_element_drop_down);
//
//      i32 cx = rectangleDropDown.width() / 3;
//
//      i32 cy = cx * 2 / 3;
//
//      ::point_i32 pointCenter = rectangleDropDown.center();
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


