// From gpu_vulkan/memory_buffer.cpp by
// camilo on 2025-07-01 12:38 <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "context.h"
#include "device.h"
#include "memory_buffer.h"
//#include "physical_device.h"


namespace gpu
{


   memory_buffer::memory_buffer()
   {
      m_pcontext = nullptr;
      //m_vkbuffer = VK_NULL_HANDLE;
      //m_vkdevicememory = VK_NULL_HANDLE;
      m_pMap = nullptr;
   }


   memory_buffer::~memory_buffer()
   {
      //if (m_vkbuffer != VK_NULL_HANDLE)
      //{
      //   vkDestroyBuffer(m_pcontext->logicalDevice(), m_vkbuffer, nullptr);
      //   m_vkbuffer = VK_NULL_HANDLE;
      //}
      //if (m_vkdevicememory != VK_NULL_HANDLE)
      //{
      //   vkFreeMemory(m_pcontext->logicalDevice(), m_vkdevicememory, nullptr);
      //   m_vkdevicememory = VK_NULL_HANDLE;
      //}
   }


   void memory_buffer::initialize_memory_buffer(::gpu::context* pcontext, memsize size, bool bIndices)
   {

      m_pcontext = pcontext;

      m_size = size;

      //VkBuffer vertexBuffer;


      // //  0 l,t
      ////  1 r,t
      ////  2 r,b
      // //  3 l,b

      // ::geometry2d::matrix m;
      // m.scale(2.0 / size.cx(), 2.0 / size.cy());
      // m.translate(-1.0, -1.0);

      // ::double_point points[4];

      // points[0] = points1[0]; // top-left
      // points[1] = points1[1]; // top-right
      // points[2] = points1[2]; // bottom-right
      // points[3] = points1[3]; // bottom-left

      // m.transform(points[0]);
      // m.transform(points[1]);
      // m.transform(points[2]);
      // m.transform(points[3]);

      // float fA = color.f32_opacity();
      // //float fR = color.f32_red();
      // //float fG = color.f32_green();
      // //float fB = color.f32_blue();
      // float fR = color.f32_red() * fA;
      // float fG = color.f32_green() * fA;
      // float fB = color.f32_blue() * fA;


      // graphics::RectangleVertex quadVertices[] = {
      //    // Triangle 1
      //    {{(float)points[0].x(), (float)points[0].y(), g_z}, {fR, fG, fB, fA}}, // Red
      //    {{(float)points[1].x(), (float)points[1].y(), g_z}, {fR, fG, fB, fA}}, // Green
      //    {{(float)points[2].x(), (float)points[2].y(), g_z}, {fR, fG, fB, fA}}, // Blue
      //    // Triangle 2
      //    {{(float)points[0].x(), (float)points[0].y(), g_z}, {fR, fG, fB, fA}}, // Green
      //    {{(float)points[2].x(), (float)points[2].y(), g_z}, {fR, fG, fB, fA}}, // Yellow
      //    {{(float)points[3].x(), (float)points[3].y(), g_z}, {fR, fG, fB, fA}}, // Blue
      // };



      //VkBufferCreateInfo bufferInfo = {
      //   .sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
      //   .size = (uint64_t)size,
      //   .usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
      //   .sharingMode = VK_SHARING_MODE_EXCLUSIVE
      //};
      //vkCreateBuffer(pcontext->logicalDevice(), &bufferInfo, NULL, &m_vkbuffer);

      //VkMemoryRequirements memReq{};
      //vkGetBufferMemoryRequirements(pcontext->logicalDevice(), m_vkbuffer, &memReq);

      //::cast < device > pdevice = pcontext->m_pgpudevice;

      //auto pphysicaldevice = pdevice->m_pphysicaldevice;

      //uint32_t memTypeIndex = 0;
      //VkPhysicalDeviceMemoryProperties memProps;
      //vkGetPhysicalDeviceMemoryProperties(pphysicaldevice->m_physicaldevice, &memProps);

      //for (uint32_t i = 0; i < memProps.memoryTypeCount; i++)
      //{
      //   if ((memReq.memoryTypeBits & (1 << i)) &&
      //      (memProps.memoryTypes[i].propertyFlags & VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT) &&
      //      (memProps.memoryTypes[i].propertyFlags & VK_MEMORY_PROPERTY_HOST_COHERENT_BIT)) {
      //      memTypeIndex = i;
      //      break;
      //   }
      //}

      ////VkBufferCreateInfo bufferInfo = {
      ////    .sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
      ////    .size = sizeof(quadVertices),
      ////    .usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
      ////    .sharingMode = VK_SHARING_MODE_EXCLUSIVE
      ////};
      ////vkCreateBuffer(device, &bufferInfo, NULL, &vertexBuffer);


      //VkMemoryAllocateInfo allocInfo = {
      //    .sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
      //    .allocationSize = memReq.size,
      //    .memoryTypeIndex = memTypeIndex
      //};
      //vkAllocateMemory(pcontext->logicalDevice(), &allocInfo, NULL, &m_vkdevicememory);
      //vkBindBufferMemory(pcontext->logicalDevice(), m_vkbuffer, m_vkdevicememory, 0);

      ////void* data;
      ////vkMapMemory(device, *outMemory, 0, bufferInfo.size, 0, &data);
      ////memcpy(data, quadVertices, sizeof(quadVertices));
      ////vkUnmapMemory(device, *outMemory);

   }


