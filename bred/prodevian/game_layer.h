#pragma once
#include "sandbox_renderer/device.h"
#include "bred/graphics3d/game_layer.h"
#include "bred/graphics3d/window_input.h"
#include "bred/graphics3d/renderer.h"
#include "SceneFoundry/sandbox_game/player.h"
#include "SceneFoundry/sandbox_game/scene.h"
//#include <iostream>
//#include <memory>

namespace sandbox_game
{


   class game_layer :
      virtual public ::graphics3d::IGameLayer
   {
   public:


      ::pointer<::graphics3d::IScene> m_pscene;
      ::pointer<::graphics3d::IWindowInput> m_pwindowinput;
      ::pointer < sandbox_engine::asset_manager > m_passetmanager;


      game_layer();


      void initialize_game_layer(::graphics3d::IWindowInput * pinput, ::sandbox_engine::asset_manager & assets);






      void onInit() override;
      void onUpdate(float dt) override;

::graphics3d::      IScene& getSceneInterface() override;
   ///private:

   };


} // namespace sandbox_game


