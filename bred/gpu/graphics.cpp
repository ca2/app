// Created by camilo on 2025-05-31 15:32 <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "binding.h"
#include "command_buffer.h"
#include "draw2d.h"
#include "frame.h"
#include "graphics.h"
#include "pixmap.h"
#include "texture.h"
#include "acme/platform/application.h"
#include "aura/user/user/interaction.h"
#include "aura/graphics/draw2d/_draw2d.h"
#include "aura/graphics/draw2d/pen.h"
#include "aura/graphics/graphics/graphics.h"
#include "aura/windowing/window.h"
#include "bred/gpu/_model.h"
#include "bred/gpu/bred_approach.h"
#include "bred/gpu/context.h"
#include "bred/gpu/context_lock.h"
#include "bred/gpu/debug_scope.h"
#include "bred/gpu/device.h"
#include "bred/gpu/model_buffer.h"
#include "bred/gpu/renderer.h"
#include "bred/gpu/render_state.h"
#include "bred/gpu/render_target.h"
#include "bred/gpu/swap_chain.h"
#include "bred/gpu/types.h"


namespace gpu
{

//
//#define __TRANSFORM(p) \
//   m_m1.transform(p); \
//p.y = iContextHeight - p.y
//
//#define __USES_TRANSFORM(pcontext) \
//auto iContextHeight = pcontext->m_rectangle.height()
//
//
//
   void thread_graphics(graphics* pgraphics)
   {

      ::get_task()->payload("gpu::graphics") = pgraphics;

   }



