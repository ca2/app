#include "framework.h"
#include "scene_base.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "asset_manager.h"
#include "bred/gpu/texture.h"
#include "bred/graphics3d/engine.h"
#include "bred/graphics3d/immersion_layer.h"
#include "bred/prodevian/actor.h"
#include "openssl/ct.h"
#include "point_light.h"
#include "skybox.h"

/// #include "SceneFoundry/scene_foundry/player.h"
// #include "SceneFoundry/sandbox_game/game_object.h"

// #include <json.hpp>


// 
// #include <spdlog/spdlog.h>


namespace graphics3d
{


   // using json = nlohmann::json;

   scene_base::scene_base()
   {

      m_bInitialized = false;
      m_bLoadedScene = false;
      // m_strSkyboxCubemapName = "skybox_hdr";
      //m_strSkybox = "skybox_hdr";
      m_interlockedcountSceneObject = 1;
   }


   scene_base::~scene_base() {}


   // void scene_base::initialize_scene(::graphics3d::IWindowInput * pwindowinput, ::graphics3d::IAssetProvider *
   // passetmanager)
   // {
   //
   //    m_pwindowinput = pwindowinput;
   //    m_passetmanager = passetmanager;
   //
   // }


   void scene_base::initialize_scene(::graphics3d::immersion_layer *pimmersionlayer)
   {

      initialize_gpu_context_object(pimmersionlayer->m_pengine->get_gpu_context());

      m_pimmersionlayer = pimmersionlayer;
      //::graphics3d::scene_base::initialize_scene(pengine);

      on_initialize_scene();
   }


   void scene_base::on_initialize_scene() {}


   //::pointer<::graphics3d::renderable> scene_base::get_skybox_cube_model()
   //{

   //   auto pmodelbuffer = øcreate_new<::gpu::model_buffer>();

   //   pmodelbuffer->initialize_gpu_context_object(m_pgpucontext);

   //   ::array_base<floating_sequence3> vertexa = {// positions
   //                                      {-1.0f, 1.0f, -1.0f},  {-1.0f, -1.0f, -1.0f}, {1.0f, -1.0f, -1.0f},
   //                                      {1.0f, -1.0f, -1.0f},  {1.0f, 1.0f, -1.0f},   {-1.0f, 1.0f, -1.0f},

   //                                      {-1.0f, -1.0f, 1.0f},  {-1.0f, -1.0f, -1.0f}, {-1.0f, 1.0f, -1.0f},
   //                                      {-1.0f, 1.0f, -1.0f},  {-1.0f, 1.0f, 1.0f},   {-1.0f, -1.0f, 1.0f},

   //                                      {1.0f, -1.0f, -1.0f},  {1.0f, -1.0f, 1.0f},   {1.0f, 1.0f, 1.0f},
   //                                      {1.0f, 1.0f, 1.0f},    {1.0f, 1.0f, -1.0f},   {1.0f, -1.0f, -1.0f},

   //                                      {-1.0f, -1.0f, 1.0f},  {-1.0f, 1.0f, 1.0f},   {1.0f, 1.0f, 1.0f},
   //                                      {1.0f, 1.0f, 1.0f},    {1.0f, -1.0f, 1.0f},   {-1.0f, -1.0f, 1.0f},

   //                                      {-1.0f, 1.0f, -1.0f},  {1.0f, 1.0f, -1.0f},   {1.0f, 1.0f, 1.0f},
   //                                      {1.0f, 1.0f, 1.0f},    {-1.0f, 1.0f, 1.0f},   {-1.0f, 1.0f, -1.0f},

   //                                      {-1.0f, -1.0f, -1.0f}, {-1.0f, -1.0f, 1.0f},  {1.0f, -1.0f, -1.0f},
   //                                      {1.0f, -1.0f, -1.0f},  {-1.0f, -1.0f, 1.0f},  {1.0f, -1.0f, 1.0f}};

   //   pmodelbuffer->static_initialize_vertexes<::floating_sequence3>(vertexa);

   //   return pmodelbuffer;
   //}


