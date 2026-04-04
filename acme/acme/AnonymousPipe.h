// Copyright (C) 2010,2011,2012 GlavSoft LLC.
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


#include "remoting/remoting_common/io/Channel.h"
#include "remoting/remoting_common/win_system/Pipe.h"
#include "remoting/remoting_common/util/CommonHeader.h"

#include "remoting/remoting_common/win_system/WindowsEvent.h"
#include "remoting/remoting_common/thread/LocalMutex.h"
//#include "log_writer/LogWriter.h"

class CLASS_DECL_REMOTING_COMMON AnonymousPipe : public Channel, public Pipe
{
public:
  // @param hWrite is a write handle getting by the CreatePipe()
  // function calling.
  // @param hRead is a read handle getting by the CreatePipe()
  // function calling but is not the same as for hWrite.
  AnonymousPipe(HANDLE hWrite, HANDLE hRead, unsigned int maxPortionSize, LogWriter *log);
  virtual ~AnonymousPipe();

  /**
   * Closes transport.
   *
   * @throws ::remoting::Exception on fail.
   */
  void close();

  /**
   * Reads data from pipe.
   * Implemented from Channel interface.
   * @param buffer buffer to receive data.
   * @param len count of bytes to read.
   * @throws ::io_exception on io error.
   */
  virtual size_t read(void *buffer, size_t len);

  /**
   * Writes data to pipe.
   * Implemented from Channel interface.
   * @param buffer buffer with data to write.
   * @param len count of bytes to write.
   * @throws ::io_exception on io error.
   */
  virtual memsize defer_write(const void *buffer, memsize len);

  virtual size_t available() { return 0; };

  // Returns pipe handle to write
  HANDLE getWriteHandle() const;

  // Returns pipe handle to read
  HANDLE getReadHandle() const;

  // This function assigns the handles for another process.
  // @param hTargetProc is a handle to the other process.
  // If neededToClose parameter set to true then after calling this function
  // the destructor will try to close the assigned handles. If the handles
  // assigned for another process then set neededToClose flag to false.
  // If keepCloseRight is true then source process keeps the right to close
  // the new handles.
  // @throw ::remoting::Exception on a fail.
  void assignHandlesFor(HANDLE hTargetProc, bool neededToClose,
                        bool keepCloseRight = false);

  void setTimeOut(unsigned int timeOut);

private:
  void checkPipeHandle(HANDLE handle);

  HANDLE m_hWrite;
  HANDLE m_hRead;
  bool m_neededToClose;
  unsigned int m_timeOut;

  LocalMutex m_hPipeMutex;
  WindowsEvent m_readEvent;
  WindowsEvent m_writeEvent;

  LogWriter *m_log;
};

//// __ANONYMOUSPIPE_H__
