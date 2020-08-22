#pragma once


//CLASS_DECL_AXIS void ensure_file_size(HANDLE h, i64 iSize);
CLASS_DECL_AXIS DWORD Winwindows_get_file_attributes(const unichar * psz);
#define WinGetFileAttributes Winwindows_get_file_attributes
CLASS_DECL_AXIS DWORD GetFileSize(HANDLE h, LPDWORD lpdwHi);
CLASS_DECL_AXIS DWORD WinSetFilePointer(HANDLE h, LONG lMove, PLONG plHi, DWORD dwMeth);
//CLASS_DECL_AXIS HANDLE FindFirstFile(const char * psz, WIN32_FIND_DATA * pdata);



CLASS_DECL_AXIS HANDLE WinFindFirstFileA(const char * pwsz, WIN32_FIND_DATAA * pdata);
CLASS_DECL_AXIS HANDLE WinFindFirstFileW(const unichar * pwsz, WIN32_FIND_DATAW * pdata);



int ftruncate(int file, filesize len);