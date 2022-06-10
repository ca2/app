#pragma once


inline i32 str::ch::ansichar_uni_len(wd32char i)
{
   if (i < 0)
   {
      return -1;
   }
   else if (i < 0x0080)
   {
      return 1;
   }
   else if (i < 0x0800)
   {
      return 2;
   }
   else
   {
      return 3;
   }
}


