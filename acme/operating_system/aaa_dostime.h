#pragma once
#ifndef DOSTIME_H
#define DOSTIME_H

/*
  dostime.h - routines for converting UNIX time to MS-DOS time.

  Various Copyrights:

  First written by Mark Adler, Richard B. Wales, Jean-loup Gailly,
  Kai Uwe Rommel, Onno van der Linden and Igor Mandrichenko (1990-1997).
  Tweaked further by Bryan Burns (1999).
  Redesigned with full error checks by Alexis Wilke (2015).

  This program is free software; you can redistribute it and/or
  modify it under the terms of the GNU General Public License
  as published by the Free Software Foundation; either version 2
  of the License, or (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*/

/** \file
 * \brief Definitions for the MS-DOS to Unix time conversions.
 *
 * This header defines a few functions helping in converting MS-DOS
 * to Unix time and vice versa.
 *
 * \note
 * This uses C code.
 */

#include <time.h>
#include <inttypes.h>



typedef uint32_t  dos_time_t;

CLASS_DECL_ACME dos_time_t   minimum_dos_time();
CLASS_DECL_ACME dos_time_t   maximum_dos_time();
CLASS_DECL_ACME posix_time      dos_time_unix_time(dos_time_t dostime);
CLASS_DECL_ACME dos_time_t   dos_time(int year, int month, int day, int hour, int minute, int second);
CLASS_DECL_ACME dos_time_t   unix_time_dos_time(posix_time unix_time);


// Local Variables:
// mode: cpp
// indent-tabs-mode: nil
// c-basic-offset: 4
// tab-width: 4
// End:

// vim: ts=2 sw=2 et
#endif
