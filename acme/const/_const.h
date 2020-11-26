#pragma once


#include "GLOBAL_ID.h"


enum enum_property : ::i64
{

   property_default = 0,
   property_id,
   property_count,

};


enum enum_factory : ::i64
{

   factory_draw2d_bitmap,
   factory_draw2d_brush,
   factory_draw2d_font,
   factory_draw2d_graphics,
   factory_draw2d_image,
   factory_draw2d_path,
   factory_draw2d_pen,
   factory_draw2d_region,
   factory_count,

};


#define SUCCESS 1
#define TIMEOUT (1 << 1)
#define FAILURE (1 << 2)


#define OK SUCCESS





#define NONE_ID 0
#define INVALID_ID ((::u64) -1)



//#define e_object_success (1 << 0)
//#define e_object_timeout (1 << 1)
//#define e_object_failure (1 << 2)
//#define PERSIST_ID (1 << 3)
//#define e_object_factory (1 << 4)
//#define e_object_storing (1 << 5)
//#define e_object_acquire (1 << 6)
//#define DEFAULT_ID (1 << 7)


#define FILEMANAGER_IMPACT 1'001'000
#define COLORSEL_IMPACT 2'001'000
#define FONTSEL_IMPACT 2'002'000

#define TABBED_GROUP 100
#define LIST_GROUP 200
#define FOLDER_SELECTION_LIST_GROUP 300


#define MAIN_IMPACT 1
#define A2_IMPACT 2
#define CONTEXT_MENU_IMPACT 3
#define MENU_IMPACT 4
#define MAIN_SWITCHER_IMPACT 5
#define DEVEDGE_IMPACT 6
#define GCOM_IMPACT 7
#define OPTIONS_IMPACT 8
#define EDIT_IMPACT 9
#define WEATHER_IMPACT 10
#define AUDIO_DEVICES_IMPACT 11
#define TEST_IMPACT 12
#define ACTION_AREA_IMPACT 13
#define DESK_IMPACT 14
#define CONFIGURATION_IMPACT 15
#define PROPERTIES_IMPACT 16
#define HELP_IMPACT 17






enum e_lib_main
{

   lib_main_none = 0,
   lib_main_any = 1 << 0,
   lib_main_process_attach = 1 << 1,
   lib_main_process_detach = 1 << 2,
   lib_main_thread_attach = 1 << 3,
   lib_main_thread_detach = 1 << 4,

};




enum e_default_init
{

   default_init

};


enum enum_subject
{

   e_subject_not_modified,
   e_subject_prepare,
   e_subject_process,
   e_subject_deliver,

};


enum enum_dialog_result
{

   e_dialog_result_none = 0,
   e_dialog_result_ok = 1,
   e_dialog_result_cancel = 2,
   e_dialog_result_abort = 3,
   e_dialog_result_retry = 4,
   e_dialog_result_ignore = 5,
   e_dialog_result_yes = 6,
   e_dialog_result_no = 7,
   e_dialog_result_close = 8,
   e_dialog_result_help = 9,
   e_dialog_result_try_again = 10,
   e_dialog_result_continue = 11,
   e_dialog_result_timeout = 32000,

};


enum enum_type
{
   /// special meaning
   type_parareturn = 0,
   type_new,
   e_type_null,
   type_key_exists,
   type_empty,
   type_empty_argument,
   type_not_found,

   // integral
   //type_block = 1000,
   type_bool,
   type_pbool,
   type_char,
   type_i8 = type_char,
   type_pi8,
   type_byte,
   type_u8 = type_byte,
   type_pu8,
   type_i16,
   type_pi16,
   type_u16,
   type_pu16,
   type_i32,
   type_pi32,
   type_u32,
   type_pu32,
   type_i64,
   type_pi64,
   type_u64,
   type_pu64,

   // floating point
   type_float = 2000,
   type_pfloat,
   type_double,
   type_pdouble,

