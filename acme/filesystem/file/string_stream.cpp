// From string_stream.h by camilo on 2023-07-05 22:02 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "string_buffer.h"
#include "string_stream.h"

//::pointer < string_buffer >   m_pstringbuffer;

string_stream::string_stream() :
   string_stream(__new(class string_buffer))
{


}


string_stream::string_stream(const ::pointer < string_buffer_base > & pstringbuffer)
{

   m_pstringbuffer = pstringbuffer;

}


string_stream::string_stream(string_stream && stream) :
   write_text_stream() 
{ 

   m_pstringbuffer = ::transfer(stream.m_pstringbuffer);

}


string_stream::~string_stream()
{

}


string_buffer * string_stream::string_buffer()
{

   return dynamic_cast < class string_buffer * > (m_pstringbuffer.m_p);

}


::string string_stream::as_string() const
{

   return ((string_stream *)this)->string_buffer()->m_strOwnStorage;

}

::string & string_stream::as_string() 
{
   return string_buffer()->m_strOwnStorage; 
}
