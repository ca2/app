#include "framework.h"
#include "_impl.h"


namespace html
{


   namespace impl
   {


      table::table()
      {

         m_iBorder         = 1;

         m_iCellSpacing    = 2;

         m_iCellPadding    = 2;

      }


      table::~table()
      {

      }


      void table::implement_phase1(html_data * pdata, ::html::element* pelemental)
      {

         m_bHasChar = true;

         element::implement_phase1(pdata, pelemental);

         if(m_pelemental->m_pbase->get_type() !=:: html::base::type_tag)
         {

            return;

         }

         tag * ptag = m_pelemental->get_tag();

         if(ptag != nullptr)
         {

            if(ptag->get_attr_value("border").has_char())
            {
               m_iBorder         = (float) ::str::to_u32(ptag->get_attr_value("border"));
            }

            if(ptag->get_attr_value("cellspacing").has_char())
            {
               m_iCellSpacing    = (float) ::str::to_u32(ptag->get_attr_value("cellspacing"));
            }

            if(ptag->get_attr_value("cellpadding").has_char())
            {
               m_iCellPadding    = (float) ::str::to_u32(ptag->get_attr_value("cellpadding"));
            }

         }

         bool bTableBorder = m_iBorder > 0;

         if(m_border.left == 0.f && bTableBorder)
         {
            m_border.left = m_iBorder;
            m_border.crLeft = argb(255, 192, 192, 192);
            m_border.styleLeft = ::html::border::style_solid;
         }
         if(m_border.top == 0.f && bTableBorder)
         {
            m_border.top = m_iBorder;
            m_border.crTop = argb(255, 192, 192, 192);
            m_border.styleTop = ::html::border::style_solid;
         }
         if(m_border.right == 0.f && bTableBorder)
         {
            m_border.right = m_iBorder;
            m_border.crRight = argb(255, 90, 90, 90);
            m_border.styleRight = ::html::border::style_solid;
         }
         if(m_border.bottom == 0.f && bTableBorder)
         {
            m_border.bottom = m_iBorder;
            m_border.crBottom = argb(255, 90, 90, 90);
            m_border.styleBottom = ::html::border::style_solid;
         }

      }


      float table::calc_width()
      {

         string strWidth = m_pelemental->m_pstyle->m_propertyset["width"].get_string();

         strWidth.trim();

//         if (false && str::ends_eat(strWidth, "%"))
//         {
//
//            strWidth.trim();
//
//            float percent = payload(strWidth).get_float();
//
//            float cx = m_bound.get_cx();
//
//            cx *= percent / 100.0f;
//
//            return cx;
//
//
//         }

         float cx = 0.f;

         for (i32 i = 0; i < m_columna.get_size(); i++)
         {

            cx += m_columna[i].m_cxMax;

         }

         return cx;

      }


      void table::layout_phase0(html_data * pdata)
      {

         for (index j = 0; j < m_rowptra.get_size(); j++)
         {

            m_rowptra[j]->m_pelemental->layout_phase0(pdata);

         }

         float cxMax = 0;

         float cxMin = 0;

         for(index i = 0; i < m_cellholdera.get_size(); i++)
         {

            cxMax += max(0, m_columna[i].m_cxMax);

            cxMin += max(0, m_columna[i].m_cxMin);

         }

         m_cxMax = cxMax;

         m_cxMin = cxMin;

      }


