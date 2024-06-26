// From text_stream.h by camilo on 2023-06-11 04:11 <3ThomasBorregaardSorensen!!
#pragma once


#include "write_text_stream.h"
//#include "string_buffer.h"

class string_buffer_base;


class CLASS_DECL_ACME string_stream :
   virtual public write_text_stream
   //public write_text_stream < string_buffer >
{
public:


   //::pointer < string_buffer >   m_pstringbuffer;


   string_stream();
   string_stream(const ::file_pointer & pfile);
   string_stream(::file_pointer && pfile);
   string_stream(string_stream && stream);
   ~string_stream() override;

   virtual class string_buffer * string_buffer();

   virtual ::string as_string() const;
   virtual ::string & string_reference();


};
