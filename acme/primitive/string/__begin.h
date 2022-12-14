#pragma once


#include "c/_.h"
#include "sz/_.h"
//#include <assert.h>

namespace comparison
{


   template < typename TYPE >
   class case_insensitive
   {
   public:


      using EQUALITY = for_type < TYPE >;
      using ORDERING = for_type < TYPE >;

      constexpr bool equals(const TYPE & a, const TYPE & b) const { return a.case_insensitive_equals(b); }
      constexpr ::std::strong_ordering order(const TYPE & a, const TYPE & b) const { return a.case_insensitive_order(b); }


   };


   template < primitive_character CHARACTER >
   class case_insensitive < CHARACTER >
   {
   public:


      using EQUALITY = for_type < CHARACTER >;
      using ORDERING = for_type < CHARACTER >;

      constexpr bool equals(CHARACTER a, CHARACTER b) const { return character_tolower(a) == character_tolower(b); }
      constexpr ::std::strong_ordering order(CHARACTER a, CHARACTER b) const { return character_tolower(a) <=> character_tolower(b); }


   };


} // namespace comparison



//template < primitive_character CHARACTER >
//constexpr bool ::comparison::comparison(CHARACTER a, CHARACTER b)
//{
//
//   return a == b;
//
//}



//template < primitive_character CHARACTER >
//constexpr ::std::strong_ordering compare_character(CHARACTER a, CHARACTER b)
//{
//
//   return a <=> b;
//
//}

//
//template < primitive_character CHARACTER >
//constexpr bool equals_character_ci(CHARACTER a, CHARACTER b)
//{
//
//   return character_tolower(a) == character_tolower(b);
//
//}
//
//
//
//template < primitive_character CHARACTER >
//constexpr ::std::strong_ordering compare_character_ci(CHARACTER a, CHARACTER b)
//{ 
//   
//   return character_tolower(a) <=> character_tolower(b); 
//
//}




template < typename ITERATOR_TYPE >
range < ITERATOR_TYPE > ::range(::ansi_character ansichar)
   {
      if constexpr(sizeof(ITEM) == 1)
      {
         m_wd32char = 0;
         m_ansichar = ansichar;
         m_begin = (this_iterator) &m_ansichar;
         m_end = (this_iterator)(&m_ansichar + 1);
         set_null_terminated(true);
      }
      else if constexpr(sizeof(ITEM) == 2)
      {
         m_wd32char = 0;
         m_wd16char = ansichar;
         m_begin = (this_iterator) &m_wd16char;
         m_end = (this_iterator)(&m_wd16char + 1);
         set_null_terminated(true);
      }
      else if constexpr(sizeof(ITEM) == 4)
      {
         m_wd32char = ansichar;
         m_begin = (this_iterator) &m_wd32char;
         m_end = (this_iterator)(&m_wd32char + 1);
         set_null_terminated(false);
      }
      else
   {
   throw exception(error_wrong_state);

   }

   }



      template < typename ITERATOR_TYPE >
range < ITERATOR_TYPE > ::range(::wd16_character wd16char)
      {
      if constexpr(sizeof(ITEM) == 1)
      {
         m_wd32char = 0;
         utf_to_utf(&m_ansichar, &wd16char, 1);
         m_begin = (this_iterator) &m_ansichar;
         m_end = (this_iterator)(&m_ansichar + utf_to_utf_length(&m_ansichar, &wd16char, 1));
         set_null_terminated(false);
      }
else if constexpr(sizeof(ITEM) == 2)
{
      m_wd32char = 0;
      m_wd16char = wd16char;
m_begin = (this_iterator) &m_wd16char;
m_end = (this_iterator)(&m_wd16char + 1);
set_null_terminated(true);
}
else if constexpr(sizeof(ITEM) == 4)
{
m_wd32char = wd16char;
m_begin = (this_iterator) &m_wd32char;
m_end = (this_iterator)(&m_wd32char + 1);
set_null_terminated(false);
}
else
      
   {
   throw exception(error_wrong_state);

   }


}




template < typename ITERATOR_TYPE >
range < ITERATOR_TYPE > ::range(::wd32_character wd32char)
{
if constexpr(sizeof(ITEM) == 1)
{
m_wd32char = 0;
utf_to_utf(&m_ansichar, &wd32char, 1);
m_begin = (this_iterator) &m_ansichar;
m_end = (this_iterator)(&m_ansichar + utf_to_utf_length(&m_ansichar, &wd32char, 1));
set_null_terminated(false);
}
else if constexpr(sizeof(ITEM) == 2)
{
m_wd32char = 0;
utf_to_utf(&m_wd16char, &wd32char, 1);
m_begin = (this_iterator) &m_wd16char;
m_end = (this_iterator)(&m_wd16char + utf_to_utf_length(&m_wd16char, &wd32char, 1));
set_null_terminated(false);
}
else if constexpr(sizeof(ITEM) == 4)
{
m_wd32char = wd32char;
m_begin = (this_iterator) &m_wd32char;
m_end = (this_iterator)(&m_wd32char + 1);
set_null_terminated(false);
}
      else
   {
   throw exception(error_wrong_state);

   }

}