      void table::layout_phase1_end(html_data * pdata)
      {

         //element::layout_phase1_end(pdata);

         for (index i = 0; i < m_columna.get_count(); i++)
         {

            m_columna[i].m_cx = 0;

         }

         index iCol;

         cell * pcell;

         for (index i = 0; i < m_cellholdera.get_count(); i++)
         {

            for (index j = 0; j < m_cellholdera[i].get_count(); j++)
            {

               cell::holder & holder = m_cellholdera[i][j];

               pcell = holder.m_pcell;

               if (pcell == nullptr)
                  continue;

               iCol = holder.m_iCol;

               if (iCol < 0)
                  continue;

               if (iCol >= m_columna.get_size())
                  continue;

               m_columna[iCol].m_cx = max(pcell->m_box.width(), m_columna[iCol].m_cx);

            }

         }


         float cx = m_iCellSpacing;

         float cy = m_iCellSpacing;

         float x = m_box.left + m_iCellSpacing;

         for (i32 i = 0; i < m_columna.get_size(); i++)
         {

            m_columna[i].m_x = x;

            x += m_columna[i].m_cx + m_iCellSpacing;

            cx += m_columna[i].m_cx + m_iCellSpacing;

         }

         for (i32 i = 0; i < m_rowptra.get_size(); i++)
         {

            //   cy += m_rowptra[i]->m_box.get_cy() + m_iCellSpacing + 1;
            cy += m_rowptra[i]->m_box.height() + m_iCellSpacing;

         }

         m_box.right =
         m_box.left
         + cx
         + m_margin.left
         + m_margin.right
         + m_border.left
         + m_border.right;
//            + m_padding.left
         //          + m_padding.right;

         m_box.bottom =
         m_box.top
         + cy
         + m_margin.top
         + m_margin.bottom
         + m_border.top
         + m_border.bottom;
//            + m_padding.top
         //          + m_padding.bottom;

         pdata->m_pcoredata->m_layoutstate1.m_cya.last() = m_box.height();

         pdata->m_pcoredata->m_layoutstate1.m_cxMax.last() = max(m_box.width(), pdata->m_pcoredata->m_layoutstate1.m_cxMax.last());

      }


      void table::layout_phase2(html_data * pdata)
      {

         UNREFERENCED_PARAMETER(pdata);

      }


      void table::layout_phase3(html_data * pdata)
      {

         UNREFERENCED_PARAMETER(pdata);

         move_to(pdata);

//         float cx = m_iCellSpacing;

         float cy = m_iCellSpacing;

         float x = m_box.left + m_iCellSpacing + m_border.left + m_margin.left;

         for (i32 i = 0; i < m_columna.get_size(); i++)
         {

            m_columna[i].m_x = x;

            x += m_columna[i].m_cx + m_iCellSpacing;

         }

         for (i32 i = 0; i < m_rowptra.get_size(); i++)
         {

            //   cy += m_rowptra[i]->m_box.get_cy() + m_iCellSpacing + 1;
            cy += m_rowptra[i]->m_box.height() + m_iCellSpacing;

         }



      }


      void table::layout_phase3_end(html_data * pdata)
      {

      }


      table::column::column()
      {

         m_iCol   = -1;
         m_cxMax  = -2;
         m_cxMin  = -2;

      }


      table::column::column(index iCol)
      {

         m_iCol   = iCol;
         m_cxMax  = -2;
         m_cxMin  = -2;

      }


      void table::set_cell(index iCol, index iRow, cell * pcell)
      {

         m_cellholdera.element_at_grow(iCol).element_at_grow(iRow).m_iCol     = iCol;
         m_cellholdera.element_at_grow(iCol).element_at_grow(iRow).m_iRow     = iRow;
         m_cellholdera.element_at_grow(iCol).element_at_grow(iRow).m_pcell    = pcell;

      }


      void table::_001OnDraw(html_data * pdata)
      {

         if(m_pelemental->m_pbase->get_type() == ::html::base::type_value)
            return;

         element::_001OnDraw(pdata);

         /*if(m_iBorder > 0)
         {

         pdata->m_pcoredata->m_pdc->draw3d_rect(get_x() - m_iBorder - 2, get_y() - m_iBorder - 2,
         get_cx() + ((m_iBorder + 2) * 2), get_cy() + ((m_iBorder + 2) * 2), argb(255, 190, 184, 184), argb(255, 90, 90, 90));

         }*/
      }

   } // namespace impl

} // namespace html
