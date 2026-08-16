// Created by camilo on 2026-07-24 09:52 <3ThomasBorregaardSørensen!! Mummi!! Bilbo!!
#include "platform.h"
#include "aura/graphics/image/image.h"
#include "bred/gpu/binding.h"
#include "bred/gpu/block.h"
#include "bred/gpu/command_buffer.h"
#include "bred/gpu/context.h"
#include "bred/gpu/context_lock.h"
#include "bred/gpu/device.h"
#include "bred/gpu/layer.h"
#include "bred/gpu/renderer.h"
#include "bred/gpu/shader.h"
#include "bred/gpu/texture.h"
#include "bred/graphics3d/engine.h"
#include "bred/graphics3d/scene_renderable.h"
#include "graphics3d/scene_base.h"
#include "texture_render_system.h"
#include "wavefront_obj_render_system.h"


CLASS_DECL_ACME ::string _001_image32_diagnostics(const ::i32_size &size, const image32_t *pimage32, int iScan);

namespace graphics3d
{


   texture_render_system::texture_render_system() {}


   texture_render_system::~texture_render_system() {}


   void texture_render_system::initialize_render_system(::graphics3d::engine *pengine)
   {

      ::graphics3d::render_system::initialize_render_system(pengine);
   }

   ::memory texture_render_system::vert_shader_memory()
   {

      ::memory memory;

      m_pengine->gpu_context()->m_pgpudevice->defer_shader_memory(memory, "matter://shaders/texture.vert");

      return memory;
   }

   ::memory texture_render_system::frag_shader_memory()
   {

      ::memory memory;

      m_pengine->gpu_context()->m_pgpudevice->defer_shader_memory(memory, "matter://shaders/texture.frag");

      return memory;
   }


   void texture_render_system::on_prepare(::gpu::context *pgpucontext)
   {

      auto prenderer = pgpucontext->m_pgpurenderer;

      m_pshader = createø<::gpu::shader>();
      m_pshader->set_global_ubo();
      m_pshader->m_propertiesPushShared.set_properties(simpler_render_properties());
      pgpucontext->layout_push_constants(m_pshader->m_propertiesPushShared, false);

      // auto &bindingUbo = m_pshader->binding();
      // bindingUbo.m_strUniform = "ubo";
      // bindingUbo.m_ebinding = ::gpu::e_binding_global_ubo;
      //m_pshader->m_bDisableDepthTest = true;
      //m_pshader->m_bDepthTestButNoDepthWrite = true;
      //m_pshader->m_bLequalDepth = true;
      m_pshader->m_bEnableBlend = true;
      m_pshader->m_bMultisample = true;
      // m_pshader->m_bDisableDepthTest = true;
      m_pshader->m_ecullmode = ::gpu::e_cull_mode_none;

            auto pbindingTexture = m_pshader->binding(1, 0);
      pbindingTexture->m_strUniform = "textureSampler";
            pbindingTexture->m_ebinding = ::gpu::e_binding_sampler2d;
      pbindingTexture->m_iTextureUnit = 0;

      m_pshader->initialize_shader_with_block(pgpucontext->m_pgpurenderer, this->vert_shader_memory(),
                                              this->frag_shader_memory(),
                                              //{
                                              //::gpu::shader::e_descriptor_set_slot_local }, {},
                                              pgpucontext->input_layout<::graphics3d::Vertex>()

      );

      // m_pshader->m_bClearColor = true;
      // m_pshader->m_colorClear = argb(0.8f, 0.1f, 0.5f, 0.1f);
   }


   void texture_render_system::on_update(::gpu::context *pgpucontext, ::graphics3d::scene_base *pscene) {}


   ::floating_matrix4 texture_render_system::model_matrix2(::graphics3d::scene_renderable *pscenerenderable)
   {

      floating_matrix4 matrixModel;

      floating_matrix4 matrixNormal;

      model_and_normal_matrices(matrixModel, matrixNormal, pscenerenderable);

      return matrixModel;
   }


   void texture_render_system::model_and_normal_matrices(::floating_matrix4 &matrixModel,
                                                               ::floating_matrix4 &matrixNormal,
                                                               ::graphics3d::scene_renderable *pscenerenderable)
   {

      #if 1

            auto T = ::floating_matrix4::translation(pscenerenderable->m_sequence3Translation);

      auto R = pscenerenderable->m_matrixRotation;

      auto s = pscenerenderable->m_sequence3Scaling;

      auto pszName = pscenerenderable->m_strName.c_str();

      if (pscenerenderable->m_ecoordinatesystem == ::gpu::e_coordinate_system_vulkan)
      {

         s.y = -s.y;

         // s.z = -s.z;
      }
      else
      {

         // s.x = -s.x;
         s.y = -s.y;
         // s.z = -s.z;
      }

      // s.y = -s.y;
      // else if (pscenerenderable->m_ecoordinatesystem == ::gpu::e_coordinate_system_znf)
      //{

      //   s.y = -s.y;

      //   // s.z = -s.z;
      //}

      auto S = ::floating_matrix4::scaling(s);

      auto modelMatrix = T * R * S;

      matrixModel = modelMatrix;

      auto determinant = matrixModel.determinant();

      if (abs(determinant) <= FLT_EPSILON)
      {

         auto &pathRenderable = pscenerenderable->m_pathRenderable;

         auto pszPathRenderable = pathRenderable.c_str();

         ::string strName = pathRenderable.name();

         auto pszName = strName.c_str();

         ::string strName2 = pscenerenderable->m_strName;

         auto pszName2 = strName2.c_str();

         ::information("model ({}) matrix determinant near zero: {}", strName2, determinant);
      }
      else if (determinant < 0.f)
      {

         auto &pathRenderable = pscenerenderable->m_pathRenderable;

         auto pszPathRenderable = pathRenderable.c_str();

         ::string strName = pathRenderable.name();

         auto pszName = strName.c_str();

         ::string strName2 = pscenerenderable->m_strName;

         auto pszName2 = strName2.c_str();

         // information("");

         // ::information("model ({}) matrix determinant (< 0): {}",
         //    strName2,
         //    determinant);

         // modelMatrix = modelMatrix * ::floating_matrix4::scaling({-1.f, 1.f, 1.f});
      }

      auto n = ::floating_matrix3(matrixModel).inversed().transposed();

      // n = -1.f * n;

      matrixNormal = n;

      #else

      matrixModel = model_matrix2(pscenerenderable);

      matrixNormal = floating_matrix3(matrixModel).inversed().transposed();

      #endif
   }


