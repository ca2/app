#pragma once





CLASS_DECL_CORE DWORD windows_get_file_attributes(const char* path);
CLASS_DECL_CORE WINBOOL window_create_directory(const char* pszPath, LPSECURITY_ATTRIBUTES lpSecurityAttributes);








CLASS_DECL_CORE HANDLE create_file(
const char *            pFileName,

DWORD                   dwDesiredAccess,
DWORD                   dwShareMode,
LPSECURITY_ATTRIBUTES   pSecurityAttributes,

DWORD                   dwCreationDisposition,
DWORD                   dwFlagsAndAttributes,
HANDLE                  hTemplateFile
);
