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
   e_timer_overflow_scrolling_start,
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
   e_timer_hover_update,
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
   e_timer_ambient_update,

   e_timer_configure_unlocked,
   e_timer_update_registered,


   e_timer_start_spin_procedure,
   e_timer_call_spin_procedure,

   e_timer_dialog_timeout_update,
   e_timer_wait_status,
   e_timer_check_status,
   e_timer_short_kick_activation,
   e_timer_update_slider,
   e_timer_animation,
   e_timer_hide_tooltip,
   e_timer_long_press_repeat_keys_first,
   e_timer_long_press_repeat_keys_repeat,
   e_timer_build_album_1,
   e_timer_build_album_2,
   e_timer_build_album_3,
   e_timer_delayed_start_searching,
   e_timer_update_bergedge_topic_file,
   e_timer_update_filter_step,
   e_timer_hover_smart_update,
   e_timer_scroll_line_a_start,
   e_timer_scroll_line_a_repeat,
   e_timer_scroll_line_b_start,
   e_timer_scroll_line_b_repeat,
   e_timer_scroll_page_a_start,
   e_timer_scroll_page_a_repeat,
   e_timer_scroll_page_b_start,
   e_timer_scroll_page_b_repeat,
   e_timer_spin_increment_start,
   e_timer_spin_increment_repeat_slower,
   e_timer_spin_increment_repeat_faster,
   e_timer_spin_decrement_start,
   e_timer_spin_decrement_repeat_slower,
   e_timer_spin_decrement_repeat_faster,
   e_timer_show_fullscreen,
   e_timer_show_minipopup,
   e_timer_check_installer,
   e_timer_check_layout,
   e_timer_defer_start_list_drag,
   e_timer_delayed_text_update,
   e_timer_goto_level,
   e_timer_scrollbar_action,
   e_timer_main,
   e_timer_step,
   e_timer_update_main_frame_caption,

};



