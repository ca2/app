#pragma once


#include "base_file.h"
#include "multithreading.h"


#ifdef __cplusplus
#include "aura/os/windows_common/comptr.h"
#endif


#ifndef _UWP

CLASS_DECL_CORE void WINAPI Sleep(DWORD dwMilliseconds);

#endif

/*#define GetAValue(rgb)      (LOBYTE((rgb)>>24))
#define ARGB(a, r,g,b)          ((COLORREF)(((BYTE)(r)|((WORD)((BYTE)(g))<<8))|(((DWORD)(BYTE)(b))<<16)|(((DWORD)(BYTE)(a))<<24)))*/


//CLASS_DECL_CORE int_bool os_initialize();
//CLASS_DECL_CORE int_bool os_finalize();


CLASS_DECL_CORE int_bool main_initialize();
CLASS_DECL_CORE int_bool main_finalize();


CLASS_DECL_CORE void set_main_thread(HTHREAD hThread);
CLASS_DECL_CORE void set_main_thread_id(UINT uiThread);


CLASS_DECL_CORE HTHREAD get_main_thread();
CLASS_DECL_CORE UINT get_main_thread_id();

CLASS_DECL_CORE oswindow get_focus();
CLASS_DECL_CORE oswindow set_focus(oswindow oswindow);

CLASS_DECL_CORE oswindow get_window(oswindow oswindow, int iWindow);

CLASS_DECL_CORE void attach_thread_input_to_main_thread(int_bool bAttach);


//CLASS_DECL_CORE DWORD WINAPI WaitForSingleObject( _In_ HANDLE hHandle, _In_ DWORD dwMilliseconds );




//CLASS_DECL_CORE char* getenv(const char* name);
//CLASS_DECL_CORE HANDLE WINAPI CreateMutex(_In_opt_ LPSECURITY_ATTRIBUTES lpMutexAttributes, _In_ BOOL bInitialOwner, _In_opt_ LPCSTR lpName  );

//CLASS_DECL_CORE HANDLE WINAPI CreateMutexW(    _In_opt_ LPSECURITY_ATTRIBUTES lpMutexAttributes,    _In_ BOOL bInitialOwner,    _In_opt_ LPCWSTR lpName    );


CLASS_DECL_CORE HANDLE create_file(const char * lpcszFileName, DWORD dwDesiredAcces, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSA, DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile);


