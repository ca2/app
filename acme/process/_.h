#pragma once


#include "exit_status.h"


#if !defined(_UWP)

CLASS_DECL_ACME ::e_status call_async(const char * pszPath, const char * pszParam, const char * pszDir, ::e_display edisplay, bool bPrivileged, unsigned int * puiPid = nullptr);

typedef i32 CALLSYNCONRETRY(i32 iTry,uptr dwParam);

typedef CALLSYNCONRETRY * PFNCALLSYNCONRETRY;

CLASS_DECL_ACME ::e_status call_sync(const char * pszPath, const char * pszParam, const char * pszDir, ::e_display edisplay, const ::duration & durationTimeout, ::property_set & set);

#endif


CLASS_DECL_ACME i32 get_current_processor_index();
CLASS_DECL_ACME i32 get_current_process_maximum_affinity();
CLASS_DECL_ACME i32 get_current_process_affinity_order();


//CLASS_DECL_ACME string expand_env(string str);
//CLASS_DECL_ACME string get_environment_variable(const char * pszEnvironmentVariable);
//CLASS_DECL_ACME string ca2_command_line();


CLASS_DECL_ACME string consume_param(const char * pszCommandLine, const char ** pszEndPtr);
CLASS_DECL_ACME bool is_command_line_param_true(string& strValue, const char* pszCommandLine, const char* pszParam, bool bDefault = false);
CLASS_DECL_ACME bool get_command_line_param(string & strValue, const char * pszCommandLine, const char * pszParam);
CLASS_DECL_ACME bool get_command_line_param(string & strValue, const char * pszCommandLine, const char * pszParam, const char * pszDefault);
CLASS_DECL_ACME string get_command_line_param(const char * pszCommandLine,const char * pszParam);


CLASS_DECL_ACME bool launch_command(class ::system * psystem, const char * const pszCommand);


CLASS_DECL_ACME string process_configuration_dir_name();

CLASS_DECL_ACME string time_binary_platform(string strPlatform);
CLASS_DECL_ACME string process_platform_dir_name();
CLASS_DECL_ACME string process_platform_dir_name2();
CLASS_DECL_ACME string process_version_dir_name();

CLASS_DECL_ACME int_bool is_process_running(::u32 pid);

//CLASS_DECL_ACME ::file::path core_app_path(string strApp);

#if !defined(_UWP)


//CLASS_DECL_ACME string module_path_from_pid(unsigned int pid);
//CLASS_DECL_ACME ::id_array module_path_get_pid(const char * pszModuleName, bool bModuleNameIsPropertyFormatted = true);


#ifndef WINDOWS

//CLASS_DECL_ACME string_array cmdline_from_pid(unsigned int pid);
//CLASS_DECL_ACME id_array app_get_pid(const char * pszModuleName);


#endif


#endif

#ifndef _UWP
//CLASS_DECL_ACME bool process_contains_module(string & strImage, ::u32 processID, const char * pszLibrary);
//CLASS_DECL_ACME void shared_library_process(dword_array & dwa, string_array & straProcesses, const char * pszLibrary);
#endif



//CLASS_DECL_ACME bool is_shared_library_busy(u32 processid, const string_array & stra);
//CLASS_DECL_ACME bool is_shared_library_busy(const string_array & stra);


CLASS_DECL_ACME bool launch_application(::matter * pobject, const string & strAppId, const string & strParams, int iBitCount);



CLASS_DECL_ACME bool shell_execute_async(const char * pszFile, const char * pszParams);
CLASS_DECL_ACME bool shell_execute_sync(const char * pszFile, const char * pszParams, ::duration durationTimeout = one_minute());

CLASS_DECL_ACME bool root_execute_async(const char * pszFile, const char * pszParams);
CLASS_DECL_ACME bool root_execute_sync(const char * pszFile, const char * pszParams, ::duration durationTimeout = one_minute());


//CLASS_DECL_ACME bool os_init_application();
//CLASS_DECL_ACME void os_term_application();



CLASS_DECL_ACME string executable_title_from_appid(string str);


CLASS_DECL_ACME ::u32 get_current_process_id();



CLASS_DECL_ACME void prepare_argc_argv(int & argc, char ** argv, char * cmd_line);


CLASS_DECL_ACME string transform_to_c_arg(const char* psz);
CLASS_DECL_ACME string_array get_c_args_from_string(const char* psz);
CLASS_DECL_ACME string_array get_c_args_from_c(const char* psz);
CLASS_DECL_ACME string_array get_c_args_for_c(const char* psz);
CLASS_DECL_ACME string_array get_c_args(int argc, char** argv);
//#ifdef WINDOWS_DESKTOP
//CLASS_DECL_ACME string ca2_command_line(hinstance hinstance);
//#else
//CLASS_DECL_ACME string ca2_command_line();
//#endif


CLASS_DECL_ACME int process_get_status();
CLASS_DECL_ACME void process_set_status(int iStatus);
CLASS_DECL_ACME int * process_get_pargc();
CLASS_DECL_ACME int process_get_argc();


#include "pipe.h"
#include "bidirectional_pipe.h"



