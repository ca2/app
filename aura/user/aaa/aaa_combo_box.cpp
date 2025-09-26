#include "framework.h"


namespace user
{


   combo_box::combo_box()
   {

      user_combo_box_common_construct();

   }


   void combo_box::user_combo_box_common_construct()
   {

      m_bCaseSensitiveMatch   = false;
      m_typeatomComboList         = ::type < ::user::list_box >();
      m_estyle                = style_simply;
      m_bEdit                 = true;
      m_edatamode             = data_mode_opaque;

   }


   combo_box::~combo_box()
   {

      if(m_plist.is_set())
      {

         if(m_plist->is_window())
         {

            m_plist->DestroyWindow();

         }

      }

   }


   void combo_box::install_message_routing(::channel * pchannel)
   {

      if(m_bEdit)
      {

         ::user::plain_edit::install_message_routing(pchannel);

      }
      else
      {

         ::user::interaction::install_message_routing(pchannel);

      }

      USER_MESSAGE_LINK(::user::e_message_mouse_move, pchannel, this, &combo_box::on_message_mouse_move);
      USER_MESSAGE_LINK(::user::e_message_mouse_leave, pchannel, this, &combo_box::on_message_mouse_leave);
      USER_MESSAGE_LINK(::user::e_message_left_button_down, pchannel, this, &combo_box::on_message_left_button_down);
      USER_MESSAGE_LINK(::user::e_message_left_button_up, pchannel, this, &combo_box::on_message_left_button_up);
      USER_MESSAGE_LINK(::user::e_message_left_button_double_click, pchannel, this, &combo_box::on_message_left_button_double_click);
      USER_MESSAGE_LINK(::user::e_message_key_down,pchannel,this,&combo_box::on_message_key_down);
      USER_MESSAGE_LINK(::user::e_message_key_up,pchannel,this,&combo_box::on_message_key_up);
      USER_MESSAGE_LINK(::user::e_message_set_focus,pchannel,this,&combo_box::on_message_set_focus);
      USER_MESSAGE_LINK(::user::e_message_kill_focus, pchannel, this, &combo_box::on_message_kill_focus);
      USER_MESSAGE_LINK(::user::e_message_show_window, pchannel, this, &combo_box::on_message_show_window);
      USER_MESSAGE_LINK(::user::e_message_reposition, pchannel, this, &combo_box::on_message_move);

   }


   void combo_box::_001OnDrawStaticText(::draw2d::graphics_pointer & pgraphics)
   {

      string strText;

      if (m_bEdit)
      {

         get_text(strText);

      }
      else
      {

         _001GetListText(current_item(), strText);

      }

      ::double_rectangle rectangleX;

      this->rectangle(rectangleX);
      //::user::e_::color::color colorText = color_text;

      ::color::color colorText(0, 0, 0, 255);

      //if (m_pdrawcontext != nullptr)
      //{

      //   if (m_pdrawcontext->is_control_selected())
      //   {

      //      if (m_pdrawcontext->is_control_hover())
      //      {

      //         colorText = ::rgba(192, 192, 192, 255);

      //      }
      //      else
      //      {

      //         colorText = ::rgba(255, 255, 255, 255);

      //      }

      //   }
      //   else
      //   {

      //      if (m_pdrawcontext->is_control_hover())
      //      {

      //         colorText = ::rgba(80, 80, 80, 255);;

      //      }
      //      else
      //      {

      //         colorText = ::rgba(80, 80, 80, 255);;

      //      }

      //   }

      //}

      //if(!select_text_color(pgraphics, colorText))
      //{

         pgraphics->set_text_color(colorText);

      //}

      ::double_rectangle rectangleText;

      get_element_rectangle(rectangleText, e_element_text);

      pgraphics->set_font(this, ::e_element_none);

      int iDrawTextFlags = e_align_left_center;

      pgraphics->draw_text(strText, rectangleText, iDrawTextFlags);

   }


