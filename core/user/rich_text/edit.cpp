#include "framework.h"
#include "box.h"
#include "data.h"
#include "edit.h"
#include "edit_impl.h"
#include "format_tool.h"
#include "line.h"
#include "span.h"
#include "acme/constant/id.h"
#include "acme/constant/user_key.h"
#include "acme/constant/message.h"
#include "acme/constant/timer.h"
#include "acme/handler/topic.h"
#include "acme/platform/node.h"
#include "acme/platform/system.h"
#include "acme/platform/timer.h"
#include "aura/graphics/draw2d/brush.h"
#include "aura/graphics/draw2d/graphics.h"
#include "aura/graphics/draw2d/path.h"
#include "aura/graphics/image/image.h"
#include "aura/graphics/write_text/font.h"
#include "aura/message/user.h"
#include "aura/user/user/frame_interaction.h"
#include "aura/user/user/copydesk.h"
#include "aura/platform/session.h"


namespace user
{


   namespace rich_text
   {

      ::collection::count longest_pline(string & strSlice, double & d, string_array & straWords, double * pdaPosition, double dPositionLeft, int cx);
      int longest_word(string & strSlice, double & dPosition, const ::scoped_string & scopedstrWord, double * pdaPosition, double dPositionLeft, int cx);
      void align(line * pline, const ::double_rectangle & rectangle);
      ::collection::count get_vars(strsize_array & ia1, strsize_array & ia2, const ::scoped_string & scopedstr);


      edit::edit()
      {

         m_bShouldDrawOverride = false;

         m_bCaretRight = false;

         m_iSelBeg = 0;

         m_iSelEnd = 0;

         m_timeCaretPeriod = 1_s;


      }


      //edit::edit(::particle * pparticle) :
      //   ::object(pparticle),
      //   ::user::picture(pparticle),
      //   ::user::picture_interaction(pparticle)
      //{

      //}


      edit::~edit()
      {

      }


      void edit::update_data(bool bSaveAndValidate)
      {

         if (bSaveAndValidate)
         {

         }
         else
         {

            set_need_layout();

            set_need_redraw();

         }

         //return true;

      }


//      void edit::assert_ok() const
//      {
//
//         ::user::interaction::assert_ok();
//
//      }
//
//
//      void edit::dump(dump_context & dumpcontext) const
//      {
//
//         ::user::interaction::dump(dumpcontext);
//
//      }


      void edit::install_message_routing(::channel * pchannel)
      {

         ::user::interaction::install_message_routing(pchannel);

         MESSAGE_LINK(e_message_create, pchannel, this, &edit::on_message_create);
         MESSAGE_LINK(e_message_destroy, pchannel, this, &edit::on_message_destroy);
         MESSAGE_LINK(e_message_show_window, pchannel, this, &edit::on_message_show_window);
         MESSAGE_LINK(e_message_left_button_down, pchannel, this, &edit::on_message_left_button_down);
         MESSAGE_LINK(e_message_left_button_up, pchannel, this, &edit::on_message_left_button_up);
         MESSAGE_LINK(e_message_mouse_move, pchannel, this, &edit::on_message_mouse_move);
         MESSAGE_LINK(e_message_mouse_leave, pchannel, this, &edit::on_message_mouse_leave);
         MESSAGE_LINK(e_message_key_down, pchannel, this, &edit::on_message_key_down);
         MESSAGE_LINK(e_message_key_up, pchannel, this, &edit::on_message_key_up);
//         MESSAGE_LINK(e_message_set_focus, pchannel, this, &edit::on_message_set_focus);
         //MESSAGE_LINK(e_message_kill_focus, pchannel, this, &edit::on_message_kill_focus);
         
#ifdef WINDOWS_DESKTOP

         text_composition_composite::initialize_text_composition_client(pchannel, this);
         
#endif

      }


      void edit::on_message_create(::message::message * pmessage)
      {

         ::pointer<::message::create>pcreate(pmessage);

         pcreate->previous();

         if (pcreate->m_bRet)
         {

            return;

         }

         __construct_new(m_plinea);

         

//#if !defined(APPLE_IOS) && !defined(__ANDROID__)

  //       psession->keyboard(); // trigger keyboard creationg

//#endif

         set_timer(100, 100_ms, nullptr);

         set_timer(e_timer_redraw, 200_ms, nullptr); // Caret

      }


      void edit::on_message_destroy(::message::message * pmessage)
      {

      }


      void edit::on_message_show_window(::message::message * pmessage)
      {

         __UNREFERENCED_PARAMETER(pmessage);
         //::pointer<::message::show_window>pshowwindow(pmessage);

      }


      void edit::on_set_keyboard_focus()
      {
         
         //__UNREFERENCED_PARAMETER(pmessage);

         //::pointer<::message::set_keyboard_focus>psetfocus(pmessage);

         if (!is_text_editable())
         {

            return;

         }

         auto pformattool = get_format_tool(true);

         ::user::rich_text::selection * pselection = this;

         pformattool->show_for_ui(this, pselection);

      }


      void edit::on_kill_keyboard_focus()
      {

         //::pointer<::message::kill_focus>pkillfocus(pmessage);

         auto pformattool = get_format_tool(false);

         if (pformattool != nullptr && pformattool->is_showing_for_ui(this))
         {

            

            auto puser = user();

            //auto puserinteractionFocusNew = puser->interaction(pkillfocus->m_oswindowNew);

            ::user::interaction * pinteraction = nullptr;

  /*          if (puserinteractionFocusNew != nullptr)
            {

               pinteraction = puserinteractionFocusNew;

            }*/

            //if (pkillfocus->m_oswindowNew == pformattool->get_oswindow()
            if(pformattool->is_ascendant_or_owner_of(pinteraction, true))
            {

               informationf("Window winning focus is own font format tool");

               return;

            }

            pformattool->hide();

         }

      }


