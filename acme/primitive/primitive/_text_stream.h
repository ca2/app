// Created by camilo on 2022-11-09 10:16 <3ThomasBorregaardSorensen!!
#pragma once


template < typename FILE >
write_text_stream < FILE >& operator << (write_text_stream < FILE > & textstream, const ::atom& atom)
{

   textstream << atom.as_string();

   return textstream;

}


template < typename FILE >
write_text_stream < FILE > & operator <<(write_text_stream < FILE > & textstream, integral_byte integralbyte)
{

   textstream.print_string_copy(integralbyte);

   if (textstream.fmtflags() & ::file::separated)
   {

      textstream.print(textstream.m_chSeparator);

   }

   return textstream;

}



