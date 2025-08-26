#pragma once
#include "bred/graphics3d/game_object.h"
#include "bred/graphics3d/window_input.h"
//#include "SceneFoundry/sandbox_game/player_input.h"
#include "bred/graphics3d/camera.h"
//#include "SceneFoundry/graphics3d/transform_component.h"
//#include "SceneFoundry/sandbox_game/camera.h"
#include "bred/graphics3d/renderer.h"

//#include "SceneFoundry/graphics3d/include/window.h"

//#include <glm/glm.hpp>
//#include <memory>
namespace prodevian
{


   class CLASS_DECL_BRED actor :
      virtual public ::graphics3d::scene_object
   {
   public:


      //private:
      //::pointer<::graphics3d::IWindowInput>       m_pInput;
      //::graphics3d::transform m_transform;
      //camera m_camera;
      ::pointer < ::graphics3d::camera >           m_pcamera;
      //mnk_controller m_controller;

      // Configuration
      float m_mouseSensitivity = 0.0025f;
      float m_moveSpeed = 30.0f;



      actor();


      void initialize_prodevian_actor(::graphics3d::scene * pscene);

      virtual void on_initialize_actor();

      void on_update(float deltaTime) override;

      //::graphics3d::transform& transform() override;

      //::graphics3d::IModel * model()  override;
      ::graphics3d::camera * camera();



   };



} // namespace sandbox_game


