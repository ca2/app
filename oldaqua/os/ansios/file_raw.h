#pragma once


CLASS_DECL_AQUA int_bool file_exists_raw(const char * path1);

CLASS_DECL_AQUA void file_put_contents_raw(const char * path, const char * psz);

CLASS_DECL_AQUA void file_add_contents_raw(const char * path, const char * psz);

CLASS_DECL_AQUA void file_beg_contents_raw(const char * path, const char * psz);

CLASS_DECL_AQUA u64 file_length_raw(const char * path);

CLASS_DECL_AQUA int_bool file_path_is_link(const char * pszPath);


