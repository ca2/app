// Created by camilo on 2024-11-18 20:51 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "release.h"


CLASS_DECL_ACME::std::strong_ordering compare_release(const ::string_array & straA, const ::string_array & straB)
{

   if (straA.is_empty())
   {

      if (straB.is_empty())
      {

         return ::std::strong_ordering::equal;

      }
      else
      {

         return ::std::strong_ordering::less;

      }

   }

   for (::collection::index i = 0; i < straA.size(); i++)
   {

      if (i >= straB.size())
      {

         return ::std::strong_ordering::greater;

      }

      auto compare = ::compare_release(straA[i], straB[i]);

      if (compare != 0)
      {

         return compare;

      }

   }

   return ::std::strong_ordering::equal;

}


CLASS_DECL_ACME::std::strong_ordering compare_release(const ::scoped_string & scopedstrA, const ::scoped_string & scopedstrB)
{

   if (scopedstrA.is_empty())
   {

      if (scopedstrB.is_empty())
      {

         return ::std::strong_ordering::equal;

      }
      else
      {

         return ::std::strong_ordering::less;

      }

   }
   else if (scopedstrB.is_empty())
   {

      return ::std::strong_ordering::greater;

   }
   else
   {

      auto a = scopedstrA.explode(".");

      auto b = scopedstrB.explode(".");

      if (a.size() <= 1 && b.size() <= 1)
      {

         return atoi(scopedstrA) <=> atoi(scopedstrB);

      }

      return compare_release(a, b);

   }

}


