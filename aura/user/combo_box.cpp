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
      m_typeComboList         = __type(::user::combo_list);
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

      IGUI_MSG_LINK(WM_MOUSEMOVE, pchannel, this, &combo_box::_001OnMouseMove);
      IGUI_MSG_LINK(WM_MOUSELEAVE, pchannel, this, &combo_box::_001OnMouseLeave);
      IGUI_MSG_LINK(WM_LBUTTONDOWN, pchannel, this, &combo_box::_001OnLButtonDown);
      IGUI_MSG_LINK(WM_LBUTTONUP, pchannel, this, &combo_box::_001OnLButtonUp);
      IGUI_MSG_LINK(WM_LBUTTONDBLCLK, pchannel, this, &combo_box::_001OnLButtonDblClk);
      IGUI_MSG_LINK(WM_KEYDOWN,pchannel,this,&combo_box::_001OnKeyDown);
      IGUI_MSG_LINK(WM_KEYUP,pchannel,this,&combo_box::_001OnKeyUp);
      IGUI_MSG_LINK(WM_SETFOCUS,pchannel,this,&combo_box::_001OnSetFocus);
      IGUI_MSG_LINK(WM_KILLFOCUS, pchannel, this, &combo_box::_001OnKillFocus);
      IGUI_MSG_LINK(WM_SHOWWINDOW, pchannel, this, &combo_box::_001OnShowWindow);
      IGUI_MSG_LINK(WM_MOVE, pchannel, this, &combo_box::_001OnMove);

   }


   void combo_box::_001OnDrawStaticText(::draw2d::graphics_pointer & pgraphics)
   {

      string strText;

      if (m_bEdit)
      {

         _001GetText(strText);

      }
      else
      {

         _001GetListText(current_item(), strText);

      }

      ::rect rectClient;

      get_client_rect(rectClient);
      //::user::e_color colorText = color_text;

      ::color colorText(0, 0, 0, 255);

      //if (m_pdrawcontext != nullptr)
      //{

      //   if (m_pdrawcontext->is_control_selected())
      //   {

      //      if (m_pdrawcontext->is_control_hover())
      //      {

      //         colorText = ::color(192,192,192, 255);

      //      }
      //      else
      //      {

      //         colorText = ::color(255, 255, 255, 255);

      //      }

      //   }
      //   else
      //   {

      //      if (m_pdrawcontext->is_control_hover())
      //      {

      //         colorText = ::color(80, 80, 80, 255);;

      //      }
      //      else
      //      {

      //         colorText = ::color(80, 80, 80, 255);;

      //      }

      //   }

      //}

      //if(!select_text_color(pgraphics, colorText))
      //{

         pgraphics->set_text_color(colorText);

      //}

      ::rect rectText;

      get_element_rect(rectText, element_text);

      pgraphics->set_font(this);

      int iDrawTextFlags = DT_LEFT | DT_VCENTER;

      pgraphics->draw_text(strText, rectText, iDrawTextFlags);

   }


   void combo_box::get_simple_drop_down_open_arrow_polygon(point_array& pointa)
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


   void combo_box::_001OnDrawCombo(::draw2d::graphics_pointer & pgraphics)
   {

      ::rect rectClient;

      get_client_rect(rectClient);

      ::draw2d::brush_pointer br(e_create);

      if(m_bEdit)
      {

         ::user::plain_edit::_001OnDraw(pgraphics);

      }
      else
      {

         pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

         _001OnDrawStaticText(pgraphics);

      }

      pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

      ::rect rectDropDown;

      get_element_rect(rectDropDown, element_drop_down);

      ::rect rectDropIn(rectDropDown);

      //::user::e_color colorDropDown = color_button_background_disabled;
      ::color colorDropDown = ::color(127, 127, 127, 255);

      //if (m_pdrawcontext != nullptr)
      //{

      //   if (m_pdrawcontext->is_control_selected())
      //   {

      //      if (m_pdrawcontext->is_control_hover())
      //      {

      //         colorDropDown = ::color(80, 80, 180, 255);

      //      }
      //      else
      //      {

      //         colorDropDown = ::color(100, 100, 200, 255);

      //      }

      //   }
      //   else
      //   {

      //      if (m_pdrawcontext->is_control_hover())
      //      {

      //         colorDropDown = ::color(200, 200, 250, 255);

      //      }
      //      else
      //      {

      //         colorDropDown = ::color(192, 192, 192, 255);

      //      }

      //   }

      //}
      //else
      {

         if (Session.get_focus_ui() == this)
         {

            if (m_itemHover)
            {

               colorDropDown = ::color(200, 200, 250, 255);

            }
            else
            {

               colorDropDown = ::color(200, 200, 250, 255);

            }

         }
         else
         {

            if (m_itemHover)
            {

               colorDropDown = ::color(200, 200, 250, 255);

            }
            else
            {

               colorDropDown = ::color(200, 200, 250, 255);

            }

         }

      }

      color c(colorDropDown);

      c.hls_rate(0.0, 0.5, 0.1);

      br->create_solid(c);

      pgraphics->set(br);

      pgraphics->fill_rect(rectDropIn);

      ::draw2d::path_pointer path(e_create);

      point_array pointa;

      get_simple_drop_down_open_arrow_polygon(pointa);

      br->create_solid(ARGB(210, 0, 0, 0));

      pgraphics->set(br);

      pgraphics->fill_polygon(pointa);

   }


   ::draw2d::font_pointer combo_box::get_font(style * pstyle, e_element eelement, estate estate) const
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


   void combo_box::_000OnDraw1(::draw2d::graphics_pointer & pgraphics)
   {

      ::user::plain_edit::_000OnDraw1(pgraphics);

   }


   void combo_box::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      ::user::interaction::_001OnDraw(pgraphics);

      _001OnDrawCombo(pgraphics);

   }


   void combo_box::_001GetText(string & str) const
   {

      if(m_bEdit)
      {

         if(!m_itemCurrent)
         {

            ::user::plain_edit::_001GetText(str);

         }
         else
         {

            _001GetListText(m_itemCurrent, str);

         }

      }
      else
      {

         if(!m_itemCurrent)
         {

            str = m_strText;

         }
         else
         {

            _001GetListText(m_itemCurrent, str);

         }

      }

   }


   void combo_box::_001SetText(const string & str, const ::action_context & context)
   {

      if(m_bEdit)
      {

         ::user::plain_edit::_001SetText(str, context);

      }
      else
      {

         m_strText = str;

         auto pgraphics = ::draw2d::create_memory_graphics();

         plain_edit_on_after_change_text(pgraphics, context);

      }

   }


   index combo_box::_001GetListCount() const
   {

      return m_straList.get_count();

   }


   bool combo_box::get_element_rect(RECT * prect, e_element eelement)

   {

      if(eelement == element_text)
      {

         eelement = element_combo_edit;

      }

      return interaction::get_element_rect(prect, eelement);


   }


   void combo_box::on_hit_test(::user::item & item)
   {

      ::rect rectElement;

      if(get_element_rect(rectElement, element_drop_down))
      {

         if (rectElement.contains(item.m_pointHitTest))
         {

            item = element_drop_down;

            return;

         }

      }

      auto rectClient = get_client_rect();

      if (rectClient.contains(item.m_pointHitTest))
      {

         item = element_text;

         return;

      }

      item = element_none;

   }


   void combo_box::_001OnShowWindow(::message::message * pmessage)
   {

      SCAST_PTR(::message::show_window, pshowwindow, pmessage);

      if (!pshowwindow->m_bShow)
      {

         if (m_plist.is_set())
         {

            m_plist->post_message(WM_CLOSE);

         }

      }

   }


   void combo_box::_001OnMove(::message::message * pmessage)
   {

      if (is_drop_down())
      {

         ::rect rectWindow;

         get_window_rect(rectWindow);

         m_plist->on_drop_down(rectWindow, m_sizeFull);

      }

   }


   void combo_box::_001OnKeyDown(::message::message * pmessage)
   {

      SCAST_PTR(::message::key,pkey,pmessage);

      if(pkey->m_ekey == ::user::key_down)
      {

         if(!is_drop_down())
         {

            _001ShowDropDown();

         }

      }

   }


   void combo_box::_001OnKeyUp(::message::message * pmessage)
   {

      UNREFERENCED_PARAMETER(pmessage);

   }


   bool combo_box::plain_edit_is_enabled()
   {

      return m_bEdit;

   }


   void combo_box::_001OnMouseMove(::message::message * pmessage)
   {

      SCAST_PTR(::message::mouse, pmouse, pmessage);

      pmouse->previous();

      if (is_window_enabled())
      {

         if (!m_bEdit || m_itemHover == element_drop_down)
         {

            pmouse->m_ecursor = cursor_arrow;

            pmouse->m_bRet = true;

         }

      }

   }


   void combo_box::_001OnMouseLeave(::message::message * pmessage)
   {

      UNREFERENCED_PARAMETER(pmessage);

      m_itemHover = element_none;

      set_need_redraw();

   }


   void combo_box::_001OnLButtonDown(::message::message * pmessage)
   {

      SCAST_PTR(::message::mouse, pmouse, pmessage);

      if (is_window_enabled())
      {

         //auto point = screen_to_client(pmouse->m_point);

         auto eelementHit = hit_test(pmouse);

         if (eelementHit && (!m_bEdit || eelementHit == element_drop_down))
         {

            tick tickLastVisibilityChangeElapsed;

            if (m_plist.is_set())
            {

               tickLastVisibilityChangeElapsed = m_plist->m_tickLastVisibilityChange.elapsed();

            }

            if (m_plist.is_null() || tickLastVisibilityChangeElapsed > 300_tick)
            {

               _001ToggleDropDown();

            }
            else if (!m_plist->is_this_screen_visible())
            {

               //output_debug_string("test");

            }

            pmouse->m_bRet = true;

         }

      }

   }


   void combo_box::_001OnLButtonUp(::message::message * pmessage)
   {

      SCAST_PTR(::message::mouse, pmouse, pmessage);

      if (is_window_enabled())
      {

         //auto point = screen_to_client(pmouse->m_point);

         auto eelementHit = hit_test(pmouse);

         if (eelementHit && (!m_bEdit || eelementHit == element_drop_down))
         {

            pmouse->m_bRet = true;

         }

      }

   }


   void combo_box::_001OnSetFocus(::message::message * pmessage)
   {

   }


   void combo_box::_001OnKillFocus(::message::message * pmessage)
   {

      SCAST_PTR(::message::kill_focus, pkillfocus, pmessage);

      if (m_plist != nullptr)
      {

         if (m_plist->get_safe_handle() != pkillfocus->m_oswindowNew)
         {

            m_plist->post_message(WM_CLOSE);

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

         //   if (m_plist->m_tickLastHide.elapsed() < 300)
         //   {

         //      m_plist->m_tickLastHide -= 300;

         //      output_debug_string("asking to show too soon!! not going to show!!");

         //      return;

         //   }

         //}

         defer_create_combo_list();

         Session.on_show_user_input_popup(m_plist);

         auto pgraphics = ::draw2d::create_memory_graphics();

         m_plist->query_full_size(pgraphics, m_sizeFull);

         ::rect rectWindow;

         get_window_rect(rectWindow);

         m_plist->on_drop_down(rectWindow, m_sizeFull);

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

         get_wnd()->SetActiveWindow();

      }

   }


   void combo_box::defer_create_combo_list()
   {

      if(m_plist == nullptr)
      {

         auto plist = __id_create < combo_list >(m_typeComboList);

         m_plist = plist;

         if(m_plist == nullptr)
         {

            __throw(resource_exception());

         }

         m_plist->m_pcombo = this;

      }

      ::rect rectClient;

      get_client_rect(rectClient);

      m_plist->m_iItemHeight = MIN(24, rectClient.height());

   }


   void combo_box::set_current_item(const ::user::item & item, const ::action_context & context)
   {

      if (m_itemCurrent != item)
      {

         m_itemCurrent = item;

         ::user::control_event ev;

         ev.m_puie = this;

         ev.m_id = m_id;

         ev.m_eevent = ::user::event_after_change_cur_sel;

         ev.m_item = item;

         ev.m_actioncontext = context;

         route_control_event(&ev);

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

         _001SetText(strItem, context);

      }
      else
      {

         _001SetText(strItem, ::source_sync);

      }

   }


   //item combo_box::current_item()
   //{

   //   return m_itemCurrent;

   //}


   void combo_box::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

      if(m_bEdit)
      {

         ::user::plain_edit::on_layout(pgraphics);

      }


      /*      ::draw2d::font_pointer fontxyz(e_create);

            ::rect rectClient;

            get_client_rect(rectClient);

            fontxyz->m_dFontSize = rectClient.height() * 0.4;
            fontxyz->m_eunitFontSize = ::draw2d::unit_pixel;
            fontxyz->m_bUpdated = false;

            SetFont(fontxyz);*/



   }


   void combo_box::plain_edit_on_after_change_text(::draw2d::graphics_pointer & pgraphics, const ::action_context & context)
   {

      string str;

      if(m_bEdit)
      {

         ::user::plain_edit::_001GetText(str);

      }
      else
      {

         str = m_strText;

      }

      m_itemCurrent = _001FindListText(str);

      if (m_plist.is_set())
      {

         m_plist->on_change_combo_sel(m_itemCurrent);

      }

   }


   void combo_box::update(::update * pupdate)
   {

      if(m_bEdit)
      {

         ::user::plain_edit::update(pupdate);

      }
      //else
      //{

      //   ::user::control::update(::update * pupdate);

      //}


   }


   bool combo_box::create_window(::user::interaction * puiParent, const ::id & id)
   {

      if (!::user::plain_edit::create_window(puiParent, id))
      {

         return false;

      }

      return true;

   }


