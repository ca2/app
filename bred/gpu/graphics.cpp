// Created by camilo on 2025-05-31 15:32 <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "draw2d.h"
#include "graphics.h"
#include "pixmap.h"
#include "acme/platform/application.h"
#include "aura/user/user/interaction.h"
#include "aura/graphics/graphics/graphics.h"
#include "aura/windowing/window.h"
#include "bred/gpu/bred_approach.h"
#include "bred/gpu/context.h"
#include "bred/gpu/context_lock.h"
#include "bred/gpu/device.h"
#include "bred/gpu/model_buffer.h"
#include "bred/gpu/renderer.h"
#include "bred/gpu/render_state.h"
#include "bred/gpu/render_target.h"
#include "bred/gpu/swap_chain.h"


namespace gpu
{


#define __TRANSFORM(p) \
   m_m1.transform(p); \
p.y() = iContextHeight - p.y()

#define __USES_TRANSFORM(pcontext) \
auto iContextHeight = pcontext->m_rectangle.height()


   void thread_graphics(graphics* pgraphics)
   {

      ::get_task()->payload("gpu::graphics") = pgraphics;

   }



   graphics::graphics()
   {

      //m_eoutputOnEndDraw = ::gpu::e_output_none;

   }


   graphics::~graphics()
   {


   }


   void graphics::initialize(::particle* pparticle)
   {

      ::draw2d::graphics::initialize(pparticle);

   }


   bool graphics::_is_ok() const
   {

      auto pcontext = ((graphics*)this)->gpu_context();

      return ::is_set(this) & ::is_set(pcontext);

   }



   void graphics::on_begin_draw()
   {

      //thread_select();

      auto pcontext = gpu_context();

      auto pgpudevice = pcontext->m_pgpudevice;

      auto prenderer = pcontext->get_gpu_renderer();

      auto prendertarget = prenderer->m_pgpurendertarget;

      if (prenderer->m_prenderstate->m_estate == ::gpu::e_state_began_render)
      {

         int iFrameIndex = prendertarget->get_frame_index();

         auto ppoolgroupFrame = pgpudevice->frame_pool_group(iFrameIndex);

         ppoolgroupFrame->m_pallocator = pgpudevice;

         ppoolgroupFrame->m_pongoingparticlearraysource = prenderer;

         ppoolgroupFrame->call_ongoing(e_call_off_to_pool);

         m_poolmodelbufferRectangle.m_ppoolgroup = ppoolgroupFrame;
         m_poolmodelbufferCharacter.m_ppoolgroup = ppoolgroupFrame;
         m_poolmodelbufferLine.m_ppoolgroup = ppoolgroupFrame;

         prenderer->current_frame_particle_array()->clear();

      }

      if (m_egraphics == e_graphics_draw)
      {

         int iFrameIndex = pcontext->m_pgpurenderer->m_pgpurendertarget->get_frame_index();

         m_poolmodelbufferRectangle.m_ppoolgroup = pgpudevice->frame_pool_group(iFrameIndex);
         m_poolmodelbufferCharacter.m_ppoolgroup = pgpudevice->frame_pool_group(iFrameIndex);
         m_poolmodelbufferLine.m_ppoolgroup = pgpudevice->frame_pool_group(iFrameIndex);

      }


      ::int_rectangle rectangle;

      if (!m_puserinteraction && m_papplication->m_gpu.m_bUseSwapChainWindow)
      {

         m_puserinteraction = dynamic_cast <::user::interaction*>(m_papplication->m_pacmeuserinteractionMain.m_p);

      }

      if (m_puserinteraction && !m_puserinteraction->host_rectangle().size().is_empty())
      {

         rectangle = m_puserinteraction->host_rectangle();

      }
      else
      {

         rectangle = { 0, 0, 1920, 1080 };

      }

      //auto pcontext = gpu_context();

      pcontext->on_begin_draw_attach(this);

   }


   //void graphics::create_end_draw()
   //{


   //}


   //::gpu::renderer* graphics::end_draw_renderer_output()
   //{

   //   ::cast < ::windowing::window > pwindow = m_puserinteraction->m_pacmewindowingwindow;

   //   if (!m_pgpucontextCompositorOutput)
   //   {

   //      __øconstruct(m_pgpucontextCompositorOutput);

   //      m_pgpucontextCompositorOutput = m_papplication->get_gpu()->get_device()->start_swap_chain_context(this, pwindow);

   //      //m_pgpucontextCompositorOutput->create_window_buffer(pwindow);

   //   }

   //   auto rectanglePlacement = pwindow->get_window_rectangle();

   //   m_pgpucontextCompositorOutput->set_placement(rectanglePlacement);

   //   auto prendererOutput = m_pgpucontextCompositorOutput->get_renderer(::gpu::e_scene_2d);

   //   prendererOutput->defer_update_renderer();

   //   return prendererOutput;

   //}


