#pragma once

//
//#if !defined(_UWP)
//
//CLASS_DECL_APEX i32 call_async(const ::file::path & path, const ::scoped_string & scopedstrParam, const ::scoped_string & scopedstrDir, ::e_display edisplay, bool bPrivileged, unsigned int * puiPid = nullptr);
//
//typedef i32 CALLSYNCONRETRY(i32 iTry,uptr dwParam);
//
//typedef CALLSYNCONRETRY * PFNCALLSYNCONRETRY;
//
//CLASS_DECL_APEX u32 call_sync(const ::file::path & path, const ::scoped_string & scopedstrParam, const ::scoped_string & scopedstrDir, ::e_display edisplay, const ::duration & durationTimeout, ::property_set & set);
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
//CLASS_DECL_APEX string consume_command_line_parameter(const ::scoped_string & scopedstrCommandLine, const char ** pszEndPtr);
//CLASS_DECL_APEX bool is_command_line_parameter_true(string& strValue, const ::scoped_string & scopedstrCommandLine, const ::scoped_string & scopedstrParam, bool bDefault = false);
//CLASS_DECL_APEX bool get_command_line_parameter(string & strValue, const ::scoped_string & scopedstrCommandLine, const ::scoped_string & scopedstrParam);
//CLASS_DECL_APEX bool get_command_line_parameter(string & strValue, const ::scoped_string & scopedstrCommandLine, const ::scoped_string & scopedstrParam, const ::scoped_string & scopedstrDefault);
//CLASS_DECL_APEX string get_command_line_parameter(const ::scoped_string & scopedstrCommandLine,const ::scoped_string & scopedstrParam);
//
//
//CLASS_DECL_APEX bool launch_command(const char * const pszCommand);
//
//
//CLASS_DECL_APEX string process_configuration_name();
//
//CLASS_DECL_APEX string time_binary_platform(string strPlatform);
//CLASS_DECL_APEX string process_platform_name();
//CLASS_DECL_APEX string process_platform_name();
//CLASS_DECL_APEX string process_version_dir_name();
//
//CLASS_DECL_APEX ::file::path core_app_path(string strApp);
//
//#if !defined(_UWP)
//
//
//CLASS_DECL_APEX string module_path_from_pid(unsigned int pid);
//CLASS_DECL_APEX atom_array module_path_get_pid(const ::scoped_string & scopedstrModuleName, bool bModuleNameIsPropertyFormatted = true);
//
//
//#ifndef WINDOWS
//
//CLASS_DECL_APEX string_array cmdline_from_pid(unsigned int pid);
//CLASS_DECL_APEX atom_array app_get_pid(const ::scoped_string & scopedstrModuleName);
//
//
//#endif
//
//
//#endif
//
//#ifndef _UWP
//CLASS_DECL_APEX bool process_contains_module(string & strImage, ::u32 processID, const ::scoped_string & scopedstrLibrary);
//CLASS_DECL_APEX void shared_library_process(dword_array & dwa, string_array & straProcesses, const ::scoped_string & scopedstrLibrary);
//#endif
//
//
//
//CLASS_DECL_APEX bool is_shared_library_busy(u32 processid, const string_array & stra);
//CLASS_DECL_APEX bool is_shared_library_busy(const string_array & stra);
//
//
//CLASS_DECL_APEX bool launch_application(::particle * pparticle, const ::string & strAppId, const ::string & strParams, int iBitCount);
//
//
//
//CLASS_DECL_APEX bool shell_execute_async(const ::scoped_string & scopedstrFile, const ::scoped_string & scopedstrParams);
//CLASS_DECL_APEX bool shell_execute_sync(const ::scoped_string & scopedstrFile, const ::scoped_string & scopedstrParams, ::duration durationTimeout = one_minute());
//
//CLASS_DECL_APEX bool root_execute_async(const ::scoped_string & scopedstrFile, const ::scoped_string & scopedstrParams);
//CLASS_DECL_APEX bool root_execute_sync(const ::scoped_string & scopedstrFile, const ::scoped_string & scopedstrParams, ::duration durationTimeout = one_minute());
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



