// Copyright (C) 2009,2010,2011,2012 GlavSoft LLC.
// All rights reserved.
//
//-------------------------------------------------------------------------
// This file is part of the T i g h t V N C software.  Please visit our Web site:
//
//                       http://www.t i g h t v n c.com/
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
// with this program; if not, write to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
//-------------------------------------------------------------------------
//
#include "framework.h"
#include "Inflater.h"
//// #include aaa_<crtdbg.h>


namespace subsystem
{
   Inflater::Inflater()
   : m_unpackedSize(0)
   {
      m_zlibStream.zalloc = Z_NULL;
      m_zlibStream.zfree = Z_NULL;

      inflateInit(&m_zlibStream);

      m_zlibStream.next_in = 0;
      m_zlibStream.avail_in = 0;

      m_zlibStream.next_out = 0;
      m_zlibStream.avail_out = 0;
   }

   Inflater::~Inflater()
   {
      inflateEnd(&m_zlibStream);
   }

   void Inflater::setUnpackedSize(memsize size)
   {
      m_unpackedSize = size;
   }

   void Inflater::inflate()
   {
      //memsize avaliableOutput = m_unpackedSize + m_unpackedSize / 100 + 1024;
      memsize avaliableOutput = m_unpackedSize;
      unsigned long prevTotalOut = m_zlibStream.total_out;

      // Check to overflow.
      ::u32 constrainedValue = (::u32)avaliableOutput;
      ASSERT(avaliableOutput == constrainedValue);
      constrainedValue = (::u32)m_inputSize;
      ASSERT(m_inputSize == constrainedValue);

      m_output.set_size(avaliableOutput);

      m_zlibStream.next_in = (Bytef *)m_input;
      m_zlibStream.avail_in = (::u32)m_inputSize;

      m_zlibStream.next_out = (Bytef *)m_output.data();
      m_zlibStream.avail_out = (::u32)avaliableOutput;

      int r = ::inflate(&m_zlibStream, Z_SYNC_FLUSH);
      informationf(
          "inflate total_out=%lu avail_out=%u ret=%d",
                  m_zlibStream.total_out,
                  m_zlibStream.avail_out,
          r);
      if (r == Z_STREAM_END) {
         throw ZLibException(("ZLib stream end"));
      }
      if (r == Z_NEED_DICT) {
         throw ZLibException(("ZLib need dictionary"));
      }
      if (r == Z_STREAM_ERROR) {
         throw ZLibException(("ZLib stream error"));
      }
      if (r == Z_MEM_ERROR) {
         throw ZLibException(("ZLib memory error"));
      }
      if (r == Z_DATA_ERROR) {
         throw ZLibException(("Zlib data error"));
      }
      if (m_zlibStream.avail_in != 0) {
         throw ZLibException(("Not enough buffer size for data decompression"));
      }

      //m_outputSize = m_zlibStream.total_out - prevTotalOut;
      
      m_outputSize =
          avaliableOutput -
          m_zlibStream.avail_out;
   }
}// namespace subsystem
