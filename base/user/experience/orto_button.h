#pragma once


#include "button.h"


namespace experience
{


   class CLASS_DECL_BASE orto_button :
      virtual public ::experience::button
   {
   public:


      

      ::oswindow                             m_oswindowPreviousFocus;
      ::draw2d::region_pointer               m_pregion;


      orto_button();
      ~orto_button() override;


      ::item_pointer on_hit_test(const ::int_point & point, ::user::e_zorder ezorder) override;


      void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;
      bool pre_create_window(::user::system * pusersystem) override;

      void install_message_routing(::channel * pchannel) override;
      void UpdateWndRgn() override;
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


      void on_layout(::draw2d::graphics_pointer & pgraphics) override;


      DECLARE_MESSAGE_HANDLER(on_message_show_window);
      DECLARE_MESSAGE_HANDLER(on_message_left_button_down);
      DECLARE_MESSAGE_HANDLER(on_message_left_button_up);
      void on_timer(::timer * ptimer) override;
      //LRESULT OnAppForwardSyncMessage(WPARAM wParam, LPARAM lParam);


   };


} // namespace experience



