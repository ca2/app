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

#include "framework.h"
#include "pkgInt.h"
#include "codingStateMachine.h"


static PR::u32 HZ_cls[ 256 / 8 ] = {
PCK4BITS(1,0,0,0,0,0,0,0),  // 00 - 07 
PCK4BITS(0,0,0,0,0,0,0,0),  // 08 - 0f 
PCK4BITS(0,0,0,0,0,0,0,0),  // 10 - 17 
PCK4BITS(0,0,0,1,0,0,0,0),  // 18 - 1f 
PCK4BITS(0,0,0,0,0,0,0,0),  // 20 - 27 
PCK4BITS(0,0,0,0,0,0,0,0),  // 28 - 2f 
PCK4BITS(0,0,0,0,0,0,0,0),  // 30 - 37 
PCK4BITS(0,0,0,0,0,0,0,0),  // 38 - 3f 
PCK4BITS(0,0,0,0,0,0,0,0),  // 40 - 47 
PCK4BITS(0,0,0,0,0,0,0,0),  // 48 - 4f 
PCK4BITS(0,0,0,0,0,0,0,0),  // 50 - 57 
PCK4BITS(0,0,0,0,0,0,0,0),  // 58 - 5f 
PCK4BITS(0,0,0,0,0,0,0,0),  // 60 - 67 
PCK4BITS(0,0,0,0,0,0,0,0),  // 68 - 6f 
PCK4BITS(0,0,0,0,0,0,0,0),  // 70 - 77 
PCK4BITS(0,0,0,4,0,5,2,0),  // 78 - 7f 
PCK4BITS(1,1,1,1,1,1,1,1),  // 80 - 87 
PCK4BITS(1,1,1,1,1,1,1,1),  // 88 - 8f 
PCK4BITS(1,1,1,1,1,1,1,1),  // 90 - 97 
PCK4BITS(1,1,1,1,1,1,1,1),  // 98 - 9f 
PCK4BITS(1,1,1,1,1,1,1,1),  // a0 - a7 
PCK4BITS(1,1,1,1,1,1,1,1),  // a8 - af 
PCK4BITS(1,1,1,1,1,1,1,1),  // b0 - b7 
PCK4BITS(1,1,1,1,1,1,1,1),  // b8 - bf 
PCK4BITS(1,1,1,1,1,1,1,1),  // c0 - c7 
PCK4BITS(1,1,1,1,1,1,1,1),  // c8 - cf 
PCK4BITS(1,1,1,1,1,1,1,1),  // d0 - d7 
PCK4BITS(1,1,1,1,1,1,1,1),  // d8 - df 
PCK4BITS(1,1,1,1,1,1,1,1),  // e0 - e7 
PCK4BITS(1,1,1,1,1,1,1,1),  // e8 - ef 
PCK4BITS(1,1,1,1,1,1,1,1),  // f0 - f7 
PCK4BITS(1,1,1,1,1,1,1,1)   // f8 - ff 
};


static PR::u32 HZ_st [ 6] = {
PCK4BITS(eStart,eError,     3,eStart,eStart,eStart,eError,eError),//00-07 
PCK4BITS(eError,eError,eError,eError,eItsMe,eItsMe,eItsMe,eItsMe),//08-0f 
PCK4BITS(eItsMe,eItsMe,eError,eError,eStart,eStart,     4,eError),//10-17 
PCK4BITS(     5,eError,     6,eError,     5,     5,     4,eError),//18-1f 
PCK4BITS(     4,eError,     4,     4,     4,eError,     4,eError),//20-27 
PCK4BITS(     4,eItsMe,eStart,eStart,eStart,eStart,eStart,eStart) //28-2f 
};

static const PR::u32 HZCharLenTable[] = {0, 0, 0, 0, 0, 0};

SMModel HZSMModel = {
  {eIdxSft4bits, eSftMsk4bits, eBitSft4bits, eUnitMsk4bits, HZ_cls },
   6,
  {eIdxSft4bits, eSftMsk4bits, eBitSft4bits, eUnitMsk4bits, HZ_st },
  HZCharLenTable,
  "HZ-GB-2312",
};


