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
#include "universal.h"
#include "SBCharsetProber.h"
#include "MBCSGroupProber.h"
#include "SBCSGroupProber.h"
#include "Latin1Prober.h"
#include "EscCharsetProber.h"


nsUniversalDetector::nsUniversalDetector()
{
  mDone = PR_FALSE;
  mBestGuess = -1;   //illegal value as signal
  mInTag = PR_FALSE;
  mEscCharSetProber = nsnull;

  mStart = PR_TRUE;
  mDetectedCharset = nsnull;
  mGotData = PR_FALSE;
  mInputState = ePureAscii;
  mLastChar = '\0';

  PR::u32 i;
  for (i = 0; i < NUM_OF_CHARSET_PROBERS; i++)
    mCharSetProbers[i] = nsnull;
}

nsUniversalDetector::~nsUniversalDetector() 
{
  for (PRInt32 i = 0; i < NUM_OF_CHARSET_PROBERS; i++)
    if (mCharSetProbers[i])      
      delete mCharSetProbers[i];
  if (mEscCharSetProber)
    delete mEscCharSetProber;
}

void nsUniversalDetector::Reset()
{
  mDone = PR_FALSE;
  mBestGuess = -1;   //illegal value as signal
  mInTag = PR_FALSE;

  mStart = PR_TRUE;
  mDetectedCharset = nsnull;
  mGotData = PR_FALSE;
  mInputState = ePureAscii;
  mLastChar = '\0';

  if (mEscCharSetProber)
    mEscCharSetProber->Reset();

  PR::u32 i;
  for (i = 0; i < NUM_OF_CHARSET_PROBERS; i++)
    if (mCharSetProbers[i])
      mCharSetProbers[i]->Reset();
}

//---------------------------------------------------------------------
#define SHORTCUT_THRESHOLD      (float)0.95
#define MINIMUM_THRESHOLD      (float)0.20

