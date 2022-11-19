// From ::papaya::weak to ::loosely by camilo on 2022-11-18 07:48 <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/primitive/collection/_loosely.h"


namespace loosely
{


   namespace map
   {


      template < typename MAP >
      typename MAP::assoc* get(MAP& m, typename MAP::BASE_KEY key)
      {

         for (auto& assoc : m)
         {

            if (contains(assoc.element1(), key))
            {

               return &assoc;

            }

         }

         return nullptr;

      }


      template < typename MAP >
      typename MAP::BASE_VALUE* pvalue(MAP& m, typename MAP::BASE_ARG_KEY key)
      {

         for (auto& assoc : m)
         {

            if (contains(assoc.element1(), key))
            {

               return &assoc.element2();

            }

         }

         return nullptr;

      }

      template < typename MAP >
      typename MAP::BASE_VALUE value(MAP& m, typename MAP::BASE_ARG_KEY key, typename MAP::BASE_VALUE default_value = ::loosely::default_value < typename MAP::BASE_VALUE >())
      {

         auto pval = pvalue(m, key);

         if (pval == nullptr)
         {

            return default_value;

         }

         return *pval;

      }


   } // namespace map


} // namespace loosely


