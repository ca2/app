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
         floating_sequence3 position;//0-12
         floating_sequence3 normal;//12-24
         floating_sequence2 uv;//24-32
         floating_sequence4 color;//32-48
         floating_sequence4 tangent;//48-64
         //floating_sequence4 bitangent; 
         // w = bitangent sign
         // floating_sequence3 mTangent;
         // floating_sequence3 mBitangent;
      };


   } // namespace gltf


} // namespace gpu


DECLARE_GPU_PROPERTIES(CLASS_DECL_BRED, ::gpu::gltf::vertex);



