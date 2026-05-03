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
#include "BufferedOutputStream.h"

//namespace subsystem
//{
   // BufferedOutputStream::BufferedOutputStream(OutputStream *output)
   // : m_dataLength(0)
   // {
   //    m_output = new DataOutputStream(output);
   // }

 BufferedOutputStream::BufferedOutputStream()
 : m_dataLength(0)
 {
    //m_output = new DataOutputStream(output);
 }

BufferedOutputStream::BufferedOutputStream(OutputStream *poutputstream, memsize iBufferSize)
: BufferedOutputStream()
 {
    _initialize_buffered_output_stream(poutputstream, iBufferSize);
    //m_output = new DataOutputStream(output);
 }
   BufferedOutputStream::~BufferedOutputStream()
   {
      try {
         flush();
      } catch (...) {
      } // try / catch.

      //delete m_output;
   }


void BufferedOutputStream::_initialize_buffered_output_stream(OutputStream *poutputstream, memsize iBufferSize)

{
    initialize(poutputstream);
      m_dataLength = 0;

    if (iBufferSize <= 0)
    {
       iBufferSize = 100000;

    }
    m_memoryBuffer.set_size(iBufferSize);

    raw_construct_newø(m_pdataoutputstream, poutputstream);

    //m_pdataoutputstream->initialize_data_output_stream(poutputstream);

}

   memsize BufferedOutputStream::defer_write(const void *buffer, memsize len)
   {
      if (m_dataLength + len >= m_memoryBuffer.size()) {
         flush();

         m_pdataoutputstream->write(buffer, len);
      } else {
         memcpy(&m_memoryBuffer.data()[m_dataLength], buffer, len);

         m_dataLength += len;
      }

      return len;
   }


   void BufferedOutputStream::flush()
   {
      m_pdataoutputstream->write(&m_memoryBuffer.data()[0], m_dataLength);

      m_dataLength = 0;
   }
//}//namespace subsystem
