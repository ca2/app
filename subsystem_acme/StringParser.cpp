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
#include "framework.h"
#include "StringParser.h"

// #include aaa_<stdio.h>

namespace subsystem
{
   bool StringParser::parseInt(const char *str, int *out)
   {
      int value = 0;
      char c;
      if(sscanf(str, "%d%c", &value, &c) != 1) {
         return false;
      }
      if (out != NULL) {
         *out = value;
      }

      return true;
   }

   bool StringParser::parseUInt(const char *str, unsigned int *out)
   {
      // Check the minus sign manually because _tcstoul does not fail on it.
      if (str != 0 && str[0] == '-') {
         return false;
      }

      char *ptr = 0;
      errno = 0;
      unsigned long ulongValue = strtoul(str, &ptr, 10);
      if (errno != 0 || ptr == 0 || *ptr != '\0') {
         return false;
      }

      unsigned int uintValue = (unsigned int)ulongValue;
      if ((unsigned long)uintValue != ulongValue) {
         return false;
      }

      if (out != NULL) {
         *out = uintValue;
      }

      return true;
   }

   bool StringParser::parseUInt64(const char *str, unsigned long long *out)
   {
      unsigned long long value = 0;
      char c;
      if(sscanf(str, "%llu%c", &value, &c) != 1) {
         return false;
      }
      if (out != NULL) {
         *out = value;
      }

      return true;
   }

   bool StringParser::tryParseInt(const char *str)
   {
      return parseInt(str, NULL);
   }

   bool StringParser::parseHex(const char *str, unsigned int *out)
   {
      char c;
      unsigned int val;
      if (sscanf(str, "%x%c", &val, &c) != 1) {
         return false;
      }
      if (out != NULL) {
         *out = val;
      }
      return true;
   }

   bool StringParser::parseByteHex(const char *str, unsigned char *out)
   {
      char c;
      int val = 0;
      if (sscanf(str, "%x%c", &val, &c) != 1) {
         return false;
      }
      if (out != NULL) {
         *out = (unsigned char)val;
      }
      return true;
   }

   bool StringParser::parseByte(const char *str, unsigned char *out)
   {
      char c;
      int val = 0;
      if (sscanf(str, "%d%c", &val, &c) != 1) {
         return false;
      }
      if (out != NULL) {
         *out = (unsigned char)val;
      }
      return true;
   }
} // namespace subsystem