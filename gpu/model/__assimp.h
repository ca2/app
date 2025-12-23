// Created by camilo on 2025-12-22 17:35 <3ThomasBorregaardSorensen!!
#pragma once


#include "gpu/model/_assimp.h"
#include "gpu/model/_.h"
#include "gpu/model/material.h"


namespace gpu
{

   namespace model
   {

      template<typename T>
      concept has_tangent = requires(T obj) { obj.tangent; };

               // Compute tangents from indexed mesh data
      template<typename VERTEX, typename INDEX>
      void computeTangents(::array_base<VERTEX> &vertices, const ::array_base<INDEX> &indices)
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


            template<typename VERTEX, typename INDEX>
      inline void processMesh(::gpu::model::model *pmodel, array_base<VERTEX> &vertexes, array_base<INDEX> &indexes,
                              ::pointer<::gpu::model::material> &pmaterial, aiMesh *mesh, const aiScene *scene,
                              ::gpu::model::material *pmaterialOverride);

            inline ::gpu::texture *loadMaterialTexture(::gpu::model::model *pmodel, const ::scoped_string &scopedstr,
                                                 aiTextureType etexturetype);
            ::gpu::texture *loadMaterialTexture(::gpu::model::model *pmodel, aiMaterial *material, aiTextureType type);


                  // recursively load all meshes in the node tree
            void processNode(::gpu::model::model * pmodel, aiNode *node, const aiScene *scene)
            {
               // process all of this node's meshes if it has any
               for (unsigned int i = 0; i < node->mNumMeshes; i++)
               {
                  aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
                  auto pmesh = pmodel->øcreate_new<::gpu::model::mesh>();
                  pmesh->m_pgpucontext = pmodel->m_pgpucontext;
                  
                  if (pmodel->m_egpumodel == ::gpu::e_model_gltf)
                  {
                     ::cast < ::gpu::model_data<::gpu::gltf::vertex> >pmodeldata = pmesh->m_pmodeldata;


                     processMesh(pmodel, pmodeldata->vertexes(), pmodeldata->indexes(),
                        
                        pmesh->m_pmaterial,
                                 mesh, scene, pmodel->m_pmaterialOverride);

                     pmodeldata->update();
                  }
                  else if (pmodel->m_egpumodel == ::gpu::e_model_wavefront)
                  {

                  ::cast < ::gpu::model_data<::graphics3d::Vertex> >pmodeldata = pmesh->m_pmodeldata;

                     processMesh(pmodel, pmodeldata->vertexes(),
                              pmodeldata->indexes(), 
                        pmesh->m_pmaterial,
                                 mesh, scene, pmodel->m_pmaterialOverride);

                     pmodeldata->update();
                    

                  }
                  auto m = node->mTransformation;
                  auto p = node->mParent;

                  while (p)
                  {

                     m = p->mTransformation * m;
                     p = p->mParent;
                  }
                  pmesh->uniformBlock.matrix = aiMatrix4x4ToColumnMajor(m);
                  pmodel->m_mesha.add(pmesh);
               }

               // continue with children
               for (unsigned int i = 0; i < node->mNumChildren; i++)
               {
                  processNode(pmodel, node->mChildren[i], scene);
               }
            }


