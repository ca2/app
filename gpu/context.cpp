// From gpu_opengl/context.h by camilo on 2025-09-28 12:00 <3ThomasBorregaardSorensen!!
#include "framework.h"
#define STB_USE_HUNTER
#include "context.h"
#include "bred/gpu/device.h"
//#include "frame_buffer.h"
#include "model/model.h"
#include "bred/gltf/vertex.h"
//#include "ibl/brdf_convolution_framebuffer.h"
#include "ibl/equirectangular_cubemap.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "aura/graphics/image/image.h"
#include "bred/gpu/command_buffer.h"
#include "bred/gpu/context_lock.h"
#include "bred/gpu/frame.h"
#include "bred/gpu/layer.h"
#include "bred/gpu/texture.h"
#include "bred/gpu/types.h"
#include "bred/graphics3d/engine.h"
#include "bred/graphics3d/immersion_layer.h"
#include "bred/graphics3d/scene_base.h"
//#include "ibl/cubemap_framebuffer.h"
#include "ibl/diffuse_irradiance_map.h"
#include "ibl/equirectangular_cubemap.h"
//#include "ibl/mipmap_cubemap_framebuffer.h"
#include "ibl/specular_map.h"
#include <ktx.h>
#include <stb/stb_image.h>


namespace gpu_gpu
{



   context::context()
   {

      m_estatus = error_not_initialized;

      
   }


   context::~context()
   {

   }

     
   ::pointer<::gpu::texture> context::cubemap_from_hdr(const ::file::path &pathHdr)
   {

      auto memory = file()->as_memory(pathHdr);

      return cubemap_from_hdr_on_memory(memory);

   }


   ::pointer<::gpu::texture> context::cubemap_from_hdr_on_memory(const ::block & block)
   {

      ::pointer<::gpu::texture> pgputexture;
        
      {

         m_pcommandbufferMain = beginSingleTimeCommands(m_pgpudevice->graphics_queue());

         // Pre-compute IBL stuff
         auto piblequirectangularcubemap = øcreate<::gpu::ibl::equirectangular_cubemap>();

         piblequirectangularcubemap->initialize_equirectangular_cubemap_with_hdr_on_memory(this, block);

                  pgputexture = piblequirectangularcubemap->m_ptextureCubemap;
         pgputexture->m_bHdr = true;
                  {



                     //{

                     //   //auto piblspecularmap = ibl_specular_map();

                     //   // if (!piblspecularmap->m_pframebufferPrefilteredEnvMap)
                     //   {
                     // this->flushCommandBuffer(layoutCmd, m_vkqueueTransfer3, true);

                     {
                        start_debug_happening(m_pcommandbufferMain, "compute equirectangular cubemap");
                        piblequirectangularcubemap->compute_equirectangular_cubemap(m_pcommandbufferMain);
                        end_debug_happening(m_pcommandbufferMain);
                     }
                     endSingleTimeCommands(m_pcommandbufferMain);

                     m_pcommandbufferMain.release();
                     //}

                     // return piblspecularmap->m_ptexturePrefilteredEnvMapCubemap;
                     //->compute();
                     //}
                  }

      }

      return pgputexture;

   }


   void context::load_ktxTexture(::gpu::texture * pgputexture, void * p_ktxTexture)
   {

      throw ::interface_only();

   }


   
      ::pointer<::gpu::texture>context::load_cube_map(const ::scoped_string &scopedstrName, const ::file::path &path,
                                                   bool b32)
   {
   
         auto ptexture = øcreate<::gpu::texture>();
   
         ptexture->m_pgpurenderer = m_pgpurenderer;

         ptexture->m_textureflags.m_bShaderResource = true;

         auto memory = file()->as_memory(path);

         //         ::string relativePath = fileName;
         //       ::string path = directory + '/' + relativePath;

         auto inputData = memory.data();

         auto inputSize = memory.size();
   
         try
         {
   
            if (path.case_insensitive_ends(".ktx"))
            {
   
         // Create ktxTexture from memory
               ktxTexture *kTexture = nullptr;
               KTX_error_code result =
                  ktxTexture_CreateFromMemory(inputData, inputSize, KTX_TEXTURE_CREATE_LOAD_IMAGE_DATA_BIT, &kTexture);

               if (result != KTX_SUCCESS)
               {
                  warning() << "Failed to load KTX from memory\n";
                  return {};
               }
               ktxTexture1 *tex1 = (ktxTexture1 *)kTexture;
               information() << "Width=" << kTexture->baseWidth << " Height=" << kTexture->baseHeight
                             << " Levels=" << kTexture->numLevels << " glInternalFormat=" << tex1->glInternalformat
                             << "\n";

               load_ktxTexture_cube_map(ptexture, kTexture);

               // Cleanup ktx object (OpenGL texture stays alive)
               ktxTexture_Destroy(kTexture);

            }
            else if (path.case_insensitive_ends(".hdr"))
            {
   
               try
               {
   
                  auto ptexture = cubemap_from_hdr(path);
                  return ptexture;
               }
               catch (const ::exception &e)
               {
   
                  throw ::exception(e.m_estatus,
                                    "Failed to load HDR cubemap '" + scopedstrName + "': " + e.get_message());
               }
            }
            else
            {
   
               warning() << "not implemented loadCubemap case";
            }
         }
         catch (const ::exception &e)
         {
   
            throw ::exception(e.m_estatus, "Failed to load HDR cubemap '" + scopedstrName + "': " + e.get_message());
         }
   
         return ptexture;

      }



