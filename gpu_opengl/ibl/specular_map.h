// From github:/tristancalderbank/OpenGL-PBR-Renderer/specular_map.h by
// camilo on 2025-09-26 19:55 <3ThomasBorregaardSorensen!!
#pragma once


//#include "gpu/ibl/brdf_convolution_framebuffer.h"
//#include "gpu/ibl/mipmap_cubemap_framebuffer.h"
#include "bred/gpu/shader.h"
#include "gpu/ibl/specular_map.h"


namespace gpu_opengl
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
      class CLASS_DECL_GPU_OPENGL specular_map
         :
         virtual public ::gpu::ibl::specular_map
      {
      public:


         // // prefiltered environment map
         // const ::u32 prefilteredEnvMapMipLevels = 5;
         // const ::u32 prefilteredEnvMapWidth = 128;
         // const ::u32 prefilteredEnvMapHeight = 128;
         //
         // const ::u32 environmentCubemapId;

         // ::pointer<::gpu::shader> m_pshaderPprefilteredEnvMap;
         // ::pointer<mipmap_cubemap_framebuffer> m_pprefilteredEnvMapFramebuffer;
         //
         // // brdf convolution
         // ::u32 m_uBrdfConvolutionMapId;
         // const ::u32 m_uBrdfConvolutionMapWidth = 512;
         // const ::u32 m_uBrdfConvolutionMapHeight = 512;
         //
         // ::pointer<::gpu::shader> m_pshaderBrdfConvolutionShader;
         // ::pointer<brdf_convolution_framebuffer> m_pshaderBrdfConvolutionFramebuffer;

         /**
          * Initialize a specular map.
          */
         specular_map();


         ~specular_map() override;




         ::memory prefiltered_environment_map_vert_memory() override;
         ::memory prefiltered_environment_map_frag_memory() override;
         ::memory brdf_convolution_vert_memory() override;
         ::memory brdf_convolution_frag_memory() override;


         //virtual void initialize_specular_map(const ::string &engineRoot, const ::u32 environmentCubemapId);


         /**
          * Render the pre-filtered environment map.
          */
         void computePrefilteredEnvMap(::gpu::command_buffer *pgpucommandbuffer) override;


         /**
          * Get the GL texture ID of the computed pre-filtered environment cubemap.
          * @return
          */
//virtual         ::u32 getPrefilteredEnvMapId();


         /**
          * Render the BRDF convolution map.
          */
         void computeBrdfConvolutionMap(::gpu::command_buffer *pgpucommandbuffer) override;


         /**
          * Get the GL texture ID of the computed BRDF convolution map.
          * @return
          */
         //::u32 getBrdfConvolutionMapId();


      };


   } // namespace ibl


} // namespace gpu_opengl
