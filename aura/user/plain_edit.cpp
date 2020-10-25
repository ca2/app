#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "aura/user/_user.h"
#endif
#include "_data.h"
#include "aura/update.h"
#include "aura/message.h"
#include "aura/user/interaction_thread.h"
#ifdef WINDOWS_DESKTOP
#ifdef ENABLE_TEXT_SERVICES_FRAMEWORK
#include "aura/user/windows_tsf/edit_window.h"
#endif
#endif
#include "acme/const/timer.h"
//#include "_tree.h"

//extern CLASS_DECL_AURA thread_int_ptr < DWORD_PTR > t_time1;




void _001AddPacks(string_to_string & base64map, string & str)
{


   auto iPack = base64map.get_count();

   strsize iData = -1;

   while (true)
   {

      iData = str.find("data:", iData + 1);

      if (iData < 0 || !(iData == 0 || !ansi_char_is_alphanumeric(str[iData - 1])))
      {

         break;

      }

      strsize iMime = str.find(';', iData + 1);

      if (iMime <= iData)
      {

         continue;

      }

      strsize iEncoding1 = str.find(',', iMime + 1);

      strsize iEncoding2 = str.find(';', iMime + 1);

      strsize iEncoding = min_non_neg(iEncoding1, iEncoding2);

      if (iEncoding <= iMime)
      {

         continue;

      }

      string strEncoding = str.Mid(iMime + 1, iEncoding - iMime - 1);

      if (strEncoding.compare_ci("base64") == 0)
      {

         ::str::base64 & b64 = System.base64();

         index iBase64 = iEncoding + 1;

         for (; iBase64 < str.get_length(); iBase64++)
         {

            if (!b64.is(str[iBase64]))
            {

               break;

            }

         }

         string strBase64 = str.Mid(iEncoding + 1, iBase64 - iEncoding - 1);

         string strPack = "%pack" + __str(iPack + 1) + "%";

         str = str.Left(iEncoding + 1) + strPack + str.Mid(iBase64);

         base64map[strPack] = strBase64;

         iPack++;

      }


   }

}


namespace user
{

   class plain_edit_internal
   {
   public:

      ::draw2d::pen_pointer              m_penCaret;
      ::draw2d::brush_pointer            m_brushText;
      ::draw2d::brush_pointer            m_brushTextCr;
      ::draw2d::brush_pointer            m_brushTextSel;
      ::draw2d::brush_pointer            m_brushTextEmpty;

      plain_edit_internal();
      ~plain_edit_internal();

      void update(::draw2d::graphics_pointer& pgraphics, plain_edit * pedit);

   };



   plain_edit::plain_edit()
   {

      plain_edit_common_construct();

   }


   //plain_edit::plain_edit(::layered * pobjectContext) :
   //   ::object(pobject),
   //   ::user::interaction(pobject),
   //   m_pmemorygraphics(e_create)
   //{

   //   plain_edit_common_construct();

   //}


   plain_edit::~plain_edit()
   {

      ::acme::del(m_pinternal);

   }


   void plain_edit::set_format(const string& strFormat)
   {

   }


   void plain_edit::set_callback(callback* pcallback)
   {


   }



   void plain_edit::plain_edit_common_construct()
   {

      m_bCaretVisible = false;

      //is_text_composition_active() = false;

      //m_bImeCancelling = false;

      m_bEnterKeyOnPaste = false;

      m_pinternal = new plain_edit_internal();

      m_psetsel = nullptr;

      m_pinsert = nullptr;

      m_bColorerTake5 = false;

      m_straLines.set_size(10, 100);

      m_daExtent.set_size(10, 100);

      m_iTabWidth = 3;

      m_bTabInsertSpaces = false;

      m_iLineHeight = 0;

      m_bPassword = false;

      m_bOwnData = false;

      m_bMultiLine = false;

      m_bReadOnly = false;

      m_bSendEnterKey = false;

      //m_bActionHover = false;

      m_bCalcLayoutHintNoTextChange = false;

      m_scrolldataHorz.m_bScrollEnable = false;

      m_scrolldataVert.m_bScrollEnable = false;

      m_y = -1;
      m_iViewOffset = 0;
      m_iViewSize = 0;
      m_bLMouseDown = false;
      m_bRMouseDown = false;
      m_tickCaretPeriod = 1000;

      set_cursor(cursor_text_select);


   }


   void plain_edit::install_message_routing(::channel * pchannel)
   {

      interaction::install_message_routing(pchannel);

#ifdef ENABLE_TEXT_SERVICES_FRAMEWORK
#ifdef WINDOWS
      ::tsf::edit_window::install_message_routing(pchannel);
#else
      //::user::edit_window
#endif
#else
#ifdef WINDOWS_DESKTOP
      //, virtual public imm_client
#endif
#endif
      MESSAGE_LINK(e_message_create, pchannel, this, &plain_edit::_001OnCreate);
      MESSAGE_LINK(WM_LBUTTONDOWN, pchannel, this, &plain_edit::_001OnLButtonDown);
      MESSAGE_LINK(WM_LBUTTONUP, pchannel, this, &plain_edit::_001OnLButtonUp);
      MESSAGE_LINK(WM_RBUTTONDOWN, pchannel, this, &plain_edit::_001OnRButtonDown);
      MESSAGE_LINK(WM_RBUTTONUP, pchannel, this, &plain_edit::_001OnRButtonUp);
      MESSAGE_LINK(e_message_mouse_move, pchannel, this, &plain_edit::_001OnMouseMove);
      MESSAGE_LINK(WM_MOUSELEAVE, pchannel, this, &plain_edit::_001OnMouseLeave);
      MESSAGE_LINK(WM_KEYDOWN, pchannel, this, &plain_edit::_001OnKeyDown);
      MESSAGE_LINK(WM_KEYUP, pchannel, this, &plain_edit::_001OnKeyUp);
      MESSAGE_LINK(WM_UNICHAR, pchannel, this, &plain_edit::_001OnUniChar);

      MESSAGE_LINK(e_message_size, pchannel, this, &::user::plain_edit::_001OnSize);

      MESSAGE_LINK(e_message_set_focus, pchannel, this, &::user::plain_edit::_001OnSetFocus);
      MESSAGE_LINK(e_message_kill_focus, pchannel, this, &::user::plain_edit::_001OnKillFocus);


      MESSAGE_LINK(WM_VSCROLL, pchannel, this, &::user::plain_edit::_001OnVScroll);
      MESSAGE_LINK(WM_HSCROLL, pchannel, this, &::user::plain_edit::_001OnHScroll);



      connect_command_probe("edit_cut", &plain_edit::_001OnUpdateEditCut);
      connect_command("edit_cut", &plain_edit::_001OnEditCut);
      connect_command_probe("edit_copy", &plain_edit::_001OnUpdateEditCopy);
      connect_command("edit_copy", &plain_edit::_001OnEditCopy);
      connect_command_probe("edit_paste", &plain_edit::_001OnUpdateEditPaste);
      connect_command("edit_paste", &plain_edit::_001OnEditPaste);
      connect_command_probe("edit_delete", &plain_edit::_001OnUpdateEditDelete);
      connect_command("edit_delete", &plain_edit::_001OnEditDelete);


#ifdef ENABLE_TEXT_SERVICES_FRAMEWORK

      install_edit_window_message_routing(pchannel);

#elif defined(WINDOWS_DESKTOP)

      imm_client::install_message_routing(pchannel);

#endif

   }


   void plain_edit::OnDraw(::image * pimage)
   {

      UNREFERENCED_PARAMETER(pimage);

   }


   void plain_edit::on_apply(::action * paction)
   {

      if(paction->id() == id_current_text_changed)
      {

         ::draw2d::graphics_pointer pgraphics = ::draw2d::create_memory_graphics();

         plain_edit_on_update(pgraphics, ::source_sync);

         m_bCalcLayoutHintNoTextChange = false;

         plain_edit_on_calc_layout(pgraphics);

      }
      else
      {

         ::user::interaction::on_apply(paction);

      }

   }


   void plain_edit::_001OnDestroy(::message::message * pmessage)
   {


   }


   void plain_edit::VirtualOnSize(::draw2d::graphics_pointer& pgraphics)
   {

      plain_edit_on_update(pgraphics, ::source_system);

      m_bCalcLayoutHintNoTextChange = true;

      plain_edit_on_calc_layout(pgraphics);

   }


   void plain_edit::_001OnPaint(::message::message * pmessage)
   {

   }


   void plain_edit::on_viewport_offset(::draw2d::graphics_pointer & pgraphics)
   {

      ::user::interaction::on_viewport_offset(pgraphics);

   }


   void plain_edit::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      m_tickLastDraw = ::get_tick();

      tick t1 = tick::now();

      auto pstyle = get_style(pgraphics);

      pgraphics->set_text_rendering_hint(::draw2d::text_rendering_hint_anti_alias);

      COLORREF crBk;
      COLORREF crBkSel;
      COLORREF crSel;
      COLORREF cr;

      auto rectClient = get_client_rect();

      COLORREF crEditBackground = get_color(pstyle, element_background);

      pgraphics->fill_rect(rectClient, crEditBackground);

      cr = get_color(pstyle, element_text);
      crBk = get_color(pstyle, element_background);
      crSel = get_color(pstyle, element_text, e_state_selected);
      crBkSel = get_color(pstyle, element_background, e_state_selected);

      m_pinternal->update(pgraphics, this);

      //::change * pchange = pgraphics->m_ptask;

      //::user::print_task * pprinttask = nullptr;

      //if (ptask != nullptr)
      //   pprinttask = dynamic_cast <::user::print_task *> (ptask);
      //else
      //   pprinttask = nullptr;

      ////::rect rectClient;

      ////GetFocusRect(rectClient);

      //if (pprinttask != nullptr)
      //{

      //   TRACE("Print Job Is Printing page %d", pprinttask->m_iPrintingPage);

      //}

      bool bCaretOn = is_caret_on();

      bool bFocus = has_focus();

      if (m_ptree == nullptr)
         return;

      ::draw2d::region_pointer rgn(e_create);

      rectClient.deflate(0, 0, 0, 0);

      rgn->create_rect(rectClient);

      double left = rectClient.left;

      //if(keyboard_focus_is_focusable() && has_focus())
      //{

      //   m_bFocus = true;

      //}
      //else
      //{

      //   m_bFocus = false;

      //}


      strsize iSelBeg;
      strsize iSelEnd;
      strsize iSelBegOriginal;
      strsize iSelEndOriginal;
      strsize lim = 0;

      ::draw2d::pen_pointer & penCaret = m_pinternal->m_penCaret;

      ::draw2d::brush_pointer & brushText = m_pinternal->m_brushText;

      ::draw2d::brush_pointer & brushTextCr = m_pinternal->m_brushTextCr;

      ::draw2d::brush_pointer & brushTextSel = m_pinternal->m_brushTextSel;

      auto pointOffset = get_viewport_offset();

      if (m_iLineHeight > 0)
      {

         int iVerticalOffsetModule = pointOffset.y % m_iLineHeight;

         if (iVerticalOffsetModule > 0)
         {

            pgraphics->OffsetViewportOrg(0, -iVerticalOffsetModule);

         }

      }

      pgraphics->OffsetViewportOrg(-pointOffset.x, 0);

      double y = rectClient.top;

      _001GetViewSel(iSelBegOriginal, iSelEndOriginal);

      iSelBeg = iSelBegOriginal;

      iSelEnd = iSelEndOriginal;

      strsize iCursor = iSelEndOriginal;

      __sort(iSelBeg, iSelEnd);

      pgraphics->set_font(this);

      pgraphics->set_text_rendering_hint(::draw2d::text_rendering_hint_anti_alias);
      //size size3;
      //size3 = pgraphics->GetTextExtent(unitext("gGYIﾍ"));
      i32 iLineHeight = m_iLineHeight;
//      string_array & straLines = m_plines->lines;
      string_array & straLines = m_straLines;
      string str1;
      string str2;
      string str3;
      string strExtent1;
      string strExtent2;
      string strExtent3;
      //index iLineStart = should_load_full_file() ? m_iLineStart : 0;
      //index iLineEnd = should_load_full_file() ?  iLineStart + m_iLineCount - 1 : straLines.get_size();
      //iLineEnd = min(iLineEnd,straLines.get_upper_bound());
      //index iLine = m_iLineStart;
      index i = 0;
      pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

      pgraphics->set_text_rendering_hint(::draw2d::text_rendering_hint_anti_alias);

      string strLineGraphics;

      if (_001GetTextLength() == 0)
      {

         if (m_strEmtpyText.has_char())
         {

            pgraphics->set(m_pinternal->m_brushTextEmpty);

            pgraphics->text_out(left, y, m_strEmtpyText);

         }

      }

      //::colorertake5::base_editor * pcolorer = colorertake5();

      for (index iLine = m_iLineStart; iLine < m_iLineEnd; i++, iLine++)
      {

         string strLine = straLines[i];

#if defined(LOG_ENABLE_PLAIN_EDIT_LINE)

         if(strLine.has_char())
         {

            auto psz = strLine.c_str();

            TRACE("Line %s", psz);

         }

#endif

         strLineGraphics = strLine;

         //colorertake5::LineRegion * pregion = nullptr;

         //if (m_bColorerTake5)
         //{

         //   pregion = pcolorer->getLineRegions(i);

         //}

         //if (pregion != nullptr)
         //{

         //   for (; pregion != nullptr; pregion = pregion->next)
         //   {
         //      if (pregion->special || pregion->rdef == nullptr)
         //         continue;
         //      index end = pregion->end;
         //      if (end == -1)
         //         end = strLine.get_length();
         //      strsize x = pregion->start;
         //      strsize len = end - pregion->start;
         //      if (x < 0)
         //      {
         //         len += x;
         //         x = 0;
         //      }
         //      if (len < 0)
         //         continue;
         //      string strExtent1;
         //      strExtent1 = strLine.Left(x);
         //      string strExtent2;
         //      strExtent2 = strLine.Mid(x, len);
         //      int x1;
         //      x1 = (int)(get_line_extent(iLine, x));
         //      if (pregion->styled()->bback)
         //      {
         //         pgraphics->fill_rect((i32)(left + x1), (i32)y, x1, m_iLineHeight, pregion->styled()->back);
         //      }
         //      ::draw2d::brush_pointer brushText(e_create);
         //      if (pregion->styled()->bfore)
         //      {
         //         brushText->create_solid(pregion->styled()->fore);
         //         pgraphics->set(brushText);
         //      }
         //      else
         //      {
         //         pgraphics->set(brushTextCr);
         //      }
         //      pgraphics->text_out(left + x1, y, strExtent2);

         //   }
         //}
         //else
         {

            COLORREF crOverride = ARGB(255, 0, 0, 0);

            bool bOverride = false;

            if (!m_bPassword)
            {

               bOverride = get_line_color(crOverride, strLine);

            }

            strsize iErrorBeg = -1;

            strsize iErrorEnd = -1;

            strsize iErrorA = 0;

            if (m_errora.get_size() > 0)
            {

               tick tickTimeout = 1000;

               tick tickPeriod = 100;

               if (m_errora[0].m_tick.elapsed() > tickTimeout)
               {

                  if (m_errora[0].m_tick.elapsed() < (tickTimeout + tickPeriod))
                  {

                     iErrorA = (strsize) ((m_errora[0].m_tick.elapsed() - tickTimeout) * 255 / tickPeriod);

                  }
                  else
                  {

                     iErrorA = 255;

                  }

                  iErrorBeg = m_errora[0].m_iStart;
                  iErrorEnd = m_errora[0].m_iEnd;
                  iErrorBeg -= lim;
                  iErrorEnd -= lim;
                  iErrorBeg = max(0, iErrorBeg);
                  iErrorEnd = min(iErrorEnd, strLine.get_length());

               }

            }

            string_array stra;

            strsize iCurLineSelBeg = iSelBeg - lim;

            strsize iCurLineSelEnd = iSelEnd - lim;

            strsize iCurLineSelCur = iCursor - lim;

            if (iCurLineSelBeg < 0)
            {

               iCurLineSelBeg = 0;

            }
            else if (iCurLineSelBeg >= strLineGraphics.length())
            {

               iCurLineSelBeg = strLineGraphics.length();

            }

            if (iCurLineSelEnd < 0)
            {

               iCurLineSelEnd = 0;

            }
            else if (iCurLineSelEnd >= strLineGraphics.length())
            {

               iCurLineSelEnd = strLineGraphics.length();

            }

            ::str::replace_tab(0, strLineGraphics, m_iTabWidth, { &iCurLineSelBeg, &iCurLineSelEnd, &iCurLineSelCur});

            if (m_bPassword)
            {

               strLine = ::str::block('*', i32 (strLine.get_length()));

            }

            double x1 = plain_edit_get_line_extent(pgraphics, iLine, iCurLineSelBeg);

            double x2 = plain_edit_get_line_extent(pgraphics, iLine, iCurLineSelEnd);

            if (m_bPassword)
            {

               strLineGraphics = ::str::block('*', i32 (strLineGraphics.get_length()));

            }

            if (iCurLineSelEnd > iCurLineSelBeg)
            {

               pgraphics->fill_solid_rect_dim(
               (double)((double)left + x1),
               (double)y,
               (double)min(x2-x1, (double)rectClient.right - ((double)left + x1)),
               (double)min((double)m_iLineHeight, (double)rectClient.bottom - y),
               crBkSel);

               pgraphics->set(brushTextSel);

            }

            if(bOverride)
            {

               brushText->create_solid(crOverride);

               pgraphics->set(brushText);

            }
            else
            {

               pgraphics->set(brushTextCr);

            }

            if(iCurLineSelBeg > 0)
            {

               // Draw Normal Text - not selected - before selection
               pgraphics->text_out(left, y, strLineGraphics.Left(iCurLineSelBeg));

            }

            if (iCurLineSelBeg < strLineGraphics.get_length())
            {

               // Draw Normal Text - not selected - after selection
               pgraphics->text_out(left + x2, y, strLineGraphics.Mid(iCurLineSelEnd));

            }

            if (bOverride)
            {

            }
            else
            {

               pgraphics->set(brushTextSel);

            }

            if (iCurLineSelBeg >= 0 && iCurLineSelEnd > iCurLineSelBeg)
            {

               // Draw Selected Text
               pgraphics->text_out(left + x1, y, strLineGraphics.Mid(iCurLineSelBeg, iCurLineSelEnd - iCurLineSelBeg));

            }

            if (0 <= iErrorBeg && iErrorBeg <= strExtent1.length())
            {

               double xA = plain_edit_get_line_extent(pgraphics, iLine, iErrorBeg);

               double xB = plain_edit_get_line_extent(pgraphics, iLine, min(iErrorEnd, strExtent1.length()));

               ::draw2d::pen_pointer point(e_create);

               point->create_solid(1.0, ARGB(iErrorA, 255, 0, 0));

               pgraphics->set(point);

               pgraphics->draw_error_line((int)xA, m_iLineHeight, (int)xB, 1);

            }

            if (iCurLineSelCur >= 0 && bFocus &&  bCaretOn && iCurLineSelCur == iCurLineSelBeg)
            {

#ifdef WINDOWS_DESKTOP

               ::point point((long)(left + x1), (long)y);

               _001ClientToScreen(point);

               get_wnd()->_001ScreenToClient(point);

               ::SetCaretPos(point.x, point.y);

#endif

               pgraphics->set(penCaret);

               pgraphics->move_to(left + x1, y);

               pgraphics->line_to(left + x1, y + iLineHeight);

            }
            else if (iCurLineSelCur >= 0 && bFocus && bCaretOn && iCurLineSelCur == iCurLineSelEnd)
            {

#ifdef WINDOWS_DESKTOP

               ::point point((long)(left + x1), (long) y);

               _001ClientToScreen(point);

               get_wnd()->_001ScreenToClient(point);

               ::SetCaretPos(point.x, point.y);

#endif

               pgraphics->set(penCaret);

               pgraphics->move_to(left + x2, y);

               pgraphics->line_to(left + x2, y + iLineHeight);

            }

         }

         y += m_iLineHeight;

         lim += m_iaLineLen[iLine];

      }


