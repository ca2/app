// From V0idsEmbrace@Twich continuum project
// by camilo on 2025-05-17 02:40 <3ThomasBorregaardSorensen!!
#pragma once


//#include "device.h"
//#include "buffer.h"
#include "bred/gpu/model_buffer.h"
#include "bred/graphics3d/utilities.h"
#include "bred/graphics3d/types.h"



#define GLM_FORCE_RADIANS	
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <functional>

//#include <memory>
//#include <vector>
//#include <unordered_map>
//


namespace graphics3d
{


   class CLASS_DECL_BRED model :
      virtual public ::gpu::model_buffer
   {
   public:


      

      struct Builder
      {
         ::array<::graphics3d::Vertex> vertices{};
         ::array<uint32_t> indices{};

      };

      struct tinyobjloader_Builder :
         public Builder
      {

         void loadModel(::gpu::context* pgpucontext, const ::file::path & path);

      };


      ::pointer < ::gpu::renderer >        m_pgpurenderer;
      bool m_bDummy = false;
      //int m_iVertices = 0;
      ::pointer < ::gpu::command_buffer > m_pcommandbufferLoading;

      //static ::pointer<model> createModelFromFile(::graphics3d::context * pgpucontext, const ::file::path & path);


      model();
      ~model();


      virtual void initialize_model(::gpu::renderer * prenderer, const model::Builder& builder);
      virtual void initialize_dummy_model(::gpu::renderer* prenderer, int iVertices);

      //virtual void draw(::gpu::context* pgpucontext);
      //virtual void bind(::gpu::context* pgpucontext);
      //virtual void unbind(::gpu::context* pgpucontext);
      virtual void draw();
      virtual void bind();
      virtual void unbind();

   //private:
   //   void createVertexBuffers(const ::array<Vertex>& vertices);
   //   void createIndexBuffers(const ::array<uint32_t>& indices);

   //   bool hasIndexBuffer = false;
   //   ::pointer < context > m_pgpucontext;


   //   ::pointer<buffer> vertexBuffer;
   //   uint32_t vertexCount;

   //   ::pointer<buffer> indexBuffer;
   //   uint32_t indexCount;

   };


}  // namespace graphics3d





//namespace std {
//   template <>
//   struct hash<::gpu::Vertex>
//   {




//   };
//
//}  // namespace std
//

