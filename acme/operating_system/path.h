#pragma once


class string_to_string_lookup;

   
/// A Default search path for PATH environment variable;
::string path_get_default_path();

/// get next entry in a PATH-environment-variable-like value
bool path_get_next_path(::scoped_string & scopedstr, ::string::RANGE & rangePath);


::file::path _path_get_path(const scoped_string & scopedstrCommand, const ::scoped_string & scopedstrPath, string_to_string_lookup * plookupEnvironment);


::file::path path_get_path(const scoped_string & scopedstrCommand, string_to_string_lookup * plookupEnvironment);


::file::path path_try_get_path(const scoped_string & scopedstrCommand, string_to_string_lookup * plookupEnvironment);


bool path_is_absolute_path(const ::scoped_string & scopedstr);



