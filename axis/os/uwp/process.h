#pragma once


CLASS_DECL_AXIS bool process_modules(string_array & stra, DWORD processID);

   
CLASS_DECL_AXIS bool load_modules_diff(string_array & straOld, string_array & straNew, const char * pszExceptDir);



