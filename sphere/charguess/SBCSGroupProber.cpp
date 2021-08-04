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
#include "SBCSGroupProber.h"
#include "SBCharsetProber.h"


nsSBCSGroupProber::nsSBCSGroupProber()
{
  mProbers[0] = new nsSingleByteCharSetProber(&Win1251Model);
  mProbers[1] = new nsSingleByteCharSetProber(&Koi8rModel);
  mProbers[2] = new nsSingleByteCharSetProber(&Latin5Model);
  mProbers[3] = new nsSingleByteCharSetProber(&MacCyrillicModel);
  mProbers[4] = new nsSingleByteCharSetProber(&Ibm866Model);
  mProbers[5] = new nsSingleByteCharSetProber(&Ibm855Model);
  mProbers[6] = new nsSingleByteCharSetProber(&Latin7Model);
  mProbers[7] = new nsSingleByteCharSetProber(&Win1253Model);
  mProbers[8] = new nsSingleByteCharSetProber(&Latin5BulgarianModel);
  mProbers[9] = new nsSingleByteCharSetProber(&Win1251BulgarianModel);

  // disable latin2 before latin1 is available, otherwise all latin1 
  // will be detected as latin2 because of their similarity.
  //mProbers[10] = new nsSingleByteCharSetProber(&Latin2HungarianModel);
  //mProbers[11] = new nsSingleByteCharSetProber(&Win1250HungarianModel);

  Reset();
}

nsSBCSGroupProber::~nsSBCSGroupProber()
{
  for (PR::u32 i = 0; i < NUM_OF_SBCS_PROBERS; i++)
  {
    delete mProbers[i];
  }
}


const char* nsSBCSGroupProber::GetCharSetName()
{
  //if we have no answer yet
  if (mBestGuess == -1)
  {
    GetConfidence();
    //no charset seems positive
    if (mBestGuess == -1)
      //we will use default.
      mBestGuess = 0;
  }
  return mProbers[mBestGuess]->GetCharSetName();
}

void  nsSBCSGroupProber::Reset(void)
{
  for (PR::u32 i = 0; i < NUM_OF_SBCS_PROBERS; i++)
  {
    mProbers[i]->Reset();
    mIsActive[i] = PR_TRUE;
  }
  mBestGuess = -1;
  mState = eDetecting;
}

//This filter apply to all scripts that does not use latin letters (english letter)
PRBool nsSBCSGroupProber::FilterWithoutEnglishLetters(const ::string & aBuf, PR::u32 aLen, char** newBuf, PR::u32& newLen)
{
  //do filtering to reduce load to probers
  char *newptr;
  char *prevPtr, *curPtr;
  
  PRBool meetMSB = PR_FALSE;   
  newptr = *newBuf = (char*)PR_MALLOC(aLen);
  if (!newptr)
    return PR_FALSE;

  for (curPtr = prevPtr = (char*)aBuf; curPtr < aBuf+aLen; curPtr++)
  {
    if (*curPtr & 0x80)
      meetMSB = PR_TRUE;
    else if (*curPtr < 'A' || (*curPtr > 'Z' && *curPtr < 'a') || *curPtr > 'z') 
    {
      //current char is a symbol, most likely a punctuation. we treat it as segment delimiter
      if (meetMSB && curPtr > prevPtr) 
      //this segment contains more than single symbol, and it has upper ascii, we need to keep it
      {
        while (prevPtr < curPtr) *newptr++ = *prevPtr++;  
        prevPtr++;
        *newptr++ = ' ';
        meetMSB = PR_FALSE;
      }
      else //ignore current segment. (either because it is just a symbol or just a english word
        prevPtr = curPtr+1;
    }
  }

  newLen = (PR::u32)(newptr - *newBuf);

  return PR_TRUE;
}

#ifdef  NO_ENGLISH_CONTAMINATION 
//This filter apply to all scripts that does use latin letters (english letter)
PRBool nsSBCSGroupProber::FilterWithEnglishLetters(const ::string & aBuf, PR::u32 aLen, char** newBuf, PR::u32& newLen)
{
  //do filtering to reduce load to probers
  char *newptr;
  char *prevPtr, *curPtr;
  PRBool isInTag = PR_FALSE;

  newptr = *newBuf = (char*)PR_MALLOC(aLen);
  if (!newptr)
    return PR_FALSE;

  for (curPtr = prevPtr = (char*)aBuf; curPtr < aBuf+aLen; curPtr++)
  {
		if (*curPtr == '>')
			isInTag = PR_FALSE;
    else if (*curPtr == '<')
      isInTag = PR_TRUE;

    if (!(*curPtr & 0x80) &&
        (*curPtr < 'A' || (*curPtr > 'Z' && *curPtr < 'a') || *curPtr > 'z') )
    {
      if (curPtr > prevPtr && !isInTag) //current segment contains more than just a symbol 
                                        // and it is not inside a tag, keep it
      {
        while (prevPtr < curPtr) *newptr++ = *prevPtr++;  
        prevPtr++;
        *newptr++ = ' ';
      }
      else
        prevPtr = curPtr+1;
    }
  }

  newLen = newptr - *newBuf;

  return PR_TRUE;
}
#endif //NO_ENGLISH_CONTAMINATION

nsProbingState nsSBCSGroupProber::HandleData(const ::string & aBuf, PR::u32 aLen)
{
  nsProbingState st;
  PR::u32 i;
  char *newBuf1;
  PR::u32 newLen1;

  //apply filter to original buffer, and we got new buffer back
  //depend on what script it is, we will feed them the new buffer 
  //we got after applying proper filter
  FilterWithoutEnglishLetters(aBuf, aLen, &newBuf1, newLen1);

  for (i = 0; i < NUM_OF_SBCS_PROBERS; i++)
  {
     if (!mIsActive[i])
       continue;
     st = mProbers[i]->HandleData(newBuf1, newLen1);
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

  PR_FREEIF(newBuf1);

  return mState;
}

float nsSBCSGroupProber::GetConfidence(void)
{
  PR::u32 i;
  float bestConf = 0.0, cf;

  switch (mState)
  {
  case eFoundIt:
    return (float)0.99; //sure yes
  case eNotMe:
    return (float)0.01;  //sure no
  default:
    for (i = 0; i < NUM_OF_SBCS_PROBERS; i++)
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
nsSBCSGroupProber::DumpStatus()
{
  PR::u32 i;
  float cf;
  
  cf = GetConfidence();
  printf("SBCS Group Prober --------begin status \r\n");
  for (i = 0; i < NUM_OF_SBCS_PROBERS; i++)
  {
    if (!mIsActive[i])
      printf("[%s] is inactive(ie. cofidence is too low).\r\n", mProbers[i]->GetCharSetName(), i);
    else
      mProbers[i]->DumpStatus();
  }
  printf("SBCS Group found best match [%s] confidence %f.\r\n", 
        mProbers[mBestGuess]->GetCharSetName(), cf);
}
#endif
