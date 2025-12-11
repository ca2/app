// From github:/tristancalderbank/OpenGL-PBR-Renderer/diffuse_irradiance_map.h by
// camilo on 2025-09-26 19:53 <3ThomasBorregaardSorensen!!
#pragma once
//#include "bred/gpu/context_object.h"

//#include <memory>

// #include "gpu/ibl/cubemap_framebuffer.h"
// #include "bred/gpu/shader.h"
//

#include "bred/graphics3d/scene_object.h"


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
      class CLASS_DECL_GPU diffuse_irradiance_map :
         virtual public ::graphics3d::scene_object
      {
      public:


         const unsigned int m_udiffuse_irradiance_mapWidth = 32;
         const unsigned int m_udiffuse_irradiance_mapHeight = 32;

         //unsigned int m_uEnvironmentCubemapId;

         //::graphics3d::renderable * m_prenderableSkybox = nullptr;

         ::pointer<::gpu::shader> m_pshaderDiffuseIrradiance;
         //::pointer<::gpu::ibl::cubemap_framebuffer> m_pframebufferDiffuseIrradiance;
         ::pointer < ::gpu::texture > m_ptextureDiffuseIrradianceCubemap;
         //::pointer<::gpu::cube> m_pgpucube;

         /**
          * Initialize a diffuse irradiance map.
          * @param hdriPath path to an .hdr image in equirectangular projection format
          */
         diffuse_irradiance_map();


         ~diffuse_irradiance_map() override;


         virtual ::block embedded_diffuse_irradiance_vert();
         virtual ::block embedded_diffuse_irradiance_frag();


         // virtual void initialize_diffuse_irradiance_map(
         //    ::gpu::renderer * pgpurenderer,
         //    unsigned int uEnvironmentCubemapId);

         //virtual void initialize_diffuse_irradiance_map(
         //   ::graphics3d::scene_base * pscenebase,
         //   ::graphics3d::renderable * prenderableSkybox);
         /// it uses current skybox renderable in pscenebase
         virtual void initialize_diffuse_irradiance_map(::graphics3d::scene_base *pscenebase);
         

         //    ::graphics3d::renderable * prenderableSkybox);
         /**
          * Render the diffuse irradiance map.
          */
         virtual void computeIrradianceMap(::gpu::command_buffer * pgpucommandbuffer);


         /**
          * Get the GL texture ID of the computed cubemap.
          * @return
          */
         //unsigned int getCubemapId();

      };


   } // namespace ibl


} // namespace gpu
