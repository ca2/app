// Created by camilo on 2025-05-17 04:14 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "engine.h"
#include "input.h"
#include "renderer.h"
#include "scene.h"
#include "shader.h"
#include "types.h"
#include "acme/exception/interface_only.h"
#include "acme/platform/application.h"
#include "acme/platform/node.h"
#include "apex/database/client.h"
#include "apex/database/stream.h"
#include "aura/graphics/gpu/approach.h"
#include "aura/graphics/gpu/context.h"
#include "aura/graphics/gpu/cpu_buffer.h"
#include "aura/graphics/gpu/device.h"
#include "aura/graphics/gpu/renderer.h"
#include "aura/graphics/graphics3d/camera.h"
#include "aura/user/user/graphics3d.h"
#include "aura/graphics/image/target.h"
#include "aura/platform/application.h"
#include <chrono>


namespace graphics3d
{


   engine::engine()
   {

      m_bCreatedGlobalUbo = false;

   }


   engine::~engine()
   {


   }


   void engine::initialize_engine(::user::graphics3d* pimpact)
   {

      m_pimpact = pimpact;

      m_pimpact->m_pengine = this;

      m_papproach = m_papplication->get_gpu();

      m_pinput = __allocate::graphics3d::input();
      m_pinput->m_pimpact = m_pimpact;
      m_pinput->m_pengine = this;
      m_pinput->m_pkeymap = m_pimpact->m_pkeymap;

   }


   void engine::on_render_frame()
   {

      if (m_rectanglePlacementNew.is_empty())
      {

         return;

      }

      auto prenderer = m_pgpucontext->get_renderer(::gpu::e_scene_3d);

      _prepare_frame();

      prenderer->on_new_frame();

      if (auto pframe = prenderer->beginFrame())
      {

         on_begin_frame();
         // render
         prenderer->on_begin_render(pframe);

         if (m_pscene->global_ubo().size() > 0)
         {

            update_global_ubo(m_pgpucontext);

         }

         m_pscene->on_render(m_pgpucontext);

         prenderer->on_end_render(pframe);

         prenderer->endFrame();

      }

   }


   void engine::create_global_ubo(::gpu::context* pgpucontext)
   {

      auto iGlobalUboSize = m_pscene->global_ubo().size();

      if (iGlobalUboSize > 0)
      {

         m_pgpucontext->create_global_ubo((int)iGlobalUboSize, pgpucontext->get_renderer(::gpu::e_scene_3d)->get_frame_count());

      }

   }


   //::file::path engine::shader_path(const ::file::path& pathShader)
   //{

   //   return pathShader;

   //}


   void engine::on_begin_frame()
   {


   }


   void engine::on_update_frame()
   {

      if (!m_pcamera)
      {

         m_pcamera = m_pscene->get_default_camera();

         m_transform.translation = m_pcamera->m_locationPosition;

         m_transform.rotation.x = m_pcamera->m_fPitch;

         m_transform.rotation.y = m_pcamera->m_fYaw;

         //VkcCamera camera(glm::vec3(0.0f, 2.0f, -10.0f), .0f, 0.0f);

         //auto viewerObject = __øcreate <::graphics3d::scene_object>();
         //papp->m_pimpact->m_bLastMouse = true;
         //viewerObject->m_transform.translation.z = -2.5f;
         //m_transform.translation.z = -2.5f;

         ::pointer <::database::client> pdatabaseclient = m_papplication;

         if (pdatabaseclient)
         {

            //pdatabaseclient->datastream()->get_block("camera", m_pcamera->as_block());
            //pdatabaseclient->datastream()->get_block("transform", as_memory_block(m_transform));
            //pdatabaseclient->datastream()->get_block("input", m_pinput->as_block());

         }

      }

      //m_fFrameTime = fFrameTime;

      m_pinput->prepare_mouse_input();

      m_pinput->process_mouse_input();

      //m_pinput->updateLook(m_pinput->getX(), m_pinput->getY(), transform);

      m_pinput->process_keyboard_input();

      //cameraController.moveInPlaneXZ(m_pimpact, frameTime, viewerObject);

      //m_pcamera->setViewYXZ(m_transform.translation, m_transform.rotation);


      float aspect = m_pimpact->getAspectRatio();

      m_pcamera->setPerspectiveProjection(glm::radians(50.f), aspect, 0.1f, 100.f);

      m_pcamera->UpdateCameraVectors();

      m_pcamera->m_matrixImpact = glm::lookAt(m_pcamera->m_locationPosition,
         m_pcamera->m_locationPosition + m_pcamera->m_poleFront,
         m_pcamera->m_poleWorldUp);

      m_pcamera->m_matrixAntImpact = glm::inverse(m_pcamera->m_matrixImpact);

   }


