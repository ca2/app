#pragma once


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
inline bool remove_value(CONTAINER & container, const VALUE & value)
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

   ::aqua::del(p);

   ::erase(iterator);

}


template < typename ITERATOR >
void erase(ITERATOR & iterator)
{

   iterator.m_pcontainer->remove_item(iterator.item());

}






