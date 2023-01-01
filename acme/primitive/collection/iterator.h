// Created by camilo on 2022-12-07 16:42 <3ThomasBorregaardSorensen!!
#pragma once


template < typename TYPE >
::index index_as_of_iterator(const TYPE * p)
{

   return (::iptr)p;

}


template < typename TYPE >
TYPE * next_as_of_iterator(const TYPE * p)
{

   return p + 1;

}


template < typename TYPE >
::count count_as_of_iterator(const TYPE * p, const TYPE * pBegin)
{

   return ::index_as_of_iterator(p) - ::index_as_of_iterator(pBegin);

}



template < typename TYPE >
class const_iterator_base;


template < typename ITERATOR_TYPE >
class iterator_base
{
public:

   
   using TYPE_TAG = ITERATOR_TYPE_TAG;


   using ITEM_POINTER = non_const < ITERATOR_TYPE >;
   using CONST_ITEM_POINTER = const_of < ITERATOR_TYPE >;
   using THIS_ITEM_POINTER = ITERATOR_TYPE;


   using ITEM = dereference < ITEM_POINTER >;


   using TYPE = ITERATOR_TYPE;


   using iterator = ::iterator_base < ITEM_POINTER >;
   using const_iterator = ::const_iterator_base < ITEM_POINTER >;
   using THIS_ITERATOR = ::iterator_base < ITERATOR_TYPE >;


   ITEM_POINTER m_p;


   iterator_base(enum_no_initialize) {};
   iterator_base(nullptr_t) { m_p = nullptr; }
   iterator_base() { m_p = nullptr; }
   iterator_base(CONST_ITEM_POINTER p) : m_p((THIS_ITEM_POINTER)p) {}
   iterator_base(const const_iterator & iterator) : m_p((ITEM_POINTER)iterator.get()) {}


   auto & get() { return m_p; }
   auto & get() const { return m_p; }


   auto & topic() { return this->m_p->topic(); }
   auto & topic() const { return this->m_p->topic(); }

//https://www.artima.com/articles/the-safe-bool-idiom BEGIN
private:

   typedef void (const_iterator:: * bool_type)() const;

   void this_type_does_not_support_comparisons() const {}

public:

   operator bool_type() const { return ::is_set(m_p) ? &const_iterator::this_type_does_not_support_comparisons : 0; }
   //https://www.artima.com/articles/the-safe-bool-idiom END

   auto & operator= (TYPE * p) { m_p = p; return *this; }
   auto & operator= (iterator p) { m_p = p.get(); return *this; }


   auto & operator *() { return *topic(); }
   auto & operator *() const { return *topic(); }


   auto operator ->() { return topic(); }
   auto operator ->() const { return topic(); }


};


template < typename ITERATOR_TYPE >
class const_iterator_base
{
public:


   using TYPE_TAG = ITERATOR_TYPE_TAG;


   using ITEM_POINTER = non_const < ITERATOR_TYPE >;
   using CONST_ITEM_POINTER = const_of < ITERATOR_TYPE >;
   using THIS_ITEM_POINTER = ITERATOR_TYPE;


   using ITEM = dereference < ITEM_POINTER >;


   using iterator = ::iterator_base < ITEM_POINTER >;
   using const_iterator = ::const_iterator_base < ITEM_POINTER >;
   using THIS_ITERATOR = ::const_iterator_base < ITERATOR_TYPE >;


   CONST_ITEM_POINTER m_p;


   const_iterator_base(enum_no_initialize) {};
   const_iterator_base(nullptr_t) { m_p = nullptr; }
   const_iterator_base() { m_p = nullptr; }
   const_iterator_base(CONST_ITEM_POINTER p) : m_p((THIS_ITEM_POINTER)p) {}
   const_iterator_base(const const_iterator & iterator) : m_p(iterator.m_p) {}

   //https://www.artima.com/articles/the-safe-bool-idiom BEGIN
private:

   typedef void (const_iterator:: * bool_type)() const;

   void this_type_does_not_support_comparisons() const {}

public:

   operator bool_type() const { return ::is_set(m_p) ? &const_iterator::this_type_does_not_support_comparisons : 0; }
   //https://www.artima.com/articles/the-safe-bool-idiom END

   auto & get() { return m_p; }
   auto & get() const { return m_p; }


   auto & topic() { return this->m_p->topic(); }
   auto & topic() const { return this->m_p->topic(); }


   auto & operator = (const ITEM_POINTER p) { m_p = p; return *this; }
   auto & operator = (const iterator & p) { m_p = p.get(); return *this; }
   auto & operator = (const const_iterator & p) { m_p = p.get(); return *this; }


   auto & operator *() { return *topic(); }
   auto & operator *() const { return *topic(); }


   auto operator ->() { return topic(); }
   auto operator ->() const { return topic(); }


};


//template < typename TYPE >
//using iterator_selector = 
//   ::if_else <
//      ::is_const < TYPE >, 
//         const_iterator_base < non_const < TYPE > >, 
//         iterator_base < non_const < TYPE > > >;



//template < typename TYPE >
//using iterator = make_iterator < iterator_base < TYPE > >;
//
//
//template < typename TYPE >
//using const_iterator = make_iterator < const_iterator_base < TYPE > >;



//template < typename ITERATOR_TYPE >
//::index iterator_offset_of(::make_iterator < ITERATOR_TYPE > a, ::make_iterator < ITERATOR_TYPE > b)
//{
//
//   return a - b;
//
//}


template < primitive_iterator ITERATOR >
constexpr bool is_set(const ITERATOR & iterator)
{

   return ::is_set(iterator.m_p);

}



