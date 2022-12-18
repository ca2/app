// With iterator.h as base by camilo on 2022-09-12 04:02 <3ThomasBorregaardSorensen!!
#pragma once


//#include "_iterator.h"
//
////
////
////template < typename TYPE >
////class const_list_iterator;
////
////
////template < typename ITERATOR_TYPE >
////class list_iterator
////{
////public:
////
////
////   using ITEM = non_const < ITERATOR_TYPE >;
////
////   using TYPE = ITERATOR_TYPE;
////
////
////   using iterator = ::list_iterator < ITEM >;
////   using const_iterator = ::const_list_iterator < ITEM >;
////
////
////   ITEM * m_p;
////
////
////   list_iterator(enum_no_initialize) {};
////   list_iterator(nullptr_t) { m_p = nullptr; }
////   list_iterator() { m_p = nullptr; }
////   list_iterator(ITEM * p) : m_p(p) {}
////   list_iterator(const iterator & iterator) : m_p(iterator.get()) {}
////
////
////   ITEM * get() { return m_p; }
////   ITEM * get() const { return ((iterator *)this)->m_p; }
////
////
////   auto & operator= (TYPE * p) { m_p = p; return *this; }
////   auto & operator= (iterator p) { m_p = p.get(); return *this; }
////
////   operator ITEM * () { return get(); }
////   operator ITEM * () const { return get(); }
////
////   ITEM & operator *() { return *get(); }
////   ITEM & operator *() const { return *get(); }
////
////   ITEM * operator ->() { return get(); }
////   ITEM * operator ->() const { return get(); }
////
////   ITEM * operator &() { return get(); }
////   ITEM * operator &() const { return get(); }
////
////
////
////};
////
////
////template < typename TYPE >
////class const_list_iterator
////{
////public:
////
////
////   using ITEM = non_const < TYPE >;
////
////
////   using iterator = ::iterator < ITEM >;
////   using const_iterator = ::const_iterator < ITEM >;
////
////
////   const ITEM * m_p;
////
////
////   const_iterator(enum_no_initialize) {};
////   const_iterator(nullptr_t) { m_p = nullptr; }
////   const_iterator() { m_p = nullptr; }
////   const_iterator(const ITEM * p) : m_p(p) {}
////   const_iterator(const iterator & iterator) : m_p(iterator.m_p) {}
////
////
////   const ITEM * get() { return m_p; }
////   const ITEM * get() const { return m_p; }
////
////
////   auto & operator = (const ITEM * p) { m_p = p; return *this; }
      //auto & operator = (const THIS_ITERATOR & iterator) { m_p = iterator.m_p; return *this; }
////   auto & operator = (const const_iterator & p) { m_p = p.get(); return *this; }
////
////   operator const ITEM * () { return get(); }
////   operator const ITEM * () const { return get(); }
////
////   const ITEM & operator *() { return *get(); }
////   const ITEM & operator *() const { return *get(); }
////
////   const ITEM * operator ->() { return get(); }
////   const ITEM * operator ->() const { return get(); }
////
////   const ITEM * operator &() { return get(); }
////   const ITEM * operator &() const { return get(); }
////
////
////};
//
//
////template < typename TYPE >
////using iterator_selector = 
////   ::if_else <
////      ::is_const < TYPE >, 
////         const_iterator_base < non_const < TYPE > >, 
////         iterator_base < non_const < TYPE > > >;

template < typename BASE_ITERATOR_TYPE >
class list_iterator_item :
   public BASE_ITERATOR_TYPE
{
public:


   using iterator = ::list_iterator_item < typename BASE_ITERATOR_TYPE::iterator >;
   using const_iterator = ::list_iterator_item < typename BASE_ITERATOR_TYPE::const_iterator >;
   using THIS_ITERATOR = ::list_iterator_item < typename BASE_ITERATOR_TYPE::THIS_ITERATOR >;


   using ITEM = typename BASE_ITERATOR_TYPE::ITEM;


   using BASE_ITERATOR_TYPE::BASE_ITERATOR_TYPE;


   list_iterator_item(const iterator & iterator) : BASE_ITERATOR_TYPE(*(BASE_ITERATOR_TYPE *)&iterator) {}
   list_iterator_item(const const_iterator & iterator) : BASE_ITERATOR_TYPE(*(BASE_ITERATOR_TYPE *)&iterator) {}


   ITEM * item() { return this->get(); }
   const ITEM * item() const { return this->get(); }


};


