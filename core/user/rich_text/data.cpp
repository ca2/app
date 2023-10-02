#include "framework.h"
#include "data.h"
#include "edit_impl.h"
#include "format.h"
#include "line.h"
#include "box.h"
#include "acme/constant/id.h"
#include "acme/parallelization/mutex.h"
#include "acme/primitive/data/listener.h"
//#include "acme/primitive/time/integral/generic.h"
#include "aura/graphics/draw2d/graphics.h"
#include "aura/graphics/write_text/font.h"
#include "aura/graphics/image/image.h"
#include "aura/graphics/draw2d/path.h"
#include "aura/graphics/draw2d/brush.h"
#include "acme/primitive/collection/_array_binary_stream.h"


namespace user
{


   namespace rich_text
   {

      void align(line * pline, const ::rectangle_f64 & rectangle);

      ::count get_vars(strsize_array& ia1, strsize_array& ia2, string str)
      {

         strsize i1 = 0;

         strsize i2 = 0;

         while (true)
         {

            i1 = str.find_index('%', i1);

            if (i1 < 0)
            {

               break;

            }

            i2 = str.find_index('%', i1 + 1);

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

         m_iSelBeg = 0;

         m_iSelEnd = 0;

         m_timeCaretPeriod = 1_s;

         defer_create_synchronization();

      }


      data::~data()
      {

         if (synchronization() == m_pedit->synchronization())
         {

            set_synchronization(nullptr);

         }

      }


      void data::initialize_data(::data::data_container_base * pdocument)
      {

         //auto estatus =
         
         ::data::data::initialize_data(pdocument);

         //if (!estatus)
         //{

         //   return estatus;

         //}

         //estatus = 
         
         __construct_new(m_pformata);

         //if (!estatus)
         //{

         //   return estatus;

         //}

         m_pformatCurrent = add_format();

         //estatus = 
         
         __construct_new(m_plinea);

         //if (!estatus)
         //{

         //   return estatus;

         //}

         //return estatus;

      }


      ::pointer<format>data::add_format()
      {

         auto pformat = __create_new < format >();

         pformat->initialize_user_rich_text_format(m_pformata);

         m_pformata->add(pformat);

         return ::transfer(pformat);

      }

      ::pointer<span>data::create_span(::e_align ealignNewLine)
      {

         return __new(span(this, ealignNewLine));

      }


      ::pointer<span>data::add_span(const span & span)
      {

         synchronous_lock synchronouslock(this->synchronization());

         return __new(class span(this, span));

      }


      ::pointer<span>data::add_span(::e_align ealignNewLine)
      {

         synchronous_lock synchronouslock(this->synchronization());

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

         return minimum(maximum(minimum_non_negative(m_iSelBeg, m_iSelEnd), 0), _001GetTextLength());

      }


      strsize data::get_sel_end()
      {

         return minimum(maximum(maximum(m_iSelBeg, m_iSelEnd), 0), _001GetTextLength());

      }


      void data::on_selection_change(format * pformat)
      {

         synchronous_lock synchronouslock(this->synchronization());

         index iSelBeg = get_sel_beg();

         index iSelEnd = get_sel_end() - 1;

         get_selection_intersection_format(pformat, iSelBeg, iSelEnd);

      }


      void data::get_selection_intersection_format(format * pformat, index iSelBeg, index iSelEnd)
      {

         synchronous_lock synchronouslock(this->synchronization());

         update_span_cache(m_spana);

         index iSpanBeg = find_span(m_spana, iSelBeg);

         index iSpanEnd = find_span(m_spana, iSelEnd);

         if (iSpanBeg >= 0 && iSpanEnd >= iSpanBeg)
         {

            ::pointer<span>pspanBeg = m_spana[iSpanBeg];

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


      strsize data::hit_test(point_f64 point)
      {

         synchronous_lock synchronouslock(this->synchronization());

         //double xLast = 0.0;

         rectangle_f64 rBox;

         rBox.right() = -1024.0 * 1024.0 * 1024.0;
         rBox.bottom() = -1024.0 * 1024.0 * 1024.0;
         rBox.left() = 1024.0 * 1024.0 * 1024.0;
         rBox.top() = 1024.0 * 1024.0 * 1024.0;

         double yStart = -1024.0 * 1024.0 * 1024.0;

         double yLast = yStart - 1.0;

         strsize iLast = 0;

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

                  strsize iPos = pbox->m_iPosBeg;

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

            return m_pedit->_001GetTextLength();

         }

         if (point.y() < rBox.top())
         {

            return 0;

         }

         return iLast;

      }


      strsize data::hit_test_line_x(index iLine, double x)
      {

         synchronous_lock synchronouslock(this->synchronization());

         auto plinea = m_plinea;

         if (iLine < 0 || iLine >= plinea->get_count())
         {

            return -1;

         }

         auto & pline = plinea->element_at(iLine);

         for (index iBox = 0; iBox < plinea->get_count(); iBox++)
         {

            auto& pbox = pline->element_at(iBox);

            if (x <= pbox->m_rectangleHitTest.left())
            {

               return pbox->m_iPosBeg;

            }
            else if (iBox >= pline->get_upper_bound() && x > pbox->m_rectangleHitTest.right())
            {

               return pbox->m_iPosEnd + 1;

            }
            else if (x <= pbox->m_rectangleHitTest.right())
            {

               double xLeft = pbox->m_rectangleBox.left();

               double xLast = pbox->m_rectangleHitTest.left();

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

         synchronous_lock synchronouslock(this->synchronization());

         str = text(m_spana);

      }


      void data::_001GetLayoutText(string & str) const
      {

         synchronous_lock synchronouslock(this->synchronization());

         str = layout_text(*m_plinea);

      }


      index data::SelToLine(strsize iSel) const
      {

         return sel_line(*m_plinea, iSel);

      }


      index data::LineColumnToSel(index iLine, strsize iColumn) const
      {

         synchronous_lock synchronouslock(this->synchronization());

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

         return minimum(plinea->element_at(iLine)->first()->m_iPosBeg + iColumn, iMax);

      }


      void data::_001Delete(strsize i1, strsize i2)
      {

         strsize iSelBeg = minimum_non_negative(i1, i2);

         strsize iSelEnd = maximum(i1, i2);

         if (iSelBeg == iSelEnd)
         {

            return;

         }

         synchronous_lock synchronouslock(this->synchronization());

         update_span_cache(m_spana);

         index iSpanBeg = find_span(m_spana, iSelBeg);

         index iSpanEnd = find_span(m_spana, iSelEnd - 1);

         if (iSpanBeg >= 0 && iSpanEnd >= iSpanBeg)
         {

            ::pointer<span>pspanBeg = m_spana[iSpanBeg];

            ::pointer<span>pspanEnd = m_spana[iSpanEnd];

            if (iSpanBeg == iSpanEnd)
            {

               ::pointer<span>pspanNext;

               if (iSpanEnd + 1 < m_spana.get_count())
               {

                  pspanNext = m_spana[iSpanEnd + 1];

               }

               if (iSelBeg == pspanBeg->m_iPosEnd && pspanNext.is_set() && pspanNext->is_new_line())
               {

                  if (pspanBeg->m_pformat == pspanNext->m_pformat)
                  {

                     pspanBeg->m_str += pspanNext->m_str;

                     m_spana.erase_at(iSpanEnd + 1);

                     return;

                  }
                  else
                  {

                     pspanNext->m_ealignNewLine = e_align_none;

                  }

               }

               pspanBeg->m_str = pspanBeg->m_str.left(iSelBeg - pspanBeg->m_iPosBeg) + pspanBeg->m_str.substr(iSelEnd - pspanBeg->m_iPosBeg);

               if (pspanBeg->m_str.is_empty())
               {

                  m_spana.erase_at(iSpanBeg);

               }

               return;

            }

            index iEndBeg = pspanEnd->m_iPosBeg;

            index iEndEnd = pspanEnd->m_iPosEnd;

            if (iSelBeg > pspanBeg->m_iPosBeg)
            {

               pspanBeg->m_str = pspanBeg->m_str.left(iSelBeg - pspanBeg->m_iPosBeg);

               pspanBeg->m_iPosEnd = (int) iSelBeg;

               iSpanBeg++;

            }

            if (iSelEnd <= iEndEnd)
            {

               pspanEnd->m_str = pspanEnd->m_str.substr(iSelEnd - iEndBeg);

               pspanEnd->m_iPosBeg = (int) iSelEnd;

               iSpanEnd--;

            }

            int iCount = (int) (iSpanEnd - iSpanBeg + 1);

            if (iCount > 0)
            {

               m_spana.erase_at(iSpanBeg, iCount);

            }

         }

         optimize_data();

      }


      string data::get_full_text()
      {

         synchronous_lock synchronouslock(this->synchronization());

         update_span_cache(m_spana);

         return text(m_spana);

      }


      void data::_001InsertText(const ::string & psz, format * pformatParam)
      {

         string_array straLines;

         straLines.add_lines(psz);

         synchronous_lock synchronouslock(this->synchronization());

         index iSelBeg = get_sel_beg();

         index iSelEnd = get_sel_end();

         _001Delete(iSelBeg, iSelEnd);

         index iSelChar = iSelBeg;

         index iSpan = find_span(m_spana, iSelChar);

         ::pointer<format>pformat;

         ::pointer<span>pspan;

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

                  pspan->m_str = pspan->m_str.left(iMid) + strLine + pspan->m_str.substr(iMid);

               }
               else
               {

                  {

                     auto pspanLast = create_span(ealignNewLine);

                     pspanLast->m_str = straLines.last() + pspan->m_str.substr(iMid);

                     pspanLast->m_ealignNewLine = pspan->get_align();

                     pspanLast->m_pformat = pspan->m_pformat;

                     m_spana.insert_at(iSpan, pspanLast);

                  }

                  pspan->m_str = pspan->m_str.left(iMid) + strLine;

               }

            }

            iSelChar += straLines[iLine].length();

            if (iLine < straLines.get_upper_bound())
            {

               iSelChar++;

            }

            iSpan++;

         }

         m_iSelBeg = m_iSelEnd = iSelChar;

         update_span_cache(m_spana);

         m_pedit->on_after_change(::id_after_change_text);

      }



      void data::_001SetSelFontFormat(const format * pformat, const e_attribute & eattribute)
      {

         synchronous_lock synchronouslock(this->synchronization());

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

                  pspanBeg->m_str = str.left(iSelBeg - pspanBeg->m_iPosBeg);

                  auto pspan2 = pspanBeg->fork(pformat, eattribute);
                  pspan2->m_str = str.substr(iSelBeg - pspanBeg->m_iPosBeg, iSelEnd - iSelBeg + 1);
                  m_spana.insert_at(iBeg + 1, pspan2);

                  if (iSelEnd < pspanBeg->m_iPosEnd)
                  {

                     auto pspan3 = pspanBeg->fork();
                     pspan3->m_str = str.substr(iSelEnd - pspanBeg->m_iPosBeg + 1);
                     m_spana.insert_at(iBeg + 2, pspan3);

                  }

               }
               else
               {

                  if (iSelEnd + 1 < pspanBeg->m_iPosEnd)
                  {

                     str = pspanBeg->m_str;

                     auto pspan2 = pspanBeg->fork();
                     pspan2->m_str = str.substr(iSelEnd - pspanBeg->m_iPosBeg + 1);
                     m_spana.insert_at(iBeg + 1, pspan2);

                     pspanBeg->m_str = str.left(iSelEnd - pspanBeg->m_iPosBeg + 1);

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

                  pspanBeg->m_str = str.left(iSelBeg - pspanBeg->m_iPosBeg);

                  auto pspan2 = pspanBeg->fork(pformat, eattribute);
                  pspan2->m_str = str.substr(iSelBeg - pspanBeg->m_iPosBeg);
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
                  pspan3->m_str = str.left(iSelEnd - iEndBeg + 1);

                  m_spana.insert_at(iEnd, pspan3);

                  pspanEnd->m_str = str.substr(iSelEnd - iEndBeg + 1);

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

         m_pedit->on_after_change(::id_after_change_text_format);

      }

      // unicode_next(str.c_str()) - str.c_str(); // at least one char is the longest pline

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

         auto u = strWord.length();

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

         strSlice = strWord.left(m);

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

      //   synchronous_lock synchronouslock(this->synchronization());

      //   if (m_pgraphics.is_null())
      //   {

      //      m_pgraphics.create(this);

      //      m_pgraphics->CreateCompatibleDC(nullptr);

      //   }

      //   ::draw2d::save_context savecontext(m_pgraphics);

      //   do_layout(m_pgraphics);

      //}


      void data::do_layout(::draw2d::graphics_pointer & pgraphics)
      {

         //m_rectangle = rectangle;

         synchronous_lock synchronouslock(this->synchronization());

         pgraphics->set_text_rendering_hint(::write_text::e_rendering_anti_alias);

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

         //bool bLineWrap = false;

         auto rectangle = get_drawing_rect();

         rectangle_f64 rectangleX(rectangle);

         int x = (int) rectangle.left();

         //int xLast = x;

         //bool bFirstParagraph = true;

         auto plinea = __new(pointer_array < line >);

         ::pointer<line>pline;

         //strsize iCharLayout = 0;

   //if (m_spana.first().m_pformat >= m_pformata.get_count())
   //{

   //   m_pformata.add(__new(format(this)));

   //}

         //if (m_spana.is_empty())
         //{

         //   add_span(e_align_left);

         //   m_spana.first_pointer()->m_iFormat = 0;

         //   if (m_spana.first_pointer()->m_iFormat >= m_pformata.get_count())
         //   {

         //      m_pformata.add(__new(format(this)));

         //   }

         //}
         //else if (!m_spana[0]->is_new_line())
         //{

         //   m_spana[0]->m_ealignNewLine = e_align_left;

         //}

         // horizontal span

         ::e_align ealign = e_align_center;

         pointer_array < span > spana;

         //strsize iSpanCharEnd = 0;

         index iSpan = 0;

         ::count cWords = 0;

         //index iSpanNextWord;
         string strSlice;

         string_array straWords;

         double dPosition;

         ::pointer<box>pbox;

         //bool bMultiWordFormat = true;

         //pointer_array < span > spanaMultiWordFormat;

//         int iHeight;

         while (iSpan < m_spana.get_count())
         {

            ::pointer<span>pspan = m_spana[iSpan];

            pspan->m_str.find_replace("\n", "");

            pspan->m_str.find_replace("\r", "");

            auto pformat = pspan->format();

            pgraphics->set(pformat->get_font(pgraphics));

            {

               auto iLenSpan = pspan->m_str.length();

               auto iLenMeasure = pgraphics->get_character_extent(pspan->m_daPositionLeft, pspan->m_daPositionRight, pspan->m_str);

               if(iLenSpan != iLenMeasure)
               {

                  ASSERT(false);

                  information("unexpected: iLenSpan != iLenMeasure");

               }

            }

            pspan->m_sizeSpan = pgraphics->get_text_extent(pspan->m_str);

            strsize iSpanChar = 0;

            double dPositionLeft = 0.;

         restart_span:

            strSlice.empty();

            //if (spanaMultiWordFormat.is_empty() &&
            if((pspan->is_new_line() || iSpanChar > 0))
            {

               if (pline.is_set())
               {

                  ASSERT(pline->has_element());

                  plinea->add(pline);

               }

               pline = __new(line);

               x = (int) rectangle.left();

               //xLast = x;

               //bLineWrap = false;

               ealign = pspan->m_ealignNewLine;

               x = (int) rectangle.left();

               //pbox = __new(box(pspan));

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

               goto new_span;

            }

            straWords.erase_all();

            words_trailing_spaces(straWords, strTopic);

            if (straWords.get_count() <= 0)
            {

               goto new_span;

            }

            strSlice.empty();

            cWords = (int) longest_pline(strSlice, dPosition, straWords, &pspan->m_daPositionRight[iSpanChar], dPositionLeft, (int) rectangleX.right() - x);

            if (ansi_char_isspace(straWords.last().last_char())
               || (iSpan + 1 < m_spana.get_count()
                  && (m_spana[iSpan + 1]->is_new_line()
                     || (m_spana[iSpan + 1]->m_str.has_char()
                        && ansi_char_isspace(m_spana[iSpan + 1]->m_str[0]))))
               || cWords < straWords.get_count())
            {

               if (cWords > 0)
               {

                  auto pbox = __new(box(pspan));

                  pbox->m_iPosBeg = pspan->m_iPosBeg + iSpanChar;

                  iSpanChar += strSlice.get_upper_bound();

                  pbox->m_iPosEnd = pspan->m_iPosBeg + iSpanChar;

                  // keeping dimensions
                  pbox->m_sizeBox.cy() = pspan->m_sizeSpan.cy();

                  pbox->m_sizeBox.cx() = dPosition - dPositionLeft;

                  // just horizonal layout
                  pbox->m_rectangleBox.set_dimension(x, 0, pbox->m_sizeBox.cx(), 0);

                  pbox->m_rectangleHitTest = pbox->m_rectangleBox;

                  pline->add(pbox);

                  x += (int) pbox->m_sizeBox.cx();

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

               strSlice.empty();

               longest_word(strSlice, dPosition, strWord, &pspan->m_daPositionRight[iSpanChar], dPositionLeft, (int) rectangleX.right() - x);

               auto pbox = __new(box(pspan));

               pbox->m_iPosBeg = pspan->m_iPosBeg + iSpanChar;

               iSpanChar += strSlice.get_upper_bound();

               pbox->m_iPosEnd = pspan->m_iPosBeg + iSpanChar;

               // keeping dimensions
               pbox->m_sizeBox.cy() = pspan->m_sizeSpan.cy();

               pbox->m_sizeBox.cx() = dPosition - dPositionLeft;

               // just horizonal layout
               pbox->m_rectangleBox.set_dimension(x, 0, pbox->m_sizeBox.cx(), 0);

               pbox->m_rectangleHitTest = pbox->m_rectangleBox;

               pline->add(pbox);

               x += (int) pbox->m_sizeBox.cx();

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
               pbox->m_sizeBox.cy() = pspan->m_sizeSpan.cy();

               pbox->m_sizeBox.cx() = dPosition;

               // just horizonal layout
               pbox->m_rectangleBox.set_dimension(x, 0, pbox->m_sizeBox.cx(), 0);

               pbox->m_rectangleHitTest = pbox->m_rectangleBox;

               pline->add(pbox);

               x += (int)  pbox->m_sizeBox.cx();

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

         for (auto& pline : *plinea)
         {

            align(pline, rectangleX);

         }

         m_plinea = plinea;

      }


      ::rectangle_f64 data::get_drawing_rect()
      {

         ::rectangle_f64 rectangle;

         if (m_pedit->is_picture_enabled())
         {

            rectangle = m_pedit->m_ppictureimpl->m_rectangleDrawing;

            rectangle -= rectangle.origin();

         }
         else
         {

            rectangle = m_pedit->rectangle();

         }

         return rectangle;

      }


      void data::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
      {

         synchronous_lock synchronouslock(this->synchronization());

         if (pgraphics->m_bPrinting)
         {

            pgraphics->set_text_rendering_hint(::write_text::e_rendering_anti_alias);

         }
         else
         {

            pgraphics->set_text_rendering_hint(::write_text::e_rendering_anti_alias);

         }

         //rectangle_f64 rectangleX(rectangle);

         auto rectangle = get_drawing_rect();

         //pgraphics->draw_inset_3d_rectangle(rectangle, argb(255, 0, 127, 0));

         bool bHasFocus = false;

         if (m_pedit->has_keyboard_focus())
         {

            bHasFocus = true;

         }

         bool bCaretOn = false;

         if (bHasFocus && m_pedit->is_text_editable())
         {

            bCaretOn = m_pedit->m_timeFocusStart.on_off(m_timeCaretPeriod);

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

            int y = (int)  rectangle.top();


            int nexty;

            // vertical span

            for (auto& pline : *plinea)
            {

               int iMaxCy = 0;

               for (auto& pbox : *pline)
               {

                  iMaxCy = maximum(iMaxCy, (int) pbox->m_sizeBox.cy());

                  pbox->m_rectangleBox.top() = y;

                  pbox->m_rectangleHitTest.top() = y;

               }

               nexty = y + iMaxCy;

               for (auto& pbox : *pline)
               {

                  pbox->m_rectangleBox.bottom() = nexty;

                  pbox->m_rectangleHitTest.bottom() = nexty;

                  //pbox->m_rectangleBox.right() += 2;

               }

               y = nexty;

            }

            // Draw Select Rectangle

            ::color::color crBkSel;

            if (bHasFocus && m_pedit->is_text_editable())
            {

               crBkSel = argb(192, 175, 200, 240);

            }
            else
            {

               crBkSel = argb(127, 192, 210, 225);

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

                        iBoxPosBeg = maximum(iBoxPosBeg, get_sel_beg());

                        iBoxPosEnd = minimum(iBoxPosEnd, get_sel_end());

                        index iBeg = pline->predicate_find_first([&](auto & pbox)
                        {

                           return pbox->m_iPosBeg <= iBoxPosBeg && iBoxPosBeg <= pbox->m_iPosEnd;

                        });

                        if (iBeg >= 0)
                        {

                           pboxBeg = pline->element_at(iBeg);

                           index iEnd = pline->predicate_find_first([&](auto & pbox)
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
                              else
                              {

                                 l = pboxBeg->get_pos_left(iBoxPosBeg);

                              }

                              double r;

                              if (iBoxPosEnd == pboxEnd->m_iPosBeg)
                              {

                                 r = pboxEnd->m_rectangleBox.left();

                              }
                              else if (iBoxPosEnd >= pboxEnd->m_iPosEnd + 1)
                              {

                                 r = pboxEnd->m_rectangleBox.right();

                              }
                              else
                              {

                                 r = pboxEnd->get_pos_left(iBoxPosEnd);
                              }

                              pgraphics->fill_rectangle(
                                 ::rectangle_f64_dimension(l,
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

            ::draw2d::fastblur blurDropShadow;

            ::image_pointer imageDropShadow;

            ::rectangle_i32 rDropShadow;

            if (m_pedit->m_ppictureimpl != nullptr)
            {

               rDropShadow = m_pedit->m_ppictureimpl->m_rectangleDrawing;

               rDropShadow.offset(-rDropShadow.center());

            }

            if (m_pedit->m_ppictureimpl != nullptr && m_pedit->m_ppictureimpl->m_bGlowDropShadow)
            {

               ::image_pointer pimage;

               pimage.create(this);

               pimage->create(m_pedit->m_ppictureimpl->m_rectangleDrawing.size());

               ::size_i32 sz = m_pedit->m_ppictureimpl->m_rectangleDrawing.size();

               pimage->g()->set_origin(sz.cx() / 2, sz.cy() / 2);

               ::draw2d::graphics_pointer pgraphicsImage = pimage->g();

               draw_text(pgraphicsImage, rectangle);

               pimage->g()->set_origin(0, 0);

               m_pedit->defer_draw_drop_shadow_phase1(rDropShadow, blurDropShadow, imageDropShadow, pimage);

               m_pedit->defer_draw_drop_shadow_phase2(pgraphics, rDropShadow, blurDropShadow, imageDropShadow);

            }

            draw_text(pgraphics, rectangle);

            // Draw Caret

            if (bCaretOn && m_pedit->is_text_editable())
            {

               ::pointer<box>pbox = find_box(*plinea, m_iSelEnd);

               if (pbox)
               {

                  double r;

                  r = pbox->get_pos(m_iSelEnd);

                  //r += rectangle.left();

                  if (r > rectangle.left())
                  {

                     r -= 1.0;

                  }

                  if (r < rectangle.left() + 2)
                  {

                     r = rectangle.left() + 2;

                  }

                  if (r > rectangle.right() - 2)
                  {

                     r = rectangle.right() - 2;

                  }

                  auto dDescent = pbox->m_pspan->m_pformat->m_pfont->get_descent(pgraphics);

                  pgraphics->fill_rectangle(::rectangle_f64(r,
                     pbox->m_rectangleBox.top() + 1,
                     r + 0.5,
                     pbox->m_rectangleBox.bottom() - dDescent),
                     argb(255, 0, 0, 0));

               }

            }

            ::geometry2d::matrix m;

            m.scaling(pgraphics->get_scaling());

            //m.invert();

            for (auto& pline : *plinea)
            {

               for (auto& pbox : *pline)
               {

                  pbox->m_rectangleDevice = pbox->m_rectangleBox;

                  m.transform(pbox->m_rectangleHitTest.top_left());
                  m.transform(pbox->m_rectangleHitTest.bottom_right());

                  m.transform(pbox->m_rectangleDevice.top_left());
                  m.transform(pbox->m_rectangleDevice.bottom_right());

               }

            }


         for (auto& pspan : m_spana)
         {

            pspan->m_daPositionDeviceLeft.erase_all();
            pspan->m_daPositionDeviceRight.erase_all();

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

         synchronous_lock synchronouslock(this->synchronization());

         m_pformata->erase_all();

         for (index i = 0; i < m_spana.get_count(); i++)
         {

            //m_spana[i]->m_pformat = this;

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

                  m_spana.erase_at(i);

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

         synchronous_lock synchronouslock(this->synchronization());

         if (m_spana.is_empty())
         {

            return 0;

         }

         return m_spana.last()->m_iPosEnd;

      }


      strsize data::_001GetLayoutTextLength() const
      {

         synchronous_lock synchronouslock(this->synchronization());

         auto plinea = m_plinea;

         if (plinea->is_empty())
         {

            return 0;

         }

         return plinea->last()->last()->m_iPosEnd + 1;

      }


      void data::internal_update_sel_char()
      {

         synchronous_lock synchronouslock(this->synchronization());

         //m_iSelBeg = sel_char(*plinea, m_iSelBeg3, m_ebiasBeg);

         //m_iSelEnd = sel_char(*plinea, m_iSelEnd3, m_ebiasEnd);

         //bool bNeedRedraw = false;

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

            //bNeedRedraw = true;

         }

         if (iSelEnd != m_iSelEnd)
         {

            m_iSelEnd = iSelEnd;

            //bNeedRedraw = true;

         }

         m_pedit->set_need_redraw();

      }


      void data::__initialize(::pointer<::user::rich_text::format>& pformat)
      {

         __defer_construct(pformat);

         //auto estatus = 
         
         pformat->initialize_user_rich_text_format(m_pformata);

         //if (!estatus)
         //{

         //   return estatus;

         //}

         //return estatus;

      }


      //void data::write(::binary_stream & stream) const
      //{

      //   synchronous_lock synchronouslock(this->synchronization());

      //   stream << m_pformata;

      //   stream << m_spana;

      //}


      //void data::read(::binary_stream & stream)
      //{

      //   synchronous_lock synchronouslock(this->synchronization());

      //   m_plinea->erase_all();

      //   m_pformata->erase_all();

      //   m_spana.erase_all();

      //   stream >> m_pformata;

      //   stream >> m_spana;

      //}


      void data::draw_text(::draw2d::graphics_pointer & pgraphics, const ::rectangle_f64 & rectangleBox)
      {

         synchronous_lock synchronouslock(pgraphics->synchronization());

         synchronous_lock sl1(synchronization());

         //synchronous_lock sl2(m_plinea->synchronization());

         //synchronous_lock sl3(m_pformata->synchronization());

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

               //   pformat = __new(format(this));

               //}

               ::rectangle_i32 rectangle = pbox->m_rectangleBox;


               if (pformat->m_escript == e_script_subscript)
               {

                  rectangle.offset(0, rectangle.height() / 6);

               }
               else if (pformat->m_escript == e_script_superscript)
               {

                  rectangle.offset(0, -rectangle.height() / 3);

               }

               if (m_pedit->m_ppictureimpl != nullptr && m_pedit->m_ppictureimpl->m_bOutline)
               {

                  auto ppath = __create < ::draw2d::path > ();

                  //ppath->add_draw_text(pbox->get_text(), rectangle, e_align_bottom_left | DT_SINGLELINE, pformat->get_font(pgraphics), pformat->m_colorForeground);
                  ppath->add_draw_text(pbox->get_text(), rectangle, e_align_bottom_left, e_draw_text_single_line, pformat->get_font(pgraphics));

                  auto ppen = __create < ::draw2d::pen > ();

                  auto pbrush = __create < ::draw2d::brush >();

                  ppen->create_solid(m_pedit->m_ppictureimpl->m_iOutlineWidth, ::color::color(m_pedit->m_ppictureimpl->m_hlsOutline));

                  pbrush->create_solid(pformat->m_colorForeground);

                  pgraphics->set(ppen);

                  pgraphics->set(pbrush);

                  pgraphics->path(ppath);

               }
               else
               {

                  pgraphics->set(pformat->get_font(pgraphics));

                  pgraphics->set_text_color(pformat->m_colorForeground);

                  string strText = pbox->get_text();

                  pgraphics->draw_text(strText, rectangle, e_align_bottom_left, e_draw_text_single_line);

               }

            }

         }

      }


   } // namespace rich_text


} // namespace user



