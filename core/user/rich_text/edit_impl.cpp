#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "core/user/rich_text/_rich_text.h"
#include "core/user/userex/_userex.h"
#endif
#include "acme/const/timer.h"


namespace user
{


   namespace rich_text
   {


      edit_impl::edit_impl()
      {

         m_bComposing = false;
         m_bEditable2 = true;
         m_bClickThrough = false;
         m_bPendingSelectionChange = false;

      }


      ::estatus edit_impl::initialize(::layered * pobjectContext)
      {

         auto estatus = ::user::rich_text::edit::initialize(pobjectContext);

         if (!estatus)
         {

            return estatus;

         }

         m_bComposing = false;

         estatus = __construct_new(m_pdata);

         m_bPendingSelectionChange = false;

         m_bEditable2 = true;

         m_pdata->m_pedit = this;

         m_bKeyPressed = false;

         m_bSelDrag = false;

         m_bClickThrough = false;

         return estatus;

      }


      edit_impl::~edit_impl()
      {

      }


      bool edit_impl::update_data(bool bSaveAndValidate)
      {

         if (bSaveAndValidate)
         {

         }
         else
         {

            set_need_layout();

            set_need_redraw();

         }

         return true;

      }


      void edit_impl::assert_valid() const
      {

         ::user::interaction::assert_valid();

      }


      void edit_impl::dump(dump_context & dumpcontext) const
      {

         ::user::interaction::dump(dumpcontext);

      }


      void edit_impl::install_message_routing(::channel * pchannel)
      {

         ::user::interaction::install_message_routing(pchannel);

         MESSAGE_LINK(e_message_create, pchannel, this, &edit_impl::_001OnCreate);
         MESSAGE_LINK(e_message_destroy, pchannel, this, &edit_impl::_001OnDestroy);
         MESSAGE_LINK(e_message_show_window, pchannel, this, &edit_impl::_001OnShowWindow);
         MESSAGE_LINK(e_message_left_button_down, pchannel, this, &edit_impl::_001OnLButtonDown);
         MESSAGE_LINK(e_message_left_button_up, pchannel, this, &edit_impl::_001OnLButtonUp);
         MESSAGE_LINK(e_message_mouse_move, pchannel, this, &edit_impl::_001OnMouseMove);
         MESSAGE_LINK(e_message_mouse_leave, pchannel, this, &edit_impl::_001OnMouseLeave);
         MESSAGE_LINK(e_message_key_down, pchannel, this, &edit_impl::_001OnKeyDown);
         MESSAGE_LINK(e_message_key_up, pchannel, this, &edit_impl::_001OnKeyUp);
         MESSAGE_LINK(e_message_set_focus, pchannel, this, &edit_impl::_001OnSetFocus);
         MESSAGE_LINK(e_message_kill_focus, pchannel, this, &edit_impl::_001OnKillFocus);

#ifdef WINDOWS_DESKTOP

         imm_client::install_message_routing(pchannel);

#endif

      }


      void edit_impl::_001OnCreate(::message::message * pmessage)
      {

         SCAST_PTR(::message::create, pcreate, pmessage);

         pcreate->previous();

         if (pcreate->m_bRet)
         {

            return;

         }

         auto psession = Session;



         m_pdata->set_mutex(mutex());

         fork([this]()
            {

               GetTopLevelFrame()->tool_window(::user::e_tool_font, true);

            });

#if !defined(APPLE_IOS) && !defined(ANDROID)
         psession->keyboard(); // trigger keyboard creationg
#endif


         SetTimer(100, 100, nullptr);

         SetTimer(e_timer_redraw, 200, nullptr); // Caret

      }


      void edit_impl::_001OnDestroy(::message::message * pmessage)
      {

      }


      void edit_impl::_001OnShowWindow(::message::message * pmessage)
      {

         SCAST_PTR(::message::show_window, pshowwindow, pmessage);

         if (pshowwindow->m_bShow)
         {

            if (is_text_editable() && m_bEditable2)
            {

               SetTimer(250, 500, nullptr); // Caret

            }

         }
         else
         {

            auto pformattool = get_format_tool(false);

            if (pformattool != nullptr && pformattool->is_showing_for_ui(this))
            {

               pformattool->hide();

            }

         }

      }


      void edit_impl::_001OnSetFocus(::message::message * pmessage)
      {


         UNREFERENCED_PARAMETER(pmessage);

         //SCAST_PTR(::message::set_focus, psetfocus, pmessage);

         if (!is_text_editable())
         {

            return;

         }

         auto pformattool = get_format_tool(true);

         pformattool->show_for_ui(this);

      }


