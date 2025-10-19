// From github:/tristancalderbank/OpenGL-PBR-Renderer/specular_map.cpp by
// camilo on 2025-09-26 19:55 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "specular_map.h"

#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include "bred/gpu/command_buffer.h"
#include "bred/gpu/context_lock.h"
#include "bred/gpu/texture.h"
#include "gpu/full_screen_quad.h"
#include "bred/gpu/device.h"
#include "bred/gpu/types.h"
//#include "constants.h"
//#include "cube.h"
//#include "fullscreenquad.h"
//#include "timer.h"
#include "brdf_convolution_framebuffer.h"
#include "bred/gpu/context.h"
#include "bred/gpu/shader.h"
#include "gpu/ibl/mipmap_cubemap_framebuffer.h"


namespace gpu
{


   namespace ibl
   {


      specular_map::specular_map()
      {


      }


      specular_map::~specular_map()
      {

      }



      ::block specular_map::embedded_prefiltered_env_map_vert()
      {

         return {};

      }


      ::block specular_map::embedded_prefiltered_env_map_frag()
      {

return {};

      }

      ::block specular_map::embedded_brdf_convolution_vert()
      {

return {};

      }


      ::block specular_map::embedded_brdf_convolution_frag()
      {

return {};

      }




      void specular_map::initialize_specular_map(::graphics3d::scene_base * pscenebase)
         //,
      //::graphics3d::renderable * prenderableSkybox)
         //const ::scoped_string & scopedstrengineRoot, const unsigned int uEnvironmentCubemapId)
      {

         initialize_scene_object(pscenebase);

         //m_uEnvironmentCubemapId = uEnvironmentCubemapId;

         //m_prenderableSkybox = prenderableSkybox;



//         ;

         // // pre-filtered env map
         // ::file::path pathPrefilteredEnvMapVertexShader = "matter://shaders/ibl_specularenv.vert";
         // ::file::path pathPrefilteredEnvMapFragmentShader = "matter://shaders/ibl_specularenv.frag";
         //
         øconstruct(m_pshaderPrefilteredEnvMap);

         auto blockVert = embedded_prefiltered_env_map_vert();

         auto blockFrag = embedded_prefiltered_env_map_frag();

         auto pgpupropertiesPosition = ::gpu_properties<::gpu::position3>();

         auto pinputlayoutPosition = m_pgpucontext->input_layout(pgpupropertiesPosition);

         m_pshaderPrefilteredEnvMap->m_ecullmode = ::gpu::e_cull_mode_none;
         m_pshaderPrefilteredEnvMap->m_bDisableDepthTest = true;
         m_pshaderPrefilteredEnvMap->m_propertiesPushShared.set_properties(::gpu_properties<specular_env_map_push_constants>());
         m_pgpucontext->layout_push_constants(m_pshaderPrefilteredEnvMap->m_propertiesPushShared);
         m_pshaderPrefilteredEnvMap->initialize_shader_with_block(
            m_pgpucontext->m_pgpurenderer,
            blockVert,
            blockFrag, {}, {},
            pinputlayoutPosition);

         m_pshaderPrefilteredEnvMap->m_bindingCubeSampler.set(0);
         m_pshaderPrefilteredEnvMap->m_bindingCubeSampler.m_strUniform = "environmentCubemap";


         øconstruct(m_pframebufferPrefilteredEnvMap);
         m_pframebufferPrefilteredEnvMap->initialize_mipmap_cubemap_framebuffer(
            m_pscene, m_uPrefilteredEnvMapWidth, m_uPrefilteredEnvMapHeight);

         // // BRDF convolution
         // ::file::path pathBrdfConvolutionVertexShader= "matter://shaders/ibl_brdfconvolution.vert";
         // ::file::path pathBrdfConvolutionFragmentShader = "matter://shaders/ibl_brdfconvolution.frag";

         øconstruct(m_pshaderBrdfConvolution);

         m_pshaderBrdfConvolution->m_bDisableDepthTest = true;
         m_pshaderBrdfConvolution->m_bEnableBlend = false;
         m_pshaderBrdfConvolution->m_ecullmode = ::gpu::e_cull_mode_none;

         m_pshaderBrdfConvolution->initialize_shader_with_block(
            m_pgpucontext->m_pgpurenderer, embedded_brdf_convolution_vert(), embedded_brdf_convolution_frag(), {}, {},
            m_pgpucontext->input_layout(::gpu_properties<::gpu::position2_uv>()));

         øconstruct(m_pbrdfconvolutionframebuffer);

         m_pbrdfconvolutionframebuffer->initialize_BrdfConvolutionFramebuffer(
            m_pscene, m_uBrdfConvolutionMapWidth, m_uBrdfConvolutionMapHeight);

      }


