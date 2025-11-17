#include "framework.h"
#include "SceneFoundry/sandbox_game/camera.h"
// 
// 
// #include <cmath>

namespace sandbox_game
{

   // camera::camera(floating_sequence3 position, float yawDeg, float pitchDeg, float zoomDeg)
   //    : m_position(position),
   //    m_worldUp(0.f, 1.f, 0.f),
   //    m_yaw(yawDeg),
   //    m_pitch(pitchDeg),
   //    m_zoom(zoomDeg)
   // {
   //    updateVectors();
   //    updateView();
   // }

   camera::camera()
   {

   }

   void camera::updateVectors() {
      floating_sequence3 front;
      front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
      front.y = sin(glm::radians(m_pitch));
      front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
      m_front = glm::normalize(front);

      // Recalculate Right and Up vector
      m_right = glm::normalize(glm::cross(m_front, m_worldUp));  // Right vector
      m_up = glm::normalize(glm::cross(m_right, m_front));
   }

   void camera::updateView() {
      m_viewMatrix = glm::lookAt(m_position, m_position + m_front, m_up);
      m_inverseViewMatrix = glm::inverse(m_viewMatrix);
   }

   void camera::updateProjection(float aspect, float nearZ, float farZ) {
      m_projMatrix = glm::perspective(glm::radians(m_zoom), aspect, nearZ, farZ);
      m_projMatrix[1][1] *= -1; // Vulkan Y-flip
   }

   void camera::move(floating_sequence3 delta) {
      m_position += delta;
      updateView();
   }

   void camera::rotate(float yawOffset, float pitchOffset) {
      m_yaw += yawOffset;
      m_pitch += pitchOffset;

      m_pitch = glm::clamp(m_pitch, -89.f, 89.f);
      updateVectors();
      updateView();
   }

   void camera::setZoom(float zoom) {
      m_zoom = glm::clamp(zoom, 1.f, 120.f);
   }

   void camera::setRotation(floating_sequence3 euler) {
      m_pitch = glm::degrees(euler.x);
      m_yaw = glm::degrees(euler.y);
      updateVectors();
      updateView();
   }


} // namespace sandbox_game




