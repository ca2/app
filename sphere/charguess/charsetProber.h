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

#ifndef nsCharSetProber_h__
#define nsCharSetProber_h__

#include "types.h"

typedef enum {
  eDetecting = 0,   //we are still detecting, no sure answer yet, but caller can ask for confidence.
  eFoundIt = 1,     //That's a positive answer
  eNotMe = 2        //negative answer
} nsProbingState;

#define SHORTCUT_THRESHOLD      (float)0.95

class nsCharSetProber {
public:
  virtual ~nsCharSetProber() {};
  virtual const char* GetCharSetName() = 0;
  virtual nsProbingState HandleData(const char* aBuf, PRUint32 aLen) = 0;
  virtual nsProbingState GetState(void) = 0;
  virtual void      Reset(void)  = 0;
  virtual float     GetConfidence(void) = 0;
  virtual void      SetOpion() = 0;

#ifdef DEBUG_chardet
  virtual void  DumpStatus() {};
#endif
};

#endif /* nsCharSetProber_h__ */

