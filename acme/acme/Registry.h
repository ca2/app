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


#include "RegistryKey.h"

namespace acme
{

class CLASS_DECL_REMOTING_COMMON Registry
{
public:
   const static int STRING_TYPE = 1;
   const static int EXPAND_STRING_TYPE = 2;
   const static int BINARY_TYPE = 3;
   const static int DWORD_TYPE = 4;
   const static int QWORD_TYPE = 5;
   
   //public:
   static ::acme::RegX * getCurrentUserKey();
   static ::acme::RegX * getCurrentLocalMachineKey();
   
   //private:
   Registry();
   ~Registry();
};

} // namespace acme





