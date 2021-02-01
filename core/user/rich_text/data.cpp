#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "core/user/rich_text/_rich_text.h"
#endif


namespace user
{


   namespace rich_text
   {


      ::count get_vars(strsize_array& ia1, strsize_array& ia2, string str)
      {

         strsize i1 = 0;

         strsize i2 = 0;

         while (true)
         {

            i1 = str.find('%', i1);

            if (i1 < 0)
            {

               break;

            }

            i2 = str.find('%', i1 + 1);

            if (i2 < 0)
            {

               break;

            }

            if (i2 == i1 + 1)
            {

               i1 = i2 + 1;

               continue;

            }

            ia1.add(i1);

            ia2.add(i2);

            i1 = i2 + 1;

         }

         ASSERT(ia1.get_size() == ia2.get_size());

         return ia1.get_size();

      }


      data::data()
      {

         //m_bNeedTextLayout = false;

         m_bCaretRight = false;

         m_pformata = __new(__pointer_array(format));

         m_pformatCurrent = add_format();

         m_plinea = __new(__pointer_array(line));

         m_iSelBeg = 0;

         m_iSelEnd = 0;

         m_millisCaretPeriod = 1000;

         defer_create_mutex();

      }


      data::~data()
      {

         if (mutex() == m_pedit->mutex())
         {

            set_mutex(nullptr);

         }

      }


      __pointer(format) data::add_format()
      {

         auto pformat = __new(format(m_pformata));

         m_pformata->add(pformat);

         return pformat;

      }

      __pointer(span) data::create_span(::e_align ealignNewLine)
      {

         return __new(span(this, ealignNewLine));

      }


      __pointer(span) data::add_span(const span & span)
      {

         sync_lock sl(mutex());

         return __new(class span(this, span));

      }


      __pointer(span) data::add_span(::e_align ealignNewLine)
      {

         sync_lock sl(mutex());

         auto pspan = create_span(ealignNewLine);

         if (pspan->m_pformat.is_null())
         {

            pspan->m_pformat = m_pformatCurrent;

         }

         m_spana.add(pspan);

         return pspan;

      }



      strsize data::get_sel_beg()
      {

         return min(max(min_non_neg(m_iSelBeg, m_iSelEnd), 0), _001GetTextLength());

      }


      strsize data::get_sel_end()
      {

         return min(max(max(m_iSelBeg, m_iSelEnd), 0), _001GetTextLength());

      }


      void data::on_selection_change(format * pformat)
      {

         sync_lock sl(mutex());

         index iSelBeg = get_sel_beg();

         index iSelEnd = get_sel_end() - 1;

         get_selection_intersection_format(pformat, iSelBeg, iSelEnd);

      }


      void data::get_selection_intersection_format(format * pformat, index iSelBeg, index iSelEnd)
      {

         sync_lock sl(mutex());

         update_span_cache(m_spana);

         index iSpanBeg = find_span(m_spana, iSelBeg);

         index iSpanEnd = find_span(m_spana, iSelEnd);

         if (iSpanBeg >= 0 && iSpanEnd >= iSpanBeg)
         {

            __pointer(span) pspanBeg = m_spana[iSpanBeg];

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

               if (m_spana[iSpanBeg]->m_ealignNewLine != e_align_none)
               {

                  ealign = e_align_none;

               }

               pformat->intersect(*m_spana[iSpanBeg]->m_pformat);

            }

         }

      }


