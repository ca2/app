// Created by camilo on 2025-05-17 04:14 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "engine.h"
#include "input.h"
#include "renderer.h"
#include "scene.h"
#include "shader.h"
#include "types.h"
#include "acme/exception/interface_only.h"
#include "acme/parallelization/synchronous_lock.h"
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

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
// Function to flip a mat4 along the Z-axis
glm::mat4 flipZMat4(const glm::mat4& mat) {
   // Create a rotation matrix that flips along the Y-axis (180 degrees)
   glm::mat4 flip = glm::rotate(glm::mat4(1.0f), glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));

   // Multiply the rotation matrix with the original matrix
   return flip * mat;
}

namespace graphics3d
{


   engine::engine()
   {
      m_fYScale = 1.0f;
      m_bCreatedGlobalUbo = false;

   }


   engine::~engine()
   {


   }


   void engine::initialize_engine(::user::graphics3d* pusergraphics3d)
   {

      m_pusergraphics3d = pusergraphics3d;

      m_pusergraphics3d->m_pengine = this;

      m_papproach = m_papplication->get_gpu();

      m_pinput = __allocate::graphics3d::input();
      m_pinput->m_pusergraphics3d = m_pusergraphics3d;
      m_pinput->m_pengine = this;
      m_pinput->m_pkeymap = m_pusergraphics3d->m_pkeymap;

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

         {

            _synchronous_lock synchronouslock(m_pscene->synchronization());

            if (m_pscene->global_ubo().size() > 0)
            {

               update_global_ubo(m_pgpucontext);

            }

            m_pscene->on_render(m_pgpucontext);

         }

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

   
   //glm::vec3 engine::camera_pole_up()
   //{
   //   
   //   return { 0.0f, 1.0f, 0.0f };

   //}


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


      float aspect = m_pusergraphics3d->getAspectRatio();

      m_pcamera->setPerspectiveProjection(glm::radians(50.f), aspect, 0.1f, 100.f);

      m_pcamera->UpdateCameraVectors();

      //if (m_fYScale < 0)
      //{

      //   m_pcamera->m_matrixImpact = glm::lookAtRH(m_pcamera->m_locationPosition,
      //      m_pcamera->m_locationPosition + m_pcamera->m_poleFront,
      //      m_pcamera->m_poleWorldUp);

      //}
      //else
      //{

      glm::mat4 matrixImpact;
          if (m_fYScale < 0)
          {
             matrixImpact=glm::lookAtRH(m_pcamera->m_locationPosition,
                m_pcamera->m_locationPosition + m_pcamera->m_poleFront,
                m_pcamera->m_poleWorldUp);
             //matrixImpact[2][0] = -matrixImpact[2][0];
             //matrixImpact[2][1] = -matrixImpact[2][1];
             //matrixImpact[2][2] = -matrixImpact[2][2];
             //matrixImpact[2][3] = -matrixImpact[2][3];
          }
          else
          {
             matrixImpact=glm::lookAtRH(m_pcamera->m_locationPosition,
                m_pcamera->m_locationPosition + m_pcamera->m_poleFront,
                m_pcamera->m_poleWorldUp);


          }
             m_pcamera->m_matrixImpact = matrixImpact;
      //}

      m_pcamera->m_matrixAntImpact = glm::inverse(m_pcamera->m_matrixImpact);

   }


   glm::mat4 engine::model_matrix(TransformComponent& transformcomponent)
   {

      auto translation = transformcomponent.translation;
      auto rotation = transformcomponent.rotation;
      auto scale = transformcomponent.scale;

      scale.z = scale.z * m_fYScale;
      //glm::mat4 makeViewMatrix(glm::vec3 translation, glm::vec3 rotationEulerDegrees, )
      //{
         // Convert degrees to radians
         //glm::vec3 rotation = glm::radians(rotationEulerDegrees);

         // Scale
         glm::mat4 S = glm::scale(glm::mat4(1.0f), scale);

         // Rotation (Euler to Quaternion to Matrix)
         glm::quat q = glm::quat(rotation);
         glm::mat4 R = glm::toMat4(q);

         // Translation
         glm::mat4 T = glm::translate(glm::mat4(1.0f), translation);

         // Model matrix (camera transform)
         glm::mat4 model = T * R * S;

         return model;

         // View matrix is inverse of camera transform
        // glm::mat4 view = glm::inverse(model);

         //return view;
      //}
      //const float c3 = glm::cos(transformcomponent.rotation.z);
      //const float s3 = glm::sin(transformcomponent.rotation.z);
      //const float c2 = glm::cos(transformcomponent.rotation.x);
      //const float s2 = glm::sin(transformcomponent.rotation.x);
      //const float c1 = glm::cos(transformcomponent.rotation.y);
      //const float s1 = glm::sin(transformcomponent.rotation.y);
      //float scalex = transformcomponent.scale.x;
      //float scaley = transformcomponent.scale.y;
      //float scalez = m_fYScale * transformcomponent.scale.z;
      //float translationx = transformcomponent.translation.x;
      //float translationy = transformcomponent.translation.y;
      //float translationz = transformcomponent.translation.z;
      //return glm::mat4{
      //   {
      //      scalex * (c1 * c3 + s1 * s2 * s3),
      //      scalex * (c2 * s3),
      //      scalex * (c1 * s2 * s3 - c3 * s1),
      //      0.0f,
      //   },
      //   {
      //      scaley * (c3 * s1 * s2 - c1 * s3),
      //      scaley * (c2 * c3),
      //      scaley * (c1 * c3 * s2 + s1 * s3),
      //      0.0f,
      //   },
      //   {
      //      scalez * (c2 * s1),
      //      scalez * (-s2),
      //      scalez * (c1 * c2),
      //      0.0f,
      //   },
      //   {translationx, translationy, translationz, 1.0f}
      //};

   }

   
   glm::mat4 engine::normal_matrix(TransformComponent& transformcomponent)
   {

      auto m = model_matrix(transformcomponent);

      return glm::inverse(m);

   }


   void engine::run_offscreen()
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

      ///auto pimpact = m_pusergraphics3d;

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

               //m_pgpucontext->make_current();

               m_pgpucontext->set_placement(m_rectanglePlacementNew);

               auto prenderer = m_pgpucontext->get_renderer(::gpu::e_scene_3d);

               prenderer->defer_update_renderer();

               if (!m_pgpucontext->m_pcpubuffer->m_pimagetarget->m_callbackOnImagePixels)
               {

                  m_pgpucontext->m_pcpubuffer->m_pimagetarget->m_callbackOnImagePixels =
                     [this]()
                     {

                        m_pusergraphics3d->set_need_redraw();

                        m_pusergraphics3d->post_redraw();

                     };

               }



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


   void engine::defer_start(::user::graphics3d* pusergraphics3d, const ::int_rectangle& rectanglePlacement)
   {

      m_pusergraphics3d = pusergraphics3d;

      auto papp = get_app();

      auto pgpu = papp->get_gpu();

      auto pwindow = m_pusergraphics3d->window();

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

            m_pusergraphics3d->on_load_engine();

            m_pgpucontext = pgpucontext;

            pgpucontext->m_pengine = this;

            if (m_pgpucontext->m_eoutput == ::gpu::e_output_cpu_buffer)
            {

               run_offscreen();

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


   void engine::run()
   {

      throw::exception(error_wrong_state);

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


