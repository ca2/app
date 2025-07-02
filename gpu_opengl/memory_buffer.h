// Created by camilo on 2025-06-11 00:50 <3ThomasBorregaardSørensen!!
#pragma once


#include "bred/gpu/memory_buffer.h"


namespace gpu_opengl
{


   class CLASS_DECL_GPU_OPENGL memory_buffer :
      virtual public ::gpu::memory_buffer
   {
   public:



      GLuint m_gluVbo;
      GLsizei m_iType;
      //::gpu_vulkan::context * m_pcontext;
      //VkDeviceMemory m_vkdevicememory;
      //VkBuffer m_vkbuffer;
      //memsize m_size;
      //void* m_pMap;


      memory_buffer();
      ~memory_buffer();


      void initialize_memory_buffer(::gpu::context* pcontext, memsize size, bool bIndices) override;


      bool is_initialized() const override;

      //   VkBufferCreateInfo bufferInfo = {
      //      .sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
      //      .size = sizeof(graphics::RectangleVertex) * 6,
      //      .usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
      //      .sharingMode = VK_SHARING_MODE_EXCLUSIVE
      //   };
      //   vkCreateBuffer(device, &bufferInfo, NULL, &vertexBuffer);

      //   VkMemoryRequirements memReq;
      //   vkGetBufferMemoryRequirements(device, vertexBuffer, &memReq);

      //   uint32_t memTypeIndex = 0;
      //   VkPhysicalDeviceMemoryProperties memProps;
      //   vkGetPhysicalDeviceMemoryProperties(physicalDevice, &memProps);
      //   for (uint32_t i = 0; i < memProps.memoryTypeCount; i++) {
      //      if ((memReq.memoryTypeBits & (1 << i)) &&
      //         (memProps.memoryTypes[i].propertyFlags & VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT) &&
      //         (memProps.memoryTypes[i].propertyFlags & VK_MEMORY_PROPERTY_HOST_COHERENT_BIT)) {
      //         memTypeIndex = i;
      //         break;
      //      }
      //   }

      //   //VkBufferCreateInfo bufferInfo = {
      //   //    .sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
      //   //    .size = sizeof(quadVertices),
      //   //    .usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
      //   //    .sharingMode = VK_SHARING_MODE_EXCLUSIVE
      //   //};
      //   //vkCreateBuffer(device, &bufferInfo, NULL, &vertexBuffer);


      //   VkMemoryAllocateInfo allocInfo = {
      //       .sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
      //       .allocationSize = memReq.size,
      //       .memoryTypeIndex = memTypeIndex
      //   };
      //   vkAllocateMemory(device, &allocInfo, NULL, outMemory);
      //   vkBindBufferMemory(device, vertexBuffer, *outMemory, 0);

      //   //void* data;
      //   //vkMapMemory(device, *outMemory, 0, bufferInfo.size, 0, &data);
      //   //memcpy(data, quadVertices, sizeof(quadVertices));
      //   //vkUnmapMemory(device, *outMemory);

      //   return vertexBuffer;
      //}

      //virtual void assign(const void* pData, memsize size);
      //virtual void assign(const ::block & block);


      void * _map(memsize start, memsize count) override;
      void _unmap() override;


      void bind() override;
      void unbind() override;


   };




} // namespace gpu_opengl



