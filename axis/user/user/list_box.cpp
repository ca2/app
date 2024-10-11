#include "framework.h"
#include "list_box.h"
#include "combo_box.h"
#include "acme/handler/item.h"
#include "acme/constant/id.h"
#include "acme/constant/message.h"
#include "acme/constant/user_key.h"
#include "acme/constant/timer.h"
#include "acme/handler/topic.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/prototype/geometry2d/_text_stream.h"
#include "acme/user/user/content.h"
#include "acme/parallelization/message_queue.h"
#include "aura/graphics/draw2d/graphics.h"
#include "aura/graphics/draw2d/brush.h"
#include "aura/graphics/draw2d/pen.h"
#include "acme/platform/timer.h"
#include "aura/user/user/scroll_state.h"
#include "aura/user/user/interaction_graphics_thread.h"
//#include "aura/user/user/interaction_impl.h"
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

      m_bDefaultClickHandling = true;

      m_bTransparent = true;

      m_bDefaultMouseHoverHandling = true;

      m_bDefaultParentMouseMessageHandling = true;

      //m_bPendingKillFocusHiding = false;

      m_ewindowflag += e_window_flag_satellite_window;

      m_ewindowflag += e_window_flag_arbitrary_positioning;

      m_bComboList = true;

      m_puiDeactivateTogether = nullptr;

      m_pcombo = nullptr;

      m_iPadding = 2;

      m_iScreenMargin = 24;

      //m_iMinListItemCount = 8;

      m_iMinListItemCount = 0;

      m_bMovingComboBox = false;

      //auto & bX = m_pscrolllayoutX->m_scrollstatea[::user::e_layout_sketch].m_bScrollEnable;
      auto& bY = m_pscrolllayoutY->m_scrollstatea[::user::e_layout_sketch].m_bScrollEnable;

      //bX = true;
      bY = true;


   }


   void list_box::install_message_routing(::channel* pchannel)
   {

      ::user::interaction::install_message_routing(pchannel);
      ::user::scroll_base::install_message_routing(pchannel);

      //install_click_default_mouse_handling(pchannel);

      MESSAGE_LINK(MESSAGE_CREATE, pchannel, this, &list_box::on_message_create);
      MESSAGE_LINK(MESSAGE_DESTROY, pchannel, this, &list_box::on_message_destroy);
      //MESSAGE_LINK(e_message_set_focus, pchannel, this, &list_box::on_message_set_focus);
      //MESSAGE_LINK(e_message_kill_focus, pchannel, this, &list_box::on_message_kill_focus);
      MESSAGE_LINK(MESSAGE_CLOSE, pchannel, this, &list_box::on_message_close);
      MESSAGE_LINK(e_message_mouse_activate, pchannel, this, &list_box::_001OnMouseActivate);
      MESSAGE_LINK(e_message_key_down, pchannel, this, &list_box::on_message_key_down);
      MESSAGE_LINK(e_message_key_up, pchannel, this, &list_box::on_message_key_up);
      MESSAGE_LINK(e_message_non_client_left_button_down, pchannel, (::user::interaction*)this, &interaction::on_message_left_button_down);
      MESSAGE_LINK(e_message_middle_button_down, pchannel, this, &list_box::on_message_middle_button_down);
      MESSAGE_LINK(e_message_right_button_down, pchannel, this, &list_box::on_message_right_button_down);
      //MESSAGE_LINK(e_message_mouse_move, pchannel, this, &list_box::on_message_mouse_move);
      MESSAGE_LINK(e_message_show_window, pchannel, this, &list_box::on_message_show_window);

   }


   void list_box::on_message_create(::message::message* pmessage)
   {

      pmessage->previous();

      add_handler(this);

   }


   bool list_box::on_set_owner(::user::interaction_base* pprimitive)
   {

      auto puserinteractionOwner = pprimitive->get_owner();

      if (puserinteractionOwner)
      {

         auto puserinteractionHost = puserinteractionOwner->get_host_user_interaction();

         if (puserinteractionHost)
         {


            throw todo;

            //auto pimpl = puserinteractionHost->m_pinteractionimpl;

            //if (pimpl)
            //{

            //   synchronous_lock synchronouslock(pimpl->synchronization());

            //   pimpl->m_userinteractionaHideOnConfigurationChange.add_unique_interaction(this);

            //}

         }

      }

      return true;

   }


   bool list_box::_001GetListText(::collection::index iSel, string& str)
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


   ::collection::index list_box::_001FindListText(const string& str)
   {


      //index combo_box::_001FindListText(const ::string & str) const
      //{

      //   ::collection::count ca = _001GetListCount();

      //   string strItem;

      //   for(::collection::index i = 0; i < ca; i++)
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

         return m_straList.case_insensitive_find_first(str);

      }

   }


   ::collection::index list_box::_001GetListCount()
   {

      return m_straList.get_count();

   }


   //::collection::index list_box::add_string(const ::string & pszString, uptr dwItemData)
   //{

   //   m_straList.add(pszString);

   //   m_straValue.add(::as_string(dwItemData));

   //   return m_straList.get_upper_bound();

   //}


   //::collection::index list_box::add_string(const ::string & pszString, const string& strValue)
   //{

   //   m_straList.add(pszString);

   //   m_straValue.add(strValue);

   //   return m_straList.get_upper_bound();

   //}

   ::collection::index list_box::add_item(const ::scoped_string& scopedstr, const ::atom& atom)
   {

      m_straList.add(scopedstr);

      m_atoma.add(atom);

      return m_straList.get_upper_bound();

   }


   ::collection::index list_box::erase_item_at(::collection::index iIndex)
   {

      if (iIndex < 0 || iIndex >= _001GetListCount())
      {

         return -1;

      }

      m_straList.erase_at(iIndex);

      m_atoma.erase_at(iIndex);

      return iIndex;

   }


   ::collection::index list_box::insert_item_at(::collection::index iIndex, const ::string& pszString)
   {

      if (iIndex < 0)
      {

         return -1;

      }

      m_straList.insert_at(iIndex, pszString);

      m_atoma.insert_at(iIndex, ::atom::e_type_null);

      return iIndex;

   }


   void list_box::reset_content()
   {

      synchronous_lock synchronouslock(this->synchronization());

      m_straList.erase_all();

      m_atoma.erase_all();

      //m_pitemCurrent = nullptr;

      //m_pitemHover = nullptr;

   }


   void list_box::handle(::topic* ptopic, ::context* pcontext)
   {

      if (ptopic->m_atom == ::id_click)
      {

         if (ptopic->user_interaction() == this)
         {

            if (m_pcombo)
            {

               m_pcombo->set_current_item(ptopic->m_pitem, ptopic->m_actioncontext);

               throw todo;

               //auto p = get_host_user_interaction()->m_pinteractionimpl->m_pgraphicsthread->get_message_queue();

               //p->m_eflagElement |= (::enum_flag)(1ll << 36);

               //m_pcombo->ShowDropDown(false);

            }
            else
            {

               set_current_item(ptopic->m_pitem, ptopic->m_actioncontext);

            }

            return;

         }

      }

   }


   void list_box::on_message_destroy(::message::message* pmessage)
   {

      auto puserinteractionOwner = get_owner();

      if (puserinteractionOwner)
      {

         auto puserinteractionHost = puserinteractionOwner->get_host_user_interaction();

         if (puserinteractionHost)
         {

            throw todo;

            //auto pimpl = puserinteractionHost->m_pinteractionimpl;

            //if (pimpl)
            //{

            //   synchronous_lock synchronouslock(pimpl->synchronization());

            //   pimpl->m_userinteractionaHideOnConfigurationChange.erase_interaction(this);

            //}

         }

      }

      pmessage->previous();

   }


   void list_box::_001OnDraw(::draw2d::graphics_pointer& pgraphics)
   {

      //pgraphics->reset_clip();

      //::draw2d::save_context savecontext(pgraphics);

      //::rectangle_f64 rectangleClipBox;

      //pgraphics->get_clip_box(rectangleClipBox);

      //pgraphics->reset_clip();

      _001OnDrawComboList(pgraphics);

   }


   void list_box::_001OnDrawComboList(::draw2d::graphics_pointer& pgraphics)
   {

      ::collection::count iListItemCount = _001GetListCount();

      string strItem;

      auto rectangleX = this->rectangle();

      status < ::color::color > colorBackground;

      status < ::color::color > colorText;

      auto pstyle = get_style(pgraphics);

      colorBackground = get_color(pstyle, ::e_element_background);

      auto pbrushBk = __create < ::draw2d::brush >();

      pbrushBk->create_solid(colorBackground);

      pgraphics->set(pbrushBk);

      pgraphics->fill_rectangle(rectangleX);

      ::rectangle_i32 rectangleItem;

      rectangleItem = rectangleX;

      rectangleItem.bottom() = rectangleX.top();

      if (m_pcombo && m_pcombo->m_bEdit)
      {

         rectangleItem.bottom() += _001GetItemHeight();

      }

      auto pointCursor = mouse_cursor_position();

      //screen_to_client(::user::e_layout_design)(pointCursor);

      pgraphics->set_font(this, ::e_element_none);

      auto pitemHover = hover_item();

      auto pitemCurrent = current_item();

      auto pbrush = __create < ::draw2d::brush >();

      for (::collection::index iItem = 0; iItem < iListItemCount; iItem++)
      {

         rectangleItem.top() = rectangleItem.bottom();

         rectangleItem.bottom() = rectangleItem.top() + _001GetItemHeight();

#if DEBUG_LIST_ITEM_DRAWING

         string strDebug;

#endif

         ::user::e_state estate = ::user::e_state_none;

         if (::is_item_set(pitemHover) && pitemHover->m_item.m_iItem == iItem)
         {

#if DEBUG_LIST_ITEM_DRAWING

            strDebug += "hover;";

#endif

            estate += ::user::e_state_hover;

            information() << "hover_item : " << iItem;

         }

         if (::is_item_set(pitemCurrent) && pitemCurrent->m_item.m_iItem == iItem)
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

      auto ppen = __create < ::draw2d::pen >();

      ppen->create_solid(1.0, crBorder);

      pgraphics->set(ppen);

      rectangleX.deflate(0, 0, 1, 1);

      pgraphics->draw_rectangle(rectangleX);

   }


   ::write_text::font_pointer list_box::get_font(style* pstyle, enum_element eelement, ::user::enum_state estate)
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


   void list_box::query_full_size(::draw2d::graphics_pointer& pgraphics, ::size_i32* psize)
   {

      _synchronous_lock synchronouslock(this->synchronization());

      pgraphics->set_font(this, ::e_element_none);

      pgraphics->set_text_rendering_hint(::write_text::e_rendering_anti_alias);

      string strItem;

      ::size_f64 size;

      psize->cx() = 0;

      m_dItemHeight = 0.;

      ::collection::count cListCount = _001GetListCount();

      for (::collection::index i = 0; i < cListCount; i++)
      {

         _001GetListText(i, strItem);

         size = pgraphics->get_text_extent(strItem);

         size.cx() += m_iPadding * 2;

         if (size.cx() > psize->cx())
         {

            psize->cx() = (::i32)size.cx();

         }

         if (size.cy() > m_dItemHeight)
         {

            m_dItemHeight = (::i32)size.cy();

            if (size.cy() != 18)
            {

               //informationf("\nCOMBO LIST ITEM HEIGHT != 18\n");

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

      psize->cy() = (::i32)(_001GetItemHeight() * (_001GetListCount() + iAddUp));

      int iScrollBarWidth = 20;

      psize->cx() += iScrollBarWidth;

      //auto rectangleComboClient = this->rectangle();

      //psize->cx() = maximum(psize->cx(), rectangleComboClient.width());
      //psize->cx() = maximum(psize->cx(), rectangleComboClient.width());

   }


   void list_box::on_change_combo_sel(::collection::index iSel)
   {

   }


   i32 list_box::_001GetItemHeight() const
   {

      return (::i32)(m_dItemHeight + m_iPadding * 2);

   }


   void list_box::ensure_item_visible_by_index(::collection::index iItem)
   {

      if (m_pscrollbarY != nullptr
         && m_pscrolllayoutY->m_scrollstatea[::user::e_layout_sketch].m_bHasScroll
         && iItem >= 0 && iItem < m_pcombo->_001GetListCount())
      {

         set_context_offset_y((::f64)(iItem * _001GetItemHeight()));

      }
      else
      {

         set_context_offset_y(0.);

      }

   }


   void list_box::_001OnTimer(::timer* ptimer)
   {

      //if (ptimer->m_etimer == e_timer_kill_focus)
      //{

      //   if (m_bPendingKillFocusHiding)
      //   {
      //      
      //      m_bPendingKillFocusHiding = false;

      //      hide();

      //      set_need_redraw();

      //      post_redraw();

      //   }

      //   KillTimer(e_timer_kill_focus);

      //}

      ::user::scroll_base::_001OnTimer(ptimer);

   }


   void list_box::on_layout(::draw2d::graphics_pointer& pgraphics)
   {

      query_full_size(pgraphics, &m_sizeFull);


      set_total_size(m_sizeFull, ::user::e_layout_design);

      ::user::scroll_base::on_layout(pgraphics);

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


   bool list_box::pre_create_window(::user::system* pusersystem)
   {


      return true;

   }


   void list_box::on_message_show_window(::message::message* pmessage)
   {

      ::pointer<::message::show_window>pshowwindow(pmessage);

      if (pshowwindow->m_bShow)
      {

         if (m_pcombo)
         {

#ifdef WINDOWS

            set_keyboard_focus();

#endif

         }

      }
      else
      {

         //informationf("list_box hide");

      }

   }


   void list_box::on_kill_keyboard_focus()
   {

      m_timeKillFocus.Now();

      if (m_pcombo)
      {

         bool bGoingToShow = m_pcombo->m_timeShowComboList.elapsed() < 300_ms;

         if (!bGoingToShow)
         {

            hide();


            //se
            //m_bPendingKillFocusHiding = true;

            //set_timer(e_timer_kill_focus, 300_ms);

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

            //      m_pcombo->get_wnd()->set_active_window();

            //   }
            //   else
            //   {

            //      //informationf("A phantom is loosing focus. What a pitty!!");

            //   }

            //}

            //pkillfocus->m_bRet = true;

            //pkillfocus->m_lresult = 0;

         }

      }

   }


   void list_box::on_set_keyboard_focus()
   {

      if (m_pcombo)
      {

         m_pcombo->m_pitemHover = m_pcombo->main_content().m_pitemCurrent;

         set_need_redraw();

      }

   }



   void list_box::_001OnActivate(::message::message* pmessage)
   {

      ::pointer<::message::activate>pactivate(pmessage);

      ::pointer<::user::interaction>pActive = (pactivate->m_eactivate == e_activate_inactive ? pactivate->m_pWndOther : this);

      if (pactivate->m_eactivate == e_activate_inactive)
      {

         //         auto pointCursor = get_cursor_position();
         //
         //         m_pcombo->screen_to_client(::user::e_layout_sketch)(pointCursor);

      }
      else
      {

         set_keyboard_focus();


      }

   }


   void list_box::_001OnMouseActivate(::message::message* pmessage)
   {

      ::pointer<::message::mouse_activate>pactivate(pmessage);

      pactivate->m_lresult = e_mouse_activate_no_activate;

      pactivate->m_bRet = true;


   }


   void list_box::on_message_key_down(::message::message* pmessage)
   {

      auto pkey = pmessage->m_union.m_pkey;

      if (pkey->m_ekey == ::user::e_key_escape)
      {

         m_pcombo->ShowDropDown(false);

      }
      else if (pkey->m_ekey == ::user::e_key_tab)
      {

         m_pcombo->ShowDropDown(false);

         ::pointer<::user::interaction_base>pelemental = m_pcombo->keyboard_get_next_focusable();

         if (pelemental.is_set())
         {

            pelemental->set_keyboard_focus();

         }


      }
      else if (pkey->m_ekey == ::user::e_key_down)
      {

         m_pcombo->m_pitemHover = __new ::item(e_element_item, minimum(m_pcombo->m_pitemHover->m_item.m_iItem + 1, m_pcombo->_001GetListCount() - 1));

      }
      else if (pkey->m_ekey == ::user::e_key_up)
      {

         m_pcombo->m_pitemHover = __new ::item(e_element_item, maximum(m_pcombo->m_pitemHover->m_item.m_iItem - 1, 0));

      }
      else if (pkey->m_ekey == ::user::e_key_return)
      {

         m_pcombo->set_current_item(m_pcombo->m_pitemHover, ::e_source_user);

         m_pcombo->ShowDropDown(false);

         ::pointer<::user::interaction_base>pelemental = m_pcombo->keyboard_get_next_focusable();

         if (pelemental.is_set())
         {

            pelemental->set_keyboard_focus();

         }

      }

   }


   void list_box::on_message_key_up(::message::message* pmessage)
   {

      __UNREFERENCED_PARAMETER(pmessage);

   }


   void list_box::on_message_middle_button_down(::message::message* pmessage)
   {

      auto pmouse = pmessage->m_union.m_pmouse;

      auto point = pmouse->m_pointHost;

      host_to_client(e_layout_sketch)(point);

      auto rectangleX = this->rectangle();

      if (rectangleX.contains(point))
      {

      }
      else
      {

         m_pcombo->_001ShowDropDown(false);

      }

      pmessage->m_bRet = true;

   }


   void list_box::on_message_right_button_down(::message::message* pmessage)
   {

      auto pmouse = pmessage->m_union.m_pmouse;

      auto point = pmouse->m_pointHost;

      host_to_client(e_layout_sketch)(point);

      auto rectangleX = this->rectangle();

      if (rectangleX.contains(point))
      {

      }
      else
      {

         m_pcombo->_001ShowDropDown(false);

      }

      pmessage->m_bRet = true;

   }


   //void list_box::on_message_mouse_move(::message::message * pmessage)
   //{

   //   __UNREFERENCED_PARAMETER(pmessage);
   //   //auto pmouse = pmessage->m_union.m_pmouse;

   //   //pmessage->m_bRet = true;

   //   //auto point = screen_to_client(pmouse->m_point);

   //   //auto itemHover = hit_test(pmouse);

   //   //if (itemHover != m_pcombo->m_pitemHover)
   //   //{

   //   //   m_pcombo->m_pitemHover = itemHover.m_iItem;

   //   //   set_need_redraw();

   //   //}

   //}


   void list_box::on_message_close(::message::message* pmessage)
   {

      pmessage->m_bRet = true;

      display(e_display_none);

      set_need_redraw();

   }


   ::item_pointer list_box::current_item()
   {

      return ::user::interaction::current_item();

   }


   ::item_pointer list_box::hover_item()
   {

      return ::user::interaction::hover_item();

   }


   ::item_pointer list_box::on_hit_test(const ::point_i32& point, ::user::e_zorder ezorder)
   {

      ::collection::count iItemCount = _001GetListCount();

      auto rectangleX = this->rectangle();

      ::rectangle_i32 rectangleItem = rectangleX;

      int iAddUp = 0;

      if (m_pcombo && m_pcombo->m_bEdit)
      {

         iAddUp = 1;

      }

      for (::collection::index iItem = 0; iItem < iItemCount; iItem++)
      {

         rectangleItem.top() = rectangleX.top() + (_001GetItemHeight() * (int)(iAddUp + iItem));

         rectangleItem.bottom() = rectangleItem.top() + _001GetItemHeight();

         if (rectangleItem.contains(point))
         {

            __defer_construct_new(main_content().m_pitema);

            auto& pitemNew = this->main_content().m_pitema->element_at_grow(iItem);

            if (__defer_construct_new(pitemNew))
            {

               pitemNew->m_item.m_eelement = e_element_item;

               pitemNew->m_item.m_iItem = iItem;

            }

            auto puseritem = user_item(pitemNew);

            puseritem->m_rectangle2 = rectangleItem;

            return pitemNew;

         }

      }

      rectangleItem.top() = rectangleX.top();

      rectangleItem.bottom() = rectangleItem.top() + _001GetItemHeight();

      if (rectangleItem.contains(point))
      {

         return __new ::item(e_element_search_edit);

      }

      auto pitemNone = __new ::item(e_element_none);

      return pitemNone;

   }


   //   bool list_box::has_pending_graphical_update()
   //   {
   //
   //      return m_bNeedRedraw;
   //
   //   }


   void list_box::on_drop_down(const ::rectangle_i32& rectangleWindow, const ::size_i32& sizeFull)
   {

      //lock_sketch_to_design lockSketchToDesign(this);

      ::rectangle_i32 rectangleMonitor;

      ::collection::index i = get_best_monitor(&rectangleMonitor, rectangleWindow);

      ::rectangle_i32 rectangleList;

      rectangleList.left() = rectangleWindow.left();
      rectangleList.right() = rectangleWindow.left() + maximum(rectangleWindow.width(), sizeFull.cx()) + 20;
      rectangleList.top() = rectangleWindow.bottom();
      rectangleList.bottom() = rectangleWindow.bottom() + sizeFull.cy();

      information() << "on_drop_down (1) : " << rectangleList;

      if (i < 0)
      {

         m_pcombo->get_parent()->window_rectangle(rectangleMonitor);

      }

      information() << "on_drop_down (2) : " << rectangleList;

      if (rectangleList.bottom() > rectangleMonitor.bottom() - m_iScreenMargin)
      {

         rectangleList.bottom() = rectangleMonitor.bottom() - m_iScreenMargin;

         if (rectangleWindow.bottom() > (rectangleMonitor.top() + rectangleMonitor.height() * 2 / 3))
         {

            rectangleList.left() = rectangleWindow.left();
            rectangleList.right() = rectangleWindow.left() + maximum(rectangleWindow.width(), sizeFull.cx()) + 20;
            rectangleList.bottom() = rectangleWindow.top();
            rectangleList.top() = rectangleList.bottom() - sizeFull.cy();

            if (rectangleList.top() < rectangleMonitor.top() + m_iScreenMargin)
            {

               rectangleList.top() = rectangleMonitor.top() + m_iScreenMargin;

            }

         }

         //::rectangle_i32 rectangleListOver;

         //rectangleListOver.left() = rectangleList.left();
         //rectangleListOver.right() = rectangleList.right();
         //rectangleListOver.bottom() = rectangleWindow.top();
         //rectangleListOver.top() = rectangleWindow.top() - sizeFull.cy();

         //if (rectangleListOver.top() < rectangleMonitor.top() + m_iBorder)
         //{

         //   rectangleListOver.move_to(rectangleListOver.left(), rectangleMonitor.top());

         //}


         //if (rectangleListOver.bottom() > rectangleMonitor.bottom() - m_iBorder)
         //{

         //   rectangleListOver.bottom() = rectangleMonitor.bottom() - m_iBorder;

         //}

         //rectangleList = rectangleListOver;

      }

      if (rectangleList.right() > rectangleMonitor.right() - m_iScreenMargin)
      {

         rectangleList.offset(rectangleMonitor.right() - (rectangleList.right() - m_iScreenMargin), 0);

      }

      if (rectangleList.left() < rectangleMonitor.left())
      {

         rectangleList.move_left_to(0);

      }

      information() << "on_drop_down (3) : " << rectangleList;

      m_pcombo->m_pitemHover = current_item();

      information() << "on_drop_down (4) : " << rectangleList;

      if (!::is_set(m_pcombo->m_pitemHover))
      {

         m_pcombo->m_pitemHover = __new ::item(::e_element_item, 0);

      }

      information() << "on_drop_down (5) : " << rectangleList;

      ensure_item_visible_by_index(::item_index(m_pcombo->m_pitemHover));

      information() << "on_drop_down (6) : " << rectangleList;

      if (i < 0)
      {

         m_pcombo->get_parent()->screen_to_client()(rectangleList);

      }

      information() << "on_drop_down (7) : " << rectangleList;

      //if (!is_window())
      //{


      set_total_size(sizeFull);

      //m_bNeedPerformLayout = true;

      m_puserinteractionOwner = m_pcombo;

      information() << "on_drop_down (8) : " << rectangleList;

      order_top_most();

      set_tool_window();

      m_bTransparent = true;

      information() << "on_drop_down (9) : " << rectangleList;

      order_top_most();

      display(e_display_normal);

      set_activation(e_activation_no_activate);

      place(::rectangle_i32(rectangleList));

      information() << "on_drop_down (10) : " << rectangleList;

      //m_procedureOnAfterCreate=[this]()
      //{

      //   //auto & window_state = const_layout().sketch();

      //   //string str;

      //   //str.formatf("%d", window_state.m_edisplay.m_eenum);

      //   set_need_layout();

      //   set_need_redraw();

      //   post_redraw();

      //   information() << "on_drop_down (22)";

      //};

      set_owner(m_pcombo);

      add_graphical_output_purpose(this, ::graphics::e_output_purpose_screen);

      defer_create_interaction(i >= 0 ? nullptr : m_pcombo->get_parent());
      //if (!)
      //{

      //   m_pcombo->m_plistbox.release();

      //   throw ::exception(error_resource);

      //}

      //information() << "on_drop_down (11) : " << rectangleList;

//      }
//      else
//      {
//
//         place(::rectangle_i32(rectangleList).inflate(m_iBorder));
//
//         order_top_most();
//
//         display(e_display_normal);
//
//         set_activation(e_activation_no_activate);
//
//         auto & window_state = const_layout().sketch();
//
//         string str;
//
//         str.formatf("%d", window_state.m_edisplay.m_eenum);
//
//         set_need_layout();
//
//         set_need_redraw();
//
//         post_redraw();
//
//      }

      set_keyboard_focus();

   }


   void list_box::set_current_item(::item* pitem, const ::action_context& context)
   {

      if (m_pcombo)
      {

         m_pcombo->set_current_item(pitem, context);

      }
      else
      {

         ::user::scroll_base::set_current_item(pitem, context);

      }

   }


   void list_box::set_current_item_by_atom(const ::atom& atom, const ::action_context& context)
   {

      ::collection::index iSel = m_atoma.find_first(atom);

      if (iSel < 0)
      {

         return;

      }

      set_current_item(__new ::item(::e_element_item, iSel), context);

   }


   void list_box::set_current_item_by_text(const ::scoped_string& scopedstr, const ::action_context& context)
   {

      ::collection::index iSel = m_straList.find_first(scopedstr);

      if (iSel < 0)
      {

         return;

      }

      set_current_item(__new ::item(::e_element_item, iSel), context);

   }

   void list_box::set_current_item_by_index(::collection::index iIndex, const ::action_context& context)
   {

      if (iIndex < 0 || iIndex >= m_atoma.get_size())
      {

         return;

      }

      set_current_item(__new ::item(::e_element_item, iIndex), context);

   }


   string list_box::get_current_item_text()
   {

      auto pitem = current_item();

      if (::is_null(pitem))
      {

         return {};

      }

      ::collection::index iSel = pitem->m_item.m_iItem;

      if (iSel < 0)
      {

         return {};

      }

      string str = m_straList[iSel];

      return str;

   }


   ::atom list_box::get_current_item_atom()
   {

      auto pitem = current_item();

      if (::is_null(pitem))
      {

         return {};

      }

      ::collection::index iSel = pitem->m_item.m_iItem;

      if (iSel < 0)
      {

         return {};

      }

      auto atom = m_atoma[iSel];

      return atom;

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



