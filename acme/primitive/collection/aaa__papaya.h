#pragma once


template < typename CONTAINER, typename PAYLOAD >
inline bool contains_payload(const CONTAINER & container, const PAYLOAD & payload);

      
//template < typename ITERATOR >
//void erase(ITERATOR & iterator);


//template < typename ITERATOR >
//void delete_erase(ITERATOR & iterator);


template < typename CONTAINER, typename ITERATOR >
inline void erase(CONTAINER & container, const ITERATOR & begin, const ITERATOR & last)
{ 
         
   if (begin)
   {

      container.erase(begin.item(), last.item());

   }

}


template < typename TYPE >
inline auto deref(const TYPE & t) { return typename TYPE::CONTAINER::dereferenced_iterator(t.item(), t.container()); }