      void edit_impl::_001OnKillFocus(::message::message * pmessage)
      {

         SCAST_PTR(::message::kill_focus, pkillfocus, pmessage);

         auto pformattool = get_format_tool(false);

         if (pformattool != nullptr && pformattool->is_showing_for_ui(this))
         {

            ::user::primitive_impl * pimplNew = oswindow_interaction_impl(pkillfocus->m_oswindowNew);

            ::user::interaction * pinteraction = nullptr;

            if (pimplNew != nullptr)
            {

               pinteraction = pimplNew->m_puserinteraction;

            }

            if (pkillfocus->m_oswindowNew == pformattool->get_safe_handle()
                  || pformattool->is_ascendant_or_owner_of(pinteraction, true))
            {

               output_debug_string("Window winning focus is own font format tool");

               return;

            }

            pformattool->hide();

         }

      }


      void edit_impl::insert_text(string str, bool bForceNewStep)
      {

         m_pdata->_001InsertText(str);

      }


      void edit_impl::on_selection_change()
      {

         auto pformattool = get_format_tool(false);

         if (pformattool.is_set())
         {

            m_pdata->on_selection_change(pformattool->m_formata[0]);

            pformattool->update_data(false);

         }

      }


      void edit_impl::_001OnLButtonDown(::message::message * pmessage)
      {

         SCAST_PTR(::message::mouse, pmouse, pmessage);

         if (!is_text_editable())
         {

            return;

         }

         auto psession = Session;

         auto item = hit_test(pmouse);

         if (item.is_set())
         {

            auto pformattool = get_format_tool(true);

            pformattool->show_for_ui(this);

            m_bSelDrag = true;

            if (psession->is_key_pressed(key_shift))
            {

               if (item < min(m_pdata->m_iSelBeg, m_pdata->m_iSelEnd))
               {

                  m_pdata->m_iSelBeg = max(m_pdata->m_iSelBeg, m_pdata->m_iSelEnd);

               }
               else if (item > max(m_pdata->m_iSelBeg, m_pdata->m_iSelEnd))
               {

                  m_pdata->m_iSelBeg = min(m_pdata->m_iSelBeg, m_pdata->m_iSelEnd);

               }

            }
            else
            {

               m_pdata->m_iSelBeg = item;

            }

            m_pdata->m_iSelEnd = item;

            m_pdata->internal_update_sel_char();

            SetCapture();

            psession->set_keyboard_focus(this);

            psession->user()->set_mouse_focus_LButtonDown(this);

            pmouse->m_bRet = true;

            m_bPendingSelectionChange = true;

            set_need_redraw();

            post_redraw();

         }
         else if(m_bClickThrough)
         {

            auto pformattool = get_format_tool(false);

            if (pformattool->is_window_visible())
            {

               pformattool->hide();

            }

         }
         else
         {

            pmouse->m_bRet = true;

         }

      }


      void edit_impl::_001OnLButtonUp(::message::message* pmessage)
      {

         SCAST_PTR(::message::mouse, pmouse, pmessage);

         ReleaseCapture();

         if (!is_text_editable())
         {

            return;

         }

         m_bSelDrag = false;

         auto item = hit_test(pmouse);

         auto psession = Session;

         if (item.is_set() && psession->user()->get_mouse_focus_LButtonDown() == this)
         {

            m_pdata->m_iSelEnd = item;

            m_pdata->internal_update_sel_char();

            pmouse->m_bRet = true;

            on_reset_focus_start_tick();

            m_bPendingSelectionChange = true;

            set_need_redraw();

            post_redraw();

         }
         else if (!m_bClickThrough)
         {

            pmouse->m_bRet = true;

         }

      }


      void edit_impl::_001OnMouseMove(::message::message* pmessage)
      {

         SCAST_PTR(::message::mouse, pmouse, pmessage);

         if (!is_text_editable())
         {

            return;

         }

         m_itemHover = hit_test(pmouse);

         if (m_itemHover.is_set())
         {

            pmouse->m_ecursor = cursor_text_select;

            pmouse->m_bRet = true;

         }

         if (m_bSelDrag)
         {

            if (m_itemHover.m_iItem != m_pdata->m_iSelEnd)
            {

               m_pdata->m_iSelEnd = m_itemHover;

               m_pdata->internal_update_sel_char();

               pmouse->m_bRet = true;

               m_bPendingSelectionChange = true;

               set_need_redraw();

               post_redraw();

            }

         }

         if (!m_bClickThrough)
         {

            pmouse->m_ecursor = cursor_text_select;

            pmouse->m_bRet = true;

         }

      }


      ::sized edit_impl::get_size()
      {

         if (is_picture_enabled())
         {

            return m_ppictureimpl->m_rect.size();

         }
         else
         {

            ::rect rect;

            get_window_rect(rect);

            return rect.size();

         }

      }



