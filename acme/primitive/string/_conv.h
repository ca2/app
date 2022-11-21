#pragma once

template < typename NATURAL, typename CHAR_TYPE >
CHAR_TYPE * __natural_to_string_internal(NATURAL u, CHAR_TYPE * buf, int iBase, ::i32 & iIndex, CHAR_TYPE chTen)
{

   while (u != 0)
   {

      i32 iDigit = (u % iBase);

      CHAR_TYPE ch;

      if (iDigit <= 9)
      {

         ch = (CHAR_TYPE)(iDigit + '0');

      }
      else
      {

         ch = (CHAR_TYPE)(iDigit - 10 + chTen);

      }

      buf[iIndex] = ch;

      u = u / iBase;

      iIndex++;

   }

   return buf;

}
