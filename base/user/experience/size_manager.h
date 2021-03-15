#pragma once


namespace experience
{


   class CLASS_DECL_BASE size_manager :
      virtual public ::object
   {
   public:


      ::experience::frame_window *  m_pframewindow;
      e_hittest                     m_ehittestSizing;
      e_hittest                     m_ehittestCursor;
      point_i32                         m_pointCursorOrigin;
      ::rectangle_i32                        m_rectWindowOrigin;
      size_i32                          m_sizeMinimumBorder;
      ::u32                          m_uiSWPFlags;
      enum_grip                        m_egripMask;
      i32                           m_iPaintCount;


      size_manager();
      virtual ~size_manager();

      
      virtual ::e_status initialize_size_manager(::experience::frame_window* pframewindow);


      e_hittest _001HitTest(const ::point_i32 & pointCursor);


      bool on_message_left_button_down(::message::mouse * pmouse);
      bool _001OnMouseMove(::message::mouse * pmouse);
      bool on_message_left_button_up(::message::mouse * pmouse);


      void NotifyFramework(e_hittest emode);
      enum_grip hittest_mode_grip(e_hittest emode);
      enum_grip GetGripMask();
      void SetGripMask(enum_grip egrip);
      bool window_is_sizing();
      //void SetSWPFlags(::u32 uFlags);
      virtual ::size_i32 GetMinSize();
      enum_cursor translate(e_hittest ehittest);
      bool set_frame_window(frame_window * pframewindow);

      void size_window(e_hittest ehittest, ::user::interaction * pframewindow, const ::point_i32 & point, bool bTracking);
      void move_window(::user::interaction * pframewindow, const ::rectangle_i32 & rectangle);

      virtual bool window_stop_sizing(bool bApply = true, ::message::mouse * pmouse = nullptr);

   };


} // namespace experience



