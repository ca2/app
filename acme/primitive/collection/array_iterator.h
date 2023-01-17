// From iterator.h as base by camilo on 2022-09-12 20:09 <3ThomasBorregaardSørensen!!
#pragma once


template < typename BASE_ITERATOR >
class make_array_iterator :
   public BASE_ITERATOR
{
public:


   using ITERATOR_TYPE = BASE_ITERATOR;


   using ITEM = ITERATOR_TYPE::ITEM;


   using ITERATOR = ::make_iterator < typename BASE_ITERATOR::ITERATOR >;
   using CONST_ITERATOR = ::make_iterator < typename BASE_ITERATOR::CONST_ITERATOR >;
   using THIS_ITERATOR = ::make_iterator < BASE_ITERATOR >;


   using ITERATOR_TYPE::ITERATOR_TYPE;


   constexpr ::count operator - (const CONST_ITERATOR & iterator) const
   {

      return ::count_as_of_iterator(iterator.get(), ITERATOR_TYPE::get());

   }


   //constexpr bool operator == (const CONST_ITERATOR & iterator) const
   //{

   //   return ITERATOR::get() == iterator.get();

   //}


   //constexpr std::strong_ordering operator <=> (const CONST_ITERATOR & iterator) const
   //{

   //   return ITERATOR::get() <=> iterator.get();

   //}


   THIS_ITERATOR & operator ++()
   {

      ITERATOR_TYPE::m_p = ::next_as_of_iterator(ITERATOR_TYPE::get());

      return *this;

   }


   THIS_ITERATOR operator ++(int)
   {

      ITERATOR_TYPE item(*this);

      ++(*this);

      return item;

   }





};



template < typename TYPE >
struct get_array_iterator
{

   using type = ::make_array_iterator < ::iterator_base < TYPE > >;

};


template < typename TYPE >
struct get_array_iterator< TYPE * >
{

   using type = TYPE *;

};


template < typename TYPE >
struct get_array_const_iterator
{

   using type = ::make_array_iterator < ::const_iterator_base < TYPE > >;

};


template < typename TYPE >
struct get_array_const_iterator< TYPE * >
{

   using type = const TYPE *;

};





//template < typename TYPE >
//constexpr bool range_is_ok(const TYPE * begin, const TYPE * end)
//{
//
//   return !::range_is_end(begin_end);
//
//}



