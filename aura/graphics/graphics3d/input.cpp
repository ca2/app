// From mnk_controller from V0idsEmbrace@Twich continuum project
// by camilo on 2025-05-18 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "input.h"
#include "scene_object.h"
#include "aura/graphics/graphics3d/camera.h"
#include "aura/graphics/graphics3d/types.h"
#include "aura/platform/application.h"
#include "aura/platform/session.h"
#include "aura/user/user/graphics3d.h"
#include <limits>


namespace graphics3d
{


   input::input(float sensitivity, float yaw, float pitch)
   {

      m_dCursorX = 0.;
      m_dCursorY = 0.;
      m_bFirstMouse = true;
      m_bLastMouse = false;

      m_f_001UpdateLookSensitivity = sensitivity;
      _yaw = yaw;
      _pitch = pitch;
      _cameraDirection = glm::vec3(0.0f, 0.0f, -1.0f);
      _cameraPosition = glm::vec3(0.0f, 0.0f, 3.0f);
   }
   //void input::moveInPlaneXZ(
   //    ::user::graphics3d * pimpact, float dt, application_object& gameObject) {
   //    glm::vec3 rotate{ 0 };
   //    if (key(e_key_lookRight) == ::user::e_key_state_pressed) rotate.y += 1.f;
   //    if (key(e_key_lookLeft) == ::user::e_key_state_pressed) rotate.y -= 1.f;
   //    if (key(e_key_lookUp) == ::user::e_key_state_pressed) rotate.x += 1.f;
   //    if (key(e_key_lookDown) == ::user::e_key_state_pressed) rotate.x -= 1.f;

   //    if (glm::dot(rotate, rotate) > std::numeric_limits<float>::epsilon()) {
   //        gameObject.transform.rotation += lookSpeed * dt * glm::normalize(rotate);
   //    }

   //    // limit pitch values between about +/- 85ish degrees
   //    gameObject.transform.rotation.x = glm::clamp(gameObject.transform.rotation.x, -1.5f, 1.5f);
   //    gameObject.transform.rotation.y = glm::mod(gameObject.transform.rotation.y, glm::two_pi<float>());

   //    float yaw = gameObject.transform.rotation.y;
   //    const glm::vec3 forwardDir{ sin(yaw), 0.f, cos(yaw) };
   //    const glm::vec3 rightDir{ forwardDir.z, 0.f, -forwardDir.x };
   //    const glm::vec3 upDir{ 0.f, -1.f, 0.f };

   //    glm::vec3 moveDir{ 0.f };
   //    if (key(e_key_moveForward) == ::user::e_key_state_pressed) moveDir += forwardDir;
   //    if (key(e_key_moveBackward) == ::user::e_key_state_pressed) moveDir -= forwardDir;
   //    if (key(e_key_moveRight) == ::user::e_key_state_pressed) moveDir += rightDir;
   //    if (key(e_key_moveLeft) == ::user::e_key_state_pressed) moveDir -= rightDir;
   //    if (key(e_key_moveUp) == ::user::e_key_state_pressed) moveDir += upDir;
   //    if (key(e_key_moveDown) == ::user::e_key_state_pressed) moveDir -= upDir;

   //    if (glm::dot(moveDir, moveDir) > std::numeric_limits<float>::epsilon()) {
   //        gameObject.transform.translation += moveSpeed * dt * glm::normalize(moveDir);
   //    }

   //    if (key(e_key_Exit) == ::user::e_key_state_pressed)
   //    {
   //       //glfwSetWindowShouldClose(window, GLFW_TRUE);

   //    }
   //}


   void input::_001OnMouseOut()
   {

      reset_mouse_last_position();

   }


   void input::reset_mouse_last_position()
   {



      if (m_b_001AbsoluteMousePosition)
      {

         m_dCursorX = 0.;
         m_dCursorY = 0.;

      }

      m_bLastMouse = true;

   }


   //void input::process_mouse_input_updateLook()
   //{

   //   auto xOffset = m_Δx;
   //   auto yOffset = m_Δy;

