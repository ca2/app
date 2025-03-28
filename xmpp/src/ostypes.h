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
typedef signed char char;
typedef short int short;
typedef int int;
typedef long long hi;

typedef unsigned char uch;
typedef unsigned short int unsigned short;
typedef unsigned int unsigned int;
typedef unsigned long long unsigned long long;
#else
#include "_stdint.h"
#endif

#endif /* __LIBSTROPHE_OSTYPES_H__ */
