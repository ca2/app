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
#include "gpu/timer.h"
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


                  ::gpu::Timer timer;

         auto pgpucommandbuffer = m_pgpucontext->beginSingleTimeCommands(m_pgpucontext->m_pgpudevice->graphics_queue());

         using namespace graphics3d;

         floating_matrix4 model = ::graphics3d::mIndentity4;

         floating_matrix4 cameraAngles[] =
         {

            lookAt(origin, unitX, -unitY), // X+ (right)
            lookAt(origin, -unitX, -unitY), // X- (left)
            lookAt(origin, unitY, unitZ), // Y+ (top)
            lookAt(origin, -unitY, -unitZ), // Y- (bottom)
            lookAt(origin, unitZ, -unitY), // Z+ (front)
            lookAt(origin, -unitZ, -unitY) // Z- (back)

         };

         floating_matrix4 projection = m_pgpucontext->m_pengine->perspective(
            90f_degrees, // 90 degrees to cover one face
            1.0f, // its a square
            0.1f,
            2.0f);

         // render the equirectangular HDR texture to a cubemap
         m_pshaderHdri->bind(pgpucommandbuffer, m_pframebuffer->m_ptexture, m_ptextureHdr);

         // render to each side of the cubemap
         for (auto i = 0; i < 6; i++)
         {

            auto impact = cameraAngles[i];

            m_pshaderHdri->setModelViewProjection(model, impact, projection);

            m_pframebuffer->set_cube_face(i, m_pshaderHdri);

            //m_pshaderHdri->set_int("faceIndex", i);

            m_pshaderHdri->push_properties(pgpucommandbuffer);

//            glViewport(0, 0, m_uCubemapWidth, m_uCubemapHeight);

            // glEnable(GL_DEPTH_TEST);
            // GLCheckError("");
            // glDepthMask(GL_TRUE);
            // GLCheckError("");

            //
            // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            // GLCheckError("");
            //
            //
            // glDisable(GL_DEPTH_TEST);
            // GLCheckError("");
            // glDepthMask(GL_FALSE);
            // GLCheckError("");

            ::int_rectangle rectangleViewport;

            rectangleViewport.set(0, 0, m_uCubemapWidth, m_uCubemapHeight);

            m_pgpucontext->set_viewport(pgpucommandbuffer, rectangleViewport);

            m_prenderableCube->bind(pgpucommandbuffer);

            m_prenderableCube->draw(pgpucommandbuffer);

            m_prenderableCube->unbind(pgpucommandbuffer);

         }

         m_pframebuffer->generateMipmap();

         timer.logDifference("Rendered equirectangular cubemap");

         // GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
         //
         // if (status != GL_FRAMEBUFFER_COMPLETE)
         // {
         //
         //    printf("Framebuffer incomplete!\n");
         //
         // }
         //
         // glBindFramebuffer(GL_FRAMEBUFFER, 0);
         // GLCheckError("");


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