   graphics::graphics()
   {

      m_ppoolgroupFrame = nullptr;

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


   void graphics::on_new_frame()
   {

      auto pcontext = gpu_context();

      auto pgpudevice = pcontext->m_pgpudevice;

      auto prenderer = pcontext->get_gpu_renderer();

      auto prendertarget = prenderer->render_target();

      int iFrameIndex = prendertarget->get_frame_index();

      if (iFrameIndex < 0)
      {

         information("iFrameIndex gpu::graphics::on_new_frame");

      }

      auto ppoolgroupFrame = pgpudevice->frame_pool_group(iFrameIndex);

      m_ppoolgroupFrame = ppoolgroupFrame;

      for (auto& pool : m_mapModelBufferPool.payloads())
      {

         pool.m_ppoolgroup = m_ppoolgroupFrame;

      }

   }


   void graphics::on_begin_draw()
   {

      //thread_select();

      auto pcontext = gpu_context();

      auto pgpudevice = pcontext->m_pgpudevice;

      auto prenderer = pcontext->get_gpu_renderer();

      auto prendertarget = prenderer->render_target();

      if (prenderer->m_prenderstate->m_estate == ::gpu::e_state_began_render)
      {

         int iFrameIndex = prendertarget->get_frame_index();

         if (iFrameIndex < 0)
         {

            information("iFrameIndex < 0 ::gpu::graphics::on_begin_draw");

         }

         auto ppoolgroupFrame = pgpudevice->frame_pool_group(iFrameIndex);

         ppoolgroupFrame->m_pallocator = pgpudevice;

         ppoolgroupFrame->m_pongoingparticlearraysource = prenderer;

         ppoolgroupFrame->call_ongoing(e_call_off_to_pool);

         //m_poolmodelbufferCharacter.m_ppoolgroup = ppoolgroupFrame;
         //m_poolmodelbufferLine.m_ppoolgroup = ppoolgroupFrame;

         auto pparticlea = prenderer->current_frame_particle_array();

         if (pparticlea)
         {

            pparticlea->clear();

         }

      }

      if (m_egraphics == e_graphics_draw)
      {

         on_new_frame();

         //int iFrameIndex = pcontext->m_pgpurenderer->m_pgpurendertarget->get_frame_index();

         //m_poolmodelbufferRectangle.m_ppoolgroup = pgpudevice->frame_pool_group(iFrameIndex);
         //m_poolmodelbufferCharacter.m_ppoolgroup = pgpudevice->frame_pool_group(iFrameIndex);
         //m_poolmodelbufferLine.m_ppoolgroup = pgpudevice->frame_pool_group(iFrameIndex);

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
   void graphics::draw_rectangle(const ::double_rectangle &rectangle, ::draw2d::pen *ppen)
   {

      line(rectangle.top_left(), rectangle.top_right(), ppen);
      line(rectangle.top_right(), rectangle.bottom_right(), ppen);
      line(rectangle.bottom_right(), rectangle.bottom_left(), ppen);
      line(rectangle.bottom_left(), rectangle.top_left(), ppen);

      //::draw2d::graphics::draw_rectangle(rectangle, ppen);
     
   }

   //::gpu::renderer* graphics::end_draw_renderer_output()
   //{

   //   ::cast < ::windowing::window > pwindow = m_puserinteraction->m_pacmewindowingwindow;

   //   if (!m_pgpucontextCompositorOutput)
   //   {

   //      øconstruct(m_pgpucontextCompositorOutput);

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


   void graphics::on_gpu_context_placement_change(const ::int_rectangle &rectangle,
                                                  ::acme::windowing::window *pacmewindowingwindow)
   {

      ::gpu::compositor::on_gpu_context_placement_change(rectangle, pacmewindowingwindow);

   }


   ::geometry2d::matrix graphics::context_matrix(enum_transform_context etransformcontext)
   {

      auto pcontext = gpu_context();
      
      ::geometry2d::matrix contextmatrix;

      //contextmatrix.translate(0.5, -0.5);

      contextmatrix.append(context_scale_matrix());

      return contextmatrix;

   }


   ::geometry2d::matrix graphics::context_scale_matrix()
   {
      
      auto pcontext = gpu_context();
      
      auto size = pcontext->m_rectangle.size();

      ::geometry2d::matrix contextmatrix;

      contextmatrix.scale(2.0 / size.cx, 2.0 / size.cy);

      contextmatrix.translate(-2.0, -2.0);

      return contextmatrix;

   }


   void graphics::gpu_layer_on_before_end_render()
   {

      gpu_context()->defer_unbind_shader();

   }


   ::pool <::gpu::model_buffer >& graphics::model_buffer_pool(::draw2d::enum_model epool)
   {

      auto& pool = m_mapModelBufferPool[epool];

      if (!pool.m_ppoolgroup)
      {

         auto pcontext = gpu_context();

         auto pgpudevice = pcontext->m_pgpudevice;

         auto prenderer = pcontext->get_gpu_renderer();

         auto prendertarget = prenderer->render_target();

         int iFrameIndex = prendertarget->get_frame_index();

         auto ppoolgroupFrame = pgpudevice->frame_pool_group(iFrameIndex);

         pool.m_ppoolgroup = ppoolgroupFrame;

      }

      return pool;

   }


   ::gpu::model_buffer * graphics::model_buffer(::draw2d::enum_model emodel)
   {

      auto & pool = model_buffer_pool(emodel);

      auto pbuffer = pool.get();

      return pbuffer;

   }


   void graphics::update_matrix()
   {

      ::draw2d::graphics::update_matrix();

   }


   void graphics::on_end_draw()
   {

      
      //end_gpu_layer();
      if (m_egraphics == e_graphics_draw)
      {

         auto pcontext = gpu_context();

         ::gpu::context_lock contextlock(pcontext);

         pcontext->defer_unbind_shader();

         pcontext->on_end_draw_detach(this);

      }

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

      auto pgpudevice = m_papplication->get_gpu_approach()->get_gpu_device(m_puserinteraction->acme_windowing_window());

      auto pcontextMain = pgpudevice->main_context();

      // if (::is_null(pcontextMain) || !pcontextMain->m_bCreated)
      // {
      //
      //    return;
      //
      // }

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



   void graphics::defer_soft_unbind_draw2d_compositor(::gpu::layer* player)
   {

      auto pcontext = gpu_context();

      pcontext->__defer_soft_unbind_draw2d_compositor(this, player);

   }
   //
   //
   // void graphics::context_transform(::double_point & p, enum_transform_context etransformcontext)
   // {
   //
   //    context_matrix().transform(p);
   //
   // }


   ::double_size graphics::total_size()
   {

      auto pcontext = gpu_context();

      if (pcontext)
      {

         return pcontext->m_rectangle.size();

      }

      return ::gpu::graphics::total_size();

   }

   
   ::gpu::shader* graphics::rectangle_shader()
   {
      
      auto pcontext = gpu_context();
      
      ::gpu::shader* pshader = nullptr;

      if (m_ealphamode == ::draw2d::e_alpha_mode_set)
      {

         if (!m_pshaderSourceRectangle)
         {

            //auto pshadervertexinput = øallocate::gpu_vulkan::shader_vertex_input();

            //pshadervertexinput->m_bindings.add(
            //   {
            //      .binding = 0,
            //      .stride = sizeof(RectangleVertex),
            //      .inputRate = VK_VERTEX_INPUT_RATE_VERTEX,
            //   });

            //pshadervertexinput->m_attribs.add({ .location = 0, .binding = 0, .format = VK_FORMAT_R32G32B32_SFLOAT, .offset = offsetof(RectangleVertex, pos) });
            //pshadervertexinput->m_attribs.add({ .location = 1, .binding = 0, .format = VK_FORMAT_R32G32B32A32_SFLOAT, .offset = offsetof(RectangleVertex, color) });

            auto pshaderRectangle = øcreate<::gpu::shader>();

            m_pshaderSourceRectangle = pshaderRectangle;
            //m_pshaderBlendRectangle->m_bDisableDepthTest = true;
            m_pshaderSourceRectangle->m_bDisableDepthTest = true;
            //m_pshaderRectangle->m_iColorAttachmentCount = 2;
            m_pshaderSourceRectangle->m_bEnableBlend = false;
            m_pshaderSourceRectangle->m_etopology = ::gpu::e_topology_triangle_list;
            m_pshaderSourceRectangle->m_ecullmode = ::gpu::e_cull_mode_none;
            //m_pshaderRectangle->m_bAccumulationEnable = true;

            pcontext->initialize_rectangle_shader(m_pshaderSourceRectangle);

         }

         pshader = m_pshaderSourceRectangle;

      }
      else
      {

         if (!m_pshaderBlendRectangle)
         {

            //auto pshadervertexinput = øallocate::gpu_vulkan::shader_vertex_input();

            //pshadervertexinput->m_bindings.add(
            //   {
            //      .binding = 0,
            //      .stride = sizeof(RectangleVertex),
            //      .inputRate = VK_VERTEX_INPUT_RATE_VERTEX,
            //   });

            //pshadervertexinput->m_attribs.add({ .location = 0, .binding = 0, .format = VK_FORMAT_R32G32B32_SFLOAT, .offset = offsetof(RectangleVertex, pos) });
            //pshadervertexinput->m_attribs.add({ .location = 1, .binding = 0, .format = VK_FORMAT_R32G32B32A32_SFLOAT, .offset = offsetof(RectangleVertex, color) });

            auto pshaderRectangle = øcreate<::gpu::shader>();

            m_pshaderBlendRectangle = pshaderRectangle;
            //m_pshaderBlendRectangle->m_bDisableDepthTest = true;
            m_pshaderBlendRectangle->m_bDisableDepthTest = true;
            //m_pshaderRectangle->m_iColorAttachmentCount = 2;
            m_pshaderBlendRectangle->m_bEnableBlend = true;
            //m_pshaderRectangle->m_bAccumulationEnable = true;
            m_pshaderBlendRectangle->m_etopology = ::gpu::e_topology_triangle_list;
            m_pshaderBlendRectangle->m_ecullmode = ::gpu::e_cull_mode_none;
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

      ::gpu::debug_scope debugscopeFillQuad(::gpu::current_command_buffer(),
         "ødebug123 _fill_quad",
         false
      );

      if (::get_task()->payload("debug").as_int() == 123)
      {
         //::string strMessage;

         //strMessage.formatf("ødebug123 _fill_quad");

         //m_pgpucontextCompositor2->gpu_debug_message(strMessage);
         debugscopeFillQuad.start();

      }

      auto pcontext = gpu_context();

      //__USES_TRANSFORM(pcontext);

      auto prenderer = pcontext->m_pgpurenderer;

      auto pgpucontext = prenderer->m_pgpucontext;

      auto pgpudevice = pgpucontext->m_pgpudevice;

      ::gpu::context_lock contextlock(pcontext);

      ::gpu::shader* pshader = rectangle_shader();

      auto pmodelbufferRectangle = model_buffer(::draw2d::e_model_fill_rectangle);

      if (pmodelbufferRectangle->is_new())
      {

         pmodelbufferRectangle->initialize_gpu_context_object(pcontext);

         pmodelbufferRectangle->sequence2_color_create_rectangle(::gpu::current_frame());

      }

      ::block_array < double_point, 4 > quad;

      quad.add(points[0]);
      quad.add(points[1]);
      quad.add(points[2]);
      quad.add(points[3]);

      __transform(quad);

      context_matrix(e_transform_context_geometry).transform(quad);

      pmodelbufferRectangle->sequence2_color_set_rectangle(
         quad.data(),
         color);

      //pcontext->defer_bind(pshader);

      //vkCmdBeginRenderPass(cmd, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
      //auto pcommandbuffer = prenderer->getCurrentCommandBuffer2(::gpu::current_frame());

      auto pcommandbuffer = ::gpu::current_command_buffer();

      //auto ptextureTarget = prenderer->m_pgpurendertarget->current_texture(::gpu::current_frame());

      pcommandbuffer->set_shader(pshader);

      //VkDeviceSize offset = 0;
      ///vkCmdBindPipeline(pcommandbuffer->m_vkcommandbuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, graphicsPipeline);
      //vkCmdBindVertexBuffers(pcommandbuffer->m_vkcommandbuffer, 0, 1, &pmodelbuffer->m_vertexBuffer, &offset);

      //pcommandbuffer->set_model(pmodelbufferRectangle);

      pcommandbuffer->draw(pmodelbufferRectangle);

      //pmodelbufferRectangle->unbind(pcommandbuffer);

      //vkCmdDraw(pcommandbuffer->m_vkcommandbuffer, 6, 1, 0, 0); // 6 vertexes for two triangles
      //vkCmdEndRenderPass(cmd);



      pcontext->defer_unbind(pshader);
      //vkvg_rectangle(m_pdc, rectangle.left, rectangle.top, rectangle.right - rectangle.left,
        // rectangle.bottom - rectangle.top);

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

       //   m_psetdescriptorlayoutRectangle = ::gpu_vulkan::descriptor_set_layout::Builder(m_pgpucontextCompositor)
       //      .addBinding(0, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, VK_SHADER_STAGE_FRAGMENT_BIT)
       //      .build();

       //   auto pdescriptorpoolbuilder = øallocate::gpu_vulkan::descriptor_pool::Builder();

       //   pdescriptorpoolbuilder->initialize_builder(m_pgpucontextCompositor);
       //   pdescriptorpoolbuilder->setMaxSets(iFrameCount * 10);
       //   pdescriptorpoolbuilder->addPoolSize(VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, iFrameCount * 10);

       //   m_psetdescriptorlayoutRectangle = pdescriptorpoolbuilder->build();

       //}

       //// Rectangle descriptors
       //if (!m_psetdescriptorlayoutRectangle)
       //{

       //   int iFrameCount = prenderer->get_frame_count();

       //   m_psetdescriptorlayoutRectangle = ::gpu_vulkan::descriptor_set_layout::Builder(m_pgpucontextCompositor)
       //      .addBinding(0, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, VK_SHADER_STAGE_FRAGMENT_BIT)
       //      .build();

       //   auto pdescriptorpoolbuilder = øallocate::gpu_vulkan::descriptor_pool::Builder();

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

       //      //auto pshadervertexinput = øallocate::gpu_vulkan::shader_vertex_input();

       //      //pshadervertexinput->m_bindings.add(
       //      //   {
       //      //      .binding = 0,
       //      //      .stride = sizeof(RectangleVertex),
       //      //      .inputRate = VK_VERTEX_INPUT_RATE_VERTEX,
       //      //   });

       //      //pshadervertexinput->m_attribs.add({ .location = 0, .binding = 0, .format = VK_FORMAT_R32G32B32_SFLOAT, .offset = offsetof(RectangleVertex, pos) });
       //      //pshadervertexinput->m_attribs.add({ .location = 1, .binding = 0, .format = VK_FORMAT_R32G32B32A32_SFLOAT, .offset = offsetof(RectangleVertex, color) });


       //      auto pshaderRectangle = øcreate<::gpu::shader>();

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

       //      //auto pshadervertexinput = øallocate::gpu_vulkan::shader_vertex_input();

       //      //pshadervertexinput->m_bindings.add(
       //      //   {
       //      //      .binding = 0,
       //      //      .stride = sizeof(RectangleVertex),
       //      //      .inputRate = VK_VERTEX_INPUT_RATE_VERTEX,
       //      //   });

       //      //pshadervertexinput->m_attribs.add({ .location = 0, .binding = 0, .format = VK_FORMAT_R32G32B32_SFLOAT, .offset = offsetof(RectangleVertex, pos) });
       //      //pshadervertexinput->m_attribs.add({ .location = 1, .binding = 0, .format = VK_FORMAT_R32G32B32A32_SFLOAT, .offset = offsetof(RectangleVertex, color) });

       //      auto pshaderRectangle = øcreate<::gpu::shader>();

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
       ///
       auto r = rectangle;
      //r.bottom--;
      //r.right--;

      double_point points[4] = {
   {r.top_left()},
   {r.top_right()},
   {r.bottom_right()},
   {r.bottom_left()}
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
      //auto pcommandbuffer = prenderer->getCurrentCommandBuffer2(::gpu::current_frame());
      ////VkDeviceSize offset = 0;
      /////vkCmdBindPipeline(pcommandbuffer->m_vkcommandbuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, graphicsPipeline);
      ////vkCmdBindVertexBuffers(pcommandbuffer->m_vkcommandbuffer, 0, 1, &pmodelbuffer->m_vertexBuffer, &offset);

      //pmodelbufferRectangle->bind(pcommandbuffer);

      //pmodelbufferRectangle->draw(pcommandbuffer);

      ////vkCmdDraw(pcommandbuffer->m_vkcommandbuffer, 6, 1, 0, 0); // 6 vertexes for two triangles
      ////vkCmdEndRenderPass(cmd);


      //pshader->unbind();
      ////vkvg_rectangle(m_pdc, rectangle.left, rectangle.top, rectangle.right - rectangle.left,
      //  // rectangle.bottom - rectangle.top);

      ////m_particleaResetOnTopFrameEnd.add(pmodelbufferRectangle);

      ////push_on_end_top_frame(m_modelbufferaRectangle, pmodelbufferRectangle);

      ////g_z -= 0.0001;

   }



   void graphics::line(double x1, double y1, double x2, double y2, ::draw2d::pen* ppen)
   {

      auto pcontext = gpu_context();

      auto prenderer = pcontext->m_pgpurenderer;

      ::gpu::context_lock contextlock(pcontext);

      //__USES_TRANSFORM(pcontext);

      auto pshader = rectangle_shader();

      float g_z = 0.0f; // Assuming z is 0 for 2D rendering, adjust as needed

      ::double_point points1[2];

      points1[0].x = x1;
      points1[0].y = y1;
      points1[1].x = x2;
      points1[1].y = y2;

      __transform(points1[0]);
      __transform(points1[1]);

      auto size = pcontext->m_rectangle.size();

      //::geometry2d::matrix m;
      //m.translate(0.5, -0.5);
      //m.scale(2.0 / size.cx, 2.0 / size.cy);
      //m.translate(-1.0, -1.0);

      ::double_point_array pointa;

      ::double_point pointPen(ppen->m_dWidth, ppen->m_dWidth);

      ::draw2d::make_line_triangles_cap_butt_square(
         pointa,
         points1[0],
         points1[1],
         pointPen);

      context_matrix(e_transform_context_geometry).transform(pointa);

      auto color = m_ppen->m_color;

      float fA = color.f32_opacity();
      float fR = color.f32_red() * fA;
      float fG = color.f32_green() * fA;
      float fB = color.f32_blue() * fA;

      ::array<::graphics3d::sequence2_color> quadVertices;
      for (auto& point : pointa)
         quadVertices.add({ {(float)point.x, (float)point.y}, {fR, fG, fB, fA} });

      auto pmodelbuffer = model_buffer(::draw2d::e_model_line);

      if (pmodelbuffer->is_new())
      {

         pmodelbuffer->initialize_gpu_context_object(pcontext);

         pmodelbuffer->create_vertexes< ::graphics3d::sequence2_color>(6, true);

      }

      pmodelbuffer->set_vertexes(quadVertices);


      ::gpu::debug_scope debugscopeLine(::gpu::current_command_buffer(),
         "ødebug line:" + pmodelbuffer->m_strDebugString,
         false
      );

      if (pmodelbuffer->m_strDebugString.has_character())
      {

         debugscopeLine.start();

      }

      //auto pcommandbuffer = prenderer->getCurrentCommandBuffer2(::gpu::current_frame());
      auto pcommandbuffer = ::gpu::current_command_buffer();
      //;
      //;
      //auto ptextureTarget = prenderer->m_pgpurendertarget->current_texture(::gpu::current_frame());

      pcommandbuffer->set_shader(pshader);

      //pcommandbuffer->set_model(pmodelbuffer);

      pcommandbuffer->draw(pmodelbuffer);

      pmodelbuffer->unbind(pcommandbuffer);

      pcontext->defer_unbind(pshader);

      m_point.x = x2;
      m_point.y = y2;
   }


   
   double_size graphics::_get_text_extent(const ::scoped_string& scopedstr)
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
         if (ch.m_memory.size() > 0)
         {

            // ch.m_ppixmap = m_pgpurenderer->m_pgpucontext->create_gpu_pixmap({ ch.Size.x, ch.Size.y });
            //
            // //ch.m_ppixmap->initialize_gpu_pixmap(m_pgpurenderer, { ch.Size.x, ch.Size.y });
            //
            // if (::is_set(p))
            // {
            //
            //    ch.m_ppixmap->set_pixels(p);
            //
            // }

            /* ::graphics3d::sequence2_uv vertexes[6] = {
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

             pmodelbuffer->sequence2_uv_set_vertex(vertexes, 6)*/

             //glBindTexture(GL_TEXTURE_2D, ch.TextureID);
          //// update content of VBO memory
          //glBindBuffer(GL_ARRAY_BUFFER, pfont->m_VBO);
          //glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertexes), vertexes); // be sure to use glBufferSubData and not glBufferData

          //auto pcommandbuffer = gpu_context()->m_pgpurenderer->getCurrentCommandBuffer2(::gpu::current_frame());

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

      pcontext->defer_end_upload_command_buffer();

      return int_size(x, y);

      //wstring wstr = lpszString;

      //character_count iRange = 0;
      //character_count i = 0;
      //character_count iLen;
      //const ::scoped_string & scopedstr = lpszString;
      //while(i < iIndex)
      //{
      //   iLen = ::str::get_utf8_char(scopedstr).length();
      //   iRange++;
      //   i += iLen;
      //   unicode_increment(psz);
      //   if(scopedstr == nullptr)
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


   void graphics::get_text_metrics(::write_text::text_metric* pmetrics)
   {

      set(m_pfont);

      ::pointer<::write_text::font>pfont = m_pfont;

      ::pointer <::typeface::face> pface = get_face(pfont);

      pface->get_text_metric(pmetrics);

   }


   ::typeface::face* graphics::get_face(::write_text::font* pfont)
   {


      ::cast < gpu::draw2d>pdraw2d = draw2d();

      auto pface = pdraw2d->_get_face(pfont);

      // if (!pface->m_pgpurenderer)
      // {
      //
      //    auto prenderer = gpu_context()->m_pgpurenderer;
      //
      //    pface->initialize_gpu_buffer(prenderer);
      //
      // }
      //
      return pface;

   }


   void graphics::text_out(double x, double yParam, const ::scoped_string& scopedstr)
   {
      //return;

      //text_out_2025_06(x, yParam, scopedstr);

      //::gpu::graphics::text_out(x, yParam, scopedstr);

      auto pcontext = gpu_context();

      //__USES_TRANSFORM(pcontext);

      ::gpu::context_lock contextlock(pcontext);

      //return;
      // activate corresponding render state	

      if (!m_pgpushaderTextOut)
      {

         øconstruct(m_pgpushaderTextOut);

         auto pcontext = gpu_context();

         m_pgpushaderTextOut->m_bEnableBlend = true;
         m_pgpushaderTextOut->m_bDisableDepthTest = true;
         // m_pgpushaderTextOut->binding(0, 0).set();
         // m_pgpushaderTextOut->m_bindingSampler.m_strUniform = "text";
         m_pgpushaderTextOut->m_etopology = ::gpu::e_topology_triangle_strip;
         m_pgpushaderTextOut->m_ecullmode = ::gpu::e_cull_mode_none;
         // m_pgpushaderTextOut->m_bindingSampler.set(0);
         m_pgpushaderTextOut->m_iPushConstants = 1;

         auto pbindingSampler = m_pgpushaderTextOut->binding();
         pbindingSampler->m_strUniform = "text";
         pbindingSampler->m_ebinding = ::gpu::e_binding_sampler2d;
         pbindingSampler->m_iTextureUnit = 0;

         // pcontext->white_to_color_sampler_shader_setup(m_pgpushaderTextOut);

         m_pgpushaderTextOut->m_propertiesPushShared.set_properties(
            ::gpu_properties<::gpu::quad_texcoords_textColor>());
         pcontext->layout_push_constants(m_pgpushaderTextOut->m_propertiesPushShared, false);

         m_pgpushaderTextOut->initialize_shader_with_block(
            pcontext->m_pgpurenderer, pcontext->white_to_color_sampler_vert(),
            pcontext->white_to_color_sampler_frag() //, {::gpu::shader::e_descriptor_set_slot_local}, {} //,
                                                                                                      //,
            // pcontext->input_layout<::graphics3d::sequence2_uv>()
         );

      }

      //pcontext->defer_bind(m_pgpushaderTextOut);

      //auto pcommandbuffer = pcontext->m_pgpurenderer->getCurrentCommandBuffer2(::gpu::current_frame());

      auto pcommandbuffer = ::gpu::current_command_buffer();

      //auto ptextureTarget = pcontext->m_pgpurenderer->m_pgpurendertarget->current_texture(::gpu::current_frame());

      pcommandbuffer->set_shader(m_pgpushaderTextOut);


      ::string strMessage;

      ::string str(scopedstr);

      strMessage.formatf("bound text out shader '%s'", str.c_str());
      ::gpu::debug_scope debugscopeBoundTextOutShader(::gpu::current_command_buffer(), strMessage);
      //pcontext->gpu_debug_message(strMessage);

      auto color = m_pbrush->m_color;
      //shader.use();
      ::cast<::gpu::shader>pshader = m_pgpushaderTextOut;
      ::floating_sequence4 vec4TextColor{ __expand_float_pre_rgba(color) };
      pshader->set_sequence4("textColor", vec4TextColor);
      // glUniform3f(glGetUniformLocation(shader.ID, "textColor"), color.x, color.y, color.z);
      //pshader->setup_sampler_and_texture("text", 0);
      //auto pcontext = gpu_context();
      // auto size = pcontext->m_rectangle.size();
      // floating_matrix4 projection = glm::ortho(
      //    0.0f,
      //    static_cast<float>(size.width()),
      //    static_cast<float>(size.height()),
      //    0.0f);
      //pshader->push_properties();
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
      //auto pcommandbuffer = pcontext->m_pgpurenderer->getCurrentCommandBuffer2(::gpu::current_frame());

      if (!m_pmodelbufferTextOutDummy)
      {

         m_pmodelbufferTextOutDummy = øcreate < ::gpu::model_buffer >();

         m_pmodelbufferTextOutDummy->initialize_dummy_model(pcontext, 4);

      }
      
      //pface->box_model_buffer()->bind(pcommandbuffer);

      // iterate through all characters
      ::string strChar;

      //if (str == "hello_multiverse")
      //{

      //   warning() << "hello_multiverse";

      //}

      auto psz = str.c_str();

      //if (str == "Options")
      //{

      //   warning() << "draw_text: " << str;

      //}
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
      //auto pcontext = gpu_context();

      //point.y = pcontext->m_rectangle.height() - point.y - pface->m_iPixelSize;

      //pcontext->set_cull_face(::gpu::e_cull_mode_back);
      pcontext->set_cull_face(::gpu::e_cull_mode_none);

      //::gpu::texture* pgputexture = nullptr;
      ::gpu::pixmap* ppixmap = nullptr;

      //auto pcommandbuffer = gpu_context()->m_pgpurenderer->getCurrentCommandBuffer2(::gpu::current_frame());

      //pcommandbuffer->set_primitive_topology_triangle_strip();

      pcommandbuffer->set_model2(m_pmodelbufferTextOutDummy);

      //glEnable(GL_BLEND);
      //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      while (next_unicode_character(strChar, psz))
      {

         auto& ch = pface->get_character(strChar);
         float h2 = (float)(ch.Size.y - ch.Bearing.y);
         float xpos = (float) (point.x + Δx + ch.Bearing.x);
         //float ypos = (float) (point.y + h2);
         float ypos = (float) (point.y);

         float sizex = (float) ch.Size.x;
         float sizey = (float) ch.Size.y;
         // update VBO for each character
         // render glyph texture over quad

         if (sizex > 0 && sizey > 0)
         {

            auto ppixmapFetch = ch.get_gpu_pixmap(gpu_context()->m_pgpurenderer);

            if (ppixmapFetch
            && ppixmapFetch->m_pgputexture
            && ppixmapFetch->m_pgputexture->is_in_shader_sampling_state())
            {
               //if (pmodelbuffer->is_new())
               //{

               //   pmodelbuffer->initialize_gpu_context_object(pcontext);

               //   pmodelbuffer->bind(pcommandbuffer);

               //   pmodelbuffer->create_vertexes < ::graphics3d::sequence2_uv>(6, true);

               //   pmodelbuffer->unbind(pcommandbuffer);

               //   //pmodelbuffer->defer_set_input_layout(m_pgpushaderTextOut->m_pinputlayout);

               //}

               //pmodelbuffer->set_vertex_array(vertexes, 6);
               //ppixmap = ppixmap;

               //if (pshader->m_pgputextureBound != ppixmap->m_pgputexture)
               //{

               // pgputexture = ppixmap->m_pgputexture;

               ppixmap = ppixmapFetch;

               pcommandbuffer->set_source(ppixmap);
               //      pshader->bind_source(pcommandbuffer, ppixmap);
               ///   pshader->on_before_draw(pcommandbuffer);

               //}

               //pshader->set_matrix4("projection", projection);

               {

                  double l = (double) (xpos);
                  double t = (double) (ypos + ch.aHeight2);
                  double r = (double) (xpos + sizex);
                  double b = (double) (t + sizey);

                  double_point p1(l, t);
                  double_point p2(r, b);

                  __transform(p1);
                  __transform(p2);

                  context_matrix(e_transform_context_text).transform(p1);
                  context_matrix(e_transform_context_text).transform(p2);

                  ::floating_sequence4 quad(p1.x, p1.y, p2.x, p2.y
                     );


                  pshader->set_sequence4("quad", quad);

               }

               {

                  auto size = ppixmap->m_pgputexture->size();

                  auto w = (float)(size.width());
                  auto h = (float)(size.height());

                  float_rectangle rectangle = ppixmap->m_rectangle;

                  float l = rectangle.left / w;
                  float t = rectangle.top / h;
                  float r = rectangle.right / w;
                  float b = rectangle.bottom / h;

                  ::floating_sequence4 texcoords(l, t, r, b);

                  pshader->set_sequence4("texcoords", texcoords);

               }

               pshader->push_properties(pcommandbuffer);

               //glBindTexture(GL_TEXTURE_2D, ch.TextureID);
               //GLCheckError("");
               //// update content of VBO memory
               //int iVbo = pface->m_FaceVBO;
               //glBindBuffer(GL_ARRAY_BUFFER, iVbo);
               //GLCheckError("");
               //glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertexes), vertexes); // be sure to use glBufferSubData and not glBufferData
               //GLCheckError("");
               //glBindBuffer(GL_ARRAY_BUFFER, 0);
               //GLCheckError("");
               // render quad
               //
               //

               //pcommandbuffer->draw(ch.m_ppixmap);

               //pmodelbuffer->bind(pcommandbuffer);

               auto w = ppixmap->m_rectangle.width();

               auto h = ppixmap->m_rectangle.height();

               strMessage.formatf("char bound '%s' (%d, %d)%s", strChar.c_str(), w, h, pshader->m_strPushConstantsDebugging.c_str());

               ::gpu::debug_scope debugscope(::gpu::current_command_buffer(), strMessage);

               //pcontext->gpu_debug_message(strMessage);

               //pmodelbuffer->m_pbufferVertex->bind();



               /* ::array < ::graphics3d::sequence2_uv > vertexes = {
                 {{xpos,     ypos + h},{   l, t }},
                 {{xpos,     ypos   }, {   l, b }},
                 {{xpos + w, ypos   }, {   r, b }},
                 {{xpos,     ypos + h},{   l, t }},
                 {{xpos + w, ypos   }, {   r, b }},
                 {{xpos + w, ypos + h},{   r, t} }
                };*/


               //pmodelbuffer->_set_vertexes(vertexes);

               m_pmodelbufferTextOutDummy->m_bNew = false;
               pcommandbuffer->draw(m_pmodelbufferTextOutDummy);

               //pmodelbuffer->unbind(pcommandbuffer);

               //glDrawArrays(GL_TRIANGLES, 0, 6);
               //GLCheckError("");
               // now advance cursors for next glyph (note that advance is number of 1/64 pixels)

            }

         }

         Δx += ch.Advance; // bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))

      }

      if (m_pmodelbufferTextOutDummy)
      {

         m_pmodelbufferTextOutDummy->unbind(pcommandbuffer);

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

      pcontext->set_cull_face(::gpu::e_cull_mode_none);
      pcontext->defer_unbind(m_pgpushaderTextOut);
   }



   void graphics::defer_set_size(const ::int_size &size) 
   {
   
   gpu_context()->m_rectangle.set_size(size);
   
   }


} // namespace gpu



