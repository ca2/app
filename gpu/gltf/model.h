// From github:/tristancalderbank/OpenGL-PBR-Renderer/model.h by
// camilo on 2025-09-26 18:35 <3ThomasBorregaardSorensen!!

#pragma once

#include "gpu/gltf/model_base.h"
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include "gpu/gltf/mesh.h"


namespace gpu
{


   namespace gltf
   {
      /**
       * A collection of meshes.
       */
      class CLASS_DECL_GPU model :
         virtual public ::gpu::gltf::model_base
      {
      public:


         // data
         ::pointer_array<mesh>                     m_mesha;

         /**
          * Load a glTF 2.0 model.
          * @param path
          */
         model();


         ~model() override;

         ::gpu::texture *get_target_texture() override;


         virtual void initialize_gpu_gltf_model(::gpu::context *pgpucontext, const ::gpu::renderable_t &model);


         virtual void initialize_gpu_gltf_model(::gpu::context * pgpucontext,  const ::file::path & path, bool flipTexturesVertically, bool bExternalPbr);


         /**
          * Load a glTF 2.0 model using a provided material. This will ignore any material
          * present in the model file.
          * @param path
          */
         virtual void initialize_gpu_gltf_model(::gpu::context * pgpucontext,
            const ::file::path & path,
            ::gpu::gltf::material *pmaterial,
                                      bool flipTexturesVertically, bool bExternalPbr);


         //Model(::string path, std::shared_ptr<Material> material, bool flipTexturesVertically);
         //void Draw(Shader &shader);

         virtual void draw(::gpu::command_buffer *pcommandbuffer) override;


         virtual void loadModel(const ::file::path & path, bool flipTexturesVertically, bool bExternalPbr);


         // recursively load all meshes in the node tree
         virtual void processNode(aiNode *node, const aiScene *scene);


         // convert assimp mesh to our own mesh class
         virtual ::pointer < ::gpu::gltf::mesh > processMesh(aiMesh *mesh, const aiScene *scene);


         // loads the first texture of given type
         virtual ::gpu::texture *loadMaterialTexture(aiMaterial *material, aiTextureType type);
         virtual ::gpu::texture *loadMaterialTexture(const ::scoped_string & scopedstr, aiTextureType type);


         //virtual ::gpu::texture> textureFromFile(const char *fileName, ::string directory, aiTextureType type);

      };

   } // namespace gltf

} // namespace gpu
