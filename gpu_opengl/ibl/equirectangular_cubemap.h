// From github:/tristancalderbank/OpenGL-PBR-Renderer/equirectangular_cubemap.h by
// camilo on 2025-09-26 19:53 <3ThomasBorregaardSorensen!!
#pragma once

#include "gpu/ibl/cubemap_framebuffer.h"
#include "bred/gpu/shader.h"
#include "gpu/ibl/equirectangular_cubemap.h"
//#include "gpu/ibl/hdri_cube.h"


namespace gpu_opengl
{


   namespace ibl
   {


      class equirectangular_cubemap :
         virtual public ::gpu::ibl::equirectangular_cubemap
      {
      public:



         equirectangular_cubemap();


         ~equirectangular_cubemap() override;

          ::block embedded_ibl_hdri_cube_vert() override;
         ::block embedded_ibl_hdri_cube_frag() override;



         void compute();


         //unsigned int getCubemapId();


      };


   } // namespace ibl


} // namespace gpu_opengl