static PR::u32 ISO2022CN_cls [ 256 / 8 ] = {
PCK4BITS(2,0,0,0,0,0,0,0),  // 00 - 07 
PCK4BITS(0,0,0,0,0,0,0,0),  // 08 - 0f 
PCK4BITS(0,0,0,0,0,0,0,0),  // 10 - 17 
PCK4BITS(0,0,0,1,0,0,0,0),  // 18 - 1f 
PCK4BITS(0,0,0,0,0,0,0,0),  // 20 - 27 
PCK4BITS(0,3,0,0,0,0,0,0),  // 28 - 2f 
PCK4BITS(0,0,0,0,0,0,0,0),  // 30 - 37 
PCK4BITS(0,0,0,0,0,0,0,0),  // 38 - 3f 
PCK4BITS(0,0,0,4,0,0,0,0),  // 40 - 47 
PCK4BITS(0,0,0,0,0,0,0,0),  // 48 - 4f 
PCK4BITS(0,0,0,0,0,0,0,0),  // 50 - 57 
PCK4BITS(0,0,0,0,0,0,0,0),  // 58 - 5f 
PCK4BITS(0,0,0,0,0,0,0,0),  // 60 - 67 
PCK4BITS(0,0,0,0,0,0,0,0),  // 68 - 6f 
PCK4BITS(0,0,0,0,0,0,0,0),  // 70 - 77 
PCK4BITS(0,0,0,0,0,0,0,0),  // 78 - 7f 
PCK4BITS(2,2,2,2,2,2,2,2),  // 80 - 87 
PCK4BITS(2,2,2,2,2,2,2,2),  // 88 - 8f 
PCK4BITS(2,2,2,2,2,2,2,2),  // 90 - 97 
PCK4BITS(2,2,2,2,2,2,2,2),  // 98 - 9f 
PCK4BITS(2,2,2,2,2,2,2,2),  // a0 - a7 
PCK4BITS(2,2,2,2,2,2,2,2),  // a8 - af 
PCK4BITS(2,2,2,2,2,2,2,2),  // b0 - b7 
PCK4BITS(2,2,2,2,2,2,2,2),  // b8 - bf 
PCK4BITS(2,2,2,2,2,2,2,2),  // c0 - c7 
PCK4BITS(2,2,2,2,2,2,2,2),  // c8 - cf 
PCK4BITS(2,2,2,2,2,2,2,2),  // d0 - d7 
PCK4BITS(2,2,2,2,2,2,2,2),  // d8 - df 
PCK4BITS(2,2,2,2,2,2,2,2),  // e0 - e7 
PCK4BITS(2,2,2,2,2,2,2,2),  // e8 - ef 
PCK4BITS(2,2,2,2,2,2,2,2),  // f0 - f7 
PCK4BITS(2,2,2,2,2,2,2,2)   // f8 - ff 
};


static PR::u32 ISO2022CN_st [ 8] = {
PCK4BITS(eStart,     3,eError,eStart,eStart,eStart,eStart,eStart),//00-07 
PCK4BITS(eStart,eError,eError,eError,eError,eError,eError,eError),//08-0f 
PCK4BITS(eError,eError,eItsMe,eItsMe,eItsMe,eItsMe,eItsMe,eItsMe),//10-17 
PCK4BITS(eItsMe,eItsMe,eItsMe,eError,eError,eError,     4,eError),//18-1f 
PCK4BITS(eError,eError,eError,eItsMe,eError,eError,eError,eError),//20-27 
PCK4BITS(     5,     6,eError,eError,eError,eError,eError,eError),//28-2f 
PCK4BITS(eError,eError,eError,eItsMe,eError,eError,eError,eError),//30-37 
PCK4BITS(eError,eError,eError,eError,eError,eItsMe,eError,eStart) //38-3f 
};

static const PR::u32 ISO2022CNCharLenTable[] = {0, 0, 0, 0, 0, 0, 0, 0, 0};

SMModel ISO2022CNSMModel = {
  {eIdxSft4bits, eSftMsk4bits, eBitSft4bits, eUnitMsk4bits, ISO2022CN_cls },
  9,
  {eIdxSft4bits, eSftMsk4bits, eBitSft4bits, eUnitMsk4bits, ISO2022CN_st },
  ISO2022CNCharLenTable,
  "ISO-2022-CN",
};

