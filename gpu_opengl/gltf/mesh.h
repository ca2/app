// From github:/tristancalderbank/OpenGL-PBR-Renderer/gltf_mesh.h by
// camilo on 2025-09-26 18:28 <3ThomasBorregaardSorensen!!
#pragma once


#include "gpu/gltf/mesh.h"

// #include "bred/gpu/context_object.h"
// #include "bred/graphics3d/renderable.h"


// #include <assimp/Importer.hpp>
// #include <assimp/postprocess.h>
// #include <assimp/scene.h>
// 
// //#include <string>
// //#include <vector>
//
// #include "gpu/gltf/material.h"
// #include "gpu/gltf/mesh.h"
// #include "bred/gpu/shader.h"


namespace gpu_opengl
{


   namespace gltf
   {
      /**
       * A gltf_mesh is a collection of geometry paired with a material.
       */
      class mesh :
         virtual public ::gpu::gltf::mesh
      {
      public:

         // OpenGL data structures
         unsigned int m_uVAO, m_uVBO, m_uEBO;

         //array_base<gltf::vertex> m_vertexa;
         // unsigned_int_array m_indexa;
         // ::pointer<gltf_material> m_pmaterial;
         //

         mesh();
         ~mesh() override;


         //void initialize_gpu_gltf_mesh(const ::array_base<::gpu::gltf::vertex> &vertexa,
         //                          const ::unsigned_int_array &indexa, ::gpu::gltf::material *pmaterial) override;


         void init() override;

         void draw(::gpu::command_buffer *pcommandbuffer) override;
         // private:
         //    // OpenGL data structures
         //    unsigned int mVAO, mVBO, mEBO;
      };


   } // namespace gltf


} // namespace gpu_opengl
