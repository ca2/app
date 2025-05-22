// Created by camilo on 2025-05-21 17:02 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "approach.h"
#include "physical_device.h"


namespace gpu_vulkan
{


   physical_device::physical_device()
   {

      m_physicaldevice = VK_NULL_HANDLE;
      m_physicaldeviceproperties = {};
      m_physicaldevicefeatures = {};
      m_physicaldevicememoryproperties = {};
      m_vksurfacekhr = nullptr;

   }


   physical_device::~physical_device()
   {


   }

   
   void physical_device::_initialize_physical_device(approach * papproach, VkPhysicalDevice physicaldevice)
   {

      m_papproach = papproach;

      m_physicaldevice = physicaldevice;

      // Store properties (including limits), features and memory properties of the physical device (so that examples can check against them)
      // Store Properties features, limits and properties of the physical device for later use
      // Device properties also contain limits and sparse properties
      vkGetPhysicalDeviceProperties(m_physicaldevice, &m_physicaldeviceproperties);
      // Features should be checked by the examples before using them
      vkGetPhysicalDeviceFeatures(m_physicaldevice, &m_physicaldevicefeatures);
      // Memory properties are used regularly for creating all kinds of buffers
      vkGetPhysicalDeviceMemoryProperties(m_physicaldevice, &m_physicaldevicememoryproperties);
      // Queue family properties, used for setting up requested queues upon device creation
      uint32_t queueFamilyCount;
      vkGetPhysicalDeviceQueueFamilyProperties(m_physicaldevice, &queueFamilyCount, nullptr);
      assert(queueFamilyCount > 0);
      m_queuefamilypropertya.set_size(queueFamilyCount);
      vkGetPhysicalDeviceQueueFamilyProperties(m_physicaldevice, &queueFamilyCount, m_queuefamilypropertya.data());

      //::array<VkDeviceQueueCreateInfo> queueCreateInfos{};

      //// Get queue family indices for the requested queue family types
      //// Note that the indices may overlap depending on the implementation

      //const float defaultQueuePriority(0.0f);

      //// Graphics queue
      //if (requestedQueueTypes & VK_QUEUE_GRAPHICS_BIT)
      //{
      //   m_queuefamilyindices.graphics = getQueueFamilyIndex(VK_QUEUE_GRAPHICS_BIT);
      //   VkDeviceQueueCreateInfo queueInfo{};
      //   queueInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
      //   queueInfo.queueFamilyIndex = m_queuefamilyindices.graphics;
      //   queueInfo.queueCount = 1;
      //   queueInfo.pQueuePriorities = &defaultQueuePriority;
      //   queueCreateInfos.add(queueInfo);
      //}
      //else
      //{
      //   m_queuefamilyindices.graphics = 0;
      //}

     

   }

