//
// Created by camilo on 30/12/2021 19:05 BRT <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "acme/primitive/geometry2d/_geometry2d.h"
#include "_shape.h"
#include "font.h"
#include "acme/primitive/geometry2d/_defer.h"


template < >
CLASS_DECL_AURA __pointer(___shape) __create_shape(const ::write_text::text_out& textout)
{

   return __new(::write_text::text_out_shape(textout));

}


template < >
CLASS_DECL_AURA __pointer(___shape) __create_shape(const ::write_text::draw_text& drawtext)
{

   return __new(::write_text::draw_text_shape(drawtext));

}


