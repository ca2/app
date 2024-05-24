//
// Created by camilo on 03/12/2020. <3tbs!!
//
#pragma once


#include "acid/primitive/collection/atom_array.h"
#include "acid/primitive/primitive/atom.h"






//
//
//CLASS_DECL_ACID::string get_command_line();
//



//CLASS_DECL_ACID bool launch_command(::acid::system * psystem, const char * const pszCommand);



#if !defined(UNIVERSAL_WINDOWS)


//CLASS_DECL_ACID string module_path_from_pid(unsigned int pid);
//CLASS_DECL_ACID ::atom_array module_path_get_pid(const ::scoped_string & scopedstrModuleName, bool bModuleNameIsPropertyFormatted = true);


#ifndef WINDOWS

//CLASS_DECL_ACID string_array cmdline_from_pid(unsigned int pid);
//CLASS_DECL_ACID atom_array app_get_pid(const ::scoped_string & scopedstrModuleName);


#endif


#endif

#ifndef UNIVERSAL_WINDOWS
//CLASS_DECL_ACID bool process_contains_module(string & strImage, ::u32 processID, const ::scoped_string & scopedstrLibrary);
//CLASS_DECL_ACID void shared_library_process(dword_array & dwa, string_array & straProcesses, const ::scoped_string & scopedstrLibrary);
#endif



//CLASS_DECL_ACID bool is_shared_library_busy(u32 processid, const string_array & stra);
//CLASS_DECL_ACID bool is_shared_library_busy(const string_array & stra);



//CLASS_DECL_ACID bool os_init_application();
//CLASS_DECL_ACID void os_term_application();




//CLASS_DECL_ACID::u32 get_current_process_id();


// it was extracted from macOS code base
// it is prepared for a command line supplied by macOS*1?
// (*1.macOS:
//          proc_pidinfo((pid_t) uiPid, PROC_PIDTASKALLINFO, SHOW_ZOMBIES, &info, sizeof(struct proc_taskallinfo));
// return info.pbsd.pbi_comm;
// )

//#ifdef WINDOWS_DESKTOP
//CLASS_DECL_ACID string ca2_command_line(hinstance hinstance);
//#else
//CLASS_DECL_ACID string ca2_command_line();
//#endif








#include "exit_status.h"


//CLASS_DECL_ACID string app_id_to_app_name(string strId);


#if !defined(UNIVERSAL_WINDOWS)

//CLASS_DECL_ACID void call_async(const ::file::path & path, const ::scoped_string & scopedstrParam, const ::scoped_string & scopedstrDir, ::e_display edisplay, bool bPrivileged, unsigned int * puiPid = nullptr);

//typedef i32 CALLSYNCONRETRY(i32 iTry,uptr dwParam);

//typedef CALLSYNCONRETRY * PFNCALLSYNCONRETRY;

//CLASS_DECL_ACID void call_sync(const ::file::path & path, const ::scoped_string & scopedstrParam, const ::scoped_string & scopedstrDir, ::e_display edisplay, const class time & timeTimeout, ::property_set & set);

#endif