   void engine::run()
   {





      //auto papp = get_app();

      //__øconstruct(m_pgpucontext);

      //m_pgpucontext->initialize_context(papp->m_pimpact);

      //__construct_new(m_prenderer);

      //m_prenderer->initialize_renderer(papp->m_pimpact, m_pgpucontext);

      //auto pglobalpoolbuilder = __allocate descriptor_pool::Builder();

      //pglobalpoolbuilder->initialize_builder(m_pgpucontext);
      //pglobalpoolbuilder->setMaxSets(render_pass::MAX_FRAMES_IN_FLIGHT);
      //pglobalpoolbuilder->addPoolSize(VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, render_pass::MAX_FRAMES_IN_FLIGHT);

      //m_pglobalpool = pglobalpoolbuilder->build();

      ////m_pglobalpool->initialize_pool(pgpucontext);

      ////= __allocate
      ////   descriptor_pool::Builder(pgpucontext)
      ////   .setMaxSets(swap_chain_render_pass::MAX_FRAMES_IN_FLIGHT)
      ////   .addPoolSize(VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, swap_chain_render_pass::MAX_FRAMES_IN_FLIGHT)
      ////   .build();
      //m_pscene->on_load_scene();

      ////pgpucontext = __allocate context(m_pvulkandevice);

      //::pointer_array<buffer> uboBuffers;

      //uboBuffers.set_size(render_pass::MAX_FRAMES_IN_FLIGHT);

      //::cast < context > pgpucontext = m_pgpucontext;

      //for (int i = 0; i < uboBuffers.size(); i++)
      //{

      //   uboBuffers[i] = __allocate buffer();

      //   uboBuffers[i]->initialize_buffer(
      //      pgpucontext,
      //      sizeof(GlobalUbo),
      //      1,
      //      VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
      //      VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT);

      //   uboBuffers[i]->map();

      //}
      //auto globalSetLayout = set_descriptor_layout::Builder(pgpucontext)
      //   .addBinding(0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_ALL_GRAPHICS)
      //   .build();


      //std::vector<VkDescriptorSet> globalDescriptorSets(render_pass::MAX_FRAMES_IN_FLIGHT);

      //for (int i = 0; i < globalDescriptorSets.size(); i++)
      //{

      //   auto bufferInfo = uboBuffers[i]->descriptorInfo();

      //   descriptor_writer(*globalSetLayout, *m_pglobalpool)
      //      .writeBuffer(0, &bufferInfo)
      //      .build(globalDescriptorSets[i]);

      //}

      //simple_render_system simpleRenderSystem{
      //    pgpucontext,
      //    m_prenderer->getRenderPass(),
      //    globalSetLayout->getDescriptorSetLayout() };

      //point_light_system pointLightSystem{
      //    pgpucontext,
      //    m_prenderer->getRenderPass(),
      //    globalSetLayout->getDescriptorSetLayout()
      //};

      //camera camera{ glm::vec3(0.0f, 2.0f, -15.0f), -90.0f, 0.0f };
      //{ glm::vec3(0.0f, 2.0f, -15.0f), -90.0f, 0.0f };
      //m_pcamera = m_pscene->get_default_camera();

      ////VkcCamera camera(glm::vec3(0.0f, 2.0f, -10.0f), .0f, 0.0f);

      ////auto viewerObject = __øcreate <::graphics3d::scene_object>();
      ////papp->m_pimpact->m_bLastMouse = true;
      ////viewerObject->m_transform.translation.z = -2.5f;
      //m_transform.translation.z = -2.5f;
      //TransformComponent transform;

      /*    glfwSetInputMode(_window.getGLFWwindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
          glfwSetWindowUserPointer(_window.getGLFWwindow(), &cameraController);*/
          //m_pinput->m_bMouseAbsolute;

      auto pimpact = m_pimpact;

      m_stdtimepoint = std::chrono::high_resolution_clock::now();
      //while (!_window.shouldClose())

      set_ok_flag();

      m_pgpucontext->send([this]()
         {

            while (task_get_run())
            {

               task_iteration();

               if (m_rectanglePlacementNew.is_empty())
               {

                  continue;

               }

               ::gpu::context_guard guard(m_pgpucontext);

               m_pgpucontext->make_current();

               m_pgpucontext->set_placement(m_rectanglePlacementNew);

               auto prenderer = m_pgpucontext->get_renderer(::gpu::e_scene_3d);

               prenderer->defer_update_renderer();

               try
               {

                  m_pgpucontext->m_pengine->_do_frame_step();

               }
               catch (...)
               {

               }

               auto pdevice = m_pgpucontext->m_pgpudevice;

               pdevice->on_top_end_frame();

         }

      });

      ::pointer <::database::client> pdatabaseclient = m_papplication;

      if (pdatabaseclient)
      {

         pdatabaseclient->datastream()->set("input", m_pinput->as_block());
         pdatabaseclient->datastream()->set("transform", as_memory_block(m_transform));
         pdatabaseclient->datastream()->set("camera", m_pcamera->as_block());

      }

      //if (pgpucontext->logicalDevice() != VK_NULL_HANDLE)
      //{

      //   vkDeviceWaitIdle(pgpucontext->logicalDevice());

      //}

   }


