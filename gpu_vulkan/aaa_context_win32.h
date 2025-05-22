#pragma once


#include "gpu_vulkan/context.h"


namespace gpu_vulkan
{


   class CLASS_DECL_GPU_VULKAN context_win32 :
      virtual public ::gpu_vulkan::context
   {
   public:


      bool                             m_bMesa;
      //HGLRC                            m_hrc;
      //HDC                              m_hdc;
      //HWND                             m_hwnd;
      //HDC                              m_hdcGraphics;

         /** @brief Physical device representation */
      //VkPhysicalDevice m_physicaldevice;
      ::pointer < physical_device >       m_pphysicaldevice;
      /** @brief Logical device representation (application's view of the device) */
      VkDevice m_device;
      ///** @brief Properties of the physical device including limits that the application can check against */
      //VkPhysicalDeviceProperties m_physicaldeviceproperties;
      ///** @brief Features of the physical device that an application can use to check if a feature is supported */
      //VkPhysicalDeviceFeatures m_physicaldevicefeatures;
      /** @brief Features that have been enabled for use on the physical device */
      VkPhysicalDeviceFeatures m_physicaldevicefeaturesCreate;
      /** @brief Features that have been enabled for use on the physical device */
      VkPhysicalDeviceFeatures m_physicaldevicefeaturesEnabled;
      ///** @brief Memory types and heaps of the physical device */
      //VkPhysicalDeviceMemoryProperties m_physicaldevicememoryproperties;
      ///** @brief Queue family properties of the physical device */
      //::array<VkQueueFamilyProperties> m_queuefamilypropertya;
      /** @brief List of extensions supported by the device */
      string_array m_straSupportedExtensions;
      /** @brief Default command pool for the graphics queue family index */
      VkCommandPool m_commandpool;

      /** @brief Contains queue family indices */
      struct
      {
         uint32_t graphics;
         uint32_t compute;
         uint32_t transfer;
      } m_queuefamilyindices;


      context_win32();
      ~context_win32() override;


      virtual void _create_context_win32();

      void on_create_context() override;


      VkDevice device() const
      {

         return m_device;

      }

      virtual VkResult createLogicalDevice(
         VkPhysicalDeviceFeatures enabledFeatures, 
         ::array<const char *> enabledExtensions, 
         void * pNextChain, 
         bool useSwapChain = true, 
         VkQueueFlags requestedQueueTypes = VK_QUEUE_GRAPHICS_BIT | VK_QUEUE_COMPUTE_BIT);
      //virtual uint32_t getQueueFamilyIndex(VkQueueFlags queueFlags) const;
      virtual VkCommandPool createCommandPool(uint32_t queueFamilyIndex, VkCommandPoolCreateFlags createFlags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT);
      virtual bool isExtensionSupported(const ::scoped_string & scopedstrExtension);

      virtual void _create_offscreen_window(const ::int_size & size);

      void defer_create_window_context(::windowing::window * pwindow) override;
      void _defer_create_window_context(::windowing::window * pwindow) override;
      virtual void _create_window_context(::windowing::window * pwindow);

      //virtual void _create_window_buffer();
      void _create_offscreen_buffer(const ::int_size& size) override;
      void resize_offscreen_buffer(const ::int_size& size) override;
      void destroy_offscreen_buffer() override;

      void make_current() override;

      bool is_mesa() override;

      void render();

      string get_shader_version_text() override;

      void _translate_shader(string_array & straFragment) override;

      void swap_buffers() override;


   };


} // namespace gpu_vulkan



