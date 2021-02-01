#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "core/user/rich_text/_rich_text.h"
#endif


namespace user
{


   namespace rich_text
   {


      bool is_equal_bool(bool b1, bool b2)
      {

         return (b1 && b2) || (!b1 && !b2);

      }


      bool is_similar_font_size(double d1, double d2)
      {

         return fabs(d2 - d1) < 0.25;

      }


      // return words with trailing spaces
      void words_trailing_spaces(string_array & stra, string str)
      {

         strsize iFind = 0;

         strsize iFind2;

         strsize iFind3;

         while (true)
         {

            iFind2 = str.find_first_in(" \t\r\n", iFind);

            if (iFind2 < 0)
            {

               stra.add(str.Mid(iFind));

               return;

            }

            iFind3 = str.find_first_not_in(" \t\r\n", iFind2);

            if (iFind3 < 0)
            {

               stra.add(str.Mid(iFind));

               return;

            }

            string strWord = str.Mid(iFind, iFind3 - iFind);

            stra.add(strWord);

            iFind = iFind3;

         }

      }


      index sel_line(const __pointer_array(line) & linea, index iSel)
      {

         if (iSel < 0)
         {

            return -1;

         }

         box * pboxLast = nullptr;

         index iLine = 0;

         for (; iLine < linea.get_count(); iLine++)
         {

            auto & pline = linea[iLine];

            for (auto & pbox : pline->ptra())
            {

               pboxLast = pbox;

               if (pbox->m_iPosBeg <= iSel && iSel <= pbox->m_iPosEnd)
               {

                  return iLine;

               }

            }

         }

         return linea.get_upper_bound();

      }


      index sel_line_x666(__pointer_array(line) & linea, index iSel, double & x)
      {

         if (iSel < 0)
         {

            return -1;

         }

         box * pboxLast = nullptr;

         index iLine = 0;

         for (; iLine < linea.get_count(); iLine++)
         {

            auto & pline = linea[iLine];

            for (auto & pbox : pline->ptra())
            {

               pboxLast = pbox;

               if (pbox->m_iPosBeg <= iSel && iSel <= pbox->m_iPosEnd)
               {

                  strsize iPos = iSel;

                  int xLeft;
                  int xRight;

                  if (iPos - 1 <= pbox->m_iPosBeg)
                  {

                     xLeft = (::i32)pbox->m_rectBox.left;

                  }
                  else if((iPos - 1) >= pbox->m_iPosEnd)
                  {

                     xLeft = (::i32)pbox->get_last_pos();

                  }
                  else
                  {

                     xLeft = (::i32)pbox->get_pos(iPos - 1);

                  }

                  if (iPos <= pbox->m_iPosBeg)
                  {

                     xRight = (::i32)pbox->m_rectBox.left;

                  }
                  else if (iPos >= pbox->m_iPosEnd)
                  {

                     xRight = (::i32)pbox->get_last_pos();

                  }
                  else
                  {

                     xRight = (::i32)pbox->get_pos(iPos);

                  }

                  x = (xRight + xLeft) / 2;

                  return iLine;

               }

            }

         }

         return linea.get_upper_bound();

      }


      index line_caret_x(__pointer_array(line)& linea, index iSel, double& x)
      {

         if (iSel < 0)
         {

            return -1;

         }

         box* pboxLast = nullptr;

         index iLine = 0;

         for (; iLine < linea.get_count(); iLine++)
         {

            auto& pline = linea[iLine];

            for (auto& pbox : pline->ptra())
            {

               pboxLast = pbox;

               if (pbox->m_iPosBeg <= iSel && iSel <= (pbox->m_iPosEnd + (pbox == pline->last_ptr() ? 1 : 0)))
               {

                  strsize iPos = iSel;

                  int xLeft;
                  //int xRight;

                  if (iPos - 1 <= pbox->m_iPosBeg)
                  {

                     xLeft = (::i32)pbox->m_rectBox.left;

                  }
                  else if ((iPos - 1) >= pbox->m_iPosEnd)
                  {

                     xLeft = (::i32)pbox->get_last_pos();

                  }
                  else
                  {

                     xLeft = (::i32)pbox->get_pos(iPos);

                  }

                  x = xLeft - 0.75;

                  return iLine;

               }

            }

         }

         return linea.get_upper_bound();

      }


      index sel_char(__pointer_array(line) & linea, index iSel)
      {

         if (iSel < 0 || linea.is_empty() || linea.first()->is_empty())
         {

            return -1;

         }

         for (auto & pline : linea.ptra())
         {

            for (auto & pbox : pline->ptra())
            {

               if (pbox->m_iPosBeg <= iSel && iSel <= pbox->m_iPosEnd)
               {

                  return min(pbox->m_iPosEnd + 1, iSel - pbox->m_iPosBeg + pbox->m_iPosBeg);

               }

            }

         }

         return linea.last()->last()->m_iPosEnd + 1;

      }




      string line_text(line & line)
      {

         string str;

         for (auto & pbox : line.ptra())
         {

            str += pbox->get_text();

         }

         return str;

      }

      string text(const __pointer_array(span) & spana)
      {

         string str;

         bool bFirstBox = true;

         for (auto & pspan : spana.ptra())
         {

            if (pspan->m_ealignNewLine != e_align_none)
            {

               if (!bFirstBox)
               {

                  str += "\n";

               }

            }

            str += pspan->m_str;

            bFirstBox = false;

         }

         return str;

      }


