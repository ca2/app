// Created by camilo on 2023-06-29 09:00 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "_text_stream.h"


// template < typename FILE >
write_text_stream < FILE > & operator << (write_text_stream < FILE > & textstream, integral_byte integralbyte)
{

   textstream.print_string_copy(integralbyte);

   if (textstream.fmtflags() & ::file::separated)
   {

      print(textstream.m_chSeparator);

   }

   return textstream;

}
