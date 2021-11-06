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

#ifndef nsEUCTWProber_h__
#define nsEUCTWProber_h__

#include "charsetProber.h"
#include "codingStateMachine.h"
#include "charDistribution.h"

class nsEUCTWProber: public nsCharSetProber {
public:
  nsEUCTWProber(void){mCodingSM = new nsCodingStateMachine(&EUCTWSMModel);
                      Reset();};
  virtual ~nsEUCTWProber(void){delete mCodingSM;};
  nsProbingState HandleData(const ::string & aBuf, PR::u32 aLen);
  const char* GetCharSetName() {return "x-euc-tw";};
  nsProbingState GetState(void) {return mState;};
  void      Reset(void);
  float     GetConfidence(void);
  void      SetOpion() {};

protected:
  void      GetDistribution(PR::u32 aCharLen, const ::string & aStr);
  
  nsCodingStateMachine* mCodingSM;
  nsProbingState mState;

  //EUCTWContextAnalysis mContextAnalyser;
  EUCTWDistributionAnalysis mDistributionAnalyser;
  char mLastChar[2];

};


#endif /* nsEUCTWProber_h__ */
