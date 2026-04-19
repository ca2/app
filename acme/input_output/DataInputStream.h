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


//#include "remoting/remoting_common/util/inttypes.h"
#include "acme/input_output/InputStream.h"
#include "acme/exception/io.h"
//namespace subsystem
//{
   /**
    * Data input stream class (decorator pattern).
    * Allows to read typed data from input stream.
    */
   class CLASS_DECL_ACME DataInputStream : public InputStream
   {
   public:
      /**
       * Creates new DataInputStream.
       * @param inputStream input stream that will be used to read data.
       */
      DataInputStream(InputStream *inputStream);
      virtual ~DataInputStream();

      /**
       * Inherited from superclass.
       * Delegates execution of method to real input stream.
       */
      virtual memsize read(void *buffer, memsize len);

      virtual memsize available();

      /**
       * Reads exactly specified count of bytes from input stream.
       * @param buffer [out] target buffer to receive data.
       * @param len count of bytes to read.
       * @throws ::io_exception on error.
       * @fixme really it can throw any kind of exception.
       */
      void readFully(void *buffer, memsize len);

      unsigned char readUInt8();
      unsigned short readUInt16();
      unsigned int readUInt32();
      unsigned long long readUInt64();

      char readInt8();
      short readInt16();
      int readInt32();
      long long readInt64();

      ::string readUtf8();

   protected:
      InputStream *m_inputStream;
   };
//} // namespace subsystem
