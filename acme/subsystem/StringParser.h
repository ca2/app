// Copyright (C) 2008,2009,2010,2011,2012 GlavSoft LLC.
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
// with this program; if not, write to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
//-------------------------------------------------------------------------
//

#pragma once
//#define _STRING_PARSER_H_

//#include "inttypes.h"
//#include "CommonHeader.h"


namespace subsystem
{

   class CLASS_DECL_ACME StringParser :
      virtual public ::particle
   {
   public:
      virtual bool tryParseInt(const char *str);
      virtual bool parseInt(const char *str, int *out);
      // FIXME: it returns true on values that greater then 0xFFFFFFFF.
      virtual bool parseUInt(const char *str, unsigned int *out);
      virtual bool parseUInt64(const char *str, unsigned long long *out);
      virtual bool parseHex(const char *str, unsigned int *out);
      virtual bool parseByte(const char *str, unsigned char *out);
      virtual bool parseByteHex(const char *str, unsigned char *out);
   };


} //   namespace subsystem

//#endif
