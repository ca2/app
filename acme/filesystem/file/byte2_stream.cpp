//
// Created by camilo on 2025-08-31 17:14 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "byte2_stream.h"
#include "acme/filesystem/file/memory_file.h"


byte2_stream::byte2_stream() :
m_pfile(::system()->create_memory_file())
{


}


byte2_stream::byte2_stream(const ::block & block) :
m_pfile(::system()->create_memory_file(block))
{



}


byte2_stream::byte2_stream(const ::file_pointer & pfile) :
m_pfile(pfile)
{


}

byte2_stream::~byte2_stream()
{



}


byte2_stream & byte2_stream::operator >>(int & i)
{

   auto iByte = m_pfile->get_unsigned_char();

   if(iByte < 0)
   {

      throw ::exception(error_io, "bytes2_stream read int exception");

   }

   i = iByte;

   iByte = m_pfile->get_unsigned_char();

   if(iByte < 0)
   {

      throw ::exception(error_io, "bytes2_stream read int exception (b)");

   }

   i |= (iByte << 8);

   iByte = m_pfile->get_unsigned_char();

   if(iByte < 0)
   {

      throw ::exception(error_io, "bytes2_stream read int exception (b)");

   }

   i |= (iByte << 16);

   iByte = m_pfile->get_unsigned_char();

   if(iByte < 0)
   {

      throw ::exception(error_io, "bytes2_stream read int exception (b)");

   }

   i |= (iByte << 24);

   return *this;

}


byte2_stream & byte2_stream::operator <<(int i)
{

   unsigned char uch = i&0xff;

   m_pfile->write(&uch, 1);

   uch = (i >> 8) & 0xff;

   m_pfile->write(&uch, 1);

   uch = (i >> 16) & 0xff;

   m_pfile->write(&uch, 1);

   uch = (i >> 24) & 0xff;

   m_pfile->write(&uch, 1);

   return *this;

}




   input_byte2_stream:: input_byte2_stream(const ::block & block) :
   byte2_stream(block)
   {
      m_estream = ::file::e_stream_input;
   }

   input_byte2_stream::~input_byte2_stream()
{


}



   output_byte2_stream::output_byte2_stream():
   byte2_stream()
   {

      m_estream = ::file::e_stream_output;
   }
output_byte2_stream::~output_byte2_stream()
{

}


