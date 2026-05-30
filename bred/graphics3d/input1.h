// From mnk_controller from V0idsEmbrace@Twich continuum project
// by camilo on 2025-05-18 <3ThomasBorregaardSorensen!!
#pragma once 
// MNK_Controller.h
#include "bred/graphics3d/scene_object.h"
//#include "window.h"
#include "acme/constant/user_key.h"
#include "bred/graphics3d/key_map.h"



namespace graphics3d
{


   struct input_t
   {
      //KeyMappings keys{};
      bool   m_bMouseAbsolute;

      ::f64 m_dMouseLastX = 0.0;
      ::f64 m_dMouseLastY = 0.0;
      ::f64 m_Δx = 0.;
      ::f64 m_Δy = 0.;

      bool m_bWasLeft = false;

      ::graphics3d::mouse_state                 m_mousestate;


      ::f64   m_dCursorX;
      ::f64   m_dCursorY;
      bool		m_bFirstMouse;
      bool		m_bLastMouse;

      ::f32    m_fMoveSpeed{ 3.f };
      ::f32    m_fLookSpeed{ 1.5f };

      bool  m_b_001AbsoluteMousePosition;
      ::f32 m_f_001UpdateLookSensitivity;  // Sensitivity factor for mouse movement
      ::f32 _yaw;          // Camera yaw (horizontal rotation)
      ::f32 _pitch;        // Camera pitch (vertical rotation)
      floating_sequence3 _cameraDirection; // Camera direction vector
      floating_sequence3 _cameraPosition;

      ::block as_block()
      {

         return as_memory_block(*this);

      }

   };

   class CLASS_DECL_BRED input :
      virtual public input_t,
      virtual public ::particle
   {
   public:



      input(::f32 sensitivity = 0.001f, ::f32 yaw = glm::radians(- 90.0f), ::f32 pitch = glm::radians(0.0f));

      //void moveInPlaneXZ(::user::graphics3d * pimpact, ::f32 dt, application_object& gameObject);

      void prepare_mouse_input();
      void process_mouse_input();
      void process_keyboard_input();


      void _001OnMouseMove(const ::i32_point & point);
      void _001OnMouseOut();
      void _001PrepareMouseInput();
      void process_mouse_input_updateLook();
      void _001UpdateLook();

      //void processMouseMovement(::f32 xOffset, ::f32 yOffset);
      void processKeyboardInput(::f32 deltaTime);
      //void handleMouseInput();

      void process_keyboard_input_updateMovement();
      void process_keyboard_input_spaceExplorer();

      void reset_mouse_last_position();
   
      floating_sequence3 getCameraDirection() const;
      floating_sequence3 getCameraPosition() const;


      ::pointer<::user::graphics3d > m_pusergraphics3d;
      ::pointer<::graphics3d::engine > m_pengine;
      ::pointer<::graphics3d::key_map > m_pkeymap;

      auto key(auto ekey)
      {

         return m_pkeymap->key(ekey);

      }

      // from MyPlace2025@V0idsEmbrace@Twitch
      ::user::enum_key_state  get_key_state(const ::user::e_key & ekey);
      bool IsKeyPressed(const ::user::e_key & ekey); // New method for released keys
      bool IsKeyReleased(const ::user::e_key & ekey); // New method for released keys
      bool IsAnyKeyPressed(); // New method to check if any keys are pressed
      // End from MyPlace2025@V0idsEmbrace@Twitch

      //public:
          //::f64 lastX = 400.0;
          //::f64 lastY = 300.0;
          //bool firstMouse = true;

   //public:



      // Existing functions...
      //void handleMouseInput(GLFWwindow* window);

      ::f32 getX() const { return (::f32) m_Δx; }
      ::f32 getY() const { return (::f32) m_Δy; }


   };


}  // namespace graphics3d