      void edit_impl::_001OnMouseLeave(::message::message * pmessage)
      {

         ReleaseCapture();

         set_need_redraw();

      }


      bool edit_impl::get_element_rect(RECT32 * prect, index i, e_element eelement)

      {

         if (eelement == ::user::element_icon)
         {

            if (!get_item_rect(prect, i))

            {

               return false;

            }

            return true;

         }
         else if (eelement == ::user::element_text)
         {

            if (!get_item_rect(prect, i))

            {

               return false;

            }

            return true;


         }

         return false;

      }

      bool edit_impl::get_item_rect(RECT32 * prect, index i)

      {

         return true;

      }


      __pointer(span) edit_impl::add_span(::e_align ealignNewLine)
      {

         return m_pdata->add_span(ealignNewLine);

      }


      double edit_impl::get_rotate()
      {

         if (is_picture_enabled())
         {

            return m_ppictureimpl->m_dRotate;

         }

         return 0.0;

      }



      void edit_impl::on_hit_test(::user::item & item)
      {

         //::pointd pointHit = item.m_pointHitTest;

         //if (is_picture_enabled())
         //{
         //
         //   //pointHit -= get_rect_for_picture().origin();

         //   // 1. += get_rect_for_picture();

         //   _001ClientToParent(pointHit);

         //   // 2. += get_rect_for_picture();

         //   drag_rtransform_point(pointHit);

         //   // 3. += get_rect_for_picture();

         //   //_001ParentToClient(pointHit);

         //   // 4. += get_rect_for_picture();

         //   //m_ppictureimpl->m_dZoom

         //}



         item = m_pdata->hit_test(item.m_pointHitTest);

      }


      void edit_impl::_001GetText(string & str) const
      {

         m_pdata->_001GetText(str);

      }

      void edit_impl::_001GetLayoutText(string & str) const
      {

         m_pdata->_001GetLayoutText(str);

      }


      void edit_impl::draw_control_background(::draw2d::graphics_pointer & pgraphics)
      {

         //::aura::draw_context* pdrawcontext = pgraphics->::aura::simple_chain < ::aura::draw_context >::get_last();

         //::rect rectClient;

         //if (pdrawcontext != nullptr)
         //{

         //   rectClient = pdrawcontext->m_rectClient;

         //}
         //else
         //{

         //   get_client_rect(rectClient);

         //}

         //if (_001IsBackgroundBypass())
         //{

         //}
         //else if (_001IsTranslucent())
         //{

         //   pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

         //   color32_t crBackground = _001GetColor(::user::color_background, ARGB(128, 255, 255, 255));

         //   //if (colorref_get_r_value(crBackground) != 255)
         //   //{

         //   //   output_debug_string("no full red");

         //   //}

         //   //crBackground = ARGB(255, 100, 200, 255);

         //   if (crBackground != 0)
         //   {

         //      pgraphics->fill_rect(rectClient, crBackground);

         //   }

         //}
         //else
         //{

         //   pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

         //   color32_t crBackground = _001GetColor(m_ecolorBackground, ARGB(200, 255, 255, 255));

         //   //if (colorref_get_r_value(crBackground) != 255)
         //   //{

         //   //   output_debug_string("no full red");

         //   //}

         //   //crBackground = ARGB(255, 255, 200, 100);

         //   pgraphics->fill_rect(rectClient, crBackground);

         //}

         ::user::rich_text::edit::draw_control_background(pgraphics);

      }





      void edit_impl::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
      {

         if (!is_picture_enabled())
         {

       /*     picture::_001OnDraw(pgraphics);

         }
         else
         {*/

            ::rect rectClient;

            get_client_rect(rectClient);

            pgraphics->fill_rect(rectClient, ARGB(40, 255, 255, 255));

            draw_impl(pgraphics);

         }

      }


      void edit_impl::draw_impl(::draw2d::graphics_pointer & pgraphics)
      {

         sync_lock sl(mutex());

         //pgraphics->OffsetViewportOrg(m_pointScroll.x, m_pointScroll.y);

         m_pdata->_001OnDraw(pgraphics);

      }


      bool edit_impl::set_text_editable(bool bEditable)
      {

         m_bEditable2 = bEditable;

         if (bEditable)
         {

            if (is_text_editable() && is_window_visible())
            {

               auto pformattool = get_format_tool(true);

               //if (!ptool->is_window_visible() || !ptool->is_showing_for_ui(this))
               {

                  pformattool->show_for_ui(this);

               }

               SetTimer(250, 500, nullptr); // Caret

            }

         }
         else
         {

            auto pformattool = get_format_tool(false);

            if (pformattool != nullptr && pformattool->is_showing_for_ui(this))
            {

               pformattool->hide();

            }

            if(has_focus())
            {

               keyboard_set_focus_next();

            }

         }

         return m_bEditable2;

      }


