#pragma once


#if !defined(_UWP)

CLASS_DECL_AURA i32 call_async(const ::string & pszPath, const ::string & pszParam, const ::string & pszDir, ::e_display edisplay, bool bPrivileged, unsigned int * puiPid = nullptr);

typedef i32 CALLSYNCONRETRY(i32 iTry,uptr dwParam);

typedef CALLSYNCONRETRY * PFNCALLSYNCONRETRY;

//CLASS_DECL_AURA u32 call_sync(const ::string & pszPath, const ::string & pszParam, const ::string & pszDir, ::e_display edisplay, const ::duration & durationTimeout, ::property_set & set);

#endif


#if !defined(_UWP) && !defined(LINUX) && !defined(__APPLE__) && !defined(ANDROID)

CLASS_DECL_AURA i32 get_current_processor_index();

CLASS_DECL_AURA i32 get_current_process_maximum_affinity();

CLASS_DECL_AURA i32 get_current_process_affinity_order();

#endif


CLASS_DECL_AURA string expand_env(string str);

CLASS_DECL_AURA string consume_param(const ::string & pszCommandLine, const ::string &* pszEndPtr);
CLASS_DECL_AURA bool is_command_line_param_true(string& strValue, const ::string & pszCommandLine, const ::string & pszParam, bool bDefault = false);
CLASS_DECL_AURA bool get_command_line_param(string & strValue, const ::string & pszCommandLine, const ::string & pszParam);
CLASS_DECL_AURA bool get_command_line_param(string & strValue, const ::string & pszCommandLine, const ::string & pszParam, const ::string & pszDefault);
CLASS_DECL_AURA string get_command_line_param(const ::string & pszCommandLine, const ::string & pszParam);


CLASS_DECL_AURA bool launch_command(const ::string & const pszCommand);


CLASS_DECL_AURA string process_configuration_dir_name();

CLASS_DECL_AURA string time_binary_platform(string strPlatform);
CLASS_DECL_AURA string process_platform_dir_name();
CLASS_DECL_AURA string process_platform_dir_name2();
CLASS_DECL_AURA string process_version_dir_name();

CLASS_DECL_AURA ::file::path core_app_path(string strApp);

#if !defined(_UWP)


CLASS_DECL_AURA string module_path_from_pid(unsigned int pid);
CLASS_DECL_AURA id_array module_path_get_pid(const ::string & pszModuleName, bool bModuleNameIsPropertyFormatted = true);


#ifndef WINDOWS

CLASS_DECL_AURA string_array cmdline_from_pid(unsigned int pid);
CLASS_DECL_AURA id_array app_get_pid(const ::string & pszModuleName);


#endif


#endif

#ifndef _UWP
CLASS_DECL_AURA bool process_contains_module(string & strImage, ::u32 processID, const ::string & pszLibrary);
CLASS_DECL_AURA void shared_library_process(dword_array & dwa, string_array & straProcesses, const ::string & pszLibrary);
#endif



CLASS_DECL_AURA bool is_shared_library_busy(u32 processid, const string_array & stra);
CLASS_DECL_AURA bool is_shared_library_busy(const string_array & stra);


CLASS_DECL_AURA bool launch_application(::object * pobject, const ::string & strAppId, const ::string & strParams, int iBitCount);



CLASS_DECL_AURA bool shell_execute_async(const ::string & pszFile, const ::string & pszParams);
CLASS_DECL_AURA bool shell_execute_sync(const ::string & pszFile, const ::string & pszParams, ::duration durationTimeout = one_minute());

CLASS_DECL_AURA bool root_execute_async(const ::string & pszFile, const ::string & pszParams);
CLASS_DECL_AURA bool root_execute_sync(const ::string & pszFile, const ::string & pszParams, ::duration durationTimeout = one_minute());


CLASS_DECL_AURA bool os_init_application();
CLASS_DECL_AURA void os_term_application();



CLASS_DECL_AURA string executable_title_from_appid(string str);


CLASS_DECL_AURA ::u32 get_current_process_id();



CLASS_DECL_AURA void prepare_argc_argv(int & argc, char ** argv, char * cmd_line);





