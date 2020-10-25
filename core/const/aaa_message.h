#pragma once


enum e_message : ::i64
{

   message_null,


   e_message_update = e_message_update,
   e_message_system = e_message_system,
   message_event = e_message_event,
   message_thread,
   e_message_desk,
   e_message_display_change,
   message_property,
   message_event1,
   e_message_event2,
   e_message_simple_command,
   message_set_schema,
   e_message_post_user,
   e_message_update_notify_icon,
   e_message_create,
   message_drag_and_drop,
   message_pos_create,
   message_frame_initial_update,
   e_message_redraw,
   e_message_apply_visual,
   e_message_destroy_window,
   message_run,
   message_done,
   message_do_show_window,
   message_auratype_key_down,
   message_auratype_key_up,
   message_auraclick_mouse,



   message_backview,
   e_message_backview_deque,

   message_graphical_command,


   message_recorder_command,
   message_recorder_event,


   e_message_player_open,
   e_message_player_start,
   e_message_player_close,
   e_message_player_filled,
   e_message_player_free,
   e_message_player_stop,

   e_message_player_command,
   e_message_player_event,
   e_message_player_notify_event,

   e_message_midi_sequence_event,

   message_need_load_form_data,
   e_message_need_save_form_data,

   e_message_text_composition,

   e_message_change_experience,


};







