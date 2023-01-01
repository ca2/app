#include "framework.h"
#include "list_box.h"
#include "combo_box.h"
#include "acme/handler/item.h"
#include "acme/constant/id.h"
#include "acme/constant/message.h"
#include "acme/constant/timer.h"
#include "acme/parallelization/synchronous_lock.h"
#include "aura/graphics/draw2d/graphics.h"
#include "aura/graphics/draw2d/brush.h"
#include "aura/graphics/draw2d/pen.h"
#include "acme/platform/timer.h"
#include "aura/user/user/scroll_data.h"
#include "aura/user/user/interaction_impl.h"
#include "aura/message/user.h"
#include "aura/user/user/user.h"
#include "aura/platform/session.h"


#define DEBUG_LIST_ITEM_DRAWING 0


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

      defer_create_synchronization();

      m_bClickDefaultMouseHandling = true;

      m_bTransparent = true;

      m_bHoverDefaultMouseHandling = true;

      m_bPendingKillFocusHiding = false;

      m_ewindowflag += e_window_flag_satellite_window;

      m_ewindowflag += e_window_flag_arbitrary_positioning;

      m_bComboList = true;

      m_puiDeactivateTogether = nullptr;

      m_pcombo = nullptr;

      m_iPadding = 2;

      m_iBorder = 0;

      //m_iMinListItemCount = 8;

      m_iMinListItemCount = 0;

      m_bMovingComboBox = false;

   }


   void list_box::install_message_routing(::channel * pchannel)
   {

      ::user::interaction::install_message_routing(pchannel);
      ::user::scroll_base::install_message_routing(pchannel);

      //install_click_default_mouse_handling(pchannel);

      MESSAGE_LINK(MESSAGE_CREATE, pchannel, this, &list_box::on_message_create);
      MESSAGE_LINK(MESSAGE_DESTROY, pchannel, this, &list_box::on_message_destroy);
      MESSAGE_LINK(e_message_set_focus, pchannel, this, &list_box::on_message_set_focus);
      MESSAGE_LINK(e_message_kill_focus, pchannel, this, &list_box::on_message_kill_focus);
      MESSAGE_LINK(MESSAGE_CLOSE, pchannel, this, &list_box::on_message_close);
      MESSAGE_LINK(e_message_mouse_activate, pchannel, this, &list_box::_001OnMouseActivate);
      MESSAGE_LINK(e_message_key_down, pchannel, this, &list_box::on_message_key_down);
      MESSAGE_LINK(e_message_key_up, pchannel, this, &list_box::on_message_key_up);
      MESSAGE_LINK(e_message_non_client_left_button_down, pchannel, (::user::interaction *)this, &interaction::on_message_left_button_down);
      MESSAGE_LINK(e_message_middle_button_down, pchannel, this, &list_box::on_message_middle_button_down);
      MESSAGE_LINK(e_message_right_button_down, pchannel, this, &list_box::on_message_right_button_down);
      MESSAGE_LINK(e_message_mouse_move, pchannel, this, &list_box::on_message_mouse_move);
      MESSAGE_LINK(e_message_show_window, pchannel, this, &list_box::on_message_show_window);

   }


   void list_box::on_message_create(::message::message * pmessage)
   {

      pmessage->previous();

      add_handler(this);

   }


   bool list_box::on_set_owner(::user::primitive * pprimitive)
   {

      auto puserinteractionOwner = pprimitive->get_owner();

      if(puserinteractionOwner)
      {

         auto puserinteractionHost = puserinteractionOwner->get_host_window();

         if (puserinteractionHost)
         {

            auto pimpl = puserinteractionHost->m_pinteractionimpl;

            if (pimpl)
            {

               synchronous_lock synchronouslock(pimpl->synchronization());

               pimpl->m_userinteractionaHideOnConfigurationChange.add_unique_interaction(this);

            }

         }

      }

      return true;

   }


   bool list_box::_001GetListText(index iSel, string& str)
   {

      str.empty();

      if (iSel < 0)
      {

         return false;

      }

      if (iSel >= m_straList.get_count())
         return false;

      str = m_straList[iSel];

      return true;

   }


   index list_box::_001FindListText(const string& str)
   {


      //index combo_box::_001FindListText(const ::string & str) const
      //{

      //   ::count ca = _001GetListCount();

      //   string strItem;

      //   for(index i = 0; i < ca; i++)
      //   {

      //      _001GetListText(i,strItem);

      //      if(m_bCaseSensitiveMatch)
      //      {

      //         if(str.compare(strItem) == 0)
      //            return i;

      //      }
      //      else
      //      {

      //         if(str.case_insensitive_order(strItem) == 0)
      //            return i;

      //      }

      //   }

      //   return -1;

      //}

      if (m_bCaseSensitiveMatch)
      {

         return m_straList.find_first(str);

      }
      else
      {

         return m_straList.find_first_ci(str);

      }

   }


   index list_box::_001GetListCount()
   {

      return m_straList.get_count();

   }


   index list_box::add_string(const ::string & pszString, uptr dwItemData)
   {

      m_straList.add(pszString);

      m_straValue.add(::as_string(dwItemData));

      return m_straList.get_upper_bound();

   }


   index list_box::add_string(const ::string & pszString, const string& strValue)
   {

      m_straList.add(pszString);

      m_straValue.add(strValue);

      return m_straList.get_upper_bound();

   }


   index list_box::delete_string(index iIndex)
   {

      if (iIndex < 0 || iIndex >= _001GetListCount())
      {

         return -1;

      }

      m_straList.erase_at(iIndex);

      m_straValue.erase_at(iIndex);

      return iIndex;

   }


   index list_box::insert_string(index iIndex, const ::string & pszString)
   {

      if (iIndex < 0)
      {

         return -1;

      }

      m_straList.insert_at(iIndex, pszString);

      m_straValue.insert_at(iIndex, "");

      return iIndex;

   }


   void list_box::reset_content()
   {

      synchronous_lock synchronouslock(this->synchronization());

      m_straList.erase_all();

      m_straValue.erase_all();

      m_pitemCurrent = nullptr;

      m_pitemHover = nullptr;

   }


   void list_box::handle(::topic * ptopic, ::context * pcontext)
   {

      if(ptopic->m_atom == ::id_click)
      {

         if(ptopic->user_interaction() == this)
         {

            if (m_pcombo)
            {

               m_pcombo->set_current_item(ptopic->m_pitem, ptopic->m_actioncontext);

               m_pcombo->ShowDropDown(false);

            }
            else
            {

               set_current_item(ptopic->m_pitem, ptopic->m_actioncontext);

            }

            return;

         }

      }

   }


   void list_box::on_message_destroy(::message::message * pmessage)
   {

      auto puserinteractionOwner = get_owner();

      if(puserinteractionOwner)
      {

         auto puserinteractionHost = puserinteractionOwner->get_host_window();

         if(puserinteractionHost)
         {

            auto pimpl = puserinteractionHost->m_pinteractionimpl;

            if (pimpl)
            {

               synchronous_lock synchronouslock(pimpl->synchronization());

               pimpl->m_userinteractionaHideOnConfigurationChange.erase_interaction(this);

            }

         }

      }

      pmessage->previous();

   }


   void list_box::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      ::draw2d::savedc savedc(pgraphics);

      ::rectangle_f64 rectangleClipBox;

      pgraphics->get_clip_box(rectangleClipBox);

      pgraphics->reset_clip();

      _001OnDrawComboList(pgraphics);

   }


   void list_box::_001OnDrawComboList(::draw2d::graphics_pointer & pgraphics)
   {

      ::count iListItemCount = _001GetListCount();

      string strItem;

      ::rectangle_i32 rectangleClient;

      layout().get_client_rect(rectangleClient, ::user::e_layout_design);

      status < ::color::color > colorBackground;

      status < ::color::color > colorText;

      auto pstyle = get_style(pgraphics);

      colorBackground = get_color(pstyle, ::e_element_background);

      auto pbrushBk = __create < ::draw2d::brush > ();

      pbrushBk->create_solid(colorBackground);

      pgraphics->set(pbrushBk);

      pgraphics->fill_rectangle(rectangleClient);

      ::rectangle_i32 rectangleItem;

      rectangleItem = rectangleClient;

      rectangleItem.bottom = rectangleClient.top;

      if (m_pcombo && m_pcombo->m_bEdit)
      {

         rectangleItem.bottom += _001GetItemHeight();

      }

      auto pointCursor = get_cursor_position();

      pointCursor+=screen_to_client(::user::e_layout_design);

      pgraphics->set_font(this, ::e_element_none);

      auto pitemHover = hover_item();

      auto pitemCurrent = current_item();

      auto pbrush = __create < ::draw2d::brush > ();

      for (index iItem = 0; iItem < iListItemCount; iItem++)
      {

         rectangleItem.top = rectangleItem.bottom;

         rectangleItem.bottom = rectangleItem.top + _001GetItemHeight();

#if DEBUG_LIST_ITEM_DRAWING

         string strDebug;

#endif

         ::user::e_state estate = ::user::e_state_none;

         if (::is_set(pitemHover) && pitemHover->m_iItem == iItem)
         {

#if DEBUG_LIST_ITEM_DRAWING

            strDebug += "hover;";

#endif

            estate += ::user::e_state_hover;

         }

         if (::is_set(pitemCurrent) && pitemCurrent->m_iItem == iItem)
         {

#if DEBUG_LIST_ITEM_DRAWING

            strDebug += "selected;";

#endif

            estate += ::user::e_state_selected;

         }

         colorBackground = get_color(pstyle, ::e_element_item_background, estate);

         colorText = get_color(pstyle, ::e_element_item_text, estate);

         pbrushBk->create_solid(colorBackground);

         pbrush->create_solid(colorText);

         pgraphics->set(pbrushBk);

         pgraphics->fill_rectangle(rectangleItem);

         _001GetListText(iItem, strItem);

         pgraphics->set(pbrush);

         auto rectangleText = rectangleItem;

         rectangleText.deflate(m_iPadding);

#if DEBUG_LIST_ITEM_DRAWING


         strItem += strDebug;

#endif

         pgraphics->draw_text(strItem, rectangleText);

      }

      ::color::color crBorder = argb(255, 0, 0, 0);

      auto ppen = __create < ::draw2d::pen > ();

      ppen->create_solid(1.0, crBorder);

      pgraphics->set(ppen);

      rectangleClient.deflate(0, 0, 1, 1);

      pgraphics->draw_rectangle(rectangleClient);

   }


   ::write_text::font_pointer list_box::get_font(style *pstyle, enum_element eelement, ::user::enum_state estate)
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


   void list_box::query_full_size(::draw2d::graphics_pointer& pgraphics, SIZE_I32 * psize)
   {

      synchronous_lock synchronouslock(this->synchronization());

      pgraphics->set_font(this, ::e_element_none);

      pgraphics->set_text_rendering_hint(::write_text::e_rendering_anti_alias);

      string strItem;

      ::size_f64 size;

      psize->cx = 0;

      m_dItemHeight = 0.;

      ::count cListCount = _001GetListCount();

      for (index i = 0; i < cListCount; i++)
      {

         _001GetListText(i, strItem);

         size = pgraphics->get_text_extent(strItem);

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

      if (m_pcombo && m_pcombo->m_bEdit)
      {

         iAddUp = 1;

      }

      if (m_iMinListItemCount > 0)
      {

         auto iAddUp2 = m_iMinListItemCount - cListCount;

         if (iAddUp2 > 0)
         {

            iAddUp = (decltype(iAddUp))iAddUp2;

         }

      }

      psize->cy = (::i32)(_001GetItemHeight() * (_001GetListCount() + iAddUp));

      psize->cx += m_iBorder * 2;

      //auto rectangleComboClient = get_client_rect();

      //psize->cx = maximum(psize->cx, rectangleComboClient.width());
      //psize->cx = maximum(psize->cx, rectangleComboClient.width());

   }


   void list_box::on_change_combo_sel(index iSel)
   {

   }


   i32 list_box::_001GetItemHeight() const
   {

      return (::i32)(m_dItemHeight + m_iPadding * 2);

   }


   void list_box::_001EnsureVisible(index iItem)
   {

      if (m_pscrollbarVertical != nullptr
         && m_pscrolldataVertical->m_bScroll
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


   void list_box::on_layout(::draw2d::graphics_pointer& pgraphics)
   {

      query_full_size(pgraphics, m_sizeFull);

   }


   bool list_box::keyboard_focus_is_focusable()
   {

      return true;

   }


   bool list_box::keyboard_focus_OnKillFocus(::oswindow oswindowNew)
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


   bool list_box::pre_create_window(::user::system * pusersystem)
   {


      return true;

   }


   void list_box::on_message_show_window(::message::message * pmessage)
   {

      ::pointer<::message::show_window>pshowwindow(pmessage);

      if (pshowwindow->m_bShow)
      {

#ifdef WINDOWS

         set_keyboard_focus();

#endif

      }
      else
      {

         output_debug_string("list_box hide");

      }

   }


   void list_box::on_message_kill_focus(::message::message * pmessage)
   {

      if (m_pcombo)
      {

         bool bGoingToShow = m_pcombo->m_timeShowComboList.elapsed() < 300_ms;

         if (!bGoingToShow)
         {

            m_timeKillFocus.Now();

            m_bPendingKillFocusHiding = true;

            set_timer(e_timer_kill_focus, 300_ms);

            //::pointer<::message::kill_focus>pkillfocus(pmessage);

            //oswindow oswindowThis = get_safe_handle();

            //oswindow oswindowNew = pkillfocus->m_oswindowNew;

            //if (oswindowThis != oswindowNew && !m_bMovingComboBox)
            //{

            //   if (layout().sketch().is_screen_visible())
            //   {

            //      m_timeLastVisibilityChange.Now();

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


   void list_box::on_message_set_focus(::message::message * pmessage)
   {

      if (m_pcombo)
      {

         m_pcombo->m_pitemHover = m_pcombo->m_pitemCurrent;

         set_need_redraw();

      }

   }



   void list_box::_001OnActivate(::message::message * pmessage)
   {

      ::pointer<::message::activate>pactivate(pmessage);

      ::pointer<::user::interaction>pActive = (pactivate->m_eactivate == e_activate_inactive ? pactivate->m_pWndOther : this);

      if (pactivate->m_eactivate == e_activate_inactive)
      {

         auto pointCursor = get_cursor_position();

         pointCursor+=m_pcombo->screen_to_client(::user::e_layout_sketch);

      }
      else
      {

         set_keyboard_focus();


      }

   }


   void list_box::_001OnMouseActivate(::message::message * pmessage)
   {

      ::pointer<::message::mouse_activate>pactivate(pmessage);

      pactivate->m_lresult = e_mouse_activate_no_activate;

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

         ::pointer<::user::primitive>pelemental = m_pcombo->keyboard_get_next_focusable();

         if (pelemental.is_set())
         {

            pelemental->set_keyboard_focus();

         }


      }
      else if (pkey->m_ekey == ::user::e_key_down)
      {

         m_pcombo->m_pitemHover = __new(::item(e_element_item, minimum(m_pcombo->m_pitemHover->item_index() + 1, m_pcombo->_001GetListCount() - 1)));

      }
      else if (pkey->m_ekey == ::user::e_key_up)
      {

         m_pcombo->m_pitemHover = __new(::item(e_element_item, maximum(m_pcombo->m_pitemHover->item_index() - 1, 0)));

      }
      else if (pkey->m_ekey == ::user::e_key_return)
      {

         m_pcombo->set_current_item(m_pcombo->m_pitemHover, ::e_source_user);

         m_pcombo->ShowDropDown(false);

         ::pointer<::user::primitive>pelemental = m_pcombo->keyboard_get_next_focusable();

         if (pelemental.is_set())
         {

            pelemental->set_keyboard_focus();

         }

      }

   }


   void list_box::on_message_key_up(::message::message * pmessage)
   {

      __UNREFERENCED_PARAMETER(pmessage);

   }


   void list_box::on_message_middle_button_down(::message::message * pmessage)
   {

      auto pmouse = pmessage->m_union.m_pmouse;

      auto point = pmouse->m_point;

      point+=screen_to_client(e_layout_sketch);

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

      point+=screen_to_client(e_layout_sketch);

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


   item_pointer list_box::current_item()
   {

      return ::user::interaction::current_item();

   }


   item_pointer list_box::hover_item()
   {

      return ::user::interaction::hover_item();

   }


   ::item_pointer list_box::on_hit_test(const ::point_i32 & point)
   {

      ::count iItemCount = _001GetListCount();

      auto rectangleClient = get_client_rect();

      ::rectangle_i32 rectangleItem = rectangleClient;

      int iAddUp = 0;

      if (m_pcombo && m_pcombo->m_bEdit)
      {

         iAddUp = 1;

      }

      for (::index iItem = 0; iItem < iItemCount; iItem++)
      {

         rectangleItem.top = rectangleClient.top + (_001GetItemHeight() * (int) (iAddUp + iItem));

         rectangleItem.bottom = rectangleItem.top + _001GetItemHeight();

         if (rectangleItem.contains(point))
         {

            return new_item_with_index(iItem);

         }

      }

      rectangleItem.top = rectangleClient.top;

      rectangleItem.bottom = rectangleItem.top + _001GetItemHeight();

      if (rectangleItem.contains(point))
      {

         return __new(item(e_element_search_edit));

      }
      
      auto pitemNone = __new(::item(e_element_none));

      return pitemNone;

   }


   bool list_box::has_pending_graphical_update()
   {

      return m_bNeedRedraw;

   }


   void list_box::on_drop_down(const ::rectangle_i32 & rectangleWindow, const ::size_i32 & sizeFull)
   {

      {

         //lock_sketch_to_design lockSketchToDesign(this);

         ::rectangle_i32 rectangleMonitor;

         ::index i = get_best_monitor(rectangleMonitor, rectangleWindow);

         ::rectangle_i32 rectangleList;

         rectangleList.left = rectangleWindow.left;
         rectangleList.right = rectangleWindow.left + maximum(rectangleWindow.width(), sizeFull.cx);
         rectangleList.top = rectangleWindow.bottom;
         rectangleList.bottom = rectangleWindow.bottom + sizeFull.cy;

         if (i < 0)
         {

            m_pcombo->get_parent()->get_window_rect(rectangleMonitor);

         }

         if (rectangleList.bottom > rectangleMonitor.bottom - m_iBorder)
         {

            rectangleList.bottom = rectangleMonitor.bottom - m_iBorder;

            ::rectangle_i32 rectangleListOver;

            rectangleListOver.left = rectangleList.left;
            rectangleListOver.right = rectangleList.right;
            rectangleListOver.bottom = rectangleWindow.top;
            rectangleListOver.top = rectangleWindow.top - sizeFull.cy;

            if (rectangleListOver.top < rectangleMonitor.top + m_iBorder)
            {

               rectangleListOver.move_to(rectangleListOver.left, rectangleMonitor.top);

            }

            rectangleList = rectangleListOver;

         }

         if (rectangleList.right > rectangleMonitor.right - m_iBorder)
         {

            rectangleList.offset(rectangleMonitor.right - (rectangleList.right - m_iBorder), 0);

         }

         if (rectangleList.left < rectangleMonitor.left)
         {

            rectangleList.move_left_to(0);

         }

         m_pcombo->m_pitemHover = current_item();

         if (!::is_set(m_pcombo->m_pitemHover))
         {

            m_pcombo->m_pitemHover = 0;

         }

         _001EnsureVisible(m_pcombo->m_pitemHover->m_iItem);

         if (i < 0)
         {

            rectangleList+=m_pcombo->get_parent()->screen_to_client();

         }

         if (!is_window())
         {

            m_puserinteractionOwner = m_pcombo;

            order_top_most();

            set_tool_window();

            m_bTransparent = true;

            display();

            place(::rectangle_i32(rectangleList).inflate(m_iBorder));

            create_interaction(i >= 0 ? nullptr : m_pcombo->get_parent());
            //if (!)
            //{

            //   m_pcombo->m_plistbox.release();

            //   throw ::exception(error_resource);

            //}

            set_owner(m_pcombo);

         }
         else
         {

            place(::rectangle_i32(rectangleList).inflate(m_iBorder));

         }

         order_top_most();

         display(e_display_restored);

         auto & window_state = const_layout().sketch();

         string str;

         str.format("%d", window_state.m_edisplay.m_eenum);

         set_need_layout();

         set_need_redraw();

      }

      post_redraw();

   }


   void list_box::set_current_item(::item * pitem, const ::action_context & context)
   {

      if(m_pcombo)
      {

         m_pcombo->set_current_item(pitem, context);

      }
      else
      {

         ::user::scroll_base::set_current_item(pitem, context);

      }

   }


   void list_box::set_current_item_by_data(uptr u, const ::action_context& context)
   {

      index iSel = m_straValue.find_first(::as_string(u));

      if (iSel < 0)
      {

         return;

      }

      set_current_item(__new(::item(::e_element_item, iSel)), context);

   }


   void list_box::set_current_item_by_string_value(const string& strValue, const ::action_context& context)
   {

      index iSel = m_straValue.find_first(strValue);

      if (iSel < 0)
      {

         return;

      }

      set_current_item(__new(::item(::e_element_item, iSel)), context);

   }

    void list_box::set_current_item_by_index(::index iIndex, const ::action_context& context)
    {

       if (iIndex < 0 || iIndex >= m_straValue.get_size())
       {

          return;

       }

       set_current_item(__new(::item(::e_element_item, iIndex)), context);

    }


    string list_box::get_current_item_string_value()
   {

      index iSel = current_item()->m_iItem;

      if (iSel < 0)
      {

         return "";

      }

      string str = m_straValue[iSel];

      return str;

   }


   void list_box::_on_show_window()
   {

      ::user::interaction::_on_show_window();

      if (m_pcombo)
      {

         if (is_screen_visible(const_layout().sketch().display()))
         {

            {

               auto psession = get_session();

               synchronous_lock synchronouslock(psession->synchronization());

               auto pinteraction = __create_new < ::user::interaction >();

               auto puser = psession->user();

               puser->m_uiptraToolWindow.add(pinteraction);

            }

            set_keyboard_focus();

         }
         else
         {

            {

               auto psession = get_session();

               synchronous_lock synchronouslock(psession->synchronization());

               auto puser = psession->user();

               auto iFind = puser->m_uiptraToolWindow.predicate_find_first([this](auto& p) {return p.get() == this; });

               if (found(iFind))
               {

                  puser->m_uiptraToolWindow.erase_at(iFind);

               }

            }

         }

      }

   }


} // namespace user



