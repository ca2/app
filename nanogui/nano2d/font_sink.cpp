//
//  font_sink.cpp
//  nanogui
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 06/04/22 05:06
//
#include "framework.h"
#include "font_sink.h"
#include "aura/graphics/draw2d/draw2d.h"
#include "nano2d/draw2d_context.h"


namespace nano2d
{


   ::write_text::font_pointer font_sink::get_shared_font(const char * face, float size)
   {
                                                 
       auto fontdescriptor = acmesystem()->m_paurasystem->draw2d()->write_text()->calculate_font_descriptor(face, size);
       
       auto & pfontShared = m_mapSharedFont[fontdescriptor.m_strFace][fontdescriptor.m_fSize];
       
       if(pfontShared)
       {
          
          ASSERT(::is_same(pfontShared->m_fontdescriptor.m_fSize, size, 0.1));
          
          ASSERT(pfontShared->m_fontdescriptor.m_strFace.equals(face));
          
       }
       else
       {
       
          pfontShared = __create < ::write_text::font >();
          
          pfontShared->m_fontdescriptor = fontdescriptor;
          
          __font_face(pfontShared, face);
          
          __font_size(pfontShared, size);
          
          pfontShared->set_modified();
             
       }
       
       return pfontShared;
       
    }


} // namespace nano2d