   void graphics::on_set_gpu_context()
   {


   }


   void graphics::update_matrix()
   {


      //auto matrix = m_matrixChangeOutput * matrixScale * m_matrix * matrixTranslate;

      //auto m = m_matrix;

      auto scaling = ::geometry2d::matrix::scaling(m_sizeScaling);

      auto translation = ::geometry2d::matrix::translation(m_pointOrigin);

      //m.scale(m_sizeScaling, ::geometry2d::matrix::mode_prepend);

      //m.scale(m_sizeScaleOutput, ::geometry2d::matrix::mode_prepend);

      //m.translate(m_pointOrigin, ::geometry2d::matrix::mode_append);

      //m.translate(m_pointTranslateOutput, ::geometry2d::matrix::mode_append);

      auto matrix = scaling * m_matrix * translation;

      _set(matrix);

   }





   void graphics::on_end_draw()
   {

      //end_gpu_layer();

      auto pcontext = gpu_context();

      pcontext->on_end_draw_detach(this);

   }


   //void graphics::start_gpu_layer()
   //{

   //   m_pgpucontextCompositor->m_pgpudevice->layer_start(m_pgpucontextCompositor->m_pgpurenderer);

   //}


   //void graphics::end_gpu_layer()
   //{

   //   auto prendererOutput = m_pgpucontextDraw2d->m_pgpurenderer;

   //   prendererOutput->end_layer();

   //}


   //void graphics::set_hint_window_output()
   //{

   //   m_eoutputOnEndDraw = ::gpu::e_output_swap_chain;

   //}



   void graphics::thread_select()
   {

      //if (thread_graphics() == this)
      //{

        // return;
      //}

      //wglMakeCurrent(m_hdc, m_hglrc);

      //m_pgpucontextCompositor->make_current();

      thread_graphics(this);

   }


   void graphics::_set(const ::geometry2d::matrix& matrix)
   {

      m_m1 = matrix;

   }


   void graphics::do_on_context(const ::procedure& procedure)
   {

      auto pgpudevice = m_papplication->get_gpu_approach()->get_gpu_device();

      auto pcontextMain = pgpudevice->main_context();

      ::cast < ::user::interaction > puserinteraction = m_puserinteraction;

      auto pwindow = puserinteraction->window();

      auto rectangleWindow = pwindow->get_window_rectangle();

      pcontextMain->set_placement(rectangleWindow);

      auto pcontext = gpu_context();

      pcontext->m_escene = ::gpu::e_scene_2d;

      pcontextMain->top_send_on_context(
         pcontext,
         m_egraphics & e_graphics_draw,
         procedure);

      //pgpudevice->start_stacking_layers();

      //pgpucontextMainWindow->top_send_on_context([this, pgpucontextMainWindow, procedure]()
      //   {

      //      m_pgpucontextDraw2d->send_on_context([this, procedure]()
      //         {

      //            if (m_egraphics & e_graphics_draw)
      //            {

      //               m_pgpucontextDraw2d->get_gpu_renderer()->do_on_frame([procedure]()
      //                  {

      //                     procedure();

      //                  });

      //            }
      //            else
      //            {

      //               procedure();

      //            }

      //         });

      //   });

   }


   //void graphics::create_offscreen_graphics_for_swap_chain_blitting(::user::interaction* puserinteraction, const ::int_size& size)
   //{

   //   create_memory_graphics(size);

   //}


   void graphics::create_for_window_draw2d(::user::interaction* puserinteraction, const ::int_size& size)
   {

      m_puserinteraction = puserinteraction;

      ::draw2d::graphics::create_for_window_draw2d(puserinteraction, size);
      ///create_offscreen_graphics_for_swap_chain_blitting(puserinteraction, size);

   }



   void graphics::bind_draw2d_compositor(::gpu::layer* player)
   {

      auto pcontext = gpu_context();

      pcontext->__bind_draw2d_compositor(this, player);

   }



   void graphics::defer_create_swap_chain(::user::interaction* puserinteraction)
   {

      if (m_papplication->m_gpu.m_bUseSwapChainWindow)
      {

         auto pgpucontext = gpu_context();

         auto pgpudevice = pgpucontext->m_pgpudevice;

         auto pcontextMain = pgpudevice->main_context();

         auto pswapchain = pcontextMain->get_swap_chain();

         if (!pswapchain->m_bSwapChainInitialized)
         {

            pswapchain->initialize_swap_chain_window(pcontextMain, puserinteraction->window());

         }

      }


   }