                     // convert assimp mesh to our own mesh class
      template<typename VERTEX, typename INDEX >
      inline void processMesh(::gpu::model::model *pmodel,
         array_base<VERTEX> &vertexes, array_base<INDEX> &indexes,
         ::pointer < ::gpu::model::material > & pmaterial,
         aiMesh *mesh, const aiScene *scene, 
         ::gpu::model::material * pmaterialOverride)
      {


         //::array_base<gltf::vertex> vertices;
         //::array_base<unsigned int> indices;
         //::pointer<::gpu::model::material> pmaterial;

         if (pmaterialOverride)
         {
            pmaterial = pmaterialOverride;
         }
         else
         {

            pmodel->øconstruct_new(pmaterial);
            pmaterial->m_pgpucontext = pmodel->m_pgpucontext;
         }


         bool bHasTangentsAndBitangents = mesh->HasTangentsAndBitangents();

         // vertices
         for (unsigned int i = 0; i < mesh->mNumVertices; i++)
         {
            VERTEX vertex;

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

            if constexpr (has_tangent<VERTEX>)
            {

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
            }

            ////// bitangents
            // floating_sequence3 bitangent;
            // bitangent.x = mesh->mBitangents[0].x;
            // bitangent.y = mesh->mBitangents[0].y;
            // bitangent.z = mesh->mBitangents[0].z;
            // vertex.bitangent = bitangent;

            vertexes.add(vertex);
         }

         // indices
         for (unsigned int i = 0; i < mesh->mNumFaces; i++)
         {

            aiFace face = mesh->mFaces[i];

            for (unsigned int j = 0; j < face.mNumIndices; j++)
            {
               indexes.add(face.mIndices[j]);
            }
         }

         if constexpr (has_tangent<VERTEX>)
         {
            if (!bHasTangentsAndBitangents)
            {


               // Compute tangents from indexed mesh data
               computeTangents(vertexes, indexes);
            }
         }

         // material
         if (!pmaterialOverride)
         {
            if (pmodel->m_strDirectory.case_insensitive_contains("cerberus"))
            {

               information() << "going to load cerberus material?!?";
            }
            else if (pmodel->m_strDirectory.case_insensitive_contains("helmet"))
            {

               information() << "going to load helmet material?!?";
            }
            if (pmodel->m_bExternalPbr)
            {
               // albedo
               if (pmaterial->m_textureaPbr[e_texture_albedo] =
                      ::gpu::model::loadMaterialTexture(pmodel, "albedo.ktx", aiTextureType_DIFFUSE))
               {

                  pmaterial->useTextureAlbedo = true;
               }

               // metallicRoughness (in gltf 2.0 they are combined in one texture)
               if (pmaterial->m_textureaPbr[e_texture_metallic_roughness] =
                      loadMaterialTexture(pmodel, "metallic.ktx", aiTextureType_UNKNOWN))
               {
                  // defined here in assimp
                  // https://github.com/assimp/assimp/blob/master/include/assimp/pbrmaterial.h#L57
                  pmaterial->useTextureMetallicRoughness = true;
               }

               // normal
               if (pmaterial->m_textureaPbr[e_texture_normal] =
                      loadMaterialTexture(pmodel, "normal.ktx", aiTextureType_NORMALS))
               {
                  pmaterial->useTextureNormal = true;
               }

               // ambient occlusion
               if (pmaterial->m_textureaPbr[e_texture_ambient_occlusion] =
                      loadMaterialTexture(pmodel, "ao.ktx", aiTextureType_LIGHTMAP))
               {
                  pmaterial->useTextureAmbientOcclusion = true;
               }

               // emissive
               if (pmaterial->m_textureaPbr[e_texture_emissive] =
                      loadMaterialTexture(pmodel, "emissive.ktx", aiTextureType_EMISSIVE))
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
                        // std::cout << "Alpha Mode: BLEND" << std::endl;
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
                  auto ptextureAlbedo = ::gpu::model::loadMaterialTexture(pmodel,aiMaterial, aiTextureType_DIFFUSE);
                  pmaterial->m_textureaPbr[e_texture_albedo] = ptextureAlbedo;
               }

               // metallicRoughness (in gltf 2.0 they are combined in one texture)
               if (aiMaterial->GetTextureCount(aiTextureType_UNKNOWN))
               {
                  // defined here in assimp
                  // https://github.com/assimp/assimp/blob/master/include/assimp/pbrmaterial.h#L57
                  pmaterial->useTextureMetallicRoughness = true;
                  pmaterial->m_textureaPbr[e_texture_metallic_roughness] =
                     ::gpu::model::loadMaterialTexture(pmodel, aiMaterial, aiTextureType_UNKNOWN);
               }

               // normal
               if (aiMaterial->GetTextureCount(aiTextureType_NORMALS))
               {
                  pmaterial->useTextureNormal = true;
                  pmaterial->m_textureaPbr[e_texture_normal] =
                     ::gpu::model::loadMaterialTexture(pmodel, aiMaterial, aiTextureType_NORMALS);
               }

               // ambient occlusion
               if (aiMaterial->GetTextureCount(aiTextureType_LIGHTMAP))
               {
                  pmaterial->useTextureAmbientOcclusion = true;
                  pmaterial->m_textureaPbr[e_texture_ambient_occlusion] =
                     ::gpu::model::loadMaterialTexture(pmodel, aiMaterial, aiTextureType_LIGHTMAP);
               }

               // emissive
               if (aiMaterial->GetTextureCount(aiTextureType_EMISSIVE))
               {
                  pmaterial->useTextureEmissive = true;
                  pmaterial->m_textureaPbr[e_texture_emissive] =
                     ::gpu::model::loadMaterialTexture(pmodel, aiMaterial, aiTextureType_EMISSIVE);
               }

               aiColor4D assimpcolor;
               if (AI_SUCCESS == aiMaterial->Get(AI_MATKEY_BASE_COLOR, assimpcolor))
               {
                  pmaterial->m_seq3Albedo.red = assimpcolor.r;
                  pmaterial->m_seq3Albedo.green = assimpcolor.g;
                  pmaterial->m_seq3Albedo.blue = assimpcolor.b;
                  // pmaterial->m_seq3Albedo. = assimpcolor.r;
               }

               // if (aiMaterial->Get())
            }
         }

         //auto pmesh = øcreate<::gpu::model::mesh>();

         //pmesh->m_pgpucontext = m_pgpucontext;

         //pmesh->m_modeldata = ::transfer(modeldata);

         //pmesh->initialize_gpu_gltf_mesh(pmaterial);

         //return pmesh;
      }


      //::gpu::texture * loadMaterialTexture(const ::scoped_string & scopedstr, aiTextureType type)
      //{

      //   return nullptr;

      //}


      //         // recursively load all meshes in the node tree
      //void processNode(::gpu::model::model * pmode, aiNode * node, const aiScene * scene)
      //{



      //}


      //// convert assimp mesh to our own mesh class
      //::pointer<::gpu::model::mesh> processMesh(aiMesh *mesh, const aiScene *scene);

      //                              // loads the first texture of given type
      //::pointer<::gpu::texture >loadMaterialTexture(aiMaterial * material, bool bSrgb)
      //{


      //}

      
      inline ::gpu::texture * loadMaterialTexture(
         ::gpu::model::model * pmodel, 
         const ::scoped_string & scopedstr,
         aiTextureType etexturetype) 
      {
      
         bool bSrgb = etexturetype == aiTextureType_DIFFUSE;

         return pmodel->loadMaterialTexture(scopedstr, bSrgb);
      
      }

            // loads the first texture of given type
      ::gpu::texture *loadMaterialTexture(
         ::gpu::model::model *pmodel, 
         aiMaterial *material, aiTextureType type)
      {

         aiString path;

         material->GetTexture(type, 0, &path);

         auto ptexture = loadMaterialTexture(pmodel, path.C_Str(), type);

         return ptexture;

      }



   } //namespace model


} // namespace gpu
