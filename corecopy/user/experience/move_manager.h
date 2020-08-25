#pragma once


namespace experience
{


   class CLASS_DECL_CORE move_manager :
      virtual public ::object
   {
   public:


      ::experience::frame_window *     m_pframewindow;
      eborder                          m_eborderMask;
      point                            m_pointCursorOrigin;
      point                            m_pointWindowOrigin;
      point                            m_pointMove;
      bool                             m_bMoving;
      UINT                             m_uiSWPFlags;
      ::user::window_state             m_stateBefore;
      int                              m_iConsiderMove;


      move_manager(::experience::frame_window * pframewindow);
      virtual ~move_manager();


      bool _001OnLButtonDown(::message::mouse * pmouse);
      bool _001OnMouseMove(::message::mouse * pmouse);
      bool _001OnLButtonUp(::message::mouse * pmouse);
      bool _001OnTimer(UINT nIDEvent);


      void SetBorderMask(const eborder & emask);
      eborder GetBorderMask();

      bool window_is_moving();
      void MoveWindow(void * oswindow, const ::point & point);
      void SetSWPFlags(UINT uiFlags);


      bool consider_move();


      bool set_frame_window(frame_window * pframewindow);

      //void message_handler(::user::interaction * pframewindow, ::message::base * pbase);


      virtual bool window_stop_moving(bool bApply = true, ::message::mouse * pmouse = nullptr);

   };



} // namespace experience




