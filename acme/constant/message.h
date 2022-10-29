#pragma once


enum enum_message : ::iptr
{

   e_message_undefined = -1,

   e_message_null = 0,

   e_message_create = 1,
   e_message_destroy = 2,
   e_message_move = 3,
   e_message_size = 5,
   e_message_activate = 6,
   e_message_set_focus = 7,
   e_message_kill_focus = 8,
   e_message_enable = 10,
   e_message_set_text = 12,
   e_message_paint = 15,
   e_message_close = 16,
   e_message_quit = 18,

   e_message_erase_background  = 20, // 0x0014

   e_message_show_window = 24, // 0x0018
   e_message_setting_change = 26,
   e_message_activate_app = 28, // 0x001C
   e_message_font_change = 29, // 0x001D
   e_message_set_cursor = 32, // 0x0020
   e_message_mouse_activate = 33, // 0x0021

   e_message_get_min_max_info = 36, // 0x0024

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

   e_message_non_client_create    =                 0x0081,
   e_message_non_client_destroy    =                0x0082,
   e_message_non_client_calcsize   =                0x0083,
   e_message_non_client_hittest     =               0x0084,
   e_message_non_client_paint      =                0x0085,
   e_message_non_client_activate   =                0x0086,

   e_message_measure_item     =             0x002C,
   e_message_window_position_changing    =        0x0046,
   e_message_window_position_changed   =          0x0047,

   e_message_non_client_mouse_move           =    0x00A0,
   e_message_non_client_left_button_down     =        0x00A1,
   e_message_non_client_left_button_up       =        0x00A2,
   e_message_command  =                    0x0111,
   e_message_timer      =                  0x0113,
   e_message_initialize_menu_popup       =         0x0117,


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
   e_message_mouse_last = 526,


   e_message_capture_changed = 533,

   
   e_message_input_language               = 0x0051,


   e_message_ime_start_composition        = 0x010D,
   e_message_ime_end_composition          = 0x010E,
   e_message_ime_composition              = 0x010F,

   e_message_device_change                = 0x0219,

   e_message_ime_set_context              = 0x0281,
   e_message_ime_notify                   = 0x0282,
   e_message_ime_composition_full         = 0x0284,
   e_message_ime_select                   = 0x0285,
   e_message_ime_char                     = 0x0286,


   e_message_ime_key_down                 = 0x0290,
   e_message_ime_key_up                   = 0x0291,


