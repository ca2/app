//
//  font_sink.hpp
//  nanoui
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 06/04/22 05:05
//  <3 Thomas likes number 5!!
//
#pragma once


////#include "acme/prototype/prototype/object.h"
#include "acme/prototype/collection/string_map.h"


namespace nano2d
{

   class CLASS_DECL_NANOUI font_sink :
      virtual public ::object
   {
   public:
      
      
      string_map < map_base < float, ::write_text::font_pointer > > m_mapSharedFont;
      

      virtual ::write_text::font_pointer get_shared_font(const_char_pointer face, float size);
      
      
   };


} // namespace nano2d



