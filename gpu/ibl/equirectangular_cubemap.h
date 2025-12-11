// From github:/tristancalderbank/OpenGL-PBR-Renderer/equirectangular_cubemap.h by
// camilo on 2025-09-26 19:53 <3ThomasBorregaardSorensen!!
#pragma once

// #include "gpu/ibl/cubemap_framebuffer.h"
// #include "bred/gpu/shader.h"
// #include "gpu/ibl/hdri_cube.h"
#include "bred/gpu/context_object.h"
//#include "bred/gpu/context_object.h"
#include "bred/gpu/properties.h"

namespace gpu
{


   namespace ibl
   {


      class CLASS_DECL_GPU equirectangular_cubemap : 
         virtual public ::gpu::context_object
      {
      public:


         
      struct push_constants
         {
         floating_matrix4 model;
         floating_matrix4 view;
         floating_matrix4 projection;

         //int faceIndex;
         int hdri;
         };

         const unsigned int m_uCubemapWidth = 2048;
         const unsigned int m_uCubemapHeight = 2048;

         ::pointer<::gpu::shader>            m_pshaderHdri;
         //::pointer<::gpu::ibl::hdri_cube>    m_phdricube;
         //::pointer<cubemap_framebuffer>      m_pframebuffer;
         ::pointer<::gpu::texture>           m_ptextureCubemap;
         ::pointer<::gpu::texture>           m_ptextureHdr;
         ::pointer<::graphics3d::renderable> m_prenderableCube;


         equirectangular_cubemap();
         ~equirectangular_cubemap() override;

         virtual ::block embedded_ibl_hdri_cube_vert();
         virtual ::block embedded_ibl_hdri_cube_frag();

         

         virtual void initialize_equirectangular_cubemap_with_hdr_on_memory(::gpu::context *pgpucontext, const ::block & block);


         virtual void compute();



      };


   } // namespace ibl


} // namespace gpu



DECLARE_GPU_PROPERTIES(CLASS_DECL_GPU, ::gpu::ibl::equirectangular_cubemap::push_constants)