   void texture_render_system::on_render(::gpu::context *pgpucontext, ::graphics3d::scene_base *pscene)
   {

      auto pgpucommandbuffer = ::gpu::current_command_buffer();

      pgpucommandbuffer->set_shader(m_pshader);

      auto pblockGlobalUbo1 = pscene->global_ubo1(pgpucontext);

      // auto pbindingsetGlobalUbo =

      // pgpucommandbuffer->set_block(pblockGlobalUbo);

      auto pbindingslotsetGlobalUbo1 =
         pblockGlobalUbo1->binding_slot_set(pgpucommandbuffer, pgpucontext->global_ubo1_binding_set());

      pgpucommandbuffer->bind_slot_set(0, pbindingslotsetGlobalUbo1);

      // m_pshader->bind(
      //       ::gpu::current_command_buffer(), pgpucontext->current_target_texture(::gpu::current_layer()));

      auto pgamelayer = m_pengine->m_pimmersionlayer;

      for (auto &[strName, pscenerenderable]: pscene->scene_renderables())
      {

         if (!pscenerenderable)
         {

            continue;
         }

         if (pscenerenderable->m_erendersystem != ::graphics3d::e_render_system_wavefront_obj)
         {

            continue;
         }

         auto prenderable = pscenerenderable->renderable();

         if (prenderable && prenderable->m_egpumodel == ::gpu::e_model_wavefront_for_texture)
         {

            if (prenderable->m_pimageTexture != prenderable->m_pimageTextureNew)
            {
            //   if (prenderable->m_pimageTextureNew.nok())
            //   {
            //      continue;
            //   }
            //   prenderable->m_pimageTexture = prenderable->m_pimageTextureNew;
            //   constructø(prenderable->m_ptextureTexture);
            //   auto str = _001_image32_diagnostics(prenderable->m_pimageTexture->m_size, prenderable->m_pimageTexture->m_pimage32Raw,
            //      prenderable->m_pimageTexture->m_iScan);
            //   information("diagnostics {}", str);
            //   prenderable->m_ptextureTexture->initialize_texture_from_pixmap(pgpucontext,
            //                                                                  {prenderable->m_pimageTexture

            //});
               //prenderable->m_ptextureTexture->generate_mipmap(pgpucommandbuffer);

            }

            if (prenderable->m_ptextureTexture)
            {

               auto pbindingsetTexture = m_pshader->binding_set(1);

               auto pbindingslotsetTexture =
                  prenderable->m_ptextureTexture->binding_slot_set(pgpucommandbuffer, pbindingsetTexture);

               pgpucommandbuffer->bind_slot_set(1, pbindingslotsetTexture);
            }

            // auto T = ::floating_matrix4::translation(pscenerenderable->m_sequence3Translation);

            // auto R = pscenerenderable->m_matrixRotation;

            // auto S = ::floating_matrix4::scaling(pscenerenderable->m_sequence3Scaling);

            ::floating_matrix4 matrixModel;

            ::floating_matrix4 matrixNormal;

            model_and_normal_matrices(matrixModel, matrixNormal, pscenerenderable);

            m_pshader->m_propertiesPushShared["modelMatrix"] = matrixModel;

            // auto normalMatrix = m_pengine->normal_matrix(pscenerenderable->m_transform);

            // floating_matrix4 normalMatrix = floating_matrix3(modelMatrix).inversed().transposed();

            //m_pshader->m_propertiesPushShared["normalMatrix"] = matrixNormal;

            /// auto pcommandbuffer = pgpucontext->m_pgpurenderer->getCurrentCommandBuffer2(::gpu::current_layer());

            m_pshader->push_properties(pgpucommandbuffer);

            // prenderable->bind(pcommandbuffer);

            //::gpu::context_lock contextlock(pgpucontext);

            on_before_draw_renderable(pgpucontext, pscene, pscenerenderable);

            pgpucommandbuffer->draw(prenderable);

            prenderable->unbind(pgpucommandbuffer);
         }
      }

      // m_pshader->unbind(::gpu::current_command_buffer());
   }


   void texture_render_system::on_before_draw_renderable(::gpu::context *pgpucontext,
                                                               ::graphics3d::scene_base *pscene,
                                                               ::graphics3d::scene_renderable *pscenerenderable)
   {
   }


} // namespace graphics3d
