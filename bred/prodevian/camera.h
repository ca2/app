#pragma once



#include "bred/graphics3d/camera.h"


namespace sandbox_game
{


   class camera :
   virtual public ::graphics3d::ICamera
   {
   public:


      camera();


      //sandbox_camera(const ::floating_sequence3 & position, ::f32 yawDeg = -90.f, ::f32 pitchDeg = 0.f, ::f32 zoomDeg = 45.f);
      virtual void initialize_sandbox_camera(const ::floating_sequence3 & position, ::f32 yawDeg = -90.f, ::f32 pitchDeg = 0.f, ::f32 zoomDeg = 45.f);

      void updateView();
      void updateProjection(::f32 aspect, ::f32 nearZ = 0.1f, ::f32 farZ = 100.f);

      void move(floating_sequence3 delta);
      void rotate(::f32 yawOffset, ::f32 pitchOffset);
      void setZoom(::f32 zoom);

      void updateVectors();


      // Getters and setters
      floating_sequence3 getForwardVector() const { return m_front; }
      floating_sequence3 getRightVector() const { return m_right; }
      floating_sequence3 getUpVector() const { return m_up; }
      floating_matrix4 getViewMatrix() const { return m_viewMatrix; }
      floating_matrix4 getProjectionMatrix() const { return m_projMatrix; }

      ::f32 getYaw() const { return m_yaw; }
      ::f32 getPitch() const { return m_pitch; }

      void setYaw(::f32 yaw) { m_yaw = yaw; updateVectors(); }
      void setPitch(::f32 pitch) { m_pitch = pitch; updateVectors(); }
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

      ::f32 m_yaw;
      ::f32 m_pitch;
      ::f32 m_zoom;

      floating_matrix4 m_viewMatrix;
      floating_matrix4 m_projMatrix;
      floating_matrix4 m_inverseViewMatrix{ 1.f };

   };



} // namespace sandbox_game


