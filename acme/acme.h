//
// Created by camilo on 2022-10-22 18:39 <3ThomasBorregaardSorensen!!
//
#pragma once



template < typename CONTAINER, typename VALUE >
inline bool contains_value(const CONTAINER & container, const VALUE & value);


template < typename ITERATOR >
void erase(ITERATOR & iterator);


template < typename ITERATOR >
void delete_erase(ITERATOR & iterator);


// template < typename CONTAINER, typename ITERATOR >
// inline void erase(CONTAINER & container, const ITERATOR & begin, const ITERATOR & last)
// {

//    if (begin)
//    {

//       container.erase(begin.item(), last.item());

//    }

// }


template < typename TYPE >
inline auto deref(const TYPE & t) { return typename TYPE::CONTAINER::dereferenced_iterator(t.item(), t.container()); }










template < typename CONTAINER, typename VALUE >
inline bool contains_value(const CONTAINER & container, const VALUE & value)
{

   auto values = container.values();

   for (auto & item : values)
   {

      if (item == value)
      {

         return true;

      }

   }

   return false;

}


template < typename CONTAINER, typename VALUE, typename START >
inline auto find_value(const CONTAINER & container, const VALUE & value, const START & start)
{

   auto p = start;

   for(; p.ok(); p++)
   {

      if (__value(*p) == value)
      {

         return p;

      }

   }

   return p;

}


template < typename CONTAINER, typename VALUE >
inline auto find_value(const CONTAINER & container, const VALUE & value)
{

   return find_value(container, value, ((CONTAINER &)container).begin());

}


template < typename CONTAINER, typename VALUE >
inline bool erase_value(CONTAINER & container, const VALUE & value)
{

   auto p = find_value(container, value);

   if (!p.ok())
   {

      return false;

   }

   auto pnonconst = (non_const < decltype(p)>) p;

   erase(pnonconst);

   return true;

}


template < typename ITERATOR >
void delete_erase(ITERATOR & iterator)
{

   auto p = iterator.operator->();

   ::acme::del(p);

   ::erase(iterator);

}


template < typename ITERATOR >
void erase(ITERATOR & iterator)
{

   iterator.m_pcontainer->erase_item(iterator.item());

}






