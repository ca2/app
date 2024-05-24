#pragma once


#include "acid/filesystem/file/text_file.h"


#include <stdio.h>


class CLASS_DECL_ACID stdio_file:
   virtual public ::file::text_file
{
public:

   
//   enum enum_flag
//   {
//
//      e_flag_none = 0,
//      e_flag_no_exception_if_not_found = 1,
//      e_flag_file_not_found = 2,
//
//   };

   //using e_flag = enumeration < enum_flag >;


   FILE *                        m_pfile;
   //e_flag                        m_eflag;


   stdio_file();
   explicit stdio_file(FILE * pfile);
   ~stdio_file() override;


   filesize get_position() const override;
   ::file::file_status get_status() const override;
   ::file::path get_file_path() const override;


   void open(const ::file::path & path, ::file::e_open eopen, ::pointer < ::file::exception > * pfileexception = nullptr) override;
   virtual void open(const ::file::path & path, const ::string & strAttributes, int iShare);

   
   void translate(filesize offset, ::enum_seek eseek) override;
   void set_size(filesize dwNewLen) override;
   filesize size() const override;


   void lock(filesize dwPos,filesize dwCount) override;
   void unlock(filesize dwPos,filesize dwCount) override;

   void flush() override;
   void close() override;


   using ::file::text_file::read;
   memsize read(void * p, ::memsize s) override;


   int get_u8() override;
   int peek_byte() override;
   void put_byte_back(::u8 b) override;

   using ::file::file::write;
   void write(const void * p, ::memsize s) override;

   string get_location() const override;

   bool is_opened() const override;

   class c_error_number c_error_number() const;

   [[noreturn]] void throw_exception(const ::scoped_string & scopedstr);

};



CLASS_DECL_ACID ::pointer<stdio_file> stdio_open(::particle * pparticle, const ::file::path & path, const scoped_string & attrs, int iShare);


::e_status fgets_string(string & str, FILE * pfile, memsize iBufferSize = 1024);


CLASS_DECL_ACID void __cdecl __clearerr_s(FILE * stream);


#include "acid/primitive/primitive/holder.h"


CLASS_DECL_ACID void destroy_pointer(FILE * p);


using FILE_holder = holder < FILE * >;
