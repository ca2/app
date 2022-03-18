#pragma once





namespace experience
{


   enum enum_frame
   {

      e_frame_none = 0,
      e_frame_sizing_left = 1,
      e_frame_sizing_top = 2,
      e_frame_sizing_right = 4,
      e_frame_sizing_bottom = 8,
      e_frame_sizing_top_left = e_frame_sizing_top | e_frame_sizing_left,
      e_frame_sizing_top_right = e_frame_sizing_top | e_frame_sizing_right,
      e_frame_sizing_bottom_left = e_frame_sizing_bottom | e_frame_sizing_left,
      e_frame_sizing_bottom_right = e_frame_sizing_bottom | e_frame_sizing_right,
      e_frame_client = 16,
      e_frame_move = 32,

   };


   enum enum_button
   {

      e_button_none,
      e_button_close, // stock_icon_close
      e_button_begin = e_button_close,
      e_button_up, // stock_icon_level_up
      e_button_down, // stock_icon_level_down
      e_button_minimize, // stock_icon_iconify
      e_button_restore, // stock_icon_restore
      e_button_maximize, // stock_icon_maximize
      e_button_notify_icon, // stock_icon_notify
      e_button_transparent_frame, // stock_icon_transparent_frame
      e_button_dock, // stock_icon_dock
      e_button_end = e_button_dock

   };


} // namespace experience



