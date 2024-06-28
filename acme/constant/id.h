#pragma once


enum enum_id : ::uptr
{


   id_invalid = ID_INVALID,


   id_none = ID_NONE,


   id_initial_update = ID_INITIAL_UPDATE,
   id_pre_close_document = ID_PRE_CLOSE_DOCUMENT,
   //id_new_document = ID_NEW_DOCUMENT,
   id_close_document = ID_CLOSE_DOCUMENT,
   //id_open_document = ID_OPEN_DOCUMENT,
   id_save_document = ID_SAVE_DOCUMENT,
   id_event = ID_EVENT,
   id_update = ID_UPDATE,
   id_full = ID_FULL,
   id_document = ID_DOCUMENT,
   id_topic_ok = ID_TOPIC_OK,
   id_initialize = ID_INITIALIZE,
   id_browse = ID_BROWSE,
   id_synchronize_path = ID_SYNCHRONIZE_PATH,
   id_filter = ID_FILTER,
   id_form = ID_FORM,
   id_redraw = ID_REDRAW,
   id_soul = ID_SOUL,
   id_create = ID_CREATE,
   id_destroy = ID_DESTROY,
   id_finish = ID_FINISH,
   id_dialog_result = ID_DIALOG_RESULT,
   id_complete = ID_COMPLETE,
   id_incoming_document = ID_INCOMING_DOCUMENT,
   id_check  = ID_CHECK,
   id_enable = ID_ENABLE,
   id_text = ID_TEXT,
   id_text_selection_begin = ID_TEXT_SELECTION_BEGIN,
   id_text_selection_end = ID_TEXT_SELECTION_END,
   id_visible  = ID_VISIBLE,




   id_id = 1 << 16,
   id_key,
   id_ostream,
   id_file,
   id_time,
   id_wallpaper_change,
   id_change_user,
   //id_weather_change,




   id_search = 1 << 20,
   id_address,
   id_find,
   id_replace,
   id_folder,
   id_full_screen,
   id_update_layout,
   id_unknown,
   id_control_event,
   id_save_to_ostream,
   id_set_edit_file,
   id_flush_edit_file,
   id_file_changed,
   id_add_location,
   id_control_saved,
   id_impact_list,
   id_impact_report,
   id_impact_icon,
   id_replace_name,
   id_new_folder,
   id_create_impacts,
   id_after_change_text,
   id_after_change_text_delayed,
   id_delete_contents,
   id_select_main_tab,
   id_new_destination,
   id_xxxid_current_area,
   id_playlists_changed,
   id_songs_added,
   id_songs_changed,
   id_song_folder_changed,
   id_playlist_list_selection_changed,
   id_impact_playlist_changed,
   id_play_playlist_changed,
   id_playback_playlist_changed,
   id_current_song_changed,
   id_current_image_changed,
   id_current_text_changed,
   id_alarms_changed,
   id_ensure_visible,
   id_frame_down,
   id_frame_up,
   id_netshare, // ["address"]
   id_playback_start,
   id_playback_stop,
   id_email_changed,
   id_open_email,
   id_synchronize_locations,
   id_synchronize_folder_selection,
   id_create_bars,
   id_pop,
   id_get_active_impact_selection,
   id_open_selection_properties,
   id_topic_start,
   id_topic_cancel,
   id_topic_save_failed,
   id_topic_saved,
   id_set_file,
   id_midi_program_change,
   id_after_change_content,
   id_get_topic_impact_id,
   id_set_topic_impact_by_id,
   id_play_if_not_playing,
   id_do_play,
   id_play_and_fail_if_playing,
   id_execute_stop,
   id_close_device,
   id_get_topic_midi_player,
   id_get_topic_wave_player,
   id_after_open_document,
   id_title,
   id_restart_track,
   id_current_song,
   id_mode,
   id_get_attachable_impact,
   id_backgrounds,
   id_after_browse,
   id_get_form_impact,
   id_document_complete,
   id_compact_mode,
   id_progress,
   id_alpha_masks,
   id_detach_playlist,
   id_drop_effect_copy,
   id_new_xxxid_123,
   id_sizes,
   id_wallpaper_changed,
   id_app_activated,
   id_app_changed_occlusion_state,
   id_name,
   id_update_current_area,
   id_player_play,
   id_layouts,
   id_player_stop,
   id_selected,
   id_enter_key_pressed,
   id_attachable,
   id_clean,
   id_build,
   id_installer,
   id_failed,
   id_launch,
   id_show,
   id_start_update,
   id_place_child_title_change,
   id_hover_font_family_name,
   id_main_title,
   id_result,
   id_open_hyperlink,
   id_user_style_change,

