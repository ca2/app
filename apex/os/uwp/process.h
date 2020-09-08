#pragma once


CLASS_DECL_APEX bool process_modules(string_array & stra, DWORD processID);

   
CLASS_DECL_APEX bool load_modules_diff(string_array & straOld, string_array & straNew, const char * pszExceptDir);



