// From mnk_controller from V0idsEmbrace@Twich continuum project
// by camilo on 2025-05-18 <3ThomasBorregaardSorensen!!
#include "platform.h"
#include "input.h"
#include "engine_instance.h"
#include "acme/platform/application.h"
#include "aura/platform/session.h"
#include "bred/user/user/graphics3d.h"
#include "bred/graphics3d/scene_base.h"
#include <cstdlib>


namespace graphics3d
{


   input::input()
   {

      m_bMouseOut = true;
      configure_keyboard_input();

   }

   input::~input() {}

   void input::on_key_event(const ::user::e_key & key, bool pressed)
   {
      int index = -1;
      if (key == ::user::e_key_w) index = key_forward;
      else if (key == ::user::e_key_s) index = key_backward;
      else if (key == ::user::e_key_a) index = key_left;
      else if (key == ::user::e_key_d) index = key_right;
      else if (key == ::user::e_key_q) index = key_down;
      else if (key == ::user::e_key_e) index = key_up;
      else if (key == ::user::e_key_left_shift) index = key_fast;
      if (index >= 0) m_keyboard.set(index, pressed);
   }


   void input::initialize_input(::f32 moveSpeed, const floating_angle &
    angleCursorPixel)
   {
      m_fMoveSpeed = moveSpeed;
      m_angleCursorPixel = angleCursorPixel;

      auto setting = [this](const char * name, double fallback, double maximum)
      {
         auto text = application()->application_file_setting(name).trimmed();
         if (text.is_empty()) return fallback;
         char * end = nullptr;
         const auto value = std::strtod(text.c_str(), &end);
         if (end == text.c_str() || *end || !std::isfinite(value) || value < 0. || value > maximum)
         {
            warningf("Ignoring invalid camera input setting: %s", name);
            return fallback;
         }
         return value;
      };
      m_fMoveSpeed = (::f32)setting("camera_move_speed.txt", moveSpeed, 1000.);
      configure_keyboard_input(
         (::f32)(setting("camera_key_tap_ms.txt", 1000. * 5. / 60., 10000.) / 1000.),
         (::f32)(setting("camera_key_hold_delay_ms.txt", 250., 60000.) / 1000.));
   
      //m_yaw = ::radians(-90.f);
   
      //m_pitch = 0.f ;
   }


   ::key::e_state input::key_state(::graphics3d::enum_key ekey)
   {
      
      return m_pgraphics3dengineinstance->m_pusergraphics3d->m_pkeymap->key_state(ekey);

   }


   //::user::enum_key_state input::get_key_state(const ::user::e_key & ekey)
   ::key::e_state input::get_key_state(const ::user::e_key & ekey)
   {
      return session()->_key_state(ekey);
      // ::i32 state = glfwGetKey(m_pimpact, key);
      // return state == GLFW_PRESS || state == GLFW_REPEAT;


      //if (session()->is_key_pressed(ekey))
      //{


        // return ::key::e_state_pressed;
      //}

      //return ::key::e_state_none;
   }
   bool input::IsKeyPressed(const ::user::e_key & ekey) { return get_key_state(ekey) == ::key::e_state_pressed; }

   bool input::IsKeyReleased(const ::user::e_key & ekey) { return get_key_state(ekey) == ::key::e_state_none; }

   // Check if any movement keys are pressed (W, A, S, D)
   bool input::IsAnyKeyPressed()
   {
      return IsKeyPressed(::user::e_key_w)
      || IsKeyPressed(::user::e_key_a)
      || IsKeyPressed(::user::e_key_s)
      || IsKeyPressed(::user::e_key_d);
   }



   void input::prepare_mouse_input()
   {

   }


   void input::process_mouse_input()
   {


   }

   void input::process_keyboard_input() {}


   void input::mouseDrag(::floating_sequence2 Δ)
   {

      m_sequence2MouseLastDragΔ = Δ; 
      
   }


   ::block input::as_block()
   {

      return {};

   }



   void input::_001OnMouseMove(const ::i32_point & point)
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