   // simple classes
   type_string = 4000,
   type_pstring,
   type_type,
   type_secs,
   type_psecs,
   type_millis,
   type_pmillis,
   type_micros,
   type_pmicros,
   type_nanos,
   type_pnanos,
   type_duration,
   type_pduration,
   type_id,
   type_pid,
   type_time,
   type_filetime,
   type_prop,
   type_pvar,
   type_routine,
   type_process,

   // matter classes
   type_element = 8000,
   type_stra,
   type_inta,
   type_vara,
   type_propset,
   type_i64a,
   type_memory,
   type_path,
   //type_image,
   __type_last_element,

   // enum
   type_enum_command = 20000,
   type_enum_status,
   type_enum_check,

};

enum e_trace_category
{
   trace_category_general,
   trace_category_first = trace_category_general,
   trace_category_com,
   trace_category_qi,
   trace_category_registrar,
   trace_category_refcount,
   trace_category_windowing,
   trace_category_controls,
   trace_category_hosting,
   trace_category_dbclient,
   trace_category_dbprovider,
   trace_category_snapin,
   trace_category_notimpl,
   trace_category_allocation,
   trace_category_exception,
   trace_category_time,
   trace_category_cache,
   trace_category_stencil,
   trace_category_string,
   trace_category_map,
   trace_category_util,
   trace_category_security,
   trace_category_sync,
   trace_category_isapi,
   trace_category_user,
   trace_category_user2,
   trace_category_user3,
   trace_category_user4,
   trace_category_appmsg,        // main message pump trace (includes dde)
   trace_category_winmsg,        // windows message tracing
   trace_category_cmdrouting,    // windows command routing trace
   trace_category_ole,          // special ole future trace
   trace_category_database,     // special database trace
   trace_category_internet,     // special internet client trace
   trace_category_dumpcontext,   // traces from dump_context
   trace_category_memory,      // matter non-kernel memory traces
   trace_category_html,         // html traces
   trace_category_socket,      // socket traces
   trace_category_colorertake5,
   trace_category_prodevian, // screen update and window layout
   trace_category_count

};

enum e_trace_level
{

   trace_level_none,
   trace_level_information, // info
   trace_level_warning,     // warn
   trace_level_error,       // error
   trace_level_fatal,       // fatal
   trace_level_count

};

enum e_cursor
{

   cursor_unmodified,
   cursor_draw2d,
   cursor_default,
   cursor_none,
   cursor_system,
   cursor_arrow,
   cursor_hand,
   cursor_text_select,
   cursor_size_top_left,
   cursor_size_top,
   cursor_size_top_right,
   cursor_size_right,
   cursor_size_bottom_right,
   cursor_size_bottom,
   cursor_size_bottom_left,
   cursor_size_left,
   cursor_size_vertical,
   cursor_size_horizontal,
   cursor_move

};

enum enum_object : i64
{

   e_object_none,
   e_object_success = 1 << 0,
   e_object_timeout = 1 << 1,
   e_object_failure = 1 << 2,
   e_object_persist = 1 << 3,
   e_object_factory = 1 << 4,
   e_object_storing = 1 << 5,
   e_object_acquire = 1 << 6,
   e_object_default = 1 << 7,
   e_object_synchro = 1 << 8,
   e_object_changed = 1 << 9,
   aaa_want_to_remove_object_locked = 1 << 10,
   aaa_want_to_remove_object_shared = 1 << 11,
   aaa_want_to_remove_object_read_only_link = 1 << 12,
   e_object_log_disable = 1 << 13,
   e_object_property_set_modified = 1 << 14,
   e_object_default_io_exchange = 1 << 15,
   e_object_alertable_wait = 1 << 16,
   e_object_any_hook = 1 << 17,
   e_object_any_update = (1 << 18) | e_object_any_hook,
   //e_object_set_finish = 1 << 19,
#if OBJ_TYP_CTR
   e_object_obj_typ_ctr = 1 << 20,
#endif

};


#define ALOG_CATEGORY trace_category_general


#include "status.h"



enum e_priority
{

   priority_none = -1,
   priority_idle = 1,
   priority_lowest = 48,
   priority_below_normal,
   priority_normal,
   priority_above_normal,
   priority_highest,
   priority_time_critical = 99

};

