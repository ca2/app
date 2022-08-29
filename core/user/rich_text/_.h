// Created by camilo on 2022-08-27 21:36 <3ThomasBorregaardSorensen!!
#pragma once


#include "_constant.h"


namespace user
{


   namespace rich_text
   {

      class document;

      class format_tool;

      class span;

      class line;

      class box;

      bool is_equal_bool(bool b1, bool b2);

      bool is_similar_font_size(double d1, double d2);

      void words_trailing_spaces(string_array & stra, string str);

      index sel_line(const __pointer_array(line) & linea, index iSel);

      index sel_line_x666(__pointer_array(line) & linea, index iSel, double & x);

      index line_caret_x(__pointer_array(line) & linea, index iSel, double & x);

      index sel_char(__pointer_array(line) & linea, index iSel);

      string line_text(line & line);

      string text(const __pointer_array(span) & spana);

      void update_span_cache(__pointer_array(span) & spana);

      ::e_align box_align(__pointer_array(span) & spana, index iBox);

      bool box_align(__pointer_array(span) & spana, index iBox, ::e_align ealign);

      index find_span(__pointer_array(span) & spana, index iSel);

      index find_char_span(__pointer_array(span) & spana, strsize iChar);

      void align(line * pline, const ::rectangle_f64 & rectangle);

      box * find_box(__pointer_array(line) & linea, index iSel);

      string layout_text(const __pointer_array(line) & linea);


   } // namespace rich_text


} // namespace user


