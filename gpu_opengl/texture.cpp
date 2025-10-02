// Created by camilo on 2025-06-08 18:14 < 3ThomasBorregaardSørensen!!
#include "framework.h"
#include "texture.h"
#include "_gpu_opengl.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "acme/graphics/image/pixmap.h"
#include "aura/graphics/image/image.h"
#include "bred/gpu/context_lock.h"
#include "context.h"
#include "device.h"
#include "gpu/_ktx.h"
#include "lock.h"
#include "renderer.h"

#include <stb/stb_image.h>

namespace gpu_opengl
{


   texture::texture()
   {

      m_gluTextureID = 0;
      m_gluDepthStencilRBO = 0;
      m_gluFbo = 0;
   }


   texture::~texture() {}


   void texture::initialize_hdr_texture_on_memory(::gpu::renderer *pgpurenderer, const ::block & block)
   {

      ::gpu::context_lock contextlock(pgpurenderer->m_pgpucontext);

      m_pgpurenderer = pgpurenderer;

      auto data = block.data();

      auto size = block.size();

      int w, h, numChannels;

      auto imagedata = stbi_loadf_from_memory(data, size, &w, &h, &numChannels, 0);

      if (!imagedata)
      {

         warning() << "Failed to load texture data";

         stbi_image_free(imagedata);

         return;

      }

      // m_etype = etype;
      m_rectangleTarget = ::int_rectangle(::int_size(w, h));

      m_bWithDepth = false;

      glGenTextures(1, &m_gluTextureID);
      GLCheckError("");
      glBindTexture(GL_TEXTURE_2D, m_gluTextureID);
      GLCheckError("");

      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, w, h, 0, GL_RGB, GL_FLOAT, imagedata);
      GLCheckError("");

      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
      GLCheckError("");
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
      GLCheckError("");
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      GLCheckError("");
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      GLCheckError("");

