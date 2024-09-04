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
#include "MBCSGroupProber.h"

#ifdef DEBUG_chardet
char *ProberName[] = 
{
  "UTF8",
  "SJIS",
  "EUCJP",
  "GB18030",
  "EUCKR",
  "Big5",
  "EUCTW",
};

#endif

nsMBCSGroupProber::nsMBCSGroupProber()
{
  mProbers[0] = new nsUTF8Prober();
  mProbers[1] = new nsSJISProber();
  mProbers[2] = new nsEUCJPProber();
  mProbers[3] = new nsGB18030Prober();
  mProbers[4] = new nsEUCKRProber();
  mProbers[5] = new nsBig5Prober();
  mProbers[6] = new nsEUCTWProber();
  Reset();
}

nsMBCSGroupProber::~nsMBCSGroupProber()
{
  for (PR::u32 i = 0; i < NUM_OF_PROBERS; i++)
  {
    delete mProbers[i];
  }
}

const char* nsMBCSGroupProber::GetCharSetName()
{
  if (mBestGuess == -1)
  {
    GetConfidence();
    if (mBestGuess == -1)
      mBestGuess = 0;
  }
  return mProbers[mBestGuess]->GetCharSetName();
}

void  nsMBCSGroupProber::Reset(void)
{
  for (PR::u32 i = 0; i < NUM_OF_PROBERS; i++)
  {
    mProbers[i]->Reset();
    mIsActive[i] = PR_TRUE;
  }
  mActiveNum = NUM_OF_PROBERS;
  mBestGuess = -1;
  mState = eDetecting;
}

nsProbingState nsMBCSGroupProber::HandleData(const ::string & aBuf, PR::u32 aLen)
{
  nsProbingState st;
  PR::u32 i;

  //do filtering to reduce load to probers
  char *highbyteBuf;
  char *hptr;
  PRBool keepNext = PR_TRUE;   //assume previous is not ascii, it will do not harm except add some noise
  hptr = highbyteBuf = (char*)PR_MALLOC(aLen);
  for (i = 0; i < aLen; i++)
  {
    if (aBuf[i] & 0x80)
    {
      *hptr++ = aBuf[i];
      keepNext = PR_TRUE;
    }
    else
    {
      //if previous is highbyte, keep this even it is a ASCII
      if (keepNext)
      {
          *hptr++ = aBuf[i];
          keepNext = PR_FALSE;
      }
    }
  }

  for (i = 0; i < NUM_OF_PROBERS; i++)
  {
     if (!mIsActive[i])
       continue;
     st = mProbers[i]->HandleData(highbyteBuf, (PR::u32)(hptr - highbyteBuf));
     if (st == eFoundIt)
     {
       mBestGuess = i;
       mState = eFoundIt;
       break;
     }
     else if (st == eNotMe)
     {
       mIsActive[i] = PR_FALSE;
       mActiveNum--;
       if (mActiveNum <= 0)
       {
         mState = eNotMe;
         break;
       }
     }
  }

  PR_FREEIF(highbyteBuf);

  return mState;
}

float nsMBCSGroupProber::GetConfidence(void)
{
  PR::u32 i;
  float bestConf = 0.0, cf;

  switch (mState)
  {
  case eFoundIt:
    return (float)0.99;
  case eNotMe:
    return (float)0.01;
  default:
    for (i = 0; i < NUM_OF_PROBERS; i++)
    {
      if (!mIsActive[i])
        continue;
      cf = mProbers[i]->GetConfidence();
      if (bestConf < cf)
      {
        bestConf = cf;
        mBestGuess = i;
      }
    }
  }
  return bestConf;
}

#ifdef DEBUG_chardet
void 
nsMBCSGroupProber::DumpStatus()
{
  PR::u32 i;
  float cf;
  
  GetConfidence();
  for (i = 0; i < NUM_OF_PROBERS; i++)
  {
    if (!mIsActive[i])
      printf("[%s] is inactive(ie. cofidence is too low).\r\n", ProberName[i]);
    else
    {
      cf = mProbers[i]->GetConfidence();
      printf("[%s] prober has confidence %f\r\n", ProberName[i], cf);
    }
  }
}
#endif
