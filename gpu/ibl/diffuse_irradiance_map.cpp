// From github:/tristancalderbank/OpenGL-PBR-Renderer/diffuse_irradiance_map.cpp by
// camilo on 2025-09-26 19:53 <3ThomasBorregaardSorensen!!
#include "framework.h"
//#include "cubemap_framebuffer.h"
#include "diffuse_irradiance_map.h"
#include "bred/gpu/context.h"
#include "bred/gpu/shader.h"
#include "bred/gpu/texture.h"
#include "bred/gpu/types.h"
#include "bred/graphics3d/shape_factory.h"
//#include "glad/glad.h"
//
//
//
//#include "constants.h"
//#include "gpu/cube.h"
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
         // ::file::path pathDiffuseIrradianceVertexShader = scopedstrengineRoot + "/src/ibl/shaders/diffuse_irradiance_map.vert";
         // ::file::path pathDiffuseIrradianceFragmentShader = scopedstrengineRoot + "/src/ibl/shaders/diffuse_irradiance_map.frag";

         øconstruct(m_pshaderDiffuseIrradiance);

         //::gpu_properties<::gpu::model_view_projection_environmentCubeSampler>()
         m_pshaderDiffuseIrradiance->m_bDisableDepthTest = true;
         m_pshaderDiffuseIrradiance->m_bEnableBlend = false;
         m_pshaderDiffuseIrradiance->m_ecullmode = ::gpu::e_cull_mode_none;
         auto pgpupropertiesPosition = ::gpu_properties<::graphics3d::shape_factory::Vertex>();

         auto pinputlayoutPosition = m_pgpucontext->input_layout(pgpupropertiesPosition);

         m_pshaderDiffuseIrradiance->m_propertiesPushShared.set_properties(
            ::gpu_properties<model_view_projection_environmentCubeSampler>());

         m_pgpucontext->layout_push_constants(m_pshaderDiffuseIrradiance->m_propertiesPushShared, false);

         m_pshaderDiffuseIrradiance->initialize_shader_with_block(
            m_pgpucontext->m_pgpurenderer, embedded_diffuse_irradiance_vert(), embedded_diffuse_irradiance_frag(), {},
            {}, pinputlayoutPosition);

         //m_pshaderDiffuseIrradiance->m_bindingCubeSampler.set(0);
         //m_pshaderDiffuseIrradiance->m_bindingCubeSampler.m_strUniform = "environmentCubemap";
         auto &bindingCubeSampler = m_pshaderDiffuseIrradiance->binding();
         bindingCubeSampler.m_strUniform = "environmentCubemap";

         øconstruct(m_ptextureDiffuseIrradianceCubemap);

         //m_ptextureDiffuseIrradianceCubemap->m_strSamplerUniform = "environmentCubemap";

         m_ptextureDiffuseIrradianceCubemap->initialize_mipmap_cubemap_texture(
            m_pgpucontext->m_pgpurenderer, ::int_rectangle{ API_CHANGED_ARGUMENT,m_udiffuse_irradiance_mapWidth, m_udiffuse_irradiance_mapHeight});

      }


      void diffuse_irradiance_map::computeIrradianceMap(::gpu::command_buffer *pgpucommandbuffer)
      {

         // Timer timer;
         //
         // floating_matrix4 model = constants::mIndentity4;
         // floating_matrix4 cameraAngles[] =
         // {
         //    glm::lookAt(constants::origin, constants::unitX, -constants::unitY),
         //    glm::lookAt(constants::origin, -constants::unitX, -constants::unitY),
         //    glm::lookAt(constants::origin, constants::unitY, constants::unitZ),
         //    glm::lookAt(constants::origin, -constants::unitY, -constants::unitZ),
         //    glm::lookAt(constants::origin, constants::unitZ, -constants::unitY),
         //    glm::lookAt(constants::origin, -constants::unitZ, -constants::unitY)
         // };
         // floating_matrix4 projection = glm::perspective(
         //    ::radians(90.0f), // 90 degrees to cover one face
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

         //         ::gpu::context_lock contextlock(m_pgpucontext);

         //// Timer timer;

         //auto pgpucommandbuffer = m_pgpucontext->beginSingleTimeCommands(m_pgpucontext->m_pgpudevice->graphics_queue());

         //floating_matrix4 model = ::gpu::gltf::mIndentity4;
         //floating_matrix4 cameraAngles[] = {glm::lookAt(::geometry3d::origin, ::geometry3d::unitX, -::geometry3d::unitY),
         //                            glm::lookAt(::geometry3d::origin, -::geometry3d::unitX, -::geometry3d::unitY),
         //                            glm::lookAt(::geometry3d::origin, ::geometry3d::unitY, ::geometry3d::unitZ),
         //                            glm::lookAt(::geometry3d::origin, -::geometry3d::unitY, -::geometry3d::unitZ),
         //                            glm::lookAt(::geometry3d::origin, ::geometry3d::unitZ, -::geometry3d::unitY),
         //                            glm::lookAt(::geometry3d::origin, -::geometry3d::unitZ, -::geometry3d::unitY)};
         //floating_matrix4 projection = glm::perspective(::radians(90.0f), // 90 degrees to cover one face
         //                                        1.0f, // its a square
         //                                        0.1f, 2.0f);


         //// auto pcube = øcreate<::gpu::cube>();
         //////::cast < ::gpu_gpu::context > pcontext = m_pgpucontext;
         //auto pcube = øcreate<::gpu::cube>();
         //pcube->initialize_gpu_cube(m_pgpucontext);

         //// glViewport(0, 0, m_udiffuse_irradiance_mapWidth, m_udiffuse_irradiance_mapHeight);
         //// GLCheckError("");
         //// m_pdiffuseIrradianceFramebuffer->bind();
         //m_pshaderDiffuseIrradiance->bind(nullptr, m_pdiffuseIrradianceFramebuffer->m_ptexture);


         //// auto pcube = øcreate<::gpu::cube >();

         //auto pskybox = m_pscene->current_skybox();

         //auto prenderable = pskybox->m_prenderable;

         //auto ptexture = pskybox->m_ptexture;

         //::cast<::gpu_directx11::texture> ptextureSkybox = ptexture;

         //// render to each side of the cubemap
         //for (auto i = 0; i < 6; i++)
         //{
         //   m_pshaderDiffuseIrradiance->setModelViewProjectionMatrices(model, cameraAngles[i], projection);
         //   m_pdiffuseIrradianceFramebuffer->setCubeFace(i, m_pshaderDiffuseIrradiance);

         //   // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
         //   // GLCheckError("");

         //   ////m_pshaderDiffuseIrradiance->set_int("environmentCubemap", 0);
         //   // glBindTexture(GL_TEXTURE_CUBE_MAP, ptextureSkybox->m_gluTextureID);
         //   //  pgpucommandbuffer->m_erendersystem = ::graphics3d::e_render_system_skybox_ibl;
         //   pcube->bind(pgpucommandbuffer);
         //   pcube->draw(pgpucommandbuffer);
         //   pcube->unbind(pgpucommandbuffer);
         //   // prenderable->bind(pgpucommandbuffer);
         //   // prenderable->draw(pgpucommandbuffer);
         //   // prenderable->unbind(pgpucommandbuffer);
         //   // glBindTexture(GL_TEXTURE_CUBE_MAP, m_uEnvironmentCubemapId);
         //   // pcube->draw(pgpucommandbuffer);
         //}

         //////timer.logDifference("Rendered diffuse irradiance map");
         //// GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

         //// if (status != GL_FRAMEBUFFER_COMPLETE)
         ////{

         ////   warning() << "Framebuffer incomplete! with status " << status;
         ////}

         //// glBindFramebuffer(GL_FRAMEBUFFER, 0);
         //// GLCheckError("");

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
