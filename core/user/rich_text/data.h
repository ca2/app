#pragma once


namespace user
{


   namespace rich_text
   {


      class edit_impl;


      class CLASS_DECL_CORE data :
         virtual public ::data::data
      {
      public:


         ::draw2d::graphics_pointer                   m_pgraphics;

         //::rectangle_f64                            m_rectangle;
         
         // storage data
         __pointer_array(span)                        m_spana;
         __pointer(__pointer_array(format))           m_pformata;

         __pointer(format)                            m_pformatCurrent;

         /// runtime span, ephemeral, derived
         /// should be easily rebuildable from "storage" data and a client rectangle_i32
         __pointer(__pointer_array(line))             m_plinea;

         strsize                                      m_iSelBeg;
         strsize                                      m_iSelEnd;
         index                                        m_iSelLine;
         rich_text::edit_impl *                       m_pedit;
         ::duration                                   m_durationCaretPeriod;
         //index                                      m_iFormatDefault;
         bool                                         m_bCaretRight;


         data();
         ~data() override;


         ::e_status initialize_data(::data::data_container_base * pdocument) override;


         virtual ::e_status __initialize(__pointer(::user::rich_text::format) & pformat);


         virtual ::rectangle_f64 get_drawing_rect();

         // if span has alignment set, it generates new line
         __pointer(span) create_span(::e_align ealignNewLine = e_align_none);

         __pointer(format) add_format();

         __pointer(span) add_span(::e_align ealignNewLine = e_align_none);

         __pointer(span) add_span(const span & span);

         //index fork_format(index iFormat);

         virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics);

         virtual void do_layout(::draw2d::graphics_pointer & pgraphics);

         virtual strsize hit_test(point_f64 point);
         virtual strsize hit_test_line_x(index iLine, double x);

         virtual strsize get_sel_beg();
         virtual strsize get_sel_end();

         string get_full_text();

         virtual void internal_update_sel_char();

         virtual void on_selection_change(format * pformat);
         virtual void get_selection_intersection_format(format* pformat, index iSelBeg, index iSelEnd);

         virtual void _001SetSelFontFormat(const format * pformat, const eattribute & eattribute);

         virtual void _001Delete(strsize i1, strsize i2);
         virtual void _001InsertText(const ::string & psz, format * pformatParam = nullptr);

         virtual void _001GetText(string & str) const;
         virtual void _001GetLayoutText(string & str) const;

         virtual void draw_text(::draw2d::graphics_pointer & pgraphics, const ::rectangle_f64 & rectangle);

         virtual void optimize_data();

         virtual index SelToLine(strsize i) const;
         virtual strsize LineColumnToSel(index iLine, strsize iColumn) const;

         virtual strsize _001GetTextLength() const;
         virtual strsize _001GetLayoutTextLength() const;

         virtual ::stream & write(::stream & stream) const override;
         virtual ::stream & read(::stream & stream) override;


      };


      inline void span::set_new_format(){ m_pformat = m_pdata->add_format(); }

   } // namespace rich_text


} // namespace user



