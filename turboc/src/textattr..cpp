/*
  TurboC, a library for porting Borland Turbo C to GNU gcc.
  Copyright 2002 Ronald S. Burkey
 
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
  
  Contact Ron Burkey at info@sandroid.org.

  Filename:	textattr.c
  Purpose:	A Turbo C conio function.
  Mod history:	01/31/02 RSB	Created.
  		03/02/02 RSB	Made sizes of colors explicit.
*/
#include "framework.h"
//#include "conio.h"

#define COLOR_BLACK ARGB(255, 0, 0, 0)
#define COLOR_BLUE  ARGB(255, 0, 0, 255)
#define COLOR_GREEN ARGB(255, 0, 255, 0)
#define COLOR_CYAN ARGB(255, 0, 255, 255)
#define COLOR_RED ARGB(255, 255, 0, 0)
#define COLOR_MAGENTA ARGB(255, 255, 0, 255)
#define COLOR_YELLOW ARGB(255, 255, 255, 0)
#define COLOR_WHITE ARGB(255, 255, 25, 255)
#define A_NORMAL 0
#define A_BOLD 1
#define A_BLINK 2

// Translates conio foreground/background colors to ncurses colors.
const i32 ForegroundColors[16] = {
  COLOR_BLACK, COLOR_BLUE, COLOR_GREEN, COLOR_CYAN, COLOR_RED, COLOR_MAGENTA,
  COLOR_YELLOW, COLOR_WHITE, COLOR_BLACK, COLOR_BLUE, COLOR_GREEN, COLOR_CYAN,
  COLOR_RED, COLOR_MAGENTA, COLOR_YELLOW, COLOR_WHITE
};
const i32 ForegroundFlags[16] = {
  A_NORMAL, A_NORMAL, A_NORMAL, A_NORMAL, A_NORMAL, A_NORMAL, A_NORMAL,
  A_NORMAL,
  A_BOLD, A_BOLD, A_BOLD, A_BOLD, A_BOLD, A_BOLD, A_BOLD, A_BOLD
};
const i32 BackgroundColors[8] = {
  COLOR_BLACK, COLOR_BLUE, COLOR_GREEN, COLOR_CYAN, COLOR_RED, COLOR_MAGENTA,
  COLOR_YELLOW, COLOR_WHITE
};
const i32 BackgroundFlags[16] = {
  A_NORMAL, A_NORMAL, A_NORMAL, A_NORMAL, A_NORMAL, A_NORMAL, A_NORMAL,
  A_NORMAL,
  A_BLINK, A_BLINK, A_BLINK, A_BLINK, A_BLINK, A_BLINK, A_BLINK, A_BLINK
};

//-------------------------------------------------------------------------
// A utility of my own that does all of the actual work of translating
// Turbo C colors to ncurses colors.

static i32 LastTranslated = -1;
static int LastNewattr = -1;

i32
TranslateTurboColor (int newattr)
{
 // i32 i, Mask = 0;
 // i16 dFore, dBack, Fore, Back;
 // if (LastNewattr == newattr)
 //   return (LastTranslated);
 // LastNewattr = newattr;
 // dFore = ForegroundColors[newattr & 0x0f];
 // dBack = BackgroundColors[(newattr >> 4) & 0x07];
 // Mask =
 //   ForegroundFlags[newattr & 0x0f] | BackgroundFlags[(newattr >> 4) & 0x0f];
 // for (i = 0; i < ColorPairsUsed; i++)
 //   {
 //     pair_content (i, &Fore, &Back);
 //     if (Fore == dFore && Back == dBack)
	//break;
 //   }
 // if (i == ColorPairsUsed)
 //   {
 //     if (ColorPairsUsed < COLOR_PAIRS)
	//{
	//  init_pair (i, dFore, dBack);
	//  ColorPairsUsed++;
	//}
 //     else
	//{
	//  i = 0;
	//  Mask = A_NORMAL;
	//}
 //   }
 // LastTranslated = (Mask | COLOR_PAIR (i));
 // return (LastTranslated);
   return 0;
}

//-------------------------------------------------------------------------

void
textattr (int newattr)
{
  i32 High, Low;
  i32 NcursesAttr;
  if (!ConioInitialized)
    textmode (LASTMODE);
  if (newattr < 0 || newattr > 255)
    return;
  // Handle the conio bookkeeping.  
  High = 0x08 & CurrentAttributes.attribute & ~CurrentAttributes.normattr;
  Low = 0x08 & ~CurrentAttributes.attribute & CurrentAttributes.normattr;
  CurrentAttributes.normattr = newattr;
  CurrentAttributes.attribute = newattr;
  if (High)
    CurrentAttributes.attribute |= 0x08;
  if (Low)
    CurrentAttributes.attribute &= ~0x08;
  // Handle ncurses.  Need to compare the desired color pair against all
  // of the already-defined color pairs.  Need to define NEW color pairs
  // (if possible) when the foreground/background combination we want hasn't
  // been defined yet.
  NcursesAttr = TranslateTurboColor (CurrentAttributes.attribute);
  //wattrset (CurrentWindow, NcursesAttr);
  //wbkgdset (CurrentWindow, NcursesAttr | ' ');
}
