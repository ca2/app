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

