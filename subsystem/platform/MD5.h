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

namespace subsystem
{
   //#include "subsystem/platform/inttypes.h"

   class CLASS_DECL_SUBSYSTEM MD5
   {
   public:
      MD5();
      void update(const unsigned char *buf, ::u32 length);
      void update(const char *buf, ::u32 length);
      MD5& finalize();

      /**
       * Returns 16 byte MD5 hash.
       */
      unsigned char *getHash();

   private:
      static const int BLOCKSIZE = 64;

      static void decode(::u32 output[], const unsigned char input[], ::u32 len);
      static void encode(unsigned char output[], const ::u32 input[], ::u32 len);

      void init();

      void transform(const unsigned char block[BLOCKSIZE]);

   private:

      //
      // low level logic operations
      //

      static ::u32 F(::u32 x, ::u32 y, ::u32 z);
      static ::u32 G(::u32 x, ::u32 y, ::u32 z);
      static ::u32 H(::u32 x, ::u32 y, ::u32 z);
      static ::u32 I(::u32 x, ::u32 y, ::u32 z);

      static ::u32 rotateLeft(::u32 x, int n);

      static void FF(::u32 &a, ::u32 b, ::u32 c, ::u32 d, ::u32 x, ::u32 s, ::u32 ac);
      static void GG(::u32 &a, ::u32 b, ::u32 c, ::u32 d, ::u32 x, ::u32 s, ::u32 ac);
      static void HH(::u32 &a, ::u32 b, ::u32 c, ::u32 d, ::u32 x, ::u32 s, ::u32 ac);
      static void II(::u32 &a, ::u32 b, ::u32 c, ::u32 d, ::u32 x, ::u32 s, ::u32 ac);

   private:
      // if finalized.
      bool m_finalized;
      // bytes that didn't fit in last 64 byte chunk.
      unsigned char m_buffer[BLOCKSIZE];
      // 64bit counter for number of bits (lo, hi).
      ::u32 m_count[2];
      // m_digest so far.
      ::u32 m_state[4];
      // the result.
      unsigned char m_digest[16];
   };

} // namespace subsystem


