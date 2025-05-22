#pragma once


#include "aura/graphics/gpu/approach.h"
#include <glm/glm.hpp>


namespace gpu_vulkan
{


   class CLASS_DECL_GPU_VULKAN approach :
      virtual public ::gpu::approach
   {
   public:


      VkInstance                       m_vkinstance;


      //VkInstance instance{ VK_NULL_HANDLE };
      ::string_array                   m_straSupportedInstanceExtensions;
      ::pointer < physical_device >    m_pphysicaldevice;
      /** @brief Set of device extensions to be enabled for this example (must be set in the derived constructor) */
      ::array<const char *>            m_pszaEnabledDeviceExtensions;
      /** @brief Set of instance extensions to be enabled for this example (must be set in the derived constructor) */
      ::array<const char *>            m_pszaEnabledInstanceExtensions;
      /** @brief Set of layer settings to be enabled for this example (must be set in the derived constructor) */
      ::array<VkLayerSettingEXT>       m_layersettingsEnabled;
      /** @brief Optional pNext structure for passing extension structures to device creation */
      void *                           m_pDeviceCreatepNextChain = nullptr;
      /** @brief Logical device, application's view of the physical device (GPU) */
      VkDevice                         m_vkdevice;
      // Handle to the device graphics queue that command buffers are submitted to
      VkQueue                          m_vkqueue;
      // Depth buffer format (selected during Vulkan initialization)
      VkFormat                         m_formatDepth;
      // Command buffer pool
      VkCommandPool                    m_vkcommandpool;
      /** @brief Pipeline stages used to wait at for graphics queue submissions */
      VkPipelineStageFlags             m_pipelinestageflagsSubmit;
      // Contains command buffers and semaphores to be presented to the queue
      VkSubmitInfo                     m_submitinfo;
      // Command buffers used for rendering
      ::array<VkCommandBuffer>         m_commandbuffera;
      // Global render pass for frame buffer writes
      VkRenderPass                     m_vkrenderpass;
      // List of available frame buffers (same as number of swap chain images)
      ::array<VkFramebuffer>           m_frameBuffera;
      // Active frame buffer index
      uint32_t                         m_uCurrentBuffer;
      // Descriptor set pool
      VkDescriptorPool                 m_descriptorpool;
      // List of shader modules created (stored for cleanup)
      ::array<VkShaderModule>          m_shadermodulea;
      // Pipeline cache object
      VkPipelineCache                  m_vkpipelinecache;
      // Wraps the swap chain to present images (framebuffers) to the windowing system
      ::pointer < swap_chain >         m_pswapchain;
      // Synchronization semaphores
      struct {
         // Swap chain image presentation
         VkSemaphore presentComplete;
         // Command buffer submission and execution
         VkSemaphore renderComplete;
      } semaphores{};
      ::array<VkFence>                 m_fencewaita;
      bool                             m_bRequiresStencil;

      //bool                             m_bPrepared = false;
      //bool                             m_bResized = false;
      //bool                             m_bImpactUpdated = false;
      //uint32_t                         m_uWidth;
      //uint32_t                         m_uHeight;

      //::pointer < ui_overlay >         m_pui;
      //CommandLineParser commandLineParser;

      /** @brief Last frame time measured using a high performance timer (if available) */
      //float                            m_fFrameTimer = 1.0f;

      ::pointer < benchmark >          m_pbenchmark;

      /** @brief Encapsulated physical and logical vulkan device */
      ::pointer < device >             m_pdevice;

      /** @brief Example settings that can be changed e.g. by command line arguments */
      struct Settings {
         /** @brief Activates validation layers (and message output) when set to true */
#ifdef _DEBUG
         bool validation = true;
#else
         bool validation = false;
#endif
         /** @brief Set to true if fullscreen mode has been requested via command line */
         bool fullscreen = false;
         /** @brief Set to true if v-sync will be forced for the swapchain */
         bool vsync = false;
         /** @brief Enable UI overlay */
         bool overlay = true;
      } settings;

      ///** @brief State of gamepad input (only used on Android) */
      //struct {
      //   glm::vec2 axisLeft = glm::vec2(0.0f);
      //   glm::vec2 axisRight = glm::vec2(0.0f);
      //} gamePadState;

      ///** @brief State of mouse/touch input */
      //struct {
      //   struct {
      //      bool left = false;
      //      bool right = false;
      //      bool middle = false;
      //   } buttons;
      //   glm::vec2 position;
      //} mouseState;

      VkClearColorValue defaultClearColor = { { 0.025f, 0.025f, 0.025f, 1.0f } };

      //static ::array<const char *> args;

      //// Defines a frame rate independent timer value clamped from -1.0...1.0
      //// For use in animations, rotations, etc.
      //float m_fTimer = 0.0f;
      //// Multiplier for speeding up (or slowing down) the global timer
      //float m_fTimerSpeed = 0.25f;
      //bool m_bPaused = false;

      //::pointer < camera > m_pcamera;

      ::string m_strTitle = "Vulkan Example";
      ::string m_strName = "vulkanExample";
      uint32_t m_uApiVersion = VK_API_VERSION_1_0;

      /** @brief Default depth stencil attachment used by the default render pass */
      struct {
         VkImage image;
         VkDeviceMemory memory;
         VkImageView view;
      } m_depthstencil{};

//      // OS specific
//#if defined(_WIN32)
//      HWND window;
//      HINSTANCE windowInstance;
//#elif defined(VK_USE_PLATFORM_ANDROID_KHR)
//   // true if application has focused, false if moved to background
//      bool focused = false;
//      struct TouchPos {
//         int32_t x;
//         int32_t y;
//      } touchPos{};
//      bool touchDown = false;
//      double touchTimer = 0.0;
//      int64_t lastTapTime = 0;
//#elif (defined(VK_USE_PLATFORM_IOS_MVK) || defined(VK_USE_PLATFORM_MACOS_MVK) || defined(VK_USE_PLATFORM_METAL_EXT))
//      void * view;
//#if defined(VK_USE_PLATFORM_METAL_EXT)
//      CAMetalLayer * metalLayer;
//#endif
//#if defined(VK_EXAMPLE_XCODE_GENERATED)
//      bool quit = false;
//#endif
//#elif defined(VK_USE_PLATFORM_DIRECTFB_EXT)
//      bool quit = false;
//      IDirectFB * dfb = nullptr;
//      IDirectFBDisplayLayer * layer = nullptr;
//      IDirectFBWindow * window = nullptr;
//      IDirectFBSurface * surface = nullptr;
//      IDirectFBEventBuffer * event_buffer = nullptr;
//#elif defined(VK_USE_PLATFORM_WAYLAND_KHR)
//      wl_display * display = nullptr;
//      wl_registry * registry = nullptr;
//      wl_compositor * compositor = nullptr;
//      struct xdg_wm_base * shell = nullptr;
//      wl_seat * seat = nullptr;
//      wl_pointer * pointer = nullptr;
//      wl_keyboard * keyboard = nullptr;
//      wl_surface * surface = nullptr;
//      struct xdg_surface * xdg_surface;
//      struct xdg_toplevel * xdg_toplevel;
//      bool quit = false;
//      bool configured = false;
//
//#elif defined(_DIRECT2DISPLAY)
//      bool quit = false;
//#elif defined(VK_USE_PLATFORM_XCB_KHR)
//      bool quit = false;
//      xcb_connection_t * connection;
//      xcb_screen_t * screen;
//      xcb_window_t window;
//      xcb_intern_atom_reply_t * atom_wm_delete_window;
//#elif defined(VK_USE_PLATFORM_HEADLESS_EXT)
//      bool quit = false;
//#elif defined(VK_USE_PLATFORM_SCREEN_QNX)
//      screen_context_t screen_context = nullptr;
//      screen_window_t screen_window = nullptr;
//      screen_event_t screen_event = nullptr;
//      bool quit = false;
//#endif


      //__creatable_from_base(vulkan, ::gpu::approach);


#ifdef WINDOWS_DESKTOP

      ATOM                          m_atomClass;

#endif
      bool                          m_bGpuLibraryInit;


      //HGLRC                         m_hrc;
      //HDC                           m_hdc;
      //HWND                          m_hwnd;
      //::int_size                        m_sizeNew;
      //::int_size                        m_size;
      //HDC                           m_hdcGraphics;
      //float                         m_z;
      //int_point                         m_pointTranslate;
      //::pointer<::vulkan::buffer>  m_pbuffer;
      //::pointer<::vulkan::program> m_pprogram;
      //unsigned int                  VAO;
      //unsigned int                  VBO;

      approach();
      virtual ~approach();


      virtual void initialize(::particle * pparticle) override;


      void initialize_gpu_approach() override;


      virtual VkResult createInstance();

      virtual void getEnabledFeatures();


      ::pointer < ::gpu::context > create_context(::particle * pparticle) override;


      int fread(void * data, int c, int s ,::file::file* pfile);

      virtual void defer_init_gpu_library() override;

      //virtual void draw();
      //virtual void start();
      //virtual void render();

      //virtual bool create_offscreen_buffer(const ::int_size& size);
      //virtual bool destroy_offscreen_buffer();


      //virtual void make_current();


      ::gpu::payload load_dds(const ::scoped_string & scopedstrImagePath) override;


   };


} // namespace vulkan



