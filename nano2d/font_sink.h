//
//  font_sink.hpp
//  nanoui
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 06/04/22 05:05
//  <3 Thomas likes number 5!!
//
#pragma once


////#include "acme/primitive/primitive/object.h"
#include "acme/primitive/collection/string_map.h"


namespace nano2d
{


   class CLASS_DECL_NANO2D font_sink :
      virtual public ::object
   {
   public:
      
      
      string_map < map < float, ::write_text::font_pointer > > m_mapSharedFont;
      

      virtual ::write_text::font_pointer get_shared_font(const char * face, float size);
      
      
   };


} // namespace nano2d



