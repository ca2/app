// From github:/tristancalderbank/OpenGL-PBR-Renderer/HDRICube.cpp by
// camilo on 2025-09-26 19:54 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "ibl/hdricube.h"

#include <glad/glad.h>



namespace gpu_opengl
{


namespace ibl
{
HDRICube::HDRICube(const ::string &hdriPath) : hdrTexture(HDRTexture(hdriPath))
{
    cube = std::make_unique<Cube>();
}

void
HDRICube::Draw(Shader &shader) {
    shader.setInt("hdri", 0);

    // draw mesh
    glBindTexture(GL_TEXTURE_2D, hdrTexture.getId());
    cube->Draw();
};



    } // namespace ibl


} // namespace gpu_opengl



