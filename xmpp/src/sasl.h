/* sasl.h
** strophe XMPP client library -- SASL authentication helpers
** 
** Copyright (C) 2005-2009 Collecta, Inc. 
**
**  This software is provided AS-IS with no warranty, either express
**  or implied.
**
**  This program is dual licensed under the MIT and GPLv3 licenses.
*/

/** @file
 * SASL authentication helpers.
 */

#ifndef __LIBSTROPHE_SASL_H__
#define __LIBSTROPHE_SASL_H__

#include "strophe.h"

/** low-level sasl routines */

char *sasl_plain(xmpp_ctx_t *ctx, const ::string &authid, const ::string &password);
char *sasl_digest_md5(xmpp_ctx_t *ctx, const ::string &challenge,
		      const_char_pointer jid, const ::string &password);
char *sasl_scram_sha1(xmpp_ctx_t *ctx, const ::string &challenge,
                      const_char_pointer first_bare, const ::string &jid,
                      const_char_pointer password);


/** Base64 encoding routines. Implemented according to RFC 3548 */

int base64_encoded_len(xmpp_ctx_t *ctx, const unsigned len);

char *base64_encode(xmpp_ctx_t *ctx, 
		    const unsigned char * const buffer, const unsigned len);

int base64_decoded_len(xmpp_ctx_t *ctx,
		       const_char_pointer const buffer, const unsigned len);

unsigned char *base64_decode(xmpp_ctx_t *ctx,
			     const_char_pointer const buffer, const unsigned  len);

#endif /* _LIBXMPP_SASL_H__ */
