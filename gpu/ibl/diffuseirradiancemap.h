// From github:/tristancalderbank/OpenGL-PBR-Renderer/DiffuseIrradianceMap.h by
// camilo on 2025-09-26 19:53 <3ThomasBorregaardSorensen!!
#pragma once

//#include <memory>

// #include "gpu/ibl/cubemapframebuffer.h"
// #include "bred/gpu/shader.h"
//

namespace gpu
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
         virtual public ::particle
      {
      public:


         const unsigned int m_uDiffuseIrradianceMapWidth = 32;
         const unsigned int m_uDiffuseIrradianceMapHeight = 32;

         const unsigned int m_uEnvironmentCubemapId;

         ::pointer<::gpu::shader> m_pshaderDiffuseIrradiance;
         ::pointer<CubemapFramebuffer> m_pdiffuseIrradianceFramebuffer;
         ::pointer<::gpu::Cube> m_pgpucube;

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
         virtual void compute();


         /**
          * Get the GL texture ID of the computed cubemap.
          * @return
          */
         //unsigned int getCubemapId();

      };


   } // namespace ibl


} // namespace gpu
