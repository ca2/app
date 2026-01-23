// Created by camilo on 2025-10-10 <3ThomasBorregaardSorensen!!

#pragma once

#include "gpu/model/mesh.h"
#include "bred/gpu/empty_texture_source.h"


namespace gpu
{


   namespace model
   {
      

      class CLASS_DECL_GPU model_base : 
         virtual public ::gpu::empty_texture_source,
         virtual public ::graphics3d::renderable
      {
      public:
         ::pointer<material> m_pmaterialOverride;

         //bool m_bExternalPbr = false;
         ::string m_strDirectory;
         ::string_map<::pointer<::gpu::texture>> m_mapTexture;

         model_base();


         ~model_base() override;

         ::gpu::texture *get_target_texture() override;


         //virtual void initialize_gpu_gltf_model(::gpu::context *pgpucontext, const ::gpu::renderable_t &model);


         //virtual void initialize_gpu_gltf_model(::gpu::context *pgpucontext, const ::file::path &path,
           //                                     bool flipTexturesVertically, bool bExternalPbr);

         //virtual void loadModel(const ::file::path &path, bool flipTexturesVertically, bool bExternalPbr);

         ::gpu::texture * loadMaterialTexture(const ::scoped_string &scopedstr, bool bSrgb);


      };


   } // namespace model


} // namespace gpu


