// Created by camilo on 2025-05-21 17:00 <3ThomasBorregaardSorensen!!
#pragma once


namespace gpu_vulkan
{


   struct SwapChainSupportDetails
   {

      VkSurfaceCapabilitiesKHR capabilities;
      ::array<VkSurfaceFormatKHR> formats;
      ::array<VkPresentModeKHR> presentModes;

   };




   class CLASS_DECL_GPU_VULKAN physical_device :
      virtual public ::particle
   {
   public:


      ::pointer < approach >           m_papproach;
      // Physical device (GPU) that Vulkan will use
      VkPhysicalDevice                 m_physicaldevice;
      // Stores physical device properties (for e.g. checking device limits)
      VkPhysicalDeviceProperties       m_physicaldeviceproperties;
      // Stores the features available on the selected physical device (for e.g. checking if a feature is available)
      VkPhysicalDeviceFeatures         m_physicaldevicefeatures;
      // Stores all available memory (type) properties for the physical device
      VkPhysicalDeviceMemoryProperties m_physicaldevicememoryproperties;
      /** @brief Queue family properties of the physical device */
      ::array<VkQueueFamilyProperties> m_queuefamilypropertya;
      ///** @brief Contains queue family indices */
      //struct
      //{
      //   uint32_t graphics;
      //   uint32_t compute;
      //   uint32_t transfer;
      //} m_queuefamilyindices;

      //::array<VkDeviceQueueCreateInfo> m_devicequeuecreateinfoa;
      VkSurfaceKHR m_vksurfacekhr;


      physical_device();
      ~physical_device() override;

      VkSurfaceKHR surface() { return m_vksurfacekhr; }

      uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
      VkFormat findSupportedFormat(
         const ::array<VkFormat> & candidates, VkImageTiling tiling, VkFormatFeatureFlags features);

      
      virtual void _initialize_physical_device(approach * papproach, VkPhysicalDevice physicaldevice);

      uint32_t getQueueFamilyIndex(VkQueueFlags queueFlags) const;

      SwapChainSupportDetails getSwapChainSupport() { return querySwapChainSupport(); }
      vulkan::QueueFamilyIndices findPhysicalQueueFamilies() { return findQueueFamilies(); }


      vulkan::QueueFamilyIndices findQueueFamilies();
      SwapChainSupportDetails querySwapChainSupport();


   };


} // namespace gpu_vulkan