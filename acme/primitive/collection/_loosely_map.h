// From ::papaya::weak to ::loosely by camilo on 2022-11-18 07:48 <3ThomasBorregaardSørensen!!
#pragma once


#include "acme/primitive/collection/_loosely.h"


namespace loosely
{


   namespace map
   {


      template < typename MAP >
      typename MAP::assoc* get(MAP& m, typename MAP::BASE_ARG_ITEM key)
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
      typename MAP::BASE_PAYLOAD * pvalue(MAP& m, typename MAP::ARG_ITEM item)
      {

         for (auto& assoc : m)
         {

            if (contains(assoc.element1(), item))
            {

               return &assoc.element2();

            }

         }

         return nullptr;

      }


      template < typename MAP >
      typename MAP::BASE_PAYLOAD value(MAP& m, typename MAP::ARG_ITEM item, typename MAP::BASE_PAYLOAD default_payload = ::loosely::default_payload < typename MAP::BASE_PAYLOAD >())
      {

         auto pval = pvalue(m, item);

         if (pval == nullptr)
         {

            return default_payload;

         }

         return *pval;

      }


   } // namespace map


} // namespace loosely


