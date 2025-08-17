#include "framework.h"
#include "data.h"
#include "edit_impl.h"
#include "format.h"
#include "line.h"
#include "box.h"
#include "global.h"
#include "text_format.h"
#include "acme/constant/id.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "acme/parallelization/mutex.h"
#include "acme/platform/system.h"
#include "acme/prototype/data/listener.h"
#include "aura/graphics/draw2d/graphics.h"
#include "aura/graphics/write_text/font.h"
#include "aura/graphics/image/image.h"
#include "aura/graphics/draw2d/path.h"
#include "aura/graphics/draw2d/brush.h"
#include "acme/prototype/collection/_array_binary_stream.h"


namespace user
{


   namespace rich_text
   {

      void align(line * pline, const ::double_rectangle & rectangle);

      ::collection::count get_vars(strsize_array & ia1, strsize_array & ia2, const ::scoped_string & scopedstr)
      {

         character_count i1 = 0;

         character_count i2 = 0;

         while (true)
         {

            i1 = scopedstr.find_index('%', i1);

            if (i1 < 0)
            {

               break;

            }

            i2 = scopedstr.find_index('%', i1 + 1);

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

         defer_create_synchronization();

      }


      data::~data()
      {

      }


      //void data::initialize_data(::data::data_container_base * pdocument)
      void data::initialize_data()
      {

         //auto estatus =

//         ::data::data::initialize_data(pdocument);

         //if (!estatus)
         //{

         //   return estatus;

         //}

         //estatus = 

         //øconstruct_new(m_pformathost);

         //if (!estatus)
         //{

         //   return estatus;

         //}

         m_pformatCurrent = add_format();

         //estatus = 

         //if (!estatus)
         //{

         //   return estatus;

         //}

         //return estatus;

      }


      void data::destroy()
      {

         ::data::data::destroy();

         ::user::rich_text::format_host::destroy();

      }



      ::pointer<span>data::create_span()
      {

         return __allocate span(this);

      }


      ::pointer<span>data::add_span(const span & span)
      {

         synchronous_lock synchronouslock(this->synchronization());

         return __allocate class span (this, span);

      }


      ::pointer<span>data::add_span(::e_align ealignNewLine, bool bEndOfLine)
      {

         synchronous_lock synchronouslock(this->synchronization());

         auto pspan = create_span();

         if (pspan->m_pformat.is_null())
         {

            pspan->m_pformat = m_pformatCurrent;

         }

         pspan->m_ealignNewLine = ealignNewLine;

         pspan->m_bEndOfLine = bEndOfLine;

         m_spana.add(pspan);

         return pspan;

      }


      //::pointer<span>data::add_start_of_line_span(::e_align ealignNewLine)
      //{

      //   return __add_span(ealignNewLine, false);

      //}


      //::pointer<span>data::add_end_of_line_span(::e_align ealignEndOfLine)
      //{

      //   ASSERT(ealignEndOfLine != ::e_align_none);

      //   return __add_span2(ealignEndOfLine);

      //}




      void data::__update_text()
      {

         _synchronous_lock synchronouslock(this->synchronization());

         set_text(::user::rich_text::as_text(m_spana), ::e_source_sync);

      }





      void data::_001Delete(character_count i1, character_count i2)
      {

         character_count iSelBeg = minimum_non_negative(i1, i2);

         character_count iSelEnd = maximum(i1, i2);

         if (iSelBeg == iSelEnd)
         {

            return;

         }

         synchronous_lock synchronouslock(this->synchronization());

         update_span_cache(m_spana);

         ::collection::index iSpanBeg = find_span(m_spana, iSelBeg);

         ::collection::index iSpanEnd = find_span(m_spana, iSelEnd - 1);

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

               if (iSelBeg == pspanBeg->m_iPosEnd && pspanNext.is_set() && pspanBeg->is_end_of_line())
               {

                  if (pspanBeg->m_pformat == pspanNext->m_pformat)
                  {

                     pspanBeg->m_str += pspanNext->m_str;

                     m_spana.erase_at(iSpanEnd + 1);

                     pspanBeg->m_bEndOfLine = false;

                     return;

                  }
                  else
                  {

                     pspanBeg->m_bEndOfLine = false;

                  }

               }

               pspanBeg->m_str = pspanBeg->m_str.left(iSelBeg - pspanBeg->m_iPosBeg) + pspanBeg->m_str.substr(iSelEnd - pspanBeg->m_iPosBeg);

               if (pspanBeg->m_str.is_empty())
               {

                  m_spana.erase_at(iSpanBeg);

               }

               return;

            }

            ::collection::index iEndBeg = pspanEnd->m_iPosBeg;

            ::collection::index iEndEnd = pspanEnd->m_iPosEnd;

            if (iSelBeg > pspanBeg->m_iPosBeg)
            {

               pspanBeg->m_str = pspanBeg->m_str.left(iSelBeg - pspanBeg->m_iPosBeg);

               pspanBeg->m_iPosEnd = (int)iSelBeg;

               iSpanBeg++;

            }

            if (iSelEnd <= iEndEnd)
            {

               pspanEnd->m_str = pspanEnd->m_str.substr(iSelEnd - iEndBeg);

               pspanEnd->m_iPosBeg = (int)iSelEnd;

               iSpanEnd--;

            }

            int iCount = (int)(iSpanEnd - iSpanBeg + 1);

            if (iCount > 0)
            {

               m_spana.erase_at(iSpanBeg, iCount);

            }

         }

