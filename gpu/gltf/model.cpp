// From github:/tristancalderbank/OpenGL-PBR-Renderer/model.cpp by
// camilo on 2025-09-26 18:14 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "model.h"
#include "bred/gltf/vertex.h"
#include "bred/gpu/texture.h"

#include <stb/stb_image.h>

#include "assimp_iosystem.h"
#include "bred/gpu/context.h"

//
// // For glm::make_mat4
#include <assimp/matrix4x4.h>
#include "_assimp.h"

//
//floating_matrix4 aiMatrix4x4ToColumnMajor(const aiMatrix4x4& from) {
//   // Assuming aiMatrix4x4 stores data contiguously in memory,
//   // and glm::make_mat4 can interpret the layout before transposition.
//   return geometry::transpose(geometry::make_mat4(&from.a1));
//}

assimp_iosystem * get_assimp_iosystem()
{
   static thread_local  assimp_iosystem * g_passimpiosystem=nullptr;
   if (!g_passimpiosystem)
   {
      g_passimpiosystem= øraw_new assimp_iosystem(::system());
   }
   return g_passimpiosystem;
}

Assimp::Importer * get_assimp_importer()
{
   static thread_local Assimp::Importer * g_passimpimporter=nullptr;
   if (!g_passimpimporter)
   {
      g_passimpimporter= øraw_new Assimp::Importer();
      g_passimpimporter->SetIOHandler(get_assimp_iosystem());
   }
   return g_passimpimporter;
}


namespace gpu
{


   namespace gltf
   {


      model::model()
      {


      }


      model::~model()
      {


      }


      ::gpu::texture *model::get_target_texture() 
      {
      
         return m_mapTexture.first().element2();
      
      }


      void model::initialize_gpu_gltf_model(::gpu::context *pgpucontext, const ::gpu::renderable_t &model)
      {

         initialize_gpu_context_object(pgpucontext);

         loadModel(model.m_pathRenderable, true, model.m_bExternalPbr);

      }


      void model::initialize_gpu_gltf_model(::gpu::context * pgpucontext,  const ::file::path & path, bool flipTexturesVertically, bool bExternalPbr)
      {

         initialize_gpu_context_object(pgpucontext);

         loadModel(path, flipTexturesVertically, bExternalPbr);

      }


      void model::initialize_gpu_gltf_model(::gpu::context * pgpucontext,  const ::file::path & path,
         ::gpu::gltf::material *pmaterial, bool flipTexturesVertically, bool bExternalPbr)
      {

         initialize_gpu_context_object(pgpucontext);
         m_pmaterialOverride = pmaterial;
         loadModel(path, flipTexturesVertically, bExternalPbr);
      }

      //void model::bind2(::gpu::command_buffer *pcommandbuffer)
      //{
      //   for (auto &pmesh: m_mesha)
      //   {
      //      pmesh->bind2(pcommandbuffer);
      //   }
      //}

      void model::draw2(::gpu::command_buffer *pcommandbuffer)
      {
         for (auto &pmesh: m_mesha)
         {
            pmesh->draw2(pcommandbuffer);
         }
      }


      void model::loadModel(const ::file::path & path, bool flipTexturesVertically, bool bExternalPbr)
      {

         {

            m_bExternalPbr = bExternalPbr;

            stbi_set_flip_vertically_on_load(flipTexturesVertically);
            //importer.SetIOHandler(get_assimp_iosystem());
            const aiScene *scene =
               // get_assimp_importer()->ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs |
               // aiProcess_CalcTangentSpace);
//                              get_assimp_importer()->ReadFile(path,
  //                                                          aiProcess_Triangulate | aiProcess_FlipUVs);
               //get_assimp_importer()->ReadFile(path, aiProcess_Triangulate);
               get_assimp_importer()->ReadFile(path, 0);

            if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
            {
               error() << "Error loading model: " << get_assimp_importer()->GetErrorString();
               stbi_set_flip_vertically_on_load(true);
               return;
            }

            m_strDirectory = path.folder();

            processNode(scene->mRootNode, scene);
            stbi_set_flip_vertically_on_load(true);
         }

      }


