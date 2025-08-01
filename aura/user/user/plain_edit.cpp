#include "framework.h"
#include "plain_edit.h"
#include "scroll_state.h"
#include "style.h"
#include "user.h"
#include "copydesk.h"
#include "interaction_style.h"
#include "text_composition_client.h"
#include "plain_text_tree.h"
#include "plain_edit_style.h"
#include "control_style.h"
#ifdef WINDOWS_DESKTOP
#include "acme/_operating_system.h"
#ifdef ENABLE_TEXT_SERVICES_FRAMEWORK
#include "aura/user/windows_tsf/edit_window.h"
#endif
#endif
#include "acme/constant/id.h"
#include "acme/constant/user_key.h"
#include "acme/constant/message.h"
#include "acme/constant/timer.h"
#include "acme/filesystem/file/memory_file.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "acme/handler/item.h"
#include "acme/handler/topic.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/prototype/string/base64.h"
#include "acme/prototype/string/international.h"
#include "acme/prototype/string/_string.h"
#include "acme/prototype/string/str.h"
#include "aura/user/menu/track_popup.h"
#include "aura/graphics/draw2d/graphics.h"
#include "aura/graphics/draw2d/brush.h"
#include "aura/graphics/draw2d/pen.h"
#include "aura/graphics/draw2d/draw2d.h"
#include "aura/windowing/keyboard.h"
#include "acme/platform/timer.h"
#include "acme/user/user/tool.h"
#include "apex/filesystem/file/edit_file.h"
#include "aura/windowing/text_editor_interface.h"
#include "aura/windowing/windowing.h"
#include "aura/windowing/window.h"
#include "aura/message/user.h"
#include "aura/platform/application.h"
#include "aura/platform/session.h"


#define REDRAW_LOG_LEVEL 2


namespace aura
{


