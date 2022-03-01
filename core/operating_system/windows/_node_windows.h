#pragma once


#include <Wtsapi32.h>
#include <Psapi.h>
#include <WinCred.h>
#include <errno.h>
#include <io.h>
#include <fcntl.h>
#include <ddeml.h>  // for MSGF_DDEMGR
#include <dde.h>
#include <ShObjIdl.h>

#include <shlobj.h>
#include <Security.h>
#include <shlobj.h>


//#include "exception.h"

string get_error_message(::u32 dwError);


CLASS_DECL_CORE bool __initialize();


//#include "system_dir.h"
//#include "system_file.h"
//
//#include "folder_watch.h"
//#include "factory_exchange.h"
//#include "uac_tools.h"
//#include "thread.h"
//#include "file.h"
//#include "crypto.h"
//#include "ip_enum.h"


#define NODE_THREAD(pthread) (dynamic_cast < ::windows::thread * > (dynamic_cast < thread * >(pthread)))


//
//#include "command.h"



void CLASS_DECL_CORE __cdecl _ca2_purecall();
void CLASS_DECL_CORE __cdecl _null_se_translator(u32 uiCode, EXCEPTION_POINTERS * ppointers);
bool CLASS_DECL_CORE __windows_init();
i32 CLASS_DECL_CORE __windows_main(::aura::system * psystem, ::create * pmaininitdata);






//#include "file_find.h"
//#include "file.h"
//#include "shell.h"
//#include "stdio_file.h"
//#include "registry.h"
//#include "os.h"


// Sanity checks for ATOMs
CLASS_DECL_CORE bool __is_valid_atom(ATOM nAtom);
//CLASS_DECL_CORE bool __is_valid_atom(const ::string & psz);
CLASS_DECL_CORE bool __is_valid_atom(const wchar_t * psz);


/////////////////////////////////////////////////////////////////////////////
// locale-invariant comparison helpers till CRT gets that support
inline i32 __invariant_stricmp(const ::string &pszLeft, const ::string &pszRight)
{
#ifdef WINDOWS_DESKTOP
   return ::CompareStringA(MAKELCID(MAKELANGID(LANG_ENGLISH,SUBLANG_ENGLISH_US),SORT_DEFAULT),
                           NORM_IGNORECASE,
                           pszLeft,
                           -1,
                           pszRight,
                           -1) - CSTR_EQUAL;
#else
   return ansi_compare_ci(pszLeft,pszRight);
#endif
}

inline i32 __invariant_stricmp(const unichar *pwszLeft,const unichar *pwszRight)
{
#ifdef WINDOWS_DESKTOP
   return ::CompareStringW(MAKELCID(MAKELANGID(LANG_ENGLISH,SUBLANG_ENGLISH_US),SORT_DEFAULT),
                           NORM_IGNORECASE,
                           pwszLeft,
                           -1,
                           pwszRight,
                           -1) - CSTR_EQUAL;
#else
   return wide_compare_case_insensitive(pwszLeft,pwszRight);
#endif
}

/////////////////////////////////////////////////////////////////////////////
// Portability abstractions

#define __set_dialog_control_id(oswindow, nID)     SetWindowLong(oswindow, GWL_ID, nID)
#define __set_dialog_control_id_(oswindow, nID)     oswindow->SetWindowLong(GWL_ID, nID)
#define __get_dialog_control_id(oswindow)         ((::u32)(::u16)::GetDlgCtrlID(oswindow))
#define __get_dialog_control_id_(oswindow)         ((::u32)(::u16)oswindow->GetDlgCtrlId())


//#include "pipe.h"
//#include "process.h"










namespace windows
{


   class thread;

   class windows
   {
      i32 function();
   };

   CLASS_DECL_CORE HINSTANCE   load_library(const ::string & psz);

   CLASS_DECL_CORE bool        shell_get_special_folder_path(oswindow oswindow,::file::path &str,i32 csidl,bool fCreate);
   CLASS_DECL_CORE ::file::path  shell_get_special_folder_path(i32 csidl, bool fCreate = true, oswindow oswindow = nullptr);
   CLASS_DECL_CORE ::u32       get_file_attributes(const ::string & pFileName);

   CLASS_DECL_CORE ::u32       get_current_directory(string & str);
   CLASS_DECL_CORE ::u32       get_temp_path(string & str);
   CLASS_DECL_CORE ::i32        reg_query_value(HKEY hkey, const ::string & pszSubKey,string & str);

   CLASS_DECL_CORE HICON       extract_icon(HINSTANCE hInst, const ::string & pszExeFileName,::u32 nIconIndex);

   CLASS_DECL_CORE bool        delete_file(const ::string & pFileName);

   //CLASS_DECL_CORE i32     get_menu_string(HMENU hMenu,::u32 uDItem,string & str,::u32 flags);
   //CLASS_DECL_CORE void        time_to_file_time(::object * pobject,const ::earth::time& time,LPFILETIME pFileTime);


} // namespace windows





CLASS_DECL_CORE ::i32 delete_registry_tree_helper(HKEY hParentKey, const ::string & strKeyName);


CLASS_DECL_CORE __pointer(::aura::application) __get_app();
CLASS_DECL_CORE HINSTANCE __get_resource_handle();
CLASS_DECL_CORE void __set_resource_handle(HINSTANCE hInstResource);

CLASS_DECL_CORE HINSTANCE __get_resource_handle();
CLASS_DECL_CORE HINSTANCE __find_string_resource_handle(::u32 nID);



CLASS_DECL_CORE i32 app_main(::aura::system * psystem, HINSTANCE hInstance, HINSTANCE hPrevInstance, char * pCmdLine, ::e_display edisplay);




//#include "tts_speaker.h"




