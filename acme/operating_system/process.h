//
// Created by camilo on 03/12/2020. <3tbs!!
//
#pragma once


#include "acme/primitive/collection/atom_array.h"
#include "acme/primitive/primitive/atom.h"


enum enum_command_system
{

   e_command_system_none = 0,
   e_command_system_inline_log = 1,

};


CLASS_DECL_ACME void command_system(string_array & straOutput, int & iExitCode, const char* psz, enum_command_system ecommandsystem = e_command_system_none, const ::duration & durationTimeout = ::duration::infinite(), ::particle * pparticleSynchronization = nullptr, ::file::file * pfileLog = nullptr);






CLASS_DECL_ACME::string get_command_line();




//CLASS_DECL_ACME bool launch_command(::acme::system * psystem, const char * const pszCommand);



#if !defined(_UWP)


//CLASS_DECL_ACME string module_path_from_pid(unsigned int pid);
//CLASS_DECL_ACME ::atom_array module_path_get_pid(const char * pszModuleName, bool bModuleNameIsPropertyFormatted = true);


#ifndef WINDOWS

//CLASS_DECL_ACME string_array cmdline_from_pid(unsigned int pid);
//CLASS_DECL_ACME atom_array app_get_pid(const char * pszModuleName);


#endif


#endif

#ifndef _UWP
//CLASS_DECL_ACME bool process_contains_module(string & strImage, ::u32 processID, const char * pszLibrary);
//CLASS_DECL_ACME void shared_library_process(dword_array & dwa, string_array & straProcesses, const char * pszLibrary);
#endif



//CLASS_DECL_ACME bool is_shared_library_busy(u32 processid, const string_array & stra);
//CLASS_DECL_ACME bool is_shared_library_busy(const string_array & stra);



//CLASS_DECL_ACME bool os_init_application();
//CLASS_DECL_ACME void os_term_application();




//CLASS_DECL_ACME::u32 get_current_process_id();


// it was extracted from macOS code base
// it is prepared for a command line supplied by macOS*1?
// (*1.macOS:
//          proc_pidinfo((pid_t) uiPid, PROC_PIDTASKALLINFO, SHOW_ZOMBIES, &info, sizeof(struct proc_taskallinfo));
// return info.pbsd.pbi_comm;
// )

//#ifdef WINDOWS_DESKTOP
//CLASS_DECL_ACME string ca2_command_line(hinstance hinstance);
//#else
//CLASS_DECL_ACME string ca2_command_line();
//#endif








#include "exit_status.h"


//CLASS_DECL_ACME string app_id_to_app_name(string strId);


#if !defined(_UWP)

//CLASS_DECL_ACME void call_async(const char * pszPath, const char * pszParam, const char * pszDir, ::e_display edisplay, bool bPrivileged, unsigned int * puiPid = nullptr);

//typedef i32 CALLSYNCONRETRY(i32 iTry,uptr dwParam);

//typedef CALLSYNCONRETRY * PFNCALLSYNCONRETRY;

//CLASS_DECL_ACME void call_sync(const char * pszPath, const char * pszParam, const char * pszDir, ::e_display edisplay, const ::duration & durationTimeout, ::property_set & set);

#endif


CLASS_DECL_ACME i32 get_current_processor_index();
CLASS_DECL_ACME i32 get_current_process_maximum_affinity();
CLASS_DECL_ACME i32 get_current_process_affinity_order();


//CLASS_DECL_ACME string expand_env(string str);
//CLASS_DECL_ACME string xxxget_environment_variable(const char * pszEnvironmentVariable);
//CLASS_DECL_ACME string ca2_command_line();




CLASS_DECL_ACME int process_get_status();
CLASS_DECL_ACME void process_set_status(int iStatus);
CLASS_DECL_ACME int * process_get_pargc();
CLASS_DECL_ACME int process_get_argc();


CLASS_DECL_ACME bool set_process_priority(::enum_priority epriority);




CLASS_DECL_ACME string time_binary_platform(string strPlatform);






#if !defined(_UWP)

