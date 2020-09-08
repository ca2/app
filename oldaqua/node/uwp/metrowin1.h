#pragma once


namespace uwp
{


   class thread;

   class _UWP
   {
      int function();
   };

   CLASS_DECL_AQUA HINSTANCE   LoadLibrary(const char * lpsz);
   CLASS_DECL_AQUA bool        SHGetSpecialFolderPath(oswindow hwnd, string &str, int csidl, bool fCreate);
   CLASS_DECL_AQUA DWORD       GetFileAttributes(const char * lpFileName);
   CLASS_DECL_AQUA bool        CreateDirectory(const char * lpPathName, LPSECURITY_ATTRIBUTES lpSecurityAttributes);
   CLASS_DECL_AQUA DWORD       GetCurrentDirectory(string & str);
   CLASS_DECL_AQUA DWORD       GetTempPath(string & str);
   CLASS_DECL_AQUA LONG        RegQueryValue(HKEY hkey, const char * lpszSubKey, string & str);
   CLASS_DECL_AQUA HICON       ExtractIcon(HINSTANCE hInst, const char * lpszExeFileName, UINT nIconIndex);
   CLASS_DECL_AQUA bool        DeleteFile(const char * lpFileName);
   CLASS_DECL_AQUA int         GetMenuStringW(HMENU hMenu, UINT uIDItem, string & str, UINT flags);
   CLASS_DECL_AQUA void        TimeToFileTime(::object * pobject, const ::datetime::time& time, LPFILETIME pFileTime);


} // namespace uwp



// helpers for registering your own WNDCLASSes
#ifndef _UWP

CLASS_DECL_AQUA LRESULT CALLBACK __window_procedure(oswindow hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam);
CLASS_DECL_AQUA WNDPROC __get_window_procedure();
#define __window_procedure (*__get_window_procedure())

/*typedef void (__MSG_CALL ::user::interaction_impl::*__PMSGW)();
   // like '__PMSG' but for ::user::interaction_impl derived classes only

typedef void (__MSG_CALL ::thread::*__PMSGT)();
   // like '__PMSG' but for thread-derived classes only*/
#endif




CLASS_DECL_AQUA LONG delete_registry_tree_helper(HKEY hParentKey, const string & strKeyName);



CLASS_DECL_AQUA ::_UWP::thread * __get_thread();
CLASS_DECL_AQUA void __set_thread(::thread * pthread);
CLASS_DECL_AQUA MSG* __get_current_message();

CLASS_DECL_AQUA void __end_thread(::object * pobject, UINT nExitCode, bool bDelete = TRUE);

CLASS_DECL_AQUA void __init_thread();
//CLASS_DECL_AQUA void __term_thread(::object * pobject, HINSTANCE hInstTerm = nullptr);
//CLASS_DECL_AQUA void __term_thread(::object * pobject);


//CLASS_DECL_AQUA __pointer(::user::interaction) __get_main_window();


CLASS_DECL_AQUA void __delete_object(HGDIOBJ* pObject);

void CLASS_DECL_AQUA __global_free(HGLOBAL hGlobal);
