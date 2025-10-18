// From github:/tristancalderbank/OpenGL-PBR-Renderer/vertex.h by
// camilo on 2025-09-26 18:35 <3ThomasBorregaardSorensen!!
#pragma once


#include "bred/gpu/properties.h"


namespace gpu
{


   namespace gltf
   {


      /**
       * gltf::vertex attributes.
       */
      struct vertex
      {
         glm::vec3 position;
         glm::vec3 normal;
         glm::vec2 uv;
         glm::vec4 color;
         glm::vec4 tangent; 
         //glm::vec4 bitangent; 
         // w = bitangent sign
         // glm::vec3 mTangent;
         // glm::vec3 mBitangent;
      };


   } // namespace gltf


} // namespace gpu


DECLARE_GPU_PROPERTIES(CLASS_DECL_BRED, ::gpu::gltf::vertex);



