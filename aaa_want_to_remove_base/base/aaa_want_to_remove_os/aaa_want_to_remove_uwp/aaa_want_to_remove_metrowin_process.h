#pragma once


CLASS_DECL_BASE void call_sync(const char * path, const char * param);


CLASS_DECL_BASE bool process_modules(string_array & stra, DWORD processID);

   
CLASS_DECL_BASE bool load_modules_diff(string_array & straOld, string_array & straNew, const char * pszExceptDir);