//bool CLASS_DECL_ACME succeeded(const ::estatus & estatus);
//bool CLASS_DECL_ACME status_succeeded(i64 i);
//bool CLASS_DECL_ACME failed(const ::estatus & estatus);
//bool CLASS_DECL_ACME status_failed(i64 i);

enum e_thread
{

   thread_none,
   thread_thread,
   thread_service,
   thread_application,
   thread_session,
   thread_system,

};


enum enum_timer : i64;

enum enum_bit
{

   // negative state... bad/failure states

   e_bit_no = -1, // 0xffffffff......
   e_bit_false = -1,

   e_bit_none = 0,
   e_bit_empty = 0, // 0x00000000......
   e_bit_undefined = 0,

   e_bit_yes = 1, // <3tbs
   e_bit_true = 1, // 0x00000001......

   // positive state... good/success states

};




enum enum_clock
{

   e_clock_none,
   e_clock_slow, // indicative usage: few minutes
   e_clock_fast, // indicative usage: few seconds or big second fraction

};








enum e_zorder
{

   zorder_none = 0,
   zorder_bottom,
   zorder_normal_anchor,
   zorder_normal,
   zorder_top,
   zorder_no_top_most,
   zorder_top_most_anchor,
   zorder_top_most,

   zorder_hwnd = -1,


};


enum e_callstack :
   i64
{

   callstack_none,
   callstack_exception = 1 << 0,
   callstack_fork_global = 1 << 1,

};


//#define __epromisse(e, mod) ((e_promisse)((i64)(promisse_##e) + (i64) mod))






enum e_unit_size
{

   unit_size,

};


enum e_display
{

   display_undefined = MINI32,
   display_notify_icon,
   display_default,
   //display_close,
   display_hide,

   display_none = 0,
   display_current,
   display_normal,
   display_restore,
   display_compact,
   display_broad,
   display_iconic,
   display_zoomed,
   display_full_screen,
   display_up,
   display_down,
   display_minimal,
   display_fixed_size,
   display_center,


   display_left = 0x1000,
   display_top = 0x2000,
   display_right = 0x4000,
   display_bottom = 0x8000,
   display_top_left = display_top | display_left,
   display_top_right = display_top | display_right,
   display_bottom_left = display_bottom | display_left,
   display_bottom_right = display_bottom | display_right,
   display_full_left = display_left | display_top | display_bottom,
   display_full_top = display_top | display_left | display_right,
   display_full_right = display_right | display_top | display_bottom,
   display_full_bottom = display_bottom | display_left | display_right,

   display_docking_mask = 0xff00,

   display_command_mask = 0xffff,

};


enum e_activation
{

   activation_none = 0,
   activation_no_activate = 1 << 0,
   activation_set_active = 1 << 1,
   activation_set_foreground = 1 << 2,
   activation_under_mouse_cursor = 1 << 3,
   activation_on_center_of_screen = 1 << 4,
   activation_display_change = 1 << 5,

};


enum e_layout_experience
{

   layout_experience_none,
   layout_experience_moving,
   layout_experience_sizing,
   layout_experience_docking,

};


enum e_appearance
{

   appearance_none = 0,
   appearance_transparent_frame = 1 << 0,

};




enum e_dock
{
   dock_none = 0,
   dock_left = 1,
   dock_top = 2,
   dock_right = 4,
   dock_bottom = 8,
   dock_top_left = dock_top | dock_left,
   dock_top_right = dock_top | dock_right,
   dock_bottom_left = dock_bottom | dock_left,
   dock_bottom_right = dock_bottom | dock_right,
   dock_all = dock_left | dock_top | dock_right | dock_bottom,
};

enum e_grip
{
   grip_none = 0,
   grip_left = 1 << 0,
   grip_top = 1 << 1,
   grip_right = 1 << 2,
   grip_bottom = 1 << 3,
   grip_top_left = 1 << 4,
   grip_top_right = 1 << 5,
   grip_bottom_left = 1 << 6,
   grip_bottom_right = 1 << 7,
   grip_all = grip_left | grip_top | grip_right | grip_bottom |
   grip_top_left | grip_top_right |
   grip_bottom_left | grip_bottom_right,
};


