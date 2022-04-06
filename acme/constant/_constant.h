#pragma once


#include "GLOBAL_ID.h"


enum enum_property : ::i64
{

   e_property_default = 0,
   e_property_id,
   e_property_count,

};


enum enum_factory : ::i64
{

   e_factory_draw2d_bitmap,
   e_factory_draw2d_brush,
   e_factory_draw2d_font,
   e_factory_draw2d_graphics,
   e_factory_draw2d_image,
   e_factory_draw2d_path,
   e_factory_draw2d_pen,
   e_factory_draw2d_region,
   e_factory_count,

};


#define SUCCESS 1
#define TIMEOUT (1 << 1)
#define FAILURE (1 << 2)


#define OK SUCCESS


#define NONE_ID 0
#define INVALID_ID ((::u64) -1)


//#define e_flag_success (1 << 0)
//#define e_flag_timeout (1 << 1)
//#define e_flag_failure (1 << 2)
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
#define FIRST_PANE 18


enum enum_library_main
{


   e_library_main_none = 0,
   e_library_main_any = 1 << 0,
   e_library_main_process_attach = 1 << 1,
   e_library_main_process_detach = 1 << 2,
   e_library_main_thread_attach = 1 << 3,
   e_library_main_thread_detach = 1 << 4,


};


//#include "topic.h"


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
   e_type_parareturn = 0,
   e_type_new,
   e_type_null,
   e_type_key_exists,
   e_type_empty,
   e_type_empty_argument,
   e_type_not_found,

   // integral
   //type_block = 1000,
   e_type_bool,
   e_type_pbool,
   e_type_char,
   e_type_i8 = e_type_char,
   e_type_pi8,
   e_type_byte,
   e_type_u8 = e_type_byte,
   e_type_pu8,
   e_type_i16,
   e_type_pi16,
   e_type_u16,
   e_type_pu16,
   e_type_i32,
   e_type_pi32,
   e_type_u32,
   e_type_pu32,
   e_type_i64,
   e_type_pi64,
   e_type_u64,
   e_type_pu64,

   // floating point_i32
   e_type_f32 = 2000,
   e_type_pfloat,
   e_type_f64,
   e_type_pdouble,

   // simple classes
   e_type_string = 4000,
   e_type_pstring,
   e_type_type,
   e_type_integral_nanosecond,
   e_type_pintegral_nanosecond,
   e_type_integral_microsecond,
   e_type_pintegral_microsecond,
   e_type_integral_millisecond,
   e_type_pintegral_millisecond,
   e_type_integral_second,
   e_type_pintegral_second,
   e_type_integral_minute,
   e_type_pintegral_minute,
   e_type_integral_hour,
   e_type_pintegral_hour,
   e_type_integral_day,
   e_type_pintegral_day,
   e_type_floating_nanosecond,
   e_type_pfloating_nanosecond,
   e_type_floating_microsecond,
   e_type_pfloating_microsecond,
   e_type_floating_millisecond,
   e_type_pfloating_millisecond,
   e_type_floating_second,
   e_type_pfloating_second,
   e_type_floating_minute,
   e_type_pfloating_minute,
   e_type_floating_hour,
   e_type_pfloating_hour,
   e_type_floating_day,
   e_type_pfloating_day,
   e_type_duration,
   e_type_pduration,
   e_type_id,
   e_type_pid,
   e_type_time,
   e_type_file_time,
   e_type_property,
   e_type_payload_pointer,
   e_type_color,
   e_type_hls,
   //e_type_process,

   // matter classes
   e_type_element = 8000,
   e_type_string_array,
   e_type_i32_array,
   e_type_payload_array,
   e_type_property_set,
   e_type_i64_array,
   e_type_memory,
   e_type_path,
   e_type_routine,
   e_type_last_element,

   // enum
   e_type_enum_command = 20000,
   e_type_enum_status,
   e_type_enum_check,
   e_type_enum_flag


};


enum enum_trace_category
{


