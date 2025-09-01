#pragma once


enum enum_message : unsigned int
{

   ::user::e_message_undefined = UINT32_MAX,

   ::user::e_message_null = 0, // 0

   ::user::e_message_create = 1, //1,
   ::user::e_message_destroy = 2, //,= 2,
   ::user::e_message_reposition = 3,//,3,
   ::user::e_message_size = 5,//,5,
   ::user::e_message_activate = 6,//,6,
   ::user::e_message_set_focus = 7,//,7,
   ::user::e_message_kill_focus = 8,// ,8,
   ::user::e_message_enable = 10,//,10,
   ::user::e_message_set_text = 12,//, 12,
   ::user::e_message_paint = 15,//,15,
   ::user::e_message_close = 16,//16,
   ::user::e_message_quit = 18,//,18,

   ::user::e_message_erase_background  = 20, // 0x0014

   ::user::e_message_show_window = 24, // 0x0018
   ::user::e_message_setting_change = 26,
   ::user::e_message_activate_app = 28, // 0x001C
   ::user::e_message_font_change = 29, // 0x001D
   ::user::e_message_set_cursor = 32, // 0x0020
   ::user::e_message_mouse_activate = 33, // 0x0021

   ::user::e_message_get_min_max_info = 36, // 0x0024
   ::user::e_message_wm_notify = 78, // 0x004E
   ::user::e_message_context_menu = 0x007B,

   ::user::e_message_key_first = 256,
   ::user::e_message_key_down = 256,
   ::user::e_message_key_up = 257,
   ::user::e_message_char = 258,
   ::user::e_message_dead_char = 259,
   ::user::e_message_sys_key_down = 260,
   ::user::e_message_sys_key_up = 261,
   ::user::e_message_sys_char = 262,
   ::user::e_message_sys_dead_char = 263,
   ::user::e_message_uni_char = 265,
   ::user::e_message_key_last = 265,

   ::user::e_message_scroll_x = 0x0114,
   ::user::e_message_scroll_y = 0x0115,

   ::user::e_message_non_client_create    =                 0x0081,
   ::user::e_message_non_client_destroy    =                0x0082,
   ::user::e_message_non_client_calc_size   =                0x0083,
   ::user::e_message_non_client_hit_test     =               0x0084,
   ::user::e_message_non_client_paint      =                0x0085,
   ::user::e_message_non_client_activate   =                0x0086,

   ::user::e_message_measure_item     =             0x002C,
   ::user::e_message_window_position_changing    =        0x0046,
   ::user::e_message_window_position_changed   =          0x0047,

   ::user::e_message_non_client_mouse_move           =    0x00A0,
   ::user::e_message_non_client_left_button_down     =        0x00A1,
   ::user::e_message_non_client_left_button_up       =        0x00A2,
   ::user::e_message_command  =                    0x0111,
   ::user::e_message_timer      =                  0x0113,
   ::user::e_message_initialize_menu_popup       =         0x0117,


   ::user::e_message_mouse_first = 512,
   ::user::e_message_mouse_move = 512,
   ::user::e_message_left_button_down = 513,
   ::user::e_message_left_button_up = 514,
   ::user::e_message_left_button_double_click = 515,
   ::user::e_message_right_button_down = 516,
   ::user::e_message_right_button_up = 517,
   ::user::e_message_right_button_double_click = 518,
   ::user::e_message_middle_button_down = 519,
   ::user::e_message_middle_button_up = 520,
   ::user::e_message_middle_button_double_click = 521,
   ::user::e_message_mouse_wheel = 522,
   ::user::e_message_mouse_last = 526,

   ::user::e_message_parent_base = 0x6000,

