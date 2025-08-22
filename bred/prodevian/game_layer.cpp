#include "framework.h"
// game_layer.cpp
#include "SceneFoundry/sandbox_game/game_layer.h"
#include "SceneFoundry/graphics3d/render_systems/point_light_render_system.h"
//#include <spdlog/spdlog.h>

namespace sandbox_game
{


   // game_layer::game_layer(::pointer<IWindowInput> input, ::graphics3d::asset_manager * Passets)
   //    : m_windowInput(std::move(input))
   //    , m_assetManager(assets)
   // {
   //
   //    m_interlockedcountGameObject = 1;
   //
   // }

   game_layer::game_layer()
   {

   }



   void game_layer::onInit()
   {
      information("game_layer::onInit");
      øconstruct(m_pscene);
      //m_scene = øcreate_pointer<sandbox_scene>(m_windowInput, m_assetManager);
      m_pscene->initialize_scene(m_pwindowinput, m_passetmanager);
      m_pscene->loadSceneFile("default_scene"); // TODO: Eventually specify which scene file to load in a better way than this probably via UI
      m_pscene->init();
   }

   void game_layer::onUpdate(float dt)
   {
      m_pscene->update(dt);
   }


   ::graphics3d::IScene& game_layer::getSceneInterface() {
      return *m_pscene;
   }


} // namespace sandbox_game