      void specular_map::computePrefilteredEnvMap(::gpu::command_buffer *pgpucommandbuffer)
      {
         // Timer timer;
         //
         // glm::mat4 model = constants::mIndentity4;
         // glm::mat4 cameraAngles[] =
         // {
         //    glm::lookAt(constants::origin, constants::unitX, -constants::unitY),
         //    glm::lookAt(constants::origin, -constants::unitX, -constants::unitY),
         //    glm::lookAt(constants::origin, constants::unitY, constants::unitZ),
         //    glm::lookAt(constants::origin, -constants::unitY, -constants::unitZ),
         //    glm::lookAt(constants::origin, constants::unitZ, -constants::unitY),
         //    glm::lookAt(constants::origin, -constants::unitZ, -constants::unitY)
         // };
         // glm::mat4 projection = glm::perspective(
         //    glm::radians(90.0f), // 90 degrees to cover one face
         //    1.0f, // its a square
         //    0.1f,
         //    2.0f);
         //
         // auto cube = Cube();
         // prefilteredEnvMapFramebuffer->bind();
         // prefilteredEnvMapShader->use();
         // prefilteredEnvMapShader->setInt("environmentCubemap", 0);
         //
         // for (auto mipLevel = 0; mipLevel < prefilteredEnvMapMipLevels; mipLevel++)
         // {
         //    prefilteredEnvMapFramebuffer->setMipLevel(mipLevel);
         //
         //    glViewport(0, 0, prefilteredEnvMapFramebuffer->getWidth(), prefilteredEnvMapFramebuffer->getHeight());
         //
         //    // each mip level has increasing roughness
         //    float roughness = (float)mipLevel / (float)(prefilteredEnvMapMipLevels - 1);
         //    prefilteredEnvMapShader->setFloat("roughness", roughness);
         //
         //    // render to each side of the cubemap
         //    for (auto i = 0; i < 6; i++)
         //    {
         //       prefilteredEnvMapShader->setModelViewProjectionMatrices(model, cameraAngles[i], projection);
         //       prefilteredEnvMapFramebuffer->setCubeFace(i);
         //
         //       glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
         //
         //       glBindTexture(GL_TEXTURE_CUBE_MAP, environmentCubemapId);
         //       cube.Draw();
         //    }
         // }
         //
         // timer.logDifference("Rendered specular pre-filtered environment map");
         //
         // glBindFramebuffer(GL_FRAMEBUFFER, 0);
      }


      // unsigned int specular_map::getPrefilteredEnvMapId()
      // {
      //    return prefilteredEnvMapFramebuffer->getCubemapTextureId();
      // }
      //

      void specular_map::computeBrdfConvolutionMap()
      {

         
         // Timer timer;

         ::gpu::context_lock contextlock(m_pgpucontext);

         auto pcommandbuffer = m_pgpucontext->beginSingleTimeCommands(m_pgpucontext->m_pgpudevice->graphics_queue());

         m_pgpucontext->start_debug_happening(pcommandbuffer, "computeBrdfConvolutionMap");

         auto pfullscreenquad = øcreate<::gpu::full_screen_quad>();

         pfullscreenquad->initialize_full_screen_quad(m_pgpucontext);
         // m_pbrdfconvolutionframebuffer->bind();

         //     auto pskybox = m_pscene->current_skybox();

         //// auto prenderable = pskybox->m_prenderable;

         // auto ptexture = pskybox->m_ptexture;

         // m_pshaderBrdfConvolution->bind(m_pbrdfconvolutionframebuffer->m_ptexture, ptexture);
         m_pshaderBrdfConvolution->bind(nullptr, m_pbrdfconvolutionframebuffer->m_ptexture);
         // m_pshaderPrefilteredEnvMap->set_int("environmentCubemap", 0);

         // glViewport(0, 0, m_uBrdfConvolutionMapWidth, m_uBrdfConvolutionMapHeight);
         // GLCheckError("");
         // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
         // GLCheckError("");
         pcommandbuffer->set_viewport(m_pbrdfconvolutionframebuffer->m_ptexture->m_rectangleTarget);


         auto colorClear = ::argb(0.625f, 0.125f, 0.25f, 0.375f);

         m_pgpucontext->clear(m_pbrdfconvolutionframebuffer->m_ptexture, colorClear);

         if (1)
         {
            pfullscreenquad->bind(pcommandbuffer);
            pfullscreenquad->draw(pcommandbuffer);
            pfullscreenquad->unbind(pcommandbuffer);
         }

         // GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

         // if (status != GL_FRAMEBUFFER_COMPLETE)
         //{

         //   printf("Framebuffer incomplete!\n");

         //}

         ////timer.logDifference("Rendered specular brdf convolution map");

         // glBindFramebuffer(GL_FRAMEBUFFER, 0);
         // GLCheckError("");
         m_pgpucontext->end_debug_happening(pcommandbuffer);


         // Timer timer;
         //
         // auto fullscreenQuad = FullscreenQuad();
         // brdfConvolutionFramebuffer->bind();
         // brdfConvolutionShader->use();
         //
         // glViewport(0, 0, brdfConvolutionMapWidth, brdfConvolutionMapHeight);
         // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
         // fullscreenQuad.Draw();
         //
         // timer.logDifference("Rendered specular brdf convolution map");
         //
         // glBindFramebuffer(GL_FRAMEBUFFER, 0);
      }

      //
      // unsigned int specular_map::getBrdfConvolutionMapId()
      // {
      //    return brdfConvolutionFramebuffer->getColorTextureId();
      // }


   } // namespace ibl


} // namespace gpu

BEGIN_GPU_PROPERTIES(::gpu::ibl::specular_map::specular_env_map_push_constants)
GPU_PROPERTY("model", ::gpu::e_type_mat4)
GPU_PROPERTY("view", ::gpu::e_type_mat4)
GPU_PROPERTY("projection", ::gpu::e_type_mat4)
GPU_PROPERTY("roughness", ::gpu::e_type_float)
GPU_PROPERTY("padding1", ::gpu::e_type_float)
GPU_PROPERTY("padding2", ::gpu::e_type_float)
GPU_PROPERTY("padding3", ::gpu::e_type_float)
END_GPU_PROPERTIES()
