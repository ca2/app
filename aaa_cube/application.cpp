#include "framework.h"
#include "application.h"
#include "bred/gpu/approach.h"
#include "graphics3d/engine.h"
#include "graphics3d/model.h"


namespace cube
{


   application::application()
   {


   }


   application::~application()
   {


   }


   //::graphics3d::camera application::get_default_camera()
   //{

   //   return{};

   //}


   //#if !(defined(VK_USE_PLATFORM_IOS_MVK) || defined(VK_USE_PLATFORM_MACOS_MVK) || defined(VK_USE_PLATFORM_METAL_EXT))
   //   // iOS & macOS: getAssetPath() and getShaderBasePath() implemented externally for access to Obj-C++ path utilities
   ::file::path application::assets_folder()
   {
      return "matter://assets";
      //#if defined(VK_USE_PLATFORM_ANDROID_KHR)
      //      return ""_ansi;
      //#elif defined(VK_EXAMPLE_ASSETS_DIR)
      //      return VK_EXAMPLE_ASSETS_DIR;
      //#else
      //      return "matter://";
      //#endif
   }

   ::file::path application::shaders_folder()
   {
      return "matter://shaders";
      //#if defined(VK_USE_PLATFORM_ANDROID_KHR)
      //      return "shaders/"_ansi;
      //#elif defined(VK_EXAMPLE_SHADERS_DIR)
      //      return VK_EXAMPLE_SHADERS_DIR;
      //#else
      //      return "./../shaders/";
      //#endif
   }
   //#endif


   ::gpu::approach* application::get_gpu()
   {

      if (!m_pgpu)
      {

         create_gpu();

      }
      
      return m_pgpu.get();

   }


   ::gpu::approach* application::gpu()
   { 
      
      return m_pgpu.get(); 
   
   }


   //#ifdef _OPENGL
   void application::create_gpu()
   {

      if (m_pgpu)
      {

         return;

      }

      //load_library("gpu_opengl");

      auto pfactoryGpu = component_factory("gpu");

      if (!pfactoryGpu)
      {

         ::string strImplementation = m_papplication->draw2d_get_default_implementation_name();

         if (strImplementation == "vkvg")
         {

            strImplementation = "vulkan";

         }

         pfactoryGpu = factory("gpu", strImplementation);

         pfactoryGpu->merge_to_global_factory();

      }

      //get_library("gpu_opengl");



      //if (!pfactoryGpu)
      //{

      //   error() <<"gpu_opengl ([a-z0-9_]+)_factory has failed";

      //   return pfactoryGpu;

      //}

      //auto estatus =

      pfactoryGpu->__øconstruct(this, m_pgpu);


      m_pgpu->initialize_gpu_approach();

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //return ::success;

   }

      //void application::run_application()
      //{

      //   m_pengine->run_application();

      ////   ::pointer < ::graphics::application> papp = m_papplication;


      ////   __construct_new(m_pvkcdevice);

      ////   m_pvkcdevice->initialize_device(m_pvkcontainer);

      ////   __construct_new(m_prenderer);

      ////   m_prenderer->initialize_renderer(m_pvkcontainer, m_pvkcdevice);

      ////   auto pglobalpoolbuilder = __allocate VkcDescriptorPool::Builder();

      ////   pglobalpoolbuilder->initialize_builder(m_pvkcdevice);
      ////   pglobalpoolbuilder->setMaxSets(VkcRenderPass::MAX_FRAMES_IN_FLIGHT);
      ////   pglobalpoolbuilder->addPoolSize(VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VkcRenderPass::MAX_FRAMES_IN_FLIGHT);

      ////   m_pglobalpool = pglobalpoolbuilder->build();

      ////   //m_pglobalpool->initialize_pool(m_pvkcdevice);

      ////   //= __allocate
      ////   //   VkcDescriptorPool::Builder(m_pvkcdevice)
      ////   //   .setMaxSets(VkcSwapChain::MAX_FRAMES_IN_FLIGHT)
      ////   //   .addPoolSize(VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VkcSwapChain::MAX_FRAMES_IN_FLIGHT)
      ////   //   .build();
      ////   loadGameObjects();

      ////   //m_pvkcdevice = __allocate VkcDevice(m_pvulkandevice);

      ////   ::pointer_array<buffer> uboBuffers;

      ////   uboBuffers.set_size(VkcRenderPass::MAX_FRAMES_IN_FLIGHT);

      ////   for (int i = 0; i < uboBuffers.size(); i++)
      ////   {

      ////      uboBuffers[i] = __allocate buffer();

      ////      uboBuffers[i]->initialize_buffer(
      ////         m_pvkcdevice,
      ////         sizeof(GlobalUbo),
      ////         1,
      ////         VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
      ////         VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT);

      ////      uboBuffers[i]->map();

