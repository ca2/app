//
//  winpr_scancode.cpp
//  apex
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 07/06/19.
//
#include "framework.h"
#include "winpr_input.h"
#include "acme/operating_system/cross/windows/_windows.h"

/**
 * Virtual Scan Codes
 */

/**
 * Keyboard Type 4
 */

static unsigned int KBD4T[128] =
{
   KBD4_T00,
   KBD4_T01,
   KBD4_T02,
   KBD4_T03,
   KBD4_T04,
   KBD4_T05,
   KBD4_T06,
   KBD4_T07,
   KBD4_T08,
   KBD4_T09,
   KBD4_T0A,
   KBD4_T0B,
   KBD4_T0C,
   KBD4_T0D,
   KBD4_T0E,
   KBD4_T0F,
   KBD4_T10,
   KBD4_T11,
   KBD4_T12,
   KBD4_T13,
   KBD4_T14,
   KBD4_T15,
   KBD4_T16,
   KBD4_T17,
   KBD4_T18,
   KBD4_T19,
   KBD4_T1A,
   KBD4_T1B,
   KBD4_T1C,
   KBD4_T1D,
   KBD4_T1E,
   KBD4_T1F,
   KBD4_T20,
   KBD4_T21,
   KBD4_T22,
   KBD4_T23,
   KBD4_T24,
   KBD4_T25,
   KBD4_T26,
   KBD4_T27,
   KBD4_T28,
   KBD4_T29,
   KBD4_T2A,
   KBD4_T2B,
   KBD4_T2C,
   KBD4_T2D,
   KBD4_T2E,
   KBD4_T2F,
   KBD4_T30,
   KBD4_T31,
   KBD4_T32,
   KBD4_T33,
   KBD4_T34,
   KBD4_T35,
   KBD4_T36,
   KBD4_T37,
   KBD4_T38,
   KBD4_T39,
   KBD4_T3A,
   KBD4_T3B,
   KBD4_T3C,
   KBD4_T3D,
   KBD4_T3E,
   KBD4_T3F,
   KBD4_T40,
   KBD4_T41,
   KBD4_T42,
   KBD4_T43,
   KBD4_T44,
   KBD4_T45,
   KBD4_T46,
   KBD4_T47,
   KBD4_T48,
   KBD4_T49,
   KBD4_T4A,
   KBD4_T4B,
   KBD4_T4C,
   KBD4_T4D,
   KBD4_T4E,
   KBD4_T4F,
   KBD4_T50,
   KBD4_T51,
   KBD4_T52,
   KBD4_T53,
   KBD4_T54,
   KBD4_T55,
   KBD4_T56,
   KBD4_T57,
   KBD4_T58,
   KBD4_T59,
   KBD4_T5A,
   KBD4_T5B,
   KBD4_T5C,
   KBD4_T5D,
   KBD4_T5E,
   KBD4_T5F,
   KBD4_T60,
   KBD4_T61,
   KBD4_T62,
   KBD4_T63,
   KBD4_T64,
   KBD4_T65,
   KBD4_T66,
   KBD4_T67,
   KBD4_T68,
   KBD4_T69,
   KBD4_T6A,
   KBD4_T6B,
   KBD4_T6C,
   KBD4_T6D,
   KBD4_T6E,
   KBD4_T6F,
   KBD4_T70,
   KBD4_T71,
   KBD4_T72,
   KBD4_T73,
   KBD4_T74,
   KBD4_T75,
   KBD4_T76,
   KBD4_T77,
   KBD4_T78,
   KBD4_T79,
   KBD4_T7A,
   KBD4_T7B,
   KBD4_T7C,
   KBD4_T7D,
   KBD4_T7E,
   KBD4_T7F
};

