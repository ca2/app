/*
  TurboC, a library for porting Borland Turbo C to GNU gcc.
  Copyright 2002 Ronald S. Burkey

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

  Contact Ron Burkey at info@sandroid.org.

  Filename:	TurboC.h
  Purpose:	TurboC is a useful little kit of stuff that can be used for
  		converting a Borland Turbo C application to a GNU gcc
		console program.  It doesn't do the whole job, but it does
		provide various library functions present in Turbo C but not
		in gcc libraries.
  Mod history:	01/27/02 RSB	Created.
  		01/31/02 RSB	Continued, defining the conio.h subset used.
		02/03/02 RSB	Split off the conio.h and alloc.h stuff into
				separate headers.
		03/02/02 RSB	Added integer datatype conversions.
				Added random.
		03/18/02 RSB	Modified for C++.
		03/23/02 RSB	Fixed a stray #elif that was supposed to be
				#else.  Added __APPLE__ options.
		03/31/02 RSB	Added some signal-handling stuff.
		04/18/02 RSB	Fixed strcpy and strncpy_dup macros.
		05/09/02 RSB	Moved variables out, and allowed
				for pthreads.
		05/19/02 RSB	Added a few default header files so as
				to conform more easily to the contributed
				code by Igor Bujna.
		12/16/02 RSB	Fixed declaration of fcloseall so that it won't
				conflict with gcc 3.2.

  Not that anybody's likely to care, but constants, datatypes, and function
  prototypes have been taken from the Turbo C Reference Guide, version 2.0,
  and not from any Borland source files.  I imagine that I might have been
  able to just abridge conio.h, alloc.h, etc., but in fact I didn't even look
  at them.
*/
#pragma once

#ifndef __SPHERE_H
#include "sphere/sphere.h"
#endif

#include "turboc/turboc_pre.h"

// Note that all system headers required by *any* TurboC header (even those
// included *after* this one) need to be included before integer datatypes
// are redefined.
////#include <sys/cdefs.h>
//#include <ncurses.h>

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <fcntl.h>
//#include <unistd.h>
#include <signal.h>
//#if defined(linux)
//#include <endian.h>
//#include "_stdint.h"
//#elif defined(__FreeBSD__) || defined(__APPLE__)
//#include <machine/endian.h>
//#include "_inttypes.h"
//#else
////#error Need header files for endian type and integer datatypes.
//#endif
#ifdef WITH_X
//#include <X11/Xlib.h>
//#include <X11/Xutil.h>
//#include "x11layer.h"

#endif
#include <sys/stat.h>		// Needed by dir.h.
//#include <pthread.h>
// (Igor Bujna) --------------------------------------------------------------
#ifdef __DJGPP__
// If anyone knows how to easily solve the following problem, it would be
// great to know about!
#error The following will not work, because TurboC has its own dos.h/bios.h.
#include <dos.h>
#include <bios.h>
#endif // __DJGPP__
//#include <sys/ioctl.h>
#ifdef __linux__
#ifndef PPRSTATUS
// Unfortunately, there's nothing within ppdev.h itself to prevent it from
// being loaded twice, which generates error messages.
#include <linux/ppdev.h>
#endif
/*
 * You must have kernel-2.4.x or newer. For kernel 2.2.x you must
 * download ppdev-patch from ftp.torque.net/pub/parport
 */
#include <linux/parport.h>
#endif // __linux__
// (End Igor) ----------------------------------------------------------------

//----------------------------------------------------------------------------
// Constants.

#define __libTurboC__

// Integer-type stuff that differs depending on whether the original
// source code was for a 16-bit compiler (default) or 32-bit.
typedef char gchar;
typedef signed char gschar;
typedef unsigned char guchar;
typedef short gshort;
typedef unsigned short gushort;
typedef int gint;
typedef unsigned int g::u32;
typedef long glong;
typedef unsigned long gulong;

#ifdef CLK_TCK
#undef CLK_TCK
#endif
#define CLK_TCK (sysconf(_SC_CLK_TCK))

#ifndef DoNotFixIntegers

// Various ctype.h macros are broken by the integer datatype conversions
// below.  This fixes them.
//#include <ctype.h>
#ifdef isupper
#undef isupper
#define isupper isupperTurbo
#undef islower
#define islower islowerTurbo
#undef isalpha
#define isalpha isalphaTurbo
#undef isdigit
#define isdigit isdigitTurbo
#undef isxdigit
#define isxdigit isxdigitTurbo
#undef isspace
#define isspace isspaceTurbo
#undef isprint
#define isprint isprintTurbo
#undef isgraph
#define isgraph isgraphTurbo
#undef iscntrl
#define iscntrl iscntrlTurbo
#undef ispunct
#define ispunct ispunctTurbo
#undef isalnum
#define isalnum isalnumTurbo
#endif // isupper

// String functions that have been renamed, or which are implemented in
// GNU by macros that are screwed up by integer datatype conversion.

#ifdef strcpy
static inline char *
strcpyTurbo (char *s1, const ::string &s2)
{
   return (strcpy (s1, s2));
}

#undef strcpy
#define strcpy strcpyTurbo
#endif // strcpy

#ifdef strncpy_dup
static inline char *
strncpyTurbo (char *s1, const ::string &s2, size_t n)
{
   return (strncpy_dup (s1, s2, n));
}

#undef strncpy_dup
#define strncpy_dup strncpyTurbo
#endif // strncpy_dup