      bool edit_impl::is_text_editable()
      {

         return is_window_enabled() && m_bEditable2;

      }


      bool edit_impl::is_text_editor()
      {

         return true;

      }


      bool edit_impl::_001IsPointInside(::point pointParam)
      {

         if (is_picture_enabled())
         {

            pointd point(pointParam);

            _001ScreenToClient(point);

            ::rect rWindow;

            get_window_rect(rWindow);

            rectd rectWindow;

            __copy(rectWindow, rWindow);

            GetParent()->_001ScreenToClient(rectWindow);

            copy(rectWindow, rectWindow);

            point += rectWindow.top_left();

            _rtransform_point(point);

            point -= rectWindow.top_left();

            auto rectClient = get_client_rect();

            return rectClient.contains(::point(point));

         }

         return ::user::interaction::_001IsPointInside(pointParam);

      }


      bool edit_impl::_001GetItemText(string & str, index iItem)
      {

         return false;

      }


      void edit_impl::on_layout(::draw2d::graphics_pointer & pgraphics)
      {

         ::draw2d::graphics_pointer graphics(e_create);

         pgraphics->CreateCompatibleDC(NULL);

         m_pdata->do_layout(pgraphics);

      }


      void edit_impl::on_control_event(::user::control_event * pevent)
      {

         if (pevent->m_eevent == ::user::event_after_change_cur_sel)
         {

            auto pformattool = get_format_tool(false);

            if (pevent->m_puie == pformattool)
            {

               if (pformattool->m_eattribute & attribute_align)
               {

                  box_align(m_pdata->m_spana, find_span(m_pdata->m_spana, m_pdata->m_iSelEnd), pformattool->m_formata[0]->m_ealign);

               }

               m_pdata->_001SetSelFontFormat(pformattool->m_formata[0], pformattool->m_eattribute);

               pformattool->m_eattribute.clear();

               set_need_layout();

               set_need_redraw();

               post_redraw();

               SetFocus();

               //pevent->Ret();

               //return;

            }

         }

         return ::user::interaction::on_control_event(pevent);

      }


      __pointer(format_tool) edit_impl::get_format_tool(bool bCreate)
      {

         auto pframe = GetTopLevelFrame();

         if (is_null(pframe))
         {

            return nullptr;

         }

         auto pformattool = pframe->tool_window(::user::e_tool_font, bCreate);

         return pformattool;

      }


      bool edit_impl::keyboard_focus_is_focusable()
      {

         return is_window_visible() && is_text_editable();

      }


      void edit_impl::keyboard_focus_OnChar(::message::message * pmessage)
      {

         if (!is_text_editable())
         {

            return;

         }

         _001OnChar(pmessage);

      }


      void edit_impl::_001OnKeyDown(::message::message * pmessage)
      {

         //sync_lock sl(mutex());

         {

            ::user::control_event ev;

            ev.m_puie = this;

            ev.m_eevent = ::user::event_key_down;

            ev.m_pmessage = pmessage;

            ev.m_actioncontext = ::source_user;

            on_control_event(&ev);

            if (ev.m_bRet)
            {

               return;

            }

         }

         SCAST_PTR(::message::key, pkey, pmessage);

         auto psession = Session;

         if (pkey->m_ekey == ::user::key_return)
         {

            if (psession->is_key_pressed(::user::key_control) && psession->is_key_pressed(::user::key_alt))
            {

               pkey->m_bRet = false;

               return;

            }

         }
         else if (pkey->m_ekey == ::user::key_tab)
         {

            if (psession->is_key_pressed(::user::key_control) && psession->is_key_pressed(::user::key_alt))
            {

               pkey->m_bRet = false;

               return;

            }

         }
         else if (pkey->m_ekey == ::user::key_alt)
         {

            pkey->m_bRet = false;

            return;

         }
         else if (pkey->m_ekey == ::user::key_escape)
         {

            ::user::control_event ev;

            ev.m_puie = this;

            ev.m_eevent = ::user::event_escape;

            ev.m_actioncontext = ::source_user;

            on_control_event(&ev);

            if (!ev.m_bRet && ev.m_bOk)
            {

               on_action("escape");

            }

            pmessage->m_bRet = true;

            return;

         }
         else if (pkey->m_ekey == ::user::key_c)
         {

            if (psession->is_key_pressed(::user::key_control))
            {

               pkey->m_bRet = true;

               string str;

               _001GetSelText(str);

               if (str.is_empty())
               {

                  _001GetSelLineText(str);

               }

               psession->copydesk().set_plain_text(str);

               return;

            }

         }
         else if (pkey->m_ekey == ::user::key_v)
         {

            if (psession->is_key_pressed(::user::key_control))
            {

               pkey->m_bRet = true;

               if (is_window_enabled())
               {

                  string str;

                  psession->copydesk().get_plain_text(str);

                  m_pdata->_001InsertText(str);

               }

               return;

            }

         }
         else if (pkey->m_ekey == ::user::key_x)
         {

            if (psession->is_key_pressed(::user::key_control))
            {

               pkey->m_bRet = true;

               string str;

               _001GetSelText(str);

               psession->copydesk().set_plain_text(str);

               if (is_window_enabled())
               {

                  _001OnDeleteText();

               }

               return;

            }

         }

         m_pkeymessageLast = pkey;

         m_bKeyPressed = true;

         key_to_char(m_pkeymessageLast);

         pkey->m_bRet = true;

      }


