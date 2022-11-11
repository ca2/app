#pragma once


#include "element.h"
#include "cell.h"


namespace html
{


   namespace impl
   {


      class CLASS_DECL_AXIS table : public element
      {
      public:


         class CLASS_DECL_AXIS column
         {
         public:

            index        m_iCol;
            float        m_cxMax;
            float        m_cxMin;
            float        m_x;
            float        m_cx;

            column();
            column(index iCol);

         };

         float                                           m_iBorder;
         float                                           m_iCellSpacing;
         float                                           m_iCellPadding;

         array < array < cell::holder > >                m_cellholdera;
         address_array < table_row * >                   m_rowptra;
         array < column >                                m_columna;


         table();
         virtual ~table();





         void set_cell(index iCol, index iRow, cell * pcell);


         void implement_phase1(html_data * pdata, ::html::element * pelement);


         virtual void layout_phase0(html_data * pdata);
         virtual void layout_phase2(html_data * pdata);
         virtual void layout_phase3(html_data * pdata);


         virtual void layout_phase1_end(html_data * pdata);
         virtual void layout_phase3_end(html_data * pdata);


         void _001OnDraw(html_data * pdata);



         virtual float calc_width();


      };


   } // namespace impl


} // namespace html




