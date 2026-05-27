#pragma once


#include "base_file.h"
#include "parallelization.h"


//#ifdef __cplusplus
//#include "operating_system-windows_common/windows_commoncomptr.h"
//#endif


//#ifndef UNIVERSAL_WINDOWS
//
//CLASS_DECL_ACME void WINAPI sleep(::u32 dw::durations);
//
//#endif

/*#define GetAValue(rgb)      (lower_byte((rgb)>>24))
#define argb(a, r,g,b)          ((color32_t)(((::u8)(r)|((::u16)((::u8)(g))<<8))|(((::u32)(::u8)(b))<<16)|(((::u32)(::u8)(a))<<24)))*/


//CLASS_DECL_ACME int_bool os_initialize();
//CLASS_DECL_ACME int_bool os_finalize();


CLASS_DECL_ACME int_bool main_initialize();
CLASS_DECL_ACME int_bool main_finalize();


CLASS_DECL_ACME void set_main_htask(htask htask);
CLASS_DECL_ACME void set_main_itask(itask itask);
CLASS_DECL_ACME htask main_htask();
CLASS_DECL_ACME itask main_itask();

//CLASS_DECL_ACME oswindow get_focus();
//CLASS_DECL_ACME oswindow set_focus(::acme::windowing::window * pacmewindowingwindow);

//CLASS_DECL_ACME oswindow get_window(::acme::windowing::window * pacmewindowingwindow, ::i32 iWindow);

//CLASS_DECL_ACME void attach_thread_input_to_main_thread(int_bool bAttach);


//CLASS_DECL_ACME ::u32 WINAPI WaitForSingleObject( _In_ HANDLE hHandle, _In_ ::u32 dw::durations );




//CLASS_DECL_ACME char_pointer getenv(const_char_pointer pszName);
//CLASS_DECL_ACME HANDLE WINAPI CreateMutex(_In_opt_ LPSECURITY_ATTRIBUTES lpMutexAttributes, _In_ BOOL bInitialOwner, _In_opt_ const_char_pointer lpName  );

//CLASS_DECL_ACME HANDLE WINAPI CreateMutexW(    _In_opt_ LPSECURITY_ATTRIBUTES lpMutexAttributes,    _In_ BOOL bInitialOwner,    _In_opt_ const ::wide_character * lpName    );



//inline int_bool is_nok(hfile hfile);

//
//inline int_bool is_ok(hfile hfile);
//
//
//CLASS_DECL_ACME void dpi_os_initialize();
//



