#pragma once
//
//
//CLASS_DECL_ACME void hfile_set_size(HANDLE h, i64 iSize);
//CLASS_DECL_ACME ::u32 Winwindows_get_file_attributes(const unichar * psz);
//#define WinGetFileAttributes Winwindows_get_file_attributes
//CLASS_DECL_ACME ::u32 GetFileSize(HANDLE h, LPDWORD lpdwHi);
//CLASS_DECL_ACME ::u32 WinSetFilePointer(HANDLE h, ::i32 lMove, PLONG plHi, ::u32 dwMeth);
////CLASS_DECL_ACME HANDLE FindFirstFile(const char * psz, WIN32_FIND_DATA * pdata);
//
//
//
//CLASS_DECL_ACME HANDLE WinFindFirstFileA(const char * pwsz, WIN32_FIND_DATAA * pdata);
//CLASS_DECL_ACME HANDLE WinFindFirstFileW(const unichar * pwsz, WIN32_FIND_DATAW * pdata);



int ftruncate(int file, filesize len);