   //   // Apply sensitivity factor
   //   xOffset *= m_f_001UpdateLookSensitivity;
   //   yOffset *= m_f_001UpdateLookSensitivity;

   //   // Update yaw and pitch based on offsets
   //   _yaw += xOffset;
   //   _pitch += yOffset;

   //   // Constrain the pitch if necessary
   //   if (_pitch > 89.0f)
   //      _pitch = 89.0f;
   //   if (_pitch < -89.0f)
   //      _pitch = -89.0f;

   //   // Update camera direction based on yaw and pitch
   //   glm::vec3 direction;
   //   direction.x = cos(glm::radians(_yaw)) * cos(glm::radians(_pitch));
   //   direction.y = sin(glm::radians(_pitch));
   //   direction.z = sin(glm::radians(_yaw)) * cos(glm::radians(_pitch));
   //   _cameraDirection = glm::normalize(direction);

   //}

   //void input::processKeyboardInput(GLFWwindow* window, float deltaTime) {
   //    float cameraSpeed = 2.5f * deltaTime; // adjust speed as necessary

   //    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
   //        _cameraPosition += _cameraDirection * cameraSpeed;
   //    }
   //    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
   //        _cameraPosition -= _cameraDirection * cameraSpeed;
   //    }
   //    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
   //        _cameraPosition -= glm::normalize(glm::cross(_cameraDirection, glm::vec3(0.0f, 1.0f, 0.0f))) * cameraSpeed;
   //    }
   //    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
   //        _cameraPosition += glm::normalize(glm::cross(_cameraDirection, glm::vec3(0.0f, 1.0f, 0.0f))) * cameraSpeed;
   //    }
   //}


   void input::process_mouse_input_updateLook()
   {

      auto xOffset = m_Δx;
      auto yOffset = m_Δy;

      xOffset *= m_f_001UpdateLookSensitivity;
      yOffset *= m_f_001UpdateLookSensitivity;

      // limit pitch values between about +/- 85ish degrees
      _yaw = m_pengine->m_pcamera->m_fYaw;
      _pitch = m_pengine->m_pcamera->m_fPitch;

      if (_yaw > glm::two_pi<float>()) _yaw -= glm::two_pi<float>();
      if (_yaw < 0.0f) _yaw += glm::two_pi<float>();

      _pitch = glm::clamp(_pitch, -1.5f, 1.5f);

      if (m_b_001AbsoluteMousePosition)
      {

         _yaw = (float) xOffset;
         _pitch = (float)yOffset;

      }
      else
      {

         _yaw += (float)xOffset;
         _pitch += (float)yOffset;

      }

      // Optional: wrap yaw
      if (_yaw > glm::two_pi<float>()) _yaw -= glm::two_pi<float>();
      if (_yaw < 0.0f) _yaw += glm::two_pi<float>();

      // Clamp pitch to avoid flipping
      _pitch = glm::clamp(_pitch, -1.5f, 1.5f);


      m_pengine->m_pcamera->m_fPitch = _pitch;
      m_pengine->m_pcamera->m_fYaw = _yaw;

   }


   void input::prepare_mouse_input()
   {

      m_pimpact->prepare_mouse_input();

   }


   void input::process_mouse_input()
   {

      m_pimpact->process_mouse_input();

   }


   void input::process_keyboard_input()
   {

      m_pimpact->process_keyboard_input();

   }


