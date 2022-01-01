//
// Created by camilo on 30/12/2021 19:03 BRT <3ThomasBorregaardSorensen!!
//
#pragma once


#include "acme/primitive/geometry2d/shape.h"


#include "text_out.h"
#include "draw_text.h"

#include "bounding_rect.h"
#include "contains.h"


namespace write_text
{


   using text_out_shape = _shape < text_out, e_shape_text_out >;
   using draw_text_shape = _shape < draw_text, e_shape_draw_text >;


} // namespace write_text





