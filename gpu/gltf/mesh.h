// From github:/tristancalderbank/OpenGL-PBR-Renderer/gltf_mesh.h by
// camilo on 2025-09-26 18:28 <3ThomasBorregaardSorensen!!
#pragma once


#include "bred/gpu/context_object.h"
#include "bred/graphics3d/renderable.h"


#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <glm/glm.hpp>
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
      class mesh : virtual public context_object, virtual public ::graphics3d::renderable
      {
      public:


         array_base<gltf::vertex> m_vertexa;
         unsigned_int_array m_indexa;
         ::pointer<gltf_material> m_pmaterial;

         gltf_mesh();
         ~gltf_mesh() override;


         void initialize_gltf_mesh(const ::array_base<gltf::vertex> &vertexa, const ::unsigned_int_array &indexa,
                                   gltf_material *pmaterial);

         virtual void init();

         // private:
         //    // OpenGL data structures
         //    unsigned int mVAO, mVBO, mEBO;
      };


   } // namespace gltf


} // namespace gpu