   bool memory_buffer::is_initialized() const
   {

      return false;

   }


   void memory_buffer::assign(const void* pData, memsize size)
   {

      if (!is_initialized())
      {

         throw ::exception(error_wrong_state, "Buffer not initialized");

      }

      //void* data;

      map(0, size);

      //vkMapMemory(m_pcontext->logicalDevice(), m_vkdevicememory, 0, size, 0, &data);

      memcpy(m_pMap, pData, size);

      unmap();

      //vkUnmapMemory(m_pcontext->logicalDevice(), m_vkdevicememory);

   }


   void memory_buffer::assign(const ::block& block)
   {

      assign(block.data(), block.size());

   }


   void memory_buffer::_assign(const void* pData, memsize size)
   {

      if (!is_initialized())
      {

         throw ::exception(error_wrong_state, "Buffer not initialized");

      }

      //void* data;

      _map(0, size);

      //vkMapMemory(m_pcontext->logicalDevice(), m_vkdevicememory, 0, size, 0, &data);

      memcpy(m_pMap, pData, size);

      _unmap();

      //vkUnmapMemory(m_pcontext->logicalDevice(), m_vkdevicememory);

   }


   void memory_buffer::_assign(const ::block& block)
   {

      _assign(block.data(), block.size());

   }


   void* memory_buffer::map()
   {

      return map(0, m_size);

   }


   void* memory_buffer::map(memsize start, memsize count)
   {

      if (!count)
      {

         throw ::exception(error_wrong_state);

      }

      bind();

      if (!m_pMap)
      {

         _map(start, count);

         //vkMapMemory(
         //   m_pcontext->logicalDevice(),
         //   m_vkdevicememory,
         //   start,
         //   count > 0 ? count : (m_size + count + 1),
         //   0,
         //   &m_pMap);

      }

      return m_pMap;

   }


   void memory_buffer::unmap()
   {

      if (!m_pMap)
      {

         return;

      }

      _unmap();

      unbind();

      m_pMap = nullptr;

   }


   void* memory_buffer::_map(memsize start, memsize count)
   {

      return __map(start, count);

   }


   void memory_buffer::_unmap()
   {

      return __unmap();

   }


   void* memory_buffer::__map(memsize start, memsize count)
   {

      return nullptr;

   }


   void memory_buffer::__unmap()
   {


   }


   void memory_buffer::bind()
   {


   }


   void memory_buffer::unbind()
   {


   }



} // namespace gpu_vulkan



