// Created by camilo on 2025-05-31 15:32 <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "graphics.h"
#include "acme/platform/application.h"
#include "aura/user/user/interaction.h"
#include "aura/graphics/graphics/graphics.h"
#include "aura/windowing/window.h"
#include "bred/gpu/approach.h"
#include "bred/gpu/context.h"
#include "bred/gpu/device.h"
#include "bred/gpu/model_buffer.h"
#include "bred/gpu/renderer.h"
#include "bred/gpu/render_target.h"
#include "bred/gpu/swap_chain.h"


namespace gpu
{


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

      auto pcontext = ((graphics *)this)->gpu_context();

      return ::is_set(this) & ::is_set(pcontext);

   }



   void graphics::on_begin_draw()
   {

      //thread_select();

      auto pcontext = gpu_context();

      auto pgpudevice = pcontext->m_pgpudevice;

      int iFrameIndex = pcontext->m_pgpurenderer->m_pgpurendertarget->get_frame_index();

      m_poolmodelbufferRectangle.m_ppoolgroup = pgpudevice->frame_pool_group(iFrameIndex);
      m_poolmodelbufferCharacter.m_ppoolgroup = pgpudevice->frame_pool_group(iFrameIndex);


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


   void graphics::create_for_window_draw2d(::user::interaction * puserinteraction, const ::int_size& size)
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



   void graphics::soft_unbind_draw2d_compositor(::gpu::layer* player)
   {

      auto pcontext = gpu_context();

      pcontext->__soft_unbind_draw2d_compositor(this, player);

   }


   void graphics::_fill_quad(const ::double_point points[4], const ::color::color& color)
   {

      auto pcontext = gpu_context();

      auto prenderer = pcontext->m_pgpurenderer;

      auto pgpucontext = prenderer->m_pgpucontext;

      auto pgpudevice = pgpucontext->m_pgpudevice;

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
            //   pcontext->input_layout(::graphics3d::sequence2_color_properties()));

         }

         pshader = m_pshaderBlendRectangle;

      }

      //auto pcontext = gpu_context();

      //::cast < ::gpu_vulkan::context > pcontext = m_pgpucontextCompositor;

      auto pmodelbufferRectangle = m_poolmodelbufferRectangle.get();

      if (pmodelbufferRectangle->is_new())
      {

         pmodelbufferRectangle->sequence2_color_create_rectangle(pcontext);

      }

      //   auto & pmodelbuffer = m_pmodelbufferRectangle;

      //if (!pmodelbuffer)
      //{

      //   

      //   //   pmodel->m_vertexBuffer = createQuadVertexBuffer(
      //   //      pgpucontext->logicalDevice(),
      //   //      pgpucontext->m_pgpudevice->m_pphysicaldevice->m_physicaldevice,
      //   //      &pmodel->m_vertexMemory);

      //   //   pmodel->m_indexBuffer = nullptr;
      //   //   pmodel->m_indexMemory = nullptr;

      //   //}


      //}

      double_point quad[4];

      quad[0] = points[0];
      m_m1.transform(quad[0]);
      quad[1] = points[1];
      m_m1.transform(quad[1]);
      quad[2] = points[2];
      m_m1.transform(quad[2]);
      quad[3] = points[3];
      m_m1.transform(quad[3]);

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

      //vkCmdDraw(pcommandbuffer->m_vkcommandbuffer, 6, 1, 0, 0); // 6 vertices for two triangles
      //vkCmdEndRenderPass(cmd);


      pshader->unbind();
      //vkvg_rectangle(m_pdc, rectangle.left(), rectangle.top(), rectangle.right() - rectangle.left(),
        // rectangle.bottom() - rectangle.top());

      //m_particleaResetOnTopFrameEnd.add(pmodelbufferRectangle);

      //push_on_end_top_frame(m_modelbufferaRectangle, pmodelbufferRectangle);

      //g_z -= 0.0001;

   }



} // namespace gpu



