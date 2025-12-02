//
// Created by camilo on 2025-08-12 16:28 <3ThomasBorregaardSørensen!!
//
#pragma once


template < typename TYPE >
class pointer_rear_iterator
{
public:


   using ITEM = non_const < TYPE >;
   using ITEM_POINTER = ITEM *;

   using iterator = ::pointer_rear_iterator < ITEM >;
   using const_iterator = ::pointer_rear_iterator < const ITEM >;


   TYPE* m_p;


   pointer_rear_iterator() { m_p = nullptr; }
   pointer_rear_iterator(const ITEM * p) { m_p = (TYPE *) p; }
   pointer_rear_iterator(const iterator & i) { m_p = (TYPE *)i.m_p; }
   pointer_rear_iterator(const const_iterator & i) { m_p = (TYPE *)i.m_p; }


   auto& operator *() { return *m_p; }
   auto& operator *() const { return *m_p; }
   auto operator ->() { return m_p; }
   auto operator ->() const { return m_p; }

   pointer_rear_iterator & operator ++()
   {
      m_p--;
      return *this;

   }
   pointer_rear_iterator& operator --()
   {
      m_p++;
      return *this;

   }

   pointer_rear_iterator operator ++(int)
   {
      auto p = *this;
      m_p--;

      return p;

   }
   pointer_rear_iterator operator --(int)
   {
      auto p = *this;
      m_p++;

      return p;

   }
   template < prototype_integral INTEGRAL >
   pointer_rear_iterator operator +(INTEGRAL i)
   {

      return m_p - i;

   }
   template < prototype_integral INTEGRAL >
   pointer_rear_iterator operator -(INTEGRAL i)
   {

      return m_p + i;

   }

   template < prototype_integral INTEGRAL >
   pointer_rear_iterator & operator +=(INTEGRAL i)
   {
      m_p -= i;
      return *this;

   }
   template < prototype_integral INTEGRAL >
   pointer_rear_iterator & operator -=(INTEGRAL i)
   {
      m_p += i;
      return *this;

   }


   bool operator ==(const pointer_rear_iterator& p) const { return m_p == p.m_p; }
   bool operator ==(const TYPE * p) const { return m_p == p; }
   ::std::strong_ordering operator <=>(const pointer_rear_iterator& p) const { return this->m_p <=> p.m_p; }

   ::collection::count operator - (const pointer_rear_iterator& p) const { return this->m_p - p.m_p; }

};
