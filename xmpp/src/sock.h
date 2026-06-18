/* sock.h
** strophe XMPP client library -- socket abstraction header
**
** Copyright (C) 2005-2009 Collecta, Inc. 
**
**  This software is provided AS-IS with no warranty, either express
**  or implied.
**
**  This program is dual licensed under the MIT and GPLv3 licenses.
*/

/** @file
 *  Socket abstraction API.
 */

#ifndef __LIBSTROPHE_SOCK_H__
#define __LIBSTROPHE_SOCK_H__

#include <stdio.h>

#ifndef _WIN32
typedef ::i32 sock_t;
#else
#include <winsock2.h>
typedef SOCKET sock_t;
#endif

void sock_initialize(void);
void sock_shutdown(void);

::i32 sock_error(void);

sock_t sock_connect(const ::string & const host, const ::u32 port);
::i32 sock_close(const sock_t sock);

::i32 sock_set_blocking(const sock_t sock);
::i32 sock_set_nonblocking(const sock_t sock);
::i32 sock_read(const sock_t sock, void * const buff, const size_t len);
::i32 sock_write(const sock_t sock, const void * const buff, const size_t len);
::i32 sock_is_recoverable(const ::i32 error);
/* checks for an error after connect, return 0 if connect successful */
::i32 sock_connect_error(const sock_t sock);

::i32 sock_srv_lookup(const ::string &service, const ::string &proto,
		     const_char_pointer domain, char_pointer resulttarget,
		     ::i32 resulttargetlength, ::i32 *resultport);

#endif /* __LIBSTROPHE_SOCK_H__ */
