#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "_impl.h"
#endif
#include "cell.h"
#include "table_row.h"
#include "table.h"
#include "axis/html/html/data.h"
#include "axis/html/html/core_data.h"
#include "axis/html/element/element.h"
#include "aura/user/user/interaction.h"


namespace html
{


   namespace impl
   {


      cell::cell()
      {

         m_iRowSpan     = 1;
         m_iColSpan     = 1;

         m_iColBeg      = -1;
         m_iColEnd      = -1;
         m_iRowBeg      = -1;
         m_iRowEnd      = -1;

      }


      cell::~cell()
      {

      }


      table * cell::get_table()
      {

         ::html::element * pelement = m_pelemental;

         while(true)
         {

            pelement = pelement->m_pparent;

            if(pelement == nullptr)
               return nullptr;

            __pointer(table) ptable = pelement->m_pimpl;

            if(ptable != nullptr)
               return ptable;

         }

      }


      table_row * cell::get_row()
      {

         ::html::element * pelement = m_pelemental;

         while(true)
         {

            pelement = pelement->m_pparent;

            if(pelement == nullptr)
               return nullptr;

            __pointer(table_row) prow = pelement->m_pimpl;

            if(prow != nullptr)
               return prow;

         }

      }


      void cell::implement_phase1(html_data * pdata, ::html::element * pelement)
      {

         m_bHasChar = true;

         ::html::impl::text::implement_phase1(pdata, pelement);

         if (!m_pelemental->m_propertyset.is_new_or_null("colspan"))
         {

            m_pelemental->m_propertyset["colspan"].as(m_iColSpan);

         }

         if (!m_pelemental->m_propertyset.is_new_or_null("rowspan"))
         {

            m_pelemental->m_propertyset["rowspan"].as(m_iRowSpan);

         }

         table * ptable = get_table();

         if (ptable == nullptr)
            return;

         table_row * prow = get_row();

         if (prow == nullptr)
            return;

         m_iColBeg = get_min_col();

         m_iColEnd = m_iColBeg + m_iColSpan - 1;

         m_iRowBeg = prow->m_iRow;

         m_iRowEnd = m_iRowBeg + m_iRowSpan - 1;

         for (index iCol = m_iColBeg; iCol <= m_iColEnd; iCol++)
         {

            for (index iRow = m_iRowBeg; iRow <= m_iRowEnd; iRow++)
            {

               ptable->set_cell(iCol, iRow, this);

               prow->set_cell(iCol, iRow, this);

            }

         }

         while (ptable->m_columna.get_size() < prow->m_cellholdera.get_size())
         {

            ptable->m_columna.add(table::column(ptable->m_columna.get_size()));

         }

         if (prow->m_iRow > 0)
         {

            // if first cell in this column has a width,
            // copy this cell width

            cell * pcellFirst = ptable->m_cellholdera[m_iColBeg][0].m_pcell;

            if (pcellFirst != nullptr && pcellFirst->m_flags.has(FlagWidth))
            {

               m_flags.add(FlagWidth);

               if (pcellFirst->m_flags.has(FlagWidthPercent))
               {

                  m_flags.add(FlagWidthPercent);

               }
               else
               {

                  m_flags.add(FlagWidthPixel);

               }

            }

         }
         else
         {

            if (!m_pelemental->m_propertyset.is_new_or_null("width"))
            {

               string strWidth(m_pelemental->m_propertyset["width"].get_string());

               if (strWidth.find("%") > 0)
               {

                  m_flags.add(FlagWidthPercent);

               }
               else
               {

                  m_flags.add(FlagWidthPixel);

               }

            }

         }

         bool bTableBorder = get_table()->m_iBorder > 0;

         if (m_border.left < 1.f && bTableBorder)
         {
            m_border.left = get_table()->m_iBorder;
            m_border.crLeft = argb(255, 90, 90, 90);
            m_border.styleLeft = ::html::border::style_solid;
         }
         if (m_border.top < 1.f && bTableBorder)
         {
            m_border.top = get_table()->m_iBorder;
            m_border.crTop = argb(255, 90, 90, 90);
            m_border.styleTop = ::html::border::style_solid;
         }
         if (m_border.right < 1.f && bTableBorder)
         {
            m_border.right = get_table()->m_iBorder;
            m_border.crRight = argb(255, 192, 192, 192);
            m_border.styleRight = ::html::border::style_solid;
         }
         if (m_border.bottom < 1.f && bTableBorder)
         {
            m_border.bottom = get_table()->m_iBorder;
            m_border.crBottom = argb(255, 192, 192, 192);
            m_border.styleBottom = ::html::border::style_solid;
         }

         bool bTableCellPadding = get_table()->m_iCellPadding > 0;

         if (m_padding.left == 0.f && bTableCellPadding)
         {
            m_padding.left = get_table()->m_iCellPadding;
         }
         if (m_padding.top == 0.f && bTableCellPadding)
         {
            m_padding.top = get_table()->m_iCellPadding;
         }
         if (m_padding.right == 0.f && bTableCellPadding)
         {
            m_padding.right = get_table()->m_iCellPadding;
         }
         if (m_padding.bottom == 0.f && bTableCellPadding)
         {
            m_padding.bottom = get_table()->m_iCellPadding;
         }

         if (m_pelemental->m_elementalptra.is_empty())
            return;

         pdata->m_pcoredata->m_bHasChar = false;

      }