   void combo_box::get_simple_drop_down_open_arrow_polygon(point_array& pointa)
   {

      ::double_rectangle rectangleDropDown;

      get_element_rectangle(rectangleDropDown, e_element_drop_down);

      int cx = rectangleDropDown.width() / 3;

      int cy = cx * 2 / 3;

      ::int_point pointCenter = rectangleDropDown.center();

      pointa.add(pointCenter.x() - cx / 2, pointCenter.y() - cy / 2);

      pointa.add(pointCenter.x() + cx / 2, pointCenter.y() - cy / 2);

      pointa.add(pointCenter.x(), pointCenter.y() + cy / 2);

   }


   void combo_box::_001OnDrawCombo(::draw2d::graphics_pointer & pgraphics)
   {

      ::double_rectangle rectangleX;

      this->rectangle(rectangleX);

      auto pbrush = øcreate < ::draw2d::brush > ();

      if(m_bEdit)
      {

         ::user::plain_edit::_001OnDraw(pgraphics);

      }
      else
      {

         pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

         _001OnDrawStaticText(pgraphics);

      }

      pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

      ::double_rectangle rectangleDropDown;

      get_element_rectangle(rectangleDropDown, e_element_drop_down);

      ::double_rectangle rectangleDropIn(rectangleDropDown);

      //::user::e_::color::color colorDropDown = color_button_background_disabled;
      ::color::color colorDropDown = ::rgba(127, 127, 127, 255);

      //if (m_pdrawcontext != nullptr)
      //{

      //   if (m_pdrawcontext->is_control_selected())
      //   {

      //      if (m_pdrawcontext->is_control_hover())
      //      {

      //         colorDropDown = ::rgba(80, 80, 180, 255);

      //      }
      //      else
      //      {

      //         colorDropDown = ::rgba(100, 100, 200, 255);

      //      }

      //   }
      //   else
      //   {

      //      if (m_pdrawcontext->is_control_hover())
      //      {

      //         colorDropDown = ::rgba(200, 200, 250, 255);

      //      }
      //      else
      //      {

      //         colorDropDown = ::rgba(192, 192, 192, 255);

      //      }

      //   }

      //}
      //else
      {

         if (psession->get_focus_ui() == this)
         {

            if (m_pitemHover)
            {

               colorDropDown = ::rgba(200, 200, 250, 255);

            }
            else
            {

               colorDropDown = ::rgba(200, 200, 250, 255);

            }

         }
         else
         {

            if (m_pitemHover)
            {

               colorDropDown = ::rgba(200, 200, 250, 255);

            }
            else
            {

               colorDropDown = ::rgba(200, 200, 250, 255);

            }

         }

      }

      ::color::color color(colorDropDown);

      c.hls_rate(0.0, 0.5, 0.1);

      pbrush->create_solid(c);

      pgraphics->set(pbrush);

      pgraphics->fill_rectangle(rectangleDropIn);

      auto ppath = øcreate < ::draw2d::path > ();

      point_array pointa;

      get_simple_drop_down_open_arrow_polygon(pointa);

      pbrush->create_solid(argb(210, 0, 0, 0));

      pgraphics->set(pbrush);

      pgraphics->fill_polygon(pointa);

   }


   ::write_text::font_pointer combo_box::get_font(style * pstyle, enum_element eelement, estate estate) const
   {

      if (pstyle)
      {

         if (pstyle->m_pfontCombo)
         {

            return pstyle->m_pfontCombo;

         }
         else if (pstyle->m_pfont)
         {

            return pstyle->m_pfont;

         }

      }

      return nullptr;

   }


