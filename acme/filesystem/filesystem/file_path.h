#pragma once


/// file_path 
///
/// functions in this module should consider just
/// the text from arguments.
/// No file should be actually queried.
/// If possible should be just c strings.
///


#include "acme/constant/path.h"


//CLASS_DECL_ACME bool is_url(const scoped_string & strUrl);


CLASS_DECL_ACME const char * file_path_name(const char * path);
CLASS_DECL_ACME const char * file_path_final_extension(const char * path);
CLASS_DECL_ACME const char * file_path_all_extensions(const char * path);
CLASS_DECL_ACME string file_path_folder(const char * path);
CLASS_DECL_ACME string file_path_title(const char * path);

CLASS_DECL_ACME bool file_path_is_relative(const scoped_string & str);
CLASS_DECL_ACME bool file_path_is_absolute(const scoped_string & str);


CLASS_DECL_ACME bool file_path_is_dots(const scoped_string & str);

CLASS_DECL_ACME bool file_path_is_equal(const scoped_string & strPath1, const scoped_string & strPath2);

CLASS_DECL_ACME string url_dir_name_for_relative(const scoped_string & strPath);

CLASS_DECL_ACME bool solve_relative_inplace(string & str, bool & bUrl, bool & bOnlyNativeFileSep, strsize_array & iaSlash);
CLASS_DECL_ACME string solve_relative(const ::string & strParam, bool * pbUrl = nullptr);
CLASS_DECL_ACME string defer_solve_relative(const scoped_string & strRelative, const scoped_string & strAbsolute);

inline char file_path_separator(enum_path epath);

inline const char * file_path_separator_sz(enum_path epath);

inline char file_path_other_separator(enum_path epath);

CLASS_DECL_ACME enum_path file_path_get_type(const ::string & str, enum_path epathForce = e_path_none);

CLASS_DECL_ACME string file_path_normalize(string strPath, enum_path epath = e_path_none);

CLASS_DECL_ACME bool file_path_normalize_inline(string & strPath, enum_path & epath);









inline char file_path_separator(enum_path epath)
{

#ifdef WINDOWS

   return epath == e_path_file ? '\\' : '/';

#else

   return '/';

#endif

}


inline const char * file_path_separator_sz(enum_path epath)
{

#ifdef WINDOWS

   return epath == e_path_file ? "\\" : "/";

#else

   return "/";

#endif

}

inline char file_path_other_separator(enum_path epath)
{

#ifdef WINDOWS

   return epath == e_path_file ? '/' : '\\';

#else

   return '\\';

#endif

}



