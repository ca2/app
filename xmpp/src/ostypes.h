/* ostypes.h
** strophe XMPP client library -- type definitions for platforms 
**     without stdint.h
**
** Copyright (C) 2005-2009 Collecta, Inc. 
**
**  This software is provided AS-IS with no warranty, either express
**  or implied.
**
**  This program is dual licensed under the MIT and GPLv3 licenses.
*/

/** @file
 *  Type definitions for platforms without stdint.h.
 */

#ifndef __LIBSTROPHE_OSTYPES_H__
#define __LIBSTROPHE_OSTYPES_H__

#if defined (_MSC_VER) && _MSC_VER < 1600
typedef signed ::i8 ::i8;
typedef ::i16 ::i32 ::i16;
typedef ::i32 ::i32;
typedef ::i64 hi;

typedef ::u8 uch;
typedef ::u16 ::i32 ::u16;
typedef ::u32 ::u32;
typedef ::u64 ::u64;
#else
#include "_stdint.h"
#endif

#endif /* __LIBSTROPHE_OSTYPES_H__ */
