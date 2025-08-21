#pragma once
//#define GLFW_INCLUDE_NONE
////#include <GLFW/glfw3.h>
////#include <vector>

//#include "app-graphics3d/gpu_vulkan/_gpu_vulkan.h"
//#include "SceneFoundry/sandbox_renderer/include/window.h"
//#include "instance.h"

namespace sandbox_renderer
{

   //
   // struct SwapChainSupportDetails
   // {
   //    VkSurfaceCapabilitiesKHR capabilities;
   //    ::array_base<VkSurfaceFormatKHR> formats;
   //    ::array_base<VkPresentModeKHR> presentModes;
   // };
   //
   // struct QueueFamilyIndices
   // {
   //    uint32_t graphicsFamily;
   //    uint32_t presentFamily;
   //    bool graphicsFamilyHasValue = false;
   //    bool presentFamilyHasValue = false;
   //    bool isComplete() { return graphicsFamilyHasValue && presentFamilyHasValue; }
   // };
   //


   class CLASS_DECL_SANDBOX_RENDERER device :
      virtual public ::particle
   {
   public:


      //private:

      ::user::interaction * m_puserinteraction;
      //sandbox_instance * m_pinstance;
      ::pointer < ::gpu::device > m_pdevice;

      ::pointer < ::gpu::context > m_pgpucontext;


      // VkCommandPool m_commandPool;
      // VkSurfaceKHR m_surface;
      // VkQueue m_graphicsQueue;
      // VkQueue m_presentQueue;


      // const ::array_base<const char*> m_deviceExtensions = {
      //     VK_KHR_SWAPCHAIN_EXTENSION_NAME,
      //     VK_EXT_DESCRIPTOR_INDEXING_EXTENSION_NAME,
      //     VK_KHR_MAINTENANCE1_EXTENSION_NAME,
      //     VK_KHR_MAINTENANCE3_EXTENSION_NAME
      //     //VK_KHR_ACCELERATION_STRUCTURE_EXTENSION_NAME,
      //     //VK_KHR_RAY_TRACING_PIPELINE_EXTENSION_NAME,
      //     //VK_KHR_DEFERRED_HOST_OPERATIONS_EXTENSION_NAME,
      //     //VK_KHR_SPIRV_1_4_EXTENSION_NAME,
      //     //VK_KHR_SHADER_FLOAT_CONTROLS_EXTENSION_NAME,
      // };


      //device(sandbox_instance * pinstance, ::user::interaction * puserinteraction);
      device(::user::interaction * puserinteraction);
      ~device();

      // // Not copyable or movable
      // device(const device *) = delete;
      // void operator=(const device *) = delete;
      // device(VkDevice&&) = delete;
      // device * operator=(device *&) = delete;

  ///    VkCommandPool getCommandPool() { return m_commandPool; }
//
      // uint32_t getMemoryType(uint32_t typeBits, VkMemoryPropertyFlags properties, VkBool32* memTypeFound = nullptr) const;
      //
      // VkDevice device() { return m_logicalDevice; }
      //
      // VkSurfaceKHR surface() { return m_surface; }
      // VkQueue graphicsQueue() { return m_graphicsQueue; }
      // VkQueue presentQueue() { return m_presentQueue; }

      // SwapChainSupportDetails getSwapChainSupport() { return querySwapChainSupport(m_physicalDevice); }
      // uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
      // QueueFamilyIndices findPhysicalQueueFamilies() { return findQueueFamilies(m_physicalDevice); }
      // VkFormat findSupportedFormat(
      //    const ::array_base<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);

      // // Buffer Helper Functions
      // void createBuffer(
      //    VkDeviceSize size,
      //    VkBufferUsageFlags usage,
      //    VkMemoryPropertyFlags properties,
      //    VkBuffer& buffer,
      //    VkDeviceMemory& bufferMemory);
      // VkCommandBuffer beginSingleTimeCommands();
      // void endSingleTimeCommands(VkCommandBuffer commandBuffer);
      // void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
      // void copyBufferToImage(
      //    VkBuffer buffer, VkImage image, uint32_t width, uint32_t height, uint32_t layerCount);
      //
      // void createImageWithInfo(
      //    const VkImageCreateInfo& imageInfo,
      //    VkMemoryPropertyFlags properties,
      //    VkImage& image,
      //    VkDeviceMemory& imageMemory);

      // void transitionImageLayout(
      //    VkImage image,
      //    VkFormat format,
      //    VkImageLayout oldLayout,
      //    VkImageLayout newLayout,
      //    uint32_t mipLevels,
      //    uint32_t layerCount);

      // VkCommandBuffer createCommandBuffer(VkCommandBufferLevel level, bool begin = false);
      // VkCommandBuffer createCommandBuffer(VkCommandBufferLevel level, VkCommandPool pool, bool begin = false);

      // /// Ends, submits and frees a one‑time command buffer
      // void flushCommandBuffer(VkCommandBuffer commandBuffer, VkQueue queue, bool free = true);
      // void flushCommandBuffer(VkCommandBuffer commandBuffer, VkQueue queue, VkCommandPool pool, bool free = true);
      //
      // QueueFamilyIndices findQueueFamilies(VkPhysicalDevice pdevice);
      //
      // VkPhysicalDeviceProperties m_deviceProperties{};
      //
      // VkPhysicalDeviceMemoryProperties m_deviceMemoryProperties;
      // VkPhysicalDeviceFeatures m_enabledFeatures;

      // VkResult createBuffer(VkBufferUsageFlags usageFlags,
      //    VkMemoryPropertyFlags memoryPropertyFlags,
      //    VkDeviceSize size,
      //    VkBuffer* buffer,
      //    VkDeviceMemory* memory,
      //    void* data = nullptr);

      
      // virtual ::pointer < ::sandbox_renderer::pipeline > create_pipeline_from_file(
      //    const ::scoped_string scopedstrVertexPath,
      //    const ::scoped_string scopedstrFragmentPath
      // );
      //
      //
      // bool checkDeviceExtensionSupport(VkPhysicalDevice pdevice);
      // SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice pdevice);
      // bool hasStencilComponent(VkFormat format);
      //
      // // Query all the swapchain-support information for OUR surface:
      // SwapChainSupportDetails querySwapchainSupport(VkSurfaceKHR surface) const;

      // Pick the best surface format you like (srgb first, else the first you get):
      //VkSurfaceFormatKHR
        // chooseSwapSurfaceFormat(const ::array_base<VkSurfaceFormatKHR>& formats) const;

      // Pick the best present mode (mailbox if available, else FIFO):
      //VkPresentModeKHR
        // chooseSwapPresentMode(const ::array_base<VkPresentModeKHR>& presentModes) const;

      // Clamp the extent to the pdevice’s capabilities:
      //VkExtent2D
        // chooseSwapExtent(const VkSurfaceCapabilitiesKHR& caps, VkExtent2D desiredExtent) const;

   //private:


      //void pickPhysicalDevice();
      //void createLogicalDevice();
      //void createCommandPool();
      //void createSurface();
      //bool isDeviceSuitable(VkPhysicalDevice pdevice);


   //public:
      // VkPhysicalDevice m_physicalDevice;
      // VkDevice m_logicalDevice;
      ::pointer<object_model> createModelFromFile(const  ::scoped_string& filepath, bool isSkybox = false);


   };



} // namespace sandbox_renderer



