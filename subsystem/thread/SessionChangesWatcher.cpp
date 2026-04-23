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
#include "SessionChangesWatcher.h"
//#include "subsystem/node/WTS.h"

//SessionChangesWatcher::SessionChangesWatcher(AnEventListener *extSessionChangesListener,
//                                             ::subsystem::LogWriter *log)
//: m_extSessionChangesListener(extSessionChangesListener),
//  m_plogwriter(log)
//{
//  ProcessIdToSessionId(GetCurrentProcessId(), &m_baseSessionId);
//  resume();
//}

namespace subsystem
{

   SessionChangesWatcher::SessionChangesWatcher() {}
   SessionChangesWatcher ::~SessionChangesWatcher() {}

   //
   // SessionChangesWatcher::SessionChangesWatcher(
   //   const ::procedure & procedureSessionChanged, ::subsystem::LogWriter *log) :
   //    m_procedureSessionChanged(procedureSessionChanged), m_plogwriter(log)
   //{
   //   ProcessIdToSessionId(GetCurrentProcessId(), &m_baseSessionId);
   //   resume();
   //}
   // SessionChangesWatcher::~SessionChangesWatcher()
   //{
   //  terminate();
   //  wait();
   //}
   //
   // void SessionChangesWatcher::execute()
   //{
   //  DWORD prevSession = m_baseSessionId;
   //   bool isRdp = WindowsSubsystem().WTS().SessionIsRdpSession(prevSession, m_plogwriter);
   //  ::string prevDeskName, currDeskName;
   //  DesktopSelector::getThreadDesktopName(&prevDeskName);
   //
   //  while (!isTerminating()) {
   //    DWORD currSessionId = prevSession;
   //    if (!isRdp) {
   //      currSessionId = WTS::getActiveConsoleSessionId(m_plogwriter);
   //    }
   //    bool sessionChanged = prevSession != currSessionId;
   //    bool desktopInfoIsAvailable = DesktopSelector::getCurrentDesktopName(&currDeskName);
   //    bool desktopChanged = !currDeskName.isEqualTo(&prevDeskName);
   //    if (sessionChanged || desktopChanged || !desktopInfoIsAvailable) {
   //      m_plogwriter->debug("Session or desktop has been changed."
   //                   " The process session = %u, current session = %u"
   //                   " The process desktop = {}, current desktop = {}",
   //                   (unsigned int)prevSession, (unsigned int)currSessionId,
   //                   prevDeskName, currDeskName);
   //      prevSession = currSessionId;
   //      prevDeskName = currDeskName;
   //      m_extSessionChangesListener->onAnObjectEvent();
   //      terminate();
   //    } else {
   //      // FIXME: Use WindowsEvent instead of Sleep().
   //      Sleep(100);
   //    }
   //  }
   //}


} // namespace subsystem
