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
#include "EscCharsetProber.h"


nsEscCharSetProber::nsEscCharSetProber(void)
{
  mCodingSM[0] = new nsCodingStateMachine(&HZSMModel);
  mCodingSM[1] = new nsCodingStateMachine(&ISO2022CNSMModel);
  mCodingSM[2] = new nsCodingStateMachine(&ISO2022JPSMModel);
  mCodingSM[3] = new nsCodingStateMachine(&ISO2022KRSMModel);
  mActiveSM = NUM_OF_ESC_CHARSETS;
  mState = eDetecting;
  mDetectedCharset = nsnull;
};

nsEscCharSetProber::~nsEscCharSetProber(void)
{
  for (PRUint32 i = 0; i < NUM_OF_ESC_CHARSETS; i++)
    delete mCodingSM[i];
}

void nsEscCharSetProber::Reset(void)
{
  mState = eDetecting;
  for (PRUint32 i = 0; i < NUM_OF_ESC_CHARSETS; i++)
    mCodingSM[i]->Reset();
  mActiveSM = NUM_OF_ESC_CHARSETS;
  mDetectedCharset = nsnull;
}

nsProbingState nsEscCharSetProber::HandleData(const char* aBuf, PRUint32 aLen)
{
  nsSMState codingState;
  PRInt32 j;
  PRUint32 i;

  for ( i = 0; i < aLen && mState == eDetecting; i++)
  {
    for (j = mActiveSM-1; j>= 0; j--)
    {
      //byte is feed to all active state machine 
      codingState = mCodingSM[j]->NextState(aBuf[i]);
      if (codingState == eError)
      {
        //got negative answer for this state machine, make it inactive
        mActiveSM--;
        if (mActiveSM == 0)
        {
          mState = eNotMe;
          return mState;
        }
        else if (j != (PRInt32)mActiveSM)
        {
          nsCodingStateMachine* t;
          t = mCodingSM[mActiveSM];
          mCodingSM[mActiveSM] = mCodingSM[j];
          mCodingSM[j] = t;
        }
      }
      else if (codingState == eItsMe)
      {
        mState = eFoundIt;
        mDetectedCharset = mCodingSM[j]->GetCodingStateMachine();
        return mState;
      }
    }
  }

  return mState;
}

