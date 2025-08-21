#pragma once
//#include <memory>
//#include "window.h"
#include "bred/graphics3d/engine.h"
#include "sandbox_renderer/device.h"
//#include "sandbox_renderer/instance.h"
#include "sandbox_renderer/renderer.h"
#include "SceneFoundry/sandbox_game/game_layer.h"
#include "SceneFoundry/sandbox_game/camera.h"
#include "bred/graphics3d/window_input.h"
#include "sandbox_engine/glfw_input.h"
#include "asset_manager.h"

namespace sandbox_engine
{

   class sandbox_engine :
   virtual public ::graphics3d::engine
   {
   public:

      //   private:
      //    SandboxWindow                       m_window{ WIDTH, HEIGHT, "A vulkan place" };
      //::pointer < ::sandbox_renderer::sandbox_window> m_pwindow;
      ::pointer < ::sandbox_renderer::sandbox_instance >                   m_pinstance;
      //::sandbox_renderer::device                     m_device{ m_vkinstance, m_window };
      ::pointer < ::sandbox_renderer::device >                     m_pgpudevice;
      //::pointer < asset_manager >                        m_passetManager{ m_device };
      ::pointer < asset_manager >                        m_passetManager;
      //::sandbox_renderer::sandbox_renderer                   m_renderer{ m_device, m_window };
      ::pointer < ::sandbox_renderer::sandbox_renderer >                   m_prenderer;

      //VkSurfaceKHR                        m_surface = VK_NULL_HANDLE;
      //VkInstance                          m_vkinstance_handle = VK_NULL_HANDLE;

      ::pointer<IWindowInput>       m_windowInput;

      // static constexpr uint32_t WIDTH = 1440;
      // static constexpr uint32_t HEIGHT = 810;

      sandbox_engine();
      ~sandbox_engine() override;

      void initialize();

      void initLayer(IGameLayer* game);

      void run(::pointer<IGameLayer> game);

   public:
      ::pointer<IWindowInput> getInputSharedPtr() {
         return m_windowInput;
      }
      asset_manager* getAssetManager() { return m_passetManager; }

      ISandboxRenderer& renderer();
      void toggleCursorLock();
      void setupInputCallbacks();
      void processInput();

      bool m_cursorLocked = true;


   };



} // namespace sandbox_engine