#ifdef strcmp
static inline i16
strcmpTurbo (const ::string &s1, const ::string &s2)
{
   return (strcmp (s1, s2));
}

#undef strcmp
#define strcmp strcmpTurbo
#endif // strcmp

//#ifdef strcasecmp
//static inline i16
//strcmpi (const ::string &s1, const ::string &s2)
//{
//  return (strcasecmp (s1, s2));
//}
//static inline i16
//stricmp (const ::string &s1, const ::string &s2)
//{
//  return (strcasecmp (s1, s2));
//}
//#else // strcasecmp
//#define strcmpi strcasecmp
//#define stricmp strcasecmp
//#endif // strcasecmp

#ifdef strncmp_dup
static inline i16
strncmpTurbo (const ::string &s1, const ::string &s2, i16 n)
{
   return (strncmp_dup (s1, s2, n));
}

#undef strncmp_dup
#define strncmp_dup strncmpTurbo
#endif // strcmp

#ifdef strncasecmp
static inline i16
strncmpi (const ::string &s1, const ::string &s2, i16 n)
{
   return (strncasecmp (s1, s2, n));
}
#else // strncasecmp
#define strncmpi strncasecmp
#endif // strncasecmp

static inline clock_t
clockUnix (void)
{
   return (clock ());
}

#ifdef clock
#undef clock
#endif
#define clock clockTurbo

// Integer datatype conversions.  This particular choice of macros has the
// happy property of handling the most commonly used integer datatype
// specifications (except "unsigned char"), while generating a compiler
// error for all other combinations.
#define short i16
#define int i16
#define unsigned u16
#define long i32

#endif // Compiler32

// Pointer modifiers that aren't needed.
#define far
#define huge

// The "free" function:  We could use the standard library function for
// almost all purposes ... except that we need to account for the sins of the
// getimage function in graphics.h.  We need to introduce a substitute
// that's identical to the standard "free" in most cases, but which
// in some cases transparently frees Pixmaps that getimage has created
// without the programmer's knowledge.  freeUnix is identical to the standard
// library function, while freeTurbo, or just free, is the replacement.
static inline void
freeUnix (void *object)
{
   free (object);
}

#ifdef free
#undef free
#endif
#define free freeTurbo

//----------------------------------------------------------------------------
// Data types.

//----------------------------------------------------------------------------
// Function prototypes.

__BEGIN_DECLS
// My custom version of "free".
CLASS_DECL_TURBOC void freeTurbo (void *object);
#ifdef WITH_X
/*CLASS_DECL_TURBOC int AssociatePixmap (void *object, image handle);
#endif

// Stuff involved in gracefully exiting the program.
void TurboTrap (void);
int TurboX (int);

//// From string.h.
//CLASS_DECL_TURBOC char *strupr (char *);
//CLASS_DECL_TURBOC char *strlwr (char *);

// From stdio.h
//CLASS_DECL_TURBOC gint fcloseall (void);

// Wrappers for ctype.h macros.
CLASS_DECL_TURBOC int isupperTurbo (int c);
CLASS_DECL_TURBOC int islowerTurbo (int c);
CLASS_DECL_TURBOC int isalphaTurbo (int c);
CLASS_DECL_TURBOC int isdigitTurbo (int c);
CLASS_DECL_TURBOC int isxdigitTurbo (int c);
CLASS_DECL_TURBOC int isspaceTurbo (int c);
CLASS_DECL_TURBOC int isprintTurbo (int c);
CLASS_DECL_TURBOC int isgraphTurbo (int c);
CLASS_DECL_TURBOC int iscntrlTurbo (int c);
CLASS_DECL_TURBOC int ispunctTurbo (int c);
CLASS_DECL_TURBOC int isalnumTurbo (int c);

#define random(n) randomTurbo(n)
CLASS_DECL_TURBOC i16 randomTurbo (i16 num);
CLASS_DECL_TURBOC void randomize (void);
CLASS_DECL_TURBOC clock_t clockTurbo (void);

// Endian conversion functions.
CLASS_DECL_TURBOC void FixLittle16 (u16 *);
CLASS_DECL_TURBOC void FixLittle32 (u32 *);
CLASS_DECL_TURBOC void FixBig16 (u16 *);
CLASS_DECL_TURBOC void FixBig32 (u32 *);

// Endian file read/write functions.
CLASS_DECL_TURBOC int ReadLittle16 (FILE * fp, u16 * Value);
CLASS_DECL_TURBOC int ReadBig16 (FILE * fp, u16 * Value);
CLASS_DECL_TURBOC int ReadLittle32 (FILE * fp, u32 * Value);
CLASS_DECL_TURBOC int ReadBig32 (FILE * fp, u32 * Value);
CLASS_DECL_TURBOC int WriteLittle16 (FILE * fp, u16 Value);
CLASS_DECL_TURBOC int WriteBig16 (FILE * fp, u16 Value);
CLASS_DECL_TURBOC int WriteLittle32 (FILE * fp, u32 Value);
CLASS_DECL_TURBOC int WriteBig32 (FILE * fp, u32 Value);

__END_DECLS
//--------------------------------------------------------------------------
// Variables.
#ifdef TURBOC_VARIABLES_C
#else // TURBOC_VARIABLES_C
extern gint TcVideoMode;
extern const int TcUnicodeMappings[256];
#endif // TURBOC_VARIABLES_C


#include "turboc/turboc_pos.h"