   //   ::pointer<::graphics3d::renderable> scene_base::get_cube_model()
   //{

   //   auto pcube = øcreate<::gpu::cube>();

   //
   //   return pcube;
   //}


   //::pointer<::graphics3d::renderable> scene_base::get_skybox_cube_model() { return m_prenderableSkyboxModel; }


   //::pointer<::gpu::texture> scene_base::get_skybox_cube_texture()
   //{

   //   return m_pimmersionlayer->m_passetmanager->m_mapSkyboxTexture[this->m_strSkybox];

   //}


   void scene_base::set_skybox(::graphics3d::skybox *pskybox)
   {
      // m_iSkyboxId = pobject->getId();
      // m_pskyboxCurrent = pskybox ;

      if (m_pskyboxCurrent2 != pskybox)
      {
         
         m_pskyboxCurrent2 = pskybox;

         generateIbl();

      }

   }


   ::graphics3d::skybox *scene_base::current_skybox()
   {

      //if (!m_pskyboxCurrent2 || m_pskyboxCurrent2->m_prenderable != get_skybox_cube_model() ||
      //    m_pskyboxCurrent2->m_ptexture != get_skybox_cube_texture())
      //{

      //   ødefer_construct_new(m_pskyboxCurrent2);

      //   m_pskyboxCurrent2->m_prenderable = get_skybox_cube_model();

      //   m_pskyboxCurrent2->m_ptexture = get_skybox_cube_texture();
      //}

      return m_pskyboxCurrent2;
   }


   //::string scene_base::getSkyboxCubemapName()
   //{

   //   return m_strSkyboxCubemapName;

   //}


   void scene_base::update(float dt)
   {

      for (auto &pprodevianactor: m_prodevianactora)
      {

         pprodevianactor->on_update(dt);
      }

      for (auto &[id, pscenerenderable]: m_mapSceneRenderable)
      {

         pscenerenderable->on_update(dt);
      }
   }


   void scene_base::load_lights(const ::property_set &setObject)
   {


      auto count = setObject.get("count", 1);
      auto radius = setObject.get("radius", 4.8f);
      auto height = setObject.get("height", -2.5f);
      auto intensity = setObject.get("intensity", 15.8f);
      const auto &colorsJson = setObject["colors"];

      for (int i = 0; i < count; ++i)
      {

         float angle = i * _2πf / count;

         floating_sequence3 pos = {radius * std::cos(angle), height, radius * std::sin(angle)};

         auto colorArray = colorsJson[i % colorsJson.array_get_count()];
         auto color = ::argb(1.0f, colorArray[0].as_float(), colorArray[1].as_float(), colorArray[2].as_float());

         auto ppointlight = this->create_point_light(intensity, 0.1f, color);

         ppointlight->transform().m_sequence3Position = pos;

         informationf("Placed point light at (%0.2f, %0.2f,%0.2f)", pos.x, pos.y, pos.z);

         // m_mapSceneObject.set_at(ppointlight->m_strName, std::move(ppointlight));
      }
   }


