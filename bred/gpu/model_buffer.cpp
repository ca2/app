// Created by camilo on 2025-06-11 01:08 <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "command_buffer.h"
#include "context.h"
#include "frame.h"
#include "input_layout.h"
#include "memory_buffer.h"
#include "model_buffer.h"
#include "render_target.h"
#include "renderer.h"
#include "acme/prototype/geometry2d/matrix.h"
#include "acme/prototype/prototype/call.h"
#include "bred/gpu/types.h"
#include "bred/graphics3d/types.h"


namespace gpu
{


   model_buffer::model_buffer()
   {

      m_iVertexTypeSize = -1;

      m_iIndexTypeSize = -1;

      m_ppool = nullptr;

      m_bDummy = false;

      m_pMap = nullptr;

      m_iVertexCount = 0;

      m_iIndexCount = 0;

   }


   model_buffer::~model_buffer()
   {


   }


   void model_buffer::sequence2_uv_create_rectangle(::gpu::context* pcontext, bool bIndexed, bool bYSwap)
   {

      initialize_gpu_context_object(pcontext);

      float y0;
      float y1;

      if (bYSwap)
      {

         y0 = 1.0f;
         y1 = -1.0f;


      }
      else
      {

         y0 = -1.0f;
         y1 = 1.0f;

      }


      // Fullscreen quad vertex data
      ::array<::graphics3d::sequence2_uv> quadVertex = {
         // pos         // uv
         {{ -1.0f, y0}, { 0.0f, 0.0f}},
         {{  1.0f, y0}, { 1.0f, 0.0f}},
         {{  1.0f, y1}, { 1.0f, 1.0f}},
         {{ -1.0f, y1}, { 0.0f, 1.0f}},
      };

      static_initialize_vertexes(quadVertex);

//      set_vertex_array < ::graphics3d::sequence2_uv>(quadVertex, 4);

      if (bIndexed)
      {

         ::array<uint16_t> quadIndex = {
            0, 1, 2,
            2, 3, 0
         };

         static_initialize_indexes(quadIndex);

//         set_index_array<uint16_t >(quadIndex, 6);

      }


   }


   bool model_buffer::is_dummy() const
   {

      return m_iIndexCount <= 0 && m_iVertexCount <= 0;

   }


   void model_buffer::sequence2_uv_create_fullscreen_quad(::gpu::frame* pgpuframe)
   {

      initialize_gpu_context_object(pgpuframe->m_pgpucommandbuffer->m_pgpurendertarget->m_pgpurenderer->m_pgpucontext);

      // Vertex data: (x, y, u, v)
#if 1
      ::array< ::graphics3d::sequence2_uv > quadvertexes = {
         //  Position   TexCoords
         {{ -1.0f,  1.0f},{  0.0f, 1.0f}}, // Top-left
         {{-1.0f, -1.0f}, { 0.0f, 0.0f}}, // Bottom-left
          {{1.0f, -1.0f}, { 1.0f, 0.0f}}, // Bottom-right

         {{-1.0f,  1.0f}, { 0.0f, 1.0f}}, // Top-left
          {{1.0f, -1.0f}, { 1.0f, 0.0f}}, // Bottom-right
          {{1.0f,  1.0f}, { 1.0f, 1.0f}}  // Top-right
      };
#else
      ::array < ::graphics3d::sequence2_uv >quadvertexes = {
         //  Position   TexCoords
         {{ 0.0f,  1.0f}, { 0.0f, 1.0f}}, // Top-left
         {{0.0f, 0.0f}, { 0.0f, 0.0f}}, // Bottom-left
          {{1.0f, 0.0f}, { 1.0f, 0.0f}}, // Bottom-right

         {{0.0f,  1.0f}, { 0.0f, 1.0f}}, // Top-left
          {{1.0f, 0.0f}, { 1.0f, 0.0f}}, // Bottom-right
          {{1.0f,  1.0f},{  1.0f, 1.0f}}  // Top-right
      };
#endif

      this->bind(pgpuframe->m_pgpucommandbuffer);


      this->static_initialize_vertexes<::graphics3d::sequence2_uv >(
         quadvertexes);

      this->unbind(pgpuframe->m_pgpucommandbuffer);



      //this->set_vertex_array<::graphics3d::sequence2_uv >(quadvertexes, 6);


   }


