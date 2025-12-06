// From github:/tristancalderbank/OpenGL-PBR-Renderer/equirectangular_cubemap.cpp by
// camilo on 2025-09-26 19:53 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "equirectangular_cubemap.h"
#include "bred/gpu/context.h"
#include "bred/gpu/shader.h"
#include "bred/gpu/texture.h"
#include "cubemap_framebuffer.h"
#include "bred/graphics3d/engine.h"
#include "bred/graphics3d/shape_factory.h"


namespace gpu
{


   namespace ibl
   {


      equirectangular_cubemap::equirectangular_cubemap()
      {


      }


      equirectangular_cubemap::~equirectangular_cubemap()
      {


      }


      ::block equirectangular_cubemap::embedded_ibl_hdri_cube_vert()
      {

         return {};

      }


      ::block equirectangular_cubemap::embedded_ibl_hdri_cube_frag()
      {

         return {};

      }


      void equirectangular_cubemap::initialize_equirectangular_cubemap_with_hdr_on_memory(::gpu::context *pgpucontext,
                                                                       const ::block &block)
      {

         initialize_gpu_context_object(pgpucontext);

         øconstruct(m_pshaderHdri);

         m_pshaderHdri->m_bindingSampler.set(0);
         m_pshaderHdri->m_bindingSampler.m_strUniform = "hdri";
         m_pshaderHdri->m_bDisableDepthTest = true;
         m_pshaderHdri->m_ecullmode = ::gpu::e_cull_mode_none;
         m_pshaderHdri->m_propertiesPushShared.set_properties(
            ::gpu_properties<::gpu::ibl::equirectangular_cubemap::push_constants>());

         m_pgpucontext->layout_push_constants(m_pshaderHdri->m_propertiesPushShared, false);

         m_pshaderHdri->initialize_shader_with_block(
            m_pgpucontext->m_pgpurenderer,
            embedded_ibl_hdri_cube_vert(),            
            embedded_ibl_hdri_cube_frag(), {}, {},
            pgpucontext->input_layout(::gpu_properties<::graphics3d::shape_factory::Vertex>()));

         øconstruct(m_ptextureHdr);

         m_ptextureHdr->initialize_hdr_texture_on_memory(m_pgpucontext->m_pgpurenderer, block);

         øconstruct(m_pframebuffer);

         m_pframebuffer->m_strSamplerUniform = "hdri";

         m_pframebuffer->initialize_cubemap_framebuffer(m_pgpucontext, m_uCubemapWidth, m_uCubemapHeight);

         m_prenderableCube = m_pgpucontext->m_pengine->shape_factory()->create_cube_001(m_pgpucontext, 2.f);

      }


      void equirectangular_cubemap::compute()
      {
        

      }


   } // namespace ibl


} // namespace gpu



BEGIN_GPU_PROPERTIES(::gpu::ibl::equirectangular_cubemap::push_constants)
GPU_PROPERTY("model", ::gpu::e_type_mat4)
GPU_PROPERTY("view", ::gpu::e_type_mat4)
GPU_PROPERTY("projection", ::gpu::e_type_mat4)
//GPU_PROPERTY("faceIndex", ::gpu::e_type_int)
GPU_PROPERTY("sampler:hdri", ::gpu::e_type_int)
END_GPU_PROPERTIES()