   void scene_base::load_scene_renderable(const ::property_set &setObject)
   {

      if (setObject.get("special", "") == "lights")
      {

         load_lights(setObject);

         return;
      }

      auto strName = setObject["name"].as_string();

      auto strModel = setObject["model"].as_string();

      auto strRenderSystem = setObject["renderSystem"].as_string();

      auto erendersystem = ::graphics3d::as_render_system(strRenderSystem);

      ::pointer<::graphics3d::renderable> prenderable;

      ::pointer<::gpu::texture> ptexture;

      ::pointer<::gpu::texture> ptextureCubemap;

      if (strModel.has_character())
      {

         prenderable = m_pimmersionlayer->m_passetmanager->get_renderable(strModel);

         if (!prenderable)
         {

         prenderable = m_pimmersionlayer->m_passetmanager->m_mapSkyboxRenderableModel[strModel];

            if (!prenderable)
         {

               return;

            throw ::exception(error_not_found, "Model not found in cache: " + strModel);
         }
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

      ::pointer<::graphics3d::scene_renderable> pscenerenderable;

      bool bSkybox = setObject["skybox"].is_true();

      if (bSkybox)
      {

         auto pskybox = this->create_sky_box();

         pscenerenderable = pskybox;

         //m_pskyboxCurrent = pscenerenderable;

         //m_pimmersionlayer->m_passetmanager->m_mapSkybox[strName] = pscenerenderable;

         //::cast<::graphics3d::skybox> pskybox = pscenerenderable;

         ptextureCubemap = m_pimmersionlayer->m_passetmanager->m_mapSkyboxTexture[strName];

         pskybox->m_prenderable = prenderable;

         pskybox->m_ptexture = ptextureCubemap;

         ////pskybox->m_strCubemapTextureName = setObject["cube"].as_string();

         ////::string strModelName = setObject["name"].as_string();

         // psceneobject

         if (m_strSkybox.is_empty())
         {

            m_strSkybox = strName;
         }

         m_mapSkybox[strName] = pskybox;
         //// Store or fallback cubemap texture name on scene_base-wide variable
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

         pscenerenderable = this->create_scene_renderable();

         pscenerenderable->m_strName = strName;

         pscenerenderable->m_strModel = strModel;

         m_mapSceneRenderable.set_at(strName, pscenerenderable);
      }

      if (strModel.has_character() && strName.has_character() && strModel != strName)
      {

         auto pscenerenderable = m_mapSceneRenderable[strModel];

         if (pscenerenderable)
         {

            m_pimmersionlayer->m_passetmanager->m_mapAliasSceneRenderable[strName] = pscenerenderable;
         }
      }


      //
      //
      // auto isSkybox =
      // gameObject->m_bIsSkybox = isSkybox;

      pscenerenderable->m_erendersystem = erendersystem;

      pscenerenderable->set_renderable(prenderable);

      auto pos = setObject.get("position", ::float_array_base{0.f, 0.f, 0.f});
      auto rot = setObject.get("rotation", ::float_array_base{0.f, 0.f, 0.f});
      auto scl = setObject.get("scale", ::float_array_base{1.f, 1.f, 1.f});

      pscenerenderable->transform().m_sequence3Position = {pos[0], pos[1], pos[2]};
      pscenerenderable->transform().m_sequence3Rotation = {rot[0], rot[1], rot[2]};
      pscenerenderable->transform().m_sequence3Scale = {scl[0], scl[1], scl[2]};

      informationf("Loaded GameObject '%s' - Pos: (%0.2f, %0.2f, %0.2f), Rot: (%0.2f, %0.2f, %0.2f), Scale: (%0.2f, "
                   "%0.2f, %0.2f)",
                   setObject.get("name", "unnamed").c_str(), pos[0], pos[1], pos[2], rot[0], rot[1], rot[2], scl[0],
                   scl[1], scl[2]);


      //
      // if (setObject.has_property("cubemap")) {
      //
      //
      // }


      // Store in map
   }


   void scene_base::loadSceneFile(const ::scoped_string &fileName)
   {

      ::file::path path = "matter://scenes/" + fileName + ".json";

      auto sceneJson = file()->as_network_payload(path);
      // if (!inFile.is_open()) {
      //    throw std::runtime_error("Could not open scene_base file: " + path);
      // }

      // json sceneJson;
      // inFile >> sceneJson;


      // Parse skybox cubemap name (if present)
      if (sceneJson.has_property("skybox"))
      {
         // m_strSkyboxCubemapName = sceneJson["skybox"].as_string();
         // information("Scene specifies skybox: '{}'", m_strSkyboxCubemapName);
      }
      else
      {

         // warning("No skybox specified in scene_base file '{}', using default '{}'", fileName,
         // m_strSkyboxCubemapName);
      }

      informationf("Loading scene_base file: %s (%s)", fileName.c_str(), path.c_str());

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

         load_scene_renderable(setObject);
      }

      if (m_bInitialCameraLoaded)
      {

         m_pimmersionlayer->on_initial_camera_load();
      }

      informationf("Scene '%s' loaded. Total renderables: %d", fileName.c_str(), m_mapSceneRenderable.size());

               if (m_strSkybox.has_character())
      {

         auto pskybox = m_mapSkybox[m_strSkybox];

         if (pskybox)
         {

            set_skybox(pskybox);
         }
      }


   }


   //::graphics3d::skybox *scene_base::current_sky_box()
   //{

   //   return m_pskyboxCurrent;

   //   // if (m_pskyboxCurrent)
   //   //{

   //   //   m_pskyboxCurrent

   //   //}

   //   // if (m_strSkyboxModelName.is_empty())
   //   //{

   //   //   return nullptr;

   //   //}
   //   // auto p = m_mapSceneObject.find(m_strSkyboxModelName);
   //   // if (!p) {

   //   //   return nullptr;
   //   //   // cast back from IGameObject→sandbox_game_object
   //   //   //return std::reference_wrapper(
   //   //     // static_cast<sandbox_game_object&>(*it->element2()));
   //   //}
   //   // return p->element2();
   //}
   //::gpu::texture *scene_base::current_sky_box_texture()
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
   // scene_base::getSkyboxObject() const
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


   void scene_base::set_default_camera(::graphics3d::camera *pgpucamera)
   {

      m_pcameraDefault = pgpucamera;

      if (m_pcameraDefault)
      {

         m_pimmersionlayer->m_pengine->m_transform.m_sequence3Position = m_pcameraDefault->position();
         m_pimmersionlayer->m_pengine->m_transform.m_sequence3Rotation = m_pcameraDefault->rotation();
      }
   }


   ::graphics3d::camera *scene_base::get_default_camera() { return m_pcameraDefault; }


   ::graphics3d::camera *scene_base::camera()
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


   ::graphics3d::camera *scene_base::scene_camera()
   {

      if (!m_pcameraScene)
      {

         m_pcameraScene = get_default_camera();
      }

      return m_pcameraScene;
   }


   ::gpu::properties &scene_base::global_ubo() { return m_gpupropertiesGlobalUbo; }


   ::graphics3d::scene_renderable &scene_base::scene_renderable(const ::scoped_string &scopedstr,
                                                                const ::file::path &pathParameter)
   {

      auto &pscenerenderable = this->scene_renderables()[scopedstr];

      if (!pscenerenderable)
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

         pscenerenderable = _scene_renderable(scopedstr, path);
      }

      return *pscenerenderable;
   }


