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

#pragma once


#include "acme/subsystem/io/OutputStream.h"

namespace remoting
{
   /**
    * Output stream to write data to memory.
    */
   class CLASS_DECL_REMOTING_COMMON ByteArrayOutputStream : public OutputStream
   {
   public:
      static const size_t DEFAULT_INNER_BUFFER_CAPACITY = 1024;
   public:
      /**
       * Creates new memory output stream with inner memory buffer.
       * @param max capacity of buffer (in bytes).
       */
      ByteArrayOutputStream(size_t max);
      /**
       * Creates new memory output stream  with inner memory buffer with default capacity.
       */
      ByteArrayOutputStream();
      /**
       * Creates memory output stream for writting into alien (but
       * owned by ByteArrayOutputStream class) memory.
       * @fixme stub.
       */
      ByteArrayOutputStream(void *alienMemory);

      virtual ~ByteArrayOutputStream();

      /**
       * Writes data to memory.
       * @param buffer source buffer.
       * @param len count to bytes to write.
       */
      virtual memsize defer_write(const void *buffer, memsize len);

      /**
       * Returns size of written data.
       */
      size_t size() const;

      /**
       * Returns written data.
       */
      const char *toByteArray() const;

   protected:
      bool m_ownMemory;
      char *m_buffer;
      size_t m_size;
      size_t m_max;
   };
}//namespace remoting
