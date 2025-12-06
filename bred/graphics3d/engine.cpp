// Created by camilo on 2025-05-17 04:14 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "engine.h"
#include "immersion_layer.h"
#include "input.h"
#include "tinyobjloader_Builder.h"
#include "scene_base.h"
#include "types.h"
#include "acme/exception/interface_only.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/platform/application.h"
#include "acme/platform/node.h"
#include "acme/prototype/geometry/matrix.h"
#include "acme/prototype/geometry2d/angle.h"
#include "apex/database/client.h"
#include "apex/database/stream.h"
#include "bred/gpu/bred_approach.h"
#include "bred/gpu/command_buffer.h"
#include "bred/gpu/context.h"
#include "bred/gpu/cpu_buffer.h"
#include "bred/gpu/device.h"
#include "bred/gpu/frame.h"
#include "bred/gpu/layer.h"
#include "bred/gpu/renderer.h"
#include "bred/gpu/render_target.h"
#include "bred/graphics3d/_functions.h"
#include "bred/graphics3d/camera.h"
#include "bred/graphics3d/shape_factory.h"
#include "bred/user/user/graphics3d.h"
#include "aura/graphics/image/target.h"
#include "aura/platform/application.h"
#include <chrono>
#include "acme/prototype/geometry/quaternion.h"

