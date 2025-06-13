// Created by camilo on 2025-05-17 02:45s <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "bred/gpu/context.h"
#include "model.h"
#include "utilities.h"
#include "acme/filesystem/filesystem/directory_context.h"
#include "acme/filesystem/filesystem/path_system.h"


// lib headers
#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>


#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/hash.hpp>

// std
#include <cassert>
#include <cstring>
#include <stdexcept>
#include <unordered_set>


namespace graphics3d
{


   model::model()
   {


   }
   
   
   model::~model() 
   {


   }


   void model::initialize_model(::gpu::context* pgpucontext, const model::Builder& builder)
   {

      m_pgpucontext = pgpucontext;
      // initialize(pvkcdevice);
      //createVertexBuffers(builder.vertices);
      //createIndexBuffers(builder.indices);
   }


   void model::draw(::gpu::context* pgpucontext)
   {


   }



   void model::bind(::gpu::context* pgpucontext)
   {



   }


   void model::unbind(::gpu::context* pgpucontext)
   {



   }


   //::pointer<model> model::createModelFromFile(::graphics::context* pgpucontext, const ::file::path & path)
   //{

   //   return {};
   //   //Builder builder{};
   //   //builder.loadModel(pvkcdevice, filepath);

   //   //__refdbg_this(pvkcdevice);

   //   //return __allocate model(pvkcdevice, builder);
   //}


   //void model::createVertexBuffers(const std::vector<Vertex>& vertices) {
   //   vertexCount = static_cast<uint32_t>(vertices.size());
   //   assert(vertexCount >= 3 && "Vertex count must be at least 3");
   //   VkDeviceSize bufferSize = sizeof(vertices[0]) * vertexCount;
   //   uint32_t vertexSize = sizeof(vertices[0]);

   //   buffer stagingBuffer;

   //   stagingBuffer.initialize_buffer(
   //      m_pgpudevice,
   //      vertexSize,
   //      vertexCount,
   //      VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
   //      VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT
   //   );

   //   stagingBuffer.map();
   //   stagingBuffer.writeToBuffer((void*)vertices.data());

   //   vertexBuffer = __allocate buffer;

   //   vertexBuffer->initialize_buffer(
   //      m_pgpudevice,
   //      vertexSize,
   //      vertexCount,
   //      VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT,
   //      VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT
   //   );


   //   m_pgpudevice->copyBuffer(stagingBuffer.getBuffer(), vertexBuffer->getBuffer(), bufferSize);


   //}

   //void model::createIndexBuffers(const std::vector<uint32_t>& indices) {
   //   indexCount = static_cast<uint32_t>(indices.size());
   //   hasIndexBuffer = indexCount > 0;

   //   if (!hasIndexBuffer) {
   //      return;
   //   }

   //   VkDeviceSize bufferSize = sizeof(indices[0]) * indexCount;
   //   uint32_t indexSize = sizeof(indices[0]);

   //   buffer stagingBuffer;
   //   stagingBuffer.initialize_buffer(
   //      m_pgpudevice,
   //      indexSize,
   //      indexCount,
   //      VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
   //      VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT)
   //      ;

   //   stagingBuffer.map();
   //   stagingBuffer.writeToBuffer((void*)indices.data());

   //   indexBuffer = __allocate buffer();

   //   indexBuffer->initialize_buffer(
   //      m_pgpudevice,
   //      indexSize,
   //      indexCount,
   //      VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT,
   //      VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);

   //   m_pgpudevice->copyBuffer(stagingBuffer.getBuffer(), indexBuffer->getBuffer(), bufferSize);
   //}


   //void model::draw(VkCommandBuffer commandBuffer) {
   //   if (hasIndexBuffer) {
   //      vkCmdDrawIndexed(commandBuffer, indexCount, 1, 0, 0, 0);
   //   }
   //   else {
   //      vkCmdDraw(commandBuffer, vertexCount, 1, 0, 0);
   //   }
   //}

