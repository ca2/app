#include "framework.h"
#include "axis/user/_user.h"
#include "acme/constant/timer.h"


namespace user
{


   list_box::list_box()
   {

      user_combo_list_common_construct();

   }


   list_box::~list_box()
   {

   }


   void list_box::user_combo_list_common_construct()
   {

      defer_create_mutex();

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


   void list_box::install_message_routing(::channel * pchannel)
   {

      ::user::scroll_base::install_message_routing(pchannel);

      install_simple_ui_default_mouse_handling(pchannel);

      MESSAGE_LINK(e_message_set_focus, pchannel, this, &list_box::_001OnSetFocus);
      MESSAGE_LINK(e_message_kill_focus, pchannel, this, &list_box::_001OnKillFocus);
      MESSAGE_LINK(e_message_close, pchannel, this, &list_box::on_message_close);
      MESSAGE_LINK(e_message_mouse_activate, pchannel, this, &list_box::_001OnMouseActivate);
      MESSAGE_LINK(e_message_key_down, pchannel, this, &list_box::on_message_key_down);
      MESSAGE_LINK(e_message_key_up, pchannel, this, &list_box::on_message_key_up);
      MESSAGE_LINK(e_message_left_button_down, pchannel, this, &list_box::on_message_left_button_down);
      MESSAGE_LINK(e_message_non_client_left_button_down, pchannel, this, &list_box::on_message_left_button_down);
      MESSAGE_LINK(e_message_left_button_up, pchannel, this, &list_box::on_message_left_button_up);
      MESSAGE_LINK(e_message_middle_button_down, pchannel, this, &list_box::on_message_middle_button_down);
      MESSAGE_LINK(e_message_right_button_down, pchannel, this, &list_box::on_message_right_button_down);
      MESSAGE_LINK(e_message_mouse_move, pchannel, this, &list_box::on_message_mouse_move);
      MESSAGE_LINK(e_message_show_window, pchannel, this, &list_box::on_message_show_window);

   }


   void list_box::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      ::draw2d::savedc savedc(pgraphics);

      if (m_pcombo == nullptr)
      {

         return;

      }

      ::rectangle rectangleClipBox;

      pgraphics->get_clip_box(rectangleClipBox);

      pgraphics->SelectClipRgn(nullptr);

      _001OnDrawComboList(pgraphics);

   }


   void list_box::_001OnDrawComboList(::draw2d::graphics_pointer & pgraphics)
   {

      ::count iListItemCount = m_pcombo->_001GetListCount();

      string strItem;

      ::rectangle rectangleClient;

      layout().get_client_rect(rectangleClient, ::user::e_layout_design);

      auto pbrushBk = __create < ::draw2d::brush > ();

      pbrushBk->create_solid(argb(230, 255, 255, 255));

      pgraphics->set(pbrushBk);

      pgraphics->fill_rectangle(rectangleClient);

      ::rectangle rectangleItem;

      //point p = pgraphics->GetViewportOrg();

      rectangleItem = rectangleClient;

      rectangleItem.bottom = rectangleClient.top;

      if (m_pcombo->m_bEdit)
      {

         rectangleItem.bottom += _001GetItemHeight();

      }

      auto pointCursor = psession->get_cursor_position();

      screen_to_client(&pointCursor, ::user::e_layout_design);

      pgraphics->set_font(this, ::e_element_none);

      auto itemHover = hover_item();

      index iCurSel = current_item();

      auto pbrush = __create < ::draw2d::brush > ();

      for (index iItem = 0; iItem < iListItemCount; iItem++)
      {

         rectangleItem.top = rectangleItem.bottom;

         rectangleItem.bottom = rectangleItem.top + _001GetItemHeight();

         color32_t crBk;

         color32_t color32;

         string strDebug;

         if (itemHover == iItem)
         {

            strDebug += "hover;";

            if (iItem == iCurSel)
            {

               //crBk = _001GetColor(::user::color_list_item_background_selected_hover);

               //color32 = _001GetColor(::user::color_list_item_text_selected_hover);

               crBk = argb(255, 120, 190, 220);

               color32 = argb(255, 255, 255, 255);

               strDebug += "sel;";

            }
            else
            {

               crBk = argb(255, 235, 245, 255);

               color32 = argb(255, 0, 0, 0);

            }

         }
         else if (iItem == iCurSel)
         {

            strDebug += "sel;";

            crBk = argb(255, 120, 150, 190);

            color32 = argb(255, 255, 255, 255);

         }
         else
         {

            crBk = argb(255, 255, 255, 255);

            color32 = argb(255, 0, 0, 0);

         }

         pbrushBk->create_solid(crBk);

         pbrush->create_solid(color32);

         pgraphics->set(pbrushBk);

         pgraphics->fill_rectangle(rectangleItem);

         m_pcombo->_001GetListText(iItem, strItem);

         pgraphics->set(pbrush);

         auto rectangleText = rectangleItem;

         rectangleText.deflate(m_iPadding);

#ifdef _DEBUG

         strItem += strDebug;

#endif

         pgraphics->draw_text(strItem, rectangleText, 0);

      }

      //color32_t crBorder = _001GetColor(::user::color_border);

      color32_t crBorder = argb(255, 0, 0, 0);

      auto ppen = __create < ::draw2d::pen > ();

      ppen->create_solid(1.0, crBorder);

      pgraphics->set(ppen);

      rectangleClient.deflate(0, 0, 1, 1);

      pgraphics->draw_rectangle(rectangleClient);

   }


