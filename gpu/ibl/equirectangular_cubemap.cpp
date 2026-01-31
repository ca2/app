// From github:/tristancalderbank/OpenGL-PBR-Renderer/equirectangular_cubemap.cpp by
// camilo on 2025-09-26 19:53 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "equirectangular_cubemap.h"
#include "bred/gpu/binding.h"
#include "bred/gpu/command_buffer.h"
#include "bred/gpu/context.h"
#include "bred/gpu/context_lock.h"
#include "bred/gpu/debug_scope.h"
#include "bred/gpu/shader.h"
#include "bred/gpu/texture.h"
#include "bred/graphics3d/engine.h"
#include "bred/graphics3d/shape_factory.h"
#include "bred/platform/timer.h"
#include "bred/gpu/device.h"


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

         auto pbindingSampler = m_pshaderHdri->binding();
         pbindingSampler->m_strUniform = "hdri";
         pbindingSampler->m_ebinding = ::gpu::e_binding_sampler2d;
         pbindingSampler->m_iTextureUnit = 0;

         //m_pshaderHdri->binding_slot(0, 0, pbindingSampler);

         m_pshaderHdri->m_bDisableDepthTest = true;
         m_pshaderHdri->m_ecullmode = ::gpu::e_cull_mode_none;

         auto pgpupropertiesVertex = ::gpu_properties<::graphics3d::shape_factory::Vertex>();

         auto pinputlayoutVertex = m_pgpucontext->input_layout(pgpupropertiesVertex);

         m_pshaderHdri->m_propertiesPushShared.set_properties(
            ::gpu_properties<::gpu::ibl::equirectangular_cubemap::push_constants>());

         m_pgpucontext->layout_push_constants(m_pshaderHdri->m_propertiesPushShared, false);

         m_pshaderHdri->initialize_shader_with_block(
            m_pgpucontext->m_pgpurenderer, embedded_ibl_hdri_cube_vert(), embedded_ibl_hdri_cube_frag(), 
            pinputlayoutVertex);

         øconstruct(m_ptextureHdr);

         m_ptextureHdr->m_textureflags.m_bShaderResource = true;

         m_ptextureHdr->initialize_hdr_texture_on_memory(m_pgpucontext, block);

         øconstruct(m_ptextureCubemap);

         ::gpu::texture_attributes textureattributes(::int_rectangle{API_CHANGED_ARGUMENT, m_uCubemapWidth,
                                                                    m_uCubemapHeight});

         textureattributes.set_cubemap_all_mips();

         ::gpu::texture_flags textureflags;

         textureflags.m_bRenderTarget = true;
         textureflags.m_bShaderResource = true;
         textureflags.m_bTransferTarget = true;
         textureflags.m_bTransferSource = true;

         m_ptextureCubemap->initialize_texture(
            m_pgpucontext, 
            textureattributes,
            textureflags);

         m_prenderableCube = m_pgpucontext->m_pengine->shape_factory()->create_cube_001(m_pgpucontext, 2.f);

      }


      void equirectangular_cubemap::compute_equirectangular_cubemap(::gpu::command_buffer * pgpucommandbuffer)
      {

         ::gpu::context_lock lockcontext(m_pgpucontext);

         ::bred::Timer timer;

         //auto pgpucommandbuffer = m_pgpucontext->beginSingleTimeCommands(m_pgpucontext->m_pgpudevice->graphics_queue());

         //::string strDebugScopeCompute;

         //strDebugScopeCompute.format("gpu::ibl::equirectangular_cubemap::compute");

         //::gpu::debug_scope debugscopeCompute(pgpucommandbuffer, strDebugScopeCompute);

         using namespace graphics3d;

         floating_matrix4 model = ::graphics3d::mIndentity4;

         floating_matrix4 cameraAngles[6];

         if (m_pgpucontext->m_eapi == ::gpu::e_api_vulkan || m_pgpucontext->m_eapi == ::gpu::e_api_directx12)
         {

            cameraAngles[0] = lookAt(origin, unitX, -unitY); // X+ (right)
            cameraAngles[1] = lookAt(origin, -unitX, -unitY); // X- (left)
            cameraAngles[2] = lookAt(origin, -unitY, -unitZ); // Y- (bottom)
            cameraAngles[3] = lookAt(origin, unitY, unitZ); // Y+ (top)
            cameraAngles[4] = lookAt(origin, unitZ, -unitY); // Z+ (front)
            cameraAngles[5] = lookAt(origin, -unitZ, -unitY); // Z- (back)

         }
         else
         {

            cameraAngles[0] = lookAt(origin, unitX, -unitY); // X+ (right)
            cameraAngles[1] = lookAt(origin, -unitX, -unitY); // X- (left)
            cameraAngles[2] = lookAt(origin, unitY, unitZ); // Y+ (top)
            cameraAngles[3] = lookAt(origin, -unitY, -unitZ); // Y- (bottom)
            cameraAngles[4] = lookAt(origin, unitZ, -unitY); // Z+ (front)
            cameraAngles[5] = lookAt(origin, -unitZ, -unitY); // Z- (back)

         }

         floating_matrix4 projection = m_pgpucontext->m_pengine->perspective(
            90_f_degrees, // 90 degrees to cover one face
            1.0f, // its a square
            0.1f,
            2.0f);

         m_pgpucontext->m_rectangle.set_size(m_ptextureCubemap->size());

         m_ptextureHdr->set_state(pgpucommandbuffer, ::gpu::e_texture_state_shader_read);

         m_ptextureCubemap->set_current_mip(-1);

         m_ptextureCubemap->set_current_layer(-1);

         m_ptextureCubemap->set_state(pgpucommandbuffer, ::gpu::e_texture_state_color_attachment);

         m_ptextureCubemap->set_current_mip(0);

         for (auto iFace = 0; iFace < 6; iFace++)
         {

            ::string strDebugScopeComputeFace;

            strDebugScopeComputeFace.format("compute face {}", iFace + 1);

            ::gpu::debug_scope debugscopeComputeFace(pgpucommandbuffer, strDebugScopeComputeFace);

            auto impact = cameraAngles[iFace];

            m_ptextureCubemap->set_current_layer(iFace);

            pgpucommandbuffer->begin_render(m_pshaderHdri, m_ptextureCubemap);

            //pgpucommandbuffer->set_source(m_ptextureHdr);

            auto mvp = projection * impact * model;

            m_pshaderHdri->set_matrix4("mvp", mvp);

            m_pshaderHdri->push_properties(pgpucommandbuffer);

            ::int_rectangle rectangleViewport;

            rectangleViewport.set(0, 0, m_uCubemapWidth, m_uCubemapHeight);

            pgpucommandbuffer->set_viewport(rectangleViewport);

            pgpucommandbuffer->set_scissor(rectangleViewport);

            pgpucommandbuffer->set_source(m_ptextureHdr);

            pgpucommandbuffer->draw(m_prenderableCube);

            pgpucommandbuffer->end_render();

         }

         m_ptextureCubemap->generate_mipmap(pgpucommandbuffer);

         m_ptextureCubemap->set_current_mip(-1);

         m_ptextureCubemap->set_current_layer(-1);

         m_ptextureCubemap->set_state(pgpucommandbuffer, ::gpu::e_texture_state_shader_read);

         m_ptextureCubemap->set_ok_flag();

         //m_pgpucontext->endSingleTimeCommands(pgpucommandbuffer);

         timer.logDifference("Rendered equirectangular cubemap");

      }


   } // namespace ibl


} // namespace gpu


BEGIN_GPU_PROPERTIES(::gpu::ibl::equirectangular_cubemap::push_constants)
GPU_PROPERTY("mvp", ::gpu::e_type_mat4)
GPU_PROPERTY("sampler:hdri", ::gpu::e_type_int)
END_GPU_PROPERTIES()