   void model_buffer::sequence2_color_create_rectangle(::gpu::frame* pgpuframe)
   {

      initialize_gpu_context_object(pgpuframe->gpu_context());

      auto pcommandbuffer = pgpuframe->m_pgpucommandbuffer;

      bind(pcommandbuffer);

      this->create_vertexes<::graphics3d::sequence2_color >(6);

      unbind(pcommandbuffer);

      //defer_set_input_layout(pcontext->input_layout(::gpu_properties<::graphics3d::sequence2_color>()));

   }


   void model_buffer::sequence2_color_create_line(::gpu::frame * pgpuframe)
   {

      initialize_gpu_context_object(pgpuframe->gpu_context());

      auto pcommandbuffer = pgpuframe->m_pgpucommandbuffer;

      bind(pcommandbuffer);

      this->create_vertexes<::graphics3d::sequence2_color >(
         2);

      unbind(pcommandbuffer);

      //defer_set_input_layout(pcontext->input_layout(::gpu_properties < ::graphics::sequence2_color>()));

   }


   void model_buffer::sequence3_color_create_rectangle(::gpu::frame* pgpuframe)
   {

      initialize_gpu_context_object(pgpuframe->gpu_context());

      auto pcommandbuffer = pgpuframe->m_pgpucommandbuffer;

      bind(pcommandbuffer);

      this->create_vertexes<::graphics3d::sequence3_color >(
         6);

      unbind(pcommandbuffer);

      //defer_set_input_layout(pcontext->input_layout(::graphics3d::sequence3_color_properties()));

   }


   void model_buffer::sequence3_color_create_line(::gpu::frame* pgpuframe)
   {

      initialize_gpu_context_object(pgpuframe->gpu_context());

      auto pcommandbuffer = pgpuframe->m_pgpucommandbuffer;

      bind(pcommandbuffer);

      this->create_vertexes<::graphics3d::sequence3_color >(
         2);

      unbind(pcommandbuffer);

      ///defer_set_input_layout(pcontext->input_layout(::graphics3d::sequence3_color_properties()));

   }