   void graphics::soft_unbind_draw2d_compositor(::gpu::layer* player)
   {

      auto pcontext = gpu_context();

      pcontext->__soft_unbind_draw2d_compositor(this, player);

   }

   
   ::gpu::shader* graphics::rectangle_shader()
   {
      
      auto pcontext = gpu_context();
      
      ::gpu::shader* pshader = nullptr;

      if (m_ealphamode == ::draw2d::e_alpha_mode_set)
      {

         if (!m_pshaderSourceRectangle)
         {

            //auto pshadervertexinput = __allocate::gpu_vulkan::shader_vertex_input();

            //pshadervertexinput->m_bindings.add(
            //   {
            //      .binding = 0,
            //      .stride = sizeof(RectangleVertex),
            //      .inputRate = VK_VERTEX_INPUT_RATE_VERTEX,
            //   });

            //pshadervertexinput->m_attribs.add({ .location = 0, .binding = 0, .format = VK_FORMAT_R32G32B32_SFLOAT, .offset = offsetof(RectangleVertex, pos) });
            //pshadervertexinput->m_attribs.add({ .location = 1, .binding = 0, .format = VK_FORMAT_R32G32B32A32_SFLOAT, .offset = offsetof(RectangleVertex, color) });

            auto pshaderRectangle = __øcreate<::gpu::shader>();

            m_pshaderSourceRectangle = pshaderRectangle;
            //m_pshaderBlendRectangle->m_bDisableDepthTest = true;
            m_pshaderSourceRectangle->m_bDisableDepthTest = true;
            //m_pshaderRectangle->m_iColorAttachmentCount = 2;
            m_pshaderSourceRectangle->m_bEnableBlend = false;
            //m_pshaderRectangle->m_bAccumulationEnable = true;

            pcontext->initialize_rectangle_shader(m_pshaderSourceRectangle);

         }

         pshader = m_pshaderSourceRectangle;

      }
      else
      {

         if (!m_pshaderBlendRectangle)
         {

            //auto pshadervertexinput = __allocate::gpu_vulkan::shader_vertex_input();

            //pshadervertexinput->m_bindings.add(
            //   {
            //      .binding = 0,
            //      .stride = sizeof(RectangleVertex),
            //      .inputRate = VK_VERTEX_INPUT_RATE_VERTEX,
            //   });

            //pshadervertexinput->m_attribs.add({ .location = 0, .binding = 0, .format = VK_FORMAT_R32G32B32_SFLOAT, .offset = offsetof(RectangleVertex, pos) });
            //pshadervertexinput->m_attribs.add({ .location = 1, .binding = 0, .format = VK_FORMAT_R32G32B32A32_SFLOAT, .offset = offsetof(RectangleVertex, color) });

            auto pshaderRectangle = __øcreate<::gpu::shader>();

            m_pshaderBlendRectangle = pshaderRectangle;
            //m_pshaderBlendRectangle->m_bDisableDepthTest = true;
            m_pshaderBlendRectangle->m_bDisableDepthTest = true;
            //m_pshaderRectangle->m_iColorAttachmentCount = 2;
            m_pshaderBlendRectangle->m_bEnableBlend = true;
            //m_pshaderRectangle->m_bAccumulationEnable = true;

            ///auto pcontext = gpu_context();

            pcontext->initialize_rectangle_shader(m_pshaderBlendRectangle);

            //::cast < ::gpu_vulkan::device > pgpudevice = pgpucontext->m_pgpudevice;
            //pshaderRectangle->initialize_shader_with_block(
            //   pcontext->m_pgpurenderer,
            //   as_memory_block(g_uaRectangleVertexShader),
            //   //as_memory_block(g_uaAccumulationFragmentShader),
            //   as_memory_block(g_uaRectangleFragmentShader),
            //   { },
            //   m_psetdescriptorlayoutRectangle,
            //   {},
            //   pcontext->input_layout<::graphics3d::sequence2_color>());

         }

         pshader = m_pshaderBlendRectangle;

      }
   
      return pshader;

   }


