#pragma once
#include "sandbox_renderer/device.h"
#include "bred/sandbox/game_layer.h"
#include "bred/sandbox/window_input.h"
#include "bred/sandbox/renderer.h"
#include "SceneFoundry/sandbox_game/player.h"
#include "SceneFoundry/sandbox_game/scene.h"
//#include <iostream>
//#include <memory>

namespace sandbox_game
{


   class game_layer :
      virtual public ::sandbox::IGameLayer
   {
   public:


      ::pointer<::sandbox::IScene> m_pscene;
      ::pointer<::sandbox::IWindowInput> m_pwindowinput;
      ::pointer < sandbox_engine::asset_manager > m_passetmanager;


      game_layer();


      void initialize_game_layer(::sandbox::IWindowInput * pinput, ::sandbox_engine::asset_manager & assets);






      void onInit() override;
      void onUpdate(float dt) override;

::sandbox::      IScene& getSceneInterface() override;
   ///private:

   };


} // namespace sandbox_game


