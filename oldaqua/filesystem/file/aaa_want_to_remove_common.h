#pragma once


//#include "aura/primitive/primitive/memory.h"


//CLASS_DECL_AQUA memory file_as_memory(const char * path);
//CLASS_DECL_AQUA memsize file_as_memory(const char * path, void * p, memsize s);
//CLASS_DECL_AQUA string file_as_string(const char * path);
//CLASS_DECL_AQUA string file_extension_dup(const char * path);
//CLASS_DECL_AQUA string get_temp_file_name_dup(const char * pszName, const char * pszExtension);
//CLASS_DECL_AQUA string file_final_extension_dup(const char * path);
//CLASS_DECL_AQUA string url_dir_name_for_relative(const char * pszPath);
///CLASS_DECL_AQUA string solve_relative(const string & str);
//CLASS_DECL_AQUA string defer_solve_relative(const char * pszRelative, const char * pszAbsolute);
//CLASS_DECL_AQUA string ca2_module_dup();



//template < class POD >
//inline bool file_put_pod(const char * path, const POD & pod)
//{
//   return file_put_contents_dup(path, &pod, sizeof(pod));
//}
//

//
//template < class POD >
//inline bool file_as_pod(POD & pod, const char * path)
//{
//   return file_as_memory(path, &pod, sizeof(pod)) == sizeof(pod);
//}
//



#ifdef WINDOWS_DESKTOP

bool write_memory_to_file(HANDLE hFile, const void * lpBuf, memsize nCount, memsize * puiWritten);

#endif


#include "aura/filesystem/file/dir.h"