      strsize data::hit_test(point_f64 point_i32)
      {

         sync_lock sl(mutex());

         //double xLast = 0.0;

         rectangle_f64 rBox;

         rBox.right = -1024.0 * 1024.0 * 1024.0;
         rBox.bottom = -1024.0 * 1024.0 * 1024.0;
         rBox.left = 1024.0 * 1024.0 * 1024.0;
         rBox.top = 1024.0 * 1024.0 * 1024.0;

         double yStart = -1024.0 * 1024.0 * 1024.0;

         double yLast = yStart - 1.0;

         strsize iLast = 0;

         auto plinea = m_plinea;

         for (auto & pline : plinea->ptra())
         {

            for (auto & pbox : pline->ptra())
            {

               rBox.max(pbox->m_rectDevice);

               yLast = pbox->m_rectHitTest.top;

               if (point.y < yLast)
               {

                  return iLast;

               }

               if (pbox->m_rectHitTest.contains_y(point.y))
               {

                  double xLeft = pbox->m_rectDevice.left;

                  double xLast = pbox->m_rectHitTest.left;

                  double xRight;

                  strsize iPos = pbox->m_iPosBeg;

                  if (point.x <= xLeft)
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

                     if (xLast <= point.x && point.x < xRight)
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

         if (point.y >= rBox.bottom)
         {

            return m_pedit->_001GetTextLength();

         }

         if (point.y < rBox.top)
         {

            return 0;

         }

         return iLast;

      }


      strsize data::hit_test_line_x(index iLine, double x)
      {

         sync_lock sl(mutex());

         auto plinea = m_plinea;

         if (iLine < 0 || iLine >= plinea->get_count())
         {

            return -1;

         }

         auto & pline = plinea->element_at(iLine);

         for (index iBox = 0; iBox < plinea->get_count(); iBox++)
         {

            auto& pbox = pline->element_at(iBox);

            if (x <= pbox->m_rectHitTest.left)
            {

               return pbox->m_iPosBeg;

            }
            else if (iBox >= pline->get_upper_bound() && x > pbox->m_rectHitTest.right)
            {

               return pbox->m_iPosEnd + 1;

            }
            else if (x <= pbox->m_rectHitTest.right)
            {

               double xLeft = pbox->m_rectBox.left;

               double xLast = pbox->m_rectHitTest.left;

               double xRight;

               strsize iPos = pbox->m_iPosBeg;

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


      void data::_001GetText(string & str) const
      {

         sync_lock sl(mutex());

         str = text(m_spana);

      }


      void data::_001GetLayoutText(string & str) const
      {

         sync_lock sl(mutex());

         str = layout_text(*m_plinea);

      }


      index data::SelToLine(strsize iSel) const
      {

         return sel_line(*m_plinea, iSel);

      }


      index data::LineColumnToSel(index iLine, strsize iColumn) const
      {

         sync_lock sl(mutex());

         if (iLine < 0)
         {

            return -1;

         }

         int iMax = (int) _001GetLayoutTextLength();

         auto plinea = m_plinea;

         if (iLine >= plinea->get_count())
         {

            return iMax;

         }

         if (iColumn < 0)
         {

            int iChar = (int) ( iColumn + plinea->element_at(iLine)->last()->m_iPosEnd + 2);

            if (iChar < 0)
            {

               return 0;

            }

            return iChar;

         }

         return min(plinea->element_at(iLine)->first()->m_iPosBeg + iColumn, iMax);

      }


      void data::_001Delete(strsize i1, strsize i2)
      {

         strsize iSelBeg = min_non_neg(i1, i2);

         strsize iSelEnd = max(i1, i2);

         if (iSelBeg == iSelEnd)
         {

            return;

         }

         sync_lock sl(mutex());

         update_span_cache(m_spana);

         index iSpanBeg = find_span(m_spana, iSelBeg);

         index iSpanEnd = find_span(m_spana, iSelEnd - 1);

         if (iSpanBeg >= 0 && iSpanEnd >= iSpanBeg)
         {

            __pointer(span) pspanBeg = m_spana[iSpanBeg];

            __pointer(span) pspanEnd = m_spana[iSpanEnd];

            if (iSpanBeg == iSpanEnd)
            {

               __pointer(span) pspanNext;

               if (iSpanEnd + 1 < m_spana.get_count())
               {

                  pspanNext = m_spana[iSpanEnd + 1];

               }

               if (iSelBeg == pspanBeg->m_iPosEnd && pspanNext.is_set() && pspanNext->is_new_line())
               {

                  if (pspanBeg->m_pformat == pspanNext->m_pformat)
                  {

                     pspanBeg->m_str += pspanNext->m_str;

                     m_spana.remove_at(iSpanEnd + 1);

                     return;

                  }
                  else
                  {

                     pspanNext->m_ealignNewLine = e_align_none;

                  }

               }

               pspanBeg->m_str = pspanBeg->m_str.Left(iSelBeg - pspanBeg->m_iPosBeg) + pspanBeg->m_str.Mid(iSelEnd - pspanBeg->m_iPosBeg);

               if (pspanBeg->m_str.is_empty())
               {

                  m_spana.remove_at(iSpanBeg);

               }

               return;

            }

            index iEndBeg = pspanEnd->m_iPosBeg;

            index iEndEnd = pspanEnd->m_iPosEnd;

            if (iSelBeg > pspanBeg->m_iPosBeg)
            {

               pspanBeg->m_str = pspanBeg->m_str.Left(iSelBeg - pspanBeg->m_iPosBeg);

               pspanBeg->m_iPosEnd = (int) iSelBeg;

               iSpanBeg++;

            }

            if (iSelEnd <= iEndEnd)
            {

               pspanEnd->m_str = pspanEnd->m_str.Mid(iSelEnd - iEndBeg);

               pspanEnd->m_iPosBeg = (int) iSelEnd;

               iSpanEnd--;

            }

            int iCount = (int) (iSpanEnd - iSpanBeg + 1);

            if (iCount > 0)
            {

               m_spana.remove_at(iSpanBeg, iCount);

            }

         }

         optimize_data();

      }


      string data::get_full_text()
      {

         sync_lock sl(mutex());

         update_span_cache(m_spana);

         return text(m_spana);

      }


      void data::_001InsertText(const char * psz, format * pformatParam)
      {

         string_array straLines;

         straLines.add_lines(psz);

         sync_lock sl(mutex());

         index iSelBeg = get_sel_beg();

         index iSelEnd = get_sel_end();

         _001Delete(iSelBeg, iSelEnd);

         index iSelChar = iSelBeg;

         index iSpan = find_span(m_spana, iSelChar);

         __pointer(format) pformat;

         __pointer(span) pspan;

         ::e_align ealignNewLine;

         if (iSpan >= 0)
         {

            pspan = m_spana[iSpan];

            pformat = pspan->format();

            ealignNewLine = pspan->get_align();

            iSpan++;

         }
         else
         {

            pformat = m_pformatCurrent;

            ealignNewLine = e_align_left;

            iSpan = 0;

         }

         string str;

         for (index iLine = 0; iLine < straLines.get_count(); iLine++)
         {

            string strLine = straLines[iLine];

            if (iLine > 0 && iLine >= straLines.get_upper_bound())
            {

               break;

            }

            bool bNewSpan = false;

            if (pformatParam != nullptr)
            {

               if (iLine <= 0 || pformatParam->m_ealign != e_align_none)
               {

                  pspan = create_span(pformatParam->m_ealign);

               }
               else
               {

                  pspan = create_span(ealignNewLine);

               }

               pspan->m_pformat = pformatParam;

               m_spana.insert_at(iSpan, pspan);

               bNewSpan = true;

            }
            else if (iLine > 0 || !pspan)
            {

               pspan = create_span(ealignNewLine);

               pspan->m_pformat = m_pformatCurrent;

               m_spana.insert_at(iSpan, pspan);

               bNewSpan = true;

            }

            if (bNewSpan)
            {

               pspan->m_str = straLines[iLine];

            }
            else
            {

               ASSERT(iSelBeg >= pspan->m_iPosBeg);

               strsize iMid = iSelBeg - pspan->m_iPosBeg + 1;

               if (iLine >= straLines.get_upper_bound())
               {

                  pspan->m_str = pspan->m_str.Left(iMid) + strLine + pspan->m_str.Mid(iMid);

               }
               else
               {

                  {

                     auto pspanLast = create_span(ealignNewLine);

                     pspanLast->m_str = straLines.last() + pspan->m_str.Mid(iMid);

                     pspanLast->m_ealignNewLine = pspan->get_align();

                     pspanLast->m_pformat = pspan->m_pformat;

                     m_spana.insert_at(iSpan, pspanLast);

                  }

                  pspan->m_str = pspan->m_str.Left(iMid) + strLine;

               }

            }

            iSelChar += straLines[iLine].get_length();

            if (iLine < straLines.get_upper_bound())
            {

               iSelChar++;

            }

            iSpan++;

         }

         m_iSelBeg = m_iSelEnd = iSelChar;

         update_span_cache(m_spana);

         m_pedit->on_after_change(::user::e_event_after_change_text);

      }



      void data::_001SetSelFontFormat(const format * pformat, const eattribute & eattribute)
      {

         sync_lock sl(mutex());

         optimize_data();

         string strText = get_full_text();

         index iSelBeg = get_sel_beg();

         index iSelEnd = get_sel_end() - 1;

         index iBeg = find_span(m_spana, iSelBeg);

         index iEnd = find_span(m_spana, iSelEnd);

         if (iBeg >= 0 && iEnd >= iBeg)
         {

            auto pspanBeg = m_spana[iBeg];

            auto pspanEnd = m_spana[iEnd];

            index iEndBeg = pspanEnd->m_iPosBeg;

            index iEndEnd = pspanEnd->m_iPosEnd;

            string str;

            if (iBeg == iEnd)
            {

               if (iSelBeg > pspanBeg->m_iPosBeg)
               {

                  str = pspanBeg->m_str;

                  pspanBeg->m_str = str.Left(iSelBeg - pspanBeg->m_iPosBeg);

                  auto pspan2 = pspanBeg->fork(pformat, eattribute);
                  pspan2->m_str = str.Mid(iSelBeg - pspanBeg->m_iPosBeg, iSelEnd - iSelBeg + 1);
                  m_spana.insert_at(iBeg + 1, pspan2);

                  if (iSelEnd < pspanBeg->m_iPosEnd)
                  {

                     auto pspan3 = pspanBeg->fork();
                     pspan3->m_str = str.Mid(iSelEnd - pspanBeg->m_iPosBeg + 1);
                     m_spana.insert_at(iBeg + 2, pspan3);

                  }

               }
               else
               {

                  if (iSelEnd + 1 < pspanBeg->m_iPosEnd)
                  {

                     str = pspanBeg->m_str;

                     auto pspan2 = pspanBeg->fork();
                     pspan2->m_str = str.Mid(iSelEnd - pspanBeg->m_iPosBeg + 1);
                     m_spana.insert_at(iBeg + 1, pspan2);

                     pspanBeg->m_str = str.Left(iSelEnd - pspanBeg->m_iPosBeg + 1);

                  }

                  pspanBeg->m_pformat.merge(m_pformata, pformat, eattribute);

               }

            }
            else
            {

               if (iSelBeg > pspanBeg->m_iPosBeg)
               {

                  iEnd++;

                  str = pspanBeg->m_str;

                  pspanBeg->m_str = str.Left(iSelBeg - pspanBeg->m_iPosBeg);

                  auto pspan2 = pspanBeg->fork(pformat, eattribute);
                  pspan2->m_str = str.Mid(iSelBeg - pspanBeg->m_iPosBeg);
                  m_spana.insert_at(iBeg + 1, pspan2);

               }
               else
               {

                  pspanBeg->m_pformat.merge(m_pformata,pformat, eattribute);

               }


               if (iSelEnd < iEndEnd)
               {

                  str = pspanEnd->m_str;

                  auto pspan3 = pspanEnd->fork(pformat, eattribute);
                  pspan3->m_str = str.Left(iSelEnd - iEndBeg + 1);

                  m_spana.insert_at(iEnd, pspan3);

                  pspanEnd->m_str = str.Mid(iSelEnd - iEndBeg + 1);

               }
               else
               {

                  pspanEnd->m_pformat.merge(m_pformata,pformat, eattribute);

               }

               for (index i = iBeg + 1; i < iEnd; i++)
               {

                  if (m_spana[i].is_set())
                  {

                     m_spana[i]->m_pformat.merge(m_pformata, pformat, eattribute);

                  }

               }

            }

         }

         m_pedit->on_after_change(::user::e_event_after_change_text_format);

      }

      // ::str::utf8_inc(str.c_str()) - str.c_str(); // at least one char is the longest pline

      // find phrase with greatest word count that fits the x, right constraints
      ::count longest_pline(string & strSlice, double & d, string_array & straWords, double * pdaPosition, double dPositionLeft, int cx)
      {

         count c = straWords.get_count();

         for (; c > 0; c--)
         {

            strSlice = straWords.implode("", 0, c);

            auto iLen = strSlice.length();

            auto iLenTrimmed = strSlice.right_trimmed().length();

            d = pdaPosition[iLenTrimmed - 1] - dPositionLeft;

            if (d <= cx)
            {

               d = pdaPosition[iLen - 1];

               return c;

            }

         }

         return -1;

      }


      int longest_word(string & strSlice, double & dPosition, string strWord, double * pdaPosition, double dPositionLeft, int cx)
      {

         long l = 1;

         auto u = strWord.get_length();

         long m = 1;

         while(l < u)
         {

            m = (long) ((l + u) / 2);

            dPosition = pdaPosition[m - 1] - dPositionLeft;

            if(dPosition > cx)
            {

               u = m - 1;

            }
            else
            {

               l = m + 1;

            }


         }

         while (m < strWord.length())
         {

            dPosition = pdaPosition[m - 1] - dPositionLeft;

            if (dPosition > cx)
            {

               break;

            }

            m++;

         }

         while (m > 1)
         {

            dPosition = pdaPosition[m - 1] - dPositionLeft;

            if (dPosition <= cx)
            {

               break;

            }

            m--;

         }

         if (m < 1)
         {

            m = 1;

         }

         strSlice = strWord.Left(m);

         dPosition = pdaPosition[m - 1];

         return (int) m;

      }


      //void data::do_layout()
      //{

      //   //if (m_rectangle.is_empty())
      //   //{
      //   //
      //   //   if (m_pedit->is_picture_enabled())
      //   //   {

      //   //      m_rectangle = m_pedit.get_rect_for_picture();

      //   //   }

      //   //}

      //   do_layout(m_pedit->m_rectangle);

      //}


      //void data::do_layout()
      //{

      //   sync_lock sl(mutex());

      //   if (m_pgraphics.is_null())
      //   {

      //      m_pgraphics.create(this);

      //      m_pgraphics->CreateCompatibleDC(nullptr);

      //   }

      //   ::draw2d::savedc savedc(m_pgraphics);

      //   do_layout(m_pgraphics);

      //}


      void data::do_layout(::draw2d::graphics_pointer & pgraphics)
      {

         //m_rectangle = rectangle_i32;

         sync_lock sl(mutex());

         pgraphics->set_text_rendering_hint(::draw2d::text_rendering_hint_anti_alias);

         if (m_spana.is_empty())
         {

            auto pspan = __new(span(this));

            m_spana.add(pspan);

         }

         if (m_spana.first()->m_ealignNewLine == e_align_none)
         {

            m_spana.first()->m_ealignNewLine = e_align_left;

         }

         update_span_cache(m_spana);

         bool bLineWrap = false;

         auto rectangle_i32 = get_drawing_rect();

         rectangle_f64 rectClient(rectangle);

         int x = (int) rectangle.left;

         int xLast = x;

         bool bFirstParagraph = true;

         auto plinea = __new(__pointer_array(line));

         __pointer(line) pline;

         //strsize iCharLayout = 0;

   //if (m_spana.first().m_pformat >= m_pformata.get_count())
   //{

   //   m_pformata.add(__new(format(get_object())));

   //}

         //if (m_spana.is_empty())
         //{

         //   add_span(e_align_left);

         //   m_spana.first_pointer()->m_iFormat = 0;

         //   if (m_spana.first_pointer()->m_iFormat >= m_pformata.get_count())
         //   {

         //      m_pformata.add(__new(format(get_object())));

         //   }

         //}
         //else if (!m_spana[0]->is_new_line())
         //{

         //   m_spana[0]->m_ealignNewLine = e_align_left;

         //}

         // horizontal span

         ::e_align ealign = e_align_center;

         __pointer_array(span) spana;

         //strsize iSpanCharEnd = 0;

         index iSpan = 0;

         ::count cWords = 0;

         //index iSpanNextWord;
         string strSlice;

         string_array straWords;

         double dPosition;

         __pointer(box) pbox;

         //bool bMultiWordFormat = true;

         //__pointer_array(span) spanaMultiWordFormat;

//         int iHeight;

         while (iSpan < m_spana.get_count())
         {

            __pointer(span) pspan = m_spana[iSpan];

            pspan->m_str.replace("\n", "");

            pspan->m_str.replace("\r", "");

            auto pformat = pspan->format();

            pgraphics->set(pformat->get_font(pgraphics));

            {

               auto iLenSpan = pspan->m_str.length();

               auto iLenMeasure = pgraphics->get_character_extent(pspan->m_daPositionLeft, pspan->m_daPositionRight, pspan->m_str);

               if(iLenSpan != iLenMeasure)
               {

                  ASSERT(FALSE);

                  output_debug_string("unexpected: iLenSpan != iLenMeasure");

               }

            }

            pspan->m_sizeSpan = pgraphics->GetTextExtent(pspan->m_str);

            strsize iSpanChar = 0;

            double dPositionLeft = 0.;

         restart_span:

            strSlice.Empty();

            //if (spanaMultiWordFormat.is_empty() &&
            if((pspan->is_new_line() || iSpanChar > 0))
            {

               if (pline.is_set())
               {

                  ASSERT(pline->has_element());

                  plinea->add(pline);

               }

               pline = __new(line);

               x = (int) rectangle.left;

               xLast = x;

               bLineWrap = false;

               ealign = pspan->m_ealignNewLine;

               x = (int) rectangle.left;

               //pbox = __new(box(pspan));

               //index iSpan = find_char_span(m_spana, iCharLayout);

               //int iHeight = pspan->format()->m_font->get_height();

               //pbox->m_rectangle.set(x, 0, x, 0);

               //pbox->m_rectHitTest.set(x, 0, x, 0);

               //pbox->m_size.set_size(0, iHeight);

               //pbox->m_iPosBeg = pspan->m_iPosBeg + iCharLayout;

               //pbox->m_iPosEnd = pspan->m_iPosBeg + (bFirstParagraph ? iCharLayout : iCharLayout + 1);

               //iCharLayout = pbox->m_iPosEnd;

               pline->m_dLeft = x;

               pline->m_dLeftDevice = x;

               //pline->add(pbox);

               bFirstParagraph = false;

            }

            // Format Word

            string strTopic = &pspan->m_str[iSpanChar];

            if (strTopic.is_empty())
            {

               if (pline->is_empty())
               {

                  auto pbox = __new(box(pspan));

                  pbox->m_iPosBeg = pspan->m_iPosBeg + iSpanChar;

                  iSpanChar += strSlice.get_upper_bound();

                  pbox->m_iPosEnd = pspan->m_iPosBeg + iSpanChar;

                  // keeping dimensions
                  //pbox->m_size.cy = pspan->m_size.cy;

                  //if (pbox->m_size.cy <= 0)
                  {

                     pbox->m_sizeBox.cy = pformat->get_font(pgraphics)->get_height(pgraphics);

                  }

                  pbox->m_sizeBox.cx = 0;

                  // just horizonal layout
                  pbox->m_rectBox.set_dim(x, 0, pbox->m_sizeBox.cx, 0);

                  pbox->m_rectHitTest = pbox->m_rectBox;

                  pline->add(pbox);

               }

               goto new_span;

            }

            straWords.remove_all();

            words_trailing_spaces(straWords, strTopic);

            if (straWords.get_count() <= 0)
            {

               goto new_span;

            }

            strSlice.Empty();

            cWords = (int) longest_pline(strSlice, dPosition, straWords, &pspan->m_daPositionRight[iSpanChar], dPositionLeft, (int) rectClient.right - x);

            if (ansi_char_is_space(straWords.last().last_char())
               || (iSpan + 1 < m_spana.get_count()
                  && (m_spana[iSpan + 1]->is_new_line()
                     || (m_spana[iSpan + 1]->m_str.has_char()
                        && ansi_char_is_space(m_spana[iSpan + 1]->m_str[0]))))
               || cWords < straWords.get_count())
            {

               if (cWords > 0)
               {

                  auto pbox = __new(box(pspan));

                  pbox->m_iPosBeg = pspan->m_iPosBeg + iSpanChar;

                  iSpanChar += strSlice.get_upper_bound();

                  pbox->m_iPosEnd = pspan->m_iPosBeg + iSpanChar;

                  // keeping dimensions
                  pbox->m_sizeBox.cy = pspan->m_sizeSpan.cy;

                  pbox->m_sizeBox.cx = dPosition - dPositionLeft;

                  // just horizonal layout
                  pbox->m_rectBox.set_dim(x, 0, pbox->m_sizeBox.cx, 0);

                  pbox->m_rectHitTest = pbox->m_rectBox;

                  pline->add(pbox);

                  x += (int) pbox->m_sizeBox.cx;

                  if (cWords >= straWords.get_count())
                  {

                     goto new_span;

                  }
                  else
                  {

                     iSpanChar++;

                     dPositionLeft = dPosition;

                     goto restart_span;

                  }

               }

               string strWord = straWords[0];

               strSlice.Empty();

               longest_word(strSlice, dPosition, strWord, &pspan->m_daPositionRight[iSpanChar], dPositionLeft, (int) rectClient.right - x);

               auto pbox = __new(box(pspan));

               pbox->m_iPosBeg = pspan->m_iPosBeg + iSpanChar;

               iSpanChar += strSlice.get_upper_bound();

               pbox->m_iPosEnd = pspan->m_iPosBeg + iSpanChar;

               // keeping dimensions
               pbox->m_sizeBox.cy = pspan->m_sizeSpan.cy;

               pbox->m_sizeBox.cx = dPosition - dPositionLeft;

               // just horizonal layout
               pbox->m_rectBox.set_dim(x, 0, pbox->m_sizeBox.cx, 0);

               pbox->m_rectHitTest = pbox->m_rectBox;

               pline->add(pbox);

               x += (int) pbox->m_sizeBox.cx;

               iSpanChar++;

               dPositionLeft = dPosition;

               goto restart_span;

            }
            else
            {

               auto pbox = __new(box(pspan));

               pbox->m_iPosBeg = pspan->m_iPosBeg + iSpanChar;

               iSpanChar += strTopic.get_upper_bound();

               pbox->m_iPosEnd = pbox->m_iPosBeg + iSpanChar;

               // keeping dimensions
               pbox->m_sizeBox.cy = pspan->m_sizeSpan.cy;

               pbox->m_sizeBox.cx = dPosition;

               // just horizonal layout
               pbox->m_rectBox.set_dim(x, 0, pbox->m_sizeBox.cx, 0);

               pbox->m_rectHitTest = pbox->m_rectBox;

               pline->add(pbox);

               x += (int)  pbox->m_sizeBox.cx;

               //spanaMultiWordFormat.add(pspan);

            }

         new_span:

            iSpan++;

         }

         if (pline.is_set())
         {

            ASSERT(pline->has_element());

            plinea->add(pline);

         }

         for (auto& pline : plinea->ptra())
         {

            align(pline, rectClient);

         }

         m_plinea = plinea;

      }


      ::rectangle_f64 data::get_drawing_rect()
      {

         ::rectangle_f64 rectangle_i32;

         if (m_pedit->is_picture_enabled())
         {

            rectangle_i32 = m_pedit->m_ppictureimpl->m_rectDrawing;

            rectangle_i32 -= rectangle.origin();

         }
         else
         {

            rectangle_i32 = m_pedit->get_client_rect();

         }

         return rectangle;

      }


      void data::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
      {

         sync_lock sl(mutex());

         if (pgraphics->m_bPrinting)
         {

            pgraphics->set_text_rendering_hint(::draw2d::text_rendering_hint_anti_alias);

         }
         else
         {

            pgraphics->set_text_rendering_hint(::draw2d::text_rendering_hint_anti_alias);

         }

         //rectangle_f64 rectClient(rectangle);

         auto rectangle_i32 = get_drawing_rect();

         //pgraphics->draw3d_rect(rectangle, ARGB(255, 0, 127, 0));

         bool bHasFocus = false;

         if (m_pedit->has_focus())
         {

            bHasFocus = true;

         }

         bool bCaretOn = false;

         if (bHasFocus && m_pedit->is_text_editable())
         {

            bCaretOn = m_pedit->m_millisFocusStart.on_off(m_millisCaretPeriod);

         }

         if (m_pedit->m_bPendingSelectionChange)
         {

            m_pedit->m_bPendingSelectionChange = false;

            m_pedit->on_selection_change();

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

            int y = (int)  rectangle.top;


            int nexty;

            // vertical span

            for (auto& pline : plinea->ptra())
            {

               int iMaxCy = 0;

               for (auto& pbox : pline->ptra())
               {

                  iMaxCy = max(iMaxCy, (int) pbox->m_sizeBox.cy);

                  pbox->m_rectBox.top = y;

                  pbox->m_rectHitTest.top = y;

               }

               nexty = y + iMaxCy;

               for (auto& pbox : pline->ptra())
               {

                  pbox->m_rectBox.bottom = nexty;

                  pbox->m_rectHitTest.bottom = nexty;

                  //pbox->m_rectBox.right += 2;

               }

               y = nexty;

            }

            // Draw Select Rectangle

            color32_t crBkSel;

            if (bHasFocus && m_pedit->is_text_editable())
            {

               crBkSel = ARGB(192, 175, 200, 240);

            }
            else
            {

               crBkSel = ARGB(127, 192, 210, 225);

            }

            {

               //strsize iSelBeg = get_sel_beg();

               //strsize iSelEnd = get_sel_end();

               for(index iLine = 0; iLine < plinea->get_count(); iLine++)
               {

                  auto& pline = plinea->element_at(iLine);

                  if (pline->has_element())
                  {

                     auto pboxBeg = pline->first_pointer();

                     auto pboxEnd = pline->last_pointer();

                     strsize iBoxPosBeg = pboxBeg->m_iPosBeg;

                     strsize iBoxPosEnd = pboxEnd->m_iPosEnd + 1;

                     if (iBoxPosBeg <= get_sel_end() && get_sel_beg() <= iBoxPosEnd)
                     {

                        iBoxPosBeg = max(iBoxPosBeg, get_sel_beg());

                        iBoxPosEnd = min(iBoxPosEnd, get_sel_end());

                        index iBeg = pline->pred_find_first([&](auto & pbox)
                        {

                           return pbox->m_iPosBeg <= iBoxPosBeg && iBoxPosBeg <= pbox->m_iPosEnd;

                        });

                        if (iBeg >= 0)
                        {

                           pboxBeg = pline->element_at(iBeg);

                           index iEnd = pline->pred_find_first([&](auto & pbox)
                           {

                              return pbox->m_iPosBeg <= iBoxPosEnd && iBoxPosEnd <= pbox->m_iPosEnd + 1;

                           });

                           if (iEnd >= 0)
                           {

                              pboxEnd = pline->element_at(iEnd);

                              double l;

                              if (iBoxPosBeg == pboxBeg->m_iPosBeg)
                              {

                                 l = pboxBeg->m_rectBox.left;

                              }
                              else
                              {

                                 l = pboxBeg->get_pos_left(iBoxPosBeg);

                              }

                              double r;

                              if (iBoxPosEnd == pboxEnd->m_iPosBeg)
                              {

                                 r = pboxEnd->m_rectBox.left;

                              }
                              else if (iBoxPosEnd >= pboxEnd->m_iPosEnd + 1)
                              {

                                 r = pboxEnd->m_rectBox.right;

                              }
                              else
                              {

                                 r = pboxEnd->get_pos_left(iBoxPosEnd);
                              }

                              pgraphics->fill_rect(
                                 ::rectd_dim(l,
                                 pboxBeg->m_rectBox.top,
                                 r,
                                 pboxEnd->m_rectBox.bottom),
                                 crBkSel);

                           }

                        }

                     }

                  }

               }

            }

            ::draw2d::fastblur blurDropShadow;

            ::image_pointer imageDropShadow;

            ::rectangle_i32 rDropShadow;

            if (m_pedit->m_ppictureimpl != nullptr)
            {

               rDropShadow = m_pedit->m_ppictureimpl->m_rectDrawing;

               rDropShadow.offset(-rDropShadow.center());

            }

            ::image_pointer pimage;

            if (m_pedit->m_ppictureimpl != nullptr && m_pedit->m_ppictureimpl->m_bGlowDropShadow)
            {

               pimage->create(m_pedit->m_ppictureimpl->m_rectDrawing.size());

               ::size_i32 sz = m_pedit->m_ppictureimpl->m_rectDrawing.size();

               pimage->g()->SetViewportOrg(sz.cx / 2, sz.cy / 2);

               ::draw2d::graphics_pointer pgraphicsImage = pimage->g();

               draw_text(pgraphicsImage, rectangle);

               pimage->g()->SetViewportOrg(0, 0);

               m_pedit->defer_draw_drop_shadow_phase1(rDropShadow, blurDropShadow, imageDropShadow, pimage);

               m_pedit->defer_draw_drop_shadow_phase2(pgraphics, rDropShadow, blurDropShadow, imageDropShadow);

            }

            draw_text(pgraphics, rectangle);

            // Draw Caret

            if (bCaretOn && m_pedit->is_text_editable())
            {

               __pointer(box) pbox = find_box(*plinea, m_iSelEnd);

               if (pbox->is_set())
               {

                  double r;

                  r = pbox->get_pos(m_iSelEnd);

                  //r += rectangle.left;

                  if (r > rectangle.left)
                  {

                     r -= 1.0;

                  }

                  if (r < rectangle.left + 2)
                  {

                     r = rectangle.left + 2;

                  }

                  if (r > rectangle.right - 2)
                  {

                     r = rectangle.right - 2;

                  }

                  auto dDescent = pbox->m_pspan->m_pformat->m_font->get_descent(pgraphics);

                  pgraphics->fill_rect(::rectangle_f64(r,
                     pbox->m_rectBox.top + 1,
                     r + 0.5,
                     pbox->m_rectBox.bottom - dDescent),
                     ARGB(255, 0, 0, 0));

               }

            }

            ::draw2d::matrix m;

            pgraphics->get_viewport_scale(m);

            //m.invert();

            for (auto& pline : plinea->ptra())
            {

               for (auto& pbox : pline->ptra())
               {

                  pbox->m_rectDevice = pbox->m_rectBox;

                  m.transform(pbox->m_rectHitTest.top_left());
                  m.transform(pbox->m_rectHitTest.bottom_right());

                  m.transform(pbox->m_rectDevice.top_left());
                  m.transform(pbox->m_rectDevice.bottom_right());

               }

            }


         for (auto& pspan : m_spana.ptra())
         {

            pspan->m_daPositionDeviceLeft.remove_all();
            pspan->m_daPositionDeviceRight.remove_all();

            for (auto& x : pspan->m_daPositionLeft)
            {

               pspan->m_daPositionDeviceLeft.add(x * m.a1);

            }

            for (auto& x : pspan->m_daPositionRight)
            {

               pspan->m_daPositionDeviceRight.add(x * m.a1);

            }

         }

      }


      void data::optimize_data()
      {

         sync_lock sl(mutex());

         m_pformata->remove_all();

         for (index i = 0; i < m_spana.get_count(); i++)
         {

            //m_spana[i]->m_pformat->get_object() = get_object();

            m_spana[i]->m_pformat->m_pcontainer = m_pformata;

            m_spana[i]->m_pformat = m_pformata->get_existing_defer_add(m_spana[i]->m_pformat);

         }


         //for (index i = 0; i < m_spana.get_count(); i++)
         //{

         //   m_spana[i]->m_pformat = get_format(m_spana, m_spana[i]->m_pformat);

         //}

         for (index i = 0; i < m_spana.get_count(); )
         {

            auto pformat = m_spana[i]->m_pformat;

            i++;

            while (i < m_spana.get_count() && !m_spana[i]->is_new_line())
            {

               if (m_spana[i]->m_pformat == pformat)
               {

                  auto pspanTarget = m_spana[i - 1];

                  auto pspanRemove = m_spana[i];

                  pspanTarget->m_str += pspanRemove->m_str;

                  m_spana.remove_at(i);

               }
               else
               {

                  break;

               }

            }

         }

         update_span_cache(m_spana);

      }


      strsize data::_001GetTextLength() const
      {

         sync_lock sl(mutex());

         if (m_spana.isEmpty())
         {

            return 0;

         }

         return m_spana.last()->m_iPosEnd;

      }


      strsize data::_001GetLayoutTextLength() const
      {

         sync_lock sl(mutex());

         auto plinea = m_plinea;

         if (plinea->is_empty())
         {

            return 0;

         }

         return plinea->last()->last()->m_iPosEnd + 1;

      }


      void data::internal_update_sel_char()
      {

         sync_lock sl(mutex());

         //m_iSelBeg = sel_char(*plinea, m_iSelBeg3, m_ebiasBeg);

         //m_iSelEnd = sel_char(*plinea, m_iSelEnd3, m_ebiasEnd);

         bool bNeedRedraw = false;

         strsize iSelBeg = m_iSelBeg;

         strsize iSelEnd = m_iSelEnd;

         string str;

         _001GetText(str);

         strsize_array ia1;

         strsize_array ia2;

         get_vars(ia1, ia2, str);

         for (index i = 0; i < ia1.get_count(); i++)
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

            bNeedRedraw = true;

         }

         if (iSelEnd != m_iSelEnd)
         {

            m_iSelEnd = iSelEnd;

            bNeedRedraw = true;

         }

         m_pedit->set_need_redraw();

      }


      stream & data::write(::stream & stream) const
      {

         sync_lock sl(mutex());

         {

            ::papaya::array::exchange_container_as_parent(stream, *m_pformata);

         }

         {

            stream.set_context_object(get_context_object());

            stream << m_spana;

         }

         return stream;

      }


      stream & data::read(::stream & stream)
      {

         sync_lock sl(mutex());

         m_plinea->remove_all();

         m_pformata->remove_all();

         m_spana.remove_all();

         {

            ::papaya::array::exchange_container_as_parent(stream, *m_pformata);

         }

         {

            stream.set_context_object(get_context_object());

            stream >> m_spana;

         }

         return stream;

      }


      void data::draw_text(::draw2d::graphics_pointer & pgraphics, const ::rectangle_f64 & rectBox)
      {

         sync_lock sl(pgraphics->mutex());

         sync_lock sl1(mutex());

         //sync_lock sl2(m_plinea->mutex());

         //sync_lock sl3(m_pformata->mutex());

         pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

         auto plinea = m_plinea;

         for (auto & pline : plinea->ptra())
         {

            for (auto & pbox : pline->ptra())
            {

               auto pformat = pbox->m_pspan->m_pformat;

               if (pformat.is_null())
               {

                  continue;

               }

               //if (pformat.is_null())
               //{

               //   pformat = __new(format(get_object()));

               //}

               ::rectangle_i32 rectangle = pbox->m_rectBox;


               if (pformat->m_escript == script_subscript)
               {

                  rectangle.offset(0, rectangle.height() / 6);

               }
               else if (pformat->m_escript == script_superscript)
               {

                  rectangle.offset(0, -rectangle.height() / 3);

               }

               if (m_pedit->m_ppictureimpl != nullptr && m_pedit->m_ppictureimpl->m_bOutline)
               {

                  ::draw2d::path_pointer path(e_create);

                  //path->add_draw_text(pbox->get_text(), rectangle_i32, e_align_bottom_left | DT_SINGLELINE, pformat->get_font(pgraphics), pformat->m_colorForeground);
                  path->add_draw_text(pbox->get_text(), rectangle_i32, e_align_bottom_left, e_draw_text_single_line, pformat->get_font(pgraphics));

                  ::draw2d::pen_pointer pen(e_create);

                  ::draw2d::brush_pointer brush(e_create);

                  pen->create_solid(m_pedit->m_ppictureimpl->m_iOutlineWidth, color(m_pedit->m_ppictureimpl->m_hlsOutline));

                  brush->create_solid(pformat->m_colorForeground);

                  pgraphics->set(pen);

                  pgraphics->set(brush);

                  pgraphics->path(path);

               }
               else
               {

                  pgraphics->set(pformat->get_font(pgraphics));

                  pgraphics->set_text_color(pformat->m_colorForeground);

                  string strText = pbox->get_text();

                  pgraphics->draw_text(strText, rectangle_i32, e_align_bottom_left, e_draw_text_single_line);

               }

            }

         }

      }


   } // namespace rich_text


} // namespace user



