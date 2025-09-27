// From github:/tristancalderbank/OpenGL-PBR-Renderer/DiffuseIrradianceMap.cpp by
// camilo on 2025-09-26 19:53 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "diffuseirradiancemap.h"

//#include "glad/glad.h"
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>

//#include "constants.h"
#include "cube.h"
//#include "timer.h"
#include "ibl/cubemapframebuffer.h"


namespace gpu
{


   namespace ibl
   {


      DiffuseIrradianceMap::DiffuseIrradianceMap()
      {


      }


      DiffuseIrradianceMap::~DiffuseIrradianceMap()
      {


      }


      void DiffuseIrradianceMap::initialize_DiffuseIrradianceMap(const ::string &engineRoot, const unsigned int uEnvironmentCubemapId)
      {

         m_uEnvironmentCubemapId = uEnvironmentCubemapId;

         ::string diffuseIrradianceVertexShaderPath = engineRoot + "/src/ibl/shaders/diffuseirradiance.vert";
         ::string diffuseIrradianceFragmentShaderPath = engineRoot + "/src/ibl/shaders/diffuseirradiance.frag";

         øconstruct(m_pshaderDiffuseIrradianceShader);

         m_pshaderDiffuseIrradiance->initialize_shader(
            diffuseIrradianceVertexShaderPath.c_str(),
                                                            diffuseIrradianceFragmentShaderPath.c_str());

         øconstruct(m_pdiffuseIrradianceFramebuffer);

         m_pdiffuseIrradianceFramebuffer->initialize_CubemapFramebuffer(
            m_uDiffuseIrradianceMapWidth, m_uDiffuseIrradianceMapHeight);

      }


      void DiffuseIrradianceMap::compute()
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
         // glViewport(0, 0, diffuseIrradianceMapWidth, diffuseIrradianceMapHeight);
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


      // unsigned int DiffuseIrradianceMap::getCubemapId()
      // {
      //
      //    //return diffuseIrradianceFramebuffer->getCubemapTextureId();
      //
      //    return 0;
      //
      // }


   } // namespace ibl


} // namespace gpu
