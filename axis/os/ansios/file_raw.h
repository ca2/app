#pragma once


CLASS_DECL_AXIS int_bool file_exists_raw(const char * path1);

CLASS_DECL_AXIS void file_put_contents_raw(const char * path, const char * psz);

CLASS_DECL_AXIS void file_add_contents_raw(const char * path, const char * psz);

CLASS_DECL_AXIS void file_beg_contents_raw(const char * path, const char * psz);

CLASS_DECL_AXIS u64 file_length_raw(const char * path);

CLASS_DECL_AXIS int_bool file_path_is_link(const char * pszPath);


