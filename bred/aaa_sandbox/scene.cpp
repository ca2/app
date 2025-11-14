//
// From V0idsEmbrace.graphics3d by camilo on 2025-08-21 19:08 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "scene.h"


namespace graphics3d
{



   //using json = nlohmann::json;

   scene::scene()
   {

      m_strSkyboxCubemapName = "skybox_hdr";
      m_interlockedcountSceneObject = 1;

   }


   scene::~scene()
   {


   }


   void scene::initialize_scene(::graphics3d::IWindowInput * pwindowinput, ::graphics3d::IAssetProvider * passetmanager)
   {

      m_pwindowinput = pwindowinput;
      m_passetmanager = passetmanager;

   }


   void scene::init()
   {

      auto pplayer = øcreate_new<player>();

      pplayer->initialize_sandbox_player(m_pwindowinput);

      pplayer->transform().translation = m_initialCameraPosition;
      pplayer->transform().rotation = m_initialCameraRotation;
      pplayer->onInit();

      m_playera.add(pplayer);

   }




   ::gpu::properties & scene::global_ubo()
   {

      return m_gpupropertiesGlobalUbo;
   }


   void scene::setSkyboxObject(::graphics3d::scene_object * pobject)
   {
      m_iSkyboxId = pobject->getId();
      m_psceneobjectSkybox = pobject;
   }


   ::string scene::getSkyboxCubemapName()
   {

      return m_strSkyboxCubemapName;

   }


   void scene::update(float dt)
   {

      for (auto& player : m_playera)
      {

         player->on_update(dt);

      }

      for (auto& [id, pobject] : m_mapSceneObject)
      {

         pobject->on_update(dt);

      }

   }


