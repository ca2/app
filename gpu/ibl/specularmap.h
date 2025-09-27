// From github:/tristancalderbank/OpenGL-PBR-Renderer/SpecularMap.h by
// camilo on 2025-09-26 19:55 <3ThomasBorregaardSorensen!!
#pragma once


//#include "gpu/ibl/brdfconvolutionframebuffer.h"
//#include "gpu/ibl/mipmapcubemapframebuffer.h"
//#include "bred/gpu/shader.h"


namespace gpu
{


   namespace ibl
   {

      /**
       * Computes specular maps to be used for PBR.
       *
       * The pre-filtered environment map has different mip levels for different roughness.
       *
       * The BRDF convolution map is a 2D map of NdotV vs. roughness, that provides F0 scale and F0 bias values.
       */
      class SpecularMap
         :
         virtual public ::particle
      {
      public:


         // prefiltered environment map
         const unsigned int m_uPrefilteredEnvMapMipLevels = 5;
         const unsigned int m_uPrefilteredEnvMapWidth = 128;
         const unsigned int m_uPrefilteredEnvMapHeight = 128;

         const unsigned int m_uEnvironmentCubemapId;

         ::pointer<::gpu::shader> m_pshaderPprefilteredEnvMap;
         ::pointer<MipmapCubemapFramebuffer> m_pprefilteredEnvMapFramebuffer;

         // brdf convolution
         unsigned int m_uBrdfConvolutionMapId;
         const unsigned int m_uBrdfConvolutionMapWidth = 512;
         const unsigned int m_uBrdfConvolutionMapHeight = 512;

         ::pointer<::gpu::shader> m_pshaderBrdfConvolutionShader;
         ::pointer<BrdfConvolutionFramebuffer> m_pbrdfConvolutionFramebuffer;

         ::pointer < ::gpu::FullscreenQuad > m_pfullscreenquad;

         /**
          * Initialize a specular map.
          */
         SpecularMap();


         ~SpecularMap() override;


         virtual void initialize_SpecularMap(const ::string &engineRoot, const unsigned int environmentCubemapId);


         /**
          * Render the pre-filtered environment map.
          */
         virtual void computePrefilteredEnvMap();


         /**
          * Get the GL texture ID of the computed pre-filtered environment cubemap.
          * @return
          */
         //unsigned int getPrefilteredEnvMapId();


         /**
          * Render the BRDF convolution map.
          */
         virtual void computeBrdfConvolutionMap();


         /**
          * Get the GL texture ID of the computed BRDF convolution map.
          * @return
          */
         //unsigned int getBrdfConvolutionMapId();


      };


   } // namespace ibl


} // namespace gpu