      void cell::layout_phase0(html_data * pdata)
      {

         if (m_pelemental->m_elementalptra.has_elements())
         {

            pdata->m_pcoredata->m_bHasChar = false;

         }

         text::layout_phase0(pdata);

      }


      void cell::layout_phase0_end(html_data * pdata)
      {

         if (m_pelemental->m_elementalptra.is_empty())
            return;

         container_raw_max_width(pdata);

         table * ptable = get_table();

         if (ptable == nullptr)
            return;

         table_row * prow = get_row();

         if (prow == nullptr)
            return;

         if (ptable->m_iCellSpacing > 0)
         {

            if (m_iColBeg == 0)
            {

               m_cxMax += ptable->m_iCellSpacing; //left;
               m_cxMin += ptable->m_iCellSpacing; //left;
               m_cxMax += ptable->m_iCellSpacing * (m_iColEnd - m_iColBeg); // mid
               m_cxMin += ptable->m_iCellSpacing * (m_iColEnd - m_iColBeg); // mid
               m_cxMax += ptable->m_iCellSpacing / 2; //half right;
               m_cxMin += ptable->m_iCellSpacing / 2; //half right;
               m_cxMax += fmodf(ptable->m_iCellSpacing, 2.f); //odd right;
               m_cxMin += fmodf(ptable->m_iCellSpacing, 2.f); //odd right;

            }
            else if (m_iColEnd == ptable->m_columna.get_upper_bound())
            {

               m_cxMax += ptable->m_iCellSpacing / 2; //half left;
               m_cxMin += ptable->m_iCellSpacing / 2; //half left;
               m_cxMax += ptable->m_iCellSpacing * (m_iColEnd - m_iColBeg); // mid
               m_cxMin += ptable->m_iCellSpacing * (m_iColEnd - m_iColBeg); // mid
               m_cxMax += ptable->m_iCellSpacing; // right;
               m_cxMin += ptable->m_iCellSpacing; // right;

            }
            else
            {

               m_cxMax += ptable->m_iCellSpacing * (m_iColEnd - m_iColBeg); // cellcount * mid = cellcount * ((half left) + (half right) + (odd right))
               m_cxMin += ptable->m_iCellSpacing * (m_iColEnd - m_iColBeg); // cellcount * mid = cellcount * ((half left) + (half right) + (odd right))

            }

         }

      }


