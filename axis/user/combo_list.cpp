#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "axis/user/_user.h"
#endif
#include "aura/const/timer.h"


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

      m_bPendingKillFocusHiding = false;

      m_ewindowflag += window_flag_satellite_window;

      m_ewindowflag += window_flag_arbitrary_positioning;

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

      IGUI_MSG_LINK(WM_SETFOCUS, pchannel, this, &combo_list::_001OnSetFocus);
      IGUI_MSG_LINK(WM_KILLFOCUS, pchannel, this, &combo_list::_001OnKillFocus);
      IGUI_MSG_LINK(WM_CLOSE, pchannel, this, &combo_list::_001OnClose);
      IGUI_MSG_LINK(WM_MOUSEACTIVATE, pchannel, this, &combo_list::_001OnMouseActivate);
      IGUI_MSG_LINK(WM_KEYDOWN, pchannel, this, &combo_list::_001OnKeyDown);
      IGUI_MSG_LINK(WM_KEYUP, pchannel, this, &combo_list::_001OnKeyUp);
      IGUI_MSG_LINK(WM_LBUTTONDOWN, pchannel, this, &combo_list::_001OnLButtonDown);
      IGUI_MSG_LINK(WM_NCLBUTTONDOWN, pchannel, this, &combo_list::_001OnLButtonDown);
      IGUI_MSG_LINK(WM_LBUTTONUP, pchannel, this, &combo_list::_001OnLButtonUp);
      IGUI_MSG_LINK(WM_MBUTTONDOWN, pchannel, this, &combo_list::_001OnMButtonDown);
      IGUI_MSG_LINK(WM_RBUTTONDOWN, pchannel, this, &combo_list::_001OnRButtonDown);
      IGUI_MSG_LINK(WM_MOUSEMOVE, pchannel, this, &combo_list::_001OnMouseMove);
      IGUI_MSG_LINK(WM_SHOWWINDOW, pchannel, this, &combo_list::_001OnShowWindow);

   }


   void combo_list::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      ::draw2d::savedc savedc(pgraphics);

      if (m_pcombo == nullptr)
      {

         return;

      }

      ::rect rectClipBox;

      pgraphics->GetClipBox(rectClipBox);

      pgraphics->SelectClipRgn(nullptr);

      _001OnDrawComboList(pgraphics);

   }


   void combo_list::_001OnDrawComboList(::draw2d::graphics_pointer & pgraphics)
   {

      ::count iListItemCount = m_pcombo->_001GetListCount();

      string strItem;

      ::rect rectClient;

      layout().get_client_rect(rectClient, ::user::layout_design);

      ::draw2d::brush_pointer brBk(e_create);

      brBk->create_solid(ARGB(230, 255, 255, 255));

      pgraphics->set(brBk);

      pgraphics->fill_rect(rectClient);

      ::rect rectItem;

      //point p = pgraphics->GetViewportOrg();

      rectItem = rectClient;

      rectItem.bottom = rectClient.top;

      if (m_pcombo->m_bEdit)
      {

         rectItem.bottom += _001GetItemHeight();

      }

      auto pointCursor = Session.get_cursor_pos();

      _001ScreenToClient(&pointCursor, ::user::layout_design);

      pgraphics->set_font(this);

      auto itemHover = hover_item();

      index iCurSel = current_item();

      ::draw2d::brush_pointer br(e_create);

      for (index iItem = 0; iItem < iListItemCount; iItem++)
      {

         rectItem.top = rectItem.bottom;

         rectItem.bottom = rectItem.top + _001GetItemHeight();

         COLORREF crBk;

         COLORREF cr;

         string strDebug;

         if (itemHover == iItem)
         {

            strDebug += "hover;";

            if (iItem == iCurSel)
            {

               //crBk = _001GetColor(::user::color_list_item_background_selected_hover);

               //cr = _001GetColor(::user::color_list_item_text_selected_hover);

               crBk = ARGB(255, 120, 190, 220);

               cr = ARGB(255, 255, 255, 255);

               strDebug += "sel;";

            }
            else
            {

               crBk = ARGB(255, 235, 245, 255);

               cr = ARGB(255, 0, 0, 0);

            }

         }
         else if (iItem == iCurSel)
         {

            strDebug += "sel;";

            crBk = ARGB(255, 120, 150, 190);

            cr = ARGB(255, 255, 255, 255);

         }
         else
         {

            crBk = ARGB(255, 255, 255, 255);

            cr = ARGB(255, 0, 0, 0);

         }

         brBk->create_solid(crBk);

         br->create_solid(cr);

         pgraphics->set(brBk);

         pgraphics->fill_rect(rectItem);

         m_pcombo->_001GetListText(iItem, strItem);

         pgraphics->set(br);

         auto rectText = rectItem;

         rectText.deflate(m_iPadding);

#ifdef _DEBUG

         strItem += strDebug;

#endif

         pgraphics->draw_text(strItem, rectText, 0);

      }

      //COLORREF crBorder = _001GetColor(::user::color_border);

      COLORREF crBorder = ARGB(255, 0, 0, 0);

      ::draw2d::pen_pointer pen(e_create);

      pen->create_solid(1.0, crBorder);

      pgraphics->set(pen);

      rectClient.deflate(0, 0, 1, 1);

      pgraphics->draw_rect(rectClient);

   }


   ::draw2d::font_pointer combo_list::get_font(style *pstyle, e_element eelement, estate estate) const
   {

      if (m_pcombo)
      {

         auto pfont = m_pcombo->get_font(pstyle, eelement, estate);

         if (pfont)
         {

            return pfont;

         }

      }

      //if (pstyle)
      //{

      //   if (pstyle->m_pfontCombo)
      //   {

      //      return pstyle->m_pfontCombo;

      //   }
      //   else if (pstyle->m_pfont)
      //   {

      //      return pstyle->m_pfont;

      //   }

      //}

      //return nullptr;

      return ::user::interaction::get_font(pstyle, eelement, estate);

   }


   void combo_list::query_full_size(::draw2d::graphics_pointer& pgraphics, LPSIZE psize)
   {

      sync_lock sl(mutex());

      pgraphics->set_font(this);

      pgraphics->set_text_rendering_hint(::draw2d::text_rendering_hint_anti_alias);

      string strItem;

      ::size size;

      psize->cx = 0;

      m_iItemHeight = 0;

      ::count cListCount = m_pcombo->_001GetListCount();

      for (index i = 0; i < cListCount; i++)
      {

         m_pcombo->_001GetListText(i, strItem);

         size = pgraphics->GetTextExtent(strItem);

         size.cx += m_iPadding * 2;

         if (size.cx > psize->cx)
         {

            psize->cx = size.cx;

         }

         if (size.cy > m_iItemHeight)
         {

            m_iItemHeight = size.cy;

            if (size.cy != 18)
            {

               //output_debug_string("\nCOMBO LIST ITEM HEIGHT != 18\n");

            }

         }

      }

      m_iItemHeight += 4;

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

      psize->cy = (LONG)(_001GetItemHeight() * (m_pcombo->_001GetListCount() + iAddUp));

      psize->cx += m_iBorder * 2;

      auto rectComboClient = m_pcombo->get_client_rect();

      psize->cx = MAX(psize->cx, rectComboClient.width());

   }


   void combo_list::on_change_combo_sel(index iSel)
   {

   }


   i32 combo_list::_001GetItemHeight() const
   {

      return m_iItemHeight + m_iPadding * 2;

   }


   void combo_list::_001EnsureVisible(index iItem)
   {

      if (m_pscrollbarVert != nullptr
         && m_scrolldataVert.m_bScroll
         && iItem >= 0 && iItem < m_pcombo->_001GetListCount())
      {

         m_pointScroll.y = (LONG) (iItem * _001GetItemHeight());

      }
      else
      {

         m_pointScroll.y = 0;

      }

   }


   void combo_list::_001OnTimer(::timer* ptimer)
   {
   
      if (ptimer->m_etimer == timer_kill_focus)
      {

         if (m_bPendingKillFocusHiding)
         {
            
            m_bPendingKillFocusHiding = false;

            hide();

            set_need_redraw();

            post_redraw();


         }

         KillTimer(timer_kill_focus);

      }

      ::user::scroll_base::_001OnTimer(ptimer);
   
   }

   bool combo_list::keyboard_focus_is_focusable()
   {

      return true;

   }


   bool combo_list::keyboard_focus_OnKillFocus(oswindow oswindowNew)
   {

      if (is_window_visible(::user::layout_sketch))
      {

         display(false);

         set_need_redraw();

         post_redraw();

         if (m_pcombo != nullptr && m_pcombo->is_window_visible(::user::layout_sketch))
         {

            m_pcombo->SetFocus();

         }

      }

      return true;

   }


   bool combo_list::pre_create_window(::user::create_struct & cs)
   {

      if (cs.style & WS_BORDER)
      {
#ifdef WINDOWS_DESKTOP
         cs.dwExStyle |= WS_EX_CLIENTEDGE;
#endif
         cs.style &= ~WS_BORDER;
      }

      cs.dwExStyle |= WS_EX_LAYERED;
      cs.dwExStyle |= WS_EX_TOOLWINDOW;
      cs.dwExStyle |= WS_EX_TOPMOST;
      //cs.dwExStyle |= WS_EX_NOACTIVATE;

      return TRUE;
   }


   void combo_list::_001OnShowWindow(::message::message * pmessage)
   {

      SCAST_PTR(::message::show_window, pshowwindow, pmessage);

      if (pshowwindow->m_bShow)
      {

#ifdef WINDOWS

         keyboard_set_focus();

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

         m_tickKillFocus.Now();

         m_bPendingKillFocusHiding = true;

         set_timer(timer_kill_focus, 300_ms);

         //SCAST_PTR(::message::kill_focus, pkillfocus, pmessage);

         //oswindow oswindowThis = get_safe_handle();

         //oswindow oswindowNew = pkillfocus->m_oswindowNew;

         //if (oswindowThis != oswindowNew && !m_bMovingComboBox)
         //{

         //   if (layout().sketch().is_screen_visible())
         //   {

         //      m_tickLastVisibilityChange.Now();

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

      SCAST_PTR(::message::activate, pactivate, pmessage);

      __pointer(::user::interaction) pActive = (pactivate->m_nState == WA_INACTIVE ? pactivate->m_pWndOther : this);

      if (pactivate->m_nState == WA_INACTIVE)
      {

         auto pointCursor = Session.get_cursor_pos();

         m_pcombo->_001ScreenToClient(&pointCursor, ::user::layout_sketch);

         //if(m_pcombo->hit_test(pointCursor) != element_drop_down)
         //{

         //   m_pcombo->_001ShowDropDown(false);

         //}




         //if(pActive != m_puiDeactivateTogether)
         //{

         //   ::experience::frame_window * pset = m_puiDeactivateTogetherSet;

         //   if(pset != nullptr)
         //   {

         //      pset->SetActiveFlag(FALSE);

         //   }

         //}



      }
      else
      {

         Session.set_keyboard_focus(this);


      }

   }


   void combo_list::_001OnMouseActivate(::message::message * pmessage)
   {

      SCAST_PTR(::message::mouse_activate, pactivate, pmessage);

      pactivate->m_lresult = MA_NOACTIVATE;

      pactivate->m_bRet = true;


   }


   void combo_list::_001OnKeyDown(::message::message * pmessage)
   {

      SCAST_PTR(::message::key, pkey, pmessage);

      if (pkey->m_ekey == ::user::key_escape)
      {

         m_pcombo->ShowDropDown(false);

      }
      else if (pkey->m_ekey == ::user::key_tab)
      {

         m_pcombo->ShowDropDown(false);

         __pointer(::user::primitive) pelemental = m_pcombo->keyboard_get_next_focusable();

         if (pelemental.is_set())
         {

            pelemental->keyboard_set_focus();

         }


      }
      else if (pkey->m_ekey == ::user::key_down)
      {

         m_pcombo->m_itemHover = MIN(m_pcombo->m_itemHover + 1, m_pcombo->_001GetListCount() - 1);

      }
      else if (pkey->m_ekey == ::user::key_up)
      {

         m_pcombo->m_itemHover = MAX(m_pcombo->m_itemHover - 1, 0);

      }
      else if (pkey->m_ekey == ::user::key_return)
      {

         m_pcombo->set_current_item(m_pcombo->m_itemHover, ::source_user);

         m_pcombo->ShowDropDown(false);

         __pointer(::user::primitive) pelemental = m_pcombo->keyboard_get_next_focusable();

         if (pelemental.is_set())
         {

            pelemental->keyboard_set_focus();

         }

      }

   }


   void combo_list::_001OnKeyUp(::message::message * pmessage)
   {

      UNREFERENCED_PARAMETER(pmessage);

   }


   void combo_list::_001OnLButtonDown(::message::message * pmessage)
   {

      SCAST_PTR(::message::mouse, pmouse, pmessage);

      auto point = screen_to_client(pmouse->m_point, layout_sketch);

      auto rectClient = get_client_rect();

      Session.user()->set_mouse_focus_LButtonDown(this);

      m_itemLButtonDown = -1;

      if (rectClient.contains(point))
      {

         m_itemLButtonDown = hit_test(pmouse);

         SetCapture();

      }

      pmessage->m_bRet = true;

   }


   void combo_list::_001OnLButtonUp(::message::message * pmessage)
   {

      SCAST_PTR(::message::mouse, pmouse, pmessage);

      auto point = screen_to_client(pmouse->m_point, layout_sketch);

      auto rectClient = get_client_rect();

      Session.user()->set_mouse_focus_LButtonDown(this);

      ReleaseCapture();

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

            ev.m_eevent = ::user::event_after_change_cur_sel;

            ev.m_actioncontext = ::source_user;

            ev.m_item = itemHit;

            route_control_event(&ev);

         }

      }



      pmouse->m_bRet = true;

   }


   void combo_list::_001OnMButtonDown(::message::message * pmessage)
   {

      SCAST_PTR(::message::mouse, pmouse, pmessage);

      auto point = pmouse->m_point;

      _001ScreenToClient(point, layout_sketch);

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

      SCAST_PTR(::message::mouse, pmouse, pmessage);

      auto point = pmouse->m_point;

      _001ScreenToClient(point, layout_sketch);

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
      //SCAST_PTR(::message::mouse, pmouse, pmessage);

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

      display(display_none);

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

         item = ::user::element_none;

         return;

      }

      ::count iItemCount = m_pcombo->_001GetListCount();

      auto rectClient = get_client_rect();

      ::rect rectItem = rectClient;

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

            item  = {::user::element_item, iItem };

            return;

         }


      }

      rectItem.top = rectClient.top;

      rectItem.bottom = rectItem.top + _001GetItemHeight();

      if (rectItem.contains(item.m_pointHitTest))
      {

         item = element_search_edit;

         return;

      }

      item = element_none;

   }


   bool combo_list::has_pending_graphical_update()
   {

      return m_bNeedRedraw;

   }


   void combo_list::on_drop_down(const ::rect & rectWindow, const ::size & sizeFull)
   {

      ::rect rectMonitor;

      Session.get_best_monitor(rectMonitor, rectWindow);

      ::rect rectList;

      rectList.left = rectWindow.left;
      rectList.right = rectWindow.left + MAX(rectWindow.width(), sizeFull.cx);
      rectList.top = rectWindow.bottom;
      rectList.bottom = rectWindow.bottom + sizeFull.cy;

      if (rectList.bottom > rectMonitor.bottom -m_iBorder)
      {

         rectList.bottom = rectMonitor.bottom - m_iBorder;

         ::rect rectListOver;

         rectListOver.left = rectWindow.left;
         rectListOver.right = rectWindow.left + sizeFull.cx;
         rectListOver.bottom = rectWindow.top;
         rectListOver.top = rectWindow.top - sizeFull.cy;

         if (rectListOver.top < rectMonitor.top + m_iBorder)
         {

            rectListOver.top = rectMonitor.top + m_iBorder;

            if (rectListOver.height() > rectList.height())
            {

               rectList = rectListOver;

            }

         }

      }

      if (rectList.right > rectMonitor.right - m_iBorder)
      {

         rectList.offset(rectMonitor.right - (rectList.right-m_iBorder), 0);

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

      if (!is_window())
      {

         ::user::create_struct createstruct(0, nullptr, "combo_list");

         createstruct.set_rect(::rect(rectList).inflate(m_iBorder));

         if (!create_window_ex(createstruct))
         {

            m_pcombo->m_plist.release();

            __throw(resource_exception());

         }

         SetOwner(m_pcombo);

      }
      else
      {

         place(::rect(rectList).inflate(m_iBorder));

      }

      order_top_most();

      display(display_normal);

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

            sync_lock sl(Session.mutex());

            auto & preference = Session.m_uiptraToolWindow.add_new();

            Session.__refer(preference, this);

         }

         keyboard_set_focus();

      }
      else
      {

         {

            sync_lock sl(Session.mutex());

            ::index iFind = Session.m_uiptraToolWindow.pred_find_first([this](auto& p) {return p.get() == this; });

            if (__found(iFind))
            {

               Session.__release(Session.m_uiptraToolWindow[iFind]);

               Session.m_uiptraToolWindow.remove_at(iFind);

            }

         }

      }

   }



} // namespace user




