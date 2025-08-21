#include "framework.h"
//#include "image.h"
//
// //#include <stdexcept>
// namespace sandbox_renderer
// {
//
//
//
//    void sandbox_image::create(
//       device* pdevice,
//       uint32_t width,
//       uint32_t height,
//       VkFormat format,
//       VkImageUsageFlags usage,
//       VkImageAspectFlags aspectMask,
//       VkSampleCountFlagBits samples,
//       VkImageLayout initialLayout,
//       VkImageTiling tiling,
//       VkMemoryPropertyFlags memoryProperties
//    ) {
//       m_pDevice = pdevice;
//       m_width = width;
//       m_height = height;
//       m_format = format;
//
//       VkImageCreateInfo imageInfo{};
//       imageInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
//       imageInfo.imageType = VK_IMAGE_TYPE_2D;
//       imageInfo.extent = { width, height, 1 };
//       imageInfo.mipLevels = 1;
//       imageInfo.arrayLayers = 1;
//       imageInfo.format = format;
//       imageInfo.tiling = tiling;
//       imageInfo.initialLayout = initialLayout;
//       imageInfo.usage = usage;
//       imageInfo.samples = samples;
//       imageInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
//
//       if (vkCreateImage(pdevice->device(), &imageInfo, nullptr, &m_image) != VK_SUCCESS) {
//          throw std::runtime_error("Failed to create image!");
//       }
//
//       VkMemoryRequirements memRequirements;
//       vkGetImageMemoryRequirements(pdevice->device(), m_image, &memRequirements);
//
//       VkMemoryAllocateInfo allocInfo{};
//       allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
//       allocInfo.allocationSize = memRequirements.size;
//       allocInfo.memoryTypeIndex = pdevice->findMemoryType(memRequirements.memoryTypeBits, memoryProperties);
//
//       if (vkAllocateMemory(pdevice->device(), &allocInfo, nullptr, &m_memory) != VK_SUCCESS) {
//          throw std::runtime_error("Failed to allocate image memory!");
//       }
//
//       vkBindImageMemory(pdevice->device(), m_image, m_memory, 0);
//
//       // Create view
//       VkImageViewCreateInfo viewInfo{};
//       viewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
//       viewInfo.image = m_image;
//       viewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
//       viewInfo.format = format;
//       viewInfo.subresourceRange.aspectMask = aspectMask;
//       viewInfo.subresourceRange.levelCount = 1;
//       viewInfo.subresourceRange.layerCount = 1;
//
//       if (vkCreateImageView(pdevice->device(), &viewInfo, nullptr, &m_imageView) != VK_SUCCESS) {
//          throw std::runtime_error("Failed to create image view!");
//       }
//    }
//
//    void sandbox_image::destroy() {
//       if (!m_pDevice) return;
//       if (m_imageView != VK_NULL_HANDLE) vkDestroyImageView(m_pDevice->device(), m_imageView, nullptr);
//       if (m_image != VK_NULL_HANDLE) vkDestroyImage(m_pDevice->device(), m_image, nullptr);
//       if (m_memory != VK_NULL_HANDLE) vkFreeMemory(m_pDevice->device(), m_memory, nullptr);
//    }
//
//    sandbox_image::~sandbox_image() {
//       destroy();
//    }
//
//
// } // namespace sandbox_renderer
//
//
