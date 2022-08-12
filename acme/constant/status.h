#pragma once


/// tbs<---3btsE---->

#define MAXIMUM_SYNCHRONIZING_OBJECTS 64

#define STATUS_RANGE 1000 // should be enough for the categorization granularity

#define MKSTATUS_RANGE(previous) ((int)(previous) + (int)(STATUS_RANGE))

#define STATUS_RANGE_GENERAL ((int)(0))

#define STATUS_RANGE_TIME_BAG MKSTATUS_RANGE(STATUS_RANGE_GENERAL)

#define STATUS_RANGE_EXCEPTION MKSTATUS_RANGE(STATUS_RANGE_TIME_BAG)

#define STATUS_RANGE_IO MKSTATUS_RANGE(STATUS_RANGE_EXCEPTION)

#define STATUS_RANGE_FILE MKSTATUS_RANGE(STATUS_RANGE_IO)

#define STATUS_RANGE_NETWORK MKSTATUS_RANGE(STATUS_RANGE_FILE)

#define STATUS_RANGE_HTTP MKSTATUS_RANGE(STATUS_RANGE_NETWORK)

#define STATUS_RANGE_AUTHENTICATION MKSTATUS_RANGE(STATUS_RANGE_HTTP)

#define STATUS_RANGE_DATABASE MKSTATUS_RANGE(STATUS_RANGE_AUTHENTICATION)

#define STATUS_RANGE_MULTIMEDIA MKSTATUS_RANGE(STATUS_RANGE_DATABASE)

#define STATUS_FAILURE (INT_MIN)

#define INT_FAILURE_STATUS(iStatusRange) (((int)STATUS_FAILURE + (iStatusRange)))

#define INT_SUCCESS_STATUS(iStatusRange) ((int)(iStatusRange))

#define FAILURE_STATUS(iStatusRange) ((::e_status    )INT_FAILURE_STATUS(iStatusRange))

#define SUCCESS_STATUS(iStatusRange) ((::e_status    )INT_SUCCESS_STATUS(iStatusRange))

#define PRIestatus PRIi64


enum enum_status : ::int64_t
{

   e_status_none = INT64_MIN,

   e_status_process_result_negative_base = (::int64_t) INT_MIN - 1,

   error_failed = INT_FAILURE_STATUS(STATUS_RANGE_GENERAL),
   error_not_set,
   error_pending,
   error_multiple,
   error_null_result,
   error_status,
   error_none,
   error_not_found,
   error_bad_response,
   error_no_memory,
   error_another_installation_already_running,
   error_warning,
   error_debug_warning,
   error_invalid_usage,
   error_no_devices_found,  /*!< No devices found on system. */
   error_invalid_device_id,    /*!< An invalid device ID was specified. */
   error_device_driver,
   error_system,
   error_threading,
   error_would_reach_buffer_limit,
   error_not_implemented,
   error_conversion_not_a_number,
   error_not_valid_email_address,
   error_not_valid_user_id,
   error_decryption,
   error_key_not_found,
   error_value_not_found,
   error_wrong_type,
   error_false,
   error_no_factory,
   error_composite_not_composer_member,
   error_path_not_found,
   error_invalid_flags,
   error_insufficient_buffer,
   error_not_initialized,
   e_status_no_work,
   error_not_running,
   error_no_windowing,
   error_no_draw2d,
   error_no_audio,
error_no_session,
error_no_system,
error_no_application,
error_no_interface,
error_last_error,
error_already_working_on_it,
error_all_failed,
error_resource,
error_win32,
error_not_supported,
error_null_pointer,
todo,
error_what_exclamation_exclamation,
error_parsing,
error_invalid_character,
error_assert,
error_exit_start,
error_exit_thread,
error_exit_application,
error_exit_session,
error_exit_system,
error_exit_end,
error_user,
error_hresult,
error_network_payload_parsing,
error_pure_call,
error_invalid_operation,
error_wait_io_completion,
error_wait_failed,
error_wait_timeout,
error_need_restart_application_to_activate_feature,
error_function_entry_not_found,
error_some_error_has_occurred,
error_library_not_found,
error_library_not_loaded,
error_debug_testing,


error_time_bag = INT_FAILURE_STATUS(STATUS_RANGE_EXCEPTION),
error_open_failed,
error_invalid_track,
error_already_open,
error_invalid_parameter,
error_invalid_buffer,
error_invalid_tk_position,
error_save_failed,
error_bad_file_format,
error_bad_data_format,
error_unsupported_function,
error_already_allocated,
error_already_exists,
error_already_added,
error_bad_device_id,
error_not_ready,
error_internal,
error_timeout,
error_wrong_state,
//error_midi_player_stop,
//error_midi_player_close,
//error_midi_player_save,
//error_midi_player_preroll_stream_open,
//error_midi_player_preroll_stream_property,
//error_midi_player_preroll_no_memory1,
//error_midi_player_preroll_no_memory2,
///error_midi_player_preroll_prepare_header,
//error_midi_player_preroll_stream_out,
//error_midi_player_preroll_read_events,
//error_midi_player_preroll_prepare_header2,
//error_midi_player_preroll_stream_out2,
error_midi,
error_midi_not_prerolled,


// RTF library error codes
error_open_rtf,
error_close_rtf,
error_rtf_header,
error_rtf_document_format,
error_rtf_section_format,
error_rtf_paragraph_format,
error_rtf_image,
error_rtf_table,



error_exception = INT_FAILURE_STATUS(STATUS_RANGE_EXCEPTION),
error_standard_exception,
error_bad_argument,
error_index_out_of_bounds,
error_unexpected,  // "This shouldn't ever happen"
error_unexpected_result, // "This shouldn't ever happen" for integer result
error_interface_only,
error_cancelled,
error_catch_all_exception,
error_overflow,
error_range,
error_invalid_type,
error_unexpected_situation,
error_datetime_parser,
error_invalid_empty_argument,

error_io = INT_FAILURE_STATUS(STATUS_RANGE_IO),
error_serial,
error_serial_io,
error_port_not_opened,
error_serialization,
error_premature_end_of_file,
error_serialization_unexpected_value,
error_file_open,

