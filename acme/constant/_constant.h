#pragma once


//#include "GLOBAL_ID.h"

enum enum_digit_case : int
{

   e_digit_case_lower = (int) 'a',
   e_digit_case_upper = (int) 'A',

};


enum enum_optional
{

   e_optional,

};


enum enum_property : ::iptr
{

   e_property_default = 0,
   e_property_id,
   e_property_count,

};


enum enum_factory : ::iptr
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


#define OLDOK OK
#undef OK

enum ENUM_I32 : int
{

   SUCCESS = 1,
   TIMEOUT = (1 << 1),
   FAILURE = (1 << 2),
   OK = SUCCESS,
   NONE_ID = 0,


};


#define OK OLDOK


enum ENUM_UPTR : ::uptr
{

   INVALID_ID = ((::uptr) -1),

};




//#define e_flag_success (1 << 0)
//#define e_flag_timeout (1 << 1)
//#define e_flag_failure (1 << 2)
//#define PERSIST_ID (1 << 3)
//#define e_object_factory (1 << 4)
//#define e_object_storing (1 << 5)
//#define e_object_acquire (1 << 6)
//#define DEFAULT_ID (1 << 7)
enum ENUM_IMPACT : ::iptr
{

BASE_IMPACT= 100'000,


FILEMANAGER_IMPACT =1'001'000,
COLORSEL_IMPACT =2'001'000,
FONTSEL_IMPACT =2'002'000,

TABBED_GROUP =100,
LIST_GROUP =200,
FOLDER_SELECTION_LIST_GROUP =300,


MAIN_IMPACT =1,
A2_IMPACT =2,
CONTEXT_MENU_IMPACT= 3,
MENU_IMPACT =4,
MAIN_SWITCHER_IMPACT =5,
DEVEDGE_IMPACT= 6,
GCOM_IMPACT =7,
OPTIONS_IMPACT =8,
EDIT_IMPACT =9,
WEATHER_IMPACT =10,
AUDIO_DEVICES_IMPACT= 11,
TEST_IMPACT =12,
ACTION_AREA_IMPACT =13,
DESK_IMPACT =14,
CONFIGURATION_IMPACT =15,
PROPERTIES_IMPACT= 16,
HELP_IMPACT =17,
FIRST_PANE =18,
APP_OPTIONS_IMPACT = 19,
CONTEXT_OPTIONS_IMPACT = 20,
ABOUT_IMPACT = 21,
};


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


enum enum_dialog_result : ::iptr
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
   e_type_bool = 1024,
   e_type_char,
   e_type_unsigned_char,
   e_type_short,
   e_type_unsigned_short,
   e_type_int,
   e_type_unsigned_int,
   //e_type_long,
   //e_type_unsigned_long,
   e_type_long_long,
   e_type_unsigned_long_long,


   // floating int_point
   e_type_float = 2048,
   e_type_double,

   // simple classes
   e_type_string = 4096,
   e_type_pstring,
   e_type_ansi_range,
   e_type_type,
   //e_type_integral_nanosecond,
   //e_type_pintegral_nanosecond,
   //e_type_integral_microsecond,
   //e_type_pintegral_microsecond,
   //e_type_integral_millisecond,
   //e_type_pintegral_millisecond,
   //e_type_integral_second,
   //e_type_pintegral_second,
   //e_type_integral_minute,
   //e_type_pintegral_minute,
   //e_type_integral_hour,
   //e_type_pintegral_hour,
   //e_type_integral_day,
   //e_type_pintegral_day,
   //e_type_floating_nanosecond,
   //e_type_pfloating_nanosecond,
   //e_type_floating_microsecond,
   //e_type_pfloating_microsecond,
   //e_type_floating_millisecond,
   //e_type_pfloating_millisecond,
   //e_type_floating_second,
   //e_type_pfloating_second,
   //e_type_floating_minute,
   //e_type_pfloating_minute,
   //e_type_floating_hour,
   //e_type_pfloating_hour,
   //e_type_floating_day,
   //e_type_pfloating_day,
   e_type_time,
   e_type_ptime,
   e_type_atom,
   e_type_patom,
   e_type_earth_time,
   e_type_file_time,
   //e_type_property,
   //e_type_payload_pointer,
   e_type_color,
   e_type_hls,
   //e_type_process,

   // matter classes
   e_type_element = 8192,
   e_type_string_array,
   e_type_int_array,
   e_type_payload_array,
   e_type_property_set,
   e_type_long_long_array,
   e_type_memory,
   e_type_path,
   e_type_last_element,

   // enum
   //e_type_enum_command = 20000,
   //e_type_enum_status,
   //e_type_enum_check,
   //e_type_enum_flag,

   e_type_primitive_mask = 65535,
   e_type_pointer_of = 65536,
   e_type_pbool = e_type_bool | e_type_pointer_of,
   e_type_punsigned_char = e_type_unsigned_char | e_type_pointer_of,
   e_type_pchar = e_type_char | e_type_pointer_of,
   e_type_punsigned_short = e_type_unsigned_short | e_type_pointer_of,
   e_type_pshort = e_type_short | e_type_pointer_of,
   e_type_punsigned_int = e_type_unsigned_int | e_type_pointer_of,
   e_type_pint = e_type_int | e_type_pointer_of,
   e_type_punsigned_long_long = e_type_unsigned_long_long | e_type_pointer_of,
   e_type_plong_long = e_type_long_long | e_type_pointer_of,
   e_type_pfloat = e_type_float | e_type_pointer_of,
   e_type_pdouble= e_type_double | e_type_pointer_of,



};