   e_trace_category_general,
   e_trace_category_first = e_trace_category_general,
   e_trace_category_com,
   e_trace_category_qi,
   e_trace_category_registrar,
   e_trace_category_refcount,
   e_trace_category_windowing,
   e_trace_category_controls,
   e_trace_category_hosting,
   e_trace_category_dbclient,
   e_trace_category_dbprovider,
   e_trace_category_snapin,
   e_trace_category_notimpl,
   e_trace_category_allocation,
   e_trace_category_exception,
   e_trace_category_time,
   e_trace_category_cache,
   e_trace_category_stencil,
   e_trace_category_string,
   e_trace_category_map,
   e_trace_category_util,
   e_trace_category_security,
   e_trace_category_sync,
   e_trace_category_isapi,
   e_trace_category_user,
   e_trace_category_user2,
   e_trace_category_user3,
   e_trace_category_user4,
   e_trace_category_appmsg,        // main message pump trace (includes dde)
   e_trace_category_winmsg,        // windows message tracing
   e_trace_category_cmdrouting,    // windows command routing trace
   e_trace_category_ole,          // special ole future trace
   e_trace_category_database,     // special database trace
   e_trace_category_internet,     // special internet client trace
   e_trace_category_dumpcontext,   // traces from dump_context
   e_trace_category_memory,      // matter non-kernel memory traces
   e_trace_category_html,         // html traces
   e_trace_category_socket,      // socket traces
   e_trace_category_colorertake5,
   e_trace_category_prodevian, // screen update and window layout
   e_trace_category_count


};


enum enum_trace_level
{


   e_trace_level_none,
   e_trace_level_information, // info
   e_trace_level_warning,     // warn
   e_trace_level_error,       // error
   e_trace_level_fatal,       // fatal
   e_trace_level_count


};


enum enum_object : i64
{


   e_object_none,
   aaa_want_to_erase_object_locked = 1 << 10,
   aaa_want_to_erase_object_shared = 1 << 11,
   aaa_want_to_erase_object_read_only_link = 1 << 12,
   e_object_log_disable = 1 << 13,
   e_object_property_set_modified = 1 << 14,
   e_object_default_io_exchange = 1 << 15,
   e_object_alertable_wait = 1 << 16,
   e_object_any_hook = 1 << 17,
   //e_object_any_hook = 1 << 17,
   //e_object_any_update = (1 << 18) | e_object_any_hook,
   //e_object_composite = 1 << 19,
#if OBJECT_TYPE_COUNTER
   e_object_object_type_counter = 1 << 20,
#endif
   e_object_synchronous = 1 << 21,
   e_object_shared = 1 << 22,


};


#define ALOG_CATEGORY trace_category_general


#include "status.h"


enum enum_priority
{


   e_priority_none = -1,
   e_priority_idle = 1,
   e_priority_lowest = 48,
   e_priority_below_normal,
   e_priority_normal,
   e_priority_above_normal,
   e_priority_highest,
   e_priority_time_critical = 99


};


//bool CLASS_DECL_ACME succeeded(const ::e_status & estatus);
//bool CLASS_DECL_ACME status_succeeded(i64 i);
//bool CLASS_DECL_ACME failed(const ::e_status & estatus);
//bool CLASS_DECL_ACME status_failed(i64 i);


enum enum_task_flag
{

   e_task_flag_fast_path, // 0 --> 1 << 0
   e_task_flag_compress_is_dir, // 1 --> 1 << 1
   e_task_flag_is_timer, // 2 --> 1 << 2
   e_task_flag_resolve_alias, // 3 -->
   e_task_flag_prevent_bad_status_exception,
   e_task_flag_using_sockets,
   e_task_flag_avoid_parsing_exception,
   e_task_flag_avoid_numeric_parsing_exception,
   e_task_flag_avoid_datetime_parsing_exception,
   e_task_flag_dynamic_source_script_instance,
   e_task_flag_count,

};


enum enum_task_payload
{

   e_task_payload,
   e_task_payload_count,

};


enum enum_thread_context
{

   
   e_thread_context_none,
   e_thread_context_thread,
   e_thread_context_service,
   e_thread_context_application,
   e_thread_context_session,
   e_thread_context_system,


};


enum enum_timer : i64;


enum enum_boolean
{


   // negative state... bad/failure states

   e_boolean_no = -1, // 0xffffffff......
   e_boolean_false = -1,

   e_boolean_none = 0,
   e_boolean_empty = 0, // 0x00000000......
   e_boolean_undefined = 0,

   e_boolean_yes = 1, // <3tbs
   e_boolean_true = 1, // 0x00000001......

   // positive state... good/success states


};


enum enum_zorder
{

