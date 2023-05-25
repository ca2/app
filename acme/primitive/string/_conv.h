// Refactored by camilo on 2022-12-09 00:48 <3ThomasBorregaardSørensen!!
#pragma once


template < primitive_character CHARACTER >
constexpr CHARACTER * __zerotosz(CHARACTER * & p)
{

   *p++ = '0';

   *p = 0;

   return p;

}


template < primitive_unsigned UNSIGNED, primitive_character CHARACTER >
constexpr void __utosz_internal(UNSIGNED u, CHARACTER * & p, int base, enum_digit_case edigitcase)
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
/// @param p [in,out] address where to write string representation of /p u. At the output, returns the address of terminated null character at the end of the string.
/// @param base base to convert
/// @param edigitcase base greater than decimal base, the case of output characters 
template < primitive_unsigned UNSIGNED, primitive_character CHARACTER >
constexpr void __rear_tosz(UNSIGNED u, CHARACTER *& p, int base, enum_digit_case edigitcase)
{

   __utosz_internal(u, p, base, edigitcase);

}


template < primitive_signed SIGNED, primitive_character CHARACTER >
constexpr void __rear_tosz(SIGNED i, CHARACTER *& p, int base, enum_digit_case edigitcase)
{

   auto [u, bNegative] = as_absolute_unsigned(i);

   __utosz_internal(u, p, base, edigitcase);

   if (bNegative) *p++ = '-';

}


/// @brief compute string representation of unsigned number
/// @tparam INTEGRAL /p u type (unsigned constraint)
/// @tparam CHARACTER /p buf character type (character constraint)
/// @param i number to convert
/// @param p [in,out] address where to write string representation of /p u. At the output, returns the address of terminated null character at the end of the string.
/// @param base base to convert
/// @param edigitcase base greater than decimal base, the case of output characters 
template < primitive_integral INTEGRAL, primitive_character CHARACTER >
constexpr void __tosz(INTEGRAL i, CHARACTER * & p, int base, enum_digit_case edigitcase)
{

   if (i == 0)
   {

      __zerotosz(p);

      return;

   }

   auto s = p;

   __rear_tosz(i, p, base, edigitcase);

   reverse(s, p);

   *p = 0;

}

//::::pair <int,int> ia;




