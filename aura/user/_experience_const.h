#pragma once


namespace experience
{


   enum e_hittest
   {

      ::experience::e_frame_none = 0,
      ::experience::e_frame_sizing_left = 1,
      ::experience::e_frame_sizing_top = 2,
      ::experience::e_frame_sizing_right = 4,
      ::experience::e_frame_sizing_bottom = 8,
      ::experience::e_frame_sizing_top_left = ::experience::e_frame_sizing_top | ::experience::e_frame_sizing_left,
      ::experience::e_frame_sizing_top_right = ::experience::e_frame_sizing_top | ::experience::e_frame_sizing_right,
      ::experience::e_frame_sizing_bottom_left = ::experience::e_frame_sizing_bottom | ::experience::e_frame_sizing_left,
      ::experience::e_frame_sizing_bottom_right = ::experience::e_frame_sizing_bottom | ::experience::e_frame_sizing_right,
      ::experience::e_frame_client = 16,
      ::experience::e_frame_move = 32,

   };


   enum e_button
   {

      button_none,
      button_close, // stock_icon_close
      button_begin = button_close,
      button_up, // stock_icon_level_up
      button_down, // stock_icon_level_down
      button_minimize, // stock_icon_iconify
      button_restore, // stock_icon_restore
      button_maximize, // stock_icon_maximize
      button_notify_icon, // stock_icon_notify
      button_transparent_frame, // stock_icon_transparent_frame
      button_dock, // stock_icon_dock
      button_end = button_dock

   };


} // namespace experience

