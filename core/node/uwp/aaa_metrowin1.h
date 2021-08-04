#pragma once


namespace uwp
{


   class thread;

   class _UWP
   {
      int function();
   };

   CLASS_DECL_CORE HINSTANCE   LoadLibrary(const ::string & lpsz);
   CLASS_DECL_CORE bool        SHGetSpecialFolderPath(oswindow hwnd, string &str, int csidl, bool fCreate);
   CLASS_DECL_CORE ::u32       GetFileAttributes(const ::string & lpFileName);
   CLASS_DECL_CORE bool        CreateDirectory(const ::string & lpPathName, LPSECURITY_ATTRIBUTES lpSecurityAttributes);
   CLASS_DECL_CORE ::u32       GetCurrentDirectory(string & str);
   CLASS_DECL_CORE ::u32       GetTempPath(string & str);
   CLASS_DECL_CORE ::i32        RegQueryValue(HKEY hkey, const ::string & lpszSubKey, string & str);
   CLASS_DECL_CORE HICON       ExtractIcon(HINSTANCE hInst, const ::string & lpszExeFileName, ::u32 nIconIndex);
   CLASS_DECL_CORE bool        DeleteFile(const ::string & lpFileName);
   CLASS_DECL_CORE int         GetMenuStringW(HMENU hMenu, ::u32 uDItem, string & str, ::u32 flags);
   CLASS_DECL_CORE void        TimeToFileTime(::object * pobject, const ::datetime::time& time, LPFILETIME pFileTime);


} // namespace uwp



// helpers for registering your own WNDCLASSes
#ifndef _UWP

CLASS_DECL_CORE LRESULT CALLBACK __window_procedure(oswindow hWnd, ::u32 nMsg, WPARAM wParam, LPARAM lParam);
CLASS_DECL_CORE WNDPROC __get_window_procedure();
#define __window_procedure (*__get_window_procedure())

/*typedef void (__MSG_CALL ::user::interaction_impl::*__PMSGW)();
   // like '__PMSG' but for ::user::interaction_impl derived classes only

typedef void (__MSG_CALL ::thread::*__PMSGT)();
   // like '__PMSG' but for thread-derived classes only*/
#endif




CLASS_DECL_CORE ::i32 delete_registry_tree_helper(HKEY hParentKey, const ::string & strKeyName);



CLASS_DECL_CORE ::_UWP::thread * __get_thread();
CLASS_DECL_CORE void __set_thread(::thread * pthread);
CLASS_DECL_CORE MSG* __get_current_message();

CLASS_DECL_CORE void __end_thread(::object * pobject, ::u32 nExitCode, bool bDelete = true);

CLASS_DECL_CORE void __init_thread();
//CLASS_DECL_CORE void __term_thread(::object * pobject, HINSTANCE hInstTerm = nullptr);
//CLASS_DECL_CORE void __term_thread(::object * pobject);


//CLASS_DECL_CORE __pointer(::user::interaction) __get_main_window();


CLASS_DECL_CORE void __delete_object(HGDIOBJ* pObject);

void CLASS_DECL_CORE __global_free(HGLOBAL hGlobal);
