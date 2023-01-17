//
// Created by camilo on 30/12/2021 19:03 BRT <3ThomasBorregaardSørensen!!
//
#pragma once


#include "acme/primitive/geometry2d/shape.h"


#include "text_out.h"
#include "draw_text.h"

#include "bounding_rect.h"
#include "contains.h"


namespace draw2d
{


   template < typename HOLDEE >
   using text_out_shape = _shape < ::write_text::text_out, e_shape_text_out, HOLDEE >;

   template < typename HOLDEE >
   using draw_text_shape = _shape < ::write_text::draw_text, e_shape_draw_text, HOLDEE >;


} // namespace draw2d





