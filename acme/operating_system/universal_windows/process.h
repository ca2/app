#pragma once


CLASS_DECL_ACME bool process_modules(string_array & stra, ::u32 processID);

   
CLASS_DECL_ACME bool load_modules_diff(string_array & straOld, string_array & straNew, const char * pszExceptDir);



