#pragma once


CLASS_DECL_ACME bool process_modules(string_array_base & stra, unsigned int processID);

   
CLASS_DECL_ACME bool load_modules_diff(string_array_base & straOld, string_array_base & straNew, const ::scoped_string & scopedstrExceptDir);



