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


byte2_stream & byte2_stream::operator >>(bool & b)
{

   auto iByte = m_pfile->get_unsigned_char();

   if (iByte < 0) {

      throw ::exception(error_io, "bytes2_stream read bool exception");

   }

   b = iByte ? true : false;

   return *this;

}


byte2_stream & byte2_stream::operator <<(bool b)
{

   unsigned char uch = b ? 0xff : 0;

   m_pfile->write(&uch, 1);

   return *this;

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

byte2_stream & byte2_stream::operator >>(long long & ll)
{

   long long iByte = m_pfile->get_unsigned_char();

   if(iByte < 0)
   {

      throw ::exception(error_io, "bytes2_stream read long long exception");

   }

   ll = iByte;

   iByte = m_pfile->get_unsigned_char();

   if(iByte < 0)
   {

      throw ::exception(error_io, "bytes2_stream read long long exception (b)");

   }

   ll |= (iByte << 8);

   iByte = m_pfile->get_unsigned_char();

   if(iByte < 0)
   {

      throw ::exception(error_io, "bytes2_stream read long long exception (c)");

   }

   ll |= (iByte << 16);

   iByte = m_pfile->get_unsigned_char();

   if(iByte < 0)
   {

      throw ::exception(error_io, "bytes2_stream read int exception (b)");

   }

   ll |= (iByte << 24);

   iByte = m_pfile->get_unsigned_char();

   if(iByte < 0)
   {

      throw ::exception(error_io, "bytes2_stream read int exception (b)");

   }

   ll |= (iByte << 32);

   iByte = m_pfile->get_unsigned_char();

   if(iByte < 0)
   {

      throw ::exception(error_io, "bytes2_stream read int exception (b)");

   }

   ll |= (iByte << 40);

   iByte = m_pfile->get_unsigned_char();

   if(iByte < 0)
   {

      throw ::exception(error_io, "bytes2_stream read int exception (b)");

   }

   ll |= (iByte << 48);

   iByte = m_pfile->get_unsigned_char();

   if(iByte < 0)
   {

      throw ::exception(error_io, "bytes2_stream read int exception (b)");

   }

   ll |= (iByte << 56);




   return *this;

}


byte2_stream & byte2_stream::operator <<(long long ll)
{

   unsigned char uch = ll&0xff;

   m_pfile->write(&uch, 1); // byte 0

   uch = (ll >> 8) & 0xff;

   m_pfile->write(&uch, 1);// byte 1

   uch = (ll >> 16) & 0xff;

   m_pfile->write(&uch, 1);// byte 2

   uch = (ll >> 24) & 0xff;

   m_pfile->write(&uch, 1);// byte 3

   uch = (ll >> 32) & 0xff;

   m_pfile->write(&uch, 1);// byte 4

   uch = (ll >> 40) & 0xff;

   m_pfile->write(&uch, 1);// byte 5

   uch = (ll >> 48) & 0xff;

   m_pfile->write(&uch, 1);// byte 6

   uch = (ll >> 56) & 0xff;

   m_pfile->write(&uch, 1);// byte 7

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
output_byte2_stream::output_byte2_stream(const ::block & block):
   byte2_stream(block)
{

   m_estream = ::file::e_stream_output;
}
output_byte2_stream::~output_byte2_stream()
{

}


byte2_stream & byte2_stream::operator >>(::string & str)
{

   int len;

   *this >> len;

   auto psz = str.get_buffer(len);

   auto read = m_pfile->read(psz, len);

   if(read < len)
   {

      throw ::exception(error_io);

   }

   str.release_buffer(len);

   return *this;

}


byte2_stream & byte2_stream::operator <<(::string & str)
{

   int len = (int)str.length();

   *this << len;

   m_pfile->write(str.data(), len);

   return *this;

}




byte2_stream & byte2_stream::operator >>(::memory & memory)
{

   long long ll;

   *this >> ll;

   memory.set_size(ll);

   auto read = m_pfile->read(memory.data(), ll);

   if(read < ll)
   {

      throw ::exception(error_io);

   }

   return *this;

}


byte2_stream & byte2_stream::operator <<(::memory & memory)
{

   auto ll = (long long)memory.size();

   *this << ll;

   m_pfile->write(memory);

   return *this;

}



