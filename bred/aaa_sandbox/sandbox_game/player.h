#pragma once
#include "bred/graphics3d/game_object.h"
#include "bred/graphics3d/window_input.h"
#include "SceneFoundry/sandbox_game/player_input.h"
#include "bred/graphics3d/camera.h"
//#include "SceneFoundry/graphics3d/transform_component.h"
#include "SceneFoundry/sandbox_game/camera.h"
#include "bred/graphics3d/renderer.h"

//#include "SceneFoundry/graphics3d/include/window.h"

#include <glm/glm.hpp>
//#include <memory>
namespace sandbox_game
{


   class player :
      virtual public ::graphics3d::IGameObject
   {
   public:


      //private:
      ::pointer<::graphics3d::IWindowInput>       m_pInput;
      ::graphics3d::transform m_transform;
      camera m_camera;
      mnk_controller m_controller;

      // Configuration
      float m_mouseSensitivity = 0.0025f;
      float m_moveSpeed = 30.0f;

      player();


      void initialize_sandbox_player(::graphics3d::IWindowInput * pinput);

      void onInit() override;
      void on_update(float deltaTime) override;

      ::graphics3d::transform& transform() override;

      ::graphics3d::IModel * model()  override;
      camera& getCamera();



   };



} // namespace sandbox_game