static unsigned int KBD4X[128] =
{
   VK_NONE,
   VK_NONE,
   VK_NONE,
   VK_NONE,
   VK_NONE,
   VK_NONE,
   VK_NONE,
   VK_NONE,
   VK_NONE,
   VK_NONE,
   VK_NONE,
   VK_NONE,
   VK_NONE,
   VK_NONE,
   VK_NONE,
   VK_NONE,
   KBD4_X10,
   VK_NONE,
   VK_NONE,
   VK_NONE,
   VK_NONE,
   VK_NONE,
   VK_NONE,
   VK_NONE,
   VK_NONE,
   KBD4_X19,
   VK_NONE,
   VK_NONE,
   KBD4_X1C,
   KBD4_X1D,
   VK_NONE,
   VK_NONE,
   KBD4_X20,
   KBD4_X21,
   KBD4_X22,
   VK_NONE,
   KBD4_X24,
   VK_NONE,
   VK_NONE,
   VK_NONE,
   VK_NONE,
   VK_NONE,
   VK_NONE,
   VK_NONE,
   VK_NONE,
   VK_NONE,
   KBD4_X2E,
   VK_NONE,
   KBD4_X30,
   VK_NONE,
   KBD4_X32,
   VK_NONE,
   VK_NONE,
   KBD4_X35,
   VK_NONE,
   KBD4_X37,
   KBD4_X38,
   VK_NONE,
   VK_NONE,
   VK_NONE,
   VK_NONE,
   VK_NONE,
   VK_NONE,
   VK_NONE,
   VK_NONE,
   VK_NONE,
   VK_NONE,
   VK_NONE,
   VK_NONE,
   VK_NONE,
   KBD4_X46,
   KBD4_X47,
   KBD4_X48,
   KBD4_X49,
   VK_NONE,
   KBD4_X4B,
   VK_NONE,
   KBD4_X4D,
   VK_NONE,
   KBD4_X4F,
   KBD4_X50,
   KBD4_X51,
   KBD4_X52,
   KBD4_X53,
   VK_NONE,
   VK_NONE,
   VK_NONE,
   VK_NONE,
   VK_NONE,
   VK_NONE,
   VK_NONE,
   KBD4_X5B,
   KBD4_X5C,
   KBD4_X5D,
   KBD4_X5E,
   KBD4_X5F,
   VK_NONE,
   VK_NONE,
   VK_NONE,
   VK_NONE,
   VK_NONE,
   KBD4_X65,
   KBD4_X66,
   KBD4_X67,
   KBD4_X68,
   KBD4_X69,
   KBD4_X6A,
   KBD4_X6B,
   KBD4_X6C,
   KBD4_X6D,
   VK_NONE,
   VK_NONE,
   VK_NONE,
   VK_NONE,
   VK_NONE,
   VK_NONE,
   VK_NONE,
   VK_NONE,
   VK_NONE,
   VK_NONE,
   VK_NONE,
   VK_NONE,
   VK_NONE,
   VK_NONE,
   VK_NONE,
   VK_NONE,
   VK_NONE,
   VK_NONE,
};

/**
 * Keyboard Type 7
 */

static unsigned int KBD7T[128] =
{
   KBD7_T00,
   KBD7_T01,
   KBD7_T02,
   KBD7_T03,
   KBD7_T04,
   KBD7_T05,
   KBD7_T06,
   KBD7_T07,
   KBD7_T08,
   KBD7_T09,
   KBD7_T0A,
   KBD7_T0B,
   KBD7_T0C,
   KBD7_T0D,
   KBD7_T0E,
   KBD7_T0F,
   KBD7_T10,
   KBD7_T11,
   KBD7_T12,
   KBD7_T13,
   KBD7_T14,
   KBD7_T15,
   KBD7_T16,
   KBD7_T17,
   KBD7_T18,
   KBD7_T19,
   KBD7_T1A,
   KBD7_T1B,
   KBD7_T1C,
   KBD7_T1D,
   KBD7_T1E,
   KBD7_T1F,
   KBD7_T20,
   KBD7_T21,
   KBD7_T22,
   KBD7_T23,
   KBD7_T24,
   KBD7_T25,
   KBD7_T26,
   KBD7_T27,
   KBD7_T28,
   KBD7_T29,
   KBD7_T2A,
   KBD7_T2B,
   KBD7_T2C,
   KBD7_T2D,
   KBD7_T2E,
   KBD7_T2F,
   KBD7_T30,
   KBD7_T31,
   KBD7_T32,
   KBD7_T33,
   KBD7_T34,
   KBD7_T35,
   KBD7_T36,
   KBD7_T37,
   KBD7_T38,
   KBD7_T39,
   KBD7_T3A,
   KBD7_T3B,
   KBD7_T3C,
   KBD7_T3D,
   KBD7_T3E,
   KBD7_T3F,
   KBD7_T40,
   KBD7_T41,
   KBD7_T42,
   KBD7_T43,
   KBD7_T44,
   KBD7_T45,
   KBD7_T46,
   KBD7_T47,
   KBD7_T48,
   KBD7_T49,
   KBD7_T4A,
   KBD7_T4B,
   KBD7_T4C,
   KBD7_T4D,
   KBD7_T4E,
   KBD7_T4F,
   KBD7_T50,
   KBD7_T51,
   KBD7_T52,
   KBD7_T53,
   KBD7_T54,
   KBD7_T55,
   KBD7_T56,
   KBD7_T57,
   KBD7_T58,
   KBD7_T59,
   KBD7_T5A,
   KBD7_T5B,
   KBD7_T5C,
   KBD7_T5D,
   KBD7_T5E,
   KBD7_T5F,
   KBD7_T60,
   KBD7_T61,
   KBD7_T62,
   KBD7_T63,
   KBD7_T64,
   KBD7_T65,
   KBD7_T66,
   KBD7_T67,
   KBD7_T68,
   KBD7_T69,
   KBD7_T6A,
   KBD7_T6B,
   KBD7_T6C,
   KBD7_T6D,
   KBD7_T6E,
   KBD7_T6F,
   KBD7_T70,
   KBD7_T71,
   KBD7_T72,
   KBD7_T73,
   KBD7_T74,
   KBD7_T75,
   KBD7_T76,
   KBD7_T77,
   KBD7_T78,
   KBD7_T79,
   KBD7_T7A,
   KBD7_T7B,
   KBD7_T7C,
   KBD7_T7D,
   KBD7_T7E,
   KBD7_T7F
};