template < typename BASE_ITERATOR_TYPE >
class list_iterator_first_item :
   public BASE_ITERATOR_TYPE
{
public:


   using iterator = ::list_iterator_first_item < typename BASE_ITERATOR_TYPE::iterator >;
   using const_iterator = ::list_iterator_first_item < typename BASE_ITERATOR_TYPE::const_iterator >;
   using THIS_ITERATOR = ::list_iterator_first_item < typename BASE_ITERATOR_TYPE::THIS_ITERATOR >;


   using ITEM = typename BASE_ITERATOR_TYPE::ITEM::ELEMENT1;


   using BASE_ITERATOR_TYPE::BASE_ITERATOR_TYPE;


   list_iterator_first_item(const iterator & iterator) : BASE_ITERATOR_TYPE(*(BASE_ITERATOR_TYPE *)&iterator) {}
   list_iterator_first_item(const const_iterator & iterator) : BASE_ITERATOR_TYPE(*(BASE_ITERATOR_TYPE *)&iterator) {}


   ITEM * item() { return &this->get()->first(); }
   const ITEM * item() const { return &this->get()->first(); }


};


template < typename BASE_ITERATOR_TYPE >
class list_iterator_second_item :
   public BASE_ITERATOR_TYPE
{
public:



   using iterator = ::list_iterator_second_item < typename BASE_ITERATOR_TYPE::iterator >;
   using const_iterator = ::list_iterator_second_item < typename BASE_ITERATOR_TYPE::const_iterator >;
   using THIS_ITERATOR = ::list_iterator_second_item < typename BASE_ITERATOR_TYPE::THIS_ITERATOR >;


   using ITEM = typename BASE_ITERATOR_TYPE::ITEM::ELEMENT2;


   using BASE_ITERATOR_TYPE::BASE_ITERATOR_TYPE;


   list_iterator_second_item(const iterator & iterator) : BASE_ITERATOR_TYPE(*(BASE_ITERATOR_TYPE *)&iterator) {}
   list_iterator_second_item(const const_iterator & iterator) : BASE_ITERATOR_TYPE(*(BASE_ITERATOR_TYPE *)&iterator) {}


   ITEM * item() { return &this->get()->second(); }
   const ITEM * item() const { return &this->get()->second(); }


};


