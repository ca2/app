// From model_base.cpp by camilo on 2025-10-10 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "bred/gpu/texture.h"
#include "bred/gltf/vertex.h"
#include "model_base.h"

#include <stb/stb_image.h>

#include "assimp_iosystem.h"
#include "bred/gpu/context.h"

#include <assimp/matrix4x4.h>
//#include <glm/glm.hpp>
//#include <glm/gtc/type_ptr.hpp> // For glm::make_mat4



namespace gpu
{


   namespace gltf
   {


      model_base::model_base() {}


      model_base::~model_base() {}


      ::gpu::texture *model_base::get_target_texture() { return nullptr; }


      //void model_base::initialize_gpu_gltf_model(::gpu::context *pgpucontext, const ::gpu::renderable_t &model_base)
      //{

      //   initialize_gpu_context_object(pgpucontext);

      //   loadModel(model_base.m_path, true, model_base.m_bExternalPbr);
      //}


      //void model_base::initialize_gpu_gltf_model(::gpu::context *pgpucontext, const ::file::path &path,
      //                                      bool flipTexturesVertically, bool bExternalPbr)
      //{

      //   initialize_gpu_context_object(pgpucontext);

      //   loadModel(path, flipTexturesVertically, bExternalPbr);
      //}


      //void model_base::initialize_gpu_gltf_model(::gpu::context *pgpucontext, const ::file::path &path,
      //                                      ::gpu::gltf::material *pmaterial, bool flipTexturesVertically,
      //                                      bool bExternalPbr)
      //{

      //   initialize_gpu_context_object(pgpucontext);
      //   m_pmaterialOverride = pmaterial;
      //   loadModel(path, flipTexturesVertically, bExternalPbr);
      //}


      //void model_base::draw(::gpu::command_buffer *pcommandbuffer)
      //{
      //   for (auto &pmesh: m_mesha)
      //   {
      //      pmesh->draw(pcommandbuffer);
      //   }
      //}


      //void model_base::loadModel(const ::file::path &path, bool flipTexturesVertically, bool bExternalPbr)
      //{

      //   {

      //      m_bExternalPbr = bExternalPbr;

      //      stbi_set_flip_vertically_on_load(flipTexturesVertically);
      //      // importer.SetIOHandler(get_assimp_iosystem());
      //      const aiScene *scene = get_assimp_importer()->ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs |
      //                                                                      aiProcess_CalcTangentSpace);

      //      if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
      //      {
      //         error() << "Error loading model_base: " << get_assimp_importer()->GetErrorString();
      //         stbi_set_flip_vertically_on_load(true);
      //         return;
      //      }

      //      m_strDirectory = path.folder();

      //      processNode(scene->mRootNode, scene);
      //      stbi_set_flip_vertically_on_load(true);
      //   }
      //}


      //// recursively load all meshes in the node tree
      //void model_base::processNode(aiNode *node, const aiScene *scene)
      //{
      //   // process all of this node's meshes if it has any
      //   for (unsigned int i = 0; i < node->mNumMeshes; i++)
      //   {
      //      aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
      //      auto pmesh = processMesh(mesh, scene);
      //      auto m = node->mTransformation;
      //      auto p = node->mParent;

      //      while (p)
      //      {

      //         m = p->mTransformation * m;
      //         p = p->mParent;
      //      }
      //      pmesh->uniformBlock.matrix = aiMatrix4x4ToGlm(m);
      //      m_mesha.add(pmesh);
      //   }

      //   // continue with children
      //   for (unsigned int i = 0; i < node->mNumChildren; i++)
      //   {
      //      processNode(node->mChildren[i], scene);
      //   }
      //}


      //// convert assimp mesh to our own mesh class
      //::pointer<::gpu::gltf::mesh> model_base::processMesh(aiMesh *mesh, const aiScene *scene)
      //{
      //   ::array_base<gltf::vertex> vertices;
      //   ::array_base<unsigned int> indices;
      //   ::pointer<::gpu::gltf::material> pmaterial;

      //   if (m_pmaterialOverride)
      //   {
      //      pmaterial = m_pmaterialOverride;
      //   }
      //   else
      //   {

      //      øconstruct_new(pmaterial);
      //   }

      //   // vertices
      //   for (unsigned int i = 0; i < mesh->mNumVertices; i++)
      //   {
      //      ::gpu::gltf::vertex vertex;

      //      // position
      //      floating_sequence3 position;
      //      position.x = mesh->mVertices[i].x;
      //      position.y = mesh->mVertices[i].y;
      //      position.z = mesh->mVertices[i].z;

      //      vertex.mPosition = position;

      //      // normal
      //      floating_sequence3 normal;
      //      normal.x = mesh->mNormals[i].x;
      //      normal.y = mesh->mNormals[i].y;
      //      normal.z = mesh->mNormals[i].z;

      //      vertex.mNormal = normal;

