#pragma once


CLASS_DECL_APEX bool process_modules(string_array & stra, unsigned int processID);

   
CLASS_DECL_APEX bool load_modules_diff(string_array & straOld, string_array & straNew, const ::scoped_string & scopedstrExceptDir);



