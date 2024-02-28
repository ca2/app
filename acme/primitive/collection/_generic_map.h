// Created by camilo on 2023-01-06 19:19 <3ThomasBorregaardSorensen!!
#pragma once


namespace generic
{


   namespace map
   {


      template < typename CONTAINER, typename PAYLOAD >
      inline bool contains_payload(const CONTAINER & container, const PAYLOAD & payload);


      template < typename CONTAINER, typename PAYLOAD, typename START >
      inline auto find_payload(const CONTAINER & container, const PAYLOAD & payload, const START & start);


      template < typename CONTAINER, typename PAYLOAD >
      inline auto find_payload(const CONTAINER & container, const PAYLOAD & payload);


      template < typename CONTAINER, typename PAYLOAD >
      inline bool erase_payload(CONTAINER & container, const PAYLOAD & payload);

         
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



