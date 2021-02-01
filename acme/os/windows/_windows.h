#pragma once


CLASS_DECL_ACME void TRACELASTERROR();

CLASS_DECL_ACME::file::path get_known_folder(REFKNOWNFOLDERID kfid);
//#include "acme/os/windows_common/comptr.h"


#include "acme/os/windows_common/comptr.h"


inline HWND __hwnd(oswindow oswindow)
{

   return (HWND)oswindow;

}



CLASS_DECL_ACME inline i32 muldiv32(i32 a, i32 b, i32 ca)
{

   return (i32) ::MulDiv((i32)a, (i32)b, (i32)ca);

}

CLASS_DECL_ACME int_bool HFILE_set_size(HANDLE h, u64 iSize);

#ifdef WINDOWS
CLASS_DECL_ACME int_bool read_resource_as_file(const char * pszFile, HINSTANCE hinst, ::u32 nID, LPCTSTR pcszType);

#endif


CLASS_DECL_ACME TCHAR *** process_get_pargv();
CLASS_DECL_ACME TCHAR ** process_get_argv();
#include <fcntl.h>
#include <VersionHelpers.h>
#include <ddeml.h>
#include <share.h>
#include <io.h>
#include <process.h>
#include <Winsvc.h>




namespace str
{

#ifdef WINDOWS

   inline ansistring & assign(ansistring & ansistrDst, const cotaskptr < PWSTR > & pwidesz);

   inline widestring & assign(widestring & widestrDst, const cotaskptr < PSTR > & pansisz);

   inline ansistring & assign(ansistring & ansistrDst, const cotaskptr < PWSTR > & pwidesz);

   inline widestring & assign(widestring & widestrDst, const cotaskptr < PSTR > & pansisz);

#endif


#ifdef WINDOWS
   // wd16
   inline  BSTR               AllocSysString(const ansichar * pchData, strsize nDataLength) noexcept;
   inline  bool               ReAllocSysString(BSTR * pbstr, const ansichar * pchData, strsize nDataLength) noexcept;

#endif

#ifdef WINDOWS
   // wd32
   inline  BSTR               AllocSysString(const wd32char * pchData, strsize nDataLength) noexcept;
   inline  bool               ReAllocSysString(BSTR * pbstr, const wd32char * pchData, strsize nDataLength) noexcept;

#endif


} //namespace str

CLASS_DECL_ACME string get_command_line(HANDLE handleProcess);



#ifdef WINDOWS


CLASS_DECL_ACME FILETIME __FILETIME(const ::datetime::time & time);


#endif



void __copy(payload * ppayload, const FILETIME * ptime);
void __copy(payload * ppayload, const SYSTEMTIME * ptime);





inline void __copy(payload * ppayload, const LPDWORD * lppdw)
{

   ppayload->operator = ((::u32 *)*lppdw);

}

inline void __copy(payload * ppayload, const long * plong)
{

   ppayload->operator = ((::i32)*plong);

}


inline void __copy(payload * ppayload, const DWORD * pdw)
{

   ppayload->operator = ((::u32)*pdw);

}


//inline void __copy(LPDWORD * ppdw, const payload * ppayload)
//{
//
//   *ppdw = (LPDWORD) (u32*) *ppayload;
//
//}

inline void __copy(long * plong, const payload * ppayload)
{

   *plong = (long)(i32)*ppayload;

}
inline void __copy(DWORD * pdw, const payload * ppayload)
{

   *pdw = (DWORD)(u32)*ppayload;

}



CLASS_DECL_ACME ::file::path module(HMODULE pmoduleosdata = nullptr);
CLASS_DECL_ACME string read_resource_as_string(hinstance hinst, ::u32 nID, const char * pcszType, strsize iReadAtMostByteCount = -1);
CLASS_DECL_ACME bool read_resource_as_memory(memory & m, HINSTANCE hinst, DWORD nID, const char * pcszType, strsize iReadAtMostByteCount = -1);


CLASS_DECL_ACME HANDLE dup_handle(HANDLE h);
#include "file.h"

#include "simple_hold_handle.h"
#include "process.h"
#include "registry.h"

inline comptr < IStream > create_istream(const memory_base & memory)
{

   return ::SHCreateMemStream(memory.get_data(), (::u32)memory.get_size());

}



CLASS_DECL_ACME time_t __time(const SYSTEMTIME & st, i32 nDST = -1);
CLASS_DECL_ACME time_t __time(const FILETIME & ft, i32 nDST = -1);
CLASS_DECL_ACME SYSTEMTIME __systemtime(const ::datetime::time & time);
inline filetime __filetime(const FILETIME & filetime) { return make64_from32(filetime.dwLowDateTime, filetime.dwHighDateTime); }



CLASS_DECL_ACME bool is_valid_FILETIME(const FILETIME & ft) noexcept;

template < typename CHAR >
CLASS_DECL_ACME BSTR AllocSysString(const ::string_base < CHAR > & str);


template < typename CHAR >
CLASS_DECL_ACME BSTR SetSysString(BSTR * pbstr, const ::string_base < CHAR > & str);


CLASS_DECL_ACME int_bool read_resource_as_file(const char * pszFile, HINSTANCE hinst, ::u32 nID, LPCTSTR pcszType);



#include "exception_engine.h"


#include "dir.h"


#include "itemidlist.h"


//#include "top_level_enum.h"


#include "extract_icon.h"


//#include "file_memory_map.h"


//#include "process_env_reader.h"





#include "api.h"



namespace windows
{


   CLASS_DECL_ACME string langid_to_iso(LANGID langid);


} // namespace windows


namespace path
{


   CLASS_DECL_ACME ::file::path module(HMODULE hmodule);


} // namespace path



