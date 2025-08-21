#include "framework.h"
// obj_model.cpp
#include "object_model.h"
//#include "app-graphics3d/gpu_vulkan/_gpu_vulkan.h"


// External
#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>

#include "bred/gpu/model_buffer.h"


//namespace std
//{
    //template <>
    //struct hash<::sandbox_renderer::object_model::Vertex> {
    //    size_t operator()(::sandbox_renderer::object_model::Vertex const& vertex) const
    //    {
    //        size_t seed = 0;
    //        tools::hashCombine(seed, vertex.position, vertex.color, vertex.normal, vertex.uv);
    //        return seed;
    //    }
    //};
//}

namespace sandbox_renderer
{

   // object_model::object_model(device * pdevice, const Builder& builder)
   //    : m_pgpudevice{ pdevice }, m_bIsSkyboxModel{ builder.isSkybox } {
   //
   //    if (builder.isSkybox) {
   //       //createVertexBuffers(builder.skyboxVertices);
   //    }
   //    else {
   //       createVertexBuffers(builder.vertexes);
   //       createIndexBuffers(builder.indexes);
   //    }
   //
   //
   // }
   object_model::object_model()
   {

      // if (builder.isSkybox) {
      //    //createVertexBuffers(builder.skyboxVertices);
      // }
      // else {
      //    createVertexBuffers(builder.vertexes);
      //    createIndexBuffers(builder.indexes);
      // }
      //

   }

   object_model::~object_model() {}


   // ::pointer<object_model> object_model::createModelFromFile(
   //    ::sandbox_renderer::device * pdevice, const ::scoped_string& filepath, bool isSkybox)
   // {
   //    Builder builder{};
   //    builder.loadModel(filepath, isSkybox);
   //    return øcreate_pointer<object_model>(pdevice, builder);
   // }
   //


   void object_model::createVertexBuffers(const ::array_base<Vertex>& vertexes)
   {

      øconstruct(m_pmodelbuffer);

      m_pmodelbuffer->static_initialize_vertexes(vertexes);

      // m_vertexCount = static_cast<uint32_t>(vertexes.size());
      // ASSERT(m_vertexCount >= 3 && "Vertex count must be at least 3");
      // VkDeviceSize bufferSize = sizeof(vertexes[0]) * m_vertexCount;
      // uint32_t vertexSize = sizeof(vertexes[0]);
      //
      // sandbox_buffer stagingBuffer{
      //     m_pgpudevice,
      //     vertexSize,
      //     m_vertexCount,
      //     VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
      //     VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
      // };
      //
      // stagingBuffer.map();
      // stagingBuffer.writeToBuffer((void*)vertexes.data());
      //
      // m_vertexBuffer = øcreate_pointer<sandbox_buffer>(
      //    m_pgpudevice,
      //    vertexSize,
      //    m_vertexCount,
      //    VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT,
      //    VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT
      // );
      //
      // m_pgpudevice->copyBuffer(stagingBuffer.getBuffer(), m_vertexBuffer->getBuffer(), bufferSize);
   }

   void object_model::createIndexBuffers(const ::array_base<uint32_t>& indexes)
   {

      øconstruct(m_pmodelbuffer);

      m_pmodelbuffer->static_initialize_indexes(indexes);

      // m_indexCount = static_cast<uint32_t>(indexes.size());
      // m_bHasIndexBuffer = m_indexCount > 0;
      // if (!m_bHasIndexBuffer) return;
      //
      // VkDeviceSize bufferSize = sizeof(indexes[0]) * m_indexCount;
      // uint32_t indexSize = sizeof(indexes[0]);
      //
      // sandbox_buffer stagingBuffer{
      //     m_pgpudevice,
      //     indexSize,
      //     m_indexCount,
      //     VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
      //     VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
      // };
      //
      // stagingBuffer.map();
      // stagingBuffer.writeToBuffer((void*)indexes.data());
      //
      // m_indexBuffer = øcreate_pointer<sandbox_buffer>(
      //    m_pgpudevice,
      //    indexSize,
      //    m_indexCount,
      //    VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT,
      //    VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
      //
      // m_pgpudevice->copyBuffer(stagingBuffer.getBuffer(), m_indexBuffer->getBuffer(), bufferSize);
   }

