#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "aura/user/user/_component.h"
#endif
#include "aura/operating_system.h"
#include "_data.h"
//#include "aura/update.h"
#include "aura/message.h"
//#include "aura/user/interaction_thread.h"
#ifdef WINDOWS_DESKTOP
#ifdef ENABLE_TEXT_SERVICES_FRAMEWORK
#include "aura/user/windows_tsf/edit_window.h"
#endif
#endif
#include "acme/constant/timer.h"
#include "acme/primitive/string/base64.h"
#include "aura/graphics/draw2d/_component.h"
#include "acme/platform/timer.h"
#include "aura/windowing/text_editor_interface.h"
#include "aura/windowing/windowing.h"
#include "aura/windowing/window.h"
//#include "_tree.h"

//extern CLASS_DECL_AURA thread_int_ptr < DWORD_PTR > t_time1;


namespace aura
{


   void system::_001AddPacks(string_to_string & base64map, string & str)
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

         strsize iEncoding = minimum_non_negative(iEncoding1, iEncoding2);

         if (iEncoding <= iMime)
         {

            continue;

         }

         string strEncoding = str.Mid(iMime + 1, iEncoding - iMime - 1);

         if (strEncoding.compare_ci("base64") == 0)
         {

            auto psystem = m_psystem;

            auto pbase64 = psystem->base64();

            index iBase64 = iEncoding + 1;

            for (; iBase64 < str.get_length(); iBase64++)
            {

               if (!pbase64->is(str[iBase64]))
               {

                  break;

               }

            }

            string strBase64 = str.Mid(iEncoding + 1, iBase64 - iEncoding - 1);

            string strPack = "%pack" + __string(iPack + 1) + "%";

            str = str.Left(iEncoding + 1) + strPack + str.Mid(iBase64);

            base64map[strPack] = strBase64;

            iPack++;

         }


      }

   }


} // namespace aura


namespace user
{

   //class plain_edit_internal :
   //   virut
   //{
   //public:

   //   ::draw2d::pen_pointer              m_ppenCaret;
   //   ::draw2d::brush_pointer            m_pbrushText;
   //   ::draw2d::brush_pointer            m_pbrushTextCr;
   //   ::draw2d::brush_pointer            m_pbrushTextSel;
   //   ::draw2d::brush_pointer            m_pbrushTextEmpty;

   //   plain_edit_internal();
   //   ~plain_edit_internal();

   //   void update(::draw2d::graphics_pointer& pgraphics, plain_edit * pedit);

   //};



   plain_edit::plain_edit()
   {

      plain_edit_common_construct();

   }


   //plain_edit::plain_edit(::object * pobject) :
   //   ::object(pobject),
   //   ::user::interaction(pobject),
   //   m_pmemorygraphics(e_create)
   //{

   //   plain_edit_common_construct();

   //}


   plain_edit::~plain_edit()
   {

   }


   void plain_edit::set_format(const string & strFormat)
   {

   }


   void plain_edit::set_callback(callback * pcallback)
   {


   }


   void plain_edit::plain_edit_common_construct()
   {

      m_econtroltype = e_control_type_edit;

      m_bCaretVisible = false;

      m_iInputConnectionBatch = 0;

      m_bEnterKeyOnPaste = false;

      //m_pcontrolstyle = new plain_edit_internal();

      m_ppropertysetsel = nullptr;

      m_pinsert = nullptr;

      m_bColorerTake5 = false;

      m_straLines.set_size(10, 100);

      m_daExtent.set_size(10, 100);

      m_iTabWidth = 3;

      m_bTabInsertSpaces = false;

      m_dLineHeight = 0.;

      m_bPassword = false;

      m_bOwnData = false;

      m_bMultiLine = false;

      m_bReadOnly = false;

      m_bSendEnterKey = false;

      //m_bActionHover = false;

      m_bCalcLayoutHintNoTextChange = false;

      m_scrolldataHorizontal.m_bScrollEnable = false;

      m_scrolldataVertical.m_bScrollEnable = false;

      m_dy = -1;
      m_iImpactOffset = 0;
      m_iImpactSize = 0;
      m_bLMouseDown = false;
      m_bRMouseDown = false;
      m_durationCaretPeriod = 1_s;

      m_iLastSelectionBeginLine = -1;
      m_iLastSelectionBeginX = -1;
      m_iLastSelectionEndLine = -1;
      m_iLastSelectionEndX = -1;
      m_iColumnX = -1;

   }


   void plain_edit::install_message_routing(::channel * pchannel)
   {

      interaction::install_message_routing(pchannel);
      scroll_base::install_message_routing(pchannel);
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
      MESSAGE_LINK(e_message_create, pchannel, this, &plain_edit::on_message_create);
      MESSAGE_LINK(e_message_left_button_down, pchannel, this, &plain_edit::on_message_left_button_down);
      MESSAGE_LINK(e_message_left_button_up, pchannel, this, &plain_edit::on_message_left_button_up);
      MESSAGE_LINK(e_message_left_button_double_click, pchannel, this, &plain_edit::on_message_left_button_double_click);
      MESSAGE_LINK(e_message_right_button_down, pchannel, this, &plain_edit::on_message_right_button_down);
      MESSAGE_LINK(e_message_right_button_up, pchannel, this, &plain_edit::on_message_right_button_up);
      MESSAGE_LINK(e_message_mouse_move, pchannel, this, &plain_edit::on_message_mouse_move);
      MESSAGE_LINK(e_message_mouse_leave, pchannel, this, &plain_edit::on_message_mouse_leave);
      MESSAGE_LINK(e_message_key_down, pchannel, this, &plain_edit::on_message_key_down);
      MESSAGE_LINK(e_message_key_up, pchannel, this, &plain_edit::on_message_key_up);
      MESSAGE_LINK(e_message_uni_char, pchannel, this, &plain_edit::_001OnUniChar);
      MESSAGE_LINK(e_message_char, pchannel, this, &plain_edit::on_message_char);

      MESSAGE_LINK(e_message_size, pchannel, this, &::user::plain_edit::on_message_size);

      //MESSAGE_LINK(e_message_set_focus, pchannel, this, &::user::plain_edit::on_message_set_focus);
      //MESSAGE_LINK(e_message_kill_focus, pchannel, this, &::user::plain_edit::on_message_kill_focus);


      MESSAGE_LINK(e_message_vscroll, pchannel, this, &::user::plain_edit::_001OnVScroll);
      MESSAGE_LINK(e_message_hscroll, pchannel, this, &::user::plain_edit::_001OnHScroll);



      add_command_prober("edit_cut", this, &plain_edit::_001OnUpdateEditCut);
      add_command_handler("edit_cut", this, &plain_edit::_001OnEditCut);
      add_command_prober("edit_copy", this, &plain_edit::_001OnUpdateEditCopy);
      add_command_handler("edit_copy", this, &plain_edit::_001OnEditCopy);
      add_command_prober("edit_paste", this, &plain_edit::_001OnUpdateEditPaste);
      add_command_handler("edit_paste", this, &plain_edit::_001OnEditPaste);
      add_command_prober("edit_delete", (interaction *)this, &interaction::_001OnUpdateEditDelete);
      add_command_handler("edit_delete", (interaction *)this, &interaction::_001OnEditDelete);


#ifdef ENABLE_TEXT_SERVICES_FRAMEWORK

      install_edit_window_message_routing(pchannel);

#elif defined(WINDOWS_DESKTOP)

      // install_text_composition_composite_message_routing(pchannel);

#endif

   }


   void plain_edit::OnDraw(::image * pimage)
   {

      __UNREFERENCED_PARAMETER(pimage);

   }


   void plain_edit::handle(::topic * ptopic, ::context * pcontext)
   {

      if (ptopic->m_atom == id_current_text_changed)
      {

         queue_graphics_call([this](::draw2d::graphics_pointer & pgraphics)
            {

               plain_edit_on_update(pgraphics, ::e_source_sync);

               m_bCalcLayoutHintNoTextChange = false;

               plain_edit_on_calc_layout(pgraphics);

            });

      }
      else
      {

         ::user::interaction::handle(ptopic, pcontext);

      }

   }


   void plain_edit::on_message_destroy(::message::message * pmessage)
   {


   }


   void plain_edit::VirtualOnSize(::draw2d::graphics_pointer & pgraphics)
   {

      plain_edit_on_update(pgraphics, ::e_source_system);

      m_bCalcLayoutHintNoTextChange = true;

      plain_edit_on_calc_layout(pgraphics);

   }


   void plain_edit::_001OnPaint(::message::message * pmessage)
   {

   }


   void plain_edit::on_context_offset(::draw2d::graphics_pointer & pgraphics)
   {

      ::user::interaction::on_context_offset(pgraphics);

   }


   bool plain_edit::validate_context_offset(::point_i32 & point)
   {

      if (!::user::scroll_base::validate_context_offset(point))
      {

         return false;

      }

      if (!m_bMultiLine)
      {

         point.y = 0;

      }

      return true;

   }


   void plain_edit::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      m_durationLastDraw = ::duration::now();

      ::duration t1 = ::duration::now();

      auto pstyle = get_style(pgraphics);

      status < ::color::color > crBk;
      status < ::color::color > crBkSel;
      status < ::color::color > crSel;
      status < ::color::color > color32;

      ::rectangle_f64 rectangleClient = get_client_rect();

      auto rectangleBackground = rectangleClient;

      rectangleBackground.offset(m_pointScroll);

      auto crEditBackground = get_color(pstyle, e_element_background);

      pgraphics->fill_rectangle(rectangleBackground, crEditBackground);

      bool bComposing = ::is_set(m_pitemComposing);

      strsize iComposeBeg = -1;

      strsize iComposeEnd = -1;

      if (bComposing)
      {

         iComposeBeg = (strsize)m_pitemComposing->m_position;

         iComposeEnd = (strsize)(m_pitemComposing->m_position + m_pitemComposing->get_extent());

      }

      color32 = get_color(pstyle, e_element_text);
      crBk = get_color(pstyle, e_element_background);
      crSel = get_color(pstyle, e_element_text, e_state_selected);
      crBkSel = get_color(pstyle, e_element_background, e_state_selected);

      status < ::color::color > colorComposeBk;

      colorComposeBk = crBk;
      colorComposeBk.blend(crBkSel, 0.5);
      colorComposeBk.alpha = 127;

      pstyle->get(m_pcontrolstyle, pgraphics, this);

      bool bCaretOn = is_caret_on();

      bool bFocus = has_keyboard_focus();

      if (m_ptree == nullptr)
      {

         return;

      }

      auto rectanglePadding = get_padding(pstyle);

      rectangleClient.deflate(rectanglePadding);

      double left = rectangleClient.left;

      strsize iSelBeg;
      strsize iSelEnd;
      strsize iSelBegOriginal;
      strsize iSelEndOriginal;
      strsize lim = 0;

      ::draw2d::pen_pointer & ppenCaret = m_pcontrolstyle->m_ppenCaret;

      ::draw2d::brush_pointer & pbrushText = m_pcontrolstyle->m_pbrushText;

      ::draw2d::brush_pointer & pbrushTextCr = m_pcontrolstyle->m_pbrushTextCr;

      ::draw2d::brush_pointer & pbrushTextSel = m_pcontrolstyle->m_pbrushTextSel;

      //auto pointOffset = get_context_offset();

      //if (m_dLineHeight > 0.)
      //{

      //   int iVerticalOffsetModule = (int) fmod(pointOffset.y, m_dLineHeight);

      //   if (iVerticalOffsetModule > 0)
      //   {

      //      pgraphics->offset_origin(0, -iVerticalOffsetModule);

      //   }

      //}

      //pgraphics->offset_origin(-pointOffset.x, 0);

      double y = rectangleClient.top + m_iCurrentPageLineStart * m_dLineHeight;

      _001_get_impact_sel(iSelBegOriginal, iSelEndOriginal);

      iSelBeg = iSelBegOriginal;

      iSelEnd = iSelEndOriginal;

      strsize iCursor = iSelEndOriginal;

      __sort(iSelBeg, iSelEnd);

      m_iLastSelectionBeginLine = plain_edit_sel_to_line_x(pgraphics, iSelBeg, m_iLastSelectionBeginX);

      m_iLastSelectionEndLine = plain_edit_sel_to_line_x(pgraphics, iSelEnd, m_iLastSelectionEndX);

      pgraphics->set_font(this, ::e_element_none);

      double dLineHeight = m_dLineHeight;

      string_array & straLines = m_straLines;

      string str1;
      string str2;
      string str3;
      string strExtent1;
      string strExtent2;
      string strExtent3;

      index i = 0;

      pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

      string strLineGraphics;

      if (_001GetTextLength() == 0)
      {

         if (m_strEmtpyText.has_char())
         {

            pgraphics->set(m_pcontrolstyle->m_pbrushTextEmpty);

            pgraphics->text_out(left, y, m_strEmtpyText);

         }

      }

      for (index iLine = m_iCurrentPageLineStart; iLine < m_iCurrentPageLineEnd; i++, iLine++)
      {

         string strLine = straLines[i];

#if defined(LOG_ENABLE_PLAIN_EDIT_LINE)

         if (strLine.has_char())
         {

            auto psz = strLine.c_str();

            FORMATTED_TRACE("Line %s", psz);

         }

#endif

         strLineGraphics = strLine;

         {

            ::color::color crOverride = argb(255, 0, 0, 0);

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

               ::duration tickTimeout = 1_s;

               ::duration tickPeriod = 100_ms;

               if (m_errora[0].m_tick.elapsed() > tickTimeout)
               {

                  if (m_errora[0].m_tick.elapsed() < (tickTimeout + tickPeriod))
                  {

                     iErrorA = (strsize)((m_errora[0].m_tick.elapsed() - tickTimeout) * 255 / tickPeriod);

                  }
                  else
                  {

                     iErrorA = 255;

                  }

                  iErrorBeg = m_errora[0].m_iStart;
                  iErrorEnd = m_errora[0].m_iEnd;
                  iErrorBeg -= lim;
                  iErrorEnd -= lim;
                  iErrorBeg = maximum(0, iErrorBeg);
                  iErrorEnd = minimum(iErrorEnd, strLine.get_length());

               }

            }

            string_array stra;

            strsize iCurLineComposeBeg = iComposeBeg - lim;

            strsize iCurLineComposeEnd = iComposeEnd - lim;

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

            if (iCurLineComposeBeg < 0)
            {

               iCurLineComposeBeg = 0;

            }
            else if (iCurLineComposeBeg >= strLineGraphics.length())
            {

               iCurLineComposeBeg = strLineGraphics.length();

            }

            if (iCurLineSelEnd < 0)
            {

               iCurLineSelEnd = 0;

            }
            else if (iCurLineSelEnd >= strLineGraphics.length())
            {

               iCurLineSelEnd = strLineGraphics.length();

            }

            if (iCurLineComposeEnd < 0)
            {

               iCurLineComposeEnd = 0;

            }
            else if (iCurLineComposeEnd >= strLineGraphics.length())
            {

               iCurLineComposeEnd = strLineGraphics.length();

            }

            replace_tab(0, strLineGraphics, m_iTabWidth, { &iCurLineSelBeg, &iCurLineSelEnd, &iCurLineSelCur });

            if (m_bPassword)
            {

               strLine = ::str().block('*', i32(strLine.get_length()));

            }

            double x1 = plain_edit_get_line_extent(pgraphics, iLine, iCurLineSelBeg);

            double x2 = plain_edit_get_line_extent(pgraphics, iLine, iCurLineSelEnd);

            double compose1 = 0.0;

            double compose2 = 0.0;

            if (bComposing)
            {

               compose1 = plain_edit_get_line_extent(pgraphics, iLine, iCurLineComposeBeg);

               compose2 = plain_edit_get_line_extent(pgraphics, iLine, iCurLineComposeEnd);

            }

            if (m_bPassword)
            {

               strLineGraphics = ::str().block('*', i32(strLineGraphics.get_length()));

            }

            if (iCurLineSelEnd > iCurLineSelBeg)
            {

               pgraphics->fill_rectangle(
                  ::rectangle_f64_dimension((double)((double)left + x1),
                     (double)y,
                     (double)minimum(x2 - x1, (double)rectangleClient.right - ((double)left + x1)),
                     (double)minimum((double)m_dLineHeight, (double)rectangleClient.bottom - y)),
                  crBkSel);

               pgraphics->set(pbrushTextSel);

            }

            if (bOverride)
            {

               pbrushText->create_solid(crOverride);

               pgraphics->set(pbrushText);

            }
            else
            {

               pgraphics->set(pbrushTextCr);

            }

            if (bComposing && iCurLineComposeEnd > iCurLineComposeBeg)
            {

               //pgraphics->fill_rectangle(
               //   ::rectangle_f64_dimension((double)((double)left + compose1),
               //      (double)y,
               //      (double)minimum(compose2 - compose1, (double)rectangleClient.right - ((double)left + compose1)),
               //      (double)minimum((double)m_dLineHeight, (double)rectangleClient.bottom - y)),
               //   colorComposeBk);

               pgraphics->fill_rectangle(
                  ::rectangle_f64_dimension((double)((double)left + compose1),
                     ((double)minimum((double)m_dLineHeight, (double)rectangleClient.bottom)) - 1.0,
                     (double)minimum(compose2 - compose1, (double)rectangleClient.right - ((double)left + compose1)),
                     1.0));

               //pgraphics->set(pbrushTextSel);

            }


            if (iCurLineSelBeg > 0)
            {

               // Draw Normal Text - not selected - before selection
               auto strLeft = strLineGraphics.Left(iCurLineSelBeg);
               pgraphics->text_out(left, y, strLeft);

            }

            if (iCurLineSelBeg < strLineGraphics.get_length())
            {

               // Draw Normal Text - not selected - after selection
               string strRight = strLineGraphics.Mid(iCurLineSelEnd);
               pgraphics->text_out(left + x2, y, strRight);

            }

            if (bOverride)
            {

            }
            else
            {

               pgraphics->set(pbrushTextSel);

            }

            if (iCurLineSelBeg >= 0 && iCurLineSelEnd > iCurLineSelBeg)
            {

               // Draw Selected Text
               string strSelected = strLineGraphics.Mid(iCurLineSelBeg, iCurLineSelEnd - iCurLineSelBeg);
               pgraphics->text_out(left + x1, y, strSelected);

            }

            if (0 <= iErrorBeg && iErrorBeg <= strExtent1.length())
            {

               double xA = plain_edit_get_line_extent(pgraphics, iLine, iErrorBeg);

               double xB = plain_edit_get_line_extent(pgraphics, iLine, minimum(iErrorEnd, strExtent1.length()));

               auto ppen = __create < ::draw2d::pen >();

               ppen->create_solid(1.0, argb((byte)iErrorA, 255, 0, 0));

               pgraphics->set(ppen);

               pgraphics->draw_error_line((int)xA, (int)m_dLineHeight, (int)xB, 1);

            }

            if (iCurLineSelCur >= 0 && bFocus && bCaretOn && iCurLineSelCur == iCurLineSelBeg)
            {

#ifdef WINDOWS_DESKTOP

               ::point_i32 point((long)(left + x1), (long)y);

               client_to_screen(point);

               get_wnd()->screen_to_client(point);

               ::SetCaretPos(point.x, point.y);

#endif

               pgraphics->set(ppenCaret);

               pgraphics->set_current_point(left + x1, y);

               pgraphics->line_to(left + x1, y + dLineHeight);

            }
            else if (iCurLineSelCur >= 0 && bFocus && bCaretOn && iCurLineSelCur == iCurLineSelEnd)
            {

#ifdef WINDOWS_DESKTOP

               ::point_i32 point((long)(left + x1), (long)y);

               client_to_screen(point);

               get_wnd()->screen_to_client(point);

               ::SetCaretPos(point.x, point.y);

#endif

               pgraphics->set(ppenCaret);

               pgraphics->set_current_point(left + x2, y);

               pgraphics->line_to(left + x2, y + dLineHeight);

            }

         }

         y += m_dLineHeight;

         lim += m_iaLineLength[iLine];

      }

      auto d1 = t1.elapsed();

