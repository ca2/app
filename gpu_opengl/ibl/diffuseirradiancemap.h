// From github:/tristancalderbank/OpenGL-PBR-Renderer/DiffuseIrradianceMap.h by
// camilo on 2025-09-26 19:53 <3ThomasBorregaardSorensen!!
#pragma once

//#include <memory>

#include "gpu/ibl/diffuseirradiancemap.h"
#include "gpu_opengl/ibl/cubemapframebuffer.h"
#include "bred/gpu/shader.h"


namespace gpu_opengl
{


   namespace ibl
   {
      /**
       * Computes a diffuse irradiance map from an environment map.
       *
       * The computed map tells you the sum of incoming light from the environment
       * for a particular direction.
       */
      class DiffuseIrradianceMap :
         virtual public ::gpu::ibl::DiffuseIrradianceMap
      {
      public:

         // const unsigned int diffuseIrradianceMapWidth = 32;
         // const unsigned int diffuseIrradianceMapHeight = 32;
         //
         // const unsigned int environmentCubemapId;
         //
         // ::pointer<Shader> diffuseIrradianceShader;
         // ::pointer<CubemapFramebuffer> diffuseIrradianceFramebuffer;


         /**
          * Initialize a diffuse irradiance map.
          * @param hdriPath path to an .hdr image in equirectangular projection format
          */
         DiffuseIrradianceMap();


         ~DiffuseIrradianceMap() override;


         virtual void initialize_DiffuseIrradianceMap(const ::string &engineRoot,
                                                      const unsigned int environmentCubemapId);


         /**
          * Render the diffuse irradiance map.
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
