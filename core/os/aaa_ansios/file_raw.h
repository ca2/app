#pragma once


CLASS_DECL_CORE int_bool file_exists_raw(const ::string & path1);

CLASS_DECL_CORE void file_put_contents_raw(const ::string & path, const ::string & psz);

CLASS_DECL_CORE void file_add_contents_raw(const ::string & path, const ::string & psz);

CLASS_DECL_CORE void file_beg_contents_raw(const ::string & path, const ::string & psz);

CLASS_DECL_CORE u64 file_length_raw(const ::string & path);
