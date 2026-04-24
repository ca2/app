/* MD5
 converted to C++ class by Frank Thilo (thilo@unix-ag.org)
 for bzflag (http://www.bzflag.org)

   based on:

   md5.h and md5.c
   reference implementation of RFC 1321

   Copyright (C) 1991-2, RSA Data Security, Inc. Created 1991. All
rights reserved.

License to copy and use this software is granted provided that it
is identified as the "RSA Data Security, Inc. MD5 Message-Digest
Algorithm" in all material mentioning or referencing this software
or this function.

License is also granted to make and use derivative works provided
that such works are identified as "derived from the RSA Data
Security, Inc. MD5 Message-Digest Algorithm" in all material
mentioning or referencing the derived work.

RSA Data Security, Inc. makes no representations concerning either
the merchantability of this software or the suitability of this
software for any particular purpose. It is provided "as is"
without express or implied warranty of any kind.

These notices must be retained in any copies of any part of this
documentation and/or software.

*/

#pragma once


//#include "subsystem/platform/inttypes.h"

class MD5
{
public:
  MD5();
  void update(const unsigned char *buf, unsigned int length);
  void update(const char *buf, unsigned int length);
  MD5& finalize();

  /**
   * Returns 16 byte MD5 hash.
   */
  unsigned char *getHash();

private:
  static const int BLOCKSIZE = 64;

  static void decode(unsigned int output[], const unsigned char input[], unsigned int len);
  static void encode(unsigned char output[], const unsigned int input[], unsigned int len);

  void init();

  void transform(const unsigned char block[BLOCKSIZE]);

private:

  //
  // low level logic operations
  //

  static unsigned int F(unsigned int x, unsigned int y, unsigned int z);
  static unsigned int G(unsigned int x, unsigned int y, unsigned int z);
  static unsigned int H(unsigned int x, unsigned int y, unsigned int z);
  static unsigned int I(unsigned int x, unsigned int y, unsigned int z);

  static unsigned int rotateLeft(unsigned int x, int n);

  static void FF(unsigned int &a, unsigned int b, unsigned int c, unsigned int d, unsigned int x, unsigned int s, unsigned int ac);
  static void GG(unsigned int &a, unsigned int b, unsigned int c, unsigned int d, unsigned int x, unsigned int s, unsigned int ac);
  static void HH(unsigned int &a, unsigned int b, unsigned int c, unsigned int d, unsigned int x, unsigned int s, unsigned int ac);
  static void II(unsigned int &a, unsigned int b, unsigned int c, unsigned int d, unsigned int x, unsigned int s, unsigned int ac);

private:
  // if finalized.
  bool m_finalized;
  // bytes that didn't fit in last 64 byte chunk.
  unsigned char m_buffer[BLOCKSIZE];
  // 64bit counter for number of bits (lo, hi).
  unsigned int m_count[2];
  // m_digest so far.
  unsigned int m_state[4];
  // the result.
  unsigned char m_digest[16];
};


