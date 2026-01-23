// From github:/tristancalderbank/OpenGL-PBR-Renderer/model.h by
// camilo on 2025-09-26 18:35 <3ThomasBorregaardSorensen!!
#pragma once


#include "gpu/model/_.h"
#include "gpu/model/model.h"
#include "gpu_opengl/gltf/mesh.h"


namespace gpu_opengl
{


   namespace gltf
   {
      /**
       * A collection of meshes.
       */
      class model :
         virtual public ::gpu::model::model
      {
      public:


         // // data
         // ::pointer_array<mesh> m_mesha;
         // ::string m_strDirectory;
         // ::string_map<::pointer<::gpu::Texture> m_mapTexture;
         // ::pointer<material> m_pmaterialOverride;
         //

         model();
         ~model() override;


         //void load_gltf_model(const ::scoped_string &scopedstr);


         //void load_gltf_model(const ::scoped_string &scopedstr, bool flipTexturesVertically);



         //Model(::string path, std::shared_ptr<Material> material, bool flipTexturesVertically);
         //void Draw(Shader &shader);

         //void draw(::gpu::command_buffer *pcommandbuffer) override;


         //void loadModel(::string path, bool flipTexturesVertically);


         // recursively load all meshes in the node tree
         //void processNode(aiNode *node, const aiScene *scene);


         // convert assimp mesh to our own mesh class
         //::pointer < ::gpu::model::mesh > processMesh(aiMesh *mesh, const aiScene *scene) override;


         // loads the first texture of given type
         //::gpu::texture *loadMaterialTexture(aiMaterial *material, aiTextureType type);


         //unsigned int textureFromFile(const char *fileName, ::string directory, aiTextureType type);

      };


   } // namespace gltf


} // namespace gpu_opengl