      void edit::on_selection_change()
      {

      }


      void edit::on_message_left_button_down(::message::message * pmessage)
      {

         __UNREFERENCED_PARAMETER(pmessage);
         
         //auto pmouse = pmessage->m_union.m_pmouse;

      }


      void edit::on_message_left_button_up(::message::message * pmessage)
      {

         __UNREFERENCED_PARAMETER(pmessage);
         
         //auto pmouse = pmessage->m_union.m_pmouse;

      }


      void edit::on_message_mouse_move(::message::message * pmessage)
      {

         __UNREFERENCED_PARAMETER(pmessage);
         
         //auto pmouse = pmessage->m_union.m_pmouse;

      }


      ::user::drawable * edit::get_drawable()
      {

         return this;

      }


      bool edit::should_draw()
      {

         return m_bShouldDrawOverride || m_ppictureimpl.is_null();

      }


      bool edit::is_this_visible(enum_layout elayout)
      {

         return should_draw() || ::user::interaction::is_this_visible(elayout);

      }


      ::double_size edit::get_size()
      {

         ::int_rectangle rectangle;

         window_rectangle(rectangle);

         return rectangle.size();

      }


      void edit::do_layout()
      {


      }



      void edit::on_message_mouse_leave(::message::message * pmessage)
      {

         defer_release_mouse_capture();

         set_need_redraw();

      }


      bool edit::get_element_rectangle(::int_rectangle * prectangle, ::collection::index i, enum_element eelement)

      {

         if (eelement == ::e_element_icon)
         {

            if (!get_item_rect(prectangle, i))

            {

               return false;

            }

            return true;

         }
         else if (eelement == ::e_element_text)
         {

            if (!get_item_rect(prectangle, i))

            {

               return false;

            }

            return true;


         }

         return false;

      }

      bool edit::get_item_rect(::int_rectangle * prectangle, ::collection::index i)

      {

         return true;

      }


      double edit::get_rotate()
      {

         if (is_picture_enabled())
         {

            return m_ppictureimpl->m_dRotate;

         }

         return 0.0;

      }


      ::item_pointer edit::on_hit_test(const ::int_point &point, ::user::e_zorder ezorder)
      {

         return ::user::interaction::on_hit_test(point, ezorder);

      }


      //void edit::get_text(string & str)
      //{

      //   ::user::interaction::get_text(str);

      //}


      //void edit::_001GetLayoutText(string & str)
      //{

      //}


