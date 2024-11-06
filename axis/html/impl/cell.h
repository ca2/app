#pragma once


#include "text.h"


namespace html
{


   namespace impl
   {


      class table;
      class table_row;


      class CLASS_DECL_AXIS cell :
         public ::html::impl::text
      {
      public:


         class CLASS_DECL_AXIS holder
         {
         public:


            ::collection::index m_iCol;
            ::collection::index m_iRow;


            holder();
            holder(int iCol, int iRow);
            holder(cell * pcell, int iCol, int iRow);
            holder(const class holder & holder);
            ::html::impl::cell *   m_pcell;

            bool is_null();

            holder & operator = (const class holder & holder);


         };

         cell();
         virtual ~cell();
         // example 1:
         // -------------------
         // |   X    |        |
         // -------------------
         // |        |        |
         // -------------------
         // population: (0, 0)
         // example 2:
         // -----------------------------
         // |        |        |         |
         // -----------------------------
         // |        |                  |
         // ----------        X         |
         // |        |                  |
         // -----------------------------
         // population: (1, 1), (1, 2), (2, 1), (2, 2)
         ::collection::index m_iColBeg;
         ::collection::index m_iRowBeg;
         ::collection::index m_iColEnd;
         ::collection::index m_iRowEnd;


         float m_fWidth;

         ::collection::count m_iRowSpan;
         ::collection::count m_iColSpan;


         table * get_table();
         table_row * get_row();
         ::collection::index get_min_col();

         using text::move_to;
         void move_to(html_data * pdocument);


         virtual ::float_size get_content_size();
         virtual ::float_point get_content_top_left();


         virtual float get_extra_content_height();


         virtual void implement_phase1(html_data * pdocument, ::html::element* pelemental);


         virtual void layout_phase0(html_data * pdocument);
         virtual bool layout_phase1(html_data * pdocument);
         virtual void layout_phase3(html_data * pdocument);


         virtual void layout_phase0_end(html_data * pdata);
         virtual void layout_phase1_end(html_data * pdata);
         virtual void layout_phase3_end(html_data * pdata);


         void on_change_layout(html_data * pdocument);

         void _001OnDraw(html_data * pdata);


         virtual float calc_width();


         virtual bool contains_column(::collection::index iCol);
         virtual bool contains_row(::collection::index iRow);
         virtual bool contains_cell(::collection::index iCol, ::collection::index iRow);

         virtual float get_table_border();
         virtual float get_cell_spacing();
         virtual float get_cell_padding();


      };


   } // namespace impl


} // namespace html