static PR::u32 ISO2022JP_cls [ 256 / 8 ] = {
PCK4BITS(2,0,0,0,0,0,0,0),  // 00 - 07 
PCK4BITS(0,0,0,0,0,0,2,2),  // 08 - 0f 
PCK4BITS(0,0,0,0,0,0,0,0),  // 10 - 17 
PCK4BITS(0,0,0,1,0,0,0,0),  // 18 - 1f 
PCK4BITS(0,0,0,0,7,0,0,0),  // 20 - 27 
PCK4BITS(3,0,0,0,0,0,0,0),  // 28 - 2f 
PCK4BITS(0,0,0,0,0,0,0,0),  // 30 - 37 
PCK4BITS(0,0,0,0,0,0,0,0),  // 38 - 3f 
PCK4BITS(6,0,4,0,0,0,0,0),  // 40 - 47 
PCK4BITS(0,0,5,0,0,0,0,0),  // 48 - 4f 
PCK4BITS(0,0,0,0,0,0,0,0),  // 50 - 57 
PCK4BITS(0,0,0,0,0,0,0,0),  // 58 - 5f 
PCK4BITS(0,0,0,0,0,0,0,0),  // 60 - 67 
PCK4BITS(0,0,0,0,0,0,0,0),  // 68 - 6f 
PCK4BITS(0,0,0,0,0,0,0,0),  // 70 - 77 
PCK4BITS(0,0,0,0,0,0,0,0),  // 78 - 7f 
PCK4BITS(2,2,2,2,2,2,2,2),  // 80 - 87 
PCK4BITS(2,2,2,2,2,2,2,2),  // 88 - 8f 
PCK4BITS(2,2,2,2,2,2,2,2),  // 90 - 97 
PCK4BITS(2,2,2,2,2,2,2,2),  // 98 - 9f 
PCK4BITS(2,2,2,2,2,2,2,2),  // a0 - a7 
PCK4BITS(2,2,2,2,2,2,2,2),  // a8 - af 
PCK4BITS(2,2,2,2,2,2,2,2),  // b0 - b7 
PCK4BITS(2,2,2,2,2,2,2,2),  // b8 - bf 
PCK4BITS(2,2,2,2,2,2,2,2),  // c0 - c7 
PCK4BITS(2,2,2,2,2,2,2,2),  // c8 - cf 
PCK4BITS(2,2,2,2,2,2,2,2),  // d0 - d7 
PCK4BITS(2,2,2,2,2,2,2,2),  // d8 - df 
PCK4BITS(2,2,2,2,2,2,2,2),  // e0 - e7 
PCK4BITS(2,2,2,2,2,2,2,2),  // e8 - ef 
PCK4BITS(2,2,2,2,2,2,2,2),  // f0 - f7 
PCK4BITS(2,2,2,2,2,2,2,2)   // f8 - ff 
};


static PR::u32 ISO2022JP_st [ 6] = {
PCK4BITS(eStart,     3,eError,eStart,eStart,eStart,eStart,eStart),//00-07 
PCK4BITS(eError,eError,eError,eError,eError,eError,eError,eError),//08-0f 
PCK4BITS(eItsMe,eItsMe,eItsMe,eItsMe,eItsMe,eItsMe,eItsMe,eItsMe),//10-17 
PCK4BITS(eError,eError,eError,     5,eError,eError,eError,     4),//18-1f 
PCK4BITS(eError,eError,eError,eError,eItsMe,eError,eItsMe,eError),//20-27 
PCK4BITS(eError,eError,eError,eError,eItsMe,eItsMe,eError,eError) //28-2f 
};

static const PR::u32 ISO2022JPCharLenTable[] = {0, 0, 0, 0, 0, 0, 0, 0};

SMModel ISO2022JPSMModel = {
  {eIdxSft4bits, eSftMsk4bits, eBitSft4bits, eUnitMsk4bits, ISO2022JP_cls },
  8,
  {eIdxSft4bits, eSftMsk4bits, eBitSft4bits, eUnitMsk4bits, ISO2022JP_st },
  ISO2022JPCharLenTable,
  "ISO-2022-JP",
};

