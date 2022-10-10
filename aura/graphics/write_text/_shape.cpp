//
// Created by camilo on 30/12/2021 19:05 BRT <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "acme/primitive/geometry2d/_geometry2d.h"
#include "aura/graphics/draw2d/path.h"
#include "_shape.h"
#include "font.h"
#include "acme/primitive/geometry2d/_defer.h"


template < >
CLASS_DECL_AURA ::pointer<___shape<::draw2d::path>> __create_shape(const ::write_text::text_out& textout, holdee<::draw2d::path>)
{

   return __new(::draw2d::text_out_shape<::draw2d::path>(textout));

}


template < >
CLASS_DECL_AURA ::pointer<___shape<::draw2d::path>> __create_shape(const ::write_text::draw_text& drawtext, holdee<::draw2d::path>)
{

   return __new(::draw2d::draw_text_shape<::draw2d::path>(drawtext));

}