      // recursively load all meshes in the node tree
      void model::processNode(aiNode *node, const aiScene *scene)
      {
         // process all of this node's meshes if it has any
         for (unsigned int i = 0; i < node->mNumMeshes; i++)
         {
            aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
            auto pmesh =processMesh(mesh, scene);
            auto m = node->mTransformation;
            auto p = node->mParent;

            while (p)
            {

               m = p->mTransformation * m;
               p = p->mParent;
            }
            pmesh->uniformBlock.matrix =aiMatrix4x4ToColumnMajor(m);
            m_mesha.add(pmesh);
         }

         // continue with children
         for (unsigned int i = 0; i < node->mNumChildren; i++)
         {
            processNode(node->mChildren[i], scene);
         }
      }


         // Compute tangents from indexed mesh data
      void computeTangents(::array_base<gltf::vertex> &vertices, const ::array_base<unsigned int> &indices) 
      {
         array_base<floating_sequence3> tan1;
         array_base<floating_sequence3> tan2;

         tan1.set_size(vertices.size());
         tan2.set_size(vertices.size());

         for (size_t i = 0; i < indices.size(); i += 3)
         {
            uint32_t i1 = indices[i + 0];
            uint32_t i2 = indices[i + 1];
            uint32_t i3 = indices[i + 2];

            const ::floating_sequence3 &v1 = vertices[i1].position;
            const ::floating_sequence3 &v2 = vertices[i2].position;
            const ::floating_sequence3 &v3 = vertices[i3].position;

            auto &w1 = vertices[i1].uv;
            auto &w2 = vertices[i2].uv;
            auto &w3 = vertices[i3].uv;

            floating_sequence3 e1 = v2 - v1;
            floating_sequence3 e2 = v3 - v1;

            float s1 = w2.x - w1.x;
            float s2 = w3.x - w1.x;
            float t1 = w2.y - w1.y;
            float t2 = w3.y - w1.y;

            float det = s1 * t2 - s2 * t1;
            if (fabs(det) < 1e-10f)
               continue;
            float r = 1.0f / det;

            floating_sequence3 sdir = (e1 * t2 - e2 * t1) * r;
            floating_sequence3 tdir = (e2 * s1 - e1 * s2) * r;

            tan1[i1] += sdir;
            tan1[i2] += sdir;
            tan1[i3] += sdir;
            tan2[i1] += tdir;
            tan2[i2] += tdir;
            tan2[i3] += tdir;
         }

         for (size_t i = 0; i < vertices.size(); ++i)
         {
            const ::floating_sequence3 &n = vertices[i].normal;
            const ::floating_sequence3 &t = tan1[i];

            auto tangent = (t - n * n.dotted(t)).normalized();
            float sign = (n.crossed(t).dotted(tan2[i]) < 0.0f) ? -1.0f : 1.0f;

            vertices[i].tangent = floating_sequence4(tangent, sign);
         }
      }

