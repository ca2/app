// From mnk_controller from V0idsEmbrace@Twich continuum project
// by camilo on 2025-05-18 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "input.h"
#include "engine.h"
#include "aura/platform/session.h"
#include "bred/user/user/graphics3d.h"


namespace graphics3d
{


   input::input()
   {

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


   }


   void input::_001OnMouseOut()
   {


   }





   void input::_001PrepareMouseInput()
   {



   }




   void input::process_mouse_input_updateLook()
   {



   }


} // namespace graphics3d