   void combo_box::_000OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      ::user::plain_edit::_000OnDraw(pgraphics);

   }


   void combo_box::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      ::user::interaction::_001OnDraw(pgraphics);

      _001OnDrawCombo(pgraphics);

   }


   void combo_box::get_text(string & str) const
   {

      if(m_bEdit)
      {

         if(!m_pitemCurrent)
         {

            ::user::plain_edit::get_text(str);

         }
         else
         {

            _001GetListText(m_pitemCurrent, str);

         }

      }
      else
      {

         if(!m_pitemCurrent)
         {

            str = m_strText;

         }
         else
         {

            _001GetListText(m_pitemCurrent, str);

         }

      }

   }


   void combo_box::set_text(const ::scoped_string & scopedstr, const ::action_context & context)
   {

      if(m_bEdit)
      {

         ::user::plain_edit::set_text(str, context);

      }
      else
      {

         m_strText = str;

         auto pgraphics = ::draw2d::create_memory_graphics();

         plain_edit_on_after_change_text(pgraphics, context);

      }

   }


   ::collection::index combo_box::_001GetListCount() const
   {

      return m_straList.get_count();

   }


   bool combo_box::get_element_rectangle(RECT32 * prect, enum_element eelement)

   {

      if(eelement == e_element_text)
      {

         eelement = e_element_combo_edit;

      }

      return interaction::get_element_rectangle(prect, eelement);


   }


   ::item_pointer combo_box::on_hit_test(const ::int_point &point, ::user::e_zorder ezorder)
   {

      ::double_rectangle rectangleElement;

      if(get_element_rectangle(rectangleElement, e_element_drop_down))
      {

         if (rectangleElement.contains(item.m_pointHitTest))
         {

            item = e_element_drop_down;

            return;

         }

      }

      auto rectangleX = this->rectangle();

      if (rectangleX.contains(item.m_pointHitTest))
      {

         item = e_element_text;

         return;

      }

      item = e_element_none;

   }


   void combo_box::on_message_show_window(::message::message * pmessage)
   {

      ::pointer<::message::show_window>pshowwindow(pmessage);

      if (!pshowwindow->m_bShow)
      {

         if (m_plist.is_set())
         {

            m_plist->post_message(::user::e_message_close);

         }

      }

   }


   void combo_box::on_message_move(::message::message * pmessage)
   {

      if (is_drop_down())
      {

         ::double_rectangle rectangleWindow;

         window_rectangle(rectangleWindow);

         m_plist->on_drop_down(rectangleWindow, m_sizeFull);

      }

   }


   void combo_box::on_message_key_down(::message::message * pmessage)
   {

      auto pkey = pmessage->m_union.m_pkey;

      if(pkey->m_ekey == ::user::e_key_down)
      {

         if(!is_drop_down())
         {

            _001ShowDropDown();

         }

      }

   }


   void combo_box::on_message_key_up(::message::message * pmessage)
   {

      __UNREFERENCED_PARAMETER(pmessage);

   }


   bool combo_box::plain_edit_is_enabled()
   {

      return m_bEdit;

   }


   void combo_box::on_message_mouse_move(::message::message * pmessage)
   {

      auto pmouse = pmessage->m_union.m_pmouse;

      pmouse->previous();

      if (is_window_enabled())
      {

         if (!m_bEdit || m_pitemHover == e_element_drop_down)
         {

            pmouse->m_ecursor = cursor_arrow;

            pmouse->m_bRet = true;

         }

      }

   }


   void combo_box::on_message_mouse_leave(::message::message * pmessage)
   {

      __UNREFERENCED_PARAMETER(pmessage);

      m_pitemHover = e_element_none;

      set_need_redraw();

   }


   void combo_box::on_message_left_button_down(::message::message * pmessage)
   {

      auto pmouse = pmessage->m_union.m_pmouse;

      if (is_window_enabled())
      {

         //auto point = screen_to_client(pmouse->m_point);

         auto eelementHit = hit_test(pmouse);

         if (eelementHit && (!m_bEdit || eelementHit == e_element_drop_down))
         {

            ::duration tickLastVisibilityChangeElapsed;

            if (m_plist.is_set())
            {

               tickLastVisibilityChangeElapsed = m_plist->m_durationLastVisibilityChange.elapsed();

            }

            if (m_plist.is_null() || tickLastVisibilityChangeElapsed > 300_tick)
            {

               _001ToggleDropDown();

            }
            else if (!m_plist->is_this_screen_visible())
            {

               //informationf("test");

            }

            pmouse->m_bRet = true;

         }

      }

   }


   void combo_box::on_message_left_button_up(::message::message * pmessage)
   {

      auto pmouse = pmessage->m_union.m_pmouse;

      if (is_window_enabled())
      {

         //auto point = screen_to_client(pmouse->m_point);

         auto eelementHit = hit_test(pmouse);

         if (eelementHit && (!m_bEdit || eelementHit == e_element_drop_down))
         {

            pmouse->m_bRet = true;

         }

      }

   }


   void combo_box::on_message_set_focus(::message::message * pmessage)
   {

   }


   void combo_box::on_message_kill_focus(::message::message * pmessage)
   {

      ::pointer<::message::kill_focus>pkillfocus(pmessage);

      if (m_plist != nullptr)
      {

         if (m_plist->get_safe_handle() != pkillfocus->m_oswindowNew)
         {

            m_plist->post_message(::user::e_message_close);

         }

      }

   }


   void combo_box::_001ToggleDropDown()
   {

      defer_create_combo_list();

      if (m_plist.is_set())
      {

         //m_plist->pred([&]()
         //{

            _001ShowDropDown(!m_plist->is_window_visible());

         //});

      }

   }


   void combo_box::_001ShowDropDown(bool bShow)
   {

      if(bShow)
      {

         //if (m_plist.is_set())
         //{

         //   if (m_plist->m_durationLastHide.elapsed() < 300)
         //   {

         //      m_plist->m_durationLastHide -= 300;

         //      informationf("asking to show too soon!! not going to show!!");

         //      return;

         //   }

         //}

         defer_create_combo_list();

         psession->on_show_user_input_popup(m_plist);

         auto pgraphics = ::draw2d::create_memory_graphics();

         m_plist->query_full_size(pgraphics, m_sizeFull);

         ::double_rectangle rectangleWindow;

         window_rectangle(rectangleWindow);

         m_plist->on_drop_down(rectangleWindow, m_sizeFull);

      }
      else
      {

         if(m_plist.is_set())
         {

            m_plist->display(false);

            m_plist->set_need_redraw();

            m_plist->post_redraw();

         }

         keyboard_set_focus();

         get_wnd()->set_active_window();

      }

   }


   void combo_box::defer_create_combo_list()
   {

      if(m_plist == nullptr)
      {

         auto plist = __id_create < list_box >(m_typeatomComboList);

         m_plist = plist;

         if(m_plist == nullptr)
         {

            throw ::exception(error_resource);

         }

         m_plist->m_pcombo = this;

      }

      ::double_rectangle rectangleX;

      this->rectangle(rectangleX);

      m_plist->m_iItemHeight = minimum(24, rectangleX.height());

   }


   void combo_box::set_current_item(const ::item & item, const ::action_context & context)
   {

      if (m_pitemCurrent != item)
      {

         m_pitemCurrent = item;

         ::topic topic;

         topic.m_puserinteraction = this;

         //topic.id() = id();

         topic.id() = ::id_after_change_cur_sel;

         topic.m_item = item;

         topic.m_actioncontext = context;

         route(&topic);

         set_need_redraw();

      }

      if (!is_window())
      {

         return;

      }

      string strItem;

      _001GetListText(item, strItem);

      if (m_bEdit)
      {

         set_text(strItem, context);

      }
      else
      {

         set_text(strItem, ::e_source_sync);

      }

   }


   //item combo_box::current_item()
   //{

   //   return m_pitemCurrent;

   //}


   void combo_box::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

      if(m_bEdit)
      {

         ::user::plain_edit::on_layout(pgraphics);

      }


      /*      ::write_text::font_pointer fontxyz(e_create);

            ::double_rectangle rectangleX;

            this->rectangle(rectangleX);

            fontxyz->m_dFontSize = rectangleX.height() * 0.4;
            fontxyz->m_eunitFontSize = ::draw2d::e_unit_pixel;
            fontxyz->m_bUpdated = false;

            SetFont(fontxyz);*/



   }


   void combo_box::plain_edit_on_after_change_text(::draw2d::graphics_pointer & pgraphics, const ::action_context & context)
   {

      string str;

      if(m_bEdit)
      {

         ::user::plain_edit::get_text(str);

      }
      else
      {

         str = m_strText;

      }

      m_pitemCurrent = _001FindListText(str);

      if (m_plist.is_set())
      {

         m_plist->on_change_combo_sel(m_pitemCurrent);

      }

   }


   void combo_box::handle(::topic * ptopic, ::handler_context * phandlercontext)
   {

      if(m_bEdit)
      {

         ::user::plain_edit::handle(ptopic, phandlercontext);

      }
      //else
      //{

      //   ::user::interaction::handle(::topic * ptopic, ::handler_context * phandlercontext);

      //}


   }


   bool combo_box::create_window(::user::interaction * puiParent, const ::atom & atom)
   {

      if (!::user::plain_edit::create_window(puiParent, atom))
      {

         return false;

      }

      return true;

   }