      void edit::do_layout(::draw2d::graphics_pointer & pgraphics)
      {

         //m_rectangle = rectangle;

         _synchronous_lock synchronouslock(this->synchronization());

         pgraphics->set_text_rendering_hint(::write_text::e_rendering_anti_alias);

         auto prichtextdata = get_rich_text_data();

         if (prichtextdata->m_spana.is_empty())
         {

            prichtextdata->add_span(::e_align_left, false);

         }

         //         if (m_spana.first()->m_ealignNewLine == e_align_none)
         //         {
         //
         //            m_spana.first()->m_ealignNewLine = e_align_left;
         //
         //         }
         //
         update_span_cache(prichtextdata->m_spana);

         //bool bLineWrap = false;

         auto rectangle = get_drawing_rect();

         double_rectangle rectangleX(rectangle);

         int x = (int)rectangle.left();

         //int xLast = x;

         //bool bFirstParagraph = true;

         auto plinea = __allocate pointer_array < line > ();

         ::pointer<line>pline;

         //character_count iCharLayout = 0;

   //if (m_spana.first().m_pformat >= m_pformathost.get_count())
   //{

   //   m_pformathost.add(__allocate format(this));

   //}

         //if (m_spana.is_empty())
         //{

         //   add_span(e_align_left);

         //   m_spana.first_pointer()->m_iFormat = 0;

         //   if (m_spana.first_pointer()->m_iFormat >= m_pformathost.get_count())
         //   {

         //      m_pformathost.add(__allocate format(this));

         //   }

         //}
         //else if (!m_spana[0]->is_new_line())
         //{

         //   m_spana[0]->m_ealignNewLine = e_align_left;

         //}

         // horizontal span

         ::e_align ealign = e_align_center;

         //pointer_array < span > spana;

         //character_count iSpanCharEnd = 0;

         //index iSpan = 0;

         ::collection::count cWords = 0;

         //index iSpanNextWord;
         string strSlice;

         string_array straWords;

         double dPosition;

         ::pointer<box>pbox;

         //bool bMultiWordFormat = true;

         //pointer_array < span > spanaMultiWordFormat;

//         int iHeight;

         //bool bLineBreak = false;

         auto defer_add_line = [&]()
            {

               if (pline)
               {

                  ASSERT(pline->has_element());

                  plinea->add(pline);

                  pline = nullptr;

               }

            };


         auto new_line = [&]()
            {

               defer_add_line();

               __construct_new(pline);

               //pline = __allocate line();

               x = (int)rectangle.left();

               //xLast = x;

               //bLineWrap = false;

               x = (int)rectangle.left();

               //pbox = __allocate box(pspan);

               //index iSpan = find_char_span(m_spana, iCharLayout);

               //int iHeight = pspan->format()->m_pfont->get_height();

               //pbox->m_rectangle.set(x, 0, x, 0);

               //pbox->m_rectangleHitTest.set(x, 0, x, 0);

               //pbox->m_size.set_size(0, iHeight);

               //pbox->m_iPosBeg = pspan->m_iPosBeg + iCharLayout;

               //pbox->m_iPosEnd = pspan->m_iPosBeg + (bFirstParagraph ? iCharLayout : iCharLayout + 1);

               //iCharLayout = pbox->m_iPosEnd;

               pline->m_dLeft = x;

               pline->m_dLeftDevice = x;

               //pline->add(pbox);

               //bFirstParagraph = false;

            };

         auto & spana = prichtextdata->m_spana;


         for (::collection::index iSpan = 0; iSpan < prichtextdata->m_spana.get_count(); iSpan++)
         {

            ::pointer < span > pspan = prichtextdata->m_spana[iSpan];

            ealign = box_align(prichtextdata->m_spana, iSpan);

            pspan->m_str.find_replace("\n", "");

            pspan->m_str.find_replace("\r", "");

            auto pformat = pspan->format();

            pgraphics->set(pformat->get_font(pgraphics));

            {

               auto iLenSpan = pspan->m_str.length();

               auto iLenMeasure = pgraphics->get_character_extent(pspan->m_daPositionLeft, pspan->m_daPositionRight, pspan->m_str);

               if (iLenSpan != iLenMeasure)
               {

                  ASSERT(false);

                  informationf("unexpected: iLenSpan != iLenMeasure");

               }

            }

            pspan->m_sizeSpan = pgraphics->get_text_extent(pspan->m_str);

            double dPositionLeft = 0.;

            character_count iSpanChar = 0;

            do
            {

               if (!pline)
               {

                  new_line();

               }

               strSlice.empty();

               // Format Word

               string strTopic = pspan->m_str.c_str() + iSpanChar;

               if (strTopic.is_empty())
               {

                  if (pline->is_empty())
                  {

                     auto pbox = __allocate box(pspan);

                     pbox->m_iPosBeg = pspan->m_iPosBeg + iSpanChar;

                     iSpanChar += strSlice.length();

                     pbox->m_iPosEnd = pspan->m_iPosBeg + iSpanChar;

                     // keeping dimensions
                     //pbox->m_size.cy() = pspan->m_size.cy();

                     //if (pbox->m_size.cy() <= 0)
                     {

                        pbox->m_sizeBox.cy() = pformat->get_font(pgraphics)->get_height(pgraphics);

                     }

                     pbox->m_sizeBox.cx() = 0;

                     // just horizonal layout
                     pbox->m_rectangleBox.set_dimension(x, 0, pbox->m_sizeBox.cx(), 0);

                     pbox->m_rectangleHitTest = pbox->m_rectangleBox;

                     pline->add(pbox);

                  }

                  break;

               }

               straWords.erase_all();

               words_trailing_spaces(straWords, strTopic);

               if (straWords.get_count() <= 0)
               {

                  break;

               }

               strSlice.empty();

               cWords = (int)longest_pline(strSlice, dPosition, straWords, &pspan->m_daPositionRight[iSpanChar], dPositionLeft, (int)rectangleX.right() - x);

               if (ansi_char_isspace(straWords.last().last_char())
                  || (iSpan + 1 < prichtextdata->m_spana.get_count()
                     && (spana[iSpan]->is_end_of_line()
                        || (spana[iSpan + 1]->m_str.has_character()
                           && ansi_char_isspace(spana[iSpan + 1]->m_str[0]))))
                  || cWords < straWords.get_count())
               {

                  if (cWords > 0)
                  {

                     auto pbox = __allocate box(pspan);

                     pbox->m_iPosBeg = pspan->m_iPosBeg + iSpanChar;

                     iSpanChar += strSlice.length();

                     pbox->m_iPosEnd = pspan->m_iPosBeg + iSpanChar;

                     // keeping dimensions
                     pbox->m_sizeBox.cy() = pspan->m_sizeSpan.cy();

                     pbox->m_sizeBox.cx() = dPosition - dPositionLeft;

                     // just horizonal layout
                     pbox->m_rectangleBox.set_dimension(x, 0, pbox->m_sizeBox.cx(), 0);

                     pbox->m_rectangleHitTest = pbox->m_rectangleBox;

                     pline->add(pbox);

                     x += (int)pbox->m_sizeBox.cx();

                     if (cWords >= straWords.get_count())
                     {

                        break;

                     }
                     else
                     {

                        //iSpanChar++;

                        dPositionLeft = dPosition;

                        new_line();

                     }

                  }
                  else
                  {

                     string strWord = straWords[0];

                     strSlice.empty();

                     longest_word(strSlice, dPosition, strWord, &pspan->m_daPositionRight[iSpanChar], dPositionLeft, (int)rectangleX.right() - x);

                     auto pbox = __allocate box(pspan);

                     pbox->m_iPosBeg = pspan->m_iPosBeg + iSpanChar;

                     iSpanChar += strSlice.length();

                     pbox->m_iPosEnd = pspan->m_iPosBeg + iSpanChar;

                     // keeping dimensions
                     pbox->m_sizeBox.cy() = pspan->m_sizeSpan.cy();

                     pbox->m_sizeBox.cx() = dPosition - dPositionLeft;

                     // just horizonal layout
                     pbox->m_rectangleBox.set_dimension(x, 0, pbox->m_sizeBox.cx(), 0);

                     pbox->m_rectangleHitTest = pbox->m_rectangleBox;

                     pline->add(pbox);

                     x += (int)pbox->m_sizeBox.cx();

                     //iSpanChar++;

                     dPositionLeft = dPosition;

                     new_line();

                  }

               }
               else
               {

                  auto pbox = __allocate box(pspan);

                  pbox->m_iPosBeg = pspan->m_iPosBeg + iSpanChar;

                  iSpanChar += strTopic.length();

                  pbox->m_iPosEnd = pbox->m_iPosBeg + iSpanChar;

                  // keeping dimensions
                  pbox->m_sizeBox.cy() = pspan->m_sizeSpan.cy();

                  pbox->m_sizeBox.cx() = dPosition;

                  // just horizonal layout
                  pbox->m_rectangleBox.set_dimension(x, 0, pbox->m_sizeBox.cx(), 0);

                  pbox->m_rectangleHitTest = pbox->m_rectangleBox;

                  pline->add(pbox);

                  x += (int)pbox->m_sizeBox.cx();

                  //spanaMultiWordFormat.add(pspan);

                  break;


               }


               //new_span:

               //   //if (spanaMultiWordFormat.is_empty() &&

               //   if(pspan->is_end_of_line() || bLineBreak)
               //   {


               //   }


            } while (iSpanChar < pspan->m_str.length());
            //if (pline.is_set())
            //{

            //   ASSERT(pline->has_element());

            //   plinea->add(pline);

            if (pspan->is_end_of_line())
            {

               new_line();

            }

         }

         defer_add_line();

         for (auto & pline : *plinea)
         {

            align(pline, rectangleX);

         }

         m_plinea = plinea;

      }


