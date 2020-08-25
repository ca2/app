#pragma once


//CLASS_DECL_CORE void ensure_file_size(HANDLE h, i64 iSize);
CLASS_DECL_CORE DWORD Winwindows_get_file_attributes(const unichar * psz);
#define WinGetFileAttributes Winwindows_get_file_attributes
CLASS_DECL_CORE DWORD GetFileSize(HANDLE h, LPDWORD lpdwHi);
CLASS_DECL_CORE DWORD WinSetFilePointer(HANDLE h, LONG lMove, PLONG plHi, DWORD dwMeth);
//CLASS_DECL_CORE HANDLE FindFirstFile(const char * psz, WIN32_FIND_DATA * pdata);



CLASS_DECL_CORE HANDLE WinFindFirstFileA(const char * pwsz, WIN32_FIND_DATAA * pdata);
CLASS_DECL_CORE HANDLE WinFindFirstFileW(const unichar * pwsz, WIN32_FIND_DATAW * pdata);



int ftruncate(int file, filesize len);