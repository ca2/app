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
#include "Latin1Prober.h"

#define UDF    0        // undefined
#define OTH    1        //other
#define ASC    2        // ascii capital letter
#define ASS    3        // ascii small letter
#define ACV    4        // accent capital vowel
#define ACO    5        // accent capital other
#define ASV    6        // accent small vowel
#define ASO    7        // accent small other
#define CLASS_NUM   8    // total classes

static unsigned char Latin1_CharToClass[] = 
{
  OTH, OTH, OTH, OTH, OTH, OTH, OTH, OTH,   // 00 - 07
  OTH, OTH, OTH, OTH, OTH, OTH, OTH, OTH,   // 08 - 0F
  OTH, OTH, OTH, OTH, OTH, OTH, OTH, OTH,   // 10 - 17
  OTH, OTH, OTH, OTH, OTH, OTH, OTH, OTH,   // 18 - 1F
  OTH, OTH, OTH, OTH, OTH, OTH, OTH, OTH,   // 20 - 27
  OTH, OTH, OTH, OTH, OTH, OTH, OTH, OTH,   // 28 - 2F
  OTH, OTH, OTH, OTH, OTH, OTH, OTH, OTH,   // 30 - 37
  OTH, OTH, OTH, OTH, OTH, OTH, OTH, OTH,   // 38 - 3F
  OTH, ASC, ASC, ASC, ASC, ASC, ASC, ASC,   // 40 - 47
  ASC, ASC, ASC, ASC, ASC, ASC, ASC, ASC,   // 48 - 4F
  ASC, ASC, ASC, ASC, ASC, ASC, ASC, ASC,   // 50 - 57
  ASC, ASC, ASC, OTH, OTH, OTH, OTH, OTH,   // 58 - 5F
  OTH, ASS, ASS, ASS, ASS, ASS, ASS, ASS,   // 60 - 67
  ASS, ASS, ASS, ASS, ASS, ASS, ASS, ASS,   // 68 - 6F
  ASS, ASS, ASS, ASS, ASS, ASS, ASS, ASS,   // 70 - 77
  ASS, ASS, ASS, OTH, OTH, OTH, OTH, OTH,   // 78 - 7F
  OTH, UDF, OTH, ASO, OTH, OTH, OTH, OTH,   // 80 - 87
  OTH, OTH, ACO, OTH, ACO, UDF, ACO, UDF,   // 88 - 8F
  UDF, OTH, OTH, OTH, OTH, OTH, OTH, OTH,   // 90 - 97
  OTH, OTH, ASO, OTH, ASO, UDF, ASO, ACO,   // 98 - 9F
  OTH, OTH, OTH, OTH, OTH, OTH, OTH, OTH,   // A0 - A7
  OTH, OTH, OTH, OTH, OTH, OTH, OTH, OTH,   // A8 - AF
  OTH, OTH, OTH, OTH, OTH, OTH, OTH, OTH,   // B0 - B7
  OTH, OTH, OTH, OTH, OTH, OTH, OTH, OTH,   // B8 - BF
  ACV, ACV, ACV, ACV, ACV, ACV, ACO, ACO,   // C0 - C7
  ACV, ACV, ACV, ACV, ACV, ACV, ACV, ACV,   // C8 - CF
  ACO, ACO, ACV, ACV, ACV, ACV, ACV, OTH,   // D0 - D7
  ACV, ACV, ACV, ACV, ACV, ACO, ACO, ACO,   // D8 - DF
  ASV, ASV, ASV, ASV, ASV, ASV, ASO, ASO,   // E0 - E7
  ASV, ASV, ASV, ASV, ASV, ASV, ASV, ASV,   // E8 - EF
  ASO, ASO, ASV, ASV, ASV, ASV, ASV, OTH,   // F0 - F7
  ASV, ASV, ASV, ASV, ASV, ASO, ASO, ASO,   // F8 - FF
};


/* 0 : illegal 
   1 : very unlikely 
   2 : normal 
   3 : very likely
*/
static unsigned char Latin1ClassModel[] = 
{
/*      UDF OTH ASC ASS ACV ACO ASV ASO  */
/*UDF*/  0,  0,  0,  0,  0,  0,  0,  0,
/*OTH*/  0,  3,  3,  3,  3,  3,  3,  3,
/*ASC*/  0,  3,  3,  3,  3,  3,  3,  3, 
/*ASS*/  0,  3,  3,  3,  1,  1,  3,  3,
/*ACV*/  0,  3,  3,  3,  1,  2,  1,  2,
/*ACO*/  0,  3,  3,  3,  3,  3,  3,  3, 
/*ASV*/  0,  3,  1,  3,  1,  1,  1,  3, 
/*ASO*/  0,  3,  1,  3,  1,  1,  3,  3,
};

void  nsLatin1Prober::Reset(void)
{
  mState = eDetecting;
  mLastCharClass = OTH;
  for (int i = 0; i < FREQ_CAT_NUM; i++)
    mFreqCounter[i] = 0;
}

PRBool nsLatin1Prober::FilterWithEnglishLetters(const ::string & aBuf, PR::u32 aLen, char** newBuf, PR::u32& newLen)
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
/*
    if (*curPtr == '>')
      isInTag = PR_FALSE;
    else if (*curPtr == '<')
      isInTag = PR_TRUE;
*/

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

  newLen = (PR::u32) (newptr - *newBuf);

  return PR_TRUE;
}


nsProbingState nsLatin1Prober::HandleData(const ::string & aBuf, PR::u32 aLen)
{
  char *newBuf1;
  PR::u32 newLen1;

  if (!FilterWithEnglishLetters(aBuf, aLen, &newBuf1, newLen1)) {
    newBuf1 = (char*)aBuf;
    newLen1 = aLen;
  }
  
  unsigned char charClass;
  unsigned char freq;
  for (PR::u32 i = 0; i < newLen1; i++)
  {
    charClass = Latin1_CharToClass[(unsigned char)newBuf1[i]];
    freq = Latin1ClassModel[mLastCharClass*CLASS_NUM + charClass];
    if (freq == 0) {
      mState = eNotMe;
      break;
    }
    mFreqCounter[freq]++;
    mLastCharClass = charClass;
  }

  if (newBuf1 != aBuf)
    PR_FREEIF(newBuf1);

  return mState;
}

float nsLatin1Prober::GetConfidence(void)
{
  if (mState == eNotMe)
    return 0.01f;
  
  float confidence;
  PR::u32 total = 0;
  for (PRInt32 i = 0; i < FREQ_CAT_NUM; i++)
    total += mFreqCounter[i];

  confidence = mFreqCounter[3]*1.0f / total;
  confidence -= mFreqCounter[1]*20.0f/total;

  if (confidence < 0.0f)
    confidence = 0.0f;
  
  // lower the confidence of latin1 so that other more accurate detector 
  // can take priority.
  confidence *= 0.50f;

  return confidence;
}

