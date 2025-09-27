// From github:/tristancalderbank/OpenGL-PBR-Renderer/EquirectangularCubemap.cpp by
// camilo on 2025-09-26 19:53 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "ibl/equirectangularcubemap.h"

#include "glad/glad.h"
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>

#include "constants.h"
#include "timer.h"
#include "ibl/cubemapframebuffer.h"
#include "ibl/hdricube.h"



namespace gpu_opengl
{


namespace ibl
{
EquirectangularCubemap::EquirectangularCubemap(const ::string &engineRoot, const ::string &hdriPath) {
    ::string hdriVertexShaderPath = engineRoot + "/src/ibl/shaders/hdricube.vert";
    ::string hdriFragmentShaderPath = engineRoot + "/src/ibl/shaders/hdricube.frag";

    hdriShader = std::make_unique<Shader>(hdriVertexShaderPath.c_str(), hdriFragmentShaderPath.c_str());
    hdriCube = std::make_unique<HDRICube>(hdriPath);
    framebuffer = std::make_unique<CubemapFramebuffer>(cubemapWidth, cubemapHeight);
}

void EquirectangularCubemap::compute() {
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

    glViewport(0, 0, cubemapWidth, cubemapHeight);

    // render the equirectangular HDR texture to a cubemap
    framebuffer->bind();
    hdriShader->use();

    // render to each side of the cubemap
    for (auto i = 0; i < 6; i++) {
        hdriShader->setModelViewProjectionMatrices(model, cameraAngles[i], projection);
        framebuffer->setCubeFace(i);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        hdriCube->Draw(*hdriShader);
    }

    framebuffer->generateMipmap();

    timer.logDifference("Rendered equirectangular cubemap");

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

unsigned int EquirectangularCubemap::getCubemapId() {
   return framebuffer->getCubemapTextureId();
}




    } // namespace ibl


} // namespace gpu_opengl