   /**
   * Get the index of a queue family that supports the requested queue flags
   * SRS - support VkQueueFlags parameter for requesting multiple flags vs. VkQueueFlagBits for a single flag only
   *
   * @param queueFlags Queue flags to find a queue family index for
   *
   * @return Index of the queue family index that matches the flags
   *
   * @throw Throws an exception if no queue family index could be found that supports the requested flags
   */
   uint32_t physical_device::getQueueFamilyIndex(VkQueueFlags queueFlags) const
   {
      // Dedicated queue for compute
      // Try to find a queue family index that supports compute but not graphics
      if ((queueFlags & VK_QUEUE_COMPUTE_BIT) == queueFlags)
      {
         for (uint32_t i = 0; i < static_cast<uint32_t>(m_queuefamilypropertya.size()); i++)
         {
            if ((m_queuefamilypropertya[i].queueFlags & VK_QUEUE_COMPUTE_BIT) && ((m_queuefamilypropertya[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) == 0))
            {
               return i;
            }
         }
      }

      // Dedicated queue for transfer
      // Try to find a queue family index that supports transfer but not graphics and compute
      if ((queueFlags & VK_QUEUE_TRANSFER_BIT) == queueFlags)
      {
         for (uint32_t i = 0; i < static_cast<uint32_t>(m_queuefamilypropertya.size()); i++)
         {
            if ((m_queuefamilypropertya[i].queueFlags & VK_QUEUE_TRANSFER_BIT) && ((m_queuefamilypropertya[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) == 0) && ((m_queuefamilypropertya[i].queueFlags & VK_QUEUE_COMPUTE_BIT) == 0))
            {
               return i;
            }
         }
      }

      // For other queue types or if no separate compute queue is present, return the first one to support the requested flags
      for (uint32_t i = 0; i < static_cast<uint32_t>(m_queuefamilypropertya.size()); i++)
      {
         if ((m_queuefamilypropertya[i].queueFlags & queueFlags) == queueFlags)
         {
            return i;
         }
      }

      throw ::exception(error_not_found, "Could not find a matching queue family index");
   }


   vulkan::QueueFamilyIndices physical_device::findQueueFamilies()
   {

      vulkan::QueueFamilyIndices indices;

      uint32_t queueFamilyCount = 0;
      vkGetPhysicalDeviceQueueFamilyProperties(m_physicaldevice, &queueFamilyCount, nullptr);

      ::array<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
      vkGetPhysicalDeviceQueueFamilyProperties(m_physicaldevice, &queueFamilyCount, queueFamilies.data());

      int i = 0;
      for (const auto & queueFamily : queueFamilies)
      {
         if (queueFamily.queueCount > 0 && queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
         {
            indices.graphicsFamily = i;
            indices.graphicsFamilyHasValue = true;
         }
         if (queueFamily.queueCount > 0 && queueFamily.queueFlags & VK_QUEUE_COMPUTE_BIT)
         {
            indices.computeFamily = i;
            indices.computeFamilyHasValue = true;
         }
         if (queueFamily.queueCount > 0 && queueFamily.queueFlags & VK_QUEUE_TRANSFER_BIT)
         {
            indices.transferFamily = i;
            indices.transferFamilyHasValue = true;
         }
         if (m_vksurfacekhr)
         {
            VkBool32 presentSupport = false;
            vkGetPhysicalDeviceSurfaceSupportKHR(m_physicaldevice, i, m_vksurfacekhr, &presentSupport);
            if (queueFamily.queueCount > 0 && presentSupport)
            {
               indices.presentFamily = i;
               indices.presentFamilyHasValue = true;
            }
         }
         //if (indices.isComplete()) {
           // break;
         //}

         i++;
      }

      return indices;

   }


   SwapChainSupportDetails physical_device::querySwapChainSupport()
   {

      SwapChainSupportDetails details{};

      if (m_vksurfacekhr)
      {

         vkGetPhysicalDeviceSurfaceCapabilitiesKHR(m_physicaldevice, m_vksurfacekhr, &details.capabilities);

         uint32_t formatCount;
         vkGetPhysicalDeviceSurfaceFormatsKHR(m_physicaldevice, m_vksurfacekhr, &formatCount, nullptr);

         if (formatCount != 0) {
            details.formats.resize(formatCount);
            vkGetPhysicalDeviceSurfaceFormatsKHR(m_physicaldevice, m_vksurfacekhr, &formatCount, details.formats.data());
         }

         uint32_t presentModeCount;
         vkGetPhysicalDeviceSurfacePresentModesKHR(m_physicaldevice, m_vksurfacekhr, &presentModeCount, nullptr);

         if (presentModeCount != 0) {
            details.presentModes.resize(presentModeCount);
            vkGetPhysicalDeviceSurfacePresentModesKHR(
               m_physicaldevice,
               m_vksurfacekhr,
               &presentModeCount,
               details.presentModes.data());
         }

      }

      return details;

   }


   VkFormat physical_device::findSupportedFormat(
   const ::array<VkFormat> & candidates, VkImageTiling tiling, VkFormatFeatureFlags features) 
   {

      for (VkFormat format : candidates) 
      {

         VkFormatProperties props;
         vkGetPhysicalDeviceFormatProperties(m_physicaldevice, format, &props);

         if (tiling == VK_IMAGE_TILING_LINEAR && (props.linearTilingFeatures & features) == features) {
            return format;
         }
         else if (
            tiling == VK_IMAGE_TILING_OPTIMAL && (props.optimalTilingFeatures & features) == features) {
            return format;
         }
      }
      throw ::exception(error_failed, "failed to find supported format!");
   }


   uint32_t physical_device::findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties) 
   {

      VkPhysicalDeviceMemoryProperties memProperties;
      vkGetPhysicalDeviceMemoryProperties(m_physicaldevice, &memProperties);
      for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++) {
         if ((typeFilter & (1 << i)) &&
            (memProperties.memoryTypes[i].propertyFlags & properties) == properties) {
            return i;
         }
      }

      throw ::exception(error_failed, "failed to find suitable memory type!");
   }

} // namespace gpu_vulkan