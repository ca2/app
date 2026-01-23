// From github:/tristancalderbank/OpenGL-PBR-Renderer/equirectangular_cubemap.cpp by
// camilo on 2025-09-26 19:53 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "equirectangular_cubemap.h"
#include "bred/gpu/context.h"
#include "bred/graphics3d/_functions.h"
#include "bred/graphics3d/engine.h"
#include "bred/graphics3d/skybox.h"
#include "bred/gpu/device.h"
//#include "glad/glad.h"
#include "gpu/model/_constant.h"
#include "bred/platform/timer.h"
#include "gpu_opengl/_gpu_opengl.h"
//#include "cubemap_framebuffer.h"
//#include "hdri_cube.h"
#include "shader/equirectangular_cubemap.vert.h"
#include "shader/equirectangular_cubemap.frag.h"


namespace gpu_opengl
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

         return g_psz_equirectangular_cubemap_vert;

      }


      ::block equirectangular_cubemap::embedded_ibl_hdri_cube_frag()
      {

         return g_psz_equirectangular_cubemap_frag;

      }


      void equirectangular_cubemap::compute_equirectangular_cubemap(::gpu::command_buffer * pgpucommandbuffer)
      {

         gpu::ibl::equirectangular_cubemap::compute_equirectangular_cubemap(pgpucommandbuffer);

         // ::bred::Timer timer;
         //
         // auto pgpucommandbuffer = m_pgpucontext->beginSingleTimeCommands(m_pgpucontext->m_pgpudevice->graphics_queue());
         //
         // using namespace graphics3d;
         //
         // floating_matrix4 model = ::graphics3d::mIndentity4;
         //
         // floating_matrix4 cameraAngles[] =
         // {
         //
         //    lookAt(origin, unitX, -unitY), // X+ (right)
         //    lookAt(origin, -unitX, -unitY), // X- (left)
         //    lookAt(origin, unitY, unitZ), // Y+ (top)
         //    lookAt(origin, -unitY, -unitZ), // Y- (bottom)
         //    lookAt(origin, unitZ, -unitY), // Z+ (front)
         //    lookAt(origin, -unitZ, -unitY) // Z- (back)
         //
         // };
         //
         // floating_matrix4 projection = m_pgpucontext->m_pengine->perspective(
         //    90f_degrees, // 90 degrees to cover one face
         //    1.0f, // its a square
         //    0.1f,
         //    2.0f);
         //
         // // render the equirectangular HDR texture to a cubemap
         // m_pshaderHdri->bind(nullptr, m_pframebuffer->m_ptexture);
         //
         // // render to each side of the cubemap
         // for (auto i = 0; i < 6; i++)
         // {
         //
         //    auto impact = cameraAngles[i];
         //
         //    m_pshaderHdri->setModelViewProjection(model, impact, projection);
         //
         //    m_pframebuffer->setCubeFace(i, m_pshaderHdri);
         //
         //    //m_pshaderHdri->set_int("faceIndex", i);
         //
         //    m_pshaderHdri->push_properties(pgpucommandbuffer);
         //
         //    glViewport(0, 0, m_uCubemapWidth, m_uCubemapHeight);
         //
         //    glEnable(GL_DEPTH_TEST);
         //    GLCheckError("");
         //    glDepthMask(GL_TRUE);
         //    GLCheckError("");
         //
         //
         //    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
         //    GLCheckError("");
         //
         //
         //    glDisable(GL_DEPTH_TEST);
         //    GLCheckError("");
         //    glDepthMask(GL_FALSE);
         //    GLCheckError("");
         //
         //    m_prenderableCube->bind(pgpucommandbuffer);
         //
         //    m_prenderableCube->draw(pgpucommandbuffer);
         //
         //    m_prenderableCube->unbind(pgpucommandbuffer);
         //
         // }
         //
         // m_pframebuffer->generateMipmap();
         //
         // timer.logDifference("Rendered equirectangular cubemap");
         //
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


      // unsigned int equirectangular_cubemap::getCubemapId()
      // {
      //
      //    ::cast<cubemap_framebuffer> pframebuffer = m_pframebuffer;
      //
      //    return pframebuffer->getCubemapTextureId();
      //
      // }


   } // namespace ibl


} // namespace gpu_opengl
