#pragma once


enum enum_timer : ::iptr
{

   e_timer_none,

   e_timer_slow, // indicative usage: few minutes
   e_timer_fast, // indicative usage: few seconds or big second fraction
   e_timer_very_fast, // indicative usage: small second fraction

   e_timer_drag_start = 10000,

   e_timer_command_probe,
   e_timer_menu,
   e_timer_overflow_scrolling,
   e_timer_key_repeat_start,
   e_timer_key_repeat,
   e_timer_update_current_area,
   e_timer_change_polling,
   e_timer_check_cached_credentials,
   e_timer_check_toggle_animation,
   e_timer_auto_save,
   //e_timer_transparent_mouse_event,
   e_timer_redraw,
   e_timer_30s,
   e_timer_hover,
   e_timer_defer_handle_auto_hide_tabs,
   e_timer_check_hover,
   e_timer_check_focus,
   e_timer_defer_notify,
   e_timer_user_hour,
   e_timer_notify,
   e_timer_icon_flash,
   e_timer_kill_focus,
   e_timer_hover_out,
   e_timer_wts_register_session_notification,
   e_timer_hide_window,
   e_timer_show_delayed,
   e_timer_click,
   e_timer_defer_save_document,


   // multimedia
   e_timer_lyric,
   e_timer_backimpact,
   e_timer_song_info,
   e_timer_visual_fade_out,
   e_timer_visual_fade_in,
   e_timer_audio_visual_fade_out,
   e_timer_audio_visual_fade_in,

   e_timer_after_text_change_delayed,
   
   e_timer_reload,
   e_timer_hover_select,

   e_timer_caret_flashing,

   e_timer_main_impact_update,

};



