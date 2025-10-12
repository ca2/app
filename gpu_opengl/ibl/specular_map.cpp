// From github:/tristancalderbank/OpenGL-PBR-Renderer/specular_map.cpp by
// camilo on 2025-09-26 19:55 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "specular_map.h"
#include "brdf_convolution_framebuffer.h"
#include "bred/graphics3d/scene_base.h"
#include "bred/graphics3d/skybox.h"
#include "bred/gpu/command_buffer.h"
#include "bred/gpu/context.h"
#include "bred/gpu/context_lock.h"
#include "gpu_opengl/_gpu_opengl.h"
#include "gpu_opengl/texture.h"
#include "gpu/cube.h"
#include "gpu/gltf/_constant.h"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "gpu/context.h"
//#include "::gpu::gltf.h"
//#include "cube.h"
//#include "fullscreenquad.h"
//#include "timer.h"
#include "mipmap_cubemap_framebuffer.h"
#include "gpu/full_screen_quad.h"

#include "shaders/specularenv.vert.h"
#include "shaders/specularenv.frag.h"
#include "shaders/brdfconvolution.vert.h"
#include "shaders/brdfconvolution.frag.h"


namespace gpu_opengl
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

         return {g_psz_specularenv_vert, sizeof(g_psz_specularenv_vert) - 1};

      }


      ::block specular_map::embedded_prefiltered_env_map_frag()
      {

         return {g_psz_specularenv_frag, sizeof(g_psz_specularenv_frag) - 1};

      }

      ::block specular_map::embedded_brdf_convolution_vert()
      {

         return {g_psz_brdfconvolution_vert, sizeof(g_psz_brdfconvolution_vert) - 1};

      }


      ::block specular_map::embedded_brdf_convolution_frag()
      {

         return {g_psz_brdfconvolution_frag, sizeof(g_psz_brdfconvolution_frag) - 1};

      }


      // void specular_map::initialize_specular_map(const ::string &engineRoot, const unsigned int environmentCubemapId)
      // {
      //
      //    initialize_environmentCubemapId(environmentCubemapId);
      //
      //    // pre-filtered env map
      //    ::string prefilteredEnvMapVertexShaderPath = engineRoot + "/src/ibl/shaders/specularenv.vert";
      //    ::string prefilteredEnvMapFragmentShaderPath = engineRoot + "/src/ibl/shaders/specularenv.frag";
      //
      //    prefilteredEnvMapShader = std::make_unique<Shader>(prefilteredEnvMapVertexShaderPath.c_str(),
      //                                                       prefilteredEnvMapFragmentShaderPath.c_str());
      //    prefilteredEnvMapFramebuffer = std::make_unique<mipmap_cubemap_framebuffer>(
      //       prefilteredEnvMapWidth, prefilteredEnvMapHeight);
      //
      //    // BRDF convolution
      //    ::string brdfConvolutionVertexShaderPath = engineRoot + "/src/ibl/shaders/brdfconvolution.vert";
      //    ::string brdfConvolutionFragmentShaderPath = engineRoot + "/src/ibl/shaders/brdfconvolution.frag";
      //
      //    brdfConvolutionShader = std::make_unique<Shader>(brdfConvolutionVertexShaderPath.c_str(),
      //                                                     brdfConvolutionFragmentShaderPath.c_str());
      //    brdfConvolutionFramebuffer = std::make_unique<brdf_convolution_framebuffer>(
      //       m_uBrdfConvolutionMapWidth, brdfConvolutionMapHeight);
      //
      // }


      void specular_map::computePrefilteredEnvMap()
      {
         //Timer timer;

         ::gpu::context_lock contextlock(m_pgpucontext);


         auto pgpucommandbuffer = m_pgpucontext->beginSingleTimeCommands(m_pgpucontext->graphics_queue());

         glm::mat4 model = ::gpu::gltf::mIndentity4;
         glm::mat4 cameraAngles[] =
         {
            glm::lookAt(::gpu::gltf::origin, ::gpu::gltf::unitX, -::gpu::gltf::unitY),
            glm::lookAt(::gpu::gltf::origin, -::gpu::gltf::unitX, -::gpu::gltf::unitY),
            glm::lookAt(::gpu::gltf::origin, ::gpu::gltf::unitY, ::gpu::gltf::unitZ),
            glm::lookAt(::gpu::gltf::origin, -::gpu::gltf::unitY, -::gpu::gltf::unitZ),
            glm::lookAt(::gpu::gltf::origin, ::gpu::gltf::unitZ, -::gpu::gltf::unitY),
            glm::lookAt(::gpu::gltf::origin, -::gpu::gltf::unitZ, -::gpu::gltf::unitY)
         };
         glm::mat4 projection = glm::perspective(
            glm::radians(90.0f), // 90 degrees to cover one face
            1.0f, // its a square
            0.1f,
            2.0f);

         auto pskybox = m_pscene->current_skybox();

         //auto prenderable = pskybox->m_prenderable;

         auto ptexture = pskybox->m_ptexture;

         //auto pcube = øcreate < ::gpu::cube >();
         //::cast < ::gpu_gpu::context > pcontext = m_pgpucontext;
         auto pcube = øcreate<::gpu::cube>();
         pcube->initialize_gpu_cube(m_pgpucontext);
         ::cast<::gpu_opengl::texture> ptextureSkybox = ptexture;

         //m_pframebufferPrefilteredEnvMap->bind();
         //m_pshaderPrefilteredEnvMap->_bind();
         m_pshaderPrefilteredEnvMap->bind(nullptr, m_pframebufferPrefilteredEnvMap->m_ptexture);
         //m_pshaderPrefilteredEnvMap->set_int("environmentCubemap", 0);

         for (auto mipLevel = 0; mipLevel < m_uPrefilteredEnvMapMipLevels; mipLevel++)
         {
            m_pframebufferPrefilteredEnvMap->setMipLevel(mipLevel);

            glViewport(0, 0, m_pframebufferPrefilteredEnvMap->getWidth(), m_pframebufferPrefilteredEnvMap->getHeight());
            GLCheckError("");
            // each mip level has increasing roughness
            float roughness = (float)mipLevel / (float)(m_uPrefilteredEnvMapMipLevels - 1);
            m_pshaderPrefilteredEnvMap->set_float("roughness", roughness);

            // render to each side of the cubemap
            for (auto i = 0; i < 6; i++)
            {
               m_pshaderPrefilteredEnvMap->setModelViewProjectionMatrices(model, cameraAngles[i], projection);
               m_pframebufferPrefilteredEnvMap->setCubeFace(i);

               glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
               GLCheckError("");

               glBindTexture(GL_TEXTURE_CUBE_MAP, ptextureSkybox->m_gluTextureID);
               GLCheckError("");
               m_pshaderPrefilteredEnvMap->set_int("environmentCubemap", 0);
               //pcube->draw(pgpucommandbuffer);
               pgpucommandbuffer->m_erendersystem = ::graphics3d::e_render_system_skybox_ibl;
               pcube->bind(pgpucommandbuffer);
               pcube->draw(pgpucommandbuffer);
               pcube->unbind(pgpucommandbuffer);

            }
         }

         //timer.logDifference("Rendered specular pre-filtered environment map");
         // timer.logDifference("Rendered diffuse irradiance map");
         GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

         if (status != GL_FRAMEBUFFER_COMPLETE)
         {

            warning() << "Framebuffer incomplete! with status " << status;
         }

         glBindFramebuffer(GL_FRAMEBUFFER, 0);
         GLCheckError("");

      }


      unsigned int specular_map::getPrefilteredEnvMapId()
      {

         ::cast <gpu_opengl::ibl::mipmap_cubemap_framebuffer> pframebuffer = m_pframebufferPrefilteredEnvMap;

         return pframebuffer->getCubemapTextureId();

      }


      void specular_map::computeBrdfConvolutionMap()
      {

         //Timer timer;

         ::gpu::context_lock contextlock(m_pgpucontext);

         auto pcommandbuffer = m_pgpucontext->beginSingleTimeCommands(m_pgpucontext->graphics_queue());

         auto pfullscreenquad = øcreate<::gpu::full_screen_quad>();

         pfullscreenquad->initialize_full_screen_quad(m_pgpucontext);
         //m_pbrdfconvolutionframebuffer->bind();

         //     auto pskybox = m_pscene->current_skybox();

         //// auto prenderable = pskybox->m_prenderable;

         //auto ptexture = pskybox->m_ptexture;
         
         //m_pshaderBrdfConvolution->bind(m_pbrdfconvolutionframebuffer->m_ptexture, ptexture);
         m_pshaderBrdfConvolution->bind(nullptr, m_pbrdfconvolutionframebuffer->m_ptexture);
         //m_pshaderPrefilteredEnvMap->set_int("environmentCubemap", 0);

         glViewport(0, 0, m_uBrdfConvolutionMapWidth, m_uBrdfConvolutionMapHeight);
         GLCheckError("");
         glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
         GLCheckError("");

         pfullscreenquad->bind(pcommandbuffer);
         pfullscreenquad->draw(pcommandbuffer);
         pfullscreenquad->unbind(pcommandbuffer);

         GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

         if (status != GL_FRAMEBUFFER_COMPLETE)
         {

            printf("Framebuffer incomplete!\n");

         }

         //timer.logDifference("Rendered specular brdf convolution map");

         glBindFramebuffer(GL_FRAMEBUFFER, 0);
         GLCheckError("");

      }


      unsigned int specular_map::getBrdfConvolutionMapId()
      {

         ::cast <::gpu_opengl::ibl::brdf_convolution_framebuffer> pframebuffer = m_pbrdfconvolutionframebuffer;

         return pframebuffer->getColorTextureId();

      }


   } // namespace ibl


} // namespace gpu_opengl