   ::pointer<::graphics3d::scene_renderable> scene_base::_scene_renderable(const ::scoped_string &scopedstr,
                                                                           const ::file::path &path)
   {

      auto pgpucontext = m_pimmersionlayer->m_pengine->gpu_context();

      ::gpu::renderable_t model;

      model.m_strName = scopedstr;

      model.m_pathRenderable = path;

      if (path.case_insensitive_ends(".obj"))
      {

         model.set_type("obj");
      }

      auto prenderable = pgpucontext->load_model(model);

      auto pscenerenderable = øcreate<::graphics3d::scene_renderable>();

      pscenerenderable->initialize_scene_renderable(this);

      if (model.m_erenderabletype == ::gpu::e_renderable_type_wavefront_obj)
      {

         pscenerenderable->m_erendersystem = ::graphics3d::e_render_system_wavefront_obj;
      }

      pscenerenderable->m_strRenderablePath = path;

      pscenerenderable->m_prenderable = prenderable;

      return pscenerenderable;
   }


   ::graphics3d::scene_renderable_map &scene_base::scene_renderables() { return m_mapSceneRenderable; }


   ::pointer<::graphics3d::scene_renderable> scene_base::create_scene_renderable()
   {

      auto pscenerenderable = øcreate_new<::graphics3d::scene_renderable>();

      pscenerenderable->initialize_scene_renderable(this);

      return pscenerenderable;

   }


