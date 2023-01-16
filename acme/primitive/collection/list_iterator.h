// With iterator.h as base by camilo on 2022-09-12 04:02 <3ThomasBorregaardSørensen!!
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
class list_iterator_node :
   public BASE_ITERATOR_TYPE
{
public:


   using iterator = ::list_iterator_node < typename BASE_ITERATOR_TYPE::iterator >;
   using const_iterator = ::list_iterator_node < typename BASE_ITERATOR_TYPE::const_iterator >;
   using this_iterator = ::list_iterator_node < BASE_ITERATOR_TYPE >;


   using ITEM = typename BASE_ITERATOR_TYPE::ITEM;
   using node = BASE_ITERATOR_TYPE;


   using ITEM_POINTER = typename BASE_ITERATOR_TYPE::ITEM_POINTER;
   using CONST_ITEM_POINTER = typename BASE_ITERATOR_TYPE::CONST_ITEM_POINTER;
   using THIS_ITEM_POINTER = typename BASE_ITERATOR_TYPE::THIS_ITEM_POINTER;


   using BASE_ITERATOR_TYPE::BASE_ITERATOR_TYPE;


   list_iterator_node(CONST_ITEM_POINTER p) : BASE_ITERATOR_TYPE(p) {}
   list_iterator_node(const iterator & iterator) : BASE_ITERATOR_TYPE(*(BASE_ITERATOR_TYPE *)&iterator) {}
   list_iterator_node(const const_iterator & iterator) : BASE_ITERATOR_TYPE(*(BASE_ITERATOR_TYPE *)&iterator) {}


   auto & topic() { return BASE_ITERATOR_TYPE::topic(); }
   auto & topic() const { return BASE_ITERATOR_TYPE::topic(); }


};


template < typename BASE_ITERATOR_TYPE >
class list_iterator_element1 :
   public BASE_ITERATOR_TYPE
{
public:


   using iterator = ::list_iterator_element1 < typename BASE_ITERATOR_TYPE::iterator >;
   using const_iterator = ::list_iterator_element1 < typename BASE_ITERATOR_TYPE::const_iterator >;
   using THIS_ITERATOR = ::list_iterator_element1 < typename BASE_ITERATOR_TYPE::THIS_ITERATOR >;


   using ITEM = typename BASE_ITERATOR_TYPE::ITEM::ELEMENT1;
   using node = ITEM;


   using BASE_ITERATOR_TYPE::BASE_ITERATOR_TYPE;


   list_iterator_element1(const iterator & iterator) : BASE_ITERATOR_TYPE(*(BASE_ITERATOR_TYPE *)&iterator) {}
   list_iterator_element1(const const_iterator & iterator) : BASE_ITERATOR_TYPE(*(BASE_ITERATOR_TYPE *)&iterator) {}


   auto & topic() { return this->m_p->item(); }
   auto & topic() const { return this->m_p->item(); }


};


template < typename BASE_ITERATOR_TYPE >
class list_iterator_element2 :
   public BASE_ITERATOR_TYPE
{
public:



   using iterator = ::list_iterator_element2 < typename BASE_ITERATOR_TYPE::iterator >;
   using const_iterator = ::list_iterator_element2 < typename BASE_ITERATOR_TYPE::const_iterator >;
   using THIS_ITERATOR = ::list_iterator_element2 < typename BASE_ITERATOR_TYPE::THIS_ITERATOR >;


   using ITEM = typename BASE_ITERATOR_TYPE::ITEM::ELEMENT2;
   using node = ITEM;


   using BASE_ITERATOR_TYPE::BASE_ITERATOR_TYPE;


   list_iterator_element2(const iterator & iterator) : BASE_ITERATOR_TYPE(*(BASE_ITERATOR_TYPE *)&iterator) {}
   list_iterator_element2(const const_iterator & iterator) : BASE_ITERATOR_TYPE(*(BASE_ITERATOR_TYPE *)&iterator) {}


   auto & topic() { return this->m_p->payload(); }
   auto & topic() const { return this->m_p->payload(); }


};


