// Created by camilo on 2023-04-27 17:06 <3ThomasBorregaardSorensen!!
#pragma once


#undef USUAL_OPERATING_SYSTEM_SUPPRESSIONS
#include "acme/_operating_system.h"


#if defined(WINDOWS_DESKTOP)
#define VK_USE_PLATFORM_WIN32_KHR
#else
#error "wwwwwhat?!?!"
#endif


#include <vulkan/vulkan.h>


// Custom define for better code readability
#define VK_FLAGS_NONE 0
// Default fence timeout in nanoseconds
#define DEFAULT_FENCE_TIMEOUT 100000000000

// Macro to check and display Vulkan return results
#if defined(__ANDROID__)
#define VK_CHECK_RESULT(f)																				\
{																										\
	VkResult res = (f);																					\
	if (res != VK_SUCCESS)																				\
	{																									\
		LOGE("Fatal : VkResult is \" %s \" in %s at line %d", vks::tools::errorString(res).c_str(), __FILE__, __LINE__); \
		assert(res == VK_SUCCESS);																		\
	}																									\
}
#else
#define VK_CHECK_RESULT(f)																				\
{																										\
	VkResult res = (f);																					\
	if (res != VK_SUCCESS)																				\
	{																									\
		::information() << "Fatal : VkResult is \"" << ::vulkan::errorString(res) << "\" in " << __FILE__ << " at line " << __LINE__ ; \
		ASSERT(res == VK_SUCCESS);																		\
	}																									\
}
#endif

//const ::string getAssetPath();
//const ::string getShaderBasePath();

namespace vulkan
{


   struct QueueFamilyIndices
   {
      int graphicsFamily;
      int presentFamily;
      int computeFamily;
      int transferFamily;
      bool graphicsFamilyHasValue = false;
      bool presentFamilyHasValue = false;
      bool computeFamilyHasValue = false;
      bool transferFamilyHasValue = false;

      void clear()
      {
         graphicsFamily = -1;
         presentFamily = -1;
         computeFamily = -1;
         transferFamily = -1;
         graphicsFamilyHasValue = false;
         presentFamilyHasValue = false;
         computeFamilyHasValue = false;
         transferFamilyHasValue = false;

      }
      //bool isComplete() { return graphicsFamilyHasValue && presentFamilyHasValue; }
   };


   /** @brief Setting this path chnanges the place where the samples looks for assets and shaders */
   //extern ::string resourcePath;

   /** @brief Disable message boxes on fatal errors */
   //extern bool errorModeSilent;

   /** @brief Returns an error code as a string */
   CLASS_DECL_GPU_VULKAN ::string errorString(VkResult errorCode);

   /** @brief Returns the device type as a string */
   CLASS_DECL_GPU_VULKAN ::string physicalDeviceTypeString(VkPhysicalDeviceType type);

   // Selected a suitable supported depth format starting with 32 bit down to 16 bit
   // Returns false if none of the depth formats in the list is supported by the device
   CLASS_DECL_GPU_VULKAN VkBool32 getSupportedDepthFormat(VkPhysicalDevice physicalDevice, VkFormat * depthFormat);
   // Same as getSupportedDepthFormat but will only select formats that also have stencil
   CLASS_DECL_GPU_VULKAN VkBool32 getSupportedDepthStencilFormat(VkPhysicalDevice physicalDevice, VkFormat * depthStencilFormat);

   // Returns true a given format support LINEAR filtering
   CLASS_DECL_GPU_VULKAN VkBool32 formatIsFilterable(VkPhysicalDevice physicalDevice, VkFormat format, VkImageTiling tiling);
   // Returns true if a given format has a stencil part
   CLASS_DECL_GPU_VULKAN VkBool32 formatHasStencil(VkFormat format);

   // Put an image memory barrier for setting an image layout on the sub resource into the given command buffer
   CLASS_DECL_GPU_VULKAN void setImageLayout(
      VkCommandBuffer cmdbuffer,
      VkImage image,
      VkImageLayout oldImageLayout,
      VkImageLayout newImageLayout,
      VkImageSubresourceRange subresourceRange,
      VkPipelineStageFlags srcStageMask = VK_PIPELINE_STAGE_ALL_COMMANDS_BIT,
      VkPipelineStageFlags dstStageMask = VK_PIPELINE_STAGE_ALL_COMMANDS_BIT);
   // Uses a fixed sub resource layout with first mip level and layer
   CLASS_DECL_GPU_VULKAN void setImageLayout(
      VkCommandBuffer cmdbuffer,
      VkImage image,
      VkImageAspectFlags aspectMask,
      VkImageLayout oldImageLayout,
      VkImageLayout newImageLayout,
      VkPipelineStageFlags srcStageMask = VK_PIPELINE_STAGE_ALL_COMMANDS_BIT,
      VkPipelineStageFlags dstStageMask = VK_PIPELINE_STAGE_ALL_COMMANDS_BIT);

   /** @brief Insert an image memory barrier into the command buffer */
   CLASS_DECL_GPU_VULKAN void insertImageMemoryBarrier(
      VkCommandBuffer cmdbuffer,
      VkImage image,
      VkAccessFlags srcAccessMask,
      VkAccessFlags dstAccessMask,
      VkImageLayout oldImageLayout,
      VkImageLayout newImageLayout,
      VkPipelineStageFlags srcStageMask,
      VkPipelineStageFlags dstStageMask,
      VkImageSubresourceRange subresourceRange);

   // Display error message and exit on fatal error
   CLASS_DECL_GPU_VULKAN void exitFatal(const ::string & message, int32_t exitCode);
   CLASS_DECL_GPU_VULKAN void exitFatal(const ::string & message, VkResult resultCode);

//   // Load a SPIR-V shader (binary)
//#if defined(__ANDROID__)
//   VkShaderModule loadShader(AAssetManager * assetManager, const char * fileName, VkDevice device);
//#else
//   VkShaderModule loadShader(const char * fileName, VkDevice device);
//#endif

   /** @brief Checks if a file exists */
   CLASS_DECL_GPU_VULKAN bool fileExists(const ::string & filename);

   CLASS_DECL_GPU_VULKAN uint32_t alignedSize(uint32_t value, uint32_t alignment);
   CLASS_DECL_GPU_VULKAN VkDeviceSize alignedVkSize(VkDeviceSize value, VkDeviceSize alignment);


} // namespace vulkan



