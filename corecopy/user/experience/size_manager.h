#pragma once


namespace experience
{


   class CLASS_DECL_CORE size_manager :
      virtual public ::object
   {
   public:


      ::experience::frame_window *  m_pframewindow;
      e_hittest                     m_ehittestSizing;
      e_hittest                     m_ehittestCursor;
      point                         m_pointCursorOrigin;
      ::rect                        m_rectWindowOrigin;
      size                          m_sizeMinimumBorder;
      UINT                          m_uiSWPFlags;
      e_grip                        m_egripMask;
      i32                           m_iPaintCount;


      size_manager(::experience::frame_window * pframewindow);
      virtual ~size_manager();


      e_hittest _001HitTest(const ::point & pointCursor);


      bool _001OnLButtonDown(::message::mouse * pmouse);
      bool _001OnMouseMove(::message::mouse * pmouse);
      bool _001OnLButtonUp(::message::mouse * pmouse);


      void NotifyFramework(e_hittest emode);
      e_grip hittest_mode_grip(e_hittest emode);
      e_grip GetGripMask();
      void SetGripMask(e_grip egrip);
      bool layout().is_sizing();
      void SetSWPFlags(UINT uiFlags);
      virtual ::size GetMinSize();
      e_cursor translate(e_hittest ehittest);
      bool set_frame_window(frame_window * pframewindow);

      void size_window(e_hittest ehittest, ::user::interaction * pframewindow, const ::point & point, bool bTracking);
      void move_window(::user::interaction * pframewindow, const ::rect & rect);

      virtual bool window_stop_sizing(bool bApply = true, ::message::mouse * pmouse = nullptr);

   };


} // namespace experience



