#pragma once


namespace universal_windows
{


   class thread;

   class UNIVERSAL_WINDOWS
   {
      int function();
   };

   CLASS_DECL_ACID HINSTANCE   LoadLibrary(const char * lpsz);
   CLASS_DECL_ACID bool        SHGetSpecialFolderPath(oswindow hwnd, string &str, int csidl, bool fCreate);
   CLASS_DECL_ACID ::u32       GetFileAttributes(const char * lpFileName);
   CLASS_DECL_ACID bool        CreateDirectory(const char * lpPathName, LPSECURITY_ATTRIBUTES lpSecurityAttributes);
   CLASS_DECL_ACID ::u32       GetCurrentDirectory(string & str);
   CLASS_DECL_ACID ::u32       GetTempPath(string & str);
   CLASS_DECL_ACID ::i32        RegQueryValue(HKEY hkey, const char * lpszSubKey, string & str);
   CLASS_DECL_ACID HICON       ExtractIcon(HINSTANCE hInst, const char * lpszExeFileName, ::u32 nIconIndex);
   CLASS_DECL_ACID bool        DeleteFile(const char * lpFileName);
   CLASS_DECL_ACID int         GetMenuStringW(HMENU hMenu, ::u32 uDItem, string & str, ::u32 flags);
   CLASS_DECL_ACID void        TimeToFileTime(::particle * pparticle, const ::earth::time& time, LPFILETIME pFileTime);


} // namespace universal_windows



// helpers for registering your own WNDCLASSes
#ifndef UNIVERSAL_WINDOWS

CLASS_DECL_ACID LRESULT CALLBACK __window_procedure(oswindow hWnd, ::u32 nMsg, WPARAM wParam, LPARAM lParam);
CLASS_DECL_ACID WNDPROC __get_window_procedure();
#define __window_procedure (*__get_window_procedure())

/*typedef void (__MSG_CALL ::user::interaction_impl::*__PMSGW)();
   // like '__PMSG' but for ::user::interaction_impl derived classes only

typedef void (__MSG_CALL ::thread::*__PMSGT)();
   // like '__PMSG' but for thread-derived classes only*/
#endif




CLASS_DECL_ACID ::i32 delete_registry_tree_helper(HKEY hParentKey, const ::string & strKeyName);



CLASS_DECL_ACID ::UNIVERSAL_WINDOWS::thread * __get_thread();
CLASS_DECL_ACID void __set_thread(::thread * pthread);
CLASS_DECL_ACID MSG* __get_current_message();

CLASS_DECL_ACID void __end_thread(::particle * pparticle, ::u32 nExitCode, bool bDelete = true);

CLASS_DECL_ACID void __init_thread();
//CLASS_DECL_ACID void __term_thread(::particle * pparticle, HINSTANCE hInstTerm = nullptr);
//CLASS_DECL_ACID void __term_thread(::particle * pparticle);


//CLASS_DECL_ACID ::pointer<::user::interaction>__get_main_window();


CLASS_DECL_ACID void __delete_object(HGDIOBJ* pObject);

void CLASS_DECL_ACID __global_free(HGLOBAL hGlobal);
