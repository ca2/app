//// From V0idsEmbrace@Twich continuum project
//// by camilo on 2025-05-17 02:40 <3ThomasBorregaardSorensen!!
//#pragma once
//
//
//namespace graphics3d
//{
//
//
//   class CLASS_DECL_CUBE context :
//      virtual public ::particle
//   {
//   public:
//
//
//      ::pointer < ::cube::impact > m_pimpact;
//      
//      context();
//      ~context();
//
//
//      virtual void initialize_context(::cube::impact* pimpact);
//
//
//
//   //   VkCommandPool getCommandPool() { return m_vkcommandpool; }
//   //   VkDevice logicalDevice() { return m_vkdevice; }
//
//   //   VkSurfaceKHR surface() { return m_vksurfacekhr; }
//   //   VkQueue graphicsQueue() { return m_vkqueueGraphics; }
//   //   VkQueue presentQueue() { return m_vkqueuePresent; }
//
//   //   SwapChainSupportDetails getSwapChainSupport() { return querySwapChainSupport(physicalDevice); }
//   //   uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
//   //   QueueFamilyIndices findPhysicalQueueFamilies() { return findQueueFamilies(physicalDevice); }
//   //   VkFormat findSupportedFormat(
//   //      const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);
//
//   //   // Buffer Helper Functions
//   //   void createBuffer(
//   //      VkDeviceSize size,
//   //      VkBufferUsageFlags usage,
//   //      VkMemoryPropertyFlags properties,
//   //      VkBuffer& buffer,
//   //      VkDeviceMemory& bufferMemory);
//   //   VkCommandBuffer beginSingleTimeCommands();
//   //   void endSingleTimeCommands(VkCommandBuffer commandBuffer);
//   //   void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
//   //   void copyBufferToImage(
//   //      VkBuffer buffer, VkImage image, uint32_t width, uint32_t height, uint32_t layerCount);
//
//   //   void createImageWithInfo(
//   //      const VkImageCreateInfo& imageInfo,
//   //      VkMemoryPropertyFlags properties,
//   //      VkImage& image,
//   //      VkDeviceMemory& imageMemory);
//
//   //   VkPhysicalDeviceProperties properties;
//
//
//   //   void submitWork(VkCommandBuffer cmdBuffer, VkQueue queue);
//
//   //public:
//   //   void createInstance();
//   //   void setupDebugMessenger();
//   //   void createSurface();
//   //   void pickPhysicalDevice();
//   //   void createLogicalDevice();
//   //   void createCommandPool();
//
//   //   // helper functions
//   //   bool isDeviceSuitable(VkPhysicalDevice pvkcdevice);
//   //   std::vector<const char*> getRequiredExtensions();
//   //   bool checkValidationLayerSupport();
//   //   QueueFamilyIndices findQueueFamilies(VkPhysicalDevice pvkcdevice);
//   //   void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
//   //   void hasGflwRequiredInstanceExtensions();
//   //   bool checkDeviceExtensionSupport(VkPhysicalDevice pvkcdevice);
//   //   SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice pvkcdevice);
//
//   //   VkInstance m_vkinstance;
//   //   VkDebugUtilsMessengerEXT debugMessenger;
//   //   VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
//   //   ::pointer < ::cube::container > m_pcontainer;
//   //   VkCommandPool m_vkcommandpool;
//
//   //   VkDevice m_vkdevice;
//   //   VkSurfaceKHR m_vksurfacekhr;
//   //   VkQueue m_vkqueueGraphics;
//   //   VkQueue m_vkqueuePresent;
//
//   //   const std::vector<const char*> validationLayers = { "VK_LAYER_KHRONOS_validation" };
//   //   const std::vector<const char*> deviceExtensions = { VK_KHR_SWAPCHAIN_EXTENSION_NAME };
//
//      virtual void clear(const ::color::color & color);
//
//
//   };
//
//
//}  // namespace graphics3d
//
//
