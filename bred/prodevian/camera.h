#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "bred/graphics3d/camera.h"


namespace sandbox_game
{


   class camera :
   virtual public ::graphics3d::ICamera
   {
   public:


      camera();


      //sandbox_camera(glm::vec3 position, float yawDeg = -90.f, float pitchDeg = 0.f, float zoomDeg = 45.f);
      virtual void initialize_sandbox_camera(glm::vec3 position, float yawDeg = -90.f, float pitchDeg = 0.f, float zoomDeg = 45.f);

      void updateView();
      void updateProjection(float aspect, float nearZ = 0.1f, float farZ = 100.f);

      void move(glm::vec3 delta);
      void rotate(float yawOffset, float pitchOffset);
      void setZoom(float zoom);

      void updateVectors();


      // Getters and setters
      glm::vec3 getForwardVector() const { return m_front; }
      glm::vec3 getRightVector() const { return m_right; }
      glm::vec3 getUpVector() const { return m_up; }
      glm::mat4 getViewMatrix() const { return m_viewMatrix; }
      glm::mat4 getProjectionMatrix() const { return m_projMatrix; }

      float getYaw() const { return m_yaw; }
      float getPitch() const { return m_pitch; }

      void setYaw(float yaw) { m_yaw = yaw; updateVectors(); }
      void setPitch(float pitch) { m_pitch = pitch; updateVectors(); }
      void setRotation(glm::vec3 euler);

      void setPosition(const glm::vec3& pos) { m_position = pos; }
      glm::vec3 getPosition() const override { return m_position; }
      glm::mat4 getInverseViewMatrix() const override { return m_inverseViewMatrix; }
   private:
      glm::vec3 m_position;
      glm::vec3 m_front;
      glm::vec3 m_up;
      glm::vec3 m_right;
      glm::vec3 m_worldUp;

      float m_yaw;
      float m_pitch;
      float m_zoom;

      glm::mat4 m_viewMatrix;
      glm::mat4 m_projMatrix;
      glm::mat4 m_inverseViewMatrix{ 1.f };

   };



} // namespace sandbox_game


