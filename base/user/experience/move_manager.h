#pragma once


////#include "acme/prototype/prototype/object.h"
#include "aura/user/user/layout_state.h"


namespace experience
{


   class CLASS_DECL_BASE move_manager :
      virtual public ::object
   {
   public:


      ::experience::frame_window *     m_pframewindow;
      e_border                         m_eborderMask;
      int_point                        m_pointCursorOrigin;
      int_point                        m_pointWindowOrigin;
      int_point                        m_pointMove;
      bool                             m_bMoving;
      //unsigned int                          m_uiSWPFlags;
      ::user::layout_state             m_stateBefore;
      int                              m_iConsiderMove;


      move_manager();
      ~move_manager() override;


      virtual void initialize_move_manager(::experience::frame_window* pframewindow);


      bool on_message_parent_mouse_move(::message::mouse * pmouse);
      bool on_message_left_button_down(::message::mouse * pmouse);
      bool on_message_mouse_move(::message::mouse * pmouse);
      bool on_message_left_button_up(::message::mouse * pmouse);
      //bool on_message_set_cursor(::message::set_cursor * psetcursor);
      bool on_timer(unsigned int uEvent);


      void SetBorderMask(const e_border & emask);
      e_border GetBorderMask();

      bool window_is_moving();
      
      virtual void cancel_moving();
      
      //void MoveWindow(void * oswindow, const ::int_point & point);
      //void SetSWPFlags(unsigned int uFlags);


      bool consider_move();


      bool set_frame_window(frame_window * pframewindow);

      //void message_handler(::user::interaction * pframewindow, ::user::message * pusermessage);


      //virtual bool window_stop_moving(bool bApply = true, ::message::mouse * pmouse = nullptr);
      virtual bool window_stop_moving(::message::mouse * pmouse = nullptr);

   };



} // namespace experience