   ::write_text::font_pointer list_box::get_font(style *pstyle, enum_element eelement, estate estate) const
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


   void list_box::query_full_size(::draw2d::graphics_pointer& pgraphics, LPSIZE32 psize)
   {

      synchronous_lock synchronouslock(mutex());

      pgraphics->set_font(this, ::e_element_none);

      pgraphics->set_text_rendering_hint(::write_text::e_rendering_anti_alias);

      string strItem;

      ::size size;

      psize->cx = 0;

      m_iItemHeight = 0;

      ::count cListCount = m_pcombo->_001GetListCount();

      for (index i = 0; i < cListCount; i++)
      {

         m_pcombo->_001GetListText(i, strItem);

         size = pgraphics->get_text_extent(strItem);

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

      psize->cy = (::i32)(_001GetItemHeight() * (m_pcombo->_001GetListCount() + iAddUp));

      psize->cx += m_iBorder * 2;

      auto rectangleComboClient = m_pcombo->get_client_rect();

      psize->cx = maximum(psize->cx, rectangleComboClient.width());

   }


   void list_box::on_change_combo_sel(index iSel)
   {

   }


   i32 list_box::_001GetItemHeight() const
   {

      return m_iItemHeight + m_iPadding * 2;

   }


   void list_box::_001EnsureVisible(index iItem)
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


   void list_box::_001OnTimer(::timer* ptimer)
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

   bool list_box::keyboard_focus_is_focusable()
   {

      return true;

   }


   bool list_box::keyboard_focus_OnKillFocus(oswindow oswindowNew)
   {

      if (is_window_visible(::user::e_layout_sketch))
      {

         display(false);

         set_need_redraw();

         post_redraw();

         if (m_pcombo != nullptr && m_pcombo->is_window_visible(::user::e_layout_sketch))
         {

            m_pcombo->SetFocus();

         }

      }

      return true;

   }


   bool list_box::pre_create_window(::user::system * pusersystem)
   {

      if (pusersystem->m_createstruct.style & WS_BORDER)
      {

         pusersystem->m_createstruct.style &= ~WS_BORDER;

      }

      pusersystem->m_createstruct.dwExStyle |= WS_EX_LAYERED;
      pusersystem->m_createstruct.dwExStyle |= WS_EX_TOOLWINDOW;
      pusersystem->m_createstruct.dwExStyle |= WS_EX_TOPMOST;
      //pusersystem->m_createstruct.dwExStyle |= WS_EX_NOACTIVATE;

      return true;
   }


   void list_box::on_message_show_window(::message::message * pmessage)
   {

      __pointer(::message::show_window) pshowwindow(pmessage);

      if (pshowwindow->m_bShow)
      {

#ifdef WINDOWS

         keyboard_set_focus();

#endif

      }
      else
      {

         output_debug_string("list_box hide");

      }

   }


   void list_box::_001OnKillFocus(::message::message * pmessage)
   {

      if (m_pcombo)
      {

         m_durationKillFocus.Now();

         m_bPendingKillFocusHiding = true;

         set_timer(e_timer_kill_focus, 300_ms);

         //__pointer(::message::kill_focus) pkillfocus(pmessage);

         //oswindow oswindowThis = get_safe_handle();

         //oswindow oswindowNew = pkillfocus->m_oswindowNew;

         //if (oswindowThis != oswindowNew && !m_bMovingComboBox)
         //{

         //   if (layout().sketch().is_screen_visible())
         //   {

         //      m_durationLastVisibilityChange.Now();

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


   void list_box::_001OnSetFocus(::message::message * pmessage)
   {

      if (m_pcombo)
      {

         m_pcombo->m_pitemHover = m_pcombo->m_pitemCurrent;

         set_need_redraw();

      }

   }



   void list_box::_001OnActivate(::message::message * pmessage)
   {

      __pointer(::message::activate) pactivate(pmessage);

      __pointer(::user::interaction) pActive = (pactivate->m_nState == WA_INACTIVE ? pactivate->m_pWndOther : this);

      if (pactivate->m_nState == WA_INACTIVE)
      {

         auto pointCursor = psession->get_cursor_position();

         m_pcombo->screen_to_client(&pointCursor, ::user::e_layout_sketch);

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

         psession->set_keyboard_focus(this);


      }

   }


   void list_box::_001OnMouseActivate(::message::message * pmessage)
   {

      __pointer(::message::mouse_activate) pactivate(pmessage);

      pactivate->m_lresult = MA_NOACTIVATE;

      pactivate->m_bRet = true;


   }


   void list_box::on_message_key_down(::message::message * pmessage)
   {

      auto pkey = pmessage->m_union.m_pkey;

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

            pelemental->keyboard_set_focus();

         }


      }
      else if (pkey->m_ekey == ::user::e_key_down)
      {

         m_pcombo->m_pitemHover = minimum(m_pcombo->m_pitemHover + 1, m_pcombo->_001GetListCount() - 1);

      }
      else if (pkey->m_ekey == ::user::e_key_up)
      {

         m_pcombo->m_pitemHover = maximum(m_pcombo->m_pitemHover - 1, 0);

      }
      else if (pkey->m_ekey == ::user::e_key_return)
      {

         m_pcombo->set_current_item(m_pcombo->m_pitemHover, ::e_source_user);

         m_pcombo->ShowDropDown(false);

         __pointer(::user::primitive) pelemental = m_pcombo->keyboard_get_next_focusable();

         if (pelemental.is_set())
         {

            pelemental->keyboard_set_focus();

         }

      }

   }


   void list_box::on_message_key_up(::message::message * pmessage)
   {

      __UNREFERENCED_PARAMETER(pmessage);

   }


   void list_box::on_message_left_button_down(::message::message * pmessage)
   {

      auto pmouse = pmessage->m_union.m_pmouse;

      auto point = screen_to_client(pmouse->m_point, e_layout_sketch);

      auto rectangleClient = get_client_rect();

      psession->user()->set_mouse_focus_LButtonDown(this);

      m_itemLButtonDown = -1;

      if (rectangleClient.contains(point))
      {

         m_itemLButtonDown = hit_test(pmouse);

         SetCapture();

      }

      pmessage->m_bRet = true;

   }


   void list_box::on_message_left_button_up(::message::message * pmessage)
   {

      auto pmouse = pmessage->m_union.m_pmouse;

      auto point = screen_to_client(pmouse->m_point, e_layout_sketch);

      auto rectangleClient = get_client_rect();

      psession->user()->set_mouse_focus_LButtonDown(this);

      ReleaseCapture();

      if (rectangleClient.contains(point))
      {

         auto itemHit = hit_test(pmouse);

         if (itemHit == m_itemLButtonDown)
         {

            if (::is_set(m_pcombo))
            {

               m_pcombo->_001ShowDropDown(false);

            }

            ::topic topic;

            topic.m_puserinteraction = this;

            //topic.m_atom = m_atom;

            topic.m_atom = ::id_after_change_cur_sel;

            topic.m_actioncontext = ::e_source_user;

            topic.m_item = itemHit;

            route(&topic);

         }

      }



      pmouse->m_bRet = true;

   }


   void list_box::on_message_middle_button_down(::message::message * pmessage)
   {

      auto pmouse = pmessage->m_union.m_pmouse;

      auto point = pmouse->m_point;

      screen_to_client(point, e_layout_sketch);

      auto rectangleClient = get_client_rect();

      if (rectangleClient.contains(point))
      {

      }
      else
      {

         m_pcombo->_001ShowDropDown(false);

      }

      pmessage->m_bRet = true;

   }


   void list_box::on_message_right_button_down(::message::message * pmessage)
   {

      auto pmouse = pmessage->m_union.m_pmouse;

      auto point = pmouse->m_point;

      screen_to_client(point, e_layout_sketch);

      auto rectangleClient = get_client_rect();

      if (rectangleClient.contains(point))
      {

      }
      else
      {

         m_pcombo->_001ShowDropDown(false);

      }

      pmessage->m_bRet = true;

   }


   void list_box::on_message_mouse_move(::message::message * pmessage)
   {

      __UNREFERENCED_PARAMETER(pmessage);
      //auto pmouse = pmessage->m_union.m_pmouse;

      //pmessage->m_bRet = true;

      //auto point = screen_to_client(pmouse->m_point);

      //auto itemHover = hit_test(pmouse);

      //if (itemHover != m_pcombo->m_pitemHover)
      //{

      //   m_pcombo->m_pitemHover = itemHover.m_iItem;

      //   set_need_redraw();

      //}

   }


   void list_box::on_message_close(::message::message * pmessage)
   {

      pmessage->m_bRet = true;

      display(e_display_none);

      set_need_redraw();

   }


   item list_box::current_item()
   {

      return m_pcombo->current_item();

   }


   item list_box::hover_item()
   {

      return ::user::interaction::hover_item();

   }


   ::item_pointer list_box::on_hit_test(const ::point_i32 &point)
   {

      if (m_pcombo == nullptr)
      {

         item = ::e_element_none;

         return;

      }

      ::count iItemCount = m_pcombo->_001GetListCount();

      auto rectangleClient = get_client_rect();

      ::rectangle rectangleItem = rectangleClient;

      int iAddUp = 0;

      if (m_pcombo->m_bEdit)
      {

         iAddUp = 1;

      }

      for (::index iItem = 0; iItem < iItemCount; iItem++)
      {

         rectangleItem.top = rectangleClient.top + (_001GetItemHeight() * (int) (iAddUp + iItem));

         rectangleItem.bottom = rectangleItem.top + _001GetItemHeight();

         if (rectangleItem.contains(item.m_pointHitTest))
         {

            item  = {::e_element_item, iItem };

            return;

         }


      }

      rectangleItem.top = rectangleClient.top;

      rectangleItem.bottom = rectangleItem.top + _001GetItemHeight();

      if (rectangleItem.contains(item.m_pointHitTest))
      {

         item = e_element_search_edit;

         return;

      }

      item = e_element_none;

   }


   bool list_box::has_pending_graphical_update()
   {

      return m_bNeedRedraw;

   }


   void list_box::on_drop_down(const ::rectangle & rectangleWindow, const ::size & sizeFull)
   {

      ::rectangle rectangleMonitor;

      psession->get_best_monitor(rectangleMonitor, rectangleWindow);

      ::rectangle rectangleList;

      rectangleList.left = rectangleWindow.left;
      rectangleList.right = rectangleWindow.left + maximum(rectangleWindow.width(), sizeFull.cx);
      rectangleList.top = rectangleWindow.bottom;
      rectangleList.bottom = rectangleWindow.bottom + sizeFull.cy;

      if (rectangleList.bottom > rectangleMonitor.bottom -m_iBorder)
      {

         rectangleList.bottom = rectangleMonitor.bottom - m_iBorder;

         ::rectangle rectangleListOver;

         rectangleListOver.left = rectangleWindow.left;
         rectangleListOver.right = rectangleWindow.left + sizeFull.cx;
         rectangleListOver.bottom = rectangleWindow.top;
         rectangleListOver.top = rectangleWindow.top - sizeFull.cy;

         if (rectangleListOver.top < rectangleMonitor.top + m_iBorder)
         {

            rectangleListOver.top = rectangleMonitor.top + m_iBorder;

            if (rectangleListOver.height() > rectangleList.height())
            {

               rectangleList = rectangleListOver;

            }

         }

      }

      if (rectangleList.right > rectangleMonitor.right - m_iBorder)
      {

         rectangleList.offset(rectangleMonitor.right - (rectangleList.right-m_iBorder), 0);

      }

      if (rectangleList.left < rectangleMonitor.left)
      {

         rectangleList.move_left_to(0);

      }

      m_pcombo->m_pitemHover = current_item();

      if (!m_pcombo->::is_set(m_pitemHover))
      {

         m_pcombo->m_pitemHover = 0;

      }

      _001EnsureVisible(m_pcombo->m_pitemHover);

      if (!is_window())
      {

         ::user::system createstruct(0, nullptr, "list_box");

         pusersystem->m_createstruct.set_rect(::rectangle(rectangleList).inflate(m_iBorder));

         if (!create_window_ex(createstruct))
         {

            m_pcombo->m_plist.release();

            throw ::exception(error_resource);

         }

         SetOwner(m_pcombo);

      }
      else
      {

         place(::rectangle(rectangleList).inflate(m_iBorder));

      }

      order_top_most();

      display(e_display_normal);

      set_need_redraw();

      set_layout_ready();

      post_redraw();

   }


   void list_box::_on_show_window()
   {

      ::user::interaction::_on_show_window();

      if (is_screen_visible(layout().sketch().display()))
      {

         {

            synchronous_lock synchronouslock(psession->mutex());

            auto & preference = psession->m_uiptraToolWindow.add_new();

            psession->__refer(preference, this);

         }

         keyboard_set_focus();

      }
      else
      {

         {

            synchronous_lock synchronouslock(psession->mutex());

            ::index iFind = psession->m_uiptraToolWindow.predicate_find_first([this](auto& p) {return p.get() == this; });

            if (__found(iFind))
            {

               psession->__release(psession->m_uiptraToolWindow[iFind]);

               psession->m_uiptraToolWindow.erase_at(iFind);

            }

         }

      }

   }



} // namespace user




