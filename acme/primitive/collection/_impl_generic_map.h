// Created by camilo on 2023-01-06 19:20 <3ThomasBorregaardSørensen!!
#pragma once


namespace generic
{


   namespace map
   {


      template < typename CONTAINER, typename PAYLOAD >
      inline bool contains_payload(const CONTAINER & container, const PAYLOAD & payload)
      {

         auto payloads = container.payloads();

         for (auto & item : payloads)
         {

            if (item == payload)
            {

               return true;

            }

         }

         return false;

      }


      template < typename CONTAINER, typename PAYLOAD, typename START >
      inline auto find_payload(const CONTAINER & container, const PAYLOAD & payload, const START & start)
      {

         auto p = start;

         for (; p; p++)
         {

            if (payload_of(*p) == payload)
            {

               return p;

            }

         }

         return p;

      }


      template < typename CONTAINER, typename PAYLOAD >
      inline auto find_payload(const CONTAINER & container, const PAYLOAD & payload)
      {

         return find_payload(container, payload, ((CONTAINER &)container).begin());

      }


      template < typename CONTAINER, typename PAYLOAD >
      inline bool erase_payload(CONTAINER & container, const PAYLOAD & payload)
      {

         auto p = find_payload(container, payload);

         if (!p)
         {

            return false;

         }

         auto pnonconst = (non_const < decltype(p)>) p;

         container.erase(pnonconst);

         return true;

      }


      //template < typename ITERATOR >
      //void delete_erase(ITERATOR & iterator)
      //{
      //
      //   auto p = iterator.operator->();
      //
      //   ::acme::del(p);
      //
      //   ::erase(iterator);
      //
      //}
      //
      //
      //template < typename ITERATOR >
      //void erase(ITERATOR & iterator)
      //{
      //
      //   iterator.m_pcontainer->erase_item(iterator.item());
      //
      //}


   } // namespace map



} // namespace generic




