#pragma once


#include "acme/graphics/image/pixmap.h"


namespace gpu
{


   class CLASS_DECL_AURA cpu_buffer :
      virtual public ::object
   {
   public:

      ::memory          m_memory;
      ::pixmap          m_pixmap;


      cpu_buffer();
      ~cpu_buffer() override;

      virtual void gpu_read();
      virtual void gpu_write();
      

   };


} // namespace gpu