constexpr bool is_number(enum_type etype)
{

   return
      etype == e_type_bool
   || etype == e_type_unsigned_char
   || etype == e_type_char
   || etype ==  e_type_unsigned_short
   || etype ==  e_type_short
   || etype ==  e_type_unsigned_int
   || etype ==  e_type_int
   || etype ==  e_type_unsigned_long_long
   || etype ==  e_type_long_long
   || etype == e_type_float
   || etype == e_type_double;

}


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
   e_trace_category_graphics_thread, // screen update and window layout
   e_trace_category_count


};


enum enum_trace_level
{


   e_trace_level_undefined,
   e_trace_level_none,
   e_trace_level_debug,       // debug
   e_trace_level_information, // info
   e_trace_level_warning,     // warn
   e_trace_level_error,       // error
   e_trace_level_fatal,       // fatal
   e_trace_level_count


};


constexpr int trace_level_letter(enum_trace_level etracelevel)
{

   return etracelevel < 0|| etracelevel >= e_trace_level_count? ' ': " IWEF"[(int)etracelevel];

}


constexpr char line_feed_letter(bool bCarriage)
{

   return bCarriage ? '\r' : '\n';

}



//enum  : long long
//{
//
//
//   e_object_none,
//   aaa_want_to_erase_object_locked = 1 << 10,
//   aaa_want_to_erase_object_shared = 1 << 11,
//   aaa_want_to_erase_object_read_only_link = 1 << 12,
//   e_object_log_disable = 1 << 13,
//   e_object_property_set_modified = 1 << 14,
//   e_object_default_io_exchange = 1 << 15,
//   //e_object_alertable_wait = 1 << 16,
//   e_object_any_hook = 1 << 17,
//   //e_object_any_hook = 1 << 17,
//   //e_object_any_update = (1 << 18) | e_object_any_hook,
//   //e_object_composite = 1 << 19,
//#if OBJECT_TYPE_COUNTER
//   e_object_object_type_counter = 1 << 20,
//#endif
//   e_object_synchronous = 1 << 21,
//   e_object_shared = 1 << 22,
//
//
//};
//

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
//bool CLASS_DECL_ACME status_succeeded(long long i);
//bool CLASS_DECL_ACME failed(const ::e_status & estatus);
//bool CLASS_DECL_ACME status_failed(long long i);


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


enum enum_timer : iptr;


//enum enum_boolean 
//{
//
//
//   // negative state... bad/failure states
//
//   e_boolean_no = -1, // 0xffffffff......
//   e_boolean_false = -1,
//
//   e_boolean_none = 0,
//   e_boolean_empty = 0, // 0x00000000......
//   e_boolean_undefined = 0,
//
//   e_boolean_yes = 1, // <3tbs
//   e_boolean_true = 1, // 0x00000001......
//
//   // positive state... good/success states
//
//   e_boolean_some_yes_some_no = 256,
//
//};


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
//   long long
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


   e_display_undefined = I32_MINIMUM,
   e_display_hide,

   e_display_none = 0,
   e_display_normal,
   e_display_compact,
   e_display_broad,
   e_display_minimal,
   e_display_notify_icon,
   e_display_iconic,
   e_display_zoomed,
   e_display_full_screen,
   e_display_up,
   e_display_down,
   e_display_last_show,


   // command default sink
   e_display_default = 1024,
   e_display_current,
   e_display_stored_state,
   e_display_fixed_size,
   e_display_center,
   e_display_last_command,


   e_display_left = 0x10000,
   e_display_top = 0x20000,
   e_display_right = 0x40000,
   e_display_bottom = 0x80000,
   e_display_top_left = e_display_top | e_display_left,
   e_display_top_right = e_display_top | e_display_right,
   e_display_bottom_left = e_display_bottom | e_display_left,
   e_display_bottom_right = e_display_bottom | e_display_right,
   e_display_full_left = e_display_left | e_display_top | e_display_bottom,
   e_display_full_top = e_display_top | e_display_left | e_display_right,
   e_display_full_right = e_display_right | e_display_top | e_display_bottom,
   e_display_full_bottom = e_display_bottom | e_display_left | e_display_right,

   e_display_docking_mask = 0xf0000,


};


