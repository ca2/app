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

#ifndef nsCodingStateMachine_h__
#define nsCodingStateMachine_h__

#include "pkgInt.h"

typedef enum {
   eStart = 0,
   eError = 1,
   eItsMe = 2 
} nsSMState;

#define GETCLASS(c) GETFROMPCK(((unsigned char)(c)), mModel->classTable)

//state machine model
typedef struct 
{
  nsPkgInt classTable;
  PRunsigned int classFactor;
  nsPkgInt stateTable;
  const PRunsigned int* charLenTable;
  const_char_pointer  name;
} SMModel;

class nsCodingStateMachine {
public:
  nsCodingStateMachine(SMModel* sm){
          mCurrentState = eStart;
          mModel = sm;
        };
  nsSMState NextState(char c){
    //for each unsigned char we get its class , if it is first unsigned char, we also get unsigned char length
    PRunsigned int byteCls = GETCLASS(c);
    if (mCurrentState == eStart)
    { 
      mCurrentBytePos = 0; 
      mCurrentCharLen = mModel->charLenTable[byteCls];
    }
    //from unsigned char's class and stateTable, we get its next state
    mCurrentState=(nsSMState)GETFROMPCK(mCurrentState*(mModel->classFactor)+byteCls,
                                       mModel->stateTable);
    mCurrentBytePos++;
    return mCurrentState;
  };
  PRunsigned int  GetCurrentCharLen(void) {return mCurrentCharLen;};
  void      Reset(void) {mCurrentState = eStart;};
  const_char_pointer  GetCodingStateMachine() {return mModel->name;};

protected:
  nsSMState mCurrentState;
  PRunsigned int mCurrentCharLen;
  PRunsigned int mCurrentBytePos;

  SMModel *mModel;
};

extern SMModel UTF8SMModel;
extern SMModel Big5SMModel;
extern SMModel EUCJPSMModel;
extern SMModel EUCKRSMModel;
extern SMModel EUCTWSMModel;
extern SMModel GB18030SMModel;
extern SMModel SJISSMModel;
extern SMModel UCS2BESMModel;


extern SMModel HZSMModel;
extern SMModel ISO2022CNSMModel;
extern SMModel ISO2022JPSMModel;
extern SMModel ISO2022KRSMModel;

#endif /* nsCodingStateMachine_h__ */