   void scene::loadSceneFile(const ::scoped_string& fileName)
   {

      ::file::path path = "matter://scenes/" + fileName + ".json";

      auto sceneJson = file()->as_network_payload(path);
      //if (!inFile.is_open()) {
      //   throw std::runtime_error("Could not open scene file: " + path);
      //}

      //json sceneJson;
      //inFile >> sceneJson;


      // Parse skybox cubemap name (if present)
      if (sceneJson.property_reference().has_property("skybox"))
      {
         m_strSkyboxCubemapName = sceneJson["skybox"].as_string();
         information("Scene specifies skybox: '{}'", m_strSkyboxCubemapName);
      }
      else
      {

         warning("No skybox specified in scene file '{}', using default '{}'", fileName, m_strSkyboxCubemapName);

      }

      information("Loading scene file: {} ({})", fileName, path);

      if (sceneJson.has_property("camera"))
      {

         auto& camJson = sceneJson["camera"].property_set_reference();

         auto pos = camJson.get("position", ::float_array_base{0.f, 0.f, 0.f});
         auto rot = camJson.get("rotation", ::float_array_base{0.f, 0.f, 0.f});

         m_initialCameraPosition = { pos[0], pos[1], pos[2] };
         m_initialCameraRotation = {
             glm::radians(rot[0]),
             glm::radians(rot[1]),
             glm::radians(rot[2])
         };

         information("Camera position: ({}, {}, {}), rotation (deg): ({}, {}, {})",
            pos[0], pos[1], pos[2], rot[0], rot[1], rot[2]);
      }

      auto objects = sceneJson["objects"].payload_array_reference();

      for (auto& item : objects)
      {

         auto & objJson = item.property_set_reference();

         if (objJson.get("special", "") == "lights")
         {
            auto count = objJson.get("count", 1);
            auto radius = objJson.get("radius", 4.8f);
            auto height = objJson.get("height", -2.5f);
            auto intensity = objJson.get("intensity", 15.8f);
            const auto& colorsJson = objJson["colors"];

            for (int i = 0; i < count; ++i) {
               float angle = i * glm::two_pi<float>() / count;
               floating_sequence3 pos = {
                   radius * std::cos(angle),
                   height,
                   radius * std::sin(angle)
               };

               auto colorArray = colorsJson[i % colorsJson.array_get_count()];
               floating_sequence3 color = {
                   colorArray[0],
                   colorArray[1],
                   colorArray[2]
               };

               auto ppointlight = this->makePointLight(intensity, 0.1f, color);
               ppointlight->transform().translation = pos;

               information("Placed point light at ({}, {}, {})", pos.x, pos.y, pos.z);

               m_mapSceneObject.set_at(ppointlight->getId(), std::move(ppointlight));
            }

            continue; // Skip normal parsing for this object
         }


         ::pointer < ::graphics3d::scene_object > psceneobject;

         if (objJson.get_bool("skybox", false)
         {

            psceneobject = createSkyBoxObject();

         }
         else
         {

            psceneobject = this->createSceneObject();

         }


         auto isSkybox =
         gameObject->m_bIsSkybox = isSkybox;


         if (auto it = objJson.find("model"); it)
         {
            const ::string modelName = it->as_string();

            // try OBJ first
            if (auto objModel = m_passetmanager->getOBJModel(modelName)) {
               gameObject->set_model(objModel);
            }
            // then try GLTF
            else if (auto gltfModel = m_passetmanager->getGLTFmodel(modelName)) {
               gameObject->set_model(gltfModel);
            }
            else {
               throw std::runtime_error("Model not found in cache: " + modelName);
            }
         }


         auto pos = objJson.get("position", ::float_array_base{0.f, 0.f, 0.f});
         auto rot = objJson.get("rotation", ::float_array_base{0.f, 0.f, 0.f});
         auto scl = objJson.get("scale", ::float_array_base{1.f, 1.f, 1.f});

         gameObject->transform().translation = { pos[0], pos[1], pos[2] };
         gameObject->transform().rotation = { rot[0], rot[1], rot[2] };
         gameObject->transform().scale = { scl[0], scl[1], scl[2] };

         information("Loaded GameObject '{}' - Pos: ({}, {}, {}), Rot: ({}, {}, {}), Scale: ({}, {}, {})",
            objJson.get("name", "unnamed"),
            pos[0], pos[1], pos[2],
            rot[0], rot[1], rot[2],
            scl[0], scl[1], scl[2]);





         if (objJson.has_property("cubemap")) {

            gameObject->m_cubemapTextureName = objJson["cubemap"].as_string();
         }

         // Store or fallback cubemap texture name on scene-wide variable
         if (isSkybox) {
            if (gameObject->m_cubemapTextureName.has_character())
            {
               m_skyboxCubemapName = gameObject->m_cubemapTextureName;
            }
            setSkyboxObject(gameObject);
            information("GameObject '{}' marked as skybox with cubemap '{}'", objJson.get("name", "unnamed"), m_skyboxCubemapName);
         }

         // Store in map
         m_gameObjects.set_at(gameObject->getId(), gameObject);
      }

      information("Scene '{}' loaded. Total objects: {}", fileName, m_gameObjects.size());
   }

   std::optional<std::reference_wrapper<sandbox_game_object>> scene::getSkyboxObject() {
      if (!m_skyboxId) return std::nullopt;
      auto it = m_gameObjects.find(*m_skyboxId);
      if (it) {
         // cast back from IGameObject→sandbox_game_object
         return std::reference_wrapper(
            static_cast<sandbox_game_object&>(*it->element2()));
      }
      return std::nullopt;
   }

   // Implements the IScene interface:
   std::optional<std::reference_wrapper<IGameObject>>
      scene::getSkyboxObject() const {
      if (!m_skyboxId) {
         return std::nullopt;
      }
      auto it = m_gameObjects.find(*m_skyboxId);
      if (it == m_gameObjects.end()) {
         return std::nullopt;
      }
      // we know it really is a sandbox_game_object, but expose it as IGameObject
      return std::make_optional<std::reference_wrapper<IGameObject>>(
         *it->element2()
      );
   }

   sandbox_camera& scene::getCamera() {
      if (m_players.empty()) {
         throw std::runtime_error("no players available to get camera from");
      }

      auto* player = dynamic_cast<sandbox_player*>(m_players[0].get());
      if (!player) {
         throw std::runtime_error("first player is not a sandbox_player");
      }

      return player->getCamera();
   }

   ::graphics3d::scene_object::map * scene::getGameObjects()
   {
      return m_gameObjects;

   }



   ::pointer<::graphics3d::scene_object> scene::createGameObject()
   {

      auto pgameobject = øcreate_new <game_object >();

      auto idGameObject = m_interlockedcountGameObject++;

      pgameobject->initialize_game_object(idGameObject);

      return pgameobject;

   }



   ::pointer<::graphics3d::scene_object> immersion_layer::makePointLight(float intensity, float radius, floating_sequence3 color)
   {
      auto ppointlight = øallocate ::graphics3d::point_light_scene_object;
      this->add_scene_object(ppointlight);
      ppointlight->m_color = color;
      ppointlight->m_transform.scale.x = radius;
      //gameObj->m_pointLight =
      ppointlight->m_pointLight->lightIntensity = intensity;
      return ppointlight;
   }






      // pass input so your Player can read it
      void scene::initialize_scene(::graphics3d::IWindowInput * input, ::graphics3d::IAssetProvider * passetmanager)
      {



      }


      //void init() override;                 // load models, spawn entities
      //void update(float dt) override;        // advance all entities

      void scene::loadSceneFile(const ::scoped_string& fileName)
   {


   }


      void scene::init()
   {


   }


      void scene::update(float deltaTime)
      {


      }

      ICamera & scene::getCamera()
      {


      }

      ::graphics3d::scene_object_map&  scene::getGameObjects()
      {



      }

      // std::optional<std::reference_wrapper<IGameObject>>
      //     getSkyboxObject() const
      // {
      //     return std::nullopt;
      // }

              IGameObject * scene::getSkyboxObject()
              {

                 return nullptr;
              }

      ::string scene::getSkyboxCubemapName()
      {
return {};

      }


   //m_mapObjects[pobject->m_iId] = pobject;
} // namespace graphics3d



