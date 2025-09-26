#include "../../../SceneFoundry/graphics3d/framework.h"
// asset_manager.cpp
#include "acme/filesystem/filesystem/file_context.h"
#include "asset_manager.h"
#include <chrono>
//#include "acme/exception/r"
//#include <json.hpp>
////#include <fstream>
////#include <spdlog/spdlog.h>
//#include <glm/glm.hpp>

//using json = nlohmann::json;

namespace graphics3d
{

   // asset_manager::asset_manager(graphics3d::device* pdevice) :
   //    m_pgpudevice(pdevice), m_transferQueue(m_pgpudevice->graphicsQueue()) {
   //
   // }
   asset_manager::asset_manager()
   {

   }


   asset_manager::~asset_manager()
   {

   }


   graphics3d::object_model *asset_manager::getOBJModel(const ::scoped_string &name)
   {
      auto p = m_mapObjectModel.find(name);
      if (!p)
      {
         return nullptr;
      }

      return p->element2();
      //   return (it != m_mapObjectModel.end()) ? it->element2() : nullptr;
   }


   graphics3d::IModel *asset_manager::getGLTFmodel(const ::scoped_string &name)
   {
      auto p = m_mapGltfModel.find(name);
      if (!p)
      {
         return nullptr;
      }

      return p->element2();
      //return (it != m_mapGltfModel.end()) ? it->element2() : nullptr;
   }


   ::gpu::texture *asset_manager::getTexture(const ::scoped_string &name)
   {
      auto p = m_mapTexture.find(name);
      if (!p)
      {
         throw_exception(error_not_found, "Texture not found: " + name);
      }
      return p->element2();
   }


   ::gpu::texture *asset_manager::getTexture(size_t index)
   {
      if (index >= (size_t)m_texturea.size())
      {
         throw_exception(error_index_out_of_bounds);
      }
      return m_texturea[index];
   }


   size_t asset_manager::getTextureIndex(const ::scoped_string &name)
   {
      auto p = m_mapTextureIndex.find(name);
      if (!p)
      {
         throw std::runtime_error("Texture not found in index map: " + name);
      }
      return p->element2();
   }


   const ::pointer_array_base<::gpu::texture> &asset_manager::getAllTextures()
   {
      return m_texturea;
   }


   bool asset_manager::hasTexture(const ::scoped_string &name)
   {
      return m_mapTexture.has(name);
   }


   graphics3d::IModel *asset_manager::getSkyboxModel()
   {
      return m_pmodelSkybox;
   } // make this override if necessary


   ::string_array_base asset_manager::listTextureNames()
   {
      ::string_array_base straKeys;
      //keys.reserve(m_textures.size());
      //keys.m_countAddUp = m_mapTexture.size();
      straKeys =  m_mapTexture.keys();
        // keys.add(n);
      return straKeys;
   }


