#pragma once


CLASS_DECL_ACID bool process_modules(string_array & stra, ::u32 processID);

   
CLASS_DECL_ACID bool load_modules_diff(string_array & straOld, string_array & straNew, const ::scoped_string & scopedstrExceptDir);