      //      // texture coordinates
      //      if (mesh->mTextureCoords[0])
      //      {
      //         glm::vec2 textureCoordinates;
      //         textureCoordinates.x = mesh->mTextureCoords[0][i].x;
      //         textureCoordinates.y = mesh->mTextureCoords[0][i].y;
      //         vertex.mTextureCoordinates = textureCoordinates;
      //      }
      //      else
      //      {
      //         vertex.mTextureCoordinates = glm::vec2(0.0f, 0.0f);
      //      }

      //      // tangents
      //      glm::vec4 color;
      //      if (mesh->mColors[0])
      //      {
      //         color.x = mesh->mColors[0]->r;
      //         color.y = mesh->mColors[0]->g;
      //         color.z = mesh->mColors[0]->y;
      //         color.w = mesh->mColors[0]->x;
      //      }
      //      else
      //      {
      //         color = glm::vec4(1.0f);
      //      }
      //      vertex.mColor = color;

      //      // tangents
      //      glm::vec4 tangent4;
      //      floating_sequence3 tangent;
      //      tangent.x = mesh->mTangents[0].x;
      //      tangent.y = mesh->mTangents[0].y;
      //      tangent.z = mesh->mTangents[0].z;
      //      floating_sequence3 bitangent;
      //      bitangent.x = mesh->mBitangents[0].x;
      //      bitangent.y = mesh->mBitangents[0].y;
      //      bitangent.z = mesh->mBitangents[0].z;
      //      tangent4.x = tangent.x;
      //      tangent4.y = tangent.y;
      //      tangent4.z = tangent.z;
      //      tangent4.w = (::glm::dot(::glm::cross(normal, tangent), bitangent) < 0.0f) ? -1.0f : 1.0f;
      //      vertex.mTangent = tangent4;

      //      //// bitangents
      //      // floating_sequence3 bitangent;
      //      // bitangent.x = mesh->mBitangents[0].x;
      //      // bitangent.y = mesh->mBitangents[0].y;
      //      // bitangent.z = mesh->mBitangents[0].z;
      //      // vertex.mBitangent = bitangent;

      //      vertices.add(vertex);
      //   }

      //   // indices
      //   for (unsigned int i = 0; i < mesh->mNumFaces; i++)
      //   {

      //      aiFace face = mesh->mFaces[i];

      //      for (unsigned int j = 0; j < face.mNumIndices; j++)
      //      {
      //         indices.add(face.mIndices[j]);
      //      }
      //   }

      //   // material
      //   if (!m_pmaterialOverride)
      //   {
      //      if (m_strDirectory.case_insensitive_contains("cerberus"))
      //      {

      //         information() << "going to load cerberus material?!?";
      //      }
      //      else if (m_strDirectory.case_insensitive_contains("helmet"))
      //      {

      //         information() << "going to load helmet material?!?";
      //      }
      //      if (m_bExternalPbr)
      //      {
      //         // albedo
      //         if (pmaterial->m_ptextureAlbedo = loadMaterialTexture("albedo.ktx", aiTextureType_DIFFUSE))
      //         {
      //            pmaterial->useTextureAlbedo = true;
      //         }

      //         // metallicRoughness (in gltf 2.0 they are combined in one texture)
      //         if (pmaterial->m_ptextureMetallicRoughness = loadMaterialTexture("metallic.ktx", aiTextureType_UNKNOWN))
      //         {
      //            // defined here in assimp
      //            // https://github.com/assimp/assimp/blob/master/include/assimp/pbrmaterial.h#L57
      //            pmaterial->useTextureMetallicRoughness = true;
      //         }

      //         // normal
      //         if (pmaterial->m_ptextureNormal = loadMaterialTexture("normal.ktx", aiTextureType_NORMALS))
      //         {
      //            pmaterial->useTextureNormal = true;
      //         }

      //         // ambient occlusion
      //         if (pmaterial->m_ptextureAmbientOcclusion = loadMaterialTexture("ao.ktx", aiTextureType_LIGHTMAP))
      //         {
      //            pmaterial->useTextureAmbientOcclusion = true;
      //         }

      //         // emissive
      //         if (pmaterial->m_ptextureEmissive = loadMaterialTexture("emissive.ktx", aiTextureType_EMISSIVE))
      //         {
      //            pmaterial->useTextureEmissive = true;
      //         }
      //      }
      //      else if (mesh->mMaterialIndex >= 0)
      //      {
      //         aiMaterial *aiMaterial = scene->mMaterials[mesh->mMaterialIndex];

      //         // albedo
      //         if (aiMaterial->GetTextureCount(aiTextureType_DIFFUSE))
      //         {
      //            pmaterial->useTextureAlbedo = true;
      //            pmaterial->m_ptextureAlbedo = loadMaterialTexture(aiMaterial, aiTextureType_DIFFUSE);
      //         }

      //         // metallicRoughness (in gltf 2.0 they are combined in one texture)
      //         if (aiMaterial->GetTextureCount(aiTextureType_UNKNOWN))
      //         {
      //            // defined here in assimp
      //            // https://github.com/assimp/assimp/blob/master/include/assimp/pbrmaterial.h#L57
      //            pmaterial->useTextureMetallicRoughness = true;
      //            pmaterial->m_ptextureMetallicRoughness = loadMaterialTexture(aiMaterial, aiTextureType_UNKNOWN);
      //         }

