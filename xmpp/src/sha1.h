/* public api for steve reid's public domain SHA-1 implementation */
/* this file is in the public domain */

/** @file
 *  SHA-1 hash API.
 */

#ifndef __SHA1_H
#define __SHA1_H

#ifdef __cplusplus
extern "C" {
#endif

/* make sure the stdint.h types are available */
#include "ostypes.h"

typedef struct {
    u32 state[5];
    u32 count[2];
    u8  buffer[64];
} SHA1_CTX;

#define SHA1_DIGEST_SIZE 20

void SHA1_Init(SHA1_CTX* action_context);
void SHA1_Update(SHA1_CTX* action_context, const u8* data, const size_t len);
void SHA1_Final(SHA1_CTX* action_context, u8 digest[SHA1_DIGEST_SIZE]);

#ifdef __cplusplus
}
#endif

#endif /* __SHA1_H */
