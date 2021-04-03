#pragma once


namespace uwp
{


   class thread;

   class _UWP
   {
      int function();
   };

   CLASS_DECL_AXIS HINSTANCE   LoadLibrary(const char * lpsz);
   CLASS_DECL_AXIS bool        SHGetSpecialFolderPath(oswindow hwnd, string &str, int csidl, bool fCreate);
   CLASS_DECL_AXIS ::u32       GetFileAttributes(const char * lpFileName);
   CLASS_DECL_AXIS bool        CreateDirectory(const char * lpPathName, LPSECURITY_ATTRIBUTES lpSecurityAttributes);
   CLASS_DECL_AXIS ::u32       GetCurrentDirectory(string & str);
   CLASS_DECL_AXIS ::u32       GetTempPath(string & str);
   CLASS_DECL_AXIS ::i32        RegQueryValue(HKEY hkey, const char * lpszSubKey, string & str);
   CLASS_DECL_AXIS HICON       ExtractIcon(HINSTANCE hInst, const char * lpszExeFileName, ::u32 nIconIndex);
   CLASS_DECL_AXIS bool        DeleteFile(const char * lpFileName);
   CLASS_DECL_AXIS int         GetMenuStringW(HMENU hMenu, ::u32 uDItem, string & str, ::u32 flags);
   CLASS_DECL_AXIS void        TimeToFileTime(::object * pobject, const ::datetime::time& time, LPFILETIME pFileTime);


} // namespace uwp



// helpers for registering your own WNDCLASSes
#ifndef _UWP

CLASS_DECL_AXIS LRESULT CALLBACK __window_procedure(oswindow hWnd, ::u32 nMsg, WPARAM wParam, LPARAM lParam);
CLASS_DECL_AXIS WNDPROC __get_window_procedure();
#define __window_procedure (*__get_window_procedure())

/*typedef void (__MSG_CALL ::user::interaction_impl::*__PMSGW)();
   // like '__PMSG' but for ::user::interaction_impl derived classes only

typedef void (__MSG_CALL ::thread::*__PMSGT)();
   // like '__PMSG' but for thread-derived classes only*/
#endif




CLASS_DECL_AXIS ::i32 delete_registry_tree_helper(HKEY hParentKey, const string & strKeyName);



CLASS_DECL_AXIS ::_UWP::thread * __get_thread();
CLASS_DECL_AXIS void __set_thread(::thread * pthread);
CLASS_DECL_AXIS MSG* __get_current_message();

CLASS_DECL_AXIS void __end_thread(::object * pobject, ::u32 nExitCode, bool bDelete = true);

CLASS_DECL_AXIS void __init_thread();
//CLASS_DECL_AXIS void __term_thread(::object * pobject, HINSTANCE hInstTerm = nullptr);
//CLASS_DECL_AXIS void __term_thread(::object * pobject);


//CLASS_DECL_AXIS __pointer(::user::interaction) __get_main_window();


CLASS_DECL_AXIS void __delete_object(HGDIOBJ* pObject);

void CLASS_DECL_AXIS __global_free(HGLOBAL hGlobal);
