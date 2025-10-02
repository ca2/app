// From github:/tristancalderbank/OpenGL-PBR-Renderer/equirectangular_cubemap.h by
// camilo on 2025-09-26 19:53 <3ThomasBorregaardSorensen!!
#pragma once

#include "gpu/ibl/cubemap_framebuffer.h"
#include "bred/gpu/shader.h"
#include "gpu/ibl/equirectangular_cubemap.h"
#include "gpu/ibl/hdri_cube.h"


namespace gpu_opengl
{


   namespace ibl
   {
      /**
       * A cubemap texture created from an equirectangular image.
       */
      class equirectangular_cubemap :
         virtual public ::gpu::ibl::equirectangular_cubemap
      {
      public:


         // const unsigned int cubemapWidth = 512;
         // const unsigned int cubemapHeight = 512;
         //
         // ::pointer<Shader> hdriShader;
         // ::pointer<hdri_cube> hdri_cube;
         // ::pointer<cubemap_framebuffer> framebuffer;

         /**
          * Initialize an equirectangular_cubemap.
          * @param hdriPath path to an .hdr image in equirectangular projection format
          */
         equirectangular_cubemap();


         ~equirectangular_cubemap() override;

          ::block embedded_ibl_hdri_cube_vert() override;
         ::block embedded_ibl_hdri_cube_frag() override;



         //virtual void initialize_equirectangular_cubemap(const ::string &engineRoot, const ::string &hdriPath);


         /**
          * Render the equirectangular cubemap.
          */
         void compute();


         /**
          * Get the GL texture ID of the computed cubemap.
          * @return
          */
         unsigned int getCubemapId();


      };


   } // namespace ibl


} // namespace gpu_opengl