      void update_span_cache(__pointer_array(span) & spana)
      {

         int iPos = 0;

         __pointer(span) pspanNext;

         for (index i = 0; i < spana.get_count(); i++)
         {

            __pointer(span) & pspan = spana[i];

            if (i > 0)
            {
               
               if (pspan->m_ealignNewLine != e_align_none)
               {

                  iPos++;

               }

            }

            pspan->m_iPosBeg = iPos;

            iPos += (::i32) pspan->m_str.get_length();

            pspan->m_iPosEnd = iPos;

         }

      }


      void update_span_cache(__pointer_array(span) & spana, __pointer_array(line) & linea)
      {

         update_span_cache(spana);

      }


      ::e_align box_align(__pointer_array(span) & spana, index iBox)
      {

         while (true)
         {

            if (iBox > spana.get_count())
            {

               iBox = spana.get_upper_bound();

            }

            if (iBox < 0)
            {

               return e_align_left;

            }

            if (spana[iBox]->m_ealignNewLine != e_align_none)
            {

               return spana[iBox]->m_ealignNewLine;

            }

            iBox--;

         }


      }


      bool box_align(__pointer_array(span) & spana, index iBox, ::e_align ealign)
      {

         if (iBox > spana.get_count())
         {

            iBox = spana.get_upper_bound();

         }

         while (true)
         {

            if (iBox < 0)
            {

               return false;

            }

            if (spana[iBox]->m_ealignNewLine != e_align_none)
            {

               spana[iBox]->m_ealignNewLine = ealign;

               return true;

            }

            iBox--;

         }

      }


      index find_span(__pointer_array(span) & spana, index iSel)
      {

         string str;

         for (index i = 0; i < spana.get_count(); i++)
         {

            __pointer(span) & pspan = spana[i];

            if (iSel <= pspan->m_iPosEnd)
            {

               return i;

            }

         }

         return spana.get_upper_bound();

      }


      index find_char_span(__pointer_array(span) & spana, strsize iChar)
      {

         if (iChar < 0)
         {

            return -1;

         }

         string str;

         for (index i = 0; i < spana.get_count(); i++)
         {

            __pointer(span) & pspan = spana[i];

            if (iChar >= pspan->m_iPosBeg && iChar <= pspan->m_iPosEnd)
            {

               return i;

            }

         }

         return spana.get_upper_bound();

      }


      void align(line * pline, const ::rectangle_f64 & rectangle)
      {

         if (pline->is_empty())
         {

            return;

         }

         auto ealign = pline->first_ptr()->m_pspan->m_ealignNewLine;

         // pline->last().m_str += "\n";

         if (ealign == e_align_left)
         {

            // Nothing to do:
            // "line" is already left aligned;

            pline->m_xOffset = 0.;

         }
         else
         {

            int iWidth = (::i32)pline->last()->m_rectBox.right;

            int iOffset = (::i32)(rectangle.right - iWidth);

            if (ealign == e_align_center)
            {

               iOffset /= 2;

            }

            pline->m_xOffset = iOffset;

            for (auto & pbox : pline->ptra())
            {

               pbox->m_rectBox.offset(iOffset, 0);

               pbox->m_rectHitTest.offset(iOffset, 0);

               // xxx
               //for (auto & d : pbox->m_daPosition)
               //{

               //   d += (double)iOffset;

               //}

            }


         }


      }


      box * find_box(__pointer_array(line) & linea, index iSel)
      {

         if (iSel < 0 || linea.isEmpty() || linea.first()->isEmpty())
         {

            return nullptr;

         }

         box * pboxLast = nullptr;

         for (auto & pline : linea.ptra())
         {

            for (auto & pbox : pline->ptra())
            {

               pboxLast = pbox;

               if (pbox->m_iPosBeg <= iSel && iSel <= (pbox->m_iPosEnd + (pbox->is_line_end() ? 1 : 0)))
               {

                  return pbox;

               }

            }

         }

         return pboxLast;

      }


      string layout_text(const __pointer_array(line) & linea)
      {

         string str;

         index iLine = 0;

         __pointer(line) plineLast = nullptr;

         for (; iLine < linea.get_count(); iLine++)
         {

            auto & pline = linea[iLine];

            if (plineLast.is_set() && plineLast->first()->m_pspan != pline->first()->m_pspan)
            {

               str += "\n";

            }

            for (auto & pbox : pline->ptra())
            {

               str += pbox->get_text();

            }

         }

         return str;

      }



      //__pointer(format) find_existing_format(__pointer_array(format) & formata, format * pformat)
      //{

      //   index iFind = spana.pred_find_first([&](auto & pitem)
      //   {

      //      return *pitem->m_pformat == *pformat;

      //   });

      //   if (iFind < 0)
      //   {

      //      return nullptr;

      //   }

      //   return spana.element_at(iFind)->m_pformat;

      //}


      //__pointer(format) get_format(__pointer_array(format) & formata, format * pformat)
      //{

      //   auto pformatExisting = formata.find_existing(pformat);

      //   if (pformatExisting->is_set())
      //   {

      //      return pformatExisting;

      //   }

      //   returreturn pformat;

      //}




   } // namespace rich_text


} // namespace user



