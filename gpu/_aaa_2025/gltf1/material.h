// From github:/tristancalderbank/OpenGL-PBR-Renderer/gltf_material.h by
// camilo on 2025-09-26 18:28 <3ThomasBorregaardSorensen!!
#pragma once

// #include <memory>

/// #include "constants.h"
// #include "texture.h"
#include "gpu/gltf/_constant.h"
#include "aura/message/user.h"
#include "bred/gpu/context_object.h"
//


namespace gpu
{


   namespace gltf
   {


      enum enum_texture
      {

         e_texture_albedo,
         e_texture_normal,
         e_texture_metallic_roughness,
         e_texture_ambient_occlusion,
         e_texture_emissive,

         e_texture_count,

      };


      class CLASS_DECL_GPU material : 
         virtual public ::gpu::context_object
      {

      public:





         enum AlphaMode
         {
            ALPHAMODE_NONE,
            ALPHAMODE_OPAQUE,
            ALPHAMODE_MASK,
            ALPHAMODE_BLEND
         };
         AlphaMode alphaMode = ALPHAMODE_OPAQUE;
         float alphaCutoff = 1.0f;

         bool useTextureAlbedo = false;
         bool useTextureMetallicRoughness = false;
         bool useTextureNormal = false;
         bool useTextureAmbientOcclusion = false;
         bool useTextureEmissive = false;

         floating_sequence3 m_seq3Albedo = ::gpu::gltf::colorWhite;
         float m_fMetallic = 1.0f;
         float m_fRoughness = 0.0f;
         float m_fAmbientOcclusion = 1.0f;
         floating_sequence3 m_seq3Emissive = floating_sequence3(0.0, 0.0, 0.0);

         ::pointer<::gpu::texture> m_textureaPbr[e_texture_count];

         //::pointer<::gpu::texture> m_textureaCached[e_texture_count];
         //::pointer<::gpu::texture> m_ptextureCachedNormal;
         //::pointer<::gpu::texture> m_ptextureCachedMetallicRoughness;
         //::pointer<::gpu::texture> m_ptextureCachedAmbientOcclusion;
         //::pointer<::gpu::texture> m_ptextureCachedEmissive;

         ::pointer<::gpu::binding_slot_set> m_pbindingslotsetGltfPbr;
         ::pointer<::gpu::binding_slot_set> m_pbindingslotsetSceneGltfPbr;

       
         //::gpu::binding_set *pbindingset,
           //                                                    ::gpu::gltf::model *pmodel);


         material();
         ~material() override;

         virtual ::gpu::binding_slot_set *pbr_binding_slot_set(::gpu::binding_set *pbindingset,
                                                               ::gpu::gltf::model *pmodel);
         virtual ::gpu::texture *loaded_texture(enum_texture etexture);
         virtual ::gpu::texture *texture(enum_texture etexture, ::gpu::empty_texture_source *pemptytexturesource);
  

      };

   } // namespace gltf


} // namespace gpu
