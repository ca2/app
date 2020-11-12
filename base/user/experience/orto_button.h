#pragma once


namespace experience
{


   class CLASS_DECL_BASE orto_button :
      virtual public ::experience::button
   {
   public:


      

      oswindow                            m_oswindowPreviousFocus;
      ::draw2d::region_pointer                 m_spregion;


      orto_button();
      virtual ~orto_button();


      virtual void on_hit_test(::user::item & item);


      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics);
      virtual bool pre_create_window(::user::create_struct& cs);

      virtual void install_message_routing(::channel * pchannel);
      void UpdateWndRgn();
      //void SetEllipsePens(
      //     ::draw2d::pen * ppen,
      //     ::draw2d::pen * ppenSel = nullptr,
      //     ::draw2d::pen * ppenFocus = nullptr,
      //     ::draw2d::pen * ppenDisabled = nullptr);
      //void SetEllipseBrushs(
      //     ::draw2d::brush * pbrush,
      //     ::draw2d::brush * pbrushSel = nullptr,
      //     ::draw2d::brush * pbrushFocus = nullptr,
      //     ::draw2d::brush * pbrushDisabled = nullptr);
      //void SetTextColors(
      //     color32_t cr,
      //     color32_t crSel,
      //     color32_t crFocus,
      //     color32_t crDisabled);


      virtual void on_layout(::draw2d::graphics_pointer & pgraphics);


      DECL_GEN_SIGNAL(_001OnShowWindow);
      DECL_GEN_SIGNAL(_001OnLButtonDown);
      DECL_GEN_SIGNAL(_001OnLButtonUp);
      void _001OnTimer(::timer * ptimer);
      LRESULT OnAppForwardSyncMessage(WPARAM wParam, LPARAM lParam);


   };


} // namespace experience