#ifdef WINDOWS_DESKTOP
   //Derived class is responsible for implementing these handlers
   //for owner/self draw controls (except for the optional DeleteItem)
   void combo_box::DrawItem(LPDRAWITEMSTRUCT)
   { ASSERT(FALSE); }
   void combo_box::MeasureItem(LPMEASUREITEMSTRUCT)
   { ASSERT(FALSE); }
   i32 combo_box::CompareItem(LPCOMPAREITEMSTRUCT)
   { ASSERT(FALSE); return 0; }
   void combo_box::DeleteItem(LPDELETEITEMSTRUCT)
   { /* default to nothing */ }
#endif

   bool combo_box::OnChildNotify(::message::base * pbase)
   {

      switch (pbase->m_id)
      {
      case WM_DRAWITEM:
#ifdef WINODWSEX
         DrawItem((LPDRAWITEMSTRUCT)pbase->m_lparam);
#else
         __throw(todo());
#endif
         break;
      case WM_MEASUREITEM:
#ifdef WINODWSEX
         MeasureItem((LPMEASUREITEMSTRUCT)pbase->m_lparam);
#else
         __throw(todo());
#endif
         break;
      case WM_COMPAREITEM:
#ifdef WINODWSEX
         *pResult = CompareItem((LPCOMPAREITEMSTRUCT)pbase->m_lparam);
#else
         __throw(todo());
#endif
         break;
      case WM_DELETEITEM:
#ifdef WINODWSEX
         DeleteItem((LPDELETEITEMSTRUCT)pbase->m_lparam);
#else
         __throw(todo());
#endif
         break;
      default:
         return ::user::interaction::OnChildNotify(pbase);
      }
      return TRUE;
   }


   void combo_box::GetLBText(index nIndex, string & rString)
   {

      ASSERT(is_window());

      GetLBText(nIndex, rString.get_string_buffer(GetLBTextLen(nIndex)));

      rString.release_string_buffer();

   }


   //::count combo_box::get_count()
   // { ASSERT(is_window()); return (count)send_message( CB_GETCOUNT, 0, 0); }
   //index combo_box::current_item()
   // { ASSERT(is_window()); return (index)send_message( CB_GETCURSEL, 0, 0); }
   //index combo_box::set_current_item(index nSelect)
   // { ASSERT(is_window()); return (index)send_message( CB_SETCURSEL, nSelect, 0); }
   //IA64: Assuming retval of CB_GETEDITSEL won't be expanded
   bool combo_box::GetEditSel(strsize & nStartChar, strsize & nEndChar)
   {
      /*      ASSERT(is_window()); u32 dw = u32(send_message( CB_GETEDITSEL, 0, 0));
            nStartChar = LOWORD(dw);
            nEndChar = LOWORD(dw);*/
      return TRUE;
   }
   bool combo_box::LimitText(strsize nMaxChars)
   {
      //ASSERT(is_window());
      //return send_message( CB_LIMITTEXT, nMaxChars, 0) != FALSE;
      return true;
   }

   bool combo_box::SetEditSel(strsize nStartChar, strsize nEndChar)
   {
      //ASSERT(is_window());
      //return send_message( CB_SETEDITSEL, 0, MAKELONG(nStartChar, nEndChar)) != FALSE;
      return true;
   }

   uptr combo_box::GetItemData(index nIndex)
   {

      //ASSERT(is_window());

      //return send_message( CB_GETITEMDATA, nIndex, 0);
      return 0;

   }

   index combo_box::SetItemData(index nIndex, uptr dwItemData)
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

   index combo_box::SetItemDataPtr(index nIndex, void * pData)
   {

      //ASSERT(is_window());

      //return SetItemData(nIndex, (uptr)(LPVOID)pData);

      return -1;

   }

   index combo_box::GetLBText(index nIndex, LPSTR pszText)

   {

      //ASSERT(is_window());

      //return (index)send_message( CB_GETLBTEXT, nIndex, (LPARAM)pszText);


      return -1;

   }

   strsize combo_box::GetLBTextLen(index nIndex)
   {

      //ASSERT(is_window());

      //return (strsize)send_message( CB_GETLBTEXTLEN, nIndex, 0);

      return -1;

   }


   void combo_box::ShowDropDown(bool bShowIt)
   {

      _001ShowDropDown(bShowIt);

   }


   index combo_box::DeleteString(index nIndex)
   {

      //ASSERT(is_window());

      //return (index) send_message( CB_DELETESTRING, nIndex, 0);

      return -1;

   }

   index combo_box::InsertString(index nIndex, const char * pszString)

   {

      //ASSERT(is_window());

      //return (i32)send_message( CB_INSERTSTRING, nIndex, (LPARAM)pszString);


      return -1;

   }


   void combo_box::ResetContent()
   {

      sync_lock sl(mutex());

      m_straList.remove_all();

      m_straValue.remove_all();

      m_itemCurrent = -1;
      m_itemHover = -1;

   }


   index combo_box::Dir(index attr, const char * pszWildCard)

   {

//      ASSERT(is_window());

//      return (index)send_message( CB_DIR, attr, (LPARAM)pszWildCard);


      return -1;

   }


   //index combo_box::FindString(index nStartAfter, const char * pszString)

   //{

   //   for (index i = nStartAfter++; i < m_straList.get_count(); i++)
   //   {

   //      if (m_straList[i].compare(pszString) == 0)

   //      {

   //         return i;

   //      }

   //   }

   //   return -1;

   //}


   //index combo_box::SelectString(index nStartAfter, const char * pszString, const ::action_context & context)

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


   void combo_box__copy()
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

   i32 combo_box::SetItemHeight(index nIndex, UINT cyItemHeight)
   {

      //ASSERT(is_window());

      //return (i32)send_message( CB_SETITEMHEIGHT, nIndex, MAKELONG(cyItemHeight, 0));

      return -1;

   }

   i32 combo_box::GetItemHeight(index nIndex)
   {

      //ASSERT(is_window());

      //return (i32)send_message( CB_GETITEMHEIGHT, nIndex, 0L);

      return -1;

   }

   index combo_box::FindStringExact(index nIndexStart, const char * pszFind)

   {

      //ASSERT(is_window());

      //return (index)send_message( CB_FINDSTRINGEXACT, nIndexStart, (LPARAM)pszFind);


      return -1;

   }

   i32 combo_box::SetExtendedUI(bool bExtended)
   {

      //ASSERT(is_window());

      //return (i32)send_message( CB_SETEXTENDEDUI, bExtended, 0L);

      return -1;

   }

   bool combo_box::GetExtendedUI()
   {

      //ASSERT(is_window());

      //return send_message( CB_GETEXTENDEDUI, 0, 0L) != 0;

      return false;

   }

   void combo_box::GetDroppedControlRect(RECT * prect)

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

   index combo_box::GetTopIndex()
   {

      //ASSERT(is_window());

      //return (index)send_message( CB_GETTOPINDEX, 0, 0);

      return -1;

   }

   index combo_box::SetTopIndex(index nIndex)
   {

      //ASSERT(is_window());

      //return (index)send_message( CB_SETTOPINDEX, nIndex, 0);

      return -1;

   }

   ::count combo_box::InitStorage(::count nItems, UINT nBytes)
   {

      //ASSERT(is_window());

      //return (count)send_message( CB_INITSTORAGE, (WPARAM)nItems, nBytes);

      return -1;

   }

   void combo_box::SetHorizontalExtent(UINT nExtent)
   {

      //ASSERT(is_window());

      //send_message( CB_SETHORIZONTALEXTENT, nExtent, 0);

   }

   UINT combo_box::GetHorizontalExtent()
   {

      //ASSERT(is_window());

      //return (UINT)send_message( CB_GETHORIZONTALEXTENT, 0, 0);

      return 0;

   }

   i32 combo_box::SetDroppedWidth(UINT nWidth)
   {

//      ASSERT(is_window());

//      return (i32)send_message( CB_SETDROPPEDWIDTH, nWidth, 0);

      return -1;

   }

   i32 combo_box::GetDroppedWidth()
   {

//      ASSERT(is_window());

//      return (i32)send_message( CB_GETDROPPEDWIDTH, 0, 0);

      return -1;

   }





   bool combo_box::_001GetListText(index iSel,string & str) const
   {

      str.Empty();

      if (iSel < 0)
         return false;

      if (iSel >= m_straList.get_count())
         return false;

      str = m_straList[iSel];

      return true;

   }


   index combo_box::_001FindListText(const string & str) const
   {


      //index combo_box::_001FindListText(const string & str) const
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

      //         if(str.compare_ci(strItem) == 0)
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
         return m_straList.find_first_ci(str);
      }

   }







   index combo_box::AddString(const char * pszString,uptr dwItemData)

   {

      sync_lock sl(mutex());

      ASSERT(m_edatamode == data_mode_opaque);

      if(m_edatamode != data_mode_opaque)
         return -1;

      m_straList.add(pszString);


      m_straValue.add(__str(dwItemData));

      return m_straList.get_upper_bound();

   }


   index combo_box::AddString(const char * pszString,const string & strValue)

   {

      ASSERT(m_edatamode == data_mode_string);

      if(m_edatamode != data_mode_string)
         return -1;

      m_straList.add(pszString);


      m_straValue.add(strValue);

      return m_straList.get_upper_bound();

   }


   bool combo_box::has_action_hover()
   {

      return ::user::plain_edit::m_itemHover || is_drop_down();

   }

   bool combo_box::has_text_input()
   {

      return m_bEdit && ::user::plain_edit::has_text_input();

   }


   void combo_box::set_current_item_by_string_value(const string & strValue, const ::action_context & context)
   {

      index iSel = m_straValue.find_first(strValue);

      if (iSel < 0)
      {

         return;

      }

      set_current_item(iSel,context);

   }


   void combo_box::set_current_item_by_data(uptr ui, const ::action_context & context)
   {

      index iSel = m_straValue.find_first(__str(ui));

      if (iSel < 0)
      {

         return;

      }

      set_current_item(iSel,context);

   }


   string combo_box::get_current_item_string_value()
   {

      index iSel = current_item();

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

      ASSERT(pdescriptor->get_control_type() == control_type_combo_box);

      if (!::user::interaction::create_control(pdescriptor))
      {

         TRACE("Failed to create control");

         return false;

      }

      display(display_none);

      m_bMultiLine = false;

      return true;

   }


   void combo_box::_001OnLButtonDblClk(::message::message * pmessage)
   {

      //output_debug_string("\nCOMBO_BOX: DOUBLE CLICK\n");

      _001OnLButtonDown(pmessage);

      //pmessage->m_bRet = true;

   }


   void combo_box::on_control_event(::user::control_event * pevent)
   {

      if(pevent->m_eevent == ::user::event_after_change_cur_sel)
      {

         if(pevent->m_puie == m_plist)
         {

            if (pevent->m_item == element_item)
            {

               set_current_item((::index) pevent->m_item.m_iItem, ::source_user);

            }

            _001ShowDropDown(false);

            pevent->Ret();

            set_need_redraw();

            post_redraw();

            keyboard_set_focus_next();

            return;

         }

      }

      ::user::plain_edit::on_control_event(pevent);

   }


} // namespace user