   //void model::bind(VkCommandBuffer commandBuffer) {
   //   VkBuffer buffers[] = { vertexBuffer->getBuffer() };
   //   VkDeviceSize offsets[] = { 0 };
   //   vkCmdBindVertexBuffers(commandBuffer, 0, 1, buffers, offsets);

   //   if (hasIndexBuffer) {
   //      vkCmdBindIndexBuffer(commandBuffer, indexBuffer->getBuffer(), 0, VK_INDEX_TYPE_UINT32);
   //   }
   //}

//std::vector<VkVertexInputBindingDescription> model::Vertex::getBindingDescriptions() 
//{
//
//      std::vector<VkVertexInputBindingDescription> bindingDescriptions(1, VkVertexInputBindingDescription{});
//
//      bindingDescriptions[0].binding = 0;
//      bindingDescriptions[0].stride = sizeof(Vertex);
//      bindingDescriptions[0].inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
//      return bindingDescriptions;
//   }
//   std::vector<VkVertexInputAttributeDescription> model::Vertex::getAttributeDescriptions() {
//      std::vector<VkVertexInputAttributeDescription> attributeDescriptions{};
//
//      attributeDescriptions.add({ 0, 0, VK_FORMAT_R32G32B32_SFLOAT, offsetof(Vertex, position) });
//      attributeDescriptions.add({ 1, 0, VK_FORMAT_R32G32B32_SFLOAT, offsetof(Vertex, color) });
//      attributeDescriptions.add({ 2, 0, VK_FORMAT_R32G32B32_SFLOAT, offsetof(Vertex, normal) });
//      attributeDescriptions.add({ 3, 0, VK_FORMAT_R32G32_SFLOAT, offsetof(Vertex, uv) });
//
//      return attributeDescriptions;
//   }


   void model::tinyobjloader_Builder::loadModel(::gpu::context* pgpucontext, const ::file::path & path)
   {

      tinyobj::attrib_t attrib;
      std::vector<tinyobj::shape_t> shapes;
      std::vector<tinyobj::material_t> materials;
      std::string warn, err;

      auto pathFile = pgpucontext->directory()->defer_get_file_system_file(path.c_str(), true);

      ::string str(::system()->path_system()->shell_path(pathFile));

      if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, str.c_str())) 
      {
         
         throw std::runtime_error(warn + err);

      }

      vertices.clear();
      indices.clear();


      ::map<::gpu::Vertex, uint32_t> uniqueVertices{};
      for (const auto& shape : shapes) {
         for (const auto& index : shape.mesh.indices) {
            ::gpu::Vertex vertex{};

            if (index.vertex_index >= 0) {
               vertex.position = {
                   attrib.vertices[3 * index.vertex_index + 0],
                   attrib.vertices[3 * index.vertex_index + 1],
                   attrib.vertices[3 * index.vertex_index + 2],
               };

               vertex.color = {
               attrib.colors[3 * index.vertex_index + 0],
               attrib.colors[3 * index.vertex_index + 1],
               attrib.colors[3 * index.vertex_index + 2],
               };

            }

            if (index.normal_index >= 0) {
               vertex.normal = {
                   attrib.normals[3 * index.normal_index + 0],
                   attrib.normals[3 * index.normal_index + 1],
                   attrib.normals[3 * index.normal_index + 2],
               };
            }

            if (index.texcoord_index >= 0) {
               vertex.uv = {
                   attrib.texcoords[2 * index.texcoord_index + 0],
                   attrib.texcoords[2 * index.texcoord_index + 1],
               };
            }

            if (uniqueVertices.count(vertex) == 0) {
               uniqueVertices[vertex] = static_cast<uint32_t>(vertices.size());
               vertices.add(vertex);
            }

            indices.add(uniqueVertices[vertex]);

         }

      }

   }


}  // namespace graphics3d



