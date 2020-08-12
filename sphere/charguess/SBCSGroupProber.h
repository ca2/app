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

#ifndef nsSBCSGroupProber_h__
#define nsSBCSGroupProber_h__

#include "charsetProber.h"

#define NUM_OF_SBCS_PROBERS    10

class nsSingleByteCharSetProber;
class nsSBCSGroupProber: public nsCharSetProber {
public:
  nsSBCSGroupProber();
  virtual ~nsSBCSGroupProber();
  nsProbingState HandleData(const char* aBuf, PRUint32 aLen);
  PRBool FilterWithoutEnglishLetters(const char* aBuf, PRUint32 aLen, char** newBuf, PRUint32& newLen);
  PRBool FilterWithEnglishLetters(const char* aBuf, PRUint32 aLen, char** newBuf, PRUint32& newLen);
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
  nsSingleByteCharSetProber* mProbers[NUM_OF_SBCS_PROBERS];
  PRBool          mIsActive[NUM_OF_SBCS_PROBERS];
  PRInt32 mBestGuess;
  PRUint32 mActiveNum;
};

#endif /* nsSBCSGroupProber_h__ */