   e_zorder_none = 0,
   e_zorder_bottom,
   e_zorder_normal_anchor,
   e_zorder_normal,
   e_zorder_top,
   e_zorder_no_top_most,
   e_zorder_top_most_anchor,
   e_zorder_top_most,

   e_zorder_hwnd = -1,


};


//enum e_callstack :
//   i64
//{
//
//
//   callstack_none,
//   callstack_exception = 1 << 0,
//   callstack_fork_global = 1 << 1,
//
//
//};


enum enum_display
{


   e_display_undefined = MINI32,
   e_display_notify_icon,
   e_display_default,
   //display_close,
   e_display_hide,

   e_display_none = 0,
   e_display_current,
   e_display_normal,
   e_display_restore,
   e_display_compact,
   e_display_broad,
   e_display_iconic,
   e_display_zoomed,
   e_display_full_screen,
   e_display_up,
   e_display_down,
   e_display_minimal,
   e_display_fixed_size,
   e_display_center,


   e_display_left = 0x1000,
   e_display_top = 0x2000,
   e_display_right = 0x4000,
   e_display_bottom = 0x8000,
   e_display_top_left = e_display_top | e_display_left,
   e_display_top_right = e_display_top | e_display_right,
   e_display_bottom_left = e_display_bottom | e_display_left,
   e_display_bottom_right = e_display_bottom | e_display_right,
   e_display_full_left = e_display_left | e_display_top | e_display_bottom,
   e_display_full_top = e_display_top | e_display_left | e_display_right,
   e_display_full_right = e_display_right | e_display_top | e_display_bottom,
   e_display_full_bottom = e_display_bottom | e_display_left | e_display_right,

   e_display_docking_mask = 0xff00,

   e_display_command_mask = 0xffff,


};


enum enum_activation
{


   e_activation_default = 0,
   e_activation_no_activate = 1 << 0,
   e_activation_set_active = 1 << 1,
   e_activation_set_foreground = 1 << 2,
   e_activation_under_mouse_cursor = 1 << 3,
   e_activation_on_center_of_screen = 1 << 4,
   e_activation_display_change = 1 << 5,


};


enum enum_layout_experience
{


   e_layout_experience_none,
   e_layout_experience_moving,
   e_layout_experience_sizing,
   e_layout_experience_docking,


};


enum enum_appearance
{

   
   e_appearance_none = 0,
   e_appearance_transparent_frame = 1 << 0,


};


enum enum_dock
{
   

   e_dock_none = 0,
   e_dock_left = 1,
   e_dock_top = 2,
   e_dock_right = 4,
   e_dock_bottom = 8,
   e_dock_top_left = e_dock_top | e_dock_left,
   e_dock_top_right = e_dock_top | e_dock_right,
   e_dock_bottom_left = e_dock_bottom | e_dock_left,
   e_dock_bottom_right = e_dock_bottom | e_dock_right,
   e_dock_all = e_dock_left | e_dock_top | e_dock_right | e_dock_bottom,


};


enum enum_grip
{


   e_grip_none = 0,
   e_grip_left = 1 << 0,
   e_grip_top = 1 << 1,
   e_grip_right = 1 << 2,
   e_grip_bottom = 1 << 3,
   e_grip_top_left = 1 << 4,
   e_grip_top_right = 1 << 5,
   e_grip_bottom_left = 1 << 6,
   e_grip_bottom_right = 1 << 7,
   e_grip_all = e_grip_left | e_grip_top | e_grip_right | e_grip_bottom |
   e_grip_top_left | e_grip_top_right |
   e_grip_bottom_left | e_grip_bottom_right,


};


enum enum_border
{


   e_border_none = 0,
   e_border_left = 1,
   e_border_top = 2,
   e_border_right = 4,
   e_border_bottom = 8,
   e_border_top_left = e_border_top | e_border_left,
   e_border_top_right = e_border_top | e_border_right,
   e_border_top_right_bottom = e_border_top | e_border_right | e_border_bottom,
   e_border_bottom_left = e_border_bottom | e_border_left,
   e_border_bottom_right = e_border_bottom | e_border_right,
   e_border_bottom_left_top = e_border_bottom | e_border_left | e_border_top,
   e_border_left_top_right = e_border_left | e_border_top | e_border_right,
   e_border_right_bottom_left = e_border_right | e_border_bottom | e_border_left,
   e_border_all = e_border_left | e_border_top | e_border_right | e_border_bottom,


};


enum enum_window_flag
{


