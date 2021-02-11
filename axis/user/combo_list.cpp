#include "framework.h"
#include "axis/user/_user.h"
#include "acme/const/timer.h"


namespace user
{


   combo_list::combo_list()
   {

      user_combo_list_common_construct();

   }


   combo_list::~combo_list()
   {

   }


   void combo_list::user_combo_list_common_construct()
   {

      defer_create_mutex();

      m_bTransparent = true;

      m_bPendingKillFocusHiding = false;

      m_ewindowflag += e_window_flag_satellite_window;

      m_ewindowflag += e_window_flag_arbitrary_positioning;

      m_bComboList = true;

      m_puiDeactivateTogether = nullptr;

      m_pcombo = nullptr;

      m_iPadding = 2;

      m_iBorder = 0;

      m_iMinListItemCount = 8;

      m_bMovingComboBox = false;

   }


   void combo_list::install_message_routing(::channel * pchannel)
   {

      ::user::scroll_base::install_message_routing(pchannel);

      install_simple_ui_default_mouse_handling(pchannel);

      MESSAGE_LINK(e_message_create, pchannel, this, &combo_list::_001OnCreate);
      MESSAGE_LINK(e_message_destroy, pchannel, this, &combo_list::_001OnDestroy);
      MESSAGE_LINK(e_message_set_focus, pchannel, this, &combo_list::_001OnSetFocus);
      MESSAGE_LINK(e_message_kill_focus, pchannel, this, &combo_list::_001OnKillFocus);
      MESSAGE_LINK(e_message_close, pchannel, this, &combo_list::_001OnClose);
      MESSAGE_LINK(e_message_mouse_activate, pchannel, this, &combo_list::_001OnMouseActivate);
      MESSAGE_LINK(e_message_key_down, pchannel, this, &combo_list::_001OnKeyDown);
      MESSAGE_LINK(e_message_key_up, pchannel, this, &combo_list::_001OnKeyUp);
      MESSAGE_LINK(e_message_left_button_down, pchannel, this, &combo_list::_001OnLButtonDown);
      MESSAGE_LINK(e_message_non_client_left_button_down, pchannel, this, &combo_list::_001OnLButtonDown);
      MESSAGE_LINK(e_message_left_button_up, pchannel, this, &combo_list::_001OnLButtonUp);
      MESSAGE_LINK(e_message_middle_button_down, pchannel, this, &combo_list::_001OnMButtonDown);
      MESSAGE_LINK(e_message_right_button_down, pchannel, this, &combo_list::_001OnRButtonDown);
      MESSAGE_LINK(e_message_mouse_move, pchannel, this, &combo_list::_001OnMouseMove);
      MESSAGE_LINK(e_message_show_window, pchannel, this, &combo_list::_001OnShowWindow);

   }


   void combo_list::_001OnCreate(::message::message * pmessage)
   {

      pmessage->previous();

   }


   bool combo_list::on_set_owner(::user::primitive * pprimitive)
   {

      auto puserinteractionOwner = pprimitive->get_owner();

      if(puserinteractionOwner)
      {

         auto puserinteractionHost = puserinteractionOwner->get_host_window();

         if (puserinteractionHost)
         {

            auto pimpl = puserinteractionHost->m_pimpl.cast<::user::interaction_impl>();

            if (pimpl)
            {

               sync_lock sl(pimpl->mutex());

               pimpl->m_userinteractionaHideOnConfigurationChange.add_unique_interaction(this);

            }

         }

      }

      return true;

   }


   void combo_list::_001OnDestroy(::message::message * pmessage)
   {

      auto puserinteractionOwner = get_owner();

      if(puserinteractionOwner)
      {

         auto puserinteractionHost = puserinteractionOwner->get_host_window();

         if(puserinteractionHost)
         {

            auto pimpl = puserinteractionHost->m_pimpl.cast<::user::interaction_impl>();

            if (pimpl)
            {

               sync_lock sl(pimpl->mutex());

               pimpl->m_userinteractionaHideOnConfigurationChange.remove_interaction(this);

            }

         }

      }

      pmessage->previous();

   }


