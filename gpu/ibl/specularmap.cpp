// From github:/tristancalderbank/OpenGL-PBR-Renderer/SpecularMap.cpp by
// camilo on 2025-09-26 19:55 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "specularmap.h"

#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>

//#include "constants.h"
//#include "cube.h"
//#include "fullscreenquad.h"
//#include "timer.h"
#include "gpu/ibl/mipmapcubemapframebuffer.h"


namespace gpu
{


   namespace ibl
   {


      SpecularMap::SpecularMap()
      {


      }


      SpecularMap::~SpecularMap()
      {

      }


      void SpecularMap::SpecularMap(const ::string &engineRoot, const unsigned int environmentCubemapId)
      {

         initialize_environmentCubemapId(environmentCubemapId);

         // pre-filtered env map
         ::string prefilteredEnvMapVertexShaderPath = engineRoot + "/src/ibl/shaders/specularenv.vert";
         ::string prefilteredEnvMapFragmentShaderPath = engineRoot + "/src/ibl/shaders/specularenv.frag";

         prefilteredEnvMapShader = std::make_unique<Shader>(prefilteredEnvMapVertexShaderPath.c_str(),
                                                            prefilteredEnvMapFragmentShaderPath.c_str());
         prefilteredEnvMapFramebuffer = std::make_unique<MipmapCubemapFramebuffer>(
            prefilteredEnvMapWidth, prefilteredEnvMapHeight);

         // BRDF convolution
         ::string brdfConvolutionVertexShaderPath = engineRoot + "/src/ibl/shaders/brdfconvolution.vert";
         ::string brdfConvolutionFragmentShaderPath = engineRoot + "/src/ibl/shaders/brdfconvolution.frag";

         brdfConvolutionShader = std::make_unique<Shader>(brdfConvolutionVertexShaderPath.c_str(),
                                                          brdfConvolutionFragmentShaderPath.c_str());
         brdfConvolutionFramebuffer = std::make_unique<BrdfConvolutionFramebuffer>(
            brdfConvolutionMapWidth, brdfConvolutionMapHeight);

      }


      void SpecularMap::computePrefilteredEnvMap()
      {
         Timer timer;

         glm::mat4 model = constants::mIndentity4;
         glm::mat4 cameraAngles[] =
         {
            glm::lookAt(constants::origin, constants::unitX, -constants::unitY),
            glm::lookAt(constants::origin, -constants::unitX, -constants::unitY),
            glm::lookAt(constants::origin, constants::unitY, constants::unitZ),
            glm::lookAt(constants::origin, -constants::unitY, -constants::unitZ),
            glm::lookAt(constants::origin, constants::unitZ, -constants::unitY),
            glm::lookAt(constants::origin, -constants::unitZ, -constants::unitY)
         };
         glm::mat4 projection = glm::perspective(
            glm::radians(90.0f), // 90 degrees to cover one face
            1.0f, // its a square
            0.1f,
            2.0f);

         auto cube = Cube();
         prefilteredEnvMapFramebuffer->bind();
         prefilteredEnvMapShader->use();
         prefilteredEnvMapShader->setInt("environmentCubemap", 0);

         for (auto mipLevel = 0; mipLevel < prefilteredEnvMapMipLevels; mipLevel++)
         {
            prefilteredEnvMapFramebuffer->setMipLevel(mipLevel);

            glViewport(0, 0, prefilteredEnvMapFramebuffer->getWidth(), prefilteredEnvMapFramebuffer->getHeight());

            // each mip level has increasing roughness
            float roughness = (float)mipLevel / (float)(prefilteredEnvMapMipLevels - 1);
            prefilteredEnvMapShader->setFloat("roughness", roughness);

            // render to each side of the cubemap
            for (auto i = 0; i < 6; i++)
            {
               prefilteredEnvMapShader->setModelViewProjectionMatrices(model, cameraAngles[i], projection);
               prefilteredEnvMapFramebuffer->setCubeFace(i);

               glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

               glBindTexture(GL_TEXTURE_CUBE_MAP, environmentCubemapId);
               cube.Draw();
            }
         }

         timer.logDifference("Rendered specular pre-filtered environment map");

         glBindFramebuffer(GL_FRAMEBUFFER, 0);
      }


      unsigned int SpecularMap::getPrefilteredEnvMapId()
      {
         return prefilteredEnvMapFramebuffer->getCubemapTextureId();
      }


      void SpecularMap::computeBrdfConvolutionMap()
      {
         Timer timer;

         auto fullscreenQuad = FullscreenQuad();
         brdfConvolutionFramebuffer->bind();
         brdfConvolutionShader->use();

         glViewport(0, 0, brdfConvolutionMapWidth, brdfConvolutionMapHeight);
         glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
         fullscreenQuad.Draw();

         timer.logDifference("Rendered specular brdf convolution map");

         glBindFramebuffer(GL_FRAMEBUFFER, 0);
      }


      unsigned int SpecularMap::getBrdfConvolutionMapId()
      {
         return brdfConvolutionFramebuffer->getColorTextureId();
      }


   } // namespace ibl


} // namespace gpu
