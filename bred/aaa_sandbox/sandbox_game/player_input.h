// player_input.h

#pragma once
#include "bred/graphics3d/window_input.h"
#include "bred/graphics3d/_types.h"

//#include <memory>

namespace sandbox_game
{


   class mnk_controller
   {
   public:
      mnk_controller(float moveSpeed = 7.f, float mouseSensitivity = 0.08f);

      void update(float dt, ::graphics3d::IWindowInput * input, ::graphics3d::transform& transform);
      void mouseCallback(floating_sequence2 delta);
      float getYaw() const { return m_yaw; }
      float getPitch() const { return m_pitch; }

   private:
      float m_moveSpeed;
      float m_mouseSensitivity;
      float m_yaw;
      float m_pitch;

      float m_smoothing = 15.f;
      floating_sequence2 m_rawDelta{ 0.f };
      floating_sequence2 m_smoothDelta{ 0.f };

      floating_sequence2 m_mouseDelta{ 0.f };
   };



} // namespace sandbox_game



 