#ifdef VERBOSE_LOG      

      if (d1 > 50_ms)
      {

         CATEGORY_INFORMATION(prodevian, "plain_edit took more than 50ms to draw " << d1.integral_millisecond());

      }

#endif

   }


   void plain_edit::on_message_create(::message::message * pmessage)
   {

      __pointer(::message::create) pcreate(pmessage);

#if !defined(_UWP)

      //auto estatus =

      initialize_text_composition_client(this, this);

      //if (!estatus)
      //{

      //   pcreate->failed("plain_edit::initialize_text_composition_client failed.");

      //   return;

      //}

#endif

      auto pwindowing = windowing();

      auto pcursor = pwindowing->get_cursor(e_cursor_text_select);

      set_mouse_cursor(pcursor);

      pcreate->previous();

#if !defined(APPLE_IOS) && !defined(ANDROID)

      __pointer(::aura::application) papp = get_app();

      //psession->keyboard(); // trigger keyboard creationg
      papp->defer_create_keyboard();

#endif

      if (m_ptree == nullptr)
      {

         set_root(__new(::user::plain_text_tree), true);

         m_ptree->m_pfile = __new(::memory_file);

         m_ptree->m_peditfile->SetFile(m_ptree->m_pfile);

         m_ptree->m_iSelBeg = 0;

         m_ptree->m_iSelEnd = 0;

         m_bGetTextNeedUpdate = true;

         queue_graphics_call([this](::draw2d::graphics_pointer & pgraphics)
            {

               //plain_edit_on_set_text(pgraphics, ::e_source_system);

               plain_edit_on_update(pgraphics, ::e_source_system);

            });

      }

      m_propertyText = fetch_property(m_atom, true);

      if (m_propertyText && !m_propertyText->is_empty())
      {

         _001SetText(m_propertyText->string(), ::e_source_initialize);

      }

      //m_ppropertyText = fetch_property(m_atom, true);

      //add_change_notification(m_ppropertyText);

      //if(m_ppropertyText && !m_ppropertyText->is_empty())
      //{

      //   _001SetText(m_ppropertyText->get_string(), ::e_source_initialize);

      //}

      add_handler(this);

   }


   void plain_edit::on_message_context_menu(::message::message * pmessage)
   {

   }


   void plain_edit::on_message_right_button_down(::message::message * pmessage)
   {

      auto pmouse = pmessage->m_union.m_pmouse;

      ::point_i32 point = pmouse->m_point;

      screen_to_client(point);

      m_bRMouseDown = true;

      queue_graphics_call([this, point](::draw2d::graphics_pointer & pgraphics)
         {

            strsize iHit = plain_edit_char_hit_test(pgraphics, point);

            if (iHit <= m_ptree->m_iSelBeg || iHit >= m_ptree->m_iSelEnd)
            {

               m_ptree->m_iSelBeg = iHit;

               m_ptree->m_iSelEnd = iHit;

            }

         });



      set_need_redraw();

      set_keyboard_focus();

      auto psession = get_session();

      psession->user()->set_mouse_focus_RButtonDown(this);

      pmouse->m_bRet = true;

      pmouse->m_lresult = 1;

   }


   void plain_edit::on_message_right_button_up(::message::message * pmessage)
   {

      auto pmouse = pmessage->m_union.m_pmouse;

      ::point_i32 point = pmouse->m_point;

      screen_to_client(point);

      //{

      //   synchronous_lock synchronouslock(mutex());

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


   //void plain_edit::on_message_set_cursor(::message::message * pmessage)
   //{

   //   pmessage->previous();

   //}


   void plain_edit::_001OnTimer(::timer * ptimer)
   {

      interaction::_001OnTimer(ptimer);

      enum_timer etimer = (enum_timer)ptimer->m_uEvent;

      if (etimer == e_timer_overflow_scrolling)
      {

         if (m_bLMouseDown)
         {

            auto pwindowing = windowing();

            auto pwindow = window();

            auto pointCursor = pwindow->get_cursor_position();

            screen_to_client(pointCursor);

            ::rectangle_i32 rectangleActiveClient;

            GetActiveClientRect(rectangleActiveClient);

            if (pointCursor.x < rectangleActiveClient.left)
            {

               scroll_left_line();

            }
            else if (pointCursor.x > rectangleActiveClient.right)
            {

               scroll_right_line();

            }

            if (pointCursor.y < rectangleActiveClient.top)
            {

               scroll_up_line();

            }
            else if (pointCursor.y > rectangleActiveClient.bottom)
            {

               scroll_down_line();

            }



         }


      }
      else if (ptimer->m_uEvent >= 100
         && ptimer->m_uEvent <= 200)
      {
         if (has_keyboard_focus())
         {

            _001OnKeyboardFocusTimer(ptimer->m_uEvent - 100);

         }
      }
      else if (ptimer->m_uEvent == 500 || ptimer->m_uEvent == 501)
      {

         if (ptimer->m_uEvent == 500)
         {

            KillTimer(500);

            SetTimer(501, 300_ms, nullptr);

         }

         _001OnMessageKey(m_pmessagekeyLast);

      }

   }


   status < ::rectangle_f64 > plain_edit::get_margin(style * pstyle, enum_element eelement, ::user::enum_state estate) const
   {

      return ::user::interaction::get_margin(pstyle, eelement, estate);

   }


   void plain_edit::on_message_key_down(::message::message * pmessage)
   {

      m_pmessagekeyLast = pmessage->m_union.m_pkey;

      _001OnMessageKey(m_pmessagekeyLast);

      pmessage->m_bRet = true;

   }


   void plain_edit::on_message_key_up(::message::message * pmessage)
   {

      auto pkey = pmessage->m_union.m_pkey;

      auto psession = get_session();

      if (pkey->m_ekey == ::user::e_key_return)
      {

         if (psession->is_key_pressed(::user::e_key_control)
            && psession->is_key_pressed(::user::e_key_alt))
         {

            pkey->m_bRet = false;

            return;

         }

      }
      else if (pkey->m_ekey == ::user::e_key_alt)
      {

         pkey->m_bRet = false;

         return;

      }

   }


   void plain_edit::pre_translate_message(::message::message * pmessage)
   {

      ::user::interaction::pre_translate_message(pmessage);

   }


   //void plain_edit::key_to_char(::message::key * pkey)
   //{

   //   ::message::key & key = *pkey;

   //   if (key.m_ekey == ::user::e_key_shift || key.m_ekey == ::user::e_key_left_shift || key.m_ekey == ::user::e_key_right_shift
   //      || key.m_ekey == ::user::e_key_control || key.m_ekey == ::user::e_key_left_control || key.m_ekey == ::user::e_key_right_control
   //      || key.m_ekey == ::user::e_key_alt || key.m_ekey == ::user::e_key_left_alt || key.m_ekey == ::user::e_key_right_alt
   //      )
   //   {

   //      return;

   //   }

   //   if (key.m_ekey == ::user::e_key_right || key.m_ekey == ::user::e_key_up
   //      || key.m_ekey == ::user::e_key_left || key.m_ekey == ::user::e_key_down)
   //   {

   //      on_message_character(&key);

   //      return;

   //   }

   //   auto psession = get_session();

   //   bool bShift = psession->is_key_pressed(::user::e_key_shift);

   //   if (key.m_nChar < 256 && isalpha((i32)key.m_nChar))
   //   {

   //      if (bShift)
   //      {

   //         key.m_nChar = toupper((i32)key.m_nChar);

   //      }
   //      else
   //      {

   //         key.m_nChar = tolower((i32)key.m_nChar);

   //      }

   //   }

   //   INFORMATION("key_to_char (1)");

   //   on_message_character(&key);

   //}


   strsize plain_edit::_001GetTextLength() const
   {

      synchronous_lock synchronouslock(mutex());

      return _001_get_text_length();


   }


   strsize plain_edit::_001_get_text_length() const
   {

      auto ptree = m_ptree;

      if (::is_null(ptree))
      {

         return 0;

      }

      auto peditfile = ptree->m_peditfile;

      if (::is_null(peditfile))
      {

         return 0;

      }

      return (strsize)peditfile->get_length();

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

      synchronous_lock synchronouslock(mutex());

      filesize iSize = m_ptree->m_peditfile->get_length();

      char * psz = str.get_string_buffer((strsize)(iSize + 1));

      m_ptree->m_peditfile->seek(0, ::e_seek_set);

      m_ptree->m_peditfile->read(psz, (memsize)iSize);

      psz[(memsize)iSize] = '\0';

      str.release_string_buffer();

      for (auto & m : m_base64map)
      {

         string strPack = m.element1();

         str.replace_with(m.element2(), strPack);

      }

   }


   void plain_edit::_001GetSelText(string & str) const
   {

      _001GetText(str, m_ptree->m_iSelBeg, m_ptree->m_iSelEnd);

   }


   void plain_edit::_001GetText(string & str, index iBegParam, index iEndParam) const
   {

      synchronous_lock synchronouslock(mutex());

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

      m_ptree->m_peditfile->seek((filesize)iBeg, ::e_seek_set);

      m_ptree->m_peditfile->read(psz, (memsize)(iSize));

      psz[(memsize)iSize] = '\0';

      str.release_string_buffer();

   }


   void plain_edit::_001SetSelText(const ::string & psz, const ::action_context & context)
   {

      {

         synchronous_lock synchronouslock(mutex());

         m_ptree->m_peditfile->seek(m_ptree->m_iSelBeg, ::e_seek_set);

         m_ptree->m_peditfile->Delete((memsize)(m_ptree->m_iSelEnd - m_ptree->m_iSelBeg));

         m_ptree->m_peditfile->seek(m_ptree->m_iSelBeg, ::e_seek_set);

         m_ptree->m_peditfile->Insert(psz, strlen(psz));

      }

      queue_graphics_call([this, context](::draw2d::graphics_pointer & pgraphics)
         {

            plain_edit_on_update(pgraphics, context);

         });

      set_need_redraw();

   }


   void plain_edit::_001SetSelEnd(strsize iSelEnd)
   {

      queue_graphics_call([this, iSelEnd](::draw2d::graphics_pointer & pgraphics)
         {

            _set_sel_end(pgraphics, iSelEnd);

         });

   }


   void plain_edit::_set_sel_end(::draw2d::graphics_pointer & pgraphics, strsize iSelEnd)
   {

      index iColumn = plain_edit_sel_to_column_x(pgraphics, iSelEnd, m_iColumnX);

      int x = 0;

      index iLine = plain_edit_sel_to_line_x(pgraphics, iSelEnd, x);

      index xEnd = 0;

      auto iLineLength = m_iaLineLength[iLine];

      xEnd = index(plain_edit_get_line_extent(pgraphics, iLine, iLineLength));

      ::rectangle_i32 rectangleClient;

      get_client_rect(rectangleClient);

      auto xContext = get_context_offset().x;

      int iBorder = 4;

      if (xEnd < rectangleClient.width() - iBorder * 2)
      {

         xContext = 0;

      }
      else if (xEnd - get_context_offset().x < rectangleClient.width() - iBorder * 2)
      {

         xContext = (int)maximum(0, xEnd - rectangleClient.width() + iBorder * 2);

      }
      else if (x < xContext && xContext > 0)
      {

         xContext = x;

      }
      else if (x > 0 && x < get_context_offset().x)
      {

         xContext = maximum(0, x - rectangleClient.width() / 2);

      }
      else if (x > get_context_offset().x + rectangleClient.width() - iBorder * 2)
      {

         xContext = (int)maximum(0, xEnd - rectangleClient.width() + iBorder * 2);

      }


      if (iSelEnd == m_ptree->m_iSelEnd && iColumn == m_iColumn && xContext == get_context_offset().x)
      {

         return;

      }

      m_ptree->m_iSelEnd = iSelEnd;

      m_iColumn = iColumn;

      if (xContext != get_context_offset().x)
      {

         set_context_offset_x(pgraphics, (int)xContext);

      }

      _001EnsureVisibleChar(pgraphics, iSelEnd);

#ifndef      SEARCH_SCROLLING_PROFILING

      set_need_redraw();

#endif

   }


   void plain_edit::plain_edit_on_end_update(::draw2d::graphics_pointer & pgraphics)
   {

      if (m_bNewSel)
      {

         _001EnsureVisibleChar(pgraphics, m_ptree->m_iSelEnd);

#ifndef      SEARCH_SCROLLING_PROFILING

         set_need_redraw();

#endif

      }

   }


   void plain_edit::_001SetSel(strsize iBeg, strsize iEnd, const ::action_context & action_context)
   {

      synchronous_lock synchronouslock(mutex());

      m_ptree->m_iSelBeg = iBeg;

      m_ptree->m_iSelEnd = iEnd;

      m_bNewSel = true;

      if (action_context.is_user_source())
      {

         auto pwindowing = windowing();

         auto ptexteditorinterface = pwindowing->get_text_editor_interface();

         if (::is_set(ptexteditorinterface))
         {

            string strText;

            _001GetText(strText);

      //      //operating_system_driver::get()->m_iInputMethodManagerSelectionStart = ansi_to_wd16_len(strText, iBeg);

      //      //operating_system_driver::get()->m_iInputMethodManagerSelectionEnd = ansi_to_wd16_len(strText, iEnd);

         auto iSelectionStart = ansi_to_wd32_len(strText, iBeg);

         auto iSelectionEnd = ansi_to_wd32_len(strText, iEnd);

         ptexteditorinterface->set_editor_selection(iSelectionStart, iSelectionEnd);

      //      if (m_pitemComposing)
      //      {

      //         auto iCandidateStart = ansi_to_wd16_len(strText, m_pitemComposing->m_position);

      //         auto iCandidateEnd = ansi_to_wd16_len(strText, m_pitemComposing->m_position + m_pitemComposing->get_extent());

      //         ptexteditorinterface->set_input_method_manager_candidate_position(iCandidateStart, iCandidateEnd);

      //      }
      //      else
      //      {

      //         ptexteditorinterface->synchronize_input_method_manager_with_selection_end();

      //      }

         }

      }

//#ifdef ANDROID
//
//      if (action_context.is_user_source())
//      {
//
//         
//         operating_system_driver::get()->m_iInputMethodManagerSelectionStart = ansi_to_wd16_len(strText, iBeg);
//
//         operating_system_driver::get()->m_iInputMethodManagerSelectionEnd = ansi_to_wd16_len(strText, iEnd);
//
//         if (m_pitemComposing)
//         {
//
//            operating_system_driver::get()->m_iInputMethodManagerCandidateStart = ansi_to_wd16_len(strText, m_pitemComposing->m_position);
//
//            operating_system_driver::get()->m_iInputMethodManagerSelectionEnd = ansi_to_wd16_len(strText, m_pitemComposing->m_position + m_pitemComposing->get_extent());
//
//         }
//         else
//         {
//
//            operating_system_driver::get()->m_iInputMethodManagerCandidateStart = operating_system_driver::get()->m_iInputMethodManagerSelectionEnd;
//
//            operating_system_driver::get()->m_iInputMethodManagerCandidateEnd = operating_system_driver::get()->m_iInputMethodManagerSelectionEnd;
//
//         }
//
//         operating_system_driver::get()->m_bInputMethodManagerUpdateSelection = true;
//
//      }
//
//#endif

   }


   void plain_edit::_001EnsureVisibleChar(::draw2d::graphics_pointer & pgraphics, strsize iChar)
   {

      plain_edit_ensure_visible_char(pgraphics, iChar);

   }


   void plain_edit::plain_edit_ensure_visible_char(::draw2d::graphics_pointer & pgraphics, strsize iChar)
   {

      int x = 0;

      plain_edit_ensure_visible_line(pgraphics, plain_edit_sel_to_line_x(pgraphics, iChar, x));

      int iBorder = 4;

      ::rectangle_i32 rectangleClient;

      get_client_rect(rectangleClient);

      int xVisibleStart = m_pointScroll.x;

      int xVisibleEnd = xVisibleStart + rectangleClient.width() - iBorder * 2;

      if (x < xVisibleStart)
      {

         m_pointScroll.x = x;

      }
      else if (x > xVisibleEnd)
      {

         m_pointScroll.x = x - rectangleClient.width() + iBorder * 2;

      }

   }


   void plain_edit::_001EnsureVisibleLine(::draw2d::graphics_pointer & pgraphics, index iLine)
   {

      plain_edit_ensure_visible_line(pgraphics, iLine);

   }


   void plain_edit::plain_edit_ensure_visible_line(::draw2d::graphics_pointer & pgraphics, ::index iLine)
   {

      if (!m_bMultiLine)
      {

         set_context_offset_y(pgraphics, 0);

      }
      else
      {

         ::rectangle_i32 rectangleClient;

         GetFocusRect(rectangleClient);

         int iCurrentPageTop = get_context_offset().y;

         int iCurrentPageBottom = get_context_offset().y + rectangleClient.height();

         index iLineTop = (::index)(iLine * m_dLineHeight);

         index iLineBottom = ((::index)((iLine + 1) * m_dLineHeight));

         if (iLineTop < iCurrentPageTop)
         {

            set_context_offset_y(pgraphics, (int)iLineTop);

         }
         else if (iLineBottom >= iCurrentPageBottom)
         {

            set_context_offset_y(pgraphics, ((int)iLineBottom - rectangleClient.height()) + (int)(m_dLineHeight / 4.0));

         }

         m_bCalcLayoutHintNoTextChange = true;

      }

      plain_edit_on_calc_offset(pgraphics);

#ifndef SEARCH_SCROLLING_PROFILING

      set_need_redraw();

#endif

   }


   void plain_edit::on_change_context_offset(::draw2d::graphics_pointer & pgraphics)
   {

      scroll_base::on_change_context_offset(pgraphics);

      plain_edit_on_calc_offset(pgraphics);

      //set_need_redraw();

   }


   bool plain_edit::plain_edit_is_enabled()
   {

      return true;

   }

   void plain_edit::on_message_mouse_move(::message::message * pmessage)
   {

      pmessage->previous();

      if (plain_edit_is_enabled())
      {

         auto pmouse = pmessage->m_union.m_pmouse;

         auto pwindowing = windowing();

         auto pcursor = pwindowing->get_cursor(e_cursor_text_select);

         pmouse->m_pcursor = pcursor;

         set_mouse_cursor(pcursor);

         if (m_bLMouseDown)
         {

            ::point_i32 point = pmouse->m_point;

            screen_to_client(point);

            if (m_pointLastCursor != point)
            {

               m_pointLastCursor = point;


               synchronous_lock synchronouslock(mutex());

               ::rectangle_i32 rectangleWindow;

               get_window_rect(rectangleWindow);

               if (pmouse->m_point.x < rectangleWindow.left - 30)
               {

                  output_debug_string("test06");

               }

               queue_graphics_call([this, point](::draw2d::graphics_pointer & pgraphics)
                  {

                     _set_sel_end(pgraphics, plain_edit_char_hit_test(pgraphics, point));

                  });

               set_need_redraw();

               post_redraw();

            }

            m_pitemHover = __new(::item(e_element_client));

         }

      }

   }


   void plain_edit::on_message_mouse_leave(::message::message * pmessage)
   {

      m_pitemHover = __new(::item(e_element_none));

      set_need_redraw();

   }


   void plain_edit::on_message_left_button_down(::message::message * pmessage)
   {

      auto pmouse = pmessage->m_union.m_pmouse;

      if (plain_edit_is_enabled())
      {

         pmouse->previous();

         ::point_i32 point = pmouse->m_point;

         screen_to_client(point);

         {

            synchronous_lock synchronouslock(mutex());

            m_bLMouseDown = true;

            SetTimer(e_timer_overflow_scrolling, 50_ms, nullptr);

            set_mouse_capture();

            queue_graphics_call([this, point](::draw2d::graphics_pointer & pgraphics)
            {

               auto iSelBeg = plain_edit_char_hit_test(pgraphics, point);

               auto iSelEnd = iSelBeg;
               
               FORMATTED_INFORMATION("LeftButtonDown(%d,%d)-queue_graphics_call", iSelBeg, iSelEnd);

               _001SetSel(iSelBeg, iSelEnd);

               m_iColumn = plain_edit_sel_to_column_x(pgraphics, m_ptree->m_iSelEnd, m_iColumnX);

            });

#if defined(WINDOWS_DESKTOP)

            on_text_composition_message(TEXT_COMPOSITION_MESSAGE_UPDATE_CANDIDATE_WINDOW_POSITION);

#endif

         }

         set_need_redraw();

         pmouse->m_bRet = true;

         pmouse->m_lresult = 1;

         on_reset_focus_start_tick();

      }
      else
      {

         pmouse->previous();

      }

   }


   void plain_edit::on_message_left_button_up(::message::message * pmessage)
   {

      auto pmouse = pmessage->m_union.m_pmouse;

      auto pwindowing = windowing();

      pwindowing->release_mouse_capture();

      if (m_bLMouseDown)
      {

         ::point_i32 point = pmouse->m_point;

         screen_to_client(point);

         queue_graphics_call([this, point](::draw2d::graphics_pointer & pgraphics)
            {

               _set_sel_end(pgraphics, plain_edit_char_hit_test(pgraphics, point));

            });

      }

      set_need_redraw();

      m_bLMouseDown = false;

      pmouse->m_bRet = true;

      pmouse->m_lresult = 1;

      on_reset_focus_start_tick();

   }


   void plain_edit::on_message_left_button_double_click(::message::message * pmessage)
   {

      pmessage->m_bRet = true;
   
   }


   void plain_edit::plain_edit_on_calc_offset(::draw2d::graphics_pointer & pgraphics, index iOnlyLineToUpdate)
   {

      synchronous_lock synchronouslock(mutex());

      _plain_edit_update_lines_and_extents(pgraphics, iOnlyLineToUpdate);

      //synchronous_lock synchronouslock(mutex());

      //::rectangle_i32 rectangleClient;

      //GetFocusRect(rectangleClient);

      //if (m_ptree == nullptr)
      //{

      //   m_iCurrentPagePotentialLineCount = 0;

      //   m_iCurrentPageLineOffset = 0;

      //   m_iCurrentPageLineStart = 0;

      //   m_iCurrentPageLineEnd = 0;

      //   m_iImpactOffset = 0;

      //   m_iImpactSize = 0;

      //   return;

      //}

      //::index i;

      //::index iLine;

      //if (pgraphics.is_null())
      //{

      //   return;

      //}

      //pgraphics->set_font(this, ::e_element_none);

      //size_f64 sizeUniText;

      //::write_text::text_metric metric;

      //pgraphics->get_text_metrics(&metric);

      //m_dLineHeight = metric.get_line_spacing();

      //if (m_dLineHeight <= 0.0)
      //{

      //   m_dLineHeight = 18.0;

      //}

      //auto pointOffset = get_context_offset();

      //m_iCurrentPagePotentialLineCount = (::count) ceil((double)rectangleClient.height() / m_dLineHeight);

      //m_iCurrentPageLineOffset = (::index) minimum(maximum(0, pointOffset.y / m_dLineHeight), m_iaLineStart.get_upper_bound());

      //bool bLoadFullFile = should_load_full_file();

      //m_iCurrentPageLineStart = bLoadFullFile ? 0 : maximum(0, m_iCurrentPageLineOffset);

      //m_iCurrentPageLineEnd = bLoadFullFile ? m_iaLineLength.get_size() : minimum(m_iaLineLength.get_size(), m_iCurrentPagePotentialLineCount + m_iCurrentPageLineStart);

      //if (m_iCurrentPageLineOffset < 0)
      //{

      //   return;

      //}

      //m_iImpactOffset = m_iaLineStart[m_iCurrentPageLineStart];

      //strsize iProperBeg = m_iaLineStart[m_iCurrentPageLineEnd - 1];

      //strsize iLen = m_iaLineLength[m_iCurrentPageLineEnd - 1];

      //m_iImpactSize = iProperBeg + iLen - m_iImpactOffset;

      //index iLineStart;

      //index iLineEnd;

      //index iImpactOffset;

      //index iImpactSize;

      //if (iLineUpdate < 0)
      //{

      //   iLineStart = m_iCurrentPageLineStart;

      //   iLineEnd = m_iCurrentPageLineEnd;

      //   iImpactOffset = m_iImpactOffset;

      //   iImpactSize = m_iImpactSize;

      //}
      //else
      //{

      //   iLineStart = iLineUpdate;

      //   iLineEnd = iLineStart + 1;

      //   iImpactOffset = m_iaLineStart[iLineStart];

      //   iProperBeg = m_iaLineStart[iLineEnd - 1];

      //   iLen = m_iaLineLength[iLineEnd - 1];

      //   iImpactSize = iProperBeg + iLen - iImpactOffset;

      //}

      //string strLine;

      //memory mem;

      //mem.set_size(iImpactSize + 1);

      //strsize iRead;

      //{

      //   m_ptree->m_peditfile->seek(iImpactOffset, ::e_seek_set);

      //   iRead = m_ptree->m_peditfile->read(mem.get_data(), iImpactSize);

      //   if (iRead < iImpactSize)
      //   {

      //      TRACE("ops1");

      //      iImpactSize = iRead;

      //   }

      //   mem.get_data()[iImpactSize] = 0;

      //}

      //strsize iPos = 0;

      ////      strsize iLen;

      //strsize iStrLen;

      ////m_plinea->lines.set_size(m_iCurrentPageLineEnd - m_iCurrentPageLineStart);
      //m_straLines.set_size(m_iCurrentPageLineEnd - m_iCurrentPageLineStart);

      //i = 0;

      //iLine = iLineStart;

      //auto iLineLength = m_iaLineLength.get_size();

      //m_daExtent.set_size(iLineLength);

      //for (; iLine < iLineEnd; i++, iLine++)
      //{

      //   iLen = m_iaLineLength[iLine];

      //   iStrLen = maximum(0, iLen - (m_iaLineFlags[iLine] & e_line_end_length));

      //   if (iPos + iStrLen > m_iImpactSize)
      //   {

      //      TRACE("ops3");

      //      iStrLen = iImpactSize - iPos;

      //      if (iStrLen <= 0)
      //      {

      //         TRACE("ops4");

      //         break;

      //      }

      //   }

      //   string strLine = string((const char *)&mem.get_data()[iPos], iStrLen);

      //   //if (strLine != m_plinea->lines[i])
      //   if (strLine != m_straLines[i])
      //   {

      //      //m_plinea->lines[i] = strLine;
      //      m_straLines[i] = strLine;

      //      m_daExtent[i + iLineStart].set_size(0);

      //   }
      //   else
      //   {

      //      //TRACE("optstr");

      //   }

      //   iPos += iLen;

      //   if (iPos > iImpactSize)
      //   {

      //      TRACE("ops2");

      //      break;

      //   }

      //}

      //m_dy = pointOffset.y;

      ////::colorertake5::base_editor * pcolorer = colorertake5();

      ////if (pcolorer != nullptr)
      ////{

      ////   pcolorer->visibleTextEvent(m_iCurrentPageLineStart, m_iLineCount);

      ////}

      ////string_array & straLines = m_plinea->lines;

      //string_array & straLines = m_straLines;

      //if (iLineUpdate < 0)
      //{

      //   //m_sizeTotal.cx = 0;

      //}

      //size_f64 size;

      //string strLineGraphics;

      //strsize_array iaTab;

      //strsize iTab;

      //strsize iAddUp;

      //for (i32 i = 0; i < straLines.get_size(); i++)
      //{

      //   strLine = straLines[i];

      //   iTab = -1;

      //   iaTab.erase_all();

      //   strLineGraphics = strLine;

      //   ::str().replace_tab(0, strLineGraphics, m_iTabWidth, &iaTab);

      //   const char * pszStart = strLine;

      //   const char * psz = pszStart;

      //   strsize iLen = 0;

      //   iAddUp = 0;

      //   iPos = 0;

      //   const char * pszNext = pszStart;

      //   double_array & daExtent = m_daExtent[m_iCurrentPageLineStart + i];

      //   if (daExtent.get_size() <= 0)
      //   {

      //      daExtent.set_size(strLine.get_length() + 1);

      //      while (*pszNext != '\0')
      //      {

      //         pszNext = ::str().next(psz);

      //         iLen = pszNext - psz;

      //         if (*psz == '\t')
      //         {

      //            iTab++;

      //            iAddUp += iaTab[iTab] - 1;

      //         }

      //         size = pgraphics->get_text_extent(strLineGraphics, strLineGraphics.get_length(), pszNext - pszStart + iAddUp);

      //         for (int j = 0; j < iLen; j++)
      //         {

      //           daExtent [(::index)(psz - pszStart + j)] = size.cx;

      //         }

      //         psz = pszNext;

      //      }

      //      if (strLineGraphics.has_char())
      //      {

      //         size = pgraphics->get_text_extent(strLineGraphics, strLineGraphics.get_length());

      //         for (int j = 0; j < iLen; j++)
      //         {

      //            daExtent[(::index)(psz - pszStart)] = size.cx;

      //         }

      //      }


      //      if (size.cx > m_sizeTotal.cx)
      //      {

      //         m_sizeTotal.cx = (i32)size.cx;

      //      }

      //   }


      //}

      ////if (iLineUpdate < 0)
      ////{

      ////   m_sizeTotal.cy = (((i32)m_iaLineLength.get_count() + (m_bMultiLine ? maximum(5, m_iLineCount) : 0)) * m_iLineHeight);

      ////   const ::size_i32 & sizePage;

      ////   sizePage = rectangleClient.size();

      ////   if (m_sizeTotal.cy < sizePage.cy)
      ////   {

      ////      sizePage.cy = m_sizeTotal.cy;

      ////   }

      ////}

      ////on_change_impact_size();

      ////m_bCalcLayoutHintNoTextChange = false;

   }


   void plain_edit::plain_edit_on_calc_layout(::draw2d::graphics_pointer & pgraphics, index iOnlyLineToUpdate)
   {

      synchronous_lock synchronouslock(mutex());

      if (!m_bMultiLine)
      {

         auto psession = get_session();

         string strTextPrevious;

         _001GetText(strTextPrevious);

         string strText(strTextPrevious);

         if (strText.contains("\n"))
         {

            if (psession->m_bProgrammerMode)
            {

               strText.replace_with("\\n", "\n");

            }
            else
            {

               strText.replace_with("", "\n");

            }

         }

         if (strText.contains("\r"))
         {

            if (psession->m_bProgrammerMode)
            {

               strText.replace_with("\\r", "\r");

            }
            else
            {

               strText.replace_with("", "\r");

            }

         }

         if (strTextPrevious != strText)
         {

            synchronous_lock synchronouslock(mutex());

            m_ptree->m_peditfile->seek(0, ::e_seek_set);
            m_ptree->m_peditfile->Delete((memsize)m_ptree->m_peditfile->get_length());
            m_ptree->m_peditfile->seek(0, ::e_seek_set);
            m_ptree->m_peditfile->Insert(strText, strText.get_length());

         }

      }

      ::rectangle_i32 rectangleClient;

      GetFocusRect(rectangleClient);

      if (rectangleClient.area() <= 0)
      {

         return;

      }

      auto pstyle = get_style(pgraphics);

      if (::is_set(pstyle))
      {

         pstyle->get(m_pcontrolstyle, pgraphics, this);

      }

      _plain_edit_update_lines_and_extents(pgraphics, iOnlyLineToUpdate);

      //      if (m_ptree == nullptr)
      //      {
      //
      //         m_iCurrentPagePotentialLineCount = 0;
      //
      //         m_iCurrentPageLineOffset = 0;
      //
      //         m_iCurrentPageLineStart = 0;
      //
      //         m_iCurrentPageLineEnd = 0;
      //
      //         m_iImpactOffset = 0;
      //
      //         m_iImpactSize = 0;
      //
      //         m_sizeTotal = { 0, 0 };
      //
      //         on_change_impact_size(pgraphics);
      //
      //         return;
      //
      //      }
      //
      //      ::index i;
      //
      //      ::index iLine;
      //
      //      pgraphics->set_font(this, ::e_element_none);
      //
      //      size_f64 sizeUniText;
      //
      //      if (pgraphics == nullptr)
      //      {
      //
      //         return;
      //
      //      }
      //
      //      ::write_text::text_metric metric;
      //
      //      pgraphics->get_text_metrics(&metric);
      //
      //      m_dLineHeight = metric.get_line_spacing();
      //
      //      m_scrolldataVertical.m_iLine = (::i32) m_dLineHeight;
      //
      //      if (m_dLineHeight <= 0)
      //      {
      //
      //         m_dLineHeight = 18;
      //
      //      }
      //
      //      auto pointOffset = get_context_offset();
      //
      //      m_iCurrentPagePotentialLineCount = (::count) ceil((double) rectangleClient.height() / m_dLineHeight);
      //
      //      m_iCurrentPageLineOffset = (::index) minimum(maximum(0, pointOffset.y / m_dLineHeight), m_iaLineStart.get_upper_bound());
      //
      //      bool bLoadFullFile = should_load_full_file();
      //
      //      m_iCurrentPageLineStart = bLoadFullFile ? 0 : maximum(0, m_iCurrentPageLineOffset);
      //
      //      m_iCurrentPageLineEnd = bLoadFullFile ? m_iaLineLength.get_size() : minimum(m_iaLineLength.get_size(), m_iCurrentPagePotentialLineCount + m_iCurrentPageLineStart);
      //
      //      if (m_iCurrentPageLineOffset < 0)
      //      {
      //
      //         return;
      //
      //      }
      //
      //      m_iImpactOffset = m_iaLineStart[m_iCurrentPageLineStart];
      //
      //      strsize iProperBeg = m_iaLineStart[m_iCurrentPageLineEnd - 1];
      //
      //      strsize iLen = m_iaLineLength[m_iCurrentPageLineEnd - 1];
      //
      //      m_iImpactSize = iProperBeg + iLen - m_iImpactOffset;
      //
      //      index iLineStart;
      //
      //      index iLineEnd;
      //
      //      index iImpactOffset;
      //
      //      index iImpactSize;
      //
      //      if (iLineUpdate < 0)
      //      {
      //
      //         iLineStart = m_iCurrentPageLineStart;
      //
      //         iLineEnd = m_iCurrentPageLineEnd;
      //
      //         iImpactOffset = m_iImpactOffset;
      //
      //         iImpactSize = m_iImpactSize;
      //
      //      }
      //      else
      //      {
      //
      //         iLineStart = iLineUpdate;
      //
      //         iLineEnd = iLineStart + 1;
      //
      //         iImpactOffset = m_iaLineStart[iLineStart];
      //
      //         iProperBeg = m_iaLineStart[iLineEnd - 1];
      //
      //         iLen = m_iaLineLength[iLineEnd - 1];
      //
      //         iImpactSize = iProperBeg + iLen - iImpactOffset;
      //
      //      }
      //
      //      string strLine;
      //
      //      memory mem;
      //
      //      mem.set_size(iImpactSize + 1);
      //
      //      strsize iRead;
      //
      //      {
      //
      //         m_ptree->m_peditfile->seek(iImpactOffset, ::e_seek_set);
      //
      //         iRead = m_ptree->m_peditfile->read(mem.get_data(), iImpactSize);
      //
      //         if (iRead < iImpactSize)
      //         {
      //
      //            TRACE("ops1");
      //
      //            iImpactSize = iRead;
      //
      //         }
      //
      //         mem.get_data()[iImpactSize] = 0;
      //
      //      }
      //
      //      strsize iPos = 0;
      //
      //      //      strsize iLen;
      //
      //      strsize iStrLen;
      //
      //      //m_plinea->lines.set_size(m_iCurrentPageLineEnd - m_iCurrentPageLineStart);
      //
      //      string_array & straLines = m_straLines;
      //
      //      straLines.set_size(m_iCurrentPageLineEnd - m_iCurrentPageLineStart);
      //
      //      i = 0;
      //
      //      iLine = iLineStart;
      //
      //      m_daExtent.set_size(m_iaLineLength.get_size());
      //
      //      for (; iLine < iLineEnd; i++, iLine++)
      //      {
      //
      //         iLen = m_iaLineLength[iLine];
      //
      //         iStrLen = maximum(0, iLen - (m_iaLineFlags[iLine] & e_line_end_length));
      //
      //         if (iPos + iStrLen > m_iImpactSize)
      //         {
      //
      //            TRACE("ops3");
      //
      //            iStrLen = iImpactSize - iPos;
      //
      //            if (iStrLen <= 0)
      //            {
      //
      //               TRACE("ops4");
      //
      //               break;
      //
      //            }
      //
      //         }
      //
      //         string strLine = string((const char *)&mem.get_data()[iPos], iStrLen);
      //
      //         string_array & straLines = m_straLines;
      //
      //         //if (strLine != m_plinea->lines[i])
      //         if (strLine != straLines[i])
      //         {
      //
      //            straLines[i] = strLine;
      //
      //            m_daExtent[i + iLineStart].set_size(0);
      //
      //         }
      //         else
      //         {
      //
      //            //TRACE("optstr");
      //
      //         }
      //
      //
      //
      //
      //         iPos += iLen;
      //
      //         if (iPos > iImpactSize)
      //         {
      //
      //            TRACE("ops2");
      //
      //            break;
      //
      //         }
      //
      //      }
      //
      //      m_dy = pointOffset.y;
      //
      //      //::colorertake5::base_editor * pcolorer = colorertake5();
      //
      //      //if (pcolorer != nullptr)
      //      //{
      //
      //      //   pcolorer->visibleTextEvent(m_iCurrentPageLineStart, m_iLineCount);
      //
      //      //}
      //
      ////      string_array & straLines = m_plinea->lines;
      ////      string_array & straLines = m_straLines;
      //
      //      if (iLineUpdate < 0)
      //      {
      //
      //         //m_sizeTotal.cx = 0;
      //
      //      }
      //
      //      size_f64 size;
      //
      //
      //
      //      string strLineGraphics;
      //
      //      strsize_array iaTab;
      //
      //      strsize iTab;
      //
      //      strsize iAddUp;
      //
      //
      //      for (i32 i = 0; i < straLines.get_size(); i++)
      //      {
      //
      //         strLine = straLines[i];
      //
      //         iTab = -1;
      //
      //         iaTab.erase_all();
      //
      //         strLineGraphics = strLine;
      //
      //         bool bTabs = strLine.find('\t') >= 0;
      //
      //         if (bTabs)
      //         {
      //
      //            ::str().replace_tab(0, strLineGraphics, m_iTabWidth, &iaTab);
      //
      //         }
      //
      //         const char * pszStart = strLine;
      //
      //         const char * psz = pszStart;
      //
      //         strsize iLen = 0;
      //
      //         iAddUp = 0;
      //
      //         iPos = 0;
      //
      //         const char * pszNext = pszStart;
      //
      //         ::size_i32 sizeLast(0, 0);
      //
      //         auto & daExtent = m_daExtent[m_iCurrentPageLineStart + i];
      //
      //         if (daExtent.get_size() <= 0)
      //         {
      //
      //            daExtent.set_size(strLine.get_length() + 1);
      //
      //            while (*pszNext != '\0')
      //            {
      //
      //               pszNext = ::str().next(psz);
      //
      //               if (pszNext == nullptr)
      //               {
      //
      //                  break;
      //
      //               }
      //
      //               iLen = pszNext - psz;
      //
      //               if (*psz == '\t')
      //               {
      //
      //                  iTab++;
      //
      //                  iAddUp += iaTab[iTab] - 1;
      //
      //               }
      //
      //               size = pgraphics->get_text_extent(strLineGraphics, strLineGraphics.get_length(), pszNext - pszStart + iAddUp);
      //
      //               if (size.cx > rectangleClient.width() + 200)
      //               {
      //
      //                  while (*psz != '\0')
      //                  {
      //
      //                     daExtent[(::index)(psz - pszStart)] = -1;
      //                     psz++;
      //
      //                  }
      //
      //                  break;
      //
      //               }
      //
      //               sizeLast.cx = (::i32) size.cx;
      //
      //               for (int j = 0; j < iLen; j++)
      //               {
      //
      //                  daExtent[(::index)(psz - pszStart + j)] = size.cx;
      //
      //               }
      //
      //               psz = pszNext;
      //
      //            }
      //
      //            if (strLineGraphics.has_char())
      //            {
      //
      //               size = pgraphics->get_text_extent(strLineGraphics, strLineGraphics.get_length());
      //
      //               daExtent[(::index)(psz - pszStart)] = size.cx;
      //
      //            }
      //
      //            if (size.cx > m_sizeTotal.cx)
      //            {
      //
      //               m_sizeTotal.cx = (i32)size.cx;
      //
      //            }
      //
      //         }
      //
      //
      //      }
      //
      //      if (iLineUpdate < 0)
      //      {
      //
      //         m_sizeTotal.cy = (::i32) ((m_iaLineLength.get_count() + 1) * m_dLineHeight);
      //
      //         ::size_f64 sizePage;
      //
      //         sizePage = rectangleClient.size();
      //
      //         if (m_sizeTotal.cy < sizePage.cy)
      //         {
      //
      //            sizePage.cy = m_sizeTotal.cy;
      //
      //         }
      //
      //      }
      //
      //      m_scrolldataVertical.m_iLine = (int) m_dLineHeight;
      //
      //      on_change_impact_size(pgraphics);
      //
      //      m_bCalcLayoutHintNoTextChange = false;

   }


   void plain_edit::_plain_edit_update_lines_and_extents(::draw2d::graphics_pointer & pgraphics, index iOnlyLineToUpdate)
   {

      _plain_edit_update_lines(pgraphics, iOnlyLineToUpdate);

      _plain_edit_update_extents(pgraphics, iOnlyLineToUpdate);

   }


   void plain_edit::_plain_edit_update_lines(::draw2d::graphics_pointer & pgraphics, index iOnlyLineToUpdate)
   {

      //synchronous_lock synchronouslock(mutex());

      ::rectangle_i32 rectangleClient;

      GetFocusRect(rectangleClient);

      if (m_ptree == nullptr)
      {

         m_iCurrentPagePotentialLineCount = 0;

         m_iCurrentPageLineOffset = 0;

         m_iCurrentPageLineStart = 0;

         m_iCurrentPageLineEnd = 0;

         m_iImpactOffset = 0;

         m_iImpactSize = 0;

         return;

      }

      ::index i;

      ::index iLine;

      if (pgraphics.is_null())
      {

         return;

      }

      pgraphics->set_font(this, ::e_element_none);

      size_f64 sizeUniText;

      ::write_text::text_metric metric;

      pgraphics->get_text_metrics(&metric);

      m_dLineHeight = metric.get_line_spacing();

      if (m_dLineHeight <= 0.0)
      {

         m_dLineHeight = 18.0;

      }

      auto pointOffset = get_context_offset();

      m_iCurrentPagePotentialLineCount = (::count)ceil((double)rectangleClient.height() / m_dLineHeight);

      m_iCurrentPageLineOffset = (::index)minimum(maximum(0, pointOffset.y / m_dLineHeight), m_iaLineStart.get_upper_bound());

      bool bLoadFullFile = should_load_full_file();

      m_iCurrentPageLineStart = bLoadFullFile ? 0 : maximum(0, m_iCurrentPageLineOffset);

      m_iCurrentPageLineEnd = bLoadFullFile ? m_iaLineLength.get_size() : minimum(m_iaLineLength.get_size(), m_iCurrentPagePotentialLineCount + m_iCurrentPageLineStart);

      if (m_iCurrentPageLineOffset < 0)
      {

         return;

      }

      m_iImpactOffset = m_iaLineStart[m_iCurrentPageLineStart];

      strsize iProperBeg = m_iaLineStart[m_iCurrentPageLineEnd - 1];

      strsize iLen = m_iaLineLength[m_iCurrentPageLineEnd - 1];

      m_iImpactSize = iProperBeg + iLen - m_iImpactOffset;

      index iLineStart;

      index iLineEnd;

      index iImpactOffset;

      index iImpactSize;

      if (iOnlyLineToUpdate < 0)
      {

         iLineStart = m_iCurrentPageLineStart;

         iLineEnd = m_iCurrentPageLineEnd;

         iImpactOffset = m_iImpactOffset;

         iImpactSize = m_iImpactSize;

      }
      else
      {

         iLineStart = iOnlyLineToUpdate;

         iLineEnd = iLineStart + 1;

         iImpactOffset = m_iaLineStart[iLineStart];

         iProperBeg = m_iaLineStart[iLineEnd - 1];

         iLen = m_iaLineLength[iLineEnd - 1];

         iImpactSize = iProperBeg + iLen - iImpactOffset;

      }

      string strLine;

      memory mem;

      mem.set_size(iImpactSize + 1);

      strsize iRead;

      {

         m_ptree->m_peditfile->seek(iImpactOffset, ::e_seek_set);

         iRead = m_ptree->m_peditfile->read(mem.get_data(), iImpactSize);

         if (iRead < iImpactSize)
         {

            TRACE("ops1");

            iImpactSize = iRead;

         }

         mem.get_data()[iImpactSize] = 0;

      }

      strsize iPos = 0;

      //      strsize iLen;

      strsize iStrLen;

      //m_plinea->lines.set_size(m_iCurrentPageLineEnd - m_iCurrentPageLineStart);
      m_straLines.set_size(m_iCurrentPageLineEnd - m_iCurrentPageLineStart);

      i = 0;

      iLine = iLineStart;

      auto iLineLength = m_iaLineLength.get_size();

      m_daExtent.set_size(iLineLength);

      for (; iLine < iLineEnd; i++, iLine++)
      {

         iLen = m_iaLineLength[iLine];

         iStrLen = maximum(0, iLen - (m_iaLineFlags[iLine] & e_line_end_length));

         if (iPos + iStrLen > m_iImpactSize)
         {

            TRACE("ops3");

            iStrLen = iImpactSize - iPos;

            if (iStrLen <= 0)
            {

               TRACE("ops4");

               break;

            }

         }

         string strLine = string((const char *)&mem.get_data()[iPos], iStrLen);

         //if (strLine != m_plinea->lines[i])
         if (strLine != m_straLines[i])
         {

            //m_plinea->lines[i] = strLine;
            m_straLines[i] = strLine;

            m_daExtent[i + iLineStart].set_size(0);

         }
         else
         {

            //TRACE("optstr");

         }

         iPos += iLen;

         if (iPos > iImpactSize)
         {

            TRACE("ops2");

            break;

         }

      }

      //m_dy = pointOffset.y;

      ////::colorertake5::base_editor * pcolorer = colorertake5();

      ////if (pcolorer != nullptr)
      ////{

      ////   pcolorer->visibleTextEvent(m_iCurrentPageLineStart, m_iLineCount);

      ////}

      ////string_array & straLines = m_plinea->lines;

      //string_array & straLines = m_straLines;

      //if (iLineUpdate < 0)
      //{

      //   //m_sizeTotal.cx = 0;

      //}

      //size_f64 size;

      //string strLineGraphics;

      //strsize_array iaTab;

      //strsize iTab;

      //strsize iAddUp;

      //for (i32 i = 0; i < straLines.get_size(); i++)
      //{

      //   strLine = straLines[i];

      //   iTab = -1;

      //   iaTab.erase_all();

      //   strLineGraphics = strLine;

      //   ::str().replace_tab(0, strLineGraphics, m_iTabWidth, &iaTab);

      //   const char * pszStart = strLine;

      //   const char * psz = pszStart;

      //   strsize iLen = 0;

      //   iAddUp = 0;

      //   iPos = 0;

      //   const char * pszNext = pszStart;

      //   double_array & daExtent = m_daExtent[m_iCurrentPageLineStart + i];

      //   if (daExtent.get_size() <= 0)
      //   {

      //      daExtent.set_size(strLine.get_length() + 1);

      //      while (*pszNext != '\0')
      //      {

      //         pszNext = ::str().next(psz);

      //         iLen = pszNext - psz;

      //         if (*psz == '\t')
      //         {

      //            iTab++;

      //            iAddUp += iaTab[iTab] - 1;

      //         }

      //         size = pgraphics->get_text_extent(strLineGraphics, strLineGraphics.get_length(), pszNext - pszStart + iAddUp);

      //         for (int j = 0; j < iLen; j++)
      //         {

      //           daExtent [(::index)(psz - pszStart + j)] = size.cx;

      //         }

      //         psz = pszNext;

      //      }

      //      if (strLineGraphics.has_char())
      //      {

      //         size = pgraphics->get_text_extent(strLineGraphics, strLineGraphics.get_length());

      //         for (int j = 0; j < iLen; j++)
      //         {

      //            daExtent[(::index)(psz - pszStart)] = size.cx;

      //         }

      //      }


      //      if (size.cx > m_sizeTotal.cx)
      //      {

      //         m_sizeTotal.cx = (i32)size.cx;

      //      }

      //   }


      //}

      ////if (iLineUpdate < 0)
      ////{

      ////   m_sizeTotal.cy = (((i32)m_iaLineLength.get_count() + (m_bMultiLine ? maximum(5, m_iLineCount) : 0)) * m_iLineHeight);

      ////   const ::size_i32 & sizePage;

      ////   sizePage = rectangleClient.size();

      ////   if (m_sizeTotal.cy < sizePage.cy)
      ////   {

      ////      sizePage.cy = m_sizeTotal.cy;

      ////   }

      ////}

      ////on_change_impact_size();

      ////m_bCalcLayoutHintNoTextChange = false;

   }


   void plain_edit::_plain_edit_update_extents(::draw2d::graphics_pointer & pgraphics, index iOnlyLineToUpdate)
   {

      //synchronous_lock synchronouslock(mutex());

//::rectangle_i32 rectangleClient;

//GetFocusRect(rectangleClient);

//if (m_ptree == nullptr)
//{

//   m_iCurrentPagePotentialLineCount = 0;

//   m_iCurrentPageLineOffset = 0;

//   m_iCurrentPageLineStart = 0;

//   m_iCurrentPageLineEnd = 0;

//   m_iImpactOffset = 0;

//   m_iImpactSize = 0;

//   return;

//}

//::index i;

//::index iLine;

//if (pgraphics.is_null())
//{

//   return;

//}

//pgraphics->set_font(this, ::e_element_none);

//size_f64 sizeUniText;

//::write_text::text_metric metric;

//pgraphics->get_text_metrics(&metric);

//m_dLineHeight = metric.get_line_spacing();

//if (m_dLineHeight <= 0.0)
//{

//   m_dLineHeight = 18.0;

//}

//auto pointOffset = get_context_offset();

//m_iCurrentPagePotentialLineCount = (::count) ceil((double)rectangleClient.height() / m_dLineHeight);

//m_iCurrentPageLineOffset = (::index) minimum(maximum(0, pointOffset.y / m_dLineHeight), m_iaLineStart.get_upper_bound());

//bool bLoadFullFile = should_load_full_file();

//m_iCurrentPageLineStart = bLoadFullFile ? 0 : maximum(0, m_iCurrentPageLineOffset);

//m_iCurrentPageLineEnd = bLoadFullFile ? m_iaLineLength.get_size() : minimum(m_iaLineLength.get_size(), m_iCurrentPagePotentialLineCount + m_iCurrentPageLineStart);

//if (m_iCurrentPageLineOffset < 0)
//{

//   return;

//}

//m_iImpactOffset = m_iaLineStart[m_iCurrentPageLineStart];

//strsize iProperBeg = m_iaLineStart[m_iCurrentPageLineEnd - 1];

//strsize iLen = m_iaLineLength[m_iCurrentPageLineEnd - 1];

//m_iImpactSize = iProperBeg + iLen - m_iImpactOffset;

//index iLineStart;

//index iLineEnd;

//index iImpactOffset;

//index iImpactSize;

//if (iLineUpdate < 0)
//{

//   iLineStart = m_iCurrentPageLineStart;

//   iLineEnd = m_iCurrentPageLineEnd;

//   iImpactOffset = m_iImpactOffset;

//   iImpactSize = m_iImpactSize;

//}
//else
//{

//   iLineStart = iLineUpdate;

//   iLineEnd = iLineStart + 1;

//   iImpactOffset = m_iaLineStart[iLineStart];

//   iProperBeg = m_iaLineStart[iLineEnd - 1];

//   iLen = m_iaLineLength[iLineEnd - 1];

//   iImpactSize = iProperBeg + iLen - iImpactOffset;

//}

//string strLine;

//memory mem;

//mem.set_size(iImpactSize + 1);

//strsize iRead;

//{

//   m_ptree->m_peditfile->seek(iImpactOffset, ::e_seek_set);

//   iRead = m_ptree->m_peditfile->read(mem.get_data(), iImpactSize);

//   if (iRead < iImpactSize)
//   {

//      TRACE("ops1");

//      iImpactSize = iRead;

//   }

//   mem.get_data()[iImpactSize] = 0;

//}

//strsize iPos = 0;

////      strsize iLen;

//strsize iStrLen;

////m_plinea->lines.set_size(m_iCurrentPageLineEnd - m_iCurrentPageLineStart);
//m_straLines.set_size(m_iCurrentPageLineEnd - m_iCurrentPageLineStart);

//i = 0;

//iLine = iLineStart;

//auto iLineLength = m_iaLineLength.get_size();

//m_daExtent.set_size(iLineLength);

//for (; iLine < iLineEnd; i++, iLine++)
//{

//   iLen = m_iaLineLength[iLine];

//   iStrLen = maximum(0, iLen - (m_iaLineFlags[iLine] & e_line_end_length));

//   if (iPos + iStrLen > m_iImpactSize)
//   {

//      TRACE("ops3");

//      iStrLen = iImpactSize - iPos;

//      if (iStrLen <= 0)
//      {

//         TRACE("ops4");

//         break;

//      }

//   }

//   string strLine = string((const char *)&mem.get_data()[iPos], iStrLen);

//   //if (strLine != m_plinea->lines[i])
//   if (strLine != m_straLines[i])
//   {

//      //m_plinea->lines[i] = strLine;
//      m_straLines[i] = strLine;

//      m_daExtent[i + iLineStart].set_size(0);

//   }
//   else
//   {

//      //TRACE("optstr");

//   }

//   iPos += iLen;

//   if (iPos > iImpactSize)
//   {

//      TRACE("ops2");

//      break;

//   }

//}

//m_dy = pointOffset.y;

////::colorertake5::base_editor * pcolorer = colorertake5();

////if (pcolorer != nullptr)
////{

////   pcolorer->visibleTextEvent(m_iCurrentPageLineStart, m_iLineCount);

////}

////string_array & straLines = m_plinea->lines;

//string_array & straLines = m_straLines;

//if (iLineUpdate < 0)
//{

//   //m_sizeTotal.cx = 0;

//}

      size_f64 size;

      string strLineGraphics;

      strsize_array iaTab;

      strsize iTab;

      strsize iAddUp;

      for (i32 i = 0; i < m_straLines.get_size(); i++)
      {

         string strLine = m_straLines[i];

         iTab = -1;

         iaTab.erase_all();

         strLineGraphics = strLine;

         replace_tab(0, strLineGraphics, m_iTabWidth, &iaTab);

         const char * pszStart = strLine;

         const char * psz = pszStart;

         strsize iLen = 0;

         iAddUp = 0;

         strsize iPos = 0;

         const char * pszNext = pszStart;

         double_array & daExtent = m_daExtent[m_iCurrentPageLineStart + i];

         if (daExtent.get_size() <= 0)
         {

            daExtent.set_size(strLine.get_length() + 1);

            while (::has_char(pszNext))
            {

               pszNext = ::str().next(psz);

               iLen = pszNext - psz;

               if (*psz == '\t')
               {

                  iTab++;

                  iAddUp += iaTab[iTab] - 1;

               }

               size = pgraphics->get_text_extent(strLineGraphics, strLineGraphics.get_length(), pszNext - pszStart + iAddUp);

               for (int j = 0; j < iLen; j++)
               {

                  daExtent[(::index)(psz - pszStart + j)] = size.cx;

               }

               psz = pszNext;

            }

            if (strLineGraphics.has_char())
            {

               size = pgraphics->get_text_extent(strLineGraphics, strLineGraphics.get_length());

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

      //   m_sizeTotal.cy = (((i32)m_iaLineLength.get_count() + (m_bMultiLine ? maximum(5, m_iLineCount) : 0)) * m_iLineHeight);

      //   const ::size_i32 & sizePage;

      //   sizePage = rectangleClient.size();

      //   if (m_sizeTotal.cy < sizePage.cy)
      //   {

      //      sizePage.cy = m_sizeTotal.cy;

      //   }

      //}

      //on_change_impact_size();

      //m_bCalcLayoutHintNoTextChange = false;

   }


   index plain_edit::plain_edit_sel_to_line(::draw2d::graphics_pointer & pgraphics, strsize iSel)
   {

      synchronous_lock synchronouslock(mutex());

      strsize i1;

      strsize i2 = 0;

      index iLine = 0;

      for (; iLine < m_iaLineLength.get_size(); iLine++)
      {

         i1 = i2;

         i2 = i1 + m_iaLineLength[iLine];

         if (iSel >= i1 && iSel < i2)
         {

            return iLine;

         }

      }

      return m_iaLineLength.get_upper_bound();

   }


   index plain_edit::plain_edit_char_to_line(::draw2d::graphics_pointer & pgraphics, strsize iChar)
   {

      synchronous_lock synchronouslock(mutex());

      for (index iLine = 0; iLine < m_iaLineStart.get_size(); iLine++)
      {

         if (iChar >= m_iaLineStart[iLine] && iChar < m_iaLineStart[iLine] + m_iaLineLength[iLine])
         {

            return iLine;

         }

      }

      return m_iaLineStart.get_count();

   }


   bool plain_edit::plain_edit_caret_rect(::draw2d::graphics_pointer & pgraphics, RECTANGLE_I32 * lprect, strsize iSel)
   {

      int x = 0;

      ::index iLine = plain_edit_sel_to_line_x(pgraphics, iSel, x);

      if (!plain_edit_line_range(pgraphics, lprect, iLine))
      {

         return false;

      }

      lprect->left = x;

      lprect->right = x + 1;

      return true;

   }


   bool plain_edit::plain_edit_index_range(::draw2d::graphics_pointer & pgraphics, RECTANGLE_I32 * lprect, strsize iSel)
   {

      index iLine = plain_edit_char_to_line(pgraphics, iSel);

      return plain_edit_line_range(pgraphics, lprect, iLine);

   }


   bool plain_edit::plain_edit_line_range(::draw2d::graphics_pointer & pgraphics, RECTANGLE_I32 * lprect, ::index iLine)
   {

      if (iLine < 0)
      {

         return false;

      }

      lprect->top = (::i32)(iLine * m_dItemHeight);

      lprect->bottom = (::i32)(lprect->top + m_dItemHeight);

      return true;

   }


   double plain_edit::plain_edit_get_line_extent(::draw2d::graphics_pointer & pgraphics, index iLine, strsize iChar)
   {

      if (iLine < 0 || iChar < 0)
      {

         return 0;

      }

      //synchronous_lock synchronouslock(mutex());

      if (iLine >= m_iaLineLength.get_size())
      {

         return 0;

      }

      if (iChar > m_iaLineLength[iLine])
      {

         return 0;

      }

      if (iLine < m_daExtent.get_size())
      {

         if (iChar == 0)
         {

            return 0;

         }
         else if (iChar - 1 < m_daExtent[iLine].get_size())
         {

            return m_daExtent[iLine][iChar - 1];

         }

      }

      pgraphics->set_font(this, ::e_element_none);

      pgraphics->set_text_rendering_hint(::write_text::e_rendering_anti_alias);

      string strLine = plain_edit_get_expanded_line(pgraphics, iLine, { &iChar });

      size_f64 size = pgraphics->get_text_extent(strLine, (i32)strLine.length(), (i32)iChar);

      return size.cx;


   }


   index plain_edit::plain_edit_sel_to_line_x(::draw2d::graphics_pointer & pgraphics, strsize iSel, i32 & x)
   {

      //synchronous_lock synchronouslock(mutex());

      ::rectangle_i32 rectangleClient;

      GetFocusRect(rectangleClient);

      strsize i1;

      strsize i2 = 0;

      for (index iLine = 0; iLine < m_iaLineLength.get_size(); iLine++)
      {

         i1 = i2;

         i2 = i1 + m_iaLineLength[iLine];

         if (iSel <= i2)
         {

            strsize iRel = iSel - i1;

            x = (i32)plain_edit_get_line_extent(pgraphics, iLine, iRel);

            return iLine;

         }

      }

      x = rectangleClient.left;

      return m_iaLineLength.get_upper_bound();

   }


   strsize plain_edit::plain_edit_line_column_to_sel(::draw2d::graphics_pointer & pgraphics, index iLine, index iColumn)
   {

      synchronous_lock synchronouslock(mutex());

      while (iLine < 0)
      {

         plain_edit_one_line_up(pgraphics);

         if (m_iImpactOffset == 0)
         {

            iLine = 0;

            break;

         }

         iLine++;

      }

      //      string_array & straLines = m_plinea->lines;
      string_array & straLines = m_straLines;

      if (iLine >= straLines.get_size())
      {

         return 0;

      }

      strsize iOffset = 0;

      for (i32 i = 0; i < iLine; i++)
      {

         iOffset += m_iaLineLength[i];

      }

      string_array stra;

      string strLine;

      stra.erase_all();

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

      return m_iImpactOffset + iOffset + iColumn;

   }


   strsize plain_edit::plain_edit_line_x_to_sel(::draw2d::graphics_pointer & pgraphics, index iLine, i32 x)
   {

      synchronous_lock synchronouslock(mutex());

      __defer_construct(pgraphics);

      pgraphics->set_font(this, ::e_element_none);

      pgraphics->set_text_rendering_hint(::write_text::e_rendering_anti_alias);

      strsize iChar = plain_edit_line_char_hit_test(pgraphics, x, iLine);

      return iChar;

   }


   index plain_edit::plain_edit_sel_to_column_x(::draw2d::graphics_pointer & pgraphics, strsize iSel, i32 & x)
   {

      synchronous_lock synchronouslock(mutex());

      ::rectangle_i32 rectangleClient;

      GetFocusRect(rectangleClient);

      strsize i1;

      strsize i2 = 0;

      for (index iLine = 0; iLine < m_iaLineLength.get_size(); iLine++)
      {

         i1 = i2;

         i2 = i1 + m_iaLineLength[iLine];

         if (iSel >= i1 && (iSel < i2
            || (iLine == m_iaLineLength.get_upper_bound() && iSel <= i2)))
         {

            strsize iRel = iSel - i1;

            int xCharacter;

            xCharacter = (int)(plain_edit_get_line_extent(pgraphics, iLine, iRel));

            xCharacter = rectangleClient.left + xCharacter;

            x = xCharacter;

            return iRel;

         }

      }

      return -1;

   }


   index plain_edit::plain_edit_sel_to_column(::draw2d::graphics_pointer & pgraphics, strsize iSel)
   {

      synchronous_lock synchronouslock(mutex());

      //string_array & straLines = m_plinea->lines;

      strsize i1;

      strsize i2 = 0;

      for (index i = 0; i < m_iaLineLength.get_size(); i++)
      {

         i1 = i2;

         i2 = i1 + m_iaLineLength[i];

         if (iSel >= i1 && iSel < i2)
         {

            return iSel - i1;

         }

      }

      return -1;

   }


   strsize plain_edit::plain_edit_char_hit_test(::draw2d::graphics_pointer & pgraphics, const ::point_i32 & pointParam)
   {

      ::point_i32 point(pointParam);

      ::rectangle_i32 rectangleClient;

      GetFocusRect(rectangleClient);

      point.y -= rectangleClient.top;

      auto pointOffset = get_context_offset();

      if (m_dLineHeight > 0)
      {

         int iVerticalOffsetModule = (int)fmod(pointOffset.y, m_dLineHeight);

         if (iVerticalOffsetModule > 0)
         {

            point.y += iVerticalOffsetModule;

         }

      }

      double dLineHeight;

      double dy = 0;

      bool bFound = false;

      dLineHeight = m_dLineHeight;

      strsize iOffset = 0;

      string_array stra;

      index iLine;

      for (iLine = m_iCurrentPageLineStart; iLine < m_iCurrentPageLineEnd; iLine++)
      {

         if (point.y < dy + dLineHeight)
         {

            bFound = true;

            break;

         }

         dy += dLineHeight;

         iOffset += m_iaLineLength[iLine];

      }

      if (!bFound)
      {

         if (iLine > m_iCurrentPageLineStart)
         {

            iLine--;

         }

      }

      return plain_edit_line_char_hit_test(pgraphics, point.x, iLine);

   }


   strsize plain_edit::plain_edit_line_char_hit_test(::draw2d::graphics_pointer & pgraphics, i32 px, index iLine)
   {

      synchronous_lock synchronouslock(mutex());

      ::rectangle_i32 rectangleClient;

      GetFocusRect(rectangleClient);

      auto pointOffset = get_context_offset();

      px -= (rectangleClient.left - pointOffset.x);


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

      strsize iSel = 0;

      string strExtent;

      for (;;)
      {

         pszPrevious = pszEnd;

         ::str().increment(pszEnd);

         if (pszEnd == nullptr)
            break;

         lim1 = lim2;

         strExtent = string(psz, pszEnd - psz);

         replace_tab(0, strExtent, m_iTabWidth);

         int x;

         x = (int)(plain_edit_get_line_extent(pgraphics, iLine, strExtent.length()));

         lim2 = x;

         lim = lim2;

         int iMid = (lim2 - lim1) * 3 / 4;

         if (px >= lim1 && px <= lim1 + iMid)
         {

            iSel = m_iaLineStart[iLine] + (pszPrevious - psz);

            goto end;

         }
         else if (px >= lim1 + iMid && px <= lim2)
         {

            iSel = m_iaLineStart[iLine] + (pszEnd - psz);

            goto end;

         }

         if (pszEnd[0] == '\0')
         {

            break;

         }

      }

      if (iLine < m_iaLineStart.get_count()
         && iLine < m_iaLineLength.get_count()
         && iLine < m_iaLineFlags.get_count())
      {

         iSel = m_iaLineStart[iLine] + (m_iaLineLength[iLine] - (m_iaLineFlags[iLine] & e_line_end_length));

      }

   end:

      if (iSel > _001GetTextLength())
      {

         iSel = _001GetTextLength();

      }

      return iSel;

   }



   void plain_edit::_001GetImpactSel(strsize & iSelBeg, strsize & iSelEnd) const
   {

      synchronous_lock synchronouslock(mutex());

      _001_get_impact_sel(iSelBeg, iSelEnd);

   }



   void plain_edit::_001_get_impact_sel(strsize & iSelBeg, strsize & iSelEnd) const
   {

      if (m_ptree == nullptr)
      {

         iSelBeg = 0;

         iSelEnd = 0;

      }
      else
      {

         iSelBeg = m_ptree->m_iSelBeg - m_iImpactOffset;

         iSelEnd = m_ptree->m_iSelEnd - m_iImpactOffset;

         if (iSelBeg < 0)
         {

            iSelBeg = 0;

         }
         else if (::comparison::gt(iSelBeg, m_ptree->m_peditfile->get_length()))
         {

            iSelBeg = (strsize)(m_ptree->m_peditfile->get_length());

         }

         if (iSelEnd < 0)
         {

            iSelEnd = 0;

         }
         else if (::comparison::gt(iSelEnd, m_ptree->m_peditfile->get_length()))
         {

            iSelEnd = (strsize)(m_ptree->m_peditfile->get_length());

         }

      }

   }


   void plain_edit::_001GetSel(strsize & iBeg, strsize & iEnd) const
   {

      synchronous_lock synchronouslock(mutex());

      iBeg = m_ptree->m_iSelBeg;

      iEnd = m_ptree->m_iSelEnd;

   }


   void plain_edit::_001GetSel(strsize & iSelStart, strsize & iSelEnd, strsize & iComposingStart, strsize & iComposingEnd) const
   {

      synchronous_lock synchronouslock(mutex());

      iSelStart = m_ptree->m_iSelBeg;

      iSelEnd = m_ptree->m_iSelEnd;

      if (m_pitemComposing)
      {

         iComposingStart = (strsize)m_pitemComposing->m_position;

         iComposingEnd = (strsize)(m_pitemComposing->m_position + m_pitemComposing->get_extent());

      }
      else
      {

         iComposingStart = iSelStart;

         iComposingEnd = iSelEnd;

      }

   }


   void plain_edit::FileSave()
   {

      synchronous_lock synchronouslock(mutex());

      m_ptree->m_peditfile->flush();

   }


   void plain_edit::plain_edit_on_file_update(::draw2d::graphics_pointer & pgraphics)
   {

      m_bGetTextNeedUpdate = true;

      plain_edit_create_line_index(pgraphics);

      m_dy = -1;

   }


   void plain_edit::plain_edit_create_line_index(::draw2d::graphics_pointer & pgraphics)
   {

      synchronous_lock synchronouslock(mutex());

      memory m;

      m.set_size(1024 * 1024);

      char * buf = (char *)m.get_data();

      memsize uRead;

      char * psz;


      m_ptree->m_peditfile->seek(0, ::e_seek_set);

      if (m_sizeTotal.cx <= 0)
      {

         m_sizeTotal.cx = 200;

      }

      i32 iLineSize = 0;

      m_iaLineLength.erase_all();

      m_iaLineFlags.erase_all();

      memsize uiPos;

      int iLastR = 0;

      while ((uRead = m_ptree->m_peditfile->read(buf, m.get_size())) > 0)
      {

         uiPos = 0;

         psz = buf;

         while (uiPos < uRead)
         {

            if (*psz == '\r')
            {

               if (iLastR)
               {

                  iLineSize++;

                  m_iaLineLength.add(iLineSize);

                  m_iaLineFlags.add(e_line_end_r);

                  iLineSize = 0;

               }

               iLastR = 1;

            }
            else if (*psz == '\n')
            {

               if (iLastR)
               {

                  iLineSize += 2;

                  m_iaLineLength.add(iLineSize);

                  m_iaLineFlags.add(e_line_end_r_n);

                  iLineSize = 0;

               }
               else
               {

                  iLineSize++;

                  m_iaLineLength.add(iLineSize);

                  m_iaLineFlags.add(e_line_end_n);

                  iLineSize = 0;

               }

               iLastR = 0;

            }
            else
            {

               if (iLastR)
               {

                  iLineSize++;

                  m_iaLineLength.add(iLineSize);

                  m_iaLineFlags.add(e_line_end_r);

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

         m_iaLineLength.add(iLineSize);

         m_iaLineFlags.add(e_line_end_r);

         iLineSize = 0;

      }

      m_iaLineLength.add(iLineSize);

      m_iaLineFlags.add(e_line_end_eof);

      ::count iAcc = 0;

      ::count iLineCount = m_iaLineLength.get_size();

      m_iaLineStart.set_size(iLineCount);

      for (index iLine = 0; iLine < iLineCount; iLine++)
      {

         m_iaLineStart[iLine] = iAcc;

         iAcc += m_iaLineLength[iLine];

      }

   }


   void plain_edit::plain_edit_update_line_index(::draw2d::graphics_pointer & pgraphics, index iLine)
   {

      synchronous_lock synchronouslock(mutex());

      memory m;

      strsize iOffset = 0;

      for (index i = 0; i < iLine; i++)
      {

         iOffset += m_iaLineLength[i];

      }

      m.set_size(1024);

      char * buf = (char *)m.get_data();

      memsize uRead;

      char * psz;

      m_ptree->m_peditfile->seek(iOffset, ::e_seek_set);

      if (m_sizeTotal.cx <= 0)
      {

         m_sizeTotal.cx = 200;

      }

      i32 iLineSize = 0;

      memsize uiPos;

      int iLastR = 0;

      bool bSet = false;

      while ((uRead = m_ptree->m_peditfile->read(buf, m.get_size())) > 0)
      {

         uiPos = 0;

         psz = buf;


         while (uiPos < uRead)
         {

            if (*psz == '\r')
            {

               if (iLastR)
               {

                  iLineSize++;

                  m_iaLineLength[iLine] = iLineSize;

                  m_iaLineFlags[iLine] = e_line_end_r;

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

                  m_iaLineLength[iLine] = iLineSize;

                  m_iaLineFlags[iLine] = e_line_end_r_n;

                  iLastR = 0;

                  bSet = true;

                  goto finished_update;

               }
               else
               {

                  iLineSize++;

                  m_iaLineLength[iLine] = iLineSize;

                  m_iaLineFlags[iLine] = e_line_end_n;

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

                  m_iaLineLength[iLine] = iLineSize;

                  m_iaLineFlags[iLine] = e_line_end_r;

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

         m_iaLineLength[iLine] = iLineSize;

         m_iaLineFlags[iLine] = e_line_end_r;

         bSet = true;

         goto finished_update;

      }

   finished_update:

      if (!bSet)
      {

         m_iaLineLength[iLine] = iLineSize;

         m_iaLineFlags[iLine] = e_line_end_eof;


      }

      ::count iLineCount = m_iaLineLength.get_size();

      for (; iLine < iLineCount; iLine++)
      {

         m_iaLineStart[iLine] = iOffset;

         iOffset += m_iaLineLength[iLine];

      }

   }


   void plain_edit::_001OnUniChar(::message::message * pmessage)
   {

      //      __pointer(::user::message) pusermessage(pmessage);
      //
      //      if (::str::ch().is_legal_uni_index(pusermessage->m_wparam))
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
      //            u32[0] = pusermessage->m_wparam;
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


   void plain_edit::plain_edit_on_delete_surrounding_text(::draw2d::graphics_pointer & pgraphics, strsize beforeLength, strsize afterLength)
   {

      synchronous_lock synchronouslock(mutex());

      bool bFullUpdate = false;

      index iLineUpdate = -1;

      if (!m_bReadOnly)
      {

         auto iSelBeg = m_ptree->m_iSelBeg;

         auto iSelEnd = m_ptree->m_iSelEnd;

         if (afterLength > 0 && iSelEnd < m_ptree->m_peditfile->get_length())
         {

            on_before_change_text();

            string str;

            _001GetText(str, iSelEnd, -1);

            const char * pdata = str.c_str();

            const char * psz = pdata;

            for (strsize i = 0; i < afterLength; i++)
            {

               auto pszNew = ::str().next(psz);

               if (::is_empty(pszNew))
               {

                  break;

               }

               psz = pszNew;

            }

            strsize iMultiByteUtf8DeleteCount = psz - pdata;

            auto i1 = iSelEnd;

            auto i2 = i1 + iMultiByteUtf8DeleteCount;

            string strSel;

            _001GetText(strSel, i1, i2);

            bFullUpdate = strSel.find('\n') >= 0 || strSel.find('\r') >= 0;

            if (!bFullUpdate)
            {

               iLineUpdate = plain_edit_sel_to_line(pgraphics, i1);

            }

            m_ptree->m_peditfile->seek(i1, ::e_seek_set);

            m_ptree->m_peditfile->Delete((memsize)(iMultiByteUtf8DeleteCount));

            m_pinsert = nullptr;

            IndexRegisterDelete(i1, iMultiByteUtf8DeleteCount);

            MacroBegin();

            MacroRecord(__new(plain_text_file_command()));

            MacroEnd();

         }

         if (beforeLength > 0 && iSelBeg > 0)
         {

            on_before_change_text();

            string str;

            _001GetText(str, 0, iSelBeg);

            const char * psz = str.c_str() + iSelBeg;

            const char * pdata = psz;

            for (strsize i = 0; i < beforeLength; i++)
            {

               auto pdataNew = ::str().utf8_dec(str.c_str(), pdata);

               if (::is_empty(pdataNew))
               {

                  break;

               }

               pdata = pdataNew;

            }

            strsize iMultiByteUtf8DeleteCount = psz - pdata;

            auto i1 = m_ptree->m_iSelBeg - iMultiByteUtf8DeleteCount;

            auto i2 = i1 + iMultiByteUtf8DeleteCount;

            string strSel;

            _001GetText(strSel, i1, i2);

            bFullUpdate = strSel.find('\n') >= 0 || strSel.find('\r') >= 0;

            if (!bFullUpdate)
            {

               iLineUpdate = plain_edit_sel_to_line(pgraphics, i1);

            }

            m_ptree->m_peditfile->seek(i1, ::e_seek_set);

            m_ptree->m_peditfile->Delete((memsize)(iMultiByteUtf8DeleteCount));

            m_pinsert = nullptr;

            IndexRegisterDelete(i1, iMultiByteUtf8DeleteCount);

            m_ptree->m_iSelBeg = i1;

            m_ptree->m_iSelEnd -= iMultiByteUtf8DeleteCount;

            MacroBegin();

            MacroRecord(__new(plain_text_file_command()));

            MacroEnd();

         }

      }

      plain_edit_update(pgraphics, bFullUpdate, iLineUpdate);

      _set_sel_end(pgraphics, m_ptree->m_iSelEnd);

   }


   void plain_edit::plain_edit_on_delete(::draw2d::graphics_pointer & pgraphics)
   {

      synchronous_lock synchronouslock(mutex());

      bool bFullUpdate = false;

      index iLineUpdate = -1;

      if (!m_bReadOnly)
      {

         strsize i1 = m_ptree->m_iSelBeg;

         strsize i2 = m_ptree->m_iSelEnd;

         if (i1 != i2)
         {

            on_before_change_text();

            auto psetsel = __new(plain_text_set_sel_command);

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

            m_ptree->m_peditfile->seek(i1, ::e_seek_set);

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
         else if (m_ptree->m_iSelEnd < m_ptree->m_peditfile->get_length())
         {

            on_before_change_text();

            char buf[512];

            __memset(buf, 0, sizeof(buf));

            m_ptree->m_peditfile->seek(m_ptree->m_iSelEnd, ::e_seek_set);

            m_ptree->m_peditfile->read(buf, sizeof(buf));

            const char * psz = ::str().next(buf);

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

            m_ptree->m_peditfile->seek(m_ptree->m_iSelEnd, ::e_seek_set);

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

      _set_sel_end(pgraphics, m_ptree->m_iSelEnd);

   }


   void plain_edit::_001DeleteSel()
   {

      bool bFullUpdate = true;

      index iLineUpdate = -1;

      auto psystem = m_psystem->m_paurasystem;

      auto pdraw2d = psystem->draw2d();

      auto pgraphics = pdraw2d->create_memory_graphics(this);

      if (plain_edit_delete_sel(pgraphics, bFullUpdate, iLineUpdate))
      {

         plain_edit_update(pgraphics, bFullUpdate, iLineUpdate);

      }

   }


   bool plain_edit::plain_edit_delete_sel(::draw2d::graphics_pointer & pgraphics, bool & bFullUpdate, index & iLineUpdate)
   {

      synchronous_lock synchronouslock(mutex());

      strsize i1 = m_ptree->m_iSelBeg;

      strsize i2 = m_ptree->m_iSelEnd;

      ::sort::sort_non_negative(i1, i2);

      if (i1 < 0 || i1 > _001GetTextLength())
      {

         i1 = _001GetTextLength();

      }

      if (i2 < 0 || i2 > _001GetTextLength())
      {

         i2 = _001GetTextLength();

      }

      if (i1 >= i2)
      {

         return false;

      }

      on_before_change_text();

      auto psetsel = __new(plain_text_set_sel_command);

      psetsel->m_iPreviousSelBeg = m_ptree->m_iSelBeg;

      psetsel->m_iPreviousSelEnd = m_ptree->m_iSelEnd;

      string strSel;

      _001GetText(strSel, i1, i2);

      bFullUpdate = strSel.find('\n') >= 0 || strSel.find('\r') >= 0;

      if (!bFullUpdate)
      {

         iLineUpdate = plain_edit_sel_to_line(pgraphics, i1);

      }

      m_ptree->m_peditfile->seek(i1, ::e_seek_set);

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


   void plain_edit::_001ReplaceSel(const ::string & pszText)
   {

      bool bFullUpdate = true;

      index iLineUpdate = -1;

      if (_001ReplaceSel(pszText, bFullUpdate, iLineUpdate))
      {

         auto psystem = m_psystem->m_paurasystem;

         auto pdraw2d = psystem->draw2d();

         auto pgraphics = pdraw2d->create_memory_graphics(this);

         plain_edit_update(pgraphics, bFullUpdate, iLineUpdate);

      }

   }


   bool plain_edit::_001ReplaceSel(const ::string & pszText, bool & bFullUpdate, index & iLineUpdate)
   {

      synchronous_lock synchronouslock(mutex());

      strsize i1 = m_ptree->m_iSelBeg;

      strsize i2 = m_ptree->m_iSelEnd;

      ::sort::sort_non_negative(i1, i2);

      if (i1 < 0 || i1 > _001GetTextLength())
      {

         i1 = _001GetTextLength();

      }

      if (i2 < 0 || i2 > _001GetTextLength())
      {

         i2 = _001GetTextLength();

      }

      if (i2 < i1)
      {

         return false;

      }

      on_before_change_text();

      auto psetsel = __new(plain_text_set_sel_command);

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

      m_ptree->m_peditfile->seek(i1, ::e_seek_set);

      if (i2 > i1)
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


   string plain_edit::get_ime_composition() const
   {

      if (!m_pitemComposing)
      {

         return "";

      }

      return ::string((const ansichar *)m_pitemComposing->get_data(), m_pitemComposing->get_extent());

   }


   void plain_edit::_001OnMessageKey(::message::message * pmessage)
   {

      ::draw2d::graphics_pointer pgraphics;

      bool bUpdate = true;

      bool bFullUpdate = false;

      index iLineUpdate = -1;

      {

         INFORMATION("plain_edit::_001OnMessageKey (1)");

         auto pkey = pmessage->m_union.m_pkey;

         string strChar;

         auto psession = get_session();

         INFORMATION("on_message_key_down (1)");

         {

            auto ptopic = create_topic(::id_key_down);

            ptopic->m_puserelement = this;

            ptopic->m_actioncontext.m_pmessage = pmessage;

            ptopic->m_actioncontext = ::e_source_user;

            route(ptopic);

            if (ptopic->m_bRet)
            {

               return;

            }

         }

         INFORMATION("on_message_key_down (2)");

         if (pkey->m_ekey == ::user::e_key_return)
         {

            auto psession = get_session();

            if (psession->is_key_pressed(::user::e_key_control) && psession->is_key_pressed(::user::e_key_alt))
            {

               pkey->m_bRet = false;

               return;

            }

            if ((!m_bMultiLine || m_bSendEnterKey) && get_parent() != nullptr)
            {

               auto ptopic = create_topic(::id_enter_key);

               ptopic->m_puserelement = this;

               ptopic->m_actioncontext = ::e_source_user;

               route(ptopic);

               if (!ptopic->m_bRet && ptopic->m_bOk)
               {

                  on_action("submit");

               }

               pmessage->m_bRet = true;

               return;

            }

         }
         else if (pkey->m_ekey == ::user::e_key_tab)
         {

            auto psession = get_session();

            if (psession->is_key_pressed(::user::e_key_control) && psession->is_key_pressed(::user::e_key_alt))
            {

               pkey->m_bRet = false;

               return;

            }

            if (!m_bMultiLine)
            {

               pkey->previous();

               auto ptopic = create_topic(::id_tab_key);

               ptopic->m_puserelement = this;

               ptopic->m_actioncontext = ::e_source_user;

               route(ptopic);

               if (!ptopic->m_bRet && ptopic->m_bOk)
               {

                  keyboard_set_focus_next();

               }

               pkey->m_bRet = true;

               return;

            }

         }
         else if (pkey->m_ekey == ::user::e_key_alt)
         {

            pkey->m_bRet = false;

            return;

         }
         else if (pkey->m_ekey == ::user::e_key_escape)
         {

            auto ptopic = create_topic(::id_escape);

            ptopic->m_puserelement = this;

            ptopic->m_actioncontext = ::e_source_user;

            route(ptopic);

            if (!ptopic->m_bRet && ptopic->m_bOk)
            {

               on_action("escape");

            }

            pmessage->m_bRet = true;

            return;

         }
         else if (pkey->m_ekey == ::user::e_key_c)
         {

            auto psession = get_session();

            if (psession->is_key_pressed(::user::e_key_control))
            {

               pkey->m_bRet = true;

               clipboard_copy();

               return;

            }

         }
         else if (pkey->m_ekey == ::user::e_key_v ||
            (pkey->m_ekey == ::user::e_key_refer_to_text_member
               && pkey->m_strText.compare_ci("v") == 0))
         {

#ifdef MACOS
            if (psession->is_key_pressed(::user::e_key_command))
#else
            if (psession->is_key_pressed(::user::e_key_control))
#endif
            {

               pkey->m_bRet = true;

               if (is_window_enabled())
               {

                  fork([this]()
                     {

                        clipboard_paste();

                     });


               }

               return;

            }

         }
         else if (pkey->m_ekey == ::user::e_key_x)
         {

            if (psession->is_key_pressed(::user::e_key_control))
            {

               pkey->m_bRet = true;

               clipboard_copy();

               if (is_window_enabled())
               {


                  queue_graphics_call([this](::draw2d::graphics_pointer & pgraphics)
                     {

                        plain_edit_on_delete(pgraphics);

                        set_need_redraw();

                        post_redraw();

                     });

               }

               return;

            }

         }
         else if (pkey->m_ekey == ::user::e_key_s)
         {

            if (psession->is_key_pressed(::user::e_key_control))
            {

               return;

            }

         }
         else if (pkey->m_ekey == ::user::e_key_a)
         {

            if (psession->is_key_pressed(::user::e_key_control))
            {

               _001SetSel(0, _001GetTextLength());

               return;

            }

         }
         else if (pkey->m_ekey == ::user::e_key_z)
         {

            if (psession->is_key_pressed(::user::e_key_control))
            {

               if (is_window_enabled())
               {

                  edit_undo();

               }

               return;

            }

         }
         else if (pkey->m_ekey == ::user::e_key_y)
         {

            if (psession->is_key_pressed(::user::e_key_control))
            {

               if (is_window_enabled())
               {

                  edit_redo();

               }

               return;

            }

         }
         else if (psession->is_key_pressed(::user::e_key_control))
         {

            if (pkey->m_ekey == ::user::e_key_home)
            {

            }
            else if (pkey->m_ekey == ::user::e_key_end)
            {

            }
            else
            {

               return;

            }

         }

         {

            synchronous_lock synchronouslock(mutex());

            bool bControl = psession->is_key_pressed(::user::e_key_control);

            bool bShift = psession->is_key_pressed(::user::e_key_shift);

            if (pkey->m_ekey == ::user::e_key_prior)
            {

               if (is_text_composition_active())
               {

                  return;

               }

               queue_graphics_call([this, bShift](::draw2d::graphics_pointer & pgraphics)
                  {

                     on_reset_focus_start_tick();

                     i32 x;

                     index iLine = plain_edit_sel_to_line_x(pgraphics, m_ptree->m_iSelEnd, x);

                     ::rectangle_i32 rectangleClient;

                     GetFocusRect(rectangleClient);

                     iLine -= (::index)(rectangleClient.height() / m_dLineHeight);

                     if (iLine < 0)
                     {

                        iLine = 0;

                     }

                     m_ptree->m_iSelEnd = plain_edit_line_x_to_sel(pgraphics, iLine, m_iColumnX);

                     if (!bShift)
                     {

                        m_ptree->m_iSelBeg = m_ptree->m_iSelEnd;

                     }

                     _001EnsureVisibleLine(pgraphics, iLine);

                  });

            }
            else if (pkey->m_ekey == ::user::e_key_next)
            {

               if (is_text_composition_active())
               {

                  return;

               }

               queue_graphics_call([this, bShift](::draw2d::graphics_pointer & pgraphics)
                  {

                     on_reset_focus_start_tick();

                     i32 x;

                     index iLine = plain_edit_sel_to_line_x(pgraphics, m_ptree->m_iSelEnd, x);

                     ::rectangle_i32 rectangleClient;

                     GetFocusRect(rectangleClient);

                     iLine += (::index)(rectangleClient.height() / m_dLineHeight);

                     if (iLine >= m_iaLineStart.get_size())
                     {

                        iLine = m_iaLineStart.get_upper_bound();

                     }
                     m_ptree->m_iSelEnd = plain_edit_line_x_to_sel(pgraphics, iLine, m_iColumnX);

                     if (!bShift)
                     {

                        m_ptree->m_iSelBeg = m_ptree->m_iSelEnd;

                     }

                     _001EnsureVisibleLine(pgraphics, iLine);

                  });

            }
            else if (pkey->m_ekey == ::user::e_key_back)
            {

               INFORMATION("plain_edit::on_message_character (key_back)");

               if (is_text_composition_active())
               {

#ifdef WINDOWS_DESKTOP

                  //edit_undo();

                  //clear_ime_composition();
                  on_text_composition_done();

#endif

                  //return;

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

                        auto psetsel = __new(plain_text_set_sel_command);

                        psetsel->m_iPreviousSelBeg = m_ptree->m_iSelBeg;

                        psetsel->m_iPreviousSelEnd = m_ptree->m_iSelEnd;

                        char buf[512];

                        __memset(buf, 0, sizeof(buf));

                        strsize iProperBegin = maximum(0, m_ptree->m_iSelEnd - 256);
                        strsize iCur = m_ptree->m_iSelEnd - iProperBegin;
                        m_ptree->m_peditfile->seek(iProperBegin, ::e_seek_set);
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

                           psz = ::str().prior(&buf[iCur], buf);

                           if (psz == nullptr)
                           {

                              psz = maximum((char *)buf, (char *)&buf[iCur - 1]);

                           }

                           iMultiByteUtf8DeleteCount = &buf[iCur] - psz;

                        }

                        index i2 = m_ptree->m_iSelEnd;
                        index i1 = i2 - iMultiByteUtf8DeleteCount;

                        string strSel;

                        _001GetText(strSel, i1, i2);

                        bFullUpdate = strSel.find('\n') >= 0 || strSel.find('\r') >= 0;

                        if (!bFullUpdate)
                        {

                           iLineUpdate = plain_edit_sel_to_line(pgraphics, i1);

                        }

                        m_ptree->m_iSelEnd -= iMultiByteUtf8DeleteCount;
                        m_ptree->m_peditfile->seek(m_ptree->m_iSelEnd, ::e_seek_set);
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

                        _001SetSelEnd(m_ptree->m_iSelEnd);

                     }

                  }

               }

            }
            else if (pkey->m_ekey == ::user::e_key_delete)
            {

               if (is_text_composition_active())
               {

                  return;

               }

               if (is_window_enabled())
               {

                  queue_graphics_call([this](::draw2d::graphics_pointer & pgraphics)
                     {

                        plain_edit_on_delete(pgraphics);

                     });

                  set_need_redraw();

                  post_redraw();

               }

               return;

            }
            else if (pkey->m_ekey == ::user::e_key_up)
            {

               if (is_text_composition_active())
               {

                  return;

               }

               queue_graphics_call([this, bShift](::draw2d::graphics_pointer & pgraphics)
                  {

                     on_reset_focus_start_tick();

                     i32 x;

                     index iLine = plain_edit_sel_to_line_x(pgraphics, m_ptree->m_iSelEnd, x);

                     iLine--;

                     if (iLine < 0)
                     {

                        iLine = 0;

                     }

                     if (m_iColumnX >= 0)
                     {

                        x = m_iColumnX;

                     }

                     m_ptree->m_iSelEnd = plain_edit_line_x_to_sel(pgraphics, iLine, x);

                     if (!bShift)
                     {

                        m_ptree->m_iSelBeg = m_ptree->m_iSelEnd;

                     }

                     _001EnsureVisibleLine(pgraphics, iLine);

                     _set_sel_end(pgraphics, m_ptree->m_iSelEnd);

                  });

            }
            else if (pkey->m_ekey == ::user::e_key_down)
            {

               if (is_text_composition_active())
               {

                  return;

               }

               queue_graphics_call([this, bShift](::draw2d::graphics_pointer & pgraphics)
                  {

                     on_reset_focus_start_tick();

                     i32 x;

                     index iLine = plain_edit_sel_to_line_x(pgraphics, m_ptree->m_iSelEnd, x);

                     iLine++;

                     if (iLine >= m_iaLineStart.get_size())
                     {

                        iLine = m_iaLineStart.get_upper_bound();

                     }

                     if (m_iColumnX >= 0)
                     {

                        x = m_iColumnX;

                     }

                     m_ptree->m_iSelEnd = plain_edit_line_x_to_sel(pgraphics, iLine, x);

                     if (!bShift)
                     {
                        m_ptree->m_iSelBeg = m_ptree->m_iSelEnd;



                     }

                     _001EnsureVisibleLine(pgraphics, iLine);

                     _set_sel_end(pgraphics, m_ptree->m_iSelEnd);

                  });

            }
            else if (pkey->m_ekey == ::user::e_key_right)
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
                  m_ptree->m_peditfile->seek(m_ptree->m_iSelEnd, ::e_seek_set);
                  memsize uRead = m_ptree->m_peditfile->read(buf, 32);
                  if (uRead == 2 &&
                     buf[0] == '\r' &&
                     buf[1] == '\n')
                  {
                     m_ptree->m_iSelEnd += 2;
                  }
                  else
                  {
                     m_ptree->m_iSelEnd += ::str().next(buf) - buf;
                  }
                  _001SetSelEnd(m_ptree->m_iSelEnd);
                  if (!bShift)
                  {
                     m_ptree->m_iSelBeg = m_ptree->m_iSelEnd;
                  }
               }
            }
            else if (pkey->m_ekey == ::user::e_key_left)
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
                     m_ptree->m_peditfile->seek(maximum(0, m_ptree->m_iSelEnd - 32), ::e_seek_set);
                     psz = &buf[minimum(32, m_ptree->m_iSelEnd)];
                     memsize uRead = m_ptree->m_peditfile->read(buf, 64);
                     if (uRead == 2 &&
                        psz[0] == '\r' &&
                        psz[1] == '\n')
                     {
                        m_ptree->m_iSelEnd -= 2;
                     }
                     else
                     {
                        m_ptree->m_iSelEnd -= psz - ::str().prior(psz, buf);
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
            else if (pkey->m_ekey == ::user::e_key_home)
            {

               if (is_text_composition_active())
               {

                  return;

               }

               queue_graphics_call([this, bControl, bShift](::draw2d::graphics_pointer & pgraphics)
                  {

                     on_reset_focus_start_tick();

                     if (bControl)
                     {

                        m_ptree->m_iSelEnd = 0;

                        _001EnsureVisibleLine(pgraphics, 0);

                     }

                     {

                        index iLine = plain_edit_sel_to_line(pgraphics, m_ptree->m_iSelEnd);

                        m_ptree->m_iSelEnd = plain_edit_line_column_to_sel(pgraphics, iLine, 0);

                     }

                     _set_sel_end(pgraphics, m_ptree->m_iSelEnd);

                     if (!bShift)
                     {

                        m_ptree->m_iSelBeg = m_ptree->m_iSelEnd;

                     }

                  });

            }
            else if (pkey->m_ekey == ::user::e_key_end)
            {

               if (is_text_composition_active())
               {

                  return;

               }

               queue_graphics_call([this, bControl, bShift](::draw2d::graphics_pointer & pgraphics)
                  {

                     on_reset_focus_start_tick();

                     ::index iSelEnd = -1;

                     if (bControl)
                     {

                        index iLine = m_iaLineStart.get_upper_bound();

                        m_ptree->m_iSelEnd = plain_edit_line_x_to_sel(pgraphics, iLine, i32(m_iaLineLength[iLine]));

                        _001EnsureVisibleLine(pgraphics, iLine);

                     }
                     else
                     {

                        index iLine = plain_edit_sel_to_line(pgraphics, m_ptree->m_iSelEnd);

                        m_ptree->m_iSelEnd = plain_edit_line_column_to_sel(pgraphics, iLine, -1);

                     }

                     _set_sel_end(pgraphics, m_ptree->m_iSelEnd);

                     if (!bShift)
                     {

                        m_ptree->m_iSelBeg = m_ptree->m_iSelEnd;

                     }

                  });

            }
            else if (pkey->m_ekey == ::user::e_key_escape)
            {

            }
            else if (pkey->m_ekey == ::user::e_key_return)
            {

#ifndef WINDOWS_DESKTOP

               if (m_bMultiLine)
               {

                  insert_text("\n", true, e_source_user);

               }

#endif

            }
            else if (is_window_enabled())
            {

               //#if defined(WINDOWS_DESKTOP) || defined(LINUX) || defined(MACOS) || defined(FREEBSD)
               //
               //               return;
               //
               //#else
               //
               //               on_reset_focus_start_tick();
               //
               //               if (!m_bReadOnly)
               //               {
               //
               //                  if (pkey->m_ekey == ::user::e_key_return)
               //                  {
               //                     // Kill Focus => Kill Key Repeat timer
               //                     //output_error_message("VK_RETURN reached plain_edit");
               //                  }
               //
               //                  string str;
               //                  char ch = 0;
               //                  if (pkey->m_ekey == ::user::e_key_tab)
               //                  {
               //
               //                     if (m_bTabInsertSpaces)
               //                     {
               //
               //                        auto iColumn = plain_edit_sel_to_column(pgraphics, m_ptree->m_iSelEnd);
               //
               //                        str = string(' ', m_iTabWidth - (iColumn % m_iTabWidth));
               //
               //                  }
               //                     else
               //                     {
               //
               //                        str = '\t';
               //
               //                     }
               //
               //               }
               //                  else if (pkey->m_ekey == ::user::e_key_refer_to_text_member)
               //                  {
               //                     str = pkey->m_strText;
               //                     //                     if(bShift)
               //                     //                     {
               //                     //                        str.make_upper();
               //                     //                     }
               //                  }
               //                  else
               //                  {
               //
               //#ifdef WINDOWS_DESKTOP
               //
               //                     return;
               //
               //#endif
               //
               //                     ch = (char)pkey->m_nChar;
               //                     if (ch == '\r')
               //                        ch = '\n';
               //                     i32 iChar = (i32)pkey->m_nChar;
               //                     if (iChar == '\r')
               //                        iChar = '\n';
               //                     if (bShift)
               //                     {
               //                        iChar |= 0x80000000;
               //                     }
               //                     i32 iCode = pkey->m_nFlags & 0xff;
               //                     if (bShift)
               //                     {
               //                        iCode |= 0x80000000;
               //                     }
               //
               //                     if (pkey->m_ekey >= ::user::e_key_a && pkey->m_ekey <= ::user::e_key_z)
               //                     {
               //                        str = (char)((pkey->m_ekey - ::user::e_key_a) + 'a');
               //                        if (psession->is_key_pressed(::user::e_key_shift))
               //                        {
               //                           str.make_upper();
               //                        }
               //                     }
               //                     else if (pkey->m_ekey == ::user::e_key_space)
               //                     {
               //                        str = "";
               //                     }
               //                     else if (pkey->m_ekey == ::user::e_key_comma)
               //                     {
               //                        str = ",";
               //                     }
               //                     else if (pkey->m_ekey == ::user::e_key_1 && psession->is_key_pressed(::user::e_key_shift))
               //                     {
               //                        str = "!";
               //                     }
               //                     else
               //                     {
               //                        //str = "(x)";
               //
               //                        return;
               //
               //                     }
               //
               //                     //str = psession->m_paurasession->()->keyboard()->process_key(pkey);
               //                     //throw ::exception(todo, "keyboard");
               //                  }
               //
               //                  insert_text(str, false, e_source_user);
               //
               //                  bUpdate = false;
               //
               //                  pkey->m_bRet = true;
               //
               //            }
               //
               //#endif

            }


            if ((pkey->m_ekey != ::user::e_key_up && pkey->m_ekey != ::user::e_key_down
               && pkey->m_ekey != ::user::e_key_prior && pkey->m_ekey != ::user::e_key_next))
            {

               queue_graphics_call([this](::draw2d::graphics_pointer & pgraphics)
                  {

                     int iColumnX;

                     auto iColumn = plain_edit_sel_to_column_x(pgraphics, m_ptree->m_iSelEnd, iColumnX);

                     if (iColumn != m_iColumn)
                     {

                        m_iColumn = iColumn;
                        m_iColumnX = iColumnX;

                     }

                  });

            }

         }

      }

      if (bUpdate)
      {

         queue_graphics_call([this, bFullUpdate, iLineUpdate](::draw2d::graphics_pointer & pgraphics)
            {

               plain_edit_update(pgraphics, bFullUpdate, iLineUpdate);

            });

         set_need_redraw();

         post_redraw();

      }

   }


   void plain_edit::on_message_char(::message::message * pmessage)
   {

      INFORMATION("plain_edit::on_message_char (1)");

      auto pkey = pmessage->m_union.m_pkey;

      string str;

      on_reset_focus_start_tick();

      if (!m_bReadOnly)
      {

         if (pkey->m_ekey == ::user::e_key_refer_to_text_member)
         {

            str = pkey->m_strText;

            if (str == "\b")
            {

               // Ignores backspace

               // Should be handled as key message (_001MessageKey)

               return;

            }

            insert_text(str, false, e_source_user);

            pkey->m_bRet = true;

         }

      }

   }


   void plain_edit::get_text_composition_area(::rectangle_i32 & rectangle)
   {

      strsize iBeg;

      strsize iEnd;

      _001GetSel(iBeg, iEnd);

      // i32 x;

      //auto pgraphics = ::draw2d::create_memory_graphics();

      //auto iLine = plain_edit_sel_to_line_x(pgraphics, iEnd, x);

      i32 x = m_iLastSelectionEndX;

      double y = m_iLastSelectionEndLine * m_dLineHeight - get_context_offset().y;

      double y2 = y + m_dLineHeight;

      ::point_i32 point((::i32)x, (::i32)y);

      get_client_rect(rectangle);

      rectangle.left = (::i32)x;

      rectangle.top = (::i32)y;

      rectangle.bottom = (::i32)y2;

      client_to_screen(rectangle);

      get_wnd()->screen_to_client(rectangle);

   }


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

         index i1 = (index)(m_pitemComposing->m_position + m_pitemComposing->get_extent());

         queue_graphics_call([this, i1](::draw2d::graphics_pointer & pgraphics)
            {

               int iLineUpdate = (int)plain_edit_sel_to_line(pgraphics, i1);

               m_ptree->m_iSelEnd = i1;
               m_ptree->m_iSelBeg = m_ptree->m_iSelEnd;
               m_ppropertysetsel->m_iSelEnd = m_ptree->m_iSelEnd;
               m_ppropertysetsel->m_iSelBeg = m_ptree->m_iSelEnd;

               bool bFullUpdate = false;

               plain_edit_update(pgraphics, bFullUpdate, iLineUpdate);

               if (iLineUpdate < 0)
               {

                  iLineUpdate = (int)plain_edit_sel_to_line(pgraphics, m_ptree->m_iSelEnd);

               }

               if (iLineUpdate >= 0)
               {

                  _001EnsureVisibleLine(pgraphics, iLineUpdate + 1);

               }

            });

         set_need_redraw();

         post_redraw();

         string strText;

         _001GetText(strText);

         ::output_debug_string("\nplain_edit::on_text_composition (m_pitemComposing != nullptr) Current Text: " + strText + "\n");

      }
      else
      {

#if defined(LINUX) || defined(MACOS)

         insert_text(strText, false, e_source_user);

#else

         insert_text(strText, true, e_source_user);


#endif

      }

   }


   void plain_edit::on_text_commit(string strText)
   {

      if (m_pitemComposing
         && !strText.contains('\r')
         && !strText.contains('\n'))
      {

         m_ptree->m_peditfile->append_insert_item_data(m_pitemComposing.get(), strText);

         index i1 = (index)(m_pitemComposing->m_position + m_pitemComposing->get_extent());

         queue_graphics_call([this, i1](::draw2d::graphics_pointer & pgraphics)
            {

               int iLineUpdate = (int)plain_edit_sel_to_line(pgraphics, i1);

               m_ptree->m_iSelEnd = i1;
               m_ptree->m_iSelBeg = m_ptree->m_iSelEnd;
               m_ppropertysetsel->m_iSelEnd = m_ptree->m_iSelEnd;
               m_ppropertysetsel->m_iSelBeg = m_ptree->m_iSelEnd;

               bool bFullUpdate = false;

               plain_edit_update(pgraphics, bFullUpdate, iLineUpdate);

               if (iLineUpdate < 0)
               {

                  iLineUpdate = (int)plain_edit_sel_to_line(pgraphics, m_ptree->m_iSelEnd);

               }

               if (iLineUpdate >= 0)
               {

                  _001EnsureVisibleLine(pgraphics, iLineUpdate + 1);

               }

            });

         set_need_redraw();

         post_redraw();

         string strText;

         _001GetText(strText);

         ::output_debug_string("Current Text: " + strText + "\n");

         __release(m_pitemComposing);

      }

   }


   void plain_edit::on_text_composition_done()
   {

      //#ifdef WINDOWS_DESKTOP
      //
      //      text_composition_composite::on_text_composition_done();
      //
      //#endif

      __release(m_pitemComposing);

      set_need_redraw();

      post_redraw();

   }


   void plain_edit::clear_ime_composition()
   {

      __release(m_pitemComposing);

      text_composition_composite::clear_ime_composition();

   }


   bool plain_edit::InputConnectionBeginBatchEdit(bool bSuper)
   {

      synchronous_lock synchronouslock(mutex());

      //MacroBegin();

      m_iInputConnectionBatch++;

      return true;

   }


   bool plain_edit::InputConnectionEndBatchEdit(bool bSuper)
   {

      synchronous_lock synchronouslock(mutex());

      //MacroEnd();

      m_iInputConnectionBatch--;

      if (m_iInputConnectionBatch == 0)
      {

         queue_selection_synchronization();

      }

      return true;

   }


   bool plain_edit::InputConnectionCommitText(const ::string & strText, strsize iNewCursorPosition, bool bSuper)
   {

      InputConnectionSetComposingText(strText, iNewCursorPosition, bSuper);

      InputConnectionFinishComposingText(bSuper);

      return true;

   }


   bool plain_edit::InputConnectionDeleteSurroundingText(strsize iBeforeLength, strsize iAfterLength, bool bSuper)
   {

      queue_graphics_call([this, iBeforeLength, iAfterLength](::draw2d::graphics_pointer & pgraphics)
         {

            plain_edit_on_delete_surrounding_text(pgraphics, iBeforeLength, iAfterLength);

         });

      set_need_redraw();

      post_redraw();

      return true;

   }


   bool plain_edit::InputConnectionSetComposingText(const ::string & strTextParam, strsize iNewCursorPosition, bool bSuper)
   {

      string strText(strTextParam);

      queue_graphics_call([this, strText, iNewCursorPosition](::draw2d::graphics_pointer & pgraphics)
         {

            if (m_ptextcompositionclient)
            {

               m_ptextcompositionclient->set_text_composition_active();

            }

            bool bTextHasNewLine = strText.contains('\r') || strText.contains('\n');

            bool bAlreadyComposing = m_pitemComposing && !bTextHasNewLine;

            if (bAlreadyComposing)
            {

               m_ptree->m_peditfile->change_insert_item_data(m_pitemComposing.get(), strText);

               m_ptree->m_iSelBeg = m_pitemComposing->m_position + m_pitemComposing->get_extent();

               m_ptree->m_iSelEnd = m_ptree->m_iSelBeg;

            }
            else
            {

               plain_edit_insert_text(pgraphics, strText, false);

               if (!m_pitemComposing)
               {

                  __refer(m_pitemComposing, m_pinsert);

               }

            }

            //bool bAlreadyComposing = m_pitemComposing && !bTextHasNewLine;

            strsize i1 = iNewCursorPosition;

            ::index iAfterComposingCursorPosition = -1;

            //if (::is_set(m_pitemComposing))
            //{

            //   string strFull;

            //   _001GetText(strFull);

            //   strsize iOffset = 0;

            //   if (iNewCursorPosition > 0)
            //   {

            //      iAfterComposingCursorPosition = (index)(m_pitemComposing->m_position + m_pitemComposing->get_extent());

            //      if (iNewCursorPosition > 1)
            //      {

            //         wd16string wstrFull(strFull.Mid(iAfterComposingCursorPosition));

            //         iOffset = wd16_to_ansi_len(wstrFull, iNewCursorPosition - 1);

            //      }

            //      iAfterComposingCursorPosition += iOffset;

            //   }
            //   else
            //   {

            //      iAfterComposingCursorPosition = (index)(m_pitemComposing->m_position);

            //      if (iNewCursorPosition < 0)
            //      {

            //         wd16string wstrFull(strFull.Left(iAfterComposingCursorPosition));

            //         iOffset = wd16_to_ansi_len(wstrFull, wstrFull.get_length() + iNewCursorPosition);

            //      }

            //      iAfterComposingCursorPosition -= iOffset;

            //   }

            //   //m_ptree->m_iSelEnd = iAfterComposingPosition;
            //   //m_ptree->m_iSelBeg = iAfterComposingPosition;
            //   //m_ppropertysetsel->m_iSelEnd = iAfterComposingPosition;
            //   //m_ppropertysetsel->m_iSelBeg = iAfterComposingPosition;

            //}
            //else

            iAfterComposingCursorPosition = m_ptree->m_iSelEnd;

            {

               string strFull;

               _001GetText(strFull);

               strsize iOffset = 0;

               if (iNewCursorPosition > 0)
               {

                  if (iNewCursorPosition > 1)
                  {

                     wd16string wstrFull(strFull.Mid(iAfterComposingCursorPosition));

                     iOffset = wd16_to_ansi_len(wstrFull, iNewCursorPosition - 1);

                  }

                  iAfterComposingCursorPosition += iOffset;

               }
               else
               {

                  if (iNewCursorPosition < 0)
                  {

                     wd16string wstrFull(strFull.Left(iAfterComposingCursorPosition));

                     iOffset = wd16_to_ansi_len(wstrFull, wstrFull.get_length() + iNewCursorPosition);

                  }

                  iAfterComposingCursorPosition -= iOffset;

               }


            }

            if (bAlreadyComposing)
            {

               int iLineUpdate = (int)plain_edit_sel_to_line(pgraphics, iAfterComposingCursorPosition);

               bool bFullUpdate = false;

               plain_edit_update(pgraphics, bFullUpdate, iLineUpdate);

               if (iLineUpdate < 0)
               {

                  iLineUpdate = (int)plain_edit_sel_to_line(pgraphics, m_ptree->m_iSelEnd);

               }

               if (iLineUpdate >= 0)
               {

                  _001EnsureVisibleLine(pgraphics, iLineUpdate + 1);

               }

            }

            if (iAfterComposingCursorPosition >= 0)
            {

               _001SetSel(iAfterComposingCursorPosition, iAfterComposingCursorPosition, ::e_source_sync);

            }

            _set_sel_end(pgraphics, m_ptree->m_iSelEnd);

         });

      return true;

   }


   bool plain_edit::InputConnectionSetComposingRegion(strsize iComposingStart, strsize iComposingEnd, bool bSuper)
   {

      queue_graphics_call([this, iComposingStart, iComposingEnd](::draw2d::graphics_pointer& pgraphics)
         {

            strsize iCandidateBeg = iComposingStart;

            strsize iCandidateEnd = iComposingEnd;

            m_ptree->m_peditfile->MacroBegin();

            __release(m_pitemComposing);

            string strText;

            _001GetText(strText);

            __sort(iCandidateBeg, iCandidateEnd);

            wd16string wstrText(strText);

            strsize iStart = wd16_to_ansi_len(wstrText, iCandidateBeg);

            strsize iEnd = wd16_to_ansi_len(wstrText, iCandidateEnd);

            string strComposition(strText.Mid(iStart, iEnd - iStart));

            m_ptree->m_peditfile->seek(iStart, ::e_seek_set);

            m_ptree->m_peditfile->Delete((memsize)(iEnd - iStart));

            IndexRegisterDelete(iStart, iEnd - iStart);

            m_ptree->m_peditfile->seek(iStart, ::e_seek_set);

            auto iLength = strComposition.get_length();

            m_pinsert = m_ptree->m_peditfile->Insert(strComposition, iLength);

            IndexRegisterInsert(iStart, strComposition);

            __refer(m_pitemComposing, m_pinsert);

            m_ptree->m_peditfile->MacroEnd();

            MacroBegin();
            MacroRecord(__new(plain_text_file_command()));
            MacroEnd();

         });

      return true;

   }


   bool plain_edit::InputConnectionSetSelection(strsize iStart, strsize iEnd, bool bSuper)
   {

      string strText;

      _001GetText(strText);

      wd16string wstrText(strText);

      strsize iAnsiBeg = wd16_to_ansi_len(wstrText, iStart);

      strsize iAnsiEnd = wd16_to_ansi_len(wstrText, iEnd);

      auto psetsel = __new(plain_text_set_sel_command);

      psetsel->m_iPreviousSelBeg = m_ptree->m_iSelBeg;

      psetsel->m_iPreviousSelEnd = m_ptree->m_iSelEnd;

      m_ptree->m_iSelBeg = iAnsiBeg;

      m_ptree->m_iSelEnd = iAnsiEnd;

      psetsel->m_iSelBeg = m_ptree->m_iSelBeg;

      psetsel->m_iSelEnd = m_ptree->m_iSelEnd;

      m_ppropertysetsel = psetsel;

      MacroBegin();
      MacroRecord(psetsel);
      MacroEnd();

      return true;

   }


   bool plain_edit::InputConnectionFinishComposingText(bool bSuper)
   {

      queue_graphics_call([this](::draw2d::graphics_pointer& pgraphics)
         {

            __release(m_pitemComposing);

            if (m_ptextcompositionclient)
            {

               m_ptextcompositionclient->set_text_composition_active(false);

            }

            m_pinsert = nullptr;

         });

      return true;

   }


   void plain_edit::queue_selection_synchronization()
   {

      queue_graphics_call([this](::draw2d::graphics_pointer& pgraphics)
         {

            auto pwindowing = windowing();

            auto ptexteditorinterface = pwindowing->get_text_editor_interface();

            if (::is_set(ptexteditorinterface))
            {

               strsize iSelectionStart = 0;

               strsize iSelectionEnd = 0;

               strsize iComposingStart = 0;

               strsize iComposingEnd = 0;

               _001GetSel(iSelectionStart, iSelectionEnd, iComposingStart, iComposingEnd);

               ptexteditorinterface->set_input_method_manager_selection(iSelectionStart, iSelectionEnd, iComposingStart, iComposingEnd);

            }

         });

      set_need_redraw();

      post_redraw();

   }


   void plain_edit::_001OnSysChar(::message::message * pmessage)
   {

      synchronous_lock synchronouslock(mutex());

      auto pkey = pmessage->m_union.m_pkey;

      if (pkey->m_ekey == ::user::e_key_delete)
      {

         if (!m_bReadOnly)
         {
            strsize i1 = m_ptree->m_iSelBeg;
            strsize i2 = m_ptree->m_iSelEnd;
            if (i1 != i2)
            {
               ::sort::sort_non_negative(i1, i2);
               m_ptree->m_peditfile->seek(i1, ::e_seek_set);
               m_ptree->m_peditfile->Delete((memsize)(i2 - i1));

               m_pinsert = nullptr;

               m_ptree->m_iSelEnd = i1;
               m_ptree->m_iSelBeg = m_ptree->m_iSelEnd;
            }
            else if (m_ptree->m_iSelEnd < m_ptree->m_peditfile->get_length())
            {
               char buf[512];
               __memset(buf, 0, sizeof(buf));
               strsize iProperBegin = maximum(0, m_ptree->m_iSelEnd - 256);
               strsize iCur = m_ptree->m_iSelEnd - iProperBegin;
               m_ptree->m_peditfile->seek(iProperBegin, ::e_seek_set);
               m_ptree->m_peditfile->read(buf, sizeof(buf));
               const char * psz = ::str().prior(&buf[iCur], buf);
               strsize iMultiByteUtf8DeleteCount = &buf[iCur] - psz;
               m_ptree->m_peditfile->seek(m_ptree->m_iSelEnd, ::e_seek_set);
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

         if (has_keyboard_focus() && is_window_visible())// && m_durationLastDraw.elapsed() > m_durationCaretPeriod / 8)
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
         // auto m_durationFocusStart = ::duration::now();
         //   m_bCaretOn = !m_bCaretOn;
         //   //set_need_redraw();
         //   set_need_redraw();
         //}
      }
   }


   void plain_edit::plain_edit_one_line_up(::draw2d::graphics_pointer & pgraphics)
   {

      ::point_i32 pointOffset = get_context_offset();

      set_context_offset_y(pgraphics, (int)(pointOffset.y - m_dLineHeight));

      double dHeight = 0.;

      m_iImpactOffset = 0;

      ::count iLineSize;

      ::index i = 0;

      __copy(pointOffset, get_context_offset());

      while (pointOffset.y > dHeight && i < m_iaLineLength.get_size())
      {

         iLineSize = m_iaLineLength[i];

         dHeight += m_dLineHeight;

         m_iImpactOffset += iLineSize;

         i++;

      }

   }

   void plain_edit::IndexRegisterDelete(strsize iSel, strsize iCount)
   {
      __UNREFERENCED_PARAMETER(iSel);
      __UNREFERENCED_PARAMETER(iCount);
      //CreateLineIndex();
      //m_peditor->modifyEvent(0);
      /*   char flag;
         m_iImpactOffset = 0;
         i32 iLineSize;
         ::u32 uRead;
         i32 iPos = 0;
         i32 iLineStart = -1;
         i32 iLineEnd = -1;
         i32 iLineStartRemain = -1;
         i32 iLineEndRemain = -1;
         i32 iLine = 0;
         i32 i = 0;
         while(i < m_iaLineLength.get_size())
         {
         iLineSize = m_iaLineLength[i];
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
         while(i < m_iaLineLength.get_size())
         {
         iLineSize = m_iaLineLength[i];
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
         m_editfileLineIndex.seek(5 * (iLineStart + 1), ::e_seek_set);
         m_editfileLineIndex.Delete(5 * (iLineEnd - iLineStart));
         }
         m_editfileLineIndex.seek(5 * iLineStart, ::e_seek_set);
         iLineSize = iLineStartRemain + iLineEndRemain;
         m_editfileLineIndex.write(&iLineSize, 4);
         m_editfileLineIndex.write(&flag, 1);
         */

   }

   void plain_edit::IndexRegisterInsert(strsize iSel, const ::string & pcszWhat)

   {
      __UNREFERENCED_PARAMETER(iSel);
      __UNREFERENCED_PARAMETER(pcszWhat);

      //CreateLineIndex();
      //m_peditor->modifyEvent(0);
   }


   void plain_edit::plain_edit_on_update(::draw2d::graphics_pointer & pgraphics, const ::action_context & context)
   {

      //printf("xxxxxxxxxx1\n");

      {

         synchronous_lock synchronouslock(mutex());

         //string str;
         //_001GetText(str);

         auto iLen = _001GetTextLength();

         if (m_ptree->m_iSelBeg > iLen)
            m_ptree->m_iSelBeg = (strsize)(iLen);
         else if (m_ptree->m_iSelBeg < 0)
            m_ptree->m_iSelBeg = 0;

         if (m_ptree->m_iSelEnd > iLen)
            m_ptree->m_iSelEnd = (strsize)(iLen);
         else if (m_ptree->m_iSelEnd < 0)
            m_ptree->m_iSelEnd = 0;

         m_bGetTextNeedUpdate = 1;

         plain_edit_create_line_index(pgraphics);

         m_dy = -1;

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
      
      if(m_bSetTextSelectionUpdatePending)
      {
         
         m_bSetTextSelectionUpdatePending = false;
         
         bool bSelectionWasAtEnd = m_bLastSelectionWasAtEnd;
         
         if(bSelectionWasAtEnd)
         {
            
            auto iTextLength = _001GetTextLength();
            
            _001SetSel(iTextLength, iTextLength);
            
         }
         else
         {
            
            ::strsize iSelectionBegin = 0;
            
            ::strsize iSelectionEnd = 0;
            
            iSelectionBegin = plain_edit_line_x_to_sel(pgraphics, m_iLastSelectionBeginLine, m_iLastSelectionBeginX);
            
            iSelectionEnd = plain_edit_line_x_to_sel(pgraphics, m_iLastSelectionEndLine, m_iLastSelectionEndX);

            _001SetSel(iSelectionBegin, iSelectionEnd);
            
         }
         
      }
      
      try
      {
         
         //if (context.is_user_source())
         {

            auto pwindowing = windowing();

            auto ptexteditorinterface = pwindowing->get_text_editor_interface();

            if (::is_set(ptexteditorinterface))
            {

               string strText;

               _001GetText(strText);

               ptexteditorinterface->set_editor_text(strText);
               
               ::strsize iBeg = -1;
               
               ::strsize iEnd = -1;
               
               _001GetSel(iBeg, iEnd);
               
               ptexteditorinterface->set_editor_selection(iBeg, iEnd);

            }

         }

      }
      catch(...)
      {
         
      }

      //printf("xxxxxxxxxx4\n");

      set_need_redraw();

      //printf("xxxxxxxxxx4.1\n");

      post_redraw();

      //printf("xxxxxxxxxx5\n");

   }


   void plain_edit::plain_edit_on_line_update(::draw2d::graphics_pointer & pgraphics, index iLine, const ::action_context & context)
   {

      {

         synchronous_lock synchronouslock(mutex());

         //string str;
         //_001GetText(str);

         auto iLen = _001GetTextLength();

         if (m_ptree->m_iSelBeg > iLen)
            m_ptree->m_iSelBeg = (strsize)(iLen);
         else if (m_ptree->m_iSelBeg < 0)
            m_ptree->m_iSelBeg = 0;

         if (m_ptree->m_iSelEnd > iLen)
            m_ptree->m_iSelEnd = (strsize)(iLen);
         else if (m_ptree->m_iSelEnd < 0)
            m_ptree->m_iSelEnd = 0;

         m_bGetTextNeedUpdate = 1;
         plain_edit_update_line_index(pgraphics, iLine);
         m_dy = -1;

         m_bCalcLayoutHintNoTextChange = false;

         plain_edit_on_calc_layout(pgraphics, iLine);

         //m_peditor->lineCountEvent(m_plinea->lines.get_count());

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
      synchronous_lock synchronouslock(mutex());
      if (m_ptree->m_pgroupcommand == nullptr)
      {
         ASSERT(false);
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
      synchronous_lock synchronouslock(mutex());
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

         synchronous_lock synchronouslock(mutex());

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

      auto psystem = m_psystem->m_paurasystem;

      auto pdraw2d = psystem->draw2d();

      auto pgraphics = pdraw2d->create_memory_graphics(this);

      plain_edit_create_line_index(pgraphics);

      m_bGetTextNeedUpdate = true;

      plain_edit_on_update(pgraphics, ::e_source_user);

      //plain_edit_on_after_change_text(pgraphics, ::e_source_user);

      return true;

   }


   bool plain_edit::edit_redo()
   {

      ::draw2d::graphics_pointer pgraphics;

      {

         synchronous_lock synchronouslock(mutex());

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

      plain_edit_on_update(pgraphics, ::e_source_user);
      //plain_edit_on_after_change_text(pgraphics, ::e_source_user);

      return true;
   }

   bool plain_edit::CanUndo()
   {
      synchronous_lock synchronouslock(mutex());
      return m_ptreeitem != m_ptree->get_base_item();
   }

   bool plain_edit::CanRedo()
   {
      synchronous_lock synchronouslock(mutex());
      return m_ptree->m_iBranch < m_ptreeitem->get_expandable_children_count()
         || m_ptreeitem->get_next() != nullptr;
   }

   ::count plain_edit::GetRedoBranchCount()
   {
      synchronous_lock synchronouslock(mutex());

      return m_ptreeitem->get_expandable_children_count()
         + (m_ptreeitem->get_next() != nullptr ? 1 : 0)
         + (m_ptreeitem->first_child() != nullptr ? 1 : 0);
   }



   void plain_edit::_001SetText(const ::string & strParam, const ::action_context & action_context)
   {
      
      ::strsize iSelBeg = 0;
      
      ::strsize iSelEnd = 0;
      
      _001GetSel(iSelBeg, iSelEnd);
      
      ::strsize iTextLength = _001GetTextLength();
      
      m_bLastSelectionWasAtEnd = (iSelBeg == iSelEnd) && (iSelEnd == iTextLength);
      
      string str(strParam);

      {

         synchronous_lock synchronouslock(mutex());

         if (m_bParseDataPacks)
         {

            m_base64map.erase_all();

            auto psystem = m_psystem->m_paurasystem;

            psystem->_001AddPacks(m_base64map, str);

         }

         if (!m_ptree)
         {

            return;

         }

         if (m_ptree->m_peditfile->get_length() > 0)
         {

            m_ptree->m_peditfile->seek(0, ::e_seek_set);

            m_ptree->m_peditfile->Delete((memsize)m_ptree->m_peditfile->get_length());

         }

         if (str.has_char())
         {

            m_ptree->m_peditfile->seek(0, ::e_seek_set);

            m_ptree->m_peditfile->Insert(str, str.get_length());

         }

      }
      
      m_bSetTextSelectionUpdatePending = true;
      
      queue_graphics_call([this, action_context](::draw2d::graphics_pointer & pgraphics)
      {

         plain_edit_on_update(pgraphics, action_context);

      });

      set_need_redraw();

      post_redraw();

   }


   void plain_edit::keyboard_focus_OnKeyDown(::message::message * pmessage)
   {

      on_message_key_down(pmessage);

   }


   void plain_edit::keyboard_focus_OnKeyUp(::message::message * pmessage)
   {

      on_message_key_up(pmessage);

   }


   void plain_edit::keyboard_focus_OnChar(::message::message * pmessage)
   {

      on_message_character(pmessage);

   }


   void plain_edit::plain_edit_on_after_change_text(::draw2d::graphics_pointer & pgraphics, const ::action_context & actioncontext)
   {

      if (actioncontext.is_user_source())
      {

         if (::is_set(m_propertyText))
         {

            plain_edit_get_text(m_propertyText.m_pproperty->as_string());

            auto papp = get_app();

            papp->on_property_changed(m_propertyText.m_pproperty, actioncontext);

         }

      }

      string strText;

      plain_edit_get_text(strText);

      auto pwindowing = windowing();

      auto ptexteditorinterface = pwindowing->get_text_editor_interface();

      if (::is_set(ptexteditorinterface))
      {

         ptexteditorinterface->set_editor_text(strText);

      }

      if (has_handler())
      {

         auto ptopic = create_topic(::id_after_change_text);

         ptopic->m_puserelement = this;

         ptopic->m_actioncontext = actioncontext;

         route(ptopic);

      }

   }


   void plain_edit::clipboard_copy()
   {

      if (m_bPassword)
      {

         return;

      }

      string str;

      _001GetSelText(str);

      str.replace_with("\r\n", "\r");

      auto pwindow = window();

      auto pcopydesk = pwindow->copydesk();

      pcopydesk->set_plain_text(str);

   }


   bool plain_edit::get_line_color(::color::color & color32, const ::string & strLine)
   {

      return false;

   }


   void plain_edit::clipboard_paste()
   {

      string str;

      auto pwindow = window();

      auto pcopydesk = pwindow->copydesk();

      if (!pcopydesk->get_plain_text(str))
      {

         return;

      }

      insert_text(str, true, e_source_user);

      if (m_bEnterKeyOnPaste)
      {

         auto ptopic = create_topic(::id_enter_key);

         ptopic->m_puserelement = this;

         ptopic->m_actioncontext = ::e_source_paste;

         route(ptopic);

         if (!ptopic->m_bRet && ptopic->m_bOk)
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

      return (::i32)(m_dLineHeight * 3.0);

   }


   void plain_edit::_001OnHScroll(::message::message * pmessage)
   {

      __UNREFERENCED_PARAMETER(pmessage);

   }


   void plain_edit::plain_edit_on_set_text(::draw2d::graphics_pointer & pgraphics, const ::action_context & context)
   {

      m_bCalcLayoutHintNoTextChange = false;

      plain_edit_on_calc_layout(pgraphics);

   }


   bool plain_edit::should_load_full_file()
   {
      return m_bColorerTake5;
   }



   void plain_edit::_009OnChar(::message::message * pmessage)
   {

      __UNREFERENCED_PARAMETER(pmessage);

   }


   //bool plain_edit::create_interaction(::user::interaction * puserinteractionParent, const ::atom & atom)
   //{

   //   if (!::user::interaction::create_interaction(puserinteractionParent, atom))
   //   {

   //      TRACE("Failed to create control");

   //      return false;

   //   }

   //   display(e_display_none);

   //   //m_bMultiLine = pdescriptor->has_function(e_control_function_edit_multi_line);

   //   return true;

   //}


   enum_input_type plain_edit::preferred_input_type() const
   {

      return e_input_type_text;

   }


   bool plain_edit::keyboard_focus_is_focusable() const
   {

      return is_window_visible();

   }


   void plain_edit::on_set_keyboard_focus()
   {

      m_ewindowflag |= e_window_flag_focus;

      SetTimer(100, 50_ms, nullptr);

      if (!m_bCaretVisible)
      {

         m_bCaretVisible = true;

         //#ifdef WINDOWS_DESKTOP
         //
         //         HWND hwnd = get_handle();
         //
         //         ::CreateCaret(hwnd, 0, 1, (int) m_dLineHeight);
         //
         //         ::point_i32 pointCaret = layout().design().origin();
         //
         //         client_to_screen(pointCaret);
         //
         //         ::screen_to_client(hwnd, pointCaret);
         //
         //         ::SetCaretPos(pointCaret.x, pointCaret.y);
         //
         //         ::ShowCaret(hwnd);
         //
         //#endif

      }

#ifdef WINDOWS_DESKTOP

      on_text_composition_message(TEXT_COMPOSITION_MESSAGE_UPDATE_CARET);

#endif

      auto pwindowing = m_puserinteraction->windowing();

      auto ptexteditorinterface = pwindowing->get_text_editor_interface();

      if (::is_set(ptexteditorinterface))
      {

         strsize iBeg = 0;

         strsize iEnd = 0;

         _001GetSel(iBeg, iEnd);

         string strText;

         _001GetText(strText);

         ptexteditorinterface->set_editor_selection(iBeg, iEnd);

         ptexteditorinterface->set_editor_text(strText);

         ptexteditorinterface->show_software_keyboard();

      }


   }


   void plain_edit::on_kill_keyboard_focus()
   {

      //      auto puserinteractionHost = get_host_window();
      //      if (puserinteractionHost)
      //      {
      //
      //
      //         puserinteractionHost->edit_on_kill_focus(this);
      //
      //      }

      KillTimer(100);

      if (m_bCaretVisible)
      {

         m_bCaretVisible = false;

#ifdef WINDOWS_DESKTOP

         ::DestroyCaret();

#endif

      }

      //DestroyImeWindow();

      m_ewindowflag -= e_window_flag_focus;

      auto pwindowing = windowing();

      auto ptexteditorinterface = pwindowing->get_text_editor_interface();

      if (::is_set(ptexteditorinterface))
      {

         ptexteditorinterface->hide_software_keyboard();

      }

      set_need_redraw();

      post_redraw();

   }


   __pointer(::data::item) plain_edit::on_allocate_item()
   {

      return __new(plain_text_command);

   }


   void plain_edit::set_root(plain_text_tree * pdata, bool bOwnData)
   {

      synchronous_lock lockRoot(mutex());

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

      __pointer(::message::command) pcommand(pmessage);

      string str;

      _001GetSelText(str);

      pcommand->enable(str.has_char());

   }


   void plain_edit::_001OnEditCut(::message::message * pmessage)
   {

      __UNREFERENCED_PARAMETER(pmessage);

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

      __pointer(::message::command) pcommand(pmessage);

      string str;

      _001GetSelText(str);

      pcommand->enable(str.has_char());

   }


   void plain_edit::_001OnEditCopy(::message::message * pmessage)
   {

      __UNREFERENCED_PARAMETER(pmessage);

      clipboard_copy();

      pmessage->m_bRet = true;

   }

   void plain_edit::_001OnUpdateEditPaste(::message::message * pmessage)
   {

      __pointer(::message::command) pcommand(pmessage);

      auto pwindow = window();

      auto pcopydesk = pwindow->copydesk();

      pcommand->enable(pcopydesk->has_plain_text());

   }


   void plain_edit::_001OnEditPaste(::message::message * pmessage)
   {

      __UNREFERENCED_PARAMETER(pmessage);

      if (is_window_enabled())
      {

         clipboard_paste();

      }

      pmessage->m_bRet = true;

   }


   ::e_status plain_edit::is_edit_delete_enabled()
   {

      string str;

      _001GetSelText(str);

      if (!str.has_char())
      {

         return ::success_none;

      }

      return ::success;

   }


   bool plain_edit::on_edit_delete(const ::action_context & actioncontext)
   {

      ::draw2d::graphics_pointer pgraphics;

      if (is_window_enabled())
      {

         plain_edit_on_delete(pgraphics);

      }

      return true;

   }


   void plain_edit::on_message_size(::message::message * pmessage)
   {

      __UNREFERENCED_PARAMETER(pmessage);

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

   //   if (nCmdShow != e_display_none)
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


   size_f64 plain_edit::get_total_size()
   {

      return m_sizeTotal;

   }


   ::payload plain_edit::get_payload()
   {

      string str;

      _001GetText(str);

      return str;

   }


   string plain_edit::plain_edit_get_expanded_line(::draw2d::graphics_pointer & pgraphics, index iLine, array < strsize * > intptra)
   {

      string strLine = plain_edit_get_line(pgraphics, iLine);

      replace_tab(0, strLine, m_iTabWidth, intptra);

      return strLine;

   }


   string plain_edit::plain_edit_get_line(::draw2d::graphics_pointer & pgraphics, index iLine)
   {

      synchronous_lock synchronouslock(mutex());

      string strLine;

      if (iLine >= m_iCurrentPageLineStart && iLine < m_iCurrentPageLineEnd)
      {

         //         strLine = m_plinea->lines[iLine - m_iCurrentPageLineStart];
         strLine = m_straLines[iLine - m_iCurrentPageLineStart];

      }
      else if (iLine >= 0
         && iLine < m_iaLineLength.get_count()
         && iLine < m_iaLineFlags.get_count())
      {

         strsize iLineLen = m_iaLineLength[iLine] - (m_iaLineFlags[iLine] & e_line_end_length);

         char * psz = strLine.get_string_buffer(iLineLen);

         m_ptree->m_peditfile->seek(m_iaLineStart[iLine], ::e_seek_set);

         m_ptree->m_peditfile->read(psz, iLineLen);

         strLine.release_string_buffer(iLineLen);

      }

      return strLine;

   }


   void plain_edit::on_before_change_text()
   {

      //if (get_ime_composition().has_char())
      //{

      //   clear_ime_composition();

      //   edit_undo();

      //}

   }


   void plain_edit::insert_text(string strText, bool bForceNewStep, const ::action_context & actioncontext)
   {

      queue_graphics_call([this, strText, bForceNewStep](::draw2d::graphics_pointer & pgraphics)
         {

            plain_edit_insert_text(pgraphics, strText, bForceNewStep);

            if (is_text_composition_active() && !m_pitemComposing)
            {

               __refer(m_pitemComposing, m_pinsert);

            }

         });

      set_need_redraw();

      post_redraw();

   }


   void plain_edit::plain_edit_insert_text(::draw2d::graphics_pointer & pgraphics, string strText, bool bForceNewStep)
   {

      ::output_debug_string("plain_edit::insert_text: \"" + strText.Left(64) + "\" \n");

      synchronous_lock synchronouslock(mutex());

      on_before_change_text();

      auto psystem = m_psystem->m_paurasystem;

      psystem->_001AddPacks(m_base64map, strText);

      if (!m_bMultiLine)
      {

         strText.find_replace("\n", "");

         strText.find_replace("\r", "");

      }

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
         m_ppropertysetsel->m_iSelEnd = m_ptree->m_iSelEnd;
         m_ppropertysetsel->m_iSelBeg = m_ptree->m_iSelEnd;

      }
      else
      {

         auto psetsel = __new(plain_text_set_sel_command);

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

            m_ptree->m_peditfile->seek(i1, ::e_seek_set);

            m_ptree->m_peditfile->Delete((memsize)(i2 - i1));

            m_pinsert = nullptr;

            IndexRegisterDelete(i1, i2 - i1);

         }

         m_ptree->m_iSelEnd = i1;

         m_ptree->m_peditfile->seek(m_ptree->m_iSelEnd, ::e_seek_set);
         m_ptree->m_iSelEnd += strText.get_length();
         m_ptree->m_iSelBeg = m_ptree->m_iSelEnd;
         //m_ptree->m_peditfile->seek(m_ptree->m_iSelBeg, ::e_seek_set);

         auto iLength = strText.get_length();

         m_pinsert = m_ptree->m_peditfile->Insert(strText, iLength);

         IndexRegisterInsert(m_ptree->m_iSelEnd, strText);

         m_ptree->m_peditfile->MacroEnd();

         psetsel->m_iSelBeg = m_ptree->m_iSelBeg;

         psetsel->m_iSelEnd = m_ptree->m_iSelEnd;

         m_ppropertysetsel = psetsel;

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

      int iColumnX = -1;

      auto iColumn = plain_edit_sel_to_column_x(pgraphics, m_ptree->m_iSelEnd, iColumnX);

      m_iColumn = iColumn;
      m_iColumnX = iColumnX;

      if (m_bMultiLine)
      {

         if (iLineUpdate >= 0)
         {

            _001EnsureVisibleLine(pgraphics, iLineUpdate + 1);

         }
         else
         {

            _001EnsureVisibleLine(pgraphics, 0);

         }

      }
      else
      {

         _001EnsureVisibleLine(pgraphics, 0);

      }

      _set_sel_end(pgraphics, m_ptree->m_iSelEnd);

   }


   void plain_edit::plain_edit_update(::draw2d::graphics_pointer & pgraphics, bool bFullUpdate, index iLineUpdate)
   {

      if (!m_bMultiLine)
      {

         if (bFullUpdate || iLineUpdate >= 0)
         {

            plain_edit_on_update(pgraphics, ::e_source_user);

         }

      }
      else if (bFullUpdate)
      {

         plain_edit_on_update(pgraphics, ::e_source_user);

      }
      else if (iLineUpdate >= 0)
      {

         plain_edit_on_line_update(pgraphics, iLineUpdate, ::e_source_user);

      }

   }


   plain_edit_style::plain_edit_style()
   {


   }


   plain_edit_style::~plain_edit_style()
   {


   }



   void plain_edit_style::on_update(::draw2d::graphics_pointer & pgraphics, ::user::style * pstyle, ::user::interaction * puserinteraction)
   {

      m_ppenCaret.release();

      m_pbrushText.release();

      m_pbrushTextCr.release();

      m_pbrushTextSel.release();

      m_pbrushTextEmpty.release();

      puserinteraction->__construct(m_ppenCaret);

      puserinteraction->__construct(m_pbrushText);

      puserinteraction->__construct(m_pbrushTextCr);

      puserinteraction->__construct(m_pbrushTextSel);

      puserinteraction->__construct(m_pbrushTextEmpty);

      auto color = puserinteraction->get_color(pstyle, e_element_text);

      m_ppenCaret->create_solid(1.0, color);

      m_pbrushTextCr->create_solid(color);

      color = puserinteraction->get_color(pstyle, e_element_text, e_state_selected);

      m_pbrushTextSel->create_solid(color);

      color = puserinteraction->get_color(pstyle, e_element_text, e_state_new_input);

      m_pbrushTextEmpty->create_solid(color);

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

            auto psystem = m_psystem->m_paurasystem;

            auto pdraw2d = psystem->draw2d();

            auto pgraphics = pdraw2d->create_memory_graphics(this);

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

