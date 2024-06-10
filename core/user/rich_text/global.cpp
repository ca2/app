#include "framework.h"
#include "line.h"
#include "box.h"
//#include "core/user/rich_text/_rich_text.h"


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

            iFind2 = str.find_first_character_in_index(" \t\r\n", iFind);

            if (iFind2 < 0)
            {

               auto strRemainingWord = str(iFind);

               if (strRemainingWord.has_char())
               {

                  stra.add(strRemainingWord);

               }

               return;

            }

            iFind3 = str.skip_any_character_in_index(" \t\r\n", iFind2);

            if (::not_found(iFind3))
            {

               stra.add(str(iFind));

               return;

            }

            string strWord = str(iFind, iFind3 - iFind);

            stra.add(strWord);

            iFind = iFind3;

         }

      }


      ::collection::index sel_line(const pointer_array < line > & linea, ::collection::index iSel)
      {

         if (iSel < 0)
         {

            return -1;

         }

         //box * pboxLast = nullptr;

         ::collection::index iLine = 0;

         for (; iLine < linea.get_count(); iLine++)
         {

            auto & pline = linea[iLine];

            for (auto & pbox : *pline)
            {

               //pboxLast = pbox;

               if (pbox->m_iPosBeg <= iSel && iSel <= pbox->m_iPosEnd)
               {

                  return iLine;

               }

            }

         }

         return linea.get_upper_bound();

      }


      ::collection::index sel_line_x666(pointer_array < line > & linea, ::collection::index iSel, double & x)
      {

         if (iSel < 0)
         {

            return -1;

         }

         //box * pboxLast = nullptr;

         ::collection::index iLine = 0;

         for (; iLine < linea.get_count(); iLine++)
         {

            auto & pline = linea[iLine];

            for (auto & pbox : *pline)
            {

               ///pboxLast = pbox;

               if (pbox->m_iPosBeg <= iSel && iSel <= pbox->m_iPosEnd)
               {

                  strsize iPos = iSel;

                  int xLeft;
                  int xRight;

                  if (iPos - 1 <= pbox->m_iPosBeg)
                  {

                     xLeft = (::i32)pbox->m_rectangleBox.left();

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

                     xRight = (::i32)pbox->m_rectangleBox.left();

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


      ::collection::index line_caret_x(pointer_array < line >& linea, ::collection::index iSel, double& x)
      {

         if (iSel < 0)
         {

            return -1;

         }

         //box* pboxLast = nullptr;

         ::collection::index iLine = 0;

         for (; iLine < linea.get_count(); iLine++)
         {

            auto& pline = linea[iLine];

            for (auto& pbox : *pline)
            {

               //pboxLast = pbox;

               //if (pbox->m_iPosBeg <= iSel && iSel <= (pbox->m_iPosEnd + (pbox == pline->last_ptr() ? 1 : 0)))
               if (pbox->m_iPosBeg <= iSel && iSel <= pbox->m_iPosEnd)
               {

                  strsize iPos = iSel;

                  int xLeft;
                  //int xRight;

                  if (iPos <= pbox->m_iPosBeg)
                  {

                     xLeft = (::i32)pbox->m_rectangleBox.left();

                  }
                  else if (iPos >= pbox->m_iPosEnd)
                  {

                     //xLeft = (::i32)pbox->get_last_pos();
                     xLeft = (::i32)pbox->m_rectangleBox.right();

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


//      index sel_char(pointer_array < line > & linea, ::collection::index iSel)
//      {
//
//         if (iSel < 0 || linea.is_empty() || linea.first()->is_empty())
//         {
//
//            return -1;
//
//         }
//
//         for (auto & pline : linea)
//         {
//
//            for (auto & pbox : *pline)
//            {
//
//               if (pbox->m_iPosBeg <= iSel && iSel <= pbox->m_iPosEnd)
//               {
//
//                  return minimum(pbox->m_iPosEnd, iSel - pbox->m_iPosBeg + pbox->m_iPosBeg);
//
//               }
//
//            }
//
//         }
//
//         return linea.last()->last()->m_iPosEnd + 1;
//
//      }




      string line_text(line & line)
      {

         string str;

         for (auto & pbox : line)
         {

            str += pbox->get_text();

         }

         return str;

      }


      ::string as_text(const pointer_array < span > & spana)
      {

         ::string str;

         for (auto & pspan : spana)
         {

            str += pspan->m_str;

            if (pspan->is_end_of_line())
            {

               str += "\n";

            }

         }

         return str;

      }


      void update_span_cache(pointer_array < span > & spana)
      {

         int iPos = 0;

         ::pointer<span>pspanNext;

         for (::collection::index i = 0; i < spana.get_count(); i++)
         {

            ::pointer<span>& pspan = spana[i];

            pspan->m_iPosBeg = iPos;

            iPos += (::i32) pspan->m_str.length();

            if (pspan->is_end_of_line())
            {

               iPos++;

            }

            pspan->m_iPosEnd = iPos;

         }

      }


      void update_span_cache(pointer_array < span > & spana, pointer_array < line > & linea)
      {

         update_span_cache(spana);

      }


      ::e_align box_align(pointer_array < span > & spana, ::collection::index iBox)
      {

         ::e_align ealign = e_align_left;

         if (iBox >= spana.get_count())
         {

            iBox = spana.get_upper_bound();

         }

         while (iBox >= 0)
         {

            if (spana[iBox]->is_start_of_line())
            {

               ealign = spana[iBox]->m_ealignNewLine;

               break;

            }

            iBox--;

         }

         return ealign;

      }


      bool box_align(pointer_array < span > & spana, ::collection::index iBox, ::e_align ealign)
      {

         if (iBox >= spana.get_count())
         {

            iBox = spana.get_upper_bound();

         }

         while (iBox >= 0)
         {

            if (spana[iBox]->is_start_of_line())
            {

               spana[iBox]->m_ealignNewLine = ealign;

               return true;

            }

            iBox--;

         }

         return false;

      }


      ::collection::index find_span(pointer_array < span > & spana, ::collection::index iSel)
      {

         string str;

         for (::collection::index i = 0; i < spana.get_count(); i++)
         {

            ::pointer<span>& pspan = spana[i];

            if (iSel < pspan->m_iPosEnd)
            {

               return i;

            }

         }

         return spana.get_upper_bound();

      }


      ::collection::index find_char_span(pointer_array < span > & spana, strsize iChar)
      {

         if (iChar < 0)
         {

            return -1;

         }

         string str;

         for (::collection::index i = 0; i < spana.get_count(); i++)
         {

            ::pointer<span>& pspan = spana[i];

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

            int iWidth = (::i32)pline->last()->m_rectangleBox.right();

            int iOffset = (::i32)(rectangle.right() - iWidth);

            if (ealign == e_align_center)
            {

               iOffset /= 2;

            }

            pline->m_xOffset = iOffset;

            for (auto & pbox : *pline)
            {

               pbox->m_rectangleBox.offset(iOffset, 0);

               pbox->m_rectangleHitTest.offset(iOffset, 0);

               // xxx
               //for (auto & d : pbox->m_daPosition)
               //{

               //   d += (double)iOffset;

               //}

            }

         }

      }


      box * find_box(pointer_array < line > & linea, ::collection::index iSel)
      {

         if (iSel < 0 || linea.is_empty())
         {

            return nullptr;

         }

         box * pboxLast = nullptr;

         for (auto & pline : linea)
         {

            for (auto & pbox : *pline)
            {

               pboxLast = pbox;

               //if (pbox->m_iPosBeg <= iSel && iSel <= (pbox->m_iPosEnd + (pbox->is_line_end() ? 1 : 0)))
               if (pbox->m_iPosBeg <= iSel && iSel <= pbox->m_iPosEnd)
               {

                  return pbox;

               }

            }

         }

         return pboxLast;

      }


      string layout_text(const pointer_array < line > & linea)
      {

         string str;

         ::collection::index iLine = 0;

         ::pointer<line>plineLast = nullptr;

         for (; iLine < linea.get_count(); iLine++)
         {

            auto & pline = linea[iLine];

//            if (plineLast.is_set() && plineLast->last()->m_pspan != pline->last()->m_pspan)
//            {
//
//            str += "\n";
//
//            }

            for (auto & pbox : *pline)
            {

               str += pbox->get_text();

            }

            str += "\n";

         }

         return str;

      }



      //::pointer<format>find_existing_format(pointer_array < format > & formata, format * pformat)
      //{

      //   auto pFind = spana.predicate_find_first([&](auto & pitem)
      //   {

      //      return *pitem->m_pformat == *pformat;

      //   });

      //   if (::is_null(pFind))
      //   {

      //      return nullptr;

      //   }

      //   return spana.element_at(iFind)->m_pformat;

      //}


      //::pointer<format>get_format(pointer_array < format > & formata, format * pformat)
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