      ::double_rectangle edit::get_drawing_rect()
      {

         ::double_rectangle rectangle;

         if (is_picture_enabled())
         {

            rectangle = m_ppictureimpl->m_rectangleDrawing;

            rectangle -= rectangle.origin();

         }
         else
         {

            rectangle = this->rectangle();

         }

         return rectangle;

      }


      void edit::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
      {

         _synchronous_lock synchronouslock(this->synchronization());

         pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

         if (pgraphics->m_bPrinting)
         {

            pgraphics->set_text_rendering_hint(::write_text::e_rendering_anti_alias);

         }
         else
         {

            pgraphics->set_text_rendering_hint(::write_text::e_rendering_anti_alias);

         }

         //double_rectangle rectangleX(rectangle);

         auto rectangle = get_drawing_rect();

         //pgraphics->draw_inset_3d_rectangle(rectangle, argb(255, 0, 127, 0));

         bool bHasFocus = false;

         if (has_keyboard_focus())
         {

            bHasFocus = true;

         }

         bool bCaretOn = false;

         if (bHasFocus && is_text_editable())
         {

            bCaretOn = m_timeFocusStart.on_off(m_timeCaretPeriod);

         }

         bHasFocus = true;

         bCaretOn = true;

         if (m_bPendingSelectionChange)
         {

            m_bPendingSelectionChange = false;

            on_selection_change();

         }

         auto plinea = m_plinea;

         if (!plinea)
         {

            return;

         }


         //if (plinea->has_elements() && plinea->last().has_elements())
         //{

         //   plinea->last().last().m_iSelEnd--;

         //   plinea->last().last().m_str.Truncate(plinea->last().last().m_str.length()-1);

         //}

         int y = (int)rectangle.top();


         int nexty;

         // vertical span

         for (auto & pline : *plinea)
         {

            int iMaxCy = 0;

            for (auto & pbox : *pline)
            {

               iMaxCy = maximum(iMaxCy, (int)pbox->m_sizeBox.cy());

               pbox->m_rectangleBox.top() = y;

               pbox->m_rectangleHitTest.top() = y;

            }

            nexty = y + iMaxCy;

            for (auto & pbox : *pline)
            {

               pbox->m_rectangleBox.bottom() = nexty;

               pbox->m_rectangleHitTest.bottom() = nexty;

               //pbox->m_rectangleBox.right() += 2;

            }

            y = nexty;

         }

         // Draw Select Rectangle

         ::color::color crBkSel;

         if (bHasFocus && is_text_editable())
         {

            crBkSel = argb(192, 175, 200, 240);

         }
         else
         {

            crBkSel = argb(127, 192, 210, 225);

         }

         {

            //character_count iSelBeg = get_sel_beg();

            //character_count iSelEnd = get_sel_end();

            for (::collection::index iLine = 0; iLine < plinea->get_count(); iLine++)
            {

               auto & pline = plinea->element_at(iLine);

               if (pline->has_element())
               {

                  auto pboxBeg = pline->first_pointer();

                  auto pboxEnd = pline->last_pointer();

                  character_count iBoxPosBeg = pboxBeg->m_iPosBeg;

                  character_count iBoxPosEnd = pboxEnd->m_iPosEnd;

                  if (iBoxPosBeg <= get_sel_end() && get_sel_beg() <= iBoxPosEnd)
                  {

                     auto iSelBeg = get_sel_beg();

                     auto iSelEnd = get_sel_end();

                     iBoxPosBeg = maximum(iBoxPosBeg, iSelBeg);

                     iBoxPosEnd = minimum(iBoxPosEnd, iSelEnd);

                     ::collection::index iBeg = pline->predicate_find_first([&](auto & pbox)
                     {

                        return pbox->m_iPosBeg <= iBoxPosBeg && iBoxPosBeg <= pbox->m_iPosEnd;

                     });

                     if (iBeg >= 0)
                     {

                        pboxBeg = pline->element_at(iBeg);

                        ::collection::index iEnd = pline->predicate_find_first([&](auto & pbox)
                        {

                           return pbox->m_iPosBeg <= iBoxPosEnd && iBoxPosEnd <= pbox->m_iPosEnd + 1;

                        });

                        if (iEnd >= 0)
                        {

                           pboxEnd = pline->element_at(iEnd);

                           double l;

                           if (iBoxPosBeg == pboxBeg->m_iPosBeg)
                           {

                              l = pboxBeg->m_rectangleBox.left();

                           }
                           else if (iBoxPosBeg >= pboxBeg->m_iPosEnd)
                           {

                              l = pboxBeg->m_rectangleBox.right();

                           }
                           else
                           {

                              l = pboxBeg->get_pos_left(iBoxPosBeg);

                           }

                           double r;

                           if (iBoxPosEnd == pboxEnd->m_iPosBeg)
                           {

                              r = pboxEnd->m_rectangleBox.left();

                           }
                           else if (iBoxPosEnd >= pboxEnd->m_iPosEnd)
                           {

                              r = pboxEnd->m_rectangleBox.right();

                           }
                           else
                           {

                              r = pboxEnd->get_pos_left(iBoxPosEnd);
                           }

                           pgraphics->fill_rectangle(
                              ::double_rectangle(l,
                                 pboxBeg->m_rectangleBox.top(),
                                 r,
                                 pboxEnd->m_rectangleBox.bottom()),
                              crBkSel);

                        }

                     }

                  }

               }

            }

         }

         ::image::fastblur blurDropShadow;

         ::image::image_pointer imageDropShadow;

         ::int_rectangle rDropShadow;

         if (m_ppictureimpl != nullptr)
         {

            rDropShadow = m_ppictureimpl->m_rectangleDrawing;

            rDropShadow.offset(-rDropShadow.center());

         }

         if (m_ppictureimpl != nullptr && m_ppictureimpl->m_bGlowDropShadow)
         {

            ::image::image_pointer pimage;

            __øconstruct(pimage);

            pimage->create(m_ppictureimpl->m_rectangleDrawing.size());

            ::int_size sz = m_ppictureimpl->m_rectangleDrawing.size();

            auto offset = sz / 2;

            pimage->g()->offset(offset);

            ::draw2d::graphics_pointer pgraphicsImage = pimage->g();

            draw_text(pgraphicsImage, rectangle);

            pimage->g()->offset(-offset);

            defer_draw_drop_shadow_phase1(rDropShadow, blurDropShadow, imageDropShadow, pimage);

            defer_draw_drop_shadow_phase2(pgraphics, rDropShadow, blurDropShadow, imageDropShadow);

         }

         draw_text(pgraphics, rectangle);

         // Draw Caret

         if (bCaretOn && is_text_editable())
         {

            ::pointer<box>pbox = find_box(*plinea, m_iSelEnd);

            if (pbox)
            {

               double r;

               r = pbox->get_pos(m_iSelEnd);

               ////r += rectangle.left();

               //if (r > rectangle.right())
               //{

               //   r -= 1.0;

               //}

               if (r < rectangle.left() + 2)
               {

                  r = rectangle.left() + 2;

               }

               if (r > rectangle.right() - 2)
               {

                  r = rectangle.right() - 2;

               }

               auto dDescent = pbox->m_pspan->m_pformat->m_pfont->get_descent(pgraphics);

               pgraphics->fill_rectangle(::double_rectangle(r,
                  pbox->m_rectangleBox.top() + 1,
                  r + 0.5,
                  pbox->m_rectangleBox.bottom() - dDescent),
                  system()->dark_mode() ? argb(255, 255, 255, 255) : argb(255, 0, 0, 0));

            }

         }

         ::geometry2d::matrix m;

         m.scaling(pgraphics->get_scaling());

         //m.invert();

         for (auto & pline : *plinea)
         {

            for (auto & pbox : *pline)
            {

               pbox->m_rectangleDevice = pbox->m_rectangleBox;

               m.transform(pbox->m_rectangleHitTest.top_left());
               m.transform(pbox->m_rectangleHitTest.bottom_right());

               m.transform(pbox->m_rectangleDevice.top_left());
               m.transform(pbox->m_rectangleDevice.bottom_right());

            }

         }

         auto prichtextdata = get_rich_text_data();

         for (auto & pspan : prichtextdata->m_spana)
         {

            pspan->m_daPositionDeviceLeft.erase_all();
            pspan->m_daPositionDeviceRight.erase_all();

            for (auto & x : pspan->m_daPositionLeft)
            {

               pspan->m_daPositionDeviceLeft.add(x * m.a1);

            }

            for (auto & x : pspan->m_daPositionRight)
            {

               pspan->m_daPositionDeviceRight.add(x * m.a1);

            }

         }

      }


