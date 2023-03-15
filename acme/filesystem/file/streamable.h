﻿// Created by camilo on 2021-08-01 22:40 Thomas Month!! <3ThomasBS__!!
#pragma once


#include "translatable.h"


namespace file
{


   class CLASS_DECL_ACME readable
   {
   public:


      virtual memsize read(const ::block & block);
      virtual ::file::file * get_file();


   };


   class CLASS_DECL_ACME writable
   {
   public:


      virtual void write(const ::block & block);


   };


   class CLASS_DECL_ACME streamable :
      virtual public translatable,
      virtual public readable,
      virtual public writable
   {
   public:


      virtual enum_status _open(const ::scoped_string & scopedstrFilePath, const ::file::enum_open & eopen);

      void translate(filesize offset, ::enum_seek eseek) override;

      virtual void flush();
      virtual void close();
      virtual void abort();


      virtual void set_size(filesize dwNewLen);

      virtual filesize size() const;


   };


} // namespace file


CLASS_DECL_ACME void __transfer_to_writable(::file::writable * pwritable, ::file::file * pfileIn, memsize uiBufSize = -1);



