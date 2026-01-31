// From github:/tristancalderbank/OpenGL-PBR-Renderer/model.h by
// camilo on 2025-09-26 18:35 <3ThomasBorregaardSorensen!!
#pragma once


#include "gpu/model/model_base.h"
#include "gpu/model/mesh.h"


namespace gpu
{





   namespace model
   {


      
      class CLASS_DECL_GPU model :
         virtual public ::gpu::model::model_base
      {
      public:




         ::pointer_array<mesh>                     m_mesha;

         enum_model m_emodel;
         ::pointer<::gpu::texture> m_ptextureEmpty;

         model();
         ~model() override;


         ::gpu::texture *get_target_texture() override;


         virtual void initialize_gpu_model(
            ::gpu::context *pgpucontext,
            const ::gpu::renderable_t &model);


         virtual void initialize_gpu_model(
            ::gpu::context * pgpucontext,  
            ::gpu::enum_model emodel,
            const ::file::path & path, 
            bool flipTexturesVertically, 
            bool bExternalPbr);


         virtual void initialize_gpu_model(::gpu::context * pgpucontext,
            const ::file::path & path, 
            ::gpu::enum_model emodel,
            ::gpu::model::material *pmaterial,
                                      bool flipTexturesVertically, bool bExternalPbr);


         //Model(::string path, std::shared_ptr<Material> material, bool flipTexturesVertically);
         //void Draw(Shader &shader);

         //virtual void bind2(::gpu::command_buffer *pcommandbuffer) override;
         virtual void draw2(::gpu::command_buffer *pcommandbuffer) override;


         virtual void load_model(const ::file::path & path, ::gpu::enum_model emodel, bool flipTexturesVertically, bool bExternalPbr);



         ::gpu::texture *loadMaterialTexture(const ::scoped_string &scopedstr, bool bSrgb);





         //virtual ::gpu::texture> textureFromFile(const char *fileName, ::string directory, aiTextureType type);

         ::gpu::texture *empty_texture() override;


      };



   } // namespace model


} // namespace gpu