   ::user::e_message_parent_mouse_move = ::user::e_message_parent_base + ::user::e_message_mouse_move,
   ::user::e_message_parent_mouse_first = ::user::e_message_parent_base + ::user::e_message_mouse_first,
   ::user::e_message_parent_left_button_down = ::user::e_message_parent_base + ::user::e_message_left_button_down,
   ::user::e_message_parent_left_button_up = ::user::e_message_parent_base + ::user::e_message_left_button_up,
   ::user::e_message_parent_left_button_double_click = ::user::e_message_parent_base + ::user::e_message_left_button_double_click,
   ::user::e_message_parent_right_button_down = ::user::e_message_parent_base + ::user::e_message_right_button_down,
   ::user::e_message_parent_right_button_up = ::user::e_message_parent_base + ::user::e_message_right_button_up,
   ::user::e_message_parent_right_button_double_click = ::user::e_message_parent_base + ::user::e_message_right_button_double_click,
   ::user::e_message_parent_middle_button_down = ::user::e_message_parent_base + ::user::e_message_middle_button_down,
   ::user::e_message_parent_middle_button_up = ::user::e_message_parent_base + ::user::e_message_middle_button_up,
   ::user::e_message_parent_middle_button_double_click = ::user::e_message_parent_base + ::user::e_message_middle_button_double_click,
   ::user::e_message_parent_mouse_wheel = ::user::e_message_parent_base + ::user::e_message_mouse_wheel,
   ::user::e_message_parent_mouse_last = ::user::e_message_parent_base + ::user::e_message_mouse_last,



   ::user::e_message_capture_changed = 533,

   
   ::user::e_message_input_language               = 0x0051,


   ::user::e_message_ime_start_composition        = 0x010D,
   ::user::e_message_ime_end_composition          = 0x010E,
   ::user::e_message_ime_composition              = 0x010F,

   ::user::e_message_device_change                = 0x0219,

   ::user::e_message_ime_set_context              = 0x0281,
   ::user::e_message_ime_notify                   = 0x0282,
   ::user::e_message_ime_composition_full         = 0x0284,
   ::user::e_message_ime_select                   = 0x0285,
   ::user::e_message_ime_char                     = 0x0286,


   ::user::e_message_ime_key_down                 = 0x0290,
   ::user::e_message_ime_key_up                   = 0x0291,


