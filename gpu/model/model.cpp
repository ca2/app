// From github:/tristancalderbank/OpenGL-PBR-Renderer/model.cpp by
// camilo on 2025-09-26 18:14 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "model.h"
#include "bred/gltf/vertex.h"
#include "bred/gpu/texture.h"
#include <stb/stb_image.h>
#include "assimp_iosystem.h"
#include "bred/gpu/context.h"
#include "_assimp.h"
#include "__assimp.h"

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


   namespace model
   {


      model::model()
      {


         m_emodel = ::gpu::e_model_none;

      }


      model::~model()
      {


      }


      ::gpu::texture *model::get_target_texture() 
      {
      
         return m_mapTexture.first().element2();
      
      }


      void model::initialize_gpu_model(::gpu::context *pgpucontext, const ::gpu::renderable_t &model)
      {

         initialize_gpu_context_object(pgpucontext);

         bool bFlipTexturesVertically = false;

         load_model(model.m_pathRenderable, model.m_egpumodel, 
            bFlipTexturesVertically,
            model.m_bExternalPbr);

      }


      void model::initialize_gpu_model(::gpu::context *pgpucontext, ::gpu::enum_model egpumodel,
                                       const ::file::path &path, bool flipTexturesVertically, bool bExternalPbr)
      {

         initialize_gpu_context_object(pgpucontext);

         load_model(path, egpumodel, flipTexturesVertically, bExternalPbr);

      }


      void model::initialize_gpu_model(::gpu::context * pgpucontext,  
         const ::file::path & path,
         ::gpu::enum_model egpumodel,
         ::gpu::model::material *pmaterial,
         bool flipTexturesVertically, bool bExternalPbr)
      {

         initialize_gpu_context_object(pgpucontext);
         m_pmaterialOverride = pmaterial;
         load_model(path, egpumodel, flipTexturesVertically, bExternalPbr);
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


      void model::load_model(const ::file::path & path, ::gpu::enum_model egpumodel, bool flipTexturesVertically, bool bExternalPbr)
      {

         {

            m_bExternalPbr = bExternalPbr;

            m_egpumodel = egpumodel;

            stbi_set_flip_vertically_on_load(flipTexturesVertically);
            //importer.SetIOHandler(get_assimp_iosystem());
            //When this flag appears
//
//You will see aiPrimitiveType_NGONEncodingFlag when :
//
//                The model has concave n -
//                gons
//
//                   The model has non -
//                planar faces
//
//                   The exporter wrote malformed polygons
//
//                      You used aiProcess_Triangulate but Assimp could not safely triangulate all faces
//
//                         So triangulation was partial,
//               not complete.
            unsigned int nFlags = 0;


            //nFlags = aiProcess_Triangulate | aiProcess_SortByPType | aiProcess_JoinIdenticalVertices;


            //nFlags = aiProcess_Triangulate | aiProcess_SortByPType | aiProcess_GenNormals | aiProcess_CalcTangentSpace;
            const aiScene *scene =
               // get_assimp_importer()->ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs |
               // aiProcess_CalcTangentSpace);
//                              get_assimp_importer()->ReadFile(path,
  //                                                          aiProcess_Triangulate | aiProcess_FlipUVs);
               //get_assimp_importer()->ReadFile(path, aiProcess_Triangulate);
               get_assimp_importer()->ReadFile(path, nFlags);

            if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
            {
               error() << "Error loading model: " << get_assimp_importer()->GetErrorString();
               stbi_set_flip_vertically_on_load(true);
               return;
            }

            m_strDirectory = path.folder();

            processNode(this, scene->mRootNode, scene);
            stbi_set_flip_vertically_on_load(true);
         }

      }





      //// loads the first texture of given type
      //::gpu::texture * model::loadMaterialTexture(aiMaterial *material, aiTextureType type)
      //{

      //   aiString path;

      //   material->GetTexture(type, 0, &path);

      //   auto ptexture = loadMaterialTexture(path.C_Str(), type);

      //   return ptexture;

      //}


      // loads the first texture of given type
      ::gpu::texture *model::loadMaterialTexture(const ::scoped_string &scopedstr, bool bSrgb)
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
            ptexture = m_pgpucontext->generic_texture(pathImage, bSrgb);
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


   } // namespace model


} // namespaceg gpu
