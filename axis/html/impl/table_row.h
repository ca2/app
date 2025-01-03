#pragma once


#include "cell.h"


namespace html
{


   namespace impl
   {


      class CLASS_DECL_AXIS table_row : public element
      {
      public:


         ::collection::index                               m_iRow;
         int                             m_cyMin;
         int                             m_cyMax;
         array < cell::holder >        m_cellholdera;


         table_row();
         virtual ~table_row();


         void _001OnDraw(html_data * pdata);

         table * get_table();

         void set_cell(::collection::index iCol, ::collection::index iRow, cell * pcell);


         virtual void implement_phase1(html_data * pdocument, ::html::element* pelemental);
         
         
         virtual void layout_phase0(html_data * pdocument);
         virtual void layout_phase1_end(html_data * pdocument);
         virtual void layout_phase3(html_data * pdata);

         
         virtual void layout_phase3_end(html_data * pdata);


         virtual bool use_in_final_layout(::html::impl::element* pimplChild);

      };


   } // namespace impl


} // namespace html




