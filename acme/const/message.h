#pragma once


enum enum_message : ::i64
{

   e_message_null = 0,

   e_message_create = 1,
   e_message_destroy = 2,
   e_message_move = 3,
   e_message_size = 5,
   e_message_activate = 6,
   e_message_set_focus = 7,
   e_message_kill_focus = 8,
   e_message_paint = 15,
   e_message_close = 16,
   e_message_quit = 18,

   e_message_mouse_activate = 0x0021,

   e_message_context_menu = 0x007B,

   e_message_key_first = 256,
   e_message_key_down = 256,
   e_message_key_up = 257,
   e_message_char = 258,
   e_message_dead_char = 259,
   e_message_sys_key_down = 260,
   e_message_sys_key_up = 261,
   e_message_sys_char = 262,
   e_message_sys_dead_char = 263,
   e_message_uni_char = 265,
   e_message_key_last = 265,

   e_message_hscroll = 0x0114,
   e_message_vscroll = 0x0115,

   e_message_nccreate    =                 0x0081,
   e_message_ncdestroy    =                0x0082,
   e_message_nccalcsize   =                0x0083,
   e_message_nchittest     =               0x0084,
   e_message_ncpaint      =                0x0085,
   e_message_ncactivate   =                0x0086,

   e_message_measure_item     =             0x002C,
   e_message_window_position_changing    =        0x0046,
   e_message_window_position_changed   =          0x0047,
   e_message_set_cursor       =             0x0020,
   e_message_erase_background  =                 0x0014,
   e_message_show_window     =              0x0018,

   e_message_non_client_mouse_move           =    0x00A0,
   e_message_non_client_left_button_down     =        0x00A1,
   e_message_non_client_left_button_up       =        0x00A2,


   e_message_mouse_first = 512,
   e_message_mouse_move = 512,
   e_message_left_button_down = 513,
   e_message_left_button_up = 514,
   e_message_left_button_double_click = 515,
   e_message_right_button_down = 516,
   e_message_right_button_up = 517,
   e_message_right_button_double_click = 518,
   e_message_middle_button_down = 519,
   e_message_middle_button_up = 520,
   e_message_middle_button_double_click = 521,
   e_message_mouse_wheel = 522,
   e_message_timer      =                  0x0113,


   e_message_mouse_leave    =               0x02A3,

   e_message_command  =                    0x0111,
   e_message_enable       =                0x000A,
   e_message_initialize_menu_popup       =         0x0117,
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
   e_message_update_device_list,



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

   e_message_prebuffer_done,

   e_message_need_load_form_data,
   e_message_need_save_form_data,

   e_message_text_composition,

   e_message_change_experience,

   e_message_open_response,
   e_message_event,
   

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






