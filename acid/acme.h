//
// Created by camilo on 2022-10-22 18:39 <3ThomasBorregaardSorensen!!
//
#pragma once



//namespace

template < typename TYPE >
inline auto deref(const TYPE & t) { return typename TYPE::CONTAINER::dereferenced_iterator(t.item(), t.container()); }






//
//
//
//
//template < typename CONTAINER, typename PAYLOAD >
//inline bool contains_payload(const CONTAINER & container, const PAYLOAD & payload)
//{
//
//   for (auto & item : container)
//   {
//
//      if (item.load() == payload)
//      {
//
//         return true;
//
//      }
//
//   }
//
//   return false;
//
//}
//
//
//template < typename CONTAINER, typename PAYLOAD, typename START >
//inline auto find_payload(const CONTAINER & container, const PAYLOAD & payload, const START & start)
//{
//
//   auto p = start;
//
//   for(; p; p++)
//   {
//
//      if(::payload_of(*p) == payload)
//      {
//
//         return p;
//
//      }
//
//   }
//
//   return p;
//
//}
//
//
//template < typename CONTAINER, typename PAYLOAD >
//inline auto find_payload(const CONTAINER & container, const PAYLOAD & payload)
//{
//
//   return find_payload(container, payload, ((CONTAINER &)container).begin());
//
//}
//
//
//template < typename CONTAINER, typename PAYLOAD >
//inline bool erase_payload(CONTAINER & container, const PAYLOAD & payload)
//{
//
//   auto p = find_payload(container, payload);
//
//   if (!p)
//   {
//
//      return false;
//
//   }
//
//   container.erase(p);
//
//   return true;
//
//}


//template < typename ITERATOR >
//void delete_erase(ITERATOR & iterator)
//{
//
//   auto p = iterator.operator->();
//
//   ::acid::del(p);
//
//   ::erase(iterator);
//
//}


//template < typename ITERATOR >
//void erase(ITERATOR & iterator)
//{
//
//   iterator.m_pcontainer->erase_item(iterator.item());
//
//}






