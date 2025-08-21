#include "framework.h"
// player_input.cpp
#include "SceneFoundry/sandbox_game/player_input.h"
//#include "SceneFoundry/sandbox/transform_component.h"


namespace sandbox_game
{

   mnk_controller::mnk_controller(float moveSpeed, float mouseSensitivity)
      : m_moveSpeed(moveSpeed), m_mouseSensitivity(mouseSensitivity), m_yaw(-90.f), m_pitch(0.f)
   {
   }

   void mnk_controller::mouseCallback(glm::vec2 delta) {
      m_rawDelta = delta;
   }

   void mnk_controller::update(
      float dt,
      ::sandbox::IWindowInput * pinput,
      ::sandbox::TransformComponent& transform)
   {

      // 1) Smooth raw mouse delta into m_smoothDelta
      float alpha = 1.0f - std::exp(-m_smoothing * dt);
      m_smoothDelta += (m_rawDelta - m_smoothDelta) * alpha;

      // 2) Camera-space movement
      float pitchDeg = glm::degrees(transform.rotation.x);
      float yawDeg = glm::degrees(transform.rotation.y);
      glm::vec3 front{
          std::cos(glm::radians(yawDeg)) * std::cos(glm::radians(pitchDeg)),
          std::sin(glm::radians(pitchDeg)),
          std::sin(glm::radians(yawDeg)) * std::cos(glm::radians(pitchDeg))
      };
      front = glm::normalize(front);
      glm::vec3 right = glm::normalize(glm::cross(front, glm::vec3(0.f, 1.f, 0.f)));
      glm::vec3 up = glm::vec3(0.f, 1.f, 0.f);

      glm::vec3 dir{ 0.f };
      if (pinput->isKeyPressed(::sandbox::SandboxKey::W)) dir += front;
      if (pinput->isKeyPressed(::sandbox::SandboxKey::S)) dir -= front;
      if (pinput->isKeyPressed(::sandbox::SandboxKey::A)) dir -= right;
      if (pinput->isKeyPressed(::sandbox::SandboxKey::D)) dir += right;
      if (pinput->isKeyPressed(::sandbox::SandboxKey::Q)) dir -= up;
      if (pinput->isKeyPressed(::sandbox::SandboxKey::E)) dir += up;

      if (glm::length(dir) > 0.0f)
         transform.translation += glm::normalize(dir) * m_moveSpeed * dt;

      // 3) Apply smoothed mouse-look
      m_yaw += m_smoothDelta.x * m_mouseSensitivity;
      m_pitch -= m_smoothDelta.y * m_mouseSensitivity;
      m_pitch = glm::clamp(m_pitch, -89.f, 89.f);

      transform.rotation = glm::vec3(
         glm::radians(m_pitch),
         glm::radians(m_yaw),
         0.f
      );

      // 4) Reset for next frame
      m_rawDelta = glm::vec2(0.f);
   }



} // namespace sandbox_game



