// Created by camilo on 2022-11-09 10:16 <3ThomasBorregaardSorensen!!
#pragma once


inline write_text_stream & operator << (write_text_stream & textstream, const ::atom& atom)
{

   textstream << atom.as_string();

   return textstream;

}



inline write_text_stream  & operator <<(write_text_stream & textstream, integral_byte integralbyte)
{

   textstream.print_string_copy(integralbyte);

   if (textstream.fmtflags() & ::file::separated)
   {

      textstream.print(textstream.m_chSeparator);

   }

   return textstream;

}



