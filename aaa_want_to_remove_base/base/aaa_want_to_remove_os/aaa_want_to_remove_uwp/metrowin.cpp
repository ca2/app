#include "framework.h"



typedef bool
(WINAPI * LPFN_ChangeWindowMessageFilter)(
    _In_ UINT message,
    _In_ DWORD dwFlag);


LPFN_ChangeWindowMessageFilter g_pfnChangeWindowMessageFilter = nullptr;



string key_to_char(WPARAM wparam, LPARAM lparam)
{
   __throw(::exception::exception("todo"));
}



//
//string get_system_error_message(u32 dwError)
//{
//   wstring wstr;
//   wstr.get_buffer(64 * 1024 / sizeof(unichar));
//   FormatMessageW(
//      FORMAT_MESSAGE_FROM_SYSTEM,
//      nullptr,
//      dwError,
//      0,
//      (LPWSTR) (LPCWSTR) wstr,
//      wstr.get_storage_size(),
//      nullptr);
//   string str(wstr);
//   return str;
//}

//
//WINBOOL IsWindow(oswindow oswindow)
//{
//
//   if(((void *) oswindow) == nullptr)
//      return FALSE;
//
//   return TRUE;
//
//}
//



//void output_debug_string(const char * psz)
//{
//   
//   ::output_debug_string(wstring(psz));
//
//}


//DWORD WINAPI WaitForSingleObject( _In_ HANDLE hHandle, _In_ DWORD dwMilliseconds )
//{
//
//   return ::WaitForSingleObjectEx(hHandle, dwMilliseconds, FALSE);
//
//}

//
//
//CLASS_DECL_BASE
//HANDLE
//WINAPI
//CreateMutex(
//    _In_opt_ LPSECURITY_ATTRIBUTES lpMutexAttributes,
//    _In_ BOOL bInitialOwner,
//    _In_opt_ LPCSTR lpName
//    )
//{
//   return CreateMutexW(lpMutexAttributes, bInitialOwner, wstring(lpName));
//}
//
//CLASS_DECL_BASE char* getenv (const char* name)
//{
//   return "";
//}
//
//
//CLASS_DECL_BASE
//HANDLE
//WINAPI
//CreateMutexW(
//    _In_opt_ LPSECURITY_ATTRIBUTES lpMutexAttributes,
//    _In_ BOOL bInitialOwner,
//    _In_opt_ LPCWSTR lpName
//    )
//{
//   return ::CreateMutexEx(lpMutexAttributes, lpName, bInitialOwner ?  CREATE_MUTEX_INITIAL_OWNER : 0, DELETE | SYNCHRONIZE);
//}


// bool __node_base_pre_init()
// {

//    return true;

// }


// bool __node_base_pos_init()
// {

//    return true;

// }


// bool __node_base_pre_term()
// {

//    return true;

// }


// bool __node_base_pos_term()
// {

//    return true;

// }





