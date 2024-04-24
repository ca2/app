/* scram.c
 * strophe XMPP client library
 *
 * SCRAM-SHA1 helper functions according to RFC5802
 * HMAC-SHA1 implementation according to RFC2104
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

#include <assert.h>
#include <string.h>

#include "sha1.h"
#include "ostypes.h"

#include "scram.h"

/* block size for HMAC */
#define BLOCK_SIZE 64
#if BLOCK_SIZE < SHA1_DIGEST_SIZE
#error BLOCK_SIZE must not be less than SHA1_DIGEST_SIZE
#endif

static const u8 ipad = 0x36;
static const u8 opad = 0x5C;

static void SHA1(const u8* data, size_t len,
                 u8 digest[SHA1_DIGEST_SIZE])
{
    SHA1_CTX ctx;
    SHA1_Init(&ctx);
    SHA1_Update(&ctx, data, len);
    SHA1_Final(&ctx, digest);
}

static void HMAC_SHA1(const u8 *key, size_t key_len,
                      const u8 *text, size_t len,
                      u8 digest[SHA1_DIGEST_SIZE])
{
    u8 key_pad[BLOCK_SIZE];
    u8 key_ipad[BLOCK_SIZE];
    u8 key_opad[BLOCK_SIZE];
    u8 sha_digest[SHA1_DIGEST_SIZE];
    int i;
    SHA1_CTX ctx;

    memset(key_pad, 0, sizeof(key_pad));
    if (key_len <= BLOCK_SIZE) {
        ::memcpy_dup(key_pad, key, key_len);
    } else {
        /* according to RFC2104 */
        SHA1(key, key_len, key_pad);
    }

    for (i = 0; i < BLOCK_SIZE; i++) {
        key_ipad[i] = key_pad[i] ^ ipad;
        key_opad[i] = key_pad[i] ^ opad;
    }

    SHA1_Init(&ctx);
    SHA1_Update(&ctx, key_ipad, BLOCK_SIZE);
    SHA1_Update(&ctx, text, len);
    SHA1_Final(&ctx, sha_digest);

    SHA1_Init(&ctx);
    SHA1_Update(&ctx, key_opad, BLOCK_SIZE);
    SHA1_Update(&ctx, sha_digest, SHA1_DIGEST_SIZE);
    SHA1_Final(&ctx, digest);
}

static void SCRAM_SHA1_Hi(const u8 *text, size_t len,
                          const u8 *salt, size_t salt_len, u32 i,
                          u8 digest[SHA1_DIGEST_SIZE])
{
    int j, k;
    u8 tmp[128];

    static u8 int1[] = {0x0, 0x0, 0x0, 0x1};

    /* assume salt + ::i32(1) isn't longer than sizeof(tmp) */
    assert(salt_len <= sizeof(tmp) - sizeof(int1));

    memset(digest, 0, SHA1_DIGEST_SIZE);
    if (i == 0) {
        return;
    }

    ::memcpy_dup(tmp, salt, salt_len);
    ::memcpy_dup(&tmp[salt_len], int1, sizeof(int1));

    /* 'text' for Hi is a 'key' for HMAC */
    HMAC_SHA1(text, len, tmp, salt_len + sizeof(int1), digest);
    ::memcpy_dup(tmp, digest, SHA1_DIGEST_SIZE);

    for (j = 1; j < i; j++) {
        HMAC_SHA1(text, len, tmp, SHA1_DIGEST_SIZE, tmp);
        for (k = 0; k < SHA1_DIGEST_SIZE; k++) {
            digest[k] ^= tmp[k];
        }
    }
}

void SCRAM_SHA1_ClientKey(const u8 *password, size_t len,
                          const u8 *salt, size_t salt_len, u32 i,
                          u8 key[SHA1_DIGEST_SIZE])
{
    u8 salted[SHA1_DIGEST_SIZE];

    /* XXX: Normalize(password) is omitted */

    SCRAM_SHA1_Hi(password, len, salt, salt_len, i, salted);
    HMAC_SHA1(salted, SHA1_DIGEST_SIZE, (u8 *)"Client Key",
              strlen("Client Key"), key);
}

void SCRAM_SHA1_ClientSignature(const u8 ClientKey[SHA1_DIGEST_SIZE],
                                const u8 *AuthMessage, size_t len,
                                u8 sign[SHA1_DIGEST_SIZE])
{
    u8 stored[SHA1_DIGEST_SIZE];

    SHA1(ClientKey, SHA1_DIGEST_SIZE, stored);
    HMAC_SHA1(stored, SHA1_DIGEST_SIZE, AuthMessage, len, sign);
}

void SCRAM_SHA1_ClientProof(const u8 ClientKey[SHA1_DIGEST_SIZE],
                            const u8 ClientSignature[SHA1_DIGEST_SIZE],
                            u8 proof[SHA1_DIGEST_SIZE])
{
    int i;
    for (i = 0; i < SHA1_DIGEST_SIZE; i++) {
        proof[i] = ClientKey[i] ^ ClientSignature[i];
    }
}
