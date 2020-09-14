#pragma once




//#include "item.h"

//CLASS_DECL_APEX int get_sync_io_error();
//CLASS_DECL_APEX void set_sync_io_error(int iError);
//CLASS_DECL_APEX int get_generate_sync_io_error();
//CLASS_DECL_APEX void set_generate_sync_io_error(int iError);


//class CLASS_DECL_APEX sync_io_error
//{
//public:
//
//
//   int   m_iGenerateBefore;
//   int   m_iErrorBefore;
//   int * m_piError;
//
//
//   sync_io_error(int * piError = nullptr)
//   {
//      m_iGenerateBefore = get_generate_sync_io_error();
//      m_iErrorBefore = get_sync_io_error();
//      set_sync_io_error(0);
//      set_generate_sync_io_error(1);
//      m_piError = piError;
//   }
//
//   ~sync_io_error()
//   {
//      if (m_piError != nullptr)
//      {
//         *m_piError = get_sync_io_error();
//      }
//      set_generate_sync_io_error(m_iGenerateBefore);
//      set_sync_io_error(m_iErrorBefore);
//   }
//
//   bool none() const { return get_sync_io_error() == 0; }
//
//
//   operator bool() const { return get_sync_io_error() != 0; }
//
//};


namespace file
{

   
   class insert_item;
   class edit_file;

};






#define FIRST_VERSION 0


#ifdef WINDOWS

#define LINE_SEPARATOR "\r\n"

#elif defined(__APPLE__)

#define LINE_SEPARATOR "\r"

#else

#define LINE_SEPARATOR "\n"

#endif

#define STATIC_ASCII_STRING_LENGTH(x) (sizeof(x) - 1)






//CLASS_DECL_APEX bool file_save_stra(const char * lpszName, const string_array & stra);
//CLASS_DECL_APEX bool file_load_stra(const char * lpszName, string_array & stra, bool bAddEmpty = true);



class memory_base;


//CLASS_DECL_APEX bool file_put_contents_dup(const char * path, const memory_base & memory);
//CLASS_DECL_APEX int_bool file_put_contents_dup(const char * path, const char * contents);
//CLASS_DECL_APEX bool file_as_memory(memory_base & memory, const char * path, memsize iReadAtMostByteCount = -1);
//CLASS_DECL_APEX memsize file_as_memory(const char * path, void * p, memsize s);
//
//CLASS_DECL_APEX filesize fsize_dup(HANDLE h);



//template < typename N > class numeric_array;
//typedef CLASS_DECL_APEX numeric_array < u32 > u32_array;
//
//
//
//
//
//
//CLASS_DECL_APEX string file_title_dup(const char * path);
//CLASS_DECL_APEX string file_name_dup(const char * path);
//
//
//CLASS_DECL_APEX string file_get_mozilla_firefox_plugin_container_path();
//
//
//
//CLASS_DECL_APEX memory file_as_memory(const char * path, strsize iReadAtMostByteCount = -1);
//CLASS_DECL_APEX memsize file_as_memory(const char * path, void * p, memsize s);
//CLASS_DECL_APEX string file_as_string(const char * path, strsize iReadAtMostByteCount = -1);
//CLASS_DECL_APEX string file_line_dup(const char * path, index iLine);
//CLASS_DECL_APEX bool file_set_line_dup(const char * path, index iLine, const char * pszLine);
//CLASS_DECL_APEX string file_extension_dup(const char * path);
//CLASS_DECL_APEX string get_temp_file_name_dup(const char * lpszName,const char * pszExtension);
//CLASS_DECL_APEX string file_final_extension_dup(const char * path);
//CLASS_DECL_APEX string url_dir_name_for_relative(const char * pszPath);
//CLASS_DECL_APEX string solve_relative(const string & str, bool * pbUrl = nullptr);
//CLASS_DECL_APEX bool solve_relative_inline(string & str, bool & bUrl, bool & bOnlyNativeFileSep, strsize * iaSlash, int * piSlashCount); // returns true if original string had trailing slash
//CLASS_DECL_APEX string defer_solve_relative(const char * pszRelative,const char * pszCurrent);
//CLASS_DECL_APEX bool file_append_dup(const string & strFile, const string & str);
//CLASS_DECL_APEX bool file_append_dup(const string & strFile, const char * psz, strsize s);
//CLASS_DECL_APEX bool file_append_wait_dup(const string & strFile, const string & str, DWORD tickTimeout = INFINITE);
//CLASS_DECL_APEX bool file_append_wait_dup(const string & strFile, const char * psz, strsize s, DWORD tickTimeout = INFINITE);
//
//CLASS_DECL_APEX bool write_memory_to_file(FILE * file, const void * pdata, memsize nCount, memsize * puiWritten);
//
//
//template < class POD >
//inline bool file_put_pod(const char * path, const POD & pod)
//{
//
//   return file_put_contents_dup(path, &pod, sizeof(pod));
//
//}
//
//
//template < class POD >
//inline bool file_as_pod(POD & pod, const char * path)
//{
//
//   return file_as_memory(path, &pod, sizeof(pod)) == sizeof(pod);
//
//}


//#include "opened.h"

//#include "exception.h"

//#include "status.h"

//#include "md5.h"

//#include "stream.h"

//#include "opened.h"

//#include "dir.h"

//#include "composite.h"

//#include "serializable.h"

//#include "path.h"

//#include "buffer.h"

//#include "text_file.h"

//#include "memory_file.h"

//#include "string_file.h"

//#include "text_stream.h"













//#include "stdio_file.h"


//#include "file_stream.h"





//namespace file
//{
//
//   using pos_type = filesize;
//   using off_type = filesize;
//
//   using iostate = ::file::e_iostate;
//   using seekdir = ::file::e_seek;
//}




//#include "memory_file.h"


//#include "byte_stream_memory_file.h"





//#include "item_array.h"


//#include "html_file.h"


//#include "_papaya.h"



#include "html_file.h"


