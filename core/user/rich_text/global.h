#pragma once


namespace user
{


   namespace rich_text
   {


      bool is_equal_bool(bool b1, bool b2);
      bool is_similar_font_size(double d1, double d2);
      void update_span_cache(pointer_array < span > & spana);
      //void update_span_cache(pointer_array < span > & spana, pointer_array < line > & layouta);
      ::collection::index find_span(pointer_array < span > & spana, ::collection::index iSel);
      ::e_align box_align(pointer_array < span > & spana, ::collection::index iBox);
      bool box_align(pointer_array < span > & spana, ::collection::index iBox, ::e_align ealign);
      ::collection::index find_char_span(pointer_array < span > & spana, character_count iChar);
      box * find_box(pointer_array < line > & span, ::collection::index iSel);
      string layout_text(const pointer_array < line > & span);
      void align(line * pline, const ::double_rectangle & rectangle);

      string line_text(line & line);
      ::collection::index sel_line(const pointer_array < line > & span, ::collection::index iSel);
      ::collection::index sel_line_x666(pointer_array < line > & span, ::collection::index iSel, double & x);
      ::collection::index line_caret_x(pointer_array < line >& span, ::collection::index iSel, double& x);
      ::string as_text(const pointer_array < span > & spana);
      //::pointer<format>get_format(pointer_array < format > & formata, format * pformat);
      //::pointer<format>get_format(pointer_array < format > & formata, format * pformat, attribute_flags & eattributea);
      void words_trailing_spaces(string_array & stra, string str);


   } // namespace rich_text


} // namespace user