static unsigned int KBD7X[128] =
{
   VK_NONE,
   VK_NONE,
   VK_NONE,
   VK_NONE,
   VK_NONE,
   VK_NONE,
   VK_NONE,
   VK_NONE,
   VK_NONE,
   VK_NONE,
   VK_NONE,
   VK_NONE,
   VK_NONE,
   VK_NONE,
   VK_NONE,
   VK_NONE,
   KBD7_X10,
   VK_NONE,
   VK_NONE,
   VK_NONE,
   VK_NONE,
   VK_NONE,
   VK_NONE,
   VK_NONE,
   VK_NONE,
   KBD7_X19,
   VK_NONE,
   VK_NONE,
   KBD7_X1C,
   KBD7_X1D,
   VK_NONE,
   VK_NONE,
   KBD7_X20,
   KBD7_X21,
   KBD7_X22,
   VK_NONE,
   KBD7_X24,
   VK_NONE,
   VK_NONE,
   VK_NONE,
   VK_NONE,
   VK_NONE,
   VK_NONE,
   VK_NONE,
   VK_NONE,
   VK_NONE,
   KBD7_X2E,
   VK_NONE,
   KBD7_X30,
   VK_NONE,
   KBD7_X32,
   KBD7_X33,
   VK_NONE,
   KBD7_X35,
   VK_NONE,
   KBD7_X37,
   KBD7_X38,
   VK_NONE,
   VK_NONE,
   VK_NONE,
   VK_NONE,
   VK_NONE,
   VK_NONE,
   VK_NONE,
   VK_NONE,
   VK_NONE,
   KBD7_X42,
   KBD7_X43,
   KBD7_X44,
   VK_NONE,
   KBD7_X46,
   KBD7_X47,
   KBD7_X48,
   KBD7_X49,
   VK_NONE,
   KBD7_X4B,
   VK_NONE,
   KBD7_X4D,
   VK_NONE,
   KBD7_X4F,
   KBD7_X50,
   KBD7_X51,
   KBD7_X52,
   KBD7_X53,
   VK_NONE,
   VK_NONE,
   VK_NONE,
   VK_NONE,
   VK_NONE,
   VK_NONE,
   VK_NONE,
   KBD7_X5B,
   KBD7_X5C,
   KBD7_X5D,
   KBD7_X5E,
   KBD7_X5F,
   VK_NONE,
   VK_NONE,
   VK_NONE,
   VK_NONE,
   VK_NONE,
   KBD7_X65,
   KBD7_X66,
   KBD7_X67,
   KBD7_X68,
   KBD7_X69,
   KBD7_X6A,
   KBD7_X6B,
   KBD7_X6C,
   KBD7_X6D,
   VK_NONE,
   VK_NONE,
   VK_NONE,
   VK_NONE,
   VK_NONE,
   VK_NONE,
   VK_NONE,
   VK_NONE,
   VK_NONE,
   VK_NONE,
   VK_NONE,
   VK_NONE,
   VK_NONE,
   VK_NONE,
   VK_NONE,
   VK_NONE,
   VK_NONE,
   VK_NONE
};

extern "C"
unsigned int GetVirtualKeyCodeFromVirtualScanCode(unsigned int scancode, unsigned int dwKeyboardType)
{
   unsigned int codeIndex;

   codeIndex = scancode & 0xFF;

   if (codeIndex > 127)
      return VK_NONE;

   if ((dwKeyboardType != 4) && (dwKeyboardType != 7))
      dwKeyboardType = 4;

   if (dwKeyboardType == 4)
   {
      return (scancode & KBDEXT) ? KBD4X[codeIndex] : KBD4T[codeIndex];
   }
   else if (dwKeyboardType == 7)
   {
      return (scancode & KBDEXT) ? KBD7X[codeIndex] : KBD7T[codeIndex];
   }

   return VK_NONE;
}

extern "C"
unsigned int GetVirtualScanCodeFromVirtualKeyCode(unsigned int vkcode, unsigned int dwKeyboardType)
{
   int i;
   unsigned int scancode;
   unsigned int codeIndex;

   scancode = 0;
   codeIndex = vkcode & 0xFF;

   if ((dwKeyboardType != 4) && (dwKeyboardType != 7))
      dwKeyboardType = 4;

   if (dwKeyboardType == 4)
   {
      if (vkcode & KBDEXT)
      {
         for (i = 0; i < 128; i++)
         {
            if (KBD4X[i] == codeIndex)
            {
               scancode = (i | KBDEXT);
               break;
            }
         }
      }
      else
      {
         for (i = 0; i < 128; i++)
         {
            if (KBD4T[i] == codeIndex)
            {
               scancode = i;
               break;
            }
         }
      }
   }
   else if (dwKeyboardType == 7)
   {
      if (vkcode & KBDEXT)
      {
         for (i = 0; i < 128; i++)
         {
            if (KBD7X[i] == codeIndex)
            {
               scancode = (i | KBDEXT);
               break;
            }
         }
      }
      else
      {
         for (i = 0; i < 128; i++)
         {
            if (KBD7T[i] == codeIndex)
            {
               scancode = i;
               break;
            }
         }
      }
   }

   return scancode;
}