      // convert assimp mesh to our own mesh class
      ::pointer <::gpu::gltf::mesh > model::processMesh(aiMesh *mesh, const aiScene *scene)
      {
         
         model_data<::gpu::gltf::vertex> modeldata;
         //::array_base<gltf::vertex> vertices;
         //::array_base<unsigned int> indices;
         ::pointer < ::gpu::gltf::material> pmaterial;

         if (m_pmaterialOverride)
         {
            pmaterial = m_pmaterialOverride;
         }
         else
         {

            øconstruct_new(pmaterial);
            pmaterial->m_pgpucontext = m_pgpucontext;

         }



         bool bHasTangentsAndBitangents = mesh->HasTangentsAndBitangents();

         // vertices
         for (unsigned int i = 0; i < mesh->mNumVertices; i++)
         {
            ::gpu::gltf::vertex vertex;

            // position
            floating_sequence3 position;
            position.x = mesh->mVertices[i].x;
            position.y = mesh->mVertices[i].y;
            position.z = mesh->mVertices[i].z;

            vertex.position = position;

            // normal
            floating_sequence3 normal;
            normal.x = mesh->mNormals[i].x;
            normal.y = mesh->mNormals[i].y;
            normal.z = mesh->mNormals[i].z;

            vertex.normal = normal;

            // texture coordinates
            if (mesh->mTextureCoords[0])
            {
               floating_sequence2 textureCoordinates;
               textureCoordinates.x = mesh->mTextureCoords[0][i].x;
               textureCoordinates.y = mesh->mTextureCoords[0][i].y;
               vertex.uv = textureCoordinates;
            }
            else
            {
               vertex.uv = floating_sequence2(0.0f, 0.0f);
            }

            // tangents
            floating_sequence4 color;
            if (mesh->mColors[0])
            {
               color.x = mesh->mColors[0]->r;
               color.y = mesh->mColors[0]->g;
               color.z = mesh->mColors[0]->b;
               color.w = mesh->mColors[0]->a;
            }
            else
            {
               color = floating_sequence4(1.0f);
            }
            vertex.color = color;

            if (bHasTangentsAndBitangents)
            {
               // tangents
               floating_sequence4 tangent4;
               floating_sequence3 tangent;
               tangent.x = mesh->mTangents[0].x;
               tangent.y = mesh->mTangents[0].y;
               tangent.z = mesh->mTangents[0].z;
               floating_sequence3 bitangent;
               bitangent.x = mesh->mBitangents[0].x;
               bitangent.y = mesh->mBitangents[0].y;
               bitangent.z = mesh->mBitangents[0].z;
               tangent4.x = tangent.x;
               tangent4.y = tangent.y;
               tangent4.z = (normal.crossed(tangent).dotted(bitangent) < 0.0f) ? -1.0f : 1.0f;
               vertex.tangent = tangent4;
            }

            ////// bitangents
            //floating_sequence3 bitangent;
            //bitangent.x = mesh->mBitangents[0].x;
            //bitangent.y = mesh->mBitangents[0].y;
            //bitangent.z = mesh->mBitangents[0].z;
            //vertex.bitangent = bitangent;

            modeldata.m_vertexes.add(vertex);

         }

         // indices
         for (unsigned int i = 0; i < mesh->mNumFaces; i++)
         {

            aiFace face = mesh->mFaces[i];

            for (unsigned int j = 0; j < face.mNumIndices; j++)
            {
               modeldata.m_indexes.add(face.mIndices[j]);

            }

         }

         if (!bHasTangentsAndBitangents)
         {


               // Compute tangents from indexed mesh data
            computeTangents(modeldata.m_vertexes, modeldata.m_indexes);

         }

         // material
         if (!m_pmaterialOverride)
         {
            if (m_strDirectory.case_insensitive_contains("cerberus"))
            {

               information() << "going to load cerberus material?!?";
                                

            }
            else if (m_strDirectory.case_insensitive_contains("helmet"))
            {

               information() << "going to load helmet material?!?";
            }
            if (m_bExternalPbr)
            {
               // albedo
               if (pmaterial->m_textureaPbr[e_texture_albedo] = loadMaterialTexture("albedo.ktx", aiTextureType_DIFFUSE))
               {
                  
                  pmaterial->useTextureAlbedo = true;

               }

               // metallicRoughness (in gltf 2.0 they are combined in one texture)
               if (pmaterial->m_textureaPbr[e_texture_metallic_roughness] = loadMaterialTexture("metallic.ktx", aiTextureType_UNKNOWN))
               {
                  // defined here in assimp
                  // https://github.com/assimp/assimp/blob/master/include/assimp/pbrmaterial.h#L57
                  pmaterial->useTextureMetallicRoughness = true;
               }

               // normal
               if (pmaterial->m_textureaPbr[e_texture_normal] =
                      loadMaterialTexture("normal.ktx", aiTextureType_NORMALS))
               {
                  pmaterial->useTextureNormal = true;
               }

               // ambient occlusion
               if (pmaterial->m_textureaPbr[e_texture_ambient_occlusion] =
                      loadMaterialTexture("ao.ktx", aiTextureType_LIGHTMAP))
               {
                  pmaterial->useTextureAmbientOcclusion = true;
               }

               // emissive
               if (pmaterial->m_textureaPbr[e_texture_emissive] =
                      loadMaterialTexture("emissive.ktx", aiTextureType_EMISSIVE))
               {
                  pmaterial->useTextureEmissive = true;
               }
            }
            else if (mesh->mMaterialIndex >= 0)
            {
               aiMaterial *aiMaterial = scene->mMaterials[mesh->mMaterialIndex];
               {
                  aiString alphaModeStr;
                  // Attempt to get the glTF alphaMode property
                  if (aiMaterial->Get(AI_MATKEY_GLTF_ALPHAMODE, alphaModeStr) == AI_SUCCESS)
                  {
                     std::string mode = alphaModeStr.C_Str();

                     if (mode == "OPAQUE")
                     {
                        // Material is fully opaque (default)
                        //;
                        //;
                        information() << "Alpha Mode: OPAQUE";
                        pmaterial->alphaMode = material::ALPHAMODE_OPAQUE;
                     }
                     else if (mode == "MASK")
                     {
                        // Material uses alpha cutoff
                        information() << "Alpha Mode: MASK";
                        // You can also retrieve the alphaCutoff value if needed:
                        pmaterial->alphaMode = material::ALPHAMODE_MASK;
                        float alphaCutoff = 0.5f; // Default value
                        if (aiMaterial->Get(AI_MATKEY_GLTF_ALPHACUTOFF, alphaCutoff) == AI_SUCCESS)
                        {
                           information() << "Alpha Cutoff: " << alphaCutoff;
                           pmaterial->alphaCutoff = alphaCutoff;
                        }
                        else
                        {
                           pmaterial->alphaCutoff = 0.5f;
                        }
                     }
                     else if (mode == "BLEND")
                     {
                        // Material uses alpha blending (transparency)
                        //std::cout << "Alpha Mode: BLEND" << std::endl;
                        pmaterial->alphaMode = material::ALPHAMODE_BLEND;
                     }
                     else
                     {
                        // Unknown or unsupported mode
                        information() << "Alpha Mode: Unknown (" << mode << ")";
                     }
                  } 
               }
               {
                  float fMetallic = 0.f;
                  // Attempt to get the glTF alphaMode property
                  if (aiMaterial->Get(AI_MATKEY_METALLIC_FACTOR, fMetallic) == AI_SUCCESS)
                  {
                     if (fMetallic < FLT_EPSILON)
                     {
                        pmaterial->m_fMetallic = 0.f;
                     }
                     else
                     {
                        pmaterial->m_fMetallic = fMetallic;

                     }
                  }
                  else
                  {

                     pmaterial->m_fMetallic = 0.f;

                  }

               }
               {
                  float fRoughness = 0.f;
                  // Attempt to get the glTF alphaMode property
                  if (aiMaterial->Get(AI_MATKEY_ROUGHNESS_FACTOR, fRoughness) == AI_SUCCESS)
                  {
                     if (fRoughness == 0.5f)
                     {
                        pmaterial->m_fRoughness = 0.5f;
                     }
                     else
                     {
                        pmaterial->m_fRoughness = fRoughness;
                     }
                  }
                  else
                  {

                     pmaterial->m_fRoughness = 0.f;
                  }
               }
               {
                  float ambientOcclusionStrength = 1.f;
                  // Attempt to get the glTF alphaMode property
                  if (aiMaterial->Get(AI_MATKEY_GLTF_TEXTURE_STRENGTH(aiTextureType_AMBIENT_OCCLUSION, 0),
                                    ambientOcclusionStrength) == AI_SUCCESS)
                  {
                     if (ambientOcclusionStrength == 1.f)
                     {
                        pmaterial->m_fAmbientOcclusion = 1.f;
                     }
                     else
                     {
                        pmaterial->m_fAmbientOcclusion = ambientOcclusionStrength;
                     }
                  }
                  else
                  {

                     pmaterial->m_fAmbientOcclusion = 1.f;
                  }
               }
               // albedo
               if (aiMaterial->GetTextureCount(aiTextureType_DIFFUSE))
               {
                  pmaterial->useTextureAlbedo = true;
                  auto ptextureAlbedo = loadMaterialTexture(aiMaterial, aiTextureType_DIFFUSE);
                  pmaterial->m_textureaPbr[e_texture_albedo] = ptextureAlbedo;
               }

               // metallicRoughness (in gltf 2.0 they are combined in one texture)
               if (aiMaterial->GetTextureCount(aiTextureType_UNKNOWN))
               {
                  // defined here in assimp https://github.com/assimp/assimp/blob/master/include/assimp/pbrmaterial.h#L57
                  pmaterial->useTextureMetallicRoughness = true;
                  pmaterial->m_textureaPbr[e_texture_metallic_roughness] =
                     loadMaterialTexture(aiMaterial, aiTextureType_UNKNOWN);
               }

               // normal
               if (aiMaterial->GetTextureCount(aiTextureType_NORMALS))
               {
                  pmaterial->useTextureNormal = true;
                  pmaterial->m_textureaPbr[e_texture_normal] =
                     loadMaterialTexture(aiMaterial, aiTextureType_NORMALS);
               }

               // ambient occlusion
               if (aiMaterial->GetTextureCount(aiTextureType_LIGHTMAP))
               {
                  pmaterial->useTextureAmbientOcclusion = true;
                  pmaterial->m_textureaPbr[e_texture_ambient_occlusion] =
                     loadMaterialTexture(aiMaterial, aiTextureType_LIGHTMAP);
               }

               // emissive
               if (aiMaterial->GetTextureCount(aiTextureType_EMISSIVE))
               {
                  pmaterial->useTextureEmissive = true;
                  pmaterial->m_textureaPbr[e_texture_emissive] =
                     loadMaterialTexture(aiMaterial, aiTextureType_EMISSIVE);
               }

               aiColor4D assimpcolor;
               if (AI_SUCCESS == aiMaterial->Get(AI_MATKEY_BASE_COLOR, assimpcolor))
               {
                  pmaterial->m_seq3Albedo.red = assimpcolor.r;
                  pmaterial->m_seq3Albedo.green = assimpcolor.g;
                  pmaterial->m_seq3Albedo.blue = assimpcolor.b;
                  //pmaterial->m_seq3Albedo. = assimpcolor.r;
                     
               }

               //if (aiMaterial->Get())
            }
         }

         auto pmesh = øcreate<::gpu::gltf::mesh>();

         pmesh->m_pgpucontext = m_pgpucontext;

         pmesh->m_modeldata = ::transfer(modeldata);

         pmesh->initialize_gpu_gltf_mesh(pmaterial);

         return pmesh;

      }


      // loads the first texture of given type
      ::gpu::texture * model::loadMaterialTexture(aiMaterial *material, aiTextureType type)
      {

         aiString path;

         material->GetTexture(type, 0, &path);

         auto ptexture = loadMaterialTexture(path.C_Str(), type);

         return ptexture;

      }


      // loads the first texture of given type
      ::gpu::texture *model::loadMaterialTexture(const ::scoped_string &scopedstr, aiTextureType type)
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



      // ::pointer < ::gpu::texture> model::textureFromFile(const char *fileName, ::string directory, aiTextureType type)
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
      //    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // image is resized using bilinear filtering
      //    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // image is enlarged using bilinear filtering
      //    //
      //    // // free the image data
      //    // stbi_image_free(data);
      //    //
      //    // return textureId;
      // }

      ::gpu::texture *model::empty_texture()
      {

         if (!m_ptextureEmpty)
         {

            m_ptextureEmpty = ::transfer(m_pgpucontext->create_empty_texture());

         }

         return m_ptextureEmpty;

      }


   } // namespace gltf


} // namespaceg gpu
