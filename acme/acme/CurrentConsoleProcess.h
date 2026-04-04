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


#include "remoting/remoting_common/win_system/Process.h"
//#include "log_writer/LogWriter.h"

/**
 * Enables you to start and stop processes in interactive console session.
 *
 * Solves problem of starting interactive processes from service.
 *
 * @note that created process will have same access rights as caller (parent process).
 *
 * @remark this class is needed for executing TightVNC Server system applications
 * like Desktop Server, Query Application, so it can do "XP Trick"
 * (force changing current session to session0 and lock workstation after) on WinXP to
 * avoid 233 'Pipe not connected error' error in CreateProcessAsUser WinAPI function
 * (It's unfixed Microsoft bug on Windows XP).
 *
 * @fixme rename it.
 */
class CLASS_DECL_REMOTING_COMMON CurrentConsoleProcess : public Process
{
public:
  /**
   * Inherited from superclass (Process class).
   *
   * See description of Process constructor.
   */
  CurrentConsoleProcess(LogWriter *log, bool connectRdpSession, const ::scoped_string & scopedstrPath = 0, const ::scoped_string & scopedstrArgs = 0);
  /**
   * Destoys instance of class.
   */
  virtual ~CurrentConsoleProcess();

  /**
   * Starts process in interactive console session.
   * @throws SystemException on fail.
   * @remark can use "XP Trick" to avoid error 233 bug on Windows XP,
   * read more at remark to CurrentConsoleProcess class.
   * @remark to detect WinXP bug it uses loop, so before XP trick will be tried,
   * it will try to start process for some times.
   */
  virtual void start();

private:
  LogWriter *m_log;
  bool m_connectRdpSession;
};


