#pragma once


#include "acme/primitive/geometry2d/_geometry2d.h"
////#include "acme/primitive/primitive/object.h"


namespace experience
{


   class CLASS_DECL_BASE size_manager :
      virtual public ::object
   {
   public:


      ::experience::frame_window *     m_pframewindow;
      ::experience::enum_frame         m_eframeSizing;
      ::experience::enum_frame         m_eframeCursor;
      point_i32                        m_pointCursorOrigin;
      ::rectangle_i32                  m_rectangleWindowOrigin;
      size_i32                         m_sizeMinimumBorder;
      ::u32                            m_uiSWPFlags;
      enum_grip                        m_egripMask;
      i32                              m_iPaintCount;


      size_manager();
      ~size_manager() override;

      
      virtual void initialize_size_manager(::experience::frame_window* pframewindow);


      virtual ::experience::enum_frame experience_frame_hit_test(const ::point_i32 & point, ::user::e_zorder ezorder);
      virtual enum_cursor experience_frame_to_cursor(::experience::enum_frame eframeHitTest);


      bool on_message_left_button_down(::message::mouse * pmouse);
      bool on_message_mouse_move(::message::mouse * pmouse);
      bool on_message_left_button_up(::message::mouse * pmouse);

      //bool on_message_set_cursor(::message::set_cursor * psetcursor);


      void NotifyFramework(enum_frame eframe);
      enum_grip experience_frame_to_experience_grip(enum_frame eframe);
      enum_grip GetGripMask();
      void SetGripMask(enum_grip egrip);
      bool window_is_sizing();
      
      virtual void cancel_sizing();
      
      //void SetSWPFlags(::u32 uFlags);
      virtual ::size_i32 GetMinSize();
      bool set_frame_window(frame_window * pframewindow);

      void size_window(::experience::enum_frame eframe, ::user::interaction * pframewindow, const ::point_i32 & point, bool bTracking);
      void move_window(::user::interaction * pframewindow, const ::rectangle_i32 & rectangle);

      virtual bool window_stop_sizing(bool bApply = true, ::message::mouse * pmouse = nullptr);

   };


} // namespace experience



