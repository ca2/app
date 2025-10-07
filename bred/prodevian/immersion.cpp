#include "framework.h"
// immersion.cpp
#include "immersion.h"
#include "bred/graphics3d/scene_base.h"
//#include "SceneFoundry/graphics3d/render_systems/point_light_render_system.h"
//#include <spdlog/spdlog.h>

namespace prodevian
{


   // immersion::immersion(::pointer<IWindowInput> input, ::graphics3d::asset_manager * Passets)
   //    : m_windowInput(std::move(input))
   //    , m_assetManager(assets)
   // {
   //
   //    m_interlockedcountGameObject = 1;
   //
   // }

   immersion::immersion()
   {

   }


   immersion::~immersion()
   {



   }


   void immersion::initialize_immersion_layer(::graphics3d::engine * pengine)
   {

      ::graphics3d::immersion_layer::initialize_immersion_layer(pengine);

   }


   ::pointer < ::graphics3d::scene_base > immersion::create_main_scene()
   {

      return {};


   }



   void immersion::on_initialize_immersion_layer()
   {

      information("immersion::onInit");

      øconstruct(m_pscene);

      //m_scene = øcreate_pointer<sandbox_scene>(m_windowInput, m_assetManager);
      m_pscene->initialize_scene(this);
      m_pscene->loadSceneFile("default_scene"); // TODO: Eventually specify which scene file to load in a better way than this probably via UI
      //m_pscene->init();

   }


   // void immersion::onUpdate(float dt)
   // {
   //    m_pscene->update(dt);
   // }


   // ::graphics3d::IScene& immersion::getSceneInterface() {
   //    return *m_pscene;
   // }




} // namespace prodevian