   //id_title,
   id_author,
   id_album,
   id_original_album,
   id_composer,
   id_artist,
   id_year,
   id_album_art,
   id_url,
   id_channel,

   id_mesh,

   id_simple,
   //id_simple_checkbox,
   //id_simple_text,
   //id_simple_text_font_family,

   id_organization,
   id_no_teacher,
   id_no_missing_photos,

   id_update_render,



   id_app_tortoise_svn,
   id_app_smart_svn,

   id_raw_left_button_down,
   id_raw_left_button_up,
   id_raw_middle_button_down,
   id_raw_middle_button_up,
   id_raw_right_button_down,
   id_raw_right_button_up,
   id_raw_keydown,
   id_raw_keyup,

   //id_no_client_frame,
   id_before_show_main_dialog,
   id_after_show_main_dialog,
   id_run,
   id_operating_system_user_theme_change,
   id_operating_system_user_icon_theme_change,
   id_operating_system_user_color_change,
   id_operating_system_font_list_change,
   id_font_enumeration,
   id_font_extents,
   id_font_list_layout,
   id_font_list_total_size,
   id_font_list_redraw,
   id_operating_system_dark_mode_change,
   id_set_operating_system_dark_mode,
   id_get_operating_system_dark_mode,
   id_get_operating_system_dark_mode_reply,
   id_application_dark_mode_change,
   id_set_application_dark_mode,
   id_get_application_dark_mode,

   id_application,
   id_session,
   id_system,
   id_thread,
   id_process_init,
   id_init,
   id_init1,
   id_init2,
   id_init3,
   id_init_instance,
   id_term3,
   id_term1,
   id_term2,
   id_term,
   id_term_instance,


   id_hide_recycle_bin,
   id_show_recycle_bin,
   id_not_modified,
      

   // procedures:

   // callbacks:

   // user topic
      
   id_initialize_control = 1'073'741'824, // 0x40000000
   id_action,
   id_left_button_down,
   id_left_button_double_click,
   id_left_button_drag,
   id_left_button_up,
   id_click,
   id_context_menu,
   //subjectnt_m_button_down,
   //subjectnt_m_button_up,
   id_list_clicked,
   //subjectnt_mouse_enter,
   //subjectnt_mouse_leave,
   id_set_check,
   id_timer,
   id_enter_key,
   id_escape,
   id_tab_key,
   id_key_down,
   id_after_change_text_format,
   id_after_change_cur_sel,
   id_after_change_cur_hover,
   id_mouse_enter,
   id_mouse_leave,
   id_timebar_change,
   id_menu_hover,
   id_context_menu_close,
   id_set_focus,
   id_kill_focus,
   id_on_create_impact,
   id_on_create_tab,
   id_form_initialize,
   id_layout,
   id_calc_item_height,
   id_change_impact_style,
   id_item_clicked,
   id_image_list_action,
   id_load_form_data,
   id_save_form_data,
   id_close_app,
   id_switch,
   id_maximize,
   id_minimize,


   id_show_impact,
   id_load_projects,


   id_task_bar_created,


   id_video_input_device_added,
   id_video_input_device_removed,


   id_array,

   
   id_on_set_transparent_frame,
   id_on_clear_transparent_frame,


   id_on_after_enter_iconic,
   id_on_after_enter_normal,
   id_on_after_enter_zoomed,
   id_on_after_enter_full_screen,

   id_on_after_exit_iconic,
   id_on_after_exit_normal,
   id_on_after_exit_zoomed,
   id_on_after_exit_full_screen,


   id_item_update,
   id_tool,
   id_content,

   id_on_activate,
   id_new_item_installing,
   id_item_finished_installing,
   id_application_menu_update,
   id_separator,
   id_edit_copy,
   id_edit_cut,
   id_edit_paste,
   id_edit_select_all,
   
   id_network_reachability_status_change,
   id_system_install,
   id_storage_install,
   id_repository_install,
   id_download,
   id_speech,

   id_load_fragment_path_prefix,
   id_cloud_provider,

   id_one_drive,
   id_dropbox,


};