template < typename BASE_ITERATOR_TYPE >
class make_list_iterator :
   public BASE_ITERATOR_TYPE
{
public:


   using ITERATOR_TYPE = BASE_ITERATOR_TYPE;


   using ITEM_POINTER = typename ITERATOR_TYPE::ITEM_POINTER;
   using CONST_ITEM_POINTER = typename ITERATOR_TYPE::CONST_ITEM_POINTER;
   using LIST_ITEM_POINTER = typename ITERATOR_TYPE::ITEM_POINTER;


   using BASE_ITERATOR = typename BASE_ITERATOR_TYPE::iterator;
   using BASE_CONST_ITERATOR = typename BASE_ITERATOR_TYPE::const_iterator;
   using BASE_THIS_ITERATOR = typename BASE_ITERATOR_TYPE::THIS_ITERATOR;


   using iterator = ::make_list_iterator < typename BASE_ITERATOR_TYPE::iterator >;
   using const_iterator = ::make_list_iterator < typename BASE_ITERATOR_TYPE::const_iterator >;
   using THIS_ITERATOR = ::make_list_iterator < BASE_ITERATOR_TYPE >;


   using node = typename BASE_ITERATOR_TYPE::node;
   using const_node = const node;


   using ITEM = typename BASE_ITERATOR_TYPE::ITEM;
   using CONST_ITEM = const ITEM;


   using BASE_ITERATOR_TYPE::BASE_ITERATOR_TYPE;


   make_list_iterator(CONST_ITEM_POINTER itempointer) : BASE_ITERATOR_TYPE(itempointer) {}
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


   template < primitive_integral INTEGRAL >
   THIS_ITERATOR & operator += (INTEGRAL c)
   { 
      
      while (c-- > 0)
      {

         ++ * this;

      }
      
      
      return *this; 
   
   }


   template < primitive_integral INTEGRAL >
   constexpr THIS_ITERATOR operator + (INTEGRAL c) const
   {

      auto iterator = *this;

      iterator += c;

      return iterator;

   }


   template < primitive_integral INTEGRAL >
   THIS_ITERATOR & operator -= (INTEGRAL c)
   { 
      
      while (c-- > 0)
      { 
         
         --*this; 
      
      } 
      
      return *this; 
   
   }


   template < primitive_integral INTEGRAL >
   constexpr THIS_ITERATOR operator - (INTEGRAL c) const
   {

      auto iterator = *this;

      iterator += c;

      return iterator;

   }


   constexpr ::count operator - (THIS_ITERATOR iterator) const
   {

      {

         auto i = *this;

         ::count c = 0;

         while (i.is_set())
         {

            if (i == iterator)
            {

               return c;

            }

            i--;

            c++;

         }

      }

      {

         auto i = iterator;

         ::count c = 0;

         while (i.is_set())
         {

            if (i == *this)
            {

               return -c;

            }

            i--;

            c++;

         }

      }

      throw "iterator is not part of list";

   }


   THIS_ITERATOR & operator =(ITEM_POINTER p) { this->m_p = p;  return *this; }
   THIS_ITERATOR & operator =(const iterator & iterator) { this->m_p = (ITEM_POINTER) iterator.get();  return *this;}
   THIS_ITERATOR & operator =(const const_iterator & iterator) { this->m_p = (ITEM_POINTER) iterator.get();  return *this; }
   THIS_ITERATOR & operator =(nullptr_t) { this->m_p = nullptr;  return *this; }


   constexpr bool operator == (THIS_ITERATOR iterator) const
   {

      return this->get() == iterator.get();

   }

   
   constexpr std::strong_ordering operator <=> (const THIS_ITERATOR & iterator) const
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

   constexpr bool is_set() const { return ::is_set(this) && ::is_set(this->get());  }
   constexpr bool is_null() const { return !is_set(); }
   constexpr bool is_ok() const { return is_set(); }
   constexpr bool operator !() const { return this->is_null(); }
   //https://www.artima.com/articles/the-safe-bool-idiom BEGIN
   typedef void (const_iterator:: * bool_type)() const;
   constexpr void this_type_does_not_support_comparisons() const {}
   constexpr operator bool_type() const { return this->is_set() ? &const_iterator::this_type_does_not_support_comparisons : 0; }
   //https://www.artima.com/articles/the-safe-bool-idiom END



   auto & operator *() { return this->topic(); }
   auto & operator *() const { return this->topic(); }


   auto operator ->() { return &this->topic(); }
   auto operator ->() const { return &this->topic(); }


   auto & back() { return this->get()->back(); }
   auto & back() const { return this->get()->back(); }

   auto & next() { return this->get()->next(); }
   auto & next() const { return this->get()->next(); }


};


template < typename ITERATOR_TYPE >
::index index_as_of_iterator(::make_list_iterator < ITERATOR_TYPE > iterator)
{
   
   return iterator.index();

}


template < typename BASE_ITERATOR_TYPE >
inline auto & get(make_list_iterator<BASE_ITERATOR_TYPE> & p)
{

   return p.topic();

}


template < typename BASE_ITERATOR_TYPE >
inline auto & get(const make_list_iterator<BASE_ITERATOR_TYPE> & p)
{

   return p.topic();

}
//template < typename LIST_ITEM >
//using list_iterator = ::make_list_iterator < ::list_iterator_item < ::iterator_base < LIST_ITEM > > >;

//template < typename LIST_ITEM >
//using const_list_iterator = ::make_list_iterator < ::list_iterator_item < ::const_iterator_base < LIST_ITEM > > >;


template < typename LIST_ITEM >
using list_iterator = ::make_list_iterator < ::list_iterator_node < ::iterator_base < LIST_ITEM > > >;

template < typename LIST_ITEM >
using const_list_iterator = ::make_list_iterator < ::list_iterator_node < ::const_iterator_base < LIST_ITEM > > >;



template < typename LIST_ITEM >
using element1_list_iterator = ::make_list_iterator < ::list_iterator_element1 < ::iterator_base < LIST_ITEM > > >;

template < typename LIST_ITEM >
using const_element1_list_iterator = ::make_list_iterator < ::list_iterator_element1 < ::const_iterator_base < LIST_ITEM > > >;



template < typename LIST_ITEM >
using element2_list_iterator = ::make_list_iterator < ::list_iterator_element2 < ::iterator_base < LIST_ITEM > > >;

template < typename LIST_ITEM >
using const_element2_list_iterator = ::make_list_iterator < ::list_iterator_element2 < ::const_iterator_base < LIST_ITEM > > >;



