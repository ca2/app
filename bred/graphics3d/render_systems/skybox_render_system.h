#pragma once


#include "bred/gpu/properties.h"
#include "bred/graphics3d/render_system.h"


namespace graphics3d
{


   class CLASS_DECL_BRED skybox_render_system : virtual public ::graphics3d::render_system
   {
   public:


      struct push_constants
      {

         // floating_matrix4 modelMatrix;
         // floating_matrix4 normalMatrix;

         // int useTextureAlbedo; // 0
         // int useTextureMetallicRoughness; // 4
         // int useTextureNormal; // 8
         // int useTextureAmbientOcclusion; // 12
         // int useTextureEmissive; // 16

         //// 20

         //::floating_sequence3 albedo; // 20
         // float metallic; // 32
         // float roughness; // 36
         // float ambientOcclusion; // 40
         //::floating_sequence3 emissive; // 44

         //// 36

         //// 56

         ////::floating_sequence3 cameraPosition;//56
         // float bloomBrightnessCutoff; // 68
         //// 72
         floating_sequence3 multiplier;
      };

      ::pointer<::graphics3d::renderable> m_prenderableCube;
      // VkDescriptorSetLayout m_skyboxLayout;
      ::pointer<::gpu::texture> m_pgputextureSkybox;
      bool m_bHasCubemap = false;
      ::pointer<::gpu::shader> m_pshaderHdr;
      ::pointer<::gpu::shader> m_pshaderNormal;



      skybox_render_system();
      ~skybox_render_system();

      virtual ::memory vertex_shader_memory();
      virtual ::memory fragment_shader_memory();
      virtual ::memory hdr_fragment_shader_memory();


      void on_prepare(gpu::context *pgpucontext) override;
      void on_render(::gpu::context *pgpucontext, ::graphics3d::scene_base *pscene) override;

      virtual void setCubemapTexture(::gpu::texture *pgputexture);

      void createSkyboxDescriptorSetLayout();
      void allocateAndWriteSkyboxDescriptorSet();


   };


} // namespace graphics3d


DECLARE_GPU_PROPERTIES(CLASS_DECL_BRED, ::graphics3d::skybox_render_system::push_constants)