//
// Function to flip a floating_matrix4 along the Z-axis
floating_matrix4 flipZMat4(const floating_matrix4& mat) {
   // Create a rotation matrix that flips along the Y-axis (180 degrees)
   floating_matrix4 flip = floating_matrix4(1.0f);
   
   
   flip.rotate(180.0_degree, floating_sequence3(0.0f, 1.0f, 0.0f));

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

      debug() << "engine::~engine()";

   }


   void engine::initialize_engine(::user::graphics3d* pusergraphics3d)
   {

      m_pusergraphics3d = pusergraphics3d;

      m_pusergraphics3d->m_pengine = this;

      //m_papproach = m_papplication->get_gpu_approach();


   }


   void engine::on_render_frame()
   {

      if (m_rectanglePlacementNew.is_empty())
      {

         return;

      }

      _prepare_frame();

      auto pgpucontext = this->gpu_context();

      auto prenderer = pgpucontext->m_pgpurenderer.m_p;

      //prenderer->on_new_frame();

      if (auto pframe = prenderer->beginFrame())
      {

         //if (m_papplication->m_gpu.m_bUseSwapChainWindow)
         //{

         //   //auto prenderer = get_gpu_context()->get_gpu_renderer();

         //   //prenderer->start_layer();

         //   start_gpu_layer(pframe);

         //}

         on_begin_frame();
         
         prenderer->on_begin_render(pframe);

         {

            auto pscene = m_pimmersionlayer->m_pscene;

            _synchronous_lock synchronouslock(pscene->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

            if (pscene->is_global_ubo_ok())
            {

               update_global_ubo(pgpucontext);

            }

            auto pgpurendertarget = prenderer->m_pgpurendertarget.m_p;

            int iFrameIndex = pgpurendertarget->get_frame_index();

            auto pcommandbuffer = pframe->m_pgpucommandbuffer;

            pcommandbuffer->m_iFrameIndex = iFrameIndex;

            pscene->on_render(pgpucontext);

         }

         prenderer->on_end_render(pframe);

         on_end_frame();

         //if (m_papplication->m_gpu.m_bUseSwapChainWindow)
         //{

         //   //m_pgpucontextCompositor->m_pgpurenderer->end_layer();

         //   end_gpu_layer(pframe);

         //}

         prenderer->endFrame();

      }

   }


   void engine::create_global_ubo(::gpu::context* pgpucontext)
   {

      pgpucontext->layout_global_ubo(&m_pimmersionlayer->m_pscene->global_ubo());

      auto iGlobalUboSize = m_pimmersionlayer->m_pscene->global_ubo().m_blockWithoutSamplers.size();

      if (iGlobalUboSize > 0)
      {

         pgpucontext->create_global_ubo((int)iGlobalUboSize, pgpucontext->get_gpu_renderer()->m_pgpurendertarget->get_frame_count());

      }

   }


   //::file::path engine::shader_path(const ::file::path& pathShader)
   //{

   //   return pathShader;

   //}


   void engine::on_begin_frame()
   {


   }

   
   void engine::on_end_frame()
   {


   }


   void engine::start_gpu_layer(::gpu::frame * pframe)
   {

      //auto pcontext = gpu_context();

      //auto player = pcontext->m_pgpudevice->next_layer(pcontext->m_pgpurenderer);

      auto player = pframe->m_pgpulayer;

      //player->m_pgpuframe = pframe;

      //pframe->m_pgpulayer = player;

      player->layer_start();


   }


   ::gpu::frame* engine::end_gpu_layer(::gpu::frame * pgpuframe)
   {

      auto pcontext = gpu_context();

      auto player = pcontext->m_pgpudevice->current_layer();

      player->layer_end();

      return pgpuframe;

   }


   //floating_sequence3 engine::camera_pole_up()
   //{
   //   
   //   return { 0.0f, 1.0f, 0.0f };

   //}


   void engine::on_update_frame()
   {

      //auto &pcameraScene = m_pimmersionlayer->m_pscene->m_pcameraScene;

      //if (!pcameraScene)
      //{
      //   pcameraScene = m_pimmersionlayer->m_pscene->get_default_camera();
      //   ::pointer <::database::client> pdatabaseclient = m_papplication;

      //   if (pdatabaseclient)
      //   {

      //      //pdatabaseclient->datastream()->get_block("camera", m_pcamera->as_block());
      //      //pdatabaseclient->datastream()->get_block("transform", as_memory_block(m_transform));
      //      //pdatabaseclient->datastream()->get_block("input", m_pinput->as_block());

      //   }

      //}

      if (m_pimmersionlayer)
      {

         if (m_pimmersionlayer->m_pscene)
         {

            if (!m_pimmersionlayer->m_pscene->m_pcameraCurrent)
            {

               m_pimmersionlayer->m_pscene->m_pcameraCurrent = m_pimmersionlayer->m_pscene->m_pcameraScene;

            }

         }

      }


      //m_pimmersionlayer->on_prepare_camera();

      //if (pcameraScene)
      //{

      //   m_transform.m_sequence3Position = pcameraScene->m_locationPosition;

      //   m_transform.m_quaternionRotation.x = pcameraScene->m_anglePitch;

      //   m_transform.m_quaternionRotation.y = pcameraScene->m_angleYaw;

      //}

         //VkcCamera camera(floating_sequence3(0.0f, 2.0f, -10.0f), .0f, 0.0f);

         //auto viewerObject = øcreate <::graphics3d::scene_object>();
         //papp->m_pimpact->m_bLastMouse = true;
         //viewerObject->m_transform.translation.z = -2.5f;
         //m_transform.translation.z = -2.5f;



      //m_fFrameTime = fFrameTime;

      m_pinput->prepare_mouse_input();

      m_pinput->process_mouse_input();

      //m_pinput->updateLook(m_pinput->getX(), m_pinput->getY(), transform);

      m_pinput->process_keyboard_input();

      //cameraController.moveInPlaneXZ(m_pimpact, frameTime, viewerObject);

      //m_pcamera->setViewYXZ(m_transform.translation, m_transform.rotation);

      //if (pcameraScene)
      //{

      //   float aspect = m_pusergraphics3d->getAspectRatio();

      //   pcameraScene->setPerspectiveProjection(::radians(50.f), aspect, 0.1f, 100.f);

      //   pcameraScene->UpdateCameraVectors();


      //   // if (m_fYScale < 0)
      //   //{

      //   //   m_pcamera->m_matrixImpact = glm::lookAtRH(m_pcamera->m_locationPosition,
      //   //      m_pcamera->m_locationPosition + m_pcamera->m_sequence3Front,
      //   //      m_pcamera->m_sequence3WorldUp);

      //   //}
      //   // else
      //   //{

      //   floating_matrix4 matrixImpact;
      //   if (m_fYScale < 0)
      //   {
      //      matrixImpact =
      //         glm::lookAtRH(pcameraScene->m_locationPosition,
      //                       pcameraScene->m_locationPosition + pcameraScene->m_sequence3Front, pcameraScene->m_sequence3WorldUp);
      //      // matrixImpact[2][0] = -matrixImpact[2][0];
      //      // matrixImpact[2][1] = -matrixImpact[2][1];
      //      // matrixImpact[2][2] = -matrixImpact[2][2];
      //      // matrixImpact[2][3] = -matrixImpact[2][3];
      //   }
      //   else
      //   {
      //      matrixImpact =
      //         glm::lookAtRH(pcameraScene->m_locationPosition,
      //                       pcameraScene->m_locationPosition + pcameraScene->m_sequence3Front, pcameraScene->m_sequence3WorldUp);
      //   }
      //   pcameraScene->m_matrixImpact = matrixImpact;
      //   //}

      //   pcameraScene->m_matrixInversedImpact = glm::inverse(pcameraScene->m_matrixImpact);

      //}

   }


   floating_matrix4 engine::model_matrix(::graphics3d::transform& transform)
   {

      auto translation = transform.m_sequence3Position;
      auto rotation = transform.m_rotation;
      //auto anglePitch = transform.m_anglePitch;
      auto scale = transform.m_sequence3Scale;

      ///scale.z = scale.z * m_fYScale;
      //floating_matrix4 makeViewMatrix(floating_sequence3 translation, floating_sequence3 rotationEulerDegrees, )
      //{
         // Convert degrees to radians
         //floating_sequence3 rotation = ::radians(rotationEulerDegrees);

         // Scale
         auto S = scale.as_scaling_matrix();

         // Rotation (Euler to Quaternion to Matrix)
         //;
         //;
         //auto quaternion = float_quaternion(rotation);
         auto R = rotation.as_rotation_matrix();

         // Translation
         auto T = translation.as_translation_matrix();

         // Model matrix (camera transform)
         auto model = T * R * S;

         return model;

         // View matrix is inverse of camera transform
        // floating_matrix4 view = glm::inverse(model);

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
      //return floating_matrix4{
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

   
   floating_matrix4 engine::normal_matrix(::graphics3d::transform& transformcomponent)
   {

      auto m = model_matrix(transformcomponent);

      return m.inversed();

   }


   void engine::run_cpu_buffer()
   {

      m_stdtimepoint = std::chrono::high_resolution_clock::now();

      set_ok_flag();

      auto pgpuapproach = m_papplication->get_gpu_approach();

      auto pgpudevice = pgpuapproach->get_gpu_device();

      m_papplication->fork([this]()
         {

            auto pcontext = gpu_context();

            ::gpu::thread_set_gpu_device(pcontext->m_pgpudevice);

            while (task_get_run())
            {

               task_iteration();

               if (m_rectanglePlacementNew.is_empty())
               {

                  continue;

               }

               if (!m_bLoadedEngine)
               {

                  continue;

               }

               //::gpu::context_guard guard(m_pgpucontextCompositor);

               auto pcontext = gpu_context();

               pcontext->set_placement(m_rectanglePlacementNew);

               auto prenderer = pcontext->get_gpu_renderer();

               prenderer->defer_update_renderer();

               auto pcpubuffer = pcontext->get_cpu_buffer();

               auto pimagetarget = pcpubuffer->get_image_target();

               if (!pimagetarget->m_callbackOnImagePixels)
               {

                  pimagetarget->m_callbackOnImagePixels =
                     [this]()
                     {

                        m_pusergraphics3d->set_need_redraw();

                        m_pusergraphics3d->post_redraw();

                     };

               }

               try
               {

                  try
                  {

                     m_pgpucontextCompositor2->m_pgpudevice->on_new_frame();

                  }
                  catch (...)
                  {


                  }

                  _do_frame_step();

               }
               catch (...)
               {

               }

               auto pdevice = pcontext->m_pgpudevice;

               pdevice->on_top_end_frame();

            }

            ::pointer <::database::client> pdatabaseclient = m_papplication;

            if (pdatabaseclient)
            {
               auto &pcameraScene = m_pimmersionlayer->m_pscene->m_pcameraScene;
               pdatabaseclient->datastream()->set("input", m_pinput->as_block());
               pdatabaseclient->datastream()->set("transform", as_memory_block(m_transform));
               //pdatabaseclient->datastream()->set("camera", pcameraScene->as_block());

            }


         });


      //if (pgpucontext->logicalDevice() != VK_NULL_HANDLE)
      //{

      //   vkDeviceWaitIdle(pgpucontext->logicalDevice());

      //}

   }


   ::gpu::enum_output engine::get_engine_gpu_eoutput()
   {

      if (m_papplication->m_gpu.m_bUseSwapChainWindow)
      {

         return ::gpu::e_output_gpu_buffer;

      }
      else
      {

         return ::gpu::e_output_cpu_buffer;

      }

   }


   void engine::defer_start(::user::graphics3d* pusergraphics3d, const ::int_rectangle& rectanglePlacement)
   {

      m_pusergraphics3d = pusergraphics3d;

      auto papp = get_app();

      auto pgpuapproach = papp->get_gpu_approach();

      auto pwindow = m_pusergraphics3d->window();

      pgpuapproach->m_rectangleOffscreen = rectanglePlacement;

      ::cast < ::gpu::device > pgpudevice = pgpuapproach->get_gpu_device();

      //auto pgpucontext = pgpudevice->get_main_context();

      //::gpu::start_gpu_output_context_t startgpuoutputcontext(
      //   this,
      //   pgpudevice,
      //   ::gpu::e_output_gpu_buffer,
      //   rectanglePlacement
      //);

      //m_pgpucontextCompositor = pgpudevice->create_gpu_context(
      //   get_engine_gpu_eoutput(),
      //   ::gpu::e_scene_3d,
      //   rectanglePlacement.size()
      //);

      //m_pgpurendererGraphics3D = pgpucontext->graphics3d_renderer();

      //if (m_papplication->m_bUseSwapChainWindow)
      //{

      //   auto pwindow = m_pimpact->window();

      //   pgpucontext = pgpudevice->start_swap_chain_context(this, pwindow);

      //}
      //else
      //if (!m_papplication->m_bUseSwapChainWindow){

         //auto callbackImage32CpuBuffer = m_callbackImage32CpuBuffer;

      //if (m_papplication->m_gpu.m_bUseSwapChainWindow)
      //{

      //   pgpucontext = pgpudevice->start_gpu_output_context(this, ::gpu::e_output_gpu_buffer, rectanglePlacement);

      //}
      //else
      //{

      //   pgpucontext = pgpudevice->start_gpu_output_context(this, ::gpu::e_output_cpu_buffer, rectanglePlacement);

      //}

      //      }

      set_ok_flag();

      m_rectanglePlacementNew = rectanglePlacement;

      get_gpu_context()->_send([this, rectanglePlacement]()
      {

            auto pcontext = gpu_context();

            auto pgpurenderer = pcontext->get_gpu_renderer();

            pgpurenderer->on_resize(rectanglePlacement.size());

            m_pusergraphics3d->on_load_engine();

            pcontext->m_pengine = this;

            m_bLoadedEngine = true;

            if (pcontext->m_eoutput == ::gpu::e_output_cpu_buffer)
            {

               run_cpu_buffer();

            }

         });

   }


   void engine::update_global_ubo(::gpu::context* pgpucontext)
   {

      auto pscene = m_pimmersionlayer->m_pscene;

      if (pscene->global_ubo().size(true) > 0)
      {

         pscene->on_update(pgpucontext);
         
         auto pcontext = gpu_context();

         pcontext->update_global_ubo(pscene->global_ubo().block_with_samplers());

      }

   }

   
   ::graphics3d::shape_factory * engine::shape_factory()
   {

      if (!m_pshapefactory)
      {

         øconstruct_new(m_pshapefactory);

      }

      return m_pshapefactory;

   }


   ::gpu::context* engine::get_gpu_context()
   {

      auto pcontext = gpu_context();

      if (!pcontext)
      {

         auto pgpudevice = m_papplication->get_gpu_approach()->get_gpu_device();

         auto pgpucontextNew = pgpudevice->create_gpu_context(
            get_engine_gpu_eoutput(),
            ::gpu::e_scene_3d,
            m_rectanglePlacement.size());

         pgpucontextNew->m_etype = ::gpu::context::e_type_graphics3d;

         pgpucontextNew->m_pgpucompositor = this;

         set_gpu_context(pgpucontextNew);

         pcontext = pgpucontextNew;

      }

      return pcontext;

   }


   void engine::engine_on_after_load_scene(::graphics3d::scene_base* pscene)
   {

      auto pcontext = gpu_context();

      pcontext->m_pgpurenderer->on_after_load_scene(pscene);
      //{



      //}

   }


   ::graphics3d::scene_base * engine::current_scene()
   {

      return m_pimmersionlayer->m_pscene;

   }


   void engine::do_frame_step(::gpu::context* pcontextParam)
   {

      if (m_rectanglePlacementNew.is_empty())
      {

         return;

      }

      //::gpu::rear_guard rear_guard(pcontext);

      auto pcontext = gpu_context();

      pcontext->_send([this]()
         {

            auto pcontext = gpu_context();

            //::gpu::context_guard guard(m_pgpucontextCompositor);

            pcontext->set_placement(m_rectanglePlacementNew);

            auto prenderer = pcontext->get_gpu_renderer();

            prenderer->defer_update_renderer();

            try
            {

               _do_frame_step();

            }
            catch (...)
            {

            }

         });

//      m_pgpurendererGraphics3D->on_new_frame();

      //pcontext->make_current();

      //auto prendererSource = m_pgpurendererGraphics3D->m_pgpucontextCompositor->m_pgpurendererOutput;

      //auto prenderer = pcontext->m_pgpurendererOutput;

      //prenderer->blend(prendererSource);

      //prenderer->soft_restore_context();

   }


   void engine::run()
   {

      throw::exception(error_wrong_state);

   }


   void engine::_001OnDraw(::draw2d::graphics_pointer& pgraphics)
   {

      auto eoutput = get_gpu_context()->m_eoutput;

      if (eoutput == ::gpu::e_output_cpu_buffer)
      {

         auto pcontext = gpu_context();

         auto pcpubuffer = pcontext->m_pcpubuffer;

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

         auto pcontext = gpu_context();

         do_frame_step(pcontext);

         on_after_done_frame_step(pgraphics);

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

            auto pcontext = gpu_context();

            pcontext->set_placement(m_rectanglePlacement);

            defer_update_engine(m_rectanglePlacement);

            //if (pgpucontext->m_pgpurendererGraphics3D)
            //{

            //   //pgpucontext->create_offscreen_buffer(m_rectanglePlacement.size());

            //   
            //   //m_pimpact->on_load_engine();

            //   //run();

            //   //m_pimpact->m_ptaskEngine.release();

            //   //return;


            //   //m_pinput = øallocate::graphics3d::input();

            //   //m_pinput->m_pimpact = m_pimpact;

            //   //m_pcamera = øallocate::graphics3d::camera(floating_sequence3(0.0f, 3.0f, 3.0f), -90.0f, 0.0f);

            //   ////m_pcamera->m_pimpact

            //   ////m_pglcapplication = m_pimpact->start_opengl_application();
            //   ////øconstruct(m_pgpucontextCompositor);

            //   //if (!m_papplication->m_bUseSwapChainWindow)
            //   //{

            //   //   pgpucontext->m_pgpucontextCompositor->resize_offscreen_buffer({ cx, cy });

            //   //}

            //   //m_prenderer = øallocate::graphics3d_opengl::renderer();

            //   ////return;
            //   //// Initialize the game logic and scene data
            //   ////Init();

            //   //pgpucontext->m_pgpucontextCompositor->m_timeSample = 1_s / 60.0;

            //   //m_pgpucontextCompositor->m_rendera.add_unique(this);

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

      if (m_rectanglePlacementNew.has_area())
      {

         on_update_frame();

         on_render_frame();

      }

   }

   void engine::on_after_done_frame_step(::draw2d::graphics_pointer& pgraphics)
   {



   }


   void engine::defer_update_engine(const ::int_rectangle& rectanglePlacement)
   {

      //if (!m_prenderer)
      //{

      //   øconstruct(m_prenderer);

      //   //::graphics3d::engine::m_prenderer = m_prenderer;

      //   m_prenderer->initialize_renderer(m_pgpucontextCompositor, m_pgpucontextCompositor->m_eoutput);

      //}


      //m_prenderer->on_context_resize();
      //m_pglobalpool->initialize_pool(pgpucontext);

      //= øallocate
      //   descriptor_pool::Builder(pgpucontext)
      //   .setMaxSets(swap_chain_render_pass::MAX_FRAMES_IN_FLIGHT)
      //   .addPoolSize(VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, swap_chain_render_pass::MAX_FRAMES_IN_FLIGHT)
      //   .build();

      //pgpucontext = øallocate context(m_pvulkandevice);

      //          m_prenderer->getRenderPass(),
        //        globalSetLayout->getDescriptorSetLayout()
          //  };

      auto pcontext = gpu_context();

      auto pscene = m_pimmersionlayer->m_pscene;

      pscene->defer_load_scene(pcontext);

      engine_on_after_load_scene(pscene);

      if (!m_bCreatedGlobalUbo)
      {

         m_bCreatedGlobalUbo = true;

         auto iGlobalUboSize = pscene->global_ubo().size(true);

         if (iGlobalUboSize > 0)
         {

            create_global_ubo(pcontext);

         }


      }


   }


   void engine::on_layout(const ::int_rectangle& rectanglePlacement)
   {

      m_rectanglePlacementNew = rectanglePlacement;

      //      auto pgpucontext = m_pgpucontextCompositor;
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
      //      auto pgpucontext = m_pgpucontextCompositor;
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
      //         //m_pinput = øallocate::graphics3d::input();
      //
      //         //m_pinput->m_pimpact = m_pimpact;
      //
      //         //m_pcamera = øallocate::graphics3d::camera(floating_sequence3(0.0f, 3.0f, 3.0f), -90.0f, 0.0f);
      //
      //         ////m_pcamera->m_pimpact
      //
      //         ////m_pglcapplication = m_pimpact->start_opengl_application();
      //         ////øconstruct(m_pgpucontextCompositor);
      //
      //         //if (!m_papplication->m_bUseSwapChainWindow)
      //         //{
      //
      //         //   pgpucontext->m_pgpucontextCompositor->resize_offscreen_buffer({ cx, cy });
      //
      //         //}
      //
      //         //m_prenderer = øallocate::graphics3d_opengl::renderer();
      //
      //         ////return;
      //         //// Initialize the game logic and scene data
      //         ////Init();
      //
      //         //pgpucontext->m_pgpucontextCompositor->m_timeSample = 1_s / 60.0;
      //
      //         //m_pgpucontextCompositor->m_rendera.add_unique(this);
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


   ::pointer<::graphics3d::renderable> engine::_load_wavefront_obj_renderable(const ::gpu::renderable_t &model)
   {

      tinyobjloader_Builder builder{};

      auto pcontext = gpu_context();

      builder.loadModel(pcontext, model.m_pathRenderable, model.m_bCounterClockwise);

      ::pointer < ::gpu::model_buffer > pmodel;

      øconstruct(pmodel);

      (*(::gpu::renderable_t *)pmodel) = model;

      pmodel->initialize_model(pcontext, builder);

      return pmodel;

   }



   //
   // void engine::add_scene(::graphics3d::scene_base* pscene)
   // {
   //
   //    m_mapScene[pscene->m_strName] = pscene;
   //
   // }
   //
   //
   // void engine::set_current_scene(::graphics3d::scene_base* pscene)
   // {
   //
   //    m_pscene = pscene;
   //
   // }

   
   //floating_matrix4 engine::ortho(float left, float right, float bottom, float top, float zNear, float zFar)
   //{

   //   throw ::interface_only();

   //   return {1.0f};

   //}


   floating_matrix4 engine::perspective(const float_angle & angleFovY, float aspect, float zNear, float zFar)
   {

      throw ::interface_only();
      
      return {1.0f}; 
   
   }


   void engine::calculate_impact(::floating_matrix4 &matrixImpact, const ::graphics3d::camera &camera)
   {


      auto positionCamera = camera.position();

      auto frontDirection = camera.front();

      auto positionCenter = positionCamera + frontDirection;

      auto worldUp = camera.world_up();

      matrixImpact = ::graphics3d::lookAt(positionCamera, positionCenter, worldUp);

   }


   void engine::calculate_projection(::floating_matrix4 &matrixProjection, const ::graphics3d::camera &camera)
   {

      matrixProjection = perspective(camera.m_angleFovY, camera.m_fAspectRatio, camera.m_fNearZ, camera.m_fFarZ);

   }



} // namespace graphics3d


