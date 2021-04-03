// Created by camilo 
// Recreated by camilo 2021-02-10 <3TBS_!!
#pragma once


namespace write_text
{


   class font_list;
   class font;
   using font_pointer = __pointer(font);
   using font_pointer_array = __pointer_array(font);


} // namespace write_text


enum enum_draw_text
{

   e_draw_text_none,
   e_draw_text_no_prefix,
   e_draw_text_word_break,
   e_draw_text_path_ellipsis,
   e_draw_text_end_ellipsis,
   e_draw_text_single_line,
   e_draw_text_expand_tabs,

};


DECLARE_ENUMERATION(e_draw_text, enum_draw_text);


#include "text.h"

#include "text_out.h"

#include "draw_text.h"


namespace write_text
{


   using text_out_shape = _shape < text_out, e_shape_text_out >;
   using draw_text_shape = _shape < draw_text, e_shape_draw_text >;


} // namespace write_text


template < >
inline ___shape* __new_shape(const ::write_text::text_out& textout)
{

   return new ::write_text::text_out_shape(textout);

}


template < >
inline ___shape* __new_shape(const ::write_text::draw_text& drawtext)
{

   return new ::write_text::draw_text_shape(drawtext);

}


#include "bounding_rect.h"

#include "contains.h"

#include "font.h"

//#include "text_box.h"

#include "font_enumeration.h"

#include "font_department.h"

//#include "aura/user/item.h"

//#include "font_list.h"

#include "write_text.h"