   void system::_001AddPacks(string_to_string & base64map, string & str)
   {

      auto iPack = base64map.get_count();

      character_count iData = -1;

      while (true)
      {

         iData = str.find_index("data:", iData + 1);

         if (iData < 0 || !(iData == 0 || !character_isalnum(str[iData - 1])))
         {

            break;

         }

         character_count iMime = str.find_index(';', iData + 1);

         if (iMime <= iData)
         {

            continue;

         }

         character_count iEncoding1 = str.find_index(',', iMime + 1);

         character_count iEncoding2 = str.find_index(';', iMime + 1);

         character_count iEncoding = minimum_non_negative(iEncoding1, iEncoding2);

         if (iEncoding <= iMime)
         {

            continue;

         }

         string strEncoding = str.substr(iMime + 1, iEncoding - iMime - 1);

         if (strEncoding.case_insensitive_order("base64") == 0)
         {

            auto pbase64 = base64();

            ::collection::index iBase64 = iEncoding + 1;

            for (; iBase64 < str.length(); iBase64++)
            {

               if (!pbase64->is(str[iBase64]))
               {

                  break;

               }

            }

            string strBase64 = str.substr(iEncoding + 1, iBase64 - iEncoding - 1);

            string strPack = "%pack" + ::as_string(iPack + 1) + "%";

            str = str.left(iEncoding + 1) + strPack + str.substr(iBase64);

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


   void plain_edit::plain_edit_common_construct()
   {

#ifdef WINDOWS

      m_eline = e_line_end_r_n;

#else

      m_eline = e_line_end_n;

#endif

      m_econtroltype = e_control_type_edit;

      m_bCaretVisible = false;

      m_iInputConnectionBatch = 0;

      m_bNewFocusSelectAll = false;

      m_iNewFocusSelectAllSelBeg = -1;

      m_iNewFocusSelectAllSelEnd = -1;

      m_iNewFocusSelectAllColumn = -1;

      m_bEnterKeyOnPaste = false;

      //m_pcontrolstyle = ___new plain_edit_internal();

      m_ppropertysetsel = nullptr;

      m_pinsert = nullptr;

      m_bColorerTake5 = false;

      m_straLines.m_countAddUp = 100;

      m_straLines.set_size(10);

      m_daExtent.m_countAddUp = 100;

      m_daExtent.set_size(10);

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

      m_bDefaultParentMouseMessageHandling = true;

      m_pscrolllayoutX->m_scrollstatea[::user::e_layout_sketch].m_bScrollEnable = false;

      m_pscrolllayoutY->m_scrollstatea[::user::e_layout_sketch].m_bScrollEnable = false;

      m_dy = -1;
      m_iImpactOffset = 0;
      m_iImpactSize = 0;
      //m_bLMouseDown = false;
      m_bRMouseDown = false;
      m_timeCaretPeriod = 1_s;

      m_iLastSelectionBeginLine = -1;
      m_iLastSelectionBeginX = -1;
      m_iLastSelectionEndLine = -1;
      m_iLastSelectionEndX = -1;
      m_iColumnX = -1;

   }

   //plain_edit::plain_edit(::particle * pparticle) :
   //   ::object(pparticle),
   //   ::user::interaction(pparticle),
   //   m_pmemorygraphics(e_create)
   //{

   //   plain_edit_common_construct();

   //}


   plain_edit::~plain_edit()
   {

   }


   void plain_edit::set_format(const ::scoped_string & scopedstrFormat)
   {

   }


   void plain_edit::set_callback(callback * pcallback)
   {


   }


   bool plain_edit::is_caret_on() const
   {

      return m_timeFocusStart.on_off(m_timeCaretPeriod);

   }


   bool plain_edit::is_new_focus_select_all() const
   {

      if (m_bNewFocusSelectAll)
      {

         auto timeNow = ::time::now();

         if (timeNow > m_timeNewFocusSelectAll
            && (timeNow - m_timeNewFocusSelectAll) > 300_ms)
         {

            ((plain_edit *)this)->m_bNewFocusSelectAll = false;

         }

      }

      return m_bNewFocusSelectAll;

   }


   bool plain_edit::is_plain_edit_modified() const
   {

      return m_ptree->is_tree_modified();

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
      MESSAGE_LINK(e_message_destroy, pchannel, this, &plain_edit::on_message_destroy);
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
      MESSAGE_LINK(e_message_context_menu, pchannel, this, &::user::plain_edit::on_message_context_menu);

      //MESSAGE_LINK(e_message_set_focus, pchannel, this, &::user::plain_edit::on_message_set_focus);
      //MESSAGE_LINK(e_message_kill_focus, pchannel, this, &::user::plain_edit::on_message_kill_focus);


      MESSAGE_LINK(e_message_scroll_y, pchannel, this, &::user::plain_edit::on_message_scroll_y);
      MESSAGE_LINK(e_message_scroll_x, pchannel, this, &::user::plain_edit::on_message_scroll_x);



      add_command_prober("edit_cut", { this,  &plain_edit::_001OnUpdateEditCut });
      add_command_handler("edit_cut", { this,  &plain_edit::_001OnEditCut });
      add_command_prober("edit_copy", { this,  &plain_edit::_001OnUpdateEditCopy });
      add_command_handler("edit_copy", { this,  &plain_edit::_001OnEditCopy });
      add_command_prober("edit_paste", { this,  &plain_edit::_001OnUpdateEditPaste });
      add_command_handler("edit_paste", { this,  &plain_edit::_001OnEditPaste });
      add_command_prober("edit_delete", { (interaction *)this, &interaction::_001OnUpdateEditDelete });
      add_command_handler("edit_delete", { (interaction *)this, &interaction::_001OnEditDelete });


#ifdef ENABLE_TEXT_SERVICES_FRAMEWORK

      install_edit_window_message_routing(pchannel);

#elif defined(WINDOWS_DESKTOP)

      // install_text_composition_composite_message_routing(pchannel);

#endif

   }


   void plain_edit::OnDraw(::image::image * pimage)
   {

      __UNREFERENCED_PARAMETER(pimage);

   }


   void plain_edit::handle(::topic * ptopic, ::handler_context * phandlercontext)
   {

      if (ptopic->id() == id_current_text_changed)
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

         ::user::interaction::handle(ptopic, phandlercontext);

      }

   }


   void plain_edit::on_message_destroy(::message::message * pmessage)
   {

      m_pmessagekeyLast.release();

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


   //void plain_edit::on_context_offset(::draw2d::graphics_pointer & pgraphics)
   //{

   //   ::user::interaction::on_context_offset(pgraphics);

   //}


   void plain_edit::constrain_context_offset(::double_point & point, ::user::enum_layout elayout)
   {

      ::user::scroll_base::constrain_context_offset(point);
      //{

      //   return false;

      //}

      if (!m_bMultiLine)
      {

         point.y() = 0.;

      }

      ///return true;

   }


   void plain_edit::_001OnNcClip(::draw2d::graphics_pointer & pgraphics)
   {

      ::user::scroll_base::_001OnNcClip(pgraphics);

   }


   void plain_edit::_001OnClip(::draw2d::graphics_pointer & pgraphics)
   {

      ::user::scroll_base::_001OnClip(pgraphics);

   }


   void plain_edit::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      __check_refdbg

         auto pparent = ::user::interaction::get_parent();

      ::string strTypeParent;

      ::string strTypeParentParent;

      ::string strTypeParentParentParent;

      if (::is_set(pparent))
      {

         strTypeParent = ::type(pparent).as_string();

         //         ::string str;
         //
         //         auto r = pparent->rectangle();

         //         str.formatf("%d,%d,%d,%d : %s", r.left(), r.top(), r.width(), r.height(), strTypeParent.c_str());
         //
         //         information() << str;

         auto pparentParent = pparent->get_parent();

         if (::is_set(pparentParent))
         {

            strTypeParentParent = ::type(pparentParent).as_string();

            //            ::string str2;
            //
            //            auto r2 = pparentParent->rectangle();
            //
            //            str2.formatf("%d,%d,%d,%d : %s", r2.left(), r2.top(), r2.width(), r2.height(), strTypeParentParent.c_str());

            //            information() << str2;

            auto pparentParentParent = pparentParent->get_parent();

            if (::is_set(pparentParentParent))
            {

               strTypeParentParentParent = ::type(pparentParentParent).as_string();

               //               ::string str3;
               //
               //               auto r3 = pparentParentParent->rectangle();

               //               str3.formatf("%d,%d,%d,%d : %s", r3.left(), r3.top(), r3.width(), r3.height(), strTypeParentParentParent.c_str());

               //               information() << str3;

            }

         }

      }

      //pgraphics->reset_clip();
      m_timeLastDraw = ::time::now();

      auto timeStart = ::time::now();

      __check_refdbg

         auto pstyle = get_style(pgraphics);

      __check_refdbg

         status < ::color::color > crBk;
      status < ::color::color > crBkSel;
      status < ::color::color > crSel;
      status < ::color::color > color32;

      ::double_rectangle rectangleX = this->rectangle();

      auto rectangleBackground = rectangleX;

      //rectangleBackground.offset(get_context_offset());

      __check_refdbg

         auto crEditBackground = get_color(pstyle, e_element_background);

      __check_refdbg

         pgraphics->fill_rectangle(rectangleBackground, crEditBackground);

      __check_refdbg

         bool bComposing = ::is_set(m_pitemComposing);

      bool bStrongSelection = bComposing || has_keyboard_focus();

      __check_refdbg

         character_count iComposeBeg = -1;

      character_count iComposeEnd = -1;

      if (bComposing)
      {

         __check_refdbg

            iComposeBeg = (character_count)m_pitemComposing->m_position;

         __check_refdbg

            iComposeEnd = (character_count)(m_pitemComposing->m_position + m_pitemComposing->get_extent());

         __check_refdbg

      }

      __check_refdbg

         color32 = get_color(pstyle, e_element_text);

      __check_refdbg

         crBk = get_color(pstyle, e_element_background);

      __check_refdbg

         crSel = get_color(pstyle, e_element_text, e_state_selected);

      __check_refdbg


         crBkSel = get_color(pstyle, e_element_background, e_state_selected);

      __check_refdbg

         status < ::color::color > colorComposeBk;

      __check_refdbg

         colorComposeBk = crBk;
      colorComposeBk.blend(crBkSel, 0.5);
      colorComposeBk.m_uchOpacity = 127;

      __check_refdbg

         pstyle->get(m_pcontrolstyle, pgraphics, this);

      __check_refdbg

         bool bCaretOn = is_caret_on();

      __check_refdbg

         bool bFocus = has_keyboard_focus();

      __check_refdbg

         if (m_ptree == nullptr)
         {

            information() << "Exiting _001OnDraw Prematurely m_ptree == nullptr";

            return;

         }

      auto rectanglePadding = get_padding(pstyle);

      rectangleX.deflate(rectanglePadding);

      double left = rectangleX.left();

      character_count iSelBeg;
      character_count iSelEnd;
      character_count iSelBegOriginal;
      character_count iSelEndOriginal;
      character_count lim = plain_edit_line_x_to_sel(pgraphics, m_iCurrentPageLineStart, 0);

      ::draw2d::pen_pointer & ppenCaret = m_pcontrolstyle->m_ppenCaret;

      ::draw2d::brush_pointer & pbrushText = m_pcontrolstyle->m_pbrushText;

      ::draw2d::brush_pointer & pbrushTextCr = m_pcontrolstyle->m_pbrushTextCr;

      ::draw2d::brush_pointer & pbrushTextSel = m_pcontrolstyle->m_pbrushTextSel;

      //auto pointOffset = get_context_offset();

      //if (m_dLineHeight > 0.)
      //{

      //   int iVerticalOffsetModule = (int) fmod(pointOffset.y(), m_dLineHeight);

      //   if (iVerticalOffsetModule > 0)
      //   {

      //      pgraphics->offset_origin(0, -iVerticalOffsetModule);

      //   }

      //}

      //pgraphics->offset_origin(-pointOffset.x(), 0);

      //double y = rectangleX.top() + m_iCurrentPageLineStart * m_dLineHeight;

      double y = rectangleX.top();

      get_text_selection(iSelBegOriginal, iSelEndOriginal);

      iSelBeg = iSelBegOriginal;

      iSelEnd = iSelEndOriginal;

      character_count iCursor = iSelEndOriginal;

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

      ::collection::index i = 0;

      pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

      string strLineGraphics;

      if (m_textproperty.get_size() == 0)
      {

         if (m_strEmtpyText.has_character())
         {

            pgraphics->set(m_pcontrolstyle->m_pbrushTextEmpty);

            pgraphics->text_out(left, y, m_strEmtpyText);

         }

      }

      if (m_iCurrentPageLineStart >= m_iCurrentPageLineEnd)
      {

#if REDRAW_LOG_LEVEL > 7

         information() << "Exiting _001OnDraw Prematurely m_iCurrentPageLineStart >= m_iCurrentPageLineEnd";

#endif

         return;

      }

      for (::collection::index iLine = m_iCurrentPageLineStart; iLine < m_iCurrentPageLineEnd; i++, iLine++)
      {

         string strLine = straLines[i];

#if defined(LOG_ENABLE_PLAIN_EDIT_LINE)

         if (strLine.has_character())
         {

            auto psz = strLine.c_str();

            informationf("Line %s", psz);

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

            character_count iErrorBeg = -1;

            character_count iErrorEnd = -1;

            character_count iErrorA = 0;

            if (m_errora.get_size() > 0)
            {

               auto timeTimeout = 1_s;

               auto timePeriod = 100_ms;

               if (m_errora[0]->m_tick.elapsed() > timePeriod)
               {

                  if (m_errora[0]->m_tick.elapsed() < (timeTimeout + timePeriod))
                  {

                     iErrorA = (character_count)((m_errora[0]->m_tick.elapsed() - timeTimeout) * 255 / timePeriod);

                  }
                  else
                  {

                     iErrorA = 255;

                  }

                  iErrorBeg = m_errora[0]->m_iStart;
                  iErrorEnd = m_errora[0]->m_iEnd;
                  iErrorBeg -= lim;
                  iErrorEnd -= lim;
                  iErrorBeg = maximum(0, iErrorBeg);
                  iErrorEnd = minimum(iErrorEnd, strLine.length());

               }

            }

            string_array stra;

            character_count iCurLineComposeBeg = iComposeBeg - lim;

            character_count iCurLineComposeEnd = iComposeEnd - lim;

            character_count iCurLineSelBeg = iSelBeg - lim;

            character_count iCurLineSelEnd = iSelEnd - lim;

            character_count iCurLineSelCur = iCursor - lim;

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

               strLine = ::str::block('*', int(strLine.length()));

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

               strLineGraphics = ::str::block('*', int(strLineGraphics.length()));

            }

            //if (bShowSelection)
            {

               if (iCurLineSelEnd > iCurLineSelBeg)
               {

                  ::color::color colorBk(crBkSel);

                  if (!bStrongSelection)
                  {

                     colorBk.set_opacity(colorBk.byte_opacity() / 2);

                  }

                  pgraphics->fill_rectangle(
                     ::double_rectangle_dimension((double)((double)left + x1),
                        (double)y,
                        (double)minimum(x2 - x1, (double)rectangleX.right() - ((double)left + x1)),
                        (double)minimum((double)m_dLineHeight, (double)rectangleX.bottom() - y)),
                     colorBk);

                  pgraphics->set(pbrushTextSel);

               }

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

            if (iCurLineComposeEnd > iCurLineComposeBeg)
            {

               //pgraphics->fill_rectangle(
               //   ::double_rectangle_dimension((double)((double)left + compose1),
               //      (double)y,
               //      (double)minimum(compose2 - compose1, (double)rectangleX.right() - ((double)left + compose1)),
               //      (double)minimum((double)m_dLineHeight, (double)rectangleX.bottom() - y)),
               //   colorComposeBk);

               pgraphics->fill_rectangle(
                  ::double_rectangle_dimension((double)((double)left + compose1),
                     ((double)minimum((double)m_dLineHeight, (double)rectangleX.bottom())) - 1.0,
                     (double)minimum(compose2 - compose1, (double)rectangleX.right() - ((double)left + compose1)),
                     bComposing ? 1.0 : 0.5));

               //pgraphics->set(pbrushTextSel);

            }


            if (iCurLineSelBeg > 0)
            {

               // Draw Normal Text - not selected - before selection
               auto strLeft = strLineGraphics.left(iCurLineSelBeg);
               pgraphics->text_out(left, y, strLeft);

            }

            if (iCurLineSelBeg < strLineGraphics.length())
            {

               // Draw Normal Text - not selected - after selection
               string strRight = strLineGraphics.substr(iCurLineSelEnd);
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
               string strSelected = strLineGraphics.substr(iCurLineSelBeg, iCurLineSelEnd - iCurLineSelBeg);
               pgraphics->text_out(left + x1, y, strSelected);

            }

            if (0 <= iErrorBeg && iErrorBeg <= strExtent1.length())
            {

               double xA = plain_edit_get_line_extent(pgraphics, iLine, iErrorBeg);

               double xB = plain_edit_get_line_extent(pgraphics, iLine, minimum(iErrorEnd, strExtent1.length()));

               auto ppen = __øcreate < ::draw2d::pen >();

               ppen->create_solid(1.0, argb((unsigned char)iErrorA, 255, 0, 0));

               pgraphics->set(ppen);

               pgraphics->draw_error_line((int)xA, (int)m_dLineHeight, (int)xB, 1);

            }

            if (iCurLineSelCur >= 0 && bFocus && bCaretOn && iCurLineSelCur == iCurLineSelBeg)
            {

#ifdef WINDOWS_DESKTOP

               ::int_point point((long)(left + x1), (long)y);

               client_to_screen()(point);

               get_wnd()->screen_to_client()(point);

               ::SetCaretPos(point.x(), point.y());

#endif

               pgraphics->set(ppenCaret);

               pgraphics->line(
                     left + x1, y,
                     left + x1, y + dLineHeight);

            }
            else if (iCurLineSelCur >= 0 && bFocus && bCaretOn && iCurLineSelCur == iCurLineSelEnd)
            {

#ifdef WINDOWS_DESKTOP

               ::int_point point((long)(left + x1), (long)y);

               client_to_screen()(point);

               get_wnd()->screen_to_client()(point);

               ::SetCaretPos(point.x(), point.y());

#endif

               pgraphics->set(ppenCaret);

               pgraphics->line(
                  left + x2, y,
                  left + x2, y + dLineHeight);

            }

         }

         y += m_dLineHeight;

         lim += m_iaLineLength[iLine];

      }

      auto timeElapsed = timeStart.elapsed();

#ifdef VERBOSE_LOG      

      if (timeElapsed > 50_ms)
      {

         information()(e_trace_category_prodevian) << "plain_edit took more than 50ms to draw " << d1.integral_millisecond();

      }

#endif

   }


   void plain_edit::on_message_create(::message::message * pmessage)
   {

      ::pointer<::message::create>pcreate(pmessage);

      auto pwindowing = windowing();

      auto pcursor = pwindowing->get_cursor(e_cursor_text_select);

      set_default_mouse_cursor(pcursor);

      pcreate->previous();

#if !defined(APPLE_IOS) && !defined(__ANDROID__)

      ::pointer<::aura::application>papp = get_app();

      //psession->keyboard(); // trigger keyboard creationg
      papp->defer_create_keyboard();

#endif

      if (!m_ptree)
      {

         set_root(this, true);

         m_ptree->m_pfile = __allocate::memory_file();

         m_ptree->m_peditfile->SetFile(m_ptree->m_pfile);

         m_ptree->m_peditfile->defer_create_synchronization();

         m_ptree->m_iSelBeg = 0;

         m_ptree->m_iSelEnd = 0;

         //m_bGetTextNeedUpdate = true;

         queue_graphics_call([this](::draw2d::graphics_pointer & pgraphics)
            {

               //plain_edit_on_set_text(pgraphics, ::e_source_system);

               plain_edit_on_update(pgraphics, ::e_source_system);

            });

      }


#if !defined(UNIVERSAL_WINDOWS)

      //auto estatus =

      initialize_text_composition_client(this, this);

      //if (!estatus)
      //{

      //   pcreate->failed("plain_edit::initialize_text_composition_client failed.");

      //   return;

      //}

#endif

      //m_linkedpropertyText = fetch_property(id(), true);

      //if (m_linkedpropertyText && !m_linkedpropertyText->is_empty())
      //{

      //   set_text(m_linkedpropertyText->as_string(), ::e_source_initialize);

      //}

      //m_ppropertyText = fetch_property(id(), true);

      //add_change_notification(m_ppropertyText);

      //if(m_ppropertyText && !m_ppropertyText->is_empty())
      //{

      //   set_text(m_ppropertyText->get_string(), ::e_source_initialize);

      //}

      add_handler(this);

   }


   void plain_edit::on_message_context_menu(::message::message * pmessage)
   {


      //      set_need_redraw();

        //    m_bRMouseDown = false;

      //      auto strXml = file()->as_string();
      //      
      //      print_out(strXml);

      if (!m_ptrackpopupContextMenu)
      {


         ::pointer < ::message::context_menu > pcontextmenu = pmessage;

         auto pointCursor = pcontextmenu->GetPoint();

         auto pmenu = user()->menu_from_xml(this, "matter://plain_edit_context_menu.menu");

         m_ptrackpopupContextMenu = __allocate::menu::track_popup(pmenu,
                                                          this,
                                                          this,
                                                                  pointCursor);

         m_ptrackpopupContextMenu->track([this]()
                                         {

                                            m_ptrackpopupContextMenu.release();
         }


         );

      }
      //                                                       )
      //      
      //      application()->track_popup_menu(this, "matter://plain_edit_context_menu.menu", 0, pointCursor);

   }


   void plain_edit::on_message_right_button_down(::message::message * pmessage)
   {

      auto pmouse = pmessage->m_union.m_pmouse;

      ::int_point point = pmouse->m_pointHost;

      host_to_client()(point);

      m_bRMouseDown = true;

      //queue_graphics_call([this, point](::draw2d::graphics_pointer & pgraphics)
      //   {

      //      character_count iHit = plain_edit_char_hit_test(pgraphics, point);

      //      if (iHit <= m_ptree->m_iSelBeg || iHit >= m_ptree->m_iSelEnd)
      //      {

      //         m_ptree->m_iSelBeg = iHit;

      //         m_ptree->m_iSelEnd = iHit;

      //      }

      //   });

      set_need_redraw();

      set_keyboard_focus();

      //

      session()->user()->set_mouse_focus_RButtonDown(this);

      pmouse->m_bRet = true;

      pmouse->m_lresult = 1;

   }


   void plain_edit::on_message_right_button_up(::message::message * pmessage)
   {

      auto pmouse = pmessage->m_union.m_pmouse;

      ::int_point point = pmouse->m_pointHost;

      host_to_client()(point);

      //{

      //   _synchronous_lock synchronouslock(this->synchronization());

      //   character_count iSelStart = -1;

      //   character_count iSelEnd = -1;

      //   _001GetSel(iSelStart, iSelEnd);

      //   if (iSelStart == iSelEnd)
      //   {

      //      set_text_selection(0, get_text_length());

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


   void plain_edit::on_timer(::timer * ptimer)
   {

      interaction::on_timer(ptimer);

      auto etimer = ptimer->m_etimer;

      if (etimer == e_timer_overflow_scrolling_start)
      {

         kill_timer(etimer);

         if (session()->is_key_pressed(::user::e_key_left_button))
         {

            set_timer(e_timer_overflow_scrolling, 300_ms);

         }

      }
      else if (etimer == e_timer_overflow_scrolling)
      {

         if (session()->is_key_pressed(::user::e_key_left_button))
         {

            auto pwindowing = windowing();

            auto pwindow = window();

            auto pointHostCursor = pwindow->m_pointCursor2;

            auto pointCursor = pointHostCursor;

            host_to_raw()(pointCursor);

            ::int_rectangle rectangleRaw;

            rectangleRaw = raw_rectangle();

            if (pointCursor.x() < rectangleRaw.left())
            {

               scroll_left_line();

            }
            else if (pointCursor.x() > rectangleRaw.right())
            {

               scroll_right_line();

            }

            if (pointCursor.y() < rectangleRaw.top())
            {

               scroll_up_line();

            }
            else if (pointCursor.y() > rectangleRaw.bottom())
            {

               scroll_down_line();

            }

            _extend_selection_end(pointHostCursor);

            set_need_redraw();

            post_redraw();

         }
         else
         {

            kill_timer(etimer);

         }

      }
      else if (ptimer->m_etimer == e_timer_caret_flashing)
      {

         //information() << "on_timer e_timer_caret_flashing";

         if (has_keyboard_focus())
         {

            //information() << "Keyboard Focus";

            _001OnKeyboardFocusTimer(ptimer->m_etimer);

         }
         else
         {

            //information() << "No keyboard Focus";

         }

      }
      else if (ptimer->m_uTimer == 500 || ptimer->m_uTimer == 501)
      {

         if (ptimer->m_uTimer == 500)
         {

            kill_timer(500);

            set_timer(501, 300_ms, nullptr);

         }

         _001OnMessageKey(m_pmessagekeyLast);

      }

   }


   status < ::double_rectangle > plain_edit::get_margin(style * pstyle, enum_element eelement, ::user::enum_state estate)
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

      if (pkey->m_ekey == ::user::e_key_return)
      {

         auto psession = session();

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

   //   

   //   bool bShift = psession->is_key_pressed(::user::e_key_shift);

   //   if (key.m_nChar < 256 && isalpha((int)key.m_nChar))
   //   {

   //      if (bShift)
   //      {

   //         key.m_nChar = toupper((int)key.m_nChar);

   //      }
   //      else
   //      {

   //         key.m_nChar = tolower((int)key.m_nChar);

   //      }

   //   }

   //   information() << "key_to_char (1)";

   //   on_message_character(&key);

   //}


   void plain_edit::extend_selection_end(const ::int_point & pointHost)
   {

      auto point = pointHost;

      host_to_client()(point);

      if (m_pointLastCursor == point)
      {

         return;

      }

      _extend_selection_end(pointHost);

   }


   void plain_edit::_extend_selection_end(const ::int_point & pointHost)
   {

      auto point = pointHost;

      host_to_client()(point);

      m_pointLastCursor = point;

      _synchronous_lock synchronouslock(this->synchronization());

      ::int_rectangle rectangleWindow;

      window_rectangle(rectangleWindow);

      if (pointHost.x() < rectangleWindow.left() - 30)
      {

         informationf("test06");

      }

      queue_graphics_call([this, point](::draw2d::graphics_pointer & pgraphics)
         {

            if (m_iNewFocusSelectAllSelBeg >= 0
               || m_iNewFocusSelectAllSelEnd >= 0
               || m_iNewFocusSelectAllColumn >= 0)
            {

               auto iBegNew = m_iNewFocusSelectAllSelBeg;
               auto iEndNew = m_iNewFocusSelectAllSelEnd;
               auto iColumn = m_iNewFocusSelectAllColumn;

               m_iNewFocusSelectAllSelBeg = -1;
               m_iNewFocusSelectAllSelEnd = -1;
               m_iNewFocusSelectAllColumn = -1;

               set_text_selection(iBegNew, iEndNew, ::e_source_sync);

               m_iColumn = iColumn;

            }

            _set_sel_end(pgraphics, plain_edit_char_hit_test(pgraphics, point), e_source_user);

         });

      set_need_redraw();

      post_redraw();

   }


   //character_count plain_edit::get_text_length()
   //{

   //   _synchronous_lock synchronouslock(this->synchronization());

   //   return _001_get_text_length();


   //}


   character_count plain_edit::get_text_length()
   {

      _synchronous_lock synchronouslock(this->synchronization());

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

      return (character_count)peditfile->get_length();

   }


   ::collection::count plain_edit::line_count() const
   {

      return m_iaLineLength.count();

   }


   //void plain_edit::get_text(string & str)
   //{

   //   get_text(str);

   //}


   ::string plain_edit::get_text() const
   {

      if (m_ptree == nullptr)
      {

         return{};

      }

      _synchronous_lock synchronouslock(this->synchronization());

      filesize iSize = m_ptree->m_peditfile->get_length();

      ::string str;

      char * psz = str.get_buffer((character_count)(iSize + 1));

      m_ptree->m_peditfile->seek(0, ::e_seek_set);

      m_ptree->m_peditfile->read(scopedstr, (memsize)iSize);

      psz[(memsize)iSize] = '\0';

      str.release_buffer();

      for (auto & m : m_base64map)
      {

         string strPack = m.element1();

         str.replace_with(m.element2(), strPack);

      }

      return str;

   }


   //void plain_edit::get_selection_text(string & str)
   //{

   //   get_text(str, m_ptree->m_iSelBeg, m_ptree->m_iSelEnd);

   //}


   void plain_edit::get_text(string & str, ::collection::index iBegParam, ::collection::index iEndParam) const
   {

      _synchronous_lock synchronouslock(this->synchronization());

      {

         if (m_ptree == nullptr)
         {

            str.empty();

         }

         //_synchronous_lock synchronouslock(this->synchronization());

         if (iEndParam < 0)
         {

            iEndParam = m_ptree->m_peditfile->get_length();

         }

         filesize iSize = iEndParam - iBegParam;

         //::string str;

         char * psz = str.get_buffer((character_count)(iSize + 1));

         m_ptree->m_peditfile->seek(iBegParam, ::e_seek_set);

         m_ptree->m_peditfile->read(scopedstr, (memsize)iSize);

         psz[(memsize)iSize] = '\0';

         str.release_buffer();

         for (auto & m : m_base64map)
         {

            string strPack = m.element1();

            str.replace_with(m.element2(), strPack);

         }

         //  return str;

      }

      //str = m_textproperty.get_text(iBegParam, iEndParam);

      //::sort_non_negative(iBegParam, iEndParam);

      //filesize iEnd;

      //filesize iBeg;

      //if (iEndParam < 0)
      //{

      //   if (iBegParam < 0)
      //   {

      //      iEnd = (filesize)m_ptree->m_peditfile->get_length();

      //      iBeg = 0;

      //   }
      //   else
      //   {

      //      iBeg = iBegParam;

      //      iEnd = (filesize)m_ptree->m_peditfile->get_length();

      //   }

      //}
      //else
      //{

      //   if (iBegParam < 0)
      //   {

      //      iEnd = iEndParam;

      //      iBeg = 0;

      //   }
      //   else
      //   {

      //      iEnd = iEndParam;

      //      iBeg = iBegParam;

      //   }

      //}

      //if (iEnd < iBeg)
      //{

      //   ::_std::__swap(iEnd, iBeg);

      //}

      //filesize iSize = iEnd - iBeg;

      //char * psz = str.get_buffer((character_count)(iSize + 1));

      //m_ptree->m_peditfile->seek((filesize)iBeg, ::e_seek_set);

      //m_ptree->m_peditfile->read(scopedstr, (memsize)(iSize));

      //psz[(memsize)iSize] = '\0';

      //str.release_buffer();

   }


   void plain_edit::on_set_property(::data::property_change & change)
   {

      if (m_textproperty && change)
      {

         if (change.m_atoma.get_size() == 2)
         {

            switch ((::enum_id)change.m_atoma[1].as_eid())
            {
            case id_text:
               set_text(change.m_payload.as_string(), change.m_actioncontext);
               return;
            case id_text_selection_begin:
               plain_edit_set_text_selection_begin(change.m_payload.as_iptr(), change.m_actioncontext);
               return;
            case id_text_selection_end:
               plain_edit_set_text_selection_end(change.m_payload.as_iptr(), change.m_actioncontext);
               return;
            default:
               break;
            }

         }

      }

      ::user::text::on_set_property(change);

   }


   ::payload plain_edit::on_get_property(const ::atom_array & atoma) const
   {

      if (m_textproperty && atoma)
      {

         if (atoma.get_size() >= 2)
         {

            switch ((::enum_id)atoma[1].as_eid())
            {
            case id_text:
            {

               ::string str;

               character_count iBegin = 0;

               if (atoma.get_size() >= 3)
               {

                  iBegin = atoma[2].as_long_long();

               }

               character_count iEnd = -1;

               if (atoma.get_size() >= 4)
               {

                  iEnd = atoma[3].as_long_long();

               }

               get_text(str, iBegin, iEnd);

               return str;

            }
            case id_text_length:
            {

               return m_ptree->m_peditfile->get_length();

            }
            case id_text_selection_begin:
            {

               character_count iBeg;

               character_count iEnd;

               get_text_selection(iBeg, iEnd);

               return iBeg;

            }
            case id_text_selection_end:
            {

               character_count iBeg;

               character_count iEnd;

               get_text_selection(iBeg, iEnd);

               return iEnd;

            }
            default:
               break;
            }

         }

      }

      return ::user::text::on_get_property(atoma);

   }



   //void plain_edit::set_text(const ::scoped_string & scopedstr, const ::action_context & actioncontext)
   //{

   //   m_textproperty.set_text(scopedstr, actioncontext);

   //}


   void plain_edit::set_selection_text(const ::scoped_string & scopedstr, const ::action_context & actioncontext)
   {

      //{

      _synchronous_lock synchronouslock(this->synchronization());

      m_textproperty.set_selection_text(scopedstr, actioncontext);

      //   m_ptree->m_peditfile->seek(m_ptree->m_iSelBeg, ::e_seek_set);

      //   m_ptree->m_peditfile->Delete((memsize)(m_ptree->m_iSelEnd - m_ptree->m_iSelBeg));

      //   m_ptree->m_peditfile->seek(m_ptree->m_iSelBeg, ::e_seek_set);

      //   m_ptree->m_peditfile->Insert(scopedstr, ansi_len(scopedstr));

      //}

      //queue_graphics_call([this, context](::draw2d::graphics_pointer & pgraphics)
      //   {

      //      plain_edit_on_update(pgraphics, context);

      //   });

      //set_need_redraw();

   }


   void plain_edit::set_selection_end(character_count iSelEnd, const ::action_context & actioncontext)
   {

      //queue_graphics_call([this, iSelEnd, actioncontext](::draw2d::graphics_pointer & pgraphics)
      //   {

      //      _set_sel_end(pgraphics, iSelEnd, actioncontext);

      //   });

      m_textproperty.set_selection_end(iSelEnd, actioncontext);

   }


   void plain_edit::_set_sel_end(::draw2d::graphics_pointer & pgraphics, character_count iSelEnd, const ::action_context & actioncontext)
   {

      ::character_count iSelBeg, iSelEndOld;

      get_text_selection(iSelBeg, iSelEndOld);

      set_text_selection(iSelBeg, iSelEnd, actioncontext);

      _ensure_selection_visible_x(pgraphics);

      //_set_sel_end(pgraphics, iSelEnd);

   }


   void plain_edit::_ensure_selection_visible_x(::draw2d::graphics_pointer & pgraphics)
   {

      ::collection::index iColumn = plain_edit_sel_to_column_x(pgraphics, m_ptree->m_iSelEnd, m_iColumnX);

      int x = 0;

      ::collection::index iLine = plain_edit_sel_to_line_x(pgraphics, m_ptree->m_iSelEnd, x);

      ::collection::index xEnd = 0;

      auto iLineLength = m_iaLineLength[iLine];

      xEnd = (::collection::index)plain_edit_get_line_extent(pgraphics, iLine, iLineLength);

      auto rectangleX = this->rectangle();

      auto xContext = get_context_offset().x();

      int iBorder = 4;

      if (xEnd < rectangleX.width() - iBorder * 2)
      {

         xContext = 0;

      }
      else if (xEnd - get_context_offset().x() < rectangleX.width() - iBorder * 2)
      {

         xContext = (int)maximum(0, xEnd - rectangleX.width() + iBorder * 2);

      }
      else if (x < xContext && xContext > 0)
      {

         xContext = x;

      }
      else if (x > 0 && x < get_context_offset().x())
      {

         xContext = maximum(0, x - rectangleX.width() / 2);

      }
      else if (x > get_context_offset().x() + rectangleX.width() - iBorder * 2)
      {

         xContext = (int)maximum(0, xEnd - rectangleX.width() + iBorder * 2);

      }

      if (iColumn == m_iColumn && xContext == get_context_offset().x())
      {

         return;

      }

      m_iColumn = iColumn;

      if (xContext != get_context_offset().x())
      {

         set_context_offset_x(xContext);

      }

      _001EnsureVisibleChar(pgraphics, m_ptree->m_iSelEnd);

   }


   void plain_edit::plain_edit_on_end_update(::draw2d::graphics_pointer & pgraphics)
   {

      if (m_bNewSel)
      {

         _001EnsureVisibleChar(pgraphics, m_ptree->m_iSelEnd);

      }

   }


   void plain_edit::plain_edit_set_text_selection_begin(character_count iBeg, const ::action_context & actioncontext)
   {

      _synchronous_lock synchronouslock(this->synchronization());

      m_ptree->m_iSelBeg = iBeg;

      _unlocked_plain_edit_on_change_text_selection(actioncontext);

   }


   void plain_edit::plain_edit_set_text_selection_end(character_count iEnd, const ::action_context & actioncontext)
   {

      _synchronous_lock synchronouslock(this->synchronization());

      m_ptree->m_iSelEnd = iEnd;

      _unlocked_plain_edit_on_change_text_selection(actioncontext);

   }


   //void plain_edit::set_text_selection(character_count iBeg, character_count iEnd, const ::action_context & actioncontext)
   void plain_edit::set_text_selection(character_count iBeg, character_count iEnd, const ::action_context & actioncontext)
   {

      _synchronous_lock synchronouslock(this->synchronization());

      m_ptree->m_iSelBeg = iBeg;

      m_ptree->m_iSelEnd = iEnd;

      _unlocked_plain_edit_on_change_text_selection(actioncontext);

   }


   void plain_edit::_unlocked_plain_edit_on_change_text_selection(const ::action_context & actioncontext)
   {

      m_bNewSel = true;

      if (actioncontext.is_user_source())
      {

         auto pwindowing = windowing();

         auto ptexteditorinterface = pwindowing->get_text_editor_interface();

         if (::is_set(ptexteditorinterface))
         {

            string strText;

            //get_text(strText);

            get_text(strText);

            //      //operating_system_driver::get()->m_iInputMethodManagerSelectionStart = ansi_to_wd16_len(strText, iBeg);

            //      //operating_system_driver::get()->m_iInputMethodManagerSelectionEnd = ansi_to_wd16_len(strText, iEnd);

            //auto iSelectionStart = ansi_to_wd32_len(strText, m_ptree->m_iSelBeg);

            //auto iSelectionEnd = ansi_to_wd32_len(strText, m_ptree->m_iSelEnd);
            auto iSelectionStart = m_ptree->m_iSelBeg;

            auto iSelectionEnd = m_ptree->m_iSelEnd;

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

      //#ifdef __ANDROID__
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


   void plain_edit::get_text_selection(character_count & iBeg, character_count & iEnd) const
   {

      _synchronous_lock synchronouslock(this->synchronization());

      iBeg = m_ptree->m_iSelBeg;

      iEnd = m_ptree->m_iSelEnd;

   }


   void plain_edit::get_text_selection(character_count & iBeg, character_count & iEnd, character_count & iComposingStart, character_count & iComposingEnd) const
   {

      _synchronous_lock synchronouslock(this->synchronization());

      iBeg = m_ptree->m_iSelBeg;

      iEnd = m_ptree->m_iSelEnd;

      if (m_pitemComposing)
      {

         iComposingStart = (character_count)m_pitemComposing->m_position;

         iComposingEnd = (character_count)(m_pitemComposing->m_position + m_pitemComposing->get_extent());

      }
      else
      {

         iComposingStart = iBeg;

         iComposingEnd = iEnd;

      }

   }


   void plain_edit::_001EnsureVisibleChar(::draw2d::graphics_pointer & pgraphics, character_count iChar)
   {

      plain_edit_ensure_visible_char(pgraphics, iChar);

   }


   void plain_edit::plain_edit_ensure_visible_char(::draw2d::graphics_pointer & pgraphics, character_count iChar)
   {

      int x = 0;

      plain_edit_ensure_visible_line(pgraphics, plain_edit_sel_to_line_x(pgraphics, iChar, x));

      int iBorder = 4;

      auto rectangleX = this->rectangle();

      auto xVisibleStart = get_context_offset_x(::user::e_layout_design);

      auto xVisibleEnd = xVisibleStart + rectangleX.width() - iBorder * 2.;

      if (x < xVisibleStart)
      {

         set_context_offset_x(x);

      }
      else if (x > xVisibleEnd)
      {

         set_context_offset_x(x - rectangleX.width() + iBorder * 2.);

      }

   }


   void plain_edit::_001EnsureVisibleLine(::draw2d::graphics_pointer & pgraphics, ::collection::index iLine)
   {

      plain_edit_ensure_visible_line(pgraphics, iLine);

   }


   void plain_edit::plain_edit_ensure_visible_line(::draw2d::graphics_pointer & pgraphics, ::collection::index iLine)
   {

      if (!m_bMultiLine)
      {

         set_context_offset_y(0);

      }
      else
      {

         ::int_rectangle rectangleX;

         GetFocusRect(rectangleX);

         auto currentPageTop = get_context_offset_y(::user::e_layout_design);

         auto currentPageBottom = get_context_offset_y(::user::e_layout_design) + rectangleX.height();

         auto lineTop = iLine * m_dLineHeight;

         auto lineBottom = (iLine + 1) * m_dLineHeight;

         if (lineTop < currentPageTop)
         {

            set_context_offset_y(lineTop, ::user::e_layout_layout);

         }
         else if (lineBottom >= currentPageBottom)
         {

            set_context_offset_y((lineBottom - rectangleX.height()) + (m_dLineHeight / 4.0), ::user::e_layout_layout);

         }

         m_bCalcLayoutHintNoTextChange = true;

      }

      on_change_context_offset(::user::e_layout_layout);

      plain_edit_on_context_offset_layout(pgraphics);

#ifndef SEARCH_SCROLLING_PROFILING

      //set_need_redraw();

#endif

   }


   //void plain_edit::on_change_context_offset(::draw2d::graphics_pointer & pgraphics)
   void plain_edit::on_context_offset_layout(::draw2d::graphics_pointer & pgraphics)
   {

      scroll_base::on_context_offset_layout(pgraphics);

      plain_edit_on_context_offset_layout(pgraphics);

   }


   bool plain_edit::plain_edit_is_enabled()
   {

      return true;

   }


   void plain_edit::set_edit_file(::file::file * pfile)
   {

      {

         _synchronous_lock writing(m_ptree->synchronization());

         m_ptree->SetFile(pfile);

      }

      queue_graphics_call([this](::draw2d::graphics_pointer & pgraphics)
      {

         plain_edit_create_line_index(pgraphics);

         plain_edit_on_update(pgraphics, ::e_source_system);

      });

      set_need_layout();

      set_need_redraw();

      post_redraw();

      //auto psystem = system();

      //auto pdraw2d = psystem->draw2d();

      //auto pgraphics = pdraw2d->create_memory_graphics(this);

      //plain_edit_on_calc_layout(pgraphics);

      //plain_edit_on_set_text(pgraphics, ::e_source_sync);

      //plain_edit_on_update(pgraphics, ::e_source_sync);

   }


   void plain_edit::on_message_mouse_move(::message::message * pmessage)
   {

      pmessage->previous();

      if (plain_edit_is_enabled())
      {

         auto pmouse = pmessage->m_union.m_pmouse;

         auto pwindowing = windowing();

         auto pcursor = pwindowing->get_cursor(e_cursor_text_select);

         user_mouse_set_cursor(pmouse, pcursor);

         set_default_mouse_cursor(pcursor);

         if (session()->is_key_pressed(::user::e_key_left_button) && !is_new_focus_select_all())
         {

            ::int_point pointHost = pmouse->m_pointHost;

            extend_selection_end(pointHost);

            m_pitemHover = stock_item(e_element_client);

         }

         pmessage->m_bRet = true;

      }

   }


   void plain_edit::on_message_mouse_leave(::message::message * pmessage)
   {

      if (!m_pitemHover || m_pitemHover->m_item.m_eelement != e_element_none)
      {

         m_pitemHover = __allocate::item(e_element_none);

         set_need_redraw();

      }

   }


   void plain_edit::on_message_left_button_down_handle_keyboard_focus(::message::message * pmessage)
   {

   }


   void plain_edit::on_message_left_button_down(::message::message * pmessage)
   {

      auto pmouse = pmessage->m_union.m_pmouse;

      m_timeLeftButtonDown.Now();

      if (plain_edit_is_enabled())
      {

         pmouse->previous();

         ::int_point point = pmouse->m_pointHost;

         host_to_client()(point);

         {

            _synchronous_lock synchronouslock(this->synchronization());

            //m_bLMouseDown = true;

            set_timer(e_timer_overflow_scrolling_start, 300_ms, nullptr);

            set_mouse_capture();

            bool bNewFocusSelectAll = is_new_focus_select_all();

            auto psession = session();

            bool bShiftKeyPressed = psession->is_key_pressed(::user::e_key_shift);

            ::pointer < ::message::message > pmessageHold = pmessage;

            queue_graphics_call([this, point, bShiftKeyPressed, bNewFocusSelectAll, pmessageHold](::draw2d::graphics_pointer & pgraphics)
            {

               ::character_count iBegNew = -1;
               ::character_count iEndNew = -1;

               ::character_count iBegOld = -1;
               ::character_count iEndOld = -1;

               get_text_selection(iBegOld, iEndOld);

               iBegNew = plain_edit_char_hit_test(pgraphics, point);

               if (bShiftKeyPressed)
               {

                  iEndNew = iBegNew;

                  iBegNew = iBegOld;

               }
               else
               {

                  iEndNew = iBegNew;

               }

               informationf("LeftButtonDown(%d,%d)-queue_graphics_call", iBegNew, iEndNew);

               auto iColumnNew = plain_edit_sel_to_column_x(pgraphics, m_ptree->m_iSelEnd, m_iColumnX);

               if (bNewFocusSelectAll)
               {

                  m_iNewFocusSelectAllSelBeg = iBegNew;

                  m_iNewFocusSelectAllSelEnd = iEndNew;

                  m_iNewFocusSelectAllColumn = iColumnNew;

               }
               else
               {

                  set_text_selection(iBegNew, iEndNew, e_source_sync);

                  m_iColumn = iColumnNew;

               }

            });

#if defined(APPLE_IOS)
            //if(windowing()->is_sandboxed()
            if (has_keyboard_focus())
            {

               auto pcontextmenu = __create_new < ::message::context_menu >();

               pcontextmenu->m_emessage = e_message_context_menu;

               auto pointHost = pmessageHold->m_union.m_pmouse->m_pointHost;

               pcontextmenu->m_pointMessage = pointHost;

               post_message(pcontextmenu);

            }

#endif

            ::user::interaction::on_message_left_button_down_handle_keyboard_focus(pmessageHold);

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

      defer_release_mouse_capture();

      m_bNewFocusSelectAll = false;

      //m_bLMouseDown = false;

      //if (m_bLMouseDown && !m_bNewFocus)
      //{

      //   ::int_point point = pmouse->m_pointHost;

      //   host_to_client()(point);

      //   queue_graphics_call([this, point](::draw2d::graphics_pointer & pgraphics)
      //      {

      //         _set_sel_end(pgraphics, plain_edit_char_hit_test(pgraphics, point), e_source_sync);

      //      });

      //}

      kill_timer(e_timer_overflow_scrolling);

      set_need_redraw();

      pmouse->m_bRet = true;

      pmouse->m_lresult = 1;

      on_reset_focus_start_tick();

   }


   void plain_edit::on_message_left_button_double_click(::message::message * pmessage)
   {

      pmessage->m_bRet = true;

   }


   void plain_edit::plain_edit_on_context_offset_layout(::draw2d::graphics_pointer & pgraphics, ::collection::index iOnlyLineToUpdate)
   {

      _synchronous_lock synchronouslock(this->synchronization());

      _plain_edit_update_extents(pgraphics, iOnlyLineToUpdate);

      //synchronous_lock synchronouslock(this->synchronization());

      //::int_rectangle rectangleX;

      //GetFocusRect(rectangleX);

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

      //::collection::index i;

      //::collection::index iLine;

      //if (pgraphics.is_null())
      //{

      //   return;

      //}

      //pgraphics->set_font(this, ::e_element_none);

      //double_size sizeUniText;

      //::write_text::text_metric metric;

      //pgraphics->get_text_metrics(&metric);

      //m_dLineHeight = metric.get_line_spacing();

      //if (m_dLineHeight <= 0.0)
      //{

      //   m_dLineHeight = 18.0;

      //}

      //auto pointOffset = get_context_offset();

      //m_iCurrentPagePotentialLineCount = (::collection::count) ceil((double)rectangleX.height() / m_dLineHeight);

      //m_iCurrentPageLineOffset = (::collection::index) minimum(maximum(0, pointOffset.y() / m_dLineHeight), m_iaLineIndex.get_upper_bound());

      //bool bLoadFullFile = should_load_full_file();

      //m_iCurrentPageLineStart = bLoadFullFile ? 0 : maximum(0, m_iCurrentPageLineOffset);

      //m_iCurrentPageLineEnd = bLoadFullFile ? m_iaLineLength.get_size() : minimum(m_iaLineLength.get_size(), m_iCurrentPagePotentialLineCount + m_iCurrentPageLineStart);

      //if (m_iCurrentPageLineOffset < 0)
      //{

      //   return;

      //}

      //m_iImpactOffset = m_iaLineIndex[m_iCurrentPageLineStart];

      //character_count iProperBeg = m_iaLineIndex[m_iCurrentPageLineEnd - 1];

      //character_count iLen = m_iaLineLength[m_iCurrentPageLineEnd - 1];

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

      //   iImpactOffset = m_iaLineIndex[iLineStart];

      //   iProperBeg = m_iaLineIndex[iLineEnd - 1];

      //   iLen = m_iaLineLength[iLineEnd - 1];

      //   iImpactSize = iProperBeg + iLen - iImpactOffset;

      //}

      //string strLine;

      //memory mem;

      //mem.set_size(iImpactSize + 1);

      //character_count iRead;

      //{

      //   m_ptree->m_peditfile->seek(iImpactOffset, ::e_seek_set);

      //   iRead = m_ptree->m_peditfile->read(mem.get_data(), iImpactSize);

      //   if (iRead < iImpactSize)
      //   {

      //      informationf("ops1");

      //      iImpactSize = iRead;

      //   }

      //   mem.get_data()[iImpactSize] = 0;

      //}

      //character_count iPos = 0;

      ////      character_count iLen;

      //character_count iStrLen;

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

      //      informationf("ops3");

      //      iStrLen = iImpactSize - iPos;

      //      if (iStrLen <= 0)
      //      {

      //         informationf("ops4");

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

      //      //informationf("optstr");

      //   }

      //   iPos += iLen;

      //   if (iPos > iImpactSize)
      //   {

      //      informationf("ops2");

      //      break;

      //   }

      //}

      //m_dy = pointOffset.y();

      ////::colorertake5::base_editor * pcolorer = colorertake5();

      ////if (pcolorer != nullptr)
      ////{

      ////   pcolorer->visibleTextEvent(m_iCurrentPageLineStart, m_iLineCount);

      ////}

      ////string_array & straLines = m_plinea->lines;

      //string_array & straLines = m_straLines;

      //if (iLineUpdate < 0)
      //{

      //   //m_sizeTotal.cx() = 0;

      //}

      //double_size size;

      //string strLineGraphics;

      //strsize_array iaTab;

      //character_count iTab;

      //character_count iAddUp;

      //for (int i = 0; i < straLines.get_size(); i++)
      //{

      //   strLine = straLines[i];

      //   iTab = -1;

      //   iaTab.erase_all();

      //   strLineGraphics = strLine;

      //   ::str::replace_tab(0, strLineGraphics, m_iTabWidth, &iaTab);

      //   const ::ansi_character * pszStart = strLine;

      //   const ::ansi_character * psz = pszStart;

      //   character_count iLen = 0;

      //   iAddUp = 0;

      //   iPos = 0;

      //   const ::ansi_character * pszNext = pszStart;

      //   double_array & daExtent = m_daExtent[m_iCurrentPageLineStart + i];

      //   if (daExtent.get_size() <= 0)
      //   {

      //      daExtent.set_size(strLine.length() + 1);

      //      while (*pszNext != '\0')
      //      {

      //         pszNext = unicode_next(scopedstr);

      //         iLen = pszNext - psz;

      //         if (*psz == '\t')
      //         {

      //            iTab++;

      //            iAddUp += iaTab[iTab] - 1;

      //         }

      //         size = pgraphics->get_text_extent(strLineGraphics, strLineGraphics.length(), pszNext - pszStart + iAddUp);

      //         for (int j = 0; j < iLen; j++)
      //         {

      //           daExtent [(::collection::index)(scopedstr - pszStart + j)] = size.cx();

      //         }

      //         psz = pszNext;

      //      }

      //      if (strLineGraphics.has_character())
      //      {

      //         size = pgraphics->get_text_extent(strLineGraphics, strLineGraphics.length());

      //         for (int j = 0; j < iLen; j++)
      //         {

      //            daExtent[(::collection::index)(scopedstr - pszStart)] = size.cx();

      //         }

      //      }


      //      if (size.cx() > m_sizeTotal.cx())
      //      {

      //         m_sizeTotal.cx() = (int)size.cx();

      //      }

      //   }


      //}

      ////if (iLineUpdate < 0)
      ////{

      ////   m_sizeTotal.cy() = (((int)m_iaLineLength.get_count() + (m_bMultiLine ? maximum(5, m_iLineCount) : 0)) * m_iLineHeight);

      ////   const ::int_size & sizePage;

      ////   sizePage = rectangleX.size();

      ////   if (m_sizeTotal.cy() < sizePage.cy())
      ////   {

      ////      sizePage.cy() = m_sizeTotal.cy();

      ////   }

      ////}

      ////on_change_impact_size();

      ////m_bCalcLayoutHintNoTextChange = false;

   }


   void plain_edit::plain_edit_on_calc_layout(::draw2d::graphics_pointer & pgraphics, ::collection::index iOnlyLineToUpdate)
   {

      _synchronous_lock synchronouslock(this->synchronization());

      if (!m_bMultiLine)
      {

         string strTextPrevious;

         get_text(strTextPrevious);

         string strText(strTextPrevious);

         if (strText.contains("\n"))
         {

            auto psession = session();

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

            auto psession = session();

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

            _synchronous_lock synchronouslock(this->synchronization());

            m_ptree->m_peditfile->seek(0, ::e_seek_set);
            m_ptree->m_peditfile->Delete((memsize)m_ptree->m_peditfile->get_length());
            m_ptree->m_peditfile->seek(0, ::e_seek_set);
            m_ptree->m_peditfile->Insert(strText, strText.length());

         }

      }

      ::int_rectangle rectangleX;

      GetFocusRect(rectangleX);

      if (rectangleX.area() <= 0)
      {

         return;

      }

      auto pstyle = get_style(pgraphics);

      if (::is_set(pstyle))
      {

         pstyle->get(m_pcontrolstyle, pgraphics, this);

      }

      plain_edit_create_line_index(pgraphics);

      _update_line_start_array(iOnlyLineToUpdate);

      _plain_edit_update_extents(pgraphics, iOnlyLineToUpdate);

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
      //      ::collection::index i;
      //
      //      ::collection::index iLine;
      //
      //      pgraphics->set_font(this, ::e_element_none);
      //
      //      double_size sizeUniText;
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
      //      m_pscrollstateVertical->m_iLine = (int) m_dLineHeight;
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
      //      m_iCurrentPagePotentialLineCount = (::collection::count) ceil((double) rectangleX.height() / m_dLineHeight);
      //
      //      m_iCurrentPageLineOffset = (::collection::index) minimum(maximum(0, pointOffset.y() / m_dLineHeight), m_iaLineIndex.get_upper_bound());
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
      //      m_iImpactOffset = m_iaLineIndex[m_iCurrentPageLineStart];
      //
      //      character_count iProperBeg = m_iaLineIndex[m_iCurrentPageLineEnd - 1];
      //
      //      character_count iLen = m_iaLineLength[m_iCurrentPageLineEnd - 1];
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
      //         iImpactOffset = m_iaLineIndex[iLineStart];
      //
      //         iProperBeg = m_iaLineIndex[iLineEnd - 1];
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
      //      character_count iRead;
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
      //            informationf("ops1");
      //
      //            iImpactSize = iRead;
      //
      //         }
      //
      //         mem.get_data()[iImpactSize] = 0;
      //
      //      }
      //
      //      character_count iPos = 0;
      //
      //      //      character_count iLen;
      //
      //      character_count iStrLen;
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
      //            informationf("ops3");
      //
      //            iStrLen = iImpactSize - iPos;
      //
      //            if (iStrLen <= 0)
      //            {
      //
      //               informationf("ops4");
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
      //            //informationf("optstr");
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
      //            informationf("ops2");
      //
      //            break;
      //
      //         }
      //
      //      }
      //
      //      m_dy = pointOffset.y();
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
      //         //m_sizeTotal.cx() = 0;
      //
      //      }
      //
      //      double_size size;
      //
      //
      //
      //      string strLineGraphics;
      //
      //      strsize_array iaTab;
      //
      //      character_count iTab;
      //
      //      character_count iAddUp;
      //
      //
      //      for (int i = 0; i < straLines.get_size(); i++)
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
      //         bool bTabs = strLine.find_index('\t') >= 0;
      //
      //         if (bTabs)
      //         {
      //
      //            ::str::replace_tab(0, strLineGraphics, m_iTabWidth, &iaTab);
      //
      //         }
      //
      //         const ::ansi_character * pszStart = strLine;
      //
      //         const ::ansi_character * psz = pszStart;
      //
      //         character_count iLen = 0;
      //
      //         iAddUp = 0;
      //
      //         iPos = 0;
      //
      //         const ::ansi_character * pszNext = pszStart;
      //
      //         ::int_size sizeLast(0, 0);
      //
      //         auto & daExtent = m_daExtent[m_iCurrentPageLineStart + i];
      //
      //         if (daExtent.get_size() <= 0)
      //         {
      //
      //            daExtent.set_size(strLine.length() + 1);
      //
      //            while (*pszNext != '\0')
      //            {
      //
      //               pszNext = unicode_next(scopedstr);
      //
      //               if (scopedstrNext == nullptr)
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
      //               size = pgraphics->get_text_extent(strLineGraphics, strLineGraphics.length(), pszNext - pszStart + iAddUp);
      //
      //               if (size.cx() > rectangleX.width() + 200)
      //               {
      //
      //                  while (*psz != '\0')
      //                  {
      //
      //                     daExtent[(::collection::index)(scopedstr - pszStart)] = -1;
      //                     psz++;
      //
      //                  }
      //
      //                  break;
      //
      //               }
      //
      //               sizeLast.cx() = (int) size.cx();
      //
      //               for (int j = 0; j < iLen; j++)
      //               {
      //
      //                  daExtent[(::collection::index)(scopedstr - pszStart + j)] = size.cx();
      //
      //               }
      //
      //               psz = pszNext;
      //
      //            }
      //
      //            if (strLineGraphics.has_character())
      //            {
      //
      //               size = pgraphics->get_text_extent(strLineGraphics, strLineGraphics.length());
      //
      //               daExtent[(::collection::index)(scopedstr - pszStart)] = size.cx();
      //
      //            }
      //
      //            if (size.cx() > m_sizeTotal.cx())
      //            {
      //
      //               m_sizeTotal.cx() = (int)size.cx();
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
      //         m_sizeTotal.cy() = (int) ((m_iaLineLength.get_count() + 1) * m_dLineHeight);
      //
      //         ::double_size sizePage;
      //
      //         sizePage = rectangleX.size();
      //
      //         if (m_sizeTotal.cy() < sizePage.cy())
      //         {
      //
      //            sizePage.cy() = m_sizeTotal.cy();
      //
      //         }
      //
      //      }
      //
      //      m_pscrollstateVertical->m_iLine = (int) m_dLineHeight;
      //
      //      on_change_impact_size(pgraphics);
      //
      //      m_bCalcLayoutHintNoTextChange = false;

   }


   void plain_edit::_plain_edit_update_extents(::draw2d::graphics_pointer & pgraphics, ::collection::index iOnlyLineStart, ::collection::index iOnlyLineEnd)
   {

      //_plain_edit_update_lines(pgraphics, iOnlyLineToUpdate);

      //_plain_edit_update_extents(pgraphics, iOnlyLineToUpdate);

      if (m_ptree == nullptr)
      {

         m_iCurrentPagePotentialLineCount = 0;

         m_iCurrentPageLineOffset = 0;

         m_iCurrentPageLineStart = 0;

         m_iCurrentPageLineEnd = 0;

         m_iImpactOffset = 0;

         m_iImpactSize = 0;

         set_total_size({ 0., 0. });

         return;

      }

      ::collection::index i;

      ::collection::index iLine;

      pgraphics->set_font(this, ::e_element_none);

      double_size sizeUniText;

      if (pgraphics == nullptr)
      {

         return;

      }

      ::int_rectangle rectangleX;

      GetFocusRect(rectangleX);

      ::write_text::text_metric metric;

      pgraphics->get_text_metrics(&metric);

      m_dLineHeight = metric.get_line_height();

      auto pointOffset = get_context_offset();

      m_iCurrentPagePotentialLineCount = (::collection::count)ceil((double)rectangleX.height() / m_dLineHeight);

      m_iCurrentPageLineOffset = (::collection::index)minimum(maximum(0, pointOffset.y() / m_dLineHeight), m_iaLineIndex.get_upper_bound());

      bool bLoadFullFile = should_load_full_file();

      m_iCurrentPageLineStart = bLoadFullFile ? 0 : maximum(0, m_iCurrentPageLineOffset);

      m_iCurrentPageLineEnd = bLoadFullFile ? m_iaLineLength.get_size() : minimum(m_iaLineLength.get_size(), m_iCurrentPagePotentialLineCount + m_iCurrentPageLineStart);

      if (m_iCurrentPageLineOffset < 0)
      {

         return;

      }

      m_iImpactOffset = m_iaLineIndex[m_iCurrentPageLineStart];

      character_count iProperBeg = m_iaLineIndex[m_iCurrentPageLineEnd - 1];

      character_count iLen = m_iaLineLength[m_iCurrentPageLineEnd - 1];

      m_iImpactSize = iProperBeg + iLen - m_iImpactOffset;

      //     m_pscrollstateVertical->m_iLine = (int)m_dLineHeight;

      if (m_dLineHeight <= 0)
      {

         m_dLineHeight = 18;

      }

      //auto pointOffset = get_context_offset();

      //m_iCurrentPagePotentialLineCount = (::collection::count)ceil((double)rectangleX.height() / m_dLineHeight);

      //m_iCurrentPageLineOffset = (::collection::index)minimum(maximum(0, pointOffset.y() / m_dLineHeight), m_iaLineIndex.get_upper_bound());

      //bool bLoadFullFile = should_load_full_file();

      //m_iCurrentPageLineStart = bLoadFullFile ? 0 : maximum(0, m_iCurrentPageLineOffset);

      //m_iCurrentPageLineEnd = bLoadFullFile ? m_iaLineLength.get_size() : minimum(m_iaLineLength.get_size(), m_iCurrentPagePotentialLineCount + m_iCurrentPageLineStart);

      //if (m_iCurrentPageLineOffset < 0)
      //{

      //   return;

      //}

      //m_iImpactOffset = m_iaLineIndex[m_iCurrentPageLineStart];

      //character_count iProperBeg = m_iaLineIndex[m_iCurrentPageLineEnd - 1];

      //character_count iLen = m_iaLineLength[m_iCurrentPageLineEnd - 1];

      //m_iImpactSize = iProperBeg + iLen - m_iImpactOffset;

      ::collection::index iLineStart;

      ::collection::index iLineEnd;

      ::collection::index iImpactOffset;

      ::collection::index iImpactSize;

      if (iOnlyLineStart < 0)
      {

         iLineStart = m_iCurrentPageLineStart;

         iLineEnd = m_iCurrentPageLineEnd;

         iImpactOffset = m_iImpactOffset;

         iImpactSize = m_iImpactSize;

      }
      else
      {

         if (iOnlyLineEnd < iOnlyLineStart)
         {

            iOnlyLineEnd = iOnlyLineStart;

         }

         iLineStart = iOnlyLineStart;

         iLineEnd = iOnlyLineEnd + 1;

         iImpactOffset = m_iaLineIndex[iLineStart];

         iProperBeg = m_iaLineIndex[iLineEnd - 1];

         iLen = m_iaLineLength[iLineEnd - 1];

         iImpactSize = iProperBeg + iLen - iImpactOffset;

      }

      string strLine;

      memory mem;

      mem.set_size(iImpactSize + 1);

      auto pszData = (char *)mem.data();

      character_count iRead;

      {

         m_ptree->m_peditfile->seek(iImpactOffset, ::e_seek_set);

         iRead = m_ptree->m_peditfile->read(scopedstrData, iImpactSize);

         if (iRead < iImpactSize)
         {

            informationf("ops1");

            iImpactSize = iRead;

         }

         pszData[iImpactSize] = 0;

      }

      character_count iPos = 0;

      //      character_count iLen;

      character_count iStrLen;

      //m_plinea->lines.set_size(m_iCurrentPageLineEnd - m_iCurrentPageLineStart);

      string_array & straLines = m_straLines;

      straLines.set_size(m_iCurrentPageLineEnd - m_iCurrentPageLineStart);

      i = iLineStart - m_iCurrentPageLineStart;

      iLine = iLineStart;

      m_daExtent.set_size(m_iaLineLength.get_size());

      for (; iLine < iLineEnd; i++, iLine++)
      {

         iLen = m_iaLineLength.element_at_grow(iLine);

         auto eol = (enum_line)m_iaLineFlags.element_at_grow(iLine);

         auto eolLen = as_length(eol);

         iStrLen = maximum(0, iLen - eolLen);

         if (iPos + iStrLen > m_iImpactSize)
         {

            informationf("ops3");

            iStrLen = iImpactSize - iPos;

            if (iStrLen <= 0)
            {

               informationf("ops4");

               break;

            }

         }

         auto p = pszData + iPos;

         string strLine = string((const char *)p, iStrLen);

         //string_array & straLines = m_straLines;

         //if (strLine != m_plinea->lines[i])
         if (strLine != straLines[i])
         {

            straLines[i] = strLine;

            m_daExtent[iLine].set_size(0);

         }
         else
         {

            //informationf("optstr");

         }

         iPos += iLen;

         if (iPos > iImpactSize)
         {

            informationf("ops2");

            break;

         }

      }

      m_dy = pointOffset.y();

      //::colorertake5::base_editor * pcolorer = colorertake5();

      //if (pcolorer != nullptr)
      //{

      //   pcolorer->visibleTextEvent(m_iCurrentPageLineStart, m_iLineCount);

      //}

//      string_array & straLines = m_plinea->lines;
//      string_array & straLines = m_straLines;

      //if (iOnlyLineToUpdate < 0)
      //{

      //   //m_sizeTotal.cx() = 0;

      //}

      double_size size;

      double_size sizeTotal;

      string strLineGraphics;

      strsize_array iaTab;

      character_count iTab;

      character_count iAddUp;

      for (int i = 0; i < straLines.get_size(); i++)
      {

         strLine = straLines[i];

         iTab = -1;

         iaTab.erase_all();

         strLineGraphics = strLine;

         bool bTabs = strLine.find_index('\t') >= 0;

         if (bTabs)
         {

            ::replace_tab(0, strLineGraphics, m_iTabWidth, &iaTab);

         }

         const ::ansi_character * pszStart = strLine;

         const ::ansi_character * psz = pszStart;

         character_count iLen = 0;

         iAddUp = 0;

         iPos = 0;

         const ::ansi_character * pszNext = pszStart;

         ::int_size sizeLast(0, 0);

         auto & daExtent = m_daExtent[m_iCurrentPageLineStart + i];

         if (daExtent.get_size() <= 0)
         {

            daExtent.set_size(strLine.length() + 1);

            while (*pszNext != '\0')
            {

               pszNext = unicode_next(scopedstr);

               if (scopedstrNext == nullptr)
               {

                  break;

               }

               iLen = pszNext - psz;

               if (*psz == '\t')
               {

                  iTab++;

                  iAddUp += iaTab[iTab] - 1;

               }

               size = pgraphics->get_text_extent(strLineGraphics, pszNext - pszStart + iAddUp);

               //if (size.cx() > rectangleX.width() + 200)
               //{

               //   while (*psz != '\0')
               //   {

               //      daExtent[(::collection::index)(scopedstr - pszStart)] = -1;
               //      psz++;

               //   }

               //   break;

               //}

               sizeLast.cx() = (int)size.cx();

               for (int j = 0; j < iLen; j++)
               {

                  daExtent[(::collection::index)(scopedstr - pszStart + j)] = size.cx();

               }

               psz = pszNext;

            }

            if (strLineGraphics.has_character())
            {

               size = pgraphics->get_text_extent(strLineGraphics, strLineGraphics.length());

               daExtent[(::collection::index)(scopedstr - pszStart)] = size.cx();

            }

         }

         if (daExtent.has_element())
         {

            auto sizeX = daExtent.last();

            if (sizeX > sizeTotal.cx())
            {

               sizeTotal.cx() = sizeX;

            }

         }

      }

      if (iLineEnd - iLineStart >= 2)
      {

         sizeTotal.cy() = (int)((m_iaLineLength.get_count() + 1) * m_dLineHeight);

         ::double_size sizePage;

         sizePage = rectangleX.size();

         if (sizeTotal.cy() < sizePage.cy())
         {

            sizePage.cy() = sizeTotal.cy();

         }

      }

      //m_pscrollstateVertical->m_iLine = (int)m_dLineHeight;

      if (m_pscrolllayoutY)
      {

         m_pscrolllayoutY->m_scrollstatea[::user::e_layout_sketch].m_dLine = m_dLineHeight;
         m_pscrolllayoutY->m_scrollstatea[::user::e_layout_sketch].m_dWheel = 3. * m_dLineHeight;

      }

      set_total_size(sizeTotal);

      //on_change_impact_size(pgraphics);

      m_bCalcLayoutHintNoTextChange = false;

   }


   //   void plain_edit::_plain_edit_update_lines(::draw2d::graphics_pointer & pgraphics, ::collection::index iOnlyLineToUpdate)
   //   {
   //
   //      _synchronous_lock synchronouslock(this->synchronization());
   //
   //      ::int_rectangle rectangleX;
   //
   //      GetFocusRect(rectangleX);
   //
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
   //         return;
   //
   //      }
   //
   //      ::collection::index i;
   //
   //      ::collection::index iLine;
   //
   //      if (pgraphics.is_null())
   //      {
   //
   //         return;
   //
   //      }
   //
   //      pgraphics->set_font(this, ::e_element_none);
   //
   //      index iLineStart;
   //
   //      index iLineEnd;
   //
   //      index iImpactOffset;
   //
   //      index iImpactSize;
   //
   //      if (iOnlyLineToUpdate < 0)
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
   //         iLineStart = iOnlyLineToUpdate;
   //
   //         iLineEnd = iLineStart + 1;
   //
   //         iImpactOffset = m_iaLineIndex[iLineStart];
   //
   //         iProperBeg = m_iaLineIndex[iLineEnd - 1];
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
   //      character_count iRead;
   //
   //      {
   //
   //         m_ptree->m_peditfile->seek(iImpactOffset, ::e_seek_set);
   //
   //         iRead = m_ptree->m_peditfile->read(mem.data(), iImpactSize);
   //
   //         if (iRead < iImpactSize)
   //         {
   //
   //            informationf("ops1");
   //
   //            iImpactSize = iRead;
   //
   //         }
   //
   //         mem.data()[iImpactSize] = 0;
   //
   //      }
   //
   //      character_count iPos = 0;
   //
   //      //      character_count iLen;
   //
   //      character_count iStrLen;
   //
   //      //m_plinea->lines.set_size(m_iCurrentPageLineEnd - m_iCurrentPageLineStart);
   //      m_straLines.set_size(m_iCurrentPageLineEnd - m_iCurrentPageLineStart);
   //
   //      i = 0;
   //
   //      iLine = iLineStart;
   //
   //      auto iLineLength = m_iaLineLength.get_size();
   //
   //      m_daExtent.set_size(iLineLength);
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
   //            informationf("ops3");
   //
   //            iStrLen = iImpactSize - iPos;
   //
   //            if (iStrLen <= 0)
   //            {
   //
   //               informationf("ops4");
   //
   //               break;
   //
   //            }
   //
   //         }
   //
   //         string strLine = string((const char *)&mem.data()[iPos], iStrLen);
   //
   //         //if (strLine != m_plinea->lines[i])
   //         if (strLine != m_straLines[i])
   //         {
   //
   //            //m_plinea->lines[i] = strLine;
   //            m_straLines[i] = strLine;
   //
   //            m_daExtent[i + iLineStart].set_size(0);
   //
   //         }
   //         else
   //         {
   //
   //            //informationf("optstr");
   //
   //         }
   //
   //         iPos += iLen;
   //
   //         if (iPos > iImpactSize)
   //         {
   //
   //            informationf("ops2");
   //
   //            break;
   //
   //         }
   //
   //      }
   //
   //      //m_dy = pointOffset.y();
   //
   //      ////::colorertake5::base_editor * pcolorer = colorertake5();
   //
   //      ////if (pcolorer != nullptr)
   //      ////{
   //
   //      ////   pcolorer->visibleTextEvent(m_iCurrentPageLineStart, m_iLineCount);
   //
   //      ////}
   //
   //      ////string_array & straLines = m_plinea->lines;
   //
   //      //string_array & straLines = m_straLines;
   //
   //      //if (iLineUpdate < 0)
   //      //{
   //
   //      //   //m_sizeTotal.cx() = 0;
   //
   //      //}
   //
   //      //double_size size;
   //
   //      //string strLineGraphics;
   //
   //      //strsize_array iaTab;
   //
   //      //character_count iTab;
   //
   //      //character_count iAddUp;
   //
   //      //for (int i = 0; i < straLines.get_size(); i++)
   //      //{
   //
   //      //   strLine = straLines[i];
   //
   //      //   iTab = -1;
   //
   //      //   iaTab.erase_all();
   //
   //      //   strLineGraphics = strLine;
   //
   //      //   ::str::replace_tab(0, strLineGraphics, m_iTabWidth, &iaTab);
   //
   //      //   const ::ansi_character * pszStart = strLine;
   //
   //      //   const ::ansi_character * psz = pszStart;
   //
   //      //   character_count iLen = 0;
   //
   //      //   iAddUp = 0;
   //
   //      //   iPos = 0;
   //
   //      //   const ::ansi_character * pszNext = pszStart;
   //
   //      //   double_array & daExtent = m_daExtent[m_iCurrentPageLineStart + i];
   //
   //      //   if (daExtent.get_size() <= 0)
   //      //   {
   //
   //      //      daExtent.set_size(strLine.length() + 1);
   //
   //      //      while (*pszNext != '\0')
   //      //      {
   //
   //      //         pszNext = unicode_next(scopedstr);
   //
   //      //         iLen = pszNext - psz;
   //
   //      //         if (*psz == '\t')
   //      //         {
   //
   //      //            iTab++;
   //
   //      //            iAddUp += iaTab[iTab] - 1;
   //
   //      //         }
   //
   //      //         size = pgraphics->get_text_extent(strLineGraphics, strLineGraphics.length(), pszNext - pszStart + iAddUp);
   //
   //      //         for (int j = 0; j < iLen; j++)
   //      //         {
   //
   //      //           daExtent [(::collection::index)(scopedstr - pszStart + j)] = size.cx();
   //
   //      //         }
   //
   //      //         psz = pszNext;
   //
   //      //      }
   //
   //      //      if (strLineGraphics.has_character())
   //      //      {
   //
   //      //         size = pgraphics->get_text_extent(strLineGraphics, strLineGraphics.length());
   //
   //      //         for (int j = 0; j < iLen; j++)
   //      //         {
   //
   //      //            daExtent[(::collection::index)(scopedstr - pszStart)] = size.cx();
   //
   //      //         }
   //
   //      //      }
   //
   //
   //      //      if (size.cx() > m_sizeTotal.cx())
   //      //      {
   //
   //      //         m_sizeTotal.cx() = (int)size.cx();
   //
   //      //      }
   //
   //      //   }
   //
   //
   //      //}
   //
   //      ////if (iLineUpdate < 0)
   //      ////{
   //
   //      ////   m_sizeTotal.cy() = (((int)m_iaLineLength.get_count() + (m_bMultiLine ? maximum(5, m_iLineCount) : 0)) * m_iLineHeight);
   //
   //      ////   const ::int_size & sizePage;
   //
   //      ////   sizePage = rectangleX.size();
   //
   //      ////   if (m_sizeTotal.cy() < sizePage.cy())
   //      ////   {
   //
   //      ////      sizePage.cy() = m_sizeTotal.cy();
   //
   //      ////   }
   //
   //      ////}
   //
   //      ////on_change_impact_size();
   //
   //      ////m_bCalcLayoutHintNoTextChange = false;
   //
   //   }
   //
   //
   //   void plain_edit::_plain_edit_update_extents(::draw2d::graphics_pointer & pgraphics, ::collection::index iOnlyLineToUpdate)
   //   {
   //
   //      //_synchronous_lock synchronouslock(this->synchronization());
   //
   ////::int_rectangle rectangleX;
   //
   ////GetFocusRect(rectangleX);
   //
   ////if (m_ptree == nullptr)
   ////{
   //
   ////   m_iCurrentPagePotentialLineCount = 0;
   //
   ////   m_iCurrentPageLineOffset = 0;
   //
   ////   m_iCurrentPageLineStart = 0;
   //
   ////   m_iCurrentPageLineEnd = 0;
   //
   ////   m_iImpactOffset = 0;
   //
   ////   m_iImpactSize = 0;
   //
   ////   return;
   //
   ////}
   //
   ////::collection::index i;
   //
   ////::collection::index iLine;
   //
   ////if (pgraphics.is_null())
   ////{
   //
   ////   return;
   //
   ////}
   //
   ////pgraphics->set_font(this, ::e_element_none);
   //
   ////double_size sizeUniText;
   //
   ////::write_text::text_metric metric;
   //
   ////pgraphics->get_text_metrics(&metric);
   //
   ////m_dLineHeight = metric.get_line_spacing();
   //
   ////if (m_dLineHeight <= 0.0)
   ////{
   //
   ////   m_dLineHeight = 18.0;
   //
   ////}
   //
   ////auto pointOffset = get_context_offset();
   //
   ////m_iCurrentPagePotentialLineCount = (::collection::count) ceil((double)rectangleX.height() / m_dLineHeight);
   //
   ////m_iCurrentPageLineOffset = (::collection::index) minimum(maximum(0, pointOffset.y() / m_dLineHeight), m_iaLineIndex.get_upper_bound());
   //
   ////bool bLoadFullFile = should_load_full_file();
   //
   ////m_iCurrentPageLineStart = bLoadFullFile ? 0 : maximum(0, m_iCurrentPageLineOffset);
   //
   ////m_iCurrentPageLineEnd = bLoadFullFile ? m_iaLineLength.get_size() : minimum(m_iaLineLength.get_size(), m_iCurrentPagePotentialLineCount + m_iCurrentPageLineStart);
   //
   ////if (m_iCurrentPageLineOffset < 0)
   ////{
   //
   ////   return;
   //
   ////}
   //
   ////m_iImpactOffset = m_iaLineIndex[m_iCurrentPageLineStart];
   //
   ////character_count iProperBeg = m_iaLineIndex[m_iCurrentPageLineEnd - 1];
   //
   ////character_count iLen = m_iaLineLength[m_iCurrentPageLineEnd - 1];
   //
   ////m_iImpactSize = iProperBeg + iLen - m_iImpactOffset;
   //
   ////index iLineStart;
   //
   ////index iLineEnd;
   //
   ////index iImpactOffset;
   //
   ////index iImpactSize;
   //
   ////if (iLineUpdate < 0)
   ////{
   //
   ////   iLineStart = m_iCurrentPageLineStart;
   //
   ////   iLineEnd = m_iCurrentPageLineEnd;
   //
   ////   iImpactOffset = m_iImpactOffset;
   //
   ////   iImpactSize = m_iImpactSize;
   //
   ////}
   ////else
   ////{
   //
   ////   iLineStart = iLineUpdate;
   //
   ////   iLineEnd = iLineStart + 1;
   //
   ////   iImpactOffset = m_iaLineIndex[iLineStart];
   //
   ////   iProperBeg = m_iaLineIndex[iLineEnd - 1];
   //
   ////   iLen = m_iaLineLength[iLineEnd - 1];
   //
   ////   iImpactSize = iProperBeg + iLen - iImpactOffset;
   //
   ////}
   //
   ////string strLine;
   //
   ////memory mem;
   //
   ////mem.set_size(iImpactSize + 1);
   //
   ////character_count iRead;
   //
   ////{
   //
   ////   m_ptree->m_peditfile->seek(iImpactOffset, ::e_seek_set);
   //
   ////   iRead = m_ptree->m_peditfile->read(mem.get_data(), iImpactSize);
   //
   ////   if (iRead < iImpactSize)
   ////   {
   //
   ////      informationf("ops1");
   //
   ////      iImpactSize = iRead;
   //
   ////   }
   //
   ////   mem.get_data()[iImpactSize] = 0;
   //
   ////}
   //
   ////character_count iPos = 0;
   //
   //////      character_count iLen;
   //
   ////character_count iStrLen;
   //
   //////m_plinea->lines.set_size(m_iCurrentPageLineEnd - m_iCurrentPageLineStart);
   ////m_straLines.set_size(m_iCurrentPageLineEnd - m_iCurrentPageLineStart);
   //
   ////i = 0;
   //
   ////iLine = iLineStart;
   //
   ////auto iLineLength = m_iaLineLength.get_size();
   //
   ////m_daExtent.set_size(iLineLength);
   //
   ////for (; iLine < iLineEnd; i++, iLine++)
   ////{
   //
   ////   iLen = m_iaLineLength[iLine];
   //
   ////   iStrLen = maximum(0, iLen - (m_iaLineFlags[iLine] & e_line_end_length));
   //
   ////   if (iPos + iStrLen > m_iImpactSize)
   ////   {
   //
   ////      informationf("ops3");
   //
   ////      iStrLen = iImpactSize - iPos;
   //
   ////      if (iStrLen <= 0)
   ////      {
   //
   ////         informationf("ops4");
   //
   ////         break;
   //
   ////      }
   //
   ////   }
   //
   ////   string strLine = string((const char *)&mem.get_data()[iPos], iStrLen);
   //
   ////   //if (strLine != m_plinea->lines[i])
   ////   if (strLine != m_straLines[i])
   ////   {
   //
   ////      //m_plinea->lines[i] = strLine;
   ////      m_straLines[i] = strLine;
   //
   ////      m_daExtent[i + iLineStart].set_size(0);
   //
   ////   }
   ////   else
   ////   {
   //
   ////      //informationf("optstr");
   //
   ////   }
   //
   ////   iPos += iLen;
   //
   ////   if (iPos > iImpactSize)
   ////   {
   //
   ////      informationf("ops2");
   //
   ////      break;
   //
   ////   }
   //
   ////}
   //
   ////m_dy = pointOffset.y();
   //
   //////::colorertake5::base_editor * pcolorer = colorertake5();
   //
   //////if (pcolorer != nullptr)
   //////{
   //
   //////   pcolorer->visibleTextEvent(m_iCurrentPageLineStart, m_iLineCount);
   //
   //////}
   //
   //////string_array & straLines = m_plinea->lines;
   //
   ////string_array & straLines = m_straLines;
   //
   ////if (iLineUpdate < 0)
   ////{
   //
   ////   //m_sizeTotal.cx() = 0;
   //
   ////}
   //
   //      double_size sizeUniText;
   //
   //      ::write_text::text_metric metric;
   //
   //      pgraphics->get_text_metrics(&metric);
   //
   //      m_dLineHeight = metric.get_line_height();
   //
   //      if (m_dLineHeight <= 0.0)
   //      {
   //
   //         m_dLineHeight = 18.0;
   //
   //      }
   //
   //      auto pointOffset = get_context_offset();
   //
   //      m_iCurrentPagePotentialLineCount = (::collection::count)ceil((double)rectangleX.height() / m_dLineHeight);
   //
   //      m_iCurrentPageLineOffset = (::collection::index)minimum(maximum(0, pointOffset.y() / m_dLineHeight), m_iaLineIndex.get_upper_bound());
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
   //      m_iImpactOffset = m_iaLineIndex[m_iCurrentPageLineStart];
   //
   //      character_count iProperBeg = m_iaLineIndex[m_iCurrentPageLineEnd - 1];
   //
   //      character_count iLen = m_iaLineLength[m_iCurrentPageLineEnd - 1];
   //
   //      m_iImpactSize = iProperBeg + iLen - m_iImpactOffset;
   //
   //      ::user::enum_layout elayout = ::user::e_layout_design;
   //
   //      double_size size;
   //
   //      string strLineGraphics;
   //
   //      strsize_array iaTab;
   //
   //      character_count iTab;
   //
   //      character_count iAddUp;
   //
   //      for (int i = 0; i < m_straLines.get_size(); i++)
   //      {
   //
   //         string strLine = m_straLines[i];
   //
   //         iTab = -1;
   //
   //         iaTab.erase_all();
   //
   //         strLineGraphics = strLine;
   //
   //         replace_tab(0, strLineGraphics, m_iTabWidth, &iaTab);
   //
   //         const ::ansi_character * pszStart = strLine;
   //
   //         const ::ansi_character * psz = pszStart;
   //
   //         character_count iLen = 0;
   //
   //         iAddUp = 0;
   //
   //         character_count iPos = 0;
   //
   //         const ::ansi_character * pszNext = pszStart;
   //
   //         double_array & daExtent = m_daExtent[m_iCurrentPageLineStart + i];
   //
   //         auto sizeTotal = get_total_size(elayout);
   //
   //         if (daExtent.get_size() <= 0)
   //         {
   //
   //            daExtent.set_size(strLine.length() + 1);
   //
   //            while (::has_character(scopedstrNext))
   //            {
   //
   //               pszNext = unicode_next(scopedstr);
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
   //               size = pgraphics->get_text_extent(strLineGraphics, pszNext - pszStart + iAddUp);
   //
   //               for (int j = 0; j < iLen; j++)
   //               {
   //
   //                  daExtent[(::collection::index)(scopedstr - pszStart + j)] = size.cx();
   //
   //               }
   //
   //               psz = pszNext;
   //
   //            }
   //
   //            if (strLineGraphics.has_character())
   //            {
   //
   //               size = pgraphics->get_text_extent(strLineGraphics, strLineGraphics.length());
   //
   //               for (int j = 0; j < iLen; j++)
   //               {
   //
   //                  daExtent[(::collection::index)(scopedstr - pszStart)] = size.cx();
   //
   //               }
   //
   //            }
   //
   //
   //            if (size.cx() > sizeTotal.cx())
   //            {
   //
   //               sizeTotal.cx() = size.cx();
   //
   //            }
   //
   //         }
   //
   //         set_total_size(sizeTotal, elayout);
   //
   //      }
   //
   //      //if (iLineUpdate < 0)
   //      //{
   //
   //      //   m_sizeTotal.cy() = (((int)m_iaLineLength.get_count() + (m_bMultiLine ? maximum(5, m_iLineCount) : 0)) * m_iLineHeight);
   //
   //      //   const ::int_size & sizePage;
   //
   //      //   sizePage = rectangleX.size();
   //
   //      //   if (m_sizeTotal.cy() < sizePage.cy())
   //      //   {
   //
   //      //      sizePage.cy() = m_sizeTotal.cy();
   //
   //      //   }
   //
   //      //}
   //
   //      //on_change_impact_size();
   //
   //      //m_bCalcLayoutHintNoTextChange = false;
   //
   //   }


   ::collection::index plain_edit::plain_edit_sel_to_line(::draw2d::graphics_pointer & pgraphics, character_count iSel)
   {

      _synchronous_lock synchronouslock(this->synchronization());

      character_count i1;

      character_count i2 = 0;

      ::collection::index iLine = 0;

      for (; iLine < m_iaLineLength.get_size(); iLine++)
      {

         i1 = i2;

         i2 = i1 + m_iaLineLength[iLine];

         if (iSel >= i1 && iSel < i2)
         {

            return iLine;

         }

      }

      return ::maximum(m_iaLineLength.get_upper_bound(), 0);

   }


   ::collection::index plain_edit::plain_edit_char_to_line(::draw2d::graphics_pointer & pgraphics, character_count iChar)
   {

      _synchronous_lock synchronouslock(this->synchronization());

      for (::collection::index iLine = 0; iLine < m_iaLineIndex.get_size(); iLine++)
      {

         if (iChar >= m_iaLineIndex[iLine] && iChar < m_iaLineIndex[iLine] + m_iaLineLength[iLine])
         {

            return iLine;

         }

      }

      return m_iaLineIndex.get_count();

   }


   bool plain_edit::plain_edit_caret_rect(::draw2d::graphics_pointer & pgraphics, ::int_rectangle * lprect, character_count iSel)
   {

      int x = 0;

      ::collection::index iLine = plain_edit_sel_to_line_x(pgraphics, iSel, x);

      if (!plain_edit_line_range(pgraphics, lprect, iLine))
      {

         return false;

      }

      lprect->left() = x;

      lprect->right() = x + 1;

      return true;

   }


   bool plain_edit::plain_edit_index_range(::draw2d::graphics_pointer & pgraphics, ::int_rectangle * lprect, character_count iSel)
   {

      ::collection::index iLine = plain_edit_char_to_line(pgraphics, iSel);

      return plain_edit_line_range(pgraphics, lprect, iLine);

   }


   bool plain_edit::plain_edit_line_range(::draw2d::graphics_pointer & pgraphics, ::int_rectangle * lprect, ::collection::index iLine)
   {

      if (iLine < 0)
      {

         return false;

      }

      lprect->top() = (int)(iLine * m_dItemHeight);

      lprect->bottom() = (int)(lprect->top() + m_dItemHeight);

      return true;

   }


   double plain_edit::plain_edit_get_line_extent(::draw2d::graphics_pointer & pgraphics, ::collection::index iLine, character_count iChar)
   {

      if (iLine < 0 || iChar < 0)
      {

         return 0;

      }

      //_synchronous_lock synchronouslock(this->synchronization());

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

      double_size size = pgraphics->get_text_extent(strLine, (int)iChar);

      return size.cx();


   }


   ::collection::index plain_edit::plain_edit_sel_to_line_x(::draw2d::graphics_pointer & pgraphics, character_count iSel, int & x)
   {

      //_synchronous_lock synchronouslock(this->synchronization());

      ::int_rectangle rectangleX;

      GetFocusRect(rectangleX);

      character_count i1;

      character_count i2 = 0;

      for (::collection::index iLine = 0; iLine < m_iaLineLength.get_size(); iLine++)
      {

         i1 = i2;

         i2 = i1 + m_iaLineLength[iLine];

         if (iSel < i2)
         {

            character_count iRel = iSel - i1;

            x = (int)plain_edit_get_line_extent(pgraphics, iLine, iRel);

            return iLine;

         }

      }

      x = rectangleX.left();

      return m_iaLineLength.get_upper_bound();

   }


   character_count plain_edit::plain_edit_line_column_to_sel(::draw2d::graphics_pointer & pgraphics, ::collection::index iLine, ::collection::index iColumn)
   {

      _synchronous_lock synchronouslock(this->synchronization());

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

      if (iLine >= m_iaLineLength.get_size())
      {

         return 0;

      }

      character_count iOffset = 0;

      character_count iLineOffset = -1;

      for (int i = 0; i < iLine; i++)
      {

         auto iNext = iOffset + m_iaLineLength[i];

         if (iLineOffset < 0 && iNext > m_iImpactOffset)
         {

            iLineOffset = i;

         }

         iOffset = iNext;

      }

      if (iLineOffset < 0)
      {

         iLineOffset = 0;

      }

      string_array stra;

      string strLine;

      stra.erase_all();

      //      string_array & straLines = m_plinea->lines;
      string_array & straLines = m_straLines;

      stra.add_lines(straLines[iLine - iLineOffset], false);

      if (stra.get_size() > 0)
      {

         strLine = stra[0];

      }
      else
      {

         strLine.empty();

      }

      if (iColumn < 0)
      {

         iColumn = iColumn + 1 + strLine.length();

      }

      if (iColumn > strLine.length())
      {

         iColumn = strLine.length();

      }

      //
      //return m_iImpactOffset + iOffset + iColumn;
      //

      return iOffset + iColumn;

   }


   character_count plain_edit::plain_edit_line_x_to_sel(::draw2d::graphics_pointer & pgraphics, ::collection::index iLine, int x)
   {

      _synchronous_lock synchronouslock(this->synchronization());

      __defer_construct(pgraphics);

      pgraphics->set_font(this, ::e_element_none);

      pgraphics->set_text_rendering_hint(::write_text::e_rendering_anti_alias);

      character_count iChar = _plain_edit_line_x_to_sel(pgraphics, iLine, x);

      return iChar;

   }


   character_count plain_edit::_plain_edit_line_x_to_sel(::draw2d::graphics_pointer & pgraphics, ::collection::index iLine, int x)
   {

      character_count iChar = plain_edit_line_char_hit_test(pgraphics, x, iLine);

      return iChar;

   }



   ::collection::index plain_edit::plain_edit_sel_to_column_x(::draw2d::graphics_pointer & pgraphics, character_count iSel, int & x)
   {

      _synchronous_lock synchronouslock(this->synchronization());

      ::int_rectangle rectangleX;

      GetFocusRect(rectangleX);

      character_count i1;

      character_count i2 = 0;

      for (::collection::index iLine = 0; iLine < m_iaLineLength.get_size(); iLine++)
      {

         i1 = i2;

         i2 = i1 + m_iaLineLength[iLine];

         if (iSel >= i1 && (iSel < i2
            || (iLine == m_iaLineLength.get_upper_bound() && iSel <= i2)))
         {

            character_count iRel = iSel - i1;

            int xCharacter;

            xCharacter = (int)(plain_edit_get_line_extent(pgraphics, iLine, iRel));

            xCharacter = rectangleX.left() + xCharacter;

            x = xCharacter;

            return iRel;

         }

      }

      return -1;

   }


   ::collection::index plain_edit::plain_edit_sel_to_column(::draw2d::graphics_pointer & pgraphics, character_count iSel)
   {

      _synchronous_lock synchronouslock(this->synchronization());

      //string_array & straLines = m_plinea->lines;

      character_count i1;

      character_count i2 = 0;

      for (::collection::index i = 0; i < m_iaLineLength.get_size(); i++)
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


   character_count plain_edit::plain_edit_char_hit_test(::draw2d::graphics_pointer & pgraphics, const ::int_point & pointParam)
   {

      ::int_point point(pointParam);

      ::int_rectangle rectangleX;

      GetFocusRect(rectangleX);

      point.y() -= rectangleX.top();

      auto pointOffset = get_context_offset();

      //if (m_dLineHeight > 0)
      //{

      //   int iVerticalOffsetModule = (int)fmod(pointOffset.y(), m_dLineHeight);

      //   if (iVerticalOffsetModule > 0)
      //   {

      //      point.y() += iVerticalOffsetModule;

      //   }

      //}

      double dLineHeight;

      double Δy = 0;

      bool bFound = false;

      dLineHeight = m_dLineHeight;

      //character_count iOffset = 0;

      string_array stra;

      ::collection::index iLine;

      if (point.y() < 0)
      {

         iLine = maximum(0, m_iCurrentPageLineStart - 1);

      }
      else if (point.y() > rectangleX.height())
      {

         iLine = minimum(line_count(), m_iCurrentPageLineEnd + 1);

      }
      else
      {

         for (iLine = m_iCurrentPageLineStart; iLine < m_iCurrentPageLineEnd; iLine++)
         {

            if (point.y() < Δy + dLineHeight)
            {

               bFound = true;

               break;

            }

            Δy += dLineHeight;

            //iOffset += m_iaLineLength[iLine];

         }

         if (!bFound)
         {

            if (iLine > m_iCurrentPageLineStart)
            {

               iLine--;

            }

         }

      }

      return plain_edit_line_char_hit_test(pgraphics, point.x(), iLine);

   }


   character_count plain_edit::plain_edit_line_char_hit_test(::draw2d::graphics_pointer & pgraphics, int px, ::collection::index iLine)
   {

      _synchronous_lock synchronouslock(this->synchronization());

      ::int_rectangle rectangleX;

      GetFocusRect(rectangleX);

      auto pointOffset = get_context_offset();

      px -= (int)(rectangleX.left() - pointOffset.x());

      if (px <= 0)
      {

         px = 0;

      }

      //int lim = 0;

      //bool bFound = false;

      string strLine = plain_edit_get_line(pgraphics, iLine);

      int lim2 = 0;

      int lim1;

      const ::ansi_character * psz = strLine;

      const ::ansi_character * pszEnd = psz;

      const ::ansi_character * pszPrevious = psz;

      //string strLineGraphics = strLine;

      //replace_tab(0, strLineGraphics, m_iTabWidth);

      character_count iSel = 0;

      string strExtent;

      if (iLine >= m_iaLineIndex.size())
      {

         return 0;

      }

      for (;;)
      {

         pszPrevious = pszEnd;

         unicode_increment(pszEnd);

         if (pszEnd == nullptr)
            break;

         lim1 = lim2;

         strExtent = string(scopedstr, pszEnd - psz);

         replace_tab(0, strExtent, m_iTabWidth);

         int x;

         x = (int)(plain_edit_get_line_extent(pgraphics, iLine, strExtent.length()));

         lim2 = x;

         //lim = lim2;

         int iMid = (lim2 - lim1) * 3 / 4;

         if (px >= lim1 && px <= lim1 + iMid)
         {

            iSel = m_iaLineIndex[iLine] + (scopedstrPrevious - psz);

            goto end;

         }
         else if (px >= lim1 + iMid && px <= lim2)
         {

            iSel = m_iaLineIndex[iLine] + (pszEnd - psz);

            goto end;

         }

         if (pszEnd[0] == '\0')
         {

            break;

         }

      }

      if (iLine < m_iaLineIndex.get_count()
         && iLine < m_iaLineLength.get_count()
         && iLine < m_iaLineFlags.get_count())
      {

         iSel = m_iaLineIndex[iLine] + (m_iaLineLength[iLine] - (m_iaLineFlags[iLine] & e_line_end_length));

      }

   end:

      if (iSel > m_textproperty.get_size())
      {

         iSel = m_textproperty.get_size();

      }

      return iSel;

   }


   //void plain_edit::get_text_selection(character_count & iSelBeg, character_count & iSelEnd)
   //{

   //   _synchronous_lock synchronouslock(this->synchronization());

   //   m_textproperty.get_selection(iSelBeg, iSelEnd);

   //}


   //void plain_edit::get_text_selection(character_count & iSelBeg, character_count & iSelEnd)
   //{

   //   _synchronous_lock synchronouslock(this->synchronization());

   //   _001_get_impact_sel(iSelBeg, iSelEnd);

   //}


   //void plain_edit::get_text_selection(character_count & iSelBeg, character_count & iSelEnd)
   //{

   //   _synchronous_lock synchronouslock(this->synchronization());

   //   if (m_ptree == nullptr)
   //   {

   //      iSelBeg = 0;

   //      iSelEnd = 0;

   //   }
   //   else
   //   {

   //      iSelBeg = m_ptree->m_iSelBeg - m_iImpactOffset;

   //      iSelEnd = m_ptree->m_iSelEnd - m_iImpactOffset;

   //      if (iSelBeg < 0)
   //      {

   //         iSelBeg = 0;

   //      }
   //      else if (::comparison::gt(iSelBeg, m_ptree->m_peditfile->get_length()))
   //      {

   //         iSelBeg = (character_count)(m_ptree->m_peditfile->get_length());

   //      }

   //      if (iSelEnd < 0)
   //      {

   //         iSelEnd = 0;

   //      }
   //      else if (::comparison::gt(iSelEnd, m_ptree->m_peditfile->get_length()))
   //      {

   //         iSelEnd = (character_count)(m_ptree->m_peditfile->get_length());

   //      }

   //   }

   //}


   //void plain_edit::_001GetSel(character_count & iBeg, character_count & iEnd)
   //{

   //   _synchronous_lock synchronouslock(this->synchronization());

   //   iBeg = m_ptree->m_iSelBeg;

   //   iEnd = m_ptree->m_iSelEnd;

   //}


   //void plain_edit::_001GetSel(character_count & iSelStart, character_count & iSelEnd, character_count & iComposingStart, character_count & iComposingEnd)
   //{

   //   _synchronous_lock synchronouslock(this->synchronization());

   //   iSelStart = m_ptree->m_iSelBeg;

   //   iSelEnd = m_ptree->m_iSelEnd;

   //   if (m_pitemComposing)
   //   {

   //      iComposingStart = (character_count)m_pitemComposing->m_position;

   //      iComposingEnd = (character_count)(m_pitemComposing->m_position + m_pitemComposing->get_extent());

   //   }
   //   else
   //   {

   //      iComposingStart = iSelStart;

   //      iComposingEnd = iSelEnd;

   //   }

   //}


   void plain_edit::FileSave()
   {

      _synchronous_lock synchronouslock(this->synchronization());

      m_ptree->m_peditfile->flush();

   }


   void plain_edit::plain_edit_on_file_update(::draw2d::graphics_pointer & pgraphics)
   {

      //m_bGetTextNeedUpdate = true;

      plain_edit_create_line_index(pgraphics);

      m_dy = -1;

   }


   void plain_edit::plain_edit_create_line_index(::draw2d::graphics_pointer & pgraphics)
   {

      _synchronous_lock synchronouslock(this->synchronization());

      memory m;

      m.set_size(1024 * 1024);

      char * buf = (char *)m.data();

      memsize uRead;

      char * psz;

      m_ptree->m_peditfile->seek(0, ::e_seek_set);

      ::user::enum_layout elayout = ::user::e_layout_design;

      auto sizeTotal = get_total_size(elayout);

      if (sizeTotal.cx() <= 0)
      {

         sizeTotal.cx() = 200;

         set_total_size(sizeTotal, elayout);

      }

      int iLineSize = 0;

      m_iaLineLength.erase_all();

      m_iaLineFlags.erase_all();

      memsize uiPos;

      int iLastR = 0;

      enum_line eline = e_line_end_eof;

      while ((uRead = m_ptree->m_peditfile->read(buf, m.size())) > 0)
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

                  eline = maximum(eline, e_line_end_r_n);

                  iLineSize = 0;

               }
               else
               {

                  iLineSize++;

                  m_iaLineLength.add(iLineSize);

                  m_iaLineFlags.add(e_line_end_n);

                  eline = maximum(eline, e_line_end_r_n);

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

                  eline = maximum(eline, e_line_end_r_n);

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

         eline = maximum(eline, e_line_end_r);

         iLineSize = 0;

      }

      if (eline != e_line_end_eof)
      {

         m_eline = eline;

      }

      m_iaLineLength.add(iLineSize);

      m_iaLineFlags.add(e_line_end_eof);

      _update_line_start_array();

   }


   void plain_edit::_update_line_start_array(::collection::index iLineStart, ::collection::index iAccumul)
   {

      ::collection::count iLineCount = m_iaLineLength.get_size();

      m_iaLineIndex.set_size(iLineCount);

      ::collection::index iLine;

      if (iAccumul >= 0)
      {

         iLine = iLineStart;

      }
      else
      {

         iLine = 0;

         iAccumul = 0;

         for (; iLine < iLineStart; iLine++)
         {

            iAccumul += m_iaLineLength[iLine];

         }

      }

      for (; iLine < iLineCount; iLine++)
      {

         auto & iLineStart = m_iaLineIndex[iLine];

         if (iAccumul != iLineStart)
         {

            iLineStart = iAccumul;

         }

         iAccumul += m_iaLineLength[iLine];

      }

   }


   void plain_edit::plain_edit_update_line_index(::draw2d::graphics_pointer & pgraphics, ::collection::index iLine)
   {

      _synchronous_lock synchronouslock(this->synchronization());

      memory m;

      character_count iOffset = 0;

      for (::collection::index i = 0; i < iLine; i++)
      {

         iOffset += m_iaLineLength[i];

      }

      m.set_size(1024);

      char * buf = (char *)m.data();

      memsize uRead;

      char * psz;

      m_ptree->m_peditfile->seek(iOffset, ::e_seek_set);

      ::user::enum_layout elayout = ::user::e_layout_design;

      auto sizeTotal = get_total_size(elayout);

      if (sizeTotal.cx() <= 0)
      {

         sizeTotal.cx() = 200;

         set_total_size(sizeTotal, elayout);

      }

      int iLineSize = 0;

      memsize uiPos;

      int iLastR = 0;

      bool bSet = false;

      while ((uRead = m_ptree->m_peditfile->read(buf, m.size())) > 0)
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

      _update_line_start_array(iLine, iOffset);

   }


   void plain_edit::_001OnUniChar(::message::message * pmessage)
   {

      //      ::pointer<::user::message>pusermessage(pmessage);
      //
      //      if (unicode_is_legal_uni_index(pusermessage->m_wparam))
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
      //            ::wd32_character unsigned int[2];
      //
      //            unsigned int[0] = pusermessage->m_wparam;
      //
      //            unsigned int[1] = 0;
      //
      //            str = wd32_to_ansi(unsigned int, 1);
      //
      //            insert_text(str);
      //
      //         }
      //#endif
      //
      //      }

   }


   void plain_edit::plain_edit_on_delete_surrounding_text(::draw2d::graphics_pointer & pgraphics, character_count beforeLength, character_count afterLength)
   {

      _synchronous_lock synchronouslock(this->synchronization());

      bool bFullUpdate = false;

      ::collection::index iLineUpdate = -1;

      if (!m_bReadOnly)
      {

         auto iSelBeg = m_ptree->m_iSelBeg;

         auto iSelEnd = m_ptree->m_iSelEnd;

         if (afterLength > 0 && iSelEnd < m_ptree->m_peditfile->get_length())
         {

            on_before_change_text();

            string str;

            get_text(str, iSelEnd, -1);

            const char * pdata = str.c_str();

            const ::ansi_character * psz = pdata;

            for (character_count i = 0; i < afterLength; i++)
            {

               auto pszNew = unicode_next(scopedstr);

               if (::is_empty(scopedstrNew))
               {

                  break;

               }

               psz = pszNew;

            }

            character_count iMultiByteUtf8DeleteCount = psz - pdata;

            auto i1 = iSelEnd;

            auto i2 = i1 + iMultiByteUtf8DeleteCount;

            string strSel;

            get_text(strSel, i1, i2);

            bFullUpdate = strSel.find_index('\n') >= 0 || strSel.find_index('\r') >= 0;

            if (!bFullUpdate)
            {

               iLineUpdate = plain_edit_sel_to_line(pgraphics, i1);

            }

            m_ptree->m_peditfile->seek(i1, ::e_seek_set);

            m_ptree->m_peditfile->Delete((memsize)(iMultiByteUtf8DeleteCount));

            m_pinsert = nullptr;

            IndexRegisterDelete(i1, iMultiByteUtf8DeleteCount);

            MacroBegin();

            MacroRecord(__allocate plain_text_file_command());

            MacroEnd();

         }

         if (beforeLength > 0 && iSelBeg > 0)
         {

            on_before_change_text();

            string str;

            get_text(str, 0, iSelBeg);

            const ::ansi_character * psz = str.c_str() + iSelBeg;

            const char * pdata = psz;

            for (character_count i = 0; i < beforeLength; i++)
            {

               auto pdataNew = utf8_dec(str.c_str(), pdata);

               if (::is_empty(pdataNew))
               {

                  break;

               }

               pdata = pdataNew;

            }

            character_count iMultiByteUtf8DeleteCount = psz - pdata;

            auto i1 = m_ptree->m_iSelBeg - iMultiByteUtf8DeleteCount;

            auto i2 = i1 + iMultiByteUtf8DeleteCount;

            string strSel;

            get_text(strSel, i1, i2);

            bFullUpdate = strSel.find_index('\n') >= 0 || strSel.find_index('\r') >= 0;

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

            MacroRecord(__allocate plain_text_file_command());

            MacroEnd();

         }

      }

      plain_edit_update(pgraphics, bFullUpdate, iLineUpdate);

      _ensure_selection_visible_x(pgraphics);

   }


   inline const char * _001DeferEOLPrior(const ::ansi_character * psz, const ::ansi_character * pszBeg)
   {

      psz--;

      if (scopedstr < pszBeg)
      {

         return nullptr;

      }

      if (*psz == '\n')
      {

         auto pszTry = psz - 1;

         if (scopedstrTry < pszBeg)
         {

            return pszBeg;

         }

         if (*pszTry == '\r')
         {

            return pszTry;

         }

         return psz;

      }
      else if (*psz == '\r')
      {

         return psz;

      }

      return nullptr;

   }


   inline const char * _001UnicodePrior(const ::ansi_character * psz, const ::ansi_character * pszBeg)
   {

      auto pszTry = _001DeferEOLPrior(scopedstr, pszBeg);

      if (scopedstrTry)
      {

         return pszTry;

      }

      return unicode_prior(scopedstr, pszBeg);

   }


   inline const char * _001DeferEOLNext(const ::ansi_character * psz)
   {

      if (!*psz)
      {

         return nullptr;

      }

      if (*psz == '\n')
      {

         return psz + 1;

      }
      else if (*psz == '\r')
      {

         auto pszTry = psz + 1;

         if (!*pszTry)
         {

            return pszTry;

         }
         else if (*pszTry == '\n')
         {

            return pszTry + 1;

         }

      }

      return nullptr;

   }


   inline const char * _001UnicodeNext(const ::ansi_character * psz, int * piError)
   {

      if (!*psz)
      {

         return nullptr;

      }

      auto pszTry = _001DeferEOLNext(scopedstr);

      if (scopedstrTry)
      {

         return pszTry;

      }

      return unicode_next(scopedstr, piError);

   }


   void plain_edit::_plain_edit_update_for_delete(::draw2d::graphics_pointer & pgraphics, const ::block & block, ::character_count i1, ::collection::index & iLine1, ::collection::index & iLine2)
   {

      ::string strSel(block);

      auto bFullUpdate = strSel.find_index('\n') >= 0 || strSel.find_index('\r') >= 0;

      auto i2 = i1 + strSel.length();

      if (bFullUpdate)
      {

         iLine1 = plain_edit_sel_to_line(pgraphics, i1);

         iLine2 = plain_edit_sel_to_line(pgraphics, i2);

         ::string_array straLinesDeleted;

         straLinesDeleted.add_lines(strSel);

         auto & iLineLen1 = m_iaLineLength[iLine1];

         auto iDeleted1 = straLinesDeleted.first().size();

         iLineLen1 -= iDeleted1;

         auto & iLineLen2 = m_iaLineLength[iLine2];

         auto iDeleted2 = straLinesDeleted.last().size();

         iLineLen2 -= iDeleted2;

         auto iDeleted = iLine2 - iLine1;

         auto eolDeleted = (enum_line)(m_iaLineFlags[iLine1]);

         iLineLen1 += iLineLen2 - as_length(eolDeleted);

         m_iaLineLength.erase_at(iLine1 + 1, iDeleted);

         m_iaLineFlags.erase_at(iLine1 + 1, iDeleted);

         m_iaLineIndex.erase_at(iLine1 + 1, iDeleted);

         m_straLines.erase_at(iLine1 + 1 - m_iCurrentPageLineStart, iDeleted);

      }
      else
      {

         iLine1 = plain_edit_sel_to_line(pgraphics, i1);

         auto & iLineLength = m_iaLineLength[iLine1];

         auto iDelLen = strSel.size();

         iLineLength -= iDelLen;

         iLine2 = iLine1;

      }

   }


   bool plain_edit::_plain_edit_on_delete(::draw2d::graphics_pointer & pgraphics, ::collection::index & iLineUpdate, ::character_count & i1, ::character_count & i2, bool bBackIfSelectionEmpty)
   {

      bool bFullUpdate = false;

      i1 = m_ptree->m_iSelBeg;

      i2 = m_ptree->m_iSelEnd;

      ::sort_non_negative(i1, i2);

      auto iSelBegOld = i1;

      auto iSelEndOld = i2;

      string strSample;

      character_count iSample;

      character_count iSample1;

      character_count iSample2;

      ::string strSel;

      if (i1 == i2)
      {

         if (bBackIfSelectionEmpty)
         {

            if (i2 <= 0)
            {

               return false;

            }

            iSample = ::minimum_maximum(i2, 0, 16);

            iSample1 = ::maximum(0, i2 - 16);;

            iSample2 = i2;

            get_text(strSel, iSample1, iSample2);

            auto pszBefore = _001UnicodePrior(strSel.end(), strSel.begin());

            if (::is_null(scopedstrBefore))
            {

               return false;

            }

            i1 -= strSel.end() - pszBefore;

         }
         else
         {

            if (i2 >= m_ptree->m_peditfile->get_length())
            {

               return false;

            }

            iSample = i1;

            iSample1 = i1;

            iSample2 = ::minimum(i2 + 16, m_ptree->m_peditfile->get_length());

            get_text(strSel, iSample1, iSample2);

            int iError = 0;

            auto pszNext = _001UnicodeNext(strSel.begin(), &iError);

            if (::is_null(scopedstrNext) || iError > 0)
            {

               return false;

            }

            i2 += pszNext - strSel.begin();

            //i2++;

         }

      }



      /*auto psetsel = __allocate plain_text_set_sel_command();

      psetsel->m_iPreviousSelBeg = m_ptree->m_iSelBeg;

      psetsel->m_iPreviousSelEnd = m_ptree->m_iSelEnd;*/

      ::sort_non_negative(i1, i2);

      //if (i1 != i2)
      //{

      on_before_change_text();

      get_text(strSel, i1, i2);

      ::collection::index iLine1 = -1;
      
      ::collection::index iLine2 = -1;

      _plain_edit_update_for_delete(pgraphics, strSel, i1, iLine1, iLine2);

      m_ptree->m_peditfile->seek(i1, ::e_seek_set);

      m_ptree->m_peditfile->Delete(i2 - i1);

      m_pinsert = nullptr;

      //IndexRegisterDelete(i1, i2 - i1);

      m_ptree->m_iSelEnd = i1;

      //psetsel->m_iPreviousSelBeg = m_ptree->m_iSelBeg;

      //psetsel->m_iPreviousSelEnd = m_ptree->m_iSelEnd;

      MacroRecord(__allocate plain_text_file_command());


      // this i1, i1 is on purpose, deleted from i1 to i2, 
// so final selection is [i1, i2]
      if (i1 != iSelBegOld || i1 != iSelEndOld)
      {

         auto psetsel = __allocate plain_text_set_sel_command();

         psetsel->m_iPreviousSelBeg = iSelBegOld;

         psetsel->m_iPreviousSelEnd = iSelEndOld;

         psetsel->m_iSelBeg = i1;

         psetsel->m_iSelEnd = i1;

         m_ptree->m_iSelBeg = i1;

         m_ptree->m_iSelEnd = i1;

         _unlocked_plain_edit_on_change_text_selection(e_source_sync);

         MacroRecord(psetsel);

      }
      //MacroRecord(psetsel);

      //auto iSelBeg = m_ptree->m_iSelEnd;

      //auto iSelEnd = m_ptree->m_iSelEnd;

      //psetsel->m_iSelBeg = iSelBeg;

      //psetsel->m_iSelEnd = iSelEnd;

      //m_ptree->m_iSelBeg = iSelBeg;

      //m_ptree->m_iSelEnd = iSelEnd;


      //if (bBackIfSelectionEmpty)
      //{

      //   psetsel->m_iSelBeg = i1;

      //   psetsel->m_iSelEnd = i1;

      //   m_ptree->m_iSelBeg = i1;

      //   m_ptree->m_iSelEnd = i1;

      //   _unlocked_plain_edit_on_change_text_selection(e_source_sync);

      //}

      //MacroRecord(psetsel);

      //MacroRecord(__allocate plain_text_file_command());


      //}
      //else
      //{

      //   //if (bBackIfSelectionEmpty)
      //   //{

      //   //}
      //   //else
      //   //{

      //   //   if (m_ptree->m_iSelEnd >= m_ptree->m_peditfile->get_length())
      //   //   {

      //   //      return;

      //   //   }

      //   //}

      //   //on_before_change_text();

      //   //char buf[512];

      //   //memory_set(buf, 0, sizeof(buf));

      //   //filesize posRead;

      //   //filesize amountToRead;

      //   //if (bBackIfSelectionEmpty)
      //   //{

      //   //   posRead = maximum(0, m_ptree->m_iSelEnd - (::filesize)sizeof(buf));

      //   //   amountToRead = minimum(sizeof(buf), m_ptree->m_iSelEnd - posRead);

      //   //}
      //   //else
      //   //{

      //   //   posRead = m_ptree->m_iSelEnd;

      //   //   amountToRead = sizeof(buf);

      //   //}

      //   //m_ptree->m_peditfile->seek(posRead, ::e_seek_set);

      //   //auto amountRead = m_ptree->m_peditfile->read(buf, amountToRead);

      //   //const ::ansi_character * pszBefore;

      //   //const ::ansi_character * pszNext;

      //   //if (bBackIfSelectionEmpty)
      //   //{

      //   //   //if(amountRead == amountToRead)
      //   //   //{

      //   //   pszNext = buf + amountRead;

      //   //   pszBefore = unicode_prior(scopedstrNext, buf);

      //   //   //}

      //   //}
      //   //else
      //   //{

      //   //   pszBefore = buf;

      //   //   pszNext = unicode_next(buf);

      //   //}

      //   character_count iMultiByteUtf8DeleteCount = pszNext - pszBefore;

      //   ::collection::index i1;

      //   if (bBackIfSelectionEmpty)
      //   {

      //      i1 = m_ptree->m_iSelEnd - iMultiByteUtf8DeleteCount;

      //   }
      //   else
      //   {

      //      i1 = m_ptree->m_iSelEnd;

      //   }

      //   ::collection::index i2 = i1 + iMultiByteUtf8DeleteCount;

      //   string strSel;

      //   get_text(strSel, i1, i2);

      //   bFullUpdate = strSel.find_index('\n') >= 0 || strSel.find_index('\r') >= 0;

      //   if (!bFullUpdate)
      //   {

      //      iLineUpdate = plain_edit_sel_to_line(pgraphics, i1);

      //   }


      //}

      //MacroBegin();

      //if (psetsel)
      //{

      //   MacroRecord(psetsel);

      //}

      //MacroRecord(__allocate plain_text_file_command());

      //MacroEnd();

   //}

   //plain_edit_update(pgraphics, bFullUpdate, iLineUpdate);

   //_ensure_selection_visible_x(pgraphics);
      return true;
   }


   void plain_edit::plain_edit_on_delete(::draw2d::graphics_pointer & pgraphics, bool bBackIfSelectionEmpty)
   {

      _synchronous_lock synchronouslock(this->synchronization());

      bool bFullUpdate = false;

      ::collection::index iLineUpdate = -1;

      if (!m_bReadOnly)
      {

         //MacroBegin();

         //_plain_edit_on_delete

            //character_count i1 = m_ptree->m_iSelBeg;

            //character_count i2 = m_ptree->m_iSelEnd;

            //string strSample;

            //character_count iSample;

            //character_count iSample1;

            //character_count iSample2;

            //if (i1 == i2)
            //{

            //   if (bBackIfSelectionEmpty)
            //   {

            //      if (i2 <= 0)
            //      {

            //         return;

            //      }

            //      iSample = ::minimum_maximum(i2, 0, 16);

            //      iSample1 = ::maximum(0, i2 - 16);;

            //      iSample2 = i2;

            //      get_text(strSel, iSample1, iSample2);

            //      auto pszBefore = unicode_prior(strSel.end(), strSel.begin());

            //      if (::is_null(scopedstrBefore))
            //      {

            //         return;

            //      }

            //      i1 -= strSel.end() - pszBefore;

            //   }
            //   else
            //   {

            //      if (i2 >= m_ptree->m_peditfile->get_length())
            //      {

            //         return;

            //      }

            //      iSample = i1;

            //      iSample1 = i1;

            //      iSample2 = ::minimum(i2 + 16, m_ptree->m_peditfile->get_length());

            //      get_text(strSel, iSample1, iSample2);

            //      int iError = 0;

            //      auto pszNext = unicode_next(strSel.begin(), &iError);

            //      if (::is_null(scopedstrNext))
            //      {

            //         return;

            //      }

            //      i2 += pszNext - strSel.begin();

            //      i2++;

            //   }

            //}

            //auto psetsel = __allocate plain_text_set_sel_command();

            //psetsel->m_iPreviousSelBeg = m_ptree->m_iSelBeg;

            //psetsel->m_iPreviousSelEnd = m_ptree->m_iSelEnd;

            //::sort_non_negative(i1, i2);

            ////if (i1 != i2)
            //{

            //   on_before_change_text();

            //   string strSel;

            //   get_text(strSel, i1, i2);

            //   bFullUpdate = strSel.find_index('\n') >= 0 || strSel.find_index('\r') >= 0;

            //   //if (bFullUpdate)
            //   //{

            //      int iLine1 = plain_edit_char_to_line(pgraphics, i1);

            //      int iLine2 = plain_edit_char_to_line(pgraphics, i2);

            //      ::string_array straLinesDeleted;

            //      straLinesDeleted.add_lines(strSel);

            //      m_iaLineLength[iLine1] -= straLinesDeleted.first().size();

            //      m_iaLineLength[iLine2] -= straLinesDeleted.last().size();

            //      auto iDeleted = iLine2 - iLine1;

            //      m_iaLineLength[iLine1] += m_iaLineLength[iLine2];

            //      m_iaLineLength.erase_at(iLine1 + 1, iDeleted);

            //      m_iaLineFlags.erase_at(iLine1 + 1, iDeleted);

            //   }
            //   else
            //   {

            //      iLineUpdate = plain_edit_sel_to_line(pgraphics, i1);

            //      m_iaLineLength[iLineUpdate] -= strSel.size();

            //   }

            //   m_ptree->m_peditfile->seek(i1, ::e_seek_set);

            //   m_ptree->m_peditfile->Delete(i2 - i1);

            //   m_pinsert = nullptr;

            //   IndexRegisterDelete(i1, i2 - i1);

            //   m_ptree->m_iSelEnd = i1;

            //   auto iSelBeg = m_ptree->m_iSelEnd;

            //   auto iSelEnd = m_ptree->m_iSelEnd;

            //   psetsel->m_iSelBeg = iSelBeg;

            //   psetsel->m_iSelEnd = iSelEnd;

            //   m_ptree->m_iSelBeg = iSelBeg;

            //   m_ptree->m_iSelEnd = iSelEnd;

            //}
            //else
            //{

            //   //if (bBackIfSelectionEmpty)
            //   //{

            //   //}
            //   //else
            //   //{

            //   //   if (m_ptree->m_iSelEnd >= m_ptree->m_peditfile->get_length())
            //   //   {

            //   //      return;

            //   //   }

            //   //}

            //   //on_before_change_text();

            //   //char buf[512];

            //   //memory_set(buf, 0, sizeof(buf));

            //   //filesize posRead;

            //   //filesize amountToRead;

            //   //if (bBackIfSelectionEmpty)
            //   //{

            //   //   posRead = maximum(0, m_ptree->m_iSelEnd - (::filesize)sizeof(buf));

            //   //   amountToRead = minimum(sizeof(buf), m_ptree->m_iSelEnd - posRead);

            //   //}
            //   //else
            //   //{

            //   //   posRead = m_ptree->m_iSelEnd;

            //   //   amountToRead = sizeof(buf);

            //   //}

            //   //m_ptree->m_peditfile->seek(posRead, ::e_seek_set);

            //   //auto amountRead = m_ptree->m_peditfile->read(buf, amountToRead);

            //   //const ::ansi_character * pszBefore;

            //   //const ::ansi_character * pszNext;

            //   //if (bBackIfSelectionEmpty)
            //   //{

            //   //   //if(amountRead == amountToRead)
            //   //   //{

            //   //   pszNext = buf + amountRead;

            //   //   pszBefore = unicode_prior(scopedstrNext, buf);

            //   //   //}

            //   //}
            //   //else
            //   //{

            //   //   pszBefore = buf;

            //   //   pszNext = unicode_next(buf);

            //   //}

            //   character_count iMultiByteUtf8DeleteCount = pszNext - pszBefore;

            //   ::collection::index i1;

            //   if (bBackIfSelectionEmpty)
            //   {

            //      i1 = m_ptree->m_iSelEnd - iMultiByteUtf8DeleteCount;

            //   }
            //   else
            //   {

            //      i1 = m_ptree->m_iSelEnd;

            //   }

            //   ::collection::index i2 = i1 + iMultiByteUtf8DeleteCount;

            //   string strSel;

            //   get_text(strSel, i1, i2);

            //   bFullUpdate = strSel.find_index('\n') >= 0 || strSel.find_index('\r') >= 0;

            //   if (!bFullUpdate)
            //   {

            //      iLineUpdate = plain_edit_sel_to_line(pgraphics, i1);

            //   }


            //   if (bBackIfSelectionEmpty)
            //   {

            //      psetsel->m_iSelBeg = i1;

            //      psetsel->m_iSelEnd = i1;

            //      m_ptree->m_iSelBeg = i1;

            //      m_ptree->m_iSelEnd = i1;

            //      _unlocked_plain_edit_on_change_text_selection(e_source_sync);

            //   }

            //}


            /*if (psetsel)
            {

               MacroRecord(psetsel);

            }*/

            /*MacroRecord(__allocate plain_text_file_command());*/

            //MacroEnd();

         ::character_count i1;

         ::character_count i2;

         auto iSelBegOld = m_ptree->m_iSelBeg;

         auto iSelEndOld = m_ptree->m_iSelEnd;

         MacroBegin();



         if (_plain_edit_on_delete(pgraphics, iLineUpdate, i1, i2, bBackIfSelectionEmpty))
         {

            if (bBackIfSelectionEmpty)
            {

               informationf("plain_edit_on_delete: back (%d, %d)", i1, i2);

            }
            else
            {

               informationf("plain_edit_on_delete: forward (%d, %d)", i1, i2);

            }

            //MacroRecord(__allocate plain_text_file_command());


            //// this i1, i1 is on purpose, deleted from i1 to i2, 
            //// so final selection is [i1, i2]
            //if (i1 != iSelBegOld || i1 != iSelEndOld)
            //{

            //   auto psetsel = __allocate plain_text_set_sel_command();

            //   psetsel->m_iPreviousSelBeg = iSelBegOld;

            //   psetsel->m_iPreviousSelEnd = iSelEndOld;

            //   psetsel->m_iSelBeg = i1;

            //   psetsel->m_iSelEnd = i1;

            //   m_ptree->m_iSelBeg = i1;

            //   m_ptree->m_iSelEnd = i1;

            //   _unlocked_plain_edit_on_change_text_selection(e_source_sync);

            //   MacroRecord(psetsel);

            //}

            MacroEnd();

            _update_line_start_array(iLineUpdate);

            _plain_edit_update_extents(pgraphics, iLineUpdate, iLineUpdate);

            _ensure_selection_visible_x(pgraphics);

         }
         else
         {

            MacroDiscard();

         }

      }

   }


   void plain_edit::_001EditCut(const ::action_context & actioncontext)
   {

      clipboard_copy();

      _001DeleteSel(false, actioncontext);

   }


   void plain_edit::_001DeleteSel(bool bBackIfSelectionEmpty, const ::action_context & actioncontext)
   {

      //bool bFullUpdate = true;

      //index iLineUpdate = -1;

      //auto psystem = system();

      //auto pdraw2d = psystem->draw2d();

      //auto pgraphics = pdraw2d->create_memory_graphics(this);

      //if (plain_edit_delete_sel(pgraphics, bFullUpdate, iLineUpdate))
      //{

      //   plain_edit_update(pgraphics, bFullUpdate, iLineUpdate);

      //}

      queue_graphics_call([this, bBackIfSelectionEmpty, actioncontext](::draw2d::graphics_pointer & pgraphics)
      {

         on_reset_focus_start_tick();

         plain_edit_on_delete(pgraphics, bBackIfSelectionEmpty);

         plain_edit_on_after_change_text(pgraphics, actioncontext);

      });

      set_need_redraw();

      post_redraw();

   }


   //bool plain_edit::plain_edit_delete_sel(::draw2d::graphics_pointer & pgraphics, bool & bFullUpdate, ::collection::index & iLineUpdate)
   //{

   //   _synchronous_lock synchronouslock(this->synchronization());

   //   character_count i1 = m_ptree->m_iSelBeg;

   //   character_count i2 = m_ptree->m_iSelEnd;

   //   ::sort_non_negative(i1, i2);

   //   if (i1 < 0 || i1 > get_text_length())
   //   {

   //      i1 = get_text_length();

   //   }

   //   if (i2 < 0 || i2 > get_text_length())
   //   {

   //      i2 = get_text_length();

   //   }

   //   if (i1 >= i2)
   //   {

   //      return false;

   //   }

   //   on_before_change_text();

   //   auto psetsel = __allocate plain_text_set_sel_command();

   //   psetsel->m_iPreviousSelBeg = m_ptree->m_iSelBeg;

   //   psetsel->m_iPreviousSelEnd = m_ptree->m_iSelEnd;

   //   string strSel;

   //   get_text(strSel, i1, i2);

   //   bFullUpdate = strSel.find_index('\n') >= 0 || strSel.find_index('\r') >= 0;

   //   if (!bFullUpdate)
   //   {

   //      iLineUpdate = plain_edit_sel_to_line(pgraphics, i1);

   //   }

   //   m_ptree->m_peditfile->seek(i1, ::e_seek_set);

   //   m_ptree->m_peditfile->Delete((memsize)(i2 - i1));

   //   m_pinsert = nullptr;

   //   IndexRegisterDelete(i1, i2 - i1);

   //   m_ptree->m_iSelEnd = i1;

   //   m_ptree->m_iSelBeg = m_ptree->m_iSelEnd;

   //   psetsel->m_iSelBeg = m_ptree->m_iSelBeg;

   //   psetsel->m_iSelEnd = m_ptree->m_iSelEnd;

   //   MacroBegin();

   //   MacroRecord(psetsel);

   //   MacroRecord(__allocate plain_text_file_command());

   //   MacroEnd();

   //   return true;

   //}


   void plain_edit::_001ReplaceSel(const ::scoped_string & scopedstrText)
   {

      bool bFullUpdate = true;

      ::collection::index iLineUpdate = -1;

      if (_001ReplaceSel(scopedstrText, bFullUpdate, iLineUpdate))
      {

         auto psystem = system();

         auto pdraw2d = psystem->draw2d();

         auto pgraphics = pdraw2d->create_memory_graphics(this);

         plain_edit_update(pgraphics, bFullUpdate, iLineUpdate);

      }

   }


   bool plain_edit::_001ReplaceSel(const ::scoped_string & scopedstrText, bool & bFullUpdate, ::collection::index & iLineUpdate)
   {

      _synchronous_lock synchronouslock(this->synchronization());

      character_count i1 = m_ptree->m_iSelBeg;

      character_count i2 = m_ptree->m_iSelEnd;

      ::sort_non_negative(i1, i2);

      if (i1 < 0 || i1 > get_text_length())
      {

         i1 = get_text_length();

      }

      if (i2 < 0 || i2 > get_text_length())
      {

         i2 = get_text_length();

      }

      if (i2 < i1)
      {

         return false;

      }

      on_before_change_text();

      auto psetsel = __allocate plain_text_set_sel_command();

      psetsel->m_iPreviousSelBeg = m_ptree->m_iSelBeg;

      psetsel->m_iPreviousSelEnd = m_ptree->m_iSelEnd;

      string strSel;

      get_text(strSel, i1, i2);

      bFullUpdate = strSel.find_index('\n') >= 0 || strSel.find_index('\r') >= 0;

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

      m_ptree->m_peditfile->Insert(scopedstrText, ansi_length(scopedstrText));

      IndexRegisterInsert(i1, pszText);

      m_pinsert = nullptr;

      IndexRegisterDelete(i1, i2 - i1);

      m_ptree->m_iSelEnd = i1;

      m_ptree->m_iSelBeg = m_ptree->m_iSelEnd;

      psetsel->m_iSelBeg = m_ptree->m_iSelBeg;

      psetsel->m_iSelEnd = m_ptree->m_iSelEnd;

      MacroBegin();

      MacroRecord(psetsel);

      MacroRecord(__allocate plain_text_file_command());

      MacroEnd();

      return true;

   }


   string plain_edit::get_ime_composition() const
   {

      if (!m_pitemComposing)
      {

         return "";

      }

      return ::string((const ::ansi_character *)m_pitemComposing->data(), m_pitemComposing->get_extent());

   }


   void plain_edit::_on_undo_edit_item(::file::edit_item_base * pedititem)
   {

      ::cast < ::file::insert_item > pinsertitem = pedititem;

      if (pinsertitem)
      {

         _on_undo_insert(pinsertitem);

         return;

      }

      ::cast < ::file::delete_item > pdeleteitem = pedititem;

      if (pdeleteitem)
      {

         _on_undo_delete(pdeleteitem);

         return;

      }

      ::cast < ::file::edit_group_item > pgrouptitem = pedititem;

      if (pgrouptitem)
      {

         for (auto & p : pgrouptitem->m_itema.rear_payloads())
         {

            _on_undo_edit_item(p);

         }

         return;

      }


   }

   
   void plain_edit::_on_undo_insert(::file::insert_item * pinsertitemParam)
   {

      auto pinsertitem = ::as_pointer(pinsertitemParam);

      queue_graphics_call([this, pinsertitem](::draw2d::graphics_pointer & pgraphics)
      {

         ::collection::index iLine1 = -1;

         ::collection::index iLine2 = -1;

         _plain_edit_update_for_delete(
            pgraphics,
            { pinsertitem->m_pdata, pinsertitem->m_size },
            pinsertitem->m_position,
            iLine1,
            iLine2);

         _update_line_start_array(iLine1);

         //if (iLine2 == iLine1)
         //{

         //   _plain_edit_update_extents(pgraphics, iLine1, iLine2);

         //}
         //else
         {

            _plain_edit_update_extents(pgraphics, -1, -1);

         }

      });

   }


   void plain_edit::_on_undo_delete(::file::delete_item * pdeleteitemParam)
   {

      auto pdeleteitem = ::as_pointer(pdeleteitemParam);

      queue_graphics_call([this, pdeleteitem](::draw2d::graphics_pointer & pgraphics)
      {

         ::collection::index iLine1 = -1;

         ::collection::index iLine2 = -1;

         _plain_edit_update_for_insert(
            pgraphics,
            pdeleteitem->m_memstorage,
            pdeleteitem->m_position,
            iLine1, 
            iLine2);

         _update_line_start_array(iLine1);

         //if (iLine2 == iLine1)
         //{

         //   _plain_edit_update_extents(pgraphics, iLine1, iLine2);

         //}
         //else
         {

            _plain_edit_update_extents(pgraphics, -1, -1);

         }

      });

   }


   void plain_edit::_on_redo_edit_item(::file::edit_item_base * pedititem)
   {

      ::cast < ::file::delete_item > pdeleteitem = pedititem;

      if (pdeleteitem)
      {

         _on_redo_delete(pdeleteitem);

         return;

      }

      ::cast < ::file::insert_item > pinsertitem = pedititem;

      if (pinsertitem)
      {

         _on_redo_insert(pinsertitem);

         return;

      }

      ::cast < ::file::edit_group_item > pgrouptitem = pedititem;

      if (pgrouptitem)
      {

         for (auto & p : pgrouptitem->m_itema)
         {

            _on_redo_edit_item(p);

         }

         return;

      }

   }


   void plain_edit::_on_redo_delete(::file::delete_item * pdeleteitemParam)
   {

      auto pdeleteitem = ::as_pointer(pdeleteitemParam);

      queue_graphics_call([this, pdeleteitem](::draw2d::graphics_pointer & pgraphics)
      {

         ::collection::index iLine1 = -1;

         ::collection::index iLine2 = -1;

         _plain_edit_update_for_delete(
            pgraphics,
            pdeleteitem->m_memstorage,
            pdeleteitem->m_position,
            iLine1,
            iLine2);

         _update_line_start_array(iLine1);

         //if (iLine2 == iLine1)
         //{

         //   _plain_edit_update_extents(pgraphics, iLine1, iLine2);

         //}
         //else
         {

            _plain_edit_update_extents(pgraphics, -1, -1);

         }

      });

   }


   void plain_edit::_on_redo_insert(::file::insert_item * pinsertitemParam)
   {

      auto pinsertitem = ::as_pointer(pinsertitemParam);

      queue_graphics_call([this, pinsertitem](::draw2d::graphics_pointer & pgraphics)
      {

         ::collection::index iLine1 = -1;

         ::collection::index iLine2 = -1;

         _plain_edit_update_for_insert(
            pgraphics,
            {pinsertitem->m_pdata, pinsertitem->m_size},
            pinsertitem->m_position,
            iLine1,
            iLine2);

         _update_line_start_array(iLine1);

         //if (iLine2 == iLine1)
         //{

         //   _plain_edit_update_extents(pgraphics, iLine1, iLine2);

         //}
         //else
         {

            _plain_edit_update_extents(pgraphics, -1, -1);

         }

      });


   }


   void plain_edit::_001OnMessageKey(::message::message * pmessage)
   {

      ::draw2d::graphics_pointer pgraphics;

      bool bUpdate = true;

      bool bFullUpdate = false;

      ::collection::index iLineUpdate = -1;

      auto psession = session();

      {

         information() << "plain_edit::_001OnMessageKey (1)";

         auto pkey = pmessage->m_union.m_pkey;

         string strChar;



         information() << "on_message_key_down (1)";

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

         information() << "on_message_key_down (2)";

         if (pkey->m_ekey == ::user::e_key_return)
         {

            auto psession = session();

            if (psession->is_key_pressed(::user::e_key_control) && psession->is_key_pressed(::user::e_key_alt))
            {

               pkey->m_bRet = false;

               return;

            }

            if ((!m_bMultiLine || m_bSendEnterKey) && ::user::interaction::get_parent() != nullptr)
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



            if (psession->is_key_pressed(::user::e_key_control))
            {

               pkey->m_bRet = true;

               clipboard_copy();

               return;

            }

         }
         else if (pkey->m_ekey == ::user::e_key_v ||
            (pkey->m_ekey == ::user::e_key_refer_to_text_member
               && pkey->m_strText.case_insensitive_order("v") == 0))
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

               _001EditCut(e_source_user);

               //clipboard_copy();

               //if (is_window_enabled())
               //{

               //   _001DeleteSel();

               //   //queue_graphics_call([this](::draw2d::graphics_pointer & pgraphics)
               //   //{

               //   //   plain_edit_on_delete(pgraphics);

               //   //});

               //   //set_need_redraw();

               //   //post_redraw();

               //}

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

               set_text_selection(0, get_text_length(), ::e_source_sync);

               return;

            }

         }
         else if (pkey->m_ekey == ::user::e_key_z)
         {

            if (is_window_enabled())
            {

               if (psession->is_key_pressed(::user::e_key_control))
               {

                  if (psession->is_key_pressed(::user::e_key_shift))
                  {

                     edit_redo();

                  }
                  else
                  {

                     edit_undo();

                  }

                  return;

               }

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

            _synchronous_lock synchronouslock(this->synchronization());

            bool bControl = psession->is_key_pressed(::user::e_key_control);

            bool bShift = psession->is_key_pressed(::user::e_key_shift);

            if (pkey->m_ekey == ::user::e_key_page_up)
            {

               if (is_text_composition_active())
               {

                  return;

               }

               queue_graphics_call([this, bShift](::draw2d::graphics_pointer & pgraphics)
                  {

                     on_reset_focus_start_tick();

                     int x;

                     ::collection::index iLine = plain_edit_sel_to_line_x(pgraphics, m_ptree->m_iSelEnd, x);

                     ::int_rectangle rectangleX;

                     GetFocusRect(rectangleX);

                     iLine -= (::collection::index)(rectangleX.height() / m_dLineHeight);

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
            else if (pkey->m_ekey == ::user::e_key_page_down)
            {

               if (is_text_composition_active())
               {

                  return;

               }

               queue_graphics_call([this, bShift](::draw2d::graphics_pointer & pgraphics)
                  {

                     on_reset_focus_start_tick();

                     int x;

                     ::collection::index iLine = plain_edit_sel_to_line_x(pgraphics, m_ptree->m_iSelEnd, x);

                     ::int_rectangle rectangleX;

                     GetFocusRect(rectangleX);

                     iLine += (::collection::index)(rectangleX.height() / m_dLineHeight);

                     if (iLine >= m_iaLineIndex.get_size())
                     {

                        iLine = m_iaLineIndex.get_upper_bound();

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

               information() << "plain_edit::on_message_character (key_back)";

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

                  //on_reset_focus_start_tick();

                  if (!m_bReadOnly)
                  {

                     _001DeleteSel(true, e_source_user);

                     //character_count i1 = m_ptree->m_iSelBeg;

                     //character_count i2 = m_ptree->m_iSelEnd;

                     //if (i1 != i2)
                     //{

                     //   _001DeleteSel();

                     //}
                     //else if (m_ptree->m_iSelEnd >= 0 && m_ptree->m_peditfile->get_length() > 0)
                     //{

                     //   on_before_change_text();

                     //   auto psetsel = __allocate plain_text_set_sel_command();

                     //   psetsel->m_iPreviousSelBeg = m_ptree->m_iSelBeg;

                     //   psetsel->m_iPreviousSelEnd = m_ptree->m_iSelEnd;

                     //   information() << "SelBeg : " << psetsel->m_iPreviousSelBeg;

                     //   information() << "SelEnd : " << psetsel->m_iPreviousSelEnd;

                     //   char buf[512];

                     //   memory_set(buf, 0, sizeof(buf));

                     //   character_count iProperBegin = maximum(0, m_ptree->m_iSelEnd - 256);
                     //   character_count iCur = m_ptree->m_iSelEnd - iProperBegin;
                     //   m_ptree->m_peditfile->seek(iProperBegin, ::e_seek_set);
                     //   m_ptree->m_peditfile->read(buf, sizeof(buf));
                     //   const ::ansi_character * psz;
                     //   character_count iMultiByteUtf8DeleteCount;
                     //   if (iCur > 1 && buf[iCur - 1] == '\n' && buf[iCur - 2] == '\r')
                     //   {

                     //      psz = &buf[iCur - 2];
                     //      iMultiByteUtf8DeleteCount = 2;

                     //   }
                     //   else
                     //   {

                     //      psz = unicode_prior(&buf[iCur], buf);

                     //      if (scopedstr == nullptr)
                     //      {

                     //         psz = maximum((char *)buf, (char *)&buf[iCur - 1]);

                     //      }

                     //      iMultiByteUtf8DeleteCount = &buf[iCur] - psz;

                     //      information() << "iMultiByteUtf8DeleteCount : " << iMultiByteUtf8DeleteCount;

                     //   }

                     //   index i2 = m_ptree->m_iSelEnd;
                     //   index i1 = i2 - iMultiByteUtf8DeleteCount;

                     //   string strSel;

                     //   get_text(strSel, i1, i2);

                     //   information() << "strSel : " << strSel;

                     //   bFullUpdate = strSel.find_index('\n') >= 0 || strSel.find_index('\r') >= 0;

                     //   if (!bFullUpdate)
                     //   {

                     //      iLineUpdate = plain_edit_sel_to_line(pgraphics, i1);

                     //   }

                     //   m_ptree->m_iSelEnd -= iMultiByteUtf8DeleteCount;
                     //   m_ptree->m_peditfile->seek(m_ptree->m_iSelEnd, ::e_seek_set);
                     //   m_ptree->m_peditfile->Delete((memsize)iMultiByteUtf8DeleteCount);

                     //   m_pinsert = nullptr;

                     //   IndexRegisterDelete(m_ptree->m_iSelEnd, iMultiByteUtf8DeleteCount);
                     //   m_ptree->m_iSelBeg = m_ptree->m_iSelEnd;
                     //   psetsel->m_iSelBeg = m_ptree->m_iSelBeg;
                     //   psetsel->m_iSelEnd = m_ptree->m_iSelEnd;
                     //   MacroBegin();
                     //   MacroRecord(psetsel);
                     //   MacroRecord(__allocate plain_text_file_command());
                     //   MacroEnd();

                     //   _001SetSelEnd(m_ptree->m_iSelEnd);

                     //}

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

                  _001DeleteSel(false, e_source_user);
                  //queue_graphics_call([this](::draw2d::graphics_pointer & pgraphics)
                  //{

                  //   plain_edit_on_delete(pgraphics);

                  //});

                  //set_need_redraw();

                  //post_redraw();

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

                     int x;

                     ::collection::index iLine = plain_edit_sel_to_line_x(pgraphics, m_ptree->m_iSelEnd, x);

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

                     _ensure_selection_visible_x(pgraphics);

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

                     int x;

                     ::collection::index iLine = plain_edit_sel_to_line_x(pgraphics, m_ptree->m_iSelEnd, x);

                     iLine++;

                     if (iLine >= m_iaLineIndex.get_size())
                     {

                        iLine = m_iaLineIndex.get_upper_bound();

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

                     _ensure_selection_visible_x(pgraphics);

                  });

            }
            else if (pkey->m_ekey == ::user::e_key_right)
            {

               _synchronous_lock synchronouslock(this->synchronization());

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
                     m_ptree->m_iSelEnd += unicode_next(buf) - buf;
                  }
                  set_selection_end(m_ptree->m_iSelEnd, e_source_user);
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
                        m_ptree->m_iSelEnd -= psz - unicode_prior(scopedstr, buf);
                     }
                  }
                  else
                  {
                     m_ptree->m_iSelEnd--;
                  }
                  set_selection_end(m_ptree->m_iSelEnd, e_source_user);
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
                     else
                     {

                        ::collection::index iLine = plain_edit_sel_to_line(pgraphics, m_ptree->m_iSelEnd);

                        m_ptree->m_iSelEnd = plain_edit_line_column_to_sel(pgraphics, iLine, 0);

                     }

                     if (!bShift)
                     {

                        m_ptree->m_iSelBeg = m_ptree->m_iSelEnd;

                     }

                     _ensure_selection_visible_x(pgraphics);

                     });

               set_need_redraw();

               post_redraw();

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

                     ::collection::index iSelEnd = -1;

                     if (bControl)
                     {

                        ::collection::index iLine = m_iaLineIndex.get_upper_bound();

                        m_ptree->m_iSelEnd = plain_edit_line_x_to_sel(pgraphics, iLine, int(m_iaLineLength[iLine]));

                        _001EnsureVisibleLine(pgraphics, iLine);

                     }
                     else
                     {

                        ::collection::index iLine = plain_edit_sel_to_line(pgraphics, m_ptree->m_iSelEnd);

                        m_ptree->m_iSelEnd = plain_edit_line_column_to_sel(pgraphics, iLine, -1);

                     }

                     _ensure_selection_visible_x(pgraphics);

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

               //#ifndef WINDOWS_DESKTOP

               if (m_bMultiLine)
               {

                  insert_text("\n", true, e_source_user);

               }

               //#endif

            }
            else if (is_window_enabled())
            {

               //#if defined(WINDOWS_DESKTOP) || defined(LINUX) || defined(MACOS) || defined(FREEBSD) || defined(OPENBSD)
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
               //                     int iChar = (int)pkey->m_nChar;
               //                     if (iChar == '\r')
               //                        iChar = '\n';
               //                     if (bShift)
               //                     {
               //                        iChar |= I32_MINIMUM;
               //                     }
               //                     int iCode = pkey->m_nFlags & 0xff;
               //                     if (bShift)
               //                     {
               //                        iCode |= I32_MINIMUM;
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
               //                     //str = psession->()->keyboard()->process_key(pkey);
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
               && pkey->m_ekey != ::user::e_key_page_up && pkey->m_ekey != ::user::e_key_page_down))
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

      information() << "plain_edit::on_message_char (1)";

      auto pkey = pmessage->m_union.m_pkey;

      string str;

      //on_reset_focus_start_tick();

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


   void plain_edit::get_text_composition_area(::int_rectangle & rectangle)
   {

      character_count iBeg;

      character_count iEnd;

      get_text_selection(iBeg, iEnd);

      // int x;

      //auto pgraphics = ::draw2d::create_memory_graphics();

      //auto iLine = plain_edit_sel_to_line_x(pgraphics, iEnd, x);

      int x = m_iLastSelectionEndX;

      double y = m_iLastSelectionEndLine * m_dLineHeight - get_context_offset().y();

      double y2 = y + m_dLineHeight;

      ::int_point point((int)x, (int)y);

      rectangle = this->rectangle();

      rectangle.left() = (int)x;

      rectangle.top() = (int)y;

      rectangle.bottom() = (int)y2;

      client_to_screen()(rectangle);

      get_wnd()->screen_to_client()(rectangle);

   }


   void plain_edit::edit_on_text(string str)
   {

      ::user::interaction::edit_on_text(str);

   }


   void plain_edit::edit_on_sel(character_count iSelBeg, character_count iSelEnd)
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

         ::collection::index i1 = (::collection::index)(m_pitemComposing->m_position + m_pitemComposing->get_extent());

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

         get_text(strText);

         information("\nplain_edit::on_text_composition (m_pitemComposing != nullptr) Current Text: " + strText + "\n");

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

      _synchronous_lock synchronouslock(this->synchronization());

      if (m_pitemComposing
         && !strText.contains('\r')
         && !strText.contains('\n'))
      {

         m_ptree->m_peditfile->append_insert_item_data(m_pitemComposing.get(), strText);

         ::collection::index i1 = (::collection::index)(m_pitemComposing->m_position + m_pitemComposing->get_extent());

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

         get_text(strText);

         information("Current Text: " + strText + "\n");

         m_pitemComposing.release();

      }

   }


   void plain_edit::on_text_composition_done()
   {

      //#ifdef WINDOWS_DESKTOP
      //
      //      text_composition_composite::on_text_composition_done();
      //
      //#endif

      m_pitemComposing.release();

      set_need_redraw();

      post_redraw();

   }


   void plain_edit::clear_ime_composition()
   {

      m_pitemComposing.release();

      text_composition_composite::clear_ime_composition();

   }


   bool plain_edit::InputConnectionBeginBatchEdit(bool bSuper)
   {

      _synchronous_lock synchronouslock(this->synchronization());

      //MacroBegin();

      m_iInputConnectionBatch++;

      return true;

   }


   bool plain_edit::InputConnectionEndBatchEdit(bool bSuper)
   {

      _synchronous_lock synchronouslock(this->synchronization());

      //MacroEnd();

      m_iInputConnectionBatch--;

      if (m_iInputConnectionBatch == 0)
      {

         queue_selection_synchronization();

      }

      return true;

   }


   bool plain_edit::InputConnectionCommitText(const ::scoped_string & scopedstrText, character_count iNewCursorPosition, bool bSuper)
   {

      InputConnectionSetComposingText(strText, iNewCursorPosition, bSuper);

      InputConnectionFinishComposingText(bSuper);

      return true;

   }


   bool plain_edit::InputConnectionDeleteSurroundingText(character_count iBeforeLength, character_count iAfterLength, bool bSuper)
   {

      queue_graphics_call([this, iBeforeLength, iAfterLength](::draw2d::graphics_pointer & pgraphics)
      {

         plain_edit_on_delete_surrounding_text(pgraphics, iBeforeLength, iAfterLength);

      });

      set_need_redraw();

      post_redraw();

      return true;

   }


   bool plain_edit::InputConnectionSetComposingText(const ::scoped_string & scopedstrTextParam, character_count iNewCursorPosition, bool bSuper)
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

               insert_text(pgraphics, strText, false);

               if (!m_pitemComposing)
               {

                  m_pitemComposing = m_pinsert;

               }

            }

            //bool bAlreadyComposing = m_pitemComposing && !bTextHasNewLine;

            character_count i1 = iNewCursorPosition;

            ::collection::index iAfterComposingCursorPosition = -1;

            //if (::is_set(m_pitemComposing))
            //{

            //   string strFull;

            //   get_text(strFull);

            //   character_count iOffset = 0;

            //   if (iNewCursorPosition > 0)
            //   {

            //      iAfterComposingCursorPosition = (index)(m_pitemComposing->m_position + m_pitemComposing->get_extent());

            //      if (iNewCursorPosition > 1)
            //      {

            //         wd16_string wstrFull(strFull.substr(iAfterComposingCursorPosition));

            //         iOffset = wd16_to_ansi_len(wstrFull, iNewCursorPosition - 1);

            //      }

            //      iAfterComposingCursorPosition += iOffset;

            //   }
            //   else
            //   {

            //      iAfterComposingCursorPosition = (index)(m_pitemComposing->m_position);

            //      if (iNewCursorPosition < 0)
            //      {

            //         wd16_string wstrFull(strFull.left(iAfterComposingCursorPosition));

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

               get_text(strFull);

               character_count iOffset = 0;

               if (iNewCursorPosition > 0)
               {

                  if (iNewCursorPosition > 1)
                  {

                     wd16_string wstrFull(strFull.substr(iAfterComposingCursorPosition));

                     iOffset = wd16_to_ansi_len(wstrFull, iNewCursorPosition - 1);

                  }

                  iAfterComposingCursorPosition += iOffset;

               }
               else
               {

                  if (iNewCursorPosition < 0)
                  {

                     wd16_string wstrFull(strFull.left(iAfterComposingCursorPosition));

                     iOffset = wd16_to_ansi_len(wstrFull, wstrFull.length() + iNewCursorPosition);

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

               set_text_selection(iAfterComposingCursorPosition, iAfterComposingCursorPosition, ::e_source_sync);

            }

            _ensure_selection_visible_x(pgraphics);

         });

      return true;

   }


   bool plain_edit::InputConnectionSetComposingRegion(character_count iComposingStart, character_count iComposingEnd, bool bSuper)
   {

      queue_graphics_call([this, iComposingStart, iComposingEnd](::draw2d::graphics_pointer & pgraphics)
         {

            _synchronous_lock synchronouslock(this->synchronization());

            character_count iCandidateBeg = iComposingStart;

            character_count iCandidateEnd = iComposingEnd;

            m_ptree->m_peditfile->MacroBegin();

            m_pitemComposing.release();

            string strText;

            get_text(strText);

            __sort(iCandidateBeg, iCandidateEnd);

            wd16_string wstrText(strText);

            character_count iStart = wd16_to_ansi_len(wstrText, iCandidateBeg);

            character_count iEnd = wd16_to_ansi_len(wstrText, iCandidateEnd);

            string strComposition(strText.substr(iStart, iEnd - iStart));

            m_ptree->m_peditfile->seek(iStart, ::e_seek_set);

            m_ptree->m_peditfile->Delete((memsize)(iEnd - iStart));

            IndexRegisterDelete(iStart, iEnd - iStart);

            m_ptree->m_peditfile->seek(iStart, ::e_seek_set);

            auto iLength = strComposition.length();

            m_pinsert = m_ptree->m_peditfile->Insert(strComposition, iLength);

            IndexRegisterInsert(iStart, strComposition);

            m_pitemComposing = m_pinsert;

            m_ptree->m_peditfile->MacroEnd();

            MacroBegin();
            MacroRecord(__allocate plain_text_file_command());
            MacroEnd();

         });

      return true;

   }


   bool plain_edit::InputConnectionSetSelection(character_count iStart, character_count iEnd, bool bSuper)
   {

      string strText;

      get_text(strText);

      wd16_string wstrText(strText);

      character_count iAnsiBeg = wd16_to_ansi_len(wstrText, iStart);

      character_count iAnsiEnd = wd16_to_ansi_len(wstrText, iEnd);

      auto psetsel = __allocate plain_text_set_sel_command();

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

      queue_graphics_call([this](::draw2d::graphics_pointer & pgraphics)
         {

            m_pitemComposing.release();

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

      queue_graphics_call([this](::draw2d::graphics_pointer & pgraphics)
         {

            auto pwindowing = windowing();

            auto ptexteditorinterface = pwindowing->get_text_editor_interface();

            if (::is_set(ptexteditorinterface))
            {

               character_count iSelectionStart = 0;

               character_count iSelectionEnd = 0;

               character_count iComposingStart = 0;

               character_count iComposingEnd = 0;

               get_text_selection(iSelectionStart, iSelectionEnd, iComposingStart, iComposingEnd);

               ptexteditorinterface->set_input_method_manager_selection(iSelectionStart, iSelectionEnd, iComposingStart, iComposingEnd);

            }

         });

      set_need_redraw();

      post_redraw();

   }


   void plain_edit::_001OnSysChar(::message::message * pmessage)
   {

      _synchronous_lock synchronouslock(this->synchronization());

      auto pkey = pmessage->m_union.m_pkey;

      if (pkey->m_ekey == ::user::e_key_delete)
      {

         if (!m_bReadOnly)
         {
            character_count i1 = m_ptree->m_iSelBeg;
            character_count i2 = m_ptree->m_iSelEnd;
            if (i1 != i2)
            {
               ::sort_non_negative(i1, i2);
               m_ptree->m_peditfile->seek(i1, ::e_seek_set);
               m_ptree->m_peditfile->Delete((memsize)(i2 - i1));

               m_pinsert = nullptr;

               m_ptree->m_iSelEnd = i1;
               m_ptree->m_iSelBeg = m_ptree->m_iSelEnd;
            }
            else if (m_ptree->m_iSelEnd < m_ptree->m_peditfile->get_length())
            {
               char buf[512];
               memory_set(buf, 0, sizeof(buf));
               character_count iProperBegin = maximum(0, m_ptree->m_iSelEnd - 256);
               character_count iCur = m_ptree->m_iSelEnd - iProperBegin;
               m_ptree->m_peditfile->seek(iProperBegin, ::e_seek_set);
               m_ptree->m_peditfile->read(buf, sizeof(buf));
               const ::ansi_character * psz = unicode_prior(&buf[iCur], buf);
               character_count iMultiByteUtf8DeleteCount = &buf[iCur] - psz;
               m_ptree->m_peditfile->seek(m_ptree->m_iSelEnd, ::e_seek_set);
               m_ptree->m_peditfile->Delete((memsize)(iMultiByteUtf8DeleteCount));

               m_pinsert = nullptr;

               IndexRegisterDelete(m_ptree->m_iSelEnd, iMultiByteUtf8DeleteCount);
               m_ptree->m_iSelBeg = m_ptree->m_iSelEnd;
            }
         }
      }
   }


   void plain_edit::_001OnKeyboardFocusTimer(::enum_timer etimer)
   {

      if (etimer == e_timer_caret_flashing)
      {

         if (has_keyboard_focus() && is_window_visible())// && m_timeLastDraw.elapsed() > m_timeCaretPeriod / 8)
         {

            auto bCaretOn = is_caret_on();

            //            if (bCaretOn)
            //            {
            //
            //               information() << "CARET ON!!!!";
            //
            //            }
            //            else
            //            {
            //
            //               information() << "CARET OFF!!!!";
            //
            //            }

            if (is_different(m_bLastCaret, bCaretOn))
            {

               m_bLastCaret = bCaretOn;

               //               if (bCaretOn)
               //               {
               //
               //                  information() << "CARET ON!!!!";
               //
               //               }
               //               else
               //               {
               //
               //                  information() << "CARET OFF!!!!";
               //
               //               }

               set_need_redraw();

               post_redraw();

            }

         }

      }

   }


   void plain_edit::plain_edit_one_line_up(::draw2d::graphics_pointer & pgraphics)
   {

      ::int_point pointOffset = get_context_offset();

      set_context_offset_y(pointOffset.y() - m_dLineHeight, ::user::e_layout_design);

      double dHeight = 0.;

      m_iImpactOffset = 0;

      ::collection::count iLineSize;

      ::collection::index i = 0;

      //copy(pointOffset, get_context_offset());

      while (pointOffset.y() > dHeight && i < m_iaLineLength.get_size())
      {

         iLineSize = m_iaLineLength[i];

         dHeight += m_dLineHeight;

         m_iImpactOffset += iLineSize;

         i++;

      }

   }

   void plain_edit::IndexRegisterDelete(character_count iSel, character_count iCount)
   {
      __UNREFERENCED_PARAMETER(iSel);
      __UNREFERENCED_PARAMETER(iCount);
      //CreateLineIndex();
      //m_peditor->modifyEvent(0);
      /*   char flag;
         m_iImpactOffset = 0;
         int iLineSize;
         unsigned int uRead;
         int iPos = 0;
         int iLineStart = -1;
         int iLineEnd = -1;
         int iLineStartRemain = -1;
         int iLineEndRemain = -1;
         int iLine = 0;
         int i = 0;
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

   void plain_edit::IndexRegisterInsert(character_count iSel, const ::scoped_string & scopedstrWhat)

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

         _synchronous_lock synchronouslock(this->synchronization());

         //string str;
         //get_text(str);

         auto iLen = get_text_length();

         if (m_ptree->m_iSelBeg > iLen)
            m_ptree->m_iSelBeg = (character_count)(iLen);
         else if (m_ptree->m_iSelBeg < 0)
            m_ptree->m_iSelBeg = 0;

         if (m_ptree->m_iSelEnd > iLen)
            m_ptree->m_iSelEnd = (character_count)(iLen);
         else if (m_ptree->m_iSelEnd < 0)
            m_ptree->m_iSelEnd = 0;

         //m_bGetTextNeedUpdate = 1;

         //plain_edit_create_line_index(pgraphics);

         m_dy = -1;

         //m_bCalcLayoutHintNoTextChange = false;

         //plain_edit_on_calc_layout(pgraphics);

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

      if (m_bSetTextSelectionUpdatePending)
      {

         m_bSetTextSelectionUpdatePending = false;

         //         bool bSelectionWasAtEnd = m_bLastSelectionWasAtEnd;
         //
         //         if (bSelectionWasAtEnd)
         //         {
         //
         //            auto iTextLength = get_text_length();
         //
         //            set_text_selection(iTextLength, iTextLength, e_source_sync);
         //
         //         }
         //         else
         {

            ::character_count iSelectionBegin = 0;

            ::character_count iSelectionEnd = 0;

            iSelectionBegin = plain_edit_line_x_to_sel(pgraphics, m_iLastSelectionBeginLine, m_iLastSelectionBeginX);

            iSelectionEnd = plain_edit_line_x_to_sel(pgraphics, m_iLastSelectionEndLine, m_iLastSelectionEndX);

            set_text_selection(iSelectionBegin, iSelectionEnd, e_source_sync);

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

               get_text(strText);

               ptexteditorinterface->set_editor_text(strText);

               ::character_count iBeg = -1;

               ::character_count iEnd = -1;

               get_text_selection(iBeg, iEnd);

               ptexteditorinterface->set_editor_selection(iBeg, iEnd);

            }

         }

      }
      catch (...)
      {

      }

      //printf("xxxxxxxxxx4\n");

      //set_need_redraw();

      //printf("xxxxxxxxxx4.1\n");

      //post_redraw();

      //printf("xxxxxxxxxx5\n");

   }


   void plain_edit::plain_edit_on_line_update(::draw2d::graphics_pointer & pgraphics, ::collection::index iLine, const ::action_context & context)
   {

      {

         _synchronous_lock synchronouslock(this->synchronization());

         //string str;
         //get_text(str);

         auto iLen = get_text_length();

         if (m_ptree->m_iSelBeg > iLen)
            m_ptree->m_iSelBeg = (character_count)(iLen);
         else if (m_ptree->m_iSelBeg < 0)
            m_ptree->m_iSelBeg = 0;

         if (m_ptree->m_iSelEnd > iLen)
            m_ptree->m_iSelEnd = (character_count)(iLen);
         else if (m_ptree->m_iSelEnd < 0)
            m_ptree->m_iSelEnd = 0;

         //m_bGetTextNeedUpdate = 1;
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

      //set_need_redraw();

   }


   void plain_edit::MacroBegin()
   {
      ::pointer<::user::plain_text_group_command>pgroupcommand = __allocate plain_text_group_command();
      pgroupcommand->m_pparent = m_ptree->m_pgroupcommand;
      m_ptree->m_pgroupcommand = pgroupcommand;
   }

   void plain_edit::MacroEnd()
   {
      _synchronous_lock synchronouslock(this->synchronization());
      if (m_ptree->m_pgroupcommand == nullptr)
      {
         ASSERT(false);
         return;
      }
      if (m_ptree->m_pgroupcommand->m_pparent == nullptr)
      {
         MacroRecord(m_ptree->m_pgroupcommand);
      }
      else
      {
         ::pointer<plain_text_group_command> pgroupcommand = m_ptree->m_pgroupcommand->m_pparent;
         if (pgroupcommand == nullptr)
         {
            ASSERT(false);
            return;
         }

         pgroupcommand->m_commanda.add(m_ptree->m_pgroupcommand);

      }
      m_ptree->m_pgroupcommand = m_ptree->m_pgroupcommand->m_pparent;
   }

   void plain_edit::MacroDiscard()
   {
      _synchronous_lock synchronouslock(this->synchronization());
      if (m_ptree->m_pgroupcommand == nullptr)
      {
         ASSERT(false);
         return;
      }
      //if (m_ptree->m_pgroupcommand->m_pparent == nullptr)
      //{
      //   MacroRecord(m_ptree->m_pgroupcommand);
      //}
      m_ptree->m_pgroupcommand = m_ptree->m_pgroupcommand->m_pparent;
   }

   void plain_edit::MacroRecord(::pointer<plain_text_command>pcommand)
   {
      _synchronous_lock synchronouslock(this->synchronization());
      if (m_ptree->m_pgroupcommand != nullptr && m_ptree->m_pgroupcommand != pcommand)
      {
         m_ptree->m_pgroupcommand->m_commanda.add(pcommand);
         return;
      }

      m_ptreeitem = m_ptree->insert_item(pcommand, ::data::e_relative_macro_record, m_ptreeitem);

   }


   bool plain_edit::__plain_edit_undo()
   {

      _synchronous_lock synchronouslock(this->synchronization());

      if (!CanUndo())
      {

         return false;

      }

      ::pointer<plain_text_command>pcommand = m_ptreeitem->m_pitem;

      pcommand->Undo(m_ptree);

      m_ptreeitem = m_ptreeitem->get_previous_or_parent();

      return true;

   }


   bool plain_edit::__plain_edit_redo()
   {

      //{

      //   _synchronous_lock synchronouslock(this->synchronization());

      //   if (m_ptreeitem == nullptr)
      //   {

      //      return false;

      //   }

      //   if (m_ptree->m_iBranch < 0
      //      || m_ptree->m_iBranch >= GetRedoBranchCount())
      //   {
      //      return false;
      //   }

      _synchronous_lock synchronouslock(this->synchronization());

      if (!CanRedo())
         return false;

      //queue_graphics_call([this](::draw2d::graphics_pointer & pgraphics)
        // {


            ::pointer<::data::tree_item<plain_text_command>>ptreeitem;

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

            ::pointer<plain_text_command>pcommand = ptreeitem->m_pitem;
            //m_pgraphicsPlainEdit = pgraphics;

            pcommand->Redo(m_ptree);
            //m_pgraphicsPlainEdit.release();


   //});

      return true;

   }


   bool plain_edit::edit_undo()
   {

      if (!__plain_edit_undo())
      {

         return false;

      }

      //queue_graphics_call([this](::draw2d::graphics_pointer & pgraphics)
      //{

      //   //plain_edit_create_line_index(pgraphics);

      //   //m_bGetTextNeedUpdate = true;

      //   plain_edit_on_update(pgraphics, ::e_source_user);

      //});

      set_need_redraw();

      post_redraw();

      return true;

   }


   bool plain_edit::edit_redo()
   {

      if (!__plain_edit_redo())
      {

         return false;

      }

      queue_graphics_call([this](::draw2d::graphics_pointer & pgraphics)
      {

         //plain_edit_create_line_index(pgraphics);

         //m_bGetTextNeedUpdate = true;

         plain_edit_on_update(pgraphics, ::e_source_user);
         //plain_edit_on_after_change_text(pgraphics, ::e_source_user);

      });

      return true;

   }


   bool plain_edit::CanUndo()
   {
      _synchronous_lock synchronouslock(this->synchronization());
      return m_ptreeitem != m_ptree->get_base_item();
   }

   bool plain_edit::CanRedo()
   {
      _synchronous_lock synchronouslock(this->synchronization());
      return m_ptreeitem &&
         m_ptree->m_iBranch >= 0
         && m_ptree->m_iBranch < GetRedoBranchCount();
      //(m_ptree->m_iBranch < m_ptreeitem->get_expandable_children_count()
      //|| m_ptreeitem->get_next() != nullptr);
   }

   ::collection::count plain_edit::GetRedoBranchCount()
   {
      _synchronous_lock synchronouslock(this->synchronization());

      return m_ptreeitem->get_expandable_children_count()
         + (m_ptreeitem->get_next() != nullptr ? 1 : 0)
         + (m_ptreeitem->first_child() != nullptr ? 1 : 0);
   }



   void plain_edit::set_text(const ::scoped_string & scopedstrParam, const ::action_context & actioncontext)
   {

      ::character_count iSelBeg = 0;

      ::character_count iSelEnd = 0;

      __check_refdbg

         get_text_selection(iSelBeg, iSelEnd);

      __check_refdbg

         //      ::character_count iTextLength = get_text_length();
         //
         //      m_bLastSelectionWasAtEnd = (iSelBeg == iSelEnd) && (iSelEnd == iTextLength);

         string str(scopedstrParam);

      {

         __check_refdbg

            _synchronous_lock synchronouslock(this->synchronization());

         __check_refdbg

            if (m_bParseDataPacks)
            {

               __check_refdbg

                  m_base64map.erase_all();

               __check_refdbg

                  auto psystem = system();

               __check_refdbg

                  psystem->_001AddPacks(m_base64map, str);

               __check_refdbg

            }

         if (!m_ptree)
         {

            return;

         }

         if (m_ptree->m_peditfile->get_length() > 0)
         {

            __check_refdbg

               m_ptree->m_peditfile->seek(0, ::e_seek_set);

            __check_refdbg

               m_ptree->m_peditfile->Delete((memsize)m_ptree->m_peditfile->get_length());

            __check_refdbg

         }

         if (str.has_character())
         {

            __check_refdbg

               m_ptree->m_peditfile->seek(0, ::e_seek_set);

            __check_refdbg

               m_ptree->m_peditfile->Insert(str, str.length());

            __check_refdbg

         }

      }

      //m_bSetTextSelectionUpdatePending = true;

      __check_refdbg

         queue_graphics_call([this, actioncontext](::draw2d::graphics_pointer & pgraphics)
         {

            plain_edit_on_update(pgraphics, actioncontext);

         });

      __check_refdbg

         set_need_redraw();

      __check_refdbg

         post_redraw();

      __check_refdbg

   }


   void plain_edit::set_text_and_selection(const ::scoped_string & scopedstrParam, character_count iSelBeg, character_count iSelEnd, const ::action_context & actioncontext)
   {

      ::character_count iTextLength = get_text_length();

      //      m_bLastSelectionWasAtEnd = (iSelBeg == iSelEnd) && (iSelEnd == iTextLength);

      string str(scopedstrParam);

      {

         _synchronous_lock synchronouslock(this->synchronization());

         if (m_bParseDataPacks)
         {

            m_base64map.erase_all();

            auto psystem = system();

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

         if (str.has_character())
         {

            m_ptree->m_peditfile->seek(0, ::e_seek_set);

            m_ptree->m_peditfile->Insert(str, str.length());

         }

         m_ptree->m_iSelBeg = iSelBeg;

         m_ptree->m_iSelEnd = iSelEnd;

         m_bNewSel = true;

      }

      queue_graphics_call([this, actioncontext](::draw2d::graphics_pointer & pgraphics)
      {

         plain_edit_on_update(pgraphics, actioncontext);

      });

      set_need_redraw();

      post_redraw();

      //      if (actioncontext.is_user_source())
      //      {
      //
      //         auto pwindowing = windowing();
      //
      //         auto ptexteditorinterface = pwindowing->get_text_editor_interface();
      //
      //         if (::is_set(ptexteditorinterface))
      //         {
      //
      //            string strText;
      //
      //            //get_text(strText);
      //
      //            get_text(strText);
      //
      //            //      //operating_system_driver::get()->m_iInputMethodManagerSelectionStart = ansi_to_wd16_len(strText, iBeg);
      //
      //            //      //operating_system_driver::get()->m_iInputMethodManagerSelectionEnd = ansi_to_wd16_len(strText, iEnd);
      //
      //            //auto iSelectionStart = ansi_to_wd32_len(strText, m_ptree->m_iSelBeg);
      //
      //            //auto iSelectionEnd = ansi_to_wd32_len(strText, m_ptree->m_iSelEnd);
      //            auto iSelectionStart = m_ptree->m_iSelBeg;
      //
      //            auto iSelectionEnd = m_ptree->m_iSelEnd;
      //
      //            ptexteditorinterface->set_editor_selection(iSelectionStart, iSelectionEnd);
      //
      //            //      if (m_pitemComposing)
      //            //      {
      //
      //            //         auto iCandidateStart = ansi_to_wd16_len(strText, m_pitemComposing->m_position);
      //
      //            //         auto iCandidateEnd = ansi_to_wd16_len(strText, m_pitemComposing->m_position + m_pitemComposing->get_extent());
      //
      //            //         ptexteditorinterface->set_input_method_manager_candidate_position(iCandidateStart, iCandidateEnd);
      //
      //            //      }
      //            //      else
      //            //      {
      //
      //            //         ptexteditorinterface->synchronize_input_method_manager_with_selection_end();
      //
      //            //      }
      //
      //         }
      //
      //      }

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


      //auto psystem = system();

      //auto pdraw2d = psystem->draw2d();

      //auto pgraphics = pdraw2d->create_memory_graphics(this);

      //plain_edit_create_line_index(pgraphics);

      //m_bGetTextNeedUpdate = true;

      //set_need_redraw();

      //plain_edit_on_calc_layout(pgraphics);


      if (m_callbackOnAfterChangeText)
      {

         m_callbackOnAfterChangeText(this, actioncontext);

      }

      if (actioncontext.is_user_source())
      {

         //if (m_linkedpropertyText)
         //{

         //   get_text(m_linkedpropertyText.m_pproperty->string_reference());

         //   auto papp = get_app();

         //   papp->on_property_changed(m_linkedpropertyText.m_pproperty, actioncontext);

         //}

      }

      string strText;

      get_text(strText);

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

      str = get_selection_text();

      // commenting str.replace_with below fix app-core/plain_text copy and
      // paste at Windows
      //str.replace_with("\r\n", "\r");

      auto pwindow = window();

      auto pcopydesk = pwindow->copydesk();

      pcopydesk->set_plain_text(str);

   }


   bool plain_edit::get_line_color(::color::color & color32, const ::scoped_string & scopedstrLine)
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


   void plain_edit::on_message_scroll_y(::message::message * pmessage)
   {

   }


   int plain_edit::get_wheel_scroll_delta()
   {

      return (int)(m_dLineHeight * 3.0);

   }


   void plain_edit::on_message_scroll_x(::message::message * pmessage)
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

   //      informationf("Failed to create control");

   //      return false;

   //   }

   //   display(e_display_none);

   //   //m_bMultiLine = pdescriptor->has_function(e_control_function_edit_multi_line);

   //   return true;

   //}


   enum_input_type plain_edit::preferred_input_type()
   {

      return e_input_type_text;

   }


   bool plain_edit::keyboard_focus_is_focusable()
   {

      return is_window_visible();

   }


   void plain_edit::on_set_keyboard_focus()
   {

      information() << "plain_edit::on_set_keyboard_focus";

      m_ewindowflag |= e_window_flag_focus;

      set_timer(e_timer_caret_flashing, 50_ms, nullptr);

      on_reset_focus_start_tick();

      if (!m_bCaretVisible)
      {

         m_bCaretVisible = true;

      }


      if (!m_bMultiLine)
      {

         character_count iBegAll = 0;

         character_count iEndAll = get_text_length();

         set_text_selection(iBegAll, iEndAll, e_source_user);

         m_bNewFocusSelectAll = true;

         m_timeNewFocusSelectAll.Now();

         m_iNewFocusSelectAllSelBeg = -1;
         m_iNewFocusSelectAllSelEnd = -1;
         m_iNewFocusSelectAllColumn = -1;

      }


#ifdef WINDOWS_DESKTOP

      on_text_composition_message(TEXT_COMPOSITION_MESSAGE_UPDATE_CARET);

#endif

      auto pwindowing = this->windowing();

      auto ptexteditorinterface = pwindowing->get_text_editor_interface();

      if (::is_set(ptexteditorinterface))
      {

         character_count iBeg = 0;

         character_count iEnd = 0;

         get_text_selection(iBeg, iEnd);

         string strText;

         get_text(strText);

         ptexteditorinterface->set_editor_selection(iBeg, iEnd);

         ptexteditorinterface->set_editor_text(strText);

         ptexteditorinterface->show_software_keyboard();

      }

      set_need_redraw();

      post_redraw();

   }


   void plain_edit::on_kill_keyboard_focus()
   {

      information() << "plain_edit::on_kill_keyboard_focus";

      kill_timer(e_timer_caret_flashing);

      if (m_bCaretVisible)
      {

         m_bCaretVisible = false;

#ifdef WINDOWS_DESKTOP

         ::DestroyCaret();

#endif

      }

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


   void plain_edit::destroy()
   {

      m_pcontrolstyle.release();

      if (m_ptree)
      {

         listen(m_ptree, false);

      }

      m_ptree.release();

      ::user::scroll_base::destroy();

      ::user::text_composition_composite::destroy();

   }


   ::pointer<::item>plain_edit::on_allocate_item()
   {

      return __allocate plain_text_command();

   }


   void plain_edit::set_root(plain_text_tree * pdata, bool bOwnData)
   {

      _synchronous_lock lockRoot(synchronization());

      if (m_ptree != nullptr && m_bOwnData)
      {

         m_ptree.release();

      }

      m_ptree = pdata;

      m_ptreeitem = m_ptree->get_base_item();

      m_bOwnData = m_ptree != nullptr && bOwnData;

      if (m_ptree != nullptr)
      {

         listen(m_ptree);

      }

   }


   void plain_edit::_001OnUpdateEditCut(::message::message * pmessage)
   {

      ::pointer<::message::command>pcommand(pmessage);

      string str;

      str = get_selection_text();

      pcommand->enable(str.has_character());

   }


   void plain_edit::_001OnEditCut(::message::message * pmessage)
   {

      __UNREFERENCED_PARAMETER(pmessage);

      _001EditCut(e_source_user);

      pmessage->m_bRet = true;

   }


   void plain_edit::_001OnUpdateEditCopy(::message::message * pmessage)
   {

      ::pointer<::message::command>pcommand(pmessage);

      string str;

      str = get_selection_text();

      pcommand->enable(str.has_character());

   }


   void plain_edit::_001OnEditCopy(::message::message * pmessage)
   {

      __UNREFERENCED_PARAMETER(pmessage);

      clipboard_copy();

      pmessage->m_bRet = true;

   }


   void plain_edit::_001OnUpdateEditPaste(::message::message * pmessage)
   {

      ::pointer<::message::command>pcommand(pmessage);

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

      str = get_selection_text();

      if (!str.has_character())
      {

         return ::success_none;

      }

      return ::success;

   }


   bool plain_edit::on_edit_delete(const ::action_context & actioncontext)
   {

      _001DeleteSel(false, actioncontext);
      //::draw2d::graphics_pointer pgraphics;

      //if (is_window_enabled())
      //{

      //   plain_edit_on_delete(pgraphics);

      //}

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


   //bool plain_edit::display(::e_display edisplay)
   //{

   //   if (nCmdShow != e_display_none)
   //   {

   //      informationf("Going to Show plain_edit");

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


   //double_size plain_edit::get_total_size(::user::enum_layout elayout)
   //{

   //   return m_sizeaTotal[elayout];

   //}


   ::payload plain_edit::get_payload()
   {

      string str;

      get_text(str);

      return str;

   }


   string plain_edit::plain_edit_get_expanded_line(::draw2d::graphics_pointer & pgraphics, ::collection::index iLine, array < character_count * > intptra)
   {

      string strLine = plain_edit_get_line(pgraphics, iLine);

      replace_tab(0, strLine, m_iTabWidth, intptra);

      return strLine;

   }


   string plain_edit::plain_edit_get_line(::draw2d::graphics_pointer & pgraphics, ::collection::index iLine)
   {

      _synchronous_lock synchronouslock(this->synchronization());

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

         character_count iLineLen = m_iaLineLength[iLine] - (m_iaLineFlags[iLine] & e_line_end_length);

         char * psz = strLine.get_buffer(iLineLen);

         m_ptree->m_peditfile->seek(m_iaLineIndex[iLine], ::e_seek_set);

         m_ptree->m_peditfile->read(scopedstr, iLineLen);

         strLine.release_buffer(iLineLen);

      }

      return strLine;

   }


   void plain_edit::on_before_change_text()
   {

      //if (get_ime_composition().has_character())
      //{

      //   clear_ime_composition();

      //   edit_undo();

      //}

   }


   void plain_edit::insert_text(const ::scoped_string & scopedstrText, bool bForceNewStep, const ::action_context & actioncontext)
   {

      ::string strText(scopedstrText);

      queue_graphics_call([this, strText, bForceNewStep, actioncontext](::draw2d::graphics_pointer & pgraphics)
         {

            on_reset_focus_start_tick();

            insert_text(pgraphics, strText, bForceNewStep);

            if (is_text_composition_active() && !m_pitemComposing)
            {

               m_pitemComposing = m_pinsert;

            }

            plain_edit_on_after_change_text(pgraphics, actioncontext);

         });

      set_need_redraw();

      post_redraw();

   }


   void plain_edit::_plain_edit_update_for_insert(::draw2d::graphics_pointer & pgraphics, const ::block & block, ::character_count i1, ::collection::index & iLine1, ::collection::index & iLine2)
   {

      //::string strInsertText;

      {

         ::string strTextHere(block);

         //auto i2 = i1 + strText.length();

         iLine1 = plain_edit_sel_to_line(pgraphics, i1);

         ::string_array straLinesHere;

         straLinesHere.add_lines(strTextHere, true, true);

         auto iUpperBoundHere = straLinesHere.get_upper_bound();

         iLine2 = iLine1 + iUpperBoundHere;

         if (iLine2 <= iLine1)
         {

            auto len = straLinesHere.last().size();

            auto & iLineLength = m_iaLineLength.element_at_grow(iLine2);

            iLineLength += len;

         }
         else
         {

            auto eolOld = (enum_line)m_iaLineFlags[iLine1];

            auto eolOldLen = as_length(eolOld);

            const char * pszLine;

            const char * pszEOLInsert;

            enum_line eolInsert;

            enum_line eolNew;

            ::character_count eolNewLen;

            ::character_count lenWithEOL;

            auto do_line_here = [&](::collection::index iLine)
               {
                  
                  pszLine = straLinesHere[iLine].c_str();

                  pszEOLInsert = straLinesHere[iLine].find_first_character_in("\r\n");

                  eolInsert = as_enum_line(scopedstrEOLInsert);

                  //auto eolNew = maximum(m_eline, eolInsert);

                  eolNew = eolInsert;

                  eolNewLen = as_length(eolNew);

                  lenWithEOL = (scopedstrEOLInsert - pszLine) + eolNewLen;

               };

            ::collection::index iLineHere = 0;

            auto iLine = iLine1;

            do_line_here(iLineHere);

            auto & iLineLength = m_iaLineLength[iLine];

            auto iLenEnd = iLineLength;

            iLineLength = ::minimum_maximum(0, i1 - m_iaLineIndex[iLine], iLineLength - eolOldLen);

            iLenEnd -= (iLineLength + eolOldLen);

            iLineLength += lenWithEOL;

            m_iaLineFlags[iLine] = eolNew;

         for (iLineHere++,iLine++; iLineHere < iUpperBoundHere; iLineHere++, iLine++)
         {

            do_line_here(iLineHere);

            m_iaLineLength.insert_at(iLine, lenWithEOL);

            m_iaLineFlags.insert_at(iLine, eolNew);

            //}

            //strInsertText += ::string(scopedstrLine, pszEOLInsert);

            //strInsertText += ::user::as_string(eolNew);

         }

         //{

            auto len = straLinesHere.last().size();

         //   if (iLineHere == 0)
         //   {

         //      auto & iLineLength = m_iaLineLength[iLineUpdate + iLineHere];

         //      m_iaLineLength[iLineUpdate] += len;

         //   }
         //   else
            //{

               //auto eolOldLen = as_length(eolOld);

               lenWithEOL = len + eolOldLen;

               m_iaLineLength.insert_at(iLine2, lenWithEOL + iLenEnd);

               m_iaLineFlags.insert_at(iLine2, eolOld);

            //}

            //strInsertText += straLines.last();

         }

      }

   }


   void plain_edit::insert_text(::draw2d::graphics_pointer & pgraphics, const ::scoped_string & scopedstrText, bool bForceNewStep)
   {

      _synchronous_lock synchronouslock(this->synchronization());

      _synchronous_lock _synchronouslock2(m_ptree->m_peditfile->synchronization());

      ::string strInsertLog = scopedstrText(0, 64);

      if (scopedstrText == "1")
      {

         information() << "typed \'1\'";

      }

      strInsertLog.find_replace("\n", "\\n");

      information("insert_text: \"" + strInsertLog + "\"");

      on_before_change_text();

      auto psystem = system();

      ::string strText(scopedstrText);

      psystem->_001AddPacks(m_base64map, strText);

      if (m_bMultiLine)
      {

#ifdef WINDOWS_DESKTOP

         if (strText.contains('\r') && !strText.contains('\n'))
         {

            strText.find_replace("\r", "\r\n");

         }

#endif

      }
      else
      {

         strText.find_replace("\n", "");

         strText.find_replace("\r", "");

      }

      bool bFullUpdate = false;

      ::collection::index iLine1 = -1;

      ::collection::index iLine2 = -1;

      character_count i1 = m_ptree->m_iSelBeg;

      character_count i2 = m_ptree->m_iSelEnd;

      ::sort_non_negative(i1, i2);

      iLine1 = plain_edit_sel_to_line(pgraphics, i1);

      bFullUpdate = strText.find_index('\n') >= 0 || strText.find_index('\r') >= 0;

      if (!bForceNewStep && !bFullUpdate && i1 == i2 && i1 >= 0 && m_pinsert != nullptr
         && m_pinsert->m_position + m_pinsert->m_size == i1
         && m_ptree->m_peditfile->m_ptreeitem != m_ptree->m_peditfile->m_ptreeitemFlush)
      {

         iLine2 = iLine1;

         m_pinsert->append_data(strText.c_str(), strText.length());

         m_ptree->m_peditfile->m_sizeEditFile += strText.length();

         m_iaLineLength[iLine2] += strText.length();

         m_ptree->m_iSelEnd += strText.length();
         m_ptree->m_iSelBeg = m_ptree->m_iSelEnd;
         m_ppropertysetsel->m_iSelEnd = m_ptree->m_iSelEnd;
         m_ppropertysetsel->m_iSelBeg = m_ptree->m_iSelEnd;

      }
      else
      {

         //::string_array straLines;

         //straLines.add_lines(strText);

         m_ppropertysetsel = __allocate plain_text_set_sel_command();

         m_ppropertysetsel->m_iPreviousSelBeg = m_ptree->m_iSelBeg;

         m_ppropertysetsel->m_iPreviousSelEnd = m_ptree->m_iSelEnd;

         MacroBegin();

         bool bDeleted = false;

         //iLine1 = plain_edit_sel_to_line(pgraphics, i1);

         MacroBegin();

         if (i1 != i2)
         {

            bDeleted = _plain_edit_on_delete(pgraphics, iLine1, i1, i2, false);

         }

         if (bDeleted)
         {

            MacroEnd();

         }
         else
         {

            MacroDiscard();

         }

         //if (!bFullUpdate)
         //{

         //   string strSel;

         //   strSel = get_selection_text();

         //   bFullUpdate = strSel.contains('\n') || strSel.contains('\r');

         //}

         //if (!bFullUpdate)
         //{

         //   iLineUpdate = plain_edit_sel_to_line(pgraphics, i1);

         //}

/*           if (i1 != i2)
           {

              m_ptree->m_peditfile->seek(i1, ::e_seek_set);

              m_ptree->m_peditfile->Delete((memsize)(i2 - i1));

              m_pinsert = nullptr;

              IndexRegisterDelete(i1, i2 - i1);

           }*/


         if (!bDeleted)
         {

            i2 = i1;

         }

         m_ptree->m_peditfile->MacroBegin();

         //_plain_edit_update_for_insert(pgraphics, strText, i1, i2, iLineUpdate, iLineHere);

         _plain_edit_update_for_insert(pgraphics, strText, i1, iLine1, iLine2);

         //::string strInsertText;

         m_ptree->m_peditfile->seek(i1, ::e_seek_set);

         i2 = i1 + strText.length();
         //i1 = i2;
         //m_ptree->m_peditfile->seek(m_ptree->m_iSelBeg, ::e_seek_set);

         auto iLength = strText.length();
         //auto a = m_ptree->m_iSelBeg;

         m_pinsert = m_ptree->m_peditfile->Insert(strText, iLength);

         IndexRegisterInsert(i1, strText);

         m_ptree->m_peditfile->MacroEnd();


         m_ppropertysetsel->m_iSelBeg = i2;

         m_ppropertysetsel->m_iSelEnd = i2;

         m_ptree->m_iSelBeg = i2;

         m_ptree->m_iSelEnd = i2;

         MacroBegin();
         MacroRecord(__allocate plain_text_file_command());
         MacroRecord(m_ppropertysetsel);
         MacroEnd();

         MacroEnd();

      }

      _update_line_start_array(iLine1);

      //m_ptree->m_peditfile->MacroEnd();


      //auto psetsel = __allocate plain_text_set_sel_command();

      //psetsel->m_iPreviousSelBeg = iSelBegOld;

//            psetsel->m_iPreviousSelEnd = iSelEndOld;

      _unlocked_plain_edit_on_change_text_selection(e_source_sync);

      informationf("insert tree->iSelBeg=%lld,iSelEnd=%lld", m_ptree->m_iSelBeg, m_ptree->m_iSelEnd);
      informationf("insert edit file size=%lld", m_ptree->m_peditfile->m_sizeEditFile);

      //}

      _plain_edit_update_extents(pgraphics, iLine1, iLine2);

      //plain_edit_update(pgraphics, bFullUpdate, iLineUpdate);

      //if (iLineUpdate < 0)
      //{

      //   iLineUpdate = plain_edit_sel_to_line(pgraphics, m_ptree->m_iSelEnd);

      //}

      int iColumnX = -1;

      auto iColumn = plain_edit_sel_to_column_x(pgraphics, m_ptree->m_iSelEnd, iColumnX);

      m_iColumn = iColumn;
      m_iColumnX = iColumnX;

      if (m_bMultiLine)
      {

         if (iLine1 >= 0)
         {

            _001EnsureVisibleLine(pgraphics, iLine1 + 1);

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

      _ensure_selection_visible_x(pgraphics);


   }


   void plain_edit::plain_edit_update(::draw2d::graphics_pointer & pgraphics, bool bFullUpdate, ::collection::index iLineUpdate)
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

      puserinteraction->__øconstruct(m_ppenCaret);

      puserinteraction->__øconstruct(m_pbrushText);

      puserinteraction->__øconstruct(m_pbrushTextCr);

      puserinteraction->__øconstruct(m_pbrushTextSel);

      puserinteraction->__øconstruct(m_pbrushTextEmpty);

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



   void plain_edit::on_updata_data(::data::simple_data * pdata, int iHint)
   {

      //if (pdata == m_ptree)
      {

         if (iHint == id_set_file)
         {

            auto psystem = system();

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
//      m_psimpleimm = __allocate simple_imm(this);
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