      bool cell::layout_phase1(html_data * pdata)
      {

         if (m_pelemental->m_elementalptra.is_empty())
         {

            return text::layout_phase1(pdata);

         }

         //set_xy(pdata);

         auto size = get_bound_size();

         float iColumnWidth = calc_width();

//         float iTableBorder = get_table()->m_iBorder;

         /*if(iTableBorder > 0)
         {

            iTableBorder += 2;

            ::size_f32.cx = (float) (iColumnWidth - (m_iColEnd == get_table()->m_columna.get_upper_bound() ? iTableBorder * 2 : iTableBorder));

            ::size_f32.cy -= (float) (m_iRowEnd == get_table()->m_rowptra.get_upper_bound() ? iTableBorder * 2 : iTableBorder);

         }
         else*/
         {

            size.cx = iColumnWidth;

         }

         /*

         table * ptable = get_table();

         if (ptable == nullptr)
            return;

         table_row * prow = get_row();

         if (prow == nullptr)
            return;

         if (ptable->m_iCellSpacing > 0)
         {

            if (m_iColBeg == 0)
            {

               iColumnWidth += ptable->m_iCellSpacing; //left;
               iColumnWidth += ptable->m_iCellSpacing * (m_iColEnd - m_iColBeg); // mid
               iColumnWidth += ptable->m_iCellSpacing / 2; //half right;
               iColumnWidth += fmod(ptable->m_iCellSpacing, 2.f); //odd right;

            }
            else if (m_iColEnd == ptable->m_columna.get_upper_bound())
            {

               iColumnWidth += ptable->m_iCellSpacing / 2; //half left;
               iColumnWidth += ptable->m_iCellSpacing * (m_iColEnd - m_iColBeg); // mid
               iColumnWidth += ptable->m_iCellSpacing; // right;

            }
            else
            {

               iColumnWidth += ptable->m_iCellSpacing * (m_iColEnd - m_iColBeg); // cellcount * mid = cellcount * ((half left) + (half right) + (odd right))

            }

         }

         */

         m_box.set_width((float) iColumnWidth);

         m_bound.set_width((float) iColumnWidth);

         pdata->m_pcoredata->m_layoutstate1.m_bHasChar = false;

         return true;

      }


      void cell::layout_phase1_end(html_data * pdata)
      {

         ::html::impl::element::layout_phase1_end(pdata);

      }


      void cell::layout_phase3(html_data * pdata)
      {

         if (m_iColBeg < 0 || m_iRowBeg < 0)
            return;

         move_left_to(pdata, get_table()->m_columna[m_iColBeg].m_x);

         set_width(pdata, get_table()->m_columna[m_iColBeg].m_cx);

         move_top_to(pdata, get_table()->m_rowptra[m_iRowBeg]->m_box.top);

      }


      void cell::layout_phase3_end(html_data * pdata)
      {

         pdata->m_pcoredata->m_layoutstate3.m_cya.last() = m_box.width();

      }


      void cell::on_change_layout(html_data * pdata)
      {

         __UNREFERENCED_PARAMETER(pdata);

      }


      void cell::move_to(html_data * pdata)
      {

         text::move_to(pdata);

      }


      ::size_f32 cell::get_content_size()
      {

         auto size = ::html::impl::element::get_content_size();

         //::size_f32.cx -= get_table()->m_iCellSpacing;

         //if(m_iColBeg == 0)
         //{
         //   ::size_f32.cx -= get_table()->m_iCellSpacing / 2.f;
         //}
         //else if(m_iColEnd == get_table()->m_columna.get_upper_bound())
         //{
         //   ::size_f32.cx -= get_table()->m_iCellSpacing / 2.f;
         //}

         //::size_f32.cy -= get_table()->m_iCellSpacing;

         //if(m_iRowBeg == 0)
         //{
         //   ::size_f32.cy -= get_table()->m_iCellSpacing / 2.f;
         //}
         //else if(m_iRowEnd == get_table()->m_rowptra.get_upper_bound())
         //{
         //   ::size_f32.cy -= get_table()->m_iCellSpacing / 2.f;
         //}

         return size;

      }


      float cell::get_extra_content_height()
      {

         return ::html::impl::element::get_extra_content_height();
         /*if (m_iRowBeg == 0 || m_iRowBeg == get_table()->m_rowptra.get_upper_bound())
         {

            return element::get_extra_content_cy() + get_table()->m_iCellSpacing + get_table()->m_iCellSpacing / 2.f;

         }
         else
         {

            return element::get_extra_content_cy() + get_table()->m_iCellSpacing;

         }*/

      }


