#pragma once


namespace papaya
{


   namespace zoneing
   {

      template < typename T >
      inline T abs(const T & t)
      {

         return t >= (T)0 ? t : -t;

      }


      template < typename T1, typename T2 >
      inline bool is_equal(const T1 & t1, const T2 & t2, double dMargin, bool bIn)
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
      inline bool is_centered(const OUTER1 & outer1, const INNER1 & inner1, const INNER2 & inner2, const OUTER2 & outer2)
      {

         auto delta1 = abs(outer1 - inner1);

         auto delta2 = abs(inner2 - outer2);

         auto delta = (delta1 + delta2) / 3;

         return abs(delta1 - delta2) < delta;

      }


   } // namespace zoneing


} // namespace papaya

