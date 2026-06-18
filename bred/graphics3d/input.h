// From mnk_controller from V0idsEmbrace@Twich continuum project
// by camilo on 2025-05-18 <3ThomasBorregaardSorensen!!
#pragma once 


#include "bred/graphics3d/scene_object.h"
#include "acme/constant/user_key.h"
#include "bred/graphics3d/key_map.h"
#include "acme/user/key/state.h"


namespace graphics3d
{

   //struct input_block_0
   //{

   //  ::graphics3d::mouse_state m_mousestate;

   //};


   class CLASS_DECL_BRED input : 
      //public input_block_0,
      virtual public ::particle
   {
   public:


      //::pointer<::user::graphics3d> m_pusergraphics3d;
      ::pointer<::graphics3d::engine> m_pengine;
      //::pointer<::graphics3d::key_map> m_pkeymap;
      //struct input_t
      //{
         // KeyMappings keys{};
         bool m_bMouseAbsolute;

         //::f64 m_dMouseLastY = 0.0;
         //::f64 m_Δx = 0.;
         //::f64 m_Δy = 0.;

         bool m_bWasLeft = false;
         ::floating_sequence2 m_sequence2MouseLast;
         //::floating_sequence2 m_sequence2MouseRawΔ{0.f};
         ::floating_sequence2 m_sequence2MouseSmoothΔ{0.f};
         ::floating_sequence2 m_sequence2MouseΔ{0.f};
         ::floating_sequence2 m_sequence2MouseLastDragΔ{0.f};


         ::f64 m_dCursorX;
         ::f64 m_dCursorY;
         bool m_bFirstMouse;
         bool m_bLastMouse;

         ::f32 m_fMoveSpeed{3.f};
         ::f32 m_fLookSpeed{1.5f};

              ::graphics3d::mouse_state m_mousestate;


                    ::f32 m_smoothing = 15.f;

         bool m_b_001AbsoluteMousePosition;
         f32_angle m_angleCursorPixel; // Sensitivity factor for mouse movement
         //f32_angle m_angleYaw; // Camera yaw (horizontal rotation)
         //f32_angle m_anglePitch; // Camera pitch (vertical rotation)
         floating_sequence3 _cameraDirection; // Camera direction vector
         floating_sequence3 _cameraPosition;
        // ::block as_block() { return as_memory_block(*this); }
      //};

               bool m_bMouseOut = true;

               //::f32 m_moveSpeed;


      input();
      ~input() override;


      virtual void initialize_input(::f32 moveSpeed = 7.f, const floating_angle &angleCursorPixel = 0.1_f_degree);


      virtual ::key::e_state key_state(::graphics3d::enum_key ekey);

      // from MyPlace2025@V0idsEmbrace@Twitch
      virtual ::key::e_state get_key_state(const ::user::e_key & ekey);
      virtual bool IsKeyPressed(const ::user::e_key & ekey); // New method for released keys
      virtual bool IsKeyReleased(const ::user::e_key & ekey); // New method for released keys
      virtual bool IsAnyKeyPressed(); // New method to check if any keys are pressed
      // End from MyPlace2025@V0idsEmbrace@Twitch


      virtual void prepare_mouse_input();
      virtual void process_mouse_input();

      virtual void process_keyboard_input();


      virtual ::block as_block();

      virtual void mouseDrag(::floating_sequence2 Δ);

      virtual void _001OnMouseMove(const ::i32_point &point);
      virtual void _001OnMouseOut();
      virtual void _001OnMouseDrag(::floating_sequence2 Δ);
      //virtual void mouseCallback(::floating_sequence2 delta);
      //virtual void _001OnMouseMove(const ::i32_point &point);
      //virtual void _001OnMouseOut();



      virtual void _001PrepareMouseInput();
      virtual void process_mouse_input_updateLook();

      virtual void _017Update(::f32 dt, ::graphics3d::transform &transform);


   };


}  // namespace graphics3d



