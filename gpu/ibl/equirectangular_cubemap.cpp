// From github:/tristancalderbank/OpenGL-PBR-Renderer/equirectangular_cubemap.cpp by
// camilo on 2025-09-26 19:53 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "equirectangular_cubemap.h"
#include "bred/gpu/context.h"
#include "bred/gpu/shader.h"
#include "bred/gpu/texture.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

//#include "gpu::gltf.h"
//#include "timer.h"
#include "cubemap_framebuffer.h"
#include "hdri_cube.h"
#include "bred/graphics3d/engine.h"
#include "bred/graphics3d/skybox.h"


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


      //void equirectangular_cubemap::initialize_equirectangular_cubemap(::gpu::context * pgpucontext,  const ::file::path & pathHdri)
      //void equirectangular_cubemap::initialize_equirectangular_cubemap(::gpu::context * pgpucontext,  ::graphics3d::skybox * pskybox)
      void equirectangular_cubemap::initialize_equirectangular_cubemap_with_hdr_on_memory(::gpu::context *pgpucontext,
                                                                       const ::block &block)
      {


         initialize_gpu_context_object(pgpucontext);

         // ::file::path pathHdriVertexShader = "matter://shaders/ibl_hdri_cube.vert";
         // ::file::path pathHdriFragmentShader = "matter://shaders/ibl_hdri_cube.frag";

         øconstruct(m_pshaderHdri);

         //m_pshaderHdri->m_bindingUbo.set(0);
         //m_pshaderHdri->m_bindingUbo.m_strUniform = "ubo";

         m_pshaderHdri->m_bindingSampler.set(0);
         m_pshaderHdri->m_bindingSampler.m_strUniform = "hdri";
         m_pshaderHdri->m_bDisableDepthTest = true;
         m_pshaderHdri->m_propertiesPushShared.set_properties(
            ::gpu_properties<::gpu::model_view_projection_hdriSampler>());
         m_pgpucontext->layout_push_constants(m_pshaderHdri->m_propertiesPushShared);
         m_pshaderHdri->initialize_shader_with_block(
            m_pgpucontext->m_pgpurenderer,
            embedded_ibl_hdri_cube_vert(),            
            embedded_ibl_hdri_cube_frag(), {}, {},
            pgpucontext->input_layout(::gpu_properties<::gpu::position3>()));

         øconstruct(m_phdricube);

         m_phdricube->initialize_hdri_cube_with_hdr_on_memory(
            m_pgpucontext->m_pgpurenderer,
            block);

         //auto pscene = pgpucontext->m_pengine->m_pimmersionlayer->m_pscene;
//m_pskybox = pskybox;
         //m_pskybox->initialize_sky_box(pscene, pathHdri);
         øconstruct(m_pframebuffer);

         m_pframebuffer->m_strSamplerUniform = "hdri";

         m_pframebuffer->initialize_cubemap_framebuffer(m_pgpucontext, m_uCubemapWidth, m_uCubemapHeight);


      }


      void equirectangular_cubemap::compute()
      {
         //Timer timer;

         // floating_matrix4 model = gpu::gltf::mIndentity4;
         // floating_matrix4 cameraAngles[] =
         // {
         //    glm::lookAt(gpu::gltf::origin, gpu::gltf::unitX, -gpu::gltf::unitY),
         //    glm::lookAt(gpu::gltf::origin, -gpu::gltf::unitX, -gpu::gltf::unitY),
         //    glm::lookAt(gpu::gltf::origin, gpu::gltf::unitY, gpu::gltf::unitZ),
         //    glm::lookAt(gpu::gltf::origin, -gpu::gltf::unitY, -gpu::gltf::unitZ),
         //    glm::lookAt(gpu::gltf::origin, gpu::gltf::unitZ, -gpu::gltf::unitY),
         //    glm::lookAt(gpu::gltf::origin, -gpu::gltf::unitZ, -gpu::gltf::unitY)
         // };
         // floating_matrix4 projection = glm::perspective(
         //    glm::radians(90.0f), // 90 degrees to cover one face
         //    1.0f, // its a square
         //    0.1f,
         //    2.0f);
         //
         // glViewport(0, 0, cubemapWidth, cubemapHeight);
         //
         // // render the equirectangular HDR texture to a cubemap
         // framebuffer->bind();
         // hdriShader->use();
         //
         // // render to each side of the cubemap
         // for (auto i = 0; i < 6; i++)
         // {
         //    hdriShader->setModelViewProjectionMatrices(model, cameraAngles[i], projection);
         //    framebuffer->setCubeFace(i);
         //
         //    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
         //    hdri_cube->Draw(*hdriShader);
         // }
         //
         // framebuffer->generateMipmap();
         //
         // timer.logDifference("Rendered equirectangular cubemap");
         //
         // glBindFramebuffer(GL_FRAMEBUFFER, 0);
      }


      // unsigned int equirectangular_cubemap::getCubemapId()
      // {
      //    return m_pframebuffer->getCubemapTextureId();
      // }

      



   } // namespace ibl


} // namespace gpu
