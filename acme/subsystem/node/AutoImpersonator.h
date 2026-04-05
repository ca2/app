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


#include "Impersonator.h"
//#include "log_writer/LogWriter.h"

// This class automaticly impesonates at the constructor and
// revertes at the destructor.
// This class doesn't throw ::remoting::Exception.
class CLASS_DECL_REMOTING_COMMON AutoImpersonator
{
public:
  AutoImpersonator(Impersonator *imp, LogWriter *log);
  virtual ~AutoImpersonator();
private:
  Impersonator *m_imp;
  LogWriter *m_log;
};

//// __AUTOIMPERSONATOR_H__
