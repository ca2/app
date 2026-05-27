#pragma once


#include "acme/prototype/collection/integer_map.h"
//#include "acme/prototype/geometry2d/_geometry2d.h"
#include "acme/prototype/geometry2d/size.h"
#include "acme/prototype/geometry2d/rectangle.h"
#include "apex/message/channel.h"


namespace experience
{


   class CLASS_DECL_BERG dock_manager:
      virtual public ::channel
   {
   public:


      ::experience::frame_window *        m_pframewindow;
      e_border                            m_eborder;
      e_dock                              m_edockMask;
      i32_point                           m_pointCursorDockOrigin;
      i32_size                            m_sizeDockRightOrigin;
      i32_point                           m_pointWindowOrigin;
      bool                                m_bDocking;
      ::e_display                         m_edisplayOrigin;
      ::i32_size                          m_sizeOrigin;
      ::i32_point                         m_pointMove;
      ::i32_map < i32_rectangle >         m_mapWorkspaceRect;
      bool                                m_bPendingCursorPos;
      ::i32                                 m_iDockMove;
      ::i32                                 m_iConsiderDockMove;
      ::i32_rectangle                     m_rectangleOnDockStart;
      ::i32_point                         m_pointLastRepositionCursorOrigin;
      ::i32_point                         m_pointLastRepositionWindowOrigin;


      dock_manager();
      ~dock_manager() override;


      virtual void initialize_dock_manager(::experience::frame_window* pframewindow);


      DECLARE_MESSAGE_HANDLER(dock_button_on_message_left_button_down);
      DECLARE_MESSAGE_HANDLER(dock_button_on_message_mouse_move);
      DECLARE_MESSAGE_HANDLER(dock_button_on_message_left_button_up);


      bool on_timer(::u32 uEvent);

      bool dock_window(::message::mouse* pmouse);

      void set_border_mask(const ::e_border & eborder);
      e_border get_border_mask();

      void set_dock_mask(e_dock edockMask);
      e_dock get_dock_mask();
      
      bool window_is_docking();

      virtual void cancel_docking();

      bool set_frame_window(frame_window * pframewindow);

      //void defer_cursor_pos();

      ::user::button * dock_button();
      ::i32_size dock_button_right_origin();


   };


} // namespace experience






