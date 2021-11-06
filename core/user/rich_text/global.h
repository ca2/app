#pragma once


namespace user
{


   namespace rich_text
   {


      bool is_equal_bool(bool b1, bool b2);
      bool is_similar_font_size(double d1, double d2);
      void update_span_cache(__pointer_array(span) & spana);
      //void update_span_cache(__pointer_array(span) & spana, __pointer_array(line) & layouta);
      index find_span(__pointer_array(span) & spana, index iSel);
      ::e_align box_align(__pointer_array(span) & spana, index iBox);
      bool box_align(__pointer_array(span) & spana, index iBox, ::e_align ealign);
      index find_char_span(__pointer_array(span) & spana, strsize iChar);
      box * find_box(__pointer_array(line) & span, index iSel);
      string layout_text(const __pointer_array(line) & span);
      void align(line * pline, const ::rectangle_f64 & rectangle);

      string line_text(line & line);
      index sel_line(const __pointer_array(line) & span, index iSel);
      index sel_line_x666(__pointer_array(line) & span, index iSel, double & x);
      index line_caret_x(__pointer_array(line)& span, index iSel, double& x);
      string text(const __pointer_array(span) & spana);
      //__pointer(format) get_format(__pointer_array(format) & formata, format * pformat);
      //__pointer(format) get_format(__pointer_array(format) & formata, format * pformat, attribute_flags & eattributea);
      void words_trailing_spaces(string_array & stra, string str);


   } // namespace rich_text


} // namespace user