template < typename BASE_ITERATOR_TYPE >
class make_list_iterator :
   public BASE_ITERATOR_TYPE
{
public:


   using ITERATOR_TYPE = BASE_ITERATOR_TYPE;


   using ITEM_POINTER = typename ITERATOR_TYPE::ITEM_POINTER;
   using LIST_ITEM_POINTER = typename ITERATOR_TYPE::ITEM_POINTER;

   using BASE_ITERATOR = typename BASE_ITERATOR_TYPE::iterator;
   using BASE_CONST_ITERATOR = typename BASE_ITERATOR_TYPE::const_iterator;
   using BASE_THIS_ITERATOR = typename BASE_ITERATOR_TYPE::THIS_ITERATOR;

   using iterator = ::make_list_iterator < typename BASE_ITERATOR_TYPE::iterator >;
   using const_iterator = ::make_list_iterator < typename BASE_ITERATOR_TYPE::const_iterator >;
   using THIS_ITERATOR = ::make_list_iterator < typename BASE_ITERATOR_TYPE::THIS_ITERATOR >;


   using ITEM = typename BASE_ITERATOR_TYPE::ITEM;
   using CONST_ITEM = const ITEM;


   using BASE_ITERATOR_TYPE::BASE_ITERATOR_TYPE;


   make_list_iterator(const iterator & iterator) : BASE_ITERATOR_TYPE(*(BASE_ITERATOR_TYPE *)&iterator) {}
   make_list_iterator(const const_iterator & iterator) : BASE_ITERATOR_TYPE(*(BASE_ITERATOR_TYPE *)&iterator) {}


   constexpr ::index index() const
   {

      ::index i = -1;

      auto iterator = *this;

      while (iterator.is_set())
      {

         i++;

         iterator--;

      }

      return i;
      
   }


   static constexpr bool difference(::count & c, const_iterator a, const_iterator b)
   {

      c = 0;

      while (::is_set(b) && b != a)
      {

         c++;

         b++;

      }

      return b.is_set();

   }


   constexpr ::count operator - (const_iterator iterator) const
   {

      ::count c;

      if (difference(c, *this, iterator))
      {

         return c;

      }

      if (difference(c, iterator, *this))
      {

         return -c;

      }

      throw_exception(error_failed, "iterators aren't from same list");

      return -1;

   }


   THIS_ITERATOR & operator += (::count c)
   { 
      
      while (c-- > 0)
      {

         ++ * this;

      }
      
      
      return *this; 
   
   }


   constexpr THIS_ITERATOR operator + (::count c) const
   {

      auto iterator = *this;

      iterator += c;

      return iterator;

   }


   THIS_ITERATOR & operator -= (::count c)
   { 
      
      while (c-- > 0)
      { 
         
         --*this; 
      
      } 
      
      return *this; 
   
   }


   constexpr THIS_ITERATOR operator - (::count c) const
   {

      auto iterator = *this;

      iterator += c;

      return iterator;

   }

   THIS_ITERATOR & operator =(ITEM_POINTER p) { this->m_p = p;  return *this; }
   THIS_ITERATOR & operator =(const iterator & iterator) { this->m_p = iterator.m_p;  return *this;}
   THIS_ITERATOR & operator =(const const_iterator & iterator) { this->m_p = iterator.m_p;  return *this; }
   THIS_ITERATOR & operator =(nullptr_t) { this->m_p = nullptr;  return *this; }



   constexpr bool operator == (THIS_ITERATOR iterator) const
   {

      return this->get() == iterator.get();

   }

   
   constexpr std::strong_ordering operator <=> (const_iterator iterator) const
   {

      return this->index() <=> iterator.index();

   }


   THIS_ITERATOR & operator ++()
   {

      *this = this->next();

      return *this;

   }


   THIS_ITERATOR operator ++(int)
   {

      auto iterator = *this;

      ++ * this;

      return iterator;

   }


   THIS_ITERATOR & operator --()
   {

      *this = this->back();

      return *this;

   }


   THIS_ITERATOR operator --(int)
   {

      auto iterator = *this;

      -- * this;

      return iterator;

   }


   constexpr bool is_set() const
   {

      return ::is_set(this) && ::is_set(this->get());

   }

   constexpr bool is_null() const
   {

      return !is_set();

   }

   constexpr bool is_ok() const
   {

      return is_set();

   }


   bool operator !() const { return ::is_set(this->get()); }


   ITEM & operator *() { return *this->item(); }
   CONST_ITEM & operator *() const { return *this->item(); }


   auto operator ->() { return this->item(); }
   auto operator ->() const { return this->item(); }


   THIS_ITERATOR back() { return this->get()->back(); }
   THIS_ITERATOR back() const { return this->get()->back(); }

   THIS_ITERATOR next() { return this->get()->next(); }
   THIS_ITERATOR next() const { return this->get()->next(); }


};


template < typename ITERATOR_TYPE >
::index index_as_of_iterator(::make_list_iterator < ITERATOR_TYPE > iterator)
{
   
   return iterator.index();

}




template < typename LIST_ITEM >
using list_iterator = ::make_list_iterator < ::list_iterator_item < ::iterator_base < LIST_ITEM > > >;

template < typename LIST_ITEM >
using const_list_iterator = ::make_list_iterator < ::list_iterator_item < ::const_iterator_base < LIST_ITEM > > >;




template < typename LIST_ITEM >
using first_item_list_iterator = ::make_list_iterator < ::list_iterator_first_item < ::iterator_base < LIST_ITEM > > >;

template < typename LIST_ITEM >
using const_first_item_list_iterator = ::make_list_iterator < ::list_iterator_first_item < ::const_iterator_base < LIST_ITEM > > >;



template < typename LIST_ITEM >
using second_item_list_iterator = ::make_list_iterator < ::list_iterator_second_item < ::iterator_base < LIST_ITEM > > >;

template < typename LIST_ITEM >
using const_second_item_list_iterator = ::make_list_iterator < ::list_iterator_second_item < ::const_iterator_base < LIST_ITEM > > >;