   e_message_mouse_leave    =               0x02A3,




//#define e_message_size_parent       0x0361  // lParam = &__SIZEPARENTPARAMS
   e_message_size_parent = 0x0361,


/////////////////////////////////////////////////////////////////////////////
// Internal _ Windows messages (see Technical note TN024 for more details)
// (0x0360 - 0x037F are reserved for aura API)

//#define WM_SETMESSAGESTRING 0x0362  // wParam = nIDS (or 0),
// lParam = pszOther (or nullptr)
   e_message_set_message_string = 0x0362,

//#define WM_IDLEUPDATECMDUI  0x0363  // wParam == bDisableIfNoHandler
   e_message_idle_update_command_user_interface = 0x0363,
//#define WM_COMMANDHELP      0x0365  // lResult = true/false,
   e_message_command_help = 0x0365,
// lParam = dwContext
//#define WM_HELPHITTEST      0x0366  // lResult = dwContext,
   e_message_help_hit_test,
// lParam = __MAKE_LONG(x,y)
//#define WM_EXITHELPMODE     0x0367  // (params unused)
   e_message_exit_help_mode,
//#define WM_RECALCPARENT     0x0368  // force on_layout on frame interaction_impl
//  (only for inplace frame windows)
   e_message_recalc_parent,
//#define WM_SIZECHILD        0x0369  // special notify from COleResizeBar
// wParam = ID of child interaction_impl
// lParam = pRectNew (memory_new position/size_i32)
   e_message_size_child,
//#define WM_KICKIDLE         0x036A  // (params unused) causes idles to kick in
   e_message_kick_idle,
//#define WM_QUERYCENTERWND   0x036B  // lParam = oswindow to use as centering parent
   e_message_query_center_window,
//#define WM_DISABLEMODAL     0x036C  // lResult = 0, disable during modal state
   e_message_disable_modal,
// lResult = 1, don't disable
//#define WM_FLOATSTATUS      0x036D  // wParam combination of FS_* flags below
   e_message_float_status,

// WM_ACTIVATETOPLEVEL is like WM_ACTIVATEAPP but works with hierarchies
//   of mixed processes (as is the case with OLE in-place activation)
//#define WM_ACTIVATETOPLEVEL 0x036E  // wParam = nState (like e_message_activate)
// lParam = pointer to oswindow[2]
//  lParam[0] = oswindow getting e_message_activate
//  lParam[1] = oswindow_Other
   e_message_activate_top_level = 0x036E,
//#define WM_RESERVED_036F   0x036F  // was WM_QUERY3DCONTROLS (now not used)

// Note: Messages 0x0370, 0x0371, and 0x372 were incorrectly used by
//  some versions of Windows.  To remain compatible, aura API does not
//  use messages in that range.
//#define WM_RESERVED_0370    0x0370
//#define WM_RESERVED_0371    0x0371
//#define WM_RESERVED_0372    0x0372

// WM_SOCKET_NOTIFY and WM_SOCKET_DEAD are used internally by aura API's
// Windows sockets implementation.  For more information, see sockcore.cpp
//#define WM_SOCKET_NOTIFY    0x0373
e_message_socket_notify= 0x0373,
//#define WM_SOCKET_DEAD      0x0374
   e_message_socket_dead,
// same as WM_SETMESSAGESTRING except not popped if IsTracking()
//#define WM_POPMESSAGESTRING 0x0375
e_message_pop_message_string,

// WM_HELPPROMPTADDR is used internally to get the address of
//   m_dwPromptContext from the associated frame interaction_impl. This is used
//   during message boxes to setup for F1 help while that msg box is
//   displayed. lResult is the address of m_dwPromptContext.
//#define WM_HELPPROMPTADDR   0x0376
      e_message_help_prompt_address,

// Constants used in DLGINIT resources for OLE control containers
// NOTE: These are NOT real Windows messages they are simply tags
// used in the control resource and are never used as 'messages'
//#define WM_OCC_LOADFROMSTREAM           0x0376
//#define WM_OCC_LOADFROMSTORAGE          0x0377
//#define WM_OCC_INITNEW                  0x0378
//#define WM_OCC_LOADFROMSTREAM_EX        0x037A
//#define WM_OCC_LOADFROMSTORAGE_EX       0x037B

// Marker used while rearranging the message queue
//#define WM_QUEUE_SENTINEL   0x0379
e_message_queue_sentinel =    0x0379,
// Note: Messages 0x037C - 0x37E reserved for future aura API use.
//#define WM_RESERVED_037C    0x037C
//#define WM_RESERVED_037D    0x037D
//#define WM_RESERVED_037E    0x037E

// WM_FORWARDMSG - used by aura to forward a message to another interaction_impl for processing
//   WPARAM - u32 dwUserData - defined by ::account::user
//   LPARAM - MESSAGE * pMsg - a pointer to the MESSAGE structure
//   return value - 0 if the message was not processed, nonzero if it was
//#define WM_FORWARDMSG      0x037F
   e_message_forward_message = 0x037F,
//#define WM_APPEXIT         WM_APP + 1444
   e_message_wm_app = 0x8000,
   e_message_ole_dragenter  = e_message_wm_app + 324,
   e_message_ole_dragover   = e_message_wm_app + 325,
   e_message_ole_dragleave  = e_message_wm_app + 326,
   e_message_ole_dragdrop  = e_message_wm_app + 327,


   e_message_system = e_message_wm_app + 1024,
   e_message_branch,
   e_message_system_command,
   e_message_system_command_probe,
   e_message_system_has_command_handler,
   e_message_system_update,
   e_message_language,
   e_message_application,
   e_message_has_command_handler,
   //e_message_event,
   e_message_thread,
   e_message_desk,
   e_message_display_change,
   e_message_property,
   e_message_midi_attribute,
   e_message_event1,
   e_message_event2_trying_to_remove,
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
   e_message_erase_application,
   e_message_erase_session,
   e_message_switch,
   e_message_subject,


   e_message_backimpact,
   e_message_backimpact_dequeue,

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
   e_message_notify_icon,

   e_message_open_response,
   e_message_application_exit,

   e_message_wave_in_data,

e_message_wm_user = 0x0400,
   e_message_main_post = e_message_wm_user + 23,
   e_message_image_loaded,




};


//
//
//struct emessage
//{
//
//   enum_message m_emessage;
//    
//   emessage(enum_message emessage = e_message_null):m_emessage(emessage) {}
//   emessage(const ::atom & atom) : m_emessage(emessage.m_emessage) {}
//
//   operator enum_message& () { return m_emessage; }
//   operator enum_message() const { return m_emessage; }
//
//};