      void edit_impl::_001OnKeyUp(::message::message * pmessage)
      {

         SCAST_PTR(::message::key, pkey, pmessage);

         auto psession = Session;

         if (pkey->m_ekey == ::user::key_return)
         {

            if (psession->is_key_pressed(::user::key_control)  && psession->is_key_pressed(::user::key_alt))
            {
               pkey->m_bRet = false;
               return;
            }
         }
         else if (pkey->m_ekey == ::user::key_alt)
         {
            pkey->m_bRet = false;
         }
         m_bKeyPressed = false;
      }


      void edit_impl::_001OnTimer(::timer * ptimer)
      {

         ::user::interaction::_001OnTimer(ptimer);

         if (ptimer->m_uEvent >= 100 && ptimer->m_uEvent <= 200)
         {
            if (has_focus())
            {

               //_001OnKeyboardFocusTimer(ptimer->m_uEvent - 100);

            }
         }
         else if (ptimer->m_uEvent == 500 || ptimer->m_uEvent == 501)
         {
            if (ptimer->m_uEvent == 500)
            {
               KillTimer(500);
               SetTimer(501, 300, nullptr);
            }
            key_to_char(m_pkeymessageLast);
         }
         else if (ptimer->m_uEvent == e_timer_redraw)
         {

            // Caret

            if (is_text_editable() && is_window_visible() && has_focus())
            {

               set_need_redraw();

               post_redraw();

            }

         }

      }


      void edit_impl::key_to_char(::message::key * pkey)
      {

         ::message::key & key = *pkey;

         auto psession = Session;

         if (key.m_ekey == ::user::key_shift || key.m_ekey == ::user::key_lshift || key.m_ekey == ::user::key_rshift
               || key.m_ekey == ::user::key_control || key.m_ekey == ::user::key_lcontrol || key.m_ekey == ::user::key_rcontrol
               || key.m_ekey == ::user::key_alt || key.m_ekey == ::user::key_lalt || key.m_ekey == ::user::key_ralt
            )
         {

            return;

         }

         if (key.m_ekey == ::user::key_right || key.m_ekey == ::user::key_up
               || key.m_ekey == ::user::key_left || key.m_ekey == ::user::key_down)
         {

            _001OnChar(&key);

            return;

         }

         bool bShift = psession->is_key_pressed(::user::key_shift);

         if (key.m_nChar < 256 && isalpha((i32)key.m_nChar))
         {

            if (bShift)
            {

               key.m_nChar = toupper((i32)key.m_nChar);

            }
            else
            {

               key.m_nChar = tolower((i32)key.m_nChar);

            }

         }

         _001OnChar(&key);

      }


      void edit_impl::_001OnDeleteText()
      {

         on_reset_focus_start_tick();

         {

            sync_lock sl(m_pdata->mutex());

            strsize i1 = m_pdata->get_sel_beg();

            strsize i2 = m_pdata->get_sel_end();

            if (i1 != i2)
            {

               m_pdata->_001Delete(i1, i2);

               m_pdata->m_iSelBeg = m_pdata->m_iSelEnd = i1;

               //index i = find_span(m_pdata->m_spana, i1);

               on_after_change(::user::event_after_change_text);

               set_need_redraw();

            }
            else if (i1 >= 0 && i1 < m_pdata->_001GetLayoutTextLength())
            {

               string str;

               _001GetLayoutText(str);

               strsize iIncLen = ::str::utf8_inc_len(&str[i1]);

               m_pdata->_001Delete(i1, i1 + iIncLen);

               m_pdata->m_iSelBeg = m_pdata->m_iSelEnd = i1;

               //index i = find_span(m_pdata->m_spana, i1);

               on_after_change(::user::event_after_change_text);

               set_need_redraw();

            }

         }


      }


