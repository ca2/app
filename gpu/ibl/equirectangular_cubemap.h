// From github:/tristancalderbank/OpenGL-PBR-Renderer/equirectangular_cubemap.h by
// camilo on 2025-09-26 19:53 <3ThomasBorregaardSorensen!!
#pragma once

// #include "gpu/ibl/cubemap_framebuffer.h"
// #include "bred/gpu/shader.h"
// #include "gpu/ibl/hdri_cube.h"
#include "bred/gpu/context_object.h"
//#include "bred/gpu/context_object.h"


namespace gpu
{


   namespace ibl
   {
      /**
       * A cubemap texture created from an equirectangular image.
       */
      class CLASS_DECL_GPU equirectangular_cubemap : 
         virtual public ::gpu::context_object
      {
      public:


         const unsigned int m_uCubemapWidth = 512;
         const unsigned int m_uCubemapHeight = 512;

         ::pointer<::gpu::shader>            m_pshaderHdri;
         ::pointer<::gpu::ibl::hdri_cube>    m_phdricube;
         //::pointer<::graphics3d::skybox>   m_pskybox;
         ::pointer<cubemap_framebuffer>      m_pframebuffer;
         


         /**
          * Initialize an equirectangular_cubemap.
          * @param hdriPath path to an .hdr image in equirectangular projection format
          */
         equirectangular_cubemap();


         ~equirectangular_cubemap() override;

         virtual ::block embedded_ibl_hdri_cube_vert();
         virtual ::block embedded_ibl_hdri_cube_frag();

         //virtual void initialize_equirectangular_cubemap(::gpu::context * pgpucontext, const ::file::path & pathHdri);
         /// it uses current skybox renderable in pscenebase
         //virtual void initialize_equirectangular_cubemap(::gpu::context * pgpucontext, ::graphics3d::skybox * pskybox);
         //virtual void initialize_equirectangular_cubemap_with_hdr(::gpu::context *pgpucontext, const ::file::path & pathHdri);
         virtual void initialize_equirectangular_cubemap_with_hdr_on_memory(::gpu::context *pgpucontext, const ::block & block);



         /**
          * Render the equirectangular cubemap.
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