enum e_border
{

   border_none = 0,
   border_left = 1,
   border_top = 2,
   border_right = 4,
   border_bottom = 8,
   border_top_left = border_top | border_left,
   border_top_right = border_top | border_right,
   border_top_right_bottom = border_top | border_right | border_bottom,
   border_bottom_left = border_bottom | border_left,
   border_bottom_right = border_bottom | border_right,
   border_bottom_left_top = border_bottom | border_left | border_top,
   border_left_top_right = border_left | border_top | border_right,
   border_right_bottom_left = border_right | border_bottom | border_left,
   border_all = border_left | border_top | border_right | border_bottom,

};



enum e_window_flag
{

   window_flag_none,
   window_flag_is_window = 1 << 0,
   window_flag_enable = 1 << 1,
   window_flag_focus = 1 << 2,
   window_flag_active = 1 << 3,
   window_flag_redraw_in_queue = 1 << 4,
   window_flag_visual_changed = 1 << 5,
   window_flag_auto_prodevian_on_show = 1 << 6,
   window_flag_on_show_window_visible = 1 << 7,
   window_flag_on_show_window_screen_visible = 1 << 8,
   window_flag_satellite_window = 1 << 9,
   window_flag_graphical = 1 << 10,
   window_flag_disable_window_placement_snapping = 1 << 11,
   window_flag_embedded_prodevian = 1 << 12,
   window_flag_arbitrary_positioning = 1 << 13,
   window_flag_desktop_window = 1 << 14,
   window_flag_dock_window = 1 << 15,
   window_flag_load_window_rect_on_impl = 1 << 17,
   window_flag_window_created = 1 << 18,
   window_flag_updown = 1 << 19,
   window_flag_postpone_visual_update = 1 << 20,
   window_flag_miniaturizable = 1 << 21,
   window_flag_auto_store_window_rect = 1 << 22,
   window_flag_pending_save_window_rect = 1 << 23,
   window_flag_loading_window_rect = 1 << 24,
   window_flag_main_frame = 1 << 25,
   window_flag_destroying = 1 << 26,
   window_flag_not_visible = 1 << 27,

};


#ifndef WM_USER
#define WM_USER 0x0400
#endif // WM_USER

#ifndef CLASS_DECL_ACME
#define CLASS_DECL_ACME
#endif // CLASS_DECL_ACME
#ifndef WM_APP
#define WM_APP 0x8000
#endif




enum e_system_message
{

   system_message_none,
   system_message_create,
   system_message_meta,
   system_message_method,
   //system_message_pred,
   //system_message_runnable,

};


/*


enum enum_method
{

   e_method_create,
   e_method_destroy,

};


enum enum_future
{

   e_future_finish,
   e_future_dialog_result,
   e_future_complete,

};


*/

//#ifndef WINDOWS_DESKTOP
//#include "acme/os/cross/windows/message_box.h"
//#endif


enum enum_message_box
{

   e_message_box_ok = 0x00000000L,
   e_message_box_yes_no = 0x00000003L,
   e_message_box_yes_no_cancel = 0x00000003L,
   e_message_box_icon_error = 0x00000010L,
   e_message_box_icon_exclamation = 0x00000030L,
   e_message_box_icon_question = 0x00000020L,
   e_message_box_icon_asterisk = 0x00000040L,
   e_message_box_icon_hand = e_message_box_icon_error,
   e_message_box_icon_warning = e_message_box_icon_exclamation,
   e_message_box_icon_information = e_message_box_icon_asterisk,
   e_message_box_icon_stop = e_message_box_icon_asterisk,
   e_message_box_system_modal = 0x00001000L,

};


enum enum_relative
{

   e_relative_none,
   e_relative_first_child,
   e_relative_last_child,
   e_relative_first_sibling,
   e_relative_previous_sibling,
   e_relative_next_sibling,
   e_relative_last_sibling,
   e_relative_owner,

};


#include "message.h"


