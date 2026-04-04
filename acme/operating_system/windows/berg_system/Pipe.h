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


#include "remoting/remoting_common/util/CommonHeader.h"
#include "WindowsEvent.h"
#include "remoting/remoting_common/io/Channel.h"
#include "remoting/remoting_common/thread/LocalMutex.h"

// This class is not an interface but is a class that contain common
// methods/source codes for derived classes to work with pipe handles.
class CLASS_DECL_REMOTING_COMMON Pipe
{
public:
  unsigned int getMaxPortionSize();

protected:
  Pipe(unsigned int maxPortionSize);
  virtual ~Pipe();

  // This read and write functions is common way to read and write
  // by pipe handles asynchronously.

  // The pointer uses because the functions must have access to
  // the same variable as in a derived class to rich a thread safe
  // handle usage.
  size_t readByHandle(void *buffer, size_t len, HANDLE pipeHandle);
  size_t writeByHandle(const void *buffer, size_t len, HANDLE pipeHandle);

  // This mutex is to use for pipe handles that uses in the above functions.
  // The mutex protect collision accesses to handle fields of derived classes.
  LocalMutex m_hPipeMutex;

  WindowsEvent m_readEvent;
  WindowsEvent m_writeEvent;

private:
  void checkPipeHandle(HANDLE pipeHandle);

  unsigned long long m_totalWrote;
  unsigned long long m_totalRead;
  unsigned int m_maxPortionSize;
};

//// __PIPE_H__
