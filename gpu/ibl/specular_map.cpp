// From github:/tristancalderbank/OpenGL-PBR-Renderer/specular_map.cpp by
// camilo on 2025-09-26 19:55 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "specular_map.h"
#include "bred/gpu/command_buffer.h"
#include "bred/gpu/context_lock.h"
#include "bred/gpu/texture.h"
#include "gpu/full_screen_quad.h"
#include "bred/gpu/device.h"
#include "bred/gpu/types.h"
#include "gpu/timer.h"
#include "brdf_convolution_framebuffer.h"
#include "bred/gpu/context.h"
#include "bred/gpu/shader.h"
#include "bred/graphics3d/engine.h"
#include "bred/graphics3d/render_system.h"
#include "bred/graphics3d/scene_base.h"
#include "bred/graphics3d/skybox.h"
#include "gpu/ibl/mipmap_cubemap_framebuffer.h"


namespace gpu
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

         return {};

      }


      ::memory specular_map::prefiltered_environment_map_frag_memory()
      {

         return {};

      }


      ::memory specular_map::brdf_convolution_vert_memory()
      {

         return {};

      }


      ::memory specular_map::brdf_convolution_frag_memory()
      {

         return {};

      }

      void specular_map::initialize_specular_map(::graphics3d::scene_base * pscenebase)
         //,
      //::graphics3d::renderable * prenderableSkybox)
         //const ::scoped_string & scopedstrengineRoot, const unsigned int uEnvironmentCubemapId)
      {

         initialize_scene_object(pscenebase);

         //m_uEnvironmentCubemapId = uEnvironmentCubemapId;

         //m_prenderableSkybox = prenderableSkybox;



//         ;

         // // pre-filtered env map
         // ::file::path pathPrefilteredEnvMapVertexShader = "matter://shaders/ibl_specularenv.vert";
         // ::file::path pathPrefilteredEnvMapFragmentShader = "matter://shaders/ibl_specularenv.frag";
         //
         øconstruct(m_pshaderPrefilteredEnvMap);

         auto blockVert = prefiltered_environment_map_vert_memory();

         auto blockFrag = prefiltered_environment_map_frag_memory();

         auto pgpupropertiesPosition = ::gpu_properties<::gpu::position3>();

         auto pinputlayoutPosition = m_pgpucontext->input_layout(pgpupropertiesPosition);

         m_pshaderPrefilteredEnvMap->m_ecullmode = ::gpu::e_cull_mode_none;
         m_pshaderPrefilteredEnvMap->m_bDisableDepthTest = true;
         m_pshaderPrefilteredEnvMap->m_propertiesPushShared.set_properties(::gpu_properties<specular_env_map_push_constants>());
         m_pgpucontext->layout_push_constants(m_pshaderPrefilteredEnvMap->m_propertiesPushShared, false);
         m_pshaderPrefilteredEnvMap->initialize_shader_with_block(
            m_pgpucontext->m_pgpurenderer,
            blockVert,
            blockFrag, {}, {},
            pinputlayoutPosition);

         m_pshaderPrefilteredEnvMap->m_bindingCubeSampler.set(0);
         m_pshaderPrefilteredEnvMap->m_bindingCubeSampler.m_strUniform = "environmentCubemap";


         øconstruct(m_pframebufferPrefilteredEnvMap);
         m_pframebufferPrefilteredEnvMap->initialize_mipmap_cubemap_framebuffer(
            m_pscene, 
            m_uPrefilteredEnvMapWidth, 
            m_uPrefilteredEnvMapHeight);

         m_iPrefilteredEnvMapMipCount = m_pframebufferPrefilteredEnvMap->m_ptexture->m_iMipCount;

         // // BRDF convolution
         // ::file::path pathBrdfConvolutionVertexShader= "matter://shaders/ibl_brdfconvolution.vert";
         // ::file::path pathBrdfConvolutionFragmentShader = "matter://shaders/ibl_brdfconvolution.frag";

         øconstruct(m_pshaderBrdfConvolution);

         m_pshaderBrdfConvolution->m_bDisableDepthTest = true;
         m_pshaderBrdfConvolution->m_bEnableBlend = false;
         m_pshaderBrdfConvolution->m_ecullmode = ::gpu::e_cull_mode_none;

         m_pshaderBrdfConvolution->initialize_shader_with_block(
            m_pgpucontext->m_pgpurenderer, brdf_convolution_vert_memory(), brdf_convolution_frag_memory(), {}, {},
            m_pgpucontext->input_layout(::gpu_properties<::gpu::position2_uv>()));

         øconstruct(m_pframebufferBrdfConvolution);

         m_pframebufferBrdfConvolution->initialize_BrdfConvolutionFramebuffer(
            m_pscene, m_uBrdfConvolutionMapWidth, m_uBrdfConvolutionMapHeight);

      }


      void specular_map::computePrefilteredEnvMap(::gpu::command_buffer *pgpucommandbuffer)
      {

                  ::gpu::Timer timer;

         ::gpu::context_lock contextlock(m_pgpucontext);

          //auto pgpucommandbuffer =         m_pgpucontext->beginSingleTimeCommands(m_pgpucontext->m_pgpudevice->graphics_queue());

         using namespace graphics3d;

         floating_matrix4 model = mIndentity4;

         floating_matrix4 cameraAngles[] = {lookAt(origin, unitX, -unitY), lookAt(origin, -unitX, -unitY),
                                            lookAt(origin, unitY, unitZ),  lookAt(origin, -unitY, -unitZ),
                                            lookAt(origin, unitZ, -unitY), lookAt(origin, -unitZ, -unitY)};

         floating_matrix4 projection =
            m_pgpucontext->m_pengine->perspective(90.0f_degrees, // 90 degrees to cover one face
                                                  1.0f, // its a square
                                                  0.1f, 2.0f);

         auto pskybox = m_pscene->current_skybox();

         // auto prenderable = pskybox->m_prenderable;

         auto ptexture = pskybox->m_ptexture;

         // auto pcube = øcreate < ::gpu::cube >();
         //::cast < ::gpu_gpu::context > pcontext = m_pgpucontext;
         // auto pcube = øcreate<::gpu::cube>();
         auto prenderableCube = m_pgpucontext->m_pengine->shape_factory()->create_cube_001(m_pgpucontext, 2.f);
         // pcube->initialize_gpu_cube(m_pgpucontext);
         //::cast<::gpu_opengl::texture> ptextureSkybox = ptexture;
         auto ptextureSkybox = ptexture;

         // m_pframebufferPrefilteredEnvMap->bind();
         // m_pshaderPrefilteredEnvMap->_bind();

         auto ptextureTarget = m_pframebufferPrefilteredEnvMap->m_ptexture;

         m_pshaderPrefilteredEnvMap->bind(pgpucommandbuffer, ptextureTarget, ptextureSkybox);

         // m_pshaderPrefilteredEnvMap->set_int("environmentCubemap", 0);

         ///::cast<::gpu_opengl::shader> pshaderPrefilteredEnvMap = m_pshaderPrefilteredEnvMap;

         auto pshaderPrefilteredEnvMap = m_pshaderPrefilteredEnvMap;

         auto mipCount = m_iPrefilteredEnvMapMipCount;

         for (auto iCurrentMip = 0; iCurrentMip < mipCount; iCurrentMip++)
         {

            m_pframebufferPrefilteredEnvMap->set_current_mip(iCurrentMip);

            auto mipWidth = m_pframebufferPrefilteredEnvMap->mip_width();

            auto mipHeight = m_pframebufferPrefilteredEnvMap->mip_height();

            // glViewport(0, 0, mipWidth, mipHeight);
            // GLCheckError("");
            //

            ::int_rectangle r(0, 0, mipWidth, mipHeight);

            m_pgpucontext->set_viewport(pgpucommandbuffer, r);

            //
            // each mip level has increasing roughness
            float roughness = (float)iCurrentMip / (float)(mipCount - 1);
            m_pshaderPrefilteredEnvMap->set_float("roughness", roughness);

            // render to each side of the cubemap
            for (auto iFace = 0; iFace < 6; iFace++)
            {

               ::string strMessage;

               strMessage.format("prefiltered_env_map mip {} face {}", iCurrentMip, iFace);

               m_pgpucontext->start_debug_happening(pgpucommandbuffer, strMessage);

               m_pshaderPrefilteredEnvMap->setModelViewProjection(model, cameraAngles[iFace], projection);
               m_pframebufferPrefilteredEnvMap->set_cube_face(iFace);


               m_pshaderPrefilteredEnvMap->bind_source(pgpucommandbuffer, ptextureSkybox);
               // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
               // GLCheckError("");

               // glBindTexture(GL_TEXTURE_CUBE_MAP, ptextureSkybox->m_gluTextureID);
               // GLCheckError("");
               m_pshaderPrefilteredEnvMap->set_int("environmentCubemap", 0);
               // pcube->draw(pgpucommandbuffer);
               //::graphics3d::render_system rendersystemScope;
               //rendersystemScope.m_erendersystem = ::graphics3d::e_render_system_skybox_ibl;
               //pgpucommandbuffer->m_prendersystem = &rendersystemScope;
               m_pshaderPrefilteredEnvMap->push_properties(pgpucommandbuffer);
               prenderableCube->bind(pgpucommandbuffer);
               prenderableCube->draw(pgpucommandbuffer);
               prenderableCube->unbind(pgpucommandbuffer);
               pgpucommandbuffer->m_prendersystem = nullptr;

               m_pgpucontext->end_debug_happening(pgpucommandbuffer);
            }
         }

         timer.logDifference("Rendered specular pre-filtered environment map");

         // GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

         // if (status != GL_FRAMEBUFFER_COMPLETE)
         //{

         //   warning() << "Framebuffer incomplete! with status " << status;
         //}

         // glBindFramebuffer(GL_FRAMEBUFFER, 0);
         // GLCheckError("");

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
         // prefilteredEnvMapFramebuffer->bind();
         // prefilteredEnvMapShader->use();
         // prefilteredEnvMapShader->setInt("environmentCubemap", 0);
         //
         // for (auto mipLevel = 0; mipLevel < prefilteredEnvMapMipLevels; mipLevel++)
         // {
         //    prefilteredEnvMapFramebuffer->setMipLevel(mipLevel);
         //
         //    glViewport(0, 0, prefilteredEnvMapFramebuffer->getWidth(), prefilteredEnvMapFramebuffer->getHeight());
         //
         //    // each mip level has increasing roughness
         //    float roughness = (float)mipLevel / (float)(prefilteredEnvMapMipLevels - 1);
         //    prefilteredEnvMapShader->setFloat("roughness", roughness);
         //
         //    // render to each side of the cubemap
         //    for (auto i = 0; i < 6; i++)
         //    {
         //       prefilteredEnvMapShader->setModelViewProjectionMatrices(model, cameraAngles[i], projection);
         //       prefilteredEnvMapFramebuffer->setCubeFace(i);
         //
         //       glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
         //
         //       glBindTexture(GL_TEXTURE_CUBE_MAP, environmentCubemapId);
         //       cube.Draw();
         //    }
         // }
         //
         // timer.logDifference("Rendered specular pre-filtered environment map");
         //
         // glBindFramebuffer(GL_FRAMEBUFFER, 0);
      }


      // unsigned int specular_map::getPrefilteredEnvMapId()
      // {
      //    return prefilteredEnvMapFramebuffer->getCubemapTextureId();
      // }
      //

      void specular_map::computeBrdfConvolutionMap()
      {

         ::gpu::Timer timer;

         ::gpu::context_lock contextlock(m_pgpucontext);

         auto pcommandbuffer = m_pgpucontext->beginSingleTimeCommands(m_pgpucontext->m_pgpudevice->graphics_queue());

         auto pfullscreenquad = øcreate<::gpu::full_screen_quad>();

         pfullscreenquad->initialize_full_screen_quad(m_pgpucontext);
         // m_pbrdfconvolutionframebuffer->bind();

         //     auto pskybox = m_pscene->current_skybox();

         //// auto prenderable = pskybox->m_prenderable;

         // auto ptexture = pskybox->m_ptexture;

         // m_pshaderBrdfConvolution->bind(m_pbrdfconvolutionframebuffer->m_ptexture, ptexture);
         m_pshaderBrdfConvolution->bind(pcommandbuffer, m_pframebufferBrdfConvolution->m_ptexture);
         // m_pshaderPrefilteredEnvMap->set_int("environmentCubemap", 0);

         // glViewport(0, 0, m_uBrdfConvolutionMapWidth, m_uBrdfConvolutionMapHeight);
         // GLCheckError("");
         // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
         // GLCheckError("");

         pcommandbuffer->begin_render();

         ::int_rectangle rectangleViewport;

         rectangleViewport.set(0, 0, m_uBrdfConvolutionMapWidth, m_uBrdfConvolutionMapHeight);

         m_pgpucontext->set_viewport(pcommandbuffer, rectangleViewport);

         m_pgpucontext->clear(m_pframebufferBrdfConvolution->m_ptexture, ::color::transparent);

         pfullscreenquad->bind(pcommandbuffer);
         pfullscreenquad->draw(pcommandbuffer);
         pfullscreenquad->unbind(pcommandbuffer);


         pcommandbuffer->end_render();

         m_pgpucontext->endSingleTimeCommands(pcommandbuffer);

         // GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

         // if (status != GL_FRAMEBUFFER_COMPLETE)
         //{

         //   printf("Framebuffer incomplete!\n");
         //}

         //// timer.logDifference("Rendered specular brdf convolution map");

         // glBindFramebuffer(GL_FRAMEBUFFER, 0);
         // GLCheckError("");

         
         //// Timer timer;

         //::gpu::context_lock contextlock(m_pgpucontext);

         //auto pcommandbuffer = m_pgpucontext->beginSingleTimeCommands(m_pgpucontext->m_pgpudevice->graphics_queue());

         //m_pgpucontext->start_debug_happening(pcommandbuffer, "computeBrdfConvolutionMap");

         //auto pfullscreenquad = øcreate<::gpu::full_screen_quad>();

         //pfullscreenquad->initialize_full_screen_quad(m_pgpucontext);
         //// m_pbrdfconvolutionframebuffer->bind();

         ////     auto pskybox = m_pscene->current_skybox();

         ////// auto prenderable = pskybox->m_prenderable;

         //// auto ptexture = pskybox->m_ptexture;

         //// m_pshaderBrdfConvolution->bind(m_pbrdfconvolutionframebuffer->m_ptexture, ptexture);
         //m_pshaderBrdfConvolution->bind(nullptr, m_pbrdfconvolutionframebuffer->m_ptexture);
         //// m_pshaderPrefilteredEnvMap->set_int("environmentCubemap", 0);

         //// glViewport(0, 0, m_uBrdfConvolutionMapWidth, m_uBrdfConvolutionMapHeight);
         //// GLCheckError("");
         //// glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
         //// GLCheckError("");
         //pcommandbuffer->set_viewport(m_pbrdfconvolutionframebuffer->m_ptexture->m_rectangleTarget);


         //auto colorClear = ::argb(0.625f, 0.125f, 0.25f, 0.375f);

         //m_pgpucontext->clear(m_pbrdfconvolutionframebuffer->m_ptexture, colorClear);

         //if (1)
         //{
         //   pfullscreenquad->bind(pcommandbuffer);
         //   pfullscreenquad->draw(pcommandbuffer);
         //   pfullscreenquad->unbind(pcommandbuffer);
         //}

         //// GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

         //// if (status != GL_FRAMEBUFFER_COMPLETE)
         ////{

         ////   printf("Framebuffer incomplete!\n");

         ////}

         timer.logDifference("Rendered specular brdf convolution map");

         //// glBindFramebuffer(GL_FRAMEBUFFER, 0);
         //// GLCheckError("");
         //m_pgpucontext->end_debug_happening(pcommandbuffer);


         //// Timer timer;
         ////
         //// auto fullscreenQuad = FullscreenQuad();
         //// brdfConvolutionFramebuffer->bind();
         //// brdfConvolutionShader->use();
         ////
         //// glViewport(0, 0, brdfConvolutionMapWidth, brdfConvolutionMapHeight);
         //// glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
         //// fullscreenQuad.Draw();
         ////
         //// timer.logDifference("Rendered specular brdf convolution map");
         ////
         //// glBindFramebuffer(GL_FRAMEBUFFER, 0);
      }

      //
      // unsigned int specular_map::getBrdfConvolutionMapId()
      // {
      //    return brdfConvolutionFramebuffer->getColorTextureId();
      // }


   } // namespace ibl


} // namespace gpu

BEGIN_GPU_PROPERTIES(::gpu::ibl::specular_map::specular_env_map_push_constants)
GPU_PROPERTY("model", ::gpu::e_type_mat4)
GPU_PROPERTY("view", ::gpu::e_type_mat4)
GPU_PROPERTY("projection", ::gpu::e_type_mat4)
GPU_PROPERTY("roughness", ::gpu::e_type_float)
GPU_PROPERTY("padding1", ::gpu::e_type_float)
GPU_PROPERTY("padding2", ::gpu::e_type_float)
GPU_PROPERTY("padding3", ::gpu::e_type_float)
END_GPU_PROPERTIES()
