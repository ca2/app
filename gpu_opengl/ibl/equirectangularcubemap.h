// From github:/tristancalderbank/OpenGL-PBR-Renderer/EquirectangularCubemap.h by
// camilo on 2025-09-26 19:53 <3ThomasBorregaardSorensen!!
#pragma once

#include "gpu/ibl/cubemapframebuffer.h"
#include "bred/gpu/shader.h"
#include "gpu/ibl/equirectangularcubemap.h"
#include "gpu/ibl/hdricube.h"


namespace gpu_opengl
{


   namespace ibl
   {
      /**
       * A cubemap texture created from an equirectangular image.
       */
      class EquirectangularCubemap :
         virtual public ::gpu::ibl::EquirectangularCubemap
      {
      public:


         // const unsigned int cubemapWidth = 512;
         // const unsigned int cubemapHeight = 512;
         //
         // ::pointer<Shader> hdriShader;
         // ::pointer<HDRICube> hdriCube;
         // ::pointer<CubemapFramebuffer> framebuffer;

         /**
          * Initialize an EquirectangularCubemap.
          * @param hdriPath path to an .hdr image in equirectangular projection format
          */
         EquirectangularCubemap();


         ~EquirectangularCubemap() override;


         virtual void initialize_EquirectangularCubemap(const ::string &engineRoot, const ::string &hdriPath);


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
