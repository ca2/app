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
#include "SBCharsetProber.h"


nsProbingState nsSingleByteCharSetProber::HandleData(const char* aBuf, PRUint32 aLen)
{
  unsigned char order;

  for (PRUint32 i = 0; i < aLen; i++)
  {
    order = mModel->charToOrderMap[(unsigned char)aBuf[i]];

    if (order < SYMBOL_CAT_ORDER)
      mTotalChar++;
    if (order < SAMPLE_SIZE)
    {
        mFreqChar++;

      if (mLastOrder < SAMPLE_SIZE)
      {
        mTotalSeqs++;
        ++(mSeqCounters[mModel->precedenceMatrix[mLastOrder*SAMPLE_SIZE+order]]);
      }
    }
    mLastOrder = order;
  }

  if (mState == eDetecting)
    if (mTotalSeqs > SB_ENOUGH_REL_THRESHOLD)
    {
      float cf = GetConfidence();
      if (cf > POSITIVE_SHORTCUT_THRESHOLD)
        mState = eFoundIt;
      else if (cf < NEGATIVE_SHORTCUT_THRESHOLD)
        mState = eNotMe;
    }

  return mState;
}

void  nsSingleByteCharSetProber::Reset(void)
{
  mState = eDetecting;
  mLastOrder = 255;
  for (PRUint32 i = 0; i < NUMBER_OF_SEQ_CAT; i++)
    mSeqCounters[i] = 0;
  mTotalSeqs = 0;
  mTotalChar = 0;
  mFreqChar = 0;
}

//#define NEGATIVE_APPROACH 1

float nsSingleByteCharSetProber::GetConfidence(void)
{
#ifdef NEGATIVE_APPROACH
  if (mTotalSeqs > 0)
    if (mTotalSeqs > mSeqCounters[NEGATIVE_CAT]*10 )
      return ((float)(mTotalSeqs - mSeqCounters[NEGATIVE_CAT]*10))/mTotalSeqs * mFreqChar / mTotalChar;
  return (float)0.01;
#else  //POSITIVE_APPROACH
  float r;

  if (mTotalSeqs > 0) {
    r = ((float)1.0) * mSeqCounters[POSITIVE_CAT] / mTotalSeqs / mModel->mTypicalPositiveRatio;
    r = r*mFreqChar/mTotalChar;
    if (r >= (float)1.00)
      r = (float)0.99;
    return r;
  }
  return (float)0.01;
#endif
}

#ifdef DEBUG_chardet
void 
nsSingleByteCharSetProber::DumpStatus()
{
  printf("[%s] prober has confidence %f\r\n", GetCharSetName(), GetConfidence());
}
#endif
