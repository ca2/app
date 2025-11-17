// From github:/tristancalderbank/OpenGL-PBR-Renderer/gltf_mesh.h by
// camilo on 2025-09-26 18:28 <3ThomasBorregaardSorensen!!
#pragma once


#include "bred/gpu/context_object.h"
#include "bred/graphics3d/renderable.h"


#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
//
// #include <string>
// #include <vector>

#include "bred/gpu/shader.h"
#include "gpu/gltf/material.h"


namespace gpu
{


   namespace gltf
   {
      /**
       * A gltf_mesh is a collection of geometry paired with a material.
       */
      class CLASS_DECL_GPU mesh :
         virtual public context_object, 
         virtual public ::graphics3d::renderable
      {
      public:


         raw_array_base<::gpu::gltf::vertex> m_vertexa;
         unsigned_int_array m_indexa;
         ::pointer<::gpu::gltf::material> m_pmaterial;
         struct UniformBlock {
            floating_matrix4 matrix;
            floating_matrix4 jointMatrix[64]{};
            float jointcount{ 0 };
         } uniformBlock;


         mesh();
         ~mesh() override;


         virtual void initialize_gpu_gltf_mesh(const ::raw_array_base<gltf::vertex> &vertexa, const ::unsigned_int_array &indexa,
                                   ::gpu::gltf::material *pmaterial);

         virtual void init();


         void draw(::gpu::command_buffer *pcommandbuffer) override;

         // private:
         //    // OpenGL data structures
         //    unsigned int mVAO, mVBO, mEBO;
      };


   } // namespace gltf


} // namespace gpu
