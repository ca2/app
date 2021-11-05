#pragma once


namespace html
{


   namespace impl
   {


      class table;
      class table_row;


      class CLASS_DECL_CORE cell :
         public ::html::impl::text
      {
      public:


         class CLASS_DECL_CORE holder
         {
         public:


            index m_iCol;
            index m_iRow;


            holder();
            holder(i32 iCol, i32 iRow);
            holder(cell * pcell, i32 iCol, i32 iRow);
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
         index m_iColBeg;
         index m_iRowBeg;
         index m_iColEnd;
         index m_iRowEnd;


         float m_fWidth;

         ::count m_iRowSpan;
         ::count m_iColSpan;


         table * get_table();
         table_row * get_row();
         index get_min_col();

         using text::move_to;
         void move_to(html_data * pdocument);


         virtual ::size_f32 get_content_size();
         virtual ::point_f32 get_content_top_left();


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


         virtual bool contains_column(index iCol);
         virtual bool contains_row(index iRow);
         virtual bool contains_cell(index iCol, index iRow);

         virtual float get_table_border();
         virtual float get_cell_spacing();
         virtual float get_cell_padding();


      };


   } // namespace impl


} // namespace html




