#pragma once


enum e_timer : ::i64
{

   timer_none,

   timer_drag_start = 10000,
   timer_command_probe,
   timer_menu,
   timer_overflow_scrolling,
   timer_key_repeat_start,
   timer_key_repeat,
   timer_update_current_area,
   timer_change_polling,
   timer_check_cached_credentials,
   timer_check_toggle_animation,
   timer_auto_save,
   timer_transparent_mouse_event,
   timer_redraw,
   timer_30s,
   timer_hover,
   timer_defer_handle_auto_hide_tabs,
   timer_check_hover,
   timer_check_focus,
   timer_defer_notify,
   timer_user_hour,
   timer_notify,
   timer_icon_flash,
   timer_kill_focus,
   timer_hover_out,
   timer_wts_register_session_notification,
   timer_hide_window,
   timer_show_delayed,
   timer_click,
   timer_defer_save_document,


   // multimedia
   timer_lyric,
   timer_backview,
   timer_song_info,
   timer_visual_fade_out,
   timer_visual_fade_in,
   timer_audio_visual_fade_out,
   timer_audio_visual_fade_in,

   timer_after_text_change_delayed,
   
   timer_reload,

};



