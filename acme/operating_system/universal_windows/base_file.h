#pragma once
//
//
//CLASS_DECL_ACME void hfile_set_size(HANDLE h, long long iSize);
//CLASS_DECL_ACME unsigned int Winwindows_get_file_attributes(const unichar * psz);
//#define WinGetFileAttributes Winwindows_get_file_attributes
//CLASS_DECL_ACME unsigned int GetFileSize(HANDLE h, LPDWORD lpdwHi);
//CLASS_DECL_ACME unsigned int WinSetFilePointer(HANDLE h, int lMove, PLONG plHi, unsigned int dwMeth);
////CLASS_DECL_ACME HANDLE FindFirstFile(const ::scoped_string & scopedstr, WIN32_FIND_DATA * pdata);
//
//
//
//CLASS_DECL_ACME HANDLE WinFindFirstFileA(const char * pwsz, WIN32_FIND_DATAA * pdata);
//CLASS_DECL_ACME HANDLE WinFindFirstFileW(const unichar * pwsz, WIN32_FIND_DATAW * pdata);



int ftruncate(int file, filesize len);