CLASS_DECL_ACME i32 call_async(const ::string & pszPath, const ::string & pszParam, const ::string & pszDir, ::e_display edisplay, bool bPrivileged, unsigned int * puiPid = nullptr);

typedef i32 CALLSYNCONRETRY(i32 iTry,uptr dwParam);

typedef CALLSYNCONRETRY * PFNCALLSYNCONRETRY;

//CLASS_DECL_ACME u32 call_sync(const ::string & pszPath, const ::string & pszParam, const ::string & pszDir, ::e_display edisplay, const ::duration & durationTimeout, ::property_set & set);

#endif


#if !defined(_UWP) && !defined(LINUX) && !defined(__APPLE__) && !defined(ANDROID)

CLASS_DECL_ACME i32 get_current_processor_index();

CLASS_DECL_ACME i32 get_current_process_maximum_affinity();

CLASS_DECL_ACME i32 get_current_process_affinity_order();

#endif


CLASS_DECL_ACME string expand_env(string str);

//CLASS_DECL_ACME string consume_command_line_parameter(const ::string & pszCommandLine, const ::string * & pszEndPtr);
//CLASS_DECL_ACME bool is_command_line_parameter_true(string& strValue, const ::string & pszCommandLine, const ::string & pszParam, bool bDefault = false);
//CLASS_DECL_ACME bool get_command_line_parameter(string & strValue, const ::string & pszCommandLine, const ::string & pszParam);
//CLASS_DECL_ACME bool get_command_line_parameter(string & strValue, const ::string & pszCommandLine, const ::string & pszParam, const ::string & pszDefault);
//CLASS_DECL_ACME string get_command_line_parameter(const ::string & pszCommandLine, const ::string & pszParam);


CLASS_DECL_ACME bool launch_command(const ::string & pszCommand);


CLASS_DECL_ACME string process_configuration_name();

CLASS_DECL_ACME string time_binary_platform(string strPlatform);
CLASS_DECL_ACME string process_platform_name();
CLASS_DECL_ACME string process_platform_name();
CLASS_DECL_ACME string process_version_dir_name();

CLASS_DECL_ACME ::file::path core_app_path(string strApp);

#if !defined(_UWP)


CLASS_DECL_ACME string module_path_from_pid(unsigned int pid);
CLASS_DECL_ACME atom_array module_path_get_pid(const ::string & pszModuleName, bool bModuleNameIsPropertyFormatted = true);


#ifndef WINDOWS

CLASS_DECL_ACME string_array cmdline_from_pid(unsigned int pid);
CLASS_DECL_ACME atom_array app_get_pid(const ::string & pszModuleName);


#endif


#endif

#ifndef _UWP
CLASS_DECL_ACME bool process_contains_module(string & strImage, ::u32 processID, const ::string & pszLibrary);
CLASS_DECL_ACME void shared_library_process(dword_array & dwa, string_array & straProcesses, const ::string & pszLibrary);
#endif



CLASS_DECL_ACME bool is_shared_library_busy(u32 processid, const string_array & stra);
CLASS_DECL_ACME bool is_shared_library_busy(const string_array & stra);


CLASS_DECL_ACME bool launch_application(::particle * pparticle, const ::string & strAppId, const ::string & strParams, int iBitCount);



CLASS_DECL_ACME bool shell_execute_async(const ::string & pszFile, const ::string & pszParams);
CLASS_DECL_ACME bool shell_execute_sync(const ::string & pszFile, const ::string & pszParams, const ::duration & durationTimeout = 1_minute);

CLASS_DECL_ACME bool root_execute_async(const ::string & pszFile, const ::string & pszParams);
CLASS_DECL_ACME bool root_execute_sync(const ::string & pszFile, const ::string & pszParams, const ::duration & durationTimeout = 1_minute);


//CLASS_DECL_ACME bool os_init_application();
//CLASS_DECL_ACME void os_term_application();



CLASS_DECL_ACME string executable_title_from_appid(string str);


//CLASS_DECL_ACME ::u32 get_current_process_id();



CLASS_DECL_ACME void prepare_argc_argv(int & argc, char ** argv, char * cmd_line);