   void model_buffer::sequence3_color_set_rectangle(
      const ::double_point points1[4],
      const  ::color::color& color,
      const ::double_size& size)
   {


   //   //void editQuadVertexBuffer(
   //   //   VkDevice device,
   //   //   VkDeviceMemory outMemory,
   //   //   const ::double_point points1[4],
   //   //   const  ::color::color & color,
   //   //   const ::double_size & size)
   //   //{
   //   //   VkBuffer vertexBuffer;


   //      //  0 l,t
   //     //  1 r,t
   //     //  2 r,b
   //      //  3 l,b

   //   ::geometry2d::matrix m;
   //   m.scale(2.0 / size.cx(), 2.0 / size.cy());
   //   m.translate(-1.0, -1.0);

   //   ::double_point points[4];

   //   points[0] = points1[0]; // top-left
   //   points[1] = points1[1]; // top-right
   //   points[2] = points1[2]; // bottom-right
   //   points[3] = points1[3]; // bottom-left

   //   m.transform(points[0]);
   //   m.transform(points[1]);
   //   m.transform(points[2]);
   //   m.transform(points[3]);

   //   float fA = color.f32_opacity();
   //   //float fR = color.f32_red();
   //   //float fG = color.f32_green();
   //   //float fB = color.f32_blue();
   //   float fR = color.f32_red() * fA;
   //   float fG = color.f32_green() * fA;
   //   float fB = color.f32_blue() * fA;

   //   float g_z = 0.0f; // Assuming z is 0 for 2D rendering, adjust as needed

   //   auto data = this->map_base < graphics3d::sequence3_color > ();

   //   //   // Triangle 1
   //   data[0] = { {points[0].x(), points[0].y(), g_z}, {fR, fG, fB, fA} };
   //   data[1] = { {points[1].x(), points[1].y(), g_z}, {fR, fG, fB, fA} };
   //   data[2] = { {points[2].x(), points[2].y(), g_z}, {fR, fG, fB, fA} };
   //   //   // Triangle 2
   //   data[3] = { {points[1].x(), points[1].y(), g_z}, {fR, fG, fB, fA} };
   //   data[4] = { {points[2].x(), points[2].y(), g_z}, {fR, fG, fB, fA} };
   //   data[5] = { {points[3].x(), points[3].y(), g_z}, {fR, fG, fB, fA} };

   //   //graphics3d::sequence3_color quadvertexes[] = {
   //   //   // Triangle 1
   //   //   {{(float)points[0].x(), (float)points[0].y(), g_z}, {fR, fG, fB, fA}}, // Red
   //   //   {{(float)points[1].x(), (float)points[1].y(), g_z}, {fR, fG, fB, fA}}, // Green
   //   //   {{(float)points[2].x(), (float)points[2].y(), g_z}, {fR, fG, fB, fA}}, // Blue
   //   //   // Triangle 2
   //   //   {{(float)points[0].x(), (float)points[0].y(), g_z}, {fR, fG, fB, fA}}, // Green
   //   //   {{(float)points[2].x(), (float)points[2].y(), g_z}, {fR, fG, fB, fA}}, // Yellow
   //   //   {{(float)points[3].x(), (float)points[3].y(), g_z}, {fR, fG, fB, fA}}, // Blue
   //   //};

   //   //m_pbufferVertex->assign(::as_memory_block(quadvertexes));

   }

   
   void model_buffer::sequence2_color_set_rectangle(
      const ::double_point points1[4],
      const  ::color::color& color,
      const ::double_size& size)
   {


      //void editQuadVertexBuffer(
      //   VkDevice device,
      //   VkDeviceMemory outMemory,
      //   const ::double_point points1[4],
      //   const  ::color::color & color,
      //   const ::double_size & size)
      //{
      //   VkBuffer vertexBuffer;


         //  0 l,t
        //  1 r,t
        //  2 r,b
         //  3 l,b

      ::geometry2d::matrix m;
      m.scale(2.0 / size.cx(), 2.0 / size.cy());
      m.translate(-1.0, -1.0);

      ::double_point points[4];

      points[0] = points1[0]; // top-left
      points[1] = points1[1]; // top-right
      points[2] = points1[2]; // bottom-right
      points[3] = points1[3]; // bottom-left

      m.transform(points[0]);
      m.transform(points[1]);
      m.transform(points[2]);
      m.transform(points[3]);

      float fA = color.f32_opacity();
      //float fR = color.f32_red();
      //float fG = color.f32_green();
      //float fB = color.f32_blue();
      float fR = color.f32_red() * fA;
      float fG = color.f32_green() * fA;
      float fB = color.f32_blue() * fA;

      float g_z = 0.0f; // Assuming z is 0 for 2D rendering, adjust as needed

      ::array<::graphics3d::sequence2_color> quadvertexes = {
         // Triangle 1
         {{(float)points[0].x(), (float)points[0].y()}, {fR, fG, fB, fA}}, // Red
         {{(float)points[1].x(), (float)points[1].y()}, {fR, fG, fB, fA}}, // Green
         {{(float)points[2].x(), (float)points[2].y()}, {fR, fG, fB, fA}}, // Blue
         // Triangle 2
         {{(float)points[0].x(), (float)points[0].y()}, {fR, fG, fB, fA}}, // Green
         {{(float)points[2].x(), (float)points[2].y()}, {fR, fG, fB, fA}}, // Yellow
         {{(float)points[3].x(), (float)points[3].y()}, {fR, fG, fB, fA}}, // Blue
      };

      this->set_vertexes(quadvertexes);

      //m_pbufferVertex->assign(::as_memory_block(quadvertexes));

   }


