// Created by camilo on 2021-08-01 22:40 Thomas Month!! <3ThomasBS__!!
#pragma once


#include "translatable.h"


namespace file
{


   class CLASS_DECL_ACME readable
   {
   public:


      virtual ~readable() {}

      virtual memsize read(void * p, ::memsize s);

      inline memsize read(const ::block & block) { return read(block.data(), block.size()); }

      virtual ::file::file * get_file();


   };


   class CLASS_DECL_ACME writable
   {
   public:


      virtual ~writable() {}


      virtual void write(const void * p, ::memsize s);

      inline void write(const ::block & block) { write(block.data(), block.size()); }

      template < typename ITERATOR_TYPE2, int t_size >
      inline void write(const ::const_string_range_static_array < ITERATOR_TYPE2, t_size > & a) 
      {
         for (int i = 0; i < t_size; i++)
         {
            write(a.element_at(i).begin(), a.element_at(i).size());
         }
      }
      
      virtual ::memsize defer_write(const void * p, ::memsize s);

      inline ::memsize defer_write(const ::block & block) { return defer_write(block.data(), block.size()); }

   };


   class CLASS_DECL_ACME streamable :
      virtual public translatable,
      virtual public readable,
      virtual public writable
   {
   public:



      streamable() {}
      streamable(streamable &&) = delete;


      virtual enum_status _open(const ::scoped_string & scopedstrFilePath, const ::file::enum_open & eopen);

      void translate(filesize offset, ::enum_seek eseek) override;

      virtual void flush();
      virtual void close();
      virtual void abort();


      virtual void set_size(filesize dwNewLen);

      virtual filesize size() const;
      virtual filesize right_size() const;


      virtual ::memory right_memory(::memsize iReadAtMostByteCount = -1);
      virtual void right_memory(memory_base & memory, ::memsize iReadAtMostByteCount = -1);
      virtual ::string right_string(::memsize iReadAtMostByteCount = -1);
      virtual void right_string(::string & str, ::memsize iReadAtMostByteCount = -1);

      virtual string full_string(::memsize iReadAtMostByteCount = -1);

      virtual void full_memory(memory_base & memory, ::memsize iReadAtMostByteCount = -1);
      virtual ::memory full_memory(::memsize iReadAtMostByteCount = -1);




      // virtual ::memory left_memory(::memsize iReadAtMostByteCount = -1);


   };


} // namespace file


CLASS_DECL_ACME void __transfer_to_writable(::file::writable * pwritable, ::file::file * pfileIn, memsize uiBufSize = -1);



