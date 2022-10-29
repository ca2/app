#pragma once


#include "acme/primitive/geometry2d/rectangle.h"


namespace write_text
{


   class CLASS_DECL_AURA draw_text :
      virtual public text_out
   {
   public:


      ::rectangle_i32            m_rectangle;
      ::e_align                  m_ealign;
      ::e_draw_text              m_edrawtext;


      draw_text() {  }


   };


} // namespace write_text



