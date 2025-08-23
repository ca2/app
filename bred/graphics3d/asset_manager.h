#pragma once
//////#include <stdexcept>
//#include <unordered_map>
//#include <memory>
//#include <vector>

//#include "SceneFoundry/graphics3d/device.h"
//#include "SceneFoundry/graphics3d/object_model.h"
//#include "SceneFoundry/graphics3d/gltf.h"
//#include "SceneFoundry/graphics3d/texture.h"
//#include "SceneFoundry/graphics3d/pipeline.h"

#include "bred/graphics3d/asset_provider.h"
#include "bred/gpu/model_buffer.h"


namespace graphics3d
{


   class CLASS_DECL_BRED asset_manager :
      public ::particle
   {
   public:

      //::string_map < OBJmodelHandle> m_objModelCache;
      //::string_map < GLTFmodelHandle> m_gltfModelCache;
      ::string_map < ::pointer < ::graphics3d::renderable>>             m_mapRenderable;
      //::string_map < ::pointer < ::graphics3d::renderable>>             m_mapGltf;

      ::pointer < ::gpu::model_buffer >                                 m_pgpumodelbufferSkybox;

      ::string_map < ::pointer<::gpu::texture>>                         m_mapTexture; // name → texture
      ::string_map < size_t>                                            m_mapTextureIndex; // name → index
      ::pointer_array_base<::gpu::texture>                              m_texturea; // index → texture

      ::pointer < graphics3d::engine >		                              m_pengine;
      //VkQueue						m_transferQueue;

      // caches
      ::pointer < ::gpu::texture >                                      m_ptextureLuBrdf;
      ::pointer < ::gpu::texture >                                      m_ptextureIrradianceCube;
      ::pointer < ::gpu::texture >                                      m_ptexturePrefilteredCube;
      ::pointer < ::gpu::texture >                                      m_ptextureEnvironmentCube;

      ::pointer < ::graphics3d::renderable>                             m_prenderableSkybox;


      asset_manager();
      ~asset_manager();


      virtual void initialize_asset_manager(graphics3d::engine* pengine);


      void preloadGlobalAssets();

   // private:
   //
   //
   //    ::pointer<::graphics3d::renderable> æloadObjModel(
   //      const ::scoped_string &name,
   //      const ::scoped_string &filepath,
   //      bool isSkybox
   //      );
   //
   //
   //    ::pointer<::graphics3d::renderable> æloadGLTFmodel(
   //       const ::scoped_string &name,
   //       const ::scoped_string &filepath,
   //       uint32_t gltfFlags,
   //       float scale
   //       );


   //public:

      //::pointer<::graphics3d::renderable> load_model(const ::gpu::load_model_t & loadmodel);

      //::pointer<graphics3d::renderable> load_model(const ::scoped_string& name, const ::scoped_string& filepath, bool isSkybox = false);
      ///::pointer<graphics3d::renderable> loadGLTFmodel(const ::scoped_string& name, const ::scoped_string& filepath, uint32_t gltfFlags = 0u, float scale = 1.f);
      ::pointer<gpu::texture> load_cubemap(
         const ::scoped_string& name,
         const ::scoped_string& ktxFilename
         // ,
         // VkFormat format,
         // VkImageUsageFlags usageFlags,
         // VkImageLayout initialLayout
      );

      virtual void generateBRDFlut();
      virtual void generateIrradianceMap();
      virtual void generatePrefilteredEnvMap();

      //using OBJmodelHandle = ::pointer<graphics3d::sandbox_object_model>;
      //using GLTFmodelHandle = ::pointer<graphics3d::gltf::Model>;
      //using TextureHandle  = ::pointer<VulkanTexture>;
      //using ShaderHandle = ::pointer<ShaderModule>;

      // VkDescriptorImageInfo getCubemapDescriptor(const ::scoped_string& name) const override {
      //    auto it = m_textures.find(name);
      //    if (it == m_textures.end()) {
      //       throw std::runtime_error("Cubemap not found: " + name);
      //    }
      //    return it->element2()->GetDescriptor();
      // }

      graphics3d::renderable * get_renderable(const ::scoped_string& name);
      //graphics3d::renderable * getGLTFmodel(const ::scoped_string& name);
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
      graphics3d::renderable * getSkyboxModel(); //const { return m_skyboxModel; }// make this override if necessary

       ::string_array_base listTextureNames() ; // const override {
      //    ::array_base<::string> keys;
      //    keys.reserve(m_textures.size());
      //    for (const auto& [n, _] : m_textures) keys.add(n);
      //    return keys;
      // }

   //private:
      // virtual void registerTextureIfNeeded(
      //    const ::scoped_string& name,
      //    const ::pointer<gpu::texture>& tex,
      //    ::string_map< ::pointer<gpu::texture>>& textures,
      //    ::string_map< size_t>& textureIndexMap,
      //    ::pointer_array_base<gpu::texture>& textureList);
      //


   };


} // namespace graphics3d



