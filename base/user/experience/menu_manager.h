#pragma once



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

         ::experience::frame_window * m_pframewindow;
         States         m_enumState;


         menu_manager(frame_window * pframewindow);
         virtual ~menu_manager();


         bool OnLButtonDblClk(::u32 nFlags, const ::point & point);
         void relay_event(::message::message * pmessage);

         bool set_frame_window(frame_window * pframewindow);

         void message_handler(::user::interaction * pframewindow, ::message::base * pbase);


      };


} // namespace experience


