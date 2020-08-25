#pragma once


enum e_message : ::i64
{

   message_null,


   message_update = UPDATE_MESSAGE,
   message_system = SYSTEM_MESSAGE,
   message_event = EVENT_MESSAGE,
   message_thread,
   message_desk,
   message_display_change,
   message_property,
   message_event1,
   message_event2,
   message_simple_command,
   message_set_schema,
   message_post_user,
   message_update_notify_icon,
   message_create,
   message_drag_and_drop,
   message_pos_create,
   message_frame_initial_update,
   message_redraw,
   message_apply_visual,
   message_destroy_window,
   message_run,
   message_done,
   message_do_show_window,
   message_auratype_key_down,
   message_auratype_key_up,
   message_auraclick_mouse,



   message_backview,
   message_backview_dequeue,

   message_graphical_command,


   message_recorder_command,
   message_recorder_event,


   message_player_open,
   message_player_start,
   message_player_close,
   message_player_filled,
   message_player_free,
   message_player_stop,

   message_player_command,
   message_player_event,
   message_player_notify_event,

   message_midi_sequence_event,

   message_need_load_form_data,
   message_need_save_form_data,

   message_text_composition,

   message_change_experience,


};







