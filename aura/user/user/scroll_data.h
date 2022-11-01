#pragma once


#include "acme/primitive/primitive/element.h"


namespace user
{


   class scroll_bar;


   class CLASS_DECL_AURA scroll_data :
      virtual public ::particle
   {
   public:


      ::i32          m_iPage;
      ::i32          m_iLine;
      bool           m_bScroll;
      i32            m_iWidth;
      bool           m_bScrollEnable;


   };

  
} // namespace user



