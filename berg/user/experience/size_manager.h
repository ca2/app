#pragma once


//#include "acme/prototype/geometry2d/_geometry2d.h"
#include "acme/prototype/geometry2d/rectangle.h"
////#include "acme/prototype/prototype/object.h"


namespace experience
{


   class CLASS_DECL_BERG size_manager :
      virtual public ::object
   {
   public:


      ::experience::frame_window *     m_pframewindow;
      //::item_pointer                   m_pitemSizing;
      //::item_pointer                   m_pitemCursor;
      ::experience::e_frame         m_eframeSizing;
      ::experience::e_frame         m_eframeCursor;
      i32_point                        m_pointCursorOrigin;
      ::i32_rectangle                  m_rectangleWindowOrigin;
      i32_size                         m_sizeMinimumBorder;
      ::u32                            m_uiSWPFlags;
      e_grip                        m_egripMask;
      ::i32                              m_iPaintCount;


      size_manager();
      ~size_manager() override;

      
      virtual void initialize_size_manager(::experience::frame_window* pframewindow);


      virtual ::experience::enum_frame experience_frame_hit_test(const ::i32_point & point, ::user::e_zorder ezorder);
      //virtual ::item_pointer experience_frame_hit_test(const ::i32_point & point, ::user::e_zorder ezorder);
      virtual enum_cursor experience_frame_to_cursor(const ::experience::e_frame & eframeHitTest);
      //virtual enum_cursor experience_frame_to_cursor(const ::item * pitemHitTest);


      bool on_message_parent_left_button_down(::message::mouse * pmouse);
      bool on_message_mouse_move(::message::mouse * pmouse);
      bool on_message_left_button_up(::message::mouse * pmouse);

      //bool on_message_set_cursor(::message::set_cursor * psetcursor);


      void NotifyFramework(const e_frame & eframe);
      //void NotifyFramework(const ::item * pitem);
      e_grip experience_frame_to_experience_grip(const e_frame & eframe);
      //enum_grip experience_frame_to_experience_grip(const ::item * pitem);
      e_grip GetGripMask();
      void SetGripMask(const e_grip & egrip);
      bool window_is_sizing();
      
      virtual void cancel_sizing();
      
      //void SetSWPFlags(::u32 uFlags);
      virtual ::i32_size GetMinSize();
      bool set_frame_window(frame_window * pframewindow);

      void size_window(const ::experience::e_frame & eframe, ::user::interaction * pframewindow, const ::i32_point & point, bool bTracking);
      //void size_window(const ::item * pitem, ::user::interaction * pframewindow, const ::i32_point & point, bool bTracking);
      void move_window(::user::interaction * pframewindow, const ::i32_rectangle & rectangle);

      virtual bool window_stop_sizing(bool bApply = true, ::message::mouse * pmouse = nullptr);

   };


} // namespace experience



