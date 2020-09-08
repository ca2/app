#pragma once


CLASS_DECL_AQUA HANDLE create_file(
const char *            pFileName,

DWORD                   dwDesiredAccess,
DWORD                   dwShareMode,
LPSECURITY_ATTRIBUTES   pSecurityAttributes,

DWORD                   dwCreationDisposition,
DWORD                   dwFlagsAndAttributes,
HANDLE                  hTemplateFile
);



