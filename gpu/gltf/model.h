// From github:/tristancalderbank/OpenGL-PBR-Renderer/model.h by
// camilo on 2025-09-26 18:35 <3ThomasBorregaardSorensen!!

#pragma once

#include <assimp/Importer.hpp>
#include <assimp/pbrmaterial.h>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
//#include "stb_image/stb_image.h"

//#include <map>
#include "gpu/gltf/mesh.h"


namespace gpu
{


   namespace gltf
   {
      /**
       * A collection of meshes.
       */
      class model :
         virtual public context_object,
         virtual public ::graphics3d::renderable
      {
      public:


         // data
         ::pointer_array<mesh>                     m_mesha;
         ::string                                  m_strDirectory;
         ::string_map<::pointer<::gpu::texture> >  m_mapTexture;
         ::pointer<material>                       m_pmaterialOverride;


         /**
          * Load a glTF 2.0 model.
          * @param path
          */
         model();


         ~model() override;


         virtual void load_gltf_model(const ::scoped_string &scopedstr);


         virtual void load_gltf_model(const ::scoped_string &scopedstr, bool flipTexturesVertically);


         /**
          * Load a glTF 2.0 model using a provided material. This will ignore any material
          * present in the model file.
          * @param path
          */
         virtual void load_gltf_model(const ::scoped_string &scopedstr, material *pmaterial,
                                      bool flipTexturesVertically);


         //Model(::string path, std::shared_ptr<Material> material, bool flipTexturesVertically);
         //void Draw(Shader &shader);

         virtual void draw(::gpu::command_buffer *pcommandbuffer) override;


         virtual void loadModel(::string path, bool flipTexturesVertically);


         // recursively load all meshes in the node tree
         virtual void processNode(aiNode *node, const aiScene *scene);


         // convert assimp mesh to our own mesh class
         virtual ::gpu::gltf::mesh *processMesh(aiMesh *mesh, const aiScene *scene);


         // loads the first texture of given type
         virtual ::gpu::texture *loadMaterialTexture(aiMaterial *material, aiTextureType type);


         virtual unsigned int textureFromFile(const char *fileName, ::string directory, aiTextureType type);

      };

   } // namespace gltf

} // namespace gpu
