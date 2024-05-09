// Created by camilo on 2022-08-27 21:36 <3ThomasBorregaardSorensen!!
#pragma once


#include "_constant.h"
//#include "acme/primitive/geometry2d/_geometry2d.h"


namespace user
{


   namespace rich_text
   {

      class format_tool;

      class span;

      class line;

      class box;

      class format;

      class format_host;

      class selection;

      bool is_equal_bool(bool b1, bool b2);

      bool is_similar_font_size(double d1, double d2);

      void words_trailing_spaces(string_array & stra, string str);

      ::collection::index sel_line(const pointer_array < line > & linea, ::collection::index iSel);

      ::collection::index sel_line_x666(pointer_array < line > & linea, ::collection::index iSel, double & x);

      ::collection::index line_caret_x(pointer_array < line > & linea, ::collection::index iSel, double & x);

      ::collection::index sel_char(pointer_array < line > & linea, ::collection::index iSel);

      string line_text(line & line);

      string text(const pointer_array < span > & spana);

      void update_span_cache(pointer_array < span > & spana);

      ::e_align box_align(pointer_array < span > & spana, ::collection::index iBox);

      bool box_align(pointer_array < span > & spana, ::collection::index iBox, ::e_align ealign);

      ::collection::index find_span(pointer_array < span > & spana, ::collection::index iSel);

      ::collection::index find_char_span(pointer_array < span > & spana, strsize iChar);

//      void align(line * pline, const ::rectangle_f64 & rectangle);
//
      box * find_box(pointer_array < line > & linea, ::collection::index iSel);

      string layout_text(const pointer_array < line > & linea);


   } // namespace rich_text


} // namespace user


