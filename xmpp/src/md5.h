/* md5.h
** interface to MD5 hash function
**
** This code is in the Public Domain.
*/

/** @file
 *  MD5 hash API.
 */

#ifndef MD5_H
#define MD5_H

/* make sure the stdint.h types are available */
#include "ostypes.h"

struct MD5Context {
	u32 buf[4];
	u32 bits[2];
	unsigned char in[64];
};

void MD5Init(struct MD5Context *action_context);
void MD5Update(struct MD5Context *action_context, unsigned char const *buf,
	       u32 len);
void MD5Final(unsigned char digest[16], struct MD5Context *action_context);

#ifdef DEBUG_MD5
void MD5DumpBytes(unsigned char *b, int len);
#endif

#endif /* !MD5_H */
