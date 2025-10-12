// From github:/tristancalderbank/OpenGL-PBR-Renderer/diffuse_irradiance_map.cpp by
// camilo on 2025-09-26 19:53 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "cubemap_framebuffer.h"
#include "diffuse_irradiance_map.h"
#include "bred/gpu/context.h"
#include "bred/gpu/shader.h"
//#include "glad/glad.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

//#include "constants.h"
#include "gpu/cube.h"
//#include "timer.h"
#include "bred/gpu/render.h"



namespace gpu
{


   namespace ibl
   {


      diffuse_irradiance_map::diffuse_irradiance_map()
      {


      }


      diffuse_irradiance_map::~diffuse_irradiance_map()
      {


      }


      ::block diffuse_irradiance_map::embedded_diffuse_irradiance_vert()
      {

         return {};

      }


      ::block diffuse_irradiance_map::embedded_diffuse_irradiance_frag()
      {

         return {};

      }


      void diffuse_irradiance_map::initialize_diffuse_irradiance_map(
         ::graphics3d::scene_base * pscenebase)
         //::graphics3d::renderable * prenderableSkybox)
         //unsigned int uEnvironmentCubemapId)
      {

         initialize_scene_object(pscenebase);

         //m_uEnvironmentCubemapId = uEnvironmentCubemapId;
         //m_prenderableSkybox = prenderableSkybox;
         //
         // embedded_diffuse_irradiance_vert();
         // embedded_diffuse_irradiance_frag();
         //
         // ::file::path pathDiffuseIrradianceVertexShader = scopedstrengineRoot + "/src/ibl/shaders/diffuseirradiance.vert";
         // ::file::path pathDiffuseIrradianceFragmentShader = scopedstrengineRoot + "/src/ibl/shaders/diffuseirradiance.frag";

         øconstruct(m_pshaderDiffuseIrradiance);

         m_pshaderDiffuseIrradiance->initialize_shader_with_block(
            m_pgpucontext->m_pgpurenderer,
            embedded_diffuse_irradiance_vert(),
            embedded_diffuse_irradiance_frag(), {}, {},
            ::gpu_properties < ::gpu::model_view_projection_environmentCubeSampler >());

         m_pshaderDiffuseIrradiance->m_bindingCubeSampler.set(0);
         m_pshaderDiffuseIrradiance->m_bindingCubeSampler.m_strUniform = "environmentCubemap";


         øconstruct(m_pdiffuseIrradianceFramebuffer);

         m_pdiffuseIrradianceFramebuffer->m_strSamplerUniform = "environmentCube";

         m_pdiffuseIrradianceFramebuffer->initialize_cubemap_framebuffer(
            m_pgpucontext, m_udiffuse_irradiance_mapWidth, m_udiffuse_irradiance_mapHeight);

      }


      void diffuse_irradiance_map::compute()
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
         // glViewport(0, 0, diffuse_irradiance_mapWidth, diffuse_irradiance_mapHeight);
         // diffuseIrradianceFramebuffer->bind();
         // diffuseIrradianceShader->use();
         //
         // // render to each side of the cubemap
         // for (auto i = 0; i < 6; i++)
         // {
         //    diffuseIrradianceShader->setModelViewProjectionMatrices(model, cameraAngles[i], projection);
         //    diffuseIrradianceFramebuffer->setCubeFace(i);
         //
         //    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
         //
         //    diffuseIrradianceShader->setInt("environmentCubemap", 0);
         //    glBindTexture(GL_TEXTURE_CUBE_MAP, environmentCubemapId);
         //    cube.Draw();
         // }
         //
         // timer.logDifference("Rendered diffuse irradiance map");
         //
         // glBindFramebuffer(GL_FRAMEBUFFER, 0);
      }


      // unsigned int diffuse_irradiance_map::getCubemapId()
      // {
      //
      //    //return diffuseIrradianceFramebuffer->getCubemapTextureId();
      //
      //    return 0;
      //
      // }


   } // namespace ibl


} // namespace gpu
