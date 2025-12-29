// Created by camilo on 2025-12-13 19:47 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "material.h"
#include "bred/gpu/binding.h"
#include "bred/gpu/context.h"
#include "gpu/model/model.h"


namespace gpu
{


   namespace model
   {


      material::material() {}


      material::~material() {}


      ::gpu::binding_slot_set *material::pbr_binding_slot_set(::gpu::binding_set *pbindingset,
                                                              ::graphics3d::renderable * prenderable)
      {

         if (pbindingset->size() == 2)
         {

            if (!m_pbindingslotsetSceneGltfPbr)
            {

               // ASSERT(::is_set(texture_albedo()));
               // ASSERT(::is_set(m_ptextureNormal));

               øconstruct(m_pbindingslotsetSceneGltfPbr);

               auto pbindingset = m_pgpucontext->scene_gltf_pbr_binding_set();

               m_pbindingslotsetSceneGltfPbr->initialize_binding_slot_set(pbindingset);

               ::cast<::gpu::empty_texture_source> pemptytexturesource = prenderable;

               m_pbindingslotsetSceneGltfPbr->set_texture(m_textureaPbr, pemptytexturesource);
               // auto pbindingslot0 = m_pbindingslotsetSceneGltfPbr->binding_slot(0);
               // pbindingslot0->m_ptexture = m_ptextureAlbedo;

               // auto pbindingslot1 = m_pbindingslotsetSceneGltfPbr->binding_slot(1);
               // pbindingslot1->m_ptexture = m_ptextureNormal;
            }
            return m_pbindingslotsetSceneGltfPbr;

         }
         else if (pbindingset->size() == 5)
         {

            if (!m_pbindingslotsetGltfPbr)
            {

               // ASSERT(::is_set(m_ptextureAlbedo));
               // ASSERT(::is_set(m_ptextureNormal));
               // ASSERT(::is_set(m_ptextureMetallicRoughness));
               // ASSERT(::is_set(m_ptextureAmbientOcclusion));
               // ASSERT(::is_set(m_ptextureEmissive));

               øconstruct(m_pbindingslotsetGltfPbr);

               //m_pbindingslotsetGltfPbr->m_pbindingset = m_pgpucontext->gltf_pbr_binding_set();

               auto pbindingset = m_pgpucontext->gltf_pbr_binding_set();

               m_pbindingslotsetGltfPbr->initialize_binding_slot_set(pbindingset);

               ::cast<::gpu::empty_texture_source> pemptytexturesource = prenderable;

               m_pbindingslotsetGltfPbr->set_texture(m_textureaPbr, pemptytexturesource);
               // auto pbindingslot0 = m_pbindingslotsetGltfPbr->binding_slot(0);
               // pbindingslot0->m_ptexture = m_ptextureAlbedo;

               // auto pbindingslot1 = m_pbindingslotsetGltfPbr->binding_slot(1);
               // pbindingslot1->m_ptexture = m_ptextureNormal;

               // auto pbindingslot2 = m_pbindingslotsetGltfPbr->binding_slot(2);
               // pbindingslot2->m_ptexture = m_ptextureMetallicRoughness;

               // auto pbindingslot3 = m_pbindingslotsetGltfPbr->binding_slot(3);
               // pbindingslot3->m_ptexture = m_ptextureAmbientOcclusion;

               // auto pbindingslot4 = m_pbindingslotsetGltfPbr->binding_slot(4);
               // pbindingslot4->m_ptexture = m_ptextureEmissive;
            }

            return m_pbindingslotsetGltfPbr;
         }
         else
         {

            throw ::exception(error_wrong_state, "No supported number of bindings");

            return nullptr;
         }


         // if (!m_pbindingslotsetIbl1)
         //{

         //   ASSERT(::is_set(m_ptextureAlbedo));
         //   ASSERT(::is_set(m_ptextureMetallicRoughness));
         //   ASSERT(::is_set(m_ptextureNormal));
         //   ASSERT(::is_set(m_ptextureAmbientOcclusion));
         //   ASSERT(::is_set(m_ptextureEmissive));
         //
         //   øconstruct(m_ptextureAlbedo);

         //   m_pbindingslotsetIbl1->m_pbindingset = m_pgpucontext->ibl1_binding_set();

         //   auto pbindingslot0 = m_pbindingslotsetIbl1->binding_slot(0);
         //   pbindingslot0->m_ptexture = m_ptextureIrradianceCube;

         //   auto pbindingslot1 = m_pbindingslotsetIbl1->binding_slot(1);
         //   pbindingslot1->m_ptexture = m_ptexturePrefilteredCube;

         //   auto pbindingslot2 = m_pbindingslotsetIbl1->binding_slot(2);
         //   pbindingslot2->m_ptexture = m_ptextureLuBrdf;
         //}

         // return m_pbindingslotsetIbl1;
      }


      ::gpu::texture *material::loaded_texture(enum_texture etexture)
      {
         ASSERT(etexture >= 0 && etexture < e_texture_count);
         return m_textureaPbr[etexture];
      }


      ::gpu::texture *material::texture(enum_texture etexture, ::gpu::empty_texture_source *pemptytexturesource)
      {
         ASSERT(etexture >= 0 && etexture < e_texture_count);
         auto ptexture = loaded_texture(etexture);
         if (::is_set(ptexture))
         {
            return ptexture;
         }
         auto ptextureEmpty = pemptytexturesource->empty_texture();
         // m_textureaLoaded[etexture];
         return ptextureEmpty;
      }


   } // namespace model


} // namespace gpu



