#pragma once


#include "graphics.h"


namespace graphics
{


   class CLASS_DECL_AURA device_context :
      virtual public graphics
   {
   public:


      ::draw2d::graphics_pointer         m_pdraw2dgraphics;


      device_context();
      ~device_context() override;


      virtual bool update_window();


      ::draw2d::graphics_lease on_begin_draw();


   };


} // namespace graphics



