#pragma once



namespace experience
{



   class CLASS_DECL_BASE dock_manager:
      virtual public ::object
   {
   public:


      ::experience::frame_window *     m_pframewindow;
      e_border                         m_eborder;
      e_dock                           m_edock;
      point                            m_pointCursorDockOrigin;
      point                            m_pointWindowOrigin;
      bool                             m_bDocking;
      edisplay                         m_edisplayOrigin;
      ::size                           m_sizeOrigin;
      ::point                          m_pointMove;
      ::i32_map < rect >               m_mapWorkspaceRect;
      bool                             m_bPendingCursorPos;
      int                              m_iDockMove;
      int                              m_iConsiderDockMove;


      dock_manager(::experience::frame_window * pframewindow);
      virtual ~dock_manager();


      bool _001OnLButtonDown(::message::mouse * pmouse);
      bool _001OnMouseMove(::message::mouse * pmouse);
      bool _001OnLButtonUp(::message::mouse * pmouse);
      bool _001OnTimer(::u32 uEvent);

      bool dock_window(::message::mouse* pmouse);

      void set_border_mask(const ::e_border & eborder);
      e_border get_border_mask();

      void set_dock_mask(e_dock edock);
      e_dock get_dock_mask();

      bool window_is_docking();

      bool set_frame_window(frame_window * pframewindow);

      //void defer_cursor_pos();

      ::user::button * dock_button();
      ::point dock_origin();


   };


} // namespace experience






