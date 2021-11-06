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

#ifndef nsMBCSGroupProber_h__
#define nsMBCSGroupProber_h__

#include "SJISProber.h"
#include "UTF8Prober.h"
#include "EUCJPProber.h"
#include "GB2312Prober.h"
#include "EUCKRProber.h"
#include "big5Prober.h"
#include "EUCTWProber.h"

#define NUM_OF_PROBERS    7

class nsMBCSGroupProber: public nsCharSetProber {
public:
  nsMBCSGroupProber();
  virtual ~nsMBCSGroupProber();
  nsProbingState HandleData(const ::string & aBuf, PR::u32 aLen);
  const char* GetCharSetName();
  nsProbingState GetState(void) {return mState;};
  void      Reset(void);
  float     GetConfidence(void);
  void      SetOpion() {};

#ifdef DEBUG_chardet
  void  DumpStatus();
#endif

protected:
  nsProbingState mState;
  nsCharSetProber* mProbers[NUM_OF_PROBERS];
  PRBool          mIsActive[NUM_OF_PROBERS];
  PRInt32 mBestGuess;
  PR::u32 mActiveNum;
};

#endif /* nsMBCSGroupProber_h__ */

