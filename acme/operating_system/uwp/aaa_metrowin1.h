#pragma once


namespace universal_windows
{


   class thread;

   class _UWP
   {
      int function();
   };

   CLASS_DECL_ACME HINSTANCE   LoadLibrary(const char * lpsz);
   CLASS_DECL_ACME bool        SHGetSpecialFolderPath(oswindow hwnd, string &str, int csidl, bool fCreate);
   CLASS_DECL_ACME ::u32       GetFileAttributes(const char * lpFileName);
   CLASS_DECL_ACME bool        CreateDirectory(const char * lpPathName, LPSECURITY_ATTRIBUTES lpSecurityAttributes);
   CLASS_DECL_ACME ::u32       GetCurrentDirectory(string & str);
   CLASS_DECL_ACME ::u32       GetTempPath(string & str);
   CLASS_DECL_ACME ::i32        RegQueryValue(HKEY hkey, const char * lpszSubKey, string & str);
   CLASS_DECL_ACME HICON       ExtractIcon(HINSTANCE hInst, const char * lpszExeFileName, ::u32 nIconIndex);
   CLASS_DECL_ACME bool        DeleteFile(const char * lpFileName);
   CLASS_DECL_ACME int         GetMenuStringW(HMENU hMenu, ::u32 uDItem, string & str, ::u32 flags);
   CLASS_DECL_ACME void        TimeToFileTime(::matter * pobject, const ::earth::time& time, LPFILETIME pFileTime);


} // namespace universal_windows



// helpers for registering your own WNDCLASSes
#ifndef _UWP

CLASS_DECL_ACME LRESULT CALLBACK __window_procedure(oswindow hWnd, ::u32 nMsg, WPARAM wParam, LPARAM lParam);
CLASS_DECL_ACME WNDPROC __get_window_procedure();
#define __window_procedure (*__get_window_procedure())

/*typedef void (__MSG_CALL ::user::interaction_impl::*__PMSGW)();
   // like '__PMSG' but for ::user::interaction_impl derived classes only

typedef void (__MSG_CALL ::thread::*__PMSGT)();
   // like '__PMSG' but for thread-derived classes only*/
#endif




CLASS_DECL_ACME ::i32 delete_registry_tree_helper(HKEY hParentKey, const ::string & strKeyName);



CLASS_DECL_ACME ::_UWP::thread * __get_thread();
CLASS_DECL_ACME void __set_thread(::thread * pthread);
CLASS_DECL_ACME MSG* __get_current_message();

CLASS_DECL_ACME void __end_thread(::matter * pobject, ::u32 nExitCode, bool bDelete = true);

CLASS_DECL_ACME void __init_thread();
//CLASS_DECL_ACME void __term_thread(::matter * pobject, HINSTANCE hInstTerm = nullptr);
//CLASS_DECL_ACME void __term_thread(::matter * pobject);


//CLASS_DECL_ACME __pointer(::user::interaction) __get_main_window();


CLASS_DECL_ACME void __delete_object(HGDIOBJ* pObject);

void CLASS_DECL_ACME __global_free(HGLOBAL hGlobal);
