// From mnk_controller from V0idsEmbrace@Twich continuum project
// by camilo on 2025-05-18 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "input.h"
#include "engine.h"
#include "aura/platform/session.h"
#include "bred/user/user/graphics3d.h"
#include "bred/graphics3d/scene_base.h"


namespace graphics3d
{


   input::input()
   {

      m_bMouseOut = true;

   }

   input::~input() {}


   ::user::enum_key_state input::key(::graphics3d::enum_key ekey) 
   {
      return m_pengine->m_pusergraphics3d->m_pkeymap->key(ekey); 
   }

   ::user::enum_key_state input::get_key_state(::user::e_key ekey)
   {
      // int state = glfwGetKey(m_pimpact, key);
      // return state == GLFW_PRESS || state == GLFW_REPEAT;


      if (session()->is_key_pressed(ekey))
      {


         return ::user::e_key_state_pressed;
      }

      return ::user::e_key_state_none;
   }
   bool input::IsKeyPressed(::user::e_key ekey) { return get_key_state(ekey) & ::user::e_key_state_pressed; }

   bool input::IsKeyReleased(::user::e_key ekey) { return !get_key_state(ekey); }

   // Check if any movement keys are pressed (W, A, S, D)
   bool input::IsAnyKeyPressed()
   {
      return IsKeyPressed(::user::e_key_w) || IsKeyPressed(::user::e_key_a) || IsKeyPressed(::user::e_key_s) ||
             IsKeyPressed(::user::e_key_d);
   }



   void input::prepare_mouse_input()
   {

   }


   void input::process_mouse_input()
   {


   }

   void input::process_keyboard_input() {}


   ::block input::as_block()
   {

      return {};

   }



   void input::_001OnMouseMove(const ::int_point & point)
   {

      if (m_mousestate.m_buttons.left)
      {

         if (point != m_sequence2MouseLast)
         {

            if (!m_bMouseOut)
            {

               auto Δ = point - m_sequence2MouseLast;

               _001OnMouseDrag(Δ);

            }

            m_bMouseOut = false;

         }

      }

      m_sequence2MouseLast = point;

   }


   void input::_001OnMouseOut()
   {

      m_bMouseOut = true;

   }

   
   void input::_001OnMouseDrag(::floating_sequence2 Δ)
   {

      m_sequence2MouseRawΔ = Δ; 

   }


   void input::_001PrepareMouseInput()
   {



   }




   void input::process_mouse_input_updateLook()
   {



   }


   void input::_017Update(float dt, ::graphics3d::transform &transform)
   {
      if (dt <= 0.0f)
         return;

      // --- 1) Smooth raw mouse delta ---
      float alpha = 1.0f - std::exp(-m_smoothing * dt);

      if (alpha < 0.f)
      {

         information("what?");
      }
      m_sequence2MouseSmoothΔ += (m_sequence2MouseRawΔ - m_sequence2MouseSmoothΔ) * alpha;

      // m_sequence2MouseSmoothΔ = m_sequence2MouseRawΔ * alpha;

      // convert pixels -> degrees
      auto angleΔYaw = -m_sequence2MouseSmoothΔ.x * m_angleCursorPixel;
      // auto angleΔPitch = m_pengine->m_fYScale * m_sequence2MouseSmoothΔ.y * m_angleCursorPixel; // invert Y for typical FPS
      auto angleΔPitch = m_sequence2MouseSmoothΔ.y * m_angleCursorPixel; // invert Y for typical FPS
      information("mx={} my={}", m_sequence2MouseSmoothΔ.x, m_sequence2MouseSmoothΔ.y);
      auto pcamera = m_pengine->m_pimmersionlayer->m_pscene->camera();

      // pcamera->m_quaternionRotation.offset_yaw_and_pitch_with_constraints(angleΔYaw, angleΔPitch, -89.0f_degrees,
      //                                                                   89.0f_degrees);

      //{

      pcamera->m_rotation.offset(angleΔYaw, angleΔPitch, -89_degrees, 89_degrees);

      //;
      //;
      //;
      // auto euler_angles = pcamera->m_rotation.euler_angles();

      information("yaw={} pitch={}", pcamera->m_rotation.m_angleYaw.m_fAngle,
                  pcamera->m_rotation.m_anglePitch.m_fAngle);
      // euler_angles.z);
      // auto angleMinimumPitch = -89.0f_degrees;

      // auto angleMaximumPitch = 89.0f_degrees;

      //// Get the Euler angles (pitch, yaw, roll)
      //::floating_sequence3 eulerAngles = glm::eulerAngles(pcamera->m_quaternionRotation);

      //// Extract pitch and yaw
      // auto pitch = ::radians(eulerAngles.x);

      // auto yaw = ::radians(eulerAngles.y);

      // yaw += angleΔYaw;

      // pitch += angleΔPitch;

      // pitch = geometry::clamp(pitch, angleMinimumPitch, angleMaximumPitch);

      // pcamera->m_quaternionRotation = ::floating_quaternion(yaw.radian(), pitch.radians(), 0.f);

      //}


      pcamera->update_vectors();

      transform.m_rotation = pcamera->m_rotation;

      // --- 3) Compute movement basis ---
      auto front = pcamera->front();
      auto right = pcamera->right();
      auto up = pcamera->up();
      //::floating_sequence3 right = front.crossed(::floating_sequence3(0.f, 1.f, 0.f)).normalized();
      //::floating_sequence3 up = ::floating_sequence3(0.f, 1.f, 0.f);

      // --- 4) Apply WASDQE movement ---
      ::floating_sequence3 dir{0.f};
      if (IsKeyPressed(::user::e_key_w))
         dir += front;
      // dir += m_pengine->m_fYScale * front;
      if (IsKeyPressed(::user::e_key_s))
         dir -= front;
      // dir -= m_pengine->m_fYScale * front;
      if (IsKeyPressed(::user::e_key_a))
         dir -= right;
      if (IsKeyPressed(::user::e_key_d))
         dir += right;
      if (IsKeyPressed(::user::e_key_q))
         dir -= m_pengine->m_fYScale * up;
      if (IsKeyPressed(::user::e_key_e))
         dir += m_pengine->m_fYScale * up;

      auto modulus = dir.modulus();

      if (modulus > 1e-6f)
      {
         dir.normalize();
         float speed = m_fMoveSpeed * (IsKeyPressed(::user::e_key_left_shift) ? 3.f : 1.f);
         transform.m_sequence3Position += dir * speed * dt;
      }

      // --- 5) Reset raw delta for next frame ---
      m_sequence2MouseRawΔ = ::floating_sequence2(0.f);
   }



} // namespace graphics3d


