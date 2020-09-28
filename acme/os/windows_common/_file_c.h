#pragma once


CLASS_DECL_ACME DWORD windows_get_file_attributes(const char* path);
CLASS_DECL_ACME WINBOOL windows_create_directory(const char* pszPath, LPSECURITY_ATTRIBUTES lpSecurityAttributes);


#define hfile_null INVALID_HANDLE_VALUE


using hfile = HANDLE;


inline int_bool is_nok(hfile hfile)
{

   return hfile == nullptr || hfile == hfile_null;

}


inline int_bool is_ok(hfile hfile)
{

   return !is_nok(hfile);

}


CLASS_DECL_ACME hfile hfile_create(
const char *            pFileName,
DWORD                   dwDesiredAccess,
DWORD                   dwShareMode,
LPSECURITY_ATTRIBUTES   pSecurityAttributes,
DWORD                   dwCreationDisposition,
DWORD                   dwFlagsAndAttributes,
HANDLE                  hTemplateFile
);


CLASS_DECL_ACME ::estatus hfile_close(hfile hfile);
CLASS_DECL_ACME memsize hfile_read(hfile hfile, void * p, memsize s);
CLASS_DECL_ACME ::estatus hfile_write(hfile hfile, const void* p, memsize s);
