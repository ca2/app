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

// for S-JIS encoding, obeserve characteristic:
// 1, kana character (or hankaku?) often have hight frequency of appereance
// 2, kana character often exist in group
// 3, certain combination of kana is never used in japanese language

#ifndef nsEUCJPProber_h__
#define nsEUCJPProber_h__

#include "charsetProber.h"
#include "codingStateMachine.h"
#include "jpCntx.h"
#include "charDistribution.h"

class nsEUCJPProber: public nsCharSetProber {
public:
  nsEUCJPProber(void){mCodingSM = ___new nsCodingStateMachine(&EUCJPSMModel);
                      Reset();};
  virtual ~nsEUCJPProber(void){delete mCodingSM;};
  nsProbingState HandleData(const ::string & aBuf, PRunsigned int aLen);
  const_char_pointer GetCharSetName() {return "EUC-JP";};
  nsProbingState GetState(void) {return mState;};
  void      Reset(void);
  float     GetConfidence(void);
  void      SetOpion() {};

protected:
  nsCodingStateMachine* mCodingSM;
  nsProbingState mState;

  EUCJPContextAnalysis mContextAnalyser;
  EUCJPDistributionAnalysis mDistributionAnalyser;

  char mLastChar[2];
};


#endif /* nsEUCJPProber_h__ */

