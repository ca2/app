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


//
// Disable warning C4290 cause
//
// "A function is declared using exception specification,
// which Visual C++ accepts but does not implement" (c) MSDN.
//
// "Visual C++ departs from the ANSI Standard in its implementation
// of exception specifications" (c) MSDN.
//
// For more info read topic "::subsystem::Exception Specifications" on MSDN.
//

//#ifdef WIN32
//#include "winhdr.h"
//#endif
// LIBJPEG_TURBO was disbled only for SDK.
//#define LIBJPEG_TURBO
// WIN32


////#include "::string.h"
#include "acme/parallelization/critical_section.h"
#include "acme/subsystem/particle.h"
#include "acme/subsystem/string_table.h"

//// __COMMONHEADER_H__
