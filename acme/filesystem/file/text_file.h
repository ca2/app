#pragma once


#include "file.h"


namespace file
{


   class CLASS_DECL_ACME text_file :
      virtual public ::file::file
   {
   public:


      text_file();
      ~text_file() override;


      virtual void write_string(const ::scoped_string & scopedstr);

      virtual bool read_string(string & str) override;
      virtual ::u32 read_full_string(string & str);

      inline text_file & operator << (const ::scoped_string & scopedstr)

      {
         write_string(scopedstr);

         return *this;
      }


   };


   typedef ::pointer<text_file>text_buffer_pointer;


} // namespace file




