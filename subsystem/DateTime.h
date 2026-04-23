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


// #include "inttypes.h"
// #include "winhdr.h"
// //#include "::string.h"
//
// /**
//  * ::earth::time class.
//  */
// class ::earth::time
// {
// public:
//   /**
//    * Creates empty ::earth::time.
//    */
//   ::earth::time();
//
//   ::earth::time(const ::earth::time &dt);
//
//   /**
//    * Creates ::earth::time object with specified time value.
//    * @param timeValue count of milliseconds from unix epoch.
//    */
//   ::earth::time(unsigned long long timeValue);
//
//   /**
//    * Creates ::earth::time object from windows FILETIME structure.
//    * @param ft time as FILETIME structure.
//    */
//   ::earth::time(FILETIME ft);
//
//   /**
//    * Returns time in milliseconds from unix epoch.
//    */
//   unsigned long long getTime() const;
//
//   ::earth::time operator- (const ::earth::time &d2);
//   ::earth::time operator+ (const ::earth::time &d2);
//
//   /**
//    * Converts this ::earth::time to FILETIME structure.
//    * @param [out] ft output parameter.
//    */
//   void toFileTime(LPFILETIME ft) const;
//
//   /**
//    * Converts this ::earth::time to SYSTEMTIME structure in UTC format.
//    * @param [out] st output parameter.
//    */
//   // FIXME: Rename this method because the now() function already
//   // returns in the local time and to convert after that this function
//   // must be used but time do not converting to UTC in this case.
//   void toUtcSystemTime(LPSYSTEMTIME st) const;
//
//   /**
//    * Converts this ::earth::time to SYSTEMTIME structure in local format.
//    * @param [out] st output parameter.
//    */
//   void toLocalSystemTime(LPSYSTEMTIME st) const;
//   /**
//    * Converts this ::earth::time to string.
//    * @param [out] out output parameter.
//    */
//   void toString(::string & out) const;
//
//   /**
//    * Returns current local time.
//    */
//   static ::earth::time now();
//
// protected:
//   unsigned long long m_timeValue;
// };
//
//
