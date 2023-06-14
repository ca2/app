// From text_stream.h by camilo on 2023-06-11 04:11 <3ThomasBorregaardSorensen!!
#pragma once


#include "write_text_stream.h"
#include "string_buffer.h"


class string_stream :
   public write_text_stream < string_buffer >
{
public:


   string_buffer   m_stringbuffer;


   string_stream() : write_text_stream(&m_stringbuffer) { }
   string_stream(string_stream && stream) : m_stringbuffer(::transfer(stream.m_stringbuffer)), write_text_stream(&m_stringbuffer, ::transfer(stream)) { }
   ~string_stream() {}

   ::string as_string() const { return m_stringbuffer.m_strOwnStorage; }
   ::string & as_string() { return m_stringbuffer.m_strOwnStorage; }


};
