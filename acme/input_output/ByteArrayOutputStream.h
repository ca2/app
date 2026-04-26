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


#include "acme/input_output/OutputStream.h"

//namespace subsystem
//{
   /**
    * Output stream to write data to memory.
    */
   class CLASS_DECL_ACME ByteArrayOutputStream : public OutputStream
   {
   public:
      static const memsize DEFAULT_INNER_BUFFER_CAPACITY = 1024;
   public:

      bool m_bOwnMemory;
      char *m_buffer;
      ::memory m_memory;
      memsize m_size;
      memsize m_max;


      /**
       * Creates new memory output stream with inner memory buffer.
       * @param max capacity of buffer (in bytes).
       */
      //ByteArrayOutputStream(memsize max);
      /**
       * Creates new memory output stream  with inner memory buffer with default capacity.
       */
      ByteArrayOutputStream();
      ByteArrayOutputStream(::particle * pparticle, memsize max);
      ByteArrayOutputStream(::particle * pparticle, void *alienMemory, memsize max);
      /**
       * Creates memory output stream for writting into alien (but
       * owned by ByteArrayOutputStream class) memory.
       * @fixme stub.
       */
      //ByteArrayOutputStream(void *alienMemory);

      ~ByteArrayOutputStream() override;


      virtual void _initialize_byte_array_output_stream(::particle * pparticle, memsize max = -1);

      virtual void _initialize_byte_array_output_stream(::particle * pparticle, void *alienMemory, memsize size);

      /**
       * Writes data to memory.
       * @param buffer source buffer.
       * @param len count to bytes to write.
       */
      virtual memsize defer_write(const void *buffer, memsize len);

      /**
       * Returns size of written data.
       */
      memsize size() const;

      /**
       * Returns written data.
       */
      const char *toByteArray() const;

   //protected:
   };
//}//namespace subsystem
