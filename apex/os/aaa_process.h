#pragma once

//
//#if !defined(_UWP)
//
//CLASS_DECL_APEX i32 call_async(const char * pszPath, const char * pszParam, const char * pszDir, ::edisplay edisplay, bool bPrivileged, unsigned int * puiPid = nullptr);
//
//typedef i32 CALLSYNCONRETRY(i32 iTry,uptr dwParam);
//
//typedef CALLSYNCONRETRY * PFNCALLSYNCONRETRY;
//
//CLASS_DECL_APEX u32 call_sync(const char * pszPath, const char * pszParam, const char * pszDir, ::edisplay edisplay, const ::duration & durationTimeout, ::property_set & set);
//
//#endif
//
//
//#if !defined(_UWP) && !defined(LINUX) && !defined(__APPLE__) && !defined(ANDROID)
//
//CLASS_DECL_APEX i32 get_current_processor_index();
//
//CLASS_DECL_APEX i32 get_current_process_maximum_affinity();
//
//CLASS_DECL_APEX i32 get_current_process_affinity_order();
//
//#endif
//
//
//CLASS_DECL_APEX string expand_env(string str);
//
//CLASS_DECL_APEX string consume_param(const char * pszCommandLine, const char ** pszEndPtr);
//CLASS_DECL_APEX bool is_command_line_param_true(string& strValue, const char* pszCommandLine, const char* pszParam, bool bDefault = false);
//CLASS_DECL_APEX bool get_command_line_param(string & strValue, const char * pszCommandLine, const char * pszParam);
//CLASS_DECL_APEX bool get_command_line_param(string & strValue, const char * pszCommandLine, const char * pszParam, const char * pszDefault);
//CLASS_DECL_APEX string get_command_line_param(const char * pszCommandLine,const char * pszParam);
//
//
//CLASS_DECL_APEX bool launch_command(const char * const pszCommand);
//
//
//CLASS_DECL_APEX string process_configuration_dir_name();
//
//CLASS_DECL_APEX string time_binary_platform(string strPlatform);
//CLASS_DECL_APEX string process_platform_dir_name();
//CLASS_DECL_APEX string process_platform_dir_name2();
//CLASS_DECL_APEX string process_version_dir_name();
//
//CLASS_DECL_APEX ::file::path core_app_path(string strApp);
//
//#if !defined(_UWP)
//
//
//CLASS_DECL_APEX string module_path_from_pid(unsigned int pid);
//CLASS_DECL_APEX id_array module_path_get_pid(const char * pszModuleName, bool bModuleNameIsPropertyFormatted = true);
//
//
//#ifndef WINDOWS
//
//CLASS_DECL_APEX string_array cmdline_from_pid(unsigned int pid);
//CLASS_DECL_APEX id_array app_get_pid(const char * pszModuleName);
//
//
//#endif
//
//
//#endif
//
//#ifndef _UWP
//CLASS_DECL_APEX bool process_contains_module(string & strImage, ::u32 processID, const char * pszLibrary);
//CLASS_DECL_APEX void shared_library_process(dword_array & dwa, string_array & straProcesses, const char * pszLibrary);
//#endif
//
//
//
//CLASS_DECL_APEX bool is_shared_library_busy(u32 processid, const string_array & stra);
//CLASS_DECL_APEX bool is_shared_library_busy(const string_array & stra);
//
//
//CLASS_DECL_APEX bool launch_application(::object * pobject, const string & strAppId, const string & strParams, int iBitCount);
//
//
//
//CLASS_DECL_APEX bool shell_execute_async(const char * pszFile, const char * pszParams);
//CLASS_DECL_APEX bool shell_execute_sync(const char * pszFile, const char * pszParams, ::duration durationTimeout = one_minute());
//
//CLASS_DECL_APEX bool root_execute_async(const char * pszFile, const char * pszParams);
//CLASS_DECL_APEX bool root_execute_sync(const char * pszFile, const char * pszParams, ::duration durationTimeout = one_minute());
//
//
//CLASS_DECL_APEX bool os_init_application();
//CLASS_DECL_APEX void os_term_application();
//
//
//
//CLASS_DECL_APEX string executable_title_from_appid(string str);
//
//
//CLASS_DECL_APEX ::u32 get_current_process_id();
//
//
//
//CLASS_DECL_APEX void prepare_argc_argv(int & argc, char ** argv, char * cmd_line);
//
//
//
//
//


#ifdef WINDOWS_DESKTOP
CLASS_DECL_APEX string ca2_command_line(HINSTANCE hinstance);
#else
CLASS_DECL_APEX string ca2_command_line();
#endif



