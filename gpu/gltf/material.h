// From github:/tristancalderbank/OpenGL-PBR-Renderer/gltf_material.h by
// camilo on 2025-09-26 18:28 <3ThomasBorregaardSorensen!!
#pragma once

// #include <memory>

/// #include "constants.h"
// #include "texture.h"
#include "gpu/gltf/_constant.h"
#include "aura/message/user.h"
#include <glm/glm.hpp>

namespace gpu
{


   namespace gltf
   {


      class CLASS_DECL_GPU material : virtual public ::message::particle
      {

      public:

         bool useTextureAlbedo = false;
         bool useTextureMetallicRoughness = false;
         bool useTextureNormal = false;
         bool useTextureAmbientOcclusion = false;
         bool useTextureEmissive = false;

         glm::vec3 m_seq3Albedo = ::gpu::gltf::colorRed;
         float m_fMetallic = 1.0f;
         float m_fRoughness = 0.0f;
         float m_fAmbientOcclusion = 1.0f;
         glm::vec3 m_seq3Emissive = glm::vec3(0.0, 0.0, 0.0);

         ::pointer<::gpu::texture> m_ptextureAlbedo;
         ::pointer<::gpu::texture> m_ptextureMetallicRoughness;
         ::pointer<::gpu::texture> m_ptextureNormal;
         ::pointer<::gpu::texture> m_ptextureAmbientOcclusion;
         ::pointer<::gpu::texture> m_ptextureEmissive;
      };

   } // namespace gltf


} // namespace gpu