   void engine::defer_start(::user::interaction* puserinteraction, const ::int_rectangle& rectanglePlacement)
   {

      auto papp = get_app();

      auto pgpu = papp->get_gpu();

      auto pwindow = puserinteraction->window();

      ::cast < ::gpu::device > pgpudevice = pgpu->get_device(pwindow, rectanglePlacement);

      ::pointer < ::gpu::context > pgpucontext;

      //if (m_papplication->m_bUseSwapChainWindow)
      //{

      //   auto pwindow = m_pimpact->window();

      //   pgpucontext = pgpudevice->start_swap_chain_context(this, pwindow);

      //}
      //else
      //if (!m_papplication->m_bUseSwapChainWindow){

         //auto callbackImage32CpuBuffer = m_callbackImage32CpuBuffer;

      if (m_papplication->m_bUseSwapChainWindow)
      {

         pgpucontext = pgpudevice->start_gpu_output_context(this, ::gpu::e_output_gpu_buffer, rectanglePlacement);

      }
      else
      {

         pgpucontext = pgpudevice->start_gpu_output_context(this, ::gpu::e_output_cpu_buffer, rectanglePlacement);

      }

      //      }

      set_ok_flag();

      pgpucontext->post([this, pgpucontext, rectanglePlacement]()
         {

            m_pimpact->on_load_engine();

            m_pgpucontext = pgpucontext;

            pgpucontext->m_pengine = this;

            if (m_pgpucontext->m_eoutput == ::gpu::e_output_cpu_buffer)
            {

               run();

            }

         });

      m_rectanglePlacementNew = rectanglePlacement;

   }


   void engine::update_global_ubo(::gpu::context* pgpucontext)
   {

      if (m_pscene->global_ubo().size() > 0)
      {

         m_pscene->on_update_global_ubo(pgpucontext);

         m_pgpucontext->update_global_ubo(m_pscene->global_ubo().m_block);

      }

   }



