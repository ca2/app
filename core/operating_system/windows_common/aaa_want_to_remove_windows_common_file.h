#pragma once


CLASS_DECL_CORE HANDLE create_file(
const char *            pFileName,

::u32                   dwDesiredAccess,
::u32                   dwShareMode,
LPSECURITY_ATTRIBUTES   pSecurityAttributes,

::u32                   dwCreationDisposition,
::u32                   dwFlagsAndAttributes,
HANDLE                  hTemplateFile
);



