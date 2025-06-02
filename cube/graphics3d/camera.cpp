// From V0idsEmbrace@Twich continuum project
// by camilo on 2025-05-17 20:12 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "camera.h"


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cmath> 
// std
#include <cassert>
#include <limits>


namespace graphics3d
{


   void camera::initialize_camera(glm::vec3 position, float yaw, float pitch)
   {
      
      m_locationPosition = position;

      m_fYaw = yaw;

      m_fPitch = pitch;

      m_poleWorldUp = { 0.0f, 1.0f, 0.0f };

      m_fZoom = 75.0f;

      m_fMovementSpeed = 8.0f;

      UpdateCameraVectors();

   }


   void camera::initialize_camera(glm::vec3 target, glm::vec3 camera)
   {

      m_locationPosition = camera;

      auto direction = glm::normalize(target - camera);

      m_fYaw = atan2(direction.z, direction.x);

      m_fPitch = asin(direction.y);

      m_poleWorldUp = { 0.0f, 1.0f, 0.0f };
      
      m_fZoom = glm::radians(75.0f);
      
      m_fMovementSpeed = 8.0f;

      UpdateCameraVectors();

   }

   // Mouse movement processing
   void camera::ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch) 
   {

      const float sensitivity = 0.1f;  // Adjust this value to your liking
      xoffset *= sensitivity;
      yoffset *= sensitivity;

      m_fYaw += xoffset;
      m_fPitch += yoffset;

      if (constrainPitch) 
      {
         
         m_fPitch = minimum_maximum(m_fPitch, glm::radians(-89.0f), glm::radians(89.0f));

      }

      UpdateCameraVectors();

   }


   void camera::ProcessKeyboardInput(int direction, float deltaTime) 
   {

      auto velocity = m_fMovementSpeed * deltaTime;  // Use movement speed

      if (direction == FORWARD)
         m_locationPosition += m_poleFront * velocity;
      if (direction == BACKWARD)
         m_locationPosition -= m_poleFront * velocity;
      if (direction == LEFT)
         m_locationPosition -= m_poleRight * velocity;
      if (direction == RIGHT)
         m_locationPosition += m_poleRight * velocity;

   }

   
   void camera::setOrthographicProjection(
      float left, float right, float top, float bottom, float fNear, float fFar) 
   {

      m_matrixProjection = glm::mat4{ 1.0f };
      m_matrixProjection[0][0] = 2.f / (right - left);
      m_matrixProjection[1][1] = 2.f / (bottom - top);
      m_matrixProjection[2][2] = 1.f / (fFar - fNear);
      m_matrixProjection[3][0] = -(right + left) / (right - left);
      m_matrixProjection[3][1] = -(bottom + top) / (bottom - top);
      m_matrixProjection[3][2] = -fNear / (fFar - fNear);

   }


   // This is the method being used below as opposed to ortho ^
   void camera::setPerspectiveProjection(float fovy, float aspect, float fNear, float fFar) 
   {

      m_matrixProjection = glm::perspective(fovy, aspect, fNear, fFar);

      /*assert(glm::abs(aspect - std::numeric_limits<float>::epsilon()) > 0.0f);
      const float tanHalfFovy = tan(fovy / 2.f);
      m_matrixProjection = glm::mat4{ 0.0f };
      m_matrixProjection[0][0] = 1.f / (aspect * tanHalfFovy);
      m_matrixProjection[1][1] = 1.f / (tanHalfFovy);
      m_matrixProjection[2][2] = fFar / (fFar - fNear);
      m_matrixProjection[2][3] = 1.f;
      m_matrixProjection[3][2] = -(fFar * fNear) / (fFar - fNear);*/

   }


   void camera::setViewDirection(glm::vec3 position, glm::vec3 direction, glm::vec3 up) 
   {

      const glm::vec3 w{ glm::normalize(direction) };
      const glm::vec3 u{ glm::normalize(glm::cross(w, up)) };
      const glm::vec3 v{ glm::cross(w, u) };

      m_matrixImpact = glm::mat4{ 1.f };
      m_matrixImpact[0][0] = u.x;
      m_matrixImpact[1][0] = u.y;
      m_matrixImpact[2][0] = u.z;
      m_matrixImpact[0][1] = v.x;
      m_matrixImpact[1][1] = v.y;
      m_matrixImpact[2][1] = v.z;
      m_matrixImpact[0][2] = w.x;
      m_matrixImpact[1][2] = w.y;
      m_matrixImpact[2][2] = w.z;
      m_matrixImpact[3][0] = -glm::dot(u, position);
      m_matrixImpact[3][1] = -glm::dot(v, position);
      m_matrixImpact[3][2] = -glm::dot(w, position);
      m_matrixAntImpact = glm::mat4{ 1.f };
      m_matrixAntImpact[0][0] = u.x;
      m_matrixAntImpact[0][1] = u.y;
      m_matrixAntImpact[0][2] = u.z;
      m_matrixAntImpact[1][0] = v.x;
      m_matrixAntImpact[1][1] = v.y;
      m_matrixAntImpact[1][2] = v.z;
      m_matrixAntImpact[2][0] = w.x;
      m_matrixAntImpact[2][1] = w.y;
      m_matrixAntImpact[2][2] = w.z;
      m_matrixAntImpact[3][0] = position.x;
      m_matrixAntImpact[3][1] = position.y;
      m_matrixAntImpact[3][2] = position.z;

   }

   
   void camera::setViewTarget(glm::vec3 position, glm::vec3 target, glm::vec3 up) 
   {

      setViewDirection(position, target - position, up);

   }


   //void camera::setViewYXZ(glm::vec3 position, glm::vec3 rotation) 
   //{

   //   m_locationPosition = position;

   //   m_fPitch = rotation.x;

   //   m_fYaw = rotation.y;

   //   UpdateCameraVectors();

   //   m_matrixImpact = GetViewMatrix();

   //   m_matrixAntImpact = glm::inverse(m_matrixImpact);

   //}


   void camera::UpdateCameraVectors()
   {

      // Calculate the new front vector based on yaw and pitch
      glm::vec3 front;
      front.x = cos(m_fPitch) * cos(m_fYaw);
      front.y = sin(m_fPitch);
      front.z = cos(m_fPitch) * sin(m_fYaw);
      this->m_poleFront = glm::normalize(front);

      // Re-calculate the right and up vector
      this->m_poleRight = glm::normalize(glm::cross(this->m_poleFront, m_poleWorldUp));
      this->m_poleUp = glm::normalize(glm::cross(this->m_poleRight, this->m_poleFront));

   }


   // Get the camera's zoom (field of view)
   float camera::GetZoom() const
   {

      return m_fZoom;

   }


   // Set the movement speed of the camera
   void camera::SetMovementSpeed(float speed)
   {

      m_fMovementSpeed = speed;

   }


   // Get the view matrix
   glm::mat4 camera::GetViewMatrix() const
   {

      return glm::lookAt(m_locationPosition, m_locationPosition + m_poleFront, m_poleUp);

   }

   // Get the camera position
   glm::vec3 camera::GetPosition() const
   {

      return m_locationPosition;

   }

      void ::graphics3d::camera::Jump(float jumpHeight) {
         m_locationPosition.y += jumpHeight;  // Move up by jumpHeight units
   }

   void ::graphics3d::camera::TeleportDownward(float distance) {
      m_locationPosition.y -= distance;  // Move down by the specified distance
   }

   void ::graphics3d::camera::TeleportInDirection(int direction) 
   {
      const float teleportDistance = 0.40f; // Set teleport distance to 50 units

      if (direction == FORWARD) {
         m_locationPosition += m_poleFront * teleportDistance;
      }
      else if (direction == BACKWARD) {
         m_locationPosition -= m_poleFront * teleportDistance;
      }
      else if (direction == LEFT) {
         m_locationPosition -= m_poleRight * teleportDistance;
      }
      else if (direction == RIGHT) {
         m_locationPosition += m_poleRight * teleportDistance;
      }
   }

   // Function to update idle movement
   void ::graphics3d::camera::UpdateIdleMovement(float deltaTime)
   {
      static float elapsedTime = 0.0f;
      elapsedTime += deltaTime;

      // Subtle oscillation parameters
      float amplitude = 0.1f; // Amplitude of the movement
      float frequency = 1.0f; // Frequency of the oscillation

      // Calculate oscillation
      float offsetX = amplitude * sin(frequency * elapsedTime);
      float offsetY = amplitude * cos(frequency * elapsedTime);

      // Apply the oscillation to the camera position
      m_locationPosition.x += offsetX;
      m_locationPosition.y += offsetY;
   }


}  // namespace graphics3d


