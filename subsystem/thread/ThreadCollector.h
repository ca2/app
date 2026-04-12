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


#include "subsystem/thread/Thread.h"
//#include "critical_section.h"
//#include "subsystem/thread/WindowsEvent.h"
//// #include aaa_<list>

#include "acme/prototype/collection/list.h"
namespace subsystem
{
   typedef ::list_base<Thread *> ThreadList;

   // Collector threads.
   // ThreadCollector has it's own thread which deletes in infinity loop not
   // active threads.
   class CLASS_DECL_ACME ThreadCollector :
      virtual public Thread
   {
   public:
      ThreadCollector();
      ~ThreadCollector() override;

      // Adds thread to a self ::list_base.
      virtual void addThread(Thread *thread) = 0;

      // Forces terminates all threads, waits until they dies and than
      // delete them from memory and thread ::list_base.
      virtual void destroyAllThreads() = 0;

      virtual const size_t Size() = 0;

   //protected:
      virtual void execute() = 0;

      // Deletes all dead threads from memory and removes them from self ::list_base.
      virtual void deleteDeadThreads() = 0;

   // //protected:
   //    ThreadList m_threads;
   //    critical_section m_lockObj;
   //
   //    WindowsEvent m_timer;
   };

   // // Collector threads.
   // // ThreadCollector has it's own thread which deletes in infinity loop not
   // // active threads.
   // class CLASS_DECL_ACME ThreadCollector :
   //    virtual public ::subsystem::composite<ThreadCollector
   // {
   // public:
   //    ThreadCollector();
   //     ~ThreadCollector() override;
   //
   //    // Adds thread to a self ::list_base.
   //    void addThread(ThreadInterface *thread) override;
   //
   //    // Forces terminates all threads, waits until they dies and than
   //    // delete them from memory and thread ::list_base.
   //    void destroyAllThreads() override;
   //
   //    const size_t Size() override;
   //
   //    //protected:
   //    void execute() override;
   //
   //    // Deletes all dead threads from memory and removes them from self ::list_base.
   //    void deleteDeadThreads() override;
   //
   //    // //protected:
   //    //    ThreadList m_threads;
   //    //    critical_section m_lockObj;
   //    //
   //    //    WindowsEvent m_timer;
   // };

   //// __THREADCOLLECTOR_H__
} // namespace subsystem