   ::user::e_message_mouse_leave    =               0x02A3,




//#define ::user::e_message_size_parent       0x0361  // lParam = &__SIZEPARENTPARAMS
   ::user::e_message_size_parent = 0x0361,


/////////////////////////////////////////////////////////////////////////////
// Internal _ Windows messages (see Technical note TN024 for more details)
// (0x0360 - 0x037F are reserved for aura API)

//#define WM_SETMESSAGESTRING 0x0362  // wParam = nIDS (or 0),
// lParam = pszOther (or nullptr)
   ::user::e_message_set_message_string = 0x0362,

//#define WM_IDLEUPDATECMDUI  0x0363  // wParam == bDisableIfNoHandler
   ::user::e_message_idle_update_command_user_interface = 0x0363,
//#define WM_COMMANDHELP      0x0365  // lResult = true/false,
   ::user::e_message_command_help = 0x0365,
// lParam = dwContext
//#define WM_HELPHITTEST      0x0366  // lResult = dwContext,
   ::user::e_message_help_hit_test,
// lParam = make_int(x,y)
//#define WM_EXITHELPMODE     0x0367  // (params unused)
   ::user::e_message_exit_help_mode,
//#define WM_RECALCPARENT     0x0368  // force on_layout on frame interaction_impl
//  (only for inplace frame windows)
   ::user::e_message_recalc_parent,
//#define WM_SIZECHILD        0x0369  // special notify from COleResizeBar
// wParam = ID of child interaction_impl
// lParam = pRectNew (aaa_memory_new position/int_size)
   ::user::e_message_size_child,
//#define WM_KICKIDLE         0x036A  // (params unused) causes idles to kick in
   ::user::e_message_kick_idle,
//#define WM_QUERYCENTERWND   0x036B  // lParam = oswindow to use as centering parent
   ::user::e_message_query_center_window,
//#define WM_DISABLEMODAL     0x036C  // lResult = 0, disable during modal state
   ::user::e_message_disable_modal,
// lResult = 1, don't disable
//#define WM_FLOATSTATUS      0x036D  // wParam combination of FS_* flags below
   ::user::e_message_float_status,

// WM_ACTIVATETOPLEVEL is like WM_ACTIVATEAPP but works with hierarchies
//   of mixed processes (as is the case with OLE in-place activation)
//#define WM_ACTIVATETOPLEVEL 0x036E  // wParam = nState (like ::user::e_message_activate)
// lParam = pointer to oswindow[2]
//  lParam[0] = oswindow getting ::user::e_message_activate
//  lParam[1] = oswindow_Other
   ::user::e_message_activate_top_level = 0x036E,
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
::user::e_message_socket_notify= 0x0373,
//#define WM_SOCKET_DEAD      0x0374
   ::user::e_message_socket_dead,
// same as WM_SETMESSAGESTRING except not popped if IsTracking()
//#define WM_POPMESSAGESTRING 0x0375
::user::e_message_pop_message_string,

// WM_HELPPROMPTADDR is used internally to get the address of
//   m_dwPromptContext from the associated frame interaction_impl. This is used
//   during message boxes to setup for F1 help while that msg box is
//   displayed. lResult is the address of m_dwPromptContext.
//#define WM_HELPPROMPTADDR   0x0376
      ::user::e_message_help_prompt_address,

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
::user::e_message_queue_sentinel =    0x0379,
// Note: Messages 0x037C - 0x37E reserved for future aura API use.
//#define WM_RESERVED_037C    0x037C
//#define WM_RESERVED_037D    0x037D
//#define WM_RESERVED_037E    0x037E

// WM_FORWARDMSG - used by aura to forward a message to another interaction_impl for processing
//   WPARAM - unsigned int dwUserData - defined by ::account::user
//   LPARAM - MESSAGE * pMsg - a pointer to the MESSAGE structure
//   return value - 0 if the message was not processed, nonzero if it was
//#define WM_FORWARDMSG      0x037F
::user::e_message_forward_message = 0x037F,

::user::e_message_user = 0x0400,
::user::e_message_main_post = ::user::e_message_user + 23,
::user::e_message_image_loaded,



//#define WM_APPEXIT         WM_APP + 1444



::user::e_message_application = 0x8000,
::user::e_message_ole_dragenter = ::user::e_message_application + 324,
::user::e_message_ole_dragover = ::user::e_message_application + 325,
::user::e_message_ole_dragleave = ::user::e_message_application + 326,
::user::e_message_ole_dragdrop = ::user::e_message_application + 327,
::user::e_message_application_exit = ::user::e_message_application + 1444,

::user::e_message_system = ::user::e_message_application + 2048,
::user::e_message_branch,
::user::e_message_system_command,
::user::e_message_system_command_probe,
::user::e_message_system_has_command_handler,
::user::e_message_system_update,
::user::e_message_language,
::user::e_message_has_command_handler,
::user::e_message_thread,
::user::e_message_desk,
::user::e_message_display_change,
::user::e_message_property,
::user::e_message_midi_attribute,
::user::e_message_event1,
::user::e_message_event2_trying_to_remove,
::user::e_message_simple_command,
::user::e_message_set_schema,
::user::e_message_post_user,
::user::e_message_update_notify_icon,
::user::e_message_drag_and_drop,
::user::e_message_after_create,
::user::e_message_frame_initial_update,
::user::e_message_redraw,
::user::e_message_apply_visual_deprecated_schedule_window_show,
::user::e_message_destroy_window,
::user::e_message_run,
::user::e_message_done,
::user::e_message_do_show_window,
::user::e_message_auratype_key_down,
::user::e_message_auratype_key_up,
::user::e_message_auraclick_mouse,
::user::e_message_update_device_list,
//::user::e_message_erase_application,
//::user::e_message_erase_session,
::user::e_message_switch,
::user::e_message_subject,


::user::e_message_backimpact,
::user::e_message_backimpact_dequeue,

::user::e_message_graphical_command,


::user::e_message_recorder_command,
::user::e_message_recorder_event,


::user::e_message_player_open,
::user::e_message_player_start,
::user::e_message_player_close,
::user::e_message_player_filled,
::user::e_message_player_free,
::user::e_message_player_stop,

::user::e_message_player_command,
::user::e_message_player_event,
::user::e_message_player_notify_event,

::user::e_message_midi_sequence_event,

::user::e_message_prebuffer_done,

::user::e_message_need_load_form_data,
::user::e_message_need_save_form_data,

::user::e_message_text_composition,

::user::e_message_change_experience,
::user::e_message_notify_icon,

::user::e_message_open_response,

::user::e_message_wave_in_data,




::user::e_message_hyper_space = 0x8000000,
::user::e_message_click,
::user::e_message_start_tab_drag,
::user::e_message_tool_tip_text,
::user::e_message_document



};


