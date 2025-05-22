#pragma once


#include "aura/graphics/gpu/context.h"
#include "acme/prototype/prototype/memory.h"


namespace gpu_vulkan
{




   class CLASS_DECL_GPU_VULKAN context :
      virtual public ::gpu::context
   {
   public:


      itask									m_itaskGpu;


      //unsigned int                     m_VAO;
      //unsigned int                     m_VBO;

      //int                            m_iMatrixUniform;

      //int                           m_gluTextureBitmap1;
      //int                              m_iLastBitmap1Scan;
      //::int_size                       m_sizeBitmap1;

      //memory                           m_memorySwap;

      bool                                m_bOffscreen;
      bool                             m_bMesa;
      //HGLRC                            m_hrc;
      //HDC                              m_hdc;
      //HWND                             m_hwnd;
      //HDC                              m_hdcGraphics;

         /** @brief Physical device representation */
      //VkPhysicalDevice m_physicaldevice;
      ::pointer < physical_device >       m_pphysicaldevice;
      /** @brief Logical device representation (application's view of the device) */
      VkDevice m_vkdevice;
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
      ///** @brief Default command pool for the graphics queue family index */
      VkCommandPool m_vkcommandpool;

      /** @brief Contains queue family indices */
      vulkan::QueueFamilyIndices m_queuefamilyindices;
      //struct
      //{
      //   uint32_t graphics;
      //   uint32_t compute;
      //   uint32_t transfer;
      //} m_queuefamilyindices;



      //graphics3d_vulkan::context
#if defined(NDEBUG)
      const bool enableValidationLayers = false;
#else
      const bool enableValidationLayers = true;
#endif

      VkInstance m_vkinstance;
      VkDebugUtilsMessengerEXT debugMessenger;
      //VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
      //::pointer < ::cube::impact > m_pimpact;

      //VkCommandPool m_vkcommandpool;

      //VkDevice m_vkdevice;
      //VkSurfaceKHR m_vksurfacekhr;
      VkQueue m_vkqueueGraphics;
      VkQueue m_vkqueuePresent;

      ::array<const char *> validationLayers;
      ::array<const char *> deviceExtensions;



      context();
      ~context() override;


      string _001GetIntroProjection() override;
      string _001GetIntroFragment() override;

      void draw() override;
      void start_drawing() override;
      void global_transform() override;
      void render() override;

      void set_bitmap_1(::image::image *pimage) override;

      void swap_buffers() override;

      //virtual void create_offscreen_buffer(const ::int_size& size);
      //virtual void _create_offscreen_buffer(const ::int_size& size);

      //virtual void resize_offscreen_buffer(const ::int_size& size);
      //virtual void destroy_offscreen_buffer();

   /*   virtual void translate_shader(string & str);

      virtual void _translate_shader(string_array& stra);*/

      //virtual void make_current();

      // virtual string load_fragment(const ::string & pszPath, enum_shader_source& eshadersource);

      //virtual string get_shader_version_text();
      
      void set_matrix_uniform(const ::gpu::payload & uniformMatrix) override;




      virtual void _create_context_win32();

      void on_create_context() override;


      VkDevice device() const
      {

         return m_vkdevice;

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
      void _create_offscreen_buffer(const ::int_size & size) override;
      void resize_offscreen_buffer(const ::int_size & size) override;
      void destroy_offscreen_buffer() override;

      void make_current() override;

      bool is_mesa() override;

      //void render();

      string get_shader_version_text() override;

      void _translate_shader(string_array & straFragment) override;

      //void swap_buffers() override;


      //graphics3d_vulkan::context


      VkCommandPool getCommandPool() { return m_vkcommandpool; }
      VkDevice logicalDevice() { return m_vkdevice; }

      VkQueue graphicsQueue() { return m_vkqueueGraphics; }
      VkQueue presentQueue() { return m_vkqueuePresent; }


      // Buffer Helper Functions
      void createBuffer(
         VkDeviceSize size,
         VkBufferUsageFlags usage,
         VkMemoryPropertyFlags properties,
         VkBuffer & buffer,
         VkDeviceMemory & bufferMemory);
      VkCommandBuffer beginSingleTimeCommands();
      void endSingleTimeCommands(VkCommandBuffer commandBuffer);
      void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
      void copyBufferToImage(
         VkBuffer buffer, VkImage image, uint32_t width, uint32_t height, uint32_t layerCount);

      void createImageWithInfo(
         const VkImageCreateInfo & imageInfo,
         VkMemoryPropertyFlags properties,
         VkImage & image,
         VkDeviceMemory & imageMemory);

      VkPhysicalDeviceProperties properties;


      void submitWork(VkCommandBuffer cmdBuffer, VkQueue queue);


      //public:
      //void _createInstance();
      //void _setupDebugMessenger();
      //void _createSurface();
      //void _pickPhysicalDevice();
      //void _createLogicalDevice();
      //void _createCommandPool();

      // helper functions
      //bool isDeviceSuitable(VkPhysicalDevice pvkcdevice);
      //::array<const char *> getRequiredExtensions();
      bool checkValidationLayerSupport();
      void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT & createInfo);
      //void hasGflwRequiredInstanceExtensions();
      //bool checkDeviceExtensionSupport(VkPhysicalDevice pvkcdevice);



   };


} // namespace gpu