static PR::u32 ISO2022KR_cls [ 256 / 8 ] = {
PCK4BITS(2,0,0,0,0,0,0,0),  // 00 - 07 
PCK4BITS(0,0,0,0,0,0,0,0),  // 08 - 0f 
PCK4BITS(0,0,0,0,0,0,0,0),  // 10 - 17 
PCK4BITS(0,0,0,1,0,0,0,0),  // 18 - 1f 
PCK4BITS(0,0,0,0,3,0,0,0),  // 20 - 27 
PCK4BITS(0,4,0,0,0,0,0,0),  // 28 - 2f 
PCK4BITS(0,0,0,0,0,0,0,0),  // 30 - 37 
PCK4BITS(0,0,0,0,0,0,0,0),  // 38 - 3f 
PCK4BITS(0,0,0,5,0,0,0,0),  // 40 - 47 
PCK4BITS(0,0,0,0,0,0,0,0),  // 48 - 4f 
PCK4BITS(0,0,0,0,0,0,0,0),  // 50 - 57 
PCK4BITS(0,0,0,0,0,0,0,0),  // 58 - 5f 
PCK4BITS(0,0,0,0,0,0,0,0),  // 60 - 67 
PCK4BITS(0,0,0,0,0,0,0,0),  // 68 - 6f 
PCK4BITS(0,0,0,0,0,0,0,0),  // 70 - 77 
PCK4BITS(0,0,0,0,0,0,0,0),  // 78 - 7f 
PCK4BITS(2,2,2,2,2,2,2,2),  // 80 - 87 
PCK4BITS(2,2,2,2,2,2,2,2),  // 88 - 8f 
PCK4BITS(2,2,2,2,2,2,2,2),  // 90 - 97 
PCK4BITS(2,2,2,2,2,2,2,2),  // 98 - 9f 
PCK4BITS(2,2,2,2,2,2,2,2),  // a0 - a7 
PCK4BITS(2,2,2,2,2,2,2,2),  // a8 - af 
PCK4BITS(2,2,2,2,2,2,2,2),  // b0 - b7 
PCK4BITS(2,2,2,2,2,2,2,2),  // b8 - bf 
PCK4BITS(2,2,2,2,2,2,2,2),  // c0 - c7 
PCK4BITS(2,2,2,2,2,2,2,2),  // c8 - cf 
PCK4BITS(2,2,2,2,2,2,2,2),  // d0 - d7 
PCK4BITS(2,2,2,2,2,2,2,2),  // d8 - df 
PCK4BITS(2,2,2,2,2,2,2,2),  // e0 - e7 
PCK4BITS(2,2,2,2,2,2,2,2),  // e8 - ef 
PCK4BITS(2,2,2,2,2,2,2,2),  // f0 - f7 
PCK4BITS(2,2,2,2,2,2,2,2)   // f8 - ff 
};


static PR::u32 ISO2022KR_st [ 5] = {
PCK4BITS(eStart,     3,eError,eStart,eStart,eStart,eError,eError),//00-07 
PCK4BITS(eError,eError,eError,eError,eItsMe,eItsMe,eItsMe,eItsMe),//08-0f 
PCK4BITS(eItsMe,eItsMe,eError,eError,eError,     4,eError,eError),//10-17 
PCK4BITS(eError,eError,eError,eError,     5,eError,eError,eError),//18-1f 
PCK4BITS(eError,eError,eError,eItsMe,eStart,eStart,eStart,eStart) //20-27 
};

static const PR::u32 ISO2022KRCharLenTable[] = {0, 0, 0, 0, 0, 0};

SMModel ISO2022KRSMModel = {
  {eIdxSft4bits, eSftMsk4bits, eBitSft4bits, eUnitMsk4bits, ISO2022KR_cls },
   6,
  {eIdxSft4bits, eSftMsk4bits, eBitSft4bits, eUnitMsk4bits, ISO2022KR_st },
  ISO2022KRCharLenTable,
  "ISO-2022-KR",
};