      m_sequence2MouseLastDragΔ += Δ;

   }


   void input::_001PrepareMouseInput()
   {



   }




   void input::process_mouse_input_updateLook()
   {



   }


   void input::_017Update(::f32 dt, ::graphics3d::transform &transform)
   {
      if (dt <= 0.0f)
         return;

      // --- 1) Smooth raw mouse delta ---
      ::f32 alpha = 1.0f - std::exp(-m_smoothing * dt);

      if (alpha < 0.f)
      {

         information("what?");
      }
      m_sequence2MouseSmoothΔ += (m_sequence2MouseLastDragΔ - m_sequence2MouseSmoothΔ) * alpha;

      // m_sequence2MouseSmoothΔ = m_sequence2MouseRawΔ * alpha;

      // convert pixels -> degrees
      auto angleΔYaw = -m_sequence2MouseSmoothΔ.x * m_angleCursorPixel;
      // auto angleΔPitch = m_pgraphics3dengineinstance->m_fYScale * m_sequence2MouseSmoothΔ.y * m_angleCursorPixel; // invert Y for typical FPS
      auto angleΔPitch = m_pgraphics3dengineinstance->m_fInputPitchFlip * m_sequence2MouseSmoothΔ.y * m_angleCursorPixel; // invert Y for typical FPS
      //information("mx={} my={}", m_sequence2MouseSmoothΔ.x, m_sequence2MouseSmoothΔ.y);
      auto pcamera = m_pgraphics3dengineinstance->m_pimmersionlayer->m_pscene->camera();

      // pcamera->m_quaternionRotation.offset_yaw_and_pitch_with_constraints(angleΔYaw, angleΔPitch, -89.0f_degrees,
      //                                                                   89.0f_degrees);

      //{

      pcamera->m_rotation.offset(angleΔYaw, angleΔPitch, -89_degrees, 89_degrees);

      //;
      //;
      //;
      // auto euler_angles = pcamera->m_rotation.euler_angles();

      //information("yaw={} pitch={}", pcamera->m_rotation.m_angleYaw.m_fAngle,
        //          pcamera->m_rotation.m_anglePitch.m_fAngle);
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

      // Apply the existing controller to each held-key interval. Rendering
      // frequency must not turn a short tap into a whole frame of movement.
      for (const auto & interval : m_keyboard.take())
      {
         const auto & keys = interval.pressed;
         const auto heldSeconds = (::f32)interval.seconds;

         // --- 3) Compute movement basis ---
         auto front = pcamera->front();
         auto right = pcamera->right();
         auto up = pcamera->up();
         //::floating_sequence3 right = front.crossed(::floating_sequence3(0.f, 1.f, 0.f)).normalized();
         //::floating_sequence3 up = ::floating_sequence3(0.f, 1.f, 0.f);

         // --- 4) Apply WASDQE movement ---
         ::floating_sequence3 dir{0.f};
         if (keys[key_forward])
            dir += front;
         // dir += m_pgraphics3dengineinstance->m_fYScale * front;
         if (keys[key_backward])
            dir -= front;
         // dir -= m_pgraphics3dengineinstance->m_fYScale * front;
         if (keys[key_left])
            dir -= right;
         if (keys[key_right])
            dir += right;
         if (keys[key_down])
            dir -= up;
         if (keys[key_up])
            dir += up;

         auto modulus = dir.modulus();

         if (std::getenv("CA2_TRACE_INPUT"))
         {
            static thread_local unsigned frame = 0;
            if (modulus > 1e-6f || (++frame % 60) == 0)
               informationf("CA2_INPUT frame dt=%.6f held=%.6f direction=(%.3f,%.3f,%.3f) speed=%.3f", dt, heldSeconds, dir.x, dir.y, dir.z, m_fMoveSpeed);
         }

         if (modulus > 1e-6f)
         {
            dir.normalize();
            ::f32 speed = m_fMoveSpeed * (keys[key_fast] ? 3.f : 1.f);
            transform.m_sequence3Position += dir * speed * heldSeconds;
         }
      }
      transform.m_rotation = pcamera->m_rotation;

      // --- 5) Reset raw delta for next frame ---
      m_sequence2MouseLastDragΔ = ::floating_sequence2(0.f);

   }


} // namespace graphics3d


