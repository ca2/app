// From gpu_vulkan/memory_buffer.h by
// camilo on 2025-07-01 12:37 <3ThomasBorregaardSørensen!!
#pragma once


namespace gpu
{


   class CLASS_DECL_BRED memory_buffer :
      virtual public ::particle
   {
   public:


      ::gpu::context* m_pcontext;
      //VkDeviceMemory m_vkdevicememory;
      //VkBuffer m_vkbuffer;
      memsize m_size;
      void* m_pMap;


      memory_buffer();
      ~memory_buffer();


      virtual void initialize_memory_buffer(::gpu::context* pcontext, memsize size, bool bIndices);

      virtual bool is_initialized() const;
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

      virtual void assign(const void* pData, memsize size);
      virtual void assign(const ::block& block);
      virtual void _assign(const void* pData, memsize size);
      virtual void _assign(const ::block& block);

      virtual void* map();
      virtual void* map(memsize start, memsize count);
      virtual void unmap();
      virtual void* _map(memsize start, memsize count);
      virtual void _unmap();
      virtual void* __map(memsize start, memsize count);
      virtual void __unmap();


      virtual void bind();
      virtual void unbind();


   };


   template < typename MAPPER, typename TYPE >
   class memory_map
   {
   public:

      MAPPER* m_pMapper;
      TYPE* m_p;

      memory_map(MAPPER* pmapper, TYPE* p) :
         m_pMapper(pmapper)
      {

         m_p = (TYPE*)m_pMapper->map(0, -1);

      }

      ~memory_map()
      {

         m_pMapper->unmap();

      }

      operator TYPE* ()
      {

         return m_p;

      }


      TYPE* operator -> ()
      {

         return m_p;

      }

      template < primitive_integral INTEGRAL >
      TYPE& operator[](INTEGRAL i)
      {

         return m_p[i];

      }

      void assign(const ::block& block)
      {

         memcpy(m_p, block.data(), block.size());

      }


   };


} // namespace gpu


