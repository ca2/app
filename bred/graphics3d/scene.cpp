#include "framework.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "point_light.h"
#include "skybox.h"
#include "bred/gpu/texture.h"
#include "bred/graphics3d/engine.h"
#include "bred/graphics3d/immersion_layer.h"
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

      m_bInitialized = false;
      m_bLoadedScene = false;
      //m_strSkyboxCubemapName = "skybox_hdr";
      m_strSkybox = "skybox_hdr";
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




   void scene::initialize_scene(::graphics3d::immersion_layer * pimmersionlayer)
   {

      m_pimmersionlayer = pimmersionlayer;
      //::graphics3d::scene::initialize_scene(pengine);


      on_initialize_scene();

   }


   void scene::on_initialize_scene()
   {


   }


   void scene::set_sky_box(::graphics3d::skybox *pskybox)
   {
      //m_iSkyboxId = pobject->getId();
      //m_pskyboxCurrent = pskybox ;

   }


   //::string scene::getSkyboxCubemapName()
   //{

   //   return m_strSkyboxCubemapName;

   //}


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


   void scene::load_lights(const ::property_set & setObject)
   {

      
            auto count = setObject.get("count", 1);
      auto radius = setObject.get("radius", 4.8f);
      auto height = setObject.get("height", -2.5f);
      auto intensity = setObject.get("intensity", 15.8f);
      const auto &colorsJson = setObject["colors"];

      for (int i = 0; i < count; ++i)
      {

         float angle = i * glm::two_pi<float>() / count;

         glm::vec3 pos = {radius * std::cos(angle), height, radius * std::sin(angle)};

         auto colorArray = colorsJson[i % colorsJson.array_get_count()];
         auto color = ::argb(1.0f, colorArray[0].as_float(), colorArray[1].as_float(), colorArray[2].as_float());

         auto ppointlight = this->create_point_light(intensity, 0.1f, color);

         ppointlight->transform().m_vec3Position = pos;

         information("Placed point light at ({}, {}, {})", pos.x, pos.y, pos.z);

         // m_mapSceneObject.set_at(ppointlight->m_strName, std::move(ppointlight));
      }


   }


   void scene::load_scene_object(const ::property_set & setObject)
   {

      if (setObject.get("special", "") == "lights")
      {

         load_lights(setObject);

         return;

      }

      auto strName = setObject["name"].as_string();

      auto strModel = setObject["model"].as_string();

      auto strRenderSystem = setObject["renderSystem"].as_string();

      auto erendersystem = as_render_system(strRenderSystem);

      ::pointer<::graphics3d::renderable> prenderable;

      ::pointer<::gpu::texture> ptexture;

      ::pointer<::gpu::texture> ptextureCubemap;

      if (strModel.has_character())
      {

         prenderable = m_pimmersionlayer->m_passetmanager->get_renderable(strModel);

         if (!prenderable)
         {

            return;

            throw ::exception(error_not_found, "Model not found in cache: " + strModel);
         }
      }

      auto strTexture = setObject["texture"].as_string();

      if (strTexture.has_character() && strName.has_character())
      {

         ptexture = m_pimmersionlayer->m_passetmanager->m_mapTexture[strTexture];

         if (ptexture)
         {

            m_pimmersionlayer->m_passetmanager->m_mapObjectTexture[strName] = ptexture;
         }
      }

      // auto strCubemap = setObject["cubemap"].as_string();

      // if (strCubemap.has_character() && strCubemap.has_character())
      //{

      //   ptextureCubemap = m_pimmersionlayer->m_passetmanager->m_mapSkyboxTexture[strCubemap];

      //   if (ptextureCubemap)
      //   {

      //      m_pimmersionlayer->m_passetmanager->m_mapObjectTexture[strName +".cubemap"] = ptexture;

      //   }

      //}

      ::pointer<::graphics3d::scene_object> psceneobject;

      bool bSkybox = setObject["skybox"].is_true();

      if (bSkybox)
      {

         psceneobject = this->create_sky_box();

         m_pskyboxCurrent = psceneobject;

         m_pimmersionlayer->m_passetmanager->m_mapSkybox[strName] = psceneobject;

         ::cast<skybox> pskybox = psceneobject;

         ptextureCubemap = m_pimmersionlayer->m_passetmanager->m_mapSkyboxTexture[strName];

         pskybox->m_ptexture = ptextureCubemap;

         ////pskybox->m_strCubemapTextureName = setObject["cube"].as_string();

         ////::string strModelName = setObject["name"].as_string();

         // psceneobject

         // m_strSkyboxName = strModelName;

         //// Store or fallback cubemap texture name on scene-wide variable
         ////if (isSkybox) {
         // if (pskybox->m_strCubemapTextureName.has_character())
         //{

         //   if (m_strSkyboxCubemapName.is_empty())
         //   {
         //      m_strSkyboxCubemapName = pskybox->m_cubemapTextureName;
         //   }
         //}

         // m_mapSceneObject.set_at(strModelName, psceneobject);

         // set_sky_box(pskybox);

         // information("GameObject '{}' marked as skybox with cubemap '{}'",
         //             strModelName,
         //             pskybox->m_strCubemapTextureName);
      }
      else
      {

         psceneobject = this->create_scene_object();

         psceneobject->m_strName = strName;

         psceneobject->m_strModel = strModel;

         m_mapSceneObject.set_at(strName, psceneobject);
      }

      if (strModel.has_character() && strName.has_character() && strModel != strName)
      {

         auto pobject = m_mapSceneObject[strModel];

         if (pobject)
         {

            m_pimmersionlayer->m_passetmanager->m_mapAliasSceneObject[strName] = pobject;
         }
      }


      //
      //
      // auto isSkybox =
      // gameObject->m_bIsSkybox = isSkybox;

      psceneobject->m_erendersystem = erendersystem;

      psceneobject->set_renderable(prenderable);

      auto pos = setObject.get("position", ::float_array_base{0.f, 0.f, 0.f});
      auto rot = setObject.get("rotation", ::float_array_base{0.f, 0.f, 0.f});
      auto scl = setObject.get("scale", ::float_array_base{1.f, 1.f, 1.f});

      psceneobject->transform().m_vec3Position = {pos[0], pos[1], pos[2]};
      psceneobject->transform().m_vec3Rotation = {rot[0], rot[1], rot[2]};
      psceneobject->transform().m_vec3Scale = {scl[0], scl[1], scl[2]};

      information("Loaded GameObject '{}' - Pos: ({}, {}, {}), Rot: ({}, {}, {}), Scale: ({}, {}, {})",
                  setObject.get("name", "unnamed"), pos[0], pos[1], pos[2], rot[0], rot[1], rot[2], scl[0], scl[1],
                  scl[2]);


      //
      // if (setObject.has_property("cubemap")) {
      //
      //
      // }


      // Store in map


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
      if (sceneJson.has_property("skybox"))
      {
         //m_strSkyboxCubemapName = sceneJson["skybox"].as_string();
         //information("Scene specifies skybox: '{}'", m_strSkyboxCubemapName);
      }
      else
      {

         //warning("No skybox specified in scene file '{}', using default '{}'", fileName, m_strSkyboxCubemapName);

      }

      information("Loading scene file: {} ({})", fileName, path);

      if (sceneJson.has_property("camera"))
      {

         auto &camJson = sceneJson["camera"].property_set_reference();

         m_pimmersionlayer->load_camera(camJson);

         m_bInitialCameraLoaded = true;

      }

      auto objects = sceneJson["objects"].payload_array_reference();

      for (auto &item: objects)
      {

         auto &setObject = item.property_set_reference();

         load_scene_object(setObject);

      }

      if (m_strSkybox.has_character())
      {

         auto pskybox = m_pimmersionlayer->m_passetmanager->m_mapSkybox[m_strSkybox];

         if (pskybox)
         {

            m_pskyboxCurrent = pskybox;

         }

      }


      if (m_bInitialCameraLoaded)
      {

         m_pimmersionlayer->on_initial_camera_load();

      }

      information("Scene '{}' loaded. Total objects: {}", fileName, m_mapSceneObject.size());

   }



   ::graphics3d::skybox *scene::current_sky_box()
   {

      return m_pskyboxCurrent;

      //if (m_pskyboxCurrent)
      //{

      //   m_pskyboxCurrent

      //}

       //if (m_strSkyboxModelName.is_empty())
       //{
      
       //   return nullptr;
      
       //}
       //auto p = m_mapSceneObject.find(m_strSkyboxModelName);
       //if (!p) {

       //   return nullptr;
       //   // cast back from IGameObject→sandbox_game_object
       //   //return std::reference_wrapper(
       //     // static_cast<sandbox_game_object&>(*it->element2()));
       //}
       //return p->element2();
   }
   //::gpu::texture *scene::current_sky_box_texture() 
   //
   //{
   //   if (m_strSkyboxTextureName.is_empty())
   //   {


   //      return nullptr;
   //   }

   //   auto p = m_pimmersionlayer->m_passetmanager->m_mapTexture[m_strSkyboxTextureName];

   //   if (!p)
   //   {

   //      return nullptr;

   //   }

   //   return p;
   //
   //}

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

      if (m_pcameraDefault)
      {

         m_pimmersionlayer->m_pengine->m_transform.m_vec3Position = m_pcameraDefault->position();
         m_pimmersionlayer->m_pengine->m_transform.m_vec3Rotation = m_pcameraDefault->rotation();
      }

   }



   ::graphics3d::camera * scene::get_default_camera()
   {

      return m_pcameraDefault;

   }


   camera  * scene::camera()
   {

      if (m_pcameraCurrent)
      {

         return m_pcameraCurrent;
      }

      auto pimmersion = m_pimmersionlayer;

      if (pimmersion)
      {

         auto pcameraImmersion = pimmersion->camera();

         if (pcameraImmersion)
         {

            return pcameraImmersion;

         }

      }

      auto pcameraScene = scene_camera();

      if (pcameraScene)
      {

         return pcameraScene;

      }

      return nullptr;

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


   class camera * scene::scene_camera()
   {

      if (!m_pcameraScene)
      {

         m_pcameraScene = get_default_camera();

      }

      return m_pcameraScene;

   }


   ::gpu::properties & scene::global_ubo()
   {

      return m_gpupropertiesGlobalUbo;

   }


   ::graphics3d::scene_object & scene::scene_object(const ::scoped_string & scopedstr, const ::file::path & pathParameter)
   {

      auto & psceneobject = this->scene_objects()[scopedstr];

      if (!psceneobject)
      {

         ::file::path path;

         if (pathParameter.has_character())
         {

            path = pathParameter;

         }
         else
         {

            path = scopedstr;

         }

         psceneobject = _scene_object(scopedstr, path);

      }

      return *psceneobject;

   }


   ::pointer < ::graphics3d::scene_object > scene::_scene_object(const ::scoped_string & scopedstr, const ::file::path & path)
   {

      auto pgpucontext = m_pimmersionlayer->m_pengine->gpu_context();

      ::gpu::renderable_t model;

      model.m_strName = scopedstr;

      model.m_path = path;

      if (path.case_insensitive_ends(".obj"))
      {

         model.set_type("obj");

      }

      auto prenderable = pgpucontext->load_model(model);

      auto psceneobject = øcreate < ::graphics3d::scene_object>();

      psceneobject->initialize_scene_object(this);

      psceneobject->m_strRenderablePath = path;

      psceneobject->m_prenderable = prenderable;

      return psceneobject;

   }


   ::graphics3d::scene_object_map & scene::scene_objects()
   {

      return m_mapSceneObject;

   }


   ::pointer<::graphics3d::scene_object> scene::create_scene_object()
   {

      auto pgameobject = øcreate_new<::graphics3d::scene_object>();

      pgameobject->initialize_scene_object(this);

      return pgameobject;

   }


   ::pointer<::graphics3d::skybox> scene::create_sky_box()
   {

      auto pgameobject = øcreate_new<skybox>();

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
      ppointlight->m_transform.m_vec3Scale.x = radius;
      //gameObj->m_pointLight =
      ppointlight->m_fLightIntensity = intensity;
      return ppointlight;
   }


   void scene::defer_load_scene(::gpu::context* pgpucontext)
   {

      _synchronous_lock synchronouslock(this->synchronization());

      if (!m_bInitialized)
      {

         m_bInitialized = true;

         initialize_scene(m_pimmersionlayer);

      }

      if (!m_bLoadedScene)
      {

         on_load_scene(pgpucontext);

         m_bLoadedScene = true;

      }

   }



   void scene::on_load_scene(::gpu::context* pgpucontext)
   {



   }


   void scene::on_update(::gpu::context* pgpucontext)
   {


   }



   void scene::on_render(::gpu::context * pgpucontext)
   {



   }

   //
   // ::pointer < ::graphics3d::renderable> scene::create_tinyobj_renderable(const ::file::path& path)
   // {
   //
   //    auto pmodel = m_pengine->create_tinyobjloader_model(path);
   //
   //    return pmodel;
   //
   // }
   //
   //
   //
   // scene_object * scene::create_tinyobj(const ::file::path& path)
   // {
   //
   //    auto prenderable = create_tinyobj_renderable(path);
   //
   //    auto psceneobject = øcreate < ::graphics3d::scene_object>();
   //
   //    psceneobject->initialize_scene_object(this);
   //
   //    psceneobject->m_strRenderablePath = path;
   //
   //    psceneobject->m_prenderable = prenderable;
   //
   //    m_mapSceneObject.set_at(psceneobject->getId(), psceneobject);
   //
   //    return psceneobject;
   //
   // }

   // ::pointer < ::graphics3d::renderable> scene::create_tinyobj_scene_object(const ::file::path& path)
   // {
   //
   //    auto pengine = m_pengine;
   //
   //    auto pgpucontext = pengine->gpu_context();
   //
   //    auto prenderable = pgpucontext->create_tinyobj_renderable(path);
   //
   //    auto psceneobject = øcreate < ::graphics3d::scene_object>();
   //
   //    psceneobject->initialize_scene_object(this);
   //
   //    psceneobject->m_strRenderablePath = path;
   //
   //    psceneobject->m_prenderable = prenderable;
   //
   //    m_mapSceneObject.set_at(psceneobject->getId(), psceneobject);
   //
   //    return psceneobject;
   //
   // }



} // namespace graphics3d
