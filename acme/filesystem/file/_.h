#pragma once




#include "item.h"

CLASS_DECL_ACME int get_sync_io_error();
CLASS_DECL_ACME void set_sync_io_error(int iError);
CLASS_DECL_ACME int get_generate_sync_io_error();
CLASS_DECL_ACME void set_generate_sync_io_error(int iError);


/////////////////////////////////////////////////////
//
//    md5 implementation
//    intentional duplication because spa
//    needs md5
//
CLASS_DECL_ACME string file_md5_dup(const char* psz);
//
//
/////////////////////////////////////////////////////

class CLASS_DECL_ACME sync_io_error
{
public:


   int   m_iGenerateBefore;
   int   m_iErrorBefore;
   int * m_piError;


   sync_io_error(int * piError = nullptr)
   {
      m_iGenerateBefore = get_generate_sync_io_error();
      m_iErrorBefore = get_sync_io_error();
      set_sync_io_error(0);
      set_generate_sync_io_error(1);
      m_piError = piError;
   }

   ~sync_io_error()
   {
      if (m_piError != nullptr)
      {
         *m_piError = get_sync_io_error();
      }
      set_generate_sync_io_error(m_iGenerateBefore);
      set_sync_io_error(m_iErrorBefore);
   }

   bool none() const { return get_sync_io_error() == 0; }


   operator bool() const { return get_sync_io_error() != 0; }

};


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






CLASS_DECL_ACME bool file_save_stra(const char * lpszName, const string_array & stra);
CLASS_DECL_ACME bool file_load_stra(const char * lpszName, string_array & stra, bool bAddEmpty = true);



class memory_base;


CLASS_DECL_ACME bool file_put_contents_dup(const char * path, const memory_base & memory);
CLASS_DECL_ACME int_bool file_put_contents_dup(const char * path, const char * contents);
CLASS_DECL_ACME bool file_as_memory(memory_base & memory, const char * path, memsize iReadAtMostByteCount = -1);
CLASS_DECL_ACME memsize file_as_memory(const char * path, void * p, memsize s);

CLASS_DECL_ACME filesize fsize_dup(HANDLE h);



template < typename N > class numeric_array;
typedef CLASS_DECL_ACME numeric_array < u32 > u32_array;






CLASS_DECL_ACME string file_title_dup(const char * path);
CLASS_DECL_ACME string file_name_dup(const char * path);


CLASS_DECL_ACME string file_get_mozilla_firefox_plugin_container_path();



CLASS_DECL_ACME memory file_as_memory(const char * path, strsize iReadAtMostByteCount = -1);
CLASS_DECL_ACME memsize file_as_memory(const char * path, void * p, memsize s);
CLASS_DECL_ACME string file_as_string(const char * path, strsize iReadAtMostByteCount = -1);
CLASS_DECL_ACME string file_line_dup(const char * path, index iLine);
CLASS_DECL_ACME bool file_set_line_dup(const char * path, index iLine, const char * pszLine);
CLASS_DECL_ACME string file_extension_dup(const char * path);
CLASS_DECL_ACME string get_temp_file_name_dup(const char * lpszName,const char * pszExtension);
CLASS_DECL_ACME string file_final_extension_dup(const char * path);
CLASS_DECL_ACME string url_dir_name_for_relative(const char * pszPath);
CLASS_DECL_ACME string solve_relative(const string & str, bool * pbUrl = nullptr);
CLASS_DECL_ACME bool solve_relative_inline(string & str, bool & bUrl, bool & bOnlyNativeFileSep, strsize * iaSlash, int * piSlashCount); // returns true if original string had trailing slash
CLASS_DECL_ACME string defer_solve_relative(const char * pszRelative,const char * pszCurrent);
CLASS_DECL_ACME bool file_append_dup(const string & strFile, const string & str);
CLASS_DECL_ACME bool file_append_dup(const string & strFile, const char * psz, strsize s);
CLASS_DECL_ACME bool file_append_wait_dup(const string & strFile, const string & str, DWORD tickTimeout = INFINITE);
CLASS_DECL_ACME bool file_append_wait_dup(const string & strFile, const char * psz, strsize s, DWORD tickTimeout = INFINITE);

CLASS_DECL_ACME bool write_memory_to_file(FILE * file, const void * pdata, memsize nCount, memsize * puiWritten);


template < class POD >
inline bool file_put_pod(const char * path, const POD & pod)
{

   return file_put_contents_dup(path, &pod, sizeof(pod));

}


template < class POD >
inline bool file_as_pod(POD & pod, const char * path)
{

   return file_as_memory(path, &pod, sizeof(pod)) == sizeof(pod);

}


#include "opened.h"

#include "exception.h"

#include "status.h"

#include "stream.h"

#include "opened.h"

#include "dir.h"

#include "composite.h"

#include "serializable.h"

#include "path.h"

#include "buffer.h"

#include "text_file.h"

#include "memory_file.h"

#include "string_file.h"

//#include "text_stream.h"













#include "stdio_file.h"


//#include "file_stream.h"





namespace file
{

   using pos_type = filesize;
   using off_type = filesize;

   using iostate = ::file::e_iostate;
   using seekdir = ::file::e_seek;
}




#include "memory_file.h"


#include "byte_stream_memory_file.h"





#include "item_array.h"


//#include "html_file.h"


#include "_papaya.h"



namespace file
{

   template < typename TRANSFER >
   bool output(::file::file* pfileOut, TRANSFER* ptransfer, bool (TRANSFER::* pfn)(::file::file* pfileOut, ::file::file* pfileIn), ::file::file* pfileIn)
   {

      __throw(not_implemented);

   }

}