      void edit::draw_impl(::draw2d::graphics_pointer & pgraphics)
      {

      }


      ::data::data * edit::_get_data(const ::atom & atom)
      {

         if (!m_prichtextdataOwned)
         {

            __construct_new(m_prichtextdataOwned);

            m_prichtextdataOwned->initialize_data();

         }

         return m_prichtextdataOwned;

      }


      ::user::rich_text::data * edit::get_rich_text_data()
      {

         auto pdata = _get_data(0);

         auto prichtextdata = dynamic_cast <::user::rich_text::data *> (pdata);

         return prichtextdata;

      }


      bool edit::set_text_editable(bool bEditable)
      {

         return false;

      }


      bool edit::is_text_editable()
      {

         return is_window_enabled();

      }


      bool edit::is_text_editor()
      {

         return true;

      }


      bool edit::_001IsPointInside(const ::int_point & pointParam)
      {

         if (is_picture_enabled())
         {

            double_point point(pointParam);

            screen_to_client()(point);

            ::int_rectangle rWindow;
            
            window_rectangle(rWindow);

            double_rectangle rectangleWindow;

            rectangleWindow = rWindow;
            
            get_parent()->screen_to_client()(rectangleWindow);

            //rectangleWindow = rectangleWindow;

            point += rectangleWindow.top_left();

            _rtransform_sequence(point);

            point -= rectangleWindow.top_left();

            auto rectangleX = this->rectangle();

            return rectangleX.contains(::int_point(point));

         }

         return ::user::interaction::_001IsPointInside(pointParam);

      }


      bool edit::_001GetItemText(string & str, ::collection::index iItem)
      {

         return false;

      }


      void edit::on_layout(::draw2d::graphics_pointer & pgraphics)
      {

         auto rectangleX = this->rectangle();

         if (rectangleX.is_empty())
         {

            return;

         }

      }


      void edit::handle(::topic * ptopic, ::handler_context * phandlercontext)
      {

         return ::user::interaction::handle(ptopic, phandlercontext);

      }


      ::pointer<format_tool>edit::get_format_tool(bool bCreate)
      {

         auto pformattool = top_level_frame()->tool_window(e_tool_font, bCreate);

         return pformattool;

      }


      ::user::rich_text::format_host * edit::get_format_host()
      {

         return nullptr;

         //return this;

      }


      ::pointer<::user::rich_text::format> edit::get_selection_common_format()
      {

         return nullptr;

      }








