#pragma once


CLASS_DECL_AURA int_bool file_exists_raw(const ::string & path1);

CLASS_DECL_AURA void file_put_contents_raw(const ::string & path, const ::string & psz);

CLASS_DECL_AURA void file_add_contents_raw(const ::string & path, const ::string & psz);

CLASS_DECL_AURA void file_beg_contents_raw(const ::string & path, const ::string & psz);

CLASS_DECL_AURA u64 file_length_raw(const ::string & path);

CLASS_DECL_AURA int_bool file_path_is_link(const ::string & pszPath);


