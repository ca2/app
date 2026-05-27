#pragma once


#include "exit_status.h"


//CLASS_DECL_ACME string app_id_to_app_name(string strId);


#if !defined(UNIVERSAL_WINDOWS)

//CLASS_DECL_ACME void call_async(const ::file::path & path, const ::scoped_string & scopedstrParam, const ::scoped_string & scopedstrDir, ::e_display edisplay, bool bPrivileged, ::u32 * puiPid = nullptr);

//typedef ::i32 CALLSYNCONRETRY(::i32 iTry,uptr dwParam);

//typedef CALLSYNCONRETRY * PFNCALLSYNCONRETRY;

//CLASS_DECL_ACME void call_sync(const ::file::path & path, const ::scoped_string & scopedstrParam, const ::scoped_string & scopedstrDir, ::e_display edisplay, const ::duration & durationTimeout, ::property_set & set);

#endif


CLASS_DECL_ACME ::i32 get_current_processor_index();
CLASS_DECL_ACME ::i32 get_current_process_maximum_affinity();
CLASS_DECL_ACME ::i32 get_current_process_affinity_order();


//CLASS_DECL_ACME string expand_env(string str);
//CLASS_DECL_ACME string xxxget_environment_variable(const ::scoped_string & scopedstrEnvironmentVariable);
//CLASS_DECL_ACME string ca2_command_line();


CLASS_DECL_ACME string consume_command_line_parameter(const ::scoped_string & scopedstrCommandLine, const_char_pointer * pszEndPtr);
CLASS_DECL_ACME bool is_command_line_parameter_true(string& strValue, const ::scoped_string & scopedstrCommandLine, const ::scoped_string & scopedstrParam, bool bDefault = false);
CLASS_DECL_ACME bool get_command_line_parameter(string & strValue, const ::scoped_string & scopedstrCommandLine, const ::scoped_string & scopedstrParam);
CLASS_DECL_ACME bool get_command_line_parameter(string & strValue, const ::scoped_string & scopedstrCommandLine, const ::scoped_string & scopedstrParam, const ::scoped_string & scopedstrDefault);
CLASS_DECL_ACME string get_command_line_parameter(const ::scoped_string & scopedstrCommandLine,const ::scoped_string & scopedstrParam);


//CLASS_DECL_ACME bool launch_command(::platform::system * psystem, const_char_pointer const pszCommand);


CLASS_DECL_ACME string process_configuration_name();

CLASS_DECL_ACME string time_binary_platform(string strPlatform);
CLASS_DECL_ACME string process_platform_name();
CLASS_DECL_ACME string process_platform_name();
CLASS_DECL_ACME string process_version_dir_name();

//CLASS_DECL_ACME int_bool is_process_running(::u32 pid);

//CLASS_DECL_ACME ::file::path core_app_path(string strApp);

#if !defined(UNIVERSAL_WINDOWS)


//CLASS_DECL_ACME string module_path_from_pid(::u32 pid);
//CLASS_DECL_ACME ::atom_array module_path_get_pid(const ::scoped_string & scopedstrModuleName, bool bModuleNameIsPropertyFormatted = true);


#ifndef WINDOWS

//CLASS_DECL_ACME string_array_base cmdline_from_pid(::u32 pid);
//CLASS_DECL_ACME atom_array app_get_pid(const ::scoped_string & scopedstrModuleName);


#endif


#endif

#ifndef UNIVERSAL_WINDOWS
//CLASS_DECL_ACME bool process_contains_module(string & strImage, ::u32 processID, const ::scoped_string & scopedstrLibrary);
//CLASS_DECL_ACME void shared_library_process(dword_array & dwa, string_array_base & straProcesses, const ::scoped_string & scopedstrLibrary);
#endif



//CLASS_DECL_ACME bool is_shared_library_busy(::u32 processid, const string_array_base & stra);
//CLASS_DECL_ACME bool is_shared_library_busy(const string_array_base & stra);



//CLASS_DECL_ACME bool os_init_application();
//CLASS_DECL_ACME void os_term_application();



CLASS_DECL_ACME string executable_title_from_appid(string str);


CLASS_DECL_ACME ::u32 get_current_process_id();



CLASS_DECL_ACME void prepare_argc_argv(::i32 & argc, char_pointer * argv, char_pointer cmd_line);


CLASS_DECL_ACME string transform_to_c_arg(const ::scoped_string & scopedstr);
CLASS_DECL_ACME string_array_base get_c_args_from_string(const ::scoped_string & scopedstr);
CLASS_DECL_ACME string_array_base no_escape_get_c_args_from_string(const ::scoped_string & scopedstr);
CLASS_DECL_ACME string_array_base get_c_args_from_c(const ::scoped_string & scopedstr);
CLASS_DECL_ACME string_array_base get_c_args_for_c(const ::scoped_string & scopedstr);
CLASS_DECL_ACME string_array_base get_c_args(::i32 argc, char_pointer * argv);

// it was extracted from macOS code base
// it is prepared for a command line supplied by macOS*1?
// (*1.macOS:
//          proc_pidinfo((pid_t) uiPid, PROC_PIDTASKALLINFO, SHOW_ZOMBIES, &info, sizeof(struct proc_taskallinfo));
// return info.pbsd.pbi_comm;
// )
CLASS_DECL_ACME string_array_base command_arguments_from_command_line(const ::scoped_string & scopedstrCommandLine);
//#ifdef WINDOWS_DESKTOP
//CLASS_DECL_ACME string ca2_command_line(hinstance hinstance);
//#else
//CLASS_DECL_ACME string ca2_command_line();
//#endif


CLASS_DECL_ACME ::i32 process_get_status();
CLASS_DECL_ACME void process_set_status(::i32 iStatus);
CLASS_DECL_ACME ::i32 * process_get_pargc();
CLASS_DECL_ACME ::i32 process_get_argc();


CLASS_DECL_ACME bool set_process_priority(::enum_priority epriority);


//#include "pipe.h"
//#include "bidirectional_pipe.h"



