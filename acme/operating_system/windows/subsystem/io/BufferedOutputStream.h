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
#include "acme/subsystem/io/DataOutputStream.h"

namespace remoting
{


/**
 * Buffered output stream class (decorator pattern).
 * Adds bufferization feature to output stream.
 * @remark size of buffer now is fixed and equals to 1400 bytes.
 */
class CLASS_DECL_REMOTING_COMMON BufferedOutputStream : public OutputStream
{
public:
  /**
   * Creates new buffered output stream.
   * @param output real output stream.
   */
  BufferedOutputStream(OutputStream *output);
  virtual ~BufferedOutputStream();

  /**
   * Writes data to output stream (with buffering).
   * @remark method can write data to inner buffer, not to real output stream.
   * data will be written to real output stream it inner buffer will overflow.
   * @throw ::io_exception on error.
   * @fixme really it can throw any kind of exception.
   */
  virtual memsize defer_write(const void *buffer, memsize len);

  /**
   * Writes content of inner buffer to real output stream.
   * @throws ::io_exception on error.
   * @fixme really it can throw any kind of exception.
   */
  void flush();

//protected:
  DataOutputStream *m_output;

  char m_buffer[100000];

  size_t m_dataLength;
};


