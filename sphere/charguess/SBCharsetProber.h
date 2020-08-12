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

#ifndef nsSingleByteCharSetProber_h__
#define nsSingleByteCharSetProber_h__

#include "charsetProber.h"

#define SAMPLE_SIZE 64
#define SB_ENOUGH_REL_THRESHOLD  1024
#define POSITIVE_SHORTCUT_THRESHOLD  (float)0.95
#define NEGATIVE_SHORTCUT_THRESHOLD  (float)0.05
#define SYMBOL_CAT_ORDER  250
#define NUMBER_OF_SEQ_CAT 4
#define POSITIVE_CAT   (NUMBER_OF_SEQ_CAT-1)
#define NEGATIVE_CAT   0

typedef struct
{
  unsigned char *charToOrderMap;     //[256] table use to find a char's order
  char *precedenceMatrix;           //[SAMPLE_SIZE][SAMPLE_SIZE]; table to find a 2-char sequence's frequency
  float  mTypicalPositiveRatio;     // = freqSeqs / totalSeqs 
  PRBool keepEnglishLetter;         //it says if this script contains latin letters
  const char* charsetName;
} SequenceModel;


class nsSingleByteCharSetProber : public nsCharSetProber{
public:
  nsSingleByteCharSetProber(SequenceModel *model){mModel = model; Reset();};
  const char* GetCharSetName() {return mModel->charsetName;};
  nsProbingState HandleData(const char* aBuf, PRUint32 aLen);
  nsProbingState GetState(void) {return mState;};
  void      Reset(void);
  float     GetConfidence(void);
  void      SetOpion() {};
  PRBool KeepEnglishLetters() {return mModel->keepEnglishLetter;};

#ifdef DEBUG_chardet
  void  DumpStatus();
#endif

protected:
  nsProbingState mState;
  SequenceModel *mModel;

  //char order of last character
  unsigned char mLastOrder;

  PRUint32 mTotalSeqs;
  PRUint32 mSeqCounters[NUMBER_OF_SEQ_CAT];

  PRUint32 mTotalChar;
  //characters that fall in our sampling range
  PRUint32 mFreqChar;
};


extern SequenceModel Koi8rModel;
extern SequenceModel Win1251Model;
extern SequenceModel Latin5Model;
extern SequenceModel MacCyrillicModel;
extern SequenceModel Ibm866Model;
extern SequenceModel Ibm855Model;
extern SequenceModel Latin7Model;
extern SequenceModel Win1253Model;
extern SequenceModel Latin5BulgarianModel;
extern SequenceModel Win1251BulgarianModel;
extern SequenceModel Latin2HungarianModel;
extern SequenceModel Win1250HungarianModel;

#endif /* nsSingleByteCharSetProber_h__ */
