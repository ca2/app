#pragma once


#include "text_out.h"


namespace write_text
{


   class CLASS_DECL_AURA draw_text :
      virtual public text_out
   {
   public:


      ::int_rectangle            m_rectangle;
      ::e_align                  m_ealign;
      ::e_draw_text              m_edrawtext;


      draw_text() {  }


   };





} // namespace write_text



