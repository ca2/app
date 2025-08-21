#pragma once
#include "bred/sandbox/game_object.h"
#include "bred/sandbox/window_input.h"
#include "SceneFoundry/sandbox_game/player_input.h"
#include "bred/sandbox/camera.h"
//#include "SceneFoundry/sandbox/transform_component.h"
#include "SceneFoundry/sandbox_game/camera.h"
#include "bred/sandbox/renderer.h"

//#include "SceneFoundry/sandbox_renderer/include/window.h"

#include <glm/glm.hpp>
//#include <memory>
namespace sandbox_game
{


   class player :
      virtual public ::sandbox::IGameObject
   {
   public:


      //private:
      ::pointer<::sandbox::IWindowInput>       m_pInput;
      ::sandbox::TransformComponent m_transform;
      camera m_camera;
      mnk_controller m_controller;

      // Configuration
      float m_mouseSensitivity = 0.0025f;
      float m_moveSpeed = 30.0f;

      player();


      void initialize_sandbox_player(::sandbox::IWindowInput * pinput);

      void onInit() override;
      void on_update(float deltaTime) override;

      ::sandbox::TransformComponent& transform() override;

      ::sandbox::IModel * model()  override;
      camera& getCamera();



   };



} // namespace sandbox_game


