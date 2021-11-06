#pragma once


//CLASS_DECL_CORE void hfile_set_size(HANDLE h, i64 iSize);
CLASS_DECL_CORE ::u32 Winwindows_get_file_attributes(const unichar * psz);
#define WinGetFileAttributes Winwindows_get_file_attributes
CLASS_DECL_CORE ::u32 GetFileSize(HANDLE h, LPDWORD lpdwHi);
CLASS_DECL_CORE ::u32 WinSetFilePointer(HANDLE h, ::i32 lMove, PLONG plHi, ::u32 dwMeth);
//CLASS_DECL_CORE HANDLE FindFirstFile(const ::string & psz, WIN32_FIND_DATA * pdata);



CLASS_DECL_CORE HANDLE WinFindFirstFileA(const ::string & pwsz, WIN32_FIND_DATAA * pdata);
CLASS_DECL_CORE HANDLE WinFindFirstFileW(const unichar * pwsz, WIN32_FIND_DATAW * pdata);



int ftruncate(int file, filesize len);