enum enum_system_command
{

   e_system_command_none,
   e_system_command_minimize,

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


enum enum_window_flag : long long
{


   e_window_flag_none,
   e_window_flag_is_window = 1 << 0,
   e_window_flag_enable = 1 << 1,
   e_window_flag_focus = 1 << 2,
   e_window_flag_active = 1 << 3,
   e_window_flag_redraw_in_queue = 1 << 4,
   //e_window_flag_visual_changed = 1 << 5,
   e_window_flag_fps_interest_on_show = 1 << 6,
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
   //e_window_flag_auto_store_window_rect = 1 << 22,
   //e_window_flag_pending_save_window_rect = 1 << 23,
   //e_window_flag_loading_window_rect = 1 << 24,
   e_window_flag_main_frame = 1 << 25,
   e_window_flag_destroying = 1 << 26,
   e_window_flag_not_visible = 1 << 27,
   e_window_flag_satellite_window_if_child = 1 << 28,
   e_window_flag_embedded_graphics_thread_if_child = 1 << 29,
   e_window_flag_composite = 1 << 30,
   e_window_flag_hosted = 1 << 31,
   e_window_flag_top_level = 1ll << 32,
   e_window_flag_root = 1ll << 33,
   e_window_flag_destroyed = 1ll << 34,

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


//#include "message.h"



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


enum enum_item : long long
{

   e_item_none = 0,
   e_item_tool,

};


#include "_geometry.h"

#include "message_box.h"



enum enum_command_system
{

   e_command_system_none = 0,
   e_command_system_inline_log = 1,

};


enum ECodePage
{
   CodePageShiftJIS = 932,
   CodePageLatin1 = 1252,
   //#ifdef WINDOWS
   //         CodePageUtf8 = CP_UTF8,
   //         CodePageAnsi = CP_ACP,
   //         CodePageOem = CP_OEMCP,
   //#else
   CodePageUtf8 = 65001,
   CodePageAnsi = 10,
   CodePageOem = 11
   ///#endif
};









enum enum_extract
{

   e_extract_none,
   e_extract_first,
   e_extract_all

};





// Created by camilo on 2021-10-08 11:10 BRT <3ThomasBorregaardSorensen!!
#pragma once


//// very short name ([{c}])ontext (switchers, as it as action_context) enums


struct default_initialization_t{};


struct no_initialize{};


//enum zero_t
//{
//
//
//   zero_t{},
//
//
//};


//enum enum_now
//{
//
//
//   now_t{},
//
//
//};

//
//enum enum_infinite
//{
//
//
//   e_infinite,
//
//
//};


enum enum_normalize
{


   e_normalize


};


enum enum_raw
{


   e_raw


};


enum enum_empty
{


   e_empty


};



enum enum_create_new
{

   e_create_new

};


enum enum_create
{

   e_create

};


enum enum_defer_new // ___new - for factoryless_allocation FACTORYLESS_ALLOCATION_ID
{

   e_defer_new

};


enum enum_pointer_transfer
{

   e_pointer_transfer

};


enum enum_copy_clone
{

   e_copy_clone

};


enum enum_flush
{

   e_flush,

};


enum enum_unit_size
{


   e_unit_size,


};




enum enum_command
{

   e_command_file_nothing = -1,
   e_command_none = 0,
   e_command_default,
   // please try to avoid "advanced" or "automatic" startup.
   // just bring the main window of the application to hold
   // the calling toolkit/system, or some background window
   // that will wait for late request for a new document or
   // some other file request.
   e_command_application_start,
   e_command_application_started,
   e_command_file_new,
   e_command_file_open,
   e_command_file_print,
   e_command_file_print_to,
   e_command_file_dde,
   e_command_app_unregister,
   e_command_request_exit,
   e_command_protocol

};





// enum enum_get_buffer
// {

//    e_get_buffer,

// };


////class string;
//enum enum_for_moving
//{
//
//   e_for_moving,
//
//};



namespace library
{


   enum enum_state
   {

      e_state_none = 0,
      e_state_available = 1,
      e_state_installed = 2,
      e_state_installing = 4,
      e_state_queued = 8,

   };


} // namespace library



enum enum_unit :
   int
{

   e_unit_rate = (int) - 1,

   e_unit_none = 0,

   e_unit_pixel,
   e_unit_point,
   e_unit_em,


};


namespace user
{


   enum enum_key : long long;


} // namespace user


enum enum_synchronicity
{

   e_synchronicity_synchronous,
   e_synchronicity_asynchronous

};



