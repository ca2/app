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
#include "DataOutputStream.h"
//////#include "remoting/remoting_common/util/::string.h"
////#include "remoting/remoting_common/util/::string.h"
//#include <vector>

#define GETBYTE(x, n) (((x) >> ((n) * 8)) & 0xFF)

namespace remoting
{
   DataOutputStream::DataOutputStream(::file::writable * pwritable)
   : m_outStream(pwritable)
   {
   }

   DataOutputStream::~DataOutputStream()
   {
   }

   memsize DataOutputStream::defer_write(const void *buffer, memsize len)
   {
      return m_outStream->defer_write(buffer, len);
   }

   void DataOutputStream::write(const void *buffer, memsize len)
   {
      char *typedBuffer = (char *)buffer;
      size_t totalWritten = 0;
      size_t left = len;
      while (totalWritten < len) {
         size_t written = m_outStream->defer_write(typedBuffer + totalWritten, left);
         left -= written;
         totalWritten += written;
      }
   }

   void DataOutputStream::writeUInt8(unsigned char x)
   {
      write((char *)&x, 1);
   };

   void DataOutputStream::writeUInt16(unsigned short data)
   {
      unsigned char buf[2];

      buf[0] = GETBYTE(data, 1);
      buf[1] = GETBYTE(data, 0);

      write((char *)buf, sizeof(buf));
   }

   void DataOutputStream::writeUInt32(unsigned int data)
   {
      unsigned char buf[4];

      buf[0] = GETBYTE(data, 3);
      buf[1] = GETBYTE(data, 2);
      buf[2] = GETBYTE(data, 1);
      buf[3] = GETBYTE(data, 0);

      write((char *)buf, sizeof(buf));
   }

   void DataOutputStream::writeUInt64(unsigned long long data)
   {
      unsigned char buf[8];

      buf[0] = GETBYTE(data, 7);
      buf[1] = GETBYTE(data, 6);
      buf[2] = GETBYTE(data, 5);
      buf[3] = GETBYTE(data, 4);
      buf[4] = GETBYTE(data, 3);
      buf[5] = GETBYTE(data, 2);
      buf[6] = GETBYTE(data, 1);
      buf[7] = GETBYTE(data, 0);

      write((char *)buf, sizeof(buf));
   }

   void DataOutputStream::writeInt8(char x)
   {
      writeUInt8((unsigned char)x);
   }

   void DataOutputStream::writeInt16(short x)
   {
      writeUInt16((unsigned short)x);
   }

   void DataOutputStream::writeInt32(int x)
   {
      writeUInt32((unsigned int)x);
   }

   void DataOutputStream::writeInt64(long long x)
   {
      writeUInt64((unsigned long long)x);
   }

   void DataOutputStream::writeUTF8(const scoped_ansi_string &str)
   {
      //size_t sizeInBytes = 0;

      // to UTF8 string convertion
      //Utf8StringStorage utf8String(&StringStorage(string));

      // FIXME: Why try/catch() is used?
      try {
         unsigned int sizeInBytes = (unsigned int)str.size();
         //_ASSERT(sizeInBytes == str.size());
         writeUInt32(sizeInBytes);
         write(str.data(), sizeInBytes);
      } catch (...) {
         throw;
      }
   }

   void DataOutputStream::flush()
   {
      m_outStream->flush();
   }
} // namespace remoting