      ////   }
      ////   auto globalSetLayout = VkcDescriptorSetLayout::Builder(m_pvkcdevice)
      ////      .addBinding(0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_ALL_GRAPHICS)
      ////      .build();


      ////   std::vector<VkDescriptorSet> globalDescriptorSets(VkcRenderPass::MAX_FRAMES_IN_FLIGHT);

      ////   for (int i = 0; i < globalDescriptorSets.size(); i++)
      ////   {

      ////      auto bufferInfo = uboBuffers[i]->descriptorInfo();

      ////      VkcDescriptorWriter(*globalSetLayout, *m_pglobalpool)
      ////         .writeBuffer(0, &bufferInfo)
      ////         .build(globalDescriptorSets[i]);

      ////   }

      ////   simple_render_system simpleRenderSystem{
      ////       m_pvkcdevice,
      ////       m_prenderer->getRenderPass(),
      ////       globalSetLayout->getDescriptorSetLayout() };

      ////   PointLightSystem pointLightSystem{
      ////       m_pvkcdevice,
      ////       m_prenderer->getRenderPass(),
      ////       globalSetLayout->getDescriptorSetLayout()
      ////   };

      ////   //VkcCamera camera{ glm::vec3(0.0f, 2.0f, -15.0f), -90.0f, 0.0f };
      ////   VkcCamera camera{ glm::vec3(0.0f, 2.0f, -15.0f), -90.0f, 0.0f };
      ////   auto viewerObject = VkcGameObject::createGameObject();
      ////   m_pvkcontainer->m_bLastMouse = true;
      ////   viewerObject.transform.translation.z = -2.5f;
      ////   MNKController cameraController{};
      ////   /*    glfwSetInputMode(_window.getGLFWwindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
      ////       glfwSetWindowUserPointer(_window.getGLFWwindow(), &cameraController);*/
      ////   cameraController.m_bMouseAbsolute;

      ////   papp->datastream()->get_block("camera", as_memory_block(camera));
      ////   papp->datastream()->get_block("transform", as_memory_block(viewerObject.transform));
      ////   papp->datastream()->get_block("camera_controller", as_memory_block(cameraController));

      ////   auto currentTime = std::chrono::high_resolution_clock::now();
      ////   //while (!_window.shouldClose())
      ////   while (!m_pvkcontainer->m_bShouldClose && task_get_run())
      ////   {

      ////      task_iteration();
      ////      //glfwPollEvents();

      ////      auto newTime = std::chrono::high_resolution_clock::now();

      ////      float frameTime = std::chrono::duration<float, std::chrono::seconds::period>(newTime - currentTime).count();

      ////      currentTime = newTime;

      ////      cameraController.handleMouseInput(m_pvkcontainer);

      ////      cameraController.updateLook(m_pvkcontainer, cameraController.getX(), cameraController.getY(), viewerObject);

      ////      cameraController.updateMovement(m_pvkcontainer, frameTime, viewerObject);

      ////      //cameraController.moveInPlaneXZ(m_pvkcontainer, frameTime, viewerObject);

      ////      camera.setViewYXZ(viewerObject.transform.translation, viewerObject.transform.rotation);

      ////      if (m_prenderer->m_pvkcrenderpass->width() > 0
      ////         && m_prenderer->m_pvkcrenderpass->height() > 0)
      ////      {

      ////         float aspect = m_prenderer->getAspectRatio();

      ////         camera.setPerspectiveProjection(glm::radians(50.f), aspect, 0.1f, 100.f);

      ////         if (auto commandBuffer = m_prenderer->beginFrame())
      ////         {

      ////            int frameIndex = m_prenderer->getFrameIndex();

      ////            FrameInfo frameInfo{ frameIndex, frameTime, commandBuffer, camera, globalDescriptorSets[frameIndex], m_gameObjects };

      ////            // update
      ////            GlobalUbo ubo{};
      ////            ubo.projection = camera.getProjection();
      ////            ubo.view = camera.getView();
      ////            ubo.inverseView = camera.getInverseView();
      ////            pointLightSystem.update(frameInfo, ubo);
      ////            uboBuffers[frameIndex]->writeToBuffer(&ubo);
      ////            uboBuffers[frameIndex]->flush();

      ////            // render
      ////            m_prenderer->beginRenderPass(commandBuffer);

      ////            simpleRenderSystem.renderGameObjects(frameInfo);
      ////            pointLightSystem.render(frameInfo);

      ////            m_prenderer->endRenderPass(commandBuffer);
      ////            m_prenderer->endFrame();

      ////         }

      ////      }

      ////   }

      ////   papp->datastream()->set("camera_controller", as_memory_block(cameraController));
      ////   papp->datastream()->set("transform", as_memory_block(viewerObject.transform));
      ////   papp->datastream()->set("camera", as_memory_block(camera));

