#pragma once
#include "device.h"
#include "bred/graphics3d/model.h"
//#include "buffer.h"
//#include "SceneFoundry/graphics3d/renderer_i.h"
#include "bred/gpu/types.h"
// libs
#define GLM_FORCE_RADIANS	
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/hash.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// std
//#include <memory>
//#include <vector>
//#include <unordered_map>
//#include <cassert>
//#include <cstring>
//#include <stdexcept>
//#include <unordered_map>
//#include <unordered_set>

namespace sandbox_renderer
{


   class CLASS_DECL_SANDBOX_RENDERER object_model :
      virtual public ::graphics3d::IModel
   {
   public:


      device * m_pgpudevice;
      bool m_bHasIndexBuffer{ false };
      bool m_bIsSkyboxModel{ false };

      //::pointer<sandbox_buffer> m_vertexBuffer;
      //uint32_t m_vertexCount;

      //::pointer<sandbox_buffer> m_indexBuffer;
      //uint32_t m_indexCount;

      ::pointer < ::gpu::model_buffer > m_pmodelbuffer;

      struct Vertex {
         glm::vec3 position{};
         glm::vec3 color{};
         glm::vec3 normal{};
         glm::vec2 uv{};

         //static ::array_base<VkVertexInputBindingDescription> getBindingDescriptions();
         //static ::array_base<VkVertexInputAttributeDescription> getAttributeDescriptions();

         bool operator==(Vertex const& o) const {
            return position == o.position &&
               normal == o.normal &&
               uv == o.uv;
         }
      };

      struct SkyboxVertex {
         glm::vec3 position;
         //static ::array_base<VkVertexInputBindingDescription>   getBindingDescriptions();
         //static ::array_base<VkVertexInputAttributeDescription> getAttributeDescriptions();
      };
      struct PrimitiveInfo {
         uint32_t      firstIndex;
         uint32_t      indexCount;
         int           textureIndex; // index into textures[]
         glm::mat4     modelMatrix;
      };
      struct Builder {
         ::array_base<Vertex> vertexes{};
         ::array_base<uint32_t> indexes{};

         void loadModel(const ::file::path & path, bool isSkybox);


         bool isSkybox{ false };

      };

      // static ::pointer<sandbox_object_model> createModelFromFile(
      //    ::sandbox_renderer::device * pdevice, const  ::scoped_string& filepath, bool isSkybox = false);

      object_model();
      ~object_model();


      virtual void initialize_object_model(device * pdevice, Builder const& builder);

      //sandbox_object_model(sandbox_object_model const&) = delete;
      //void operator=(sandbox_object_model const&) = delete;

      //void bind(VkCommandBuffer cmd)override;
      //void draw(VkCommandBuffer cmd)override;


      void bind(gpu::command_buffer* pcommandbuffer) override;
      void draw(gpu::command_buffer* pcommandbuffer) override;


      bool isSkybox() const { return m_bIsSkyboxModel; }
      void createVertexBuffers(::array_base<Vertex> const& vertexes);
      void createIndexBuffers(::array_base<uint32_t> const& indexes);

   };


} // namespace sandbox_renderer


template < >
inline ::hash32 as_hash32<::sandbox_renderer::object_model::Vertex>(const ::sandbox_renderer::object_model::Vertex& vertex)
{

   hash32 seed{};

   ::gpu::hash_combine(
      seed,
      vertex.position,
      vertex.color,
      vertex.normal,
      vertex.uv);

   return seed;

}
