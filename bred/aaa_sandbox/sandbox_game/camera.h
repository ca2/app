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


      //sandbox_camera(floating_sequence3 position, float yawDeg = -90.f, float pitchDeg = 0.f, float zoomDeg = 45.f);
      virtual void initialize_sandbox_camera(floating_sequence3 position, float yawDeg = -90.f, float pitchDeg = 0.f, float zoomDeg = 45.f);

      void updateView();
      void updateProjection(float aspect, float nearZ = 0.1f, float farZ = 100.f);

      void move(floating_sequence3 delta);
      void rotate(float yawOffset, float pitchOffset);
      void setZoom(float zoom);

      void updateVectors();


      // Getters and setters
      floating_sequence3 getForwardVector() const { return m_front; }
      floating_sequence3 getRightVector() const { return m_right; }
      floating_sequence3 getUpVector() const { return m_up; }
      floating_matrix4 getViewMatrix() const { return m_viewMatrix; }
      floating_matrix4 getProjectionMatrix() const { return m_projMatrix; }

      float getYaw() const { return m_yaw; }
      float getPitch() const { return m_pitch; }

      void setYaw(float yaw) { m_yaw = yaw; updateVectors(); }
      void setPitch(float pitch) { m_pitch = pitch; updateVectors(); }
      void setRotation(floating_sequence3 euler);

      void setPosition(const floating_sequence3& pos) { m_position = pos; }
      floating_sequence3 getPosition() const override { return m_position; }
      floating_matrix4 getInverseViewMatrix() const override { return m_inverseViewMatrix; }
   private:
      floating_sequence3 m_position;
      floating_sequence3 m_front;
      floating_sequence3 m_up;
      floating_sequence3 m_right;
      floating_sequence3 m_worldUp;

      float m_yaw;
      float m_pitch;
      float m_zoom;

      floating_matrix4 m_viewMatrix;
      floating_matrix4 m_projMatrix;
      floating_matrix4 m_inverseViewMatrix{ 1.f };

   };



} // namespace sandbox_game


