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


      virtual void on_hit_test(::item & item);


      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics);
      virtual bool pre_create_window(::user::system * pusersystem);

      void install_message_routing(::channel * pchannel) override;
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
      //     ::color32_t color32,
      //     ::color::color crSel,
      //     ::color::color crFocus,
      //     ::color::color crDisabled);


      virtual void on_layout(::draw2d::graphics_pointer & pgraphics);


      DECLARE_MESSAGE_HANDLER(on_message_show_window);
      DECLARE_MESSAGE_HANDLER(on_message_left_button_down);
      DECLARE_MESSAGE_HANDLER(on_message_left_button_up);
      void _001OnTimer(::timer * ptimer);
      //LRESULT OnAppForwardSyncMessage(WPARAM wParam, LPARAM lParam);


   };


} // namespace experience



