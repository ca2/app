#pragma once


//#include "item.h"


#include "plain_text_file_options.h"


//#include "stdio_file.h"




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




namespace file
{

   
   class insert_item;
   class edit_file;
   class enumerator;


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



//template < typename N, enum_type m_etypeContainer >
//class numeric_array;








//CLASS_DECL_ACME string file_path_title(const char * path);
CLASS_DECL_ACME const char * file_path_name(const char * path);



CLASS_DECL_ACME ::file::path dir_ca2_module();

CLASS_DECL_ACME ::file::path dir_base_module();






#include "opened.h"

//#include "exception.h"

//#include "status.h"

//#include "stream.h"

//#include "opened.h"

#include "dir.h"

//#include "composite.h"

//#include "serializable.h"

//#include "path.h"

//#include "buffer.h"

//#include "text_file.h"

//#include "memory_file.h"

//#include "string_buffer.h"

//#include "text_stream.h"

//#include "payload_stream.h"













//#include "stdio_file.h"


//#include "file_stream.h"





namespace file
{


   using pos_type = filesize;
   using off_type = filesize;


   using iostate = ::file::e_iostate;
   using seekdir = ::enum_seek;


   class writable;
   class file;

}


//#include "memory_file.h"


#include "byte_stream_memory_file.h"





//#include "item_array.h"


//#include "html_file.h"


#include "_papaya.h"



namespace file
{

   //template < typename TRANSFER >
   CLASS_DECL_ACME bool output(::file::file* pfileOut, const ::function < bool (::file::file* pfileOut, ::file::file* pfileIn) > & function, ::file::file* pfileIn);
//   {
//
//      throw ::not_implemented();
//
//   }


} // namespace file





#include "listing_provider.h"


//#include "folder.h"