   ::pointer<::graphics3d::skybox> scene_base::create_sky_box()
   {

      auto pskybox = øcreate_new<::graphics3d::skybox>();

      pskybox->initialize_scene_renderable(this);

      return pskybox;

   }


   ::pointer<::graphics3d::point_light> scene_base::create_point_light(float intensity, float radius,
                                                                       const ::color::color &color)
   {
      auto ppointlight = øallocate ::graphics3d::point_light;
      m_pointlighta.add(ppointlight);
      ppointlight->m_color = color;
      ppointlight->m_transform.m_sequence3Scale.x = radius;
      // gameObj->m_pointLight =
      ppointlight->m_fLightIntensity = intensity;
      return ppointlight;
   }


   void scene_base::defer_load_scene(::gpu::context *pgpucontext)
   {

      _synchronous_lock synchronouslock(this->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

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


   void scene_base::on_load_scene(::gpu::context *pgpucontext) {}


   void scene_base::on_update(::gpu::context *pgpucontext) {}


   void scene_base::on_render(::gpu::context *pgpucontext) {}

   //
   // ::pointer < ::graphics3d::renderable> scene_base::create_tinyobj_renderable(const ::file::path& path)
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
   // scene_object * scene_base::create_tinyobj(const ::file::path& path)
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

   // ::pointer < ::graphics3d::renderable> scene_base::create_tinyobj_scene_object(const ::file::path& path)
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


   void scene_base::generateIbl()
   {

      // void scene::generateIbl()
      //   {

      //if (m_strSkybox.is_empty())
      //{

      //   auto pimmersionlayer = m_pimmersionlayer;

      //   if (pimmersionlayer)
      //   {

      //      auto passetmanager = pimmersionlayer->m_passetmanager;

      //      if (passetmanager)
      //      {

      //         if (passetmanager->m_mapSkyboxTexture.size() > 0)
      //         {

      //            m_strSkybox = passetmanager->m_mapSkyboxTexture.first().element1();

      //         }
      //      }
      //   }

      //}


      //if (!m_prenderableSkyboxModel)
      //{

      //   auto pimmersionlayer = m_pimmersionlayer;

      //   if (pimmersionlayer)
      //   {

      //      auto passetmanager = pimmersionlayer->m_passetmanager;

      //      if (passetmanager)
      //      {

      //         if (passetmanager->m_mapSkyboxRenderableModel.size() > 0)
      //         {

      //            m_prenderableSkyboxModel = passetmanager->m_mapSkyboxRenderableModel.first().element2();

      //         }
      //      }
      //   }
      //}

      try
      {

         // Generate BRDF LUT first (your existing function)
         generateIblBRDFlut();
      }
      catch (...)
      {
      }

      // Now generate irradiance and prefiltered maps using environmentCube (must be valid)
      if (!m_pgpucontext->m_pengine->m_pimmersionlayer->m_passetmanager->m_ptextureEnvironmentCube)
      {
         
         error("[scene] environmentCube is null - aborting IBL generation to avoid descriptor errors.");

      }
      else
      {
         try
         {
            generateIblIrradianceMap();
            generateIblPrefilteredEnvMap();
            information("[scene] IBL assets generated successfully.");
         }
         catch (const ::exception &e)
         {
            errorf("[scene] IBL generation failed: %s", e.get_message().c_str());
         }
      }


      //}
   }


   void scene_base::generateIblBRDFlut()
   {

      // return {};
   }

   void scene_base::generateIblPrefilteredEnvMap() {}


   void scene_base::generateIblIrradianceMap() {}


   //::pointer<::gpu::texture> scene_base::generatePrefilteredEnvMap(::gpu::texture *environmentCubeExisting,
   //                                                             ::graphics3d::renderable *prenderableSkybox)
   //{

   //   //return {};
   //}


   //::pointer<::gpu::texture> scene_base::generateIrradianceMap(
   //   //         ::gpu::texture * irradianceCube,
   //   ::gpu::texture *environmentCube, ::graphics3d::renderable *prenderableSkybox)
   //{

   //   return {};
   //}


} // namespace graphics3d
