#pragma once


CLASS_DECL_ACME ::u32 windows_get_file_attributes(const char* path);
CLASS_DECL_ACME int_bool windows_create_directory(const char* pszPath ARG_SEC_ATTRS);


using hfile = void *;

#define hfile_null ((::hfile)(::iptr) -1)

inline int_bool is_nok(hfile hfile)
{

   return hfile == nullptr || hfile == hfile_null;

}


inline int_bool is_ok(hfile hfile)
{

   return !is_nok(hfile);

}

using HANDLE = void *;

CLASS_DECL_ACME hfile hfile_create(
const char *            pFileName,
::u32                   dwDesiredAccess,
::u32                   dwShareMode,
void *                  pSecurityAttributes,
::u32                   dwCreationDisposition,
::u32                   dwFlagsAndAttributes,
HANDLE                  hTemplateFile
);


CLASS_DECL_ACME ::e_status hfile_close(hfile hfile);
CLASS_DECL_ACME memsize hfile_read(hfile hfile, void * p, memsize s);
CLASS_DECL_ACME ::e_status hfile_write(hfile hfile, const void* p, memsize s);
