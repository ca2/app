#pragma once
#include "bred/sandbox/window_input.h"
#include "bred/sandbox/scene.h"
#include "bred/sandbox/entity.h"
#include "SceneFoundry/sandbox_game/player.h"
#include "SceneFoundry/sandbox_engine/asset_manager.h"
#include "SceneFoundry/sandbox_game/game_object.h"
//#include <memory>
//#include <vector>
//////#include <stdexcept>
//#include <fstream>
#include <optional>


namespace sandbox_game
{


	class scene :
		virtual public sandbox::IScene
	{
	public:


	   ::interlocked_count                                         m_interlockedcountSceneObject;


		::pointer<::sandbox::IWindowInput>							      m_pwindowinput;
		::pointer < ::sandbox_engine::asset_manager >				   m_passetmanager;

		         ::pointer_array_base<player>								m_playera;
		::map<unsigned int, ::pointer<::sandbox::ISceneObject>>		m_mapSceneObject;
		glm::vec3													            m_initialCameraPosition{ 0.f };
		glm::vec3													            m_initialCameraRotation{ 0.f };

		int															            m_iSkyboxId = -1;
		::pointer<::sandbox::ISceneObject>							      m_psceneobjectSkybox;
		::string													               m_strSkyboxCubemapName;


		scene();
		~scene() override;

		// pass input so your Player can read it
		void initialize_scene(::sandbox::IWindowInput * input, ::sandbox::IAssetProvider * passetprovider) override;


		void init() override;                 // load models, spawn entities
		void update(float dt) override;        // advance all entities

		void loadSceneFile(const ::scoped_string& fileName);

		::sandbox::scene_object_map & getGameObjects() override ;


		::pair<glm::mat4, glm::mat4> getMainCameraMatrices()const;

		void setSkyboxObject(::sandbox::ISceneObject * pobject);

		camera& getCamera();

		void addGameObject(uint32_t id, ::sandbox::ISceneObject * obj);
		void removeGameObject(uint32_t id);

		::sandbox::IGameObject * getSkyboxObject() override;

		//::sandbox::sandbox_game_object>>
		//	getSkyboxObject();

		::string getSkyboxCubemapName();

	   ::pointer<::sandbox::ISceneObject> create_scene_object();


	   ::pointer<::sandbox::ISceneObject> create_skybox_object();


		::pointer<::sandbox::ISceneObject> create_point_light(float intensity = 10.f, float radius = 0.1f, glm::vec3 color = glm::vec3(1.f));



	};


} // namespace sandbox_game



