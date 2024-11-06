#pragma once


//#include "acme/prototype/geometry2d/_geometry2d.h"
////#include "acme/prototype/prototype/object.h"


namespace experience
{


   class CLASS_DECL_BASE menu_manager :
      virtual public object
   {
   public:


      friend class client;

      enum States
      {
         e_state_initial = 0,
         StateMBDown = 1 // MOUSE BUtton down
      };

      ::experience::frame_window* m_pframewindow;
      States         m_enumState;


      menu_manager();
      virtual ~menu_manager();


      virtual void initialize_menu_manager(frame_window* pframewindow);


      bool OnLButtonDblClk(unsigned int nFlags, const ::int_point& point);
      void relay_event(::message::message* pmessage);

      bool set_frame_window(frame_window* pframewindow);

      void message_handler(::user::interaction* pframewindow, ::user::message* pusermessage);


   };


} // namespace experience