   void asset_manager::preloadGlobalAssets()
   {
      // Read model & cubemap list JSON
      auto modelJson = file()->as_network_payload("matter://scene_assets/default_scene_assets.json");
      //if (!in.is_open()) {
      //    throw std::runtime_error("Failed to open model list JSON.");
      //}

      //::property_set modelJson;
      //modelJson.parse_network_payload()

      // 1) Load models first (unchanged from your flow)

      auto &payloada = modelJson["models"].payload_array_reference();
      for (const auto &element: payloada)
      {

         auto &entry = element.property_set_reference();
         const ::string name = entry["name"];
         const ::string type = entry.get("type", "obj");
         const ::string path = "matter://models/" + entry["path"].as_file_path();

         try
         {
            if (type == "obj")
            {
               auto model = loadObjModel(name, path, false);
               information("[asset_manager] Successfully loaded OBJ model '{}' from '{}'", name, path);
            }
            else if (type == "gltf")
            {
               uint32_t flags = entry.get("flags", 0); // Optional flags
               float scale = entry.get("scale", 1.0f); // Optional scale
               auto pmodel = loadGLTFmodel(name, path, flags, scale);
               if (entry.get("usage", "") == "skybox" || name == "cube")
               {
                  m_pmodelSkybox = pmodel;
               }
               information("[asset_manager] Successfully loaded glTF model '{}' from '{}'", name, path);
            }
            else
            {
               warning("[asset_manager] Unknown model type '{}' for asset '{}'", type, name);
            }
         }
         catch (const ::exception &e)
         {
            error("[asset_manager] Failed to load model '{}': {}", name, e.get_message());
         }
      }

      // 2) Load cubemaps *before* generating BRDF / irradiance / prefiltered maps
      // Keep track of whether we loaded the environment cubemap used for IBL
      ::pointer<::gpu::texture> loadedEnvironmentCubemap = nullptr;

      auto &payloada2 = modelJson["v"].payload_array_reference();

      for (const auto &element: payloada2)
      {
         auto &entry = element.property_set_reference();
         const ::string name = entry["name"];
         const ::string path = "matter://res/textures/" + entry["path"].as_file_path();

         // Map format string (if present) to VkFormat; default to R32G32B32A32_SFLOAT
         ::string fmtStr = entry.get("format", "VK_FORMAT_R32G32B32A32_SFLOAT");
         // VkFormat format = VK_FORMAT_R32G32B32A32_SFLOAT;
         // if (fmtStr == "VK_FORMAT_R16G16B16A16_SFLOAT") format = VK_FORMAT_R16G16B16A16_SFLOAT;
         // else if (fmtStr == "VK_FORMAT_R32G32B32A32_SFLOAT") format = VK_FORMAT_R32G32B32A32_SFLOAT;
         // Add more mappings here if you expect other formats

         try
         {
            // loadCubemap() must return ::pointer<texture>
            auto cubemap = loadCubemap(
               name,
               path //,
               //format
               // ,
               // VK_IMAGE_USAGE_SAMPLED_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT,
               // VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL
               );

            if (!cubemap)
            {
               error("[asset_manager] loadCubemap returned nullptr for '{}'", name);
               continue;
            }

            // Register into your caches (optional helper)
            registerTextureIfNeeded(name, cubemap, m_textures, m_textureIndexMap, m_textureList);

            information("[asset_manager] Successfully loaded cubemap '{}' from '{}'", name, path);

            // If this cubemap is the environment (skybox_hdr per your JSON), remember it.
            // Use the name you expect in your code / JSON. I see "skybox_hdr" in your example JSON.
            if (name == "skybox_hdr" || entry.get("environment", false))
            {
               // prefer explicit "environment" : true in JSON or name match
               loadedEnvironmentCubemap = cubemap;
            }
         }
         catch (const ::exception &e)
         {
            error("[asset_manager] Failed to load cubemap '{}': {}", name, e.get_message());
         }
      }

      // 3) Create/generate BRDF LUT and IBL assets — ensure environmentCube points to the loaded cubemap
      // If your JSON didn't mark which cubemap is the environment, we fallback to looking up "skybox_hdr"
      if (!loadedEnvironmentCubemap)
      {
         auto it = m_textures.find("skybox_hdr");
         if (it)
         {
            loadedEnvironmentCubemap = it->element2();
         }
      }

      if (!loadedEnvironmentCubemap)
      {
         warning(
            "[asset_manager] No environment cubemap found (expected 'skybox_hdr' or 'environment':true). Using placeholder/empty environmentCube.");
         // Optionally: throw or create a debug 1x1 texture so validation doesn't fail.
         // For now we will not create an invalid shared_ptr (keeps previous behavior safer).
      }
      else
      {
         environmentCube = loadedEnvironmentCubemap;
      }

      // Create BRDF LUT, irradianceCube, prefilteredCube structures (these should allocate their own images)
      // Note: remove any line that reassigns environmentCube to an empty texture (that was the bug)
      lutBrdf = øcreate_pointer<graphics3d::texture>(&m_pgpudevice);
      irradianceCube = øcreate_pointer<graphics3d::texture>(&m_pgpudevice);
      prefilteredCube = øcreate_pointer<graphics3d::texture>(&m_pgpudevice);

      // Generate BRDF LUT first (your existing function)
      generateBRDFlut();

      // Now generate irradiance and prefiltered maps using environmentCube (must be valid)
      if (!environmentCube)
      {
         error("[asset_manager] environmentCube is null - aborting IBL generation to avoid descriptor errors.");
      }
      else
      {
         try
         {
            generateIrradianceMap();
            generatePrefilteredEnvMap();
            information("[asset_manager] IBL assets generated successfully.");
         }
         catch (const ::exception &e)
         {
            error("[asset_manager] IBL generation failed: {}", e.get_message());
         }
      }

      information("Assets loaded");
   }


   void asset_manager::generatePrefilteredEnvMap()
   {

   }


   ::pointer<sandbox_object_model> asset_manager::loadObjModel(
      const ::scoped_string &name,
      const ::scoped_string &filepath,
      bool isSkybox
      )
   {
      // 1) cache check
      if (auto it = m_mapObjectModel.find(name); it != m_mapObjectModel.end())
         return it->element2();

      // 2) load
      auto model = sandbox_object_model::createModelFromFile(m_pgpudevice, filepath, isSkybox);

      // 3) cache & return
      m_mapObjectModel[name] = model;
      return model;
   }


   ::pointer<gltf::Model> asset_manager::loadGLTFmodel(
      const ::scoped_string &name,
      const ::scoped_string &filepath,
      uint32_t gltfFlags,
      float scale
      )
   {
      if (auto it = m_mapGltfModel.find(name); it != m_mapGltfModel.end())
         return it->element2();

      auto model = øcreate_pointer<gltf::Model>();
      model->loadFromFile(filepath, &m_pgpudevice, m_pgpudevice->graphicsQueue(), gltfFlags, scale);

      m_mapGltfModel[name] = model;
      return model;
   }


   ::pointer<texture> asset_manager::loadCubemap(
      const ::scoped_string &name,
      const ::scoped_string &ktxFilename,
      VkFormat format,
      VkImageUsageFlags usageFlags,
      VkImageLayout initialLayout)
   {
      if (auto it = m_textures.find(name); it != m_textures.end())
         return it->element2();

      auto tex = øcreate_pointer<texture>();
      tex->m_pDevice = &m_pgpudevice;
      try
      {
         tex->KtxLoadCubemapFromFile(
            name,
            ktxFilename,
            format,
            &m_pgpudevice,
            m_pgpudevice->graphicsQueue(),
            usageFlags,
            initialLayout
            );
      }
      catch (const ::exception &e)
      {
         throw std::runtime_error("Failed to load HDR cubemap '" + name + "': " + e.what());
      }

      registerTextureIfNeeded(name, tex, m_textures, m_textureIndexMap, m_textureList);
      return tex;
   }


   void asset_manager::registerTextureIfNeeded(
      const ::scoped_string &name,
      const ::pointer<texture> &tex,
      ::string_map<::pointer<texture>> &textures,
      ::string_map<size_t> &textureIndexMap,
      ::pointer_array_base<texture>> &textureList)
   {
      if (textures.find(name) == textures.end())
      {
         textures[name] = tex;
         m_texture.add(tex);
         textureIndexMap[name] = textureList.size() - 1;
      }
   }


} // namespace graphics3d
