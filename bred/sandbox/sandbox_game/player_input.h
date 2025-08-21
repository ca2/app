// player_input.h

#pragma once
#include "bred/sandbox/window_input.h"
#include "bred/sandbox/_types.h"
#include <glm/glm.hpp>
//#include <memory>

namespace sandbox_game
{


   class mnk_controller
   {
   public:
      mnk_controller(float moveSpeed = 7.f, float mouseSensitivity = 0.08f);

      void update(float dt, ::sandbox::IWindowInput * input, ::sandbox::TransformComponent& transform);
      void mouseCallback(glm::vec2 delta);
      float getYaw() const { return m_yaw; }
      float getPitch() const { return m_pitch; }

   private:
      float m_moveSpeed;
      float m_mouseSensitivity;
      float m_yaw;
      float m_pitch;

      float m_smoothing = 15.f;
      glm::vec2 m_rawDelta{ 0.f };
      glm::vec2 m_smoothDelta{ 0.f };

      glm::vec2 m_mouseDelta{ 0.f };
   };



} // namespace sandbox_game



 