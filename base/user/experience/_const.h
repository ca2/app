#pragma once


namespace experience
{


   enum e_hittest
   {

      hittest_none = 0,
      hittest_sizing_left = 1,
      hittest_sizing_top = 2,
      hittest_sizing_right = 4,
      hittest_sizing_bottom = 8,
      hittest_sizing_top_left = hittest_sizing_top | hittest_sizing_left,
      hittest_sizing_top_right = hittest_sizing_top | hittest_sizing_right,
      hittest_sizing_bottom_left = hittest_sizing_bottom | hittest_sizing_left,
      hittest_sizing_bottom_right = hittest_sizing_bottom | hittest_sizing_right,
      hittest_client = 16,
      hittest_move = 32,

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