#ifdef WINDOWS_DESKTOP
   //Derived class is responsible for implementing these handlers
   //for owner/self draw controls (except for the optional DeleteItem)
   void combo_box::DrawItem(LPDRAWITEMSTRUCT)
   { ASSERT(false); }
   void combo_box::MeasureItem(LPMEASUREITEMSTRUCT)
   { ASSERT(false); }
   int combo_box::CompareItem(LPCOMPAREITEMSTRUCT)
   { ASSERT(false); return 0; }
   void combo_box::DeleteItem(LPDELETEITEMSTRUCT)
   { /* default to nothing */ }
#endif

   bool combo_box::OnChildNotify(::user::message * pusermessage)
   {

      switch (pusermessage->id())
      {
      case WM_DRAWITEM:
#ifdef WINODWSEX
         DrawItem((LPDRAWITEMSTRUCT)pusermessage->m_lparam);
#else
         throw ::exception(todo);
#endif
         break;
      case ::user::e_message_measure_item:
#ifdef WINODWSEX
         MeasureItem((LPMEASUREITEMSTRUCT)pusermessage->m_lparam);
#else
         throw ::exception(todo);
#endif
         break;
      case WM_COMPAREITEM:
#ifdef WINODWSEX
         *pResult = CompareItem((LPCOMPAREITEMSTRUCT)pusermessage->m_lparam);
#else
         throw ::exception(todo);
#endif
         break;
      case WM_DELETEITEM:
#ifdef WINODWSEX
         DeleteItem((LPDELETEITEMSTRUCT)pusermessage->m_lparam);
#else
         throw ::exception(todo);
#endif
         break;
      default:
         return ::user::interaction::OnChildNotify(pusermessage);
      }
      return true;
   }


   void combo_box::GetLBText(index nIndex, string & rString)
   {

      ASSERT(is_window());

      GetLBText(nIndex, rString.get_buffer(GetLBTextLen(nIndex)));

      rString.release_buffer();

   }


   //::collection::count combo_box::get_count()
   // { ASSERT(is_window()); return (count)send_message( CB_GETCOUNT, 0, 0); }
   //index combo_box::current_item()
   // { ASSERT(is_window()); return (index)send_message( CB_GETCURSEL, 0, 0); }
   //index combo_box::set_current_item(index nSelect)
   // { ASSERT(is_window()); return (index)send_message( CB_SETCURSEL, nSelect, 0); }
   //IA64: Assuming retval of CB_GETEDITSEL won't be expanded
   bool combo_box::GetEditSel(character_count & nStartChar, character_count & nEndChar)
   {
      /*      ASSERT(is_window()); unsigned int dw = unsigned int(send_message( CB_GETEDITSEL, 0, 0));
            nStartChar = LOWORD(dw);
            nEndChar = LOWORD(dw);*/
      return true;
   }
   bool combo_box::LimitText(character_count nMaxChars)
   {
      //ASSERT(is_window());
      //return send_message( CB_LIMITTEXT, nMaxChars, 0) != false;
      return true;
   }

   bool combo_box::SetEditSel(character_count nStartChar, character_count nEndChar)
   {
      //ASSERT(is_window());
      //return send_message( CB_SETEDITSEL, 0, MAKELONG(nStartChar, nEndChar)) != false;
      return true;
   }

   uptr combo_box::GetItemData(index nIndex)
   {

      //ASSERT(is_window());

      //return send_message( CB_GETITEMDATA, nIndex, 0);
      return 0;

   }

   ::collection::index combo_box::SetItemData(index nIndex, uptr dwItemData)
   {

      //ASSERT(is_window());

      //return (index)send_message( CB_SETITEMDATA, nIndex, (LPARAM)dwItemData);

      return -1;

   }

   void * combo_box::GetItemDataPtr(index nIndex)
   {

      //ASSERT(is_window()); return (LPVOID)GetItemData(nIndex);

      return nullptr;

   }

   ::collection::index combo_box::SetItemDataPtr(index nIndex, void * pData)
   {

      //ASSERT(is_window());

      //return SetItemData(nIndex, (uptr)(LPVOID)pData);

      return -1;

   }

   ::collection::index combo_box::GetLBText(index nIndex, char * pszText)

   {

      //ASSERT(is_window());

      //return (index)send_message( CB_GETLBTEXT, nIndex, (LPARAM)pszText);


      return -1;

   }

   character_count combo_box::GetLBTextLen(index nIndex)
   {

      //ASSERT(is_window());

      //return (character_count)send_message( CB_GETLBTEXTLEN, nIndex, 0);

      return -1;

   }


   void combo_box::ShowDropDown(bool bShowIt)
   {

      _001ShowDropDown(bShowIt);

   }


   ::collection::index combo_box::DeleteString(index nIndex)
   {

      //ASSERT(is_window());

      //return (index) send_message( CB_DELETESTRING, nIndex, 0);

      return -1;

   }

   ::collection::index combo_box::InsertString(index nIndex, const ::scoped_string & scopedstrString)

   {

      //ASSERT(is_window());

      //return (int)send_message( CB_INSERTSTRING, nIndex, (LPARAM)pszString);


      return -1;

   }


   void combo_box::reset_content()
   {

      synchronous_lock synchronouslock(this->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      m_straList.erase_all();

      m_straValue.erase_all();

      m_pitemCurrent = -1;
      m_pitemHover = -1;

   }


   ::collection::index combo_box::Dir(index attr, const ::scoped_string & scopedstrWildCard)

   {

//      ASSERT(is_window());

//      return (index)send_message( CB_DIR, attr, (LPARAM)pszWildCard);


      return -1;

   }


   //index combo_box::FindString(index nStartAfter, const ::scoped_string & scopedstrString)

   //{

   //   for (::collection::index i = nStartAfter++; i < m_straList.get_count(); i++)
   //   {

   //      if (m_straList[i].compare(scopedstrString) == 0)

   //      {

   //         return i;

   //      }

   //   }

   //   return -1;

   //}


   //index combo_box::SelectString(index nStartAfter, const ::scoped_string & scopedstrString, const ::action_context & context)

   //{

   //   index iSel = FindString(nStartAfter, pszString);


   //   if (iSel >= 0)
   //   {

   //      set_current_item(iSel, context);

   //   }

   //   return -1;

   //}

   //
   void combo_box::clear()
   {

      //ASSERT(is_window());

      //send_message(WM_CLEAR, 0, 0);

   }


   void combo_boxcopy()
   {

      //ASSERT(is_window());

      //send_message(WM_COPY, 0, 0);

   }

   void combo_box::Cut()
   {

      //ASSERT(is_window());

      //send_message( WM_CUT, 0, 0);

   }

   void combo_box::Paste()
   {

      //ASSERT(is_window());

      //send_message( WM_PASTE, 0, 0);

   }

   int combo_box::SetItemHeight(index nIndex, unsigned int cyItemHeight)
   {

      //ASSERT(is_window());

      //return (int)send_message( CB_SETITEMHEIGHT, nIndex, MAKELONG(cyItemHeight, 0));

      return -1;

   }

   int combo_box::GetItemHeight(index nIndex)
   {

      //ASSERT(is_window());

      //return (int)send_message( CB_GETITEMHEIGHT, nIndex, 0L);

      return -1;

   }

   ::collection::index combo_box::FindStringExact(index nIndexStart, const ::scoped_string & scopedstrFind)

   {

      //ASSERT(is_window());

      //return (index)send_message( CB_FINDSTRINGEXACT, nIndexStart, (LPARAM)pszFind);


      return -1;

   }

   int combo_box::SetExtendedUI(bool bExtended)
   {

      //ASSERT(is_window());

      //return (int)send_message( CB_SETEXTENDEDUI, bExtended, 0L);

      return -1;

   }

   bool combo_box::GetExtendedUI()
   {

      //ASSERT(is_window());

      //return send_message( CB_GETEXTENDEDUI, 0, 0L) != 0;

      return false;

   }

   void combo_box::GetDroppedControlRect(RECT32 * prect)

   {

      //ASSERT(is_window());

      //send_message( CB_GETDROPPEDCONTROLRECT, 0, (LPARAM)prect);


   }

   bool combo_box::GetDroppedState()
   {

      //ASSERT(is_window());

      //return send_message( CB_GETDROPPEDSTATE, 0, 0L) != 0;

      return false;

   }

   LCID combo_box::GetLocale()
   {

      //ASSERT(is_window());

      //return (LCID)send_message( CB_GETLOCALE, 0, 0);

      return -1; // everywhere

   }

   LCID combo_box::SetLocale(LCID nNewLocale)
   {

      //ASSERT(is_window());

      //return (LCID)send_message( CB_SETLOCALE, (WPARAM)nNewLocale, 0);

      return nNewLocale; // set where it is

   }

   ::collection::index combo_box::GetTopIndex()
   {

      //ASSERT(is_window());

      //return (index)send_message( CB_GETTOPINDEX, 0, 0);

      return -1;

   }

   ::collection::index combo_box::SetTopIndex(index nIndex)
   {

      //ASSERT(is_window());

      //return (index)send_message( CB_SETTOPINDEX, nIndex, 0);

      return -1;

   }

   ::collection::count combo_box::InitStorage(::collection::count nItems, unsigned int nBytes)
   {

      //ASSERT(is_window());

      //return (count)send_message( CB_INITSTORAGE, (WPARAM)nItems, nBytes);

      return -1;

   }

   void combo_box::SetHorizontalExtent(unsigned int nExtent)
   {

      //ASSERT(is_window());

      //send_message( CB_SETHORIZONTALEXTENT, nExtent, 0);

   }

   unsigned int combo_box::GetHorizontalExtent()
   {

      //ASSERT(is_window());

      //return (unsigned int)send_message( CB_GETHORIZONTALEXTENT, 0, 0);

      return 0;

   }

   int combo_box::SetDroppedWidth(unsigned int nWidth)
   {

//      ASSERT(is_window());

//      return (int)send_message( CB_SETDROPPEDWIDTH, nWidth, 0);

      return -1;

   }

   int combo_box::GetDroppedWidth()
   {

//      ASSERT(is_window());

//      return (int)send_message( CB_GETDROPPEDWIDTH, 0, 0);

      return -1;

   }





   bool combo_box::_001GetListText(::collection::index iSel,string & str) const
   {

      str.empty();

      if (iSel < 0)
         return false;

      if (iSel >= m_straList.get_count())
         return false;

      str = m_straList[iSel];

      return true;

   }


   ::collection::index combo_box::_001FindListText(const ::scoped_string & scopedstr) const
   {


      //index combo_box::_001FindListText(const ::scoped_string & scopedstr) const
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


      if(m_bCaseSensitiveMatch)
      {
         return m_straList.find_first(str);
      }
      else
      {
         return m_straList.case_insensitive_find_first(str);
      }

   }







   ::collection::index combo_box::AddString(const ::scoped_string & scopedstrString,uptr dwItemData)

   {

      synchronous_lock synchronouslock(this->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      ASSERT(m_edatamode == data_mode_opaque);

      if(m_edatamode != data_mode_opaque)
         return -1;

      m_straList.add(scopedstrString);


      m_straValue.add(as_string(dwItemData));

      return m_straList.get_upper_bound();

   }


   ::collection::index combo_box::AddString(const ::scoped_string & scopedstrString, const ::scoped_string & scopedstrValue)

   {

      ASSERT(m_edatamode == data_mode_string);

      if(m_edatamode != data_mode_string)
         return -1;

      m_straList.add(scopedstrString);


      m_straValue.add(strValue);

      return m_straList.get_upper_bound();

   }


   bool combo_box::has_action_hover()
   {

      return ::user::plain_edit::m_pitemHover || is_drop_down();

   }

   bool combo_box::has_text_input()
   {

      return m_bEdit && ::user::plain_edit::has_text_input();

   }


   void combo_box::set_current_item_by_string_value(const ::scoped_string & scopedstrValue, const ::action_context & context)
   {

      ::collection::index iSel = m_straValue.find_first(strValue);

      if (iSel < 0)
      {

         return;

      }

      set_current_item(iSel,context);

   }


   void combo_box::set_current_item_by_data(uptr u, const ::action_context & context)
   {

      ::collection::index iSel = m_straValue.find_first(as_string(u));

      if (iSel < 0)
      {

         return;

      }

      set_current_item(iSel,context);

   }


   string combo_box::get_current_item_string_value()
   {

      ::collection::index iSel = current_item();

      if (iSel < 0)
      {

         return "";

      }

      string str = m_straValue[iSel];

      return str;

   }


   bool combo_box::keyboard_focus_is_focusable()
   {

      return is_window_enabled() && is_window_visible();

   }


   bool combo_box::is_drop_down()
   {

      return m_plist != nullptr && m_plist->is_window_visible();

   }


   bool combo_box::create_control(class control_descriptor * pdescriptor)
   {

      ASSERT(pdescriptor->get_control_type() == e_control_type_combo_box);

      if (!::user::interaction::create_control(pdescriptor))
      {

         informationf("Failed to create control");

         return false;

      }

      display(e_display_none);

      m_bMultiLine = false;

      return true;

   }


   void combo_box::on_message_left_button_double_click(::message::message * pmessage)
   {

      //informationf("\nCOMBO_BOX: DOUBLE CLICK\n");

      on_message_left_button_down(pmessage);

      //pmessage->m_bRet = true;

   }


   void combo_box::handle(::topic * ptopic, ::handler_context * phandlercontext)
   {

      if(ptopic->id() == ::id_after_change_cur_sel)
      {

         if(ptopic->user_interaction() == m_plist)
         {

            if (ptopic->m_item == e_element_item)
            {

               set_current_item((::collection::index) ptopic->m_item.m_iItem, ::e_source_user);

            }

            _001ShowDropDown(false);

            ptopic->Ret();

            set_need_redraw();

            post_redraw();

            keyboard_set_focus_next();

            return;

         }

      }

      ::user::plain_edit::handle(ptopic, phandlercontext);

   }


} // namespace user



