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


//
//


namespace graphics3d
{



   void tinyobjloader_Builder::loadModel(::gpu::context *pgpucontext, const ::file::path &path)
   {

      loadModel_002(pgpucontext, path);
   }


   void tinyobjloader_Builder::loadModel_001(::gpu::context *pgpucontext, const ::file::path &path)
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

      m_vertexes.clear();

      m_indexes.clear();

      //::map_base<::graphics3d::Vertex, uint32_t> uniquevertexes{};

      for (const auto& shape : shapes)
      {

                 size_t index_offset = 0;
         for (size_t f = 0; f < shape.mesh.num_face_vertices.size(); f++)
         {
            size_t fv = shape.mesh.num_face_vertices[f]; // Number of vertices in this face

            for (size_t v = 0; v < fv; v++)
            {
               tinyobj::index_t idx = shape.mesh.indices[index_offset + v];

               Vertex vertex;
               vertex.position[0] = attrib.vertices[3 * idx.vertex_index + 0];
               vertex.position[1] = attrib.vertices[3 * idx.vertex_index + 1];
               vertex.position[2] = attrib.vertices[3 * idx.vertex_index + 2];
                        vertex.color =
                        {
                           attrib.colors[3 * idx.vertex_index + 0],
                           attrib.colors[3 * idx.vertex_index + 1],
                           attrib.colors[3 * idx.vertex_index + 2],
                        };


               if (idx.normal_index >= 0)
               {
                  vertex.normal[0] = attrib.normals[3 * idx.normal_index + 0];
                  vertex.normal[1] = attrib.normals[3 * idx.normal_index + 1];
                  vertex.normal[2] = attrib.normals[3 * idx.normal_index + 2];
               }

               if (idx.texcoord_index >= 0)
               {
                  vertex.uv[0] = attrib.texcoords[2 * idx.texcoord_index + 0];
                  vertex.uv[1] = attrib.texcoords[2 * idx.texcoord_index + 1];
               }
               m_vertexes.add(vertex);
               //m_indexes.add(static_cast<unsigned int>(m_indexes.size())); // Simple sequential indexing
            }
            index_offset += fv;
         }

      //   for (const auto& index : shape.mesh.indices)
      //   {

      //      ::graphics3d::Vertex vertex{};

      //      if (index.vertex_index >= 0)
      //      {

      //         vertex.position =
      //         {
      //             attrib.vertices[3 * index.vertex_index + 0],
      //             attrib.vertices[3 * index.vertex_index + 1],
      //             attrib.vertices[3 * index.vertex_index + 2],
      //         };

      //         vertex.color =
      //         {
      //            attrib.colors[3 * index.vertex_index + 0],
      //            attrib.colors[3 * index.vertex_index + 1],
      //            attrib.colors[3 * index.vertex_index + 2],
      //         };

      //      }

      //      if (index.normal_index >= 0)
      //      {

      //         vertex.normal =
      //         {
      //             attrib.normals[3 * index.normal_index + 0],
      //             attrib.normals[3 * index.normal_index + 1],
      //             attrib.normals[3 * index.normal_index + 2],
      //         };
      //      }

      //      if (index.texcoord_index >= 0)
      //      {

      //         vertex.uv =
      //         {
      //             attrib.texcoords[2 * index.texcoord_index + 0],
      //             attrib.texcoords[2 * index.texcoord_index + 1],
      //         };
      //      }

      //      //if (uniquevertexes.count(vertex) == 0)
      //      //{

      //        // uniquevertexes[vertex] = static_cast<uint32_t>(m_vertexes.size());
      //         m_vertexes.add(vertex);

      //      //}
      //      //else
      //      //{

      //        /// ::information("Duplicate vertex found");

      //      //}

      //      //m_indexes.add(uniquevertexes[vertex]);

      //   }

      }

   }



}  // namespace graphics3d