   void engine::do_frame_step(::gpu::context* pcontext)
   {

      if (m_rectanglePlacementNew.is_empty())
      {

         return;

      }

      ::gpu::rear_guard rear_guard(pcontext);

      m_pgpucontext->send([this]()
         {

            ::gpu::context_guard guard(m_pgpucontext);

            m_pgpucontext->make_current();

            m_pgpucontext->set_placement(m_rectanglePlacementNew);

            auto prenderer = m_pgpucontext->get_renderer(::gpu::e_scene_3d);

            prenderer->defer_update_renderer();

            try
            {

               m_pgpucontext->m_pengine->_do_frame_step();

            }
            catch (...)
            {

            }

         });

      pcontext->make_current();

      auto prendererSource = m_pgpucontext->m_pgpurenderer;

      auto prenderer = pcontext->m_pgpurenderer;

      prenderer->blend(prendererSource);

      prenderer->soft_restore_context();

   }


   void engine::_001OnDraw(::draw2d::graphics_pointer& pgraphics)
   {

      auto pgpucontext = m_pgpucontext;

      if (pgpucontext->m_eoutput == ::gpu::e_output_cpu_buffer)
      {

         auto pcpubuffer = pgpucontext->m_pcpubuffer;

         if (pcpubuffer)
         {

            auto pimagetarget = pcpubuffer->m_pimagetarget;

            if (::is_set(pimagetarget))
            {

               pimagetarget->_001OnDraw(pgraphics);

            }

         }

      }
      else
      {

         auto pcontext = m_pgpucontext->m_pgpudevice->current_context();

         do_frame_step(pcontext);

      }

   }


   void engine::_engine_on_frame_context_initialization()
   {


   }


   void engine::_prepare_frame()
   {

      if (!m_bEngineOnFrameContextInitialization)
      {

         m_bEngineOnFrameContextInitialization = true;

         _engine_on_frame_context_initialization();

      }

      if (!m_rectanglePlacementNew.is_empty())
      {

         if (m_rectanglePlacementNew != m_rectanglePlacement)
         {

            m_rectanglePlacement = m_rectanglePlacementNew;

            auto pgpucontext = m_pgpucontext;

            pgpucontext->set_placement(m_rectanglePlacement);

            defer_update_engine(m_rectanglePlacement);

            //if (pgpucontext->m_pgpurenderer)
            //{

            //   //pgpucontext->create_offscreen_buffer(m_rectanglePlacement.size());

            //   
            //   //m_pimpact->on_load_engine();

            //   //run();

            //   //m_pimpact->m_ptaskEngine.release();

            //   //return;


            //   //m_pinput = __allocate::graphics3d::input();

            //   //m_pinput->m_pimpact = m_pimpact;

            //   //m_pcamera = __allocate::graphics3d::camera(glm::vec3(0.0f, 3.0f, 3.0f), -90.0f, 0.0f);

            //   ////m_pcamera->m_pimpact

            //   ////m_pglcapplication = m_pimpact->start_opengl_application();
            //   ////__øconstruct(m_pgpucontext);

            //   //if (!m_papplication->m_bUseSwapChainWindow)
            //   //{

            //   //   pgpucontext->m_pgpucontext->resize_offscreen_buffer({ cx, cy });

            //   //}

            //   //m_prenderer = __allocate::graphics3d_opengl::renderer();

            //   ////return;
            //   //// Initialize the game logic and scene data
            //   ////Init();

            //   //pgpucontext->m_pgpucontext->m_timeSample = 1_s / 60.0;

            //   //m_pgpucontext->m_rendera.add_unique(this);

            //}

         }

      }


   }


   void engine::_do_frame_step()
   {

      auto newTime = std::chrono::high_resolution_clock::now();

      float frameTime = std::chrono::duration<float, std::chrono::seconds::period>(newTime - m_stdtimepoint).count();

      m_stdtimepoint = newTime;

      m_fFrameTime = frameTime;

      if (!m_rectanglePlacementNew.is_empty())
      {

         on_update_frame();

         on_render_frame();

      }

   }