   void combo_list::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      ::draw2d::savedc savedc(pgraphics);

      if (m_pcombo == nullptr)
      {

         return;

      }

      ::rectangle_f64 rectClipBox;

      pgraphics->get_clip_box(&rectClipBox);

      pgraphics->reset_clip();

      _001OnDrawComboList(pgraphics);

   }


   void combo_list::_001OnDrawComboList(::draw2d::graphics_pointer & pgraphics)
   {

      ::count iListItemCount = m_pcombo->_001GetListCount();

      string strItem;

      ::rectangle_i32 rectClient;

      layout().get_client_rect(rectClient, ::user::e_layout_design);

      ::draw2d::brush_pointer brBk(e_create);

      brBk->create_solid(argb(230, 255, 255, 255));

      pgraphics->set(brBk);

      pgraphics->fill_rectangle(rectClient);

      auto pstyle = get_style(pgraphics);

      ::rectangle_i32 rectItem;

      rectItem = rectClient;

      rectItem.bottom = rectClient.top;

      if (m_pcombo->m_bEdit)
      {

         rectItem.bottom += _001GetItemHeight();

      }

      auto psession = Session;

      auto puser = psession->user();

      auto pwindowing = puser->windowing();

      auto pointCursor = pwindowing->get_cursor_pos();

      _001ScreenToClient(&pointCursor, ::user::e_layout_design);

      pgraphics->set_font(this, ::user::e_element_none);

      auto itemHover = hover_item();

      index iCurSel = current_item();

      ::draw2d::brush_pointer br(e_create);

      for (index iItem = 0; iItem < iListItemCount; iItem++)
      {

         rectItem.top = rectItem.bottom;

         rectItem.bottom = rectItem.top + _001GetItemHeight();

         ::color::color colorBackground;

         ::color::color colorText;

         string strDebug;

         ::user::e_state estate = ::user::e_state_none;

         if (itemHover == iItem)
         {

            strDebug += "hover;";

            estate += ::user::e_state_hover;

         }

         if (iItem == iCurSel)
         {

            strDebug += "selected;";

            estate += ::user::e_state_selected;

         }

         colorBackground = get_color(pstyle, ::user::e_element_item_background, estate);

         colorText = get_color(pstyle, ::user::e_element_item_text, estate);

         brBk->create_solid(colorBackground);

         br->create_solid(colorText);

         pgraphics->set(brBk);

         pgraphics->fill_rectangle(rectItem);

         m_pcombo->_001GetListText(iItem, strItem);

         pgraphics->set(br);

         auto rectText = rectItem;

         rectText.deflate(m_iPadding);

#ifdef _DEBUG

         strItem += strDebug;

#endif

         pgraphics->draw_text(strItem, rectText);

      }

      color32_t crBorder = argb(255, 0, 0, 0);

      ::draw2d::pen_pointer pen(e_create);

      pen->create_solid(1.0, crBorder);

      pgraphics->set(pen);

      rectClient.deflate(0, 0, 1, 1);

      pgraphics->draw_rectangle(rectClient);

   }


   ::write_text::font_pointer combo_list::get_font(style *pstyle, enum_element eelement, ::user::enum_state estate) const
   {

      if (m_pcombo)
      {

         auto pfont = m_pcombo->get_font(pstyle, eelement, estate);

         if (pfont)
         {

            return pfont;

         }

      }

      return ::user::interaction::get_font(pstyle, eelement, estate);

   }


   void combo_list::query_full_size(::draw2d::graphics_pointer& pgraphics, SIZE_I32 * psize)
   {

      sync_lock sl(mutex());

      pgraphics->set_font(this, ::user::e_element_none);

      pgraphics->set_text_rendering_hint(::write_text::e_rendering_anti_alias);

      string strItem;

      ::size_f64 size;

      psize->cx = 0;

      m_dItemHeight = 0.;

      ::count cListCount = m_pcombo->_001GetListCount();

      for (index i = 0; i < cListCount; i++)
      {

         m_pcombo->_001GetListText(i, strItem);

         size = pgraphics->GetTextExtent(strItem);

         size.cx += m_iPadding * 2;

         if (size.cx > psize->cx)
         {

            psize->cx = (::i32)size.cx;

         }

         if (size.cy > m_dItemHeight)
         {

            m_dItemHeight = (::i32)size.cy;

            if (size.cy != 18)
            {

               //output_debug_string("\nCOMBO LIST ITEM HEIGHT != 18\n");

            }

         }

      }

      m_dItemHeight += 4.0;

      int iAddUp = 0;

      if (m_pcombo->m_bEdit)
      {

         iAddUp = 1;

      }

      if (m_iMinListItemCount > 0)
      {

         auto iAddUp2 = cListCount - m_iMinListItemCount;

         if (iAddUp2 > 0)
         {

            iAddUp = (decltype(iAddUp))iAddUp2;

         }

      }

      psize->cy = (::i32)(_001GetItemHeight() * (m_pcombo->_001GetListCount() + iAddUp));

      psize->cx += m_iBorder * 2;

      auto rectComboClient = m_pcombo->get_client_rect();

      psize->cx = max(psize->cx, rectComboClient.width());

   }


   void combo_list::on_change_combo_sel(index iSel)
   {

   }


   i32 combo_list::_001GetItemHeight() const
   {

      return (::i32)(m_dItemHeight + m_iPadding * 2);

   }


   void combo_list::_001EnsureVisible(index iItem)
   {

      if (m_pscrollbarVertical != nullptr
         && m_scrolldataVertical.m_bScroll
         && iItem >= 0 && iItem < m_pcombo->_001GetListCount())
      {

         m_pointScroll.y = (::i32) (iItem * _001GetItemHeight());

      }
      else
      {

         m_pointScroll.y = 0;

      }

   }


   void combo_list::_001OnTimer(::timer* ptimer)
   {
   
      if (ptimer->m_etimer == e_timer_kill_focus)
      {

         if (m_bPendingKillFocusHiding)
         {
            
            m_bPendingKillFocusHiding = false;

            hide();

            set_need_redraw();

            post_redraw();


         }

         KillTimer(e_timer_kill_focus);

      }

      ::user::scroll_base::_001OnTimer(ptimer);
   
   }


   bool combo_list::keyboard_focus_is_focusable() const
   {

      return true;

   }


   bool combo_list::keyboard_focus_OnKillFocus(oswindow oswindowNew)
   {

      if (is_window_visible(::user::e_layout_sketch))
      {

         display(e_display_hide);

         set_need_redraw();

         post_redraw();

         if (m_pcombo != nullptr && m_pcombo->is_window_visible(::user::e_layout_sketch))
         {

            m_pcombo->set_keyboard_focus();

         }

      }

      return true;

   }


   bool combo_list::pre_create_window(::user::system * pusersystem)
   {

//#ifdef WINDOWS_DESKTOP
//
//      if (pusersystem->m_createstruct.style & WS_BORDER)
//      {
//
//         pusersystem->m_createstruct.style &= ~WS_BORDER;
//
//      }
//
//      pusersystem->m_createstruct.dwExStyle |= WS_EX_TOOLWINDOW;
//
//      pusersystem->m_createstruct.dwExStyle |= WS_EX_TOPMOST;
//
//#endif
//
//      pusersystem->m_createstruct.dwExStyle |= WS_EX_LAYERED;
      
      //pusersystem->m_createstruct.dwExStyle |= WS_EX_NOACTIVATE;

      return true;

   }


   void combo_list::_001OnShowWindow(::message::message * pmessage)
   {

      __pointer(::message::show_window) pshowwindow(pmessage);

      if (pshowwindow->m_bShow)
      {

#ifdef WINDOWS

         set_keyboard_focus();

#endif

      }
      else
      {

         output_debug_string("combo_list hide");

      }

   }


   void combo_list::_001OnKillFocus(::message::message * pmessage)
   {

      if (m_pcombo)
      {

         bool bGoingToShow = m_pcombo->m_millisShowComboList.elapsed() < 300_ms;

         if (!bGoingToShow)
         {

            m_millisKillFocus.Now();

            m_bPendingKillFocusHiding = true;

            set_timer(e_timer_kill_focus, 300_ms);

            //__pointer(::message::kill_focus) pkillfocus(pmessage);

            //oswindow oswindowThis = get_safe_handle();

            //oswindow oswindowNew = pkillfocus->m_oswindowNew;

            //if (oswindowThis != oswindowNew && !m_bMovingComboBox)
            //{

            //   if (layout().sketch().is_screen_visible())
            //   {

            //      m_millisLastVisibilityChange.Now();

            //      hide();

            //      set_need_redraw();

            //      post_redraw();

            //      m_pcombo->keyboard_set_focus();

            //      m_pcombo->get_wnd()->SetActiveWindow();

            //   }
            //   else
            //   {

            //      //output_debug_string("A phantom is loosing focus. What a pitty!!");

            //   }

            //}

            //pkillfocus->m_bRet = true;

            //pkillfocus->m_lresult = 0;

         }

      }

   }


   void combo_list::_001OnSetFocus(::message::message * pmessage)
   {

      if (m_pcombo)
      {

         m_pcombo->m_itemHover = m_pcombo->m_itemCurrent;

         set_need_redraw();

      }

   }



   void combo_list::_001OnActivate(::message::message * pmessage)
   {

      __pointer(::message::activate) pactivate(pmessage);

      __pointer(::user::interaction) pActive = (pactivate->m_eactivate == e_activate_inactive ? pactivate->m_pWndOther : this);

      if (pactivate->m_eactivate == e_activate_inactive)
      {

         auto psession = Session;

         auto puser = psession->user();

         auto pwindowing = puser->windowing();

         auto pointCursor = pwindowing->get_cursor_pos();

         m_pcombo->_001ScreenToClient(&pointCursor, ::user::e_layout_sketch);

         //if(m_pcombo->hit_test(pointCursor) != e_element_drop_down)
         //{

         //   m_pcombo->_001ShowDropDown(false);

         //}




         //if(pActive != m_puiDeactivateTogether)
         //{

         //   ::experience::frame_window * pset = m_puiDeactivateTogetherSet;

         //   if(pset != nullptr)
         //   {

         //      pset->SetActiveFlag(false);

         //   }

         //}



      }
      else
      {

         set_keyboard_focus();


      }

   }


   void combo_list::_001OnMouseActivate(::message::message * pmessage)
   {

      __pointer(::message::mouse_activate) pactivate(pmessage);

      pactivate->m_lresult = MA_NOACTIVATE;

      pactivate->m_bRet = true;


   }


   void combo_list::_001OnKeyDown(::message::message * pmessage)
   {

      __pointer(::message::key) pkey(pmessage);

      if (pkey->m_ekey == ::user::e_key_escape)
      {

         m_pcombo->ShowDropDown(false);

      }
      else if (pkey->m_ekey == ::user::e_key_tab)
      {

         m_pcombo->ShowDropDown(false);

         __pointer(::user::primitive) pelemental = m_pcombo->keyboard_get_next_focusable();

         if (pelemental.is_set())
         {

            pelemental->set_keyboard_focus();

         }


      }
      else if (pkey->m_ekey == ::user::e_key_down)
      {

         m_pcombo->m_itemHover = min(m_pcombo->m_itemHover + 1, m_pcombo->_001GetListCount() - 1);

      }
      else if (pkey->m_ekey == ::user::e_key_up)
      {

         m_pcombo->m_itemHover = max(m_pcombo->m_itemHover - 1, 0);

      }
      else if (pkey->m_ekey == ::user::e_key_return)
      {

         m_pcombo->set_current_item(m_pcombo->m_itemHover, ::e_source_user);

         m_pcombo->ShowDropDown(false);

         __pointer(::user::primitive) pelemental = m_pcombo->keyboard_get_next_focusable();

         if (pelemental.is_set())
         {

            pelemental->set_keyboard_focus();

         }

      }

   }


   void combo_list::_001OnKeyUp(::message::message * pmessage)
   {

      UNREFERENCED_PARAMETER(pmessage);

   }


   void combo_list::_001OnLButtonDown(::message::message * pmessage)
   {

      __pointer(::message::mouse) pmouse(pmessage);

      auto point = screen_to_client(pmouse->m_point, e_layout_sketch);

      auto rectClient = get_client_rect();

      auto psession = Session;

      psession->user()->set_mouse_focus_LButtonDown(this);

      m_itemLButtonDown = -1;

      if (rectClient.contains(point))
      {

         m_itemLButtonDown = hit_test(pmouse);

         set_mouse_capture();

      }

      pmessage->m_bRet = true;

   }


   void combo_list::_001OnLButtonUp(::message::message * pmessage)
   {

      __pointer(::message::mouse) pmouse(pmessage);

      auto point = screen_to_client(pmouse->m_point, e_layout_sketch);

      auto rectClient = get_client_rect();

      auto psession = Session;

      psession->user()->set_mouse_focus_LButtonDown(this);

      auto puser = psession->user();

      auto pwindowing = puser->windowing();

      pwindowing->release_capture();

      if (rectClient.contains(point))
      {

         auto itemHit = hit_test(pmouse);

         if (itemHit == m_itemLButtonDown)
         {

            if (::is_set(m_pcombo))
            {

               m_pcombo->_001ShowDropDown(false);

            }

            ::user::control_event ev;

            ev.m_puie = this;

            ev.m_id = m_id;

            ev.m_eevent = ::user::e_event_after_change_cur_sel;

            ev.m_actioncontext = ::e_source_user;

            ev.m_item = itemHit;

            route_control_event(&ev);

         }

      }



      pmouse->m_bRet = true;

   }


   void combo_list::_001OnMButtonDown(::message::message * pmessage)
   {

      __pointer(::message::mouse) pmouse(pmessage);

      auto point = pmouse->m_point;

      _001ScreenToClient(point, e_layout_sketch);

      auto rectClient = get_client_rect();

      if (rectClient.contains(point))
      {

      }
      else
      {

         m_pcombo->_001ShowDropDown(false);

      }

      pmessage->m_bRet = true;

   }


   void combo_list::_001OnRButtonDown(::message::message * pmessage)
   {

      __pointer(::message::mouse) pmouse(pmessage);

      auto point = pmouse->m_point;

      _001ScreenToClient(point, e_layout_sketch);

      auto rectClient = get_client_rect();

      if (rectClient.contains(point))
      {

      }
      else
      {

         m_pcombo->_001ShowDropDown(false);

      }

      pmessage->m_bRet = true;

   }


   void combo_list::_001OnMouseMove(::message::message * pmessage)
   {

      UNREFERENCED_PARAMETER(pmessage);
      //__pointer(::message::mouse) pmouse(pmessage);

      //pmessage->m_bRet = true;

      //auto point = screen_to_client(pmouse->m_point);

      //auto itemHover = hit_test(pmouse);

      //if (itemHover != m_pcombo->m_itemHover)
      //{

      //   m_pcombo->m_itemHover = itemHover.m_iItem;

      //   set_need_redraw();

      //}

   }


   void combo_list::_001OnClose(::message::message * pmessage)
   {

      pmessage->m_bRet = true;

      display(e_display_none);

      set_need_redraw();

   }


   item combo_list::current_item()
   {

      return m_pcombo->current_item();

   }


   item combo_list::hover_item()
   {

      return ::user::interaction::hover_item();

   }


   void combo_list::on_hit_test(::user::item & item)
   {

      if (m_pcombo == nullptr)
      {

         item = ::user::e_element_none;

         return;

      }

      ::count iItemCount = m_pcombo->_001GetListCount();

      auto rectClient = get_client_rect();

      ::rectangle_i32 rectItem = rectClient;

      int iAddUp = 0;

      if (m_pcombo->m_bEdit)
      {

         iAddUp = 1;

      }

      for (::index iItem = 0; iItem < iItemCount; iItem++)
      {

         rectItem.top = rectClient.top + (_001GetItemHeight() * (int) (iAddUp + iItem));

         rectItem.bottom = rectItem.top + _001GetItemHeight();

         if (rectItem.contains(item.m_pointHitTest))
         {

            item  = {::user::e_element_item, iItem };

            return;

         }


      }

      rectItem.top = rectClient.top;

      rectItem.bottom = rectItem.top + _001GetItemHeight();

      if (rectItem.contains(item.m_pointHitTest))
      {

         item = e_element_search_edit;

         return;

      }

      item = e_element_none;

   }


   bool combo_list::has_pending_graphical_update()
   {

      return m_bNeedRedraw;

   }


   void combo_list::on_drop_down(const ::rectangle_i32 & rectWindow, const ::size_i32 & sizeFull)
   {

      ::rectangle_i32 rectMonitor;

      auto psession = Session;

      auto puser = psession->user();

      auto pwindowing = puser->windowing();

      auto pdisplay = pwindowing->display();

      ::index i = pdisplay->get_best_monitor(rectMonitor, rectWindow);

      ::rectangle_i32 rectList;

      rectList.left = rectWindow.left;
      rectList.right = rectWindow.left + max(rectWindow.width(), sizeFull.cx);
      rectList.top = rectWindow.bottom;
      rectList.bottom = rectWindow.bottom + sizeFull.cy;

      if (i < 0)
      {

         m_pcombo->get_parent()->get_window_rect(rectMonitor);

      }

      if (rectList.bottom > rectMonitor.bottom - m_iBorder)
      {

         rectList.bottom = rectMonitor.bottom - m_iBorder;

         ::rectangle_i32 rectListOver;

         rectListOver.left = rectList.left;
         rectListOver.right = rectList.right;
         rectListOver.bottom = rectWindow.top;
         rectListOver.top = rectWindow.top - sizeFull.cy;

         if (rectListOver.top < rectMonitor.top + m_iBorder)
         {

            rectListOver.move_to(rectListOver.left, rectMonitor.top);

         }

         rectList = rectListOver;

      }

      if (rectList.right > rectMonitor.right - m_iBorder)
      {

         rectList.offset(rectMonitor.right - (rectList.right - m_iBorder), 0);

      }

      if (rectList.left < rectMonitor.left)
      {

         rectList.move_left_to(0);

      }

      m_pcombo->m_itemHover = current_item();

      if (!m_pcombo->m_itemHover.is_set())
      {

         m_pcombo->m_itemHover = 0;

      }

      _001EnsureVisible(m_pcombo->m_itemHover);

      if (i < 0)
      {

         m_pcombo->get_parent()->_001ScreenToClient(rectList);

      }

      if (!is_window())
      {

         //auto pusersystem = __new(::user::system(0, nullptr, "combo_list", i >= 0 ? 0 : WS_CHILD));

         m_puserinteractionOwner = m_pcombo;

         order_top_most();

         set_tool_window();

         m_bTransparent = true;

         display();

         place(::rectangle_i32(rectList).inflate(m_iBorder));

         if (!create_interaction(i >= 0 ? nullptr : m_pcombo->get_parent()))
         //if(!create_host())
         {

            m_pcombo->m_plist.release();

            __throw(resource_exception());

         }

         set_owner(m_pcombo);

      }
      else
      {

         place(::rectangle_i32(rectList).inflate(m_iBorder));

      }

      order_top_most();

      display(e_display_normal);

      set_need_redraw();

      set_layout_ready();

      post_redraw();

   }


   void combo_list::_on_show_window()
   {

      ::user::interaction::_on_show_window();

      if (is_screen_visible(layout().sketch().display()))
      {

         {

            auto psession = Session;

            sync_lock sl(psession->mutex());

            auto pinteraction = __create_new < ::user::interaction >();

            auto puser = User;

            puser->m_uiptraToolWindow.add(pinteraction);

         }

         set_keyboard_focus();

      }
      else
      {

         {

            auto psession = Session;

            sync_lock sl(psession->mutex());

            auto puser = User;

            ::index iFind = puser->m_uiptraToolWindow.pred_find_first([this](auto& p) {return p.get() == this; });

            if (__found(iFind))
            {

               auto puser = User;

               puser->m_uiptraToolWindow.remove_at(iFind);

            }

         }

      }

   }



} // namespace user