      bool edit::keyboard_focus_is_focusable()
      {

         return is_window_visible() && is_text_editable();

      }


      void edit::keyboard_focus_OnChar(::message::message * pmessage)
      {

         if (!is_text_editable())
         {

            return;

         }

         on_message_character(pmessage);

      }


      void edit::on_message_key_down(::message::message * pmessage)
      {

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

         auto pkey = pmessage->m_union.m_pkey;

         auto psession = session();

         if (pkey->m_ekey == ::user::e_key_return)
         {

            if (psession->is_key_pressed(::user::e_key_control) && psession->is_key_pressed(::user::e_key_alt))
            {

               pkey->m_bRet = false;

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

            ptopic->id() = ::id_escape;

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

               string str;

               str=get_selection_text();

               if (str.is_empty())
               {

                  _001GetSelLineText(str);

               }

               auto pcopydesk = copydesk();

               pcopydesk->set_plain_text(str);

               return;

            }

         }
         else if (pkey->m_ekey == ::user::e_key_v)
         {

            if (psession->is_key_pressed(::user::e_key_control))
            {

               pkey->m_bRet = true;

               if (is_window_enabled())
               {

               }

               return;

            }

         }
         else if (pkey->m_ekey == ::user::e_key_x)
         {

            if (psession->is_key_pressed(::user::e_key_control))
            {

               pkey->m_bRet = true;

               string str;

               str = get_selection_text();

               auto pcopydesk = copydesk();

               pcopydesk->set_plain_text(str);

               if (is_window_enabled())
               {

                  _001OnDeleteText();

               }

               return;

            }

         }

         pkey->m_bRet = true;

      }


      void edit::on_message_key_up(::message::message * pmessage)
      {

         auto pkey = pmessage->m_union.m_pkey;

         auto psession = session();

         if (pkey->m_ekey == ::user::e_key_return)
         {

            if (psession->is_key_pressed(::user::e_key_control) && psession->is_key_pressed(::user::e_key_alt))
            {
               pkey->m_bRet = false;
               return;
            }
         }
         else if (pkey->m_ekey == ::user::e_key_alt)
         {

            pkey->m_bRet = false;

         }

      }


      void edit::on_timer(::timer * ptimer)
      {

         ::user::interaction::on_timer(ptimer);

         if (ptimer->m_uTimer >= 100 && ptimer->m_uTimer <= 200)
         {

         }
         else if (ptimer->m_uTimer == 500 || ptimer->m_uTimer == 501)
         {

            if (ptimer->m_uTimer == 500)
            {

               kill_timer(500);

               set_timer(501, 300_ms, nullptr);

            }

         }
         else if (ptimer->m_uTimer == e_timer_redraw)
         {

            // Caret

            if (is_text_editable() && is_window_visible() && has_keyboard_focus())
            {

               set_need_redraw();

            }

         }

      }


      void edit::key_to_char(::message::key * pkey)
      {

         ::message::key & key = *pkey;

         if (key.m_ekey == ::user::e_key_shift || key.m_ekey == ::user::e_key_left_shift || key.m_ekey == ::user::e_key_right_shift
            || key.m_ekey == ::user::e_key_control || key.m_ekey == ::user::e_key_left_control || key.m_ekey == ::user::e_key_right_control
            || key.m_ekey == ::user::e_key_alt || key.m_ekey == ::user::e_key_left_alt || key.m_ekey == ::user::e_key_right_alt
            )
         {

            return;

         }

         if (key.m_ekey == ::user::e_key_right || key.m_ekey == ::user::e_key_up
            || key.m_ekey == ::user::e_key_left || key.m_ekey == ::user::e_key_down)
         {

            on_message_character(&key);

            return;

         }

         auto psession = session();

         bool bShift = psession->is_key_pressed(::user::e_key_shift);

         if (key.m_nChar < 256 && character_isalpha((char)key.m_nChar))
         {

            if (bShift)
            {

               key.m_nChar = character_toupper((char)key.m_nChar);

            }
            else
            {

               key.m_nChar = character_tolower((char)key.m_nChar);

            }

         }

         on_message_character(&key);

      }


      void edit::_001OnDeleteText()
      {

         on_reset_focus_start_tick();

      }


      void edit::on_message_character(::message::message * pmessage)
      {

      }


      void edit::destroy()
      {

         ::user::interaction::destroy();
         ::user::picture_interaction::destroy();
         ::user::text_composition_composite::destroy();
         ::user::rich_text::selection::destroy();

      }


      void edit::on_after_change(const ::atom & atom)
      {

      }


      //character_count edit::get_text_length()
      //{

      //   return 0;

      //}


      void edit::get_text_selection(character_count & iBeg, character_count & iEnd) const
      {

      }


      void edit::_001GetSelLineText(string & strText)
      {

      }


      void edit::update_placement()
      {

         if (m_ppictureimpl == nullptr)
         {

            return;

         }

         place(m_ppictureimpl->m_rectangle);

      }


      //void edit::write(::binary_stream & stream) const
      //{

      //   return ::user::picture::write(stream);

      //}


      //void edit::read(::binary_stream & stream)
      //{

      //   return ::user::picture::read(stream);

      //}


      void edit::get_text_composition_area(::int_rectangle & r)
      {

      }


      void edit::on_text_composition(const ::scoped_string & scopedstr)
      {

      }


      void edit::on_text_composition_done()
      {

      }


      bool edit::edit_undo()
      {

         return false;

      }


      bool edit::has_text_input()
      {

         return is_window_enabled() && is_text_editor() && is_text_editable();

      }

      character_count edit::get_sel_beg()
      {

         auto length = _001GetLayoutTextLength();

         auto begin = m_iSelBeg;

         auto end = m_iSelEnd;

         return minimum(maximum(minimum_non_negative(begin, end), 0), length);

      }