      //         // normal
      //         if (aiMaterial->GetTextureCount(aiTextureType_NORMALS))
      //         {
      //            pmaterial->useTextureNormal = true;
      //            pmaterial->m_ptextureNormal = loadMaterialTexture(aiMaterial, aiTextureType_NORMALS);
      //         }

      //         // ambient occlusion
      //         if (aiMaterial->GetTextureCount(aiTextureType_LIGHTMAP))
      //         {
      //            pmaterial->useTextureAmbientOcclusion = true;
      //            pmaterial->m_ptextureAmbientOcclusion = loadMaterialTexture(aiMaterial, aiTextureType_LIGHTMAP);
      //         }

      //         // emissive
      //         if (aiMaterial->GetTextureCount(aiTextureType_EMISSIVE))
      //         {
      //            pmaterial->useTextureEmissive = true;
      //            pmaterial->m_ptextureEmissive = loadMaterialTexture(aiMaterial, aiTextureType_EMISSIVE);
      //         }
      //      }
      //   }

      //   auto pmesh = øcreate<::gpu::gltf::mesh>();

      //   pmesh->initialize_gpu_gltf_mesh(vertices, indices, pmaterial);


      //   return pmesh;
      //}


      //// loads the first texture of given type
      //::gpu::texture *model_base::loadMaterialTexture(aiMaterial *material, aiTextureType type)
      //{

      //   aiString path;

      //   material->GetTexture(type, 0, &path);

      //   auto ptexture = loadMaterialTexture(path.C_Str(), type);

      //   return ptexture;
      //}


      // loads the first texture of given type
      ::gpu::texture *model_base::loadMaterialTexture(const ::scoped_string &scopedstr, aiTextureType type)
      {

         // check if we already have it loaded and use that if so
         auto iterator = m_mapTexture.find(scopedstr);
         if (iterator != m_mapTexture.end())
         {
            return iterator->element2();
         }

         ::file::path pathImage = ::file::path(m_strDirectory) / scopedstr;

         ::pointer<::gpu::texture> ptexture;

         try
         {
            ptexture = m_pgpucontext->generic_texture(pathImage, type);
         }
         catch (...)
         {
         }

         // auto ptexture = øcreate<::gpu::texture>();
         //
         information() << "Process material: " << scopedstr;

         // auto p
         // //ptexture->mId = textureFromFile(path.C_Str(), m_strDirectory, type);
         // //texture->mPath = path.C_Str();
         //
         // cache it for future lookups
         m_mapTexture.set_at(scopedstr, ptexture);

         return ptexture;
      }


      // ::pointer < ::gpu::texture> model_base::textureFromFile(const char *fileName, ::string directory, aiTextureType
      // type)
      // {
      //
      //    return {};
      //    // int width, height, numChannels;
      //    //
      //    // ::string relativePath = fileName;
      //    // ::string path = directory + '/' + relativePath;
      //    //
      //    // unsigned char *data = stbi_load(path.c_str(), &width, &height, &numChannels, 0);
      //    //
      //    // if (!data)
      //    // {
      //    //    std::cout << "Failed to load texture data" << std::endl;
      //    //    stbi_image_free(data);
      //    // }
      //    //
      //    // GLenum format;
      //    //
      //    // switch (numChannels)
      //    // {
      //    //    case 1:
      //    //       format = GL_RED;
      //    //       break;
      //    //    case 3:
      //    //       format = GL_RGB;
      //    //       break;
      //    //    case 4:
      //    //       format = GL_RGBA;
      //    //       break;
      //    // }
      //    //
      //    // GLenum internalFormat = format;
      //    //
      //    // // account for sRGB textures here
      //    // //
      //    // // diffuse textures are in sRGB space (non-linear)
      //    // // metallic/roughness/normals are usually in linear
      //    // // AO depends
      //    // if (type == aiTextureType_DIFFUSE)
      //    // {
      //    //    if (internalFormat == GL_RGB)
      //    //    {
      //    //       internalFormat = GL_SRGB;
      //    //    }
      //    //    else if (internalFormat == GL_RGBA)
      //    //    {
      //    //       internalFormat = GL_SRGB_ALPHA;
      //    //    }
      //    // }
      //    //
      //    // unsigned int textureId;
      //    // glGenTextures(1, &textureId);
      //    // glBindTexture(GL_TEXTURE_2D, textureId);
      //    //
      //    // // generate the texture
      //    // glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, data);
      //    // glGenerateMipmap(GL_TEXTURE_2D);
      //    //
      //    // // texture wrapping/filtering options
      //    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
      //    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
      //    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // image is resized using bilinear
      //    filtering
      //    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // image is enlarged using bilinear
      //    filtering
      //    //
      //    // // free the image data
      //    // stbi_image_free(data);
      //    //
      //    // return textureId;
      // }


   } // namespace gltf


} // namespace gpu
