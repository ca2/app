#ifndef __JPCNTX_H__
#define __JPCNTX_H__

#define NUM_OF_CATEGORY 6

#include "types.h" 

#define ENOUGH_REL_THRESHOLD  100
#define MAX_REL_THRESHOLD     1000

//hiragana frequency category table
extern ::i8 jp2CharContext[83][83];

class JapaneseContextAnalysis
{
public:
  JapaneseContextAnalysis() {Reset();};

  void HandleData(const ::string & aBuf, PRunsigned ::i32 aLen);

  void HandleOneChar(const ::string & aStr, PRunsigned ::i32 aCharLen)
  {
    PRInt32 order;

    //if we received enough data, stop here   
    if (mTotalRel > MAX_REL_THRESHOLD)   mDone = PR_TRUE;
    if (mDone)       return;
     
    //Only 2-bytes characters are of our interest
    order = (aCharLen == 2) ? GetOrder(aStr) : -1;
    if (order != -1 && mLastCharOrder != -1)
    {
      mTotalRel++;
      //count this sequence to its category counter
      mRelSample[jp2CharContext[mLastCharOrder][order]]++;
    }
    mLastCharOrder = order;
  };

  ::f32 GetConfidence();
  void      Reset(void);
  void      SetOpion(){};
  PRBool GotEnoughData() {return mTotalRel > ENOUGH_REL_THRESHOLD;};

protected:
  virtual PRInt32 GetOrder(const ::scoped_string & scopedstr, PRunsigned ::i32 *charLen) = 0;
  virtual PRInt32 GetOrder(const ::scoped_string & scopedstr) = 0;

  //category counters, each interger counts sequence in its category
  PRunsigned ::i32 mRelSample[NUM_OF_CATEGORY];

  //total sequence received
  PRunsigned ::i32 mTotalRel;
  
  //The order of previous ::i8
  PRInt32  mLastCharOrder;

  //if last ::u8 in current buffer is not the last ::u8 of a character, we
  //need to know how many ::u8 to skip in next buffer.
  PRunsigned ::i32 mNeedToSkipCharNum;

  //If this flag is set to PR_TRUE, detection is done and conclusion has been made
  PRBool   mDone;
};


class SJISContextAnalysis : public JapaneseContextAnalysis
{
  //SJISContextAnalysis(){};
protected:
  PRInt32 GetOrder(const ::scoped_string & scopedstr, PRunsigned ::i32 *charLen);

  PRInt32 GetOrder(const ::scoped_string & scopedstr)
  {
    //We only interested in Hiragana, so first ::u8 is '\202'
    if (*str == '\202' && 
          (::u8)*(str+1) >= (::u8)0x9f && 
          (::u8)*(str+1) <= (::u8)0xf1)
      return (::u8)*(str+1) - (::u8)0x9f;
    return -1;
  };
};

class EUCJPContextAnalysis : public JapaneseContextAnalysis
{
protected:
  PRInt32 GetOrder(const ::scoped_string & scopedstr, PRunsigned ::i32 *charLen);
  PRInt32 GetOrder(const ::scoped_string & scopedstr)
    //We only interested in Hiragana, so first ::u8 is '\244'
  {
    if (*str == '\244' &&
          (::u8)*(str+1) >= (::u8)0xa1 &&
          (::u8)*(str+1) <= (::u8)0xf3)
      return (::u8)*(str+1) - (::u8)0xa1;
    return -1;
  };
};

#endif /* __JPCNTX_H__ */