   void graphics::_fill_quad(const ::double_point points[4], const ::color::color& color)
   {

      auto pcontext = gpu_context();

      __USES_TRANSFORM(pcontext);

      auto prenderer = pcontext->m_pgpurenderer;

      auto pgpucontext = prenderer->m_pgpucontext;

      auto pgpudevice = pgpucontext->m_pgpudevice;

      ::gpu::context_lock contextlock(pcontext);

      //// Rectangle descriptors
      //if (!m_psetdescriptorlayoutRectangle)
      //{

      //   int iFrameCount = prenderer->get_frame_count();

      //   m_psetdescriptorlayoutRectangle = ::gpu_vulkan::set_descriptor_layout::Builder(m_pgpucontextCompositor)
      //      .addBinding(0, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, VK_SHADER_STAGE_FRAGMENT_BIT)
      //      .build();

      //   auto pdescriptorpoolbuilder = __allocate::gpu_vulkan::descriptor_pool::Builder();

      //   pdescriptorpoolbuilder->initialize_builder(m_pgpucontextCompositor);
      //   pdescriptorpoolbuilder->setMaxSets(iFrameCount * 10);
      //   pdescriptorpoolbuilder->addPoolSize(VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, iFrameCount * 10);

      //   m_psetdescriptorlayoutRectangle = pdescriptorpoolbuilder->build();

      //}

      //// Rectangle descriptors
      //if (!m_psetdescriptorlayoutRectangle)
      //{

      //   int iFrameCount = prenderer->get_frame_count();

      //   m_psetdescriptorlayoutRectangle = ::gpu_vulkan::set_descriptor_layout::Builder(m_pgpucontextCompositor)
      //      .addBinding(0, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, VK_SHADER_STAGE_FRAGMENT_BIT)
      //      .build();

      //   auto pdescriptorpoolbuilder = __allocate::gpu_vulkan::descriptor_pool::Builder();

      //   pdescriptorpoolbuilder->initialize_builder(m_pgpucontextCompositor);
      //   pdescriptorpoolbuilder->setMaxSets(iFrameCount * 10);
      //   pdescriptorpoolbuilder->addPoolSize(VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, iFrameCount * 10);

      //   m_psetdescriptorlayoutRectangle = pdescriptorpoolbuilder->build();

      //}

      ::gpu::shader* pshader = rectangle_shader();


      auto pmodelbufferRectangle = m_poolmodelbufferRectangle.get();

      if (pmodelbufferRectangle->is_new())
      {

         pmodelbufferRectangle->sequence2_color_create_rectangle(pcontext);

      }

      double_point quad[4];

      quad[0] = points[0];
      __TRANSFORM(quad[0]);
      auto& p0 = quad[0];
      quad[1] = points[1];
      __TRANSFORM(quad[1]);
      auto& p1 = quad[1];
      quad[2] = points[2];
      __TRANSFORM(quad[2]);
      auto& p2 = quad[2];
      quad[3] = points[3];
      __TRANSFORM(quad[3]);
      auto& p3 = quad[3];

      //pmodelbuffer->sequence3_color_set_rectangle();
      //pgpucontext = pgpudevice->get_main_context();
      //editQuadVertexBuffer(
      //   pgpucontext->logicalDevice(),
      //   pmodel->m_vertexMemory,
      //   quad, color, pgpucontext->rectangle().size());

      pmodelbufferRectangle->sequence2_color_set_rectangle(
         quad,
         color,
         pgpucontext->m_rectangle.size());


      pshader->bind();

      //vkCmdBeginRenderPass(cmd, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
      auto pcommandbuffer = prenderer->getCurrentCommandBuffer2();
      //VkDeviceSize offset = 0;
      ///vkCmdBindPipeline(pcommandbuffer->m_vkcommandbuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, graphicsPipeline);
      //vkCmdBindVertexBuffers(pcommandbuffer->m_vkcommandbuffer, 0, 1, &pmodelbuffer->m_vertexBuffer, &offset);

      pmodelbufferRectangle->bind(pcommandbuffer);

      pmodelbufferRectangle->draw(pcommandbuffer);

      pmodelbufferRectangle->unbind(pcommandbuffer);

      //vkCmdDraw(pcommandbuffer->m_vkcommandbuffer, 6, 1, 0, 0); // 6 vertices for two triangles
      //vkCmdEndRenderPass(cmd);



      pshader->unbind();
      //vkvg_rectangle(m_pdc, rectangle.left(), rectangle.top(), rectangle.right() - rectangle.left(),
        // rectangle.bottom() - rectangle.top());

      //m_particleaResetOnTopFrameEnd.add(pmodelbufferRectangle);

      //push_on_end_top_frame(m_modelbufferaRectangle, pmodelbufferRectangle);

      //g_z -= 0.0001;

   }