   e_window_flag_none,
   e_window_flag_is_window = 1 << 0,
   e_window_flag_enable = 1 << 1,
   e_window_flag_focus = 1 << 2,
   e_window_flag_active = 1 << 3,
   e_window_flag_redraw_in_queue = 1 << 4,
   e_window_flag_visual_changed = 1 << 5,
   e_window_flag_auto_prodevian_on_show = 1 << 6,
   e_window_flag_on_show_window_visible = 1 << 7,
   e_window_flag_on_show_window_screen_visible = 1 << 8,
   e_window_flag_satellite_window = 1 << 9,
   e_window_flag_graphical = 1 << 10,
   e_window_flag_disable_window_placement_snapping = 1 << 11,
   e_window_flag_embedded_prodevian = 1 << 12,
   e_window_flag_arbitrary_positioning = 1 << 13,
   e_window_flag_desktop_window = 1 << 14,
   e_window_flag_dock_window = 1 << 15,
   e_window_flag_load_window_rect_on_impl = 1 << 17,
   e_window_flag_window_created = 1 << 18,
   e_window_flag_updown = 1 << 19,
   e_window_flag_postpone_visual_update = 1 << 20,
   e_window_flag_miniaturizable = 1 << 21,
   e_window_flag_auto_store_window_rect = 1 << 22,
   e_window_flag_pending_save_window_rect = 1 << 23,
   e_window_flag_loading_window_rect = 1 << 24,
   e_window_flag_main_frame = 1 << 25,
   e_window_flag_destroying = 1 << 26,
   e_window_flag_not_visible = 1 << 27,
   e_window_flag_satellite_window_if_child = 1 << 28,
   e_window_flag_embedded_prodevian_if_child = 1 << 29,
   e_window_flag_composite = 1 << 30,


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


enum enum_system_message
{


   e_system_message_none,
   e_system_message_create,
   e_system_message_meta,
   e_system_message_method,


};


enum enum_message_box
{


   e_message_box_ok                    = 0x00000000L,
   e_message_box_ok_cancel             = 0x00000001L,
   e_message_box_abort_retry_ignore    = 0x00000002L,
   e_message_box_yes_no_cancel         = 0x00000003L,
   e_message_box_yes_no                = 0x00000004L,
   e_message_box_retry_cancel          = 0x00000005L,
   e_message_box_cancel_try_continue   = 0x00000006L,
   e_message_box_icon_error            = 0x00000010L,
   e_message_box_icon_exclamation      = 0x00000030L,
   e_message_box_icon_question         = 0x00000020L,
   e_message_box_icon_asterisk         = 0x00000040L,
   e_message_box_default_button_1      = 0x00000000L,
   e_message_box_default_button_2      = 0x00000100L,
   e_message_box_default_button_3      = 0x00000200L,
   e_message_box_default_button_4      = 0x00000300L,
   e_message_box_button_mask           = 0x00000300L,
   
   
   e_message_box_icon_hand             = e_message_box_icon_error,
   e_message_box_icon_warning          = e_message_box_icon_exclamation,
   e_message_box_icon_information      = e_message_box_icon_asterisk,
   e_message_box_icon_stop             = e_message_box_icon_asterisk,
   
   
   e_message_box_system_modal          = 0x00001000L,

   
   e_message_box_type_mask             = 0x0000000FL,
   e_message_box_icon_mask             = 0x000000F0L,
   e_message_box_default_button_mask   = 0x00000F00L,
   e_message_box_mode_mask             = 0x00003000L,
   e_message_box_miscellaneous_mask    = 0x0000C000L,


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


enum enum_operating_system
{


   e_operating_system_unknown = -1,
   e_operating_system_none = 0,
   e_operating_system_current,
   e_operating_system_windows,
   e_operating_system_macos,
   e_operating_system_ios,
   e_operating_system_linux,
   e_operating_system_android,
   e_operating_system_unix,


};


enum enum_linux_distribution
{


   e_linux_distribution_not_initialized = -2,
   e_linux_distribution_unknown = -1,
   e_linux_distribution_default = 0,
   e_linux_distribution_ubuntu,
   e_linux_distribution_manjaro,
   e_linux_distribution_fedora,
   e_linux_distribution_centos,


};


enum enum_service_status
{


   e_service_status_stopped,
   e_service_status_starting,
   e_service_status_running,
   e_service_status_stopping,


};


#include "parallelization.h"