         optimize_data();

      }


      string data::get_full_text()
      {

         _synchronous_lock synchronouslock(this->synchronization());

         update_span_cache(m_spana);

         return ::user::rich_text::as_text(m_spana);

      }


      character_count data::_001InsertText(character_count i1, character_count i2, const ::scoped_string & scopedstrNewText, format * pformatParam)
      {

         ::string strProcess(scopedstrNewText);

         strProcess.find_replace("\r\n", "\n");

         strProcess.find_replace("\r", "\n");

         string_array_base straLines;

         straLines.add_lines(strProcess);

         synchronous_lock synchronouslock(this->synchronization());

         ::collection::index iSelBeg = i1;

         ::collection::index iSelEnd = i2;

         _001Delete(iSelBeg, iSelEnd);

         ::collection::index iSelChar = iSelBeg;

         ::collection::index iSpan = find_span(m_spana, iSelChar);

         ::pointer<format>pformat;

         ::pointer<span>pspan;

         ::e_align m_ealignNewLine;

         if (iSpan >= 0)
         {

            pspan = m_spana[iSpan];

            pformat = pspan->format();

            m_ealignNewLine = pspan->get_align();

            iSpan++;

         }
         else
         {

            pformat = m_pformatCurrent;

            m_ealignNewLine = e_align_left;

            iSpan = 0;

         }

         string str;

         for (::collection::index iLine = 0; iLine < straLines.get_count(); iLine++)
         {

            string strLine = straLines[iLine];

            if (iLine > 0 && iLine >= straLines.get_upper_bound())
            {

               break;

            }

            bool bNewSpan = false;

            if (pformatParam != nullptr)
            {

               pspan = create_span();

               if (iLine <= 0 || pformatParam->m_ealign != e_align_none)
               {

                  pspan->m_ealignNewLine = pformatParam->m_ealign;

               }
               else
               {

                  pspan->m_ealignNewLine = m_ealignNewLine;

               }

               pspan->m_pformat = pformatParam;

               m_spana.insert_at(iSpan, pspan);

               bNewSpan = true;

            }
            else if (iLine > 0 || !pspan)
            {

               pspan = create_span();

               pspan->m_ealignNewLine = m_ealignNewLine;

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

               information() << "iSelBeg : " << iSelBeg;
               information() << "pspan : " << (::iptr)pspan.m_p;
               information() << "pspan->m_iPosBeg : " << (iptr)pspan->m_iPosBeg;

               ASSERT(iSelBeg >= pspan->m_iPosBeg);

               character_count iMid = iSelBeg - pspan->m_iPosBeg;

               if (iLine >= straLines.get_upper_bound())
               {

                  pspan->m_str = pspan->m_str.left(iMid) + strLine + pspan->m_str.substr(iMid);

               }
               else
               {

                  {

                     auto pspanLast = create_span();

                     pspanLast->m_str = straLines.last() + pspan->m_str.substr(iMid);

                     pspanLast->m_ealignNewLine = pspan->get_align();

                     pspanLast->m_pformat = pspan->m_pformat;

                     m_spana.insert_at(iSpan, pspanLast);

                  }

                  pspan->m_bEndOfLine = true;

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

         update_span_cache(m_spana);

//         m_pedit->on_after_change(::id_after_change_text);

         return iSelChar;

      }


      void data::_001SetFontFormat(character_count i1, character_count i2, const format * pformat, const e_attribute & eattribute)
      {

         synchronous_lock synchronouslock(this->synchronization());

         optimize_data();

         string strText = get_full_text();

         ::collection::index iSelBeg = i1;

         ::collection::index iSelEnd = i2 - 1;

         ::collection::index iBeg = find_span(m_spana, iSelBeg);

         ::collection::index iEnd = find_span(m_spana, iSelEnd);

         if (iSelEnd - iSelBeg + 1 > 0)
         {

            if (iBeg >= 0 && iEnd >= iBeg)
            {

               auto pspanBeg = m_spana[iBeg];

               auto pspanEnd = m_spana[iEnd];

               ::collection::index iEndBeg = pspanEnd->m_iPosBeg;

               ::collection::index iEndEnd = pspanEnd->m_iPosEnd;

               string str;

               if (iBeg == iEnd)
               {

                  if (iSelBeg > pspanBeg->m_iPosBeg)
                  {

                     str = pspanBeg->m_str;

                     pspanBeg->m_str = str.left(iSelBeg - pspanBeg->m_iPosBeg);

                     auto pspan2 = pspanBeg->fork(pformat, eattribute);

                     pspan2->m_bEndOfLine = pspanBeg->m_bEndOfLine;

                     pspanBeg->m_bEndOfLine = false;

                     pspan2->m_str = str.substr(iSelBeg - pspanBeg->m_iPosBeg, iSelEnd - iSelBeg + 1);

                     m_spana.insert_at(iBeg + 1, pspan2);

                     if (iSelEnd + 1 < pspanBeg->m_iPosEnd)
                     {

                        auto pspan3 = pspanBeg->fork();

                        pspan3->m_bEndOfLine = pspan2->m_bEndOfLine;

                        pspan2->m_bEndOfLine = false;

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

                     auto pformatNew = add_format();

                     *pformatNew = *pspanBeg->m_pformat;

                     pformatNew->apply(pformat, eattribute);

                     pspanBeg->m_pformat = pformatNew;

                  }

               }
               else
               {

                  ::collection::index iInnerBeg;

                  ::collection::index iInnerEnd;

                  if (iSelBeg > pspanBeg->m_iPosBeg)
                  {

                     iEnd++;

                     str = pspanBeg->m_str;

                     pspanBeg->m_str = str.left(iSelBeg - pspanBeg->m_iPosBeg);

                     auto pspan2 = pspanBeg->fork(pformat, eattribute);

                     pspan2->m_bEndOfLine = pspanBeg->m_bEndOfLine;

                     pspanBeg->m_bEndOfLine = false;

                     pspan2->m_str = str.substr(iSelBeg - pspanBeg->m_iPosBeg);

                     m_spana.insert_at(iBeg + 1, pspan2);

                     iInnerBeg = iBeg + 2;

                  }
                  else
                  {

                     iInnerBeg = iBeg;

                  }

                  if (iSelEnd < iEndEnd)
                  {

                     str = pspanEnd->m_str;

                     auto pspan3 = pspanEnd->fork(pformat, eattribute);

                     pspan3->m_str = str.left(iSelEnd - iEndBeg + 1);

                     pspan3->m_ealignNewLine = pspanEnd->m_ealignNewLine;

                     pspanEnd->m_ealignNewLine = e_align_none;

                     m_spana.insert_at(iEnd, pspan3);

                     pspanEnd->m_str = str.substr(iSelEnd - iEndBeg + 1);

                     iInnerEnd = iEnd - 1;

                  }
                  else
                  {

                     //pspanEnd->m_pformat->apply(pformat, eattribute);

                     iInnerEnd = iEnd;

                  }

                  for (::collection::index i = iInnerBeg; i <= iInnerEnd; i++)
                  {

                     if (m_spana[i].is_set())
                     {

                        auto pformatNew = add_format();

                        *pformatNew = *m_spana[i]->m_pformat;

                        pformatNew->apply(pformat, eattribute);

                        m_spana[i]->m_pformat = pformatNew;

                     }

                  }

               }

            }

         }
         else
         {

            information() << "iSelEnd - iSelBeg + 1 <= 0";

         }

      }

      // unicode_next(str.c_str()) - str.c_str(); // at least one char is the longest pline

      // find phrase with greatest word count that fits the x, right constraints
      ::collection::count longest_pline(string & strSlice, double & d, string_array_base & straWords, double * pdaPosition, double dPositionLeft, int cx)
      {

         ::collection::count c = straWords.get_count();

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


      int longest_word(string & strSlice, double & dPosition, const ::scoped_string & scopedstrWord, double * pdaPosition, double dPositionLeft, int cx)
      {

         long l = 1;

         auto u = scopedstrWord.length();

         long m = 1;

         while (l < u)
         {

            m = (long)((l + u) / 2);

            dPosition = pdaPosition[m - 1] - dPositionLeft;

            if (dPosition > cx)
            {

               u = m - 1;

            }
            else
            {

               l = m + 1;

            }


         }

         while (m < scopedstrWord.length())
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

         strSlice = scopedstrWord.left(m);

         dPosition = pdaPosition[m - 1];

         return (int)m;

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



      void data::optimize_data()
      {

         synchronous_lock synchronouslock(this->synchronization());

         {

            erase_all();

            for (auto & pspan : m_spana)
            {

               format_host::defer_use_existing(pspan->m_pformat);

            }

         }

         //for (::collection::index i = 0; i < m_spana.get_count(); i++)
         //{

         //   m_spana[i]->m_pformat = get_format(m_spana, m_spana[i]->m_pformat);

         //}

         for (::collection::index i = 0; i < m_spana.get_count(); )
         {

            auto pformat = m_spana[i]->m_pformat;

            i++;

            while (i < m_spana.get_count() && !m_spana[i - 1]->is_end_of_line())
            {

               auto pformat2 = m_spana[i]->m_pformat;

               if (pformat2 == pformat)
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


      character_count data::_get_text_length() const
      {

         _synchronous_lock synchronouslock(this->synchronization());

         if (m_spana.is_empty())
         {

            return 0;

         }

         return m_spana.last()->m_iPosEnd;

      }




      void data::__initialize(::pointer<::user::rich_text::format> & pformat)
      {

         ødefer_construct(pformat);

         //auto estatus = 

         pformat->initialize_user_rich_text_format(this);

         //if (!estatus)
         //{

         //   return estatus;

         //}

         //return estatus;

      }


      //void data::write(::binary_stream & stream) const
      //{

      //   synchronous_lock synchronouslock(this->synchronization());

      //   stream << m_pformathost;

      //   stream << m_spana;

      //}


      //void data::read(::binary_stream & stream)
      //{

      //   synchronous_lock synchronouslock(this->synchronization());

      //   m_plinea->erase_all();

      //   m_pformathost->erase_all();

      //   m_spana.erase_all();

      //   stream >> m_pformathost;

      //   stream >> m_spana;

      //}



      bool data::on_new_data()
      {

         return ::data::data::on_new_data();

      }


      void data::read_data(::binary_stream & binarystream, const ::scoped_string & scopedstrFormat)
      {

         if (scopedstrFormat.case_insensitive_order("rtf") == 0)
         {

            read_from_stream(binarystream);
            //auto preader = file()->get_reader(payloadFile);

            //parse_rtf_text(str);

            //if (parse_rtf_text(str))
            //{

            //auto pfactory = system()->factory("text_format", "rtf");

            //auto ptextformat = øcreate< ::user::rich_text::text_format >(pfactory);

            //ptextformat->text_format_read(this, bin);

            //id_update_all_impacts(id_incoming_document);

            //}

         }


         //return true;

      }


      void data::write_data(::binary_stream & binarystream, const ::scoped_string & scopedstrFormat)
      {

         if (scopedstrFormat.case_insensitive_order("rtf") == 0)
         {

            write_to_stream(binarystream);

            //auto pfactory = system()->factory("text_format", "rtf");

            //auto ptextformat = øcreate< ::user::rich_text::text_format >(pfactory);

            //ptextformat->text_format_save(pfile, this);

         }

         //return true;

      }

      
      void data::read_from_stream(::binary_stream & binarystream)
      {

         auto pfactory = system()->factory("text_format", "rtf");

         auto ptextformat = øcreate< ::user::rich_text::text_format >(pfactory);

         ptextformat->text_format_read(this, binarystream);

      }


      void data::write_to_stream(::binary_stream & binarystream)
      {

         auto pfactory = system()->factory("text_format", "rtf");

         auto ptextformat = øcreate< ::user::rich_text::text_format >(pfactory);

         ptextformat->text_format_write(binarystream, this);

      }


   } // namespace rich_text


} // namespace user