   void graphics::fill_rectangle(const ::double_rectangle& rectangle, const ::color::color& color)
   {

      /* auto pcontext = gpu_context();

       ::cast < ::gpu::renderer >prenderer = pcontext->m_pgpurenderer;

       ::cast < ::gpu::context > pgpucontext = prenderer->m_pgpucontext;

       ::cast < ::gpu::device > pgpudevice = pgpucontext->m_pgpudevice;*/



       //// Rectangle descriptors
       //if (!m_psetdescriptorlayoutRectangle)
       //{

       //   int iFrameCount = prenderer->get_frame_count();

       //   m_psetdescriptorlayoutRectangle = ::gpu_vulkan::set_descriptor_layout::Builder(m_pgpucontextCompositor)
       //      .addBinding(0, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, VK_SHADER_STAGE_FRAGMENT_BIT)
       //      .build();

       //   auto pdescriptorpoolbuilder = __allocate::gpu_vulkan::descriptor_pool::Builder();

       //   pdescriptorpoolbuilder->initialize_builder(m_pgpucontextCompositor);
       //   pdescriptorpoolbuilder->setMaxSets(iFrameCount * 10);
       //   pdescriptorpoolbuilder->addPoolSize(VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, iFrameCount * 10);

       //   m_psetdescriptorlayoutRectangle = pdescriptorpoolbuilder->build();

       //}

       //// Rectangle descriptors
       //if (!m_psetdescriptorlayoutRectangle)
       //{

       //   int iFrameCount = prenderer->get_frame_count();

       //   m_psetdescriptorlayoutRectangle = ::gpu_vulkan::set_descriptor_layout::Builder(m_pgpucontextCompositor)
       //      .addBinding(0, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, VK_SHADER_STAGE_FRAGMENT_BIT)
       //      .build();

       //   auto pdescriptorpoolbuilder = __allocate::gpu_vulkan::descriptor_pool::Builder();

       //   pdescriptorpoolbuilder->initialize_builder(m_pgpucontextCompositor);
       //   pdescriptorpoolbuilder->setMaxSets(iFrameCount * 10);
       //   pdescriptorpoolbuilder->addPoolSize(VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, iFrameCount * 10);

       //   m_psetdescriptorlayoutRectangle = pdescriptorpoolbuilder->build();

       //}

       //::gpu::shader* pshader = nullptr;

       //if (m_ealphamode == ::draw2d::e_alpha_mode_set)
       //{
       //   if (!m_pshaderSourceRectangle)
       //   {

       //      //auto pshadervertexinput = __allocate::gpu_vulkan::shader_vertex_input();

       //      //pshadervertexinput->m_bindings.add(
       //      //   {
       //      //      .binding = 0,
       //      //      .stride = sizeof(RectangleVertex),
       //      //      .inputRate = VK_VERTEX_INPUT_RATE_VERTEX,
       //      //   });

       //      //pshadervertexinput->m_attribs.add({ .location = 0, .binding = 0, .format = VK_FORMAT_R32G32B32_SFLOAT, .offset = offsetof(RectangleVertex, pos) });
       //      //pshadervertexinput->m_attribs.add({ .location = 1, .binding = 0, .format = VK_FORMAT_R32G32B32A32_SFLOAT, .offset = offsetof(RectangleVertex, color) });


       //      auto pshaderRectangle = __øcreate<::gpu::shader>();

       //      m_pshaderSourceRectangle = pshaderRectangle;
       //      //m_pshaderBlendRectangle->m_bDisableDepthTest = true;
       //      m_pshaderSourceRectangle->m_bDisableDepthTest = true;
       //      //m_pshaderRectangle->m_iColorAttachmentCount = 2;
       //      m_pshaderSourceRectangle->m_bEnableBlend = false;
       //      //m_pshaderRectangle->m_bAccumulationEnable = true;

       //      auto pcontext = gpu_context();

       //      //::cast < ::gpu_vulkan::device > pgpudevice = pgpucontext->m_pgpudevice;
       //      pshaderRectangle->initialize_shader_with_block(
       //         pcontext->m_pgpurenderer,
       //         pcontext->rectangle_shader_vert(),
       //         //as_memory_block(g_uaAccumulationFragmentShader),
       //         pcontext->rectangle_shader_frag(),
       //         {},
       //         {},
       //         {},
       //         pcontext->input_layout<::graphics3d::sequence2_color>());

       //   }
       //   pshader = m_pshaderSourceRectangle;

       //}
       //else
       //{

       //   if (!m_pshaderBlendRectangle)
       //   {

       //      //auto pshadervertexinput = __allocate::gpu_vulkan::shader_vertex_input();

       //      //pshadervertexinput->m_bindings.add(
       //      //   {
       //      //      .binding = 0,
       //      //      .stride = sizeof(RectangleVertex),
       //      //      .inputRate = VK_VERTEX_INPUT_RATE_VERTEX,
       //      //   });

       //      //pshadervertexinput->m_attribs.add({ .location = 0, .binding = 0, .format = VK_FORMAT_R32G32B32_SFLOAT, .offset = offsetof(RectangleVertex, pos) });
       //      //pshadervertexinput->m_attribs.add({ .location = 1, .binding = 0, .format = VK_FORMAT_R32G32B32A32_SFLOAT, .offset = offsetof(RectangleVertex, color) });

       //      auto pshaderRectangle = __øcreate<::gpu::shader>();

       //      m_pshaderBlendRectangle = pshaderRectangle;
       //      //m_pshaderBlendRectangle->m_bDisableDepthTest = true;
       //      m_pshaderBlendRectangle->m_bDisableDepthTest = true;
       //      //m_pshaderRectangle->m_iColorAttachmentCount = 2;
       //      m_pshaderBlendRectangle->m_bEnableBlend = true;
       //      //m_pshaderRectangle->m_bAccumulationEnable = true;

       //      auto pcontext = gpu_context();

       //      ::cast < ::gpu::device > pgpudevice = pgpucontext->m_pgpudevice;
       //      pshaderRectangle->initialize_shader_with_block(
       //         pcontext->m_pgpurenderer,
       //         pcontext->rectangle_shader_vert(),
       //         //as_memory_block(g_uaAccumulationFragmentShader),
       //         pcontext->rectangle_shader_frag(),
       //         { },
       //         {},
       //         {},
       //         pcontext->input_layout<::graphics3d::sequence2_color>());

       //   }

       //   pshader = m_pshaderBlendRectangle;

       //}

       ////auto pcontext = gpu_context();

       ////::cast < ::gpu_vulkan::context > pcontext = m_pgpucontextCompositor;

       //auto pmodelbufferRectangle = m_poolmodelbufferRectangle.get();

       //if (pmodelbufferRectangle->is_new())
       //{

       //   pmodelbufferRectangle->sequence2_color_create_rectangle(pcontext);

       //}

       ////   auto & pmodelbuffer = m_pmodelbufferRectangle;

       ////if (!pmodelbuffer)
       ////{

       ////   

       ////   //   pmodel->m_vertexBuffer = createQuadVertexBuffer(
       ////   //      pgpucontext->logicalDevice(),
       ////   //      pgpucontext->m_pgpudevice->m_pphysicaldevice->m_physicaldevice,
       ////   //      &pmodel->m_vertexMemory);

       ////   //   pmodel->m_indexBuffer = nullptr;
       ////   //   pmodel->m_indexMemory = nullptr;

       ////   //}


       ////}

      double_point points[4] = {
   {rectangle.top_left()},
   {rectangle.top_right()},
   {rectangle.bottom_right()},
   {rectangle.bottom_left()}
      };

      _fill_quad(points, color);

      //double_point quad[4];

      //quad[0] = points[0];
      //m_m1.transform(quad[0]);
      //quad[1] = points[1];
      //m_m1.transform(quad[1]);
      //quad[2] = points[2];
      //m_m1.transform(quad[2]);
      //quad[3] = points[3];
      //m_m1.transform(quad[3]);

      //

      ////pmodelbuffer->sequence3_color_set_rectangle();
      ////pgpucontext = pgpudevice->get_main_context();
      ////editQuadVertexBuffer(
      ////   pgpucontext->logicalDevice(),
      ////   pmodel->m_vertexMemory,
      ////   quad, color, pgpucontext->rectangle().size());

      //pmodelbufferRectangle->sequence2_color_set_rectangle(
      //   quad,
      //   color,
      //   pgpucontext->m_rectangle.size());


      //pshader->bind();

      ////vkCmdBeginRenderPass(cmd, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
      //auto pcommandbuffer = prenderer->getCurrentCommandBuffer2();
      ////VkDeviceSize offset = 0;
      /////vkCmdBindPipeline(pcommandbuffer->m_vkcommandbuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, graphicsPipeline);
      ////vkCmdBindVertexBuffers(pcommandbuffer->m_vkcommandbuffer, 0, 1, &pmodelbuffer->m_vertexBuffer, &offset);

      //pmodelbufferRectangle->bind(pcommandbuffer);

      //pmodelbufferRectangle->draw(pcommandbuffer);

      ////vkCmdDraw(pcommandbuffer->m_vkcommandbuffer, 6, 1, 0, 0); // 6 vertices for two triangles
      ////vkCmdEndRenderPass(cmd);


      //pshader->unbind();
      ////vkvg_rectangle(m_pdc, rectangle.left(), rectangle.top(), rectangle.right() - rectangle.left(),
      //  // rectangle.bottom() - rectangle.top());

      ////m_particleaResetOnTopFrameEnd.add(pmodelbufferRectangle);

      ////push_on_end_top_frame(m_modelbufferaRectangle, pmodelbufferRectangle);

      ////g_z -= 0.0001;

   }

   
   double_size graphics::get_text_extent(const ::scoped_string& scopedstr)
   {

      auto pcontext = gpu_context();

      ::gpu::context_lock contextlock(pcontext);

      //return{};

      //if(lpszString.is_empty())
      //   return int_size(0, 0);
      set(m_pfont);

      ::pointer<::write_text::font>pfont = m_pfont;

      ::pointer <::typeface::face> pface = get_face(pfont);

      //glBindVertexArray(pfont->m_VAO);

   // iterate through all characters
      ::string strChar;
      ::string str(scopedstr);
      auto psz = str.c_str();

      float x = 0.0f;
      float y = 0.0f;
      //glEnable(GL_CULL_FACE);
      //glEnable(GL_BLEND);
      //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      int xpos = 0;
      int ypos = 0;
      while (next_unicode_character(strChar, psz))
      {

         auto& ch = pface->get_character(strChar);

         //float xpos = x + ch.Bearing.x * scale;
         //float ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

         float w = (float) ch.Size.x;
         float h = (float)ch.Size.y;
         y = maximum(h, y);
         //// update VBO for each character
         // render glyph texture over quad
         if (ch.m_ppixmap)
         {
            /* ::graphics3d::sequence2_uv vertices[6] = {
                 {{xpos,     ypos + h},  { 0.0f, 0.0f } },
             { {xpos,     ypos    },     {  0.0f, 1.0f }},
                 {{xpos + w, ypos    },  {     1.0f, 1.0f }},
                 {{xpos,     ypos + h},  { 0.0f, 0.0f }},
                 {{xpos + w, ypos    },  {     1.0f, 1.0f }},
                 {{xpos + w, ypos + h},  { 1.0f, 0.0f }}
             };

             auto pmodelbuffer = m_poolmodelbufferCharacter.get();

             if (pmodelbuffer->is_null())
             {

                pmodelbuffer->create_vertex_buffer < ::graphics3d::sequence2_uv>(6);

             }

             pmodelbuffer->sequence2_uv_set_vertex(vertices, 6)*/

             //glBindTexture(GL_TEXTURE_2D, ch.TextureID);
          //// update content of VBO memory
          //glBindBuffer(GL_ARRAY_BUFFER, pfont->m_VBO);
          //glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // be sure to use glBufferSubData and not glBufferData

          //auto pcommandbuffer = gpu_context()->m_pgpurenderer->getCurrentCommandBuffer2();

          //pcommandbuffer->

          //pcommandbuffer->draw(ch.m_ppixmap);

          //ch.m_ppixmap;
          //glBindBuffer(GL_ARRAY_BUFFER, 0);
          //// render quad
          //glDrawArrays(GL_TRIANGLES, 0, 6);
          // now advance cursors for next glyph (note that advance is number of 1/64 pixels)
            x += ch.Advance; // bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))

         }

      }

      return int_size(x, y);

      //wstring wstr = lpszString;

      //character_count iRange = 0;
      //character_count i = 0;
      //character_count iLen;
      //const ::scoped_string & scopedstr = lpszString;
      //while(i < iIndex)
      //{
      //   iLen = ::str::get_utf8_char(psz).length();
      //   iRange++;
      //   i += iLen;
      //   unicode_increment(psz);
      //   if(psz == nullptr)
      //      break;
      //   if(*psz == '\0')
      //      break;
      //}

      //set(m_pfont);

      //::pointer<font>pfont = m_pfont;

      //::int_size s = { 0 };

      //::GetTextExtentPointW(pfont->m_hdcFont, wstr, wstr.get_length(), &s);

      //return s;

   }


