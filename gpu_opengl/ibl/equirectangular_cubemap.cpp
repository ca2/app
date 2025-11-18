// From github:/tristancalderbank/OpenGL-PBR-Renderer/equirectangular_cubemap.cpp by
// camilo on 2025-09-26 19:53 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "equirectangular_cubemap.h"
#include "bred/gpu/context.h"
#include "bred/graphics3d/_functions.h"
#include "bred/graphics3d/skybox.h"
#include "bred/gpu/device.h"
//
#include "glad/glad.h"
//

#include "gpu/gltf/_constant.h"
#include "gpu_opengl/_gpu_opengl.h"
// #include "timer.h"
#include "cubemap_framebuffer.h"
#include "hdri_cube.h"

#include "shaders/hdricube.frag.h"
#include "shaders/hdricube.vert.h"

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

         return {g_psz_hdricube_vert, sizeof(g_psz_hdricube_vert) - 1};
      }


      ::block equirectangular_cubemap::embedded_ibl_hdri_cube_frag()
      {

         return {g_psz_hdricube_frag, sizeof(g_psz_hdricube_frag) - 1};
      }


      // equirectangular_cubemap::equirectangular_cubemap(const ::string &engineRoot, const ::string &hdriPath) {
      //     ::string hdriVertexShaderPath = engineRoot + "/src/ibl/shaders/hdri_cube.vert";
      //     ::string hdriFragmentShaderPath = engineRoot + "/src/ibl/shaders/hdri_cube.frag";
      //
      //     hdriShader = std::make_unique<Shader>(hdriVertexShaderPath.c_str(), hdriFragmentShaderPath.c_str());
      //     hdri_cube = std::make_unique<hdri_cube>(hdriPath);
      //     framebuffer = std::make_unique<cubemap_framebuffer>(cubemapWidth, cubemapHeight);
      // }

      void equirectangular_cubemap::compute()
      {
         // Timer timer;

         auto pgpucommandbuffer = m_pgpucontext->beginSingleTimeCommands(m_pgpucontext->m_pgpudevice->graphics_queue());
         floating_matrix4 model = ::gpu::gltf::mIndentity4;
         using namespace graphics3d;
         floating_matrix4 cameraAngles[] = 
         {
            lookAt(origin, unitX, -unitY), // X+ (right)
            lookAt(origin, -unitX, -unitY), // X- (left)
            lookAt(origin, unitY, unitZ), // Y+ (top)
            lookAt(origin, -unitY, -unitZ), // Y- (bottom)
            lookAt(origin, unitZ, -unitY), // Z+ (front)
            lookAt(origin, -unitZ, -unitY) // Z- (back)
         };
         floating_matrix4 projection = m_pgpucontext->perspective(radians(90.0f), // 90 degrees to cover one face
                                                 1.0f, // its a square
                                                 0.1f, 2.0f);

         glViewport(0, 0, m_uCubemapWidth, m_uCubemapHeight);

         // render the equirectangular HDR texture to a cubemap
         //m_pframebuffer->bind();
         m_pshaderHdri->bind(nullptr, m_pframebuffer->m_ptexture);

         // render to each side of the cubemap
         for (auto i = 0; i < 6; i++)
         {
            
            m_pshaderHdri->setModelViewProjectionMatrices(model, cameraAngles[i], projection);
            
            m_pframebuffer->setCubeFace(i, m_pshaderHdri);
            
            m_pshaderHdri->push_properties(pgpucommandbuffer);


            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            
            GLCheckError("");

                // auto pshader = pcommandbuffer->m_pgpurendertarget->m_pgpurenderer->m_pgpucontext->
            //   m_pshaderBound;

            //m_pshaderHdri->set_int("hdri", 0);


            m_phdricube->draw(pgpucommandbuffer);

         }

         m_pframebuffer->generateMipmap();

         // timer.logDifference("Rendered equirectangular cubemap");

         GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

         if (status != GL_FRAMEBUFFER_COMPLETE)
         {

            printf("Framebuffer incomplete!\n");
         }

         // timer.logDifference("Rendered specular brdf convolution map");

         glBindFramebuffer(GL_FRAMEBUFFER, 0);
         GLCheckError("");
      }


      unsigned int equirectangular_cubemap::getCubemapId()
      {

         ::cast<cubemap_framebuffer> pframebuffer = m_pframebuffer;
         return pframebuffer->getCubemapTextureId();
      }


   } // namespace ibl


} // namespace gpu_opengl
