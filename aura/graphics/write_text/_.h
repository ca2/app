// Created by camilo 
// Recreated by camilo 2021-02-10 <3TBS_!!
#pragma once


namespace write_text
{


   struct font_descriptor
   {

      string      m_strFace;
      float       m_fSize;

   };

   class font_list;
   class font;
   using font_pointer = __pointer(font);
   using font_pointer_array = __pointer_array(font);


} // namespace write_text




#include "text.h"

#include "text_out.h"

#include "text_out_array.h"

#include "draw_text.h"


#include "acme/primitive/geometry2d/_geometry2d.h"


#include "aura/graphics/draw2d/path.h"


#include "aura/graphics/draw2d/region.h"


template < >
CLASS_DECL_AURA __pointer(___shape< ::draw2d::path>) __create_shape(const ::write_text::text_out & textout, holdee < ::draw2d::path>);

template < >
CLASS_DECL_AURA __pointer(___shape< ::draw2d::path>) __create_shape(const ::write_text::draw_text & drawtext, holdee < ::draw2d::path>);


template < >
CLASS_DECL_AURA __pointer(___shape< ::draw2d::region>) __create_shape(const ::write_text::text_out & textout, holdee < ::draw2d::region>);

template < >
CLASS_DECL_AURA __pointer(___shape< ::draw2d::region>) __create_shape(const ::write_text::draw_text & drawtext, holdee < ::draw2d::region>);




#include "bounding_rect.h"

#include "contains.h"

#include "font.h"

#include "font_enumeration_item.h"

#include "font_enumeration.h"

#include "fonts.h"

#include "text_box.h"

#include "font_list_item.h"

#include "font_list_data.h"

#include "write_text.h"



