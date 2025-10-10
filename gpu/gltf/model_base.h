// Created by camilo on 2025-10-10 <3ThomasBorregaardSorensen!!

#pragma once

#include <assimp/pbrmaterial.h>
// #include "stb_image/stb_image.h"

// #include <map>
#include "gpu/gltf/mesh.h"


namespace gpu
{


   namespace gltf
   {
      /**
       * A collection of meshes.
       */
      class CLASS_DECL_GPU model_base : virtual public context_object, virtual public ::graphics3d::renderable
      {
      public:
         ::pointer<material> m_pmaterialOverride;

         //bool m_bExternalPbr = false;
         ::string m_strDirectory;
         ::string_map<::pointer<::gpu::texture>> m_mapTexture;

         /**
          * Load a glTF 2.0 model.
          * @param path
          */
         model_base();


         ~model_base() override;

         ::gpu::texture *get_target_texture() override;


         //virtual void initialize_gpu_gltf_model(::gpu::context *pgpucontext, const ::gpu::renderable_t &model);


         //virtual void initialize_gpu_gltf_model(::gpu::context *pgpucontext, const ::file::path &path,
           //                                     bool flipTexturesVertically, bool bExternalPbr);


         /**
          * Load a glTF 2.0 model using a provided material. This will ignore any material
          * present in the model file.
          * @param path
          */
         /*virtual void initialize_gpu_gltf_model(::gpu::context *pgpucontext, const ::file::path &path,
                                                ::gpu::gltf::material *pmaterial, bool flipTexturesVertically,
                                                bool bExternalPbr);
*/


         //virtual void loadModel(const ::file::path &path, bool flipTexturesVertically, bool bExternalPbr);



         virtual ::gpu::texture *loadMaterialTexture(const ::scoped_string &scopedstr, aiTextureType type);

      };

   } // namespace gltf

} // namespace gpu
