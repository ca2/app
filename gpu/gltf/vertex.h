// From github:/tristancalderbank/OpenGL-PBR-Renderer/vertex.h by
// camilo on 2025-09-26 18:35 <3ThomasBorregaardSorensen!!
#pragma once


namespace gpu
{


   namespace gltf
   {


      /**
       * gltf::vertex attributes.
       */
      struct vertex
      {
         glm::vec3 mPosition;
         glm::vec3 mNormal;
         glm::vec2 mTextureCoordinates;
         glm::vec4 mColor;
         glm::vec4 mTangent; // w = bitangent sign
         //glm::vec3 mTangent;
         //glm::vec3 mBitangent;
      };


   } // namespace gltf


} // namespace gpu
