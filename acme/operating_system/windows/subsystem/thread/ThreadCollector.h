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


//#include "critical_section.h"
//#include "remoting/remoting_common/win_system/WindowsEvent.h"
//#include <list>

#include "acme/prototype/collection/list.h"
#include "acme/operating_system/windows/subsystem/thread/Thread.h"

typedef ::list_base<Thread *> ThreadList;

// Collector threads.
// ThreadCollector has it's own thread which deletes in infinity loop not
// active threads.
class CLASS_DECL_REMOTING_COMMON ThreadCollector : protected task
{
public:
  ThreadCollector();
  virtual ~ThreadCollector();

  // Adds thread to a self ::list_base.
  virtual void addThread(task *thread);

  // Forces terminates all threads, waits until they dies and than
  // delete them from memory and thread ::list_base.
  void destroyAllThreads();

  const size_t Size();

protected:
  virtual void execute();

  // Deletes all dead threads from memory and removes them from self ::list_base.
  void deleteDeadThreads();

protected:
  ThreadList m_threads;
  critical_section m_lockObj;

  manual_reset_happening m_timer;
};

//// __THREADCOLLECTOR_H__