      stbi_image_free(imagedata);

   }


   void texture::initialize_image_texture(::gpu::renderer *prenderer, const ::int_rectangle &rectangleTarget,
                                          bool bWithDepth, const ::pointer_array<::image::image> &imagea,
                                          enum_type etype)
   {

      if (m_rectangleTarget == rectangleTarget)
      {

         return;
      }

      if (etype == e_type_cube_map)
      {

         m_gluType = GL_TEXTURE_CUBE_MAP;
      }
      else
      {

         m_gluType = GL_TEXTURE_2D;
      }

      auto sizeCurrent = m_rectangleTarget.size();

      ::gpu::texture::initialize_image_texture(prenderer, rectangleTarget, bWithDepth, imagea, etype);

      ::gpu::context_lock contextlock(m_pgpurenderer->m_pgpucontext);

      if (sizeCurrent != rectangleTarget.size())
      {

         if (!m_gluTextureID)
         {

            glGenTextures(1, &m_gluTextureID); // 1. Generate a texture ID
            GLCheckError("");
         }

         glBindTexture(m_gluType, m_gluTextureID); // 2. Bind the texture to the 2D texture target
         GLCheckError("");

         glTexParameteri(m_gluType, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
         GLCheckError("");
         glTexParameteri(m_gluType, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
         GLCheckError("");
         if (m_gluType == GL_TEXTURE_CUBE_MAP)
         {
            glTexParameteri(m_gluType, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
            GLCheckError("");
         }
         glTexParameteri(m_gluType, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
         GLCheckError("");
         glTexParameteri(m_gluType, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
         GLCheckError("");

         if (m_gluType == GL_TEXTURE_2D)
         {

            ::memory memory;

            if (imagea.has_element())
            {

               auto scan_area = m_rectangleTarget.area() * 4;

               memory.set_size(scan_area);

               if (imagea.size() != rectangleTarget.size())
               {

                  throw ::exception(error_wrong_state);
               }

               auto pimage32 = (image32_t *)memory.data();

               pimage32->copy(imagea.first());
            }

            auto data = memory.data();

            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_rectangleTarget.width(), m_rectangleTarget.height(), 0, GL_RGBA,
                         GL_UNSIGNED_BYTE, data);
            GLCheckError("");
         }
         else if (m_gluType == GL_TEXTURE_CUBE_MAP)
         {

            if (imagea.first()->width() <= 0 || imagea.first()->height() <= 0)
            {

               throw ::exception(error_wrong_state);
            }
            else if (imagea.first()->height() != imagea.first()->width())
            {

               throw ::exception(error_wrong_state);
            }

            ::memory memory;

            memory.set_size(imagea.first()->area() * 4);

            ::int_point point(0, 0);

            ::int_size size(imagea.first()->size());

            int scan = size.width() * 4;

            for (unsigned int i = 0; i < 6; i++)
            {

               auto pimage32 = (::image32_t *)memory.data();

               pimage32->copy(size.cx(), size.cy(), scan, imagea[i]->image32(), imagea[i]->m_iScan);

               if (pimage32)
               {

                  // Load the texture data into the cubemap
                  glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_BGRA, size.cx(), size.cy(), 0, GL_BGRA,
                               GL_UNSIGNED_BYTE, pimage32);

                  GLCheckError("");

                  // stbi_image_free(data);
               }
               // else if (data) {
               //    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
               //       0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
               //    stbi_image_free(data);
               // }
               // else {
               //    std::cout << "Failed to load cubemap texture at path: " << facesCubemap[i] << std::endl;
               //    stbi_image_free(data);
               // }
            }
         }
         else
         {

            throw ::exception(error_wrong_state);
         }

         // Optional: generate mipmaps
         // glGenerateMipmap(GL_TEXTURE_2D);

         // free(data);

         glBindTexture(m_gluType, 0); // Unbind when done
         GLCheckError("");
      }
   }


   // void texture::blend(::gpu::texture* ptexture, const ::int_rectangle& rectangleTarget)
   //{

   //   m_pgpurenderer->blend(this, ptexture, rectangleTarget);

   //}


   void texture::create_render_target()
   {

      if (m_gluFbo)
      {

         return;
      }

      //::gpu::context_lock contextlock(m_pgpurenderer->m_pgpucontext);


      // GLuint fboSrc, fboDst;
      glGenFramebuffers(1, &m_gluFbo);
      GLCheckError("");
      glBindFramebuffer(GL_FRAMEBUFFER, m_gluFbo);
      GLCheckError("");

      if (m_gluTextureID)
      {

         glBindTexture(GL_TEXTURE_2D, m_gluTextureID);
         GLCheckError("");

         glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_gluTextureID, 0);
         GLCheckError("");

         // Set draw buffer
         GLenum drawBufs[] = {GL_COLOR_ATTACHMENT0};
         glDrawBuffers(1, drawBufs); // REQUIRED for user-defined FBOs
         GLCheckError("");
      }

      if (m_gluDepthStencilRBO)
      {

         glBindRenderbuffer(GL_RENDERBUFFER, m_gluDepthStencilRBO);
         GLCheckError("");

         glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_gluDepthStencilRBO);
         GLCheckError("");
      }

      GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

      if (status != GL_FRAMEBUFFER_COMPLETE)
      {

         warning() << "Framebuffer attachment is not complete";
      }

      glBindFramebuffer(GL_FRAMEBUFFER, 0);
   }


   void texture::create_depth_resources()
   {

      if (m_gluDepthStencilRBO)
      {

         return;
      }

      int width = m_rectangleTarget.width();

      int height = m_rectangleTarget.height();

      glGenRenderbuffers(1, &m_gluDepthStencilRBO);
      GLCheckError("");

      glBindRenderbuffer(GL_RENDERBUFFER, m_gluDepthStencilRBO);
      GLCheckError("");

      glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
      GLCheckError("");

      glBindRenderbuffer(GL_RENDERBUFFER, 0);
      GLCheckError("");
   }


   void texture::bind_render_target()
   {

      if (!m_gluFbo)
      {

         create_render_target();
      }

      if (!m_gluFbo)
      {

         throw ::exception(error_wrong_state);
      }

      glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_gluFbo);
      GLCheckError("");

      glDrawBuffer(GL_COLOR_ATTACHMENT0);
      GLCheckError("");
   }


   void texture::set_pixels(const ::int_rectangle &rectangle, const void *data)
   {

      glBindTexture(GL_TEXTURE_2D, m_gluTextureID);
      glTexSubImage2D(GL_TEXTURE_2D,
                      0, // mip level
                      rectangle.left(), rectangle.top(), // offset inside the texture
                      rectangle.width(), rectangle.height(),
                      GL_RGBA, // format of the new data
                      GL_UNSIGNED_BYTE, // type of the new data
                      data // pointer to new pixels
      );

      glBindTexture(GL_TEXTURE_2D, 0);
   }


   // Loads a cubemap from a single KTX file
   void texture::KtxLoadCubemapFromFile(const ::scoped_string &name, ::string filename, bool b32)
   // VkFormat format,
   // VkQueue copyQueue,
   // VkImageUsageFlags imageUsageFlags,
   // VkImageLayout imageLayout)
   {
      m_etype = e_type_cube_map;

      ktxTexture *ktxTexture;
      ktxResult result = loadKTXFile(this, filename, &ktxTexture);
      if (result != KTX_SUCCESS)
      {

         throw ::exception(error_failed);

         return;
      }

      GLenum glError = 0;

      ktxResult resultUpload = ktxTexture_GLUpload(ktxTexture, &m_gluTextureID, &m_gluType, &glError);

      if (resultUpload != KTX_SUCCESS)
      {

         throw ::exception(error_failed);

         return;
      }

      // ::cast<::gpu_opengl::context> pcontext = m_pgpurenderer->m_pgpucontext;
      //
      // ::cast<::gpu_opengl::device> pgpudevice = pcontext->m_pgpudevice;
      //
      // //auto pphysicaldevice = pgpudevice->m_pphysicaldevice;
      //
      // m_rectangleTarget.left() = 0;
      // m_rectangleTarget.top() = 0;
      // //this->m_pDevice = pdevice;
      // m_rectangleTarget.right() = ktxTexture->baseWidth;
      // m_rectangleTarget.bottom() = ktxTexture->baseHeight;
      // m_mipLevels = ktxTexture->numLevels;
      //
      // ktx_uint8_t *ktxTextureData = ktxTexture_GetData(ktxTexture);
      // ktx_size_t ktxTextureSize = ktxTexture_GetDataSize(ktxTexture);
      //
      // // VkMemoryAllocateInfo memAllocInfo = vkinit::memoryAllocateInfo();
      // // VkMemoryRequirements memReqs;
      // //
      // // // Create a host-visible staging buffer that contains the raw image data
      // // VkBuffer stagingBuffer;
      // // VkDeviceMemory stagingMemory;
      // //
      // // VkBufferCreateInfo bufferCreateInfo = vkinit::bufferCreateInfo();
      // // bufferCreateInfo.size = ktxTextureSize;
      // // // This buffer is used as a transfer source for the buffer copy
      // // bufferCreateInfo.usage = VK_BUFFER_USAGE_TRANSFER_SRC_BIT;
      // // bufferCreateInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
      // //
      // // VK_CHECK_RESULT(vkCreateBuffer(pcontext->logicalDevice(), &bufferCreateInfo, nullptr, &stagingBuffer));
      // //
      // // // Get memory requirements for the staging buffer (alignment, memory type bits)
      // // vkGetBufferMemoryRequirements(pcontext->logicalDevice(), stagingBuffer, &memReqs);
      // //
      // // memAllocInfo.allocationSize = memReqs.size;
      // // // Get memory type index for a host visible buffer
      // // memAllocInfo.memoryTypeIndex = pphysicaldevice->findMemoryType(
      // //    memReqs.memoryTypeBits, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
      // //
      // // VK_CHECK_RESULT(vkAllocateMemory(pcontext->logicalDevice(), &memAllocInfo, nullptr, &stagingMemory));
      // // VK_CHECK_RESULT(vkBindBufferMemory(pcontext->logicalDevice(), stagingBuffer, stagingMemory, 0));
      // //
      // // // Copy texture data into staging buffer
      // // uint8_t *data;
      // // VK_CHECK_RESULT(vkMapMemory(pcontext->logicalDevice(), stagingMemory, 0, memReqs.size, 0, (void **)&data));
      // // memcpy(data, ktxTextureData, ktxTextureSize);
      // // vkUnmapMemory(pcontext->logicalDevice(), stagingMemory);
      //
      // // Setup buffer copy regions for each face including all of its mip levels
      // ::array_base<VkBufferImageCopy> bufferCopyRegions;
      //
      // for (uint32_t face = 0; face < 6; face++)
      // {
      //    for (uint32_t level = 0; level < m_mipLevels; level++)
      //    {
      //       ktx_size_t offset;
      //       KTX_error_code result = ktxTexture_GetImageOffset(ktxTexture, level, 0, face, &offset);
      //       ASSERT(result == KTX_SUCCESS);
      //
      //       VkBufferImageCopy bufferCopyRegion = {};
      //       bufferCopyRegion.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
      //       bufferCopyRegion.imageSubresource.mipLevel = level;
      //       bufferCopyRegion.imageSubresource.baseArrayLayer = face;
      //       bufferCopyRegion.imageSubresource.layerCount = 1;
      //       bufferCopyRegion.imageExtent.width = ktxTexture->baseWidth >> level;
      //       bufferCopyRegion.imageExtent.height = ktxTexture->baseHeight >> level;
      //       bufferCopyRegion.imageExtent.depth = 1;
      //       bufferCopyRegion.bufferOffset = offset & ~0xF;
      //
      //       bufferCopyRegions.add(bufferCopyRegion);
      //    }
      // }
      //
      // // Create optimal tiled target image
      // VkImageCreateInfo imageCreateInfo = vkinit::imageCreateInfo();
      // imageCreateInfo.imageType = VK_IMAGE_TYPE_2D;
      // imageCreateInfo.format = format;
      // imageCreateInfo.mipLevels = m_mipLevels;
      // imageCreateInfo.samples = VK_SAMPLE_COUNT_1_BIT;
      // imageCreateInfo.tiling = VK_IMAGE_TILING_OPTIMAL;
      // imageCreateInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
      // imageCreateInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
      // imageCreateInfo.extent =
      // {
      //    (uint32_t) m_rectangleTarget.width(),
      //    (uint32_t) m_rectangleTarget.height(),
      //    1
      // };
      // imageCreateInfo.usage = imageUsageFlags;
      // // Ensure that the TRANSFER_DST bit is set for staging
      // if (!(imageCreateInfo.usage & VK_IMAGE_USAGE_TRANSFER_DST_BIT))
      // {
      //    imageCreateInfo.usage |= VK_IMAGE_USAGE_TRANSFER_DST_BIT;
      // }
      // // Cube faces count as array layers in Vulkan
      // imageCreateInfo.arrayLayers = 6;
      // // This flag is required for cube map images
      // imageCreateInfo.flags = VK_IMAGE_CREATE_CUBE_COMPATIBLE_BIT;
      //
      //
      // VK_CHECK_RESULT(vkCreateImage(pcontext->logicalDevice(), &imageCreateInfo, nullptr, &m_vkimage));
      //
      // vkGetImageMemoryRequirements(pcontext->logicalDevice(), m_vkimage, &memReqs);
      //
      // memAllocInfo.allocationSize = memReqs.size;
      // memAllocInfo.memoryTypeIndex =
      //    pphysicaldevice->findMemoryType(memReqs.memoryTypeBits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
      //
      // VK_CHECK_RESULT(vkAllocateMemory(pcontext->logicalDevice(), &memAllocInfo, nullptr, &m_vkdevicememory));
      // VK_CHECK_RESULT(vkBindImageMemory(pcontext->logicalDevice(), m_vkimage, m_vkdevicememory, 0));
      //
      // // Use a separate command buffer for texture loading
      // //VkCommandBuffer pcommandbufferCopy->m_vkcommandbuffer =
      // pdevice->createCommandBuffer(VK_COMMAND_BUFFER_LEVEL_PRIMARY, true);
      //
      // auto pgpucommandbufferCopy = pcontext->beginSingleTimeCommands(pcontext->transfer_queue());
      //
      // ::cast<command_buffer> pcommandbufferCopy = pgpucommandbufferCopy;
      //
      // // Image barrier for optimal image (target)
      // // Set initial layout for all array layers (faces) of the optimal (target) tiled texture
      // VkImageSubresourceRange subresourceRange = {};
      // subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
      // subresourceRange.baseMipLevel = 0;
      // subresourceRange.levelCount = m_mipLevels;
      // subresourceRange.layerCount = 6;
      //
      // vulkan::setImageLayout(pcommandbufferCopy->m_vkcommandbuffer, m_vkimage, VK_IMAGE_LAYOUT_UNDEFINED,
      // VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
      //                       subresourceRange);
      //
      // // Copy the cube map faces from the staging buffer to the optimal tiled image
      // vkCmdCopyBufferToImage(pcommandbufferCopy->m_vkcommandbuffer, stagingBuffer, m_vkimage,
      // VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
      //                        static_cast<uint32_t>(bufferCopyRegions.size()), bufferCopyRegions.data());
      //
      // // Change texture image layout to shader read after all faces have been copied
      // m_state.m_vkimagelayout = imageLayout;
      // vulkan::setImageLayout(pcommandbufferCopy->m_vkcommandbuffer, m_vkimage, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
      // imageLayout, subresourceRange);
      //
      // //pdevice->flushCommandBuffer(pcommandbufferCopy->m_vkcommandbuffer, copyQueue);
      //
      // pcontext->endSingleTimeCommands(pcommandbufferCopy);
      //
      // // Create sampler
      // VkSamplerCreateInfo samplerCreateInfo = vkinit::samplerCreateInfo();
      // samplerCreateInfo.magFilter = VK_FILTER_LINEAR;
      // samplerCreateInfo.minFilter = VK_FILTER_LINEAR;
      // samplerCreateInfo.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;
      // samplerCreateInfo.addressModeU = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
      // samplerCreateInfo.addressModeV = samplerCreateInfo.addressModeU;
      // samplerCreateInfo.addressModeW = samplerCreateInfo.addressModeU;
      // samplerCreateInfo.mipLodBias = 0.0f;
      // samplerCreateInfo.maxAnisotropy =
      //    pphysicaldevice->m_vkphysicaldevicefeatures.samplerAnisotropy ?
      //    pphysicaldevice->m_vkphysicaldeviceproperties.limits.maxSamplerAnisotropy
      //                                      : 1.0f;
      // samplerCreateInfo.anisotropyEnable =
      //    pphysicaldevice->m_vkphysicaldevicefeatures.samplerAnisotropy ? VK_TRUE : VK_FALSE;
      // samplerCreateInfo.compareOp = VK_COMPARE_OP_NEVER;
      // samplerCreateInfo.minLod = 0.0f;
      // samplerCreateInfo.maxLod = (float)m_mipLevels;
      // samplerCreateInfo.borderColor = VK_BORDER_COLOR_FLOAT_OPAQUE_WHITE;
      // VK_CHECK_RESULT(vkCreateSampler(pcontext->logicalDevice(), &samplerCreateInfo, nullptr,
      // &m_vksamplerDedicated));
      //
      // // Create image view
      // VkImageViewCreateInfo viewCreateInfo = vkinit::imageViewCreateInfo();
      // viewCreateInfo.viewType = VK_IMAGE_VIEW_TYPE_CUBE;
      // viewCreateInfo.format = format;
      // viewCreateInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
      // viewCreateInfo.subresourceRange.baseMipLevel = 0;
      // viewCreateInfo.subresourceRange.levelCount = m_mipLevels;
      // viewCreateInfo.subresourceRange.baseArrayLayer = 0;
      // viewCreateInfo.subresourceRange.layerCount = 6;
      // viewCreateInfo.image = m_vkimage;
      // VK_CHECK_RESULT(vkCreateImageView(pcontext->logicalDevice(), &viewCreateInfo, nullptr, &m_vkimageview));
      //
      // // Clean up staging resources
      // ktxTexture_Destroy(ktxTexture);
      // vkDestroyBuffer(pcontext->logicalDevice(), stagingBuffer, nullptr);
      // vkFreeMemory(pcontext->logicalDevice(), stagingMemory, nullptr);
      //
      // // Update descriptor image info member that can be used for setting up descriptor sets
      // UpdateDescriptor();
   }


} // namespace gpu_opengl
