// From mnk_controller from V0idsEmbrace@Twich continuum project
// by camilo on 2025-05-18 <3ThomasBorregaardSorensen!!
#pragma once 


#include "bred/graphics3d/scene_object.h"
#include "acme/constant/user_key.h"
#include "bred/graphics3d/key_map.h"


namespace graphics3d
{

   struct input_block_0
   {

     ::graphics3d::mouse_state m_mousestate;

   };


   class CLASS_DECL_BRED input : 
      public input_block_0,
      virtual public ::particle
   {
   public:


      //::pointer<::user::graphics3d> m_pusergraphics3d;
      ::pointer<::graphics3d::engine> m_pengine;
      //::pointer<::graphics3d::key_map> m_pkeymap;


      input();
      ~input() override;


      virtual ::user::enum_key_state key(::graphics3d::enum_key ekey);

      // from MyPlace2025@V0idsEmbrace@Twitch
      virtual ::user::enum_key_state get_key_state(::user::e_key ekey);
      virtual bool IsKeyPressed(::user::e_key ekey); // New method for released keys
      virtual bool IsKeyReleased(::user::e_key ekey); // New method for released keys
      virtual bool IsAnyKeyPressed(); // New method to check if any keys are pressed
      // End from MyPlace2025@V0idsEmbrace@Twitch


      virtual void prepare_mouse_input();
      virtual void process_mouse_input();

      virtual void process_keyboard_input();


      virtual ::block as_block();



      virtual void _001OnMouseMove(const ::int_point &point);
      virtual void _001OnMouseOut();



      virtual void _001PrepareMouseInput();
      virtual void process_mouse_input_updateLook();



   };


}  // namespace graphics3d



