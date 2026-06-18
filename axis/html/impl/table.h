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

            ::collection::index        m_iCol;
            ::f32        m_cxMax;
            ::f32        m_cxMin;
            ::f32        m_x;
            ::f32        m_cx;

            column();
            column(::collection::index iCol);

         };

         ::f32                                           m_iBorder;
         ::f32                                           m_iCellSpacing;
         ::f32                                           m_iCellPadding;

         array_base < array_base < cell::holder > >      m_cellholdera;
         address_array_base < table_row * >              m_rowptra;
         array_base < column >                           m_columna;


         table();
         virtual ~table();





         void set_cell(::collection::index iCol, ::collection::index iRow, cell * pcell);


         void implement_phase1(html_data * pdata, ::html::element * pelement);


         virtual void layout_phase0(html_data * pdata);
         virtual void layout_phase2(html_data * pdata);
         virtual void layout_phase3(html_data * pdata);


         virtual void layout_phase1_end(html_data * pdata);
         virtual void layout_phase3_end(html_data * pdata);


         void _001OnDraw(html_data * pdata);



         virtual ::f32 calc_width();


      };


   } // namespace impl


} // namespace html