      ////   if (m_pvkcdevice->device() != VK_NULL_HANDLE)
      ////   {

      ////      vkDeviceWaitIdle(m_pvkcdevice->device());

      ////   }

      ////}


      ////void Application::resize(int cx, int cy)
      ////{

      ////   m_prenderer->m_pvkcrenderpass->windowExtent.width = cx;
      ////   m_prenderer->m_pvkcrenderpass->windowExtent.height = cy;

      //}


      //void application::on_loa()
      //{

      //   //{
      //   //   ::pointer<VkcModel> vkcModel = VkcModel::createModelFromFile(m_pvkcdevice, "matter://models/flat_vase.obj");
      //   //   auto flatVase = VkcGameObject::createGameObject();

      //   //   flatVase.model = vkcModel;
      //   //   flatVase.transform.translation = { -.5f, .5f, 0.f };
      //   //   flatVase.transform.scale = { 3.f, 1.5f, 3.f };
      //   //   m_gameObjects.emplace(flatVase.getId(), std::move(flatVase));
      //   //}

      //   //{
      //   //   ::pointer<VkcModel> vkcModel = VkcModel::createModelFromFile(m_pvkcdevice, "matter://models/quad.obj");
      //   //   auto floor = VkcGameObject::createGameObject();
      //   //   floor.model = vkcModel;
      //   //   assert(vkcModel);
      //   //   floor.transform.translation = { 0.f, .5f, 0.f };
      //   //   floor.transform.scale = { 8.f, 1.f, 8.f };
      //   //   m_gameObjects.emplace(floor.getId(), std::move(floor));
      //   //}

      //   //{
      //   //   ::pointer<VkcModel> vkcModel = VkcModel::createModelFromFile(m_pvkcdevice, "matter://models/smooth_vase.obj");
      //   //   auto smoothVase = VkcGameObject::createGameObject();
      //   //   smoothVase.model = vkcModel;
      //   //   smoothVase.transform.translation = { .5f, .5f, 0.f };
      //   //   smoothVase.transform.scale = { 3.f, 1.5f, 3.f };
      //   //   m_gameObjects.emplace(smoothVase.getId(), std::move(smoothVase));

      //   //}

      //   //{
      //   //   ::pointer<VkcModel> vkcModel = VkcModel::createModelFromFile(m_pvkcdevice, "matter://models/StoneSphere.obj");
      //   //   auto stoneSphere = VkcGameObject::createGameObject();
      //   //   stoneSphere.model = vkcModel;
      //   //   stoneSphere.transform.translation = { .0f, 0.f, 2.f };
      //   //   stoneSphere.transform.scale = { .5f, .5f, .5f };
      //   //   m_gameObjects.emplace(stoneSphere.getId(), std::move(stoneSphere));

      //   //}

      //   //{

      //   //   ::pointer<VkcModel> vkcModel = VkcModel::createModelFromFile(m_pvkcdevice, "matter://models/Barrel_OBJ.obj");
      //   //   auto woodBarrel = VkcGameObject::createGameObject();
      //   //   woodBarrel.model = vkcModel;
      //   //   woodBarrel.transform.translation = { 1.f, -.4f, -1.5f };
      //   //   woodBarrel.transform.scale = { 1.f, 1.f, 1.f };
      //   //   m_gameObjects.emplace(woodBarrel.getId(), std::move(woodBarrel));

      //   //}

      //   //float fLo = 0.5f;

      //   //std::vector<glm::vec3> lightColors{
      //   //      {1.f, fLo, fLo},
      //   //      {fLo, fLo, 1.f},
      //   //      {fLo, 1.f, fLo},
      //   //      {1.f, 1.f, fLo},
      //   //      {fLo, 1.f, 1.f},
      //   //      {1.f, 1.f, 1.f}
      //   //};

      //   //for (int i = 0; i < lightColors.size(); i++) {
      //   //   auto pointLight = VkcGameObject::makePointLight(0.2f);
      //   //   pointLight.color = lightColors[i];
      //   //   auto rotateLight = glm::rotate(
      //   //      glm::mat4(1.f),
      //   //      (i * glm::two_pi<float>()) / lightColors.size(),
      //   //      { 0.f, -1.f, 0.f });
      //   //   pointLight.pointLight->lightIntensity = 1.0f;
      //   //   pointLight.transform.translation = glm::vec3(rotateLight * glm::vec4(-1.f, -1.f, -1.f, 1.f));
      //   //   m_gameObjects.emplace(pointLight.getId(), std::move(pointLight));
      //   //}

      //}


      //void application::handle_mouse_move(int x, int y)
      //{



      //}

      //void application::resize(int cx, int cy)
      //{


      //}



   ::string application::graphics3d_get_implementation_name()
   {

      return "opengl";

   }


} // namespace cube



