// Copyright (C) 2008,2009,2010,2011,2012 GlavSoft LLC.
// All rights reserved.
//
//-------------------------------------------------------------------------
// This file is part of the T i g h t V N C software.  Please visit our Web site:
//
//                       http://www.t i g h t v n c.com/
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
#include "framework.h"
#include "StringParser.h"

// #include aaa_<stdio.h>

namespace subsystem
{
   bool StringParser::parseInt(const_char_pointer str, ::i32 *out)
   {
      ::i32 value = 0;
      ::i8 c;
      if(sscanf(str, "%d%c", &value, &c) != 1) {
         return false;
      }
      if (out != NULL) {
         *out = value;
      }

      return true;
   }

   bool StringParser::parseUInt(const_char_pointer str, ::u32 *out)
   {
      // Check the minus sign manually because _tcstoul does not fail on it.
      if (str != 0 && str[0] == '-') {
         return false;
      }

      char_pointer ptr = 0;
      errno = 0;
      ulong ulongValue = strtoul(str, &ptr, 10);
      if (errno != 0 || ptr == 0 || *ptr != '\0') {
         return false;
      }

      ::u32 uintValue = (::u32)ulongValue;
      if ((ulong)uintValue != ulongValue) {
         return false;
      }

      if (out != NULL) {
         *out = uintValue;
      }

      return true;
   }

   bool StringParser::parseUInt64(const_char_pointer str, ::u64 *out)
   {
      ::u64 value = 0;
      ::i8 c;
      if(sscanf(str, "%llu%c", &value, &c) != 1) {
         return false;
      }
      if (out != NULL) {
         *out = value;
      }

      return true;
   }

   bool StringParser::tryParseInt(const_char_pointer str)
   {
      return parseInt(str, NULL);
   }

   bool StringParser::parseHex(const_char_pointer str, ::u32 *out)
   {
      ::i8 c;
      ::u32 val;
      if (sscanf(str, "%x%c", &val, &c) != 1) {
         return false;
      }
      if (out != NULL) {
         *out = val;
      }
      return true;
   }

   bool StringParser::parseByteHex(const_char_pointer str, ::u8 *out)
   {
      ::i8 c;
      ::i32 val = 0;
      if (sscanf(str, "%x%c", &val, &c) != 1) {
         return false;
      }
      if (out != NULL) {
         *out = (::u8)val;
      }
      return true;
   }

   bool StringParser::parseByte(const_char_pointer str, ::u8 *out)
   {
      ::i8 c;
      ::i32 val = 0;
      if (sscanf(str, "%d%c", &val, &c) != 1) {
         return false;
      }
      if (out != NULL) {
         *out = (::u8)val;
      }
      return true;
   }
} // namespace subsystem