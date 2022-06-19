#pragma once


namespace experience
{


   class CLASS_DECL_BASE move_manager :
      virtual public ::object
   {
   public:


      ::experience::frame_window *     m_pframewindow;
      e_border                         m_eborderMask;
      point_i32                            m_pointCursorOrigin;
      point_i32                            m_pointWindowOrigin;
      point_i32                            m_pointMove;
      bool                             m_bMoving;
      //::u32                             m_uiSWPFlags;
      ::user::layout_state             m_stateBefore;
      int                              m_iConsiderMove;


      move_manager();
      ~move_manager() override;


      virtual void initialize_move_manager(::experience::frame_window* pframewindow);


      bool on_message_left_button_down(::message::mouse * pmouse);
      bool on_message_mouse_move(::message::mouse * pmouse);
      bool on_message_left_button_up(::message::mouse * pmouse);
      //bool on_message_set_cursor(::message::set_cursor * psetcursor);
      bool _001OnTimer(::u32 uEvent);


      void SetBorderMask(const e_border & emask);
      e_border GetBorderMask();

      bool window_is_moving();
      //void MoveWindow(void * oswindow, const ::point_i32 & point);
      //void SetSWPFlags(::u32 uFlags);


      bool consider_move();


      bool set_frame_window(frame_window * pframewindow);

      //void message_handler(::user::interaction * pframewindow, ::user::message * pusermessage);


      virtual bool window_stop_moving(bool bApply = true, ::message::mouse * pmouse = nullptr);

   };



} // namespace experience




