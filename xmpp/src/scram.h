/* scram.h
 * strophe XMPP client library -- SCRAM-SHA1 helper functions
 *
 * Copyright (C) 2013 Dmitry Podgorny <pasis.ua@gmail.com>
 *
 *  This software is provided AS-IS with no warranty, either express
 *  or implied.
 *
 *  This program is dual licensed under the MIT and GPLv3 licenses.
 */

/** @file
 *  SCRAM-SHA1 helper functions.
 */

#ifndef __LIBSTROPHE_SCRAM_H__
#define __LIBSTROPHE_SCRAM_H__

/* make sure the stdint.h types are available */
#include "ostypes.h"

#include "sha1.h"

void SCRAM_SHA1_ClientKey(const unsigned char *password, size_t len,
                          const unsigned char *salt, size_t salt_len, unsigned int i,
                          unsigned char key[SHA1_DIGEST_SIZE]);

void SCRAM_SHA1_ClientSignature(const unsigned char ClientKey[SHA1_DIGEST_SIZE],
                                const unsigned char *AuthMessage, size_t len,
                                unsigned char sign[SHA1_DIGEST_SIZE]);

void SCRAM_SHA1_ClientProof(const unsigned char ClientKey[SHA1_DIGEST_SIZE],
                            const unsigned char ClientSignature[SHA1_DIGEST_SIZE],
                            unsigned char proof[SHA1_DIGEST_SIZE]);

#endif /* __LIBSTROPHE_SCRAM_H__ */