   void model_buffer::sequence2_color_set_rectangle(
      const ::double_point * pointa,
      const  ::color::color& color)
   {


         //  0 l,t
        //  1 r,t
        //  2 r,b
         //  3 l,b


      float fA = color.f32_opacity();
      //float fR = color.f32_red();
      //float fG = color.f32_green();
      //float fB = color.f32_blue();
      float fR = color.f32_red() * fA;
      float fG = color.f32_green() * fA;
      float fB = color.f32_blue() * fA;

      float g_z = 0.0f; // Assuming z is 0 for 2D rendering, adjust as needed

      ::array<::graphics3d::sequence2_color> quadvertexes = {
         // Triangle 1
         {{(float)pointa[0].x(), (float)pointa[0].y()}, {fR, fG, fB, fA}}, // Red
         {{(float)pointa[1].x(), (float)pointa[1].y()}, {fR, fG, fB, fA}}, // Green
         {{(float)pointa[2].x(), (float)pointa[2].y()}, {fR, fG, fB, fA}}, // Blue
         // Triangle 2
         {{(float)pointa[0].x(), (float)pointa[0].y()}, {fR, fG, fB, fA}}, // Green
         {{(float)pointa[2].x(), (float)pointa[2].y()}, {fR, fG, fB, fA}}, // Yellow
         {{(float)pointa[3].x(), (float)pointa[3].y()}, {fR, fG, fB, fA}}, // Blue
      };

      this->set_vertexes(quadvertexes);

      //m_pbufferVertex->assign(::as_memory_block(quadvertexes));

   }

   
   //
   void model_buffer::sequence3_color_set_line(
      const ::double_point& pointA,
      const ::double_point& pointB,
      const  ::color::color& color,
      const ::double_size& size)
   {
//      VkBuffer vertexBuffer;




      //static const graphics::RectangleVertex quadvertexes[] = {
      //   // Triangle 1
      //   {{-0.5f, -0.5f}, {1.0f, 0.0f, 0.0f, 0.5f}}, // Red
      //   {{ 0.5f, -0.5f}, {0.0f, 1.0f, 0.0f, 0.5f}}, // Green
      //   {{-0.5f,  0.5f}, {0.0f, 0.0f, 1.0f, 0.5f}}, // Blue
      //   // Triangle 2
      //   {{ 0.5f, -0.5f}, {0.0f, 1.0f, 0.0f, 0.5f}}, // Green
      //   {{ 0.5f,  0.5f}, {1.0f, 1.0f, 0.0f, 0.5f}}, // Yellow
      //   {{-0.5f,  0.5f}, {0.0f, 0.0f, 1.0f, 0.5f}}, // Blue
      //};

      float fA = color.f32_opacity();
      ////float fR = color.f32_red();
      ////float fG = color.f32_green();
      ////float fB = color.f32_blue();
      float fR = color.f32_red() * fA;
      float fG = color.f32_green() * fA;
      float fB = color.f32_blue() * fA;


      //rectangle is x0 y0 w100 h100;
      // size(100, 100) l = (0 - 100 / 2) / 100 = -0.5
      // size(100, 100) r = (100 - 100 / 2) / 100 = 0.5

      //float l = (float)(2. * (rectangle.left() - size.cx()/2.)/ (size.cx()));
      //float r = (float)(2. * (rectangle.right() - size.cx()/2.) / (size.cx()));
      //float t = (float)(2. * (rectangle.bottom() - size.cy()/2.) / (size.cy()));
      //float b = (float)(2. * (rectangle.top() - size.cy()/2.) / (size.cy()));

      //  0 l,t
      //  1 r,t
      //  2 r,b
      //  3 l,b

      ::geometry2d::matrix m;
      m.scale(2.0 / size.cx(), 2.0 / size.cy());
      m.translate(-1.0, -1.0);

      ::double_point points[2];

      points[0] = pointA;
      points[1] = pointB;

      m.transform(points[0]);
      m.transform(points[1]);


      float g_z = 0.f;

      graphics3d::sequence3_color linevertexes[] = {
         {{(float)points[0].x(), (float)points[0].y(), g_z}, {fR, fG, fB, fA}},
         {{(float)points[1].x(), (float)points[1].y(), g_z}, {fR, fG, fB, fA}},
      };


      //graphics::RectangleVertex quadvertexes[] = {
      //   // Triangle 1
      //   {{l, t, g_z}, {fR, fG, fB, fA}}, // Red
      //   {{ r, t, g_z}, {fR, fG, fB, fA}}, // Green
      //   {{r,  b, g_z}, {fR, fG, fB, fA}}, // Blue
      //   // Triangle 2
      //   {{ l, t, g_z}, {fR, fG, fB, fA}}, // Green
      //   {{ r,  b, g_z}, {fR, fG, fB, fA}}, // Yellow
      //   {{l,  b, g_z}, {fR, fG, fB, fA}}, // Blue
      //};

      //auto pcontext = this->context();

      //VkBufferCreateInfo bufferInfo = {
      //   .sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
      //   .size = sizeof(linevertexes),
      //   .usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
      //   .sharingMode = VK_SHARING_MODE_EXCLUSIVE
      //};
      //vkCreateBuffer(pcontext->logicalDevice(), &bufferInfo, NULL, &m_);

      //VkMemoryRequirements memReq;
      //vkGetBufferMemoryRequirements(pcontext->logicalDevice(), vertexBuffer, &memReq);

      //uint32_t memTypeIndex = 0;
      //VkPhysicalDeviceMemoryProperties memProps;
      //vkGetPhysicalDeviceMemoryProperties(physicalDevice, &memProps);
      //for (uint32_t i = 0; i < memProps.memoryTypeCount; i++) {
      //   if ((memReq.memoryTypeBits & (1 << i)) &&
      //      (memProps.memoryTypes[i].propertyFlags & VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT) &&
      //      (memProps.memoryTypes[i].propertyFlags & VK_MEMORY_PROPERTY_HOST_COHERENT_BIT)) {
      //      memTypeIndex = i;
      //      break;
      //   }
      //}

      //VkMemoryAllocateInfo allocInfo = {
      //   .sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
      //   .allocationSize = memReq.size,
      //   .memoryTypeIndex = memTypeIndex
      //};
      //vkAllocateMemory(device, &allocInfo, NULL, outMemory);
      //vkBindBufferMemory(device, vertexBuffer, *outMemory, 0);

      //auto pcontext = this->context();

      auto data = map <::graphics3d::sequence3_color >();

      data.assign(as_memory_block(linevertexes));

      //vkMapMemory(pcontext->logicalDevice(), 
      //   m_pbufferVertex->m_vkdevicememory, 
      //   0,
      //   m_pbufferVertex->m_size,
      //   0,
      //   (void **)& data);


      //vkUnmapMemory(
      //   pcontext->logicalDevice(), 
      //   m_pbufferVertex->m_vkdevicememory);

      //return vertexBuffer;
   }