      character_count edit::get_sel_end()
      {

         return minimum(maximum(maximum(m_iSelBeg, m_iSelEnd), 0), _001GetLayoutTextLength());

      }


      void edit::on_selection_change(format * pformat)
      {

         auto prichtextdata = get_rich_text_data();

         _synchronous_lock synchronouslock(prichtextdata->synchronization());

         ::collection::index iSelBeg = get_sel_beg();

         ::collection::index iSelEnd = get_sel_end() - 1;

         get_selection_intersection_format(pformat, iSelBeg, iSelEnd);

      }


      void edit::get_selection_intersection_format(format * pformat, ::collection::index iSelBeg, ::collection::index iSelEnd)
      {

         auto prichtextdata = get_rich_text_data();

         _synchronous_lock synchronouslock(prichtextdata->synchronization());

         update_span_cache(prichtextdata->m_spana);

         ::collection::index iSpanBeg = find_span(prichtextdata->m_spana, iSelBeg);

         ::collection::index iSpanEnd = find_span(prichtextdata->m_spana, iSelEnd);

         if (iSpanBeg >= 0 && iSpanEnd >= iSpanBeg)
         {

            ::pointer<span>pspanBeg = prichtextdata->m_spana[iSpanBeg];

            *pformat = *pspanBeg->m_pformat;

            ::e_align ealign = pspanBeg->get_align();

            pformat->m_ealign = ealign;

            while (true)
            {

               iSpanBeg++;

               if (iSpanBeg > iSpanEnd)
               {

                  break;

               }

               pformat->intersect(*prichtextdata->m_spana[iSpanBeg]->m_pformat);

            }

         }

      }


      void edit::_001SetSelFontFormat(const format * pformat, const e_attribute & eattribute)
      {

         auto prichtextdata = get_rich_text_data();

         auto i1 = get_sel_beg();

         auto i2 = get_sel_end();

         prichtextdata->_001SetFontFormat(i1, i2, pformat, eattribute);

         m_iSelBeg = i1;

         m_iSelEnd = i2;

         on_after_change(::id_after_change_text_format);

      }


      void edit::_001InsertText(const ::scoped_string & scopedstr, format * pformat)
      {

         auto prichtextdata = get_rich_text_data();

         auto i1 = m_iSelBeg;

         auto i2 = m_iSelEnd;

         auto iSelChar = prichtextdata->_001InsertText(i1, i2, scopedstr, pformat);

         m_iSelBeg = m_iSelEnd = iSelChar;

         on_after_change(::id_after_change_text);

      }


      void edit::_001GetLayoutText(string & str) const
      {

         _synchronous_lock synchronouslock(this->synchronization());

         str = layout_text(*m_plinea);

      }


      ::collection::index edit::SelToLine(character_count iSel)
      {

         return sel_line(*m_plinea, iSel);

      }


      ::collection::index edit::LineColumnToSel(::collection::index iLine, character_count iColumn)
      {

         auto prichtextdata = get_rich_text_data();

         _synchronous_lock synchronouslock(prichtextdata->synchronization());

         if (iLine < 0)
         {

            return -1;

         }

         int iMax = (int)_001GetLayoutTextLength();

         auto plinea = m_plinea;

         if (iLine >= plinea->get_count())
         {

            return iMax;

         }

         if (iColumn < 0)
         {

            int iChar = (int)(iColumn + plinea->element_at(iLine)->last()->m_iPosEnd + 1);

            if (iChar < 0)
            {

               return 0;

            }

            return iChar;

         }

         auto iPosBeg = plinea->element_at(iLine)->first()->m_iPosBeg;

         return minimum(iPosBeg + iColumn, iMax);

      }


      character_count edit::_hit_test(double_point point)
      {

         auto prichtextdata = get_rich_text_data();

         _synchronous_lock synchronouslock(prichtextdata->synchronization());

         //double xLast = 0.0;

         double_rectangle rBox;

         rBox.right() = -1024.0 * 1024.0 * 1024.0;
         rBox.bottom() = -1024.0 * 1024.0 * 1024.0;
         rBox.left() = 1024.0 * 1024.0 * 1024.0;
         rBox.top() = 1024.0 * 1024.0 * 1024.0;

         double yStart = -1024.0 * 1024.0 * 1024.0;

         double yLast = yStart - 1.0;

         character_count iLast = 0;

         auto plinea = m_plinea;

         for (auto & pline : *plinea)
         {

            for (auto & pbox : *pline)
            {

               rBox.unite(pbox->m_rectangleDevice);

               yLast = pbox->m_rectangleHitTest.top();

               if (point.y() < yLast)
               {

                  return iLast;

               }

               if (pbox->m_rectangleHitTest.contains_y(point.y()))
               {

                  double xLeft = pbox->m_rectangleDevice.left();

                  double xLast = pbox->m_rectangleHitTest.left();

                  double xRight;

                  character_count iPos = pbox->m_iPosBeg;

                  if (point.x() <= xLeft)
                  {

                     return iPos;

                  }

                  for (; iPos <= pbox->m_iPosEnd; iPos++)
                  {

                     xLeft = pbox->get_dev_pos_left(iPos);

                     xRight = (pbox->get_dev_pos_right(iPos) - xLeft) / 2.0 + xLeft;

                     if (floor(pbox->get_dev_pos_right(iPos)) == pbox->get_dev_pos_right(iPos))
                     {

                        xRight -= 0.5;

                     }

                     if (xLast <= point.x() && point.x() < xRight)
                     {

                        return iPos;

                     }

                     xLast = xRight;

                  }

                  if (pbox == pline->last_ptr())
                  {

                     return pbox->m_iPosEnd + 1;

                  }

               }

               if (pbox->m_iPosEnd > iLast)
               {

                  iLast = pbox->m_iPosEnd;

               }

            }

         }

         if (point.y() >= rBox.bottom())
         {

            return _001GetLayoutTextLength();

         }

         if (point.y() < rBox.top())
         {

            return 0;

         }

         return iLast;

      }


