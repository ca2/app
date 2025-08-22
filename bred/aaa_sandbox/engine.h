#pragma once
//#include <memory>
//#include "window.h"
#include "bred/graphics3d/engine.h"
#include "graphics3d/device.h"
//#include "graphics3d/instance.h"
#include "graphics3d/renderer.h"
#include "SceneFoundry/sandbox_game/game_layer.h"
#include "SceneFoundry/sandbox_game/camera.h"
#include "bred/graphics3d/window_input.h"
#include "graphics3d/glfw_input.h"
#include "asset_manager.h"

namespace graphics3d
{

   class graphics3d :
   virtual public ::graphics3d::engine
   {
   public:

      //   private:
      //    SandboxWindow                       m_window{ WIDTH, HEIGHT, "A vulkan place" };
      //::pointer < ::graphics3d::sandbox_window> m_pwindow;
      ::pointer < ::graphics3d::sandbox_instance >                   m_pinstance;
      //::graphics3d::device                     m_device{ m_vkinstance, m_window };
      ::pointer < ::graphics3d::device >                     m_pgpudevice;
      //::pointer < asset_manager >                        m_passetManager{ m_device };
      ::pointer < asset_manager >                        m_passetManager;
      //::graphics3d::graphics3d                   m_renderer{ m_device, m_window };
      ::pointer < ::graphics3d::graphics3d >                   m_prenderer;

      //VkSurfaceKHR                        m_surface = VK_NULL_HANDLE;
      //VkInstance                          m_vkinstance_handle = VK_NULL_HANDLE;

      ::pointer<IWindowInput>       m_windowInput;

      // static constexpr uint32_t WIDTH = 1440;
      // static constexpr uint32_t HEIGHT = 810;

      graphics3d();
      ~graphics3d() override;

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



} // namespace graphics3d


