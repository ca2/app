#pragma once


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


DECLARE_C_FLAG(e_draw_text, enum_draw_text);


#include "text.h"

#include "text_out.h"

#include "draw_text.h"




using text_out_shape = _shape < ::text_out, e_shape_text_out >;
using draw_text_shape = _shape < ::draw_text, e_shape_draw_text >;




template < >
inline ___shape* __new_shape(const ::text_out& textout)
{

   return new text_out_shape(textout);

}


template < >
inline ___shape* __new_shape(const ::draw_text& drawtext)
{

   return new draw_text_shape(drawtext);

}


#include "bounding_rect.h"


#include "contains.h"



