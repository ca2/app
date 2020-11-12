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
#include "big5Prober.h"


void  nsBig5Prober::Reset(void)
{
  mCodingSM->Reset(); 
  mState = eDetecting;
  mDistributionAnalyser.Reset();
}

nsProbingState nsBig5Prober::HandleData(const char* aBuf, PR::u32 aLen)
{
  nsSMState codingState;

  for (PR::u32 i = 0; i < aLen; i++)
  {
    codingState = mCodingSM->NextState(aBuf[i]);
    if (codingState == eError)
    {
      mState = eNotMe;
      break;
    }
    if (codingState == eItsMe)
    {
      mState = eFoundIt;
      break;
    }
    if (codingState == eStart)
    {
      PR::u32 charLen = mCodingSM->GetCurrentCharLen();

      if (i == 0)
      {
        mLastChar[1] = aBuf[0];
        mDistributionAnalyser.HandleOneChar(mLastChar, charLen);
      }
      else
        mDistributionAnalyser.HandleOneChar(aBuf+i-1, charLen);
    }
  }

  mLastChar[0] = aBuf[aLen-1];

  if (mState == eDetecting)
    if (mDistributionAnalyser.GotEnoughData() && GetConfidence() > SHORTCUT_THRESHOLD)
      mState = eFoundIt;

  return mState;
}

float nsBig5Prober::GetConfidence(void)
{
  float distribCf = mDistributionAnalyser.GetConfidence();

  return (float)distribCf;
}

