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
#include "DataInputStream.h"
//#include <vector>
////#include "remoting/remoting_common/util/::string.h"

#define SETBYTE(y, n) (((y) & 0xFF) << ((n) * 8))

namespace remoting
{
   DataInputStream::DataInputStream(InputStream* inputStream)
      : m_inputStream(inputStream)
   {
   }


   DataInputStream::~DataInputStream()
   {
   }


   size_t DataInputStream::available()
   {
      return m_inputStream->available();
   }


   size_t DataInputStream::read(void* buffer, size_t len)
   {
      return m_inputStream->read(buffer, len);
   }


   void DataInputStream::readFully(void* buffer, size_t len)
   {
      char* typedBuffer = (char *)buffer;
      size_t totalRead = 0;
      size_t left = len;
      while (totalRead < len)
      {
         size_t read = m_inputStream->read(typedBuffer + totalRead, left);
         left -= read;
         totalRead += read;
      }
   }


   unsigned char DataInputStream::readUInt8()
   {
      unsigned char x;
      readFully(&x, 1);
      return x;
   }


   unsigned short DataInputStream::readUInt16()
   {
      unsigned short x = 0;
      unsigned char buf[2];
      readFully(&buf[0], 2);
      x += SETBYTE(buf[0], 1);
      x += SETBYTE(buf[1], 0);
      return x;
   }


   unsigned int DataInputStream::readUInt32()
   {
      unsigned int x = 0;
      unsigned char buf[4];
      readFully(&buf[0], 4);
      x += SETBYTE(buf[0], 3);
      x += SETBYTE(buf[1], 2);
      x += SETBYTE(buf[2], 1);
      x += SETBYTE(buf[3], 0);
      return x;
   }


   unsigned long long DataInputStream::readUInt64()
   {
      unsigned long long x = 0;
      unsigned char buf[8];
      readFully(&buf[0], 8);
      x += (unsigned long long)buf[0] << (7 * 8);
      x += (unsigned long long)buf[1] << (6 * 8);
      x += (unsigned long long)buf[2] << (5 * 8);
      x += (unsigned long long)buf[3] << (4 * 8);
      x += (unsigned long long)buf[4] << (3 * 8);
      x += (unsigned long long)buf[5] << (2 * 8);
      x += (unsigned long long)buf[6] << (1 * 8);
      x += (unsigned long long)buf[7] << (0 * 8);
      return x;
   }


   char DataInputStream::readInt8()
   {
      char x;
      readFully(&x, 1);
      return x;
   }


   short DataInputStream::readInt16()
   {
      return (short)readUInt16();
   }


   int DataInputStream::readInt32()
   {
      return (int)readUInt32();
   }


   long long DataInputStream::readInt64()
   {
      return (long long)readUInt64();
   }


   ::string DataInputStream::read_utf8_string()
   {
      //::string strStorage;
      unsigned int sizeInBytes = readUInt32();
      if (sizeInBytes <= 0)
      {
         return {};
      }
      ::memory buffer;

      buffer.set_size(sizeInBytes);

      readFully(buffer.data(), sizeInBytes);
      ::string utf8String((const char *) buffer.data(), buffer.size());
      return utf8String;

   }
} // namespace remoting
