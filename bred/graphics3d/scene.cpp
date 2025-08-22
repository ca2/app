#include "framework.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "point_light.h"
#include "sky_box.h"
#include "bred/graphics3d/engine.h"
#include "bred/graphics3d/scene.h"
#include "bred/prodevian/actor.h"
#include "openssl/ct.h"
///#include "SceneFoundry/scene_foundry/player.h"
//#include "SceneFoundry/sandbox_game/game_object.h"

//#include <json.hpp>


//#include <glm/gtc/constants.hpp>
//#include <spdlog/spdlog.h>

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


   // void scene::initialize_scene(::graphics3d::IWindowInput * pwindowinput, ::graphics3d::IAssetProvider * passetmanager)
   // {
   //
   //    m_pwindowinput = pwindowinput;
   //    m_passetmanager = passetmanager;
   //
   // }


   void scene::initialize_scene(::graphics3d::engine * pengine)
   {

      ::graphics3d::scene::initialize_scene(pengine);

      auto pprodevianactor = øcreate_new<::prodevian::actor>();

      pprodevianactor->initialize_prodevian_actor(this);

      pprodevianactor->transform().m_vec3Translation = m_initialCameraPosition;
      pprodevianactor->transform().m_vec3Rotation = m_initialCameraRotation;
      //pprodevianactor->onInit();

      m_prodevianactora.add(pprodevianactor);

      on_initialize_scene();

   }


   void scene::set_sky_box(::graphics3d::sky_box *pskybox)
   {
      //m_iSkyboxId = pobject->getId();
      m_pskyboxCurrent = pskybox ;

   }


   ::string scene::getSkyboxCubemapName()
   {

      return m_strSkyboxCubemapName;

   }


   void scene::update(float dt)
   {

      for (auto &pprodevianactor: m_prodevianactora)
      {

         pprodevianactor->on_update(dt);

      }

      for (auto &[id, pobject]: m_mapSceneObject)
      {

         pobject->on_update(dt);

      }

   }


   void scene::loadSceneFile(const ::scoped_string &fileName)
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

         auto &camJson = sceneJson["camera"].property_set_reference();

         auto pos = camJson.get("position", ::float_array_base{0.f, 0.f, 0.f});
         auto rot = camJson.get("rotation", ::float_array_base{0.f, 0.f, 0.f});

         m_initialCameraPosition = {pos[0], pos[1], pos[2]};
         m_initialCameraRotation = {
            glm::radians(rot[0]),
            glm::radians(rot[1]),
            glm::radians(rot[2])
         };

         information("Camera position: ({}, {}, {}), rotation (deg): ({}, {}, {})",
                     pos[0], pos[1], pos[2], rot[0], rot[1], rot[2]);
      }

      auto objects = sceneJson["objects"].payload_array_reference();

      for (auto &item: objects)
      {

         auto &objJson = item.property_set_reference();

         if (objJson.get("special", "") == "lights")
         {
            auto count = objJson.get("count", 1);
            auto radius = objJson.get("radius", 4.8f);
            auto height = objJson.get("height", -2.5f);
            auto intensity = objJson.get("intensity", 15.8f);
            const auto &colorsJson = objJson["colors"];

            for (int i = 0; i < count; ++i)
            {
 float angle = i * glm::two_pi<float>() / count;

               glm::vec3 pos = {
                  radius * std::cos(angle),
                  height,
                  radius * std::sin(angle)
               };

               auto colorArray = colorsJson[i % colorsJson.array_get_count()];
               auto color = ::argb(
                  1.0f,
                  colorArray[0].as_float(),
                  colorArray[1].as_float(),
                  colorArray[2].as_float());

               auto ppointlight = this->create_point_light(intensity, 0.1f, color);

               ppointlight->transform().translation = pos;

               information("Placed point light at ({}, {}, {})", pos.x, pos.y, pos.z);

               m_mapSceneObject.set_at(ppointlight->getId(), std::move(ppointlight));

            }

            continue; // Skip normal parsing for this object
         }

         ::string strModelName;

         strModelName = objJson["model"].as_string();

         auto prenderable = m_passetmanager->get_renderable(strModelName);

         if (!prenderable)
         {

            throw ::exception(error_not_found, "Model not found in cache: " + strModelName);

         }

         ::pointer<::graphics3d::scene_object> psceneobject;

         bool bSkybox = objJson["skybox"].is_true();

         if (bSkybox)
         {

            psceneobject = this->create_sky_box();

            ::cast<sky_box> pskybox = psceneobject;

            pskybox->m_strCubemapTextureName = objJson["cubemap"].as_string();

            // Store or fallback cubemap texture name on scene-wide variable
            //if (isSkybox) {
            if (pskybox->m_strCubemapTextureName.has_character())
            {

               if (m_strSkyboxCubemapName.is_empty())
               {
                  m_strSkyboxCubemapName = pskybox->m_cubemapTextureName;
               }
            }

            set_sky_box(pskybox);

            information("GameObject '{}' marked as skybox with cubemap '{}'",
                        strModelName,
                        pskybox->m_strCubemapTextureName);


         }
         else
         {

            psceneobject = this->create_scene_object();

            m_mapSceneObject.set_at(psceneobject->getId(), psceneobject);

         }
         //
         //
         // auto isSkybox =
         // gameObject->m_bIsSkybox = isSkybox;

         psceneobject->set_renderable(prenderable);

         auto pos = objJson.get("position", ::float_array_base{0.f, 0.f, 0.f});
         auto rot = objJson.get("rotation", ::float_array_base{0.f, 0.f, 0.f});
         auto scl = objJson.get("scale", ::float_array_base{1.f, 1.f, 1.f});

         psceneobject->transform().translation = {pos[0], pos[1], pos[2]};
         psceneobject->transform().rotation = {rot[0], rot[1], rot[2]};
         psceneobject->transform().scale = {scl[0], scl[1], scl[2]};

         information("Loaded GameObject '{}' - Pos: ({}, {}, {}), Rot: ({}, {}, {}), Scale: ({}, {}, {})",
                     objJson.get("name", "unnamed"),
                     pos[0], pos[1], pos[2],
                     rot[0], rot[1], rot[2],
                     scl[0], scl[1], scl[2]);


         //
         // if (objJson.has_property("cubemap")) {
         //
         //
         // }


         // Store in map

      }

      information("Scene '{}' loaded. Total objects: {}", fileName, m_mapSceneObject.size());

   }



   ::graphics3d::sky_box *scene::current_sky_box()
   {

      return m_pskyboxCurrent;

      // if (m_iSkyboxId <= 0)
      // {
      //
      //    return nullptr;
      //
      // }
      // auto it = m_gameObjects.find(*m_skyboxId);
      // if (it) {
      //    // cast back from IGameObject→sandbox_game_object
      //    return std::reference_wrapper(
      //       static_cast<sandbox_game_object&>(*it->element2()));
      // }
      // return std::nullopt;
   }
   //
   //
   // // Implements the IScene interface:
   // std::optional<std::reference_wrapper<IGameObject>>
   // scene::getSkyboxObject() const
   // {
   //    if (!m_skyboxId)
   //    {
   //       return std::nullopt;
   //    }
   //    auto it = m_gameObjects.find(*m_skyboxId);
   //    if (it == m_gameObjects.end())
   //    {
   //       return std::nullopt;
   //    }
   //    // we know it really is a sandbox_game_object, but expose it as IGameObject
   //    return std::make_optional<std::reference_wrapper<IGameObject>>(
   //       *it->element2()
   //       );
   // }


   void scene::set_default_camera(::graphics3d::camera * pgpucamera)
   {

      m_pcameraDefault = pgpucamera;

   }



   ::graphics3d::camera * scene::get_default_camera()
   {

      return m_pcameraDefault;

   }


   camera  * scene::camera()
   {

      return m_pcameraCurrent;
      // if (m_p.empty())
      // {
      //    throw std::runtime_error("no players available to get camera from");
      // }
      //
      // auto *player = dynamic_cast<sandbox_player *>(m_players[0].get());
      // if (!player)
      // {
      //    throw std::runtime_error("first player is not a sandbox_player");
      // }
      //
      // return player->getCamera();
   }


   ::gpu::properties & scene::global_ubo()
   {

      return m_gpupropertiesGlobalUbo;

   }


   ::graphics3d::scene_object_map & scene::scene_objects()
   {

      return m_mapSceneObject;

   }


   ::pointer<::graphics3d::scene_object> scene::create_scene_object()
   {

      auto pgameobject = øcreate_new<scene_object>();

      pgameobject->initialize_scene_object(this);

      return pgameobject;

   }


   ::pointer<::graphics3d::sky_box> scene::create_sky_box()
   {

      auto pgameobject = øcreate_new<sky_box>();

      pgameobject->initialize_scene_object(this);

      return pgameobject;

   }



   ::pointer<::graphics3d::point_light> scene::create_point_light(
      float intensity,
      float radius,
      const ::color::color & color)
   {
      auto ppointlight = øallocate ::graphics3d::point_light;
      m_pointlighta.add(ppointlight);
      ppointlight->m_color = color;
      ppointlight->m_transform.scale.x = radius;
      //gameObj->m_pointLight =
      ppointlight->m_fLightIntensity = intensity;
      return ppointlight;
   }

   void scene::on_load_scene(::gpu::context* pgpucontext)
   {



   }


   void scene::on_update_global_ubo(::gpu::context* pgpucontext)
   {


   }



   void scene::on_render(::gpu::context * pgpucontext)
   {



   }


   ::pointer < ::graphics3d::renderable> scene::create_tinyobj_renderable(const ::file::path& path)
   {

      auto pmodel = m_pengine->create_tinyobjloader_model(path);

      return pmodel;

   }



   scene_object * scene::create_tinyobj(const ::file::path& path)
   {

      auto pmodel = create_tinyobjloader_model(path);

      auto pobject = øcreate < ::graphics3d::scene_object>();

      add_object(pobject);

      pobject->m_pmodel = pmodel;

      pobject->m_strPath = path;

      return *pobject;

   }


} // namespace graphics3d
