#pragma once


#include "acme/filesystem/file/text_file.h"


#include <stdio.h>


class CLASS_DECL_ACME stdio_file:
   virtual public ::file::text_file
{
public:

   
   enum enum_flag
   {
      
      flag_none = 0,
      flag_no_exception_if_not_found = 1,
      flag_file_not_found = 2,

   };

   using e_flag = enumeration < enum_flag >;


   FILE *                        m_pfile;
   e_flag                        m_eflag;


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

   [[noreturn]] void throw_exception(const ::scoped_string & scopedstr);

};



CLASS_DECL_ACME ::pointer<stdio_file> stdio_open(::particle * pparticle, const ::file::path & path, const scoped_string & attrs, int iShare);