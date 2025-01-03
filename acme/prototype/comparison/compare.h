#pragma once


#include "acme/prototype/mathematics/numeric_info.h"


namespace comparison
{

   template < typename A, typename B >
   inline bool eq(const A & a, const B & b)
   {
      return a == b;
   }

   template < primitive_signed SIGNED, primitive_unsigned UNSIGNED >
   inline bool eq(SIGNED s, UNSIGNED u)
   {
      return s < 0 ? false : (UNSIGNED)s == u;
   }



//   template < typename A, typename B >
//   inline bool lt(const A & a, const B & b)
//   {
//
//      return a < b;
//
//   }


   template < primitive_unsigned UNSIGNED, primitive_signed SIGNED >
   inline bool lt(UNSIGNED u, SIGNED s)
   {
      return s < 0 ? false : u < (UNSIGNED)s;
   }

   template < primitive_signed SIGNED, primitive_unsigned UNSIGNED >
   inline bool lt(SIGNED s, UNSIGNED u)
   {
      return s < 0 ? true : (UNSIGNED)s < u;
   }


   template < primitive_signed SIGNED1, primitive_signed SIGNED2 >
   inline bool lt(SIGNED1 s1, SIGNED2 s2)
   {
      
      return s1 < s2;

   }

   template < primitive_unsigned UNSIGNED1, primitive_unsigned UNSIGNED2 >
   inline bool lt(UNSIGNED1 u1, UNSIGNED2 u2)
   {

      return u1 > ::numeric_info<UNSIGNED2>::maximum() ? false : (UNSIGNED2)u1 < u2;

   }




   template < >
   inline bool lt(unsigned long u, long i)
   {
      return i < 0 ? false : u < (unsigned int) i;
   }



   template < typename A, typename B >
   inline bool le(A a, B b)
   {
      return a <= b;
   }

   template < primitive_signed SIGNED, primitive_unsigned UNSIGNED >
   inline bool le(SIGNED s, UNSIGNED u)
   {
      return s < 0 ? true : ((UNSIGNED)s) <= u;
   }


//   template < typename A, typename B >
//   inline bool gt(const A & a, const B & b)
//   {
//      return b < a;
//   }


   template < primitive_signed SIGNED, primitive_unsigned UNSIGNED >
   inline bool gt(SIGNED i, UNSIGNED u)
   {

      return i < 0 ? false : ((UNSIGNED)i) > u;

   }


   template < primitive_unsigned UNSIGNED, primitive_signed SIGNED >
   inline bool gt(UNSIGNED u, SIGNED s)
   {

      return s < 0 ? true : u > ((UNSIGNED) s);

   }

   template < primitive_signed SIGNED1, primitive_signed SIGNED2 >
   inline bool gt(SIGNED1 s1, SIGNED2 s2)
   {

      return s2 < s1;

   }


   template < primitive_unsigned UNSIGNED1, primitive_unsigned UNSIGNED2 >
   inline bool gt(UNSIGNED1 u1, UNSIGNED2 u2)
   {

      return u2 < u1;

   }

   template < typename A, typename B >
   inline bool ge(A a, B b)
   {
      return a >= b;
   }

   template < primitive_signed SIGNED, primitive_unsigned UNSIGNED >
   inline bool ge(SIGNED s, UNSIGNED u)
   {

      return s < 0 ? false : ((UNSIGNED)s) >= u;

   }


   template < primitive_unsigned UNSIGNED1, primitive_unsigned UNSIGNED2 >
   inline bool ge(UNSIGNED1 u1, UNSIGNED2 u2)
   {
      return u1 >= u2;
   }

   template < primitive_signed SIGNED1, primitive_signed SIGNED2 >
   inline bool ge(SIGNED1 s1, SIGNED2 s2)
   {
      return s1 >= s2;
   }


   template < primitive_unsigned UNSIGNED, primitive_signed SIGNED >
   inline bool ge(UNSIGNED u, SIGNED s)
   {
      return s < 0 ? true : u >= (UNSIGNED)s;
   }





   template < typename T1, typename T2 >
   inline bool is_equal(const T1& t1, const T2& t2, double dMargin, bool bIn)
   {

      double delta = (double)(t1 - t2);

      if (bIn)
      {

         return delta >= (-dMargin / 2.0) && delta <= dMargin;

      }
      else
      {

         return delta >= (-dMargin) && delta <= dMargin * 2.0;

      }


   }


   template < typename OUTER1, typename INNER1, typename INNER2, typename OUTER2 >
   inline bool is_centered(const OUTER1& outer1, const INNER1& inner1, const INNER2& inner2, const OUTER2& outer2)
   {

      auto delta1 = abs(outer1 - inner1);

      auto delta2 = abs(inner2 - outer2);

      auto delta = (delta1 + delta2) / 3;

      return abs(delta1 - delta2) < delta;

   }

   

} // namespace comparison






template < typename TYPE, typename MINIMUM, typename MAXIMUM >
[[nodiscard]]constexpr auto constrained(TYPE t, MINIMUM tMinimum, MAXIMUM tMaximum)
{
   
   return minimum(tMaximum, maximum(tMinimum, t));

}

template < typename TYPE, typename MINIMUM, typename MAXIMUM >
constexpr TYPE & constrain(TYPE & t, MINIMUM tMinimum, MAXIMUM tMaximum)
{
   
   return t = constrained(t, tMinimum, tMaximum);

}


template < typename TYPE, typename MINIMUM, typename MAXIMUM >
[[nodiscard]]constexpr auto sort_constrained(TYPE t, MINIMUM tMinimum, MAXIMUM tMaximum)
{

   return tMinimum < tMaximum ? constrain(tMinimum, tMaximum) : constrain(tMaximum, tMinimum);

}


template < typename TYPE, typename MINIMUM, typename MAXIMUM >
constexpr TYPE & sort_constrain(TYPE & t, MINIMUM tMinimum, MAXIMUM tMaximum)
{

   return t = sort_constrained(t, tMinimum, tMaximum);

}



template < typename TYPE >
[[nodiscard]]constexpr auto u16_constrained(TYPE t)
{

   return (unsigned short) constrain(t, 0, UINT16_MAX);

}


template < typename TYPE >
[[nodiscard]]constexpr unsigned int u32_constrained(TYPE t)
{

   return (unsigned int) constrain(t, 0, UINT32_MAX);

}


struct domain_id
{


   enum_domain    m_edomain;
   int          m_iId;


   constexpr domain_id() : m_edomain(e_domain_none), m_iId(-1){}
   constexpr domain_id(enum_domain edomain, int iId) : m_edomain(edomain), m_iId(iId){}
   constexpr domain_id(const domain_id & domainid) : m_edomain(domainid.m_edomain), m_iId(domainid.m_iId){}

   inline constexpr bool operator == (const ::domain_id & domainid) const
   {

      return ::comparison::tuple
              (
                      [&]() { return m_edomain == domainid.m_edomain; },
                      [&]() { return m_iId == domainid.m_iId; }
              );

   }


   inline constexpr ::std::strong_ordering operator <=>(const ::domain_id & domainid) const
   {

      return ::comparison::tuple
              (
                      [&]() { return m_edomain <=> domainid.m_edomain; },
                      [&]() { return m_iId <=> domainid.m_iId; }
              );

   }


   inline constexpr bool is_ok() const
   {

      return m_edomain > e_domain_none && m_iId > 0;

   }


   inline constexpr bool is_nok() const
   {

      return !is_ok();

   }

   
};



