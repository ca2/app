// From github:/tristancalderbank/OpenGL-PBR-Renderer/specular_map.cpp by
// camilo on 2025-09-26 19:55 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "specular_map.h"
#include "bred/gpu/binding.h"
#include "bred/gpu/command_buffer.h"
#include "bred/gpu/context_lock.h"
#include "bred/gpu/texture.h"
#include "gpu/full_screen_quad.h"
#include "bred/gpu/device.h"
#include "bred/gpu/types.h"
#include "gpu/timer.h"
#include "bred/gpu/context.h"
#include "bred/gpu/shader.h"
#include "bred/graphics3d/engine.h"
#include "bred/graphics3d/scene_base.h"
#include "bred/graphics3d/skybox.h"


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
      {

         initialize_scene_object(pscenebase);
         
         øconstruct(m_pshaderPrefilteredEnvMap);

         auto blockVert = prefiltered_environment_map_vert_memory();

         auto blockFrag = prefiltered_environment_map_frag_memory();

         auto pbindingSampler = m_pshaderPrefilteredEnvMap->binding();
         pbindingSampler->m_strUniform = "environmentCubemap";
         pbindingSampler->m_ebinding = ::gpu::e_binding_cube_sampler;

         m_pshaderPrefilteredEnvMap->m_ecullmode = ::gpu::e_cull_mode_none;
         m_pshaderPrefilteredEnvMap->m_bDisableDepthTest = true;

         auto pgpupropertiesVertex = ::gpu_properties<::graphics3d::shape_factory::Vertex>();

         auto pinputlayoutVertex = m_pgpucontext->input_layout(pgpupropertiesVertex);

         m_pshaderPrefilteredEnvMap->m_propertiesPushShared.set_properties(
            ::gpu_properties<prefiltered_env_map_push_constants>());
         
         m_pgpucontext->layout_push_constants(m_pshaderPrefilteredEnvMap->m_propertiesPushShared, false);

         m_pshaderPrefilteredEnvMap->initialize_shader_with_block(m_pgpucontext->m_pgpurenderer, blockVert, blockFrag,
                                                                  pinputlayoutVertex);

         øconstruct(m_ptexturePrefilteredEnvMapCubemap);

         ::gpu::texture_attributes textureattributesPrefilteredEnvMap(
            ::int_rectangle{API_CHANGED_ARGUMENT, m_uPrefilteredEnvMapWidth, m_uPrefilteredEnvMapHeight});

         textureattributesPrefilteredEnvMap.set_cubemap_all_mips();

         m_iPrefilteredEnvMapMipCount = textureattributesPrefilteredEnvMap.m_iMipCount;

         ::gpu::texture_flags textureflagsPrefilteredEnvMap;

         textureflagsPrefilteredEnvMap.m_bTransferTarget = true;
         textureflagsPrefilteredEnvMap.m_bShaderResource = true;
         textureflagsPrefilteredEnvMap.m_bRenderTarget = true;

         m_ptexturePrefilteredEnvMapCubemap->initialize_texture(
            m_pgpucontext->m_pgpurenderer, 
            textureattributesPrefilteredEnvMap, 
            textureflagsPrefilteredEnvMap);

         m_prenderableCube = m_pgpucontext->m_pengine->shape_factory()->create_cube_001(m_pgpucontext, 2.f);

         øconstruct(m_pshaderBrdfConvolution);

         m_pshaderBrdfConvolution->m_bDisableDepthTest = true;
         m_pshaderBrdfConvolution->m_bEnableBlend = false;
         m_pshaderBrdfConvolution->m_ecullmode = ::gpu::e_cull_mode_none;

         m_pshaderBrdfConvolution->initialize_shader_with_block(
            m_pgpucontext->m_pgpurenderer, brdf_convolution_vert_memory(), brdf_convolution_frag_memory(), 
            m_pgpucontext->input_layout(::gpu_properties<::gpu::position2_uv>()));

         øconstruct(m_ptextureBrdfConvolutionMap);

         ::gpu::texture_attributes textureattributesBrdfConvMap(int_rectangle{API_CHANGED_ARGUMENT, m_uBrdfConvolutionMapWidth, m_uBrdfConvolutionMapHeight});
         textureattributesBrdfConvMap.m_iBitsPerChannel = 16;
         textureattributesBrdfConvMap.m_iChannelCount = 2;
         textureattributesBrdfConvMap.m_iFloat = 1;

         ::gpu::texture_flags textureflagsBrdfConvMap;
         textureflagsBrdfConvMap.m_bRenderTarget = true;
         textureflagsBrdfConvMap.m_bShaderResource = true;

         m_ptextureBrdfConvolutionMap->initialize_texture(
            m_pgpucontext->m_pgpurenderer, 
            textureattributesBrdfConvMap,
            textureflagsBrdfConvMap);

      }


      void specular_map::computePrefilteredEnvMap(::gpu::command_buffer *pgpucommandbuffer)
      {

         ::gpu::Timer timer;

         ::gpu::context_lock contextlock(m_pgpucontext);

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

         auto ptextureSource = pskybox->m_ptexture;

         auto ptextureTarget = m_ptexturePrefilteredEnvMapCubemap;

         auto pshaderPrefilteredEnvMap = m_pshaderPrefilteredEnvMap;

         auto mipCount = m_iPrefilteredEnvMapMipCount;

         m_pshaderPrefilteredEnvMap->set_int("numSamples", 1);

         for (auto iCurrentMip = 0; iCurrentMip < mipCount; iCurrentMip++)
         {

            m_ptexturePrefilteredEnvMapCubemap->set_current_mip(iCurrentMip);

            auto mipWidth = m_ptexturePrefilteredEnvMapCubemap->mip_width();

            auto mipHeight = m_ptexturePrefilteredEnvMapCubemap->mip_height();

            ::int_rectangle r(0, 0, mipWidth, mipHeight);

            pgpucommandbuffer->set_viewport(r);

            // each mip level has increasing roughness
            float roughness = (float)iCurrentMip / (float)(mipCount - 1);

            m_pshaderPrefilteredEnvMap->set_float("roughness", roughness);

            for (auto iFace = 0; iFace < 6; iFace++)
            {

               ::string strMessage;

               strMessage.format("prefiltered_env_map mip {} face {}", iCurrentMip, iFace);

               m_pgpucontext->start_debug_happening(pgpucommandbuffer, strMessage);

               m_ptexturePrefilteredEnvMapCubemap->set_current_layer(iFace);

               pgpucommandbuffer->begin_render(m_pshaderPrefilteredEnvMap, ptextureTarget);

               pgpucommandbuffer->set_source(ptextureSource);

               auto impact = cameraAngles[iFace];

               auto mvp = projection * impact * model;

               m_pshaderPrefilteredEnvMap->set_matrix4("mvp", mvp);

               m_pshaderPrefilteredEnvMap->push_properties(pgpucommandbuffer);

               pgpucommandbuffer->draw(m_prenderableCube);

               pgpucommandbuffer->end_render();

               m_pgpucontext->end_debug_happening(pgpucommandbuffer);

            }

         }

         ptextureTarget->set_current_mip(-1);

         ptextureTarget->set_current_layer(-1);

         ptextureTarget->set_state(pgpucommandbuffer, ::gpu::e_texture_state_shader_read);

         timer.logDifference("Rendered specular pre-filtered environment map");

      }


      void specular_map::computeBrdfConvolutionMap()
      {

         ::gpu::Timer timer;

         ::gpu::context_lock contextlock(m_pgpucontext);

         auto pcommandbuffer = m_pgpucontext->beginSingleTimeCommands(m_pgpucontext->m_pgpudevice->graphics_queue());

         auto pfullscreenquad = øcreate<::gpu::full_screen_quad>();

         pfullscreenquad->initialize_full_screen_quad(m_pgpucontext);
         
         pcommandbuffer->begin_render(m_pshaderBrdfConvolution, m_ptextureBrdfConvolutionMap);

         ::int_rectangle rectangleViewport;

         rectangleViewport.set(0, 0, m_uBrdfConvolutionMapWidth, m_uBrdfConvolutionMapHeight);

         m_pgpucontext->set_viewport(pcommandbuffer, rectangleViewport);

         m_pgpucontext->clear(m_ptextureBrdfConvolutionMap, ::color::transparent);

         pcommandbuffer->draw(pfullscreenquad);
         
         pfullscreenquad->unbind(pcommandbuffer);

         pcommandbuffer->end_render();

         m_ptextureBrdfConvolutionMap->set_state(pcommandbuffer, ::gpu::e_texture_state_shader_read);

         m_pgpucontext->endSingleTimeCommands(pcommandbuffer);

         timer.logDifference("Rendered specular brdf convolution map");

         m_pgpucontext->end_debug_happening(pcommandbuffer);

      }


   } // namespace ibl


} // namespace gpu


BEGIN_GPU_PROPERTIES(::gpu::ibl::specular_map::prefiltered_env_map_push_constants)
GPU_PROPERTY("mvp", ::gpu::e_type_mat4)
//GPU_PROPERTY("view", ::gpu::e_type_mat4)
//GPU_PROPERTY("projection", ::gpu::e_type_mat4)
GPU_PROPERTY("roughness", ::gpu::e_type_float)
GPU_PROPERTY("numSamples", ::gpu::e_type_int)
END_GPU_PROPERTIES()



