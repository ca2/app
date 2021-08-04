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

#ifndef CharDistribution_h__
#define CharDistribution_h__

#include "types.h"

#define ENOUGH_DATA_THRESHOLD 1024
 
class CharDistributionAnalysis
{
public:
  CharDistributionAnalysis() {Reset();};

  //feed a block of data and do distribution analysis
  void HandleData(const ::string & aBuf, PR::u32 aLen) {};
  
  //Feed a character with known length
  void HandleOneChar(const ::string & aStr, PR::u32 aCharLen)
  {
    PRInt32 order;

    //we only care about 2-bytes character in our distribution analysis
    order = (aCharLen == 2) ? GetOrder(aStr) : -1;

    if (order >= 0)
    {
      mTotalChars++;
      //order is valid
      if ((PR::u32)order < mTableSize)
      {
        if (512 > mCharToFreqOrder[order])
          mFreqChars++;
      }
    }
  };

  //return confidence base on existing data
  float GetConfidence();

  //Reset analyser, clear any state 
  void      Reset(void) 
  {
    mDone = PR_FALSE;
    mTotalChars = 0;
    mFreqChars = 0;
  };

  //This function is for future extension. Caller can use this function to control
  //analyser's behavior
  void      SetOpion(){};

  //It is not necessary to receive all data to draw conclusion. For charset detection,
  // certain amount of data is enough
  PRBool GotEnoughData() {return mTotalChars > ENOUGH_DATA_THRESHOLD;};

protected:
  //we do not handle character base on its original encoding string, but 
  //convert this encoding string to a number, here called order.
  //This allow multiple encoding of a language to share one frequency table 
  virtual PRInt32 GetOrder(const ::string & str) {return -1;};
  
  //If this flag is set to PR_TRUE, detection is done and conclusion has been made
  PRBool   mDone;

  //The number of characters whose frequency order is less than 512
  PR::u32 mFreqChars;

  //Total character encounted.
  PR::u32 mTotalChars;

  //Mapping table to get frequency order from char order (get from GetOrder())
  const PRInt16  *mCharToFreqOrder;

  //Size of above table
  PR::u32 mTableSize;

  //This is a constant value varies from language to language, it is used in 
  //calculating confidence. See my paper for further detail.
  float    mTypicalDistributionRatio;
};


class EUCTWDistributionAnalysis: public CharDistributionAnalysis
{
public:
  EUCTWDistributionAnalysis();
protected:

  //for euc-TW encoding, we are interested 
  //  first  byte range: 0xc4 -- 0xfe
  //  second byte range: 0xa1 -- 0xfe
  //no validation needed here. State machine has done that
  PRInt32 GetOrder(const ::string & str) 
  { if ((unsigned char)*str >= (unsigned char)0xc4)  
      return 94*((unsigned char)str[0]-(unsigned char)0xc4) + (unsigned char)str[1] - (unsigned char)0xa1;
    else
      return -1;
  };
};


class EUCKRDistributionAnalysis : public CharDistributionAnalysis
{
public:
  EUCKRDistributionAnalysis();
protected:
  //for euc-KR encoding, we are interested 
  //  first  byte range: 0xb0 -- 0xfe
  //  second byte range: 0xa1 -- 0xfe
  //no validation needed here. State machine has done that
  PRInt32 GetOrder(const ::string & str) 
  { if ((unsigned char)*str >= (unsigned char)0xb0)  
      return 94*((unsigned char)str[0]-(unsigned char)0xb0) + (unsigned char)str[1] - (unsigned char)0xa1;
    else
      return -1;
  };
};

class GB2312DistributionAnalysis : public CharDistributionAnalysis
{
public:
  GB2312DistributionAnalysis();
protected:
  //for GB2312 encoding, we are interested 
  //  first  byte range: 0xb0 -- 0xfe
  //  second byte range: 0xa1 -- 0xfe
  //no validation needed here. State machine has done that
  PRInt32 GetOrder(const ::string & str) 
  { if ((unsigned char)*str >= (unsigned char)0xb0 && (unsigned char)str[1] >= (unsigned char)0xa1)  
      return 94*((unsigned char)str[0]-(unsigned char)0xb0) + (unsigned char)str[1] - (unsigned char)0xa1;
    else
      return -1;
  };
};


class Big5DistributionAnalysis : public CharDistributionAnalysis
{
public:
  Big5DistributionAnalysis();
protected:
  //for big5 encoding, we are interested 
  //  first  byte range: 0xa4 -- 0xfe
  //  second byte range: 0x40 -- 0x7e , 0xa1 -- 0xfe
  //no validation needed here. State machine has done that
  PRInt32 GetOrder(const ::string & str) 
  { if ((unsigned char)*str >= (unsigned char)0xa4)  
      if ((unsigned char)str[1] >= (unsigned char)0xa1)
        return 157*((unsigned char)str[0]-(unsigned char)0xa4) + (unsigned char)str[1] - (unsigned char)0xa1 +63;
      else
        return 157*((unsigned char)str[0]-(unsigned char)0xa4) + (unsigned char)str[1] - (unsigned char)0x40;
    else
      return -1;
  };
};

class SJISDistributionAnalysis : public CharDistributionAnalysis
{
public:
  SJISDistributionAnalysis();
protected:
  //for sjis encoding, we are interested 
  //  first  byte range: 0x81 -- 0x9f , 0xe0 -- 0xfe
  //  second byte range: 0x40 -- 0x7e,  0x81 -- oxfe
  //no validation needed here. State machine has done that
  PRInt32 GetOrder(const ::string & str) 
  { 
    PRInt32 order;
    if ((unsigned char)*str >= (unsigned char)0x81 && (unsigned char)*str <= (unsigned char)0x9f)  
      order = 188 * ((unsigned char)str[0]-(unsigned char)0x81);
    else if ((unsigned char)*str >= (unsigned char)0xe0 && (unsigned char)*str <= (unsigned char)0xef)  
      order = 188 * ((unsigned char)str[0]-(unsigned char)0xe0 + 31);
    else
      return -1;
    order += (unsigned char)*(str+1) - 0x40;
    if ((unsigned char)str[1] > (unsigned char)0x7f)
      order--;
    return order;
  };
};

class EUCJPDistributionAnalysis : public CharDistributionAnalysis
{
public:
  EUCJPDistributionAnalysis();
protected:
  //for euc-JP encoding, we are interested 
  //  first  byte range: 0xa0 -- 0xfe
  //  second byte range: 0xa1 -- 0xfe
  //no validation needed here. State machine has done that
  PRInt32 GetOrder(const ::string & str) 
  { if ((unsigned char)*str >= (unsigned char)0xa0)  
      return 94*((unsigned char)str[0]-(unsigned char)0xa1) + (unsigned char)str[1] - (unsigned char)0xa1;
    else
      return -1;
  };
};

#endif //CharDistribution_h__

