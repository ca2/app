#pragma once


//#include "acme/prototype/geometry2d/_geometry2d.h"
#include "acme/prototype/geometry2d/rectangle.h"
////#include "acme/prototype/prototype/object.h"


namespace experience
{


   class CLASS_DECL_BASE size_manager :
      virtual public ::object
   {
   public:


      ::experience::frame_window *     m_pframewindow;
      //::item_pointer                   m_pitemSizing;
      //::item_pointer                   m_pitemCursor;
      ::experience::enum_frame         m_eframeSizing;
      ::experience::enum_frame         m_eframeCursor;
      point_i32                        m_pointCursorOrigin;
      ::rectangle_i32                  m_rectangleWindowOrigin;
      size_i32                         m_sizeMinimumBorder;
      unsigned int                            m_uiSWPFlags;
      enum_grip                        m_egripMask;
      int                              m_iPaintCount;


      size_manager();
      ~size_manager() override;

      
      virtual void initialize_size_manager(::experience::frame_window* pframewindow);


      virtual ::experience::enum_frame experience_frame_hit_test(const ::point_i32 & point, ::user::e_zorder ezorder);
      //virtual ::item_pointer experience_frame_hit_test(const ::point_i32 & point, ::user::e_zorder ezorder);
      virtual enum_cursor experience_frame_to_cursor(::experience::enum_frame eframeHitTest);
      //virtual enum_cursor experience_frame_to_cursor(const ::item * pitemHitTest);


      bool on_message_parent_left_button_down(::message::mouse * pmouse);
      bool on_message_mouse_move(::message::mouse * pmouse);
      bool on_message_left_button_up(::message::mouse * pmouse);

      //bool on_message_set_cursor(::message::set_cursor * psetcursor);


      void NotifyFramework(enum_frame eframe);
      //void NotifyFramework(const ::item * pitem);
      enum_grip experience_frame_to_experience_grip(enum_frame eframe);
      //enum_grip experience_frame_to_experience_grip(const ::item * pitem);
      enum_grip GetGripMask();
      void SetGripMask(enum_grip egrip);
      bool window_is_sizing();
      
      virtual void cancel_sizing();
      
      //void SetSWPFlags(unsigned int uFlags);
      virtual ::size_i32 GetMinSize();
      bool set_frame_window(frame_window * pframewindow);

      void size_window(::experience::enum_frame eframe, ::user::interaction * pframewindow, const ::point_i32 & point, bool bTracking);
      //void size_window(const ::item * pitem, ::user::interaction * pframewindow, const ::point_i32 & point, bool bTracking);
      void move_window(::user::interaction * pframewindow, const ::rectangle_i32 & rectangle);

      virtual bool window_stop_sizing(bool bApply = true, ::message::mouse * pmouse = nullptr);

   };


} // namespace experience