   void context::load_generic_texture(::pointer<::gpu::texture> &ptexture, const ::file::path &path,
                                      bool bSrgb)
   {

      ødefer_construct(ptexture);

      ptexture->m_textureflags.m_bShaderResource = true;

      auto memory = file()->as_memory(path);

      //         ::string relativePath = fileName;
      //       ::string path = directory + '/' + relativePath;

      auto inputData = memory.data();

      auto inputSize = memory.size();


      if (path.case_insensitive_ends(".hdr"))
      {
      }
      else if (path.case_insensitive_ends(".ktx"))
      {

         load_ktx_texture_from_file_path(ptexture, path);

         return;

      }
      else
      {
         int width, height, numChannels;
         
         //stbi_set_flip_vertically_on_load(true);

         unsigned char *data = stbi_load_from_memory(inputData, inputSize, &width, &height, &numChannels, 0);

         //stbi_set_flip_vertically_on_load(false);

         if (!data)
         {
            information() << "Failed to load texture data";
            stbi_image_free(data);

            return;
         }

         //GLenum format;

         //switch (numChannels)
         //{
         //   case 1:
         //      format = DXGI_FORMAT_R8_UNORM;
         //      break;
         //   case 3:
         //      format = DXGI_FORMAT_B8G8R8_UNORM;
         //      break;
         //   case 4:
         //      format = DXGI_FORMAT_B8G8R8A8_UNORM;
         //      break;
         //}

         //GLenum internalFormat = format;

         //
         //bool bSrgb = false;
         //// account for sRGB textures here
         ////
         //// diffuse textures are in sRGB space (non-linear)
         //// metallic/roughness/normals are usually in linear
         //// AO depends
         //if (iAssimpTextureType == aiTextureType_DIFFUSE)
         //{
         //   bSrgb = true;
         ////   //if (numChannels == 3)
         ////   //{
         ////   //   internalFormat = GL_SRGB;
         ////   //   bSrgb
         ////   //}
         ////   //else if (internalFormat == GL_RGBA)
         ////   //{
         ////   //   internalFormat = GL_SRGB_ALPHA;
         ////   //}
         //}

         ::int_rectangle rectangleTarget(0, 0, width, height);
         ptexture->initialize_with_image_data(m_pgpurenderer, rectangleTarget, numChannels, bSrgb, data);
         //glGenTextures(1, &textureId);
         //glBindTexture(GL_TEXTURE_2D, textureId);
         //glTarget = GL_TEXTURE_2D;
         //// generate the texture
         //glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, data);
         //glGenerateMipmap(GL_TEXTURE_2D);

         //// texture wrapping/filtering options
         //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
         //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
         //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // image is resized using bilinear filtering
         //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // image is enlarged using bilinear filtering

         // free the image data
         stbi_image_free(data);
      }

      //::cast<::gpu_opengl::texture> popengltexture = ptexture;
      ptexture->m_path = path;
   }

   
   ::pointer<::graphics3d::renderable> context::_load_model(const ::gpu::renderable_t &model)
   {

      // if (auto it = m_mapgltfModel.find(name); it != m_mapgltfModel.end())
      //  return it->element2();

      ::gpu::context_lock contextlock(this);

      ::pointer<::graphics3d::renderable> prenderable;

      //if (model.m_ecoordinatesystem)

      auto pmodel = øcreate<::gpu::model::model>();

      (*(::gpu::renderable_t *)pmodel) = model;

      //::cast<::gpu_opvulkan::queue> pqueueGraphics = graphics_queue();

      // pmodel->loadFromFile(model.m_path.c_str(), this, pqueueGraphics->m_vkqueue, model.m_iFlags, model.m_fScale);

      pmodel->initialize_gpu_model(
         this, 
         model.m_egpumodel,
         model.m_pathRenderable, 
         false,
         model.m_bExternalPbr);

      // m_mapgltfModel[name] = model;
      return pmodel;
   }


   void context::load_ktxTexture_cube_map(::gpu::texture * pgputexture, void * p_ktxTexture)
   {

      throw ::interface_only();

   }


   void context::load_ktx_texture_from_file_path(::gpu::texture * ptexture, const ::file::path & pathImage)
   {

      ptexture->m_textureflags.m_bShaderResource = true;

      auto memory = file()->as_memory(pathImage);

      //         ::string relativePath = fileName;
      //       ::string path = directory + '/' + relativePath;

      auto data = memory.data();

      auto size = memory.size();

      load_ktx_texture_from_memory(ptexture, data, size);

   }


   void context::load_ktx_texture_from_memory(::gpu::texture * ptexture, const void * data, memsize size)
   {

      // Create ktxTexture from memory
      ktxTexture *kTexture = nullptr;
      KTX_error_code result =
         ktxTexture_CreateFromMemory((const ktx_uint8_t *) data, size, KTX_TEXTURE_CREATE_LOAD_IMAGE_DATA_BIT, &kTexture);

      if (result != KTX_SUCCESS)
      {
         warning() << "Failed to load KTX from memory\n";
         return;
      }
      ktxTexture1 *tex1 = (ktxTexture1 *)kTexture;
      try
      {
         information() << "Width=" << kTexture->baseWidth << " Height=" << kTexture->baseHeight
                       << " Levels=" << kTexture->numLevels << " glInternalFormat=" << tex1->glInternalformat << "\n";

         load_ktxTexture(ptexture, kTexture);
      }
      catch (...)
      {


      }

      // Cleanup ktx object (OpenGL texture stays alive)
      ktxTexture_Destroy(kTexture);


   }



} // namespace gpu_gpu
