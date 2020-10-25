#pragma once


enum enum_message : ::i64
{

   e_message_null,

   e_message_create = 1,
   e_message_destroy = 2,
   e_message_move = 3,
   e_message_size = 5,
   e_message_activate = 6,
   e_message_set_focus = 7,
   e_message_kill_focus = 8,
   e_message_quit = 18,


   e_message_non_client_mouse_move = 160,

   e_message_mouse_first = 512,
   e_message_mouse_move = 512,



   e_message_system = WM_APP + 1024,
   e_message_system_command,
   e_message_system_command_probe,
   e_message_system_has_command_handler,
   e_message_system_update,
   e_message_language,
   e_message_application,
   e_message_has_command_handler,
   e_message_event,
   e_message_thread,
   e_message_desk,
   e_message_display_change,
   e_message_property,
   e_message_midi_attribute,
   e_message_event1,
   e_message_event2,
   e_message_simple_command,
   e_message_set_schema,
   e_message_post_user,
   e_message_update_notify_icon,
   e_message_drag_and_drop,
   e_message_pos_create,
   e_message_frame_initial_update,
   e_message_redraw,
   e_message_apply_visual,
   e_message_destroy_window,
   e_message_run,
   e_message_done,
   e_message_do_show_window,
   e_message_auratype_key_down,
   e_message_auratype_key_up,
   e_message_auraclick_mouse,



   e_message_backview,
   e_message_backview_dequeue,

   e_message_graphical_command,


   e_message_recorder_command,
   e_message_recorder_event,


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

   e_message_need_load_form_data,
   e_message_need_save_form_data,

   e_message_text_composition,

   e_message_change_experience,

};


//
//
//struct emessage
//{
//
//   enum_message m_emessage;
//    
//   emessage(enum_message emessage = e_message_null):m_emessage(emessage) {}
//   emessage(const ::id & id) : m_emessage(emessage.m_emessage) {}
//
//   operator enum_message& () { return m_emessage; }
//   operator enum_message() const { return m_emessage; }
//
//};






