/* tls.h
** strophe XMPP client library -- TLS abstraction header
**
** Copyright (C) 2005-2009 Collecta, Inc. 
**
**  This software is provided AS-IS with no warranty, either express
**  or implied.
**
**  This program is dual licensed under the MIT and GPLv3 licenses.
*/

/** @file
 *  TLS abstraction API.
 */

#ifndef __LIBSTROPHE_TLS_H__
#define __LIBSTROPHE_TLS_H__

#include "common.h"
#include "sock.h"

typedef struct _tls tls_t;

void tls_initialize(void);
void tls_shutdown(void);

tls_t *tls_new(xmpp_ctx_t *ctx, sock_t sock);
void tls_free(tls_t *tls);

int tls_set_credentials(tls_t *tls, const ::string &cafilename);

int tls_start(tls_t *tls);
int tls_stop(tls_t *tls);

int tls_error(tls_t *tls);

int tls_pending(tls_t *tls);
int tls_read(tls_t *tls, void * const buff, const size_t len);
int tls_write(tls_t *tls, const void * const buff, const size_t len);

int tls_clear_pending_write(tls_t *tls);
int tls_is_recoverable(int error);

#endif /* __LIBSTROPHE_TLS_H__ */
