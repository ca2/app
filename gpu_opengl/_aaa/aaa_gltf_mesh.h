// From tristancalderbank/OpenGL-PBR-Renderer/mesh.h by
// camilo on 2025-09-26 18:28 <3ThomasBorregaardSorensen!!
#pragma once


#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

//#include <string>
//#include <vector>

#include "gpu/gpu/gltf_material.h"
#include "bred/gpu/shader.h"
#include "gpu/gpu/gltf_vertex.h"


namespace gpu_opengl
{


   /**
    * A mesh is a collection of geometry paired with a material.
    */
   class Mesh :
      virtual public ::particle
   {
   public:
      Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, Material material);
      void Draw(Shader &shader);

   public:
      std::vector<Vertex> mVertices;
      std::vector<unsigned int> mIndices;
      Material mMaterial;

   private:
      void init();

   private:
      // OpenGL data structures
      unsigned int mVAO, mVBO, mEBO;
   };


} // namespace gpu_opengl