   void input::process_keyboard_input_updateMovement()
   {

      //auto& transform = m_pengine->m_transform;

      float yaw = m_pengine->m_pcamera->m_fYaw;
      const glm::vec3 forwardDir{ cos(yaw), 0.f, sin(yaw) };
      const glm::vec3 rightDir{ forwardDir.z, 0.f, -forwardDir.x };
      const glm::vec3 upDir{ 0.f, -1.f, 0.f };

      auto pinput = m_pengine->m_pinput;

      glm::vec3 moveDir{ 0.f };
      {
         using namespace ::graphics3d;
         if (pinput->key(e_key_moveForward) == ::user::e_key_state_pressed) moveDir += forwardDir;
         if (pinput->key(e_key_moveBackward) == ::user::e_key_state_pressed) moveDir -= forwardDir;
         if (pinput->key(e_key_moveRight) == ::user::e_key_state_pressed) moveDir += rightDir;
         if (pinput->key(e_key_moveLeft) == ::user::e_key_state_pressed) moveDir -= rightDir;
         if (pinput->key(e_key_moveUp) == ::user::e_key_state_pressed) moveDir += upDir;
         if (pinput->key(e_key_moveDown) == ::user::e_key_state_pressed) moveDir -= upDir;

         if (glm::dot(moveDir, moveDir) > std::numeric_limits<float>::epsilon())
         {

            m_pengine->m_pcamera->m_locationPosition += m_fMoveSpeed * m_pengine->dt() * glm::normalize(moveDir);

         }

         if (pinput->key(e_key_Exit) == ::user::e_key_state_pressed)
         {

            m_pimpact->m_bShouldClose = true;

         }

      }

   }

   ::user::enum_key_state  input::get_key_state(::user::e_key ekey)
   {
      //int state = glfwGetKey(m_pimpact, key);
      //return state == GLFW_PRESS || state == GLFW_REPEAT;


      if (session()->is_key_pressed(ekey))
      {


         return ::user::e_key_state_pressed;

      }

      return ::user::e_key_state_none;
   }
   bool input::IsKeyPressed(::user::e_key ekey)
   {
      return get_key_state(ekey) & ::user::e_key_state_pressed;
   }

   bool input::IsKeyReleased(::user::e_key ekey)
   {
      return !get_key_state(ekey);
   }

   // Check if any movement keys are pressed (W, A, S, D)
   bool input::IsAnyKeyPressed() {
      return IsKeyPressed(::user::e_key_w) ||
         IsKeyPressed(::user::e_key_a) ||
         IsKeyPressed(::user::e_key_s) ||
         IsKeyPressed(::user::e_key_d);
   }

   void input::process_keyboard_input_spaceExplorer()
   {

      if (key(e_key_moveForward) == ::user::e_key_state_pressed)
      {

         m_pengine->m_pcamera->ProcessKeyboardInput(e_key_moveForward, m_pengine->dt());

         if (IsKeyPressed(::user::e_key_left_shift))
         {

            m_pengine->m_pcamera->TeleportInDirection(e_key_moveForward);

         }

      }

      if (key(e_key_moveBackward) == ::user::e_key_state_pressed)
      {

         m_pengine->m_pcamera->ProcessKeyboardInput(e_key_moveBackward, m_pengine->dt());

         if (IsKeyPressed(::user::e_key_left_shift))
         {

            m_pengine->m_pcamera->TeleportInDirection(e_key_moveBackward);

         }

      }

      if (key(e_key_moveLeft) == ::user::e_key_state_pressed)
      {

         m_pengine->m_pcamera->ProcessKeyboardInput(e_key_moveLeft, m_pengine->dt());

         if (IsKeyPressed(::user::e_key_left_shift))
         {

            m_pengine->m_pcamera->TeleportInDirection(e_key_moveLeft);

         }

      }

      if (key(e_key_moveRight) == ::user::e_key_state_pressed)
      {

         m_pengine->m_pcamera->ProcessKeyboardInput(e_key_moveRight, m_pengine->dt());

         if (IsKeyPressed(::user::e_key_left_shift))
         {

            m_pengine->m_pcamera->TeleportInDirection(e_key_moveRight);

         }
      }

      if (IsKeyPressed(::user::e_key_escape))
      {

         m_pimpact->m_bShouldClose = true;

      }

      if (IsKeyPressed(::user::e_key_4))
      {
         m_pengine->m_bWireframeMode = !m_pengine->m_bWireframeMode;

      }
      // Check for jump (Space key)
      if (IsKeyPressed(::user::e_key_space))
      {
         float jumpHeight = 0.20f;  // Define how high the jump should be
         m_pengine->m_pcamera->Jump(jumpHeight);
      }
      //// Teleport down (Left Control key)
      //if (IsKeyPressed(::user::e_key_left_shift))
      //{
      //   float teleportDistance = 0.1081f;  // Define the downward distance
      //   m_pengine->m_pcamera->TeleportDownward(teleportDistance);
      //}

      // Idle movement
      if (!IsAnyKeyPressed()) { // You might want to implement IsAnyKeyPressed to check for movement keys
         // m_pcamera->UpdateIdleMovement(deltaTime);
      }


   }