      ::point_f32 cell::get_content_top_left()
      {

         auto point = ::html::impl::element::get_content_top_left();

         /*if(m_iColBeg == 0)
         {
            ::point_f32.x += get_table()->m_iCellSpacing;
         }
         else
         {
            ::point_f32.x += get_table()->m_iCellSpacing / 2.f;
         }

         if(m_iRowBeg == 0)
         {
            ::point_f32.y += get_table()->m_iCellSpacing;
         }
         else
         {
            ::point_f32.y += get_table()->m_iCellSpacing / 2.f;
         }*/

         return point;

      }


      index cell::get_min_col()
      {

         index iMinCol = 0;

         table_row * prow = get_row();

         if(prow != nullptr)
         {

            for(i32 i = 0; i < prow->m_pelemental->m_elementalptra.get_count(); i++)
            {

               ::html::element * pelement = prow->m_pelemental->m_elementalptra[i];

               if(pelement == m_pelemental)
                  break;

               __pointer(cell) pcell = pelement->m_pimpl;

               if(pcell != nullptr)
               {

                  iMinCol += pcell->m_iColSpan;

               }
               else if(pelement->m_etag == tag_td)
               {

                  if(!pelement->m_propertyset.is_new_or_null("colspan"))
                  {

                     iMinCol += pelement->m_propertyset["colspan"].i32();

                  }
                  else
                  {

                     iMinCol += 1;

                  }

               }

            }

         }

         return iMinCol;

      }


      cell::holder::holder()
      {

         m_pcell  =   nullptr;
         m_iCol      = -1;
         m_iRow      = -1;

      }


      cell::holder::holder(i32 iCol, i32 iRow)
      {

         m_pcell     = nullptr;
         m_iCol      = iCol;
         m_iRow      = iRow;

      }


      cell::holder::holder(cell * pcell, i32 iCol, i32 iRow)
      {

         m_pcell     = pcell;
         m_iCol      = iCol;
         m_iRow      = iRow;

      }


      cell::holder::holder(const class holder & holder)
      {

         operator = (holder);

      }


      bool cell::holder::is_null()
      {

         return m_pcell == nullptr;

      }


      cell::holder & cell::holder::operator = (const class holder & holder)
      {

         if(&holder != this)
         {

            m_pcell     = holder.m_pcell;
            m_iCol     = holder.m_iCol;
            m_iRow     = holder.m_iRow;

         }

         return *this;

      }


      void cell::_001OnDraw(html_data * pdata)
      {

         text::_001OnDraw(pdata);

         //::html::impl::element::_001OnDraw(pdata);

      }


      bool cell::contains_column(index iCol)
      {

         return iCol >= m_iColBeg && iCol <= m_iColEnd;

      }


      bool cell::contains_row(index iRow)
      {

         return iRow >= m_iRowBeg && iRow <= m_iRowEnd;

      }


      bool cell::contains_cell(index iCol, index iRow)
      {

         return contains_column(iCol) && contains_row(iRow);

      }


      float cell::calc_width()
      {

         float iColumnWidth = 0;

         float cxMax;

         if(get_table() != nullptr)
         {

            ::count n = get_table()->m_columna.get_size();

            float cellMax = 0;

            float sMax = 0;

            for(index iColumn = 0; iColumn < n; iColumn++)
            {

               cxMax = get_table()->m_columna[iColumn].m_cxMax;

               sMax += cxMax;

               if(contains_column(iColumn))
               {

                  cellMax += cxMax;

               }

            }

            float W = get_table()->calc_width();

            if(sMax > 0)
            {

               iColumnWidth = W * cellMax  / sMax;

            }
            else
            {

               iColumnWidth = W / n;

            }

         }

         return iColumnWidth;

      }


      float cell::get_table_border()
      {

         return get_table()->m_iBorder;

      }


      float cell::get_cell_spacing()
      {

         return get_table()->m_iCellSpacing;

      }


      float cell::get_cell_padding()
      {

         return get_table()->m_iCellPadding;

      }


   } // namespace impl


} // namespace html



