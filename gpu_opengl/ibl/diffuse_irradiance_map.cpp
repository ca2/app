// From github:/tristancalderbank/OpenGL-PBR-Renderer/diffuse_irradiance_map.cpp by
// camilo on 2025-09-26 19:53 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "diffuse_irradiance_map.h"
#include "bred/gpu/command_buffer.h"
#include "bred/gpu/context.h"
#include "bred/gpu/context_lock.h"
#include "bred/gpu/device.h"
#include "bred/graphics3d/_functions.h"
#include "bred/graphics3d/engine.h"
#include "bred/graphics3d/renderable.h"
#include "bred/graphics3d/scene_base.h"
#include "bred/graphics3d/scene_renderable.h"
#include "bred/graphics3d/skybox.h"
#include "gpu/model/_constant.h"
//#include "gpu/cube.h"
//#include <glad/glad.h>
//
//
#include "gpu_opengl/_gpu_opengl.h"
#include "gpu_opengl/texture.h"
//#include "::gpu::model.h"
//#include "cube.h"
///#include "timer.h"
//#include "gpu/ibl/cubemap_framebuffer.h"
#include "bred/gpu/model_buffer.h"
#include "gpu/context.h"
#include "shader/diffuse_irradiance_map.vert.h"
#include "shader/diffuse_irradiance_map.frag.h"

namespace gpu_opengl
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

         return g_psz_diffuse_irradiance_map_vert;

      }


      ::block diffuse_irradiance_map::embedded_diffuse_irradiance_frag()
      {

         return g_psz_diffuse_irradiance_map_frag;


      }


      // diffuse_irradiance_map::on_diffuse_irradiance_map(const ::string &engineRoot, const unsigned int environmentCubemapId) :
      //    environmentCubemapId(environmentCubemapId)
      // {
      //
      //    ::string diffuseIrradianceVertexShaderPath = engineRoot + "/src/ibl/shaders/diffuse_irradiance_map.vert";
      //    ::string diffuseIrradianceFragmentShaderPath = engineRoot + "/src/ibl/shaders/diffuse_irradiance_map.frag";
      //
      //    diffuseIrradianceShader = std::make_unique<Shader>(diffuseIrradianceVertexShaderPath.c_str(),
      //                                                       diffuseIrradianceFragmentShaderPath.c_str());
      //    diffuseIrradianceFramebuffer = std::make_unique<cubemap_framebuffer>(
      //       diffuse_irradiance_mapWidth, diffuse_irradiance_mapHeight);
      // }



      void diffuse_irradiance_map::computeIrradianceMap(::gpu::command_buffer *pgpucommandbuffer)
      {

         ::gpu::ibl::diffuse_irradiance_map::computeIrradianceMap(pgpucommandbuffer);

         //::gpu::context_lock contextlock(m_pgpucontext);

         ////Timer timer;

         ////auto pgpucommandbuffer = m_pgpucontext->beginSingleTimeCommands(m_pgpucontext->m_pgpudevice->graphics_queue());

         //using namespace graphics3d;

         //floating_matrix4 model = ::graphics3d::mIndentity4;

         //floating_matrix4 cameraAngles[] =
         //{
         //   lookAt(origin, unitX, -unitY),
         //   lookAt(origin, -unitX, -unitY),
         //   lookAt(origin, unitY, unitZ),
         //   lookAt(origin, -unitY, -unitZ),
         //   lookAt(origin, unitZ, -unitY),
         //   lookAt(origin, -unitZ, -unitY)
         //};

         //auto projection = m_pgpucontext->m_pengine->perspective(
         //   90_degrees, // 90 degrees to cover one face
         //   1.0f, // its a square
         //   0.1f,
         //   2.0f);

         ////auto pcube = øcreate<::gpu::cube>();
         //////::cast < ::gpu_gpu::context > pcontext = m_pgpucontext;
         ////auto pcube = øcreate<::gpu::cube>();
         //auto prenderableCube = m_pgpucontext->m_pengine->shape_factory()->create_cube_001(m_pgpucontext, 2.f);
         ////pcube->initialize_gpu_cube(m_pgpucontext);

         //glViewport(0, 0, m_udiffuse_irradiance_mapWidth, m_udiffuse_irradiance_mapHeight);
         //GLCheckError("");
         ////m_pdiffuseIrradianceFramebuffer->bind();
         //m_pshaderDiffuseIrradiance->bind(nullptr, m_ptextureDiffuseIrradiance->m_ptexture);


         //
         ////auto pcube = øcreate<::gpu::cube >();

         //auto pskybox = m_pscene->current_skybox();

         //auto prenderable = pskybox->m_prenderable;

         //auto ptexture = pskybox->m_ptexture;

         //::cast<::gpu_opengl::texture> ptextureSkybox = ptexture;

         //// render to each side of the cubemap
         //for (auto i = 0; i < 6; i++)
         //{
         //   m_pshaderDiffuseIrradiance->setModelViewProjection(model, cameraAngles[i], projection);
         //   m_pframebufferDiffuseIrradiance->set_cube_face(i, m_pshaderDiffuseIrradiance);

         //   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
         //   GLCheckError("");

         //   m_pshaderDiffuseIrradiance->push_properties(pgpucommandbuffer);

         //   //m_pshaderDiffuseIrradiance->set_int("environmentCubemap", 0);
         //   glBindTexture(GL_TEXTURE_CUBE_MAP, ptextureSkybox->m_gluTextureID);
         //   // pgpucommandbuffer->m_erendersystem = ::graphics3d::e_render_system_skybox_ibl;
         //   prenderableCube->bind(pgpucommandbuffer);
         //   prenderableCube->draw(pgpucommandbuffer);
         //   prenderableCube->unbind(pgpucommandbuffer);
         //   //prenderable->bind(pgpucommandbuffer);
         //   //prenderable->draw(pgpucommandbuffer);
         //   //prenderable->unbind(pgpucommandbuffer);
         //   //glBindTexture(GL_TEXTURE_CUBE_MAP, m_uEnvironmentCubemapId);
         //   //pcube->draw(pgpucommandbuffer);
         //}

         ////timer.logDifference("Rendered diffuse irradiance map");
         //GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

         //if (status != GL_FRAMEBUFFER_COMPLETE)
         //{

         //   warning() << "Framebuffer incomplete! with status " << status;
         //}

         //glBindFramebuffer(GL_FRAMEBUFFER, 0);
         //GLCheckError("");


      }


      // unsigned int diffuse_irradiance_map::getCubemapId()
      // {
      //
      //    ::cast <cubemap_framebuffer > pframebuffer = m_pframebufferDiffuseIrradiance;
      //
      //    return pframebuffer->getCubemapTextureId();
      //
      // }


   } // namespace ibl


} // namespace gpu_opengl
