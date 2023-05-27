#pragma once


#include "acme/primitive/collection/int_map.h"
#include "acme/primitive/geometry2d/_geometry2d.h"
#include "apex/message/channel.h"


namespace experience
{


   class CLASS_DECL_BASE dock_manager:
      virtual public ::channel
   {
   public:


      ::experience::frame_window *        m_pframewindow;
      e_border                            m_eborder;
      e_dock                              m_edock;
      point_i32                           m_pointCursorDockOrigin;
      size_i32                            m_sizeDockRightOrigin;
      point_i32                           m_pointWindowOrigin;
      bool                                m_bDocking;
      ::e_display                         m_edisplayOrigin;
      ::size_i32                          m_sizeOrigin;
      ::point_i32                         m_pointMove;
      ::i32_map < rectangle_i32 >         m_mapWorkspaceRect;
      bool                                m_bPendingCursorPos;
      int                                 m_iDockMove;
      int                                 m_iConsiderDockMove;


      dock_manager();
      ~dock_manager() override;


      virtual void initialize_dock_manager(::experience::frame_window* pframewindow);


      DECLARE_MESSAGE_HANDLER(dock_button_on_message_left_button_down);
      DECLARE_MESSAGE_HANDLER(dock_button_on_message_mouse_move);
      DECLARE_MESSAGE_HANDLER(dock_button_on_message_left_button_up);


      bool _001OnTimer(::u32 uEvent);

      bool dock_window(::message::mouse* pmouse);

      void set_border_mask(const ::e_border & eborder);
      e_border get_border_mask();

      void set_dock_mask(e_dock edock);
      e_dock get_dock_mask();
      
      bool window_is_docking();

      virtual void cancel_docking();

      bool set_frame_window(frame_window * pframewindow);

      //void defer_cursor_pos();

      ::user::button * dock_button();
      ::size_i32 dock_button_right_origin();


   };


} // namespace experience






