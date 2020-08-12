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

#ifndef nsPkgInt_h__
#define nsPkgInt_h__
#include "types.h"

typedef enum {
  eIdxSft4bits  = 3,
  eIdxSft8bits  = 2,
  eIdxSft16bits = 1
} nsIdxSft; 

typedef enum {
  eSftMsk4bits  = 7,
  eSftMsk8bits  = 3,
  eSftMsk16bits = 1
} nsSftMsk; 

typedef enum {
  eBitSft4bits  = 2,
  eBitSft8bits  = 3,
  eBitSft16bits = 4
} nsBitSft; 

typedef enum {
  eUnitMsk4bits  = 0x0000000FL,
  eUnitMsk8bits  = 0x000000FFL,
  eUnitMsk16bits = 0x0000FFFFL
} nsUnitMsk; 

typedef struct nsPkgInt {
  nsIdxSft  idxsft;
  nsSftMsk  sftmsk;
  nsBitSft  bitsft;
  nsUnitMsk unitmsk;
  PRUint32  *data;
} nsPkgInt;


#define PCK16BITS(a,b)            ((PRUint32)(((b) << 16) | (a)))

#define PCK8BITS(a,b,c,d)         PCK16BITS( ((PRUint32)(((b) << 8) | (a))),  \
                                             ((PRUint32)(((d) << 8) | (c))))

#define PCK4BITS(a,b,c,d,e,f,g,h) PCK8BITS(  ((PRUint32)(((b) << 4) | (a))), \
                                             ((PRUint32)(((d) << 4) | (c))), \
                                             ((PRUint32)(((f) << 4) | (e))), \
                                             ((PRUint32)(((h) << 4) | (g))) )

#define GETFROMPCK(i, c) \
 (((((c).data)[(i)>>(c).idxsft])>>(((i)&(c).sftmsk)<<(c).bitsft))&(c).unitmsk)

#endif /* nsPkgInt_h__ */

