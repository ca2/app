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
      mnk_controller(::f32 moveSpeed = 7.f, ::f32 mouseSensitivity = 0.08f);

      void update(::f32 dt, ::graphics3d::IWindowInput * input, ::graphics3d::transform& transform);
      void mouseCallback(floating_sequence2 delta);
      ::f32 getYaw() const { return m_yaw; }
      ::f32 getPitch() const { return m_pitch; }

   private:
      ::f32 m_moveSpeed;
      ::f32 m_mouseSensitivity;
      ::f32 m_yaw;
      ::f32 m_pitch;

      ::f32 m_smoothing = 15.f;
      floating_sequence2 m_rawDelta{ 0.f };
      floating_sequence2 m_smoothDelta{ 0.f };

      floating_sequence2 m_mouseDelta{ 0.f };
   };



} // namespace sandbox_game



 