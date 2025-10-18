// From github:/tristancalderbank/OpenGL-PBR-Renderer/specular_map.h by
// camilo on 2025-09-26 19:55 <3ThomasBorregaardSorensen!!
#pragma once


#include "bred/graphics3d/scene_object.h"
#include "bred/gpu/properties.h"

//#include "gpu/ibl/brdfconvolutionframebuffer.h"
//#include "gpu/ibl/mipmap_cubemap_framebuffer.h"
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
      class CLASS_DECL_GPU specular_map :
         virtual public ::graphics3d::scene_object
      {
      public:

         struct specular_env_map_push_constants
         {
            
            ::glm::mat4 model;
            ::glm::mat4 view;
            ::glm::mat4 projection;

            float roughness;
            float padding1;
            float padding2;
            float padding3;
         };


         // prefiltered environment map
         const unsigned int m_uPrefilteredEnvMapMipLevels = 5;
         const unsigned int m_uPrefilteredEnvMapWidth = 128;
         const unsigned int m_uPrefilteredEnvMapHeight = 128;

         //unsigned int m_uEnvironmentCubemapId;

         //::graphics3d::renderable * m_prenderableSkybox = nullptr;

         ::pointer<::gpu::shader> m_pshaderPrefilteredEnvMap;
         ::pointer<mipmap_cubemap_framebuffer> m_pframebufferPrefilteredEnvMap;

         // brdf convolution
         unsigned int m_uBrdfConvolutionMapId;
         const unsigned int m_uBrdfConvolutionMapWidth = 512;
         const unsigned int m_uBrdfConvolutionMapHeight = 512;

         ::pointer<::gpu::shader> m_pshaderBrdfConvolution;
         ::pointer<brdf_convolution_framebuffer> m_pbrdfconvolutionframebuffer;

         //::pointer < ::gpu::full_screen_quad > m_pfullscreenquad;

          //* Initialize a specular map.
         /**
          */
         specular_map();


         ~specular_map() override;


         virtual ::block embedded_prefiltered_env_map_vert();
         virtual ::block embedded_prefiltered_env_map_frag();

         virtual ::block embedded_brdf_convolution_vert();
         virtual ::block embedded_brdf_convolution_frag();


         //virtual void initialize_specular_map(::gpu::context  * pgpucontext,  const ::scoped_string & scopedstrengineRoot, const unsigned int environmentCubemapId);

         //virtual void initialize_specular_map(::graphics3d::scene_base * pscenebase, ::graphics3d::renderable * prenderableSkybox);
         /// it uses current skybox renderable in pscenebase
         virtual void initialize_specular_map(::graphics3d::scene_base *pscenebase);


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



DECLARE_GPU_PROPERTIES(CLASS_DECL_GPU, ::gpu::ibl::specular_map::specular_env_map_push_constants);
