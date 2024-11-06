#pragma once


//#include "gdi_winrt.h"


#define GW_HWNDFIRST        0
#define GW_HWNDLAST         1
#define GW_HWNDNEXT         2
#define GW_HWNDPREV         3
#define GW_OWNER            4
#define GW_CHILD            5
#if(WINVER <= 0x0400)
#define GW_MAX              5
#else
#define GW_ENABLEDPOPUP     6
#define GW_MAX              6
#endif


//CLASS_DECL_ACME bool __cdecl __is_idle_message(::message::message * pmessage);
//CLASS_DECL_ACME bool __cdecl __is_idle_message(MESSAGE * pMsg);


//CLASS_DECL_ACME oswindow WINAPI WinGetFocus();
//CLASS_DECL_ACME oswindow WINAPI WinSetFocus(oswindow oswindow);


CLASS_DECL_ACME string normalize_path(const char* lpcszPath);


//CLASS_DECL_ACME oswindow get_capture();
//CLASS_DECL_ACME oswindow set_capture(oswindow oswindow);
//CLASS_DECL_ACME int_bool release_capture();
//
//CLASS_DECL_ACME oswindow get_active_window();
//CLASS_DECL_ACME oswindow set_active_window(oswindow oswindow);
//
//
//
//CLASS_DECL_ACME int_bool is_window(oswindow oswindow);


void CLASS_DECL_ACME __cdecl _ca2_purecall();
void CLASS_DECL_ACME __cdecl _null_se_translator(unsigned int uiCode, EXCEPTION_POINTERS* ppointers);
bool CLASS_DECL_ACME __windows_init();


CLASS_DECL_ACME HANDLE hfile_create(const char * lpcszFileName, unsigned int dwDesiredAcces, unsigned int dwShareMode, LPSECURITY_ATTRIBUTES lpSA, unsigned int dwCreationDisposition, unsigned int dwFlagsAndAttributes, HANDLE hTemplateFile);


//CLASS_DECL_ACME int WINAPI GetSystemMetrics(int i);

namespace user
{

   //class interaction_impl;
   class interaction;
   //   class interaction;
   //
   //
} // namespace user


//#include "acme/graphics/graphics/buffer.h"
//#include "_UWP_gdi_winrt.h"


//#include "oswindow.h"



#include "exception_engine.h"



//CLASS_DECL_ACME ::winrt::Windows::Storage::StorageFolder ^ get_os_folder(const char * lpcszDirName);
//CLASS_DECL_ACME::winrt::Windows::Storage::StorageFile ^ get_os_file(const char * lpcszFileName, dword dwDesiredAcces, dword dwShareMode, LPSECURITY_ATTRIBUTES lpSA, dword dwCreationDisposition, dword dwFlagsAndAttributes, HANDLE hTemplateFile);
//CLASS_DECL_ACME bool get_file_time(::winrt::Windows::Storage::StorageFile ^ file, LPFILETIME lpCreationTime, LPFILETIME lpItemTime, LPFILETIME lpLastWriteTime);








#include "base_file.h"
#include "parallelization.h"


//#ifdef __cplusplus
//#include "operating_system-windows_common/windows_commoncomptr.h"
//#endif


//#ifndef UNIVERSAL_WINDOWS
//
//CLASS_DECL_ACME void WINAPI sleep(unsigned int dw::times);
//
//#endif

/*#define GetAValue(rgb)      (lower_u8((rgb)>>24))
#define argb(a, r,g,b)          ((color32_t)(((unsigned char)(r)|((unsigned short)((unsigned char)(g))<<8))|(((unsigned int)(unsigned char)(b))<<16)|(((unsigned int)(unsigned char)(a))<<24)))*/


//CLASS_DECL_ACME int_bool os_initialize();
//CLASS_DECL_ACME int_bool os_finalize();


CLASS_DECL_ACME int_bool main_initialize();
CLASS_DECL_ACME int_bool main_finalize();


CLASS_DECL_ACME void set_main_htask(htask_t htask);
CLASS_DECL_ACME void set_main_itask(itask_t itask);
CLASS_DECL_ACME htask_t main_htask();
CLASS_DECL_ACME itask_t main_itask();

//CLASS_DECL_ACME oswindow get_focus();
//CLASS_DECL_ACME oswindow set_focus(oswindow oswindow);

//CLASS_DECL_ACME oswindow get_window(oswindow oswindow, int iWindow);

//CLASS_DECL_ACME void attach_thread_input_to_main_thread(int_bool bAttach);


//CLASS_DECL_ACME unsigned int WINAPI WaitForSingleObject( _In_ HANDLE hHandle, _In_ unsigned int dw::times );




//CLASS_DECL_ACME char* getenv(const char* name);
//CLASS_DECL_ACME HANDLE WINAPI CreateMutex(_In_opt_ LPSECURITY_ATTRIBUTES lpMutexAttributes, _In_ BOOL bInitialOwner, _In_opt_ const char * lpName  );

//CLASS_DECL_ACME HANDLE WINAPI CreateMutexW(    _In_opt_ LPSECURITY_ATTRIBUTES lpMutexAttributes,    _In_ BOOL bInitialOwner,    _In_opt_ const ::wide_character * lpName    );



//inline int_bool is_nok(hfile hfile);

//
//inline int_bool is_ok(hfile hfile);
//
//
//CLASS_DECL_ACME void dpi_os_initialize();
//




#include "_winrt_foundation.h"


