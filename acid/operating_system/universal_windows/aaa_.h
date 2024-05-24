#pragma once


#include "base_file.h"
#include "parallelization.h"


//#ifdef __cplusplus
//#include "operating_system-windows_common/windows_commoncomptr.h"
//#endif


//#ifndef UNIVERSAL_WINDOWS
//
//CLASS_DECL_ACID void WINAPI sleep(::u32 dw::durations);
//
//#endif

/*#define GetAValue(rgb)      (lower_u8((rgb)>>24))
#define argb(a, r,g,b)          ((color32_t)(((::u8)(r)|((::u16)((::u8)(g))<<8))|(((::u32)(::u8)(b))<<16)|(((::u32)(::u8)(a))<<24)))*/


//CLASS_DECL_ACID int_bool os_initialize();
//CLASS_DECL_ACID int_bool os_finalize();


CLASS_DECL_ACID int_bool main_initialize();
CLASS_DECL_ACID int_bool main_finalize();


CLASS_DECL_ACID void set_main_user_htask(htask_t htask);
CLASS_DECL_ACID void set_main_user_itask(itask_t itask);


CLASS_DECL_ACID htask_t main_user_htask();
CLASS_DECL_ACID itask_t main_user_itask();

//CLASS_DECL_ACID oswindow get_focus();
//CLASS_DECL_ACID oswindow set_focus(oswindow oswindow);

//CLASS_DECL_ACID oswindow get_window(oswindow oswindow, int iWindow);

//CLASS_DECL_ACID void attach_thread_input_to_main_thread(int_bool bAttach);


//CLASS_DECL_ACID ::u32 WINAPI WaitForSingleObject( _In_ HANDLE hHandle, _In_ ::u32 dw::durations );




//CLASS_DECL_ACID char* getenv(const char* name);
//CLASS_DECL_ACID HANDLE WINAPI CreateMutex(_In_opt_ LPSECURITY_ATTRIBUTES lpMutexAttributes, _In_ BOOL bInitialOwner, _In_opt_ const char * lpName  );

//CLASS_DECL_ACID HANDLE WINAPI CreateMutexW(    _In_opt_ LPSECURITY_ATTRIBUTES lpMutexAttributes,    _In_ BOOL bInitialOwner,    _In_opt_ const ::wide_character * lpName    );



//inline int_bool is_nok(hfile hfile);

//
//inline int_bool is_ok(hfile hfile);
//
//
//CLASS_DECL_ACID void dpi_os_initialize();
//



