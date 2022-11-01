#include "framework.h"
#include "int_biunique.h"
#include "acme/primitive/collection/numeric_array.h"


index_biunique::index_biunique()
{

}


int_biunique::int_biunique()
{
}


CLASS_DECL_ACME index array_translate_a(index_biunique & ia, index aNew, index aOld)
{

   if (aOld < 0 || aNew < 0)
   {
      return ia.m_iEmptyB;
   }

   index bParam = ia.get_b(aOld);
   if (bParam == ia.m_iEmptyB)
   {
      return ia.m_iEmptyB;
   }

   if (aNew == aOld)
   {
      return bParam;
   }

   ia.m_ba.erase_key(bParam);
   ia.m_ab.erase_key(aOld);
   ia.m_iMaxA = ia.calc_max_a();
   ia.m_iMaxB = ia.calc_max_b();
   //if (aNew > aOld)
   //{
   //   T a = aOld;
   //   while (a + 1 <= m_iMaxA)
   //   {
   //      T b = get_b(a + 1);
   //      if (b == m_iEmptyB)
   //      {
   //         break;
   //      }
   //      m_ba.erase_key(b);
   //      m_ab.erase_key(a + 1);
   //      m_ba.set_at(b, a);
   //      m_ab.set_at(a, b);
   //      m_iMaxA = calc_max_a();
   //      m_iMaxB = calc_max_b();
   //      a++;
   //   }
   //}

   // making room
   if (ia.has_a(aNew))
   {
      index a = aNew;
      index b;
      while (true)
      {
         a++;
         if (a > ia.m_iMaxA)
         {
            break;
         }
         b = ia.get_b(a);
         if (b == ia.m_iEmptyB)
         {
            break;
         }
      }
      a--;
      while (a >= aNew)
      {
         b = ia.get_b(a);
         if (b != ia.m_iEmptyB)
         {
            ia.m_ba.erase_key(b);
            ia.m_ab.erase_key(a);
            ia.m_ba.set_at(b, a + 1);
            ia.m_ab.set_at(a + 1, b);
         }
         a--;
      }
   }

   // actually (in)se(r)tting
   ia.m_ba.set_at(bParam, aNew);
   ia.m_ab.set_at(aNew, bParam);

   ia.m_iMaxA = ia.calc_max_a();
   ia.m_iMaxB = ia.calc_max_b();

   return bParam;

}



CLASS_DECL_ACME index_array array_translate_a_array(index_biunique & ia, index_array iaNew, index_array iaOld)
{




   if (iaNew.get_size() != iaOld.get_size())
   {

      return index_array();

   }

   index_array iaB;

   for (index i = 0; i < iaNew.get_size();)
   {

      if (iaNew[i] < 0 || iaOld[i] < 0 || iaNew[i] == iaOld[i])
      {

         iaNew.erase_at(i);
         iaOld.erase_at(i);



      }
      else
      {

         index b = ia.get_b(iaOld[i]);

         if (b == ia.m_iEmptyB)
         {

            iaNew.erase_at(i);
            iaOld.erase_at(i);

         }
         else
         {

            iaB.add(b);

            i++;

         }

      }

   }

   if (iaOld.get_size() <= 0 || iaNew.get_size() <= 0 || iaB.get_size() <= 0 || iaB.get_size() != iaOld.get_size() || iaOld.get_size() != iaNew.get_size())
   {

      return index_array();

   }

   ::count c = iaOld.get_size();

   for (index i = 0; i < c; i++)
   {

      ia.m_ba.erase_key(iaB[i]);

      ia.m_ab.erase_key(iaOld[i]);

   }

   ia.m_iMaxA = ia.calc_max_a();

   ia.m_iMaxB = ia.calc_max_b();

   // making room
   for (index i = c - 1; i >= 0; i--)
   {

      index newb = ia.get_b(iaNew[i]);

      if (newb >= 0)
      {

         index a = iaNew[i];

         index b;

         while (true)
         {

            a++;

            if (a > ia.m_iMaxA)
            {

               break;

            }

            b = ia.get_b(a);

            if (b == ia.m_iEmptyB && !iaNew.contains(a))
            {

               break;

            }

         }

         a--;

         index iOffset = 1;

         while (a >= iaNew[i])
         {

            b = ia.get_b(a);

            if (iaNew.contains(a) && a != iaNew[i])
            {

               iOffset++;

            }
            else if (b != ia.m_iEmptyB)
            {

               ia.m_ba.erase_key(b);

               ia.m_ab.erase_key(a);

               ia.m_ba.set_at(b, a + iOffset);

               ia.m_ab.set_at(a + iOffset, b);

            }

            a--;

         }

      }

      ia.m_ba.set_at(iaB[i], iaNew[i]);

      ia.m_ab.set_at(iaNew[i], iaB[i]);

      ia.m_iMaxA = ia.calc_max_a();

      ia.m_iMaxB = ia.calc_max_b();

   }

   return iaB;

}