      void edit_impl::_001OnChar(::message::message * pmessage)
      {

            SCAST_PTR(::message::key, pkey, pmessage);

            string strChar;

            auto psession = Session;

            if (pkey->m_ekey == ::user::key_s)
            {

               if (psession->is_key_pressed(::user::key_control))
               {

                  return;

               }

            }
            else if (pkey->m_ekey == ::user::key_a)
            {

               if (psession->is_key_pressed(::user::key_control))
               {

                  _001SetSel(0, _001GetTextLength());

                  return;

               }

            }
            else if (pkey->m_ekey == ::user::key_z)
            {

               if (psession->is_key_pressed(::user::key_control))
               {

                  if (is_window_enabled())
                  {

                     //Undo();

                  }

                  return;

               }

            }
            else if (pkey->m_ekey == ::user::key_y)
            {

               if (psession->is_key_pressed(::user::key_control))
               {

                  if (is_window_enabled())
                  {

                     //Redo();

                  }

                  return;

               }

            }
            else if (psession->is_key_pressed(::user::key_control))
            {

               if (pkey->m_ekey == ::user::key_home)
               {

               }
               else if (pkey->m_ekey == ::user::key_end)
               {

               }
               else
               {

                  return;
               }

            }

            {

               sync_lock sl(mutex());

               bool bControl = psession->is_key_pressed(::user::key_control);

               bool bShift = psession->is_key_pressed(::user::key_shift);

               if (pkey->m_ekey == ::user::key_prior)
               {

                  //on_reset_focus_start_tick();

                  //i32 x;
                  //index iLine = SelToLineX(m_pdata->m_iSelEnd, x);

                  //::rect rectClient;

                  //GetFocusRect(rectClient);

                  //iLine -= rectClient.height() / m_iLineHeight;

                  //if (iLine < 0)
                  //{

                  //   iLine = 0;

                  //}

                  //m_pdata->m_iSelEnd = LineXToSel(iLine, m_iColumnX);

                  //if (!bShift)
                  //{

                  //   m_pdata->m_iSelBeg = m_pdata->m_iSelEnd;

                  //}

                  //_001EnsureVisibleLine(iLine);

               }
               else if (pkey->m_ekey == ::user::key_next)
               {

                  //on_reset_focus_start_tick();

                  //i32 x;

                  //index iLine = SelToLineX(m_pdata->m_iSelEnd, x);

                  //::rect rectClient;

                  //GetFocusRect(rectClient);

                  //iLine += rectClient.height() / m_iLineHeight;

                  //if (iLine >= m_iaLineBeg.get_size())
                  //{

                  //   iLine = m_iaLineBeg.get_upper_bound();

                  //}

                  //m_pdata->m_iSelEnd = LineXToSel(iLine, m_iColumnX);

                  //if (!bShift)
                  //{

                  //   m_pdata->m_iSelBeg = m_pdata->m_iSelEnd;

                  //}

                  //_001EnsureVisibleLine(iLine);

               }
               else if (pkey->m_ekey == ::user::key_back)
               {

                  if (is_window_enabled())
                  {

                     on_reset_focus_start_tick();

                     {
                        sync_lock sl(m_pdata->mutex());

                        strsize i1 = m_pdata->get_sel_beg();

                        strsize i2 = m_pdata->get_sel_end();

                        if (i1 > 0)
                        {

                           if (i1 != i2)
                           {

                              m_pdata->_001Delete(i1, i2);

                              m_pdata->m_iSelBeg = m_pdata->m_iSelEnd = i1;

                              on_after_change(::user::event_after_change_text);

                              set_need_redraw();

                           }
                           else
                           {

                              string str;

                              _001GetLayoutText(str);

                              strsize iDecLen = ::str::utf8_dec_len(str, &str[i1]);

                              m_pdata->_001Delete(i1, i1 - iDecLen);

                              m_pdata->m_iSelBeg = m_pdata->m_iSelEnd = i1 - iDecLen;

                              on_after_change(::user::event_after_change_text);

                              set_need_redraw();

                           }

                        }

                     }

                  }

               }
               else if (pkey->m_ekey == ::user::key_delete)
               {

                  if (is_window_enabled())
                  {

                     _001OnDeleteText();

                  }

                  return;

               }
               else if (pkey->m_ekey == ::user::key_up)
               {

                  on_reset_focus_start_tick();

                  sync_lock sl(m_pdata->mutex());

                  double x;

                  auto plinea = m_pdata->m_plinea;

                  index iLine = line_caret_x(*plinea, m_pdata->m_iSelEnd, x);

                  iLine--;

                  if (iLine >= 0)
                  {

                     m_pdata->m_iSelEnd = m_pdata->hit_test_line_x(iLine, x);

                     if (!bShift)
                     {

                        m_pdata->m_iSelBeg = m_pdata->m_iSelEnd;

                     }

                     //_001EnsureVisibleLine(iLine);

                     m_pdata->internal_update_sel_char();

                  }

               }
               else if (pkey->m_ekey == ::user::key_down)
               {

                  on_reset_focus_start_tick();

                  sync_lock sl(m_pdata->mutex());

                  double x;

                  auto plinea = m_pdata->m_plinea;

                  index iLine = line_caret_x(*plinea, m_pdata->m_iSelEnd, x);

                  iLine++;

                  if (iLine < plinea->get_count())
                  {

                     m_pdata->m_iSelEnd = m_pdata->hit_test_line_x(iLine, x);

                     if (!bShift)
                     {

                        m_pdata->m_iSelBeg = m_pdata->m_iSelEnd;

                     }


                     //_001EnsureVisibleLine(iLine);

                     m_pdata->internal_update_sel_char();

                  }

               }
               else if (pkey->m_ekey == ::user::key_right)
               {

                  on_reset_focus_start_tick();

                  if (!bShift && m_pdata->m_iSelBeg > m_pdata->m_iSelEnd)
                  {

                     sync_lock sl(m_pdata->mutex());

                     m_pdata->m_iSelEnd = m_pdata->m_iSelBeg;

                     m_pdata->internal_update_sel_char();

                  }
                  else if (!bShift && m_pdata->m_iSelEnd > m_pdata->m_iSelBeg)
                  {

                     sync_lock sl(m_pdata->mutex());

                     m_pdata->m_iSelBeg = m_pdata->m_iSelEnd;

                     m_pdata->internal_update_sel_char();

                  }
                  else
                  {

                     sync_lock sl(m_pdata->mutex());

                     if (m_pdata->m_iSelEnd < m_pdata->_001GetLayoutTextLength())
                     {

                        string strText;

                        _001GetLayoutText(strText);

                        const char * psz = strText;

                        const char * end = &psz[m_pdata->m_iSelEnd];

                        const char * inc = ::str::utf8_inc(end);

                        m_pdata->m_iSelEnd += inc - end;

                        if (!bShift)
                        {

                           m_pdata->m_iSelBeg = m_pdata->m_iSelEnd;

                        }

                        m_pdata->internal_update_sel_char();

                     }

                  }

               }
               else if (pkey->m_ekey == ::user::key_left)
               {

                  on_reset_focus_start_tick();

                  if (!bShift && m_pdata->m_iSelBeg < m_pdata->m_iSelEnd)
                  {

                     sync_lock sl(m_pdata->mutex());

                     m_pdata->m_iSelEnd = m_pdata->m_iSelBeg;

                     m_pdata->internal_update_sel_char();

                  }
                  else if (!bShift && m_pdata->m_iSelEnd < m_pdata->m_iSelBeg)
                  {

                     sync_lock sl(m_pdata->mutex());

                     m_pdata->m_iSelBeg = m_pdata->m_iSelEnd;

                     m_pdata->internal_update_sel_char();

                  }
                  else if (m_pdata->m_iSelEnd > 0)
                  {

                     sync_lock sl(m_pdata->mutex());

                     string strText;

                     _001GetLayoutText(strText);

                     const char * psz = strText;

                     const char * end = &psz[m_pdata->m_iSelEnd];

                     const char * dec = ::str::uni_dec(psz, end);

                     m_pdata->m_iSelEnd -= end - dec;

                     if (!bShift)
                     {

                        m_pdata->m_iSelBeg = m_pdata->m_iSelEnd;

                     }

                     m_pdata->internal_update_sel_char();

                  }

               }
               else if (pkey->m_ekey == ::user::key_home)
               {

                  on_reset_focus_start_tick();

                  sync_lock sl(m_pdata->mutex());

                  if (bControl)
                  {

                     m_pdata->m_iSelEnd = 0;

                     //   _001EnsureVisibleLine(0);

                  }
                  else
                  {

                     index iLine = m_pdata->SelToLine(m_pdata->m_iSelEnd);

                     m_pdata->m_iSelEnd = m_pdata->LineColumnToSel(iLine, 0);

                  }

                  if (!bShift)
                  {

                     m_pdata->m_iSelBeg = m_pdata->m_iSelEnd;

                  }

                  m_pdata->internal_update_sel_char();

               }
               else if (pkey->m_ekey == ::user::key_end)
               {

                  on_reset_focus_start_tick();

                  sync_lock sl(m_pdata->mutex());

                  if (bControl)
                  {

                     m_pdata->m_iSelEnd = _001GetTextLength();

                     //   _001EnsureVisibleLine(iLine);

                  }
                  else
                  {

                     index iLine = m_pdata->SelToLine(m_pdata->m_iSelEnd);

                     m_pdata->m_iSelEnd = m_pdata->LineColumnToSel(iLine, -1);

                  }

                  if (!bShift)
                  {

                     m_pdata->m_iSelBeg = m_pdata->m_iSelEnd;

                  }

                  m_pdata->internal_update_sel_char();

               }
               else if (pkey->m_ekey == ::user::key_escape)
               {

               }
               else if (pkey->m_ekey == ::user::key_return)
               {

//                if(m_bMultiLine)
                  {

                     insert_text("\n", true);

                  }

               }
               else if (is_window_enabled())
               {

#if defined(WINDOWS_DESKTOP) || defined(LINUX) || defined(MACOS)

                  return;

#else

                  on_reset_focus_start_tick();

                  string str;

                  char ch = 0;

                  if (pkey->m_ekey == ::user::key_tab)
                  {

                     str = "   ";

                  }
                  else if (pkey->m_ekey == ::user::key_refer_to_text_member)
                  {

                     str = pkey->m_strText;

                  }
                  else
                  {

                     ch = (char)pkey->m_nChar;

                     if (ch == '\r')
                     {

                        ch = '\n';

                     }

                     i32 iChar = (i32)pkey->m_nChar;

                     if (iChar == '\r')
                     {

                        iChar = '\n';

                     }

                     if (bShift)
                     {

                        iChar |= 0x80000000;

                     }

                     i32 iCode = pkey->m_nFlags & 0xff;

                     if (bShift)
                     {

                        iCode |= 0x80000000;

                     }

                     //str = psession->keyboard().process_key(pkey);
                                          //str = psession->keyboard().process_key(pkey);
                     __throw(todo("keyboard"));


                  }



                  m_pdata->_001InsertText(str);

                  #endif

               }


            }


      }


