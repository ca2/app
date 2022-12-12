// Refactored by camilo on 2022-12-09 00:48 <3ThomasBorregaardSorensen!!
#pragma once


template < primitive_character CHARACTER >
CHARACTER * __zerotosz(CHARACTER * p)
{

   *p++ = '0';

   *p = 0;

   return p;

}


template < primitive_unsigned UNSIGNED, primitive_character CHARACTER >
void __utosz_internal(UNSIGNED u, CHARACTER * & p, int base, enum_digit_case edigitcase)
{

   while (u != 0)
   {

      auto digit = (u % base);

      if (digit <= 9)
      {

         *p = (CHARACTER)(digit + '0');

      }
      else
      {

         *p = (CHARACTER)(digit - 10 + edigitcase);

      }

      u = (UNSIGNED) (u / base);

      p++;

   }

}


/// @brief compute string representation of unsigned number
/// @tparam UNSIGNED /p u type (unsigned constraint)
/// @tparam CHARACTER /p buf character type (character constraint)
/// @param u number to convert
/// @param buf address where to write string representation of /p u
/// @param iBase base to convert
/// @param edigitcase base greater than decimal base, the case of output characters 
/// @return address of end of number (address of the terminating null character>
template < primitive_unsigned UNSIGNED, primitive_character CHARACTER >
void __utosz(UNSIGNED u, CHARACTER * & p, int iBase, enum_digit_case edigitcase)
{

   if (u == 0)
   {

      __zerotosz(p);

      return;

   }

   auto s = p;

   __utosz_internal(u, p, iBase, edigitcase);

   reverse(s, p - 1);

   *p = 0;

}



template < primitive_signed SIGNED, primitive_character CHARACTER >
void __itosz(SIGNED i, CHARACTER * & p, int base, enum_digit_case edigitcase)
{

   if (i == 0)
   {

      __zerotosz(p);

      return;

   }

   auto s = p;

   auto [ u, bNegative ] = as_absolute_unsigned(i);

   __utosz(u, p, base, edigitcase);

   if (bNegative) *p++ = '-';

   reverse(s, p - 1);

   *p = 0;

}



