// Copyright (C) 2009,2010,2011,2012 GlavSoft LLC.
// All rights reserved.
//
//-------------------------------------------------------------------------
// This file is part of the TightVNC software.  Please visit our Web site:
//
//                       http://www.tightvnc.com/
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along
// with this program; if not, w_rite to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
//-------------------------------------------------------------------------
//
#include "framework.h"
#include "ByteArrayInputStream.h"
#include "acme/exception/io.h"
// #include aaa_<algorithm>

//namespace subsystem
//{
   //ByteArrayInputStream::ByteArrayInputStream(const char *buffer, memsize bufferSize)
   // : m_buffer(buffer), m_bufferSize(bufferSize), m_left(bufferSize)
   // {
   // }


ByteArrayInputStream::ByteArrayInputStream()
: m_buffer(nullptr), m_bufferSize(0), m_left(0)
   {
   }
ByteArrayInputStream::ByteArrayInputStream(::particle * pparticle, const ::block & block)
: ByteArrayInputStream()
{
   _initialize_byte_array_input_stream(pparticle, block);
}
   ByteArrayInputStream::~ByteArrayInputStream()
   {
   }

   void ByteArrayInputStream::_initialize_byte_array_input_stream(::particle * pparticle, const ::block & block)
{

   _initialize_byte_array_input_stream(pparticle, block.data(), block.size());

}

   void ByteArrayInputStream::_initialize_byte_array_input_stream(::particle * pparticle, const void *buffer, memsize bufferSize)
   {
initialize(pparticle);
      m_buffer = (const char *) buffer;
      m_bufferSize = bufferSize;
      m_left = bufferSize;

   }


   memsize ByteArrayInputStream::read(void *buffer, memsize len)
   {
      if (m_left == 0) {
         throw ::io_exception(error_io, "End of stream reached");
      }

      if (len < 0) {
         throw ::io_exception(error_io, "Negative data length value");
      }

      char *out = (char *)buffer;
      char *in = (char *)m_buffer;

      memsize bytesToCopy = ::minimum(m_left, len);
      memsize outOffset = 0;
      memsize inOffset = m_bufferSize - m_left;

      memcpy(out + outOffset, in + inOffset, bytesToCopy);

      m_left -= bytesToCopy;

      return bytesToCopy;
   }

   memsize ByteArrayInputStream::available() {
      return m_left;
   }
//}//namespace subsystem