      character_count edit::_hit_test_line_x(::collection::index iLine, double x)
      {

         auto prichtextdata = get_rich_text_data();

         _synchronous_lock synchronouslock(prichtextdata->synchronization());

         auto plinea = m_plinea;

         if (iLine < 0 || iLine >= plinea->get_count())
         {

            return -1;

         }

         auto & pline = plinea->element_at(iLine);

         for (::collection::index iBox = 0; iBox < plinea->get_count(); iBox++)
         {

            auto & pbox = pline->element_at(iBox);

            if (x <= pbox->m_rectangleHitTest.left())
            {

               return pbox->m_iPosBeg;

            }
            else if (iBox >= pline->get_upper_bound() && x > pbox->m_rectangleHitTest.right())
            {

               return pbox->m_iPosEnd;

            }
            else if (x <= pbox->m_rectangleHitTest.right())
            {

               double xLeft = pbox->m_rectangleBox.left();

               double xLast = pbox->m_rectangleHitTest.left();

               double xRight;

               character_count iPos = pbox->m_iPosBeg;

               for (; iPos < pbox->m_iPosEnd; iPos++)
               {

                  xRight = (pbox->get_pos(iPos) - xLeft) / 2.0 + xLeft;

                  if (floor(xLast) < x && x <= floor(xRight))
                  {

                     return iPos - 1;

                  }

                  xLeft = pbox->get_pos(iPos);

                  xLast = xRight;

               }

               return iPos;

            }

         }

         return -1;

      }


      void edit::internal_update_sel_char()
      {

         _synchronous_lock synchronouslock(this->synchronization());

         //m_iSelBeg = sel_char(*plinea, m_iSelBeg3, m_ebiasBeg);

         //m_iSelEnd = sel_char(*plinea, m_iSelEnd3, m_ebiasEnd);

         //bool bNeedRedraw = false;

         character_count iSelBeg = m_iSelBeg;

         character_count iSelEnd = m_iSelEnd;

         string str;

         str = get_text();

         strsize_array ia1;

         strsize_array ia2;

         get_vars(ia1, ia2, str);

         for (::collection::index i = 0; i < ia1.get_count(); i++)
         {

            if (iSelEnd == ia1[i])
            {

               iSelEnd = ia1[i];

               iSelBeg = ia1[i];

               break;

            }
            else if (iSelEnd == ia2[i])
            {

               iSelEnd = ia2[i] + 1;

               iSelBeg = ia2[i] + 1;

               break;

            }
            else if (iSelEnd > ia1[i] && iSelEnd < ia2[i])
            {

               iSelEnd = ia1[i];

               iSelBeg = ia2[i] + 1;

               break;

            }

         }

         if (iSelBeg != m_iSelBeg)
         {

            m_iSelBeg = iSelBeg;

            //bNeedRedraw = true;

         }

         if (iSelEnd != m_iSelEnd)
         {

            m_iSelEnd = iSelEnd;

            //bNeedRedraw = true;

         }

         set_need_redraw();

         post_redraw();

      }


      character_count edit::_001GetLayoutTextLength() const
      {

         _synchronous_lock synchronouslock(this->synchronization());

         auto plinea = m_plinea;

         if (plinea->is_empty())
         {

            return 0;

         }

         return plinea->last()->last()->m_iPosEnd + 1;

      }


      void edit::draw_text(::draw2d::graphics_pointer & pgraphics, const ::double_rectangle & rectangleBox)
      {

         _synchronous_lock synchronouslock(pgraphics->synchronization());

         _synchronous_lock sl1(this->synchronization());

         //_synchronous_lock sl2(m_plinea->synchronization());

         //_synchronous_lock sl3(m_pformathost->synchronization());

         pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

         auto plinea = m_plinea;

         for (auto & pline : *plinea)
         {

            for (auto & pbox : *pline)
            {

               auto pformat = pbox->m_pspan->m_pformat;

               if (pformat.is_null())
               {

                  continue;

               }

               //if (pformat.is_null())
               //{

               //   pformat = __allocate format(this);

               //}

               ::int_rectangle rectangle = pbox->m_rectangleBox;


               if (pformat->m_escript == e_script_subscript)
               {

                  rectangle.offset(0, rectangle.height() / 6);

               }
               else if (pformat->m_escript == e_script_superscript)
               {

                  rectangle.offset(0, -rectangle.height() / 3);

               }

               if (m_ppictureimpl != nullptr && m_ppictureimpl->m_bOutline)
               {

                  auto ppath = __øcreate < ::draw2d::path >();

                  //ppath->add_draw_text(pbox->get_text(), rectangle, e_align_bottom_left | DT_SINGLELINE, pformat->get_font(pgraphics), pformat->m_colorForeground);
                  ppath->add_draw_text(pbox->get_text(), rectangle, e_align_bottom_left, e_draw_text_single_line, pformat->get_font(pgraphics));

                  auto ppen = __øcreate < ::draw2d::pen >();

                  auto pbrush = __øcreate < ::draw2d::brush >();

                  ppen->create_solid(m_ppictureimpl->m_iOutlineWidth, ::color::color(m_ppictureimpl->m_hlsOutline));

                  pbrush->create_solid(pformat->m_colorForeground);

                  pgraphics->set(ppen);

                  pgraphics->set(pbrush);

                  pgraphics->path(ppath);

               }
               else
               {

                  string strText = pbox->get_text();

                  if (strText.has_character())
                  {

                     pgraphics->set(pformat->get_font(pgraphics));

                     pgraphics->set_text_color(pformat->m_colorForeground);

                     pgraphics->draw_text(strText, rectangle, e_align_bottom_left, e_draw_text_single_line);

                  }

               }

            }

         }

      }



   } // namespace rich_text


} // namespace user