      void edit_impl::on_after_change(::user::enum_event eevent)
      {

         m_pdata->optimize_data();

         ::user::control_event ev;

         ev.m_eevent = eevent;

         ev.m_id = m_id;

         ev.m_puie = this;

         on_control_event(&ev);

         set_need_layout();

         set_need_redraw();

         post_redraw();

      }


      strsize edit_impl::_001GetTextLength() const
      {

         return m_pdata->_001GetTextLength();

      }


      void edit_impl::_001GetSel(strsize & iBeg, strsize & iEnd) const
      {

         iBeg = m_pdata->m_iSelBeg;

         iEnd = m_pdata->m_iSelEnd;


      }


      void edit_impl::_001GetSelLineText(string & strText) const
      {

//         double x;

         index iLine = m_pdata->SelToLine(m_pdata->m_iSelBeg);

         index iLineEnd = m_pdata->SelToLine(m_pdata->m_iSelBeg);

         if (iLine != iLineEnd)
         {

            return;

         }

         index iBeg = m_pdata->LineColumnToSel(iLine, 0);

         index iEnd = m_pdata->LineColumnToSel(iLine, -1);

         _001GetText(strText, iBeg, iEnd);

      }


      void edit_impl::update_placement()
      {

         if (m_ppictureimpl == nullptr)
         {

            return;

         }

         place(m_ppictureimpl->m_rect);

      }


      stream & edit_impl::write(::stream & stream) const
      {

         ::user::picture::write(stream);

         m_pdata->write(stream);

         ::rect rectWindow;

         ((edit_impl *)this)->get_window_rect(rectWindow);

         if (GetParent() != nullptr)
         {

            GetParent()->_001ScreenToClient(rectWindow);

         }

         stream << rectWindow;

         return stream;

      }


      stream & edit_impl::read(::stream & stream)
      {

         ::user::picture::read(stream);

         m_pdata->read(stream);

         ::rect rectWindow;

         stream >> rectWindow;

         place(rectWindow);

         display(e_display_normal);

         set_need_layout();

         return stream;

      }


      void edit_impl::get_text_composition_area(::rect & r)
      {

      }


      void edit_impl::on_text_composition(string str)
      {

         if (!m_bComposing)
         {

            m_bComposing = true;

         }
         else
         {

            edit_undo();

         }

         m_pdata->_001InsertText(str);

      }


      void edit_impl::on_text_composition_done()
      {

      }


      bool edit_impl::edit_undo()
      {

         return false;


      }


      ::user::rich_text::data * edit_impl::get_rich_text_data()
      {

         return m_pdata;

      }



   } // namespace rich_text


} // namespace user


