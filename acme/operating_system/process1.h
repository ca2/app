//
// Created by camilo on 03/12/2020. <3tbs!!
//
#pragma once


#include "acme/primitive/collection/atom_array.h"
#include "acme/primitive/primitive/atom.h"






//
//
//CLASS_DECL_ACME::string get_command_line();
//



//CLASS_DECL_ACME bool launch_command(::acme::system * psystem, const char * const pszCommand);



#if !defined(_UWP)


//CLASS_DECL_ACME string module_path_from_pid(unsigned int pid);
//CLASS_DECL_ACME ::atom_array module_path_get_pid(const scoped_string & strModuleName, bool bModuleNameIsPropertyFormatted = true);


#ifndef WINDOWS

//CLASS_DECL_ACME string_array cmdline_from_pid(unsigned int pid);
//CLASS_DECL_ACME atom_array app_get_pid(const scoped_string & strModuleName);


#endif


#endif

#ifndef _UWP
//CLASS_DECL_ACME bool process_contains_module(string & strImage, ::u32 processID, const scoped_string & strLibrary);
//CLASS_DECL_ACME void shared_library_process(dword_array & dwa, string_array & straProcesses, const scoped_string & strLibrary);
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

//CLASS_DECL_ACME void call_async(const scoped_string & strPath, const scoped_string & strParam, const scoped_string & strDir, ::e_display edisplay, bool bPrivileged, unsigned int * puiPid = nullptr);

//typedef i32 CALLSYNCONRETRY(i32 iTry,uptr dwParam);

//typedef CALLSYNCONRETRY * PFNCALLSYNCONRETRY;

//CLASS_DECL_ACME void call_sync(const scoped_string & strPath, const scoped_string & strParam, const scoped_string & strDir, ::e_display edisplay, const class time & timeTimeout, ::property_set & set);

#endif