void nsUniversalDetector::HandleData(const ::string & aBuf, PR::u32 aLen)
{
  if(mDone) 
    return;

  if (aLen > 0)
    mGotData = PR_TRUE;

  //If the data starts with BOM, we know it is UTF
  if (mStart)
  {
    mStart = PR_FALSE;
    if (aLen > 3)
      switch (aBuf[0])
        {
        case '\xEF':
          if (('\xBB' == aBuf[1]) && ('\xBF' == aBuf[2]))
            // EF BB BF  UTF-8 encoded BOM
            mDetectedCharset = "UTF-8";
        break;
        case '\xFE':
          if (('\xFF' == aBuf[1]) && ('\x00' == aBuf[2]) && ('\x00' == aBuf[3]))
            // FE FF 00 00  UCS-4, unusual octet order BOM (3412)
            mDetectedCharset = "X-ISO-10646-UCS-4-3412";
          else if ('\xFF' == aBuf[1])
            // FE FF  UTF-16, big endian BOM
            mDetectedCharset = "UTF-16BE";
        break;
        case '\x00':
          if (('\x00' == aBuf[1]) && ('\xFE' == aBuf[2]) && ('\xFF' == aBuf[3]))
            // 00 00 FE FF  UTF-32, big-endian BOM
            mDetectedCharset = "UTF-32BE";
          else if (('\x00' == aBuf[1]) && ('\xFF' == aBuf[2]) && ('\xFE' == aBuf[3]))
            // 00 00 FF FE  UCS-4, unusual octet order BOM (2143)
            mDetectedCharset = "X-ISO-10646-UCS-4-2143";
        break;
        case '\xFF':
          if (('\xFE' == aBuf[1]) && ('\x00' == aBuf[2]) && ('\x00' == aBuf[3]))
            // FF FE 00 00  UTF-32, little-endian BOM
            mDetectedCharset = "UTF-32LE";
          else if ('\xFE' == aBuf[1])
            // FF FE  UTF-16, little endian BOM
            mDetectedCharset = "UTF-16LE";
        break;
      }  // switch

      if (mDetectedCharset)
      {
        mDone = PR_TRUE;
        return;
      }
  }
  
  PR::u32 i;
  for (i = 0; i < aLen; i++)
  {
    //other than 0xa0, if every othe character is ascii, the page is ascii
    if (aBuf[i] & '\x80' && aBuf[i] != '\xA0')  //Since many Ascii only page contains NBSP 
    {
      //we got a non-ascii byte (high-byte)
      if (mInputState != eHighbyte)
      {
        //adjust state
        mInputState = eHighbyte;

        //kill mEscCharSetProber if it is active
        if (mEscCharSetProber) {
          delete mEscCharSetProber;
          mEscCharSetProber = nsnull;
        }

        //start multibyte and singlebyte charset prober
        if (nsnull == mCharSetProbers[0])
          mCharSetProbers[0] = new nsMBCSGroupProber;
        if (nsnull == mCharSetProbers[1])
          mCharSetProbers[1] = new nsSBCSGroupProber;
        if (nsnull == mCharSetProbers[2])
          mCharSetProbers[2] = new nsLatin1Prober; 
      }
    }
    else
    {
      //ok, just pure ascii so far
      if ( ePureAscii == mInputState &&
        (aBuf[i] == '\033' || (aBuf[i] == '{' && mLastChar == '~')) )
      {
        //found escape character or HZ "~{"
        mInputState = eEscAscii;
      }
      mLastChar = aBuf[i];
    }
  }

  nsProbingState st;
  switch (mInputState)
  {
  case eEscAscii:
    if (nsnull == mEscCharSetProber)
      mEscCharSetProber = new nsEscCharSetProber;
    st = mEscCharSetProber->HandleData(aBuf, aLen);
    if (st == eFoundIt)
    {
      mDone = PR_TRUE;
      mDetectedCharset = mEscCharSetProber->GetCharSetName();
    }
    break;
  case eHighbyte:
    for (i = 0; i < NUM_OF_CHARSET_PROBERS; i++)
    {
      st = mCharSetProbers[i]->HandleData(aBuf, aLen);
      if (st == eFoundIt) 
      {
        mDone = PR_TRUE;
        mDetectedCharset = mCharSetProbers[i]->GetCharSetName();
        return;
      } 
    }
    break;

  default:  //pure ascii
    ;//do nothing here
  }
  return ;  
}


//---------------------------------------------------------------------
void nsUniversalDetector::DataEnd()
{
  if (!mGotData)
  {
    // we haven't got any data yet, return immediately 
    // caller program sometimes call DataEnd before anything has been sent to detector
    return;
  }

  if (mDetectedCharset)
  {
    mDone = PR_TRUE;
    Report(mDetectedCharset);
    return;
  }
  
  switch (mInputState)
  {
  case eHighbyte:
    {
      float proberConfidence;
      float maxProberConfidence = (float)0.0;
      PRInt32 maxProber = 0;

      for (PRInt32 i = 0; i < NUM_OF_CHARSET_PROBERS; i++)
      {
        proberConfidence = mCharSetProbers[i]->GetConfidence();
#ifdef DEBUG_chardet
        mCharSetProbers[i]->DumpStatus();
#endif

        if (proberConfidence > maxProberConfidence)
        {
          maxProberConfidence = proberConfidence;
          maxProber = i;
        }
      }
      //do not report anything because we are not confident of it, that's in fact a negative answer
      if (maxProberConfidence > MINIMUM_THRESHOLD)
        Report(mCharSetProbers[maxProber]->GetCharSetName());
    }
    break;
  case eEscAscii:
    break;
  default:
    ;
  }
  return;
}


void nsUniversalDetector::Report(const ::string & aCharset)
{
	if (!mDone)
	{
		mDone = PR_TRUE;
		mDetectedCharset = aCharset;
	}
}

const char* nsUniversalDetector::GetCharset(void)
{
	if (mDone == PR_TRUE)
		return (mDetectedCharset);
	else
		return nullptr;
}