   void model_buffer::sequence2_color_set_line(
      const ::double_point& pointA,
      const ::double_point& pointB,
      const  ::color::color& color,
      const ::double_size& size)
   {
      //      VkBuffer vertexBuffer;




            //static const graphics::RectangleVertex quadvertexes[] = {
            //   // Triangle 1
            //   {{-0.5f, -0.5f}, {1.0f, 0.0f, 0.0f, 0.5f}}, // Red
            //   {{ 0.5f, -0.5f}, {0.0f, 1.0f, 0.0f, 0.5f}}, // Green
            //   {{-0.5f,  0.5f}, {0.0f, 0.0f, 1.0f, 0.5f}}, // Blue
            //   // Triangle 2
            //   {{ 0.5f, -0.5f}, {0.0f, 1.0f, 0.0f, 0.5f}}, // Green
            //   {{ 0.5f,  0.5f}, {1.0f, 1.0f, 0.0f, 0.5f}}, // Yellow
            //   {{-0.5f,  0.5f}, {0.0f, 0.0f, 1.0f, 0.5f}}, // Blue
            //};

      float fA = color.f32_opacity();
      ////float fR = color.f32_red();
      ////float fG = color.f32_green();
      ////float fB = color.f32_blue();
      float fR = color.f32_red() * fA;
      float fG = color.f32_green() * fA;
      float fB = color.f32_blue() * fA;


      //rectangle is x0 y0 w100 h100;
      // size(100, 100) l = (0 - 100 / 2) / 100 = -0.5
      // size(100, 100) r = (100 - 100 / 2) / 100 = 0.5

      //float l = (float)(2. * (rectangle.left() - size.cx()/2.)/ (size.cx()));
      //float r = (float)(2. * (rectangle.right() - size.cx()/2.) / (size.cx()));
      //float t = (float)(2. * (rectangle.bottom() - size.cy()/2.) / (size.cy()));
      //float b = (float)(2. * (rectangle.top() - size.cy()/2.) / (size.cy()));

      //  0 l,t
      //  1 r,t
      //  2 r,b
      //  3 l,b

      ::geometry2d::matrix m;
      m.scale(2.0 / size.cx(), 2.0 / size.cy());
      m.translate(-1.0, -1.0);

      ::double_point points[2];

      points[0] = pointA;
      points[1] = pointB;

      m.transform(points[0]);
      m.transform(points[1]);


      float g_z = 0.f;

      graphics3d::sequence2_color linevertexes[] = {
         {{(float)points[0].x(), (float)points[0].y()}, {fR, fG, fB, fA}},
         {{(float)points[1].x(), (float)points[1].y()}, {fR, fG, fB, fA}},
      };


      //graphics::RectangleVertex quadvertexes[] = {
      //   // Triangle 1
      //   {{l, t, g_z}, {fR, fG, fB, fA}}, // Red
      //   {{ r, t, g_z}, {fR, fG, fB, fA}}, // Green
      //   {{r,  b, g_z}, {fR, fG, fB, fA}}, // Blue
      //   // Triangle 2
      //   {{ l, t, g_z}, {fR, fG, fB, fA}}, // Green
      //   {{ r,  b, g_z}, {fR, fG, fB, fA}}, // Yellow
      //   {{l,  b, g_z}, {fR, fG, fB, fA}}, // Blue
      //};

      //auto pcontext = this->context();

      //VkBufferCreateInfo bufferInfo = {
      //   .sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
      //   .size = sizeof(linevertexes),
      //   .usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
      //   .sharingMode = VK_SHARING_MODE_EXCLUSIVE
      //};
      //vkCreateBuffer(pcontext->logicalDevice(), &bufferInfo, NULL, &m_);

      //VkMemoryRequirements memReq;
      //vkGetBufferMemoryRequirements(pcontext->logicalDevice(), vertexBuffer, &memReq);

      //uint32_t memTypeIndex = 0;
      //VkPhysicalDeviceMemoryProperties memProps;
      //vkGetPhysicalDeviceMemoryProperties(physicalDevice, &memProps);
      //for (uint32_t i = 0; i < memProps.memoryTypeCount; i++) {
      //   if ((memReq.memoryTypeBits & (1 << i)) &&
      //      (memProps.memoryTypes[i].propertyFlags & VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT) &&
      //      (memProps.memoryTypes[i].propertyFlags & VK_MEMORY_PROPERTY_HOST_COHERENT_BIT)) {
      //      memTypeIndex = i;
      //      break;
      //   }
      //}

      //VkMemoryAllocateInfo allocInfo = {
      //   .sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
      //   .allocationSize = memReq.size,
      //   .memoryTypeIndex = memTypeIndex
      //};
      //vkAllocateMemory(device, &allocInfo, NULL, outMemory);
      //vkBindBufferMemory(device, vertexBuffer, *outMemory, 0);

      //auto pcontext = this->context();

      auto data = map< ::graphics3d::sequence2_color>();

      data.assign(as_memory_block(linevertexes));

      //::graphics3d::sequence3_color* data;

      //vkMapMemory(pcontext->logicalDevice(),
      //   m_pbufferVertex->m_vkdevicememory,
      //   0,
      //   m_pbufferVertex->m_size,
      //   0,
      //   (void**)&data);


      //vkUnmapMemory(
      //   pcontext->logicalDevice(),
      //   m_pbufferVertex->m_vkdevicememory);

      //return vertexBuffer;
   }