      tick d1 = t1.elapsed();

      if (d1 > 50)
      {

         CINFO(prodevian)("plain_edit took more than 50ms to draw " + __str(d1));

      }

   }


   void plain_edit::_001OnCreate(::message::message * pmessage)
   {

      SCAST_PTR(::message::create, pcreate, pmessage);

      pcreate->previous();

#if !defined(APPLE_IOS) && !defined(ANDROID)

      //Session.keyboard(); // trigger keyboard creationg
      Application.defer_create_keyboard();

#endif

      if (m_ptree == nullptr)
      {

         set_root(__new(::user::plain_text_tree), true);

         m_ptree->m_pfile = __new(::memory_file);

         m_ptree->m_peditfile->SetFile(m_ptree->m_pfile);

         m_ptree->m_iSelBeg = 0;

         m_ptree->m_iSelEnd = 0;

         m_bGetTextNeedUpdate = true;

         auto pgraphics = ::draw2d::create_memory_graphics();

         plain_edit_on_set_text(pgraphics, ::source_system);

         plain_edit_on_update(pgraphics, ::source_system);

      }

      m_ppropertyText = fetch_property(m_id, true);

      bind_update(m_ppropertyText);

      if(m_ppropertyText && !m_ppropertyText->is_empty())
      {

         _001SetText(m_ppropertyText->get_string(), ::source_initialize);

      }

   }


   void plain_edit::_001OnContextMenu(::message::message * pmessage)
   {

   }


   void plain_edit::_001OnRButtonDown(::message::message * pmessage)
   {

      SCAST_PTR(::message::mouse, pmouse, pmessage);

      ::point point = pmouse->m_point;

      _001ScreenToClient(point);

      m_bRMouseDown = true;

      {

         sync_lock sl(mutex());

         auto pgraphics = ::draw2d::create_memory_graphics();

         strsize iHit = plain_edit_char_hit_test(pgraphics, point.x, point.y);

         if (iHit <= m_ptree->m_iSelBeg || iHit >= m_ptree->m_iSelEnd)
         {

            m_ptree->m_iSelBeg = iHit;

            m_ptree->m_iSelEnd = iHit;

         }

      }

      set_need_redraw();

      Session.set_keyboard_focus(this);

      Session.user()->set_mouse_focus_RButtonDown(this);

      pmouse->m_bRet = true;

      pmouse->m_lresult = 1;

   }


   void plain_edit::_001OnRButtonUp(::message::message * pmessage)
   {

      SCAST_PTR(::message::mouse, pmouse, pmessage);

      ::point point = pmouse->m_point;

      _001ScreenToClient(point);

      //{

      //   sync_lock sl(mutex());

      //   strsize iSelStart = -1;

      //   strsize iSelEnd = -1;

      //   _001GetSel(iSelStart, iSelEnd);

      //   if (iSelStart == iSelEnd)
      //   {

      //      _001SetSel(0, _001GetTextLength());

      //   }

      //}

      set_need_redraw();

      m_bRMouseDown = false;

      //track_popup_xml_menu("matter://system/edit_focus_popup.xml", 0, pmouse->m_point);

      pmouse->m_lresult = 1;

      pmouse->m_bRet = true;


   }





   void plain_edit::_001OnSetCursor(::message::message * pmessage)
   {
      //pmouse->m_ecursor = cursor_arrow;

      pmessage->previous();
   }


   void plain_edit::_001OnTimer(::timer * ptimer)
   {

      interaction::_001OnTimer(ptimer);

      enum_timer etimer = (enum_timer) ptimer->m_uEvent;

      if (etimer == e_timer_overflow_scrolling)
      {

         if (m_bLMouseDown)
         {

            ::point pointCursor;

            Session.get_cursor_pos(&pointCursor);

            _001ScreenToClient(pointCursor);

            ::rect rectActiveClient;

            GetActiveClientRect(rectActiveClient);

            if (pointCursor.x < rectActiveClient.left)
            {

               scroll_left_line();

            }
            else if (pointCursor.x > rectActiveClient.right)
            {

               scroll_right_line();

            }

            if (pointCursor.y < rectActiveClient.top)
            {

               scroll_up_line();

            }
            else if (pointCursor.y > rectActiveClient.bottom)
            {

               scroll_down_line();

            }



         }


      }
      else if (ptimer->m_uEvent >= 100
               && ptimer->m_uEvent <= 200)
      {
         if (has_focus())
         {

            _001OnKeyboardFocusTimer(ptimer->m_uEvent - 100);

         }
      }
      else if (ptimer->m_uEvent == 500 || ptimer->m_uEvent == 501)
      {

         if (ptimer->m_uEvent == 500)
         {

            KillTimer(500);

            SetTimer(501, 300, nullptr);

         }

         key_to_char(m_pmessagekeyLast);

      }

   }


   void plain_edit::_001OnKeyDown(::message::message * pmessage)
   {

      INFO("_001OnKeyDown (1)");

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

      INFO("_001OnKeyDown (2)");

      SCAST_PTR(::message::key, pkey, pmessage);

      if (pkey->m_ekey == ::user::key_return)
      {

         if (Session.is_key_pressed(::user::key_control) && Session.is_key_pressed(::user::key_alt))
         {

            pkey->m_bRet = false;

            return;

         }

         if ((!m_bMultiLine || m_bSendEnterKey) && GetParent() != nullptr)
         {

            ::user::control_event ev;

            ev.m_puie = this;

            ev.m_eevent = ::user::event_enter_key;

            ev.m_actioncontext = ::source_user;

            on_control_event(&ev);

            if(!ev.m_bRet && ev.m_bOk)
            {

               on_action("submit");

            }

            pmessage->m_bRet = true;

            return;

         }

      }
      else if (pkey->m_ekey == ::user::key_tab)
      {

         if (Session.is_key_pressed(::user::key_control) && Session.is_key_pressed(::user::key_alt))
         {

            pkey->m_bRet = false;

            return;

         }

         if (!m_bMultiLine)
         {

            pkey->previous();

            ::user::control_event ev;

            ev.m_puie = this;

            ev.m_eevent = ::user::event_tab_key;

            ev.m_actioncontext = ::source_user;

            on_control_event(&ev);

            if(!ev.m_bRet && ev.m_bOk)
            {

               keyboard_set_focus_next();

            }

            pkey->m_bRet = true;

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

         if(!ev.m_bRet && ev.m_bOk)
         {

            on_action("escape");

         }

         pmessage->m_bRet = true;

         return;

      }
      else if (pkey->m_ekey == ::user::key_c)
      {

         if (Session.is_key_pressed(::user::key_control))
         {

            pkey->m_bRet = true;

            clipboard_copy();

            return;

         }

      }
      else if (pkey->m_ekey == ::user::key_v ||
      (pkey->m_ekey == ::user::key_refer_to_text_member
      && pkey->m_strText.compare_ci("v")==0))
      {

#ifdef MACOS
         if (Session.is_key_pressed(::user::key_command))
#else
         if (Session.is_key_pressed(::user::key_control))
#endif
         {

            pkey->m_bRet = true;

            if (is_window_enabled())
            {

               clipboard_paste();

            }

            return;

         }

      }
      else if (pkey->m_ekey == ::user::key_x)
      {

         if (Session.is_key_pressed(::user::key_control))
         {

            pkey->m_bRet = true;

            clipboard_copy();

            if (is_window_enabled())
            {

               auto pgraphics = ::draw2d::create_memory_graphics();

               plain_edit_on_delete(pgraphics);

            }

            return;

         }

      }

      INFO("_001OnKeyDown (3)");

      m_pmessagekeyLast = pkey;

      key_to_char(m_pmessagekeyLast);

      pkey->m_bRet = true;

   }


   void plain_edit::_001OnKeyUp(::message::message * pmessage)
   {

      SCAST_PTR(::message::key, pkey, pmessage);

      if (pkey->m_ekey == ::user::key_return)
      {

         if (Session.is_key_pressed(::user::key_control)
               && Session.is_key_pressed(::user::key_alt))
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

   }


   void plain_edit::pre_translate_message(::message::message * pmessage)
   {

      ::user::interaction::pre_translate_message(pmessage);

   }


   void plain_edit::key_to_char(::message::key * pkey)
   {

      ::message::key & key = *pkey;

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

      bool bShift = Session.is_key_pressed(::user::key_shift);

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

      INFO("key_to_char (1)");

      _001OnChar(&key);

   }


   strsize plain_edit::_001GetTextLength() const
   {

      sync_lock sl(mutex());

      return strsize (m_ptree->m_peditfile->get_length());

   }


   void plain_edit::_001GetText(string & str) const
   {

      plain_edit_get_text(str);

   }


   void plain_edit::plain_edit_get_text(string & str) const
   {

      if (m_ptree == nullptr)
      {

         return;

      }

      sync_lock sl(mutex());

      filesize iSize = m_ptree->m_peditfile->get_length();

      char * psz = str.get_string_buffer((strsize)(iSize + 1));

      m_ptree->m_peditfile->seek(0, ::file::seek_begin);

      m_ptree->m_peditfile->read(psz, (memsize)iSize);

      psz[(memsize)iSize] = '\0';

      str.release_string_buffer();

      for (auto & m : m_base64map)
      {

         string strPack = m.element1();

         str.replace(strPack, m.element2());

      }

   }


   void plain_edit::_001GetSelText(string & str) const
   {

      _001GetText(str, m_ptree->m_iSelBeg, m_ptree->m_iSelEnd);

   }


   void plain_edit::_001GetText(string & str, index iBegParam, index iEndParam) const
   {

      sync_lock sl(mutex());

      ::sort::sort_non_negative(iBegParam, iEndParam);

      filesize iEnd;

      filesize iBeg;

      if (iEndParam < 0)
      {

         if (iBegParam < 0)
         {

            iEnd = (filesize)m_ptree->m_peditfile->get_length();

            iBeg = 0;

         }
         else
         {

            iBeg = iBegParam;

            iEnd = (filesize)m_ptree->m_peditfile->get_length();

         }

      }
      else
      {

         if (iBegParam < 0)
         {

            iEnd = iEndParam;

            iBeg = 0;

         }
         else
         {

            iEnd = iEndParam;

            iBeg = iBegParam;

         }

      }

      if (iEnd < iBeg)
      {

         ::_std::__swap(iEnd, iBeg);

      }

      filesize iSize = iEnd - iBeg;

      char * psz = str.get_string_buffer((strsize)(iSize + 1));

      m_ptree->m_peditfile->seek((filesize)iBeg, ::file::seek_begin);

      m_ptree->m_peditfile->read(psz, (memsize)(iSize));

      psz[(memsize)iSize] = '\0';

      str.release_string_buffer();

   }


   void plain_edit::_001SetSelText(const char * psz, const ::action_context & context)
   {

      {

         sync_lock sl(mutex());

         m_ptree->m_peditfile->seek(m_ptree->m_iSelBeg, ::file::seek_begin);

         m_ptree->m_peditfile->Delete((memsize)(m_ptree->m_iSelEnd - m_ptree->m_iSelBeg));

         m_ptree->m_peditfile->seek(m_ptree->m_iSelBeg, ::file::seek_begin);

         m_ptree->m_peditfile->Insert(psz, strlen(psz));

      }

      auto pgraphics = ::draw2d::create_memory_graphics();

      plain_edit_on_update(pgraphics, context);

      set_need_redraw();

   }


   void plain_edit::_001SetSelEnd(strsize iSelEnd)
   {

      auto pgraphics = ::draw2d::create_memory_graphics();

      return _set_sel_end(pgraphics, iSelEnd);

   }


   void plain_edit::_set_sel_end(::draw2d::graphics_pointer& pgraphics, strsize iSelEnd)
   {

      sync_lock sl(mutex());

      index iColumn = plain_edit_sel_to_column_x(pgraphics, iSelEnd, m_iColumnX);

      int x = 0;

      index iLine = plain_edit_sel_to_line_x(pgraphics, iSelEnd, x);

      index xEnd = 0;

      xEnd = index (plain_edit_get_line_extent(pgraphics, iLine, m_iaLineLen[iLine]));

      ::rect rectClient;

      get_client_rect(rectClient);

      auto xViewport = get_viewport_offset().x;

      if (x > 0 && x < get_viewport_offset().x)
      {

         xViewport = max(0, x - rectClient.width() / 2);

      }
      else if (x > rectClient.width())
      {

         xViewport = max(0, x - rectClient.width() / 2);

      }

      if (iSelEnd == m_ptree->m_iSelEnd && iColumn == m_iColumn && xViewport == get_viewport_offset().x)
      {

         return;

      }

      m_ptree->m_iSelEnd = iSelEnd;

      m_iColumn = iColumn;

      if (xViewport != get_viewport_offset().x)
      {

         set_viewport_offset_x((int) xViewport);

      }

      _001EnsureVisibleChar(iSelEnd);

#ifndef      SEARCH_SCROLLING_PROFILING

      set_need_redraw();

#endif

   }


   void plain_edit::plain_edit_on_end_update()
   {

      if (m_bNewSel)
      {

         _001EnsureVisibleChar(m_ptree->m_iSelEnd);

#ifndef      SEARCH_SCROLLING_PROFILING

         set_need_redraw();

#endif

      }

   }


   void plain_edit::_001SetSel(strsize iBeg, strsize iEnd)
   {

      sync_lock sl(mutex());

      m_ptree->m_iSelBeg = iBeg;

      m_ptree->m_iSelEnd = iEnd;

      m_bNewSel = true;

   }


   void plain_edit::_001EnsureVisibleChar(strsize iChar)
   {

      auto pgraphics = ::draw2d::create_memory_graphics();

      plain_edit_ensure_visible_char(pgraphics, iChar);

   }


   void plain_edit::plain_edit_ensure_visible_char(::draw2d::graphics_pointer & pgraphics, strsize iChar)
   {

      plain_edit_ensure_visible_line(pgraphics, plain_edit_char_to_line(pgraphics, iChar));

   }


   void plain_edit::_001EnsureVisibleLine(index iLine)
   {

      auto pgraphics = ::draw2d::create_memory_graphics();

      plain_edit_ensure_visible_line(pgraphics, iLine);

   }


   void plain_edit::plain_edit_ensure_visible_line(::draw2d::graphics_pointer& pgraphics, ::index iLine)
   {

      if (!m_bMultiLine)
      {

         set_viewport_offset_y(0);

      }
      else
      {

         ::rect rectClient;

         GetFocusRect(rectClient);

         int iCurrentPageOffsetStart = (int) get_viewport_offset().y;

         int iCurrentPageOffsetEnd = (int) (get_viewport_offset().y + rectClient.height());

         index iCandidateCursorOffset = (::index) (min((double) max(0, iLine)* m_iLineHeight, m_sizeTotal.cy));

         if (iCandidateCursorOffset < iCurrentPageOffsetStart)
         {

            set_viewport_offset_y((int)iCandidateCursorOffset);

         }
         else if (iCandidateCursorOffset > iCurrentPageOffsetEnd)
         {

            set_viewport_offset_y((int)(iCandidateCursorOffset - iCurrentPageOffsetEnd + iCurrentPageOffsetStart));

         }

         m_bCalcLayoutHintNoTextChange = true;

      }

      plain_edit_on_calc_offset(pgraphics);

#ifndef SEARCH_SCROLLING_PROFILING

      set_need_redraw();

#endif

   }


   void plain_edit::on_change_viewport_offset()
   {

      ::user::interaction::on_change_viewport_offset();

      auto pgraphics = ::draw2d::create_memory_graphics();

      plain_edit_on_calc_offset(pgraphics);

      set_need_redraw();

   }


   bool plain_edit::plain_edit_is_enabled()
   {

      return true;

   }

   void plain_edit::_001OnMouseMove(::message::message * pmessage)
   {

      pmessage->previous();

      if (plain_edit_is_enabled())
      {

         SCAST_PTR(::message::mouse, pmouse, pmessage);

         pmouse->m_ecursor = cursor_text_select;

         if (m_bLMouseDown)
         {

            ::point point = pmouse->m_point;

            _001ScreenToClient(point);

            if (m_pointLastCursor != point)
            {

               m_pointLastCursor = point;


               sync_lock sl(mutex());

               ::rect rectWindow;

               get_window_rect(rectWindow);

               if (pmouse->m_point.x < rectWindow.left - 30)
               {

                  output_debug_string("test06");

               }

               auto pgraphics = ::draw2d::create_memory_graphics();

               _set_sel_end(pgraphics, plain_edit_char_hit_test(pgraphics,point.x, point.y));

            }

            m_itemHover = element_client;

         }

      }

   }


   void plain_edit::_001OnMouseLeave(::message::message * pmessage)
   {

      m_itemHover = element_none;

      set_need_redraw();

   }


   void plain_edit::_001OnLButtonDown(::message::message * pmessage)
   {

      SCAST_PTR(::message::mouse, pmouse, pmessage);

      if (plain_edit_is_enabled())
      {

         ::point point = pmouse->m_point;

         _001ScreenToClient(point);

         {

            sync_lock sl(mutex());

            m_bLMouseDown = true;

            SetTimer(e_timer_overflow_scrolling, 50, nullptr);

            SetCapture();

            auto pgraphics = ::draw2d::create_memory_graphics();

            auto iSelBeg = plain_edit_char_hit_test(pgraphics, point.x, point.y);

            auto iSelEnd = m_ptree->m_iSelBeg;

            _001SetSel(iSelBeg, iSelEnd);

            m_iColumn = plain_edit_sel_to_column_x(pgraphics, m_ptree->m_iSelEnd, m_iColumnX);

#if defined(WINDOWS_DESKTOP)

            on_text_composition_message(TEXT_COMPOSITION_MESSAGE_UPDATE_CANDIDATE_WINDOW_POSITION);

#endif

         }

         pmouse->previous();

         set_need_redraw();

         Session.set_keyboard_focus(this);

         Session.user()->set_mouse_focus_LButtonDown(this);

         pmouse->m_bRet = true;

         pmouse->m_lresult = 1;

         on_reset_focus_start_tick();

      }
      else
      {

         pmouse->previous();

      }

   }


   void plain_edit::_001OnLButtonUp(::message::message * pmessage)
   {

      SCAST_PTR(::message::mouse, pmouse, pmessage);

      ReleaseCapture();

      if (m_bLMouseDown)
      {

         ::point point = pmouse->m_point;

         _001ScreenToClient(point);

         auto pgraphics = ::draw2d::create_memory_graphics();

         _set_sel_end(pgraphics, plain_edit_char_hit_test(pgraphics, point.x, point.y));

      }

      set_need_redraw();

      m_bLMouseDown = false;

      pmouse->m_bRet = true;

      pmouse->m_lresult = 1;

      on_reset_focus_start_tick();

   }




   void debug_func(const string & str)
   {


   }


   void plain_edit::plain_edit_on_calc_offset(::draw2d::graphics_pointer& pgraphics, index iLineUpdate)
   {

      sync_lock sl(mutex());

      ::rect rectClient;

      GetFocusRect(rectClient);

      if (m_ptree == nullptr)
      {

         m_iLineCount = 0;

         m_iLineOffset = 0;

         m_iLineStart = 0;

         m_iLineEnd = 0;

         m_iViewOffset = 0;

         m_iViewSize = 0;

         return;

      }

      ::index i;

      ::index iLine;

      if (pgraphics.is_null())
      {

         return;

      }

      pgraphics->set_font(this);

      sized sizeUniText;

      pgraphics->set_text_rendering_hint(::draw2d::text_rendering_hint_anti_alias);

      ::draw2d::text_metric metric;

      pgraphics->get_text_metrics(&metric);

      m_iLineHeight = (int)metric.tmHeight;

      if (m_iLineHeight <= 0)
      {

         m_iLineHeight = 18;

      }

      auto pointOffset = get_viewport_offset();

      m_iLineCount = ((rectClient.height() + m_iLineHeight - 1) / m_iLineHeight) + 2;

      m_iLineOffset = min(max(0, pointOffset.y / m_iLineHeight), m_iaLineBeg.get_upper_bound());

      bool bLoadFullFile = should_load_full_file();

      m_iLineStart = bLoadFullFile ? 0 : max(0, m_iLineOffset);

      m_iLineEnd = bLoadFullFile ? m_iaLineLen.get_size() : min(m_iaLineLen.get_size(), m_iLineCount + m_iLineStart);

      if (m_iLineOffset < 0)
      {

         return;

      }

      m_iViewOffset = m_iaLineBeg[m_iLineStart];

      strsize iProperBeg = m_iaLineBeg[m_iLineEnd - 1];

      strsize iLen = m_iaLineLen[m_iLineEnd - 1];

      m_iViewSize = iProperBeg + iLen - m_iViewOffset;

      index iLineStart;

      index iLineEnd;

      index iViewOffset;

      index iViewSize;

      if (iLineUpdate < 0)
      {

         iLineStart = m_iLineStart;

         iLineEnd = m_iLineEnd;

         iViewOffset = m_iViewOffset;

         iViewSize = m_iViewSize;

      }
      else
      {

         iLineStart = iLineUpdate;

         iLineEnd = iLineStart + 1;

         iViewOffset = m_iaLineBeg[iLineStart];

         iProperBeg = m_iaLineBeg[iLineEnd - 1];

         iLen = m_iaLineLen[iLineEnd - 1];

         iViewSize = iProperBeg + iLen - iViewOffset;

      }

      string strLine;

      memory mem;

      mem.set_size(iViewSize + 1);

      strsize iRead;

      {

         m_ptree->m_peditfile->seek(iViewOffset, ::file::seek_begin);

         iRead = m_ptree->m_peditfile->read(mem.get_data(), iViewSize);

         if (iRead < iViewSize)
         {

            TRACE("ops1");

            iViewSize = iRead;

         }

         mem.get_data()[iViewSize] = 0;

      }

      strsize iPos = 0;

      //      strsize iLen;

      strsize iStrLen;

      //m_plines->lines.set_size(m_iLineEnd - m_iLineStart);
      m_straLines.set_size(m_iLineEnd - m_iLineStart);

      i = 0;

      iLine = iLineStart;

      m_daExtent.set_size(m_iaLineLen.get_size());

      for (; iLine < iLineEnd; i++, iLine++)
      {

         iLen = m_iaLineLen[iLine];

         iStrLen = max(0, iLen - (m_iaLineEnd[iLine] & 255));

         if (iPos + iStrLen > m_iViewSize)
         {

            TRACE("ops3");

            iStrLen = iViewSize - iPos;

            if (iStrLen <= 0)
            {

               TRACE("ops4");

               break;

            }

         }

         string strLine = string((const char *)&mem.get_data()[iPos], iStrLen);

         //if (strLine != m_plines->lines[i])
         if (strLine != m_straLines[i])
         {

            //m_plines->lines[i] = strLine;
            m_straLines[i] = strLine;

            m_daExtent[i + iLineStart].set_size(0);

         }
         else
         {

            //TRACE("optstr");

         }

         iPos += iLen;

         if (iPos > iViewSize)
         {

            TRACE("ops2");

            break;

         }

      }

      m_y = pointOffset.y;

      //::colorertake5::base_editor * pcolorer = colorertake5();

      //if (pcolorer != nullptr)
      //{

      //   pcolorer->visibleTextEvent(m_iLineStart, m_iLineCount);

      //}

      //string_array & straLines = m_plines->lines;

      string_array & straLines = m_straLines;

      if (iLineUpdate < 0)
      {

         //m_sizeTotal.cx = 0;

      }

      sized size;

      string strLineGraphics;

      strsize_array iaTab;

      strsize iTab;

      strsize iAddUp;

      for (i32 i = 0; i < straLines.get_size(); i++)
      {

         strLine = straLines[i];

         iTab = -1;

         iaTab.remove_all();

         strLineGraphics = strLine;

         ::str::replace_tab(0, strLineGraphics, m_iTabWidth, &iaTab);

         const char * pszStart = strLine;

         const char * psz = pszStart;

         strsize iLen = 0;

         iAddUp = 0;

         iPos = 0;

         const char * pszNext = pszStart;

         double_array & daExtent = m_daExtent[m_iLineStart + i];

         if (daExtent.get_size() <= 0)
         {

            daExtent.set_size(strLine.get_length() + 1);

            while (*pszNext != '\0')
            {

               pszNext = ::str::utf8_inc(psz);

               iLen = pszNext - psz;

               if (*psz == '\t')
               {

                  iTab++;

                  iAddUp += iaTab[iTab] - 1;

               }

               size = pgraphics->GetTextExtent(strLineGraphics, strLineGraphics.get_length(), pszNext - pszStart + iAddUp);

               for (int j = 0; j < iLen; j++)
               {

                 daExtent [(::index)(psz - pszStart + j)] = size.cx;

               }

               psz = pszNext;

            }

            if (strLineGraphics.has_char())
            {

               size = pgraphics->GetTextExtent(strLineGraphics, strLineGraphics.get_length());

               for (int j = 0; j < iLen; j++)
               {

                  daExtent[(::index)(psz - pszStart)] = size.cx;

               }

            }


            if (size.cx > m_sizeTotal.cx)
            {

               m_sizeTotal.cx = (i32)size.cx;

            }

         }


      }

      //if (iLineUpdate < 0)
      //{

      //   m_sizeTotal.cy = (((i32)m_iaLineLen.get_count() + (m_bMultiLine ? max(5, m_iLineCount) : 0)) * m_iLineHeight);

      //   const ::size & sizePage;

      //   sizePage = rectClient.size();

      //   if (m_sizeTotal.cy < sizePage.cy)
      //   {

      //      sizePage.cy = m_sizeTotal.cy;

      //   }

      //}

      //on_change_view_size();

      //m_bCalcLayoutHintNoTextChange = false;

   }


   void plain_edit::plain_edit_on_calc_layout(::draw2d::graphics_pointer& pgraphics, index iLineUpdate)
   {

      sync_lock sl(mutex());

      if (!m_bMultiLine)
      {

         string strTextPrevious;

         _001GetText(strTextPrevious);

         string strText(strTextPrevious);

         if (strText.contains("\n"))
         {

            if(Session.m_bProgrammerMode)
            {

               strText.replace("\n", "\\n");

            }
            else
            {

               strText.replace("\n", "");

            }

         }

         if (strText.contains("\r"))
         {

            if (Session.m_bProgrammerMode)
            {

               strText.replace("\r", "\\r");

            }
            else
            {

               strText.replace("\r", "");

            }

         }

         if (strTextPrevious != strText)
         {

            sync_lock sl(mutex());

            m_ptree->m_peditfile->seek(0, ::file::seek_begin);
            m_ptree->m_peditfile->Delete((memsize)m_ptree->m_peditfile->get_length());
            m_ptree->m_peditfile->seek(0, ::file::seek_begin);
            m_ptree->m_peditfile->Insert(strText, strText.get_length());


         }

      }

      ::rect rectClient;

      GetFocusRect(rectClient);

      if (rectClient.area() <= 0)
      {

         return;

      }

      m_pinternal->update(pgraphics, this);

      if (m_ptree == nullptr)
      {

         m_iLineCount = 0;

         m_iLineOffset = 0;

         m_iLineStart = 0;

         m_iLineEnd = 0;

         m_iViewOffset = 0;

         m_iViewSize = 0;

         m_sizeTotal = rectClient.size();

         on_change_view_size();

         return;

      }

      ::index i;

      ::index iLine;

      pgraphics->set_font(this);

      sized sizeUniText;

      if (pgraphics == nullptr)
      {

         return;

      }

      pgraphics->set_text_rendering_hint(::draw2d::text_rendering_hint_anti_alias);

      ::draw2d::text_metric metric;

      pgraphics->get_text_metrics(&metric);

      //int iChW = sizeUniText.cy / wstr.length();

      m_iLineHeight = (int)metric.tmHeight;

      m_scrolldataVert.m_iLine = m_iLineHeight;

      //m_scrolldataHorz.m_iLine = metric.tmAveCharWidth;

      if (m_iLineHeight <= 0)
      {

         m_iLineHeight = 18;

      }

      auto pointOffset = get_viewport_offset();

      m_iLineCount = ((rectClient.height() + m_iLineHeight - 1) / m_iLineHeight) + 2;

      m_iLineOffset = min(max(0, pointOffset.y / m_iLineHeight), m_iaLineBeg.get_upper_bound());

      bool bLoadFullFile = should_load_full_file();

      m_iLineStart = bLoadFullFile ? 0 : max(0, m_iLineOffset);

      m_iLineEnd = bLoadFullFile ? m_iaLineLen.get_size() : min(m_iaLineLen.get_size(), m_iLineCount + m_iLineStart);

      if (m_iLineOffset < 0)
      {

         return;

      }

      m_iViewOffset = m_iaLineBeg[m_iLineStart];

      strsize iProperBeg = m_iaLineBeg[m_iLineEnd - 1];

      strsize iLen = m_iaLineLen[m_iLineEnd - 1];

      m_iViewSize = iProperBeg + iLen - m_iViewOffset;

      index iLineStart;

      index iLineEnd;

      index iViewOffset;

      index iViewSize;

      if (iLineUpdate < 0)
      {

         iLineStart = m_iLineStart;

         iLineEnd = m_iLineEnd;

         iViewOffset = m_iViewOffset;

         iViewSize = m_iViewSize;

      }
      else
      {

         iLineStart = iLineUpdate;

         iLineEnd = iLineStart + 1;

         iViewOffset = m_iaLineBeg[iLineStart];

         iProperBeg = m_iaLineBeg[iLineEnd - 1];

         iLen = m_iaLineLen[iLineEnd - 1];

         iViewSize = iProperBeg + iLen - iViewOffset;

      }

      string strLine;

      memory mem;

      mem.set_size(iViewSize + 1);

      strsize iRead;

      {

         m_ptree->m_peditfile->seek(iViewOffset, ::file::seek_begin);

         iRead = m_ptree->m_peditfile->read(mem.get_data(), iViewSize);

         if (iRead < iViewSize)
         {

            TRACE("ops1");

            iViewSize = iRead;

         }

         mem.get_data()[iViewSize] = 0;

      }

      strsize iPos = 0;

      //      strsize iLen;

      strsize iStrLen;

      //m_plines->lines.set_size(m_iLineEnd - m_iLineStart);

      string_array & straLines = m_straLines;

      straLines.set_size(m_iLineEnd - m_iLineStart);

      i = 0;

      iLine = iLineStart;

      m_daExtent.set_size(m_iaLineLen.get_size());

      for (; iLine < iLineEnd; i++, iLine++)
      {

         iLen = m_iaLineLen[iLine];

         iStrLen = max(0, iLen - (m_iaLineEnd[iLine] & 255));

         if (iPos + iStrLen > m_iViewSize)
         {

            TRACE("ops3");

            iStrLen = iViewSize - iPos;

            if (iStrLen <= 0)
            {

               TRACE("ops4");

               break;

            }

         }

         string strLine = string((const char *)&mem.get_data()[iPos], iStrLen);

         string_array & straLines = m_straLines;

         //if (strLine != m_plines->lines[i])
         if (strLine != straLines[i])
         {

            straLines[i] = strLine;

            m_daExtent[i + iLineStart].set_size(0);

         }
         else
         {

            //TRACE("optstr");

         }




         iPos += iLen;

         if (iPos > iViewSize)
         {

            TRACE("ops2");

            break;

         }

      }

      m_y = pointOffset.y;

      //::colorertake5::base_editor * pcolorer = colorertake5();

      //if (pcolorer != nullptr)
      //{

      //   pcolorer->visibleTextEvent(m_iLineStart, m_iLineCount);

      //}

//      string_array & straLines = m_plines->lines;
//      string_array & straLines = m_straLines;

      if (iLineUpdate < 0)
      {

         //m_sizeTotal.cx = 0;

      }

      sized size;



      string strLineGraphics;

      strsize_array iaTab;

      strsize iTab;

      strsize iAddUp;


      for (i32 i = 0; i < straLines.get_size(); i++)
      {

         strLine = straLines[i];

         iTab = -1;

         iaTab.remove_all();

         strLineGraphics = strLine;

         bool bTabs = strLine.find('\t') >= 0;

         if (bTabs)
         {

            ::str::replace_tab(0, strLineGraphics, m_iTabWidth, &iaTab);

         }

         const char * pszStart = strLine;

         const char * psz = pszStart;

         strsize iLen = 0;

         iAddUp = 0;

         iPos = 0;

         const char * pszNext = pszStart;

         ::size sizeLast(0, 0);

         auto & daExtent = m_daExtent[m_iLineStart + i];

         if (daExtent.get_size() <= 0)
         {

            daExtent.set_size(strLine.get_length() + 1);

            while (*pszNext != '\0')
            {

               pszNext = ::str::utf8_inc(psz);

               if (pszNext == nullptr)
               {

                  break;

               }

               iLen = pszNext - psz;

               if (*psz == '\t')
               {

                  iTab++;

                  iAddUp += iaTab[iTab] - 1;

               }

               size = pgraphics->GetTextExtent(strLineGraphics, strLineGraphics.get_length(), pszNext - pszStart + iAddUp);

               if (size.cx > rectClient.width() + 200)
               {

                  while (*psz != '\0')
                  {

                     daExtent[(::index)(psz - pszStart)] = -1;
                     psz++;

                  }

                  break;

               }

               sizeLast.cx = (LONG) size.cx;

               for (int j = 0; j < iLen; j++)
               {

                  daExtent[(::index)(psz - pszStart + j)] = size.cx;

               }

               psz = pszNext;

            }

            if (strLineGraphics.has_char())
            {

               size = pgraphics->GetTextExtent(strLineGraphics, strLineGraphics.get_length());

               daExtent[(::index)(psz - pszStart)] = size.cx;

            }

            if (size.cx > m_sizeTotal.cx)
            {

               m_sizeTotal.cx = (i32)size.cx;

            }

         }


      }

      if (iLineUpdate < 0)
      {

         m_sizeTotal.cy = (LONG) ((((i32)m_iaLineLen.get_count() + (m_bMultiLine ? max(5, m_iLineCount) : 0)) * m_iLineHeight));

         ::sized sizePage;

         sizePage = rectClient.size();

         if (m_sizeTotal.cy < sizePage.cy)
         {

            sizePage.cy = m_sizeTotal.cy;

         }

      }

      on_change_view_size();

      m_bCalcLayoutHintNoTextChange = false;

   }


   index plain_edit::plain_edit_sel_to_line(::draw2d::graphics_pointer& pgraphics, strsize iSel)
   {

      sync_lock sl(mutex());

      strsize i1;

      strsize i2 = 0;

      index iLine = 0;

      for (; iLine < m_iaLineLen.get_size(); iLine++)
      {

         i1 = i2;

         i2 = i1 + m_iaLineLen[iLine];

         if (iSel >= i1 && iSel < i2)
         {

            return iLine;

         }

      }

      return m_iaLineLen.get_upper_bound();

   }


   index plain_edit::plain_edit_char_to_line(::draw2d::graphics_pointer& pgraphics, strsize iChar)
   {

      sync_lock sl(mutex());

      for (index iLine = 0; iLine < m_iaLineBeg.get_size(); iLine++)
      {

         if (iChar >= m_iaLineBeg[iLine] && iChar < m_iaLineBeg[iLine] + m_iaLineLen[iLine])
         {

            return iLine;

         }

      }

      return m_iaLineBeg.get_count();

   }


   bool plain_edit::plain_edit_caret_rect(::draw2d::graphics_pointer& pgraphics, LPRECT lprect, strsize iSel)
   {

      int x = 0;

      ::index iLine = plain_edit_sel_to_line_x(pgraphics, iSel, x);

      if(!plain_edit_line_range(pgraphics, lprect, iLine))
      {

         return false;

      }

      lprect->left = x;

      lprect->right = x + 1;

      return true;

   }


   bool plain_edit::plain_edit_index_range(::draw2d::graphics_pointer& pgraphics, LPRECT lprect, strsize iSel)
   {

      index iLine = plain_edit_char_to_line(pgraphics, iSel);

      return plain_edit_line_range(pgraphics, lprect, iLine);

   }


   bool plain_edit::plain_edit_line_range(::draw2d::graphics_pointer& pgraphics, LPRECT lprect, ::index iLine)
   {

      if(iLine < 0)
      {

         return false;

      }

      lprect->top = (LONG) (iLine * m_iItemHeight);

      lprect->bottom = (LONG) (lprect->top + m_iItemHeight);

      return true;

   }


   double plain_edit::plain_edit_get_line_extent(::draw2d::graphics_pointer& pgraphics, index iLine, strsize iChar)
   {

      if (iLine < 0 || iChar < 0)
      {

         return 0;

      }

      sync_lock sl(mutex());

      if (iLine >= m_iaLineLen.get_size())
      {

         return 0;

      }

      if (iChar > m_iaLineLen[iLine])
      {

         return 0;

      }

      if (iLine < m_daExtent.get_size())
      {

         if (iChar == 0)
         {

            return 0;

         }
         else if (iChar -1< m_daExtent[iLine].get_size())
         {

            return m_daExtent[iLine][iChar-1];

         }

      }

      pgraphics->set_font(this);

      pgraphics->set_text_rendering_hint(::draw2d::text_rendering_hint_anti_alias);

      string strLine = plain_edit_get_expanded_line(pgraphics, iLine, { &iChar });

      sized size = pgraphics->GetTextExtent(strLine, (i32)strLine.length(), (i32)iChar);

      return size.cx;


   }


   index plain_edit::plain_edit_sel_to_line_x(::draw2d::graphics_pointer & pgraphics, strsize iSel, i32 & x)
   {

      sync_lock sl(mutex());

      ::rect rectClient;

      GetFocusRect(rectClient);

      strsize i1;

      strsize i2 = 0;

      for (index iLine = 0; iLine < m_iaLineLen.get_size(); iLine++)
      {

         i1 = i2;

         i2 = i1 + m_iaLineLen[iLine];

         if (iSel < i2)
         {

            strsize iRel = iSel - i1;

            x = (i32)plain_edit_get_line_extent(pgraphics, iLine, iRel);

            return iLine;

         }

      }

      x = rectClient.left;

      return m_iaLineLen.get_upper_bound();

   }


   strsize plain_edit::plain_edit_line_column_to_sel(::draw2d::graphics_pointer& pgraphics, index iLine, index iColumn)
   {

      sync_lock sl(mutex());

      while (iLine < 0)
      {

         plain_edit_one_line_up(pgraphics);

         if (m_iViewOffset == 0)
         {

            iLine = 0;

            break;

         }

         iLine++;

      }

//      string_array & straLines = m_plines->lines;
      string_array & straLines = m_straLines;

      if (iLine >= straLines.get_size())
      {

         return 0;

      }

      strsize iOffset = 0;

      for (i32 i = 0; i < iLine; i++)
      {

         iOffset += m_iaLineLen[i];

      }

      string_array stra;

      string strLine;

      stra.remove_all();

      stra.add_lines(straLines[iLine], false);

      if (stra.get_size() > 0)
      {

         strLine = stra[0];

      }
      else
      {

         strLine.Empty();

      }

      if (iColumn < 0)
      {

         iColumn = iColumn + 1 + strLine.get_length();

      }

      if (iColumn > strLine.get_length())
      {

         iColumn = strLine.get_length();

      }

      return m_iViewOffset + iOffset + iColumn;

   }


   strsize plain_edit::plain_edit_line_x_to_sel(::draw2d::graphics_pointer& pgraphics, index iLine, i32 x)
   {

      sync_lock sl(mutex());

      pgraphics.defer_create();

      pgraphics->set_font(this);

      ::rect rectClient;

      GetFocusRect(rectClient);

      pgraphics->set_text_rendering_hint(::draw2d::text_rendering_hint_anti_alias);

      strsize iChar = plain_edit_line_char_hit_test(pgraphics, x, iLine);

      return iChar;

   }


   index plain_edit::plain_edit_sel_to_column_x(::draw2d::graphics_pointer& pgraphics, strsize iSel, i32 & x)
   {

      sync_lock sl(mutex());

      ::rect rectClient;

      GetFocusRect(rectClient);

      strsize i1;

      strsize i2 = 0;

      for (index iLine = 0; iLine < m_iaLineLen.get_size(); iLine++)
      {

         i1 = i2;

         i2 = i1 + m_iaLineLen[iLine];

         if (iSel >= i1 && iSel < i2)
         {

            strsize iRel = iSel - i1;

            int x;

            x = (int) (plain_edit_get_line_extent(pgraphics, iLine, iRel));

            x = rectClient.left + x;

            return iRel;

         }

      }

      return -1;

   }


   index plain_edit::plain_edit_sel_to_column(::draw2d::graphics_pointer& pgraphics, strsize iSel)
   {

      sync_lock sl(mutex());

      //string_array & straLines = m_plines->lines;

      strsize i1;

      strsize i2 = 0;

      for (index i = 0; i < m_iaLineLen.get_size(); i++)
      {

         i1 = i2;

         i2 = i1 + m_iaLineLen[i];

         if (iSel >= i1 && iSel < i2)
         {

            return iSel - i1;

         }

      }

      return -1;

   }


   strsize plain_edit::plain_edit_char_hit_test(::draw2d::graphics_pointer& pgraphics, i32 px, i32 py)
   {

      sync_lock sl(mutex());

      ::rect rectClient;

      GetFocusRect(rectClient);

      py -= rectClient.top;

      auto pointOffset = get_viewport_offset();

      if (m_iLineHeight > 0)
      {

         int iVerticalOffsetModule = pointOffset.y % m_iLineHeight;

         if (iVerticalOffsetModule > 0)
         {

            py += iVerticalOffsetModule;

         }

      }

      i32 iLineHeight;

      i32 y = 0;

      bool bFound = false;

      iLineHeight = m_iLineHeight;

      strsize iOffset = 0;

      string_array stra;

      index iLine;

      for (iLine = m_iLineStart; iLine < m_iLineEnd; iLine++)
      {

         if (py < y + iLineHeight)
         {

            bFound = true;

            break;

         }

         y += iLineHeight;

         iOffset += m_iaLineLen[iLine];

      }

      if (!bFound)
      {

         if (iLine > m_iLineStart)
         {

            iLine--;

         }

      }

      return plain_edit_line_char_hit_test(pgraphics, px, iLine);

   }


   strsize plain_edit::plain_edit_line_char_hit_test(::draw2d::graphics_pointer& pgraphics, i32 px, index iLine)
   {

      sync_lock sl(mutex());

      ::rect rectClient;

      GetFocusRect(rectClient);

      auto pointOffset = get_viewport_offset();

      px -= (rectClient.left - pointOffset.x);


      if (px <= 0)
      {

         px = 0;

      }

      i32 lim = 0;

      //bool bFound = false;

      string strLine = plain_edit_get_line(pgraphics, iLine);

      i32 lim2 = 0;

      i32 lim1;

      const char * psz = strLine;

      const char * pszEnd = psz;

      const char * pszPrevious = psz;

      //string strLineGraphics = strLine;

      //replace_tab(0, strLineGraphics, m_iTabWidth);

      strsize iSel;

      string strExtent;

      for (;;)
      {

         pszPrevious = pszEnd;

         pszEnd = ::str::utf8_inc(pszEnd);

         if (pszEnd == nullptr)
            break;

         lim1 = lim2;

         strExtent = string(psz, pszEnd - psz);

         ::str::replace_tab(0, strExtent, m_iTabWidth);

         int x;

         x = (int) (plain_edit_get_line_extent(pgraphics, iLine, strExtent.length()));

         lim2 = x;

         lim = lim2;

         int iMid = (lim2 - lim1) * 3 / 4;

         if (px >= lim1 && px <= lim1 + iMid)
         {

            iSel = m_iaLineBeg[iLine] + (pszPrevious - psz);

            goto end;

         }
         else if (px >= lim1 + iMid && px <= lim2)
         {

            iSel = m_iaLineBeg[iLine] + (pszEnd - psz);

            goto end;

         }

         if (pszEnd[0] == '\0')
         {

            break;

         }

      }

      iSel = m_iaLineBeg[iLine] + (m_iaLineLen[iLine] - (m_iaLineEnd[iLine] & 0xf));

end:

      if (iSel > _001GetTextLength())
      {

         iSel = _001GetTextLength();

      }

      return iSel;

   }




   void plain_edit::_001GetViewSel(strsize & iSelBeg, strsize & iSelEnd) const
   {

      sync_lock sl(mutex());




      if (m_ptree == nullptr)
      {

         iSelBeg = 0;

         iSelEnd = 0;

      }
      else
      {

         iSelBeg = m_ptree->m_iSelBeg - m_iViewOffset;

         iSelEnd = m_ptree->m_iSelEnd - m_iViewOffset;

         if (iSelBeg < 0)
         {

            iSelBeg = 0;

         }
         else if (::comparison::gt(iSelBeg, m_ptree->m_peditfile->get_length()))
         {

            iSelBeg = (strsize) (m_ptree->m_peditfile->get_length());

         }

         if (iSelEnd < 0)
         {

            iSelEnd = 0;

         }
         else if (::comparison::gt(iSelEnd, m_ptree->m_peditfile->get_length()))
         {

            iSelEnd = (strsize) (m_ptree->m_peditfile->get_length());

         }

      }

   }


   void plain_edit::_001GetSel(strsize & iBeg, strsize & iEnd) const
   {

      sync_lock sl(mutex());

      iBeg = m_ptree->m_iSelBeg;

      iEnd = m_ptree->m_iSelEnd;

   }




   void plain_edit::FileSave()
   {

      sync_lock sl(mutex());



      m_ptree->m_peditfile->flush();

   }


   void plain_edit::plain_edit_on_file_update(::draw2d::graphics_pointer& pgraphics)
   {

      m_bGetTextNeedUpdate = true;

      plain_edit_create_line_index(pgraphics);

      m_y = -1;

   }


   void plain_edit::plain_edit_create_line_index(::draw2d::graphics_pointer& pgraphics)
   {

      sync_lock sl(mutex());

      memory m;

      m.set_size(1024 * 1024);

      char * buf = (char *)m.get_data();

      memsize uiRead;

      char * psz;


      m_ptree->m_peditfile->seek(0, ::file::seek_begin);

      if (m_sizeTotal.cx <= 0)
      {

         m_sizeTotal.cx = 200;

      }

      i32 iLineSize = 0;

      m_iaLineLen.remove_all();

      m_iaLineEnd.remove_all();

      memsize uiPos;

      int iLastR = 0;

      while ((uiRead = m_ptree->m_peditfile->read(buf, m.get_size())) > 0)
      {

         uiPos = 0;

         psz = buf;


         while (uiPos < uiRead)
         {

            if (*psz == '\r')

            {

               if (iLastR)
               {

                  iLineSize++;

                  m_iaLineLen.add(iLineSize);

                  m_iaLineEnd.add(1 | 512);

                  iLineSize = 0;

               }

               iLastR = 1;

            }
            else if (*psz == '\n')

            {

               if (iLastR)
               {

                  iLineSize += 2;

                  m_iaLineLen.add(iLineSize);

                  m_iaLineEnd.add(2 | 1024);

                  iLineSize = 0;


               }
               else
               {

                  iLineSize++;

                  m_iaLineLen.add(iLineSize);

                  m_iaLineEnd.add(1 | 256);

                  iLineSize = 0;

               }

               iLastR = 0;

            }
            else
            {

               if (iLastR)
               {

                  iLineSize++;

                  m_iaLineLen.add(iLineSize);

                  m_iaLineEnd.add(1 | 512);

                  iLineSize = 0;

                  iLastR = 0;

               }

               iLineSize++;

            }

            psz++;

            uiPos++;

         }


      }

      if (iLastR)
      {

         iLineSize++;

         m_iaLineLen.add(iLineSize);

         m_iaLineEnd.add(1 | 512);

         iLineSize = 0;

      }

      m_iaLineLen.add(iLineSize);

      m_iaLineEnd.add(0);

      ::count iAcc = 0;

      ::count iLineCount = m_iaLineLen.get_size();

      m_iaLineBeg.set_size(iLineCount);

      for (index iLine = 0; iLine < iLineCount; iLine++)
      {

         m_iaLineBeg[iLine] = iAcc;

         iAcc += m_iaLineLen[iLine];

      }

   }


   void plain_edit::plain_edit_update_line_index(::draw2d::graphics_pointer& pgraphics, index iLine)
   {

      sync_lock sl(mutex());

      memory m;

      strsize iOffset = 0;

      for (index i = 0; i < iLine; i++)
      {

         iOffset += m_iaLineLen[i];

      }

      m.set_size(1024);

      char * buf = (char *)m.get_data();

      memsize uiRead;

      char * psz;

      m_ptree->m_peditfile->seek(iOffset, ::file::seek_begin);

      if (m_sizeTotal.cx <= 0)
      {

         m_sizeTotal.cx = 200;

      }

      i32 iLineSize = 0;

      memsize uiPos;

      int iLastR = 0;

      bool bSet = false;

      while ((uiRead = m_ptree->m_peditfile->read(buf, m.get_size())) > 0)
      {

         uiPos = 0;

         psz = buf;


         while (uiPos < uiRead)
         {

            if (*psz == '\r')

            {

               if (iLastR)
               {

                  iLineSize++;

                  m_iaLineLen[iLine] = iLineSize;

                  m_iaLineEnd[iLine] = 1 | 512;

                  iLastR = 0;

                  bSet = true;

                  goto finished_update;

               }

               iLastR = 1;

            }
            else if (*psz == '\n')

            {

               if (iLastR)
               {

                  iLineSize += 2;

                  m_iaLineLen[iLine] = iLineSize;

                  m_iaLineEnd[iLine] = 2 | 1024;

                  iLastR = 0;

                  bSet = true;

                  goto finished_update;

               }
               else
               {

                  iLineSize++;

                  m_iaLineLen[iLine] = iLineSize;

                  m_iaLineEnd[iLine] = 1 | 256;

                  iLastR = 0;

                  bSet = true;

                  goto finished_update;

               }

               //iLastR = 0;

            }
            else
            {

               if (iLastR)
               {

                  iLineSize++;

                  m_iaLineLen[iLine] = iLineSize;

                  m_iaLineEnd[iLine] = 1 | 512;

                  iLastR = 0;

                  bSet = true;

                  goto finished_update;

               }

               iLineSize++;

            }

            psz++;


            uiPos++;

         }


      }

      if (iLastR)
      {

         iLineSize++;

         m_iaLineLen[iLine] = iLineSize;

         m_iaLineEnd[iLine] = 1 | 512;

         bSet = true;

         goto finished_update;

      }

finished_update:

      if (!bSet)
      {

         m_iaLineLen[iLine] = iLineSize;

         m_iaLineEnd[iLine] = 0;


      }

      ::count iLineCount = m_iaLineLen.get_size();

      for (; iLine < iLineCount; iLine++)
      {

         m_iaLineBeg[iLine] = iOffset;

         iOffset += m_iaLineLen[iLine];

      }

   }


   void plain_edit::_001OnUniChar(::message::message * pmessage)
   {

      //      SCAST_PTR(::message::base, pbase, pmessage);
      //
      //      if (::str::ch::is_legal_uni_index(pbase->m_wparam))
      //      {
      //
      //#ifdef WINDOWS_DESKTOP
      //
      //         on_reset_focus_start_tick();
      //
      //         if (!m_bReadOnly)
      //         {
      //
      //            string str;
      //
      //            wd32char u32[2];
      //
      //            u32[0] = pbase->m_wparam;
      //
      //            u32[1] = 0;
      //
      //            str = wd32_to_ansi(u32, 1);
      //
      //            insert_text(str);
      //
      //         }
      //#endif
      //
      //      }

   }


   void plain_edit::plain_edit_on_delete(::draw2d::graphics_pointer& pgraphics)
   {

      sync_lock sl(mutex());

      bool bFullUpdate = false;

      index iLineUpdate = -1;

      if (!m_bReadOnly)
      {

         strsize i1 = m_ptree->m_iSelBeg;

         strsize i2 = m_ptree->m_iSelEnd;

         if (i1 != i2)
         {

            on_before_change_text();

            auto psetsel  = __new(plain_text_set_sel_command);

            psetsel->m_iPreviousSelBeg = m_ptree->m_iSelBeg;

            psetsel->m_iPreviousSelEnd = m_ptree->m_iSelEnd;

            ::sort::sort_non_negative(i1, i2);

            string strSel;

            _001GetText(strSel, i1, i2);

            bFullUpdate = strSel.find('\n') >= 0 || strSel.find('\r') >= 0;

            if (!bFullUpdate)
            {

               iLineUpdate = plain_edit_sel_to_line(pgraphics, i1);

            }

            m_ptree->m_peditfile->seek(i1, ::file::seek_begin);

            m_ptree->m_peditfile->Delete((memsize)(i2 - i1));

            m_pinsert = nullptr;

            m_ptree->m_iSelEnd = i1;

            auto iSelBeg = m_ptree->m_iSelEnd;

            auto iSelEnd = m_ptree->m_iSelEnd;

            psetsel->m_iSelBeg = iSelBeg;

            psetsel->m_iSelEnd = iSelEnd;

            _001SetSel(iSelBeg, iSelEnd);

            MacroBegin();

            MacroRecord(psetsel);

            MacroRecord(__new(plain_text_file_command()));

            MacroEnd();

         }
         else if (m_ptree->m_iSelEnd< m_ptree->m_peditfile->get_length())
         {

            on_before_change_text();

            char buf[512];

            __memset(buf, 0, sizeof(buf));

            m_ptree->m_peditfile->seek(m_ptree->m_iSelEnd, ::file::seek_begin);

            m_ptree->m_peditfile->read(buf, sizeof(buf));

            const char * psz = ::str::utf8_inc(buf);

            strsize iMultiByteUtf8DeleteCount = psz - buf;

            index i1 = m_ptree->m_iSelEnd;

            index i2 = i1 + iMultiByteUtf8DeleteCount;

            string strSel;

            _001GetText(strSel, i1, i2);

            bFullUpdate = strSel.find('\n') >= 0 || strSel.find('\r') >= 0;

            if (!bFullUpdate)
            {

               iLineUpdate = plain_edit_sel_to_line(pgraphics, i1);

            }

            m_ptree->m_peditfile->seek(m_ptree->m_iSelEnd, ::file::seek_begin);

            m_ptree->m_peditfile->Delete((memsize)(iMultiByteUtf8DeleteCount));

            m_pinsert = nullptr;

            IndexRegisterDelete(m_ptree->m_iSelEnd, iMultiByteUtf8DeleteCount);

            m_ptree->m_iSelBeg = m_ptree->m_iSelEnd;

            MacroBegin();

            MacroRecord(__new(plain_text_file_command()));

            MacroEnd();

         }

      }

      plain_edit_update(pgraphics, bFullUpdate, iLineUpdate);

   }


   void plain_edit::_001DeleteSel()
   {

      bool bFullUpdate = true;

      index iLineUpdate = -1;

      auto pgraphics = ::draw2d::create_memory_graphics();

      if(plain_edit_delete_sel(pgraphics, bFullUpdate, iLineUpdate))
      {

         plain_edit_update(pgraphics, bFullUpdate, iLineUpdate);

      }

   }


   bool plain_edit::plain_edit_delete_sel(::draw2d::graphics_pointer& pgraphics, bool & bFullUpdate, index & iLineUpdate)
   {

      sync_lock sl(mutex());

      strsize i1 = m_ptree->m_iSelBeg;

      strsize i2 = m_ptree->m_iSelEnd;

      ::sort::sort_non_negative(i1, i2);

      if(i1 < 0 || i1 > _001GetTextLength())
      {

         i1  = _001GetTextLength();

      }

      if(i2 < 0 || i2 > _001GetTextLength())
      {

         i2 = _001GetTextLength();

      }

      if(i1 >= i2)
      {

         return false;

      }

      on_before_change_text();

      auto psetsel  = __new(plain_text_set_sel_command);

      psetsel->m_iPreviousSelBeg = m_ptree->m_iSelBeg;

      psetsel->m_iPreviousSelEnd = m_ptree->m_iSelEnd;

      string strSel;

      _001GetText(strSel, i1, i2);

      bFullUpdate = strSel.find('\n') >= 0 || strSel.find('\r') >= 0;

      if (!bFullUpdate)
      {

         iLineUpdate = plain_edit_sel_to_line(pgraphics, i1);

      }

      m_ptree->m_peditfile->seek(i1, ::file::seek_begin);

      m_ptree->m_peditfile->Delete((memsize)(i2 - i1));

      m_pinsert = nullptr;

      IndexRegisterDelete(i1, i2 - i1);

      m_ptree->m_iSelEnd = i1;

      m_ptree->m_iSelBeg = m_ptree->m_iSelEnd;

      psetsel->m_iSelBeg = m_ptree->m_iSelBeg;

      psetsel->m_iSelEnd = m_ptree->m_iSelEnd;

      MacroBegin();

      MacroRecord(psetsel);

      MacroRecord(__new(plain_text_file_command()));

      MacroEnd();

      return true;

   }


   void plain_edit::_001ReplaceSel(const char * pszText)
   {

      bool bFullUpdate = true;

      index iLineUpdate = -1;

      if(_001ReplaceSel(pszText, bFullUpdate, iLineUpdate))
      {

         auto pgraphics = ::draw2d::create_memory_graphics();

         plain_edit_update(pgraphics, bFullUpdate, iLineUpdate);

      }

   }


   bool plain_edit::_001ReplaceSel(const char * pszText, bool & bFullUpdate, index & iLineUpdate)
   {

      sync_lock sl(mutex());

      strsize i1 = m_ptree->m_iSelBeg;

      strsize i2 = m_ptree->m_iSelEnd;

      ::sort::sort_non_negative(i1, i2);

      if(i1 < 0 || i1 > _001GetTextLength())
      {

         i1  = _001GetTextLength();

      }

      if(i2 < 0 || i2 > _001GetTextLength())
      {

         i2 = _001GetTextLength();

      }

      if(i2 < i1)
      {

         return false;

      }

      on_before_change_text();

      auto psetsel  = __new(plain_text_set_sel_command);

      psetsel->m_iPreviousSelBeg = m_ptree->m_iSelBeg;

      psetsel->m_iPreviousSelEnd = m_ptree->m_iSelEnd;

      string strSel;

      _001GetText(strSel, i1, i2);

      bFullUpdate = strSel.find('\n') >= 0 || strSel.find('\r') >= 0;

      ::draw2d::graphics_pointer pgraphics;

      if (!bFullUpdate)
      {

         iLineUpdate = plain_edit_sel_to_line(pgraphics, i1);

      }

      m_ptree->m_peditfile->seek(i1, ::file::seek_begin);

      if(i2 > i1)
      {

         m_ptree->m_peditfile->Delete((memsize)(i2 - i1));

         IndexRegisterDelete(i1, i2);

      }

      m_ptree->m_peditfile->Insert(pszText, ansi_length(pszText));

      IndexRegisterInsert(i1, pszText);

      m_pinsert = nullptr;

      IndexRegisterDelete(i1, i2 - i1);

      m_ptree->m_iSelEnd = i1;

      m_ptree->m_iSelBeg = m_ptree->m_iSelEnd;

      psetsel->m_iSelBeg = m_ptree->m_iSelBeg;

      psetsel->m_iSelEnd = m_ptree->m_iSelEnd;

      MacroBegin();

      MacroRecord(psetsel);

      MacroRecord(__new(plain_text_file_command()));

      MacroEnd();

      return true;

   }


   void plain_edit::_001OnChar(::message::message * pmessage)
   {

      ::draw2d::graphics_pointer pgraphics;

      bool bUpdate = true;

      bool bFullUpdate = false;

      index iLineUpdate = -1;

      {

         _009OnChar(pmessage);

         if (pmessage->m_bRet)
            return;

         INFO("plain_edit::_001OnChar (1)");

         SCAST_PTR(::message::key, pkey, pmessage);

         string strChar;

         if (pkey->m_ekey == ::user::key_s)
         {
            if (Session.is_key_pressed(::user::key_control))
            {
               return;
            }
         }
         else if (pkey->m_ekey == ::user::key_a)
         {
            if (Session.is_key_pressed(::user::key_control))
            {
               _001SetSel(0, _001GetTextLength());
               return;
            }
         }
         else if (pkey->m_ekey == ::user::key_z)
         {
            if (Session.is_key_pressed(::user::key_control))
            {
               if (is_window_enabled())
               {
                  edit_undo();
               }
               return;
            }
         }
         else if (pkey->m_ekey == ::user::key_y)
         {
            if (Session.is_key_pressed(::user::key_control))
            {
               if (is_window_enabled())
               {
                  edit_redo();
               }
               return;
            }
         }
         else if (Session.is_key_pressed(::user::key_control))
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

            bool bControl = Session.is_key_pressed(::user::key_control);
            bool bShift = Session.is_key_pressed(::user::key_shift);

            if (pkey->m_ekey == ::user::key_prior)
            {


               if (is_text_composition_active())
               {

                  return;

               }


               on_reset_focus_start_tick();

               i32 x;

               auto pgraphics = ::draw2d::create_memory_graphics();

               index iLine = plain_edit_sel_to_line_x(pgraphics, m_ptree->m_iSelEnd, x);

               ::rect rectClient;

               GetFocusRect(rectClient);

               iLine -= rectClient.height() / m_iLineHeight;

               if (iLine < 0)
               {

                  iLine = 0;

               }

               m_ptree->m_iSelEnd = plain_edit_line_x_to_sel(pgraphics, iLine, m_iColumnX);

               if (!bShift)
               {

                  m_ptree->m_iSelBeg = m_ptree->m_iSelEnd;

               }

               _001EnsureVisibleLine(iLine);

            }
            else if (pkey->m_ekey == ::user::key_next)
            {

               if (is_text_composition_active())
               {

                  return;

               }


               on_reset_focus_start_tick();

               i32 x;

               auto pgraphics = ::draw2d::create_memory_graphics();

               index iLine = plain_edit_sel_to_line_x(pgraphics, m_ptree->m_iSelEnd, x);

               ::rect rectClient;

               GetFocusRect(rectClient);

               iLine += rectClient.height() / m_iLineHeight;

               if (iLine >= m_iaLineBeg.get_size())
               {

                  iLine = m_iaLineBeg.get_upper_bound();

               }

               m_ptree->m_iSelEnd = plain_edit_line_x_to_sel(pgraphics, iLine, m_iColumnX);

               if (!bShift)
               {

                  m_ptree->m_iSelBeg = m_ptree->m_iSelEnd;

               }

               _001EnsureVisibleLine(iLine);

            }
            else if (pkey->m_ekey == ::user::key_back)
            {

               INFO("plain_edit::_001OnChar (key_back)");

               if (is_text_composition_active())
               {

#ifdef WINDOWS_DESKTOP

                  if (m_strImeComposition.has_char())
                  {

                     edit_undo();

                     m_strImeComposition.Empty();

                  }

#endif

                  return;

               }


               if (is_window_enabled())
               {

                  on_reset_focus_start_tick();

                  if (!m_bReadOnly)
                  {

                     strsize i1 = m_ptree->m_iSelBeg;

                     strsize i2 = m_ptree->m_iSelEnd;

                     if (i1 != i2)
                     {

                        _001DeleteSel();

                     }
                     else if (m_ptree->m_iSelEnd >= 0 && m_ptree->m_peditfile->get_length() > 0)
                     {

                        on_before_change_text();

                        auto psetsel  = __new(plain_text_set_sel_command);

                        psetsel->m_iPreviousSelBeg = m_ptree->m_iSelBeg;

                        psetsel->m_iPreviousSelEnd = m_ptree->m_iSelEnd;

                        char buf[512];

                        __memset(buf, 0, sizeof(buf));

                        strsize iProperBegin = max(0, m_ptree->m_iSelEnd - 256);
                        strsize iCur = m_ptree->m_iSelEnd - iProperBegin;
                        m_ptree->m_peditfile->seek(iProperBegin, ::file::seek_begin);
                        m_ptree->m_peditfile->read(buf, sizeof(buf));
                        const char * psz;
                        strsize iMultiByteUtf8DeleteCount;
                        if (iCur > 1 && buf[iCur - 1] == '\n' && buf[iCur - 2] == '\r')
                        {

                           psz = &buf[iCur - 2];
                           iMultiByteUtf8DeleteCount = 2;

                        }
                        else
                        {

                           psz = ::str::uni_dec(buf, &buf[iCur]);

                           if (psz == nullptr)
                           {

                              psz = max((char *) buf, (char *) &buf[iCur - 1]);

                           }

                           iMultiByteUtf8DeleteCount = &buf[iCur] - psz;

                        }

                        index i1 = m_ptree->m_iSelEnd;
                        index i2 = i1 + iMultiByteUtf8DeleteCount;

                        string strSel;

                        _001GetText(strSel, i1, i2);

                        bFullUpdate = strSel.find('\n') >= 0 || strSel.find('\r') >= 0;

                        if (!bFullUpdate)
                        {

                           iLineUpdate = plain_edit_sel_to_line(pgraphics, i1);

                        }

                        m_ptree->m_iSelEnd -= iMultiByteUtf8DeleteCount;
                        m_ptree->m_peditfile->seek(m_ptree->m_iSelEnd, ::file::seek_begin);
                        m_ptree->m_peditfile->Delete((memsize)iMultiByteUtf8DeleteCount);

                        m_pinsert = nullptr;

                        IndexRegisterDelete(m_ptree->m_iSelEnd, iMultiByteUtf8DeleteCount);
                        m_ptree->m_iSelBeg = m_ptree->m_iSelEnd;
                        psetsel->m_iSelBeg = m_ptree->m_iSelBeg;
                        psetsel->m_iSelEnd = m_ptree->m_iSelEnd;
                        MacroBegin();
                        MacroRecord(psetsel);
                        MacroRecord(__new(plain_text_file_command()));
                        MacroEnd();
                        //                     bUpdate = true;
                     }
                  }
               }
            }
            else if (pkey->m_ekey == ::user::key_delete)
            {
               if (is_text_composition_active())
               {

                  return;

               }

               if (is_window_enabled())
               {

                  plain_edit_on_delete(pgraphics);

               }

               return;

            }
            else if (pkey->m_ekey == ::user::key_up)
            {

               if (is_text_composition_active())
               {

                  return;

               }


               on_reset_focus_start_tick();

               i32 x;
               index iLine = plain_edit_sel_to_line_x(pgraphics, m_ptree->m_iSelEnd, x);

               iLine--;

               if (iLine < 0)
               {

                  iLine = 0;

               }

               m_ptree->m_iSelEnd = plain_edit_line_x_to_sel(pgraphics, iLine, m_iColumnX);

               if (!bShift)
               {

                  m_ptree->m_iSelBeg = m_ptree->m_iSelEnd;

               }

               _001EnsureVisibleLine(iLine);

            }
            else if (pkey->m_ekey == ::user::key_down)
            {

               if (is_text_composition_active())
               {

                  return;

               }


               on_reset_focus_start_tick();

               i32 x;

               index iLine = plain_edit_sel_to_line_x(pgraphics, m_ptree->m_iSelEnd, x);

               iLine++;

               if (iLine >= m_iaLineBeg.get_size())
               {

                  iLine = m_iaLineBeg.get_upper_bound();

               }

               m_ptree->m_iSelEnd = plain_edit_line_x_to_sel(pgraphics, iLine, m_iColumnX);

               if (!bShift)
               {
                  m_ptree->m_iSelBeg = m_ptree->m_iSelEnd;
               }
               _001EnsureVisibleLine(iLine);
            }
            else if (pkey->m_ekey == ::user::key_right)
            {
               if (is_text_composition_active())
               {

                  return;

               }


               on_reset_focus_start_tick();

               if (!bShift && m_ptree->m_iSelBeg > m_ptree->m_iSelEnd)
               {
                  m_ptree->m_iSelEnd = m_ptree->m_iSelBeg;
               }
               else if (!bShift && m_ptree->m_iSelEnd > m_ptree->m_iSelBeg)
               {
                  m_ptree->m_iSelBeg = m_ptree->m_iSelEnd;
               }
               else if (m_ptree->m_iSelEnd < m_ptree->m_peditfile->get_length())
               {
                  char buf[32];
                  m_ptree->m_peditfile->seek(m_ptree->m_iSelEnd, ::file::seek_begin);
                  memsize uiRead = m_ptree->m_peditfile->read(buf, 32);
                  if (uiRead == 2 &&
                        buf[0] == '\r' &&
                        buf[1] == '\n')
                  {
                     m_ptree->m_iSelEnd += 2;
                  }
                  else
                  {
                     m_ptree->m_iSelEnd += ::str::utf8_inc(buf) - buf;
                  }
                  _001SetSelEnd(m_ptree->m_iSelEnd);
                  if (!bShift)
                  {
                     m_ptree->m_iSelBeg = m_ptree->m_iSelEnd;
                  }
               }
            }
            else if (pkey->m_ekey == ::user::key_left)
            {

               if (is_text_composition_active())
               {

                  return;

               }

               on_reset_focus_start_tick();

               if (!bShift && m_ptree->m_iSelBeg < m_ptree->m_iSelEnd)
               {
                  m_ptree->m_iSelEnd = m_ptree->m_iSelBeg;
               }
               else if (!bShift && m_ptree->m_iSelEnd < m_ptree->m_iSelBeg)
               {
                  m_ptree->m_iSelBeg = m_ptree->m_iSelEnd;
               }
               else if (m_ptree->m_iSelEnd > 0)
               {
                  if (m_ptree->m_iSelEnd > 2)
                  {
                     char buf[64];
                     char * psz;
                     m_ptree->m_peditfile->seek(max(0, m_ptree->m_iSelEnd - 32), ::file::seek_begin);
                     psz = &buf[min(32, m_ptree->m_iSelEnd)];
                     memsize uiRead = m_ptree->m_peditfile->read(buf, 64);
                     if (uiRead == 2 &&
                           psz[0] == '\r' &&
                           psz[1] == '\n')
                     {
                        m_ptree->m_iSelEnd -= 2;
                     }
                     else
                     {
                        m_ptree->m_iSelEnd -= psz - ::str::uni_dec(buf, psz);
                     }
                  }
                  else
                  {
                     m_ptree->m_iSelEnd--;
                  }
                  _001SetSelEnd(m_ptree->m_iSelEnd);
                  if (!bShift)
                  {
                     m_ptree->m_iSelBeg = m_ptree->m_iSelEnd;
                  }
               }
            }
            else if (pkey->m_ekey == ::user::key_home)
            {

               if (is_text_composition_active())
               {

                  return;

               }


               on_reset_focus_start_tick();

               if (bControl)
               {

                  m_ptree->m_iSelEnd = 0;

                  _001EnsureVisibleLine(0);

               }

               {

                  index iLine = plain_edit_sel_to_line(pgraphics, m_ptree->m_iSelEnd);

                  m_ptree->m_iSelEnd = plain_edit_line_column_to_sel(pgraphics, iLine, 0);

               }

               if (!bShift)
               {

                  m_ptree->m_iSelBeg = m_ptree->m_iSelEnd;

               }

            }
            else if (pkey->m_ekey == ::user::key_end)
            {

               if (is_text_composition_active())
               {

                  return;

               }


               on_reset_focus_start_tick();

               if (bControl)
               {

                  index iLine = m_iaLineBeg.get_upper_bound();

                  m_ptree->m_iSelEnd = plain_edit_line_x_to_sel(pgraphics, iLine, i32 (m_iaLineLen[iLine]));

                  _001EnsureVisibleLine(iLine);

               }
               else
               {

                  index iLine = plain_edit_sel_to_line(pgraphics, m_ptree->m_iSelEnd);

                  m_ptree->m_iSelEnd = plain_edit_line_column_to_sel(pgraphics, iLine, -1);

               }

               if (!bShift)
               {

                  m_ptree->m_iSelBeg = m_ptree->m_iSelEnd;

               }

            }
            else if (pkey->m_ekey == ::user::key_escape)
            {

            }
            else if (pkey->m_ekey == ::user::key_return)
            {

               if(m_bMultiLine)
               {

                  insert_text("\n", true);

               }

            }
            else if(is_window_enabled())
            {

#if defined(WINDOWS_DESKTOP) || defined(LINUX) || defined(MACOS)

               return;

#else

               on_reset_focus_start_tick();

               if (!m_bReadOnly)
               {

                  if (pkey->m_ekey == ::user::key_return)
                  {
                     // Kill Focus => Kill Key Repeat timer
                     //System.message_box("VK_RETURN reached plain_edit");
                  }

                  string str;
                  char ch = 0;
                  if (pkey->m_ekey == ::user::key_tab)
                  {

                     if (m_bTabInsertSpaces)
                     {

                        auto iColumn = plain_edit_sel_to_column(pgraphics, m_ptree->m_iSelEnd);

                        str = string(' ', m_iTabWidth - (iColumn % m_iTabWidth));

                     }
                     else
                     {

                        str = '\t';

                     }

                  }
                  else if (pkey->m_ekey == ::user::key_refer_to_text_member)
                  {
                     str = pkey->m_strText;
//                     if(bShift)
//                     {
//                        str.make_upper();
//                     }
                  }
                  else
                  {

#ifdef WINDOWS_DESKTOP

                     return;

#endif

                     ch = (char)pkey->m_nChar;
                     if (ch == '\r')
                        ch = '\n';
                     i32 iChar = (i32)pkey->m_nChar;
                     if (iChar == '\r')
                        iChar = '\n';
                     if (bShift)
                     {
                        iChar |= 0x80000000;
                     }
                     i32 iCode = pkey->m_nFlags & 0xff;
                     if (bShift)
                     {
                        iCode |= 0x80000000;
                     }
                     //str = Session.keyboard().process_key(pkey);
                     __throw(todo("keyboard"));
                  }

                  insert_text(str, false);

                  bUpdate = false;

                  pkey->m_bRet = true;

               }

#endif

            }

            int iColumnX;

            auto iColumn = plain_edit_sel_to_column_x(pgraphics, m_ptree->m_iSelEnd, iColumnX);

            if ((pkey->m_ekey != ::user::key_up && pkey->m_ekey == ::user::key_down
                  && pkey->m_ekey != ::user::key_prior && pkey->m_ekey != ::user::key_next) &&
                  iColumn != m_iColumn)
            {

               m_iColumn = iColumn;
               m_iColumnX = iColumnX;

            }



         }

      }

      if (bUpdate)
      {

         plain_edit_update(pgraphics, bFullUpdate, iLineUpdate);

      }

   }

   //if()


// HWND hwndIme = ImmGetDefaultIMEWnd(get_handle());
   void plain_edit::get_text_composition_area(::rect & rect)
   {

      strsize iBeg;

      strsize iEnd;

      _001GetSel(iBeg, iEnd);

      i32 x;

      auto pgraphics = ::draw2d::create_memory_graphics();

      auto iLine = plain_edit_sel_to_line_x(pgraphics, iEnd, x);

      index y = (index) ((iLine)* m_iLineHeight - get_viewport_offset().y);
      index y2 = y + m_iLineHeight;
      ::point point((LONG)x,(LONG) y);
      get_client_rect(rect);
      rect.left =(LONG) x;
      rect.top = (LONG)y;
      rect.bottom = (LONG)y2;
      _001ClientToScreen(rect);
      get_wnd()->_001ScreenToClient(rect);

   }


   //int plain_edit::on_draft_message(int iMessage)
   //{

   //   if (iMessage == IME_MESSAGE_UPDATE_CARET)
   //   {
   //      /*
   //               strsize iBeg;
   //               strsize iEnd;

   //               _001GetSel(iBeg, iEnd);

   //               i32 x;
   //               i32 iLine = plain_edit_sel_to_line_x(iEnd, x);




   //               int y = (iLine)* m_iLineHeight - get_viewport_offset().y;
   //               int y2 = y + m_iLineHeight;
   //               const ::point & ::point(x, y);
   //               ::rect r;
   //               get_client_rect(rect);
   //               rect.left = x;
   //               rect.top = y;
   //               rect.bottom = y2;
   //               _001ClientToScreen(rect);
   //               get_wnd()->_001ScreenToClient(rect);
   //      */

   //      //SetCaretPos(rect.left, rect.top);
   //      //ShowCaret(get_handle());
   //   }
   //   else if (iMessage == IME_MESSAGE_UPDATE_CANDIDATE_WINDOW_POSITION)
   //   {

   //      //simple_imm imm(this);

   //      //if (!imm)
   //      //{

   //      //   return 0;

   //      //}


   //      //if()


   //      // HWND hwndIme = ImmGetDefaultIMEWnd(get_handle());

   //      //strsize iBeg;
   //      //strsize iEnd;

   //      //_001GetSel(iBeg, iEnd);

   //      //i32 x;
   //      //i32 iLine = plain_edit_sel_to_line_x(iEnd, x);




   //      //int y = (iLine)* m_iLineHeight - get_viewport_offset().y;
   //      //int y2 = y + m_iLineHeight;
   //      //const ::point & ::point(x, y);
   //      //rect r;
   //      //get_client_rect(rect);
   //      //rect.left = x;
   //      //rect.top = y;
   //      //rect.bottom = y2;
   //      //_001ClientToScreen(rect);
   //      //get_wnd()->_001ScreenToClient(rect);

   //      //POINTS point;

   //      //point.x = point.x;
   //      //point.y = point.y;

   //      //::set_window_pos(hwndIme, HWND_TOP, point.x, point.y, 0, 0, SWP_NOSIZE);
   //      //SendMessage(hwndIme, WM_IME_CONTROL, IMC_SETSTATUSWINDOWPOS,(LPARAM) &point);
   //      //if (::ImmSetStatusWindowPos(imm, point))
   //      //{
   //      //   output_debug_string("set ime status window pos");
   //      //}


   //      //COMPOSITIONFORM com = {};

   //      //com.uStyle = CFS_FORCE_POSITION;
   //      //com.ptCurrentPos = rect.top_left();
   //      //com.ptCurrentPos.y -= 100;
   //      //::rect rect2(rect);
   //      //rect2.offset_y(-100);
   //      //com.uStyle = CFS_RECT;
   //      //com.rcArea = rect2;

   //      //ShowCaret(get_handle());

   //      //::draw2d::font_pointer pfont = _001GetFont(::user::font_plain_edit);
   //      //if (pfont.is_set())
   //      //{

   //      //   LOGFONTW lf = {};
   //      //   if (pfont->GetLogFont(&lf))
   //      //   {

   //      //      if (ImmSetCompositionFontW(imm, &lf))
   //      //      {

   //      //         output_debug_string("set ime composition font (Unicode) pos");

   //      //      }



   //      //   }

   //      //}

   //      //if (::ImmSetCompositionWindow(imm, &com))
   //      //{
   //      //   output_debug_string("set ime composition window pos");
   //      //}
   //      //CANDIDATEFORM can = {};

   //      //can.uStyle = CFS_CANDIDATEPOS;

   //      //can.ptCurrentPos = rect.bottom_left();

   //      //if (::ImmSetCandidateWindow(imm, &can))
   //      //{

   //      //   output_debug_string("set ime candidate window pos");

   //      //}

   //      //return 1;

   //   }

   //   return 0;

   //}


   void plain_edit::edit_on_text(string str)
   {

      ::user::interaction::edit_on_text(str);

   }


   void plain_edit::edit_on_sel(strsize iSelBeg, strsize iSelEnd)
   {

      ::user::interaction::edit_on_sel(iSelBeg, iSelEnd);

   }


   void plain_edit::on_text_composition(string strText)
   {

      if (m_pitemComposing
         && !strText.contains('\r')
         && !strText.contains('\n'))
      {

         m_ptree->m_peditfile->change_insert_item_data(m_pitemComposing.get(), strText);

         index i1 = (index) (m_pitemComposing->m_position + m_pitemComposing->get_extent());

         auto pgraphics = ::draw2d::create_memory_graphics();

         int iLineUpdate = (int) plain_edit_sel_to_line(pgraphics, i1);

         m_ptree->m_iSelEnd = i1;
         m_ptree->m_iSelBeg = m_ptree->m_iSelEnd;
         m_psetsel->m_iSelEnd = m_ptree->m_iSelEnd;
         m_psetsel->m_iSelBeg = m_ptree->m_iSelEnd;

         bool bFullUpdate = false;

         plain_edit_update(pgraphics, bFullUpdate, iLineUpdate);

         if (iLineUpdate < 0)
         {

            iLineUpdate = (int) plain_edit_sel_to_line(pgraphics, m_ptree->m_iSelEnd);

         }

         if (iLineUpdate >= 0)
         {

            _001EnsureVisibleLine(iLineUpdate + 1);

         }

         set_need_redraw();

         post_redraw();

         string strText;

         _001GetText(strText);

         ::output_debug_string("Current Text: " + strText + "\n");

      }
      else
      {

#if defined(LINUX) || defined(MACOS)

         insert_text(strText, false);

#else

         insert_text(strText, true);

         __refer(m_pitemComposing, m_pinsert);

#endif

      }

   }


   void plain_edit::on_text_composition_done()
   {

      __release(m_pitemComposing);

   }


   void plain_edit::_001OnSysChar(::message::message * pmessage)
   {

      sync_lock sl(mutex());

      SCAST_PTR(::message::key, pkey, pmessage);

      if (pkey->m_ekey == ::user::key_delete)
      {

         if (!m_bReadOnly)
         {
            strsize i1 = m_ptree->m_iSelBeg;
            strsize i2 = m_ptree->m_iSelEnd;
            if (i1 != i2)
            {
               ::sort::sort_non_negative(i1, i2);
               m_ptree->m_peditfile->seek(i1, ::file::seek_begin);
               m_ptree->m_peditfile->Delete((memsize)(i2 - i1));

               m_pinsert = nullptr;

               m_ptree->m_iSelEnd = i1;
               m_ptree->m_iSelBeg = m_ptree->m_iSelEnd;
            }
            else if (m_ptree->m_iSelEnd < m_ptree->m_peditfile->get_length())
            {
               char buf[512];
               __memset(buf, 0, sizeof(buf));
               strsize iProperBegin = max(0, m_ptree->m_iSelEnd - 256);
               strsize iCur = m_ptree->m_iSelEnd - iProperBegin;
               m_ptree->m_peditfile->seek(iProperBegin, ::file::seek_begin);
               m_ptree->m_peditfile->read(buf, sizeof(buf));
               const char * psz = ::str::uni_dec(buf, &buf[iCur]);
               strsize iMultiByteUtf8DeleteCount = &buf[iCur] - psz;
               m_ptree->m_peditfile->seek(m_ptree->m_iSelEnd, ::file::seek_begin);
               m_ptree->m_peditfile->Delete((memsize)(iMultiByteUtf8DeleteCount));

               m_pinsert = nullptr;

               IndexRegisterDelete(m_ptree->m_iSelEnd, iMultiByteUtf8DeleteCount);
               m_ptree->m_iSelBeg = m_ptree->m_iSelEnd;
            }
         }
      }
   }


   void plain_edit::_001OnKeyboardFocusTimer(u64 iTimer)
   {
      if (iTimer == 0)
      {

         if (has_focus() && is_window_visible())// && m_tickLastDraw.elapsed() > m_tickCaretPeriod / 8)
         {

            if (is_different(m_bLastCaret, is_caret_on()))
            {

               m_bLastCaret = is_caret_on();

               set_need_redraw();

               post_redraw();

            }

         }

         //if(m_dwFocusStart + m_dwCaretTime < ::get_tick())
         //{
         // auto m_tickFocusStart = ::tick::now();
         //   m_bCaretOn = !m_bCaretOn;
         //   //set_need_redraw();
         //   set_need_redraw();
         //}
      }
   }


   void plain_edit::plain_edit_one_line_up(::draw2d::graphics_pointer& pgraphics)
   {

      ::point pointOffset = get_viewport_offset();

      set_viewport_offset_y(pointOffset.y - m_iLineHeight);

      //      if(m_scrolldata.m_pointScroll.y < 0)
      //       m_scrolldata.m_pointScroll.y = 0;
      i32 iHeight = 0;
      //char flag;
      m_iViewOffset = 0;
      ::count iLineSize;
      ::index i = 0;
      __copy(pointOffset, get_viewport_offset());
      while (pointOffset.y > iHeight && i < m_iaLineLen.get_size())
      {
         iLineSize = m_iaLineLen[i];
         iHeight += m_iLineHeight;
         m_iViewOffset += iLineSize;
         i++;
      }

   }

   void plain_edit::IndexRegisterDelete(strsize iSel, strsize iCount)
   {
      UNREFERENCED_PARAMETER(iSel);
      UNREFERENCED_PARAMETER(iCount);
      //CreateLineIndex();
      //m_peditor->modifyEvent(0);
      /*   char flag;
         m_iViewOffset = 0;
         i32 iLineSize;
         UINT uiRead;
         i32 iPos = 0;
         i32 iLineStart = -1;
         i32 iLineEnd = -1;
         i32 iLineStartRemain = -1;
         i32 iLineEndRemain = -1;
         i32 iLine = 0;
         i32 i = 0;
         while(i < m_iaLineLen.get_size())
         {
         iLineSize = m_iaLineLen[i];
         iLineStart = iLine;
         if(iSel < (iPos + iLineSize))
         {
         iLineStartRemain = iSel - iPos;
         break;
         }
         iPos += iLineSize;
         iLine++;
         i++;
         }
         if(iSel + iCount <= (iPos + iLineSize))
         {
         iLineEnd = iLineStart;
         iLineEndRemain = (iPos + iLineSize) - (iSel + iCount);
         }
         else
         {
         while(i < m_iaLineLen.get_size())
         {
         iLineSize = m_iaLineLen[i];
         iLine++;
         iLineEnd = iLine;
         m_editfileLineIndex.read(&flag, 1);
         if(iSel + iCount <= (iPos + iLineSize))
         {
         iLineEndRemain = (iPos + iLineSize) - (iSel + iCount);
         break;
         }
         iPos += iLineSize;
         }
         }

         if(iLineEnd > iLineStart)
         {
         m_editfileLineIndex.seek(5 * (iLineStart + 1), ::file::seek_begin);
         m_editfileLineIndex.Delete(5 * (iLineEnd - iLineStart));
         }
         m_editfileLineIndex.seek(5 * iLineStart, ::file::seek_begin);
         iLineSize = iLineStartRemain + iLineEndRemain;
         m_editfileLineIndex.write(&iLineSize, 4);
         m_editfileLineIndex.write(&flag, 1);
         */

   }

   void plain_edit::IndexRegisterInsert(strsize iSel, const char * pcszWhat)

   {
      UNREFERENCED_PARAMETER(iSel);
      UNREFERENCED_PARAMETER(pcszWhat);

      //CreateLineIndex();
      //m_peditor->modifyEvent(0);
   }


   void plain_edit::plain_edit_on_update(::draw2d::graphics_pointer & pgraphics, const ::action_context & context)
   {

      //printf("xxxxxxxxxx1\n");

      {

         sync_lock sl(mutex());

         //string str;
         //_001GetText(str);

         auto iLen = _001GetTextLength();

         if (m_ptree->m_iSelBeg > iLen)
            m_ptree->m_iSelBeg = (strsize) (iLen);
         else if (m_ptree->m_iSelBeg < 0)
            m_ptree->m_iSelBeg = 0;

         if (m_ptree->m_iSelEnd > iLen)
            m_ptree->m_iSelEnd = (strsize) (iLen);
         else if (m_ptree->m_iSelEnd < 0)
            m_ptree->m_iSelEnd = 0;

         m_bGetTextNeedUpdate = 1;

         plain_edit_create_line_index(pgraphics);

         m_y = -1;

         m_bCalcLayoutHintNoTextChange = false;

         plain_edit_on_calc_layout(pgraphics);

      }

      //printf("xxxxxxxxxx2\n");

      try
      {

         plain_edit_on_set_text(pgraphics, context);

      }
      catch (...)
      {

      }

      //printf("xxxxxxxxxx3\n");

      try
      {

         plain_edit_on_after_change_text(pgraphics, context);

      }
      catch (...)
      {

      }

      //printf("xxxxxxxxxx4\n");

      set_need_redraw();

      //printf("xxxxxxxxxx4.1\n");

      post_redraw();

      //printf("xxxxxxxxxx5\n");

   }


   void plain_edit::plain_edit_on_line_update(::draw2d::graphics_pointer& pgraphics, index iLine, const ::action_context & context)
   {

      {

         sync_lock sl(mutex());

         //string str;
         //_001GetText(str);

         auto iLen = _001GetTextLength();

         if (m_ptree->m_iSelBeg > iLen)
            m_ptree->m_iSelBeg = (strsize) (iLen);
         else if (m_ptree->m_iSelBeg < 0)
            m_ptree->m_iSelBeg = 0;

         if (m_ptree->m_iSelEnd > iLen)
            m_ptree->m_iSelEnd = (strsize) (iLen);
         else if (m_ptree->m_iSelEnd < 0)
            m_ptree->m_iSelEnd = 0;

         m_bGetTextNeedUpdate = 1;
         plain_edit_update_line_index(pgraphics, iLine);
         m_y = -1;

         m_bCalcLayoutHintNoTextChange = false;

         plain_edit_on_calc_layout(pgraphics, iLine);

         //m_peditor->lineCountEvent(m_plines->lines.get_count());

      }

      try
      {

         plain_edit_on_set_text(pgraphics, context);

      }
      catch (...)
      {

      }


      try
      {

         plain_edit_on_after_change_text(pgraphics, context);

      }
      catch (...)
      {

      }

      set_need_redraw();

   }


   void plain_edit::MacroBegin()
   {
      __pointer(::user::plain_text_group_command) pgroupcommand = __new(plain_text_group_command);
      pgroupcommand->m_pparent = m_ptree->m_pgroupcommand;
      m_ptree->m_pgroupcommand = pgroupcommand;
   }

   void plain_edit::MacroEnd()
   {
      sync_lock sl(mutex());
      if (m_ptree->m_pgroupcommand == nullptr)
      {
         ASSERT(FALSE);
         return;
      }
      if (m_ptree->m_pgroupcommand->m_pparent == nullptr)
      {
         MacroRecord(m_ptree->m_pgroupcommand);
      }
      m_ptree->m_pgroupcommand = m_ptree->m_pgroupcommand->m_pparent;
   }


   void plain_edit::MacroRecord(__pointer(plain_text_command) pcommand)
   {
      sync_lock sl(mutex());
      if (m_ptree->m_pgroupcommand != nullptr && m_ptree->m_pgroupcommand != pcommand)
      {
         m_ptree->m_pgroupcommand->m_commanda.add(pcommand);
         return;
      }

      m_ptreeitem = m_ptree->insert_item(pcommand, ::data::RelativeMacroRecord, m_ptreeitem);

   }


   bool plain_edit::plain_edit_undo()
   {

      {

         sync_lock sl(mutex());

         {
            if (!CanUndo())
               return false;

            __pointer(plain_text_command) pcommand = m_ptreeitem->m_pdataitem;


            pcommand->Undo(m_ptree);

         }

         m_ptreeitem = m_ptreeitem->get_previous_or_parent();

      }

      return true;

   }


   bool plain_edit::edit_undo()
   {

      plain_edit_undo();

      auto pgraphics = ::draw2d::create_memory_graphics();

      plain_edit_create_line_index(pgraphics);

      m_bGetTextNeedUpdate = true;

      plain_edit_on_update(pgraphics, ::source_user);

      //plain_edit_on_after_change_text(pgraphics, ::source_user);

      return true;

   }


   bool plain_edit::edit_redo()
   {

      ::draw2d::graphics_pointer pgraphics;

      {

         sync_lock sl(mutex());

         if (m_ptreeitem == nullptr)
         {

            return false;

         }

         if (m_ptree->m_iBranch < 0
               || m_ptree->m_iBranch >= GetRedoBranchCount())
         {
            return false;
         }

         __pointer(::data::tree_item) ptreeitem;

         if (m_ptree->m_iBranch < m_ptreeitem->get_expandable_children_count())
         {

            ptreeitem = m_ptreeitem->get_expandable_child(m_ptree->m_iBranch);

         }
         else
         {

            ptreeitem = m_ptreeitem->get_child_next_or_parent();

         }

         if (ptreeitem.is_null())
         {

            return false;

         }

         m_ptreeitem = ptreeitem;

         __pointer(plain_text_command) pcommand = ptreeitem->m_pdataitem;

         pcommand->Redo(m_ptree);

      }

      plain_edit_create_line_index(pgraphics);

      m_bGetTextNeedUpdate = true;

      plain_edit_on_update(pgraphics, ::source_user);
      //plain_edit_on_after_change_text(pgraphics, ::source_user);

      return true;
   }

   bool plain_edit::CanUndo()
   {
      sync_lock sl(mutex());
      return m_ptreeitem != m_ptree->get_base_item();
   }

   bool plain_edit::CanRedo()
   {
      sync_lock sl(mutex());
      return m_ptree->m_iBranch < m_ptreeitem->get_expandable_children_count()
             || m_ptreeitem->get_next() != nullptr;
   }

   ::count plain_edit::GetRedoBranchCount()
   {
      sync_lock sl(mutex());

      return m_ptreeitem->get_expandable_children_count()
             + (m_ptreeitem->get_next() != nullptr ? 1 : 0)
             + (m_ptreeitem->first_child() != nullptr ? 1 : 0);
   }



   void plain_edit::_001SetText(const string & strParam, const ::action_context & context)
   {

      string str(strParam);

      ::draw2d::graphics_pointer pgraphics;

      {

         sync_lock sl(mutex());




         if (m_bParseDataPacks)
         {

            m_base64map.remove_all();

            _001AddPacks(m_base64map, str);

         }

         if (!m_ptree)
         {

            return;

         }

         if(m_ptree->m_peditfile->get_length() > 0)
         {

            m_ptree->m_peditfile->seek(0, ::file::seek_begin);

            m_ptree->m_peditfile->Delete((memsize)m_ptree->m_peditfile->get_length());

         }

         if(str.has_char())
         {

            m_ptree->m_peditfile->seek(0, ::file::seek_begin);

            m_ptree->m_peditfile->Insert(str, str.get_length());

         }

      }

      plain_edit_on_set_text(pgraphics, context);

      plain_edit_on_update(pgraphics, context);

   }


   void plain_edit::keyboard_focus_OnKeyDown(::message::message * pmessage)
   {

      _001OnKeyDown(pmessage);

   }


   void plain_edit::keyboard_focus_OnKeyUp(::message::message * pmessage)
   {

      _001OnKeyUp(pmessage);

   }


   void plain_edit::keyboard_focus_OnChar(::message::message * pmessage)
   {

      _001OnChar(pmessage);

   }


   void plain_edit::plain_edit_on_after_change_text(::draw2d::graphics_pointer& pgraphics, const ::action_context & context)
   {

      if(context.is_user_source())
      {

         if(::is_set(m_ppropertyText))
         {

            plain_edit_get_text(strtext());

            get_context_application()->apply_update(m_ppropertyText->m_id, context);

         }

      }

      ::user::control_event ev;

      ev.m_puie = this;

      ev.m_id = m_id;

      ev.m_eevent = ::user::event_after_change_text;

      ev.m_actioncontext = context;

      route_control_event(&ev);

   }


   void plain_edit::clipboard_copy()
   {

      if (m_bPassword)
         return;
      string str;
      _001GetSelText(str);
      str.replace("\r", "\r\n");
      Session.copydesk().set_plain_text(str);
   }

   bool plain_edit::get_line_color(COLORREF & cr, const string & strLine)
   {

      return false;

   }


   void plain_edit::clipboard_paste()
   {

      string str;

      if(!Session.copydesk().get_plain_text(str))
      {

         return;

      }

      insert_text(str, true);

      if(m_bEnterKeyOnPaste)
      {

         ::user::control_event ev;

         ev.m_puie = this;

         ev.m_eevent = ::user::event_enter_key;

         ev.m_actioncontext = ::source_paste;

         on_control_event(&ev);

         if(!ev.m_bRet && ev.m_bOk)
         {

            on_action("submit");

         }

      }


   }


   void plain_edit::_001OnVScroll(::message::message * pmessage)
   {

   }


   i32 plain_edit::get_wheel_scroll_delta()
   {

      return m_iLineHeight * 3;

   }


   void plain_edit::_001OnHScroll(::message::message * pmessage)
   {

      UNREFERENCED_PARAMETER(pmessage);

   }


   void plain_edit::plain_edit_on_set_text(::draw2d::graphics_pointer& pgraphics, const ::action_context & context)
   {

      m_bCalcLayoutHintNoTextChange = false;

      plain_edit_on_calc_layout(pgraphics);

   }


   bool plain_edit::should_load_full_file()
   {
      return m_bColorerTake5;
   }

   //colorertake5::file_type *plain_edit::colorer_select_type()
   //{

   //   if (!m_bColorerTake5)
   //   {

   //      return nullptr;

   //   }

   //   sync_lock sl(mutex());
   //   colorertake5::file_type *type = nullptr;
   //   /*if (typeDescription != nullptr){
   //     type = hrcParser->getFileType(typeDescription);
   //     if (type == nullptr){
   //     for(i32 idx = 0;; idx++){
   //     type = hrcParser->enumerateFileTypes(idx);
   //     if (type == nullptr) break;
   //     if (type->getDescription() != nullptr &&
   //     type->getDescription()->length() >= typeDescription->length() &&
   //     DString(type->getDescription(), 0, typeDescription->length()).equalsIgnoreCase(typeDescription))
   //     break;
   //     if (type->getName()->length() >= typeDescription->length() &&
   //     DString(type->getName(), 0, typeDescription->length()).equalsIgnoreCase(typeDescription))
   //     break;
   //     type = nullptr;
   //     }
   //     }
   //     }*/
   //   //  if (typeDescription == nullptr || type == nullptr){
   //   //__pointer(::user::impact) pview = (this);
   //   //if (pview != nullptr)
   //   //{
   //   //   __pointer(::user::document) pdocument = pview->get_document();
   //   //   if (type == nullptr)
   //   //   {
   //   //      //string textStart;
   //   //      //strsize totalLength = 0;
   //   //      //for (i32 i = 0; i < 4 && i < m_plines->getLineCount(); i++)
   //   //      //{
   //   //      //   string iLine = m_plines->getLine(i);
   //   //      //   textStart += iLine;
   //   //      //   textStart += "\n";
   //   //      //   totalLength += iLine.get_length();
   //   //      //   if (totalLength > 500) break;
   //   //      //}
   //   //      //type = System.parser_factory().getHRCParser()->chooseFileType(pdocument->get_file_path(), textStart, 0);
   //   //   }
   //   //}

   //   //if (type != nullptr)
   //   //{

   //   //   type->getBaseScheme();

   //   //   colorertake5()->setFileType(type);

   //   //}

   //   return ptype;

   //}


   void plain_edit::_009OnChar(::message::message * pmessage)
   {
      UNREFERENCED_PARAMETER(pmessage);
   }


   bool plain_edit::create_control(class control_descriptor * pdescriptor)
   {

      ASSERT(pdescriptor->get_control_type() == control_type_edit_plain_text);

      if (!::user::interaction::create_control(pdescriptor))
      {

         TRACE("Failed to create control");

         return false;

      }

      display(display_none);

      m_bMultiLine = pdescriptor->has_function(control_function_edit_multi_line);

      return true;

   }


   bool plain_edit::keyboard_focus_is_focusable()
   {

      return is_window_visible();

   }


   void plain_edit::_001OnSetFocus(::message::message * pmessage)
   {

      m_bFocus = true;

      if (Session.m_puiHost)
      {

         auto puiHost = __user_interaction(Session.m_puiHost);

         if (puiHost)
         {

            puiHost->edit_on_set_focus(this);

         }

      }

      //::image_pointer pimage;

      SetTimer(100, 50, nullptr);

      //pimage = create_image({1,  24});

      //::draw2d::brush_pointer br(e_create);

      //br->create_solid(ARGB(255, 255, 0, 0));

      //pimage->g()->set(br);

      //pimage->g()->FillEllipse(pimage->rect());

      if (!m_bCaretVisible)
      {

         m_bCaretVisible = true;

#ifdef WINDOWS_DESKTOP

         HWND hwnd = get_handle();

         ::CreateCaret(hwnd, 0, 1, m_iLineHeight);

         ::point pointCaret = layout().design().origin();

         _001ClientToScreen(pointCaret);

         ::ScreenToClient(hwnd, pointCaret);

         ::SetCaretPos(pointCaret.x, pointCaret.y);

         ::ShowCaret(hwnd);

#endif

      }

      //EnableIME();

      on_text_composition_message(TEXT_COMPOSITION_MESSAGE_UPDATE_CARET);

      string strText;

      _001GetText(strText);

      strsize iBeg;

      strsize iEnd;

      _001GetSel(iBeg, iEnd);

      Session.keyboard().defer_show_software_keyboard(this, true, strText, iBeg, iEnd);

   }


   void plain_edit::_001OnKillFocus(::message::message * pmessage)
   {

      if (Session.m_puiHost)
      {

         auto puiHost = __user_interaction(Session.m_puiHost);

         puiHost->edit_on_kill_focus(this);

      }

      KillTimer(100);

      if (m_bCaretVisible)
      {

         m_bCaretVisible = false;

#ifdef WINDOWS_DESKTOP

         ::DestroyCaret();

#endif

      }


      string strText;

      _001GetText(strText);

      strsize iBeg;

      strsize iEnd;

      _001GetSel(iBeg, iEnd);

      auto pinteraction = get_wnd();

      if (::is_set(pinteraction))
      {

         Session.keyboard().defer_show_software_keyboard(this, false, strText, iBeg, iEnd);

      }

      //DestroyImeWindow();

      m_bFocus = false;

   }


   __pointer(::data::item) plain_edit::on_allocate_item()
   {
      return __new(plain_text_command);
   }


   void plain_edit::set_root(plain_text_tree * pdata, bool bOwnData)
   {

      sync_lock lockRoot(mutex());

      if (m_ptree != nullptr && m_bOwnData)
      {

         __release(m_ptree);

      }

      __compose(m_ptree, pdata);

      m_ptreeitem = m_ptree->get_base_item();

      m_bOwnData = m_ptree != nullptr && bOwnData;

      if (m_ptree != nullptr)
      {

         listen(m_ptree);

      }

   }


   void plain_edit::_001OnUpdateEditCut(::message::message * pmessage)
   {

      SCAST_PTR(::user::command, pcommand, pmessage);

      string str;

      _001GetSelText(str);

      pcommand->enable(str.has_char());

   }


   void plain_edit::_001OnEditCut(::message::message * pmessage)
   {

      UNREFERENCED_PARAMETER(pmessage);

      clipboard_copy();

      ::draw2d::graphics_pointer pgraphics;

      if (is_window_enabled())
      {

         plain_edit_on_delete(pgraphics);

      }

      pmessage->m_bRet = true;

   }


   void plain_edit::_001OnUpdateEditCopy(::message::message * pmessage)
   {

      SCAST_PTR(::user::command, pcommand, pmessage);

      string str;

      _001GetSelText(str);

      pcommand->enable(str.has_char());

   }


   void plain_edit::_001OnEditCopy(::message::message * pmessage)
   {

      UNREFERENCED_PARAMETER(pmessage);

      clipboard_copy();

      pmessage->m_bRet = true;

   }

   void plain_edit::_001OnUpdateEditPaste(::message::message * pmessage)
   {

      SCAST_PTR(::user::command, pcommand, pmessage);

      pcommand->enable(Session.copydesk().has_plain_text());

   }


   void plain_edit::_001OnEditPaste(::message::message * pmessage)
   {

      UNREFERENCED_PARAMETER(pmessage);

      if (is_window_enabled())
      {

         clipboard_paste();

      }

      pmessage->m_bRet = true;

   }


   void plain_edit::_001OnUpdateEditDelete(::message::message * pmessage)
   {

      SCAST_PTR(::user::command, pcommand, pmessage);

      string str;

      _001GetSelText(str);

      pcommand->enable(str.has_char());

   }


   void plain_edit::_001OnEditDelete(::message::message * pmessage)
   {

      UNREFERENCED_PARAMETER(pmessage);

      ::draw2d::graphics_pointer pgraphics;

      if (is_window_enabled())
      {

         plain_edit_on_delete(pgraphics);

      }

      pmessage->m_bRet = true;

   }



   void plain_edit::_001OnSize(::message::message * pmessage)
   {

      UNREFERENCED_PARAMETER(pmessage);

   }


   void plain_edit::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

#ifdef WINDOWS_DESKTOP

      //get_wnd()->m_pimpl2->m_puserthread->m_peditwnd->m_AdviseSink.pTextStoreACPSink->OnLayoutChange(TS_LC_CHANGE, EDIT_VIEW_COOKIE);

#endif

      //m_bCalcLayoutHintNoTextChange = true;

      plain_edit_on_calc_layout(pgraphics);

   }


   //bool plain_edit::display(edisplay edisplay)
   //{

   //   if (nCmdShow != display_none)
   //   {

   //      TRACE("Going to Show plain_edit");

   //   }

   //   return ::user::interaction::display(nCmdShow);

   //}


   //bool plain_edit::has_action_hover()
   //{

   //   return  m_bActionHover;

   //}


   bool plain_edit::has_text_input()
   {

      return is_window_enabled();

   }


   sized plain_edit::get_total_size()
   {

      return m_sizeTotal;

   }


   var plain_edit::get_ex_value()
   {

      string str;

      _001GetText(str);

      return str;

   }


   string plain_edit::plain_edit_get_expanded_line(::draw2d::graphics_pointer& pgraphics, index iLine, array < strsize * > intptra)
   {

      string strLine = plain_edit_get_line(pgraphics, iLine);

      ::str::replace_tab(0, strLine, m_iTabWidth, intptra);

      return strLine;

   }


   string plain_edit::plain_edit_get_line(::draw2d::graphics_pointer& pgraphics, index iLine)
   {

      sync_lock sl(mutex());

      string strLine;

      if (iLine >= m_iLineStart && iLine < m_iLineEnd)
      {

//         strLine = m_plines->lines[iLine - m_iLineStart];
         strLine = m_straLines[iLine - m_iLineStart];

      }
      else
      {

         strsize iLineLen = m_iaLineLen[iLine] - (m_iaLineEnd[iLine] & 0xf);

         char *psz = strLine.get_string_buffer(iLineLen);

         m_ptree->m_peditfile->seek(m_iaLineBeg[iLine], ::file::seek_begin);

         m_ptree->m_peditfile->read(psz, iLineLen);

         strLine.release_string_buffer(iLineLen);

      }

      return strLine;

   }


   void plain_edit::on_before_change_text()
   {

      //if (m_strImeComposition.has_char())
      //{

      //   m_strImeComposition.Empty();

      //   edit_undo();

      //}

   }


   void plain_edit::insert_text(string strText, bool bForceNewStep)
   {

      auto pgraphics = ::draw2d::create_memory_graphics();

      return plain_edit_insert_text(pgraphics, strText, bForceNewStep);

   }


   void plain_edit::plain_edit_insert_text(::draw2d::graphics_pointer & pgraphics, string strText, bool bForceNewStep)
   {

      ::output_debug_string("plain_edit::insert_text: \"" + strText.Left(64) + "\" \n");

      sync_lock sl(mutex());

      on_before_change_text();

      _001AddPacks(m_base64map, strText);

      bool bFullUpdate = false;

      index iLineUpdate = -1;

      strsize i1 = m_ptree->m_iSelBeg;

      strsize i2 = m_ptree->m_iSelEnd;

      bFullUpdate = strText.find('\n') >= 0 || strText.find('\r') >= 0;

      if (!bForceNewStep && !bFullUpdate && i1 == i2 && i1 >= 0 && m_pinsert != nullptr
            && m_pinsert->m_position + m_pinsert->m_memstorage.get_size() == i1
            && m_ptree->m_peditfile->m_ptreeitem != m_ptree->m_peditfile->m_ptreeitemFlush)
      {

         // insert character at the last insert operation
         m_pinsert->m_memstorage.append(strText, strText.get_length());

         m_ptree->m_peditfile->m_size += strText.get_length();

         if (!bFullUpdate)
         {

            iLineUpdate = plain_edit_sel_to_line(pgraphics, i1);

         }
         m_ptree->m_iSelEnd += strText.get_length();
         m_ptree->m_iSelBeg = m_ptree->m_iSelEnd;
         m_psetsel->m_iSelEnd = m_ptree->m_iSelEnd;
         m_psetsel->m_iSelBeg = m_ptree->m_iSelEnd;

      }
      else
      {

         auto psetsel  = __new(plain_text_set_sel_command);

         psetsel->m_iPreviousSelBeg = m_ptree->m_iSelBeg;

         psetsel->m_iPreviousSelEnd = m_ptree->m_iSelEnd;

         ::sort::sort_non_negative(i1, i2);

         m_ptree->m_peditfile->MacroBegin();

         if (!bFullUpdate)
         {

            string strSel;

            _001GetSelText(strSel);

            bFullUpdate = strSel.find('\n') >= 0 || strSel.find('\r') >= 0;

         }

         if (!bFullUpdate)
         {

            iLineUpdate = plain_edit_sel_to_line(pgraphics, i1);

         }

         if (i1 != i2)
         {

            m_ptree->m_peditfile->seek(i1, ::file::seek_begin);

            m_ptree->m_peditfile->Delete((memsize)(i2 - i1));

            m_pinsert = nullptr;

            IndexRegisterDelete(i1, i2 - i1);

         }

         m_ptree->m_iSelEnd = i1;

         m_ptree->m_peditfile->seek(m_ptree->m_iSelEnd, ::file::seek_begin);
         m_ptree->m_iSelEnd += strText.get_length();
         m_ptree->m_iSelBeg = m_ptree->m_iSelEnd;
         //m_ptree->m_peditfile->seek(m_ptree->m_iSelBeg, ::file::seek_begin);

         auto iLength = strText.get_length();

         m_pinsert = m_ptree->m_peditfile->Insert(strText, iLength);

         IndexRegisterInsert(m_ptree->m_iSelEnd, strText);

         m_ptree->m_peditfile->MacroEnd();

         psetsel->m_iSelBeg = m_ptree->m_iSelBeg;

         psetsel->m_iSelEnd = m_ptree->m_iSelEnd;

         m_psetsel = psetsel;

         MacroBegin();
         MacroRecord(psetsel);
         MacroRecord(__new(plain_text_file_command()));
         MacroEnd();

      }

      plain_edit_update(pgraphics, bFullUpdate, iLineUpdate);

      if (iLineUpdate < 0)
      {

         iLineUpdate = plain_edit_sel_to_line(pgraphics, m_ptree->m_iSelEnd);

      }

      if(m_bMultiLine)
      {

         if (iLineUpdate >= 0)
         {

            _001EnsureVisibleLine(iLineUpdate + 1);

         }
         else
         {

            _001EnsureVisibleLine(0);

         }

      }
      else
      {

         _001EnsureVisibleLine(0);

      }

   }


   void plain_edit::plain_edit_update(::draw2d::graphics_pointer& pgraphics, bool bFullUpdate, index iLineUpdate)
   {

      if (!m_bMultiLine)
      {

         if (bFullUpdate || iLineUpdate >= 0)
         {

            plain_edit_on_update(pgraphics, ::source_user);

         }

      }
      else if (bFullUpdate)
      {

         plain_edit_on_update(pgraphics, ::source_user);

      }
      else if (iLineUpdate >= 0)
      {

         plain_edit_on_line_update(pgraphics, iLineUpdate, ::source_user);

      }

   }


   plain_edit_internal::plain_edit_internal()
   {


   }


   plain_edit_internal::~plain_edit_internal()
   {


   }


   void plain_edit_internal::update(::draw2d::graphics_pointer& pgraphics, plain_edit * pedit)
   {

      m_penCaret.release();

      m_brushText.release();

      m_brushTextCr.release();

      m_brushTextSel.release();

      m_brushTextEmpty.release();

      __construct(m_penCaret);

      __construct(m_brushText);

      __construct(m_brushTextCr);

      __construct(m_brushTextSel);

      __construct(m_brushTextEmpty);

      auto pstyle = pedit->get_style(pgraphics);

      auto color = pedit->get_color(pstyle, element_text);

      m_penCaret->create_solid(1.0, color);

      m_brushTextCr->create_solid(color);

      color = pedit->get_color(pstyle, element_text, e_state_selected);

      m_brushTextSel->create_solid(color);

      color = pedit->get_color(pstyle, element_text, e_state_new_input);

      m_brushTextEmpty->create_solid(color);

   }


   void plain_edit::_001OnNcDraw(::draw2d::graphics_pointer & pgraphics)
   {

      ::user::interaction::_001OnNcDraw(pgraphics);

   }



   void plain_edit::on_updata_data(::data::simple_data * pdata, i32 iHint)
   {

      //if (pdata == m_ptree)
      {

         if (iHint == id_set_file)
         {

            auto pgraphics = ::draw2d::create_memory_graphics();

            plain_edit_on_file_update(pgraphics);

         }

      }

   }


} // namespace aura








//#ifdef WINDOWS_DESKTOP


//simple_imm & simple_frame_window::imm()
//{
//
//   if (m_psimpleimm.is_null())
//   {
//
//      m_psimpleimm = __new(simple_imm(this));
//
//   }
//
//   return m_psimpleimm;
//
//}


//simple_imm::simple_imm(::user::interaction * pinteraction)
//{
//
//
//
//}
//
//
//simple_imm::simple_imm(HWND hwnd)
//{
//
//   m_hwnd = hwnd;
//   m_himc = ImmGetContext(m_hwnd);
//
//}
//
//#endif
//
//simple_imm::~simple_imm()
//{
//#ifdef WINDOWS_DESKTOP
//   ImmReleaseContext(m_hwnd, m_himc);
//#endif
//
//}
//
//#ifdef WINDOWS_DESKTOP
//
//#endif // WINDOWS