   ::typeface::face* graphics::get_face(::write_text::font* pfont)
   {


      ::cast < gpu::draw2d>pdraw2d = draw2d();

      auto pface = pdraw2d->_get_face(pfont);

      if (!pface->m_pgpurenderer)
      {

         auto prenderer = gpu_context()->m_pgpurenderer;

         pface->initialize_gpu_buffer(prenderer);

      }

      return pface;

   }


   void graphics::text_out(double x, double yParam, const ::scoped_string& scopedstr)
   {

      //text_out_2025_06(x, yParam, scopedstr);

      //::gpu::graphics::text_out(x, yParam, scopedstr);

      auto pcontext = gpu_context();

      __USES_TRANSFORM(pcontext);

      ::gpu::context_lock contextlock(pcontext);

      //return;
      // activate corresponding render state	

      if (!m_pgpushaderTextOut)
      {

      


         m_pgpushaderTextOut = __øcreate< ::gpu::shader >();

         auto pcontext = gpu_context();

         m_pgpushaderTextOut->m_bEnableBlend = true;
         m_pgpushaderTextOut->m_bDisableDepthTest = true;
         
         pcontext->white_to_color_sampler_shader_setup(m_pgpushaderTextOut);

         m_pgpushaderTextOut->initialize_shader_with_block(
            pcontext->m_pgpurenderer,
            pcontext->white_to_color_sampler_vert(),
            pcontext->white_to_color_sampler_frag(),
            {},
            {},
            {},
            pcontext->input_layout<::graphics3d::sequence2_uv>()
         );

      }

      m_pgpushaderTextOut->bind();
      auto color = m_pbrush->m_color;
      //shader.use();
      ::cast<::gpu::shader>pshader = m_pgpushaderTextOut;
      ::glm::vec4 vec4TextColor{ __expand_float_pre_rgba(color) };
      pshader->set_vec4("textColor", vec4TextColor);
      // glUniform3f(glGetUniformLocation(shader.ID, "textColor"), color.x, color.y, color.z);
      pshader->setup_sampler_and_texture("text", 0);
      //auto pcontext = gpu_context();

      glm::mat4 projection = glm::ortho(
         0.0f,
         static_cast<float>(pcontext->m_rectangle.width()),
         static_cast<float>(pcontext->m_rectangle.height()),
         0.0f);
      pshader->set_mat4("projection", projection);

      set(m_pfont);

      ::pointer<::write_text::font>pfont = m_pfont;

      auto pgpuface = get_face(pfont);
      ::cast < ::typeface::face>pface = pgpuface;

      //pcontext->set_topic_texture(0);


      //glEnable(GL_BLEND);
      //glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

      //glDisable(GL_DEPTH_TEST);
      //glDepthMask(GL_FALSE);

      //glBindVertexArray(pface->m_FaceVAO);
      //GLCheckError("");
      auto pcommandbuffer = pcontext->m_pgpurenderer->getCurrentCommandBuffer2();
      
      pface->box_model_buffer()->bind(pcommandbuffer);

      // iterate through all characters
      ::string strChar;
      ::string str(scopedstr);
      auto psz = str.c_str();

      if (str == "Options")
      {

         warning() << "draw_text: " << str;

      }
      //float scale;
      //if (pfont->m_fontsize.eunit() == e_unit_point)
      //{
      //   scale = pfont->m_fontsize.as_float() / FONT_POINT_DENOMINATOR;
      //}
      //else
      //{
      //   scale = pfont->m_fontsize.as_float() / FONT_PIXEL_DENOMINATOR;
      //}
      //auto y = m_pgpucontextCompositor->m_rectangle.height() - yParam - pface->m_iPixelSize;
      auto y = yParam;


      ::int_point point(x, y);
      int Δx = 0;
      __TRANSFORM(point);

      //auto pcontext = gpu_context();

      point.y() = pcontext->m_rectangle.height() - point.y() - pface->m_iPixelSize;

      pcontext->set_cull_face();


      ::gpu::model_buffer* pmodelbuffer = nullptr;
      ::gpu::pixmap* ppixmap = nullptr;
      //glEnable(GL_BLEND);
      //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      while (next_unicode_character(strChar, psz))
      {

         auto& ch = pface->get_character(strChar);
         float h2 = (float)(ch.Size.y - ch.Bearing.y);
         float xpos = (float) (point.x() + Δx + ch.Bearing.x);
         float ypos = (float) (point.y() + h2);

         float w = (float) ch.Size.x;
         float h = (float) ch.Size.y;
         // update VBO for each character
         ::array < ::graphics3d::sequence2_uv > vertices = {
             {{xpos,     ypos + h},{   0.0f, 0.0f }},
             {{xpos,     ypos   }, {   0.0f, 1.0f }},
             {{xpos + w, ypos   }, {   1.0f, 1.0f }},
             {{xpos,     ypos + h},{   0.0f, 0.0f }},
             {{xpos + w, ypos   }, {   1.0f, 1.0f }},
             {{xpos + w, ypos + h},{   1.0f, 0.0f} }
         };
         // render glyph texture over quad
         if (ch.m_ppixmap)
         {

            pmodelbuffer = m_poolmodelbufferCharacter.get();

            if (pmodelbuffer->is_new())
            {

               pmodelbuffer->initialize_gpu_context_object(pcontext);

               pmodelbuffer->bind(pcommandbuffer);

               pmodelbuffer->create_vertices < ::graphics3d::sequence2_uv>(6);

               pmodelbuffer->unbind(pcommandbuffer);

               //pmodelbuffer->defer_set_input_layout(m_pgpushaderTextOut->m_pinputlayout);

            }

            //pmodelbuffer->set_vertex_array(vertices, 6);
            ppixmap = ch.m_ppixmap;
            ppixmap->bind_texture(pshader);
            //glBindTexture(GL_TEXTURE_2D, ch.TextureID);
            //GLCheckError("");
            //// update content of VBO memory
            //int iVbo = pface->m_FaceVBO;
            //glBindBuffer(GL_ARRAY_BUFFER, iVbo);
            //GLCheckError("");
            //glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // be sure to use glBufferSubData and not glBufferData
            //GLCheckError("");
            //glBindBuffer(GL_ARRAY_BUFFER, 0);
            //GLCheckError("");
            // render quad
            // 
            // 

            auto pcommandbuffer = gpu_context()->m_pgpurenderer->getCurrentCommandBuffer2();

            //pcommandbuffer->draw(ch.m_ppixmap);

            pmodelbuffer->bind(pcommandbuffer);

            //pmodelbuffer->m_pbufferVertex->bind();

            pmodelbuffer->set_vertices(vertices);

            pmodelbuffer->draw(pcommandbuffer);

            //pmodelbuffer->unbind(pcommandbuffer);

            //glDrawArrays(GL_TRIANGLES, 0, 6);
            //GLCheckError("");
            // now advance cursors for next glyph (note that advance is number of 1/64 pixels)
            Δx += ch.Advance; // bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))

         }
      }

      if (pmodelbuffer)
      {

         pmodelbuffer->unbind(pcommandbuffer);

      }

      if (ppixmap)
      {

         ppixmap->unbind_texture(pshader);

      }

      //glBindVertexArray(0);
      //GLCheckError("");


      //glBindTexture(GL_TEXTURE_2D, 0);
      //GLCheckError("");
      //glDisable(GL_CULL_FACE);
      //GLCheckError("");

      pcontext->set_cull_face(false);
      m_pgpushaderTextOut->unbind();
   }

} // namespace gpu



