#pragma once


#include "acme/primitive/collection/iterator.h"


template < class TYPE, class ARG_TYPE >
inline bool LessCompareElements(ARG_TYPE element1, ARG_TYPE element2)
{
   return element1 < element2;
}


namespace comparison
{

   template < class TYPE, class ARG_TYPE = const TYPE & >
   class less
   {
   public:

      inline bool operator() (ARG_TYPE element1, ARG_TYPE element2) const
      {
         return ::LessCompareElements < TYPE, ARG_TYPE > (element1, element2);
      }


   };


} // namespace comparison

template <bool b> struct StaticAssertionFailed;
template <> struct StaticAssertionFailed <true> {};

#define STATIC_ASSERT(x) \
    {StaticAssertionFailed <x> ();}

// https://stackoverflow.com/questions/23367775/pragma-packshow-with-gcc - Morten Jensen
      /*
   The static_assert macro will generate an error at compile-time, if the predicate is false
   but will only work for predicates that are resolvable at compile-time!

   E.g.: to assert the size of a data structure, static_assert(sizeof(struct_t) == 10)
*/
#define COMPILE_TIME_ASSERT(COND,MSG) typedef char static_assertion_##MSG[(!!(COND))*2-1]
/* token pasting madness: */
#define COMPILE_TIME_ASSERT3(X,L)     COMPILE_TIME_ASSERT(X,at_line_##L)             /* add line-number to error message for better warnings, especially GCC will tell the name of the variable as well */
#define COMPILE_TIME_ASSERT2(X,L)     COMPILE_TIME_ASSERT3(X, L)               /* expand line-number */
#define compile_time_assert(X)        COMPILE_TIME_ASSERT2(X, __LINE__)        /* call with line-number macro */

#define PACKED  __attribute__ ((gcc_struct, __packed__))


namespace comparison
{


   template < >
   class less < string , const string & >
   {
   public:


      inline bool operator()(const string & element1, const string & element2) const
      {

         return element1 < element2;

      }

   };


   template < >
   class less < wstring, const wstring & >
   {
   public:


      inline bool operator()(const wstring & element1, const wstring & element2) const
      {

         return element1 < element2;

      }

   };


} // namespace comparison






