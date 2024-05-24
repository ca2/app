#pragma once


CLASS_DECL_ACID i32 file_touch(const ::scoped_string & scopedstr);
CLASS_DECL_ACID int_bool file_exists_raw(const ::file::path & path1);
CLASS_DECL_ACID void file_add_contents_raw(const ::file::path & path, const ::scoped_string & scopedstr);
//CLASS_DECL_ACID string get_current_directory_name();

::file::e_type operating_system_executable_type(const ::file::path & path);

void operating_system_determine_executable(::file::path & path);

::file::path path_defer_apply_working_directory(const ::file::path &path, const ::file::path &working_directory);

bool is_directory_accessible(const ::file::path & path);




