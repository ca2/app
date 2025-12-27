//
// Created by camilo on 2025-12-25 20:20 <3ThomasBorregaardSørensen!!
//
#include "framework.h"
#include "context.h"


namespace gpu_opengl
{
   void device::_swap_buffers()
   {

      system()->acme_windowing()->acme_display()->__gl_swap_buffers();

   }


}