   //void* model_buffer::_map(memsize start, memsize count)
   //{

   //   if (m_pMap)
   //   {

   //      return m_pMap;

   //   }

   //   auto pcontext = this->context();

   //   vkMapMemory(pcontext->logicalDevice(),
   //      m_pbufferVertex->m_vkdevicememory,
   //      0,
   //      m_pbufferVertex->m_size,
   //      0,
   //      (void**)&m_pMap);

   //   return m_pMap;

   //}


   //void model_buffer::unmap()
   //{

   //   auto pcontext = this->context();

   //   vkUnmapMemory(
   //      pcontext->logicalDevice(),
   //      m_pbufferVertex->m_vkdevicememory);

   //}


   void model_buffer::bind(::gpu::command_buffer* pgpucommandbuffer)
   {

      //if (m_pbufferVertex)
      //{

      //   ::cast < command_buffer > pcommandbuffer = pgpucommandbuffer;

      //   VkDeviceSize offsets[] = { 0 };

      //   ::cast < memory_buffer > pbufferVertex = m_pbufferVertex;

      //   vkCmdBindVertexBuffers(
      //      pcommandbuffer->m_vkcommandbuffer,
      //      0, 1,
      //      &pbufferVertex->m_vkbuffer, offsets);

      //   if (m_pbufferIndex)
      //   {

      //      ::cast < memory_buffer > pbufferIndex = m_pbufferIndex;

      //      vkCmdBindIndexBuffer(
      //         pcommandbuffer->m_vkcommandbuffer,
      //         pbufferIndex->m_vkbuffer, 0, VK_INDEX_TYPE_UINT16);

      //   }

      //}

   }