   error_file = INT_FAILURE_STATUS(STATUS_RANGE_FILE),
   error_file_not_found,
   error_bad_path,
   error_too_many_open_files,
   error_file_access_denied,
   error_invalid_file,
   error_erase_current_dir,
   error_directory_full,
   error_bad_seek,
   error_hard_io,
   error_file_sharing_violation,
   error_file_lock_violation,
   error_disk_full,
   error_end_of_file,
   error_end_of_coding,
   error_end_of_decoding,


   error_network = INT_FAILURE_STATUS(STATUS_RANGE_NETWORK),
   error_connection_timed_out,
   error_connection_cancelled,
   error_on_connection_timeout,
   error_socket,

   abandoned_base = -0x7FFFFFFE00000000ll,
   abandoned_end = abandoned_base + MAXIMUM_SYNCHRONIZING_OBJECTS,

   success_login = INT_FAILURE_STATUS(STATUS_RANGE_AUTHENTICATION),


   error_http = INT_FAILURE_STATUS(STATUS_RANGE_HTTP),

   error_database = INT_FAILURE_STATUS(STATUS_RANGE_DATABASE),
   error_dataset,
   error_dataset_wrong_state,
   error_dataset_inactive,
   error_field_not_found,

   undefined = INT_SUCCESS_STATUS(STATUS_RANGE_GENERAL),
   success,
   success_true,
   success_multiple,
   success_none,
   success_exit_thread,
   success_not_found,
   success_not_ready,
   success_promise,
   success_color_index,
   success_mouse_has_left,
   partial_one_third_or_less_has_failed, // <= 1/3 success
   partial_sorf_of_half_has_failed, // ~ 1/2 success (between 1/3 and 2/3)
   partial_two_thirds_or_more_but_not_all_has_failed, // >= 2/3 success
   success_hresult,
   success_not_constructed,
   success_not_allocated,
   success_not_created,
   success_not_composed,
   success_already_added,
   success_started,
   success_scheduled,
   status_quit,
   status_kick_idle,

   success_http = INT_SUCCESS_STATUS(STATUS_RANGE_HTTP),
   success_http_redirection,


   success_dataset_empty = INT_SUCCESS_STATUS(STATUS_RANGE_DATABASE),


   success_time_bag = INT_SUCCESS_STATUS(STATUS_RANGE_TIME_BAG),
   success_event_not_found,
   success_track_not_found,
   success_no_found,
   success_end_of_file,
   success_reached_tk_max,
   success_meta_pending,
   success_no_meta,
   success_end_of_track,
   success_skip,


#include "status_range_authentication.h"

   e_status_process_result_positive_base = 0x10000000,
   signaled_base = 0x10000000,
   signaled_end = signaled_base + MAXIMUM_SYNCHRONIZING_OBJECTS,

};


#undef MAXIMUM_SYNCHRONIZING_OBJECTS


#if __cplusplus > 202001L
#define INLINE_CONSTEXPR inline constexpr
#else
#define INLINE_CONSTEXPR inline
#endif


INLINE_CONSTEXPR bool is_exit_exception_status(::enum_status estatus)
{

   return estatus > error_exit_start && estatus < error_exit_end;

}



CLASS_DECL_ACME::enum_status _errno_to_status(i32 nErrno);
CLASS_DECL_ACME::enum_status _failed_errno_to_status(i32 nErrno);