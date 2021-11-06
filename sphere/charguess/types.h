/*
	libcharguess	-	Guess the encoding/charset of a string
    Copyright (C) 2003  Stephane Corbe <noubi@users.sourceforge.net>
	Based on Mozilla sources

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
*/
#include "aura/.h"

#include <stdio.h>

typedef signed long   PRInt32;
typedef unsigned long PR::u32;
typedef signed short    PRInt16;
typedef unsigned short  PR::u3216;
typedef signed char   PRInt8;
typedef unsigned char PR::u328;
typedef unsigned int PR::u32n;
typedef char PRBool;

#define PR_FALSE 0
#define PR_TRUE  1
#define nsnull   nullptr

#define PR_MALLOC memory_allocate
#define PR_FREEIF memory_free


#define NS_ASSERTION(a,b) { if (!(a)) { puts(b); abort(); } }