   glm::vec3 input::getCameraDirection() const
   {
      return _cameraDirection;
   }


   glm::vec3 input::getCameraPosition() const
   {
      return _cameraPosition;
   }


   void input::_001OnMouseMove(const ::int_point& point)
   {

      //m_mousestate.position.x = point.x();
//m_mousestate.position.y = point.y();
//m_mousestate.m_buttons.left = true;
//         pmouse->m_p

      double w = m_pimpact->m_iWidth;
      double h = m_pimpact->m_iHeight;

      if (m_bLastMouse)
      {

         m_bLastMouse = false;
         m_bFirstMouse = true;

      }

      double xCursor;
      double yCursor;

      if (m_b_001AbsoluteMousePosition)
      {

         xCursor = ((point.x() - (w / 2.0)) * 2.0);
         yCursor = ((point.y() - (h / 2.0)) * 2.0);

      }
      else
      {

         //xCursor = point.x();
         //yCursor = point.y();

         xCursor = point.x();
         yCursor = point.y();

      }

      m_dCursorX = xCursor;
      m_dCursorY = yCursor;

      m_pimpact->track_mouse_leave();

      m_pimpact->m_pengine->on_mouse_move((float)xCursor, (float)yCursor);

   }


   void input::_001PrepareMouseInput()
   {

      double x, y;
      double newx, newy;

      if (m_b_001AbsoluteMousePosition)
      {

         newx = m_dCursorX * 1.25 * MATH_PI;
         newy = m_dCursorY * 1.25 * MATH_PI / 2.0;

      }
      else
      {

         newx = m_dCursorX;
         newy = m_dCursorY;

      }
      //glfwGetCursorPos(window, &xpos, &ypos);

      //if (m_pimpact->m_bFirstMouse) {
      //   _lastX = newx;
      //   _lastY = newy;
      //   m_pimpact->m_bFirstMouse = false;
      //   xpos = _lastX;
      //   ypos = _lastY;
      //}
      //else
      if (!m_b_001AbsoluteMousePosition)
      {

         //if (m_bFirstMouse)
         if (!m_bWasLeft && m_mousestate.m_buttons.left)
         {
            m_dMouseLastX = newx;
            m_dMouseLastY = newy;
            m_bWasLeft = true;

         }
         else if (m_bWasLeft && !m_mousestate.m_buttons.left)
         {

            m_bWasLeft = false;

         }

      }

      if (m_mousestate.m_buttons.left)
      {

         if (m_b_001AbsoluteMousePosition)
         {

            x = m_dMouseLastX + (newx - m_dMouseLastX) * 0.05;
            y = m_dMouseLastY + (newy - m_dMouseLastY) * 0.05;

         }
         else
         {

            x = newx;
            y = newy;

         }

         if (m_b_001AbsoluteMousePosition)
         {

            m_Δx = x;
            m_Δy = -y;  // reversed Y

         }
         else
         {

            //m_Δx = x - m_dMouseLastX;
            //m_Δy = m_dMouseLastY - y;  // reversed Y
            m_Δx = m_Δx + static_cast<float>(m_dMouseLastX -x - m_Δx) * 0.1;
            m_Δy = m_Δy + static_cast<float>(y- m_dMouseLastY  - m_Δy) * 0.1;  // reversed Y

         }

         m_dMouseLastX = x;
         m_dMouseLastY = y;

      }
      else
      {
         
         if (!m_b_001AbsoluteMousePosition)
         {

            m_Δx *= 0.90;
            m_Δy *= 0.90;

         }

      }

   }


} // namespace graphics3d