   void model_buffer::draw(::gpu::command_buffer* pgpucommandbuffer)
   {

      //if (m_pbufferVertex)
      //{

      //   ::cast < command_buffer > pcommandbuffer = pgpucommandbuffer;

      //   if (m_pbufferIndex)
      //   {
      //      vkCmdDrawIndexed(
      //         pcommandbuffer->m_vkcommandbuffer,
      //         m_iIndexCount, 1, 0, 0, 0);
      //   }
      //   else
      //   {
      //      vkCmdDraw(
      //         pcommandbuffer->m_vkcommandbuffer,
      //         m_iVertexCount, 1, 0, 0);
      //   }
      //}
   }


   void model_buffer::draw_lines(::gpu::command_buffer* pgpucommandbuffer)
   {

      //if (m_pbufferVertex)
      //{

      //   ::cast < command_buffer > pcommandbuffer = pgpucommandbuffer;

      //   if (m_pbufferIndex)
      //   {
      //      vkCmdDrawIndexed(
      //         pcommandbuffer->m_vkcommandbuffer,
      //         m_iIndexCount, 1, 0, 0, 0);
      //   }
      //   else
      //   {
      //      vkCmdDraw(
      //         pcommandbuffer->m_vkcommandbuffer,
      //         m_iVertexCount, 1, 0, 0);
      //   }
      //}
   }


