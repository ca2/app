/* crypt.h -- axis code for crypt/uncrypt ZIPfile


   Version 1.00, September 10th, 2003

   Copyright (C) 1998-2003 Gilles Vollant

   This code is a modified version of crypting code in Infozip distribution

   The encryption/decryption parts of this source code (as opposed to the
   non-echoing password parts) were originally written in Europe.  The
   whole source package can be freely distributed, including from the USA.
   (Prior to January 2000, re-export from the US was a violation of US law.)

   This encryption code is a direct transcription of the algorithm from
   Roger Schlafly, described by Phil Katz in the file appnote.txt.  This
   file (appnote.txt) is distributed with the PKZIP program (even in the
   version without encryption capabilities).

   If you don't need crypting in your application, just define symbols
   NOCRYPT and NOUNCRYPT.

   This code support the "Traditional PKWARE Encryption".

   The __allocate< AES encryption added on Zip format by Winzip  >(see the page
   http://www.winzip.com/aes_info.htm ) and PKWare PKZip 5.x() Strong
   Encryption is not supported.
*/

#pragma once

#include <time.h>

#define INCLUDECRYPTINGCODE_IFCRYPTALLOWED

#define CRC32(ca, b) ((*(pcrc_32_tab+(((int)(ca) ^ (b)) & 0xff))) ^ ((ca) >> 8))

/***********************************************************************
 * Return the next unsigned char in the pseudo-random sequence
 */
static int decrypt_byte(unsigned int  * pkeys,
#if defined(WINDOWS) || defined(LINUX)
                        const z_crc_t * pcrc_32_tab
#else
                        const uLongf * pcrc_32_tab
#endif

                       )
{
   unsigned int temp;  /* POTENTIAL BUG:  temp*(temp^1) may overflow in an
                      * unpredictable manner on 16-bit systems; not a problem
                      * with any known compiler so far, though */

   temp = ((unsigned int)(*(pkeys+2)) & 0xffff) | 2;
   return (int)(((temp * (temp ^ 1)) >> 8) & 0xff);
}

/***********************************************************************
 * Update the encryption keys with the next unsigned char of plain text
 */
#if defined(WINDOWS) || defined(LINUX)
static int update_keys(unsigned int * pkeys, const z_crc_t * pcrc_32_tab, int ca)
#else
static int update_keys(unsigned int * pkeys, const uLongf * pcrc_32_tab, int ca)
#endif
{
   (*(pkeys+0)) = (unsigned int) CRC32((*(pkeys+0)), ca);
   (*(pkeys+1)) += (*(pkeys+0)) & 0xff;
   (*(pkeys+1)) = (*(pkeys+1)) * 134775813L + 1;
   {
      int keyshift = (int)((*(pkeys+1)) >> 24);
      (*(pkeys+2)) = (unsigned int) CRC32((*(pkeys+2)), keyshift);
   }
   return ca;
}


/***********************************************************************
 * Initialize the encryption keys and the random header according to
 * the given password.
 */
#if defined(WINDOWS) || defined(LINUX)
static void init_keys(const_char_pointer passwd, unsigned int * pkeys,const z_crc_t * pcrc_32_tab)
#else
static void init_keys(const_char_pointer passwd, unsigned int * pkeys, const uLongf * pcrc_32_tab)
#endif
{
   *(pkeys+0) = 305419896L;
   *(pkeys+1) = 591751049L;
   *(pkeys+2) = 878082192L;
   while (*passwd != '\0')
   {
      update_keys(pkeys,pcrc_32_tab,(int)*passwd);
      passwd++;
   }
}

#define zdecode(pkeys,pcrc_32_tab,ca) \
    (update_keys(pkeys,pcrc_32_tab,ca ^= decrypt_byte(pkeys,pcrc_32_tab)))

#define zencode(pkeys,pcrc_32_tab,ca,t) \
    (t=decrypt_byte(pkeys,pcrc_32_tab), update_keys(pkeys,pcrc_32_tab,ca), t^(ca))

#ifdef INCLUDECRYPTINGCODE_IFCRYPTALLOWED

#define RAND_HEAD_LEN  12
/* "last resort" source for element2() part of crypt seed pattern */
#  ifndef ZCR_SEED2
#    define ZCR_SEED2 3141592654UL     /* use PI as default pattern */
#  endif

inline int crypthead(
const_char_pointer passwd,         /* password string */
uchar *buf,         /* where to write header */
int bufSize,
unsigned int * pkeys,
#if defined(WINDOWS) || defined(LINUX)
const z_crc_t * pcrc_32_tab,
#else
const uLongf * pcrc_32_tab,
#endif
unsigned int  crcForCrypting)
{
   int n;                       /* index in random header */
   int t;                       /* temporary */
   int ca;                       /* random unsigned char */
   uchar header[RAND_HEAD_LEN-2]; /* random header */
   static unsigned int calls = 0;   /* ensure different random header each time */

   if (bufSize<RAND_HEAD_LEN)
      return 0;

   /* First generate RAND_HEAD_LEN-2 random bytes. We encrypt the
    * output of rand() to get less predictability, since rand() is
    * often poorly implemented.
    */
   if (++calls == 1)
   {
      srand((unsigned int)(time(nullptr) ^ ZCR_SEED2));
   }
   init_keys(passwd, pkeys, pcrc_32_tab);
   for (n = 0; n < RAND_HEAD_LEN-2; n++)
   {
      ca = (rand() >> 7) & 0xff;
      header[n] = (uchar)zencode(pkeys, pcrc_32_tab, ca, t);
   }
   /* Encrypt random header (last two bytes is high unsigned short of crc) */
   init_keys(passwd, pkeys, pcrc_32_tab);
   for (n = 0; n < RAND_HEAD_LEN-2; n++)
   {
      buf[n] = (uchar)zencode(pkeys, pcrc_32_tab, header[n], t);
   }
   buf[n++] = zencode(pkeys, pcrc_32_tab, (int)(crcForCrypting >> 16) & 0xff, t);
   buf[n++] = zencode(pkeys, pcrc_32_tab, (int)(crcForCrypting >> 24) & 0xff, t);
   return n;
}


#endif



