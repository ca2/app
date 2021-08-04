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

#ifndef nsLatin1Prober_h__
#define nsLatin1Prober_h__

#include "charsetProber.h"

#define FREQ_CAT_NUM    4

class nsLatin1Prober: public nsCharSetProber {
public:
  nsLatin1Prober(void){Reset();};
  virtual ~nsLatin1Prober(void){};
  nsProbingState HandleData(const ::string & aBuf, PR::u32 aLen);
  const char* GetCharSetName() {return "windows-1252";};
  nsProbingState GetState(void) {return mState;};
  void      Reset(void);
  float     GetConfidence(void);
  void      SetOpion() {};

protected:
  PRBool FilterWithEnglishLetters(const ::string & aBuf, PR::u32 aLen, char** newBuf, PR::u32& newLen);
  
  nsProbingState mState;
  char mLastCharClass;
  PR::u32 mFreqCounter[FREQ_CAT_NUM];
};


#endif /* nsLatin1Prober_h__ */

