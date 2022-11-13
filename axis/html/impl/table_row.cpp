#include "framework.h"
#include "cell.h"
#include "table_row.h"
#include "table.h"
#include "acme/primitive/data/listener.h"
#include "axis/html/html/data.h"
#include "axis/html/element/element.h"
#include "axis/html/graphics/base.h"
#include "axis/html/graphics/font.h"
#include "axis/html/graphics/style.h"
#include "axis/html/html/core_data.h"
#include "aura/user/user/interaction.h"


namespace html
{


   namespace impl
   {


      table_row::table_row()
      {

         m_cyMin = -1;
         m_cyMax = 0;

      }


      table_row::~table_row()
      {

      }


      table * table_row::get_table()
      {

         ::html::element * pelement = m_pelemental;

         while(true)
         {

            pelement = pelement->m_pparent;

            if(pelement == nullptr)
               return nullptr;

            ::pointer<table>ptable = pelement->m_pimpl;

            if(ptable != nullptr)
               return ptable;

         }

      }


      void table_row::implement_phase1(html_data * pdata, ::html::element * pelement)
      {

         m_bHasChar = true;

         element::implement_phase1(pdata, pelement);

         table * ptable = get_table();

         if(ptable == nullptr)
            return;

         m_iRow = ptable->m_rowptra.get_size();

         if(m_pelemental->m_pbase->get_type() == ::html::base::type_tag)
         {

            ptable->m_rowptra.add_unique(this);

         }

         for(i32 i = 0; i < get_table()->m_cellholdera.get_size(); i++)
         {

            for(i32 j = 0; j < get_table()->m_cellholdera[i].get_size(); j++)
            {

               if(ptable->m_cellholdera[i][j].m_iRow == m_iRow)
               {

                  m_cellholdera.set_at_grow(ptable->m_cellholdera[i][j].m_iCol, get_table()->m_cellholdera[i][j]);

               }

            }

         }

      }


      void table_row::layout_phase0(html_data * pdata)
      {

         float iTableBorder = get_table()->m_iBorder;

         if(iTableBorder > 0)
         {

            iTableBorder += 1;

         }

         index i;

         float cxMax = 0.f;

         float cxMin = 0.f;

         for(i = 0; i < m_cellholdera.get_size() && i < get_table()->m_columna.get_size(); i++)
         {

            cell * pcell = m_cellholdera[i].m_pcell;

            if (pcell == nullptr)
               continue;

            pcell->m_pelemental->layout_phase0(pdata);

            if(pcell->m_cxMax > cxMax)
            {

               cxMax = pcell->m_cxMax;

            }

            if(pcell->m_cxMin > cxMin)
            {

               cxMin = pcell->m_cxMin;

            }

            if(pcell->m_cxMax > get_table()->m_columna[i].m_cxMax)
            {

               get_table()->m_columna[i].m_cxMax = pcell->m_cxMax + (i == get_table()->m_columna.get_upper_bound() ?  iTableBorder * 2.f : iTableBorder);

            }

            if(pcell->m_cxMin > get_table()->m_columna[i].m_cxMin)
            {

               get_table()->m_columna[i].m_cxMin = pcell->m_cxMin + (i == get_table()->m_columna.get_upper_bound() ?  iTableBorder * 2.f : iTableBorder);

            }

         }

         if(get_table() != nullptr)
         {

            for(index i = 0; i < get_table()->m_columna.get_size(); i++)
            {

               cxMax += maximum(0.f, get_table()->m_columna[i].m_cxMax);

               cxMin += maximum(0.f, get_table()->m_columna[i].m_cxMin);

            }

         }

         cxMax += m_padding.left + m_padding.right + m_border.left + m_border.right + m_margin.left + m_margin.right;

         cxMin += m_padding.left + m_padding.right + m_border.left + m_border.right + m_margin.left + m_margin.right;


      }


      void table_row::layout_phase1_end(html_data * pdata)
      {

         for (i32 i = 0; i < m_cellholdera.get_size(); i++)
         {

            cell * pcell = m_cellholdera[i].m_pcell;

            if (pcell != nullptr)
            {

               if (pcell->height() > m_cyMax)
               {

                  m_cyMax = (i32) pcell->height();

               }

               if (pcell->height() < m_cyMin || m_cyMin < 0)
               {

                  m_cyMin = (i32)pcell->height();

               }

            }

         }

         for (i32 i = 0; i < m_cellholdera.get_size(); i++)
         {

            cell * pcell = m_cellholdera[i].m_pcell;

            if (pcell != nullptr)
            {

               pcell->m_box.set_height((float) m_cyMax);

            }

         }

         m_box.set_height((float)m_cyMax);

         m_bound.set_height((float)m_cyMax);

         pdata->m_pcoredata->m_layoutstate1.m_cy = (float)m_cyMax;

         pdata->m_pcoredata->m_layoutstate1.m_cya.last() = (float)m_cyMax;

      }


      void table_row::layout_phase3(html_data * pdata)
      {

         pdata->m_pcoredata->m_layoutstate3.m_y += get_table()->m_iCellSpacing;

         move_to(pdata);

      }


      void table_row::layout_phase3_end(html_data * pdata)
      {

//         pdata->m_pcoredata->m_layoutstate3.m_cya.last() = m_box.get_cy();

      }


      void table_row::set_cell(index iCol, index iRow, cell * pcell)
      {

         if(iRow != m_iRow)
            return;

         m_cellholdera.element_at_grow(iCol).m_pcell = pcell;

      }

      void table_row::_001OnDraw(html_data * pdata)
      {
      }


      bool table_row::use_in_final_layout(::html::impl::element * pimplChild)
      {

         if(pimplChild->m_pelemental->m_etag == tag_tr)
         {

            return false;

         }

         return true;

      }


   } // namespace impl


} // namespace html





