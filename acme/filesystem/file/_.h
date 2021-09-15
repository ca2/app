#pragma once


#include "item.h"


#include "stdio_file.h"


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








class memory_base;

// CLASS_DECL_ACME bool xxxfile_save_stra(const char * lpszName, const string_array & stra);
// CLASS_DECL_ACME bool xxxfile_load_stra(const char * lpszName, string_array & stra, bool bAddEmpty = true);


// CLASS_DECL_ACME bool xxxfile_put_contents(const char * path, const memory_base & memory);
// CLASS_DECL_ACME int_bool xxxfile_put_contents(const char * path, const char * contents);
// CLASS_DECL_ACME bool xxxfile_as_memory(memory_base & memory, const char * path, memsize iReadAtMostByteCount = -1);
// CLASS_DECL_ACME memsize xxxfile_as_memory(const char * path, void * p, memsize s);



template < typename N, enum_type t_etypePayload >
class numeric_array;

typedef CLASS_DECL_ACME numeric_array < u32 > u32_array;






//CLASS_DECL_ACME string file_path_title(const char * path);
//CLASS_DECL_ACME string file_path_name(const char * path);



CLASS_DECL_ACME ::file::path dir_ca2_module();

CLASS_DECL_ACME ::file::path dir_base_module();






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

#include "text_stream.h"

#include "var_stream.h"













//#include "stdio_file.h"


//#include "file_stream.h"





namespace file
{


   using pos_type = filesize;
   using off_type = filesize;


   using iostate = ::file::e_iostate;
   using seekdir = ::enum_seek;


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

      throw ::exception::exception(error_not_implemented);

   }


}



