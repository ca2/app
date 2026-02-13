// From github:/tristancalderbank/OpenGL-PBR-Renderer/specular_map.cpp by
// camilo on 2025-09-26 19:55 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "specular_map.h"
//#include "brdf_convolution_framebuffer.h"
#include "bred/graphics3d/_functions.h"
#include "bred/graphics3d/engine.h"
#include "bred/graphics3d/render_system.h"
#include "bred/graphics3d/scene_base.h"
#include "bred/graphics3d/skybox.h"
#include "bred/gpu/command_buffer.h"
#include "bred/gpu/context.h"
#include "bred/gpu/context_lock.h"
#include "bred/gpu/device.h"
#include "gpu_opengl/_gpu_opengl.h"
#include "gpu_opengl/shader.h"
#include "gpu_opengl/texture.h"
//#include "gpu/cube.h"
#include "gpu/model/_constant.h"
//#include <glad/glad.h>
#include "gpu/context.h"
#include "bred/platform/timer.h"
//#include "aaa_mipmap_cubemap_framebuffer.h"
#include "gpu/full_screen_quad.h"
#include "shader/prefiltered_environment_map.vert.h"
#include "shader/prefiltered_environment_map.frag.h"
#include "shader/brdf_convolution_map.vert.h"
#include "shader/brdf_convolution_map.frag.h"


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


      ::memory specular_map::prefiltered_environment_map_vert_memory()
      {

         return g_psz_prefiltered_environment_map_vert;

      }


      ::memory specular_map::prefiltered_environment_map_frag_memory()
      {

         return g_psz_prefiltered_environment_map_frag;

      }


      ::memory specular_map::brdf_convolution_vert_memory()
      {

         return g_psz_brdf_convolution_map_vert;

      }


      ::memory specular_map::brdf_convolution_frag_memory()
      {

         return g_psz_brdf_convolution_map_frag;

      }


      void specular_map::computePrefilteredEnvMap(::gpu::command_buffer *pgpucommandbuffer)
      {

         ::gpu::ibl::specular_map::computePrefilteredEnvMap(pgpucommandbuffer);
//
//          ::bred::Timer timer;
//
//          ::gpu::context_lock contextlock(m_pgpucontext);
//
//          //auto pgpucommandbuffer = m_pgpucontext->beginSingleTimeCommands(m_pgpucontext->m_pgpudevice->graphics_queue());
//
//          using namespace graphics3d;
//
//          floating_matrix4 model = mIndentity4;
//
//          floating_matrix4 cameraAngles[] =
//          {
//             lookAt(origin, unitX, -unitY),
//             lookAt(origin, -unitX, -unitY),
//             lookAt(origin, unitY, unitZ),
//             lookAt(origin, -unitY, -unitZ),
//             lookAt(origin, unitZ, -unitY),
//             lookAt(origin, -unitZ, -unitY)
//          };
//
//          floating_matrix4 projection = m_pgpucontext->m_pengine->perspective(
//             90.0f_degrees, // 90 degrees to cover one face
//             1.0f, // its a square
//             0.1f,
//             2.0f);
//
//          auto pskybox = m_pscene->current_skybox();
//
//          //auto prenderable = pskybox->m_prenderable;
//
//          auto ptexture = pskybox->m_ptexture;
//
//          //auto pcube = øcreate < ::gpu::cube >();
//          //::cast < ::gpu_gpu::context > pcontext = m_pgpucontext;
//          //auto pcube = øcreate<::gpu::cube>();
//          auto prenderableCube = m_pgpucontext->m_pengine->shape_factory()->create_cube_001(m_pgpucontext, 2.f);
//          //pcube->initialize_gpu_cube(m_pgpucontext);
//          ::cast<::gpu_opengl::texture> ptextureSkybox = ptexture;
//
//          //m_pframebufferPrefilteredEnvMap->bind();
//          //m_pshaderPrefilteredEnvMap->_bind();
//          m_pshaderPrefilteredEnvMap->bind(nullptr, m_pframebufferPrefilteredEnvMap->m_ptexture);
//          //m_pshaderPrefilteredEnvMap->set_int("environmentCubemap", 0);
//
//          ::cast<::gpu_opengl::shader> pshaderPrefilteredEnvMap = m_pshaderPrefilteredEnvMap;
//
//          auto mipCount = m_iPrefilteredEnvMapMipCount;
//
//          for (auto iCurrentMip = 0; iCurrentMip < mipCount; iCurrentMip++)
//          {
//
//             m_pframebufferPrefilteredEnvMap->set_current_mip(iCurrentMip);
//
//             auto mipWidth = m_pframebufferPrefilteredEnvMap->mip_width();
//
//             auto mipHeight = m_pframebufferPrefilteredEnvMap->mip_height();
//
//             glViewport(0, 0, mipWidth, mipHeight);
//             ::opengl::check_error("");
//             // each mip level has increasing roughness
//             float roughness = (float)iCurrentMip / (float)(mipCount - 1);
//             m_pshaderPrefilteredEnvMap->set_float("roughness", roughness);
//
//             // render to each side of the cubemap
//             for (auto iFace = 0; iFace < 6; iFace++)
//             {
//
//                ::string strMessage;
//
//                strMessage.format("prefiltered_env_map mip {} face {}", iCurrentMip, iFace);
//
//                m_pgpucontext->start_debug_happening(pgpucommandbuffer, strMessage);
//
//                m_pshaderPrefilteredEnvMap->setModelViewProjection(model, cameraAngles[iFace], projection);
//                m_pframebufferPrefilteredEnvMap->set_cube_face(iFace);
//
// //               glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//   //             ::opengl::check_error("");
//
//                int iTextureId = ptextureSkybox->m_gluTextureID;
//
//                glBindTexture(GL_TEXTURE_CUBE_MAP, iTextureId);
//                ::opengl::check_error("");
//                pshaderPrefilteredEnvMap->set_int("environmentCubemap", 0);
//                //pcube->draw(pgpucommandbuffer);
//                ::graphics3d::render_system rendersystemScope;
//                rendersystemScope.m_erendersystem = ::graphics3d::e_render_system_skybox_ibl;
//                pgpucommandbuffer->m_prendersystem = &rendersystemScope;
//                m_pshaderPrefilteredEnvMap->push_properties(pgpucommandbuffer);
//                prenderableCube->bind(pgpucommandbuffer);
//                prenderableCube->draw(pgpucommandbuffer);
//                prenderableCube->unbind(pgpucommandbuffer);
//                pgpucommandbuffer->m_prendersystem = nullptr;
//
//                m_pgpucontext->end_debug_happening(pgpucommandbuffer);
//
//             }
//          }
//
//          timer.logDifference("Rendered specular pre-filtered environment map");
//
//          GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
//
//          if (status != GL_FRAMEBUFFER_COMPLETE)
//          {
//
//             warning() << "Framebuffer incomplete! with status " << status;
//          }
//
//          glBindFramebuffer(GL_FRAMEBUFFER, 0);
//          ::opengl::check_error("");

      }


      // unsigned int specular_map::getPrefilteredEnvMapId()
      // {
      //
      //    ::cast <gpu_opengl::ibl::aaa_mipmap_cubemap_framebuffer> pframebuffer = m_pframebufferPrefilteredEnvMap;
      //
      //    return pframebuffer->getCubemapTextureId();
      //
      // }


      void specular_map::computeBrdfConvolutionMap(::gpu::command_buffer *pgpucommandbuffer)
      {

         ::gpu::ibl::specular_map::computeBrdfConvolutionMap(pgpucommandbuffer);

         // //Timer timer;
         //
         // ::gpu::context_lock contextlock(m_pgpucontext);
         //
         // auto pcommandbuffer = m_pgpucontext->beginSingleTimeCommands(m_pgpucontext->m_pgpudevice->graphics_queue());
         //
         // auto pfullscreenquad = øcreate<::gpu::full_screen_quad>();
         //
         // pfullscreenquad->initialize_full_screen_quad(m_pgpucontext);
         // //m_pbrdfconvolutionframebuffer->bind();
         //
         // //     auto pskybox = m_pscene->current_skybox();
         //
         // //// auto prenderable = pskybox->m_prenderable;
         //
         // //auto ptexture = pskybox->m_ptexture;
         //
         // //m_pshaderBrdfConvolution->bind(m_pbrdfconvolutionframebuffer->m_ptexture, ptexture);
         // m_pshaderBrdfConvolution->bind(nullptr, m_pbrdfconvolutionframebuffer->m_ptexture);
         // //m_pshaderPrefilteredEnvMap->set_int("environmentCubemap", 0);
         //
         // glViewport(0, 0, m_uBrdfConvolutionMapWidth, m_uBrdfConvolutionMapHeight);
         // ::opengl::check_error("");
         // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
         // ::opengl::check_error("");
         //
         // pfullscreenquad->bind(pcommandbuffer);
         // pfullscreenquad->draw(pcommandbuffer);
         // pfullscreenquad->unbind(pcommandbuffer);
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
         // //timer.logDifference("Rendered specular brdf convolution map");
         //
         // glBindFramebuffer(GL_FRAMEBUFFER, 0);
         // ::opengl::check_error("");

      }


      // unsigned int specular_map::getBrdfConvolutionMapId()
      // {
      //
      //    ::cast <::gpu_opengl::ibl::brdf_convolution_framebuffer> pframebuffer = m_pbrdfconvolutionframebuffer;
      //
      //    return pframebuffer->getColorTextureId();
      //
      // }


   } // namespace ibl


} // namespace gpu_opengl
