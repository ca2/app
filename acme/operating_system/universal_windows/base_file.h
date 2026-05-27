#pragma once
//
//
//CLASS_DECL_ACME void hfile_set_size(HANDLE h, ::i64 iSize);
//CLASS_DECL_ACME ::u32 Winwindows_get_file_attributes(const wide_character * psz);
//#define WinGetFileAttributes Winwindows_get_file_attributes
//CLASS_DECL_ACME ::u32 GetFileSize(HANDLE h, LPDWORD lpdwHi);
//CLASS_DECL_ACME ::u32 WinSetFilePointer(HANDLE h, ::i32 lMove, PLONG plHi, ::u32 dwMeth);
////CLASS_DECL_ACME HANDLE FindFirstFile(const ::scoped_string & scopedstr, WIN32_FIND_DATA * pdata);
//
//
//
//CLASS_DECL_ACME HANDLE WinFindFirstFileA(const_char_pointer pwsz, WIN32_FIND_DATAA * pdata);
//CLASS_DECL_ACME HANDLE WinFindFirstFileW(const wide_character * pwsz, WIN32_FIND_DATAW * pdata);



::i32 ftruncate(::i32 file, filesize len);
