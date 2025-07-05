// Created by camilo on 2025-05-17 02:45s <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "model.h"
#include "utilities.h"
#include "acme/filesystem/filesystem/directory_context.h"
#include "acme/filesystem/filesystem/path_system.h"
#include "bred/gpu/context.h"
#include "bred/gpu/renderer.h"


#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>


#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/hash.hpp>


namespace graphics3d
{


   model::model()
   {


   }
   
   
   model::~model() 
   {


   }


   void model::initialize_model(::gpu::renderer* pgpurenderer, const model::Builder& builder)
   {

      initialize_gpu_context_object(pgpurenderer->m_pgpucontext);

      m_pgpurenderer = pgpurenderer;

   }


   void model::initialize_dummy_model(::gpu::renderer* pgpurenderer, int iVertices)
   {

      initialize_gpu_context_object(pgpurenderer->m_pgpucontext);

      m_pgpurenderer = pgpurenderer;
      m_bDummy = true;
      m_iVertexCount = iVertices;

   }


   void model::draw()
   {


   }



   void model::bind()
   {



   }


   void model::unbind()
   {



   }


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

      ::map<::graphics3d::Vertex, uint32_t> uniqueVertices{};

      for (const auto& shape : shapes) 
      {

         for (const auto& index : shape.mesh.indices) 
         {

            ::graphics3d::Vertex vertex{};

            if (index.vertex_index >= 0) 
            {

               vertex.position = 
               {
                   attrib.vertices[3 * index.vertex_index + 0],
                   attrib.vertices[3 * index.vertex_index + 1],
                   attrib.vertices[3 * index.vertex_index + 2],
               };

               vertex.color = 
               {
                  attrib.colors[3 * index.vertex_index + 0],
                  attrib.colors[3 * index.vertex_index + 1],
                  attrib.colors[3 * index.vertex_index + 2],
               };

            }

            if (index.normal_index >= 0) 
            {

               vertex.normal = 
               {
                   attrib.normals[3 * index.normal_index + 0],
                   attrib.normals[3 * index.normal_index + 1],
                   attrib.normals[3 * index.normal_index + 2],
               };
            }

            if (index.texcoord_index >= 0) 
            {

               vertex.uv = 
               {
                   attrib.texcoords[2 * index.texcoord_index + 0],
                   attrib.texcoords[2 * index.texcoord_index + 1],
               };
            }

            if (uniqueVertices.count(vertex) == 0) 
            {

               uniqueVertices[vertex] = static_cast<uint32_t>(vertices.size());
               vertices.add(vertex);

            }

            indices.add(uniqueVertices[vertex]);

         }

      }

   }


}  // namespace graphics3d



