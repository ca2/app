// IScene.h
#pragma once


#include "bred/gpu/properties.h"
//#include <unordered_map>
//#include <memory>
//#include "SceneFoundry/graphics3d/game_object_i.h"
//#include "SceneFoundry/graphics3d/camera_i.h"
//#include "SceneFoundry/graphics3d/renderer_i.h"   // for FrameContext
//#include <optional>
//////#include <stdexcept>
///
///

namespace graphics3d
{

   class scene :
      virtual public ::particle
   {
   public:


      ::gpu::properties m_gpupropertiesGlobalUbo;

      ::interlocked_count                                         m_interlockedcountSceneObject;


      ::pointer<::graphics3d::IWindowInput>							      m_pwindowinput;
      ::pointer < ::sandbox_engine::asset_manager >				   m_passetmanager;

      ::pointer_array_base<player>								m_playera;
      ::map<unsigned int, ::pointer<::graphics3d::scene_object>>		m_mapSceneObject;
      glm::vec3													            m_initialCameraPosition{ 0.f };
      glm::vec3													            m_initialCameraRotation{ 0.f };

      int															            m_iSkyboxId = -1;
      ::pointer<::graphics3d::scene_object>							      m_psceneobjectSkybox;
      ::string													               m_strSkyboxCubemapName;


      scene();
      ~scene() override;

      // pass input so your Player can read it
      void initialize_scene(::graphics3d::IWindowInput * input, ::graphics3d::IAssetProvider * passetprovider) override;


      void init() override;                 // load models, spawn entities
      void update(float dt) override;        // advance all entities

      void loadSceneFile(const ::scoped_string& fileName);

      ::graphics3d::scene_object_map & getGameObjects() override ;


      ::pair<glm::mat4, glm::mat4> getMainCameraMatrices()const;

      void setSkyboxObject(::graphics3d::scene_object * pobject);

      camera& getCamera();

      void addGameObject(uint32_t id, ::graphics3d::scene_object * obj);
      void removeGameObject(uint32_t id);

      ::graphics3d::IGameObject * getSkyboxObject() override;

      //::graphics3d::sandbox_game_object>>
      //	getSkyboxObject();

      ::string getSkyboxCubemapName();

      ::pointer<::graphics3d::scene_object> create_scene_object();


      ::pointer<::graphics3d::scene_object> create_skybox_object();


      ::pointer<::graphics3d::scene_object> create_point_light(float intensity = 10.f, float radius = 0.1f, glm::vec3 color = glm::vec3(1.f));






      ///virtual ~IScene() = default;
      //


      virtual ::gpu::properties &global_ubo();


      // pass input so your Player can read it
      virtual void initialize_scene(::graphics3d::IWindowInput *input, ::graphics3d::IAssetProvider *passetprovider);


      //void init() override;                 // load models, spawn entities
      //void update(float dt) override;        // advance all entities

      virtual void loadSceneFile(const ::scoped_string &fileName);


      virtual void init();


      virtual void update(float deltaTime);


      virtual ICamera &getCamera();


      virtual ::graphics3d::scene_object_map &getGameObjects();


      // virtual std::optional<std::reference_wrapper<IGameObject>>
      //     getSkyboxObject() const
      // {
      //     return std::nullopt;
      // }

      virtual IGameObject *getSkyboxObject();


      virtual ::string getSkyboxCubemapName();
   };


} // namespace graphics3d
