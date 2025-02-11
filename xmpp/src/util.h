/* util.h
** strophe XMPP client library -- various utility functions
**
** Copyright (C) 2005-2009 Collecta, Inc. 
**
**  This software is provided AS-IS with no warranty, either express
**  or implied.
**
**  This program is dual licensed under the MIT and GPLv3 licenses.
*/

/** @file
 *  Internally used utility functions.
 */

#ifndef __LIBSTROPHE_UTIL_H__
#define __LIBSTROPHE_UTIL_H__

#include "ostypes.h"

/* timing functions */
unsigned long long time_stamp(void);
unsigned long long time_elapsed(unsigned long long t1, unsigned long long t2);

#endif /* __LIBSTROPHE_UTIL_H__ */
