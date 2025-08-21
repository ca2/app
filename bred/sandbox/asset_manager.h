#pragma once
//////#include <stdexcept>
//#include <unordered_map>
//#include <memory>
//#include <vector>

#include "SceneFoundry/sandbox_renderer/device.h"
#include "SceneFoundry/sandbox_renderer/object_model.h"
//#include "SceneFoundry/sandbox_renderer/gltf.h"
//#include "SceneFoundry/sandbox_renderer/texture.h"
//#include "SceneFoundry/sandbox_renderer/pipeline.h"

#include "bred/sandbox/asset_provider.h"


namespace sandbox_engine
{


   class asset_manager :
      public ::sandbox::IAssetProvider
   {
   public:

      //::string_map < OBJmodelHandle> m_objModelCache;
      //::string_map < GLTFmodelHandle> m_gltfModelCache;
      ::string_map < ::pointer < ::sandbox_renderer::object_model>>     m_mapObjectModel;
      ::string_map < ::pointer < ::sandbox::IModel>>                    m_mapGltfModel;



      ::string_map < ::pointer<::gpu::texture>>                         m_mapTexture; // name → texture
      ::string_map < size_t>                                            m_mapTextureIndex; // name → index
      ::pointer_array_base<::gpu::texture>                              m_texturea; // index → texture

      ::pointer < sandbox_renderer::device >		                        m_pgpudevice;
      //VkQueue						m_transferQueue;

      // caches
      ::pointer < ::gpu::texture >                                      m_ptextureLuBrdf;
      ::pointer < ::gpu::texture >                                      m_ptextureIrradianceCube;
      ::pointer < ::gpu::texture >                                      m_ptexturePrefilteredCube;
      ::pointer < ::gpu::texture >                                      m_ptextureEnvironmentCube;

      ::pointer < ::sandbox::IModel>                                    m_pmodelSkybox;


      asset_manager();
      ~asset_manager();


      virtual void initialize_asset_manager(sandbox_renderer::device* pdevice);


      void preloadGlobalAssets();
      ::pointer<sandbox_renderer::object_model> loadObjModel(const ::scoped_string& name, const ::scoped_string& filepath, bool isSkybox = false);
      ::pointer<sandbox::IModel> loadGLTFmodel(const ::scoped_string& name, const ::scoped_string& filepath, uint32_t gltfFlags = 0u, float scale = 1.f);
      ::pointer<gpu::texture> loadCubemap(
         const ::scoped_string& name,
         const ::scoped_string& ktxFilename
         // ,
         // VkFormat format,
         // VkImageUsageFlags usageFlags,
         // VkImageLayout initialLayout
      );

      void generateBRDFlut();
      void generateIrradianceMap();
      void generatePrefilteredEnvMap();

      //using OBJmodelHandle = ::pointer<sandbox_renderer::sandbox_object_model>;
      //using GLTFmodelHandle = ::pointer<sandbox_renderer::gltf::Model>;
      //using TextureHandle  = ::pointer<VulkanTexture>;
      //using ShaderHandle = ::pointer<ShaderModule>;

      // VkDescriptorImageInfo getCubemapDescriptor(const ::scoped_string& name) const override {
      //    auto it = m_textures.find(name);
      //    if (it == m_textures.end()) {
      //       throw std::runtime_error("Cubemap not found: " + name);
      //    }
      //    return it->element2()->GetDescriptor();
      // }

      sandbox_renderer::object_model * getOBJModel(const ::scoped_string& name);
      sandbox::IModel * getGLTFmodel(const ::scoped_string& name);
      ::gpu::texture * getTexture(const ::scoped_string& name);
      ::gpu::texture * getTexture(size_t index);
      size_t getTextureIndex(const ::scoped_string& name);
      const ::pointer_array_base<::gpu::texture>& getAllTextures();
      bool hasTexture(const ::scoped_string& name);


      // VkDescriptorImageInfo getBRDFLUTDescriptor()    const override { return lutBrdf->GetDescriptor(); }
      // VkDescriptorImageInfo getIrradianceDescriptor() const override { return irradianceCube->GetDescriptor(); }
      // VkDescriptorImageInfo getPrefilteredDescriptor() const override { return prefilteredCube->GetDescriptor(); }
      //
      // VkDescriptorImageInfo getTextureDescriptor(const ::scoped_string& name) const override {
      //    return getTexture(name)->GetDescriptor();
      // }
      sandbox::IModel * getSkyboxModel(); //const { return m_skyboxModel; }// make this override if necessary

       ::string_array_base listTextureNames() ; // const override {
      //    ::array_base<::string> keys;
      //    keys.reserve(m_textures.size());
      //    for (const auto& [n, _] : m_textures) keys.add(n);
      //    return keys;
      // }

   //private:
      virtual void registerTextureIfNeeded(
         const ::scoped_string& name,
         const ::pointer<gpu::texture>& tex,
         ::string_map< ::pointer<gpu::texture>>& textures,
         ::string_map< size_t>& textureIndexMap,
         ::pointer_array_base<gpu::texture>& textureList);



   };


} // namespace sandbox_engine