   void model_buffer::unbind(::gpu::command_buffer* pgpucommandbuffer)
   {

      //if (m_pbufferVertex)
      //{

      //   ::cast < command_buffer > pcommandbuffer = pgpucommandbuffer;

      //   VkDeviceSize offsets[] = { 0 };

      //   ::cast < memory_buffer > pbufferVertex = m_pbufferVertex;

      //   vkCmdBindVertexBuffers(
      //      pcommandbuffer->m_vkcommandbuffer,
      //      0, 1,
      //      &pbufferVertex->m_vkbuffer, offsets);

      //   if (m_pbufferIndex)
      //   {

      //      ::cast < memory_buffer > pbufferIndex = m_pbufferIndex;

      //      vkCmdBindIndexBuffer(
      //         pcommandbuffer->m_vkcommandbuffer,
      //         pbufferIndex->m_vkbuffer, 0, VK_INDEX_TYPE_UINT16);

      //   }

      //}

   }


   void model_buffer::set_input_layout(::gpu::input_layout* pinputlayout)
   {

      m_pinputlayout = pinputlayout;

      apply_input_layout();

   }


   void model_buffer::apply_input_layout()
   {

   }


   //void model_buffer::handle(const ::call& call)
   //{

   //   if (call == id_restore_on_top_frame_end)
   //   {

   //      m_paPool->add(this);

   //   }

   //}

   ::gpu::command_buffer* model_buffer::_defer_get_loading_command_buffer()
   {

      return nullptr;

   }


   void model_buffer::initialize_dummy_model(::gpu::context* pgpucontext, int iVertexCount)
   {

      initialize_gpu_context_object(pgpucontext);

      m_iVertexCount = iVertexCount;

      m_bDummy = true;

   }


   void model_buffer::static_initialize_vertex_buffer(const void* data, memsize iTypeSize, ::collection::count iVertexCount)
   {

      m_iVertexCount = (int) iVertexCount;

      m_iVertexTypeSize = (int) iTypeSize;

      auto size = iTypeSize * iVertexCount;

      ødefer_construct(m_pbufferVertex);

      m_pbufferVertex->static_initialize_memory_buffer_with_model_buffer(
         this,
         data,
         size,
         memory_buffer::e_type_vertex_buffer);

   }


   void model_buffer::static_initialize_index_buffer(const void* data, memsize iTypeSize, ::collection::count iIndexCount)
   {

      m_iIndexCount = (int) iIndexCount;

      m_iIndexTypeSize = (int) iTypeSize;

      auto size = iIndexCount * m_iIndexTypeSize;

      ødefer_construct(m_pbufferIndex);

      m_pbufferIndex->static_initialize_memory_buffer_with_model_buffer(
         this,
         data,
         size,
         memory_buffer::e_type_index_buffer);

   }


   void model_buffer::static_initialize_vertexes_block(const ::block& blockvertexes)
   {

      m_iVertexCount = -1;

      m_iVertexTypeSize = -1;

      m_iVertexByteSize = (int) blockvertexes.size();

      ødefer_construct(m_pbufferVertex);

      m_pbufferVertex->static_initialize_memory_buffer_with_model_buffer(
         this,
         blockvertexes.data(),
         blockvertexes.size(),
         memory_buffer::e_type_vertex_buffer);

      //defer_set_input_layout(m_pgpucontext->input_layout(::gpu_properties< VERTEX >()));

   }


   void model_buffer::static_initialize_indexes_block(const ::block& blockindexes)
   {

      m_iIndexCount = -1;

      m_iIndexTypeSize = -1;

      m_iIndexByteSize = (int)blockindexes.size();

      ødefer_construct(m_pbufferIndex);

      m_pbufferIndex->static_initialize_memory_buffer_with_model_buffer(
         this,
         blockindexes.data(),
         blockindexes.size(),
         memory_buffer::e_type_index_buffer);

   }



} // namespace gpu



