#pragma once


#include "base_file.h"
#include "multithreading.h"


//#ifdef __cplusplus
//#include "apex/os/windows_common/comptr.h"
//#endif


#ifndef _UWP

CLASS_DECL_APEX void WINAPI Sleep(DWORD dwMilliseconds);

#endif

/*#define GetAValue(rgb)      (LOBYTE((rgb)>>24))
#define ARGB(a, r,g,b)          ((COLORREF)(((BYTE)(r)|((WORD)((BYTE)(g))<<8))|(((DWORD)(BYTE)(b))<<16)|(((DWORD)(BYTE)(a))<<24)))*/


//CLASS_DECL_APEX int_bool os_initialize();
//CLASS_DECL_APEX int_bool os_finalize();


//CLASS_DECL_APEX int_bool main_initialize();
//CLASS_DECL_APEX int_bool main_finalize();


//CLASS_DECL_APEX void set_main_thread(HTHREAD hThread);
//CLASS_DECL_APEX void set_main_thread_id(UINT uiThread);


//CLASS_DECL_APEX HTHREAD get_main_thread();
//CLASS_DECL_APEX UINT get_main_thread_id();

//CLASS_DECL_APEX oswindow get_focus();
//CLASS_DECL_APEX oswindow set_focus(oswindow oswindow);

//CLASS_DECL_APEX oswindow get_window(oswindow oswindow, int iWindow);

//CLASS_DECL_APEX void attach_thread_input_to_main_thread(int_bool bAttach);


//CLASS_DECL_APEX DWORD WINAPI WaitForSingleObject( _In_ HANDLE hHandle, _In_ DWORD dwMilliseconds );




//CLASS_DECL_APEX char* getenv(const char* name);
//CLASS_DECL_APEX HANDLE WINAPI CreateMutex(_In_opt_ LPSECURITY_ATTRIBUTES lpMutexAttributes, _In_ BOOL bInitialOwner, _In_opt_ LPCSTR lpName  );

//CLASS_DECL_APEX HANDLE WINAPI CreateMutexW(    _In_opt_ LPSECURITY_ATTRIBUTES lpMutexAttributes,    _In_ BOOL bInitialOwner,    _In_opt_ LPCWSTR lpName    );


//CLASS_DECL_APEX HANDLE hfile_create(const char * lpcszFileName, DWORD dwDesiredAcces, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSA, DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile);