   void engine::defer_update_engine(const ::int_rectangle& rectanglePlacement)
   {

      //if (!m_prenderer)
      //{

      //   __øconstruct(m_prenderer);

      //   //::graphics3d::engine::m_prenderer = m_prenderer;

      //   m_prenderer->initialize_renderer(m_pgpucontext, m_pgpucontext->m_eoutput);

      //}


      //m_prenderer->on_context_resize();
      //m_pglobalpool->initialize_pool(pgpucontext);

      //= __allocate
      //   descriptor_pool::Builder(pgpucontext)
      //   .setMaxSets(swap_chain_render_pass::MAX_FRAMES_IN_FLIGHT)
      //   .addPoolSize(VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, swap_chain_render_pass::MAX_FRAMES_IN_FLIGHT)
      //   .build();

      //pgpucontext = __allocate context(m_pvulkandevice);

      //          m_prenderer->getRenderPass(),
        //        globalSetLayout->getDescriptorSetLayout()
          //  };

      m_pscene->defer_load_scene(m_pgpucontext);
      if (!m_bCreatedGlobalUbo)
      {

         m_bCreatedGlobalUbo = true;

         auto iGlobalUboSize = m_pscene->global_ubo().size();

         if (iGlobalUboSize > 0)
         {

            create_global_ubo(m_pgpucontext);

         }


      }


   }


   void engine::on_layout(const ::int_rectangle& rectanglePlacement)
   {

      m_rectanglePlacementNew = rectanglePlacement;

      //      auto pgpucontext = m_pgpucontext;
      //
      //if (!pgpucontext)
      //{
      //
      //   return;
      //
      //}
      //
      //pgpucontext->post([this, cx, cy]
      //   {
      //
      //      auto pgpucontext = m_pgpucontext;
      //
      //      if (pgpucontext->m_prenderer)
      //      {
      //
      //         pgpucontext->m_prenderer->set_placement({cx, cy});
      //
      //         //m_pimpact->on_load_engine();
      //
      //         //run();
      //
      //         //m_pimpact->m_ptaskEngine.release();
      //
      //         //return;
      //
      //
      //         //m_pinput = __allocate::graphics3d::input();
      //
      //         //m_pinput->m_pimpact = m_pimpact;
      //
      //         //m_pcamera = __allocate::graphics3d::camera(glm::vec3(0.0f, 3.0f, 3.0f), -90.0f, 0.0f);
      //
      //         ////m_pcamera->m_pimpact
      //
      //         ////m_pglcapplication = m_pimpact->start_opengl_application();
      //         ////__øconstruct(m_pgpucontext);
      //
      //         //if (!m_papplication->m_bUseSwapChainWindow)
      //         //{
      //
      //         //   pgpucontext->m_pgpucontext->resize_offscreen_buffer({ cx, cy });
      //
      //         //}
      //
      //         //m_prenderer = __allocate::graphics3d_opengl::renderer();
      //
      //         ////return;
      //         //// Initialize the game logic and scene data
      //         ////Init();
      //
      //         //pgpucontext->m_pgpucontext->m_timeSample = 1_s / 60.0;
      //
      //         //m_pgpucontext->m_rendera.add_unique(this);
      //
      //      }
      //
      //      //pgpucontext->resize_offscreen_buffer({ cx, cy });
      //
      //      ////on_layout(cx, cy);
      //
      //      //m_pimpact->m_iWidth = cx;
      //      //m_pimpact->m_iHeight = cy;
      //
      //   });
      //


   }


   void engine::on_mouse_move(float x, float y)
   {


   }


   ::pointer<model> engine::create_tinyobjloader_model(const ::file::path& path)
   {

      model::tinyobjloader_Builder builder{};

      builder.loadModel(m_pgpucontext, path);

      auto pmodel = __øcreate < model>();

      pmodel->initialize_model(m_pgpucontext, builder);

      return pmodel;

   }




   void engine::add_scene(::graphics3d::scene* pscene)
   {

      m_mapScene[pscene->m_strName] = pscene;

   }





   void engine::set_current_scene(::graphics3d::scene* pscene)
   {

      m_pscene = pscene;

   }



} // namespace graphics3d


