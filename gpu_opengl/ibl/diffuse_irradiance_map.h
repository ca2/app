// From github:/tristancalderbank/OpenGL-PBR-Renderer/diffuse_irradiance_map.h by
// camilo on 2025-09-26 19:53 <3ThomasBorregaardSorensen!!
#pragma once

//#include <memory>

#include "gpu/ibl/diffuse_irradiance_map.h"
#include "gpu_opengl/ibl/cubemap_framebuffer.h"
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
      class CLASS_DECL_GPU_OPENGL diffuse_irradiance_map :
         virtual public ::gpu::ibl::diffuse_irradiance_map
      {
      public:

         // const unsigned int diffuse_irradiance_mapWidth = 32;
         // const unsigned int diffuse_irradiance_mapHeight = 32;
         //
         // const unsigned int environmentCubemapId;
         //
         // ::pointer<Shader> diffuseIrradianceShader;
         // ::pointer<cubemap_framebuffer> diffuseIrradianceFramebuffer;


         /**
          * Initialize a diffuse irradiance map.
          * @param hdriPath path to an .hdr image in equirectangular projection format
          */
         diffuse_irradiance_map();


         ~diffuse_irradiance_map() override;




        ::block embedded_diffuse_irradiance_vert() override;
        ::block embedded_diffuse_irradiance_frag() override;

         // void initialize_diffuse_irradiance_map(
         //    ::gpu::renderer * pgpurenderer,
         //    unsigned int uEnvironmentCubemapId) override;

         /**
          * Render the diffuse irradiance map.
          */
         void compute() override;


         /**
          * Get the GL texture ID of the computed cubemap.
          * @return
          */

         unsigned int getCubemapId();


      };


   } // namespace ibl


} // namespace gpu_opengl