   void object_model::draw(::gpu::command_buffer * pcommandbuffer)
   {

      //VkCommandBuffer cmd = commandBuffer;

      m_pmodelbuffer->draw(pcommandbuffer);

      //if (m_bHasIndexBuffer) {
        // vkCmdDrawIndexed(cmd, m_indexCount, 1, 0, 0, 0);
      //}
      //else {
        // vkCmdDraw(cmd, m_vertexCount, 1, 0, 0);
      //}
   }


   void object_model::bind(::gpu::command_buffer * pcommandbuffer)
   {

      m_pmodelbuffer->bind(pcommandbuffer);

      // VkCommandBuffer cmd = commandBuffer;
      //
      // VkBuffer buffers[] = { m_vertexBuffer->getBuffer() };
      // VkDeviceSize offsets[] = { 0 };
      // vkCmdBindVertexBuffers(cmd, 0, 1, buffers, offsets);
      //
      // if (m_bHasIndexBuffer) {
      //    vkCmdBindIndexBuffer(cmd, m_indexBuffer->getBuffer(), 0, VK_INDEX_TYPE_UINT32);
      // }
   }

   //
   //
   // ::array_base<VkVertexInputBindingDescription> object_model::Vertex::getBindingDescriptions()
   // {
   //    return {
   //        VkVertexInputBindingDescription{
   //            0, sizeof(Vertex), VK_VERTEX_INPUT_RATE_VERTEX
   //        }
   //    };
   // }
   //
   // ::array_base<VkVertexInputAttributeDescription> object_model::Vertex::getAttributeDescriptions()
   // {
   //    return {
   //        { 0, 0, VK_FORMAT_R32G32B32_SFLOAT, offsetof(Vertex, position) },
   //        { 1, 0, VK_FORMAT_R32G32B32_SFLOAT, offsetof(Vertex, color) },
   //        { 2, 0, VK_FORMAT_R32G32B32_SFLOAT, offsetof(Vertex, normal) }
   //        //{ 3, 0, VK_FORMAT_R32G32_SFLOAT,    offsetof(Vertex, uv) }
   //    };
   // }


   void object_model::Builder::loadModel(const ::file::path & path, bool isSkybox) {
      this->isSkybox = isSkybox;
      vertexes.clear();
      //skyboxVertices.clear();
      indexes.clear();

      // 1) Check extension
      ::string ext = path.final_extension();
      if (ext.is_empty()) 
      {
         throw std::runtime_error("Model file has no extension: " + path);
      }
      
      ext.make_lower();

      if (ext == "obj") {
         // tinyobj loader ---
         tinyobj::attrib_t attrib;
         ::std::vector<tinyobj::shape_t>    shapes;
         ::std::vector<tinyobj::material_t> materials;
         ::std::string warn, err;

         if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, path.c_str())) {
            throw std::runtime_error("Failed to load OBJ: " + warn + err);
         }


         else {
            ::map_base<Vertex, uint32_t> uniqueVertices{};
            for (auto const& shape : shapes) {
               for (auto const& index : shape.mesh.indices) {
                  Vertex vertex{};
                  // copy position, color, normal, uv exactly as before
                  if (index.vertex_index >= 0) {
                     vertex.position = {
                         attrib.vertices[3 * index.vertex_index + 0],
                         attrib.vertices[3 * index.vertex_index + 1],
                         attrib.vertices[3 * index.vertex_index + 2],
                     };
                  }
                  if (!attrib.colors.empty()) {
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
                         1.0f - attrib.texcoords[2 * index.texcoord_index + 1],
                     };
                  }

                  if (uniqueVertices.count(vertex) == 0) {
                     uniqueVertices[vertex] = static_cast<uint32_t>(vertexes.size());
                     vertexes.add(vertex);
                  }
                  indexes.add(uniqueVertices[vertex]);
               }
            }
         }
         return;
      }
      else {
         throw std::runtime_error("Unsupported model format: " + ext);
      }
   }



} // namespace sandbox_renderer



